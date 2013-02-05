################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../alloc.o \
../avprintf-cb.o \
../display-relocs.o \
../dprintf.o \
../elfedit.o \
../futex.o \
../gdb.o \
../glibc.o \
../internal-test-alloc.o \
../internal-test-futex.o \
../internal-test-list.o \
../internal-tests.o \
../interp.o \
../libvdl.o \
../readversiondef.o \
../stage1.o \
../stage2.o \
../system.o \
../valgrind.o \
../vdl-alloc.o \
../vdl-context.o \
../vdl-dl-public.o \
../vdl-dl.o \
../vdl-fini.o \
../vdl-gc.o \
../vdl-init.o \
../vdl-linkmap.o \
../vdl-list.o \
../vdl-log.o \
../vdl-lookup.o \
../vdl-map.o \
../vdl-mem.o \
../vdl-reloc.o \
../vdl-sort.o \
../vdl-tls.o \
../vdl-unmap.o \
../vdl-utils.o \
../vdl.o 

C_SRCS += \
../alloc.c \
../avprintf-cb.c \
../display-relocs.c \
../dprintf.c \
../elfedit.c \
../futex.c \
../gdb.c \
../glibc.c \
../interp.c \
../libvdl.c \
../readversiondef.c \
../stage1.c \
../stage2.c \
../system.c \
../valgrind.c \
../vdl-alloc.c \
../vdl-context.c \
../vdl-dl-public.c \
../vdl-dl.c \
../vdl-fini.c \
../vdl-gc.c \
../vdl-init.c \
../vdl-linkmap.c \
../vdl-list.c \
../vdl-log.c \
../vdl-lookup.c \
../vdl-map.c \
../vdl-mem.c \
../vdl-reloc.c \
../vdl-sort.c \
../vdl-tls.c \
../vdl-unmap.c \
../vdl-utils.c \
../vdl.c 

CC_SRCS += \
../internal-test-alloc.cc \
../internal-test-futex.cc \
../internal-test-list.cc \
../internal-tests.cc 

OBJS += \
./alloc.o \
./avprintf-cb.o \
./display-relocs.o \
./dprintf.o \
./elfedit.o \
./futex.o \
./gdb.o \
./glibc.o \
./internal-test-alloc.o \
./internal-test-futex.o \
./internal-test-list.o \
./internal-tests.o \
./interp.o \
./libvdl.o \
./readversiondef.o \
./stage1.o \
./stage2.o \
./system.o \
./valgrind.o \
./vdl-alloc.o \
./vdl-context.o \
./vdl-dl-public.o \
./vdl-dl.o \
./vdl-fini.o \
./vdl-gc.o \
./vdl-init.o \
./vdl-linkmap.o \
./vdl-list.o \
./vdl-log.o \
./vdl-lookup.o \
./vdl-map.o \
./vdl-mem.o \
./vdl-reloc.o \
./vdl-sort.o \
./vdl-tls.o \
./vdl-unmap.o \
./vdl-utils.o \
./vdl.o 

C_DEPS += \
./alloc.d \
./avprintf-cb.d \
./display-relocs.d \
./dprintf.d \
./elfedit.d \
./futex.d \
./gdb.d \
./glibc.d \
./interp.d \
./libvdl.d \
./readversiondef.d \
./stage1.d \
./stage2.d \
./system.d \
./valgrind.d \
./vdl-alloc.d \
./vdl-context.d \
./vdl-dl-public.d \
./vdl-dl.d \
./vdl-fini.d \
./vdl-gc.d \
./vdl-init.d \
./vdl-linkmap.d \
./vdl-list.d \
./vdl-log.d \
./vdl-lookup.d \
./vdl-map.d \
./vdl-mem.d \
./vdl-reloc.d \
./vdl-sort.d \
./vdl-tls.d \
./vdl-unmap.d \
./vdl-utils.d \
./vdl.d 

CC_DEPS += \
./internal-test-alloc.d \
./internal-test-futex.d \
./internal-test-list.d \
./internal-tests.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


