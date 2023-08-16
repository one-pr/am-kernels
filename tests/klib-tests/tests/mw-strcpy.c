#include "mem-write.cc"


void test_strcpy() {
  char *pdata = (char *)data;

  for (int i=0; i <= special_chars_len; i++) {
  // 复制越来越少的字符
    const char *src = special_chars + i;
    int str_len = special_chars_len - i;  // 最终为 0
    init_data_seq();

    char *ret = strcpy(pdata, src);

    assert(ret == pdata);
    check_seq(0, str_len, src[0]);    // [0, str_len)
    assert('\0' == pdata[str_len]);   // [str_len] == '\0'
    check_seq(str_len + 1, DATA_MAX_LEN, str_len+2);  // [str_len+1. MAX)
  }
} // test_strcpy


/*
  Type1 内存和字符串的写入函数:
  - memset/memcpy/memmove
  - strcpy/strncpy/strcat
*/
int main() {

  test_strcpy();

	return 0;
}
