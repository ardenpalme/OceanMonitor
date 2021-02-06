/* USART-specific functions for the atmega1284p chip
 * Some functions have been adapted from the atmega1284p datasheet
 */
#include <avr/io.h>

void initUSART0(void);
void USART0_tx(unsigned char data);
unsigned char USART0_rx(void);

void initUSART1(void);
void USART1_tx(unsigned char data);
unsigned char USART1_rx(void);
