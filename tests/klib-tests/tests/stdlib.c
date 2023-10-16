#include <limits.h>
#include "test-globals.cc"

#define STDLIB_TEST_WARP(_eval_val, _ref_val) \
  assert_equals_with_ctx((_ref_val), \
    _eval_val, \
    printf("\tFUNC: %s\n" \
           "\twant = '%d'\n" \
           "\tgot  = '%d'\n", \
            #_eval_val, \
            (_ref_val), \
            _eval_val))
// ----------------------------------------------
#define ATOI_TEST(_ref_val, _str_input) \
  STDLIB_TEST_WARP(atoi((_str_input)), _ref_val)

// 带前缀的测试, 不支持负数
#define ATOI_TEST_PREFIX(_ref_val, _str_input) \
  ATOI_TEST(_ref_val, "   " _str_input); \
  ATOI_TEST(_ref_val, "+" _str_input); \
  ATOI_TEST(-1 * (_ref_val), "-" _str_input)
// ----------------------------------------------

// int atoi(const char *nptr);
void test_atoi_const() {
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

void test_strtoi_const() {
#define strtol_TEST(_ref_val, _str_input) \
  STDLIB_TEST_WARP(strtol(_str_input, NULL, 10), _ref_val)
// 带前缀的测试, 不支持负数
#define strtol_TEST_PREFIX(_ref_val, _str_input) \
  strtol_TEST(_ref_val,       "  +" _str_input); \
  strtol_TEST(-1*(_ref_val),  "  -" _str_input)
// ----------------------------------------------

  strtol_TEST(0, "0");
  strtol_TEST(1, "1");
  strtol_TEST(123, "123");
  strtol_TEST(512, "512");
  strtol_TEST(1024, "1024");
  strtol_TEST(INT_MAX, "2147483647");

  strtol_TEST(-1, "-1");
  // strtol_TEST(-100, "-100"); // FIXME
}

#define ABS_TEST(_ref_val, _input) \
  STDLIB_TEST_WARP(  abs((_input)), _ref_val)
#define LABS_TEST(_ref_val, _input) \
  STDLIB_TEST_WARP( labs((_input)), _ref_val)
#define LLABS_TEST(_ref_val, _input) \
  STDLIB_TEST_WARP(llabs((_input)), _ref_val)

#define _ABS_TEST_POS3(_ref_val, _input) \
  ABS_TEST(_ref_val, _input); \
  LABS_TEST(_ref_val, _input); \
  LLABS_TEST(_ref_val, _input)
// 同时测试正数、负数
#define ALL3_ABS_TEST(_ref_val, _input) \
  _ABS_TEST_POS3(_ref_val, _input); \
  _ABS_TEST_POS3(_ref_val, (-1*(_input)))

void test_abs() {
  ALL3_ABS_TEST(0, 0);
  ALL3_ABS_TEST(1, 1);
  ALL3_ABS_TEST(8, 8);
  ALL3_ABS_TEST(16, 16);
  ALL3_ABS_TEST(1024, 1024);
  ALL3_ABS_TEST(INT_MAX/2, INT_MAX/2);
  ALL3_ABS_TEST(INT_MAX, INT_MAX);
  ALL3_ABS_TEST(INT_MAX, INT_MIN+1);

// ---- int
  // (int)INT_MIN 取负溢出
  ABS_TEST(INT_MIN, INT_MIN);

// ---- long
  LABS_TEST(-1UL * INT_MIN, INT_MIN); // long 可正常表示 -INT_MIN
  // (long)LONG_MIN 取负溢出
  LABS_TEST(LONG_MIN, LONG_MIN);
  LABS_TEST(LONG_MAX, LONG_MIN+1);
  LABS_TEST(LONG_MAX, LONG_MAX);

// ---- long long
  LLABS_TEST(-1UL * INT_MIN, INT_MIN); // long long 也可正常表示 -INT_MIN
  LLABS_TEST(-1ULL * LONG_MIN, LONG_MIN); // long long 可正常表示 -LONG_MIN
  LLABS_TEST(LONG_MAX, LONG_MIN+1);
  LLABS_TEST(LONG_MAX, LONG_MAX);
  // (long long)LLONG_MIN 取负溢出
  LLABS_TEST(LLONG_MIN, LLONG_MIN);
  LLABS_TEST(LLONG_MAX, LLONG_MIN+1);
  LLABS_TEST(LLONG_MAX, LLONG_MAX);

} /* test_abs */


int main() {

  test_atoi_const();
  test_strtoi_const();

  test_abs();

	return 0;
}
