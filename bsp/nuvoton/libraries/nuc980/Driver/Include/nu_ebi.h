/**************************************************************************//**
 * @file     ebi.h
 * @brief    EBI driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_EBI_H__
#define __NU_EBI_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "nuc980.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EBI_Driver EBI Driver
  @{
*/

/** @addtogroup EBI_EXPORTED_CONSTANTS EBI Exported Constants
  @{
*/

#define EBI                  ((EBI_T *)   EBI_BA)

/*---------------------- External Bus Interface Controller -------------------------*/
/**
    @addtogroup EBI External Bus Interface Controller(EBI)
    Memory Mapped Structure for EBI Controller
@{ */


typedef struct
{

    __IO uint32_t CTL0;          /* Offset: 0x00  External Bus Interface Bank0 Control Register */
    __IO uint32_t TCTL0;         /* Offset: 0x04  External Bus Interface Bank0 Timing Control Register */
    __I  uint32_t RESERVE0[2];
    __IO uint32_t CTL1;          /* Offset: 0x10  External Bus Interface Bank1 Control Register */
    __IO uint32_t TCTL1;         /* Offset: 0x14  External Bus Interface Bank1 Timing Control Register */
    __I  uint32_t RESERVE1[2];
    __IO uint32_t CTL2;          /* Offset: 0x20  External Bus Interface Bank1 Control Register */
    __IO uint32_t TCTL2;         /* Offset: 0x24  External Bus Interface Bank1 Timing Control Register */

} EBI_T;



/**
    @addtogroup EBI_CONST EBI Bit Field Definition
    Constant Definitions for EBI Controller
@{ */

#define EBI_CTL_EN_Pos                  (0)                                               /*!< EBI_T::CTL: EN Position \hideinitializer */
#define EBI_CTL_EN_Msk                  (0x1ul << EBI_CTL_EN_Pos)                         /*!< EBI_T::CTL: EN Mask \hideinitializer */

#define EBI_CTL_DW16_Pos                (1)                                               /*!< EBI_T::CTL: DW16 Position \hideinitializer */
#define EBI_CTL_DW16_Msk                (0x1ul << EBI_CTL_DW16_Pos)                       /*!< EBI_T::CTL: DW16 Mask \hideinitializer */

#define EBI_CTL_CSPOLINV_Pos            (2)                                               /*!< EBI_T::CTL: CSPOLINV Position \hideinitializer */
#define EBI_CTL_CSPOLINV_Msk            (0x1ul << EBI_CTL_CSPOLINV_Pos)                   /*!< EBI_T::CTL: CSPOLINV Mask \hideinitializer */

#define EBI_CTL_CACCESS_Pos             (4)                                               /*!< EBI EBICON: CS_PINV Position \hideinitializer */
#define EBI_CTL_CACCESS_Msk             (1ul << EBI_CTL_CACCESS_Pos)                      /*!< EBI EBICON: CS_PINV Mask \hideinitializer */

#define EBI_CTL_MCLKDIV_Pos             (8)                                               /*!< EBI_T::CTL: MCLKDIV Position \hideinitializer */
#define EBI_CTL_MCLKDIV_Msk             (0x7ul << EBI_CTL_MCLKDIV_Pos)                    /*!< EBI_T::CTL: MCLKDIV Mask \hideinitializer */

#define EBI_CTL_WBUFEN_Pos              (24)                                              /*!< EBI_T::CTL: WBUFEN Position \hideinitializer */
#define EBI_CTL_WBUFEN_Msk              (0x1ul << EBI_CTL_WBUFEN_Pos)                     /*!< EBI_T::CTL: WBUFEN Mask \hideinitializer */

#define EBI_TCTL_TACC_Pos               (3)                                               /*!< EBI_T::TCTL: TACC Position \hideinitializer */
#define EBI_TCTL_TACC_Msk               (0x1ful << EBI_TCTL_TACC_Pos)                     /*!< EBI_T::TCTL: TACC Mask \hideinitializer */

#define EBI_TCTL_TAHD_Pos               (8)                                               /*!< EBI_T::TCTL: TAHD Position \hideinitializer */
#define EBI_TCTL_TAHD_Msk               (0x7ul << EBI_TCTL_TAHD_Pos)                      /*!< EBI_T::TCTL: TAHD Mask \hideinitializer */

#define EBI_TCTL_W2X_Pos                (12)                                              /*!< EBI_T::TCTL: W2X Position \hideinitializer */
#define EBI_TCTL_W2X_Msk                (0xful << EBI_TCTL_W2X_Pos)                       /*!< EBI_T::TCTL: W2X Mask \hideinitializer */

#define EBI_TCTL_RAHDOFF_Pos            (22)                                              /*!< EBI_T::TCTL: RAHDOFF Position \hideinitializer */
#define EBI_TCTL_RAHDOFF_Msk            (0x1ul << EBI_TCTL_RAHDOFF_Pos)                   /*!< EBI_T::TCTL: RAHDOFF Mask \hideinitializer */

#define EBI_TCTL_WAHDOFF_Pos            (23)                                              /*!< EBI_T::TCTL: WAHDOFF Position \hideinitializer */
#define EBI_TCTL_WAHDOFF_Msk            (0x1ul << EBI_TCTL_WAHDOFF_Pos)                   /*!< EBI_T::TCTL: WAHDOFF Mask \hideinitializer */

#define EBI_TCTL_R2R_Pos                (24)                                              /*!< EBI_T::TCTL: R2R Position \hideinitializer */
#define EBI_TCTL_R2R_Msk                (0xful << EBI_TCTL_R2R_Pos)                       /*!< EBI_T::TCTL: R2R Mask \hideinitializer */

/**@}*/ /* EBI_CONST */
/**@}*/ /* end of EBI register group */

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
#define EBI_TIMING_NORMAL       0x3UL /*!< EBI timing is normal  \hideinitializer */
#define EBI_TIMING_SLOW         0x4UL /*!< EBI timing is slow \hideinitializer */
#define EBI_TIMING_VERYSLOW     0x5UL /*!< EBI timing is very slow \hideinitializer */
#define EBI_TIMING_SLOWEST      0x6UL /*!< EBI timing is the slowest \hideinitializer */

#define EBI_OPMODE_NORMAL       0x0UL          /*!< EBI bus operate in normal mode \hideinitializer */
#define EBI_OPMODE_CACCESS      (0x1UL << 4)   /*!< EBI bus operate in Continuous Data Access mode \hideinitializer */


/*@}*/ /* end of group EBI_EXPORTED_CONSTANTS */

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
  * @return      None
  *
  * @details     This macro is used to improve EBI write operation for EBI all banks.
  * \hideinitializer
  */
#define EBI_ENABLE_WRITE_BUFFER()           outpw(REG_EBI_CTL0, inpw(REG_EBI_CTL0) | (0x1UL << 24))


/**
  * @brief       Disable EBI Write Buffer
  *
  * @return      None
  *
  * @details     This macro is used to disable EBI write buffer function.
  * \hideinitializer
  */
#define EBI_DISABLE_WRITE_BUFFER()          outpw(REG_EBI_CTL0, (inpw(REG_EBI_CTL0) & ~(0x1UL << 24)) | (0x1UL << 24))

void EBI_Open(uint32_t u32Bank, uint32_t u32DataWidth, uint32_t u32TimingClass, uint32_t u32BusMode, uint32_t u32CSActiveLevel);
void EBI_Close(uint32_t u32Bank);
void EBI_SetBusTiming(uint32_t u32Bank, uint32_t u32TimingConfig, uint32_t u32MclkDiv);

/*@}*/ /* end of group EBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EBI_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_EBI_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
