/*
  rotary.h: helper functions to read the voltage of a potenciometer
  
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

#ifndef ROTARY_H
#define ROTARY_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct struct_rotary {
    int fd;
    double scale;
} ROTARY;

extern int rotary_open(ROTARY *rotary, const char device_path[], const char scale_path[]);
extern int rotary_one_shot_read(ROTARY rotary);
extern int rotary_continuous_read(ROTARY rotary, int sample_size, int sampling_rate);
extern int rotary_close(ROTARY *rotary);

#ifdef __cplusplus
};
#endif

#endif