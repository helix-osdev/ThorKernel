#include <efi.h>
#include <kstring.h>




void strcpy(char *dst, char *s) {
	while(*s) {
		*dst = *s;

		s++;
		dst++;
	}
}
