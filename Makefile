# Project name. Binary file will be name (TARG).hex
TARG = LoRa

# MCU type & frequency
MCU1=atmega328p
F_CPU1=16000000L
MCU2=atmega328p
F_CPU2=16000000L

# Files in the project
SRCS1 = module1.c avr-libs-master/uart/uart.c avr-libs-master/spi/spi.c LoRa.c
SRCS2 = module2.c avr-libs-master/uart/uart.c avr-libs-master/spi/spi.c LoRa.c

OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

# Flags for compiler
CFLAGS1 = -mmcu=$(MCU1) -DF_CPU=$(F_CPU1) -Wall -g -Os -lm  -mcall-prologues -std=c99
LDFLAGS1 = -mmcu=$(MCU1) -Wall -g -Os
CFLAGS2 = -mmcu=$(MCU2) -DF_CPU=$(F_CPU2) -Wall -g -Os -lm  -mcall-prologues -std=c99
LDFLAGS2 = -mmcu=$(MCU2) -Wall -g -Os

all: module1 module2 clean

module1: $(OBJS1)
	$(CC) $(LDFLAGS1) -o module1.elf  $(OBJS1) -lm
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram  module1.elf module1.hex
	$(SIZE) -t module1.hex

%.o: %.c
	$(CC) $(CFLAGS1) -c -o $@ $<

module2: $(OBJS2)
	$(CC) $(LDFLAGS2) -o module2.elf  $(OBJS2) -lm
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram  module2.elf module2.hex
	$(SIZE) -t module2.hex

%.o: %.c
	$(CC) $(CFLAGS2) -c -o $@ $<

clean:
	rm -f $(SRCS1:.c=.elf) module1.elf $(OBJS1)
	rm -f $(SRCS2:.c=.elf) module2.elf $(OBJS2)

prog: prog1 prog2

prog1:
	avrdude -carduino -P/dev/ttyUSB0 -p$(MCU1) -b57600 -D -Uflash:w:module1.hex:i    # Arduino Nano ATmega328p

prog2:
	avrdude -carduino -P/dev/ttyUSB1 -p$(MCU2) -b115200 -D -Uflash:w:module2.hex:i   # Arduino Uno ATmega368p
