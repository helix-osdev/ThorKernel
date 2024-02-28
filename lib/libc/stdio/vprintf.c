#include <efi.h>
#include <kstdio.h>
#include <kstring.h>





int vprintf(char *fmt, va_list ap) {
	char buf[1024];


	while(*fmt != '\0') {
		if (*fmt == '%') {
			fmt++;

			switch(*fmt) {
				case 'c': {
					buf[0] = va_arg(ap, int);
					buf[1] = '\0';

					puts(buf);
					fmt++;
					break;
				}

				case 's': {
					char *_s = va_arg(ap, char*);

					puts(_s);
					fmt++;
					break;
				}

				case 'i':
				case 'd': {
					int32_t _d = va_arg(ap, int32_t);

					itoa(_d, buf, 10);
					puts(buf);
					fmt++;
					break;			  
				}

				case 'x': {
					uint64_t _x = va_arg(ap, uint64_t);

					itoa(_x, buf, 16);
					puts(buf);
					fmt++;
					break;
				}

				case 'u': {
					uint64_t _u = va_arg(ap, uint64_t);

					itoa(_u, buf, 10);
					puts(buf);
					fmt++;
					break;
				}

				case 'b': {
					uint64_t _b = va_arg(ap, uint64_t);

					itoa(_b, buf, 2);
					puts(buf);
					fmt++;
					break;
				}

				case 'o': {
					uint64_t _o = va_arg(ap, uint64_t);

					itoa(_o, buf, 8);
					puts(buf);
					fmt++;
					break;
				}

				default: {
					fmt++;
					break;
				
				}
			}
		}

		buf[0] = *fmt;
		buf[1] = '\0';

		puts(buf);
		fmt++;
	}

	return 0;
}


