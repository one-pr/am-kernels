#include "trap.h"

#if defined(__ISA_NATIVE__) && !defined(__NATIVE_USE_KLIB__)
#define WITH_DEBUG_LOG 1
#endif

#define DATA_MAX_LEN  32
uint8_t data[DATA_MAX_LEN];
uint8_t data_copy[DATA_MAX_LEN] = {0};

void clear_data() {
  for (int i = 0; i < DATA_MAX_LEN; i ++)
    data[i] = 0;
}
// 初始化 data[DATA_MAX_LEN] = 1..DATA_MAX_LEN
void init_data_seq() {
  for (int i = 0; i < DATA_MAX_LEN; i ++) {
    data[i] = i + 1;
  }
} // init_data_seq
void init_data_copy_seq() {
  for (int i = 0; i < DATA_MAX_LEN; i ++) {
    data_copy[i] = i + 1;
  }
} // init_data_copy_seq


// 检查 [l,r) 区间中的值是否依次为 val, val + 1, val + 2...
void check_seq(int l, int r, int val) {
  for (int i = l; i < r; i ++) {
#ifdef WITH_DEBUG_LOG
    if (data[i] != val + i - l) {
      printf("[native.dbg] check_seq(l=%d, r=%d, val=%d):"
             " data[%d](%d) != %d\n",
              l, r, val,
              i, data[i], val + i - l);
    }
#endif // WITH_DEBUG_LOG
    assert(data[i] == val + i - l);
  }
} // check_seq

// 检查 [l,r) 区间中的值是否均为 val
void check_eq(int l, int r, int val) {
  for (int i = l; i < r; i ++) {
#ifdef WITH_DEBUG_LOG
    if (data[i] != val) {
      printf("[native.dbg] check_eq(l=%d, r=%d, val=%d):"
             " data[%d](%d) != %d\n",
              l, r, val,
              i, data[i], val);
    }
#endif // WITH_DEBUG_LOG
    assert(data[i] == val);
  }
} // check_eq


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

void test_memmove() {
  // putstr("[test_memmove] start\n");
  // 要移动的区间长度
  for (int len = 0; len <= DATA_MAX_LEN; len++) {
    init_data_seq();
    check_seq(0, DATA_MAX_LEN, 1);  // 1..N

    init_data_seq();
    memmove(data, data, len);
    check_seq(0, DATA_MAX_LEN, 1);  // 1..N

    /*
      check_seq(0, s, 1);
      check_seq(s, dst, s + 1);
      check_seq(dst, end, s + 1);
      check_seq(end, DATA_MAX_LEN, end + 1);
    */
  }
  // putstr("[test_memmove] END\n");
} // test_memmove


/*
  Type1 内存和字符串的写入函数:
  - memset/memcpy/memmove
  - strcat/strcpy/strncpy
*/
int main() {
  // putstr("[main] start\n");

  test_memset();
  test_memcpy();
  test_memmove();

	return 0;
}
