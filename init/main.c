#include <efi.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <kernel.h>
#include <kstdio.h>
#include <kstring.h>
#include <bootinfo.h>






int kernel_stage1(bootinfo_t *info) {
	bootinfo_t *b = (bootinfo_t *)info;

	uart_config_t cfg = {
		.parity = false,
		.baudrate = 115200,
		.data_bits = 8,
		.stop_bits = 1
	};

	//efi_runtime_services_init(b);
	uart_init(&cfg);

	printf(">> Thor Kernel <<\n");

	//efi_shutdown();
	while(1);
}
