.section .text,"x"
.global __inval_tlb_all
.global __inval_icache_all

.global __flush_dcache_all
.global __inval_dcache_all



__inval_tlb_all:
	stp x29, x30, [sp, #-16]!

	dsb sy
	tlbi vmalle1
	dsb ish
	dmb sy
	isb

	ldp x29, x30, [sp], #16
	ret

__inval_icache_all:
	stp x29, x30, [sp, #-16]!

	dsb sy
	ic iallu
	dsb sy
	isb

	ldp x29, x30, [sp], #16
	ret


// This was pulled from:
// https://github.com/cassebas/Raspberry-Pi-Multicore/blob/experiment/xRTOS/invalidate_cache.S
//
// Because this shit was daunting
__flush_dcache_all:
	mov x0, #0
	b __dcache_all

__inval_dcache_all:
	mov x0, #1
	b __dcache_all

__dcache_level:
	lsl	x12, x0, #1
	msr	csselr_el1, x12
	isb
	mrs	x6, ccsidr_el1
	and	x2, x6, #7
	add	x2, x2, #4
	mov	x3, #0x3ff
	and	x3, x3, x6, lsr #3
	clz	w5, w3
	mov	x4, #0x7fff
	and	x4, x4, x6, lsr #13

loop_set:
	mov	x6, x3
loop_way:
	lsl	x7, x6, x5
	orr	x9, x12, x7
	lsl	x7, x4, x2
	orr	x9, x9, x7
	tbz	w1, #0, 1f
	dc	isw, x9
	b	2f
1:	dc	cisw, x9
2:	subs	x6, x6, #1
	bge	loop_way
	subs	x4, x4, #1
	bge	loop_set
	ret

__dcache_all:
	mov	x1, x0
	dsb	sy
	mrs	x10, clidr_el1
	lsr	x11, x10, #24
	and	x11, x11, #0x7
	cbz	x11, finished
	mov	x15, lr
	mov	x0, #0

loop_level:
	lsl	x12, x0, #1
	add	x12, x12, x0
	lsr	x12, x10, x12
	and	x12, x12, #7
	cmp	x12, #2
	blt	skip
	bl	__dcache_level

skip:
	add	x0, x0, #1
	cmp	x11, x0
	bgt loop_level

	mov	x0, #0
	msr	csselr_el1, x0
	dsb	sy
	isb
	mov	lr, x15

finished:
	ret
