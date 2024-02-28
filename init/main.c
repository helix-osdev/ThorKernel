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

	// This should cause a fault since the region is R/O
	// but still is accessable... wtf QEMU!!!
	uint64_t *p = (uint64_t *)0xffff000040000000;
	p[0] = 0x41414141;

	//efi_shutdown();
	while(1);
}
