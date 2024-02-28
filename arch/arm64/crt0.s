.section .text, "x"
.global _start





_start:
	mov x29, xzr
	mov x30, xzr

	// Preserve boot arguments from Helix
	mov x20, x0
	mov x21, x1
	mov x22, x2
	mov x23, x3

	// Mask interrupts
	msr DAIFset, #0b1111

	// Set vector table
	adr x0, vector_table
	msr vbar_el1, x0

	// Setup initial stack space
	ldr x0, =__sstack
	mov sp, x0

	// Now that we're in virtual memory we need to
	// setup new page tables and discard the ones
	// used by Helix
	bl mmu_init

	// Restore boot arguments
	mov x0, x20
	mov x1, x21
	mov x2, x22
	mov x3, x23

	// Branch to main routine
	b kernel_stage1

halt:
	wfi
	b halt
