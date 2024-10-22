uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t keySpace[8] = { 0, 0, 44, 0, 0, 0, 0 };

int switch1 = 5;
int switch2 = 4;
int switch3 = 3;
int onboardPin = 13;

void setup() {
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);

  pinMode(onboardPin, OUTPUT);
    Serial.begin(9600);
}

int ledVal = HIGH;

       /* Serial.write(keySpace, 8); */
       /* Serial.read(); */
       /* Serial.write(keyNone, 8); */

void handleSwitch(int index) {
  ledVal = !ledVal;
  digitalWrite(onboardPin, ledVal);
  char buf[64];
  snprintf(buf, 63, "switch %d\n", index);
  Serial.write(buf, strlen(buf));
}

void loop() {
  digitalWrite(onboardPin, ledVal);
  int switch1val = digitalRead(switch1);
  int switch2val = digitalRead(switch2);
  int switch3val = digitalRead(switch3);

  while (1) {
    int new1val = digitalRead(switch1);
    int new2val = digitalRead(switch2);
    int new3val = digitalRead(switch3);
    if (switch1val != new1val) {
      handleSwitch(1);
      switch1val = new1val;
      delay(500);
    }
    if (switch2val != new2val) {
      handleSwitch(2);
      switch2val = new2val;
      delay(500);
    }
    if (switch3val != new3val) {
      handleSwitch(3);
      switch3val = new3val;
      delay(500);
    }
  }
}
