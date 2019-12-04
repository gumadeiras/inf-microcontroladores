/*
  adc.c: helper functions to read using the galileo adc
  
  Copyright (c) 2019 Gustavo Santana, Lúcio Franco

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#include <byteswap.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <galileo2io.h>

#include "adc.h"

#define SAMPLING_PERIOD 0.00025 // 0.25ms = 4kHz
#define DATA_POINTS 16000 // 16k samples = 4s @ 4kHz

struct sensors
{
        uint16_t mic;       /* be:u12/16>>0 */
        int64_t timestamp;  /* le:s64/64>>0 */
};

int adc_open(ADC *adc, const char device_path[], const char scale_path[])
{
    // one shot: "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
    // continuous: "/dev/iio:device0"
    char data_str[80];

    if((adc->fd=open(device_path,O_RDONLY)) < 0)
    {
            perror("error opening adc device path");
            return -1;
    }
    
    if (pgets(data_str, sizeof data_str, scale_path) < 0) // scale: "/sys/bus/iio/devices/iio:device0/in_voltage0_scale" 
    {
    	perror("error getting adc scale.");
    	return -1;
    }

    adc->scale = atof(data_str)/1000.0;

    return 0;
}

int adc_one_shot_read(ADC adc)
{
	int raw;
	char data_str[80];

	lseek(adc.fd, 0, SEEK_SET);
    read(adc.fd, data_str, sizeof data_str);
    raw = atoi(data_str);

    return raw;
}

int adc_continuous_read_begin()
{
    char data_str[80];
    double scale;
    int fd;
    static struct sensors data[DATA_POINTS];
    int i;
    int samples;
    FILE *file;
    char path_str[80];

    pgets(data_str,sizeof data_str, "/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
    scale = atof(data_str)/1000.0;
    printf("scale: %d\n", scale);

    pputs("/sys/bus/iio/devices/iio:device0/buffer/enable","0");
    
    snprintf(path_str,sizeof path_str,"/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en");
    pputs(path_str,"1");
    
    pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en","1");

    snprintf(data_str,sizeof data_str,"%d",DATA_POINTS);
    pputs("/sys/bus/iio/devices/iio:device0/buffer/length",data_str);
    

    pgets(data_str,sizeof data_str,"/sys/bus/iio/devices/trigger0/name");
    pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger",data_str);

    snprintf(data_str,sizeof data_str,"%d",(int)(1.0/SAMPLING_PERIOD));
    // printf("%s\n", data_str);
    pputs("/sys/bus/iio/devices/trigger0/frequency",data_str);

    pputs("/sys/bus/iio/devices/iio:device0/buffer/enable","1");

    
    sleep((int)(DATA_POINTS*SAMPLING_PERIOD));
    
    pputs("/sys/bus/iio/devices/iio:device0/buffer/enable","0");
    
    pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger","\n");
    
    if((fd=open("/dev/iio:device0",O_RDONLY)) < 0)
    {
            perror("Opening /dev/iio:device0:");
            return -1;
    }
    
    samples=read(fd,data,sizeof data)/sizeof(struct sensors);
    close(fd);
    printf("samples recorded: %d\n", samples);
    
    pputs("/sys/bus/iio/devices/iio:device0/buffer/length","2");
    
    pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en", "0");

    pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en", "0");
    
    if((file=fopen("data.pcm","w")) == NULL)
    {
            perror("Opening output file:");
            return -1;
    }

    for(i=0;i < samples;i++)
    {
        data[i].mic=bswap_16(data[i].mic);
        // printf("%f\t%f\n", data[i].mic*scale, (data[i].timestamp-data[0].timestamp)*1e-9);
        printf("%f\n", data[i].mic*scale);
        fprintf(file, "%f\n", data[i].mic*scale);
        // fwrite(data[i].mic*scale, 1, sizeof(data[i].mic*scale), file);
    }

    fclose(file);
    
    return 0;
}

int adc_close(ADC *adc)
{
	close(adc->fd);

	return 0;
}