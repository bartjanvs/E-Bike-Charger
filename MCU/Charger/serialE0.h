/*!
 *  \file    serialE0.h
 *  \author  Wim Dolman (<a href="mailto:w.e.dolman@hva.nl">w.e.dolman@hva.nl</a>)
 *  \date    03-10-2016
 *  \version 1.2
 *
 *  \brief   Serial interface voor HvA-Xmegaboard
 *
 *  \details This serial interface doesn't use the drivers of Atmel
 *           The interface uses two \e non circulair buffers for sending and 
 *           receiving the data.
 *           It is based om md_serial.c from J.D.Bakker.
 *
 *           It is a serial interface for the HvA-Xmegaboard (Version 2) with a
 *           Xmega256a3u and Xmega32a4u for programming and the serial interface.
 *           You can use the standard printf, putchar, puts, scanf, getchar, ...
 *           functions.
 *
 *           The baud rate is 115200
 */
 
#ifndef SERIALE0_H_
#define SERIALE0_H_

#include <stdio.h>

#define TXBUF_DEPTH_E0    100      //!<  size of transmit buffer
#define RXBUF_DEPTH_E0    100      //!<  size of receive buffer

#define UART_NO_DATA      0x0100                      //!< Macro UART_NO_DATA is returned by uart_getc when no data is present
#define clear_screen()    printf("\e[H\e[2J\e[3J");   //!< Macro to reset and clear the terminal

char     *getline(char* buf,  uint16_t len);
void      init_stream(uint32_t f_cpu);
uint16_t  uartE0_getc(void);
void      uartE0_putc(uint8_t data);
void      uartE0_puts(char *s);

#endif // SERIALE0_H_ 
