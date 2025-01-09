/*
 * IO.h
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#ifndef IO_H
#define IO_H

#include <avr/io.h>

#define PWM1_DDR DDRB
#define PWM1_PIN PB1
#define PWM2_DDR DDRD
#define PWM2_PIN PD3
#define LED_PULSE_DDR DDRB
#define LED_PULSE_PORT PORTB
#define LED_PULSE_PIN PB0

void IO_init(void);				// Inicialização de I/O
void LED_ON(void);				// Altera a porta do LED para “0”
void LED_OFF(void);				// Altera a porta do LED para “1”

#endif
