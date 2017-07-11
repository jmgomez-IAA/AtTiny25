/**
 * https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829
 * http://www.instructables.com/id/How-to-get-started-with-Eclipse-and-AVR/
 * http://www.atmel.com/webdoc/avrlibcreferencemanual/group__avr__interrupts.html
 * https://wiki.mcselec.com/bavr/index.php?title=Using_USI_(Universal_Serial_Interface)&redirect=no#Example_.28SPI_Master_with_USI.29:
 * http://www.naylampmechatronics.com/blog/22_Tutorial-Lector-RFID-RC522.html
 * https://waterproofman.wordpress.com/2007/02/07/avr-interrupts-in-c/
 *
 * https://www.arduino.cc/en/Reference/SPI
 *
 * Baudrate Max = 10Mbits/s
 * 64 Bytes Tx/Rx Buffer.
 * */



#define F_CPU 8000000UL
#define SPI_BAUD (F_CPU/8)/100

#define CYCLES_PER_BIT      ( F_CPU / SPI_BAUD ) //utilizar esto para calcular cuanto tiempo dara CLK para lecturas.



#include <avr/io.h>
#include <avr/interrupt.h>
#include "SPI.h"
#include <util/delay.h>
#include "MFRC522.h"



uint8_t tx_buffer[MAX_TX_SIZE];
uint8_t rx_buffer[MAX_RX_SIZE];



/** @brief Interrupt vector for pin change on PB0
 *	Solo se acepta una pulsacion, despues deshabilitamos.
 */
ISR (PCINT0_vect){
	uint8_t pinbVal = PINB;
	if (!(pinbVal & 1<<PINB4))   // Trigger if DI is Low
	{
		//GIMSK &= ~_BV(PCIE);
		PINB |= _BV(PINB3);
	}
}



/**
 * @brief Configure the USI register to three-wire mode.
 *
 * Configuration PINS for SPI.
 *
 *  El SPI se implementa empleando el Three-wire Mode del USI Interface.
 *
 * PB0 => DI (input pull-up)
 * PB1 => DO (output )
 * PB2 => USCK (output)
 *
 * PB3 => SS (output) Select Slave.
 * Verificar si es compatible con el LED.
 **/


SPIClass SPI;

int main(void){


	//Disable Interrupts
	cli();

	DDRB |= _BV(DDB3) | _BV(DDB2) | _BV(DDB1);
	//DDRB &=  ~_BV(DDB5) & ~_BV(DDB4) & ~_BV(DDB0);	// Default is 0.
	PORTB |= _BV(PORTB0);  //Pull-ups on PB0.

	// Configure Interrupts to detect pin-change on PB0.
	GIMSK |= _BV(PCIE);               // Enable pin change interrupts
	PCMSK |= _BV(PCINT4);             // Enable pin change on pin PB4

	//spi_cmd = Stop;
	SPI.begin();


	sei();

	for (uint8_t i= 0; i < MAX_TX_SIZE; ++i){
		tx_buffer[i] = (i%2)?0x55: 0x42;
	}

	// Insert nop for synchronization
	//_NOP();
	//PORTB |= 1<<PB3;

	// Read port pins
	while(1){
		PINB |= _BV(PINB3);
		_delay_ms(1000);/* 100 ms delay */
	//	SPI.endTransaction();
		//PORTB |= _BV(PB3);
		SPI.beginTransaction(SPISettings());

		SPI.transfer((void *) tx_buffer, 16);


	}

	return 0;
}
