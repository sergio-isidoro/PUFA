/*
 * UART.h
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define BAUD 76800									// Definir a taxa de transmissão (Baud rate)
#define F_CPU 8000000UL								// Definir a frequência do clock (8 MHz)
#define BAUD_PRESCALE ((F_CPU / (8UL * BAUD)) - 1) // Cálculo do prescaler para a UART

void UART_init(void);								// Inicializa o módulo UART
void UART_transmit(char data);						// Transmite um único caractere pela UART
void UART_send_string(const char *str);				// Envia uma string pela UART

#endif
