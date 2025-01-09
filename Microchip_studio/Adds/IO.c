/*
 * IO.c
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#include "IO.h"

void IO_init() {
	
	PWM1_DDR |= (1 << PWM1_PIN);				// Configura o pino como saída
	PWM2_DDR |= (1 << PWM2_PIN);				// Configura o pino como saída
	LED_PULSE_DDR |= (1 << LED_PULSE_PIN);		// Configura o pino como saída
}

void LED_ON() {
	LED_PULSE_PORT &= ~(1 << LED_PULSE_PIN);	// Liga o LED
}

void LED_OFF() {
	LED_PULSE_PORT |= (1 << LED_PULSE_PIN);		// Desliga o LED
}
