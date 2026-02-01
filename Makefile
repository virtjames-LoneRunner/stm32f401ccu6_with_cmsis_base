# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Flags for a Cortex-M4 (e.g., STM32F4)
CFLAGS = -mcpu=cortex-m4 -mthumb -O0 -g3 -ffunction-sections -fdata-sections
CPPFLAGS = -DSTM32F401xC \
           -I./CMSIS/Device/ST/STM32F4xx/Include \
           -I./CMSIS/Core/Include

LINKER_FILE = stm32_ls.ld
LDFLAGS = -T $(LINKER_FILE) -Wl,--gc-sections --specs=nosys.specs -nostdlib # You'll need this file from the CMSIS repo

BUILDDIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, $(BUILDDIR)/%.o, $(SRCS))

all: main.bin

main.elf: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(BUILDDIR)/main.elf $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

main.bin: main.elf
	$(OBJCOPY) -O binary $(BUILDDIR)/main.elf $(BUILDDIR)/main.bin

flash: main.bin
	st-flash --reset write $(BUILDDIR)/main.bin 0x08000000

clean:
	rm build/*

.PHONY:
	clean, flash
