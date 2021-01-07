/*  Ocean Monitoring Project
 *  Arden Diakhate-Palme
 *
 *  Testing USART communication of GPS coordinates
 *  from atmega1284p to laptop
 */
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "USART.h"

int main(int argc, char **argv){
    initUSART0();
    initUSART1();
    while(1){
        USART0_tx(USART1_rx());
    }
    return 0;
}

