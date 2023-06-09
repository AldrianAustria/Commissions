#include <EEPROM.h>

#define read_pin 4
#define output_relay 33

int lampToggle = 1;
int inputVal = 50;
int lampOldEvent = 50;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(64);
  pinMode(output_relay, OUTPUT);
  digitalWrite(output_relay, EEPROM.read(0));
  Serial.println(EEPROM.read(0));

}

void loop() {
  if (inputVal < 30 && lampOldEvent > 30) {
    if (lampToggle == 0) {
      digitalWrite(output_relay, LOW);
      EEPROM.write(0, 0);
      EEPROM.commit();
      lampToggle = 1;
    } else {
      digitalWrite(output_relay, HIGH);
      EEPROM.write(0, 1);
      EEPROM.commit();
      lampToggle = 0;
    }
  }
  lampOldEvent = inputVal;
  inputVal = touchRead(read_pin);
}
