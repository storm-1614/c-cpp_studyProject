compile: ./0-LED.ino
	arduino-cli compile --fqbn arduino:avr:uno .
upload: compile
	arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:uno .
