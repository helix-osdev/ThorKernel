.section .text,"x"
.global mmu_init


.equ L0_SHIFT,	39
.equ L1_SHIFT,	30
.equ L2_SHIFT,	21
.equ L3_SHIFT,	12

.equ PT_FAULT,			0x0
.equ PT_VALID,			(1UL << 0UL)
.equ PT_TABLE,			(1UL << 3UL)
.equ PT_BLOCK,			(1UL << 1UL)

.equ PAGE_SHIFT,		12
.equ TABLE_SHIFT,		9

.equ PGD_SHIFT, (PAGE_SHIFT + 3 * TABLE_SHIFT)
.equ PUD_SHIFT, (PAGE_SHIFT + 2 * TABLE_SHIFT)
.equ PMD_SHIFT, (PAGE_SHIFT + TABLE_SHIFT)

.equ PTRS_PER_TABLE,	(1UL << TABLE_SHIFT)

.equ PT_NORMAL_WBWA,	0x405
.equ PT_DEVICE_nGnRnE,	0x409

.equ PT_NS,				(1UL << 5UL)
.equ PT_SE,				(2UL << 5UL)

.equ PT_AP_NO_EL0_AC,	(1UL << 6UL) // No access on EL0
.equ PT_AP_ALL_EL_RO,	(2UL << 6UL) // R/O on ELx
.equ PT_AP_NO_EL0_RO,	(3UL << 6UL) // No read at EL0

.equ PT_SH_NS,			(0UL << 8UL)
.equ PT_SH_OS,			(1UL << 8UL)
.equ PT_SH_IS,			(2UL << 8UL)

.equ PT_AF,				(1UL << 10UL)
.equ PT_NG,				(1UL << 11UL)

.equ PT_CON,			(1ULL << 52ULL)
.equ PT_PNX,			(1ULL << 53ULL)
.equ PT_UNX,			(1ULL << 54ULL)

.equ PT_KERNEL,			(1ULL << 63ULL)

.equ PT_DEVICE,			(PT_VALID | PT_AF | PT_DEVICE_nGnRnE | PT_KERNEL)
.equ PT_NORMAL,			(PT_VALID | PT_AF | PT_SH_IS | PT_KERNEL)
.equ PT_NORMAL_BLOCK,	(PT_VALID | PT_AF | PT_SH_IS | PT_KERNEL | PT_BLOCK)




.equ TCR_IRGN0_NC,		(0UL << 8UL)
.equ TCR_IRGN0_WBWA,	(1UL << 8UL)
.equ TCR_IRGN0_WTC,		(2UL << 8UL)
.equ TCR_IRGN0_WB_NC,	(3UL << 8UL)

.equ TCR_ORGN0_NC,		(0UL << 10UL)
.equ TCR_ORGNO_WBWA,	(1UL << 10UL)
.equ TCR_ORGN0_WTC,		(2UL << 10UL)
.equ TCR_ORGN0_WB_NC,	(3UL << 10UL)

.equ TCR_SH0_NSH,		(0UL << 12UL)
.equ TCR_SH0_OSH,		(2UL << 12UL)
.equ TCR_SH0_ISH,		(3UL << 12UL)

.equ TCR_TG0_4K,		(0UL << 14UL)
.equ TCR_TG0_64K,		(1UL << 14UL)

.equ TCR_EPD0_DISABLE,	(1UL << 7UL)
.equ TCR_EPD1_DISABLE,	(1UL << 23UL)

.equ TCR_IRGN1_NC,		(0UL << 24UL)
.equ TCR_IRGN1_WBWA,	(1UL << 24UL)
.equ TCR_IRGN1_WTC,		(2UL << 24UL)
.equ TCR_IRGN1_WB_NC,	(3UL << 24UL)

.equ TCR_ORGN1_NC,		(0ULL << 26UL)
.equ TCR_ORGN1_WBWA,	(1UL << 26UL)
.equ TCR_ORGN1_WTC,		(2UL << 26UL)
.equ TCR_ORGN1_WB_NC,	(3UL << 26UL)

.equ TCR_SH1_NSH,		(0UL << 28UL)
.equ TCR_SH1_OSH,		(2UL << 28UL)
.equ TCR_SH1_ISH,		(3UL << 28UL)

.equ TCR_TG1_4K,		(0UL << 30UL)
.equ TCR_TG1_64K,		(1UL << 30UL)

.equ TCR_IPS_4GB,		(0UL << 32UL)
.equ TCR_IPS_64GB,		(1UL << 32UL)
.equ TCR_IPS_1TB,		(2UL << 32UL)
.equ TCR_IPS_4TB,		(3UL << 32UL)
.equ TCR_IPS_16TB,		(4UL << 32UL)
.equ TCR_IPS_256TB,		(5UL << 32UL)

.equ TCR_TBI0_TBI,		(1UL << 37UL)
.equ TCR_TBI1_TBI,		(1UL << 38UL)

.equ SCTLR_MMU_ENABLE,		(1UL << 0UL)

.equ SCTLR_ALIGN_ENABLE,	(1UL << 1UL)

.equ SCTLR_DCACHE_ENABLE,	(1UL << 2UL)
.equ SCTLR_ICACHE_ENABLE,	(1UL << 12UL)

.macro __map_table_entry tbl, virt, shift, flags, tmp1
	lsr \tmp1, \virt, #\shift
	lsl \tmp1, \tmp1, #3
	orr \virt, \virt, \flags
	str \virt, [\tbl, \tmp1]
.endm









mmu_init:
	stp x29, x30, [sp, #-16]!

	ldr x0, =l1_table
	ldr x1, =l2_table
	ldr x3, =l3_table


	bl __flush_dcache_all
	bl __inval_dcache_all

	ldp x29, x30, [sp], #16
	ret



.section .data.page_tables,"wa"
.global l1_table
.global l2_table
.global l3_table




l1_table:
	.fill 512 * 8, 1, 0

l2_table:
	.fill 512 * 8, 1, 0

l3_table:
	.fill 512 * 8, 1, 0
