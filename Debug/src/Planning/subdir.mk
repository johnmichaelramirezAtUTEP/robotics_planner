################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Planning/parameters.c \
../src/Planning/planning.c 

OBJS += \
./src/Planning/parameters.o \
./src/Planning/planning.o 

C_DEPS += \
./src/Planning/parameters.d \
./src/Planning/planning.d 


# Each subdirectory must supply rules for building sources it contributes
src/Planning/%.o: ../src/Planning/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-linux-gnueabi-gcc -mcpu=arm9 -marm -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -IC:/ev3/API -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


