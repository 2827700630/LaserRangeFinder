################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/TFTc/subdir.mk
-include src/subdir.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
LaserRangeFinder.hex \

SECONDARY_LIST += \
LaserRangeFinder.lst \

SECONDARY_SIZE += \
LaserRangeFinder.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: LaserRangeFinder.elf secondary-outputs

# Tool invocations
LaserRangeFinder.elf: $(OBJS) $(USER_OBJS_ESCAPE)
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -g -T "d:/CH573FEVT/LaserRangeFinder/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -L"d:/CH573FEVT/LaserRangeFinder/StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"LaserRangeFinder.map" --specs=nano.specs --specs=nosys.specs -o "LaserRangeFinder.elf" $(OBJS) $(LIBS)
LaserRangeFinder.hex: LaserRangeFinder.elf
	@	riscv-none-embed-objcopy -O ihex "LaserRangeFinder.elf" "LaserRangeFinder.hex"
LaserRangeFinder.lst: LaserRangeFinder.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "LaserRangeFinder.elf" > "LaserRangeFinder.lst"
LaserRangeFinder.siz: LaserRangeFinder.elf
	riscv-none-embed-size --format=berkeley "LaserRangeFinder.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) LaserRangeFinder.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets