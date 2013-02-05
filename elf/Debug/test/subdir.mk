################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../test/lb22.o \
../test/liba.o \
../test/libb.o \
../test/libd.o \
../test/libe.o \
../test/libefl.o \
../test/libf.o \
../test/libg.o \
../test/libh.o \
../test/libi.o \
../test/libj.o \
../test/libk.o \
../test/libl.o \
../test/libn.o \
../test/libo.o \
../test/libp.o \
../test/libq.o \
../test/test0.o \
../test/test0_1.o \
../test/test0_2.o \
../test/test1.o \
../test/test10.o \
../test/test11.o \
../test/test12.o \
../test/test13.o \
../test/test14.o \
../test/test15.o \
../test/test16.o \
../test/test17.o \
../test/test18.o \
../test/test19.o \
../test/test2.o \
../test/test20.o \
../test/test21.o \
../test/test22.o \
../test/test3.o \
../test/test4.o \
../test/test5.o \
../test/test6.o \
../test/test7.o \
../test/test8.o \
../test/test8_5.o \
../test/test9.o 

C_SRCS += \
../test/hello.c \
../test/lb22.c \
../test/liba.c \
../test/libb.c \
../test/libd.c \
../test/libe.c \
../test/libefl.c \
../test/libf.c \
../test/libg.c \
../test/libh.c \
../test/libi.c \
../test/libj.c \
../test/libk.c \
../test/libl.c \
../test/libn.c \
../test/libo.c \
../test/libp.c \
../test/libq.c \
../test/test0.c \
../test/test0_1.c \
../test/test0_2.c \
../test/test1.c \
../test/test10.c \
../test/test11.c \
../test/test12.c \
../test/test13.c \
../test/test14.c \
../test/test15.c \
../test/test17.c \
../test/test18.c \
../test/test19.c \
../test/test2.c \
../test/test20.c \
../test/test22.c \
../test/test3.c \
../test/test4.c \
../test/test5.c \
../test/test6.c \
../test/test7.c \
../test/test8.c \
../test/test8_5.c \
../test/test9.c 

CC_SRCS += \
../test/test16.cc \
../test/test21.cc 

OBJS += \
./test/hello.o \
./test/lb22.o \
./test/liba.o \
./test/libb.o \
./test/libd.o \
./test/libe.o \
./test/libefl.o \
./test/libf.o \
./test/libg.o \
./test/libh.o \
./test/libi.o \
./test/libj.o \
./test/libk.o \
./test/libl.o \
./test/libn.o \
./test/libo.o \
./test/libp.o \
./test/libq.o \
./test/test0.o \
./test/test0_1.o \
./test/test0_2.o \
./test/test1.o \
./test/test10.o \
./test/test11.o \
./test/test12.o \
./test/test13.o \
./test/test14.o \
./test/test15.o \
./test/test16.o \
./test/test17.o \
./test/test18.o \
./test/test19.o \
./test/test2.o \
./test/test20.o \
./test/test21.o \
./test/test22.o \
./test/test3.o \
./test/test4.o \
./test/test5.o \
./test/test6.o \
./test/test7.o \
./test/test8.o \
./test/test8_5.o \
./test/test9.o 

C_DEPS += \
./test/hello.d \
./test/lb22.d \
./test/liba.d \
./test/libb.d \
./test/libd.d \
./test/libe.d \
./test/libefl.d \
./test/libf.d \
./test/libg.d \
./test/libh.d \
./test/libi.d \
./test/libj.d \
./test/libk.d \
./test/libl.d \
./test/libn.d \
./test/libo.d \
./test/libp.d \
./test/libq.d \
./test/test0.d \
./test/test0_1.d \
./test/test0_2.d \
./test/test1.d \
./test/test10.d \
./test/test11.d \
./test/test12.d \
./test/test13.d \
./test/test14.d \
./test/test15.d \
./test/test17.d \
./test/test18.d \
./test/test19.d \
./test/test2.d \
./test/test20.d \
./test/test22.d \
./test/test3.d \
./test/test4.d \
./test/test5.d \
./test/test6.d \
./test/test7.d \
./test/test8.d \
./test/test8_5.d \
./test/test9.d 

CC_DEPS += \
./test/test16.d \
./test/test21.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

test/%.o: ../test/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


