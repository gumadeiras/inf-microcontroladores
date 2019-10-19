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

#define PWM_PERIOD "1000000" // 1000Hz
#define PWM_HALF_P "500000"

int main(int argc, char const *argv[])
{
    int duty_cycle;
    char str[100];
    int scale;
        
    if(argc != 2)
    {
        puts("usage: main <duty cycle [0-100]>");
        return -1;
    }

    duty_cycle = atof(argv[1]);
    scale      = 10000.;

    if (duty_cycle < 0)
    {
        puts("duty cycle value has to be in the range (0-100); setting to 0");
        duty_cycle = 0;
    } else if (duty_cycle > 100 )
    {
        puts("duty cycle value has to be in the range (0-100); setting to 100");
        duty_cycle = 100;
    }

    pputs(PIN_PWM_PERIOD, PWM_PERIOD);



    /* SET DUTY TO ZERO (OPEN CIRCUIT)*/
    /* SET ENABLE SIGNALS*/
    /* SET REAL DUTY*/

    pputs(PIN_PWM_ENABLE,"1");
    if (duty_cycle < 50)
    {
        /* set motor_ccw */

        snprintf(str, sizeof str, "%d\n", duty_cycle * 2 * scale);
        pputs(PIN_PWM_DUTY, "0");
        pputs(PIN_PWM_EN_L, "0");
        pputs(PIN_PWM_EN_R, "1");
        pputs(PIN_PWM_DUTY, str);
        sleep(5);

    } else if (duty_cycle > 50)
    {
        /* set motor_cw */

        snprintf(str, sizeof str, "%d\n", (duty_cycle - 51) * 2 * scale);
        pputs(PIN_PWM_DUTY, "0");
        pputs(PIN_PWM_EN_R, "0");
        pputs(PIN_PWM_EN_L, "1");
        pputs(PIN_PWM_DUTY, str);
        sleep(5);

    } else
    {
        /* set motor_stop */

        snprintf(str, sizeof str, "%d\n", 0);
        pputs(PIN_PWM_DUTY, "0");
        pputs(PIN_PWM_EN_L, "0");
        pputs(PIN_PWM_EN_R, "0");
        pputs(PIN_PWM_DUTY, str);
        sleep(5);
    }
    pputs(PIN_PWM_ENABLE,"0");

    return 0;
}