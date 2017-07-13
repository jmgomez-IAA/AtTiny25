/*
 * main.cpp
 *
 *  Created on: 12 de jul. de 2017
 *      Author: greenlean
 */

#include <avr/io.h>
#include "wrapper_arduino.h"
#include "SPIClass.cpp"
//#include "MFRC522.h"

constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above

//MFRC522 testObject(SS_PIN, RST_PIN);


//MFRC522::MIFARE_Key key;

SPIClass SPI;

int main(){

	//void setSPIConfig();
	SPI.setDataMode(10);
}
