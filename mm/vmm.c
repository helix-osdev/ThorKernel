#include <efi.h>
#include <mm/vmm.h>
#include <mm/pmm.h>
#include <kstdio.h>
#include <kstring.h>





efi_memory_descriptor_t *for_each_desc(efi_memory_map_t *m, uint64_t index) {
	efi_memory_descriptor_t *e = NULL;

	e = ((efi_memory_descriptor_t *)(uint8_t *)m->map + index * m->desc_size);

	return e;
}


