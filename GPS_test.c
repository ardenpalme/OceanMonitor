/*  Ocean Monitoring Project
 *  Arden Diakhate-Palme
 *
 *  Testing USART communication of GPS coordinates
 *  from atmega1284p to laptop
 */

void initUSART0(void);
void initUSART1(void);


int main(int argc, char **argv){
    return 0;
}


void initUSART0(void){
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */

  //UCSR0A |= (1 << U2X0);      //set for 2x data rate
  UCSR0A &= ~(1 << U2X0);

  UBRR0H= 0;
  UBRR0L= 0x06;
}

void initUSART1(void){
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */

  //UCSR0A |= (1 << U2X0);      //set for 2x data rate
  UCSR0A &= ~(1 << U2X0);

  UBRR0H= 0;
  UBRR0L= 0x06;
}
