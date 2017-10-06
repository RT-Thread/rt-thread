/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2014
 *                         All Rights Reserved.
 *
 ****************************************************************************/

#ifndef __AE210P_REGS_H__
#define __AE210P_REGS_H__

#ifndef __ASSEMBLER__
#include <inttypes.h>
#include <nds32_intrinsic.h>
#endif

#if (defined(CONFIG_CPU_ICACHE_ENABLE) || defined(CONFIG_CPU_DCACHE_ENABLE))
/*
 * The NTC1 is set to noncache region and NTM1 is mapped to partition 0 (I/O region).
 * Map the I/O address to NTC1 to be uncachable.
 */
#define UNCACHE_MAP(addr)		((addr) | 0x40000000)
#else
#define UNCACHE_MAP(addr)		(addr)
#endif

#define _IO_(addr)			UNCACHE_MAP(addr)


/*****************************************************************************
 * ExLM - AE210P AHB
 * **************************************************************************/
#define EILM_BASE			0x00000000
#ifdef CONFIG_OSC_SUPPORT
#define EDLM_BASE			0x00100000
#else
#define EDLM_BASE			0x00200000
#endif
#define SPIAHBMEM_BASE		0x00800000

/*****************************************************************************
 * AHBC - AE210P AHB
 ****************************************************************************/
#define AHBC_BASE_4_7			_IO_(0x00400000) /* Vendor AHB Slave 8~9 */
#define AHBC_BASE_0_3			_IO_(0x00E20000) /* Vendor AHB Slave 0~7 */

/*****************************************************************************
 * BMC - AE210P AHB
 ****************************************************************************/
#define BMC_BASE			_IO_(0x00E00000) /* Device base address */

/*****************************************************************************
 * OSC - AE210P OSC
 ****************************************************************************/
#define OSC_BASE			_IO_(0x00E01000)

/* OSC register */
#define OSC_CTRL			(OSC_BASE + 0x00)
#define OSC_OVLFS			(OSC_BASE + 0x04)
#define OSC_OVLBASE			(OSC_BASE + 0x08)
#define OSC_OVLEND			(OSC_BASE + 0x0C)
#define OSC_DMAST			(OSC_BASE + 0x10)

/*****************************************************************************
 * DMAC - AE210P AHB
 ****************************************************************************/
#define DMAC_BASE			_IO_(0x00E0E000) /* Device base address */

/*****************************************************************************
 * APBBRG - AE210P APB
 ****************************************************************************/
#define APBBR_BASE			_IO_(0x00F00000) /* Device base address */

/*****************************************************************************
 * SMU - AE210P
 ****************************************************************************/
#define SMU_BASE			_IO_(0x00F01000) /* Device base address */

/*****************************************************************************
 * UARTx - AE210P
 ****************************************************************************/
#define UART1_BASE			_IO_(0x00F02000) /* Device base address */
#define UART2_BASE			_IO_(0x00F03000) /* Device base address */
#define STUARTC_BASE        UART2_BASE /* standard/IR UART */

/* UART register offsets (4~8-bit width) */
/* SD_LCR_DLAB == 0 */
#define UARTC_RBR_OFFSET                0x20 /* receiver biffer register */
#define UARTC_THR_OFFSET                0x20 /* transmitter holding register */
#define UARTC_IER_OFFSET                0x24 /* interrupt enable register */
#define UARTC_IIR_OFFSET                0x28 /* interrupt identification register */
#define UARTC_FCR_OFFSET                0x28 /* FIFO control register */
#define UARTC_LCR_OFFSET                0x2c /* line control regitser */
#define UARTC_MCR_OFFSET                0x30 /* modem control register */
#define UARTC_LSR_OFFSET                0x34 /* line status register */
#define UARTC_TST_OFFSET                0x34 /* testing register */
#define UARTC_MSR_OFFSET                0x38 /* modem status register */
#define UARTC_SPR_OFFSET                0x3c /* scratch pad register */

/* SD_LCR_DLAB == 0 */
#define UARTC_DLL_OFFSET                0x20 /* baudrate divisor latch LSB */
#define UARTC_DLM_OFFSET                0x24 /* baudrate divisor latch MSB */
#define UARTC_PSR_OFFSET                0x28 /* prescaler register */


/*****************************************************************************
 * PIT - AE210P
 ****************************************************************************/
#define PIT_BASE			_IO_(0x00F04000) /* Device base address */

