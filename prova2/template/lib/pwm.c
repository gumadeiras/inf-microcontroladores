/*
  pwm.c: helper functions for using the galileo pwm
  
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

#include "pwm.h"

int pwm_init(const char device_path[], const char duty_path[], const char enable_path[])
{
    pputs(device_path, "20000000");
    pputs(duty_path, "0");
    pputs(enable_path, "1");

    return 0;
}

int pwm_read_duty(const char duty_path[])
{
    int duty;
    char data_str[80];

    pgets(data_str,sizeof data_str, duty_path);
    duty = atoi(data_str);

    return duty; // convert duty cycle to angle range
}

int pwm_write_duty(int duty_cycle, const char duty_path[])
{
    char str[100];
    snprintf(str, sizeof str,"%d\n", duty_cycle);
    pputs(duty_path, str);

    return 0;
}

int pwm_stop(const char duty_path[], const char enable_path[])
{
    pputs(duty_path, "0");
    pputs(enable_path, "0");

    return 0;
}
