#include <efi.h>
#include <bootinfo.h>


efi_runtime_services_t *RT;


efi_status_t efi_runtime_services_init(bootinfo_t *info) {
	efi_status_t ret = 0;


	if (!info->RT) {
		return EFI_NOT_FOUND;
	}

	RT = info->RT;

	return EFI_SUCCESS;
}

efi_status_t efi_soft_reboot(void) {
	efi_status_t ret = 0;


	ret = RT->reset_system(EfiResetWarm, 0, 0, NULL);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}

efi_status_t efi_hard_reboot(void) {
	efi_status_t ret = 0;


	ret = RT->reset_system(EfiResetCold, 0, 0, NULL);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}

efi_status_t efi_shutdown(void) {
	efi_status_t ret = 0;


	ret = RT->reset_system(EfiResetShutdown, 0, 0, NULL);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}

efi_status_t efi_get_var(char16_t *var, efi_guid_t guid, uint32_t attrib, uint64_t data_size, void *data) {
	efi_status_t ret = 0;


	ret = RT->get_variable(var, &guid, &attrib, data_size, &data);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}

efi_status_t efi_set_var(char16_t *var, efi_guid_t guid, uint32_t attrib, uint64_t data_size, void *data) {
	efi_status_t ret = 0;


	ret = RT->set_variable(var, &guid, attrib, data_size, &data);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}
