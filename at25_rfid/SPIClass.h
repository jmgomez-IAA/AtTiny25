/*
 * SPIClass.h
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#ifndef SPICLASS_H_
#define SPICLASS_H_

#include <avr/io.h>

class SPIClass;

#define SPI_CLOCK_DIV8 8
#define MSBFIRST 1
#define SPI_MODE0 0

class SPISettings{
public:
	//SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0
	SPISettings(uint8_t clock_div, uint8_t byteorder, uint8_t mode){
		clock = 8;
	};

private:
	uint8_t clock;

	friend SPIClass;
};

class SPIClass {
public:
	SPIClass();
	SPIClass(SPISettings &spiConfig);
	void setDataMode(uint8_t spimode){mode = spimode;};
	void setClockDivider(uint8_t div){clkdiv = div;};
	void setBitOrder(uint8_t order){bitorder = order;};

	void beginTransaction(SPISettings settings);
	int transfer(uint8_t val);
	void endTransaction();
	~SPIClass();

private:
	uint8_t clkdiv;
	uint8_t mode;
	uint8_t bitorder;
	uint8_t state;
};


extern SPIClass SPI;
#endif /* SPICLASS_H_ */
