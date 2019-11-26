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
#include <unistd.h>

#include <galileo2io.h>
#include "motor.h"


int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        puts("usage: main <duty cycle [0-100]>");
        return -1;
    }

    int duty_cycle = atof(argv[1]);
    puts("initializing PWM");
    pwm_init();
    puts("5%");
    set_pwm_duty_cycle_percentage(duty_cycle);
    sleep(5);
    set_pwm_duty_cycle_percentage(50);
    set_motor_stop();

    return 0;
}