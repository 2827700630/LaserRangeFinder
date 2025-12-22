################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../LaserRangeFinderch592F/Startup/startup_CH592.S 

S_UPPER_DEPS += \
./LaserRangeFinderch592F/Startup/startup_CH592.d 

OBJS += \
./LaserRangeFinderch592F/Startup/startup_CH592.o 

DIR_OBJS += \
./LaserRangeFinderch592F/Startup/*.o \

DIR_DEPS += \
./LaserRangeFinderch592F/Startup/*.d \

DIR_EXPANDS += \
./LaserRangeFinderch592F/Startup/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
LaserRangeFinderch592F/Startup/%.o: ../LaserRangeFinderch592F/Startup/%.S
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

