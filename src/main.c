#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <stdlib.h>
#include <string.h>

#define NMEA_LEN 74

static void clock_setup(void)
{
	/* We are running on MSI after boot. */
	/* Enable GPIOD clock for LED & USARTs. */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

	/* Enable clocks for USART */
	rcc_periph_clock_enable(RCC_USART2);
	rcc_periph_clock_enable(RCC_USART1);
}

static void usart_setup(uint32_t usart, uint32_t baud_rate, uint32_t mode)
{
	/* Setup USART2 parameters. */
	usart_set_baudrate(usart, baud_rate);
	usart_set_databits(usart, 8);
	usart_set_stopbits(usart, USART_STOPBITS_1);
	usart_set_mode(usart, mode);
	usart_set_parity(usart, USART_PARITY_NONE);
	usart_set_flow_control(usart, USART_FLOWCONTROL_NONE);

	usart_enable(usart);
}

static void gpio_setup(void)
{
	/* Setup GPIO pin for Green LED. */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);

	/* Setup GPIO pins for USART2 transmit. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

	/* Setup GPIO pins for USART1 transmit. */
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
	gpio_set_af(GPIOB, GPIO_AF7, GPIO6);

	/* Setup GPIO pins for USART1 recieve. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO10);
}

static void send_msg(uint32_t usart, char *msg, int msg_len)
{
    int i;
    for (i=0; i<msg_len; i++) {
        if(msg[i] != 0)
            usart_send_blocking(usart, (uint16_t)msg[i]);
    }
}

static void recv_msg(uint32_t usart, char *msg, int msg_len)
{
    int i;
    uint16_t c;
    for (i=0; i<msg_len; i++) {
        c = usart_recv_blocking(usart);
        msg[i] = (char)c;
        if(c == '\n')
            break;
    }
}


int main(void)
{
	int i;
    char msg[NMEA_LEN];

	clock_setup();
	gpio_setup();
	usart_setup(USART2, 115200, USART_MODE_TX);
	usart_setup(USART1, 9600, USART_MODE_TX_RX);

	while (1) {
        recv_msg(USART1, msg, NMEA_LEN);
		gpio_toggle(GPIOA, GPIO5);

        // print and parse NMEA sentence
        if(!strncmp(msg,"$GPGGA", 6)) {
            //send_msg(USART2, msg, NMEA_LEN);
            //usart_send_blocking(USART2, '\n');

            i=0;
            char *tok = strtok(msg, ",");
            while(tok != NULL){
                if(i > 1 && i <= 5) {
                    send_msg(USART2, tok, strlen(tok));
                    if(i % 2 != 0){
                        if(i==5)
                            usart_send_blocking(USART2, '\n');
                        else
                            usart_send_blocking(USART2, ',');
                    }
                }

                tok = strtok(NULL, ",");
                i++;
            }
        }else if(!strncmp(msg,"$GPGLL", 6)) {
            send_msg(USART2, msg, NMEA_LEN);
            usart_send_blocking(USART2, '\n');
        }
	}

	return 0;
}
