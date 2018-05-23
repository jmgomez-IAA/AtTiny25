
default:
	# compile for attiny86 with warnings, optimizations, and 1 MHz clock frequency
	avr-gcc -Wall -Os -DF_CPU=1000000 -mmcu=attiny85 -o hello.elf hello.c
	avr-objcopy -j .text -j .data -O ihex hello.elf hello.hex
	avr-size -C --mcu=attiny85 hello.elf
	#avrdude -c avrisp -P /dev/ttyACM0-p t85 -U flash:w:hello.hex:i
	avrdude -P /dev/ttyUSB0 -b 19200 -c avrisp -p t85 -U flash:w:hello.hex:i
clean: l
	rm -f hello.o hello.hex
