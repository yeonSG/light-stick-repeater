################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include yes/subdir.mk
-include user_data/subdir.mk
-include response-printf/subdir.mk
-include rail-app-config/EFR32_F_1_1_P/gcc/subdir.mk
-include pa-conversions/subdir.mk
-include hal-efr32/subdir.mk
-include emlib/subdir.mk
-include emdrv/subdir.mk
-include command-interpreter-rail/subdir.mk
-include circular-queue/subdir.mk
-include buffer-pool-memory-manager/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: 20210311_siliconLabs_code.axf

# Tool invocations
20210311_siliconLabs_code.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/../../Device/SiliconLabs/EFR32FG1P/Source/GCC/efr32fg1p.ld" -L"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/micro/cortexm3/" -Xlinker --defsym=FLASH_SIZE=262144 -Xlinker --defsym=RAM_SIZE=32768 -Xlinker --defsym=SIMEEPROM_SIZE=0 -Xlinker --defsym=NULL_BTL=1 -Xlinker --gc-sections -Xlinker -Map="20210311_siliconLabs_code.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o 20210311_siliconLabs_code.axf -Wl,--start-group "./app_hal.o" "./app_main.o" "./rail_config.o" "./buffer-pool-memory-manager/buffer_pool_allocator.o" "./circular-queue/circular_queue.o" "./command-interpreter-rail/command_interpreter.o" "./emdrv/dmadrv.o" "./emdrv/gpiointerrupt.o" "./emdrv/rtcdriver.o" "./emdrv/sleep.o" "./emdrv/tempdrv.o" "./emdrv/uartdrv.o" "./emdrv/ustimer.o" "./emlib/em_adc.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_ldma.o" "./emlib/em_leuart.o" "./emlib/em_mpu.o" "./emlib/em_msc.o" "./emlib/em_prs.o" "./emlib/em_rmu.o" "./emlib/em_rtcc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_wdog.o" "./emlib/system_efr32fg1p.o" "./hal-efr32/bsp_init.o" "./hal-efr32/bsp_stk.o" "./hal-efr32/bsp_stk_leds.o" "./hal-efr32/dmactrl.o" "./hal-efr32/em_assert.o" "./hal-efr32/em_rtc.o" "./hal-efr32/hal_common.o" "./hal-efr32/hal_efr.o" "./hal-efr32/i2cspm.o" "./hal-efr32/retargetio.o" "./hal-efr32/retargetserial.o" "./hal-efr32/udelay.o" "./pa-conversions/pa_conversions_efr32.o" "./rail-app-config/EFR32_F_1_1_P/gcc/startup_efr32fg1p.o" "./response-printf/response_print.o" "./user_data/user_data.o" "./yes/my_uart.o" "./yes/parameter_ci.o" "./yes/yes_radio.o" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/autogen/librail_release/librail_efr32xg1_gcc_release.a" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: 20210311_siliconLabs_code.hex'
	arm-none-eabi-objcopy -O ihex "20210311_siliconLabs_code.axf" "20210311_siliconLabs_code.hex"
	@echo ' '

	@echo 'Building bin file: 20210311_siliconLabs_code.bin'
	arm-none-eabi-objcopy -O binary "20210311_siliconLabs_code.axf" "20210311_siliconLabs_code.bin"
	@echo ' '

	@echo 'Building s37 file: 20210311_siliconLabs_code.s37'
	arm-none-eabi-objcopy -O srec "20210311_siliconLabs_code.axf" "20210311_siliconLabs_code.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "20210311_siliconLabs_code.axf" -A
	@echo ' '

	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) 20210311_siliconLabs_code.axf
	-@echo ' '

pre-build:
	-cmd //c 'C:\Dev\Repeater\202103~1/yes_infra_dual-prebuild.bat' '20210311_siliconLabs_code' 'C:/Dev/Repeater/20210311_siliconLabs_code' '' 'C:\SiliconLabs\SimplicityStudio\v4'
	-@echo ' '

post-build:
	-cmd //c 'C:\Dev\Repeater\202103~1/yes_infra_dual-postbuild.bat' '20210311_siliconLabs_code' 'C:/Dev/Repeater/20210311_siliconLabs_code' '' 'C:\SiliconLabs\SimplicityStudio\v4'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
