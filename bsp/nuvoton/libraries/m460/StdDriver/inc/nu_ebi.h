/**************************************************************************//**
 * @file     nu_ebi.h
 * @version  V3.00
 * @brief    External Bus Interface(EBI) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_EBI_H__
#define __NU_EBI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EBI_Driver EBI Driver
  @{
*/

/** @addtogroup EBI_EXPORTED_CONSTANTS EBI Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  Miscellaneous Constant Definitions                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_BANK0_BASE_ADDR     0x60000000UL /*!< EBI bank0 base address \hideinitializer */
#define EBI_BANK1_BASE_ADDR     0x60100000UL /*!< EBI bank1 base address \hideinitializer */
#define EBI_BANK2_BASE_ADDR     0x60200000UL /*!< EBI bank2 base address \hideinitializer */
#define EBI_MAX_SIZE            0x00100000UL /*!< Maximum EBI size for each bank is 1 MB \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Constants for EBI bank number                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_BANK0               0UL    /*!< EBI bank 0 \hideinitializer */
#define EBI_BANK1               1UL    /*!< EBI bank 1 \hideinitializer */
#define EBI_BANK2               2UL    /*!< EBI bank 2 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Constants for EBI data bus width                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_BUSWIDTH_8BIT       8UL   /*!< EBI bus width is 8-bit \hideinitializer */
#define EBI_BUSWIDTH_16BIT      16UL  /*!< EBI bus width is 16-bit \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Constants for EBI CS Active Level                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_CS_ACTIVE_LOW       0UL    /*!< EBI CS active level is low \hideinitializer */
#define EBI_CS_ACTIVE_HIGH      1UL    /*!< EBI CS active level is high \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Constants for EBI MCLK divider and Timing                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define EBI_MCLKDIV_1           0x0UL /*!< EBI output clock(MCLK) is HCLK/1 \hideinitializer */
#define EBI_MCLKDIV_2           0x1UL /*!< EBI output clock(MCLK) is HCLK/2 \hideinitializer */
#define EBI_MCLKDIV_4           0x2UL /*!< EBI output clock(MCLK) is HCLK/4 \hideinitializer */
#define EBI_MCLKDIV_8           0x3UL /*!< EBI output clock(MCLK) is HCLK/8 \hideinitializer */
#define EBI_MCLKDIV_16          0x4UL /*!< EBI output clock(MCLK) is HCLK/16 \hideinitializer */
#define EBI_MCLKDIV_32          0x5UL /*!< EBI output clock(MCLK) is HCLK/32 \hideinitializer */
#define EBI_MCLKDIV_64          0x6UL /*!< EBI output clock(MCLK) is HCLK/64 \hideinitializer */
#define EBI_MCLKDIV_128         0x7UL /*!< EBI output clock(MCLK) is HCLK/128 \hideinitializer */

#define EBI_TIMING_FASTEST      0x0UL /*!< EBI timing is the fastest \hideinitializer */
#define EBI_TIMING_VERYFAST     0x1UL /*!< EBI timing is very fast \hideinitializer */
#define EBI_TIMING_FAST         0x2UL /*!< EBI timing is fast \hideinitializer */
#define EBI_TIMING_NORMAL       0x3UL /*!< EBI timing is normal \hideinitializer */
#define EBI_TIMING_SLOW         0x4UL /*!< EBI timing is slow \hideinitializer */
#define EBI_TIMING_VERYSLOW     0x5UL /*!< EBI timing is very slow \hideinitializer */
#define EBI_TIMING_SLOWEST      0x6UL /*!< EBI timing is the slowest \hideinitializer */

#define EBI_OPMODE_NORMAL       0x0UL                 /*!< EBI bus operate in normal mode \hideinitializer */
#define EBI_OPMODE_CACCESS      (EBI_CTL_CACCESS_Msk) /*!< EBI bus operate in Continuous Data Access mode \hideinitializer */
#define EBI_OPMODE_ADSEPARATE   (EBI_CTL_ADSEPEN_Msk) /*!< EBI bus operate in AD Separate mode \hideinitializer */

