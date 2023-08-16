#include <limits.h>
#include "test-globals.cc"


static char outbuf[512] = {0};

void clear_buf() {
  memset(outbuf, '\0', 512);
}

// 简单的手动测试
void test_sprintf_const() {
  clear_buf();

#define SPRINTF_fmt_S_TEST(_const_str) \
  sprintf(outbuf, "%s", _const_str); \
  assert0ret(strcmp(outbuf, _const_str))

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
} /* test_sprintf_const */



void test_sprintf_fmt_d() {
    clear_buf();

#define SPRINTF_fmt_d_TEST(_const_str, _num) \
  sprintf(outbuf, "%d", _num); \
  assert_equals_with_ctx( \
    0, strcmp(outbuf, _const_str), \
    printf("\toutbuf = '%s'\n" \
           "\tconst  = '%s'\n", \
            outbuf, _const_str));
// -----------------------------------------------------

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

#undef SPRINTF_fmt_d_TEST
} // test_sprintf_fmt_d

int main() {

  test_sprintf_const();
  test_sprintf_fmt_d();

	return 0;
}
