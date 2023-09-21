/* from http://rosettacode.org/wiki/CRC-32#C */

#include <klib-macros.h>
#include "trap.h"

#define CRC_PLOY_SIZE   256
#define STR "The quick brown fox jumps over the lazy dog"
#define STRLEN (sizeof(STR) - 1)

static uint32_t g_crc32_table[CRC_PLOY_SIZE];


/* Calculate CRC table. */
static void crc32_init() {
  for (int i = 0; i < CRC_PLOY_SIZE; i++) {
    /* remainder from polynomial division */
    uint32_t rem = i;

    for (int j = 0; j < 8; j++) {
      if (rem & 1) {
        rem >>= 1;
        rem ^= 0xedb88320;
      } else {
        rem >>= 1;
      }
    }

    g_crc32_table[i] = rem;
  }
} /* crc32_init */

uint32_t crc32(uint32_t crc, const char *buf, size_t len) {
	crc = ~crc;

	const char *end = buf + len;
	for (const char *p = buf; p < end; p++) {
		uint8_t octet = *p;  /* Cast to unsigned octet. */
		crc = (crc >> 8) ^ g_crc32_table[(crc & 0xff) ^ octet];
	}

	return ~crc;
} /* crc32 */

/* This check is not thread safe; there is no mutex. */
int main() {
  crc32_init();

  check(0x414FA339 == crc32(0, STR, STRLEN));

	return 0;
}
