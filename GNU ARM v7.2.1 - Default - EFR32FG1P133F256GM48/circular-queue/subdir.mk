################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/queue/circular_queue.c 

OBJS += \
./circular-queue/circular_queue.o 

C_DEPS += \
./circular-queue/circular_queue.d 


# Each subdirectory must supply rules for building sources it contributes
circular-queue/circular_queue.o: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/queue/circular_queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=gnu99 '-DNULL_BTL=1' '-DCONFIGURATION_HEADER="flex-configuration.h"' '-DPLATFORM_HEADER="platform/base/hal/micro/cortexm3/compiler/gcc.h"' '-DEFR32FG1P=1' '-DEFR32FG1P133F256GM48=1' '-DEFR32_SERIES1_CONFIG1_MICRO=1' '-DHAL_MICRO=1' '-DEMBER_SERIAL0_DEBUG=1' '-DEMBER_AF_API_EMBER_TYPES="stack/include/ember-types.h"' '-DEMBER_STACK_CONNECT=1' '-DHAL_CONFIG=1' '-DEMBER_AF_USE_HWCONF=1' '-DPHY_RAIL=1' '-DCORTEXM3=1' '-DCORTEXM3_EFM32_MICRO=1' '-DCORTEXM3_EFR32=1' '-DCORTEXM3_EFR32_MICRO=1' -I"C:\Dev\Repeater\20210311_siliconLabs_code" -I"C:\Dev\Repeater\20210311_siliconLabs_code\hal-config" -I"C:\Dev\Repeater\20210311_siliconLabs_code\emdrv" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//protocol" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//protocol/stack" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//protocol/flex/util" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/Device/SiliconLabs-Restricted/EFR32FG1P/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/Device/SiliconLabs/EFR32FG1P/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//hardware/kit/common" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//hardware/kit/common/halconfig" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/.." -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/micro" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/micro/cortexm3/common" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/micro/cortexm3/efm32" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/micro/cortexm3/efm32/board" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal/micro/cortexm3/efm32/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emdrv/gpiointerrupt/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emdrv/rtcdrv/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emdrv/rtcdrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emdrv/ustimer/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emdrv/ustimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/halconfig/inc/hal-config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/chip/efr32" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/chip/efr32/rf/common/cortex" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/common" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/hal" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/hal/efr32" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/plugin/pa-conversions" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/protocol/ble" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/radio/rail_lib/protocol/ieee802154" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//protocol/flex/connect/plugins" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//protocol/flex/connect/plugins/stack" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//protocol/flex/connect/plugins/stack/include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//util/silicon_labs/silabs_core/command_interpreter" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//util/silicon_labs/silabs_core/memory_manager" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//util/silicon_labs/silabs_core/queue" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//util/silicon_labs/silabs_core/response_print" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal//plugin" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal//micro/cortexm3/efm32" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal//micro/cortexm3/efm32/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base/hal//micro/cortexm3/efm32/efr32" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/dmadrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/gpiointerrupt/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/rtcdrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/rtcdrv/test" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/sleep/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/spidrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/tempdrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/uartdrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emdrv/ustimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../middleware/glib" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../middleware/glib/glib" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../radio/rail_lib/plugin" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../radio/rail_lib/chip/efr32/rf/common/cortex" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3//platform/base//../radio/rail_lib/chip/efr32/rf/rfprotocol/ieee802154/cortex" -Os -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"circular-queue/circular_queue.d" -MT"circular-queue/circular_queue.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


