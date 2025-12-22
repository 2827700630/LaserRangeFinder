################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/TFTc/TFT_CAD.c \
../User/TFTc/TFT_init.c \
../User/TFTc/TFT_io.c \
../User/TFTc/TFT_text.c \
../User/TFTc/font.c 

C_DEPS += \
./User/TFTc/TFT_CAD.d \
./User/TFTc/TFT_init.d \
./User/TFTc/TFT_io.d \
./User/TFTc/TFT_text.d \
./User/TFTc/font.d 

OBJS += \
./User/TFTc/TFT_CAD.o \
./User/TFTc/TFT_init.o \
./User/TFTc/TFT_io.o \
./User/TFTc/TFT_text.o \
./User/TFTc/font.o 

DIR_OBJS += \
./User/TFTc/*.o \

DIR_DEPS += \
./User/TFTc/*.d \

DIR_EXPANDS += \
./User/TFTc/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/TFTc/%.o: ../User/TFTc/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/LaserRangeFinderch592F/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/LaserRangeFinderch592F/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

