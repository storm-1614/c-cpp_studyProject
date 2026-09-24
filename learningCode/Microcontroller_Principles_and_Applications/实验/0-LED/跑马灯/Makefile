BOARD ?= arduino:avr:uno
PORT ?= /dev/ttyUSB0
SKETCH_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

.PHONY: compile upload

compile:
	arduino-cli compile --fqbn $(BOARD) "$(SKETCH_DIR)"
upload: compile
	arduino-cli upload -p $(PORT) --fqbn $(BOARD) "$(SKETCH_DIR)"
