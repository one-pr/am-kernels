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



/* ASCII 可见字符 95 个 */
static const char ascii_chars[] =
// 0~15
  " !\"#$%&'()*+,-./"
  "0123456789"
  ":;<=>?@"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "[\\]^_`"
  "abcdefghijklmnopqrstuvwxyz"
  "{|}~"
  ;
static const int ascii_char_num = 95;
static_assert((95+1) == ARRLEN(ascii_chars));

static const char special_chars[] = " !\"#$%&'()*+,-./";
static const int special_chars_num = 16;
static_assert((16+1) == ARRLEN(special_chars));
