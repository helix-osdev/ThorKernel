#include <efi.h>
#include <mm/mm.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <kernel.h>
#include <kstdio.h>
#include <kstring.h>
#include <bootinfo.h>






int kernel_stage1(bootinfo_t *boot_info) {
	bootinfo_t *info = (bootinfo_t *)boot_info;

	uart_config_t cfg = {
		.parity = false,
		.baudrate = 115200,
		.data_bits = 8,
		.stop_bits = 1
	};

	uart_init(&cfg);

	printf("Thor Kernel init\n");

	while(1);
}
