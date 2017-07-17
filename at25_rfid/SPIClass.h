/*
 * SPIClass.h
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#ifndef SPICLASS_H_
#define SPICLASS_H_

#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>

class SPIClass;

#define SPI_CLOCK_DIV8 8

class SPISettings{
public:

	/**
	 * SPI Data modes: Four combinations of SCK Phase (CPHA) and Polarity (POL).
	 *
	 *  	- SPI_MODE0 : CPHA=0  & CPLO=0 => No phase offset. Samples on High, Change on Low.
	 *  	- SPI_MODE2 : CPHA=0  & CPLO=1 => No phase offset. Samples on Low, Change on High.
	 *  	- SPI_MODE1 : CPHA=1  & CPLO=0 => half cycle phase offset. Samples on High, Change on Low.
	 *  	- SPI_MODE3 : CPHA=1  & CPLO=0 => half cycle phase offset. High, Change on Low.
	 **/
	enum SPI_MODE{ SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3};
	enum BYTE_ORDER{ LSBFIRST, MSBFIRST};


	//SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0
	SPISettings(uint8_t clock_div, BYTE_ORDER byte_order, SPI_MODE spi_mode){
		clockDiv = clock_div;
		byteOrder = byte_order;
		spiMode = spi_mode;
	};

private:
	uint8_t clockDiv;
	BYTE_ORDER byteOrder;
	SPI_MODE spiMode;

	friend SPIClass;
};


class SPIClass {
public:
	enum IF_STATUS {IDLE, READY, TRANSMIT, RECEIVE, STOP};

	SPIClass();
	SPIClass(SPISettings &spiConfig);
	void setDataMode(SPISettings::SPI_MODE spimode){mode = spimode;};
	void setClockDivider(uint8_t div){clkdiv = div;};
	void setBitOrder(SPISettings::BYTE_ORDER order){bitorder = order;};

	void begin();
	void stop();
	void beginTransaction(SPISettings settings);
	int transfer(uint8_t val);
	void transfer(void *buf, size_t count);
	void endTransaction();

	void manage_USI_OVF_ISR();
	void manage_TIMER0_COMPA_ISR();
	~SPIClass();

private:
	IF_STATUS spi_state;
	uint8_t clkdiv;
	uint8_t mode;
	uint8_t bitorder;
	uint8_t state;

	//Auxiliary Funtions
	void setCounterMode();
	void setCounterTime();
	void configSPI(SPISettings settings);
	void stopTimer();
	void startTimer();
};


extern SPIClass SPI;
#endif /* SPICLASS_H_ */
