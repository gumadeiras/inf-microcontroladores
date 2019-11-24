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
#include "pid.h"
#include "motor.h"
#include "counter.h"
#include "limit.h"

int main(int argc, char const *argv[])
{
    int duty_cycle;
    unsigned char str_register;
    COUNTER counter;
    int update_period, counter_value;
    unsigned long long duration, current_time, start_time;
    double error_prior, desired_value, output;

    puts("initializing PWM\n");
    pwm_init();
    
    puts("slowly moving arm to left limit\n");
    duty_cycle = 18; // choose duty cycle %
    set_pwm_duty_cycle_percentage(duty_cycle); // set motor to ccw diretion with 15% duty cycle

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
    printf("Counter: %d; Rad: %f\n", counter_read(counter), counter_read_rad(counter));

    puts("slowly moving arm to right limit\n");
    duty_cycle = 68; // choose duty cycle %
    set_pwm_duty_cycle_percentage(duty_cycle); // set motor to ccw diretion with 15% duty cycle

    if (limit_poll(2) < 0) // poll limit1 switch and stop motor and limit is reached
    {
        set_motor_stop();
        pputs(PIN_PWM_ENABLE,"0"); // disable PWM
        puts("polling limit2 switch failed, aborting\n");
    }
    set_motor_stop();
    puts("arm reached its limit\n");
    printf("Counter: %d; Rad: %f\n", counter_read(counter), counter_read_rad(counter));

    puts("moving arm back a bit\n");
    duty_cycle = 18; // choose duty cycle %
    set_pwm_duty_cycle_percentage(duty_cycle); // set motor to ccw diretion with 15% duty cycle
    usleep(500 * 1000); // 500ms
    set_motor_stop();

    puts("initializing PID\n");
    desired_value = atof(argv[1]);
    duration = atoi(argv[2]);
    printf("chosen position: %f rad; %f degrees; run duration: %llu\n", desired_value, desired_value*180/PI_CONST, duration);
    
    start_time = time_ms();
    current_time = time_ms();
    update_period = 100;
    error_prior = 0;
    if (desired_value > 3.142)
    {
        puts("desired value is bigger than 3.142, or 180 degrees, aborting...\n");
        exit(-1);
    }

    puts("checking if arm is not at the limits\n");
    printf("limit1: %d\n", (limit_read(1)));
    printf("limit2: %d\n", (limit_read(2)));

    puts("beginning PID tunning");
    int print_counter = 0;
    while((limit_read(1) == 1) && (limit_read(2) == 1))
    {
        // if chosen duration is up, stop
        if ((time_ms() - start_time) > (duration * 1000 + start_time))
        {
            puts("duration reached, exiting...");
            break;
        }

        // only update if period is up
        if (time_ms() > current_time + update_period)
        {
            current_time = time_ms();
            counter_value = counter_read_rad(counter);
            
            // pid_control(desired, actual, kp, ki, kd, error prior pid, duration in seconds)
            output = pid_control(desired_value, counter_value, 3, 0.1, 10, error_prior, duration, update_period);
            error_prior = desired_value - counter_value;

            // check if output is bigger than voltage limit
            // using max voltage +-15V, just to be safe
            if (output > 15)
            {
                output = 15;
            } else if (output < -15){
                output = -15;
            }
            set_motor_voltage(output);
            usleep(update_period * 1000);
        }
        print_counter = print_counter + 1;
        if ((print_counter % 10) == 0)
        {
        printf("Counter: %d; Rad: %f; Voltage: %f\n", counter_read(counter), counter_read_rad(counter), output);
        }
    }
    
    set_motor_stop();
    pputs(PIN_PWM_ENABLE,"0"); // disable PWM
        
    return 0;
}