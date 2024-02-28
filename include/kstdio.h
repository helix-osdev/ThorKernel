#ifndef KSTDIO_H
#define KSTDIO_H

#include <efi.h>
#include <devices/uart.h>







void putc(char c);
void puts(char *s);
int printf(char *fmt, ...);
int sprintf(void *buf, char *fmt, ...);
int vsprintf(void *buf, char *fmt, va_list ap);
int vprintf(char *fmt, va_list ap);

#endif
