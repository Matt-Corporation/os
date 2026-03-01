#include "hal.h"
#include "hal/gdt.h"
#include "hal/idt.h"
#include "hal/irq.h"
#include "hal/isr.h"
#include "hal/paging.h"
#include <serial.h>
#include <terminal.h>

void hal_initialize() {
  gdt_initialize();
  idt_initialize();
  isr_initialize();
  irq_initialize();
  paging_initialize();
}
