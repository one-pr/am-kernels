#include "trap.h"

char *s[] = {
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	", World!\n",
	"Hello, World!\n",
	"#####"
};

char str1[] = "Hello";
char str[20];

int main() {
// -- strcmp
	check(strcmp(s[0], s[2]) == 0);
	check(strcmp(s[0], s[1]) < 0);
	check(strcmp(s[0] + 1, s[1] + 1) < 0);
	check(strcmp(s[0] + 2, s[1] + 2) < 0);
	check(strcmp(s[0] + 3, s[1] + 3) < 0);

// -- strcpy
  strcpy(str, s[5]);
  check(str[0] == '#');
  check(str[4] == '#');
  check(str[5] == '\0');
  check(strcmp(str, s[5]) == 0);
  strcpy(str+5, s[5]);
  check(str[5] == '#');
  strcpy(str, s[5]);
  check(str[4] == '#');
  check(str[5] == '\0'); // check if copy NUL

// -- strcat
	check(strcmp( strcat(strcpy(str, str1), s[3]), s[4]) == 0);

// -- memset
  memset(str, '\0', 20);
  check(str[0] == 0);
  check(str[5] == 0);
  check(str[6] == 0);
  memset(str, '#', 5);
  check(str[0] == '#');
  check(str[4] == '#');
  check(str[5] == 0);
  check(strcmp(str, s[5]) == 0);

// -- memcmp
	check(memcmp(memset(str, '#', 5), s[5], 5) == 0);

	return 0;
}
