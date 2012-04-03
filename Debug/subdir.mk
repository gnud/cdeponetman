################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cmdList.c \
../cmdMan.c \
../network.c \
../server.c 

OBJS += \
./cmdList.o \
./cmdMan.o \
./network.o \
./server.o 

C_DEPS += \
./cmdList.d \
./cmdMan.d \
./network.d \
./server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -pthread -lmxml -std=c99 -D_GNU_SOURCE -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


