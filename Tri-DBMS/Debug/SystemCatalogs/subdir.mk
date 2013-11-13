################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SystemCatalogs/IndexCatalog.cpp \
../SystemCatalogs/SysColumnsCatalog.cpp \
../SystemCatalogs/SysTablesCatalog.cpp 

OBJS += \
./SystemCatalogs/IndexCatalog.o \
./SystemCatalogs/SysColumnsCatalog.o \
./SystemCatalogs/SysTablesCatalog.o 

CPP_DEPS += \
./SystemCatalogs/IndexCatalog.d \
./SystemCatalogs/SysColumnsCatalog.d \
./SystemCatalogs/SysTablesCatalog.d 


# Each subdirectory must supply rules for building sources it contributes
SystemCatalogs/%.o: ../SystemCatalogs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


