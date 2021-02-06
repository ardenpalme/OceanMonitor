#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "USART.h"

int main(int argc, char **argv){
    /* Initialization */
    initUSART0();
    initUSART1();
    DDRC|= 1;
    int i;
    for(i=0;i<20;i++){
        PORTC^= 1; _delay_ms(10);
    }

    while(1){
        USART0_tx(USART1_rx());
    }
    return 0;
}
