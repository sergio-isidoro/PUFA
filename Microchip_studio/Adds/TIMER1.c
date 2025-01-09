/*
 * TIMER1.c
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#include "TIMER1.h"

void TIMER1_init(void) {
	TCCR1A = (1 << COM1A1);					// PWM, Phase and Frequency Correct, ICR1 e Saída no OC1A não invertido (PB3)
	TCCR1B = (1 << WGM13) | (1 << CS12);	// Modo PWM e prescaler de 256
	ICR1 = 15625;							// Valor para duty cycle de 100% (1Hz = 8MHz / (2 * 256 * ICR1))	// Para	60 BPM  // 1Hz
	
	// Exemplos de outros valores de frequência:
	// ICR1 = 3906;  // Para 240 BPM
	// ICR1 = 7813;  // Para 120 BPM
	// ICR1 = 31250; // Para 30 BPM
}
