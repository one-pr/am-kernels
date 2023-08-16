#include "mem-write.cc"


void test_strcat() {
  char *pdata = (char *)data;

// TODO: 从中间开始复制
  for (int i=0; i <= special_chars_len; i++) {
  // 复制越来越少的字符
    const char *src = special_chars + i;
    int str_len = special_chars_len - i;  // 最终为 0
  // ---- 未使用部分为全 0
    clear_data();
    char *ret = strcat(pdata, src);

    assert(ret == pdata);
    check_seq(0, str_len, src[0]);    // [0, str_len)
    check_eq(str_len, DATA_MAX_LEN, 0);  // [str_len,  MAX)

  // ---- 未使用部分为正常
    init_data_seq();
    pdata[0] = '\0';  // 字符串清零
    ret = strcat(pdata, src);

    assert(ret == pdata);
    check_seq(0, str_len, src[0]);    // [0, str_len)
    check_eq(str_len, str_len+1, 0);  // [str_len] == '\0'
    check_seq(str_len+1, DATA_MAX_LEN, str_len+2);  // [str_len+1. MAX)
  }
} // test_strcat


/*
  Type1 内存和字符串的写入函数:
  - memset/memcpy/memmove
  - strcpy/strncpy/strcat
*/
int main() {

  test_strcat();

	return 0;
}
