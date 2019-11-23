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
#include "pid.h"

int main(int argc, char const *argv[])
{
    int duty_cycle;
    char str[100];
    unsigned char str_register;
    COUNTER counter;

    puts("initializing PWM\n");
    pwm_init();
    
    puts("slowly moving arm to left limit\n");
    duty_cycle = 15; // choose duty cycle to be 15%
    snprintf(str, sizeof str, "%d\n", duty_cycle * 2 * PWM_SCALE);
    set_motor_ccw(str) // set motor to ccw diretion with 15% duty cycle

    if (limit_poll(1) < 0) // poll limit1 switch and stop motor and limit is reached
    {
        set_motor_stop();
        pputs(PIN_PWM_ENABLE,"0"); // disable PWM
        puts("polling limit1 switch failed, aborting\n");
    }

    set_motor_stop();
    puts("arm reached its limit\n");
    
    puts("initializing counter\n");

    counter_open(&counter, SPI_PATH, SPI_SS_PATH);
    counter_init(counter);
    counter_mode_read(counter);
    counter_reset(counter); 

    pputs(SPI_EN_C_PATH, "1"); // enable counter
    str_register = counter_byte_read(counter, READ_MDR0); // status register
    printf("Status Register STR: %d\n", str_register); 
    printf("Counter: %d; Rad: %d\n", counter_read(counter), counter_read_rad(counter));

    puts("slowly moving arm to right limit");
    set_motor_cw(str) // set motor to ccw diretion with 15% duty cycle

    if (limit_poll(2) < 0) // poll limit1 switch and stop motor and limit is reached
    {
        set_motor_stop();
        pputs(PIN_PWM_ENABLE,"0"); // disable PWM
        puts("polling limit2 switch failed, aborting\n");
    }
    printf("Counter: %d; Rad: %d\n", str_register, counter_read(counter), counter_read_rad(counter));

    puts("initializing PID");
    printf("chosen position: %d rad; %d degrees", atoi(argv[1]), atoi(argv[1])*180/PI_CONST);
    
    pid_control(atoi(argv[1]), 3, 0.1, 10); // (position, kp, ki, kd)
    
    return 0;
}