stompboard
==========

Karolina wanted some footswitches to change tracks in itunes.
Trying to make this happen with an arduino uno.

notes
-----

```
# I read instructions on  https://arduino.github.io/arduino-cli/1.0/installation/
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
# ...which installs in $PWD/bin
arduino-cli config init
arduino-cli core update-index
arduino-cli core install arduino:avr
cat <<EOF >/tmp/Aproj/Aproj.ino
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);
  delay(3000);
}
EOF
arduino-cli compile --fqbn arduino:avr:uno /tmp/Aproj --output-dir /tmp/Aproj/build
# or: arduino-cli compile --fqbn arduino:avr:uno /tmp/Aproj --verbose
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno /tmp/Aproj
```

bash script
-----------

```
#!/bin/bash

while IFS= read -r line; do
# valid applescript messages to Music.app include:
#   playpause
#   next track
#   previous track
osascript <<EOF
 tell application "Music"
   next track
 end tell
EOF
echo $line
done < /dev/cu.usbmodem21401
```

firmware
--------

- Shorting the two pins on the 6-pin header nearest to the usb port,
  puts the device in DFU ("device firmware update") mode

When I did that I noticed a change from lsusb having
```
Bus 005 Device 015: ID 2a03:0043 dog hunter AG Arduino Uno Rev3
```
to having
```
Bus 005 Device 019: ID 03eb:2fef Atmel Corp. atmega16u2 DFU bootloader
```

In order to save whatever firmware was on the device when I got it, I did
```
dfu-programmer atmega16u2 dump > existing-usbserial.bin
objcopy -I binary -O ihex existing-usbserial.bin existing-usbserial.hex
```

In order to flash a new firmware, I did
```
# put board in dfu mode
dfu-programmer atmega16u2 erase
dfu-programmer atmega16u2 flash ~/tmp/Arduino-usbserial-atmega16u2-Uno-Rev3.hex
dfu-programmer atmega16u2 reset
# plug-cycle board
```
where that `.hex` file came from https://github.com/arduino/ArduinoCore-avr/blob/master/firmwares/atmegaxxu2/arduino-usbserial/Arduino-usbserial-atmega16u2-Uno-Rev3.hex


In order to flash the original firmware, I did
```
# put board in dfu mode
dfu-programmer atmega16u2 erase
dfu-programmer atmega16u2 flash existing-usbserial.hex
dfu-programmer atmega16u2 reset
# plug-cycle board
```

Then I see
```
Bus 005 Device 055: ID 2341:0043 Arduino SA Uno R3 (CDC ACM)
```

firmware
--------

In the [firmware](firmware) directory I have

- Arduino-keyboard-0.3.hex from https://github.com/coopermaa/USBKeyboard/blob/master/firmware/Arduino-keyboard-0.3.hex
- Arduino-usbserial-atmega16u2-Uno-Rev3.hex from https://github.com/arduino/ArduinoCore-avr/blob/master/firmwares/atmegaxxu2/arduino-usbserial/Arduino-usbserial-atmega16u2-Uno-Rev3.hex
- existing-usbserial.hex from the `dfu-programmer atmega16u2 dump` command above. This is what I found on my board after buying it at a yard sale.

Arduino-keyboard
----------------

There are some blog posts from like 2011 where Darran Hunt is experimenting with HID firmware. Some of it exists on wayback machine.

https://web.archive.org/web/20120122101210/http://hunt.net.nz/users/darran/search/?tag=hid

This link
https://web.archive.org/web/20120301033429/http://hunt.net.nz/users/darran/weblog/faf5e/Arduino_UNO_Keyboard_HID_part_2.html
points to
https://web.archive.org/web/20120301033429/http://hunt.net.nz/arduino/arduino-keyboard.tar.gz
which does seem to exist! I struggled to find later versions.

http://hunt.net.nz/sandbox/users/darran/weblog/b3029/attachments/bd341/arduino-keyboard-0.3.tar.gz

Here's another thread where someone is trying to use LUFA:
https://groups.google.com/g/lufa-support/c/TCltpzEU65A

This points to
https://github.com/NicoHood/HID
