/*
  rotary.c: helper functions to read the voltage of a potenciometer
  
  Copyright (c) 2019 Gustavo Santana <gmsantana@inf.ufrgs.br>

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

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <galileo2io.h>

#include "rotary.h"

struct sensors
{
        uint16_t pot;       /* be:u12/16>>0 */
        int64_t timestamp;  /* le:s64/64>>0 */
};

int rotary_open(ROTARY *rotary, const char device_path[], const char scale_path[])
{
    // one shot: "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
    // continuous: "/dev/iio:device0"
    if((rotary->fd=open(device_path,O_RDONLY)) < 0)
    {
            perror("error opening rotary device path");
            return -1;
    }
    
    if (pgets(data_str, sizeof data_str, scale_path) < 0) // scale: "/sys/bus/iio/devices/iio:device0/in_voltage0_scale"
    {
    	perror("error getting rotary scale.")
    	return -1;
    }

    rotary->scale = atof(data_str)/1000.0;

    return 0;
}

int rotary_one_shot_read(ROTARY rotary)
{
	int raw;
	char data_str[80];

	lseek(rotary.fd, 0, SEEK_SET);
    read(rotary.fd, data_str, sizeof data_str);
    raw = atoi(data_str);

    return raw;
}

int rotary_continuous_read(ROTARY rotary, int sample_size, int sampling_rate)
{
    static struct sensors data[sample_size];
    int i;
    int samples;
    int average_read = 0;
    char data_str[80];
    char path_str[80];
    
    int    fd    = rotary.fd;
    double scale = rotary.scale;

    pputs("/sys/bus/iio/devices/iio:device0/buffer/enable","0");
            
    snprintf(path_str, sizeof path_str, "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en");
    pputs(path_str, "1");
    pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en", "1");

    snprintf(data_str, sizeof data_str, "%d", samples);
    pputs("/sys/bus/iio/devices/iio:device0/buffer/length", data_str);
    
    pgets(data_str, sizeof data_str, "/sys/bus/iio/devices/trigger1/name");
    pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger", data_str);

    snprintf(data_str, sizeof data_str, "%d", (int)round(1.0/sampling_rate));
    pputs("/sys/bus/iio/devices/trigger1/frequency", data_str);

    pputs("/sys/bus/iio/devices/iio:device0/buffer/enable", "1");

    sleep(ceil(sample_size*sampling_rate));

    pputs("/sys/bus/iio/devices/iio:device0/buffer/enable", "0");
    
    pputs("/sys/bus/iio/devices/iio:device0/trigger/current_trigger", "\n");
    
    samples = read(fd,data, sizeof data)/sizeof(struct sensors);
    close(fd);
    
    pputs("/sys/bus/iio/devices/iio:device0/buffer/length", "2");
    
    snprintf(path_str, sizeof path_str, "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en");
    pputs(path_str, "0");

    pputs("/sys/bus/iio/devices/iio:device0/scan_elements/in_timestamp_en", "0");
    
    for(i = 0; i < samples; i++)
    {
        pot = bswap_16(data[0].pot) * scale;
        average_read = average_read + pot;
    }

    average_read = average_read / samples;

    return average_read;
}

int rotary_close(ROTARY *rotary)
{
	close(rotary->fd);

	return 0;
}