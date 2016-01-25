CC = avr-gcc
DEVICE = atmega32u4

TARGET = "teensy_level1"



MMCU = -mmcu=$(DEVICE)
CFLAGS = -Os -Wall
CFLAGS += $(MMCU)

CC += $(CFLAGS)

all:
	$(CC) $(TARGET).c -o $(TARGET).hex

asm:
	gavrasm -lb $(TARGET).asm

teensy:
	teensy_loader_cli -mmcu=atmega32u4 -w -v $(TARGET).hex

program: $(TARGET).hex
	avrdude -p m32u4 -c USBasp -U flash:w:$(TARGET).hex

clean:
	rm -rf *.o *.s *.err *.lst *.hex *.out
