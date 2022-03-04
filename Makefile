CC=/home/khorton/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc
OBJDUMP=/home/khorton/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-objdump
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0
OBJ_DIR=./objs/

main.o: main.c
	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

main.s: main.c
	$(CC) $(CFLAGS) -S  $^ -o $@

led.o: led.c
	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

final.elf: main.o led.o stm32_startup.o
	$(CC) -nostdlib $(OBJ_DIR)*.o -T stm32_ls.ld -Wl,-Map=final.map -o $@

objdump: final.elf
	$(OBJDUMP) -h $^

clean:
	rm -rf $(OBJ_DIR)*.o *.out *.elf *.map