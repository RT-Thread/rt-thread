/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef FH_SDIO_H_
#define FH_SDIO_H_

#include <rtthread.h>

//#define __ASIC_BRANCH__

enum {
	CTRL        = 0x0, 	/** Control */
	PWREN    = 0x4, 	/** Power-enable */
	CLKDIV   = 0x8, 	/** Clock divider */
	CLKSRC   = 0xC, 	/** Clock source */
	CLKENA   = 0x10,    /** Clock enable */
	TMOUT    = 0x14,    /** Timeout */
	CTYPE    = 0x18,    /** Card type */
	BLKSIZ   = 0x1C,    /** Block Size */
	BYTCNT   = 0x20,    /** Byte count */
	INTMSK   = 0x24,    /** Interrupt Mask */
	CMDARG   = 0x28,    /** Command Argument */
	CMD      = 0x2C,    /** Command */
	RESP0    = 0x30,    /** Response 0 */
	RESP1    = 0x34,    /** Response 1 */
	RESP2    = 0x38,    /** Response 2 */
	RESP3    = 0x3C,    /** Response 3 */
	MINTSTS  = 0x40,    /** Masked interrupt status */
	RINTSTS  = 0x44,    /** Raw interrupt status */
	STATUS   = 0x48,    /** Status */
	FIFOTH   = 0x4C,    /** FIFO threshold */
	CDETECT  = 0x50,    /** Card detect */
	WRTPRT   = 0x54,    /** Write protect */
	GPIO     = 0x58,    /** General Purpose IO */
	TCBCNT   = 0x5C,    /** Transferred CIU byte count */
	TBBCNT   = 0x60,    /** Transferred host/DMA to/from byte count */
	DEBNCE   = 0x64,    /** Card detect debounce */
	USRID    = 0x68,    /** User ID */
	VERID    = 0x6C,    /** Version ID */
	HCON     = 0x70,    /** Hardware Configuration */
	UHSREG   = 0x74,    /** Reserved */
 	BMOD	 = 0x80,    /** Bus mode Register */
	PLDMND	 = 0x84,    /** Poll Demand */
	DBADDR	 = 0x88,    /** Descriptor Base Address */
	IDSTS	 = 0x8C,    /** Internal DMAC Status */
	IDINTEN  = 0x90,    /** Internal DMAC Interrupt Enable */
	DSCADDR  = 0x94,    /** Current Host Descriptor Address */
	BUFADDR	 = 0x98,    /** Current Host Buffer Address */
	FIFODAT  = 0x200,   /** FIFO data read write */
};

/* Control register definitions */
#define CTRL_RESET	          0x00000001
#define FIFO_RESET              0x00000002
#define DMA_RESET	          0x00000004
#define INT_ENABLE	          0x00000010
#define READ_WAIT	          0x00000040
#define CTRL_USE_IDMAC	   0x02000000

/* Interrupt mask defines */
#define INTMSK_CDETECT        0x00000001
#define INTMSK_RESP_ERR     0x00000002
#define INTMSK_CMD_DONE   0x00000004
#define INTMSK_DAT_OVER    0x00000008
#define INTMSK_TXDR             0x00000010
#define INTMSK_RXDR             0x00000020
#define INTMSK_RCRC             0x00000040
#define INTMSK_DCRC             0x00000080
#define INTMSK_RTO               0x00000100
#define INTMSK_DTO               0x00000200
#define INTMSK_HTO               0x00000400
#define INTMSK_VSI                INTMSK_HTO  // VSI => Voltage Switch Interrupt
#define INTMSK_FRUN             0x00000800
#define INTMSK_HLE                0x00001000
#define INTMSK_SBE                0x00002000
#define INTMSK_ACD               0x00004000
#define INTMSK_EBE                0x00008000
#define INTMSK_SDIO              0x00010000
#define INTMASK_ERROR        (INTMSK_RESP_ERR|INTMSK_RCRC|INTMSK_DCRC|INTMSK_RTO|INTMSK_DTO|INTMSK_HTO|INTMSK_FRUN|INTMSK_HLE|INTMSK_SBE|INTMSK_EBE)

