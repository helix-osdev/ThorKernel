#include <efi.h>
#include <kstring.h>




void memset(void *dst, char ch, uint64_t len) {
	char *d = (char *)dst;

	for (uint64_t i = 0; i < len; i++) {
		d[i] = ch;
	}
}
