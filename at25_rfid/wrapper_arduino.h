/*
 * wrapper_arduino.h
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#ifndef WRAPPER_ARDUINO_H_
#define WRAPPER_ARDUINO_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

typedef uint8_t byte;

#define LOW 0
#define HIGH 1

void digitalWrite(uint8_t pin, uint8_t val);

#define OUTPUT 1
#define INPUT 0
void pinMode(uint8_t pin, uint8_t dir);

uint8_t digitalRead(uint8_t pin);
void delay(uint8_t ms);

void memcpy(uint8_t *output, uint8_t *input, uint8_t size);

#endif /* WRAPPER_ARDUINO_H_ */
