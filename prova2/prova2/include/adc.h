/*
  adc.h: helper functions to read the voltage of a potenciometer
  
  Copyright (c) 2019 Gustavo Santana, Lúcio Franco

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

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct struct_adc {
    int fd;
    double scale;
} ADC;

extern int adc_open(ADC *adc, const char device_path[], const char scale_path[]);
extern int adc_one_shot_read(ADC adc);
extern int adc_continuous_read_begin();
extern int adc_close(ADC *adc);

#ifdef __cplusplus
};
#endif

#endif