#include <EEPROM.h>

#define LED_BUILTIN 4
#define MY_BUTTON 3

unsigned int buttom_status_address = 0;
byte buttom_status = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MY_BUTTON, INPUT);
  pinMode(MY_BUTTON, INPUT_PULLUP);
  buttom_status = EEPROM.read(buttom_status_address );
}

void loop() {
  if (buttom_status == 0 )
  {
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(200);  
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); 
    delay(200);  
  }
  
  // Change Buttom Status
  if(digitalRead(MY_BUTTON) == LOW)  
  {
    while(digitalRead(MY_BUTTON) == LOW)
    {
      delay(100);
    }
    
    buttom_status = 1 - buttom_status;
    EEPROM.update(buttom_status_address ,buttom_status);
    delay(1000);
  }

  
}
