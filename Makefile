# Should be done with original firmware
all:
	arduino-cli compile --fqbn arduino:avr:uno src
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno src

# Flash original arduino firmware
flash-original:
	dfu-programmer atmega16u2 erase
	dfu-programmer atmega16u2 flash firmware/existing-usbserial.hex
	dfu-programmer atmega16u2 reset

# Flash HID device firmware
flash-keyboard:
	dfu-programmer atmega16u2 erase
	dfu-programmer atmega16u2 flash firmware/Arduino-keyboard-0.3.hex
	dfu-programmer atmega16u2 reset
