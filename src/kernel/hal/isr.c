// ISR from https://github.com/nanobyte-dev/nanobyte_os

#include "isr.h"
#include "idt.h"
#include <logs.h>
#include <panic.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/io.h>

isr_handler_t g_isr_handlers[256];

static const char *const g_exceptions[] = {"Divide by zero error",
                                           "Debug",
                                           "Non-maskable Interrupt",
                                           "Breakpoint",
                                           "Overflow",
                                           "Bound Range Exceeded",
                                           "Invalid Opcode",
                                           "Device Not Available",
                                           "Double Fault",
                                           "Coprocessor Segment Overrun",
                                           "Invalid TSS",
                                           "Segment Not Present",
                                           "Stack-Segment Fault",
                                           "General Protection Fault",
                                           "Page Fault",
                                           "",
                                           "x87 Floating-Point Exception",
                                           "Alignment Check",
                                           "Machine Check",
                                           "SIMD Floating-Point Exception",
                                           "Virtualization Exception",
                                           "Control Protection Exception ",
                                           "",
                                           "",
                                           "",
                                           "",
                                           "",
                                           "",
                                           "Hypervisor Injection Exception",
                                           "VMM Communication Exception",
                                           "Security Exception",
                                           ""};

void isr_initialize_gates();

void isr_initialize() {
  msgf(STATUS_BLANK, "Initializing ISR...");
  isr_initialize_gates();

  for (int i = 0; i < 256; i++) {
    idt_enable_gate(i);
  }

  idt_disable_gate(0x80);
  msgf(STATUS_OK, "Initialized ISR.");
}

void __attribute__((cdecl)) isr_handler(registers_t *regs) {
  if (g_isr_handlers[regs->interrupt] != NULL) {
    g_isr_handlers[regs->interrupt](regs);
  } else if (regs->interrupt >= 32) {
    printf("Unhandled interrupt %lu!\n", (unsigned long)regs->interrupt);
  } else {
    panicf("Unhandled exception %d %s\n"
           "  eax=0x%x  ebx=0x%x  ecx=0x%x  edx=0x%x  esi=0x%x  edi=0x%x\n"
           "  esp=0x%x  ebp=0x%x  eip=0x%x  eflags=0x%x  cs=0x%x  ds=0x%x  "
           "ss=0x%x\n"
           "  interrupt=0x%x  errorcode=0x%x\n",
           regs->interrupt, g_exceptions[regs->interrupt], regs->eax, regs->ebx,
           regs->ecx, regs->edx, regs->esi, regs->edi, regs->esp, regs->ebp,
           regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss,
           regs->interrupt, regs->error);
  }
}

void isr_register_handler(int interrupt, isr_handler_t handler) {
  g_isr_handlers[interrupt] = handler;
  idt_enable_gate(interrupt);
}
