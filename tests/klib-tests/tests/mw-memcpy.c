#include "mem-write.cc"


void test_memcpy() {
// -- 复制数组
  clear_data();
  init_data_copy_seq();
  memcpy(data, data_copy, DATA_MAX_LEN);
  check_seq(0, DATA_MAX_LEN, 1);

  int l, r;
  for (l = 0; l < DATA_MAX_LEN; l ++) {
    for (r = l + 1; r <= DATA_MAX_LEN; r ++) {
      clear_data();
      init_data_copy_seq();
      // 复制 val
      uint8_t val = (l + r) / 2;
      memset(data_copy + l, val, r - l);  // 修改 data_copy
      memcpy(data, data_copy, DATA_MAX_LEN);
      check_seq(0, l, 1);
      check_eq(l, r, val);
      check_seq(r, DATA_MAX_LEN, r + 1);
    }
  }
} // test_memcpy


/*
  Type1 内存和字符串的写入函数:
  - memset/memcpy/memmove
  - strcpy/strncpy/strcat
*/
int main() {

  test_memcpy();

	return 0;
}
