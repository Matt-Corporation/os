.text
  .code32
  .globl enable_interrupts
  .globl disable_interrupts

enable_interrupts:
  sti
  ret

disable_interrupts:
  cli
  ret
