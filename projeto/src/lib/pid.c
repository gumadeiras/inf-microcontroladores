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

#include "pid.h"

// #define kp 1 // proportional constant, "step size"
// #define ki 1 // accumulating errors over time, integral
// #define kd 1 // dampening constant, derivative

unsigned long long time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL); // NULL = timezone
    return (((unsigned long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

double pid_control(double desired_value, double actual_value, float kp, float ki, float kd, double error_prior, int update_period)
{
    double ki_sensitivity;
    double integral = 0;
    double error, derivative, output, bias;

    bias = 0.00000000001; // avoid output = 0

    // DOES: error = desired_value – actual_value
    // printf("desired value: %f; actual_value: %f\n", desired_value, actual_value);
    error = desired_value - actual_value;

    // DOES: integral = integral + (error*update_period)
    // if error is within 5 degrees, start computing the integral part
    ki_sensitivity = 0.0872665; // 5 degrees in radians
    if ((error > -ki_sensitivity) && (error < ki_sensitivity))
    {
        integral = integral + (error * update_period);
    } else {
        integral = 0;
    }

    // DOES: derivative = (error – error_prior)/update_period
    derivative = (error - error_prior) / update_period;
    
    // DOES: output = kp*error + ki*integral + kd*derivative + bias
    output = kp * error + ki * integral + kd * derivative + bias;
    // printf("error: %f; error_prior: %f; integral: %f; derivative: %f\n", error, error_prior, integral, derivative);

    // save error for next iteration
    return output;
}