/* PIT register (32-bit width) */
#define PIT_ID_REV			(PIT_BASE + 0x00 ) /* (ro)  PIT ID and Revision Register */
#define PIT_CFG				(PIT_BASE + 0x10 ) /* (ro)  PIT Configuration Register	 */
#define PIT_INT_EN			(PIT_BASE + 0x14 ) /* (rw)  PIT Interrupt Enable Register*/
#define PIT_INT_ST			(PIT_BASE + 0x18 ) /* (w1c) PIT Interrupt Status Register*/
#define PIT_CH_EN			(PIT_BASE + 0x1C ) /* (rw)  PIT Channel Enable Register	 */

/* _chn_ from 0 to 3*/
/* (rw) PIT Channel x Control Register (32-bit width) */
#define PIT_CHNx_CTL(_chn_)		( PIT_BASE + 0x20 + ( (_chn_)* 0x10) )

/* (rw) PIT Channel x Reload Register (32-bit width)  */
#define PIT_CHNx_LOAD(_chn_)		( PIT_BASE + 0x24 + ( (_chn_)* 0x10) )

/* (ro) PIT Channel x Counter Register (32-bit width) */
#define PIT_CHNx_COUNT(_chn_)		( PIT_BASE + 0x28 + ( (_chn_)* 0x10) )


/*****************************************************************************
 * WDT - AE210P
 ****************************************************************************/
#define WDTC_BASE			_IO_(0x00F05000) /* Device base address */

/*****************************************************************************
 * RTC - AE210P
 ****************************************************************************/
#define RTC_BASE			_IO_(0x00F06000) /* Device base address */

/*****************************************************************************
 * GPIO - AE210P
 ****************************************************************************/
#define GPIOC_BASE			_IO_(0x00F07000) /* Device base address */

/*****************************************************************************
 * I2C - AE210P
 ****************************************************************************/
#define I2C_BASE			_IO_(0x00F0A000) /* Device base address */

/*****************************************************************************
 * SPI1 - AE210P
 ****************************************************************************/
#define SPI1_BASE			_IO_(0x00F0B000) /* Device base address */

/*****************************************************************************
 * I2S/AC97 - AE210P (SSP2)
 ****************************************************************************/
#define SPI2_BASE			_IO_(0x00F0F000) /* Device base address */

/*****************************************************************************
 * APB_SLAVE - AE210P Vender APB Slave 0~4
 ****************************************************************************/
#define APB_SLAVE_BASE 			_IO_(0x00F19000) /* Device base address */


/*****************************************************************************
 * Macros for Register Access
 ****************************************************************************/
#define REG32(reg)			(  *( (volatile uint32_t *) (reg) ) )

#ifdef REG_IO_HACK

/* 8 bit access */
//#define IN8(reg)			(  *( (volatile uint8_t *) (reg) ) )
#define OUT8(reg, data)			( (*( (volatile uint8_t *) (reg) ) ) = (uint8_t)(data) )

#define CLR8(reg)			(  *( (volatile uint8_t *) (reg) ) = (uint8_t)0 )
#define MASK8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) & (uint8_t)(mask) )
#define UMSK8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) & ~( (uint8_t)(mask) ) )

#define SETR8SHL(reg, mask, shift, v)	(  *( (volatile uint8_t *) (reg) ) = \
					( ( *( (volatile uint8_t *) (reg) ) & ~( (uint8_t)(mask) ) ) | \
					( ( (uint8_t)(v) << (shift) ) & (uint8_t)(mask)          ) ) )

#define SETR8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) = \
					( ( *( (volatile uint8_t *) (reg) ) & ~( (uint8_t)(mask) ) ) | (uint8_t)(mask) ) )

#define CLRR8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) &= ~( (uint8_t)(mask) ) )

#define SETB8(reg, bit)			(  *( (volatile uint8_t *) (reg) ) |= (uint8_t)( (uint8_t)1 << (bit) ) )
#define CLRB8(reg, bit)			(  *( (volatile uint8_t *) (reg) ) &= ( ~( (uint8_t) ( (uint8_t)1 << (bit) ) ) ) )
#define GETB8(reg, bit)			(  *( (volatile uint8_t *) (reg) ) & (uint8_t) ( (uint8_t)1 << (bit) ) )
#define GETB8SHR(reg, bit)		( (*( (volatile uint8_t *) (reg) ) & (uint8_t) ( (uint8_t)1 << (bit) )) >> (bit) )

/* 16 bit access */
#define IN16(reg)			(  *( (volatile uint16_t *) (reg) ) )
#define OUT16(reg, data)		( (*( (volatile uint16_t *) (reg) ) ) = (uint16_t)(data) )

