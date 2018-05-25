#include <EEPROM.h>
#include <avr/pgmspace.h>

const char msg_contador[] PROGMEM = "Contador";


int cont;
int eeprom_cont_address = 32;
char msg[32];

void setup()
{
	Serial.begin(19200);
	cont = EEPROM.read(eeprom_cont_address);
	strcpy_P( msg, (char*) msg_contador);

}

void loop()
{
	Serial.print(msg);
	Serial.println(cont);

	cont ++;
	EEPROM.write(eeprom_cont_address, cont);
	delay (1000);
}

