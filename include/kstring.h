#ifndef KSTRING_H
#define KSTRING_H

#include <efi.h>




void memset(void *dst, char ch, uint64_t len);
void memcpy(void *dst, void *src, uint64_t len);
int memcmp(void *b, void *a, uint64_t length);
int32_t guidcmp(efi_guid_t *g1, efi_guid_t *g2);
int strcmp(char *b, char *a, uint64_t len);
uint64_t strlen(char *s);
void strcpy(char *dst, char *s);
void strrev(char *s, uint64_t length);
void strrep(char *s, char a, char b);
char *itoa(int num, char *buf, int base);

#endif
