################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../i386/machine.c 

S_UPPER_SRCS += \
../i386/resolv.S \
../i386/stage0.S 

OBJS += \
./i386/machine.o \
./i386/resolv.o \
./i386/stage0.o 

C_DEPS += \
./i386/machine.d 


# Each subdirectory must supply rules for building sources it contributes
i386/%.o: ../i386/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

i386/%.o: ../i386/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


