CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

TARGET = $(notdir $(CURDIR))

REF = $(HOME)/development/systems-embedded/references/STM32CubeC0

CMSIS = $(REF)/Drivers/CMSIS
DEVICE = $(CMSIS)/Device/ST/STM32C0xx

CFLAGS = -mcpu=cortex-m0plus -mthumb \
         -O0 -g3 -Wall -Wextra \
         -DSTM32C031xx \
         -I$(CMSIS)/Include \
         -I$(DEVICE)/Include \
         -ffunction-sections -fdata-sections

LDFLAGS = -T STM32C031C6TX_FLASH.ld \
          -nostdlib \
          -Wl,--gc-sections \
          -Wl,-Map=$(TARGET).map

SOURCES = main.c \
	  bsp.c \
	  uart.c \
          system_stm32c0xx.c \
	  runtime.c \
          startup_stm32c031c6tx.s

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(TARGET).elf $(TARGET).bin $(TARGET).map

.PHONY: all clean
