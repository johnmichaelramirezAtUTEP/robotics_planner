################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Sensors/subdir.mk
-include src/Planning/subdir.mk
-include src/Control/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
robotics_planner.hex \

SECONDARY_SIZE += \
robotics_planner.siz \


# All Target
all: robotics_planner.elf secondary-outputs

# Tool invocations
robotics_planner.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-linux-gnueabi-gcc -mcpu=arm9 -marm -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -Xlinker --gc-sections -s -LC:/ev3/API -Wl,-Map,"robotics_planner.map" -o "robotics_planner.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

robotics_planner.hex: robotics_planner.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-linux-gnueabi-objcopy -O ihex "robotics_planner.elf"  "robotics_planner.hex"
	@echo 'Finished building: $@'
	@echo ' '

robotics_planner.siz: robotics_planner.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-linux-gnueabi-size --format=berkeley "robotics_planner.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) robotics_planner.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
