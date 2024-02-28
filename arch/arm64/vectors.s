.section .text, "x"
.global vector_table


.equ ESR_UNKNOWN,		0x00
.equ ESR_SYSCALL_ARM64, 0x15
.equ ESR_SYS_ARM64,		0x18
.equ ESR_IABT_EL0,		0x20
.equ ESR_IABT_EL1,		0x21
.equ ESR_DABT_EL0,		0x24
.equ ESR_DABT_EL1,		0x25
.equ ESR_PC_ALIGN,		0x22
.equ ESR_SP_ALIGN,		0x26




.macro __build_stack_frame
	stp x30, xzr, [sp, #-16]!
	stp x28, x29, [sp, #-16]!
	stp x26, x27, [sp, #-16]!
	stp x24, x25, [sp, #-16]!
	stp x22, x23, [sp, #-16]!
	stp x20, x21, [sp, #-16]!
	stp x18, x19, [sp, #-16]!
	stp x16, x17, [sp, #-16]!
	stp x14, x15, [sp, #-16]!
	stp x12, x13, [sp, #-16]!
	stp x10, x11, [sp, #-16]!
	stp x8, x9, [sp, #-16]!
	stp x6, x7, [sp, #-16]!
	stp x4, x5, [sp, #-16]!
	stp x2, x3, [sp, #-16]!
	stp x0, x1, [sp, #-16]!

	mrs x0, elr_el1
	mrs x1, spsr_el1
	stp x0, x1, [sp, #-16]!	
.endm

.macro __restore_stack_frame
	ldp x0, x1, [sp], #16
	msr spsr_el1, x0
	msr elr_el1, x1

	ldp x0, x1, [sp], #16
	ldp x2, x3, [sp], #16
	ldp x4, x5, [sp], #16
	ldp x6, x7, [sp], #16
	ldp x8, x9, [sp], #16
	ldp x10, x11, [sp], #16
	ldp x12, x13, [sp], #16
	ldp x14, x15, [sp], #16
	ldp x16, x17, [sp], #16
	ldp x18, x19, [sp], #16
	ldp x20, x21, [sp], #16
	ldp x22, x23, [sp], #16
	ldp x24, x25, [sp], #16
	ldp x26, x27, [sp], #16
	ldp x28, x29, [sp], #16
	ldp x30, xzr, [sp], #16
.endm




.balign 2048
vector_table:
	// ELx AARCH64 with SP0
	.balign 0x80
	b __sync_sp0_current_el

	.balign 0x80
	b __irq_sp0_current_el

	.balign 0x80
	b __fiq_sp0_current_el

	.balign 0x80
	b __serror_sp0_current_el



	// ELx AARCH64
	.balign 0x80
	b __sync_spx_current_el

	.balign 0x80
	b __irq_spx_current_el

	.balign 0x80
	b __fiq_spx_current_el

	.balign 0x80
	b __serror_spx_current_el



	// EL0 AARCH64 with SP0
	.balign 0x80
	b __sync_spx_el0

	.balign 0x80
	b __irq_spx_el0

	.balign 0x80
	b __fiq_spx_el0

	.balign 0x80
	b __serror_spx_el0



	// EL0 AARCH32 (unused)
	.balign 0x80
	b .

	.balign 0x80
	b .

	.balign 0x80
	b .

	.balign 0x80
	b .




__sync_sp0_current_el:
	b __el_inval

__irq_sp0_current_el:
	b __el_inval

__fiq_sp0_current_el:
	b __el_inval

__serror_sp0_current_el:
	b __el_inval





__sync_spx_current_el:
	__build_stack_frame

	mrs x20, esr_el1
	lsr x21, x20, #26

	cmp x21, #ESR_UNKNOWN
	beq __el_inval

	cmp x21, #ESR_DABT_EL1
	beq __do_data_abort

	cmp x21, #ESR_PC_ALIGN
	beq __do_pc_align

	cmp x21, #ESR_SP_ALIGN
	beq __do_sp_align

	cmp x21, #ESR_SYS_ARM64
	beq __do_undef

	cmp x21, #0x3c
	beq __do_dbg

	b __el_inval



__do_pc_align:
	b __el_inval

__do_sp_align:
	b __el_inval

__do_data_abort:
	b __el_inval

__do_undef:
	mov x0, sp
	mrs x1, far_el1
	b undef_handler

__do_dbg:
	mov x0, sp
	mrs x1, far_el1
	b dbg_handler




__irq_spx_current_el:
	b __el_inval

__fiq_spx_current_el:
	b __el_inval

__serror_spx_current_el:
	b __el_inval






__sync_spx_el0:
	__build_stack_frame

	mrs x20, esr_el1
	lsr x21, x20, #26

	cmp x21, #ESR_SYSCALL_ARM64
	beq __do_syscall_el0

	__restore_stack_frame
	eret

__do_syscall_el0:
	b .







__irq_spx_el0:
	b __el_inval

__fiq_spx_el0:
	b __el_inval

__serror_spx_el0:
	b __el_inval




__el_inval:
	mov x0, sp
	mov x1, x21
	mrs x2, far_el1
	b el_abort_handler
