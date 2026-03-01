#!/usr/bin/env bash
rm -rf iso
rm -f libk.a
rm -f build.iso
rm -f kernel.bin
rm -f tarinit.tar
rm -f tarinit/test
rm -f $(find src/bootloader -name "*.o")
rm -f $(find src/kernel -name "*.o")
rm -f $(find src/libk -name "*.o")
rm -f $(find src/tests -name "*.o")
