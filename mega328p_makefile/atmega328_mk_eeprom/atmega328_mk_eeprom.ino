#include <EEPROM.h>


int cont;
int eeprom_cont_address = 0;

void setup()
{
	Serial.begin(19200);
	cont = EEPROM.read(eeprom_cont_address);
}

void loop()
{
	Serial.print("Contador: ");
	Serial.println(cont);

	cont ++;
	EEPROM.write(eeprom_cont_address, cont);
	delay (1000);
}

