#!/usr/bin/env bash
mkdir -p iso/boot/grub
mkdir -p iso/EFI/BOOT
cp tarinit.tar iso/tarinit.tar
cp kernel.bin iso/boot/kernel.bin
cp src/grub.cfg iso/boot/grub/grub.cfg
cp src/bootloader/BOOTX64.efi iso/EFI/BOOT/BOOTX64.efi
cp src/bootloader/grubx64.efi iso/EFI/BOOT/grubx64.efi
i686-elf-grub-mkrescue -o build.iso iso 2>/dev/null
