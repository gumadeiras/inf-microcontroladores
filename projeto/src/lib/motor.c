/*
  motor.c: helper functions to operate the motor using the IBT-2 H-Bridge
  
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

#include <motor.h>

int pwm_init()
{
    pputs(PIN_PWM_PERIOD, PWM_PERIOD); // set PWM period
    pputs(PIN_PWM_DUTY, "0"); // set duty_cycle to 0
    pputs(PIN_PWM_ENABLE,"1"); // enable PWM
    return 0;
}

int set_motor_stop()
{
    pputs(PIN_PWM_DUTY, "0");
    pputs(PIN_PWM_EN_L, "0");
    pputs(PIN_PWM_EN_R, "0");
    return 0;
}

int set_motor_cw(char str)
{
    pputs(PIN_PWM_DUTY, "0");
    pputs(PIN_PWM_EN_R, "0");
    pputs(PIN_PWM_EN_L, "1");
    pputs(PIN_PWM_DUTY, str);
    return 0;
}

int set_motor_ccw(char str)
{
    pputs(PIN_PWM_DUTY, "0");
    pputs(PIN_PWM_EN_L, "0");
    pputs(PIN_PWM_EN_R, "1");
    pputs(PIN_PWM_DUTY, str);
    return 0;
}

// set duty cycle by percentage
int set_pwm_duty_cycle_percentage(int percentage)
{
    char str[100];
    int scale = 10000.;
    int duty_cycle = percentage;

    if (duty_cycle < 0)
    {
        puts("duty cycle value has to be in the range (0-100); setting to 0");
        duty_cycle = 0;
    } else if (duty_cycle > 100)
    {
        puts("duty cycle value has to be in the range (0-100); setting to 100");
        duty_cycle = 100;
    }


    // convert % to linear range and apply duty cycle

    if (duty_cycle > 50)
    {
        snprintf(str, sizeof str, "%d\n", (duty_cycle - 50) * 2 * scale);
        if(set_motor_cw(str) < 0)
        {
            printf("error setting motor to clockwise directionwith duty cycle %s\n", str);
            return -1;
        }
    } else if (duty_cycle < 50)
    {
        snprintf(str, sizeof str, "%d\n", duty_cycle * 2 * scale);
        if(set_motor_ccw(str) < 0)
        {
            printf("error setting motor to counterclockwise direction with duty cycle %s\n", str);
            return -1;
        }
    } else if (duty_cycle == 50)
    {
        snprintf(str, sizeof str, "%d\n", 0);
        if(set_motor_stop(str) < 0)
        {
            printf("error stopping motor with duty cycle %s\n", str);
            return -1;
        }
    } else
    {
        printf("invalid duty cycle percentage\n");
        return -1;
    }
    return 0;
}

// set motor voltage
int set_motor_voltage(int voltage)
{
    int duty_cycle_percentage;
    int max_voltage = 27;
    
    if (voltage > 27 | voltage < -27)
    {
        printf("error: voltage has to be in the range (-27,27)\n");
        return -1;
    }

    // 0 -> 0%
    // 54V  -> 100% (-27 to 27)
    // scale = 100/54 = 1.851851852

    if (voltage == 27)
    {
        set_pwm_duty_cycle_percentage(50);
    } else {
        voltage = voltage + max_voltage;
        duty_cycle_percentage = floor(voltage * 1.851851852);
        set_pwm_duty_cycle_percentage(duty_cycle_percentage);
    }

    return 0;
}