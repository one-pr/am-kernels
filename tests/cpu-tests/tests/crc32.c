/* from http://rosettacode.org/wiki/CRC-32#C */

#include <klib-macros.h>
#include "trap.h"

#define CRC_PLOY_SIZE   256
#define STRLEN(_str)      (sizeof(_str) - 1)
#define STR_ARGS(_str)    _str, STRLEN(_str)

static uint32_t g_crc32_table[CRC_PLOY_SIZE];
static struct test {
  uint32_t crc;
  const char *str;
  uint32_t len;
} tests[] = {
  {0x414FA339, STR_ARGS("The quick brown fox jumps over the lazy dog")},

  {0x00000000, STR_ARGS("")},
  {0xE96CCF45, STR_ARGS(" ")},
  {0xE8B7BE43, STR_ARGS("a")},
  {0x352441C2, STR_ARGS("abc")},
  {0xAFABD35E, STR_ARGS("crc32")},
  {0xF52FB817, STR_ARGS("Risc-V 32")},
  {0x1B851995, STR_ARGS("Hello world!")},
  {0xAAB34F5B, STR_ARGS("Cyclic Redundancy Check")},
  {0x9CD969CA, STR_ARGS("Welcome to riscv32-NEMU!")},

  {0xABF77822, STR_ARGS("ABCDEFGHIJKLMNOPQRSTUVWXYZ")},
  {0x4C2750BD, STR_ARGS("abcdefghijklmnopqrstuvwxyz")},
  {0x1fc2e6d2, STR_ARGS(
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789")},
  {0x9CD969CA, STR_ARGS("Welcome to riscv32-NEMU!")},
  {0x342A13F2, STR_ARGS(
    "If trace is enabled,"
    " a log file will be generated to record the trace."
    " This may lead to a large log file."
    " If it is not necessary,"
    " you can disable it in menuconfig")},

  {0, NULL, 0},
}; // tests[]


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

  for (int i=0; tests[i].str; i++) {
    uint32_t crc = tests[i].crc;
    const char *str = tests[i].str;
    uint32_t len = tests[i].len;

    check(crc == crc32(0, str, len));
  }

	return 0;
}
