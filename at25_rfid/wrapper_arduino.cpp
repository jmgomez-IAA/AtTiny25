/*
 * wrapper_arduino.cpp
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#include <avr/io.h>
#include "wrapper_arduino.h"

void digitalWrite(uint8_t pin, uint8_t val){
	if (val == 1)
		PORTB |= _BV(val);
	else
		PORTB &= ~_BV(val);
};

void pinMode(uint8_t pin, uint8_t dir){
	if (dir ==1)
		DDRB |= _BV(pin);
	else
		DDRB &= ~_BV(pin);
}

uint8_t digitalRead(uint8_t pin){

	return PINB;
}

void delay(uint8_t ms){
	_delay_ms(ms);
}

void memcpy(uint8_t *output, uint8_t *input, uint8_t size){
	for(uint8_t i=0; i< size; ++i){
		output[i] = input[i];
	}
}
