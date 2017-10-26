rwildcard = $(foreach d, $(wildcard $1*), $(filter $(subst *, %, $2), $d) $(call rwildcard, $d/, $2))

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_tools

TARGET   := $(notdir $(CURDIR))
INCLUDES := include
SOURCE   := source
BUILD    := build
LIBS     :=

INCLUDE := $(foreach incdir, $(INCLUDES), -I"$(shell pwd)/$(incdir)")
ARCH    := -mlittle-endian -mthumb -mcpu=arm926ej-s -msoft-float

CFLAGS  := $(ARCH) -O2 -ggdb -ffast-math -std=c99 -pipe -Wextra \
           -ffunction-sections -fdata-sections $(INCLUDE)
ASFLAGS := $(ARCH) -x assembler-with-cpp $(INCLUDE)

LDFLAGS := $(ARCH) -Tlink.ld -ggdb -Wl,--gc-sections -nostartfiles $(LIBS)

OBJS    := $(patsubst $(SOURCE)/%.s, $(BUILD)/%.s.o, \
           $(patsubst $(SOURCE)/%.c, $(BUILD)/%.c.o, \
           $(call rwildcard, $(SOURCE), *.s *.c)))

.PHONY: all clean
all: $(TARGET).bin

clean:
	@rm -rf $(BUILD) $(TARGET).elf $(TARGET).bin

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -S -O binary $^ __tmp.bin
	@cat header.bin __tmp.bin > $(TARGET).bin
	@rm __tmp.bin

$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD)/%.c.o: $(SOURCE)/%.c
	@mkdir -p "$(@D)"
	$(CC) $(CFLAGS) $^ -c -o $@

$(BUILD)/%.s.o: $(SOURCE)/%.s
	@mkdir -p "$(@D)"
	$(CC) $(ASFLAGS) $^ -c -o $@
