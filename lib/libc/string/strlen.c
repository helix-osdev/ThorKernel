#include <efi.h>
#include <kstring.h>





uint64_t strlen(char *s) {
	uint64_t size = 0;

	while(*s != '\0') {
		size++;
		s++;
	}

	return size;
}
