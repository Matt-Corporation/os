#!/usr/bin/env bash
qemu-system-i386 -cdrom build.iso -monitor telnet:127.0.0.1:1234,server,nowait -serial stdio
