#include <efi.h>
#include <kstring.h>




int strcmp(char *b, char *a, uint64_t len) {
	efi_status_t ret = 0;

	for (uint64_t i = 0; i < len; i++) {
		if (a[i] > b[i]) {
			return -1;
		} else if (a[i] < b[i]) {
			return -1;
		}
	}

	return 0;
}
