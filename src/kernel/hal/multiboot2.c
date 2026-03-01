#include "multiboot2.h"
#include <panic.h>
#include <stddef.h>

void *multiboot2_find_tag(uint32_t type, multiboot2_tag_t *tags) {
  while (tags->type != 0) {
    if (tags->type == type)
      return tags;

    // The following applies only to setting the pointer (the line before
    // incrementing the total_tags variable).
    // Source - https://stackoverflow.com/a/79104028
    // Posted by IsCoffeeTho, modified by community. See post 'Timeline' for
    // change history Retrieved 2026-01-26, License - CC BY-SA 4.0
    tags = (multiboot2_tag_t *)((uint8_t *)tags + ((tags->size + 7) & ~7));
  }

  panicf("multiboot2 tag %d does not exist", type);

  return NULL; // not needed
}
