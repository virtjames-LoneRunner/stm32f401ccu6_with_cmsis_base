# Toolchain
<<<<<<< HEAD
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
=======
TOOLDIR = ${TOOLS_PATH}
CC = ${TOOLSDIR}/arm-none-eabi-gcc
OBJCOPY = ${TOOLSDIR}/arm-none-eabi-objcopy
>>>>>>> f3704e1 (build(makefile): specifiy the tools path with an env variable)

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

main.elf: $(OBS)
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
		--suppress=missingIncludeSystem \
		--suppress=comparePointers \
		-i src/startup_stm32.c
