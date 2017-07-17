/*
 * SPIClass.cpp
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#include "SPIClass.h"


uint8_t spi_tx_count;
uint8_t transmissionSize;
uint8_t *spi_tx_buffer;
uint8_t usi_byte_read;


/*
 * @brief USI Counter Overflow Interrupt handler.
 * If there are pendant data to transmit continue, otherwise stop Timer/Counter
 */
/*
extern "C" void USI_OVF_vect (void)  __attribute__ ((signal));

void USI_OVF_vect (void){
//void __attribute__((interrupt)) USI_OVF_vect(void){
	spi_tx_count++;
	USISR = _BV(USIOIF);
	usi_byte_read = USIBR;

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
		//spi_state = READY;

	}
}
*/
/** @brief Handle Compare Interrupt.
 * It means we are on the middle of the SPI bit reception.
 * Just start the USI module.
 */
/*
extern "C" void TIMER0_COMPA_vect (void)  __attribute__ ((signal));

void TIMER0_COMPA_vect (void){

//ISR(TIMER0_COMPA_vect){
	USICR |= _BV(USITC);
	PINB |= _BV(PINB3);
};
*/


SPIClass::SPIClass() {
	// TODO Auto-generated constructor stub
	clkdiv = 10;
}

SPIClass::SPIClass(SPISettings &spiConfig) {
	// TODO Auto-generated constructor stub
	clkdiv = 10;
}


SPIClass::~SPIClass() {
	// TODO Auto-generated destructor stub
	clkdiv = 0;
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
void SPIClass::configSPI(SPISettings settings){
	//USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS0);	// No funciona, Reloj mitad de periodo que la salida.

	USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS1) | _BV(USICLK); // Software CLK. Positive Edge.

	if (settings.spiMode == SPISettings::SPI_MODE0){
		USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS1) | _BV(USICLK); // Software CLK. Positive Edge.
	}

	if (settings.spiMode == SPISettings::SPI_MODE3){
		USICR |=  _BV(USIOIE) | _BV(USIWM0) | _BV(USICS1) | _BV(USICS0) | _BV(USICLK); // Software CLK. Negative Edge.
	}

}

/* Use friend to modify the class.
void SPIClass::setDataMode(uint8_t spimode){mode = spimode;};
void SPIClass::setClockDivider(uint8_t div){clkdiv = div;};
void SPIClass::setBitOrder(uint8_t order){bitorder = order;};
*/

void SPIClass::begin(){
	spi_state = IDLE;

}

void SPIClass::stop(){
	spi_state = STOP;

}

void SPIClass::beginTransaction(SPISettings settings){
//Configure the USI to these settings.

	// Stop and reset Timer.
	stopTimer();
	// Configure
	setCounterMode();
	//Calculate from SPISettings.
	setCounterTime();

	//Configure USI module as SPI.
	configSPI(settings);

	spi_state = READY;

};

int SPIClass::transfer(uint8_t val){
	mode = 0;
	spi_state = TRANSMIT;

	//Charges first value

	USIDR = val;
	USISR &= ~_BV(0x0F);	//Secounter to 0.
	USISR |= _BV(0x07);	//Secounter to 0.
	transmissionSize = 1;
	spi_tx_count = 0;
	startTimer();

	while(spi_state == TRANSMIT){
			_delay_us(1);
	};
	return usi_byte_read;
};

void SPIClass::transfer(void *buf, size_t count){
	uint8_t num_bytes = 0;

	spi_tx_buffer =  (uint8_t *) buf;

	spi_state = TRANSMIT;
	//Charges first value
	USIDR = *spi_tx_buffer;
	transmissionSize = count;
	spi_tx_count = 0;
	startTimer();

}


void SPIClass::endTransaction(){
	mode  =0;
	stopTimer();
};

void SPIClass::manage_USI_OVF_ISR(){
	//void __attribute__((interrupt)) USI_OVF_vect(void){
		spi_tx_count++;
		USISR = _BV(USIOIF);
		usi_byte_read = USIBR;

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
			spi_state = READY;
		}
};

void SPIClass::manage_TIMER0_COMPA_ISR(){
	//ISR(TIMER0_COMPA_vect){
		USICR |= _BV(USITC);
		//PINB |= _BV(PINB3);
};


