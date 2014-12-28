/**************************************************************************//**
 * @file     ebi.h
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series EBI driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EBI_H__
#define __EBI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_EBI_Driver EBI Driver
  @{
*/

/** @addtogroup M051_EBI_EXPORTED_CONSTANTS EBI Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  Miscellaneous Constant Definitions                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_BASE_ADDR           0x60000000UL /*!< EBI base address */
#define EBI_MAX_SIZE            0x00020000UL /*!< Maximum EBI size */

/*---------------------------------------------------------------------------------------------------------*/
/*  Constants for EBI data bus width                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_BUSWIDTH_8BIT       8     /*!< EBI bus width is 8-bit */
#define EBI_BUSWIDTH_16BIT      16    /*!< EBI bus width is 16-bit */

/*---------------------------------------------------------------------------------------------------------*/
/*  Constants for EBI MCLK divider and Timing                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_MCLKDIV_1           0x0UL /*!< EBI output clock(MCLK) is HCLK/1 */
#define EBI_MCLKDIV_2           0x1UL /*!< EBI output clock(MCLK) is HCLK/2 */
#define EBI_MCLKDIV_4           0x2UL /*!< EBI output clock(MCLK) is HCLK/4 */
#define EBI_MCLKDIV_8           0x3UL /*!< EBI output clock(MCLK) is HCLK/8 */
#define EBI_MCLKDIV_16          0x4UL /*!< EBI output clock(MCLK) is HCLK/16 */
#define EBI_MCLKDIV_32          0x5UL /*!< EBI output clock(MCLK) is HCLK/32 */

#define EBI_TIMING_FASTEST      0x0UL /*!< EBI timing is the fastest */
#define EBI_TIMING_VERYFAST     0x1UL /*!< EBI timing is very fast */
#define EBI_TIMING_FAST         0x2UL /*!< EBI timing is fast */
#define EBI_TIMING_NORMAL       0x3UL /*!< EBI timing is normal  */
#define EBI_TIMING_SLOW         0x4UL /*!< EBI timing is slow */
#define EBI_TIMING_VERYSLOW     0x5UL /*!< EBI timing is very slow */
#define EBI_TIMING_SLOWEST      0x6UL /*!< EBI timing is the slowest */

/*@}*/ /* end of group M051_EBI_EXPORTED_CONSTANTS */


/** @addtogroup M051_EBI_EXPORTED_FUNCTIONS EBI Exported Functions
  @{
*/

/**
  * @details    This macro read 8-bit data from specify EBI address.
  */
#define EBI_READ_DATA8(u32Addr)             (*((volatile unsigned char *)(EBI_BASE_ADDR+u32Addr)))

/**
  * @details    This macro write 8-bit data to specify EBI address.
  */
#define EBI_WRITE_DATA8(u32Addr, u32Data)   (*((volatile unsigned char *)(EBI_BASE_ADDR+u32Addr)) = u32Data)

/**
  * @details    This macro read 16-bit data from specify EBI address.
  */
#define EBI_READ_DATA16(u32Addr)            (*((volatile unsigned short *)(EBI_BASE_ADDR+u32Addr)))

/**
  * @details    This macro write 16-bit data to specify EBI address.
  */
#define EBI_WRITE_DATA16(u32Addr, u32Data)  (*((volatile unsigned short *)(EBI_BASE_ADDR+u32Addr)) = u32Data)

/**
  * @details    This macro read 32-bit data from specify EBI address.
  */
#define EBI_READ_DATA32(u32Addr)            (*((volatile unsigned int *)(EBI_BASE_ADDR+u32Addr)))

/**
  * @details    This macro write 32-bit data to specify EBI address.
  */
#define EBI_WRITE_DATA32(u32Addr, u32Data)  (*((volatile unsigned int *)(EBI_BASE_ADDR+u32Addr)) = u32Data)Write 32-bit data to EBI bank 0

void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel);
void EBI_Close(uint32_t u32Bank);
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv);

/*@}*/ /* end of group M051_EBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_EBI_Driver */

/*@}*/ /* end of group M051_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__EBI_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
