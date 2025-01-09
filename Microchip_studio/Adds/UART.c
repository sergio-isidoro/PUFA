/*
 * UART.c
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */
#include "UART.h"

void UART_init() {
	UBRR0H = (BAUD_PRESCALE >> 8);				// Configura os 4 bits mais significativos do prescaler da baud rate
	UBRR0L = BAUD_PRESCALE;						// Configura os 8 bits menos significativos do prescaler da baud rate
	UCSR0A = (1 << U2X0);						// Habilita o modo de "double speed", dobrando a taxa de transmissão
	UCSR0B = (1 << TXEN0);						// Habilita o transmissor UART
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);		// Configura o formato do quadro UART: 8 bits de dados, 1 bit de parada
}


void UART_transmit(char data) {
	while (!(UCSR0A & (1 << UDRE0)));			// Aguarda até que o registrador esteja pronto para receber novos dados
	UDR0 = data;								// Envia o dado
}

void UART_send_string(const char *str) {
	while (*str) {								// Envia cada caractere da string
		UART_transmit(*str);
		str++;
	}
}
