/* USART-specific functions for the atmega1284p chip
 * Some functions have been adapted from the atmega1284p datasheet
 * Baudrate= 9600 at F_CPU= 8MHz
 */
#include <avr/io.h>
#include <util/setbaud.h>
#include "USART.h"

void initUSART0(void){
  UBRR0L= 0x0c; //prescaler for 9600 baud
  UCSR0A|= (1 << U2X0); //must have double-data rate
  UCSR0B|= (1 << TXEN0) | (1 << RXEN0);
  UCSR0C|= (1 << UCSZ01) | (1 << UCSZ00);
}
void USART0_tx(unsigned char data){
    /* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0)) ) ;
	UDR0 = data;
}

unsigned char USART0_rx(void){
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) ) ;
    return UDR0;
}

void initUSART1(void){
  UBRR1L= 0x0c; //prescaler for 9600 baud
  UCSR1A|= (1 << U2X1); //must have double-data rate
  UCSR1B = (1 << TXEN1) | (1 << RXEN1);
  UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void USART1_tx(unsigned char data){
    /* Wait for empty transmit buffer */
	while ( !(UCSR1A & (1<<UDRE1)) ) ;
	UDR1 = data;
}

unsigned char USART1_rx(void){
    /* Wait for data to be received */
    while ( !(UCSR1A & (1<<RXC1)) ) ;
    return UDR1;
}
