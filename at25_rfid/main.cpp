/*
 * main.cpp
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#define F_CPU 8000000UL  // 1 MHz

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>



#include "wrapper_arduino.h"
#include "SPIClass.h"
#include "MFRC522.h"

constexpr uint8_t RST_PIN = 4;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 3;     // Configurable, see typical pin layout above

SPIClass SPI;
uint8_t spiOn;

//MFRC522 testObject(SS_PIN, RST_PIN);
//MFRC522::MIFARE_Key key;


/** @brief Interrupt vector for pin change on PB0
 *	Solo se acepta una pulsacion, despues deshabilitamos.
 */
/*
ISR (PCINT0_vect){
	uint8_t pinbVal = PINB;
	if (!(pinbVal & 1<<PINB4))   // Trigger if DI is Low
	{
		//GIMSK &= ~_BV(PCIE);
		PINB |= _BV(PINB3);
		spiOn = 1;
	}
}
*/

extern "C" void USI_OVF_vect (void)  __attribute__ ((signal));
void USI_OVF_vect (void){
	SPI.manage_USI_OVF_ISR();
}



extern "C" void TIMER0_COMPA_vect (void)  __attribute__ ((signal));
void TIMER0_COMPA_vect (void){
	SPI.manage_TIMER0_COMPA_ISR();
};


int main(){

	//Prepare and configure interrupts and outputs.
	cli();

	DDRB |= _BV(DDB4) | _BV(DDB3) | _BV(DDB2) | _BV(DDB1);
	//DDRB &=  ~_BV(DDB5) & ~_BV(DDB4) & ~_BV(DDB0);	// Default is 0.
	PORTB |= _BV(PORTB0);  //Pull-ups on PB0.

	// Configure Interrupts to detect pin-change on PB0.
	//GIMSK |= _BV(PCIE);               // Enable pin change interrupts
	//PCMSK |= _BV(PCINT4);             // Enable pin change on pin PB4


	SPI.begin();
	spiOn = 0;

	sei();

	MFRC522 mfrc522(SS_PIN, RST_PIN, &SPI, SPISettings(8, SPISettings::MSBFIRST, SPISettings::SPI_MODE0));


	//void setSPIConfig();
	SPI.setDataMode(SPISettings::SPI_MODE0);

	mfrc522.PCD_Init();

	//PORTB |= _BV(PINB4);	//Take out from sleep mode.
	_delay_ms(50);

	bool result = mfrc522.PCD_PerformSelfTest();

	while(1){
		//if (spiOn == 1){

		_delay_ms(100);
		/*
			SPI.beginTransaction(SPISettings(8, SPISettings::MSBFIRST, SPISettings::SPI_MODE0));
			PORTB &= ~_BV(PINB3);	//SS, slave select 0.
			SPI.transfer(0x02);
			//_delay_ms(2);
			SPI.transfer(0x0F);
			//_delay_ms(20);
			PORTB |= _BV(PINB3);
			spiOn = 0;
		//}
		//_delay_ms(20);
		SPI.endTransaction();
		_delay_ms(50);

		uint8_t readVal = 0xFF;
		do{
			SPI.beginTransaction(SPISettings(8, SPISettings::MSBFIRST, SPISettings::SPI_MODE0));
			PORTB &= ~_BV(PINB3);	//SS, slave select 0.
			SPI.transfer(0x82);
			readVal = SPI.transfer(0x00);
			PORTB |= _BV(PINB3);
			SPI.endTransaction();
			_delay_ms(10);
		}
		while( readVal & (1<<4));
*/
	}

	SPI.stop();

}
