# Architecture directories
ARCHITECTURE_DIR = efr32
BUILD_DIR = build
OUTPUT_DIR = $(BUILD_DIR)/$(ARCHITECTURE_DIR)
LST_DIR = lst
PROJECTNAME = yes_infra_dual

# Stack and submodule directories
GLOBAL_BASE_DIR     = ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/..

SOURCE_FILES = \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/dmadrv/src/dmadrv.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/gpiointerrupt/src/gpiointerrupt.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/rtcdrv/src/rtcdriver.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/sleep/src/sleep.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/tempdrv/src/tempdrv.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/ustimer/src/ustimer.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_adc.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_cmu.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_core.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_emu.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_gpio.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_i2c.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_ldma.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_leuart.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_mpu.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_msc.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_prs.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_rmu.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_rtcc.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_system.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_timer.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_usart.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/src/em_wdog.c \
../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../Device/SiliconLabs/EFR32FG1P/Source/system_efr32fg1p.c \
  emdrv/uartdrv.c \
  main.c \
  rail_config.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/bsp/bsp_init.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/bsp/bsp_stk.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/bsp/bsp_stk_leds.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/drivers/dmactrl.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/drivers/i2cspm.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/drivers/retargetio.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/drivers/retargetserial.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/drivers/udelay.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/Device/SiliconLabs/EFR32FG1P/Source/GCC/startup_efr32fg1p.S \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emlib/src/em_assert.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emlib/src/em_rtc.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/hal/efr32/hal_efr.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/hal/hal_common.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/command_interpreter/command_interpreter.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/memory_manager/buffer_pool_allocator.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/queue/circular_queue.c \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/response_print/response_print.c \


LIB_FILES = \
  ../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/autogen/librail_release/librail_efr32xg1_gcc_release.a \


CDEFS = -DNULL_BTL \
-DEFR32FG1P133F256GM48 \
-DEFR32FG1P \
-DCORTEXM3 \
-DCORTEXM3_EFR32 \
-DCORTEXM3_EFR32_MICRO \
-DCORTEXM3_EFM32_MICRO \
-DEFR32_SERIES1_CONFIG1_MICRO \
-DCONFIGURATION_HEADER=\"flex-configuration.h\" \
-DPLATFORM_HEADER=\"../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/compiler/gcc.h\" \
  -DHAL_MICRO \
  -DEMBER_SERIAL0_DEBUG \
  -DEMBER_AF_API_EMBER_TYPES=\"stack/include/ember-types.h\" \
  -DEMBER_STACK_CONNECT \
  -DHAL_CONFIG=1 \
  -DEMBER_AF_USE_HWCONF \
  -DPHY_RAIL=1 \


ASMDEFS = -DNULL_BTL \
-DEFR32FG1P133F256GM48 \
-DEFR32FG1P \
-DCORTEXM3 \
-DCORTEXM3_EFR32 \
-DCORTEXM3_EFR32_MICRO \
-DCORTEXM3_EFM32_MICRO \
-DEFR32_SERIES1_CONFIG1_MICRO \
-DCONFIGURATION_HEADER=\"flex-configuration.h\" \
-DPLATFORM_HEADER=\"../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/compiler/gcc.h\" \
  -DHAL_MICRO \
  -DEMBER_SERIAL0_DEBUG \
  -DEMBER_AF_API_EMBER_TYPES=\"stack/include/ember-types.h\" \
  -DEMBER_STACK_CONNECT \
  -DHAL_CONFIG=1 \
  -DEMBER_AF_USE_HWCONF \
  -DPHY_RAIL=1 \


CINC = -I./ \
-I$(ARM_IAR7_DIR)/ARM/INC \
-I..\..\..\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v2.3 \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/protocol/flex/connect \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/protocol/flex/connect/../.. \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/protocol/flex/connect/../../stack \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/protocol/flex/connect/../util \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/plugin \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/.. \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/efm32 \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/efm32/config \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/efm32/efr32 \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../CMSIS/Include \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../Device/SiliconLabs-Restricted/efr32fg1p/Include \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../Device/SiliconLabs/efr32fg1p/Include \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/common/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/config \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/dmadrv/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/gpiointerrupt/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/rtcdrv/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/sleep/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/spidrv/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/tempdrv/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/uartdrv/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emdrv/ustimer/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../emlib/inc \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../middleware/glib \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../middleware/glib/glib \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../radio/rail_lib/plugin \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../radio/rail_lib/chip/efr32/rf/common/cortex \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../radio/rail_lib/chip/efr32/rf/rfprotocol/ieee802154/cortex \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/../../halconfig/inc/hal-config \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3 \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/halconfig/inc/hal-config \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/halconfig \
-I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/bsp \
  -Ihal-config \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/bsp \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/drivers \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/hardware/kit/common/halconfig \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/common \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/efm32 \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/efm32/board \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/base/hal/micro/cortexm3/efm32/config \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/CMSIS/Include \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emdrv/common/inc \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emdrv/gpiointerrupt/inc \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emdrv/rtcdrv/config \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emdrv/rtcdrv/inc \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emdrv/sleep/inc \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emdrv/ustimer/config \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emdrv/ustimer/inc \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/emlib/inc \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/halconfig/inc/hal-config \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/chip/efr32 \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/chip/efr32/rf/common/cortex \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/common \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/hal \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/hal/efr32 \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/plugin/pa-conversions \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/protocol/ble \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/platform/radio/rail_lib/protocol/ieee802154 \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/protocol/flex/connect/plugins \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/protocol/flex/connect/plugins/stack \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/protocol/flex/connect/plugins/stack/include \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/command_interpreter \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/memory_manager \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/queue \
  -I../../../SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.3/util/silicon_labs/silabs_core/response_print \


