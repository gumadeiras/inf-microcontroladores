/*
  limit.h: helper functions to read quanser position limit switches

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

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>

#define PIN_LIMIT1 "/sys/class/gpio/gpio0/value" // IO5
#define PIN_LIMIT1_EDGE "/sys/class/gpio/gpio0/edge"
#define PIN_LIMIT2 "/sys/class/gpio/gpio1/value" // IO6
#define PIN_LIMIT2_EDGE "/sys/class/gpio/gpio1/edge"

// read limit switch
extern int limit_read(int switch_limit);

// poll limit switch
extern int limit_poll(int switch_limit);