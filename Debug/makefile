################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.list \


# All Target
all: Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.elf secondary-outputs

# Tool invocations
Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.elf: $(OBJS) $(USER_OBJS) C:\Users\Elif\Desktop\Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje\STM32F030F4PX_FLASH.ld
	arm-none-eabi-gcc -o "Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\Elif\Desktop\Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje\STM32F030F4PX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Gokhan_Beyaz_25221304003_gomulu_sistemler_Vize_Proje.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
