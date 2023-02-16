NAME := main
HEX := $(NAME).hex
OUT := $(NAME).out
MAP := $(NAME).map
SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

MCU := atmega328p
MCU_AVRDUDE := m328p
PROGRAMMER := arduino
DEVICE := /dev/ttyACM0
BAUDRATE := 115200

CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size -A

CFLAGS := -Wall -pedantic -mmcu=$(MCU) -std=c99 -g -Os -DF_CPU=16000000UL
AVRDUDE_FLAGS := -F -V -D -v

all: $(HEX) flash clean

clean:
	rm -f $(HEX) $(OUT) $(MAP) $(OBJECTS)

flash: $(HEX)
	avrdude $(AVRDUDE_FLAGS) -c $(PROGRAMMER) -p $(MCU_AVRDUDE) -P $(DEVICE) -b $(BAUDRATE) -U flash:w:$(HEX)

$(HEX): $(OUT)
	$(OBJCOPY) -R .eeprom -O ihex $< $@

$(OUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ -Wl,-Map,$(MAP) $^
	@echo
	@$(SIZE) $@
	@echo

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<


