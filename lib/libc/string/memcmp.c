#include <efi.h>
#include <kstring.h>





int memcmp(void *b, void *a, uint64_t length) {
	uint8_t *_a = (uint8_t *)a;
	uint8_t *_b = (uint8_t *)b;

	for (uint64_t i = 0; i < length; i++) {
		if (_a[i] > _b[i]) {
			return -1;
		} else if (_a[i] < _b[i]) {
			return -1;
		}
	}

	return 0;
}
