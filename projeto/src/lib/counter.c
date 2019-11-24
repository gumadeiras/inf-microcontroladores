/*
  counter.c: helper functions for SPI communication with the LS7366 quadrature encoder
  
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


#include <counter.h>


int counter_open(COUNTER *counter, char *spi, char *ss)
{
    if((counter->fd_spi = open(spi, O_RDWR)) < 0)
    {
        printf("Error opening spi.\n");
        exit(-1);
    }
    
    if((counter->fd_ss = open(ss, O_WRONLY)) < 0) {
        printf("Error opening SS.\n");
        exit(-1);
    }

    return 0;
}

int counter_byte_write(COUNTER counter, unsigned char data, unsigned char op_code)
{
    // slave select high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS HIGH\n");
        return -1;
    }
    // slave select low
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "0", 1) < 0) {
        printf("error setting SS LOW\n");
        return -1;
    }

    // send command
    if(write(counter.fd_spi, &op_code, sizeof op_code) < 0) {
        printf("error writing to counter.\n");
        return -1;
    }
    // send data
    if(write(counter.fd_spi, &data, sizeof data) < 0) {
        printf("error writing to counter.\n");
        return -1;
    }

    // slave select high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS HIGH\n");
        return -1;
    }

    return 0;
}

int counter_init(COUNTER counter)
{
    uint8_t mode = SPI_MODE_0;
    uint8_t lsb = 0;
    uint8_t bpw = 8;
    uint32_t rate = SPI_FREQUENCY;
    unsigned char mdr0, mdr1;

    if(ioctl(counter.fd_spi, SPI_IOC_WR_MODE, &mode) < 0){
        printf("error setting SPI write mode.\n");
        return -1;
    }

    if(ioctl(counter.fd_spi, SPI_IOC_WR_LSB_FIRST, &lsb)){
        printf("error setting SPI LSB first.\n");
        return -1;
    }

    if(ioctl(counter.fd_spi, SPI_IOC_WR_BITS_PER_WORD, &bpw)){
        printf("error setting SPI bits per word.\n");
        return -1;
    }

    if(ioctl(counter.fd_spi, SPI_IOC_WR_MAX_SPEED_HZ, &rate)){
        printf("error setting SPI max speed.\n");
        return -1;
    }
    
    mdr0 = QUADRX4|FREE_RUN|DISABLE_INDX|FILTER_2;
    mdr1 = BYTE_4|EN_CNTR|NO_FLAGS;
    if(counter_byte_write(counter, mdr0, WRITE_MDR0) < 0){
        printf("Error writing to MDR0.\n");
        return -1;
    }

    if(counter_byte_write(counter, mdr1, WRITE_MDR1)){
        printf("Error writing to MDR1.\n");
        return -1;
    }

    return 0;
}

unsigned char counter_byte_read(COUNTER counter, unsigned char op_code)
{
    unsigned char data;

    // slave select high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS HIGH\n");
        return -1;
    }
    // slave select low
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "0", 1) < 0) {
        printf("error setting SS LOW\n");
        return -1;
    }

    // send command
    if(write(counter.fd_spi, &op_code, sizeof op_code) < 0) {
        printf("error writing to counter.\n");
        return -1;
    }

    // read data
    lseek(counter.fd_spi, 0, SEEK_SET);
    while(read(counter.fd_spi, &data, 1) != 1);

    // slave select high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS LOW\n");
        return -1;
    }

    return data;   
}

int counter_reset(COUNTER counter)
{
    unsigned char op_code = CLR_CNTR;

    // slave select high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS HIGH\n");
        return -1;
    }
    // slave select low
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "0", 1) < 0) {
        printf("error setting SS LOW\n");
        return -1;
    }

    if(write(counter.fd_spi, &op_code, sizeof op_code) < 0){
        printf("error reseting counter.\n");
        return -1;
    }

    // slave select high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS LOW\n");
        return -1;
    }

    return 0;  
}

int counter_read(COUNTER counter)
{
    unsigned char c1, c2, c3, c4;
    unsigned long counter_value;
    char read_opcode = READ_CNTR;

    // SS high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS HIGH\n");
        return -1;
    }
    // SS low
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "0", 1) < 0) {
        printf("error setting SS LOW\n");
        return -1;
    }

    // send command to read counter
    if(write(counter.fd_spi, &read_opcode, 1) < 0) {
        printf("error writing to counter.\n");
        return -1;
    }

    // read most significant byte
    lseek(counter.fd_spi, 0, SEEK_SET);
    while(read(counter.fd_spi, &c1, 1) != 1);
    // read least significant byte
    lseek(counter.fd_spi, 0, SEEK_SET);
    while(read(counter.fd_spi, &c2, 1) != 1);
// read least significant byte
    lseek(counter.fd_spi, 0, SEEK_SET);
    while(read(counter.fd_spi, &c3, 1) != 1);
// read least significant byte
    lseek(counter.fd_spi, 0, SEEK_SET);
    while(read(counter.fd_spi, &c4, 1) != 1);

    // slave select high
    lseek(counter.fd_ss, 0, SEEK_SET);
    if(write(counter.fd_ss, "1", 1) < 0) {
        printf("error setting SS HIGH\n");
        return -1;
    }
    
    counter_value = 0;
    counter_value = counter_value | c1;
    counter_value = (counter_value << 8) | c2;
    counter_value = (counter_value << 8) | c3;
    counter_value = (counter_value << 8) | c4;
    return counter_value/4;
}

float counter_read_rad(COUNTER counter)
{
    float counter_value;
    counter_value = counter_read(counter) * 1.;

    // 1 rev = 360 degrees
    // 1024 pulses / rev
    // 4096 counts / rev
    // 2.84 pulses = 1 degree
    // 11.36 counts = 1 degree
    counter_value = counter_read(counter);
    return counter_value * PI_CONST / 1024;
}

int counter_mode_read(COUNTER counter)
{
    unsigned char md0r, md1r;

    md0r = counter_byte_read(counter, READ_MDR0);
    md1r = counter_byte_read(counter, READ_MDR1);
    printf("md0r (131): %d; md1r (0): %d\n", md0r, md1r);
    return 0;
}