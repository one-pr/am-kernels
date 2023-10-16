#include <limits.h>
#include "test-globals.cc"

#define CTYPE_H_TEST(__func, __ref_val, __input) \
  tmp_ret_val = __func((__input)); \
  assert_equals_with_ctx((__ref_val), \
    tmp_ret_val, \
    printf("\tFUNC: %s( %s(%d) )\n" \
           "\twant = '%s'(%d)\n" \
           "\tgot  = '%c'(%d)\n", \
           TOSTRING(__func), #__input, (__input), \
           #__ref_val, (__ref_val), \
           tmp_ret_val, tmp_ret_val))
// ----------------------------------------------


// 非 ASCII 范围的输入
#define CTYPE_CHAR_CLASSIFY_BAD_RANGE(__func) \
  CTYPE_H_TEST(__func, false, 256); \
  CTYPE_H_TEST(__func, false, 1024); \
  CTYPE_H_TEST(__func, false, 20231016); \
  CTYPE_H_TEST(__func, false, INT_MAX); \
  CTYPE_H_TEST(__func, false, INT_MIN); \
  CTYPE_H_TEST(__func, false, INT_MIN+1); \
  CTYPE_H_TEST(__func, false, -4096); \
  CTYPE_H_TEST(__func, false, -1)
// CTYPE_CHAR_CLASSIFY_BAD_RANGE

void test_ctypes_char_classification() {
  int tmp_ret_val = INT_MIN;

#define CTYPE_H_TEST_isalnum(__ref_val, __expr) \
  CTYPE_H_TEST(isalnum, __ref_val, __expr)
/* int isalnum(int ch) */
  CTYPE_H_TEST_isalnum(true, '0');
  CTYPE_H_TEST_isalnum(true, '9');
  CTYPE_H_TEST_isalnum(true, 'a');
  CTYPE_H_TEST_isalnum(true, 'z');
  CTYPE_H_TEST_isalnum(true, 'A');
  CTYPE_H_TEST_isalnum(true, 'Z');
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || ('0' <= i && i <= '9')
      || ('A' <= i && i <= 'Z')
      || ('a' <= i && i <= 'z')
      ;
    CTYPE_H_TEST(isalnum, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(isalnum);

/* int isalpha(int ch) */
  CTYPE_H_TEST(isalpha, false, '0');
  CTYPE_H_TEST(isalpha, false, '9');
  CTYPE_H_TEST(isalpha, true, 'a');
  CTYPE_H_TEST(isalpha, true, 'z');
  CTYPE_H_TEST(isalpha, true, 'A');
  CTYPE_H_TEST(isalpha, true, 'Z');
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || ('A' <= i && i <= 'Z')
      || ('a' <= i && i <= 'z')
      ;
    CTYPE_H_TEST(isalpha, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(isalpha);

/* int isblank(int ch) */
  CTYPE_H_TEST(isblank, true, ' ');
  CTYPE_H_TEST(isblank, true, '\t');
  CTYPE_H_TEST(isblank, false, '\n');
  CTYPE_H_TEST(isblank, false, '\0');
  for (int i = '\t'+1; i <= '\r'; i++) {
    CTYPE_H_TEST(isblank, false, i);
  }
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || (' ' == i)
      || ('\t' == i)
      ;
    CTYPE_H_TEST(isblank, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(isblank);

/* int isdigit(int ch) */
  CTYPE_H_TEST(isdigit, true, '0');
  CTYPE_H_TEST(isdigit, true, '9');
  CTYPE_H_TEST(isdigit, false, 'a');
  CTYPE_H_TEST(isdigit, false, 'z');
  CTYPE_H_TEST(isdigit, false, 'A');
  CTYPE_H_TEST(isdigit, false, 'Z');
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || ('0' <= i && i <= '9')
      ;
    CTYPE_H_TEST(isdigit, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(isdigit);

/* int islower(int ch) */
  CTYPE_H_TEST(islower, false, '0');
  CTYPE_H_TEST(islower, false, '9');
  CTYPE_H_TEST(islower, true, 'a');
  CTYPE_H_TEST(islower, true, 'z');
  CTYPE_H_TEST(islower, false, 'A');
  CTYPE_H_TEST(islower, false, 'Z');
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || ('a' <= i && i <= 'z')
      ;
    CTYPE_H_TEST(islower, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(islower);

/* int isspace(int ch) */
  CTYPE_H_TEST(isspace, true, ' ');
  CTYPE_H_TEST(isspace, true, '\t');
  CTYPE_H_TEST(isspace, true, '\n');
  CTYPE_H_TEST(isspace, false, '\0');
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || (' ' == i)
      || ('\t' <= i && i <= '\r')
      ;
    CTYPE_H_TEST(isspace, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(isspace);

/* int isupper(int ch) */
  CTYPE_H_TEST(isupper, false, '0');
  CTYPE_H_TEST(isupper, false, '9');
  CTYPE_H_TEST(isupper, false, 'a');
  CTYPE_H_TEST(isupper, false, 'z');
  CTYPE_H_TEST(isupper, true, 'A');
  CTYPE_H_TEST(isupper, true, 'Z');
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || ('A' <= i && i <= 'Z')
      ;
    CTYPE_H_TEST(isupper, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(isupper);

/* int isxdigit(int ch) */
  CTYPE_H_TEST(isxdigit, true, '0');
  CTYPE_H_TEST(isxdigit, true, '9');
  CTYPE_H_TEST(isxdigit, true, 'a');
  CTYPE_H_TEST(isxdigit, true, 'f');
  CTYPE_H_TEST(isxdigit, false, 'z');
  CTYPE_H_TEST(isxdigit, true, 'A');
  CTYPE_H_TEST(isxdigit, true, 'F');
  CTYPE_H_TEST(isxdigit, false, 'Z');
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    bool is_good = false
      || ('0' <= i && i <= '9')
      || ('A' <= i && i <= 'F')
      || ('a' <= i && i <= 'f')
      ;
    CTYPE_H_TEST(isxdigit, is_good, i);
  }
  CTYPE_CHAR_CLASSIFY_BAD_RANGE(isxdigit);

} /* test_ctypes_char_classification */


void test_ctypes_char_mapping() {
  int tmp_ret_val = INT_MIN;

#define TOLOWER_SAME_TEST(__input_char) \
  CTYPE_H_TEST(tolower, __input_char, __input_char)
/* int tolower(int ch) */
  TOLOWER_SAME_TEST('0');
  TOLOWER_SAME_TEST('9');
  TOLOWER_SAME_TEST('a');
  TOLOWER_SAME_TEST('z');
  CTYPE_H_TEST(tolower, 'a', 'A');
  CTYPE_H_TEST(tolower, 'z', 'Z');


#define TOUPPER_SAME_TEST(__input_char) \
  CTYPE_H_TEST(toupper, __input_char, __input_char)
/* int toupper(int ch) */
  TOUPPER_SAME_TEST('0');
  TOUPPER_SAME_TEST('9');
  TOUPPER_SAME_TEST('A');
  TOUPPER_SAME_TEST('Z');
  CTYPE_H_TEST(toupper, 'A', 'a');
  CTYPE_H_TEST(toupper, 'Z', 'z');

} /* test_ctypes_char_mapping */

int main() {

  test_ctypes_char_classification();
  test_ctypes_char_mapping();

	return 0;
}