/**@}*/ /* end of group EBI_EXPORTED_CONSTANTS */


/** @addtogroup EBI_EXPORTED_FUNCTIONS EBI Exported Functions
  @{
*/

/**
  * @brief      Read 8-bit data on EBI bank0
  *
  * @param[in]  u32Addr     The data address on EBI bank0.
  *
  * @return     8-bit Data
  *
  * @details    This macro is used to read 8-bit data from specify address on EBI bank0.
  * \hideinitializer
  */
#define EBI0_READ_DATA8(u32Addr)            (*((volatile unsigned char *)(EBI_BANK0_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 8-bit data to EBI bank0
  *
  * @param[in]  u32Addr     The data address on EBI bank0.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 8-bit data to specify address on EBI bank0.
  * \hideinitializer
  */
#define EBI0_WRITE_DATA8(u32Addr, u32Data)  (*((volatile unsigned char *)(EBI_BANK0_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 16-bit data on EBI bank0
  *
  * @param[in]  u32Addr     The data address on EBI bank0.
  *
  * @return     16-bit Data
  *
  * @details    This macro is used to read 16-bit data from specify address on EBI bank0.
  * \hideinitializer
  */
#define EBI0_READ_DATA16(u32Addr)           (*((volatile unsigned short *)(EBI_BANK0_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 16-bit data to EBI bank0
  *
  * @param[in]  u32Addr     The data address on EBI bank0.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 16-bit data to specify address on EBI bank0.
  * \hideinitializer
  */
#define EBI0_WRITE_DATA16(u32Addr, u32Data) (*((volatile unsigned short *)(EBI_BANK0_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 32-bit data on EBI bank0
  *
  * @param[in]  u32Addr     The data address on EBI bank0.
  *
  * @return     32-bit Data
  *
  * @details    This macro is used to read 32-bit data from specify address on EBI bank0.
  * \hideinitializer
  */
#define EBI0_READ_DATA32(u32Addr)           (*((volatile unsigned int *)(EBI_BANK0_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 32-bit data to EBI bank0
  *
  * @param[in]  u32Addr     The data address on EBI bank0.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 32-bit data to specify address on EBI bank0.
  * \hideinitializer
  */
#define EBI0_WRITE_DATA32(u32Addr, u32Data) (*((volatile unsigned int *)(EBI_BANK0_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 8-bit data on EBI bank1
  *
  * @param[in]  u32Addr     The data address on EBI bank1.
  *
  * @return     8-bit Data
  *
  * @details    This macro is used to read 8-bit data from specify address on EBI bank1.
  * \hideinitializer
  */
#define EBI1_READ_DATA8(u32Addr)            (*((volatile unsigned char *)(EBI_BANK1_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 8-bit data to EBI bank1
  *
  * @param[in]  u32Addr     The data address on EBI bank1.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 8-bit data to specify address on EBI bank1.
  * \hideinitializer
  */
#define EBI1_WRITE_DATA8(u32Addr, u32Data)  (*((volatile unsigned char *)(EBI_BANK1_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 16-bit data on EBI bank1
  *
  * @param[in]  u32Addr     The data address on EBI bank1.
  *
  * @return     16-bit Data
  *
  * @details    This macro is used to read 16-bit data from specify address on EBI bank1.
  * \hideinitializer
  */
#define EBI1_READ_DATA16(u32Addr)           (*((volatile unsigned short *)(EBI_BANK1_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 16-bit data to EBI bank1
  *
  * @param[in]  u32Addr     The data address on EBI bank1.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 16-bit data to specify address on EBI bank1.
  * \hideinitializer
  */
