#ifndef MM_H
#define MM_H

#include <efi.h>


typedef struct {
	uint64_t 				max_entries;
    uint64_t 				map_size;
    uint64_t 				map_key;
    uint64_t 				desc_size;
    uint32_t 				desc_version;
    efi_memory_descriptor_t *map;
} efi_memory_map_t;





efi_memory_descriptor_t *for_each_desc(efi_memory_map_t *m, uint64_t idx);

#endif