/*BMOD register define */
#define  BMOD_SWR 	  	   0x00000001
#define  BMOD_DE 		   0x00000080

/* for STATUS register */
#define GET_FIFO_COUNT(x)           	(((x)&0x3ffe0000)>>17)
#define GET_FIFO_DEPTH(x)       ((((x)&0x0FFF0000)>>16)+1)

/* for IDMA intr register */
#define IDMAINTBITS   0x337

/* PMU related registers */
//#define PMU_REG_BASE           0xF0000000
#define PMU_REG_RST             0xF0000100
#define PMU_REG_CLK_DIV3   0xF0000030
#define PMU_SDC0_RST_BIT  9
#define PMU_SDC1_RST_BIT  10
#define PMU_RST_MODULE(x) *((volatile unsigned int*)(PMU_REG_RST)) = (~((1<<(x))))

/* Define Card status bits (R1 response) */
#define R1CS_ADDRESS_OUT_OF_RANGE       0x80000000
#define R1CS_ADDRESS_MISALIGN		    0x40000000
#define R1CS_BLOCK_LEN_ERR       		0x20000000
#define R1CS_ERASE_SEQ_ERR	           	0x10000000
#define R1CS_ERASE_PARAM	            0x08000000
#define R1CS_WP_VIOLATION		        0x04000000
#define R1CS_CARD_IS_LOCKED	            0x02000000
#define R1CS_LCK_UNLCK_FAILED		    0x01000000
#define R1CS_COM_CRC_ERROR		        0x00800000
#define R1CS_ILLEGAL_COMMAND		    0x00400000
#define R1CS_CARD_ECC_FAILED		    0x00200000
#define R1CS_CC_ERROR		        	0x00100000
#define R1CS_ERROR		            	0x00080000
#define R1CS_UNDERRUN		        	0x00040000
#define R1CS_OVERRUN		        	0x00020000
#define R1CS_CSD_OVERWRITE	        	0x00010000
#define R1CS_WP_ERASE_SKIP	        	0x00008000
#define R1CS_RESERVED_0	        		0x00004000
#define R1CS_ERASE_RESET        		0x00002000
#define R1CS_CURRENT_STATE_MASK    		0x00001e00
#define R1CS_READY_FOR_DATA	        	0x00000100
#define R1CS_SWITCH_ERROR        		0x00000080
#define R1CS_RESERVED_1		        	0x00000040
#define R1CS_APP_CMD		        	0x00000020
#define R1CS_RESERVED_2		        	0x00000010
#define R1CS_APP_SPECIFIC_MASK	    	0x0000000c
#define R1CS_MANUFAC_TEST_MASK    		0x00000003
#define R1CS_ERROR_OCCURED_MAP	    	0xfdffa080
#define R1CS_CURRENT_STATE(x)	    	(((x)&R1CS_CURRENT_STATE_MASK)>>9)

/* R5 response */
#define R5_IO_CRC_ERR	  0x00008000
#define R5_IO_BAD_CMD	  0x00004000
#define R5_IO_GEN_ERR	  0x00000800
#define R5_IO_FUNC_ERR	  0x00000200
#define R5_IO_OUT_RANGE 0x00000100
#define R5_IO_ERR_BITS	  0x0000cb00

enum {
	NONE_TYPE = 0,
	SD_TYPE,
	SD_2_0_TYPE,
	SDIO_TYPE,
};

enum {
	CARD_STATE_EMPTY = -1,
	CARD_STATE_IDLE = 0,
	CARD_STATE_READY = 1,
	CARD_STATE_IDENT = 2,
	CARD_STATE_STBY = 3,
	CARD_STATE_TRAN = 4,
	CARD_STATE_DATA = 5,
	CARD_STATE_RCV = 6,
	CARD_STATE_PRG = 7,
	CARD_STATE_DIS = 8,
	CARD_STATE_INA = 9
};

