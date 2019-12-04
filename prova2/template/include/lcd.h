/*
  lcd.h: helper functions to operate the grover lcd
  
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

#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct struct_lcd {
    int fd;
} LCD;

extern static void i2c_error(const char *msg);
extern int lcd_init(LCD *lcd, const char i2c_path[]);
extern int lcd_set_backlight(int fd, int r_c, int g_c, int b_c);
extern int lcd_write(LCD *lcd, int line, const char *msg);
extern int lcd_clean(LCD lcd, int line);
extern int lcd_close(LCD *lcd);

#ifdef __cplusplus
};
#endif

#endif