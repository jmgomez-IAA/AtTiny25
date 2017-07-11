/*
 * SPI.h
 *
 *  Created on: 10 jul. 2017
 *      Author: jmgomez
 */


	//Realizar seguiendo esto: https://www.arduino.cc/en/Reference/SPI
	//Definir modo de transmission:
		//SPI Modo 0 Muestrea en flanco positivo. <= Nuestro caso.
		//SPI Modo 1 (Muestres en flanco negativo.


/*
 * SPI Master library for AVRTiny25.
 *
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

//#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>

// SPI_HAS_TRANSACTION means SPI has beginTransaction(), endTransaction(),
// usingInterrupt(), and SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_NOTUSINGINTERRUPT means that SPI has notUsingInterrupt() method
#define SPI_HAS_NOTUSINGINTERRUPT 1

// SPI_ATOMIC_VERSION means that SPI has atomicity fixes and what version.
// This way when there is a bug fix you can check this define to alert users
// of your code if it uses better version of this library.
// This also implies everything that SPI_HAS_TRANSACTION as documented above is
// available too.
#define SPI_ATOMIC_VERSION 1

// Uncomment this line to add detection of mismatched begin/end transactions.
// A mismatch occurs if other libraries fail to use SPI.endTransaction() for
// each SPI.beginTransaction().  Connect an LED to this pin.  The LED will turn
// on if any mismatch is ever detected.
//#define SPI_TRANSACTION_MISMATCH_LED 5

#define MSBFIRST

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif


#define SPI_CLOCK_DIV1 0x01
#define SPI_CLOCK_DIV8 0x02
#define SPI_CLOCK_DIV64 0x03
#define SPI_CLOCK_DIV256 0x04
#define SPI_CLOCK_DIV1024 0x05

#define SPI_CLOCK_T0_POS 0x06
#define SPI_CLOCK_TO_NEG 0x07


#define _SPI_MODE0 0x00
#define _SPI_MODE1 0x04
#define _SPI_MODE2 0x08
#define _SPI_MODE3 0x0C

#define MAX_TX_SIZE  32
#define MAX_RX_SIZE  32


//Tal ve controlar las fases se importante, Revisas datasheet a ver cuando muestrea el Attiny25.
enum SPI_MODE {SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3};
//enum BYTE_ORDER {MSBFIRST, LSBFIRST};
enum OP {Stop, Tx, Rx, Idle, Wait};




class SPISettings {
private:
  friend class SPIClass;
public:

  // Expected configuration. SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
	  /*
    if (__builtin_constant_p(clock)) {
      init_AlwaysInline(clock, bitOrder, dataMode);
    } else {
      init_MightInline(clock, bitOrder, dataMode);
    }
    */

  };
  SPISettings() {
  //  init_AlwaysInline(4000000, 1, SPI_MODE0);
  };


};



class SPIClass {
private:
	OP spi_cmd;
	//uint8_t spi_rx_buffer[MAX_RX_SIZE];


	//static uint8_t initialized;
	//static uint8_t interruptMode; // 0=none, 1=mask, 2=global
	//static uint8_t interruptMask; // which interrupts to mask
	//static uint8_t interruptSave; // temp storage, to restore state
#ifdef SPI_TRANSACTION_MISMATCH_LED
	static uint8_t inTransactionFlag;
#endif

	void stopTimer();
	void startTimer();
	void setCounterTime();
	void setCounterMode();
	void configSPI();

public:
  // Initialize the SPI library
  void begin();

  // Before using SPI.transfer() or asserting chip select pins,
  // this function is used to gain exclusive access to the SPI bus
  // and configure the correct settings.
  void beginTransaction(SPISettings settings);

  //perform a group of transfers and releasing the chip select
  void transfer(void *buf, size_t count);

  // After performing a group of transfers and releasing the chip select
  // signal, this function allows others to access the SPI bus
  void endTransaction(void);
  // Disable the SPI bus
 // static void end();
};

extern SPIClass SPI;

#endif


