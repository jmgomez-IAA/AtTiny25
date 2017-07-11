################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
AVR-USI.lss \

FLASH_IMAGE += \
AVR-USI.hex \

EEPROM_IMAGE += \
AVR-USI.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: AVR-USI.elf secondary-outputs

# Tool invocations
AVR-USI.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,AVR-USI.map,--cref -mrelax -Wl,--gc-sections -mmcu=attiny25 -o "AVR-USI.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AVR-USI.lss: AVR-USI.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AVR-USI.elf  >"AVR-USI.lss"
	@echo 'Finished building: $@'
	@echo ' '

AVR-USI.hex: AVR-USI.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex AVR-USI.elf  "AVR-USI.hex"
	@echo 'Finished building: $@'
	@echo ' '

AVR-USI.eep: AVR-USI.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex AVR-USI.elf  "AVR-USI.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AVR-USI.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny25 AVR-USI.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: AVR-USI.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pt25 -carduino -P/dev/ttyACM0 -b19200 -Uflash:w:AVR-USI.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(PDE_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(CC_DEPS)$(ELFS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) AVR-USI.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
