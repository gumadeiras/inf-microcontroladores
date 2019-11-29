/*
  galileo2io.h: Helper functions for Galileo I/O
  
  Copyright (c) 2016 Walter Fetter Lages <w.fetter@ieee.org>

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
 * @file galileo2io.h
 * @brief Helper functions for Galileo I/O
 */

#ifndef GALILEO2IO_H
#define GALILEO2IO_H

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief reads the value from a pseudo-file (galileo pin).
 *  @param *s pointer to char.
 *  @param size string size.
 *  @param path to pseudo-file.
 *  @return chat read value as a char.
 */
extern char * pgets(char *s, int size, const char path[]);

/** @brief writes a value to a pseudo-file (galileo pin).
 *  @param path to pseudo-file.
 *  @param s char to write.
 *  @return bytes written.
 */
extern int pputs(const char path[], const char s[]);

/** @brief reads the value from a pseudo-file (galileo pin) but returns an integer value (0 or 1).
 *  @param path to pseudo-file.
 *  @return value integer value. 0 for low and 1 for high. -1 if an error occur.
 */
extern int pread_gpio(const char path[]);

#ifdef __cplusplus
};
#endif

#endif
