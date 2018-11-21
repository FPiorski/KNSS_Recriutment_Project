################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/Users/293426/workspace/rekrutacyjny/HAL_Driver/Inc/Legacy" -I"C:/Users/293426/workspace/rekrutacyjny/inc" -I"C:/Users/293426/workspace/rekrutacyjny/CMSIS/device" -I"C:/Users/293426/workspace/rekrutacyjny/CMSIS/core" -I"C:/Users/293426/workspace/rekrutacyjny/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


