#ifndef BOOTINFO_H
#define BOOTINFO_H

#include <efi.h>
#include <mm/vmm.h>


typedef struct {
	efi_memory_map_t		*map;
	efi_runtime_services_t	*RT;
	efi_rsdp_t				*rsdp;

	uint64_t				kernel_base;
	uint64_t				kernel_size;
	uint64_t				stack_base;
} __attribute__((packed)) bootinfo_t;

#endif
