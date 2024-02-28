#include <efi.h>
#include <kstring.h>




void strrep(char *s, char a, char b) {
	if (!s) {
		return;
	}

	while(*s != '\0') {
		if (*s == a) {
			*s = b;
		}

		s++;
	}
}
