################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFRC522.cpp \
../MFRC522Debug.cpp \
../MFRC522Extended.cpp \
../MFRC522Hack.cpp \
../SPI.cpp \
../main.cpp 

OBJS += \
./MFRC522.o \
./MFRC522Debug.o \
./MFRC522Extended.o \
./MFRC522Hack.o \
./SPI.o \
./main.o 

CPP_DEPS += \
./MFRC522.d \
./MFRC522Debug.d \
./MFRC522Extended.d \
./MFRC522Hack.d \
./SPI.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/share/Workspace/Arduino/Resources/Libraries/rfid/src -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wcpp -funsigned-char -funsigned-bitfields -fno-exceptions -std=c++11 -mmcu=attiny25 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


