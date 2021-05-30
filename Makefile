# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES = $(wildcard kernel/*.c drivers/*.c intrpt/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h intrpt/*.h)

OBJ = ${C_SOURCES:.c=.o intrpt/interrupt.o}

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/bin/gdb
QEMU = /usr/bin/qemu-system-x86_64

CFLAGS = -g -ffreestanding

# Main rules
os-image.bin : boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin : boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

run: os-image.bin
	${QEMU} -fda os-image.bin

# Debug rules
kernel.elf : boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

debug : os-image.bin kernel.elf
	${QEMU} -s -fda os-image.bin &
	${GDB} -ix=/home/rose/.gdbinit -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Wildcard rules
%.o : %.c ${HEADERS}
	${CC} ${CFLAGS} -std=c99 -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -o $@

# Other rules
clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o drivers/*.o intrpt/*.o boot/*.o boot/*.bin