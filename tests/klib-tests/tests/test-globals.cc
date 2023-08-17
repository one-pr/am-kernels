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


/* ==== 字符串常量 ==== */

__attribute_used__
static const char *empty_str = "";
__attribute_used__
static const char *empty_strarr[1] = { "" };
static char empty_carr[1] = { 0 };
static_assert((1) == ARRLEN(empty_carr));
static char empty_null[1] = { '\0' };
static_assert((1) == ARRLEN(empty_null));
static char zeros_carr[8] = { 0 };
static_assert((8) == ARRLEN(zeros_carr));

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
static const int ascii_char_len = 95;
static_assert((95+1) == ARRLEN(ascii_chars));

// 初始的特殊符号
static const char special_chars[] = " !\"#$%&'()*+,-./";
static const int special_chars_len = 16;
static_assert((16+1) == ARRLEN(special_chars));

// 数字
static const char numner_chars[] = "0123456789";
static const int numner_chars_len = 10;
static_assert((10+1) == ARRLEN(numner_chars));

// 大写字母
static const char uppercase_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int uppercase_chars_len = 26;
static_assert((26+1) == ARRLEN(uppercase_chars));

// 小写字母
static const char lowercase_chars[] = "abcdefghijklmnopqrstuvwxyz";
static const int lowercase_chars_len = 26;
static_assert((26+1) == ARRLEN(lowercase_chars));

// 转义字符.  C11, §A.1.5, (6.4.4.4) simple-escape-sequence:
static const char simple_escape_chars[] =
  "\'\"\?\\"
  "\a\b\f\n\r\t\v"
  ;
static const int simple_escape_chars_len = 11;
static_assert((11+1) == ARRLEN(simple_escape_chars));

static const char *escape_onechar_arr[] = {
// simple-escape-sequence:
  "\'", "\"", "\?", "\\",
  "\a", "\b", "\f", "\n", "\r", "\t", "\v",
// octal-escape-sequence
  "\001", "\007", "\070", "\077",
// hexadecimal-escape-sequence
  "\x1", "\x01", "\x0001", "\x00000001",
  "\xf", "\x0f", "\x000f", "\x0000000f",
  "\xf", "\xff",
  "\xF", "\xFF",
// universal-character-name
  // "\u0020", "\u007E",
};
static const int escape_onechar_arr_len = 27;
static_assert((27) == ARRLEN(escape_onechar_arr));