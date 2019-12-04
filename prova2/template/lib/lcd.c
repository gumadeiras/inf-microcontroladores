/*
  lcd.c: helper functions to operate the grover lcd
  
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

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <i2cutil.h>
#include <jhdlcd.h>

#include <galileo2io.h>

#include "lcd.h"

static void i2c_error(const char *msg)
{
    perror(msg);
    exit(-errno);
}


int lcd_init(LCD *lcd, const char i2c_path[])
{
    if((lcd->fd=open(i2c_path,O_WRONLY)) < 0) i2c_error("Opening /dev/i2c-0");
    usleep(30000);  /* Wait for 30 ms after power on */

    /* LCD initialization */
    if(ioctl(lcd->fd,I2C_SLAVE, LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

    i2c_write_reg(lcd->fd, LCD_C0, LCD_FUNCTIONSET | LCD_2LINE);
    usleep(40);  /* Wait for more than 39 us */

    i2c_write_reg(lcd->fd, LCD_C0, LCD_DISPLAYSWITCH | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
    usleep(40); /* Wait for more than 39 us */

    i2c_write_reg(lcd->fd, LCD_C0, LCD_SCREENCLEAR);
    usleep(1600);   /* Wait for more than 1.53 ms */

    i2c_write_reg(lcd->fd, LCD_C0, LCD_INPUTSET | LCD_ENTRYLEFT | LCD_DECREMENT);

    if(ioctl(lcd->fd,I2C_SLAVE, BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
    i2c_write_reg(lcd->fd, BL_MODE1, 0);
    i2c_write_reg(lcd->fd, BL_LEDOUT, BL_RED_GRPPWM | BL_GREEN_GRPPWM | BL_BLUE_GRPPWM);
    i2c_write_reg(lcd->fd, BL_MODE2, BL_DMBLNK);

    return 0;
}

int lcd_set_backlight(LCD lcd, int r_c, int g_c, int b_c)
{
    if(ioctl(lcd.fd, I2C_SLAVE, BL_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

    i2c_write_reg(lcd.fd, BL_RED, r_c);
    i2c_write_reg(lcd.fd, BL_GREEN, g_c);
    i2c_write_reg(lcd.fd, BL_BLUE, b_c);

    return 0;
}

int lcd_write(LCD lcd, int line, const char *msg)
{
    int i, msg_len;

    msg_len = strlen(msg);
    
    if(ioctl(lcd.fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");
    
    if (line == 1)
    {
        i2c_write_reg(lcd.fd, LCD_C0, LCD_DDRAMADDRSET | 0);
        for(i = 0; i < line1_len;i++) i2c_write_reg(lcd.fd, LCD_RS, line1[i]);
    } else if (line == 2) {        
        i2c_write_reg(lcd.fd, LCD_C0, LCD_DDRAMADDRSET | 0x40);
        for(i = 0; i < line2_len;i++) i2c_write_reg(lcd.fd, LCD_RS, line2[i]);
    } else {
        perror("can only write to line==[1,2]");
        return -1;
    }

    return 0;
}

int lcd_clean(LCD lcd, int line)
{
    int i;

    if(ioctl(lcd.fd,I2C_SLAVE,LCD_ADDR) < 0) i2c_error("ioctl on /dev/i2c-0");

    if (line == 1)
    {
        i2c_write_reg(lcd.fd, LCD_C0, LCD_DDRAMADDRSET | 0);
        for(i = 0; i <= 15;i++) i2c_write_reg(lcd.fd, LCD_RS, ' ');
    } else if (line == 2) {        
        i2c_write_reg(lcd.fd, LCD_C0, LCD_DDRAMADDRSET | 0x40);
        for(i = 0; i <= 15;i++) i2c_write_reg(lcd.fd, LCD_RS, ' ');
    } else {
        perror("can only write to line==[1,2]");
        return -1;
    }

}

int lcd_close(LCD *lcd)
{
    close(lcd->fd);

    return 0;
}
