#include "tarfs.h"
#include <string.h>

static int oct_to_bin(unsigned char *str, int size) {
  int n = 0;
  unsigned char *c = str;

  while (size-- > 0) {
    n *= 8;
    n += *c - '0';
    c++;
  }

  return n;
}

// returns file size and pointer to file data in out
static int tar_lookup(const unsigned char *archive, const char *filename,
                      char **out) {
  unsigned char *ptr = (void *)archive;

  while (!memcmp(ptr + 257, "ustar", 5)) {
    int filesize = oct_to_bin(ptr + 0x7c, 11);

    if (!memcmp(ptr, filename, strlen(filename) + 1)) {
      *out = (char *)ptr + 512;
      return filesize;
    }

    ptr += (((filesize + 511) / 512) + 1) * 512;
  }

  return -1;
}

char *tar_read(const unsigned char *archive, const char *filename) {
  char *ptr;

  if (tar_lookup(archive, filename, &ptr) < 0) {
    return NULL;
  }

  return ptr;
}
