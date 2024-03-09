#include <efi.h>
#include <mm/mm.h>
#include <kstdio.h>
#include <kstring.h>
#include <kstdlib.h>





efi_memory_descriptor_t *for_each_desc(efi_memory_map_t *m, uint64_t idx) {
	efi_memory_descriptor_t *md = NULL;

	md = ((efi_memory_descriptor_t *)((uint64_t)m->map + (idx * m->desc_size)));

	return md;
}
