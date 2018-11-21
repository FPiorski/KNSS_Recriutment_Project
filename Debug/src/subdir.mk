################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/clocks.c \
../src/dma.c \
../src/errors.c \
../src/main.c \
../src/stm32f1xx_it.c \
../src/syscalls.c \
../src/system_stm32f1xx.c \
../src/uart.c 

OBJS += \
./src/adc.o \
./src/clocks.o \
./src/dma.o \
./src/errors.o \
./src/main.o \
./src/stm32f1xx_it.o \
./src/syscalls.o \
./src/system_stm32f1xx.o \
./src/uart.o 

C_DEPS += \
./src/adc.d \
./src/clocks.d \
./src/dma.d \
./src/errors.d \
./src/main.d \
./src/stm32f1xx_it.d \
./src/syscalls.d \
./src/system_stm32f1xx.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F103xB -DUSE_HAL_DRIVER -I"C:/Users/293426/workspace/rekrutacyjny/HAL_Driver/Inc/Legacy" -I"C:/Users/293426/workspace/rekrutacyjny/inc" -I"C:/Users/293426/workspace/rekrutacyjny/CMSIS/device" -I"C:/Users/293426/workspace/rekrutacyjny/CMSIS/core" -I"C:/Users/293426/workspace/rekrutacyjny/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


