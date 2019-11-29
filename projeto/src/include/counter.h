/*
  counter.h: helper functions for SPI communication with the LS7366 quadrature encoder

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

/**
 * @file counter.h
 * @brief helper functions for SPI communication with the LS7366 quadrature encoder
 */

#ifndef COUNTER_H
#define COUNTER_H

#ifdef __cplusplus
extern "C"
{
#endif

// --
// -- defines from the LS7366 datasheet
// --

/***MDR0 configuration data - the configuration data is formed with***
 ***single segments taken from each group and ORing all together.***/

//Count modes
#define NQUAD   0x00 //non-quadrature mode
#define QUADRX1 0x01 //X1 quadrature mode
#define QUADRX2 0x02 //X2 quadrature mode
#define QUADRX4 0x03 //X4 quadrature mode

//Running modes
#define FREE_RUN    0x00
#define SINGE_CYCLE 0x04
#define RANGE_LIMIT 0x08
#define MODULO_N    0x0C

//Index modes
#define DISABLE_INDX 0x00 //index_disabled
#define INDX_LOADC   0x10 //index_load_CNTR
#define INDX_RESETC  0x20 //index_rest_CNTR
#define INDX_LOADO   0x30 //index_load_OL
#define ASYNCH_INDX  0x00 //asynchronous index
#define SYNCH_INDX   0x80 //synchronous index

//Clock filter modes
#define FILTER_1 0x00 //filter clock frequncy division factor 1
#define FILTER_2 0x80 //filter clock frequncy division factor 2

/***MDR1 configuration data; any of these***
 ***data segments can be ORed together***/

//Flag modes
#define NO_FLAGS 0x00 //all flags disabled
#define IDX_FLAG 0x10 //IDX flag
#define CMP_FLAG 0x20 //CMP flag
#define BW_FLAG  0x40 //BW flag
#define CY_FLAG  0x80 //CY flag

//1 to 4 datas data-width
#define BYTE_4 0x00 //four data mode
#define BYTE_3 0x01 //three data mode
#define BYTE_2 0x02 //two data mode
#define BYTE_1 0x03 //one data mode

//Enable/disable counter
#define EN_CNTR  0x00 //counting enabled
#define DIS_CNTR 0x04 //counting disabled

/* LS7366R op-code list */
#define CLR_MDR0   0x08
#define CLR_MDR1   0x10
#define CLR_CNTR   0x20
#define CLR_STR    0x30

#define READ_MDR0  0x48
#define READ_MDR1  0x50
#define READ_CNTR  0x60
#define READ_OTR   0x68
#define READ_STR   0x70

#define WRITE_MDR1 0x90
#define WRITE_MDR0 0x88
#define WRITE_DTR  0x98

#define LOAD_CNTR  0xE0
#define LOAD_OTR   0xE4

#define SPI_PATH "/dev/spidev1.0"
#define SPI_EN_C_PATH "/sys/class/gpio/gpio10/value" // enable counter
#define SPI_SS_PATH "/sys/class/gpio/gpio4/value" //IO9 

#define COUNTS_REV 4096

#define SPI_FREQUENCY 5000000
#define PI_CONST 3.14159

/** @brief struct with file descriptors for the decoder/counter
 */
typedef struct struct_counter {
    /** SPI file descriptor (/dev/spidev1.0)  **/
    int fd_spi;
    /** Slave Select file descriptor (Galileo IO9) **/
    int fd_ss;
} COUNTER;


// open file descriptors for the counter
extern int counter_open(COUNTER *counter, char *spi, char *ss);

// write one byte
extern int counter_byte_write(COUNTER counter, unsigned char data, unsigned char op_code);

// initialize MDR0 and MDR1 registers on the LS7366
extern int counter_init(COUNTER counter);

// read one byte
extern unsigned char counter_byte_read(COUNTER counter, unsigned char op_code);

// reset counter
extern int counter_reset(COUNTER counter);

// read counter value
extern int counter_read(COUNTER counter);

// read counter value in radians
extern float counter_read_rad(COUNTER counter);

// read MODE registers
extern int counter_mode_read(COUNTER counter);

#ifdef __cplusplus
};
#endif

#endif