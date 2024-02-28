#include <efi.h>
#include <kstdio.h>





int sprintf(void *buf, char *fmt, ...) {
	int ret = 0;
	va_list args;


	va_start(args, fmt);
	ret = vsprintf(buf, fmt, args);
	va_end(args);

	return ret;
}
