/*
  motor.h: helper functions to operate the motor using the H-Bridge
  
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

/**
 * @file motor.h
 * @brief helper functions to operate the motor using the H-Bridge
 */

#ifndef MOTOR_H
#define MOTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

/** 1kHz */
#define PWM_PERIOD "1000000"
/** scales the duty cycle value */
#define PWM_SCALE 10000.

#define PIN_PWM_PERIOD  "/sys/class/pwm/pwmchip0/device/pwm_period"
#define PIN_PWM3_ENABLE "/sys/class/pwm/pwmchip0/pwm3/enable"       // IO5 R_PWM
#define PIN_PWM3_DUTY   "/sys/class/pwm/pwmchip0/pwm3/duty_cycle"
#define PIN_PWM5_ENABLE "/sys/class/pwm/pwmchip0/pwm5/enable"       // IO6 L_PWM
#define PIN_PWM5_DUTY   "/sys/class/pwm/pwmchip0/pwm5/duty_cycle"
#define PIN_PWM_EN_R    "/sys/class/gpio/gpio14/value"              // IO3
#define PIN_PWM_EN_L    "/sys/class/gpio/gpio6/value"               // IO4

// initialize PWM

/** @brief open and initialize PWM pins, period, and duty cycle.
 *  @return -1 in case of error, 0 otherwise.
 */
extern int pwm_init();

/** @brief disables PWM related functions.
 *  @return -1 in case of error, 0 otherwise.
 */
extern int pwm_stop();

/** @brief applies 0V to the DC motor, effectively stopping the motor.
 *  @return -1 in case of error, 0 otherwise.
 */
extern int set_motor_stop();

/** @brief sets the given duty cycle value. Motor motion will be in the clockwise direction. Converts 0-100% value to be in the equivalent value, given that 0% is -27V and 100% is 27V.
 *  @param duty_cycle duty cycle percentage (0-100%)
 *  @return -1 in case of error, 0 otherwise.
 */
extern int set_motor_cw(int duty_cycle);

/** @brief sets the given duty cycle value. Motor motion will be in the counter-clockwise direction. Converts 0-100% value to be in the equivalent value, given that 0% is -27V and 100% is 27V.
 *  @param duty_cycle duty cycle percentage (0-100%)
 *  @return -1 in case of error, 0 otherwise.
 */
extern int set_motor_ccw(int duty_cycle);


/** @brief sets the given duty cycle value. 0% is -27V and 100% is 27V.
 *  @param percentage duty cycle percentage (0-100%)
 *  @return -1 in case of error, 0 otherwise.
 */
extern int set_pwm_duty_cycle_percentage(float percentage);


/** @brief applies the given voltage to the motor. Converts the given voltage to an appropriate duty cycle percentage, given that 0% is -27V and 100% is 27V.
 *  @param voltage voltage value in the range -27V and 27V.
 *  @return -1 in case of error, 0 otherwise.
 */
extern int set_motor_voltage(double voltage);

#ifdef __cplusplus
};
#endif

#endif