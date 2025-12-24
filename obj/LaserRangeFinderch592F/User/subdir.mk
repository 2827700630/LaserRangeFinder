################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LaserRangeFinderch592F/User/M01LaserRangeFinder.c \
../LaserRangeFinderch592F/User/Main.c 

C_DEPS += \
./LaserRangeFinderch592F/User/M01LaserRangeFinder.d \
./LaserRangeFinderch592F/User/Main.d 

OBJS += \
./LaserRangeFinderch592F/User/M01LaserRangeFinder.o \
./LaserRangeFinderch592F/User/Main.o 

DIR_OBJS += \
./LaserRangeFinderch592F/User/*.o \

DIR_DEPS += \
./LaserRangeFinderch592F/User/*.d \

DIR_EXPANDS += \
./LaserRangeFinderch592F/User/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
LaserRangeFinderch592F/User/%.o: ../LaserRangeFinderch592F/User/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

