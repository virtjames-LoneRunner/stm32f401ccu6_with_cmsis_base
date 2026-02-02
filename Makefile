# Toolchain
ifdef TOOLS_PATH
	export PATH := $(TOOLS_PATH)/bin:$(PATH)
	CC = $(TOOLS_PATH)/arm-none-eabi-gcc
	OBJCOPY = $(TOOLS_PATH)/arm-none-eabi-objcopy
else
	CC = arm-none-eabi-gcc
	OBJCOPY = arm-none-eabi-objcopy
endif


# Flags for a Cortex-M4 (e.g., STM32F4)
CFLAGS = -mcpu=cortex-m4 -mthumb -O0 -g3 -ffunction-sections -fdata-sections
CADDFLAGS = -DSTM32F401xC \
           -I./CMSIS/Device/ST/STM32F4xx/Include \
           -I./CMSIS/Core/Include

LINKER_FILE = stm32_ls.ld
LDFLAGS = -T ${LINKER_FILE} -Wl,--gc-sections -nostdlib\

BUILDDIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, $(BUILDDIR)/%.o, $(SRCS))

CPPCHECK = cppcheck

all: main.bin

main.elf: $(OBJS)
	$(CC) $(CFLAGS) $(CADDFLAGS) $(OBJS) -o $(BUILDDIR)/main.elf $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) $(CADDFLAGS) -c $< -o $@

main.bin: main.elf
	$(OBJCOPY) -O binary $(BUILDDIR)/main.elf $(BUILDDIR)/main.bin



.PHONY:
	clean flash cppcheck

flash: main.bin
	st-flash --reset write $(BUILDDIR)/main.bin 0x08000000

clean:
	rm build/*

cppcheck:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 \
		--inline-suppr \
		$(CADDFLAGS) \
		$(SRCS) \
		-i src/startup_stm32.c
