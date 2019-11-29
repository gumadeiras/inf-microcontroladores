/*
  pid.c: helper functions for the PID control algorithm

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
#include <sys/time.h>

#include "pid.h"

unsigned long long time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL); // NULL = timezone
    return (((unsigned long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

double pid_control(double desired_value, double actual_value, float kp, float ki, float kd, double error_prior, int update_period)
{
    double integral = 0;
    double error, derivative, output;

    error      = desired_value - actual_value;
    integral   = integral + (error * update_period);
    derivative = (error - error_prior) / update_period;
    output     = kp * error + ki * integral + kd * derivative;
    // printf("error: %f; error_prior: %f; integral: %f; derivative: %f\n", error, error_prior, integral, derivative);

    return output;
}