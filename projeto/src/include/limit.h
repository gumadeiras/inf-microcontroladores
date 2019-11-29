/*
  limit.h: helper functions to read quanser position limit switches

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
 * @file limit.h
 * @brief helper functions to read quanser position limit switches
 */

#ifndef LIMIT_H
#define LIMIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#define PIN_LIMIT1 "/sys/class/gpio/gpio12/value" // IO7
#define PIN_LIMIT1_EDGE "/sys/class/gpio/gpio12/edge"
#define PIN_LIMIT2 "/sys/class/gpio/gpio13/value" // IO8
#define PIN_LIMIT2_EDGE "/sys/class/gpio/gpio13/edge"

/** @brief read limit switch.
 *  @param switch_limit indicates which switch to read (1 or 2)
 *  @return 0 if arm is at the limit, 1 otherwise. -1 if there is an error.
 */
extern int limit_read(int switch_limit);

/** @brief polls the limit switch. will return only when the arm reaches the limit.
 *  @param switch_limit indicates which switch to read (1 or 2)
 *  @return 0 when arm is at the limit, -1 if there is an error
 */
extern int limit_poll(int switch_limit);

#ifdef __cplusplus
};
#endif

#endif