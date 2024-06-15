/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
**************************************************************************//*!
*
* @file SD.h
*
* @author
*
* @version
*
* @date May-28-2009
*
* @brief  This file is SD Card Driver Header File
*****************************************************************************/
#ifndef __SD_esdhc_kinetis__
#define __SD_esdhc_kinetis__

/* Includes */
#include "derivative.h"
#include "esdhc_kinetis.h"
#include "usb_msc.h"
#include "types.h"

/* User definitions */
#define SD_BLOCK_512
#define SD_WAIT_CYCLES 10

#if (defined __MK_xxx_H__)
#if (defined MCU_MK40N512VMD100)
#define SD_DE                       (GPIOA_PDIR | GPIO_PSOR_PTSO(16))   /* Card detection (AN0 input register)*/
#define _SD_DE                      GPIOA_PCOR = 1 << 16    /* Card detection (AN0 direction: input) */

#define kSD_Insert  0
#define kSD_Desert  (1<<16)
#elif (defined MCU_MK60N512VMD100)||(defined MCU_MK53N512CMD100) || (defined MCU_MK70F12)
#define SD_DE                       (GPIOE_PDIR | GPIO_PSOR_PTSO(28))/* Card detection (AN0 input register) */
#define _SD_DE                      GPIOE_PCOR = 1 << 28 /* Card detection (AN0 direction: input) */

#define kSD_Insert  0
#define kSD_Desert  (1<<28)
#endif
#endif

#if (defined __MK_xxx_H__)
#if (defined MCU_MK53N512CMD100)
#define SD_WR                      (GPIOC_PDIR | GPIO_PSOR_PTSO(9)) /* Card detection (AN0 input register) */
#define _SD_WR                      GPIOC_PCOR |= 1 << 9    /* Card detection (AN0 direction: input) */

#define kSD_WP      (1<<9)
#define kSD_WnP     0
#else
#define SD_WR                      (GPIOE_PDIR | GPIO_PSOR_PTSO(27))    /* Card detection (AN0 input register) */
#define _SD_WR                      GPIOE_PCOR |= 1 << 27   /* Card detection (AN0 direction: input) */

#define kSD_WP      (1<<27)
#define kSD_WnP     0
#endif
#endif

#ifdef SD_BLOCK_512
#define SD_BLOCK_SIZE   (0x00000200)
#define SD_BLOCK_SHIFT  (9)
#define BLOCK_SIZE      512
#endif


/* TypeDefs */
typedef union
{
   uint_8  bytes[4];
   uint_32 lword;
}T32_8;


typedef union
{
   uint_8  u8[2];
   uint_16 u16;
}T16_8;


/* Prototypes */
uint_8 SD_Init(void);
extern void   SD_Write_Block(PTR_LBA_APP_STRUCT);
extern void   SD_Read_Block(PTR_LBA_APP_STRUCT);
extern void SD_Card_Info(uint_32_ptr max_blocks_ptr, uint_32_ptr block_size_ptr);
#endif /* __SD_esdhc_kinetis__ */

