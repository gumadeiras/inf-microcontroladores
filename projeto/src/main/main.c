/*
  main.c: Galileo Gen2 Shield + Quanser interface API demonstration + PID algorithm
  
  Copyright (c) 2019 Gustavo Madeira Santana; Lúcio Pereira Franco; Rodrigo Franzoi Scroferneker

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
    unsigned char str_register;
    unsigned long long duration, current_time, start_time;
    int update_period, limit1_switch, limit2_switch;
    float kp, ki, kd;
    double error_prior, desired_value, counter_value, output;
    COUNTER counter;

    if (argc < 6)
    {
        puts("usage: ./main [position in rads] [kp] [ki] [kd] [run duration in seconds]");
        exit(-1);
    }

    puts("initializing PWM\n");
    pwm_init();
    
    puts("slowly moving arm to left limit\n");
    set_motor_voltage(-15);

    if (limit_poll(1) < 0) // poll limit1 switch and stop motor when limit is reached
    {
        set_motor_stop();
        pwm_stop();
        puts("polling limit1 switch failed, aborting\n");
    }

    set_motor_stop();
    puts("arm reached its limit\n");
    
    puts("initializing counter\n");
    counter_open(&counter, SPI_PATH, SPI_SS_PATH); // open file descriptors
    counter_init(counter); // initialize LS7366 registers
    counter_mode_read(counter); // read mode registers
    counter_reset(counter);  // reset counter value
    pputs(SPI_EN_C_PATH, "1"); // enable counter

    str_register = counter_byte_read(counter, READ_MDR0); // status register
    printf("Status Register STR: %d\n", str_register); 
    // printf("Counter: %d; Rad: %f\n", counter_read(counter), counter_read_rad(counter));

    puts("slowly moving arm to right limit\n");
    set_motor_voltage(15);

    if (limit_poll(2) < 0) // poll limit2 switch and stop motor when limit is reached
    {
        set_motor_stop();
        pwm_stop();
        puts("polling limit2 switch failed, aborting\n");
    }
    set_motor_stop();
    puts("arm reached its limit\n");
    printf("Counter: %d; Rad: %f\n", counter_read(counter), counter_read_rad(counter));

    puts("moving arm back a bit\n");
    set_motor_voltage(-15);
    usleep(500 * 1000); // 500ms
    set_motor_stop();

    puts("checking if arm is not at the limits\n");
    printf("limit1: %d\n", (limit_read(1)));
    printf("limit2: %d\n", (limit_read(2)));


    puts("initializing PID\n");
    desired_value = atof(argv[1]);
    kp            = atof(argv[2]);
    ki            = atof(argv[3]);
    kd            = atof(argv[4]);
    duration      = atoi(argv[5]);
    printf("chosen position: %f rad; %f degrees; run duration: %llu\n", desired_value, desired_value*180/PI_CONST, duration);
    printf("chosen constants: kp=%f; ki=%f; kd=%f\n", kp, ki, kd);
    
    start_time    = time_ms();
    current_time  = start_time;
    update_period = 10; // in ms
    error_prior   = 0;
    if (desired_value > 3.142) // 3.142 rad = 180 degrees
    {
        puts("desired value is bigger than 3.142, or 180 degrees, aborting...\n");
        exit(-1);
    }

    puts("beginning PID\n");
    int print_counter = 0;
    while(1)
    {
        // if chosen duration is up, stop
        if ((time_ms() - start_time) > (duration * 1000))
        {
            puts("duration reached\n");
            break;
        }

        // check if arm is at its limit
        limit1_switch = limit_read(1);
        limit2_switch = limit_read(2);
        if ((limit1_switch == 0) || (limit2_switch == 0))
        {
            puts("stopping, arm reached a limit:\n");
            printf("limit1: %d\n", limit1_switch);
            printf("limit2: %d\n", limit2_switch);
            break;
        }

        // only update if period is up
        if (time_ms() > current_time + update_period)
        {
            current_time  = time_ms();
            counter_value = counter_read_rad(counter);
            
            // pid_control(desired, actual, kp, ki, kd, error prior pid, duration in seconds)
            output      = pid_control(desired_value, counter_value, kp, ki, kd, error_prior, update_period);
            error_prior = desired_value - counter_value;

            // check if output is bigger than voltage limit
            // using max voltage +-15V, just to be safe
            if (output > 27)
            {
                output = 27;
            } else if (output < -27){
                output = -27;
            }
            set_motor_voltage(output);
            usleep(update_period * 1000);
        }

        print_counter = print_counter + 1;
        if ((print_counter % 100) == 0)
        {
            printf("Rad: %f; Angle: %f; Voltage: %f\n", counter_read_rad(counter), counter_read_rad(counter)*180/PI_CONST, output);
        }
    }

    puts("stopping motor and exiting...\n");
    set_motor_stop(); // stop motor
    pwm_stop();

    return 0;
}