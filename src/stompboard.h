int readPin = 8;
int ledPin = 9;
int onboardPin = 13;

void setup() {
  pinMode(readPin, INPUT);
  pinMode(ledPin, OUTPUT);
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
      Serial.write("change\n");
      ledVal = !ledVal;
      digitalWrite(onboardPin, ledVal);
      oldVal = newVal;
      delay(100);
    }
  }
}
