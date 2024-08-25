all:
	arduino-cli compile --fqbn arduino:avr:uno src
	arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno src
