#include "mem-write.cc"


// 简单的手动测试
void test_strlen_trivial() {
// const string
  assert_equals(0, strlen(""));

  assert_equals(1, strlen("0"));
  assert_equals(1, strlen("1"));
  assert_equals(2, strlen("10"));
  assert_equals(2, strlen("()"));
  assert_equals(2, strlen("[]"));
  assert_equals(2, strlen("{}"));
  assert_equals(2, strlen("<>"));
  assert_equals(2, strlen("''"));
  assert_equals(2, strlen("\"\""));

  assert_equals(4, strlen("ysyx"));
  assert_equals(5, strlen("cyhan"));
  assert_equals(6, strlen("strlen"));
  assert_equals(8, strlen("01234567"));
  assert_equals(10, strlen("0123456789"));
  assert_equals(10, strlen("!@#$%^&*()"));  // <Shift> + <0-9>
  assert_equals(10, strlen("1234567890"));
  assert_equals(12, strlen("Hello World!"));
  assert_equals(16, strlen("0123456789ABCDEF"));
  assert_equals(16, strlen("0123456789abcdef"));
  assert_equals(26, strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
  assert_equals(26, strlen("abcdefghijklmnopqrstuvwxyz"));

// empty str
  assert_equals(0, strlen(""));
  assert_equals(0, strlen(empty_str));
  assert_equals(0, strlen(empty_strarr[0]));
  assert_equals(0, strlen(empty_carr));
  assert_equals(0, strlen(empty_null));
  assert_equals(0, strlen(zeros_carr));

// 常量字符串
  assert_equals(ascii_char_len, strlen(ascii_chars));
  assert_equals(special_chars_len, strlen(special_chars));
  assert_equals(numner_chars_len, strlen(numner_chars));
  assert_equals(uppercase_chars_len, strlen(uppercase_chars));
  assert_equals(lowercase_chars_len, strlen(lowercase_chars));
  assert_equals(simple_escape_chars_len, strlen(simple_escape_chars));
} /* test_strlen_trivial */

// 无其他依赖的自动化测试
void test_strlen() {
// 转义字符
  for(int i=0; i < escape_onechar_arr_len; i++) {
    assert_equals_with_ctx(1, strlen(escape_onechar_arr[i]),
      printf("ctx: i=%d\n", i));
  }

// 字符指针
  const char *p = ascii_chars;
  for(int i=0; i <= ascii_char_len; i++, p++) {
    assert_equals_with_ctx(
      ascii_char_len-i, strlen(p),
      printf("ctx: i=%d; *p=\"%s\"\n", i, p));
  }
  p = simple_escape_chars;
  for(int i=0; i <= simple_escape_chars_len; i++, p++) {
    assert_equals_with_ctx(
      simple_escape_chars_len-i, strlen(p),
      printf("ctx: i=%d; *p=\"%s\"\n", i, p));
  }

} /* test_strlen */

/*
  Type3 内存和字符串的[读取]函数:
  - memcmp
  - strlen/strcmp
*/
int main() {

  test_strlen_trivial();
  test_strlen();

	return 0;
}
