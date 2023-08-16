#include "mem-write.cc"

#define MEMCMP_TEST(_expected, _str) \
  assert0ret(memcmp(_expected, _str, sizeof(_expected))); \
  assert0ret(memcmp(_str, _expected, sizeof(_expected)));

// 简单的手动测试
void test_strcmp_eq() {
#define MEMCMP_SELF_EQ(_const_str) \
  assert0ret(memcmp(_const_str, _const_str, sizeof(_const_str)))

// const string
  MEMCMP_SELF_EQ("");
  MEMCMP_SELF_EQ("0");
  MEMCMP_SELF_EQ("1");

  MEMCMP_TEST(" !\"#$%&'()*+,-./", special_chars);  // <Shift> + <0-9>
  MEMCMP_TEST("0123456789", numner_chars);
  MEMCMP_TEST("ABCDEFGHIJKLMNOPQRSTUVWXYZ", uppercase_chars);
  MEMCMP_TEST("abcdefghijklmnopqrstuvwxyz", lowercase_chars);
  MEMCMP_SELF_EQ(special_chars);
  MEMCMP_SELF_EQ(numner_chars);
  MEMCMP_SELF_EQ(uppercase_chars);
  MEMCMP_SELF_EQ(lowercase_chars);
  MEMCMP_SELF_EQ(simple_escape_chars);

  for (int i=0; i < escape_onechar_arr_len; i++) {
    MEMCMP_SELF_EQ(escape_onechar_arr[i]);
  }

// empty str
  MEMCMP_TEST("", empty_str);
  MEMCMP_TEST("", empty_strarr[0]);
  MEMCMP_TEST("", empty_carr);
  MEMCMP_TEST("", empty_null);
  MEMCMP_TEST("", zeros_carr);
  MEMCMP_SELF_EQ(empty_str);
  MEMCMP_SELF_EQ(empty_strarr[0]);
  MEMCMP_SELF_EQ(empty_carr);
  MEMCMP_SELF_EQ(empty_null);
  MEMCMP_SELF_EQ(zeros_carr);

#undef MEMCMP_SELF_EQ
} /* test_strcmp_eq */


void test_strcmp_ne() {
#define MEMCMP_TEST_LT(_expected, _rstr) \
  /* LT */ assert(memcmp(_expected, _rstr, sizeof(_expected)) < 0); \
  /* GT */ assert(memcmp(_rstr, _expected, sizeof(_expected)) > 0)
// def MEMCMP_TEST_LT

  MEMCMP_TEST_LT("", "ysyx");
  MEMCMP_TEST_LT("", "cyhan");

// 可见字符的比较
  MEMCMP_TEST_LT(" ", special_chars);
  MEMCMP_TEST_LT(special_chars, numner_chars);
  MEMCMP_TEST_LT(numner_chars, uppercase_chars);
  MEMCMP_TEST_LT(uppercase_chars, lowercase_chars);
  MEMCMP_TEST_LT(lowercase_chars, "~");
// 传递性
  MEMCMP_TEST_LT(" ", "~");

#undef MEMCMP_TEST_LT
} /* test_strcmp_ne */


// 无其他依赖的自动化测试
void test_strcmp() {
  static char buf[2] = {0};
// 转义字符
  for(int i=0; i < escape_onechar_arr_len; i++) {
    buf[0] = escape_onechar_arr[i][0];
    buf[1] = '\0';
    MEMCMP_TEST(buf, escape_onechar_arr[i]);
  }

// 字符指针
  const char *p = ascii_chars;
  for(int i=0; i <= ascii_char_len; i++, p++) {
    assert0ret(memcmp(p, p, ascii_char_len-i));
  }
  p = simple_escape_chars;
  for(int i=0; i <= simple_escape_chars_len; i++, p++) {
    assert0ret(memcmp(p, p, simple_escape_chars_len-i));
  }

// NE
  p = ascii_chars;
  for(int i=0; i < (ascii_char_len-1); i++, p++) {
    size_t short_str_len = ascii_char_len-i-1;
    assert(memcmp(p, p+1, short_str_len) < 0);
    assert(memcmp(p+1, p, short_str_len) > 0);
  }

} /* test_strcmp */

/*
  Type3 内存和字符串的[读取]函数:
  - memcmp
  - strlen/strcmp
*/
int main() {

  test_strcmp_eq();
  test_strcmp_ne();

  test_strcmp();

	return 0;
}
