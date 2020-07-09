/*!
*******************************************************************************
**
** \file      gk_mmap.h
**
** \brief     GoKe memory map defines.
**
**            This file contains common GoKe memory map defines
**            used by all drivers and applications.
**
**            (C) Copyright 2012-2013 by Goke Microelectronics Shanghai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Revision: 1.0 $
**
******************************************************************************/
#ifndef _GK_MMAP_H_
#define _GK_MMAP_H_


#define GK_MMAP_DDR_SIZE_1G             0x08000000  //!< 1gbit size
#define GK_MMAP_DDR_SIZE_2G             0x10000000  //!< 2gbit size

#ifdef __LINUX__

#define GK_MMAP_ADDR_OFFSET             0x00000000  //!< no need offset for arm11 and arc4

#define GK_MMAP_DDR0_START             (0x00100000 - GK_MMAP_ADDR_OFFSET)   //!< ddr0  start address
#define GK_MMAP_DDR1_START             (0x40000000 - GK_MMAP_ADDR_OFFSET)   //!< ddr1  start address

#define GK_MMAP_DDR0_SIZE               GK_MMAP_DDR_SIZE_1G  //!< ddr0 size in byte
#define GK_MMAP_DDR1_SIZE               GK_MMAP_DDR_SIZE_1G  //!< ddr1 size in byte

#define GK_MMAP_ARC_START              (0x00200000 - GK_MMAP_ADDR_OFFSET)   //!< ARC4 code start address
#define GK_MMAP_ARM11_START            (0x01000000 - GK_MMAP_ADDR_OFFSET)   //!< ARM11 code start address
#define GK_MMAP_AS211_START            (0x40000000 - GK_MMAP_ADDR_OFFSET)   //!< AS211 code start address
#else


#define GK_MMAP_ADDR_OFFSET             0x00000000  //!< no need offset for arm11 and arc4


#define GK_MMAP_DDR0_START             (DDR_MEMORY_START_1 - GK_MMAP_ADDR_OFFSET)   //!< ddr0  start address
#define GK_MMAP_DDR1_START             (DDR_MEMORY_START_2 - GK_MMAP_ADDR_OFFSET)   //!< ddr1  start address

#define GK_MMAP_DDR0_SIZE               DDR_MEMORY_BYTES_1  //!< ddr0 size in byte
#define GK_MMAP_DDR1_SIZE               DDR_MEMORY_BYTES_2  //!< ddr1 size in byte


#endif


#define GK_MMAP_BOOTROM_START          (0x00000000 - GK_MMAP_ADDR_OFFSET)   //!< bootrom code start address
#define GK_MMAP_SRAM_START             (0x00080000 - GK_MMAP_ADDR_OFFSET)   //!< sram code start address
#define GK_MMAP_UBOOTER_START          (0xF0000000 - GK_MMAP_ADDR_OFFSET)   //!< Ubooter code start address
			// FPGA has one ddr memory only
#define GK_MMAP_FRAME_BUFFER_START     (0x00400000 - GK_MMAP_ADDR_OFFSET)   //!< Frame data buffer for videc


#define GK_MMAP_DDR0_END                GK_MMAP_DDR0_SIZE                         //!< ddr0 end address
#define GK_MMAP_DDR1_END               (GK_MMAP_DDR1_START + GK_MMAP_DDR1_SIZE) //!< ddr1 end address

/*
*******************************************************************************
**
** system memory definitions
**
*******************************************************************************
*/
#define GK_MMAP_AS211_CODE_SIZE         0x00400000  //!< as211 code size
#define GK_MMAP_USER_DATA_SIZE          0x00100000  //!< user data size
#define GK_MMAP_COMM_DATA_SIZE          0x00003000  // current used 0x3000 (64*64*3 = size * number * cpu)
#define GK_MMAP_ICC_CMD_SIZE            264 // 255+5+2 = 255 byte data + 5 byte ISO header + 2 byte SW1SW2  and 2 byte algin
#define GK_MMAP_ICC_RES_SIZE            264 // 255+5+2 = 255 byte data + 5 byte ISO header + 2 byte SW1SW2


#if (GK_MMAP_DDR0_SIZE == GK_MMAP_DDR_SIZE_1G)
#define GK_MMAP_FRAME_BUFFER_SIZE       0x04000000  //!< Frame buffer size
#define GK_MMAP_DECODER_MODULE_SIZE     0x02000000 //!< decoder module  size
#elif (GK_MMAP_DDR0_SIZE == GK_MMAP_DDR_SIZE_2G)
#define GK_MMAP_FRAME_BUFFER_SIZE       0x08000000  //!< Frame buffer size
#define GK_MMAP_DECODER_MODULE_SIZE     0x04000000 //!< decoder module  size
#else
#define GK_MMAP_FRAME_BUFFER_SIZE       0x04000000  //!< Frame buffer size
#define GK_MMAP_DECODER_MODULE_SIZE     0x02000000 //!< decoder module  size
#endif

