#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdlib.h>
#include <stdio.h>
#include "USART.h"

void sendMsgUSART0(char *msg);
void sendMsgUSART1(char *msg);

int getMsgUSART0(int bufLen, char *outMsg);
int getMsgUSART1(int bufLen, char *outMsg);

int main(int argc, char **argv){
    DDRC|= 1;
    initUSART0();
    initUSART1();
    sendMsgUSART1("AT+SEND=1,10,INITALIZED\r\n");

    //max msg size is 240 bytes
    char *cmd= malloc(sizeof(char*) * 220);
    char preCmd[20]= "AT+SEND=1,";
    char CRNL[20]= "\r\n";

    char *NMEA= malloc(sizeof(char*) * 180);
    int NMEA_len;
    while(1){
        NMEA_len= getMsgUSART0(180, NMEA);
        sprintf(cmd, "%s%d,%s%s", preCmd, NMEA_len, NMEA, CRNL);
        sendMsgUSART1(cmd);
        PORTC^= 1;
        _delay_ms(50);
    }
    return 0;
}

void sendMsgUSART0(char *msg){
    int i=0;
    while(msg[i] != '\0'){
        USART0_tx(msg[i]);
        i++;
    }
}
void sendMsgUSART1(char *msg){
    int i=0;
    while(msg[i] != '\0'){
        USART1_tx(msg[i]);
        i++;
    }
}

int getMsgUSART0(int bufLen, char *outMsg){
    int i=0;
    while(i < bufLen){
        outMsg[i]= USART0_rx();
        i++;
    }
    return i;
}
int getMsgUSART1(int bufLen, char *outMsg){
    int i=0;
    while(i < bufLen){
        outMsg[i]= USART1_rx();
        i++;
    }
    return i;
}
