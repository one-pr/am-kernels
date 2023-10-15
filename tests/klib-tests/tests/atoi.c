#include <limits.h>
#include "test-globals.cc"

#define ATOI_TEST(_ref_val, _str_input) \
  tmp_ret_val = atoi(_str_input); \
  assert_equals_with_ctx((_ref_val), \
    tmp_ret_val, \
    printf("\texpr : \"%s\"\n" \
           "\twant = '%d'\n" \
           "\tgot  = '%d'\n", \
            _str_input, (_ref_val), tmp_ret_val))
// ----------------------------------------------

// 带前缀的测试, 不支持负数
#define ATOI_TEST_PREFIX(_ref_val, _str_input) \
  ATOI_TEST(_ref_val, "   " _str_input); \
  ATOI_TEST(_ref_val, "+" _str_input); \
  ATOI_TEST(-1 * (_ref_val), "-" _str_input)
// ----------------------------------------------

// int atoi(const char *nptr);
void test_atoi_const() {
  int tmp_ret_val = 0;

  ATOI_TEST_PREFIX(0, "0");
  ATOI_TEST_PREFIX(1, "1");
  ATOI_TEST_PREFIX(123, "123");
  ATOI_TEST_PREFIX(512, "512");
  ATOI_TEST_PREFIX(1024, "1024");
  ATOI_TEST_PREFIX(INT_MAX, "2147483647");

  ATOI_TEST((INT_MAX),    "-2147483649"); // INT_MIN - 1 => INT_MAX
  ATOI_TEST(INT_MIN,      "-2147483648"); // INT_MIN
  ATOI_TEST(INT_MIN + 1,  "-2147483647"); // INT_MIN + 1
  ATOI_TEST(INT_MAX - 1,  "2147483646");  // INT_MAX - 1
  ATOI_TEST(INT_MAX,      "2147483647");  // INT_MAX
  ATOI_TEST((INT_MIN),    "2147483648");  // INT_MAX + 1 => INT_MIN
  ATOI_TEST(UINT_MAX - 1, "4294967294");  // UINT_MAX - 1
  ATOI_TEST(UINT_MAX,     "4294967295");  // UINT_MAX
  ATOI_TEST(UINT_MAX + 1, "4294967296");  // UINT_MAX + 1

// space prefix
  ATOI_TEST(0,    "   0");
  ATOI_TEST(123,  "   123");
} /* test_atoi_const */


int main() {

  test_atoi_const();

	return 0;
}
