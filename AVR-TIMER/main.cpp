/**
 * http://www.instructables.com/id/How-to-get-started-with-Eclipse-and-AVR/
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
	PORTB = ~(PINB & 0x08);
	//}

	return;
}

ISR(TIMER0_OVF_vect){

	PORTB &= ~(0x08);
}


int main(void){


	//En primer lugar, deshabilitamos las interrupciones globales.
	// Recuerda que para volver a activarlas se usa la función sei().
	cli();

	buttomValue = 0;

	/*Configure PORT direction*/

	// If DDRxn is  0 (input), and PORTxn is 1 => pull-up enable. Verify Bit 6 – PUD: Pull-up Disable of MCUCR – MCU Control Register
	DDRB |=1<<PB3 | 0<<PB4;  //PB3 is output pin  & PB4 is input pin with pull-up.
	PORTB |= 1<<PB3 | 1<<PB4;	// Set output high.

	/*Configure Interrupts*/
	//Enable Pin PB4 interrupt, mask the rest.
	PCMSK = 0x10;
	//Enable PCIE
	GIMSK = 0x20;

	/*Configure Timers*/
	//GTCCR |= 0b10000001;	// Halts the timer to configure. Reset Prescaler and stop Counter.

	TCCR0B = 1<<CS02 | 1<<CS00;
	TIFR = 1 <<TOV0;
	TIMSK = 1<<TOIE0;
	// WGM0[2:0]= 0 => Normal Mode
	// GTCCR
	//TCCR0A y TCCR0B
	// TCNT0
	// OCR0A y OCR0B y TIFR

	sei();
	// Insert nop for synchronization
	//_NOP();
	PORTB &= 0<<PB3;

	// Read port pins
	while(1){
		/*
		while(buttomValue != 0){
			//Enable Counter.
			GTCCR &= 0b01111111;
		}

		GTCCR |= 0b10000001;	//StopISRs.
*/
		_delay_ms(100);
		//Put Low the outputs
	//	PORTB &= 0<<PB3;
	}

	return 0;
}
