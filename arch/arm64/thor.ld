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
	bss		PT_LOAD;
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

	.page_tables ALIGN(0x1000) (NOLOAD) : AT(ADDR(.page_tables) - KERNEL_VIRT) {
		__page_tables_start = .;
		KEEP(*(.page_tables*));
		__page_tables_end = .;
	} :bss

	. += CONSTANT(MAXPAGESIZE);

	.bss ALIGN(0x1000) (NOLOAD) : AT(ADDR(.bss) - KERNEL_VIRT) {
		__sbss = .;
		*(.bss*)
		*(COMMON)
		__ebss = .;

		__stack_start = .;
		/* 512KB stack */
		. = . + 0x80000;
		__stack_end = .;

	} :bss

	__kernel_end = .;

	/DISCARD/ : {
		*(.note)
		*(.interp*)
		*(.comment)
	}
}
