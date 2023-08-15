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

    /* 完全相交：do-nothing
        start  end
        ┌──────O
        └──────O───────────────────────┘
        data   +len                    +MAX_LEN
    */
    init_data_seq();
    memmove(data, data, len);
    check_seq(0, DATA_MAX_LEN, 1);  // 1..N

    /* 完全不相交：退化为 memcpy
               start  end
               ┌──────O
        └──────O───────────────────────┘
        data   +len                    +MAX_LEN
    */
    int start = len;  // 确保完全不相交
    int end = start + len;
    while (end <= DATA_MAX_LEN) {
      init_data_seq();
      memmove(data+start, data, len);

      check_seq(0, start, 1);
      check_seq(start, end, 1);
      check_seq(len, start, len + 1);
      check_seq(end, DATA_MAX_LEN, end + 1);

      start++;
      end = start + len;
    }

    /* 确保相交
              start           end
              ┌───────────────O
          └────────────O────────────────────┘
          data         +len                 +MAX_LEN
    */
    start = 1;
    end = start + len;
    while (start < len) {  // 确保一定相交
      init_data_seq();
      memmove(data+start, data, len);

      check_seq(0, start, 1);
      check_seq(start, end, 1);
      check_seq(end, DATA_MAX_LEN, end + 1);
      start++;
      end = start + len;
    }
  }
  // putstr("[test_memmove] END\n");
} // test_memmove

// const int ascii_char_num = 95;
// /* ASCII 可见字符 95 个 */
// static const char strbuf[] =
// // 0~15
//   " !\"#$%&'()*+,-./"
// //
//   "0123456789"
//   ":;<=>?@"
//   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//   "[\\]^_`"
//   "abcdefghijklmnopqrstuvwxyz"
//   "{|}~"
//   ;
// assert((ascii_char_num+1) == ARRLEN(strbuf));

static const char special_chars[] = " !\"#$%&'()*+,-./";
static const int special_chars_num = 16;
// assert((special_chars_num+1) == ARRLEN(special_chars));

void test_strcpy() {
  char *pdata = (char *)data;

  for (int i=0; i <= special_chars_num; i++) {
  // 复制越来越少的字符
    const char *src = special_chars + i;
    int str_len = special_chars_num - i;  // 最终为 0
    init_data_seq();

    char *ret = strcpy(pdata, src);

    assert(ret == pdata);
    check_seq(0, str_len, src[0]);    // [0, str_len)
    assert('\0' == pdata[str_len]);   // [str_len] == '\0'
    check_seq(str_len + 1, DATA_MAX_LEN, str_len+2);  // [str_len+1. MAX)
  }
} // test_strcpy

void test_strcat() {
  char *pdata = (char *)data;

// TODO: 从中间开始复制
  for (int i=0; i <= special_chars_num; i++) {
  // 复制越来越少的字符
    const char *src = special_chars + i;
    int str_len = special_chars_num - i;  // 最终为 0
  // ---- 未使用部分为全 0
    clear_data();
    char *ret = strcat(pdata, src);

    assert(ret == pdata);
    check_seq(0, str_len, src[0]);    // [0, str_len)
    check_eq(str_len, DATA_MAX_LEN, 0);  // [str_len,  MAX)

  // ---- 未使用部分为正常
    init_data_seq();
    pdata[0] = '\0';  // 字符串清零
    ret = strcat(pdata, src);

    assert(ret == pdata);
    check_seq(0, str_len, src[0]);    // [0, str_len)
    check_eq(str_len, str_len+1, 0);  // [str_len] == '\0'
    check_seq(str_len+1, DATA_MAX_LEN, str_len+2);  // [str_len+1. MAX)
  }
} // test_strcat


/*
  Type1 内存和字符串的写入函数:
  - memset/memcpy/memmove
  - strcpy/strncpy/strcat
*/
int main() {
  // putstr("[main] start\n");

  test_memset();
  test_memcpy();
  test_memmove();

  test_strcpy();
  test_strcat();

	return 0;
}