#define CLR16(reg)			(  *( (volatile uint16_t *) (reg) ) = (uint16_t)0 )
#define MASK16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) & (uint16_t)(mask) )
#define UMSK16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) & ~( (uint16_t)(mask) ) )

#define SETR16SHL(reg, mask, shift, v)	(  *( (volatile uint16_t *) (reg) ) = \
					( ( *( (volatile uint16_t *) (reg) ) & ~( (uint16_t)(mask) ) ) | \
					( ( (uint16_t)(v) << (shift) ) & (uint16_t)(mask)          ) ) )

#define SETR16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) = \
					( ( *( (volatile uint16_t *) (reg) ) & ~( (uint16_t)(mask) ) ) | (uint16_t)(mask) ) )

#define CLRR16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) &= ~( (uint16_t)(mask) ) )

#define SETB16(reg, bit)		(  *( (volatile uint16_t *) (reg) ) |= (uint16_t)( (uint16_t)1 << (bit) ) )
#define CLRB16(reg, bit)		(  *( (volatile uint16_t *) (reg) ) &= ( ~( (uint16_t) ( (uint16_t)1 << (bit) ) ) ) )
#define GETB16(reg, bit)		(  *( (volatile uint16_t *) (reg) ) & (uint16_t) ( (uint16_t)1 << (bit) ) )
#define GETB16SHR(reg, bit)		( (*( (volatile uint16_t *) (reg) ) & (uint16_t) ( (uint16_t)1 << (bit) )) >> (bit) )

/* 32 bit access */
#define IN32(reg)			_IN32((uint32_t)(reg))
#define OUT32(reg, data)		_OUT32((uint32_t)(reg), (uint32_t)(data))

#define CLR32(reg)			_CLR32((uint32_t)(reg))
#define MASK32(reg, mask)		_MASK32((uint32_t)(reg), (uint32_t)(mask))
#define UMSK32(reg, mask)		_UMSK32((uint32_t)(reg), (uint32_t)(mask))

#define SETR32SHL(reg, mask, shift, v)	_SETR32SHL((uint32_t)(reg), (uint32_t)(mask), (uint32_t)(shift), (uint32_t)(v))
#define SETR32(reg, mask)		_SETR32((uint32_t)(reg), (uint32_t)(mask))
#define CLRR32(reg, mask)		_CLRR32((uint32_t)(reg), (uint32_t)(mask))

#define SETB32(reg, bit)		_SETB32((uint32_t)(reg), (uint32_t)(bit))
#define CLRB32(reg, bit)		_CLRB32((uint32_t)(reg), (uint32_t)(bit))
#define GETB32(reg, bit)		_GETB32((uint32_t)(reg), (uint32_t)(bit))
#define GETB32SHR(reg, bit)		_GETB32SHR((uint32_t)(reg), (uint32_t)(bit))

#else /* REG_IO_HACK */

/* 8 bit access */
//#define IN8(reg)			(  *( (volatile uint8_t *) (reg) ) )
#define OUT8(reg, data)			( (*( (volatile uint8_t *) (reg) ) ) = (uint8_t)(data) )

#define CLR8(reg)			(  *( (volatile uint8_t *) (reg) ) = (uint8_t)0 )
#define MASK8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) & (uint8_t)(mask) )
#define UMSK8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) & ~( (uint8_t)(mask) ) )

#define SETR8SHL(reg, mask, shift, v)	(  *( (volatile uint8_t *) (reg) ) = \
					( ( *( (volatile uint8_t *) (reg) ) & ~( (uint8_t)(mask) ) ) | \
					( ( (uint8_t)(v) << (shift) ) & (uint8_t)(mask)          ) ) )

#define SETR8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) = \
					( ( *( (volatile uint8_t *) (reg) ) & ~( (uint8_t)(mask) ) ) | (uint8_t)(mask) ) )

#define CLRR8(reg, mask)		(  *( (volatile uint8_t *) (reg) ) &= ~( (uint8_t)(mask) ) )

#define SETB8(reg, bit)			(  *( (volatile uint8_t *) (reg) ) |= (uint8_t)( (uint8_t)1 << (bit) ) )
#define CLRB8(reg, bit)			(  *( (volatile uint8_t *) (reg) ) &= ( ~( (uint8_t) ( (uint8_t)1 << (bit) ) ) ) )
#define GETB8(reg, bit)			(  *( (volatile uint8_t *) (reg) ) & (uint8_t) ( (uint8_t)1 << (bit) ) )
#define GETB8SHR(reg, bit)		( (*( (volatile uint8_t *) (reg) ) & (uint8_t) ( (uint8_t)1 << (bit) )) >> (bit) )

