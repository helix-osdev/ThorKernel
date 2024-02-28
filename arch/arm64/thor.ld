OUTPUT_FORMAT("elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)




KERNEL_VIRT = 0xffff000040300000;


/* NOTE:
 * Don't place 'PHDRS' in text program header. This
 * fucks up the address alignment and Helix can't
 * allocate pages to this address
 */
PHDRS
{	
	text    PT_LOAD;
	data	PT_LOAD;
    rodata  PT_LOAD;
}



SECTIONS
{
	. = KERNEL_VIRT;

	__kernel_start = .;

	.text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VIRT) {
		__stext = .;
		*(.text*)
		__etext = .;
	} :text

	.data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VIRT) {
		__sdata = .;
		*(.data*)
		__edata = .;
	} :data

	.rodata ALIGN(4K) : AT(ADDR(.rodata) - KERNEL_VIRT) {
		__srodata = .;
		*(.rodata*)
		__erodata = .;
	} :rodata

	.bss ALIGN(4K) : AT(ADDR(.bss) - KERNEL_VIRT) {
		__sbss = .;
		*(.bss*)
		*(COMMON)
		__ebss = .;

		__sstack = .;
		. += 524288;
		__estack = .;

		__page_tables_start = .;
		KEEP(*(.bss.page_tables));
		__page_tables_end = .;
	} :data

	__kernel_end = .;

	/DISCARD/ : {
		*(.note)
		*(.interp*)
		*(.comment)
		*(.eh_frame)
		*(.dynamic)
		*(.dynstr)
		*(.dynsym)
	}
}
