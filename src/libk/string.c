#include <stddef.h>
#include <stdint.h>
#include <string.h>

size_t strlen(const char *str) {
  size_t len = 0;

  while (str[len]) {
    len++;
  }

  return len;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
  uint8_t *restrict pdest = (uint8_t *restrict)dest;
  const uint8_t *restrict psrc = (const uint8_t *restrict)src;

  for (size_t i = 0; i < n; i++) {
    pdest[i] = psrc[i];
  }

  return dest;
}

void *memset(void *s, int c, size_t n) {
  uint8_t *p = (uint8_t *)s;

  for (size_t i = 0; i < n; i++) {
    p[i] = (uint8_t)c;
  }

  return s;
}

void *memmove(void *dest, const void *src, size_t n) {
  uint8_t *pdest = (uint8_t *)dest;
  const uint8_t *psrc = (const uint8_t *)src;

  if (src > dest) {
    for (size_t i = 0; i < n; i++) {
      pdest[i] = psrc[i];
    }
  } else if (src < dest) {
    for (size_t i = n; i > 0; i--) {
      pdest[i - 1] = psrc[i - 1];
    }
  }

  return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const uint8_t *p1 = (const uint8_t *)s1;
  const uint8_t *p2 = (const uint8_t *)s2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] < p2[i] ? -1 : 1;
    }
  }

  return 0;
}

// Source - https://stackoverflow.com/a/2933896
// Posted by Joey Adams, modified by community. See post 'Timeline' for change
// history Retrieved 2026-02-04, License - CC BY-SA 3.0

size_t strlcpy(char *dest, const char *src, size_t len) {
  char *d = dest;
  char *e = dest + len; /* end of destination buffer */
  const char *s = src;

  /* Insert characters into the destination buffer
     until we reach the end of the source string
     or the end of the destination buffer, whichever
     comes first. */
  while (*s != '\0' && d < e) {
    *d++ = *s++;
  }

  /* Terminate the destination buffer, being wary of the fact
     that len might be zero. */
  if (d < e) { // If the destination buffer still has room.
    *d = 0;
  } else if (len > 0) { // We ran out of room, so zero out the last char
                        // (if the destination buffer has any items at all).
    d[-1] = 0;
  }

  /* Advance to the end of the source string. */
  while (*s != '\0')
    s++;

  /* Return the number of characters
     between *src and *s,
     including *src but not including *s .
     This is the length of the source string. */
  return s - src;
}
