################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/M01LaserRangeFinder.c \
../User/Main.c 

C_DEPS += \
./User/M01LaserRangeFinder.d \
./User/Main.d 

OBJS += \
./User/M01LaserRangeFinder.o \
./User/Main.o 

DIR_OBJS += \
./User/*.o \

DIR_DEPS += \
./User/*.d \

DIR_EXPANDS += \
./User/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/LaserRangeFinderch592F/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/LaserRangeFinderch592F/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

