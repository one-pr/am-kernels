#include "trap.h"

#define DATA_MAX_LEN  32
uint8_t data[DATA_MAX_LEN];


// 初始化 data[DATA_MAX_LEN] = 1..DATA_MAX_LEN
void init_data_seq() {
  for (int i = 0; i < DATA_MAX_LEN; i ++) {
    data[i] = i + 1;
  }
} // init_data_seq

// 检查 [l,r) 区间中的值是否依次为 val, val + 1, val + 2...
void check_seq(int l, int r, int val) {
  for (int i = l; i < r; i ++) {
    assert(data[i] == val + i - l);
  }
} // check_seq

// 检查 [l,r) 区间中的值是否均为 val
void check_eq(int l, int r, int val) {
  for (int i = l; i < r; i ++) {
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


int main() {

  test_memset();

	return 0;
}
