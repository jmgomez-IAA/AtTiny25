COMPILE		= avr-c++
OBJCOPY 	= avr-objcopy
OBJDUMP 	= avr-objdump
SIZE		= avr-size
NM 		= avr-nm
AVRDUDE 	= avrdude
REMOVE 		= rm -f

#CPU Specific flags.
MCU 		= attiny85
F_CPU 		= 1000000

#Compiler flags.
CSTANDARD	= -std=c++11
CPPDEFS		= -DF_CPU=$(F_CPU)UL -mmcu=$(MCU)
CFLAGS		= -Wall -Wextra -pedantic -DF_CPU=$(F_CPU)UL  -mmcu=$(MCU) -fsigned-char -O2 -fno-exceptions
CPPFLAGS	= -std=c++11
CINCLUDES	= -Isrc -Isrc/mcal/avr -Isrc/util/STL -Isrc/util/STL_C++11_Compatibility -Isrc/util/STL_C++17_Compatibility

SOURCES = src/mcal/mcal.cpp  src/mcal/avr/mcal_cpu.cpp  src/mcal/avr/mcal_led.cpp src/mcal/avr/mcal_gpt.cpp src/mcal/avr/mcal_irq.cpp src/mcal/avr/mcal_led.cpp src/sys/start/sys_start.cpp
OBJECTS = bin/mcal.o bin/mcal_cpu.o bin/mcal_gpt.o bin/mcal_irq.o bin/mcal_led.o bin/sys_start.o
#  src/mcal/mcal_gcc_cxx_completion.cpp
#  bin/mcal_gcc_cxx_completion.o
all : chapter02_03.elf

bin/mcal.o	: src/mcal/mcal.cpp
	echo "Compile  : mcal.cpp to bin/mcal.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/mcal.cpp -o bin/mcal.o

#bin/mcal_gcc_cxx_completion.o :  src/mcal/mcal_gcc_cxx_completion.cpp
#	echo "Compile  : mcal_gcc_cxx_completion.cpp to bin/mcal_gcc_cxx_completion.o"
#	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/mcal_gcc_cxx_completion.cpp -o bin/mcal_gcc_cxx_completion.o

bin/mcal_cpu.o : src/mcal/avr/mcal_cpu.cpp
	echo "Compile  : mcal_cpu.cpp to bin/mcal_cpu.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/avr/mcal_cpu.cpp -o bin/mcal_cpu.o

bin/mcal_gpt.o : src/mcal/avr/mcal_gpt.cpp
	echo "Compile  : mcal_gpt.cpp to bin/mcal_gpt.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/avr/mcal_gpt.cpp -o bin/mcal_gpt.o

bin/mcal_irq.o : src/mcal/avr/mcal_irq.cpp
	echo "Compile  : mcal_irq.cpp to bin/mcal_irq.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/avr/mcal_irq.cpp -o bin/mcal_irq.o

bin/mcal_led.o : src/mcal/avr/mcal_led.cpp
	echo "Compile  : mcal_led.cpp to bin/mcal_led.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/mcal/avr/mcal_led.cpp -o bin/mcal_led.o

bin/sys_start.o : src/sys/start/sys_start.cpp
	echo "Compile  : sys_start.cpp to bin/sys_start.o"
	$(COMPILE) -x c++ $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -c src/sys/start/sys_start.cpp -o bin/sys_start.o

chapter02_03.elf : $(OBJECTS)
	echo "Link     : objects to bin/chapter02_03.elf"
	$(COMPILE) -x none -mrelax $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -Wl,--gc-sections  $(OBJECTS) -o bin/chapter02_03.elf
#	avr-objdump -Pmem-usage app.elf
	avr-size -C --mcu=attiny85 bin/chapter02_03.elf


flash :
	echo "Flashing AVRDUDE: Locate Fuses to 1MHz clock."
	avr-objcopy -j .text -j .data -O ihex bin/chapter02_03.elf bin/chapter02_03.hex
	#avrdude -P /dev/ttyACM0 -b 19200 -c avrisp -p t85 -U flash:w:bin/chapter02_03.hex:i

	avrdude -P /dev/ttyUSB0 -b 19200 -c avrisp -p t85 -U flash:w:bin/chapter02_03.hex:i

clear : 
	rm bin/*
