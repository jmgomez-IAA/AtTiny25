
/**
* /usr/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -mmcu=attiny25 -DF_CPU=8000000L -DARDUINO=10609 -DARDUINO_AVR_ATTINYX5 -DARDUINO_ARCH_AVR   -I"/home/share/Workspace/Arduino/Bin/ATTinyCore/avr/cores/tiny" -I"/home/share/Workspace/Arduino/Bin/ATTinyCore/avr/variants/tinyX5" -I"/home/jmgomez/Arduino/libraries/MFRC522" -I"/home/jmgomez/Arduino/libraries/MFRC522/src" -I"/home/share/Workspace/Arduino/Bin/ATTinyCore/avr/libraries/SPI" -MMD -MP -MF"core/HardwareSerial.cpp.d" -MT"core/HardwareSerial.cpp.o" -D__IN_ECLIPSE__=1 -x c++ "/home/share/Workspace/Arduino/Bin/ATTinyCore/avr/cores/tiny/HardwareSerial.cpp"  -o  "core/HardwareSerial.cpp.o"
*
*/

#include <avr/io.h>

using namespace std;

int main(){
	uint8_t test0, test1, test2;

	test1= 10;
	test2 = 25;


	test0 = test1 + test2;



	return 0;
}
