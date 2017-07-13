/*
 * SPIClass.cpp
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#include "SPIClass.h"


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

/* Use friend to modify the class.
void SPIClass::setDataMode(uint8_t spimode){mode = spimode;};
void SPIClass::setClockDivider(uint8_t div){clkdiv = div;};
void SPIClass::setBitOrder(uint8_t order){bitorder = order;};
*/

void SPIClass::beginTransaction(SPISettings settings){
	mode = settings.clock;
	bitorder = settings.clock;
	clkdiv = settings.clock;
};

int SPIClass::transfer(uint8_t val){
	mode = 0;
	return val;
};

void SPIClass::endTransaction(){
	mode  =0;
};
