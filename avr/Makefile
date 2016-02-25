TARGET = level2

# Default target.
all:
	avr-gcc -mmcu=atmega128 $(TARGET).c -o $(TARGET).hex
	avrdude -p m128 -c USBasp -U flash:w:$(TARGET).hex

assembly:
	gavrasm $(TARGET).asm
	avrdude -p m128 -c USBasp -U flash:w:$(TARGET).hex