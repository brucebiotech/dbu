#
#
#

##############################################################################
ifndef BUILD_DIR
BUILD_DIR = .
endif


LDFLAGS =
CHIP_INFO = chip.txt

##############################################################################
# DBU
#
ifeq ($(APPLICATION_NAME), DBU_v1)
CHIP_INFO = chip_17.txt

BOARD = -D__SAML21E17B__ -DBOARD_DBU_v1
LDFLAGS += -Wl,--script=../linker/saml21e17b.ld
BUILD_DIR = build/dbu_v1

##############################################################################
# First fizzit
#
else ifeq ($(APPLICATION_NAME), FIZZIT_MDU_V1)

BOARD = -D__SAML21G18B__ -DBOARD_FIZZIT_MDU_V1 -DDUBUG_UNIT_PERFORMANCE_ATTR=
LDFLAGS += -Wl,--script=../linker/saml21e18b.ld
CHIP_INFO = chip_qfn48.txt
BUILD_DIR = build/fizzit_mdu_v1

else

ifndef APPLICATION_NAME
$(error you need to specify an application board, e.g. make APPLICATION_NAME=DBU_v1)
else
$(error unsupported board)
endif

endif


##############################################################################
.PHONY: all clean size

#TOOL_PREFIX = /c/armgcc/2021-10.3/bin/arm-none-eabi-
TOOL_PREFIX = arm-none-eabi-

CC = $(TOOL_PREFIX)gcc
OBJCOPY = $(TOOL_PREFIX)objcopy
SIZE = $(TOOL_PREFIX)size

# --std=gnu1

CFLAGS += -W -Wall -Wextra --std=c99 -O2 -Dasm=__asm
CFLAGS += -fno-diagnostics-show-caret -fno-diagnostics-color 
CFLAGS += -Wno-unused-parameter -Wno-address-of-packed-member -Wno-override-init
CFLAGS += -fdata-sections -ffunction-sections -fomit-frame-pointer
CFLAGS += -funsigned-char -funsigned-bitfields
CFLAGS += -mcpu=cortex-m0plus -mthumb
CFLAGS += -MD -MP -MT $(BUILD_DIR)/$(*F).o -MF $(BUILD_DIR)/$(@F).d


LDFLAGS += --specs=nano.specs  -mcpu=cortex-m0plus -mthumb 
LDFLAGS += -Wl,--gc-sections

INCLUDES += \
  -I../../../io\
  -I../../../cmsis-dap\
  -I../include \
  -I../include/cmsis \
  -I../include/cpu/asf
  
OBJS += \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/udc.o \
	$(BUILD_DIR)/usb.o \
	$(BUILD_DIR)/usb_descriptors.o \
	$(BUILD_DIR)/startup_saml21.o

DEFINES += \
  -DDONT_USE_CMSIS_INIT \
  -DF_CPU=48000000\
  $(BOARD)
 
CFLAGS += $(INCLUDES) $(DEFINES) -g3

CHIP_SECTION = chip

BINARY_NAME = $(BUILD_DIR)/dbu.elf


all: $(BUILD_DIR) $(BUILD_DIR)/dbu.elf size

$(BINARY_NAME): $(OBJS) $(CHIP_INFO) makefile
	@echo LD $@
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
	@$(OBJCOPY) --add-section $(CHIP_SECTION)=$(CHIP_INFO) \
		--set-section-flags $(CHIP_SECTION)=noload,readonly $@ $@
		
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/dbu.hex: $(BINARY_NAME)
	@echo OBJCOPY $@
	@$(OBJCOPY) -O ihex $^ $@

$(BUILD_DIR)/dbu.bin: $(BINARY_NAME)
	@echo OBJCOPY $@
	@$(OBJCOPY) -O binary $^ $@

size: $(BINARY_NAME)
	@echo size:
	@$(SIZE) -t $^

clean:
	@echo clean
	@-rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(BINARY_NAME) $(BUILD_DIR)/*.map

.PHONY: all clean size

-include $(wildcard $(BUILD_DIR)/*.d)