#define GK_MMAP_BM_SIZE     			0x01C00000 //!< ALL BM size	  28m bytes
#define GK_MMAP_VBV_BUFFER_SIZE         0x00F00000 //!< vbv data buffer size
#define GK_MMAP_ABV_BUFFER_SIZE         0x00200000 //!< abv data buffer size
#define GK_MMAP_AC3_BUFFER_SIZE         0x00004000 //!< ac3 data buffer size
#define GK_MMAP_TTX_BUFFER_SIZE         0x00004000 //!< ttx data buffer size

#define GK_MMAP_PCR_BUFFER_SIZE         0x00000400 //!< pcr data buffer size
#define GK_MMAP_SCT_BUFFER_SIZE         0x00002000  //!< sct data buffer size
#define GK_MMAP_PSI_BUFFER_SIZE         0x00800000   //!< psi data buffer size
#define GK_MMAP_EMM_BUFFER_SIZE         0x00000C00   //!< emm data buffer size
#define GK_MMAP_PIP_BUFFER_SIZE         0    //!< pip data buffer size


#define GK_MMAP_USER_DATA_START          GK_MMAP_DDR0_START                                  //!< user share data start address
#define GK_MMAP_COMM_DATA_START          GK_MMAP_USER_DATA_START                             //!< communication share data start address
#define GK_MMAP_ICC_CMD_START           (GK_MMAP_COMM_DATA_START + GK_MMAP_COMM_DATA_SIZE)   //!< icc command data start address
#define GK_MMAP_ICC_RES_START           (GK_MMAP_ICC_CMD_START + GK_MMAP_ICC_CMD_SIZE)       //!< icc response data start address
#define GK_MMAP_USER_RESERVED_START     (GK_MMAP_ICC_RES_START + GK_MMAP_ICC_RES_SIZE)       //!< reserved datastart address

#define GK_MMAP_BM_OFFSET          		(GK_MMAP_FRAME_BUFFER_START + GK_MMAP_FRAME_BUFFER_SIZE)
#define GK_MMAP_VBV_BUFFER_ADDR          GK_MMAP_BM_OFFSET                               //!< vbv buffer start address
#define GK_MMAP_ABV_BUFFER_ADDR         (GK_MMAP_VBV_BUFFER_ADDR+GK_MMAP_VBV_BUFFER_SIZE) //!< ABV buffer start address
#define GK_MMAP_AC3_BUFFER_ADDR         (GK_MMAP_ABV_BUFFER_ADDR+GK_MMAP_ABV_BUFFER_SIZE) //!< AC3 buffer start address
#define GK_MMAP_TTX_BUFFER_ADDR         (GK_MMAP_AC3_BUFFER_ADDR+GK_MMAP_AC3_BUFFER_SIZE) //!< TTX buffer start address
#define GK_MMAP_PCR_BUFFER_ADDR         (GK_MMAP_TTX_BUFFER_ADDR+GK_MMAP_TTX_BUFFER_SIZE) //!< PCR buffer start address
#define GK_MMAP_PSI_BUFFER_ADDR         (GK_MMAP_PCR_BUFFER_ADDR+GK_MMAP_PCR_BUFFER_SIZE) //!< PSI buffer start address
#define GK_MMAP_EMM_BUFFER_ADDR         (GK_MMAP_PSI_BUFFER_ADDR+GK_MMAP_PSI_BUFFER_SIZE) //!< PIP buffer start address
#define GK_MMAP_PIP_BUFFER_ADDR         (GK_MMAP_EMM_BUFFER_ADDR+GK_MMAP_EMM_BUFFER_SIZE) //!< PIP buffer start address

#define GK_MMAP_DECODER_MODULE_ADDR     (GK_MMAP_BM_OFFSET + GK_MMAP_BM_SIZE)                               //!< vbv buffer start address
#define GK_MMAP_BUFFERS_END_ADDR        (GK_MMAP_DECODER_MODULE_ADDR+GK_MMAP_DECODER_MODULE_SIZE) //!< end of bm buffer address


/* DSP Debug ports */ 
#define AHB_BASE	0x60000000
#define APB_BASE	0x70000000


#define DSP_DEBUG0_OFFSET               0x100000
#define DSP_DEBUG1_OFFSET               0x110000
#define DSP_DEBUG2_OFFSET               0x120000
#define DSP_DEBUG3_OFFSET               0x130000
#define DSP_DEBUG4_OFFSET               0x140000
#define DSP_DEBUG5_OFFSET               0x150000
#define DSP_DEBUG6_OFFSET               0x160000
#define DSP_DEBUG7_OFFSET               0x170000

