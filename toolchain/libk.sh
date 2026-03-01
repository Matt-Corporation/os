#!/usr/bin/env bash
set -e

CC=i686-elf-gcc
AS=i686-elf-as
AR=i686-elf-ar

LIBK_A=libk.a
declare -a LIBK_SRCS=$(find src/libk -name "*.c")

for file in ${LIBK_SRCS[@]}
do
  $CC -I "src/libk/includes" -lgcc -ffreestanding -nostdlib -c $file -o "${file%.c}.o" -Wno-multistatement-macros
done

LIBK_OBJS=$(find src/libk -name "*.o")

$AR rcs $LIBK_A $LIBK_OBJS
