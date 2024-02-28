#include <efi.h>
#include <kstdio.h>



int printf(char *fmt, ...) {
	int ret = 0;
	va_list args;

	va_start(args, fmt);
	ret = vprintf(fmt, args);
	va_end(args);

	return ret;
}
