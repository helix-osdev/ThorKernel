#include <efi.h>
#include <kstring.h>




void strrev(char *s, uint64_t length) {
	uint64_t start = 0, end = length - 1;

	while(start < end) {
		char tmp = s[start];

		s[start] = s[end];
		s[end] = tmp;

		start++;
		end--;
	}
}
