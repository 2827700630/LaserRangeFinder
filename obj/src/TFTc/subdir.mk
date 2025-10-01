################################################################################
# MRS Version: 2.2.0
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


EXPANDS += \
./src/TFTc/TFT_CAD.c.234r.expand \
./src/TFTc/TFT_init.c.234r.expand \
./src/TFTc/TFT_io.c.234r.expand \
./src/TFTc/TFT_text.c.234r.expand \
./src/TFTc/font.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
src/TFTc/%.o: ../src/TFTc/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

