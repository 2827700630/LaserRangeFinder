################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_adc.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_clk.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_flash.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_gpio.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_i2c.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_lcd.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_pwm.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_pwr.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_spi0.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_sys.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer0.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer1.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer2.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer3.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart0.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart1.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart2.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart3.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbdev.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbhostBase.c \
../LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbhostClass.c 

C_DEPS += \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_adc.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_clk.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_flash.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_gpio.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_i2c.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_lcd.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_pwm.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_pwr.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_spi0.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_sys.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer0.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer1.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer2.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer3.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart0.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart1.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart2.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart3.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbdev.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbhostBase.d \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbhostClass.d 

OBJS += \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_adc.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_clk.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_flash.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_gpio.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_i2c.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_lcd.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_pwm.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_pwr.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_spi0.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_sys.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer0.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer1.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer2.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_timer3.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart0.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart1.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart2.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_uart3.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbdev.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbhostBase.o \
./LaserRangeFinderch592F/StdPeriphDriver/CH59x_usbhostClass.o 

DIR_OBJS += \
./LaserRangeFinderch592F/StdPeriphDriver/*.o \

DIR_DEPS += \
./LaserRangeFinderch592F/StdPeriphDriver/*.d \

DIR_EXPANDS += \
./LaserRangeFinderch592F/StdPeriphDriver/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
LaserRangeFinderch592F/StdPeriphDriver/%.o: ../LaserRangeFinderch592F/StdPeriphDriver/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -DDEBUG=1 -I"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver/inc" -I"d:/CH573FEVT/LaserRangeFinder/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

