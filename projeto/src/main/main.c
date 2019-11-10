/*
  main.c: Galileo Gen2 Shield + Quanser interface API demonstration
  
  Copyright (c) 2019 Gustavo Madeira Santana <gmsantana@inf.ufrgs.br>

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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include <galileo2io.h>
#include "motor.h"
#include "counter.h"

int main(int argc, char const *argv[])
{
    unsigned char md1r;
    unsigned char md2r;

    COUNTER counter;

    counter_open(&counter, SPI_PATH, SPI_SS_PATH);
    counter_init(counter);

    md1r = counter_byte_read(counter, READ_MDR0);
    md2r = counter_byte_read(counter, READ_MDR1);
    printf("md1r: %d\nmd2r: %d\n", md1r, md2r);

    counter_reset(counter);

    while(1) {
        printf("Counter: %d\n", counter_read(counter)/4);
        usleep(1000000);
    }

    return 0;
}