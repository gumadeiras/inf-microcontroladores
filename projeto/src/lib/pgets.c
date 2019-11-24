/*
  pgets.c: Gets a string from a file, given its path.
  
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

#include <fcntl.h>
#include <unistd.h>

#include <galileo2io.h>

char *pgets(char *s, int size, const char path[])
{
	int fd;
	
	if((fd=open(path,O_RDONLY)) ==-1) return NULL;
	read(fd,s,size);
	close(fd);
	return s;
}

int pread_gpio(const char path[])
{
    int fd, n;
    if((fd=open(path, O_RDONLY)) == -1) return -1;

    char c;
    lseek(fd, 0, SEEK_SET);
    n = read(fd, &c, sizeof(c));
    close(fd);

    if(n < 0)
    {
        return -1;
    }

    if(c == '0')
    {
        return 0;
    } else {
        return 1;
    }
}