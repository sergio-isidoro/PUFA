/*
 * TIMER0.c
 *
 * Sergio Isidoro - 1221709
 * Andre Nogueira - 1221709
 *
 * CHIP: Atmega328p 8MHz
 */

#include "TIMER0.h"
#include "ADC.h"
#include "IO.h"

float time_count = 0.0, ts = 0.0, PERIOD = 0.0, IBI = 600.0, average_seg = 0.0, average_min = 0.0, BPM = 0.0;
volatile uint16_t adc_samples[NUM_SAMPLES] = {0};
volatile uint16_t adc_value = 0, Hsignal = 512, Lsignal = 512, thresh = 530, amp = 0, signal = 0;
volatile uint8_t update_UART = 0, uart_status = 0, update_OLED = 0, update_batt = 0, sample_index = 0, fall = 0, beat_state = 1;
volatile bool firstBeat = true, secondBeat = false, Pulse = false;


uint16_t filtro_media_movel(uint16_t novo_valor) {
	adc_samples[sample_index] = novo_valor;									// Adiciona o novo valor ao buffer circular
	sample_index = (sample_index + 1) % NUM_SAMPLES;						// Atualiza o índice circular

	uint16_t soma = 0;														// Inicializa a soma das amostras
	for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
		soma += adc_samples[i];												// Soma todos os valores no buffer
	}

	return (soma / NUM_SAMPLES);											// Retorna a média
}

void calculate_heart_beat(int adc_value) {
	signal = adc_value;
	PERIOD = time_count - ts;

	if (signal < thresh && PERIOD > (IBI / 4) * 3) {						// Evita ruído dicrótico
		if (signal < Lsignal) Lsignal = signal;								// Atualiza o menor valor do sinal
	}

	if (signal > thresh && signal > Hsignal) Hsignal = signal;				// Atualiza o maior valor do sinal

	if (PERIOD >= 240.0) {													// Evita ruído de alta frequência
		if ((signal > thresh) && (!Pulse) && (PERIOD > (IBI / 4) * 3)) {
			Pulse = true;													// Detecta batimento
			IBI = time_count - ts;											// Calcula o intervalo entre batimentos
			ts = time_count;												// Atualiza o tempo inicial

			if (secondBeat) {												// Se for o segundo batimento
				secondBeat = false;
				firstBeat = true;
				BPM = (60000.0 / IBI);											// Calcula BPM
				LED_ON();													// Acende o LED
			}

			if (firstBeat) {												// Se for o primeiro batimento
				firstBeat = false;
				secondBeat = true;
			}
		}
	}

	if (signal < thresh && Pulse) {											// Finaliza o batimento
		Pulse = false;														// Reseta o estado do pulso
		amp = Hsignal - Lsignal;											// Calcula amplitude do sinal
		thresh = amp / 2 + Lsignal;											// Ajusta o limiar
		Hsignal = thresh;
		Lsignal = thresh;
	}

	if (PERIOD > 2000.0) {													// Se mais de 2 segundos sem batimento reset
		thresh = 530;
		Hsignal = 512;
		Lsignal = 512;
		ts = time_count;
		firstBeat = true;
		secondBeat = false;
	}
}

void TIMER0_init(void) {
	TCCR0A = (1 << WGM01);													// Modo CTC
	TCCR0B = (1 << CS01) | (1 << CS00);										// Prescaler 64
	OCR0A = 124;															// Valor para 1ms
	TIMSK0 = (1 << OCIE0A);													// Habilita interrupção de comparação
}

ISR(TIMER0_COMPA_vect) {
	time_count += 1;														// Incrementa o tempo
	update_OLED = 1;														// Atualiza o OLED
	
	if (beat_state == 3) beat_state = 1;
	if (beat_state == 2){
		calculate_heart_beat(adc_value);
		beat_state = 3;
	}
	if (beat_state == 1){
		adc_value = filtro_media_movel(ADC_read(SENSOR_BPM));
		beat_state = 2;
	}

	if ((int)time_count % 100 == 0) LED_OFF();								// Desliga o LED a cada 100ms
	if ((int)time_count % 1000 == 0) {										// A cada 1 segundo
		average_seg += BPM;
		update_batt = 1;
		fall = 0;
	}
	if ((int)time_count % 7500 == 0) {										// A cada 7,5 segundos 4x7,5= 30s
		update_UART = 1;
		uart_status++;
		if (uart_status > 3) uart_status = 1;
	}
	if (time_count > 60000.0) {												// A cada 60 segundos
		average_min = average_seg / 60;
		average_seg = 0.0;
		time_count = 0.0;
		ts = 0.0;
	}

	
}

