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
