/*
  ibt.c: helper functions to operate the motor through the IBT-2 H-Bridge
  
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


#include <motor.h>

int set_motor_stop()
{
	// set pin EN_R LOW
	// set pin EN_L LOW
	return 0;
}

int set_motor_cw()
{
	// set pin EN_R HIGH
	// set pin EN_L LOW
	return 0;
}

int set_motor_ccw()
{
	// set pin EN_R HIGH
	// set pin EN_L LOW
	return 0;
}

// set motor voltage
int set_motor_voltage()
{
	// convert voltage to pwm duty cycle
	// set_pwm_duty_cycle(percentage); 
	return 0;
}

// set duty cycle
int set_pwm_duty_cycle(int percentage)
{
	// convert % to linear range
	if (percentage > 50)
	{
		if(set_motor_cw() < 0)
		{
			printf("error setting motor to clockwise direction\n");
			return -1
		}
	} else if (percentage < 50)
	{
		if(set_motor_ccw() < 0)
		{
			printf("error setting motor to counterclockwise direction\n");
			return -1
		}
	} else
	{
		if(set_motor_stop() < 0)
		{
			printf("error stopping motor\n");
			return -1
		}
	}
	return 0;
}