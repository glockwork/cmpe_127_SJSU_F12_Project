################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../L5_Application/source/handlers.cpp \
../L5_Application/source/highLevelInitialize.cpp \
../L5_Application/source/tasks.cpp \
../L5_Application/source/utilities.cpp 

OBJS += \
./L5_Application/source/handlers.o \
./L5_Application/source/highLevelInitialize.o \
./L5_Application/source/tasks.o \
./L5_Application/source/utilities.o 

CPP_DEPS += \
./L5_Application/source/handlers.d \
./L5_Application/source/highLevelInitialize.d \
./L5_Application/source/tasks.d \
./L5_Application/source/utilities.d 


# Each subdirectory must supply rules for building sources it contributes
L5_Application/source/%.o: ../L5_Application/source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Yagarto Windows GCC C++ Compiler'
	arm-none-eabi-g++ -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L0_LowLevel" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L1_FreeRTOS\include" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L1_FreeRTOS\portable" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L2_Drivers" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L3_Utils" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L4_IO" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L4_IO\fat" -I"C:\Users\Trent Smith\Desktop\SJSU_Dev\projects\lpc17xx_CPP_HelloWorld\L5_Application" -Os -Wall -Wa,-adhlns="$@.lst" -fno-exceptions -fno-rtti -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


