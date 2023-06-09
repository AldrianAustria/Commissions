//Library
#include <EEPROM.h>

//Pin  Definitions
#define touchPin 4
#define outputRelay 33

//Logic Variables
int lampToggle = 1;
int inputVal = 0;
int lampOldEvent = 0;

void setup() {
  //Setup pins
  pinMode(outputRelay, OUTPUT);
  pinMode(touchPin, INPUT);
  //EEPROM Init
  EEPROM.begin(64);
  //Sets Previous state on start
  digitalWrite(outputRelay, EEPROM.read(0));
}

void loop() {
  //Latching Logic
  if (inputVal == HIGH && lampOldEvent == LOW) {
    if (lampToggle == 0) {
      //Turn On
      digitalWrite(outputRelay, LOW);
      //Sets EEPROM address 0 to 0
      EEPROM.write(0, 0);
      EEPROM.commit();
      lampToggle = 1;
    } else {
      //Turn Off
      digitalWrite(outputRelay, HIGH);
      //Sets EEPROM address 0 to 1
      EEPROM.write(0, 1);
      EEPROM.commit();
      lampToggle = 0;
    }
  }
  lampOldEvent = inputVal;

  //Read touch input
  inputVal = digitalRead(touchPin);
}
