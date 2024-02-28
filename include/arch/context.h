#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>

#define SYNC_SP0_EL		0x1
#define IRQ_SP0_EL		0x2
#define FIQ_SP0_EL		0x3
#define SERROR_SP0_EL	0x4

#define SYNC_SPX_EL		0x11
#define IRQ_SPX_EL		0x12
#define FIQ_SPX_EL		0x13
#define SERROR_SPX_EL	0x14

#define SYNC_SPX_EL0	0x21
#define IRQ_SPX_EL0		0x22
#define FIQ_SPX_EL0		0x23
#define SERROR_SPX_EL0	0x24

#define ESR_EC_SHIFT		26
#define ESR_UNKNOWN			0x00
#define ESR_SYSCALL_ARM64	0x15
#define ESR_SYS_ARM64		0x18
#define ESR_IABT_EL0		0x20
#define ESR_IABT_EL1		0x21
#define ESR_DABT_EL0		0x24
#define ESR_DABT_EL1		0x25
#define ESR_PC_ALIGN		0x22
#define ESR_SP_ALIGN		0x26
#define ESR_BRK_ARM64		0x3c





#ifdef ARM64
typedef struct {
	uint64_t	spsr;
	uint64_t	elr;
	uint64_t	x0;
	uint64_t	x1;
	uint64_t	x2;
	uint64_t	x3;
	uint64_t	x4;
	uint64_t	x5;
	uint64_t	x6;
	uint64_t	x7;
	uint64_t	x8;
	uint64_t	x9;
	uint64_t	x10;
	uint64_t	x11;
	uint64_t	x12;
	uint64_t	x13;
	uint64_t	x14;
	uint64_t	x15;
	uint64_t	x16;
	uint64_t	x17;
	uint64_t	x18;
	uint64_t	x19;
	uint64_t	x20;
	uint64_t	x21;
	uint64_t	x22;
	uint64_t	x23;
	uint64_t	x24;
	uint64_t	x25;
	uint64_t	x26;
	uint64_t	x27;
	uint64_t	x28;
	uint64_t	x29;
	uint64_t	x30;
} context_t;
#endif

#endif
