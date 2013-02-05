################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../x86_64/machine.o \
../x86_64/resolv.o \
../x86_64/stage0.o 

C_SRCS += \
../x86_64/machine.c 

S_UPPER_SRCS += \
../x86_64/resolv.S \
../x86_64/stage0.S 

OBJS += \
./x86_64/machine.o \
./x86_64/resolv.o \
./x86_64/stage0.o 

C_DEPS += \
./x86_64/machine.d 


# Each subdirectory must supply rules for building sources it contributes
x86_64/%.o: ../x86_64/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

x86_64/%.o: ../x86_64/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


