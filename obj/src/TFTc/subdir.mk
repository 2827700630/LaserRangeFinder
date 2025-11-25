################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TFTc/TFT_CAD.c \
../src/TFTc/TFT_init.c \
../src/TFTc/TFT_io.c \
../src/TFTc/TFT_text.c \
../src/TFTc/font.c 

C_DEPS += \
./src/TFTc/TFT_CAD.d \
./src/TFTc/TFT_init.d \
./src/TFTc/TFT_io.d \
./src/TFTc/TFT_text.d \
./src/TFTc/font.d 

OBJS += \
./src/TFTc/TFT_CAD.o \
./src/TFTc/TFT_init.o \
./src/TFTc/TFT_io.o \
./src/TFTc/TFT_text.o \
./src/TFTc/font.o 

DIR_OBJS += \
./src/TFTc/*.o \

DIR_DEPS += \
./src/TFTc/*.d \

DIR_EXPANDS += \
./src/TFTc/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
src/TFTc/%.o: ../src/TFTc/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

