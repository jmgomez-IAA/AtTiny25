/**
 * http://www.instructables.com/id/How-to-get-started-with-Eclipse-and-AVR/
 * http://www.atmel.com/webdoc/avrlibcreferencemanual/group__avr__interrupts.html
 * */



#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


uint8_t buttomValue;

/**
 *  @brief Interrupt routine.
 *  There are 2 sources for external GPIO interrupt. INT0 and PCINT0[5..0].
 *  PCINT0[5..0] -> Pin change asynchronous interrupt, trigger when pin toggles. The PCMSK register control which pins INT is enabled.
 *  INT0, interrupt level, triggers when the pin is in a level.
 **/
ISR(PCINT0_vect){

	//Check whihc is interrupt source
	//if (GIFR & 0x10){
		if (PINB & 0x10){
		//Enable LED blink.
			buttomValue = 1;
		}
		else{
		//Disable LED blink.
			buttomValue = 0;
		}
	//}

	return;
}


int main(void){


	//En primer lugar, deshabilitamos las interrupciones globales.
	// Recuerda que para volver a activarlas se usa la función sei().
	cli();

	buttomValue = 0;

	// If DDRxn is  0 (input), and PORTxn is 1 => pull-up enable. Verify Bit 6 – PUD: Pull-up Disable of MCUCR – MCU Control Register
	DDRB |=1<<PB3 | 0<<PB4;  //PB3 is output pin  & PB4 is input pin with pull-up.
	PORTB |= 1<<PB3 | 1<<PB4;	// Set output high.

	//Enable Pin PB4 interrupt, mask the rest.
	PCMSK = 0x10;
	//Enable PCIE
	GIMSK = 0x20;

	sei();
	// Insert nop for synchronization
	//_NOP();
	PORTB &= 0<<PB3;

	// Read port pins

	while(1){
		while(buttomValue != 0){
			PORTB &= ~(1<<PB3);/* PB3 LOW */
			_delay_ms(100);/* 100 ms delay */

			PORTB |=(1<<PB3); /* PB3 HIGH */
			_delay_ms(100);/* 100 ms delay */

		}

		//Put Low the outputs
		PORTB &= 0<<PB3;
	}

	return 0;
}
