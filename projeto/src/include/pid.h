/*
  pid.h: helper functions for the PID control algorithm

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

/**
 * @file pid.h
 * @brief helper functions for the PID control algorithm
 */

#ifndef PID_H
#define PID_H

#ifdef __cplusplus
extern "C"
{
#endif


/** @brief get current time in ms.
 *  @return (unsigned long long) time in ms
 */
extern unsigned long long time_ms(void);

/** @brief PID control algorithm, computes the output voltage that minimizes the error (relative arm position given some target position).
 *  @param desired_value desired arm position in radians
 *  @param actual_value current arm position in radians
 *  @param kp PID proportial constant
 *  @param ki PID integral constant
 *  @param kd PID derivative constant
 *  @param error_prior error from the preivous iteration
 *  @param update_period time since last iteration
 *  @return (double) output returns the voltage to be applied
 */
extern double pid_control(double desired_value, double actual_value, float kp, float ki, float kd, double error_prior, int update_period);

#ifdef __cplusplus
};
#endif

#endif