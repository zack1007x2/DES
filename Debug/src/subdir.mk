################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DES.cpp \
../src/EventList.cpp \
../src/week10.cpp \
../src/week11.cpp \
../src/week12.cpp \
../src/week13.cpp \
../src/week14.cpp \
../src/week4.cpp \
../src/week5.cpp \
../src/week6.cpp \
../src/week7.cpp \
../src/week8.cpp \
../src/week9.cpp 

OBJS += \
./src/DES.o \
./src/EventList.o \
./src/week10.o \
./src/week11.o \
./src/week12.o \
./src/week13.o \
./src/week14.o \
./src/week4.o \
./src/week5.o \
./src/week6.o \
./src/week7.o \
./src/week8.o \
./src/week9.o 

CPP_DEPS += \
./src/DES.d \
./src/EventList.d \
./src/week10.d \
./src/week11.d \
./src/week12.d \
./src/week13.d \
./src/week14.d \
./src/week4.d \
./src/week5.d \
./src/week6.d \
./src/week7.d \
./src/week8.d \
./src/week9.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


