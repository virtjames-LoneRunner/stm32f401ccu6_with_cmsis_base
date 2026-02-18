# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Flags for a Cortex-M4 (e.g., STM32F4)
CFLAGS = -mcpu=cortex-m4 -mthumb -O0 -g3 -ffunction-sections -fdata-sections
CADDFLAGS = -DSTM32F401xC \
            -I./external/CMSIS/Device/ST/STM32F4xx/Include \
            -I./external/CMSIS/Core/Include \
						-I./external/printf \
					  -I./src/common \
					  -I./src/drivers \
					  -I./src/app 

LINKER_FILE = stm32_ls.ld
LDFLAGS = -T ${LINKER_FILE} -Wl,--gc-sections -nostdlib

BUILDDIR = build
SRCS_WITH_HEADERS = src/drivers/io.c \
										src/drivers/rcc.c \
										src/drivers/flash.c \
										src/drivers/pwr.c \
										src/drivers/dma.c \
										src/test/init.test.c

SRCS = $(wildcard src/*.c) \
			 src/common/utils.c \
			 $(SRCS_WITH_HEADERS)

HEADERS = $(SRCS_WITH_HEADERS:.c=.h) \
					src/common/defines.h \
					src/test/blink.test.h 

OBJS = $(patsubst src/%.c, $(BUILDDIR)/%.o, $(SRCS))

CPPCHECK = cppcheck

all: main.bin

main.elf: $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(CADDFLAGS) $(OBJS) -o $(BUILDDIR)/main.elf $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.c
	@mkdir -p build build/drivers build/common build/app build/test
	$(CC) $(CFLAGS) $(CADDFLAGS) -c $< -o $@

main.bin: main.elf
	$(OBJCOPY) -O binary $(BUILDDIR)/main.elf $(BUILDDIR)/main.bin


.PHONY:
	clean flash cppcheck

flash: main.bin
	st-flash --reset write $(BUILDDIR)/main.bin 0x08000000

clean:
	rm -rf build/*

cppcheck:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 \
		--language=c \
		--inline-suppr \
		-I./src \
		-i./external/CMSIS \
		-i./external/printf \
		--suppress=*:src/startup_stm32.c \
		--suppress=missingInclude \
		--suppress=checkersReport \
		--suppress=missingIncludeSystem \
		--suppress=unusedFunction \
		$(SRCS) 

