/*
  ibt.h: helper functions to operate the motor through the IBT-2 H-Bridge
  
  Copyright (c) 2019 Gustavo Santana <wgmsantana@inf.ufrgs.br>

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



// set motor direction as stop
int set_motor_stop();

// set motor direction to clockwise
int set_motor_cw();

// set motor direction to counterclockwise
int set_motor_ccw();

// set motor voltage
int set_motor_voltage();

// set duty cycle
int set_pwm_duty_cycle();