/* 16 bit access */
#define IN16(reg)			(  *( (volatile uint16_t *) (reg) ) )
#define OUT16(reg, data)		( (*( (volatile uint16_t *) (reg) ) ) = (uint16_t)(data) )

#define CLR16(reg)			(  *( (volatile uint16_t *) (reg) ) = (uint16_t)0 )
#define MASK16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) & (uint16_t)(mask) )
#define UMSK16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) & ~( (uint16_t)(mask) ) )

#define SETR16SHL(reg, mask, shift, v)	(  *( (volatile uint16_t *) (reg) ) = \
					( ( *( (volatile uint16_t *) (reg) ) & ~( (uint16_t)(mask) ) ) | \
					( ( (uint16_t)(v) << (shift) ) & (uint16_t)(mask)          ) ) )

#define SETR16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) = \
					( ( *( (volatile uint16_t *) (reg) ) & ~( (uint16_t)(mask) ) ) | (uint16_t)(mask) ) )
#define CLRR16(reg, mask)		(  *( (volatile uint16_t *) (reg) ) &= ~( (uint16_t)(mask) ) )

#define SETB16(reg, bit)		(  *( (volatile uint16_t *) (reg) ) |= (uint16_t)( (uint16_t)1 << (bit) ) )
#define CLRB16(reg, bit)		(  *( (volatile uint16_t *) (reg) ) &= ( ~( (uint16_t) ( (uint16_t)1 << (bit) ) ) ) )
#define GETB16(reg, bit)		(  *( (volatile uint16_t *) (reg) ) & (uint16_t) ( (uint16_t)1 << (bit) ) )
#define GETB16SHR(reg, bit)		( (*( (volatile uint16_t *) (reg) ) & (uint16_t) ( (uint16_t)1 << (bit) )) >> (bit) )

/* 32 bit access */
#define IN32(reg)			(  *( (volatile uint32_t *) (reg) ) )
#define OUT32(reg, data)		( (*( (volatile uint32_t *) (reg) ) ) = (uint32_t)(data) )

#define CLR32(reg)			(  *( (volatile uint32_t *) (reg) ) = (uint32_t)0 )
#define MASK32(reg, mask)		(  *( (volatile uint32_t *) (reg) ) & (uint32_t)(mask) )
#define UMSK32(reg, mask)		(  *( (volatile uint32_t *) (reg) ) & ~( (uint32_t)(mask) ) )

#define SETR32SHL(reg, mask, shift, v)	(  *( (volatile uint32_t *) (reg) ) = \
					( ( *( (volatile uint32_t *) (reg) ) & ~( (uint32_t)(mask) ) ) | \
					( ( (uint32_t)(v) << (shift) ) & (uint32_t)(mask)          ) ) )

#define SETR32(reg, mask)		(  *( (volatile uint32_t *) (reg) ) = \
					( ( *( (volatile uint32_t *) (reg) ) & ~( (uint32_t)(mask) ) ) | (uint32_t)(mask) ) )

#define CLRR32(reg, mask)		(  *( (volatile uint32_t *) (reg) ) &= ~( (uint32_t)(mask) ) )

#define SETB32(reg, bit)		(  *( (volatile uint32_t *) (reg) ) |= (uint32_t)( (uint32_t)1 << (bit) ) )
#define CLRB32(reg, bit)		(  *( (volatile uint32_t *) (reg) ) &= ( ~( (uint32_t) ( (uint32_t)1 << (bit) ) ) ) )
#define GETB32(reg, bit)		(  *( (volatile uint32_t *) (reg) ) & (uint32_t) ( (uint32_t)1 << (bit) ) )
#define GETB32SHR(reg, bit)		( (*( (volatile uint32_t *) (reg) ) & (uint32_t) ( (uint32_t)1 << (bit) )) >> (bit) )

#endif /* REG_IO_HACK */

#define SR_CLRB32(reg, bit)		\
{					\
	int mask = __nds32__mfsr(reg)& ~(1<<bit);\
        __nds32__mtsr(mask, reg);	 \
	__nds32__dsb();				 \
}

#define SR_SETB32(reg,bit)\
{\
	int mask = __nds32__mfsr(reg)|(1<<bit);\
	__nds32__mtsr(mask, reg);			\
	__nds32__dsb();						\
}

#endif /* __AE210P_REGS_H__ */
