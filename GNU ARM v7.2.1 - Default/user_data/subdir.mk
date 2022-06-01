################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Dev/Repeater/20210311_siliconLabs_code/user_data/user_data.c 

OBJS += \
./user_data/user_data.o 

C_DEPS += \
./user_data/user_data.d 


# Each subdirectory must supply rules for building sources it contributes
user_data/user_data.o: C:/Dev/Repeater/20210311_siliconLabs_code/user_data/user_data.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=gnu99 '-DCORTEXM3=1' '-DCORTEXM3_EFM32_MICRO=1' '-DCORTEXM3_EFR32=1' '-DCORTEXM3_EFR32_MICRO=1' '-DNULL_BTL=1' '-DCONFIGURATION_HEADER="flex-configuration.h"' '-DPLATFORM_HEADER="platform/base/hal/micro/cortexm3/compiler/gcc.h"' '-DEFR32FG1P=1' '-DEFR32FG1P133F256GM48=1' '-DEFR32_SERIES1_CONFIG1_MICRO=1' '-DHAL_MICRO=1' '-DEMBER_SERIAL0_DEBUG=1' '-DEMBER_AF_API_EMBER_TYPES="stack/include/ember-types.h"' '-DEMBER_STACK_CONNECT=1' '-DHAL_CONFIG=1' '-DEMBER_AF_USE_HWCONF=1' '-DPHY_RAIL=1' -I"C:\Dev\Repeater\20210311_siliconLabs_code\hal-config" -I"C:\Dev\Repeater\20210311_siliconLabs_code\emdrv" -I"C:/SiliconLabs/SimplicityStudio/v4/GNU ARM v7.2.1 - Default/" -I"/platform/base/hal/plugin" -I"/platform/base/hal/micro/cortexm3/efm32/efr32" -I"/platform/emdrv/config" -I"/platform/emdrv/dmadrv/inc" -I"/platform/emdrv/rtcdrv/test" -I"/platform/emdrv/spidrv/inc" -I"/platform/emdrv/tempdrv/inc" -I"/platform/emdrv/uartdrv/inc" -I"/platform/middleware/glib" -I"/platform/middleware/glib/glib" -I"/platform/radio/rail_lib/plugin" -I"/platform/radio/rail_lib/chip/efr32/rf/rfprotocol/ieee802154/cortex" -I"../" -I"/platform/base/hal" -I"/platform/base/hal//plugin" -I"/platform/base/hal//micro/cortexm3/efm32" -I"/platform/base/hal//micro/cortexm3/efm32/config" -I"/platform/base/hal//micro/cortexm3/efm32/efr32" -I"/platform/base" -I"/platform/base//../CMSIS/Include" -I"/platform/base//../emdrv/common/inc" -I"/platform/base//../emdrv/config" -I"/platform/base//../emdrv/dmadrv/inc" -I"/platform/base//../emdrv/gpiointerrupt/inc" -I"/platform/base//../emdrv/rtcdrv/inc" -I"/platform/base//../emdrv/rtcdrv/test" -I"/platform/base//../emdrv/sleep/inc" -I"/platform/base//../emdrv/spidrv/inc" -I"/platform/base//../emdrv/tempdrv/inc" -I"/platform/base//../emdrv/uartdrv/inc" -I"/platform/base//../emdrv/ustimer/inc" -I"/platform/base//../emlib/inc" -I"/platform/base//../middleware/glib" -I"/platform/base//../middleware/glib/glib" -I"/platform/base//../radio/rail_lib/plugin" -I"/platform/base//../radio/rail_lib/chip/efr32/rf/common/cortex" -I"/platform/base//../radio/rail_lib/chip/efr32/rf/rfprotocol/ieee802154/cortex" -I"/platform/halconfig/inc/hal-config" -I"/hardware/kit/common/halconfig" -I"/hardware/kit/common/bsp" -IC:/Dev/Repeater/20210311_siliconLabs_code -IC:/Dev/Repeater/20210311_siliconLabs_code/hal-config -IC:/Dev/Repeater/20210311_siliconLabs_code/emdrv -I"/protocol" -I"/protocol/stack" -I"/protocol/flex/util" -I"/platform/Device/SiliconLabs-Restricted/EFR32FG1P/Include" -I"/platform/Device/SiliconLabs/EFR32FG1P/Include" -I"/hardware/kit/common" -I"/hardware/kit/common/drivers" -I"/platform/base/hal/.." -I"/platform/base/hal/micro" -I"/platform/base/hal/micro/cortexm3/common" -I"/platform/base/hal/micro/cortexm3/efm32" -I"/platform/base/hal/micro/cortexm3/efm32/board" -I"/platform/base/hal/micro/cortexm3/efm32/config" -I"/platform/CMSIS/Include" -I"/platform/emdrv/common/inc" -I"/platform/emdrv/gpiointerrupt/inc" -I"/platform/emdrv/rtcdrv/config" -I"/platform/emdrv/rtcdrv/inc" -I"/platform/emdrv/sleep/inc" -I"/platform/emdrv/ustimer/config" -I"/platform/emdrv/ustimer/inc" -I"/platform/emlib/inc" -I"/platform/radio/rail_lib/chip/efr32" -I"/platform/radio/rail_lib/chip/efr32/rf/common/cortex" -I"/platform/radio/rail_lib/common" -I"/platform/radio/rail_lib/hal" -I"/platform/radio/rail_lib/hal/efr32" -I"/platform/radio/rail_lib/plugin/pa-conversions" -I"/platform/radio/rail_lib/protocol/ble" -I"/platform/radio/rail_lib/protocol/ieee802154" -I"/protocol/flex/connect/plugins" -I"/protocol/flex/connect/plugins/stack" -I"/protocol/flex/connect/plugins/stack/include" -I"/util/silicon_labs/silabs_core/command_interpreter" -I"/util/silicon_labs/silabs_core/memory_manager" -I"/util/silicon_labs/silabs_core/queue" -I"/util/silicon_labs/silabs_core/response_print" -Os -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"user_data/user_data.d" -MT"user_data/user_data.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


