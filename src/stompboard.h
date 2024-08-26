uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t keySpace[8] = { 0, 0, 44, 0, 0, 0, 0 };

int readPin = 8;
int onboardPin = 13;

void setup() {
  pinMode(readPin, INPUT);
  pinMode(onboardPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ledVal = HIGH;
  digitalWrite(onboardPin, ledVal);
  int oldVal = digitalRead(readPin);

  while (1) {
    int newVal = digitalRead(readPin);
    if (oldVal != newVal) {

      // Send space character
      Serial.write(keySpace, 8);
      Serial.read();
      Serial.write(keyNone, 8);

      ledVal = !ledVal;
      digitalWrite(onboardPin, ledVal);
      delay(100);
      oldVal = newVal;
    }
  }
}
