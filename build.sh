i686-elf-as boot.s -o boot.o
i686-elf-gcc -c src/boot.c -o src/boot.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I src/libc
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o src/boot.o -lgcc
