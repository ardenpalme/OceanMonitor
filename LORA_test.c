#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>
#include "USART.h"


void LORAInit(void);

void LORATestRx(void);
void LORATestTx(void);

int main(){
/*
  initUSART1(); //LORA USART
  initUSART0(); //serial USART
  LORAInit();
  DDRC|= 1;
*/
    while(1){
        //USART0_tx(0x20);
        PORTC^= 1;
        _delay_ms(50);
    }
    return 0;
}

void LORAInit(void){
    int cmd_ct= 6;
    char at_cmd[6][30]= {"AT+RESET\r\n",
                         "AT+IPR=9600\r\n",
                         "AT+NETWORK=6\r\n",
                         "AT+ADDRESS=1\r\n",
                         "AT+BAND=868500000\r\n",
                         "AT+PARAMETER=10,7,1,7\r\n"};
    int i= 0;
    int j= 0;
    while(i < cmd_ct){
        //send commdand string
        char c= *( *(at_cmd + i) + j);
        while(c){
            USART1_tx(c);
            if(c >= 0x30) USART0_tx(c);
            j++;
        }
        i++;
    }
}

void LORATestTx(void){
    int i=0;
    char test_cmd[30]= "AT+SEND=2,5,HELLO\r\n"; //send HELLO to LORA @ 2
    while(test_cmd[i])
        USART1_tx(test_cmd[i++]);
    i=0;
}

void LORATestRx(void){
    USART0_tx(USART1_rx());
}
