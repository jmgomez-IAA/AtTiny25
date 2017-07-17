################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFRC522.cpp \
../SPIClass.cpp \
../main.cpp \
../wrapper_arduino.cpp 

OBJS += \
./MFRC522.o \
./SPIClass.o \
./main.o \
./wrapper_arduino.o 

CPP_DEPS += \
./MFRC522.d \
./SPIClass.d \
./main.d \
./wrapper_arduino.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -std=c++11 -mmcu=attiny25 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


