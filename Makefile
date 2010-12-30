TARGET = spi
MCU    = atmega168
FORMAT = ihex

PROGRAMMER = dragon_isp
PROGRAMMER_PORT = usb

CFLAGS = -g -Os -Wall -mmcu=$(MCU) -ffunction-sections -fdata-sections -std=gnu99
LDFLAGS = 

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

SRC = $(TARGET).c
OBJ = $(SRC:.c=.o)

all: $(TARGET).elf

upload: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PROGRAMMER_PORT) -e -U flash:w:$(TARGET).hex

%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.elf *.hex

	
