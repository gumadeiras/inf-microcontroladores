/*
  pid.c: helper functions for the PID control algorithm

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

#include <stdio.h>
#include <sys/time.h>

#include "motor.h"
#include "counter.h"
#include "limit.h"

// #define kp 1 // proportional constant, "step size"
// #define ki 1 // accumulating errors over time, integral
// #define kd 1 // dampening constant, derivative

long long time_ms(void) 
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec) * 1000) + (tv.tv_usec/1000);
}

int pid_control(double desired_value, float kp, float ki, float kd)
{
    double ki_sensitivity;
    double update_period = 100;
    double error_prior = 0;
    double integral = 0;
    long long current_time;
    double error, actual_value, derivative, output, bias;

    bias = 0.00000000001 // avoid output = 0

    while (1)
    {
        if (time_ms() > current_time + update_period)
        {
            current_time = time_ms();

            // DOES: error = desired_value – actual_value
            actual_value = counter_read_rad(counter);
            error = desired_value - actual_value;

            // DOES: integral = integral + (error*update_period)
            // if error is within 5 degrees
            ki_sensitivity = 0.0872665; // 5 degrees in radians
            if (error > -ki_sensitivity && error < ki_sensitivity)
            {
                integral = integral + (error * update_period);
            } else {
                integral = 0;
            }

            // DOES: derivative = (error – error_prior)/update_period
            derivative = (error – error_prior) / update_period;
            
            // DOES: output = kp*error + ki*integral + kd*derivative + bias
            output = kp * error + ki * integral + kd * derivative + bias;
            
            // check for limit voltage in the output
            if (voltage > 15)
            {
                output = 15;
            } else if (voltage < -15){
                output = -15;
            }
            set_motor_voltage(output);

            // save error for next iteration
            error_prior = error;

            // wait before updating again
            sleep(update_period);
        }
    }
}