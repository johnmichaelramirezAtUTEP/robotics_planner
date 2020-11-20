################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Control/control_setup.c \
../src/Control/goalfinding.c \
../src/Control/lego_control.c \
../src/Control/wander.c 

OBJS += \
./src/Control/control_setup.o \
./src/Control/goalfinding.o \
./src/Control/lego_control.o \
./src/Control/wander.o 

C_DEPS += \
./src/Control/control_setup.d \
./src/Control/goalfinding.d \
./src/Control/lego_control.d \
./src/Control/wander.d 


# Each subdirectory must supply rules for building sources it contributes
src/Control/%.o: ../src/Control/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-linux-gnueabi-gcc -mcpu=arm9 -marm -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -IC:/ev3/API -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


