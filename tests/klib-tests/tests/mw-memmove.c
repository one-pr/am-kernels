#include "mem-write.cc"


void test_memmove() {
  // putstr("[test_memmove] start\n");
  // 要移动的区间长度
  for (int len = 0; len <= DATA_MAX_LEN; len++) {
    init_data_seq();
    check_seq(0, DATA_MAX_LEN, 1);  // 1..N

    /* 完全相交：do-nothing
        start  end
        ┌──────O
        └──────O───────────────────────┘
        data   +len                    +MAX_LEN
    */
    init_data_seq();
    memmove(data, data, len);
    check_seq(0, DATA_MAX_LEN, 1);  // 1..N

    /* 完全不相交：退化为 memcpy
               start  end
               ┌──────O
        └──────O───────────────────────┘
        data   +len                    +MAX_LEN
    */
    int start = len;  // 确保完全不相交
    int end = start + len;
    while (end <= DATA_MAX_LEN) {
      init_data_seq();
      memmove(data+start, data, len);

      check_seq(0, start, 1);
      check_seq(start, end, 1);
      check_seq(len, start, len + 1);
      check_seq(end, DATA_MAX_LEN, end + 1);

      start++;
      end = start + len;
    }

    /* 确保相交
              start           end
              ┌───────────────O
          └────────────O────────────────────┘
          data         +len                 +MAX_LEN
    */
    start = 1;
    end = start + len;
    while (start < len) {  // 确保一定相交
      init_data_seq();
      memmove(data+start, data, len);

      check_seq(0, start, 1);
      check_seq(start, end, 1);
      check_seq(end, DATA_MAX_LEN, end + 1);
      start++;
      end = start + len;
    }
  }
  // putstr("[test_memmove] END\n");
} // test_memmove


/*
  Type1 内存和字符串的写入函数:
  - memset/memcpy/memmove
  - strcpy/strncpy/strcat
*/
int main() {

  test_memmove();

	return 0;
}
