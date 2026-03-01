#!/usr/bin/env bash
CC=i686-elf-gcc
AS=i686-elf-as

declare -a LIBK_SRCS=$(find src/libk -name "*.c")
declare -a LIBK_OBJS=$(find src/libk -name "*.o")

$AS "src/bootloader/header.s" -o "src/bootloader/header.o"
$AS "src/kernel/hal/gdt_asm.s" -o "src/kernel/hal/gdt_asm.o"
$AS "src/kernel/hal/idt_asm.s" -o "src/kernel/hal/idt_asm.o"
$AS "src/kernel/hal/isr_asm.s" -o "src/kernel/hal/isr_asm.o"
$AS "src/kernel/hal/paging_asm.s" -o "src/kernel/hal/paging_asm.o"
$AS "src/kernel/hal/interrupts.s" -o "src/kernel/hal/interrupts.o"

declare -a KERNEL_SRCS=$(find src/kernel -name "*.c")

for file in ${KERNEL_SRCS[@]}
do
  $CC -c $file -o "${file%.c}.o" -std=gnu99 -ffreestanding -O3 -Wall -Wextra -I "src/libk/includes" -Wno-multistatement-macros
done

declare -a KERNEL_OBJS=$(find src/kernel -name "*.o")

declare -a TESTS_SRCS=$(find src/tests -name "*.c")

for file in ${TESTS_SRCS[@]}
do
  $CC -c $file -o "${file%.c}.o" -std=gnu99 -ffreestanding -O3 -Wall -Wextra -I "src/libk/includes" -Wno-multistatement-macros
done

declare -a TESTS_OBJS=$(find src/tests -name "*.o")

$CC -T "src/linker.ld" -o kernel.bin -ffreestanding -O3 -nostdlib "src/bootloader/header.o" $KERNEL_OBJS $TESTS_OBJS "libk.a" -lgcc

if i686-elf-grub-file --is-x86-multiboot2 kernel.bin; then
  echo multiboot2 confirmed!!1!
else
  echo "the file is not multiboot2; ur code is shit"
fi
