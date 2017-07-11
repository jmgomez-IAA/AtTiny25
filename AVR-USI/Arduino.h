/*
 * Arduino.h
 *
 *  Created on: 11 jul. 2017
 *      Author: jmgomez
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <avr/io.h>

#define LOW 0
#define HIGH 1

typedef uint8_t byte;

void digitalWrite(uint8_t pinNumber, uint8_t value){

	if (value == HIGH){
		PORTB |= _BV(pinNumber);
	}
	else{
		PORTB &= ~ _BV(pinNumber);
	}
}
#endif /* ARDUINO_H_ */
