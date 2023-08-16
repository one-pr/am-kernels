#include "mem-write.cc"


static const char *empty_str = "";
static const char *empty_strarr[1] = { "" };
static char empty_carr[1] = { 0 };
static char empty_null[1] = { '\0' };
//
static char zeros_carr[8] = { 0 };


// 简单的手动测试
void test_strlen_trivial() {
// const string
  assert(0 == strlen(""));
  assert(1 == strlen("0"));
  assert(1 == strlen("1"));
  assert(2 == strlen("10"));
  assert(2 == strlen("()"));
  assert(2 == strlen("[]"));
  assert(2 == strlen("{}"));
  assert(2 == strlen("<>"));
  assert(2 == strlen("''"));
  assert(2 == strlen("\"\""));
  assert(4 == strlen("ysyx"));
  assert(5 == strlen("cyhan"));
  assert(6 == strlen("strlen"));
  assert(8 == strlen("01234567"));
  assert(10 == strlen("0123456789"));
  assert(10 == strlen("!@#$%^&*()"));  // <Shift> + <0-9>
  assert(10 == strlen("1234567890"));
  assert(12 == strlen("Hello World!"));
  assert(16 == strlen("0123456789ABCDEF"));
  assert(16 == strlen("0123456789abcdef"));
  assert(26 == strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
  assert(26 == strlen("abcdefghijklmnopqrstuvwxyz"));

// empty str
  assert(0 == strlen(""));
  assert(0 == strlen(empty_str));
  assert(0 == strlen(empty_strarr[0]));
  assert(0 == strlen(empty_carr));
  assert(0 == strlen(empty_null));
  assert(0 == strlen(zeros_carr));

// 常量字符串
  assert(ascii_char_len == strlen(ascii_chars));
  assert(special_chars_len == strlen(special_chars));
  assert(numner_chars_len == strlen(numner_chars));
  assert(uppercase_chars_len == strlen(uppercase_chars));
  assert(lowercase_chars_len == strlen(lowercase_chars));
} /* test_strlen_trivial */

// 无其他依赖的自动化测试
void test_strlen() {

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