TARGET = yes_infra_dual

CSOURCES = $(filter %.c, $(SOURCE_FILES))
ASMSOURCES = $(filter %.s79, $(SOURCE_FILES))
ASMSOURCES2 = $(filter %.s, $(SOURCE_FILES))
ASMSOURCES3 = $(filter %.S, $(SOURCE_FILES))

COBJS = $(addprefix $(OUTPUT_DIR)/,$(CSOURCES:.c=.o))
ASMOBJS = $(addprefix $(OUTPUT_DIR)/,$(ASMSOURCES:.s79=.o))
ASMOBJS2 = $(addprefix $(OUTPUT_DIR)/,$(ASMSOURCES2:.s=.o))
ASMOBJS3 = $(addprefix $(OUTPUT_DIR)/,$(ASMSOURCES3:.S=.o))

OUTPUT_DIRS = $(sort $(dir $(COBJS)) $(dir $(ASMOBJS)) $(dir $(ASMOBJS2)) $(dir $(ASMOBJS3)))

ARCHITECTUREID = efr32~family[f]~series[1]~device_configuration[1]~performance[p]~radio[133]~flash[256k]~temp[g]~package[m]~pins[48]~!module+none+gcc

# GNU ARM compiler
ifeq ($(findstring +gcc,$(ARCHITECTUREID)), +gcc)
$(info GCC Build)
	# Add linker circular reference as the order of objects may matter for any libraries used
	GROUP_START =-Wl,--start-group
	GROUP_END =-Wl,--end-group        

	CCFLAGS = -g3 \
    -gdwarf-2 \
    -mcpu=cortex-m4 \
    -mthumb \
    -std=gnu99 \
    -Os  \
    -Wall  \
    -c  \
    -fmessage-length=0  \
    -ffunction-sections  \
    -fdata-sections  \
    -mfpu=fpv4-sp-d16  \
    -mfloat-abi=softfp \
	$(CDEFS) \
	$(CINC) \

	ASMFLAGS = -c \
	-g3 \
	-gdwarf-2 \
	-mcpu=cortex-m4 \
	-mthumb \
	-c \
	-x assembler-with-cpp \
	$(CINC) \
	$(ASMDEFS)

	LDFLAGS = -g3 \
	-gdwarf-2 \
	-mcpu=cortex-m4 \
	-mthumb -T "C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v2.3\platform\base\hal/../../Device/SiliconLabs/EFR32FG1P/Source/GCC/efr32fg1p.ld" \
	-L"$(GLOBAL_BASE_DIR)/hal/micro/cortexm3/" \
	-Xlinker --defsym="SIMEEPROM_SIZE=0" \
	-Xlinker --defsym="FLASH_SIZE=262144" \
	-Xlinker --defsym="RAM_SIZE=32768" \
	-Xlinker --defsym="NULL_BTL=1" \
	-Xlinker --gc-sections \
	-Xlinker -Map="$(PROJECTNAME).map" \
	-mfpu=fpv4-sp-d16 \
	-mfloat-abi=softfp --specs=nano.specs -u _printf_float \
	-Wl,--start-group -lgcc -lc    -Wl,--end-group

	ARCHFLAGS = r

	ELFTOOLFLAGS_BIN = -O binary
	ELFTOOLFLAGS_HEX = -O ihex
	ELFTOOLFLAGS_S37 = -O srec

	ifeq ($(OS),Windows_NT)
		ARCH = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc-ar.exe
		AS = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc.exe
		CC = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc.exe
		ELFTOOL = $(ARM_GNU_DIR)/bin/arm-none-eabi-objcopy.exe
		LD = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc.exe
	else
		ARCH = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc-ar
		AS = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc
		CC = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc
		ELFTOOL = $(ARM_GNU_DIR)/bin/arm-none-eabi-objcopy
		LD = $(ARM_GNU_DIR)/bin/arm-none-eabi-gcc
	endif

