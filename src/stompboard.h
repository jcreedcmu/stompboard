uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t keyA[8] = { 0, 0, 4, 0, 0, 0, 0 };

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  uint8_t ledStatus;
  Serial.write(keyA, 8);
  ledStatus = Serial.read();
  Serial.write(keyNone, 8);
  delay(1000);
}


/* int readPin = 8; */
/* int onboardPin = 13; */

/* void setup() { */
/*   pinMode(readPin, INPUT); */
/*   pinMode(onboardPin, OUTPUT); */
/*   Serial.begin(9600); */
/* } */

/* void loop() { */
/*   int ledVal = HIGH; */
/*   digitalWrite(onboardPin, ledVal); */
/*   int oldVal = digitalRead(readPin); */

/*   while (1) { */
/*     int newVal = digitalRead(readPin); */
/*     if (oldVal != newVal) { */
/*       Serial.write("change\n"); */
/*       ledVal = !ledVal; */
/*       digitalWrite(onboardPin, ledVal); */
/*       oldVal = newVal; */
/*       delay(100); */
/*     } */
/*   } */
/* } */