enum DmaDescriptorDES1    // Buffer's size field of Descriptor
{
     DescBuf2SizMsk       = 0x03FFE000,    /* Mask for Buffer2 Size                            25:13   */
     DescBuf2SizeShift    = 13,            /* Shift value for Buffer2 Size                             */
     DescBuf1SizMsk       = 0x00001FFF,    /* Mask for Buffer1 Size                            12:0    */
     DescBuf1SizeShift    = 0,             /* Shift value for Buffer2 Size                             */
};

enum DmaDescriptorDES0    // Control and status word of DMA descriptor DES0
{
     DescOwnByDma          = 0x80000000,   /* (OWN)Descriptor is owned by DMA engine              31   */
     DescCardErrSummary    = 0x40000000,   /* Indicates EBE/RTO/RCRC/SBE/DRTO/DCRC/RE             30   */
     DescEndOfRing         = 0x00000020,   /* A "1" indicates End of Ring for Ring Mode           05   */
     DescSecAddrChained    = 0x00000010,   /* A "1" indicates DES3 contains Next Desc Address     04   */
     DescFirstDesc         = 0x00000008,   /* A "1" indicates this Desc contains first            03
                                              buffer of the data                                       */
     DescLastDesc          = 0x00000004,   /* A "1" indicates buffer pointed to by this this      02
                                              Desc contains last buffer of Data                        */
     DescDisInt            = 0x00000002,   /* A "1" in this field disables the RI/TI of IDSTS     01
                                              for data that ends in the buffer pointed to by
                                              this descriptor                                          */
};

typedef struct DmaDescStruct {
		unsigned int desc0;   	 /* control and status information of descriptor */
		unsigned int desc1;   	 /* buffer sizes                                 */
		unsigned int desc2;   	 /* physical address of the buffer 1             */
		unsigned int desc3;    	 /* physical address of the buffer 2             */
}DmaDesc;

typedef struct {
	unsigned int wkmod;
	volatile DmaDesc *pDmaDesc;
	unsigned int idma_support;
	unsigned int rca;
	unsigned int ip_base;
	unsigned int card_type;
	unsigned int fifo_depth;
	unsigned int fifo_threth;
	unsigned int sectors;
	unsigned int scr[2];
	unsigned int csd[4];
	unsigned int idsts;
	rt_sem_t sem;
	rt_sem_t mutex;
	void (*cb)(void);
} sdc_t;

#define ONE_BIT_MODE     (0)
#define FOUR_BIT_MODE   (1)

#define BE32_TO_CPU(x) ((unsigned int)(             \
       (((unsigned int)(x) & (unsigned int)0x000000ffUL) << 24) |        \
        (((unsigned int)(x) & (unsigned int)0x0000ff00UL) <<  8) |        \
       (((unsigned int)(x) & (unsigned int)0x00ff0000UL) >>  8) |        \
     (((unsigned int)(x) & (unsigned int)0xff000000UL) >> 24)))

#define synopmob_set_bits(reg, bit_id) *((volatile unsigned int *)(reg)) |= ((unsigned int)(bit_id))
#define synopmob_clear_bits(reg, bit_id) *((volatile unsigned int *)(reg)) &= (~((unsigned int)(bit_id)))
#define synopmob_set_register(reg, val) *((volatile unsigned int*)(reg)) = (val)
#define synopmob_read_register(reg) (*((volatile unsigned int*)(reg)))


enum {
	ERRNOERROR = 0,
		
	// for raw interrupt status error
	ERRRESPRECEP,    // 1
	ERRRESPCRC,
	ERRDCRC,
	ERRRESPTIMEOUT,
	ERRDRTIMEOUT,
	ERRUNDERWRITE,
	ERROVERREAD,
	ERRHLE,
	ERRSTARTBIT,
	ERRENDBITERR,  // 10

