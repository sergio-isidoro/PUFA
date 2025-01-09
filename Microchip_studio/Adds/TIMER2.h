/*
 * TIMER2.h
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#ifndef TIMER2_H
#define TIMER2_H

#include <avr/io.h>
#include <avr/interrupt.h>

void TIMER2_init(void);		// Inicialização do PWM no Timer2 (5KHz)

#endif // TIMER2_PWM_H
