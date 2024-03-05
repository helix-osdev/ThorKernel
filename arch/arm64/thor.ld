OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)



KERNEL_VIRT = 0xffff000000000000;
KERNEL_PHYS = 0x40300000;


PHDRS
{	
	text    PT_LOAD;
	data	PT_LOAD;
    rodata  PT_LOAD;
}

SECTIONS
{
	. = KERNEL_VIRT;

	/* This will ensure the final executable's physical
	 * address will match it' virtual memory region
	 */
	. = . + KERNEL_PHYS;

	__kernel_start = .;

	.text ALIGN(0x1000) : AT(ADDR(.text) - KERNEL_VIRT) {
		__stext = .;
		*(.text*)
		*(.eh_frame)
		__etext = .;
	} :text

	. += CONSTANT(MAXPAGESIZE);

	.data ALIGN(0x1000) : AT(ADDR(.data) - KERNEL_VIRT) {
		__sdata = .;
		*(.data*)
		*(.got*)
		__edata = .;
	} :data

	. += CONSTANT(MAXPAGESIZE);

	.rodata ALIGN(0x1000) : AT(ADDR(.rodata) - KERNEL_VIRT) {
		__srodata = .;
		*(.rodata*)
		__erodata = .;
	} :rodata

	. += CONSTANT(MAXPAGESIZE);

	.bss ALIGN(0x1000) (NOLOAD) : AT(ADDR(.bss) - KERNEL_VIRT) {
		__sbss = .;
		*(.bss*)
		*(COMMON)
		__ebss = .;

		__heap_start = .;
		/* 1MB heap */
		. = . + 0x100000;
		__heap_end = .;

		__stack_start = .;
		/* 1MB stack */
		. = . + 0x100000;
		__stack_end = .;

		__page_tables_start = .;
		/* 1MB page tables */
		. = . + 0x100000;
		__page_tables_end = .;
	} :data

	__kernel_end = .;

	/DISCARD/ : {
		*(.note)
		*(.interp*)
		*(.comment)
	}
}
