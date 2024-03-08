.section .text, "x"
.global _start





_start:
	mov x29, xzr
	mov x30, xzr

	// Mask interrupts
	msr DAIFset, #0b1111

	// Preserve boot arguments from Helix
	mov x20, x0
	mov x21, x1
	mov x22, x2
	mov x23, x3

	// Helix will have setup temporary page tables
	// to get us into virtual memory. We'll need to
	// setup new initial page tables :^)
	bl mmu_init

	// Setup stack
	ldr x0, =__stack_end
	mov sp, x0

	// Set vector table
	adr x0, vector_table
	msr vbar_el1, x0

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
