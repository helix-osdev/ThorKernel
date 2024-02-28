#include <efi.h>
#include <kstdio.h>
#include <devices/uart.h>





void puts(char *s) {
	uart_puts(s);
}