#define EBI1_WRITE_DATA16(u32Addr, u32Data) (*((volatile unsigned short *)(EBI_BANK1_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 32-bit data on EBI bank1
  *
  * @param[in]  u32Addr     The data address on EBI bank1.
  *
  * @return     32-bit Data
  *
  * @details    This macro is used to read 32-bit data from specify address on EBI bank1.
  * \hideinitializer
  */
#define EBI1_READ_DATA32(u32Addr)           (*((volatile unsigned int *)(EBI_BANK1_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 32-bit data to EBI bank1
  *
  * @param[in]  u32Addr     The data address on EBI bank1.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 32-bit data to specify address on EBI bank1.
  * \hideinitializer
  */
#define EBI1_WRITE_DATA32(u32Addr, u32Data) (*((volatile unsigned int *)(EBI_BANK1_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 8-bit data on EBI bank2
  *
  * @param[in]  u32Addr     The data address on EBI bank2.
  *
  * @return     8-bit Data
  *
  * @details    This macro is used to read 8-bit data from specify address on EBI bank2.
  * \hideinitializer
  */
#define EBI2_READ_DATA8(u32Addr)            (*((volatile unsigned char *)(EBI_BANK2_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 8-bit data to EBI bank2
  *
  * @param[in]  u32Addr     The data address on EBI bank2.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 8-bit data to specify address on EBI bank2.
  * \hideinitializer
  */
#define EBI2_WRITE_DATA8(u32Addr, u32Data)  (*((volatile unsigned char *)(EBI_BANK2_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 16-bit data on EBI bank2
  *
  * @param[in]  u32Addr     The data address on EBI bank2.
  *
  * @return     16-bit Data
  *
  * @details    This macro is used to read 16-bit data from specify address on EBI bank2.
  * \hideinitializer
  */
#define EBI2_READ_DATA16(u32Addr)           (*((volatile unsigned short *)(EBI_BANK2_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 16-bit data to EBI bank2
  *
  * @param[in]  u32Addr     The data address on EBI bank2.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 16-bit data to specify address on EBI bank2.
  * \hideinitializer
  */
#define EBI2_WRITE_DATA16(u32Addr, u32Data) (*((volatile unsigned short *)(EBI_BANK2_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief      Read 32-bit data on EBI bank2
  *
  * @param[in]  u32Addr     The data address on EBI bank2.
  *
  * @return     32-bit Data
  *
  * @details    This macro is used to read 32-bit data from specify address on EBI bank2.
  * \hideinitializer
  */
#define EBI2_READ_DATA32(u32Addr)           (*((volatile unsigned int *)(EBI_BANK2_BASE_ADDR+(u32Addr))))

/**
  * @brief      Write 32-bit data to EBI bank2
  *
  * @param[in]  u32Addr     The data address on EBI bank2.
  * @param[in]  u32Data     Specify data to be written.
  *
  * @return     None
  *
  * @details    This macro is used to write 32-bit data to specify address on EBI bank2.
  * \hideinitializer
  */
#define EBI2_WRITE_DATA32(u32Addr, u32Data) (*((volatile unsigned int *)(EBI_BANK2_BASE_ADDR+(u32Addr))) = (u32Data))

/**
  * @brief       Enable EBI Write Buffer
  *
  * @param       None
  *
  * @return      None
  *
  * @details     This macro is used to improve EBI write operation for all EBI banks.
  * \hideinitializer
  */
#define EBI_ENABLE_WRITE_BUFFER()           (EBI->CTL0 |= EBI_CTL_WBUFEN_Msk);

/**
  * @brief       Disable EBI Write Buffer
  *
  * @param       None
  *
  * @return      None
  *
  * @details     This macro is used to disable EBI write buffer function.
  * \hideinitializer
  */
#define EBI_DISABLE_WRITE_BUFFER()          (EBI->CTL0 &= ~EBI_CTL_WBUFEN_Msk);

void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel);
void EBI_Close(uint32_t u32Bank);
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv);

/**@}*/ /* end of group EBI_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group EBI_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_EBI_H__ */