	// for R1 response
	ERRADDRESSRANGE,  // 11
	ERRADDRESSMISALIGN,
	ERRBLOCKLEN,
	ERRERASESEQERR,
	ERRERASEPARAM,
	ERRPROT,
	ERRCARDLOCKED,
	ERRCRC,
	ERRILLEGALCOMMAND,
	ERRECCFAILED,
	ERRCCERR,
	ERRUNKNOWN,
	ERRUNDERRUN,
	ERROVERRUN,
	ERRCSDOVERWRITE,
	ERRERASERESET,
	ERRFSMSTATE,  // 27

	// for R5 response
	ERRBADFUNC,   // 28

	// others
	ERRCARDNOTCONN,  // 29
	ERRCARDWPROTECT,
	ERRCMDRETRIESOVER,
	ERRNOTSUPPORTED,
	ERRHARDWARE,
	ERRDATANOTREADY,
	ERRCARDINTERNAL,
	ERRACMD41TIMEOUT,
	ERRIDMA,
	ERRNORES,

	ERRNOTEQUAL,
};

#ifdef __ASIC_BRANCH__
#define SDC_WHERE() *((volatile unsigned int*)0x9b800000) = ((unsigned int)(__LINE__))
#define SDC_ERROR()  do { *((volatile unsigned int*)0x9b800008)=ret; *((volatile unsigned int*)0x9a7ff000) = 0;}while(0)
#define SDC_FINISH() *((volatile unsigned int*)0x9a7ff004) = 0;
#else
#define SDC_WHERE()
#define SDC_ERROR()
#define SDC_FINISH()
#endif //__ASIC_BRANCH__

#define SDC_WKMOD_25M_STAND_SPEED  0x0002   // 25M standard speed
#define SDC_WKMOD_50M_HI_SPEED         0x0004   // 50M high speed
#define SDC_WKMOD_1WIRE                        0x0008   // 1 wire transfer mode
#define SDC_WKMOD_4WIRE                        0x0010   // 4 wire transfer mode

#define SDC_RW_USE_DMA                           0x80000000   // Use DMA transfer?


typedef void* HSDC;

// map to DmaDesc
typedef struct _buf_chain {
    unsigned int csi;             // desc0
    unsigned int size;            // desc1
    void * buf;             // desc2
    struct _buf_chain *next; // desc3
}buf_chain_t;


/*
  * for SD card
   */
extern int sdc_is_connected(unsigned int which);
extern int sdc_init(unsigned int which, unsigned int wkmod, unsigned int* dma_desc/*4Byte aligned,16 bytes space*/, HSDC* phandle);
extern int sdc_read_block(HSDC handle, unsigned int blk, unsigned int num, unsigned char* buffer);
extern int sdc_write_block(HSDC handle, unsigned int blk, unsigned int num, unsigned char* buffer);
extern int sdc_erase_block(HSDC handle, unsigned int blk, unsigned int num);
extern int sdc_get_sector_num(HSDC handle);
extern int sdc_set_clk_divider(unsigned int divider);

/*
  * for SDIO WIFI card
   */
extern void fh_sdio0_init(void);
extern void fh_sdio1_init(void);
extern void fh_sdio_init(void);
extern int sdio_init(unsigned int which, unsigned int wkmod, unsigned int* dma_desc/*4Byte aligned,16 bytes space*/, HSDC* phandle);
extern int sdio_high_speed_mode(HSDC handle, int bitwidth, int freq);
extern int sdio_enable_card_int(HSDC handle, int enable);
extern int sdio_set_card_int_cb(HSDC handle, void (*cb)(void));
extern int sdio_drv_read(HSDC handle, unsigned int addr, unsigned int fn, unsigned int bcnt, unsigned int bsize, unsigned char *buf);
extern int sdio_drv_write(HSDC handle, unsigned int addr, unsigned int fn, unsigned int bcnt, unsigned int bsize, unsigned char *buf);
extern int sdio_drv_creg_read(HSDC handle, int addr, int fn, unsigned int *resp);
extern int sdio_drv_creg_write(HSDC handle, int addr, int fn, unsigned char data, unsigned int *resp);

extern void inv_dcache_range(unsigned long start, unsigned long len);
extern void flush_dcache_range(unsigned long start, unsigned long len);
 
#endif //__sdcard_h__