#define DSP_DEBUG0_BASE                 (APB_BASE + DSP_DEBUG0_OFFSET)
#define DSP_DEBUG1_BASE                 (APB_BASE + DSP_DEBUG1_OFFSET)
#define DSP_DEBUG2_BASE                 (APB_BASE + DSP_DEBUG2_OFFSET)
#define DSP_DEBUG3_BASE                 (APB_BASE + DSP_DEBUG3_OFFSET)
#define DSP_DEBUG4_BASE                 (APB_BASE + DSP_DEBUG4_OFFSET)
#define DSP_DEBUG5_BASE                 (APB_BASE + DSP_DEBUG5_OFFSET)
#define DSP_DEBUG6_BASE                 (APB_BASE + DSP_DEBUG6_OFFSET)
#define DSP_DEBUG7_BASE                 (APB_BASE + DSP_DEBUG7_OFFSET)

#define MEMD_OFFSET			0x150000
#define CODE_OFFSET			0x160000
#define MEMD_BASE			(APB_BASE + 0x150000)
#define CODE_BASE			(APB_BASE + 0x160000)

#define DSP_DRAM_MAIN_OFFSET		0x0008
#define DSP_DRAM_SUB0_OFFSET		0x0008
#define DSP_DRAM_SUB1_OFFSET		0x8008
#define DSP_CONFIG_MAIN_OFFSET		0x0000
#define DSP_CONFIG_SUB0_OFFSET		0x0000
#define DSP_CONFIG_SUB1_OFFSET		0x8000

#define DSP_DRAM_MAIN_REG		(CODE_BASE + 0x0008)	/* CODE */
#define DSP_DRAM_SUB0_REG		(MEMD_BASE + 0x0008)	/* ME */
#define DSP_DRAM_SUB1_REG		(MEMD_BASE + 0x8008)	/* MD */
#define DSP_CONFIG_MAIN_REG		(CODE_BASE + 0x0000)
#define DSP_CONFIG_SUB0_REG		(MEMD_BASE + 0x0000)
#define DSP_CONFIG_SUB1_REG		(MEMD_BASE + 0x8000)

#define DSP_TEXT_BASE_ADDR_CORE		0x900000
#define DSP_TEXT_BASE_ADDR_MDXF		0x600000
#define DSP_TEXT_BASE_ADDR_MEMD		0x300000


/******************************************/
/* Interrupt numbers of the uITRON kernel */
/******************************************/
#define USBVBUS_INT_VEC	 		0
#define VOUT_INT_VEC	 		1
#define ORC_VOUT1_INT_VEC		1
#define VIN_INT_VEC	 		2
#define VDSP_INT_VEC	 		3
#define USBC_INT_VEC	 		4

#define VIC2_INT_VEC_OFFSET	32
#define VIC2_INT_VEC(x)			((x) + VIC2_INT_VEC_OFFSET)
#define AUDIO_ORC_INT_VEC 		VIC2_INT_VEC(0)
#define DMA_FIOS_INT_VEC 		VIC2_INT_VEC(1)
#define ADC_LEVEL_INT_VEC 		VIC2_INT_VEC(2)
#define VOUT1_SYNC_MISSED_INT_VEC 	VIC2_INT_VEC(3)
#define IDC2_INT_VEC			VIC2_INT_VEC(4)
#define IDSP_LAST_PIXEL_INT_VEC 	VIC2_INT_VEC(5)
#define IDSP_VSYNC_INT_VEC 		VIC2_INT_VEC(6)
#define IDSP_SENSOR_VSYNC_INT_VEC 	VIC2_INT_VEC(7)
#define ORC_VOUT0_INT_VEC		VIC2_INT_VEC(12)

/* * RTOS memory options */
#define KERNEL_RAM_START 0xC0100000
#define KERNEL_NONCACHEBUFFERED_SIZE 0x0050000
#define RAMDISK_RAM_START 0x00000000
#define RAMDISK_RAM_SIZE 0x00000000
#define IDSP_RAM_START 0xC3600000 //0xC2800000
#define IDSP_RAM_SIZE 0x04A00000//0x05800000
/* 1 Gbits = 128 MB*/
#define DRAM_START_ADDR         0xC0000000
#define DRAM_SIZE		0x08000000
#define DRAM_END_ADDR		(DRAM_START_ADDR + DRAM_SIZE - 1)

/* Align 1st payload nicely to the start of the IDSP area */
#define DSP_FW_DOWNLOAD_ADDR	(IDSP_RAM_START - 0x50)

#define IAV_BITS_FIFO_SIZE 0x00E00000
#define PJPEG_FIFO_SIZE 0x00400000

#define RTOS_HEAP_END           (IDSP_RAM_START - 1)
#define RTOS_NCACHED_HEAP_START (RTOS_HEAP_END - KERNEL_NONCACHEBUFFERED_SIZE + 1)
#define RTOS_NCACHED_HEAP_END    RTOS_HEAP_END
#define RTOS_NCACHED_HEAP_SIZE   KERNEL_NONCACHEBUFFERED_SIZE

#endif /* _GK_MMAP_H_ */
