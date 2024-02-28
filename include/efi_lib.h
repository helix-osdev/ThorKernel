#ifndef EFI_LIB_H
#define EFI_LIB_H

#include <efi_api.h>
#include <efi_def.h>
#include <bootinfo.h>


extern efi_runtime_services_t *RT;


efi_status_t efi_runtime_services_init(bootinfo_t *info);
efi_status_t efi_soft_reboot(void);
efi_status_t efi_hard_reboot(void);
efi_status_t efi_shutdown(void);
efi_status_t efi_get_var(char16_t *var, efi_guid_t guid, uint32_t attrib, uint64_t data_size, void *data);
efi_status_t efi_set_var(char16_t *var, efi_guid_t guid, uint32_t attrib, uint64_t data_size, void *data);

#endif
