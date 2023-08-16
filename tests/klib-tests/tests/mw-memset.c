#include "test-globals.cc"

void test_memset() {
  int l, r;
  for (l = 0; l < DATA_MAX_LEN; l ++) {
    for (r = l + 1; r <= DATA_MAX_LEN; r ++) {
      init_data_seq();
      uint8_t val = (l + r) / 2;
      memset(data + l, val, r - l);
      check_seq(0, l, 1);
      check_eq(l, r, val);
      check_seq(r, DATA_MAX_LEN, r + 1);
    }
  }
} // test_memset


/*
  Type1 内存和字符串的写入函数:
  - memset/memcpy/memmove
  - strcpy/strncpy/strcat
*/
int main() {

  test_memset();

	return 0;
}
