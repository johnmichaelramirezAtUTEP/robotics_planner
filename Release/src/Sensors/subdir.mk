################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Sensors/sensors.c 

OBJS += \
./src/Sensors/sensors.o 

C_DEPS += \
./src/Sensors/sensors.d 


# Each subdirectory must supply rules for building sources it contributes
src/Sensors/%.o: ../src/Sensors/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-linux-gnueabi-gcc -mcpu=arm9 -marm -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -IC:/ev3/API -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


