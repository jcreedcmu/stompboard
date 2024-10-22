// Debugging mode assumes standard arduino firmware so that serial
// writes end up on (for me on my machine) /dev/ttyACM0.
#define DEBUG 1

// Taken from pp90-91 of https://usb.org/sites/default/files/hut1_5.pdf
#define KEY_SPACE 0x2c // Keyboard Space Bar
#define KEY_RIGHT 0x4f // Keyboard Right Arrow
#define KEY_LEFT 0x50 // Keyboard Left Arrow

// The data we send for a key event is an 8-byte structure.
// cf. https://wiki.osdev.org/USB_Human_Interface_Devices
// Byte 0 is for modifier keys, which we don't emulate.
// Byte 1 is reserved
// The subsequent 6 bytes are for scan codes of keys currently pressed.
// We only ever emulate pressing one key at a time, so we use only byte 2.
#define KEYPRESS_1 2

uint8_t scanCodes[3] = { KEY_LEFT, KEY_SPACE, KEY_RIGHT };

uint8_t keyNone[8] = { 0, 0, 0, 0, 0, 0, 0 };
uint8_t keyBuf[8] = { 0, 0, 0, 0, 0, 0, 0 };

int switch0 = 5;
int switch1 = 4;
int switch2 = 3;
int onboardLedPin = 13;

void setup() {
  pinMode(switch0, INPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);

  pinMode(onboardLedPin, OUTPUT);

  Serial.begin(9600); // This is used in both debug and production mode.
  // Perhaps the USB HID firmware intercepts serial writes? In any case
  // it's how we update key state, by sending 8-byte frames.
}

int ledVal = HIGH;

// index should be 0, 1, or 2.
void handleSwitch(int index) {
#ifdef DEBUG
  ledVal = !ledVal;
  digitalWrite(onboardLedPin, ledVal);
  char buf[64];
  snprintf(buf, 63, "switch %d\n", index);
  Serial.write(buf, strlen(buf));
#else
  keyBuf[KEYPRESS_1] = scanCodes[index];
  Serial.write(keyBuf, 8);
  Serial.read();
  Serial.write(keyNone, 8);
#endif
}

void loop() {
  digitalWrite(onboardLedPin, ledVal);
  int switch0val = digitalRead(switch0);
  int switch1val = digitalRead(switch1);
  int switch2val = digitalRead(switch2);

  while (1) {
    int new0val = digitalRead(switch0);
    int new1val = digitalRead(switch1);
    int new2val = digitalRead(switch2);
    if (switch0val != new0val) {
      handleSwitch(0);
      switch0val = new0val;
      delay(500);
    }
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
  }
}
