/*
 * SPI.cpp
 *
 *  Created on: 10 jul. 2017
 *      Author: jmgomez
 */


#include "SPI.h"

uint8_t spi_tx_count;
uint8_t transmissionSize;
uint8_t *spi_tx_buffer;


/*
 * @brief USI Counter Overflow Interrupt handler.
 * If there are pendant data to transmit continue, otherwise stop Timer/Counter
 */

extern "C" void USI_OVF_vect (void)  __attribute__ ((signal));

void USI_OVF_vect (void){
//void __attribute__((interrupt)) USI_OVF_vect(void){
	spi_tx_count++;
	USISR = _BV(USIOIF);

	if (spi_tx_count < transmissionSize){
		//Parece que no es necesario volver a configurar.
		//USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS0);
		USIDR = spi_tx_buffer[spi_tx_count];
		//GTCCR &= ~_BV(TSM);
		//GTCCR |= _BV(PSR0); //Reset prescaler, tal vez para ajustar mejor los tiempos.

	}
	else{
		//GTCCR |= _BV(TSM) | _BV(PSR0);	//Stop clock generation.
		//TIMSK &= ~_BV(OCIE0A);	//Stop Timer Counter ISR. No CLK on USCk
		//USICR = 0;
		transmissionSize = 0;

	}
}

/** @brief Handle Compare Interrupt.
 * It means we are on the middle of the SPI bit reception.
 * Just start the USI module.
 */
extern "C" void TIMER0_COMPA_vect (void)  __attribute__ ((signal));

void TIMER0_COMPA_vect (void){

//ISR(TIMER0_COMPA_vect){
	USICR |= _BV(USITC);
};



void SPIClass::begin(){
	spi_cmd = Idle;
	uint8_t transmissionSize = 0;
	uint8_t spi_tx_count = 0;
	//initialized = 0;
}


/**
 * @brief Kept the Counter in Reset State. It ensueres the counter is halted.
 **/
void SPIClass::stopTimer(){
	GTCCR |= _BV(TSM);
	GTCCR |= _BV(PSR0);
}

/**
 * @brief PSR0 will be cleared by Hardware and the counter will start counting.
 **/
void SPIClass::startTimer(){
	GTCCR |= _BV(PSR0);
	GTCCR &= ~_BV(TSM);
}


/**
 * @brief Set counter mode, with Clear Timer on Compare Match mode.
 **/
void SPIClass::setCounterMode(){
	//Set CTC mode.
	TCCR0A |= _BV(WGM01);

	//Clear and enable interrupts.
	TIFR |= _BV(OCF0A);              // Clear output compare interrupt flag
	TIMSK |= _BV(OCIE0A);             // Enable output compare interrupt
}

/**
 * @brief Set Counter Time.
 **/
void SPIClass::setCounterTime(){
	TCCR0B |= _BV(CS01); //clkIO/8 preescaling.
	OCR0A = 0x68;//CYCLES_PER_BIT;
	TCNT0 = 0;                      // Count up from 0
}


/* @brief Configure USI register to Three-wire Mode. Should be used counter as Software CLK.
 * The clock source for the counter and for the USCk is teken from Timer 0 Compare Match.
 * Interrupts will be generated, untill end of tranmission.
 * Data on positive Edges.
 * @pre The Counter should configured, but stopped PSR0=0.
 */
void SPIClass::configSPI(){
	//USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS0);	// No funciona, Reloj mitad de periodo que la salida.
	//USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS1) | _BV(USICS0) | _BV(USICLK); // Software CLK. Negative Edge.
	USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS1) | _BV(USICLK); // Software CLK. Positive Edge.

}

// Before using SPI.transfer() or asserting chip select pins,
// this function is used to gain exclusive access to the SPI bus
// and configure the correct settings.
void SPIClass::beginTransaction(SPISettings settings) {


	// Stop and reset Timer.
	stopTimer();
	// Configure
	setCounterMode();
	setCounterTime();

	//Configure USI module as SPI.
	configSPI();

}


void SPIClass::transfer(void *buf, size_t count){
	uint8_t num_bytes = 0;

	spi_tx_buffer =  (uint8_t *) buf;

	spi_cmd = Tx;
	//Charges first value
	USIDR = *spi_tx_buffer;
	transmissionSize = count;
	spi_tx_count = 0;
	startTimer();
}


// After performing a group of transfers and releasing the chip select
// signal, this function allows others to access the SPI bus
void SPIClass::endTransaction(void){
	stopTimer();
	spi_cmd = Idle;
}


