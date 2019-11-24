/*
  limit.c: helper functions to read quanser position limit switch_limites

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

#include <limit.h>


int limit_read(int switch_limit)
{
    if (switch_limit == 1)
    {
        return pread_gpio(PIN_LIMIT1);
    }
    else if (switch_limit == 2)
    {
        return pread_gpio(PIN_LIMIT2);
    } else
    {
        puts("invalid switch_limit");
        return -1;
    }

}

int limit_poll(int switch_limit)
{
    unsigned char c;
    struct pollfd pfd;

    if (switch_limit == 1)
    {
        if((pfd.fd=open(PIN_LIMIT1, O_RDONLY)) < 0)
        {
            perror("opening LIMIT1");
            return -1;
        }
        read(pfd.fd, &c, 1);
        pfd.events=POLLPRI;
        puts("waiting for interrupt (F) on LIMIT1");
        pputs(PIN_LIMIT1_EDGE, "falling");
        poll(&pfd, 1, -1);
        pputs(PIN_LIMIT1_EDGE,"none");
        // lseek(pfd.fd, 0, SEEK_SET);
        // read(pfd.fd, &c, 1);
    }
    else if (switch_limit == 2)
    {
        if((pfd.fd=open(PIN_LIMIT2, O_RDONLY)) < 0)
        {
            perror("opening LIMIT2");
            return -1;
        }
        read(pfd.fd, &c, 1);
        pfd.events=POLLPRI;
        puts("waiting for interrupt (F) on LIMIT1");
        pputs(PIN_LIMIT2_EDGE, "falling");
        poll(&pfd, 1, -1);
        pputs(PIN_LIMIT2_EDGE,"none");
        // lseek(pfd.fd, 0, SEEK_SET);
        // read(pfd.fd, &c, 1);
    }
    else
    {
        puts("invalid switch_limit");
        return -1;
    }

    close(pfd.fd);
    return 0;
}