################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../BufferManagement/BufferManager.cpp \
../BufferManagement/Frame.cpp \
../BufferManagement/LRUPageReplacement.cpp 

OBJS += \
./BufferManagement/BufferManager.o \
./BufferManagement/Frame.o \
./BufferManagement/LRUPageReplacement.o 

CPP_DEPS += \
./BufferManagement/BufferManager.d \
./BufferManagement/Frame.d \
./BufferManagement/LRUPageReplacement.d 


# Each subdirectory must supply rules for building sources it contributes
BufferManagement/%.o: ../BufferManagement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


