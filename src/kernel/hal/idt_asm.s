# IDT from https://github.com/nanobyte-dev/nanobyte_os

.text
  .code32
  .globl i686_IDT_Load

.stub:
  ret

i686_IDT_Load:
  # make new call frame
  push %ebp              # save old call frame
  mov %esp, %ebp         # initialize new call frame
  
  # load idt
  mov 8(%ebp), %eax
  lidt (%eax)

  # restore old call frame
  mov %ebp, %esp
  pop %ebp

  call .stub
