/*
 * TIMER2.c
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#include "TIMER2.h"
#include "IO.h"

void TIMER2_init(void) {
	TCCR2A = (1 << WGM21) | (1 << WGM20); // Modo Fast PWM
	TCCR2A |= (1 << COM2B1);              // Saída no OC2B não invertido
	TCCR2B = (1 << CS21);                 // Prescaler de 8

	OCR2B = 199;						  // 5KHz
}
