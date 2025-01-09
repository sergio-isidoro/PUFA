/*
 * ADC.c
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#include "adc.h"

void ADC_init(void) {
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);	// Habilita o ADC e configura o prescaler para 64
}

uint16_t ADC_read(uint8_t canal) {
	canal &= 0x07;										// Limita o canal para valores válidos (0 a 7) embora 6 e 7 nao tem no dip atmega328p
	ADMUX = (ADMUX & 0xF8) | canal;						// Seleciona o canal no ADMUX, preservando as outras configurações
	ADCSRA |= (1 << ADSC);								// Inicia a conversão
	while (ADCSRA & (1 << ADSC));						// Aguarda o término da conversão
	return ADC;											// Retorna o valor convertido
}
