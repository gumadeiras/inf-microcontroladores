/*
  motor.h: helper functions to operate the motor using the IBT-2 H-Bridge
  
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
#include <unistd.h>

#include <galileo2io.h>

#define PWM_PERIOD "1000000" // 1kHz
#define PWM_HALF_P "500000"
#define PWM_SCALE 10000.

#define PIN_PWM_PERIOD  "/sys/class/pwm/pwmchip0/device/pwm_period"
#define PIN_PWM_ENABLE  "/sys/class/pwm/pwmchip0/pwm1/enable"
#define PIN_PWM_DUTY    "/sys/class/pwm/pwmchip0/pwm1/duty_cycle"
#define PIN_PWM_EN_L    "/sys/class/gpio/gpio6/value"
#define PIN_PWM_EN_R    "/sys/class/gpio/gpio13/value"

// initialize PWM
extern int pwm_init();

// set motor direction as stop
extern int set_motor_stop();

// set motor direction to clockwise
extern int set_motor_cw(int duty_cycle);

// set motor direction to counterclockwise
extern int set_motor_ccw(int duty_cycle);

// set duty cycle
extern int set_pwm_duty_cycle_percentage(int percentage);

// set motor voltage
extern int set_motor_voltage(int voltage);