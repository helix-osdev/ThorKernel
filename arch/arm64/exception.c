#include <efi.h>
#include <kstdio.h>
#include <arch/context.h>







void undef_handler(context_t *ctx, uint64_t far_el1) {
	printf(">>> Undefined instruction @ %x! <<<\n\n", far_el1);

	while(1);
}

void el_abort_handler(context_t *ctx, uint64_t esr) {
	printf("\033[1;31m>>> KERNEL PANIC <<<\033[0m\n\n");

	switch(esr) {
		case ESR_IABT_EL1: {
			printf("Instruction abort taken w/o change in exception level!\n");
			break;
		}

		default: {
			printf("Unknown exception! (ESR: %x)\n", esr);
			break;
		}
	}

	while(1);
}

void dbg_handler(context_t *ctx, uint64_t far_el1) {
	printf("\033[1;33m>>> BREAKPOINT <<<\033[0m\n\n");

	while(1);
}
