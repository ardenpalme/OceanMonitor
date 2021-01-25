#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "USART.h"

void LORAInit();

int main(int argc, char **argv){
    initUSART0();               //TTL serial to laptop
    initUSART1();               //USART to RYLR896
    LORA_tx();
    while(1){
        /* TX module */
        char test_cmd[30]= "AT+SEND=2,5,HELLO\r\n"; //send HELLO to LORA @ 2
        USART1_tx(cmd_str);

        /* RX  module */
        //USART1_tx(USART0_rx());
    }
    return 0;
}

void LORA_tx(){
    int cmd_ct= 6;
    char ** at_cmd[cmd_ct]= ["RESET",
                             "IPR=9600",
                             "NETWORK=6",
                             "ADDRESS=1",
                             "BAND=868500000",
                             "PARAMETER=10,7,1,7"];
    char *cmd_str;
    char CR[]= "\r\n";
    char AT[]= "AT+";
    while(cmd_ct != 0){
        sprintf(cmd_str, "%s%s%s", &AT, at_cmd[cmd_ct--], &CR);
        printf("%s",cmd_str);
        USART1_tx(cmd_str);
    }
}
