################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LaserRangeFinderch592F/User/TFTc/TFT_CAD.c \
../LaserRangeFinderch592F/User/TFTc/TFT_init.c \
../LaserRangeFinderch592F/User/TFTc/TFT_io.c \
../LaserRangeFinderch592F/User/TFTc/TFT_text.c \
../LaserRangeFinderch592F/User/TFTc/font.c 

C_DEPS += \
./LaserRangeFinderch592F/User/TFTc/TFT_CAD.d \
./LaserRangeFinderch592F/User/TFTc/TFT_init.d \
./LaserRangeFinderch592F/User/TFTc/TFT_io.d \
./LaserRangeFinderch592F/User/TFTc/TFT_text.d \
./LaserRangeFinderch592F/User/TFTc/font.d 

OBJS += \
./LaserRangeFinderch592F/User/TFTc/TFT_CAD.o \
./LaserRangeFinderch592F/User/TFTc/TFT_init.o \
./LaserRangeFinderch592F/User/TFTc/TFT_io.o \
./LaserRangeFinderch592F/User/TFTc/TFT_text.o \
./LaserRangeFinderch592F/User/TFTc/font.o 

DIR_OBJS += \
./LaserRangeFinderch592F/User/TFTc/*.o \

DIR_DEPS += \
./LaserRangeFinderch592F/User/TFTc/*.d \

DIR_EXPANDS += \
./LaserRangeFinderch592F/User/TFTc/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
LaserRangeFinderch592F/User/TFTc/%.o: ../LaserRangeFinderch592F/User/TFTc/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

