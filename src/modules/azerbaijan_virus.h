#pragma once

#include "../kmod.h"

static inline int virus() {
  puts("Hello I am Azerbaijan virus, due to poor development in my country I am not able to steal your files. Please kindly smash your computer with a hammer");
  return 0;
}

const kernel_module_t azerbaijan_virus = {.name = "azerbaijan_virus", .init = virus, .exit = virus};
