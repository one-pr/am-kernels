#include <limits.h>
#include "test-globals.cc"


#define SPRINTF_fmt_TEST(_const_str, _fmt, _str_input) \
  sprintf(outbuf, _fmt, _str_input); \
  assert_equals_with_ctx(0, \
    strcmp(outbuf, _const_str), \
    printf("\twant = \"%s\"\n" \
           "\tgot  = \"%s\"\n", \
            _const_str, outbuf))
// ----------------------------------------------

static char outbuf[512] = {0};

void clear_buf() {
  memset(outbuf, '\0', 512);
}


// 简单的手动测试
void test_sprintf_fmt_s() {
  clear_buf();

#define SPRINTF_fmt_S_TEST(_const_str) \
  SPRINTF_fmt_TEST(_const_str, "%s", _const_str)

// const string
  SPRINTF_fmt_S_TEST("");
  SPRINTF_fmt_S_TEST("0");
  SPRINTF_fmt_S_TEST("1");

  SPRINTF_fmt_S_TEST(special_chars);
  SPRINTF_fmt_S_TEST(numner_chars);
  SPRINTF_fmt_S_TEST(uppercase_chars);
  SPRINTF_fmt_S_TEST(lowercase_chars);
  SPRINTF_fmt_S_TEST(simple_escape_chars);

  for (int i=0; i < escape_onechar_arr_len; i++) {
    SPRINTF_fmt_S_TEST(escape_onechar_arr[i]);
  }

// empty str
  SPRINTF_fmt_S_TEST(empty_str);
  SPRINTF_fmt_S_TEST(empty_strarr[0]);
  SPRINTF_fmt_S_TEST(empty_carr);
  SPRINTF_fmt_S_TEST(empty_null);
  SPRINTF_fmt_S_TEST(zeros_carr);

#undef SPRINTF_fmt_S_TEST
} /* test_sprintf_fmt_s */

void test_sprintf_fmt_d() {
    clear_buf();

#define SPRINTF_fmt_d_TEST(_const_str, _num) \
  SPRINTF_fmt_TEST(_const_str, "%d", _num)
// --------------------------------------------

  SPRINTF_fmt_d_TEST("0", 0);
  SPRINTF_fmt_d_TEST("0", -0);
  SPRINTF_fmt_d_TEST("0", 000);
  SPRINTF_fmt_d_TEST("1", 1);
  SPRINTF_fmt_d_TEST("256", 256);

  SPRINTF_fmt_d_TEST("-2147483648", INT_MIN);
  SPRINTF_fmt_d_TEST("-2147483647", INT_MIN + 1);
  SPRINTF_fmt_d_TEST("126322567",   INT_MAX / 17);
  SPRINTF_fmt_d_TEST("252645135",   UINT_MAX / 17);
  SPRINTF_fmt_d_TEST("2147483647",  INT_MAX);
  SPRINTF_fmt_d_TEST("-1",  UINT_MAX);
  SPRINTF_fmt_d_TEST("0",   UINT_MAX+1);

// %
  SPRINTF_fmt_TEST("0%",    "%d%%", 0);
  SPRINTF_fmt_TEST("100%",  "%d%%", 100);
#undef SPRINTF_fmt_d_TEST
} // test_sprintf_fmt_d

// [%c]
void test_sprintf_fmt_c() {
#define SPRINTF_fmt_c_TEST(_const_str, _num) \
  SPRINTF_fmt_TEST(_const_str, "%c", _num)
// --------------------------------------------

  clear_buf();
  SPRINTF_fmt_c_TEST("", 0);
  SPRINTF_fmt_c_TEST("", -0);
  SPRINTF_fmt_c_TEST("", 000);
  SPRINTF_fmt_c_TEST("\0", 0);
  SPRINTF_fmt_c_TEST("A", 0x41);
  SPRINTF_fmt_c_TEST("a", 0x61);
  SPRINTF_fmt_c_TEST("\xff", 0xff);

  SPRINTF_fmt_c_TEST("", 0xff+1);

#undef SPRINTF_fmt_c_TEST
} // test_sprintf_fmt_c


int main() {

  test_sprintf_fmt_s();
  test_sprintf_fmt_d();
  test_sprintf_fmt_c();

	return 0;
}
