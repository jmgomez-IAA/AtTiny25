int cont;

void setup()
{
	Serial.begin(19200);
	cont = 0;
}

void loop()
{
	Serial.print("Contador: ");
	Serial.println(cont);

	cont ++;
	delay (1000);
}

