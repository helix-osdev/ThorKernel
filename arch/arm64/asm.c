#include <efi.h>
#include <arch/asm.h>




uint64_t read_esr(void) {
	uint64_t esr = 0;

	__asm__ volatile("mrs %0, esr_el1\n\t"
					 : "=r"(esr)
					 : : "x0");

	return esr;
}
