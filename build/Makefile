CC=/home/khorton/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc
CPP=/home/khorton/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-g++
OBJDUMP=/home/khorton/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-objdump
NM=/home/khorton/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-nm
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0
CPPFLAGS = -c -mcpu=$(MACH) -fno-exceptions -mthumb -std=c++11 -O0
OBJ_DIR=../objs/
SRC_DIR=../source/
BUILD_DIR=./build/
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=$(OBJ_DIR).o)
FINAL = final_cpp.elf

all: $(FINAL)

# main.o: main.c
# 	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

# main.s: main.c
# 	$(CC) $(CFLAGS) -S  $^ -o $@

# gpio.o: gpio.c
# 	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

# uart.o: uart.c
# 	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

# adc.o: adc.c
# 	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

# systick.o: systick.c
# 	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

# tim.o: tim.c
# 	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@

stm32_startup.o: $(SRC_DIR)stm32_startup.c
	$(CC) $(CFLAGS) $^ -o $(OBJ_DIR)$@


main.o: $(SRC_DIR)main.cpp
	$(CPP) $(CPPFLAGS) $^ -o $(OBJ_DIR)$@

main.s: main.c
	$(CC) $(CFLAGS) -S  $^ -o $@

gpio.o: $(SRC_DIR)gpio.cpp
	$(CPP) $(CPPFLAGS) $^ -o $(OBJ_DIR)$@

uart.o: $(SRC_DIR)uart.cpp
	$(CPP) $(CPPFLAGS) $^ -o $(OBJ_DIR)$@

adc.o: $(SRC_DIR)adc.cpp
	$(CPP) $(CPPFLAGS) $^ -o $(OBJ_DIR)$@

systick.o: $(SRC_DIR)systick.cpp
	$(CPP) $(CPPFLAGS) $^ -o $(OBJ_DIR)$@

tim.o: $(SRC_DIR)tim.cpp
	$(CPP) $(CPPFLAGS) $^ -o $(OBJ_DIR)$@

$(FINAL): main.o gpio.o stm32_startup.o uart.o adc.o systick.o tim.o
	$(CPP) -nostdlib  $(OBJ_DIR)*.o -T stm32_ls.ld -Wl,-Map=final.map -o $@

final.elf: main.o gpio.o stm32_startup.o uart.o adc.o systick.o tim.o
	$(CC) -nostdlib  $(OBJ_DIR)*.o -T stm32_ls.ld -Wl,-Map=final.map -o $@

objdump: $(FINAL)
	$(OBJDUMP) -h $^

symbols: $(FINAL)
	$(NM) $^

load:
	 openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg 
	
debug:
	/home/khorton/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gdb


clean:
	rm -rf $(OBJ_DIR)*.o *.out *.elf *.map