################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../tos/libtostest.o \
../tos/testtos.o 

C_SRCS += \
../tos/app.c \
../tos/libtos.c \
../tos/libtostest.c \
../tos/testtos.c 

OBJS += \
./tos/app.o \
./tos/libtos.o \
./tos/libtostest.o \
./tos/testtos.o 

C_DEPS += \
./tos/app.d \
./tos/libtos.d \
./tos/libtostest.d \
./tos/testtos.d 


# Each subdirectory must supply rules for building sources it contributes
tos/%.o: ../tos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


