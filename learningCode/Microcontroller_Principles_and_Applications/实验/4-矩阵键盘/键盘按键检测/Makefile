BOARD ?= arduino:avr:uno
PORT ?= /dev/ttyUSB0
ARDUINO_CLI ?= arduino-cli
SKETCH_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR ?= $(SKETCH_DIR).build

.PHONY: deps compile lsp upload clean

# Install the sketch dependency once. The library is installed in Arduino CLI's
# configured user library directory, so both compile and LSP can find it.
deps:
	@if ! $(ARDUINO_CLI) lib list | awk '$$1 == "Keypad" { found = 1 } END { exit !found }'; then \
		$(ARDUINO_CLI) lib install Keypad; \
	fi

compile: deps
	$(ARDUINO_CLI) compile --fqbn $(BOARD) --build-path "$(BUILD_DIR)" "$(SKETCH_DIR)"

# clangd automatically looks for compile_commands.json in the sketch directory.
lsp: deps
	$(ARDUINO_CLI) compile --fqbn $(BOARD) --build-path "$(BUILD_DIR)" --only-compilation-database "$(SKETCH_DIR)"
	cp "$(BUILD_DIR)/compile_commands.json" "$(SKETCH_DIR)compile_commands.json"

upload: compile
	$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD) --build-path "$(BUILD_DIR)" "$(SKETCH_DIR)"

clean:
	rm -rf "$(BUILD_DIR)" "$(SKETCH_DIR)compile_commands.json"
