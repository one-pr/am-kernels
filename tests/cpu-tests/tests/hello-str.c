#include "trap.h"
#include <limits.h>

char buf[128];

int main() {
  int count = -1;

// ---- 无格式化符
  count = sprintf(buf, "");
  check(strcmp(buf, "") == 0);
  check(0 == count);

  count = sprintf(buf, "Hello world!\n");
  check(strcmp(buf, "Hello world!\n") == 0);
  check(13 == count);

  count = sprintf(buf, "\0");
  check(strcmp(buf, "") == 0);
  check(0 == count);

// ---- %%
  count = sprintf(buf, "%%");
  check(strcmp(buf, "%") == 0);
  check(1 == count);

// ---- %s
  count = sprintf(buf, "%s", "");
  check(strcmp(buf, "") == 0);
  check(0 == count);

  count = sprintf(buf, "%s", NULL);
  check(strcmp(buf, "(null)") == 0);
  check(6 == count);

  count = sprintf(buf, "%s", "Hello world!\n");
  check(strcmp(buf, "Hello world!\n") == 0);
  check(13 == count);

// ---- %d
  count = sprintf(buf, "%d", 1);
  check(strcmp(buf, "1") == 0);
  check(1 == count);

  count = sprintf(buf, "%d", INT_MAX);
  check(strcmp(buf, "2147483647") == 0);
  check(10 == count);
  count = sprintf(buf, "%d", INT_MIN+1);
  check(strcmp(buf, "-2147483647") == 0);
  check(11 == count);
  count = sprintf(buf, "%d", INT_MIN);
  check(strcmp(buf, "-2147483648") == 0);
  check(11 == count);

  count = sprintf(buf, "%d", -1);
  check(strcmp(buf, "-1") == 0);
  check(2 == count);

  count = sprintf(buf, "%d + %d = %d\n", 1, 1, 2);
  check(strcmp(buf, "1 + 1 = 2\n") == 0);
  check(10 == count);

  count = sprintf(buf, "%d + %d = %d\n", 2, 10, 12);
  check(strcmp(buf, "2 + 10 = 12\n") == 0);
  check(12 == count);

  return 0;
}
