################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HeapFileManagement/DBMainHeaderPage.cpp \
../HeapFileManagement/DataPage.cpp \
../HeapFileManagement/DirectoryEntry.cpp \
../HeapFileManagement/DirectoryHeaderPage.cpp \
../HeapFileManagement/DirectoryPage.cpp \
../HeapFileManagement/FreePageManager.cpp 

OBJS += \
./HeapFileManagement/DBMainHeaderPage.o \
./HeapFileManagement/DataPage.o \
./HeapFileManagement/DirectoryEntry.o \
./HeapFileManagement/DirectoryHeaderPage.o \
./HeapFileManagement/DirectoryPage.o \
./HeapFileManagement/FreePageManager.o 

CPP_DEPS += \
./HeapFileManagement/DBMainHeaderPage.d \
./HeapFileManagement/DataPage.d \
./HeapFileManagement/DirectoryEntry.d \
./HeapFileManagement/DirectoryHeaderPage.d \
./HeapFileManagement/DirectoryPage.d \
./HeapFileManagement/FreePageManager.d 


# Each subdirectory must supply rules for building sources it contributes
HeapFileManagement/%.o: ../HeapFileManagement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


