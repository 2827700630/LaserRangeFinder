################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LaserRangeFinderch592F/RVMSIS/core_riscv.c 

C_DEPS += \
./LaserRangeFinderch592F/RVMSIS/core_riscv.d 

OBJS += \
./LaserRangeFinderch592F/RVMSIS/core_riscv.o 

DIR_OBJS += \
./LaserRangeFinderch592F/RVMSIS/*.o \

DIR_DEPS += \
./LaserRangeFinderch592F/RVMSIS/*.d \

DIR_EXPANDS += \
./LaserRangeFinderch592F/RVMSIS/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
LaserRangeFinderch592F/RVMSIS/%.o: ../LaserRangeFinderch592F/RVMSIS/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