endif

# IAR 7.xx toolchain
ifeq ($(findstring +iar,$(ARCHITECTUREID)), +iar)
$(info IAR Build)

	# IAR is not sensitive to linker lib order thus no groups needed.
	GROUP_START =
	GROUP_END =
	CINC += -I$(ARM_IAR6_DIR)/ARM/INC

	ifndef ARM_IAR7_DIR
	$(error ARM_IAR7_DIR is not set. Please define ARM_IAR7_DIR pointing to your IAR 7.xx installation folder.)
	endif

	CCFLAGS = --cpu=cortex-m3 \
	--cpu_mode=thumb \
	--diag_suppress=Pa050 \
	-e \
	--endian=little \
	--fpu=none \
	--no_path_in_file_macros \
	--separate_cluster_for_initialized_variables \
	--dlib_config=$(ARM_IAR7_DIR)/ARM/inc/c/DLib_Config_Normal.h \
	--debug \
	--dependencies=m $*.d \
	-Ohz \
	$(CDEFS) \
	$(CINC)

	ASMFLAGS = --cpu cortex-M3 \
	--fpu None \
	-s+ \
	"-M<>" \
	-w+ \
	-t2 \
	-r \
	$(CINC) \
	$(ASMDEFS)

	LDFLAGS = --entry __iar_program_start \
	--diag_suppress=Lp012 \
	--config ${TOOLKIT_DIR}\config\linker\SiliconLaboratories\EFR32FG1P133F256GM48.icf \
	--config_def NULL_BTL=1

	ARCH = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/iarchive.exe
	AS = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/iasmarm.exe
	CC = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/iccarm.exe
	ELFTOOL = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/ielftool.exe
	LD = $(JAMEXE_PREFIX) $(ARM_IAR7_DIR)/arm/bin/ilinkarm.exe

	# No archiver arguments needed for IAR.
	ARCHFLAGS =

	ELFTOOLFLAGS_BIN = --bin
	ELFTOOLFLAGS_HEX = --ihex
	ELFTOOLFLAGS_S37 = --srec --srec-s3only

endif

.PHONY: all clean PROLOGUE

all: PROLOGUE $(OUTPUT_DIRS) $(COBJS) $(ASMOBJS) $(ASMOBJS2) $(ASMOBJS3) $(LIB_FILES)
	@echo 'Linking...'
	@$(LD) $(GROUP_START) $(LDFLAGS) $(COBJS) $(ASMOBJS) $(ASMOBJS2) $(ASMOBJS3) $(LIB_FILES) $(GROUP_END) -o $(OUTPUT_DIR)/$(TARGET).out	
	@$(ELFTOOL) $(OUTPUT_DIR)/$(TARGET).out $(ELFTOOLFLAGS_BIN) $(OUTPUT_DIR)/$(TARGET).bin
	@$(ELFTOOL) $(OUTPUT_DIR)/$(TARGET).out $(ELFTOOLFLAGS_HEX) $(OUTPUT_DIR)/$(TARGET).hex
	@$(ELFTOOL) $(OUTPUT_DIR)/$(TARGET).out $(ELFTOOLFLAGS_S37) $(OUTPUT_DIR)/$(TARGET).s37
	@echo 'Done.'

PROLOGUE:
#	@echo $(COBJS)
#	@echo $(ASMOBJS)
#	@echo $(ASMOBJS2)

$(OUTPUT_DIRS):
	@mkdir -p $@

$(COBJS): %.o:
	@echo 'Building $(notdir $(@:%.o=%.c))...'
	@$(CC) $(CCFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.c),$(CSOURCES)) > /dev/null \

$(ASMOBJS): %.o:
	@echo 'Building $(notdir $(@:%.o=%.s79))...'
	@$(AS) $(ASMFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.s79),$(ASMSOURCES)) > /dev/null

$(ASMOBJS2): %.o:
	@echo 'Building $(notdir $(@:%.o=%.s))...'
	@$(AS) $(ASMFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.s),$(ASMSOURCES2)) > /dev/null

$(ASMOBJS3): %.o:
	@echo 'Building $(notdir $(@:%.o=%.S))...'
	@$(AS) $(ASMFLAGS) -o $@ $(filter %$(@:$(OUTPUT_DIR)/%.o=%.S),$(ASMSOURCES3)) > /dev/null
  
clean:
	$(RM) -r $(COBJS)
	$(RM) -r $(ASMOBJS)
	$(RM) -r $(ASMOBJS2)
	$(RM) -r $(OUTPUT_DIR)
