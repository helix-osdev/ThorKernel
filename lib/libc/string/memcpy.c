#include <efi.h>
#include <kstring.h>




void memcpy(void *dst, void *src, uint64_t len) {
	char *d = (char *)dst;
	char *s = (char *)src;

	
	for (uint64_t i = 0; i < len; i++) {
		d[i] = s[i];
	}
}
