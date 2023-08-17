#include "test-globals.cc"


// 简单的手动测试
void test_strncmp_eq() {
#define STRCMP_SELF_EQ(_str)  \
  assert0ret(strncmp(_str, _str, strlen(_str)-1)); \
  assert0ret(strncmp(_str, _str, strlen(_str))); \
  assert0ret(strncmp(_str, _str, strlen(_str)+1))

// const string
  STRCMP_SELF_EQ("");
  STRCMP_SELF_EQ("0");
  STRCMP_SELF_EQ("1");

  assert0ret(strncmp(" !\"#$%&'()*+,-./", special_chars, strlen(special_chars)-1));  // <Shift> + <0-9>
  assert0ret(strncmp("0123456789", numner_chars, strlen(numner_chars)-1));
  assert0ret(strncmp("ABCDEFGHIJKLMNOPQRSTUVWXYZ", uppercase_chars, strlen(uppercase_chars)-1));
  assert0ret(strncmp("abcdefghijklmnopqrstuvwxyz", lowercase_chars, strlen(lowercase_chars)-1));
  STRCMP_SELF_EQ(special_chars);
  STRCMP_SELF_EQ(numner_chars);
  STRCMP_SELF_EQ(uppercase_chars);
  STRCMP_SELF_EQ(lowercase_chars);
  STRCMP_SELF_EQ(simple_escape_chars);

  for (int i=0; i < escape_onechar_arr_len; i++) {
    STRCMP_SELF_EQ(escape_onechar_arr[i]);
  }

// empty str
  assert0ret(strncmp("", empty_str, 1));
  assert0ret(strncmp("", empty_strarr[0], 1));
  assert0ret(strncmp("", empty_carr, 1));
  assert0ret(strncmp("", empty_null, 1));
  assert0ret(strncmp("", zeros_carr, 1));
  STRCMP_SELF_EQ(empty_str);
  STRCMP_SELF_EQ(empty_strarr[0]);
  STRCMP_SELF_EQ(empty_carr);
  STRCMP_SELF_EQ(empty_null);
  STRCMP_SELF_EQ(zeros_carr);

#undef STRCMP_SELF_EQ
} /* test_strncmp_eq */


void test_strcmp_ne() {
#define STRCMP_TEST_LT(_lstr, _rstr) \
  /* LT */ assert(strncmp(_lstr, _rstr, strlen(_lstr)) < 0); \
           assert(strncmp(_lstr, _rstr, strlen(_rstr)) < 0); \
  /* GT */ assert(strncmp(_rstr, _lstr, strlen(_lstr)) > 0); \
           assert(strncmp(_rstr, _lstr, strlen(_rstr)) > 0)
// def STRCMP_TEST_LT

  // n==0, 返回值恒为 0
  assert0ret(strncmp("", "ysyx", 0));
  assert0ret(strncmp(" ", special_chars, 1));   // BUG

// 可见字符的比较
  STRCMP_TEST_LT(special_chars, numner_chars);
  STRCMP_TEST_LT(numner_chars, uppercase_chars);
  STRCMP_TEST_LT(uppercase_chars, lowercase_chars);
  // STRCMP_TEST_LT(lowercase_chars, "~");
// 传递性
  STRCMP_TEST_LT(" ", "~");

#undef STRCMP_TEST_LT
} /* test_strcmp_ne */


// 无其他依赖的自动化测试
void test_strcmp() {
//   static char buf[2] = {0};
// // 转义字符
//   for(int i=0; i < escape_onechar_arr_len; i++) {
//     buf[0] = escape_onechar_arr[i][0];
//     buf[1] = '\0';
//     assert_equals_with_ctx(0, strcmp(buf, escape_onechar_arr[i]),
//       printf("ctx: i=%d;\n"
//              "\tbuf   =%s\n"
//              "\tescape=%s\n",
//              i, buf, escape_onechar_arr[i]));
//   }

// // 字符指针
//   const char *p = ascii_chars;
//   for(int i=0; i <= ascii_char_len; i++, p++) {
//     assert_equals_with_ctx(
//       0, strcmp(p, p),
//       printf("ctx: i=%d;\n"
//              "\tp = %s\n",
//              i, p));
//   }
//   p = simple_escape_chars;
//   for(int i=0; i <= simple_escape_chars_len; i++, p++) {
//     assert_equals_with_ctx(
//       0, strcmp(p, p),
//       printf("ctx: i=%d;\n"
//              "\tp = %s\n",
//              i, p));
//   }

// // NE
//   p = ascii_chars;
//   for(int i=0; i < (ascii_char_len-1); i++, p++) {
//     assert(strcmp(p, p+1) < 0);
//     assert(strcmp(p+1, p) > 0);
//   }

} /* test_strcmp */

/*
  Type3 内存和字符串的[读取]函数:
  - memcmp
  - strlen/strcmp
*/
int main() {

  test_strncmp_eq();
  test_strcmp_ne();

  test_strcmp();

	return 0;
}
