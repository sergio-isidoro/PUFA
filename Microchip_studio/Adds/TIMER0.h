/*
 * TIMER0.h
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */


#ifndef TIMER0_H
#define TIMER0_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define NUM_SAMPLES 10											// Número de amostras para a média móvel
#define SENSOR_BPM 2											

float time_count, ts, PERIOD, IBI, average_seg, average_min, BPM;
volatile uint16_t adc_samples[NUM_SAMPLES];
volatile uint16_t adc_value, Hsignal, Lsignal, thresh, amp, signal;
volatile uint8_t update_UART, uart_status, update_OLED, update_batt, sample_index, fall, beat_state;
volatile bool firstBeat, secondBeat, Pulse, QS;

void TIMER0_init(void);											// Função de inicialização do Timer0
uint16_t filtro_media_movel(uint16_t novo_valor);				// Função filtragem do sinal
void calculate_heart_beat(int adc_value);						// Função deteta beats

#endif
