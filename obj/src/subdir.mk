################################################################################
# MRS Version: 2.2.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Main.c 

C_DEPS += \
./src/Main.d 

OBJS += \
./src/Main.o 


EXPANDS += \
./src/Main.c.234r.expand 



# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

