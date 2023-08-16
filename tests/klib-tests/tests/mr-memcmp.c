#include "mem-write.cc"


// 简单的手动测试
void test_strcmp_eq() {
#define MEMCMP_SELF_EQ(_const_str)  assert0ret(memcmp(_const_str, _const_str, sizeof(_const_str)))

// const string
  MEMCMP_SELF_EQ("");
  MEMCMP_SELF_EQ("0");
  MEMCMP_SELF_EQ("1");

//   assert0ret(memcmp(" !\"#$%&'()*+,-./", special_chars));  // <Shift> + <0-9>
//   assert0ret(memcmp("0123456789", numner_chars));
//   assert0ret(memcmp("ABCDEFGHIJKLMNOPQRSTUVWXYZ", uppercase_chars));
//   assert0ret(memcmp("abcdefghijklmnopqrstuvwxyz", lowercase_chars));
  MEMCMP_SELF_EQ(special_chars);
  MEMCMP_SELF_EQ(numner_chars);
  MEMCMP_SELF_EQ(uppercase_chars);
  MEMCMP_SELF_EQ(lowercase_chars);
  MEMCMP_SELF_EQ(simple_escape_chars);

//   for (int i=0; i < escape_onechar_arr_len; i++) {
//     MEMCMP_SELF_EQ(escape_onechar_arr[i]);
//   }

// // empty str
//   assert0ret(memcmp("", empty_str));
//   assert0ret(memcmp("", empty_strarr[0]));
//   assert0ret(memcmp("", empty_carr));
//   assert0ret(memcmp("", empty_null));
//   assert0ret(memcmp("", zeros_carr));
  MEMCMP_SELF_EQ(empty_str);
  MEMCMP_SELF_EQ(empty_strarr[0]);
  MEMCMP_SELF_EQ(empty_carr);
  MEMCMP_SELF_EQ(empty_null);
  MEMCMP_SELF_EQ(zeros_carr);

#undef MEMCMP_SELF_EQ
} /* test_strcmp_eq */


void test_strcmp_ne() {
#define MEMCMP_TEST_LT(_lstr, _rstr) \
  /* LT */ assert(memcmp(_lstr, _rstr) < 0); \
  /* GT */ assert(memcmp(_rstr, _lstr) > 0)
// def MEMCMP_TEST_LT

//   MEMCMP_TEST_LT("", "ysyx");
//   MEMCMP_TEST_LT("", "cyhan");

// // 可见字符的比较
//   MEMCMP_TEST_LT(" ", special_chars);
//   MEMCMP_TEST_LT(special_chars, numner_chars);
//   MEMCMP_TEST_LT(numner_chars, uppercase_chars);
//   MEMCMP_TEST_LT(uppercase_chars, lowercase_chars);
//   MEMCMP_TEST_LT(lowercase_chars, "~");
// // 传递性
//   MEMCMP_TEST_LT(" ", "~");

#undef MEMCMP_TEST_LT
} /* test_strcmp_ne */


// 无其他依赖的自动化测试
void test_strcmp() {
//   static char buf[2] = {0};
// // 转义字符
//   for(int i=0; i < escape_onechar_arr_len; i++) {
//     buf[0] = escape_onechar_arr[i][0];
//     buf[1] = '\0';
//     assert_equals_with_ctx(0, memcmp(buf, escape_onechar_arr[i]),
//       printf("ctx: i=%d;\n"
//              "\tbuf   =%s\n"
//              "\tescape=%s\n",
//              i, buf, escape_onechar_arr[i]));
//   }

// // 字符指针
//   const char *p = ascii_chars;
//   for(int i=0; i <= ascii_char_len; i++, p++) {
//     assert_equals_with_ctx(
//       0, memcmp(p, p),
//       printf("ctx: i=%d;\n"
//              "\tp = %s\n",
//              i, p));
//   }
//   p = simple_escape_chars;
//   for(int i=0; i <= simple_escape_chars_len; i++, p++) {
//     assert_equals_with_ctx(
//       0, memcmp(p, p),
//       printf("ctx: i=%d;\n"
//              "\tp = %s\n",
//              i, p));
//   }

// // NE
//   p = ascii_chars;
//   for(int i=0; i < (ascii_char_len-1); i++, p++) {
//     assert(memcmp(p, p+1) < 0);
//     assert(memcmp(p+1, p) > 0);
//   }

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
