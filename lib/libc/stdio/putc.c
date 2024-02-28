#include <efi.h>
#include <kstdio.h>
#include <devices/uart.h>





void putc(char c) {
	uart_putc(c);
}
