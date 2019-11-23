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
#include "limit.h"

int main(int argc, char const *argv[])
{
    int duty_cycle;
    char str[100];
    unsigned char md0r;
    unsigned char md1r;
    unsigned char str_register;
    COUNTER counter;

    puts("initializing PWM\n");
 
    pputs(PIN_PWM_PERIOD, PWM_PERIOD); // set PWM period
    pputs(PIN_PWM_DUTY, "0"); // set duty_cycle to 0
    pputs(PIN_PWM_ENABLE,"1"); // enable PWM
    
    puts("slowly moving arm to left limit\n");
    duty_cycle = 15; // choose duty cycle to be 15%
    snprintf(str, sizeof str, "%d\n", duty_cycle * 2 * PWM_SCALE);
    pputs(PIN_PWM_EN_L, "0"); // set H-bridge to
    pputs(PIN_PWM_EN_R, "1"); // ccw direction
    pputs(PIN_PWM_DUTY, str); // set duty cycle

    if (limit_poll(1) < 0)
    {
        pputs(PIN_PWM_DUTY, "0"); // set duty_cycle to 0
        pputs(PIN_PWM_ENABLE,"0"); // disable PWM
        puts("polling limit switch failed, aborting\n");
    }

    pputs(PIN_PWM_EN_L, "0"); // set H-bridge to
    pputs(PIN_PWM_EN_R, "0"); // "stop" position
    pputs(PIN_PWM_DUTY, "0"); // set duty_cycle to 0 and stop motor

    puts("arm reached its limit\n");
    
    puts("initializing decoder counter\n");

    counter_open(&counter, SPI_PATH, SPI_SS_PATH);
    counter_init(counter);

    md0r = counter_byte_read(counter, READ_MDR0);
    md1r = counter_byte_read(counter, READ_MDR1);
    printf("md0r (131): %d; md1r (0): %d\n", md0r, md1r);
    pputs(SPI_EN_C_PATH, "1");

    counter_reset(counter); 
    str_register = counter_byte_read(counter, READ_MDR0);
    printf("STR: %d; Counter: %d\n", str_register, counter_read(counter)/4);

    puts("slowly moving arm to center");
    // TODO
    printf("Counter: %d\n", counter_read(counter));

    puts("slowly moving arm to right limit");
    // TODO

    puts("slowly moving arm to 45 degrees right");
    // TODO

    puts("slowly moving arm to 45 degrees left");
    // TODO

    return 0;
}