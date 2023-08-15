#include "trap.h"

char str[6] = {0};
char s[] = "#####";

int main() {

// -- memcmp
	check(memcmp(memset(str, '#', 5), s, 5) == 0);

	return 0;
}
