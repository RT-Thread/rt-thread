/**************************************************************************//**
 * @file    nu_spim.h
 * @version V1.00
 * @brief   M480 series SPIM driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_SPIM_H__
#define __NU_SPIM_H__

/*---------------------------------------------------------------------------------------------------------*/
/* Include related headers                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SPIM_Driver SPIM Driver
  @{
*/


/** @addtogroup SPIM_EXPORTED_CONSTANTS SPIM Exported Constants
  @{
*/

#define SPIM_DMM_MAP_ADDR      0x8000000UL       /*!< DMM mode memory map base address    \hideinitializer */
#define SPIM_DMM_SIZE          0x2000000UL       /*!< DMM mode memory mapping size        \hideinitializer */
#define SPIM_CCM_ADDR          0x20020000UL      /*!< CCM mode memory map base address    \hideinitializer */
#define SPIM_CCM_SIZE          0x8000UL          /*!< CCM mode memory size                \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* SPIM_CTL0 constant definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define SPIM_CTL0_RW_IN(x)              ((x) ? 0UL : (0x1UL << SPIM_CTL0_QDIODIR_Pos))      /*!< SPIM_CTL0: SPI Interface Direction Select \hideinitializer */
#define SPIM_CTL0_BITMODE_SING          (0UL << SPIM_CTL0_BITMODE_Pos)          /*!< SPIM_CTL0: One bit mode (SPI Interface including DO, DI, HOLD, WP) \hideinitializer */
#define SPIM_CTL0_BITMODE_DUAL          (1UL << SPIM_CTL0_BITMODE_Pos)          /*!< SPIM_CTL0: Two bits mode (SPI Interface including D0, D1, HOLD, WP) \hideinitializer */
#define SPIM_CTL0_BITMODE_QUAD          (2UL << SPIM_CTL0_BITMODE_Pos)          /*!< SPIM_CTL0: Four bits mode (SPI Interface including D0, D1, D2, D3) \hideinitializer */
#define SPIM_CTL0_OPMODE_IO             (0UL << SPIM_CTL0_OPMODE_Pos)           /*!< SPIM_CTL0: I/O Mode \hideinitializer */
#define SPIM_CTL0_OPMODE_PAGEWRITE      (1UL << SPIM_CTL0_OPMODE_Pos)           /*!< SPIM_CTL0: Page Write Mode \hideinitializer */
#define SPIM_CTL0_OPMODE_PAGEREAD       (2UL << SPIM_CTL0_OPMODE_Pos)           /*!< SPIM_CTL0: Page Read Mode \hideinitializer */
#define SPIM_CTL0_OPMODE_DIRECTMAP      (3UL << SPIM_CTL0_OPMODE_Pos)           /*!< SPIM_CTL0: Direct Map Mode \hideinitializer */

#define CMD_NORMAL_PAGE_PROGRAM         (0x02UL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Page Program (Page Write Mode Use) \hideinitializer */
#define CMD_NORMAL_PAGE_PROGRAM_4B      (0x12UL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Page Program (Page Write Mode Use) \hideinitializer */
#define CMD_QUAD_PAGE_PROGRAM_WINBOND   (0x32UL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Quad Page program (for Winbond) (Page Write Mode Use) \hideinitializer */
#define CMD_QUAD_PAGE_PROGRAM_MXIC      (0x38UL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Quad Page program (for MXIC) (Page Write Mode Use) \hideinitializer */
#define CMD_QUAD_PAGE_PROGRAM_EON       (0x40UL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Quad Page Program (for EON) (Page Write Mode Use) \hideinitializer */

#define CMD_DMA_NORMAL_READ             (0x03UL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Read Data (Page Read Mode Use) \hideinitializer */
#define CMD_DMA_FAST_READ               (0x0BUL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Fast Read (Page Read Mode Use) \hideinitializer */
#define CMD_DMA_NORMAL_DUAL_READ        (0x3BUL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Fast Read Dual Output (Page Read Mode Use) \hideinitializer */
#define CMD_DMA_FAST_READ_DUAL_OUTPUT   (0x3BUL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Fast Read Dual Output (Page Read Mode Use) \hideinitializer */
#define CMD_DMA_FAST_READ_QUAD_OUTPUT   (0x6BUL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Fast Read Dual Output (Page Read Mode Use) \hideinitializer */
#define CMD_DMA_FAST_DUAL_READ          (0xBBUL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Fast Read Dual Output (Page Read Mode Use) \hideinitializer */
#define CMD_DMA_NORMAL_QUAD_READ        (0xE7UL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Fast Read Quad I/O (Page Read Mode Use) \hideinitializer */
#define CMD_DMA_FAST_QUAD_READ          (0xEBUL << SPIM_CTL0_CMDCODE_Pos)       /*!< SPIM_CTL0: Fast Read Quad I/O (Page Read Mode Use) \hideinitializer */

/** @cond HIDDEN_SYMBOLS */

typedef enum
{
    MFGID_UNKNOW    = 0x00U,
    MFGID_SPANSION  = 0x01U,
    MFGID_EON       = 0x1CU,
    MFGID_ISSI      = 0x7FU,
    MFGID_MXIC      = 0xC2U,
    MFGID_WINBOND   = 0xEFU
}
E_MFGID;

/* Flash opcodes. */
#define OPCODE_WREN             0x06U   /* Write enable */
#define OPCODE_RDSR             0x05U   /* Read status register #1*/
#define OPCODE_WRSR             0x01U   /* Write status register #1 */
#define OPCODE_RDSR2            0x35U   /* Read status register #2*/
#define OPCODE_WRSR2            0x31U   /* Write status register #2 */
#define OPCODE_RDSR3            0x15U   /* Read status register #3*/
#define OPCODE_WRSR3            0x11U   /* Write status register #3 */
#define OPCODE_PP               0x02U   /* Page program (up to 256 bytes) */
#define OPCODE_SE_4K            0x20U   /* Erase 4KB sector */
#define OPCODE_BE_32K           0x52U   /* Erase 32KB block */
#define OPCODE_CHIP_ERASE       0xc7U   /* Erase whole flash chip */
#define OPCODE_BE_64K           0xd8U   /* Erase 64KB block */
#define OPCODE_READ_ID          0x90U   /* Read ID */
#define OPCODE_RDID             0x9fU   /* Read JEDEC ID */
#define OPCODE_BRRD             0x16U   /* SPANSION flash - Bank Register Read command  */
#define OPCODE_BRWR             0x17U   /* SPANSION flash - Bank Register write command */
#define OPCODE_NORM_READ        0x03U   /* Read data bytes */
#define OPCODE_FAST_READ        0x0bU   /* Read data bytes */
#define OPCODE_FAST_DUAL_READ   0x3bU   /* Read data bytes */
#define OPCODE_FAST_QUAD_READ   0x6bU   /* Read data bytes */

/* Used for SST flashes only. */
#define OPCODE_BP               0x02U   /* Byte program */
#define OPCODE_WRDI             0x04U   /* Write disable */
#define OPCODE_AAI_WP           0xadU   /* Auto u32Address increment word program */

/* Used for Macronix flashes only. */
#define OPCODE_EN4B             0xb7U   /* Enter 4-byte mode */
#define OPCODE_EX4B             0xe9U   /* Exit 4-byte mode */

#define OPCODE_RDSCUR           0x2bU
#define OPCODE_WRSCUR           0x2fU

#define OPCODE_RSTEN            0x66U
#define OPCODE_RST              0x99U

#define OPCODE_ENQPI            0x38U
#define OPCODE_EXQPI            0xFFU

/* Status Register bits. */
#define SR_WIP                  0x1U    /* Write in progress */
#define SR_WEL                  0x2U    /* Write enable latch */
#define SR_QE                   0x40U   /* Quad Enable for MXIC */
/* Status Register #2 bits. */
#define SR2_QE                  0x2U    /* Quad Enable for Winbond */
/* meaning of other SR_* bits may differ between vendors */
#define SR_BP0                  0x4U    /* Block protect 0 */
#define SR_BP1                  0x8U    /* Block protect 1 */
#define SR_BP2                  0x10U   /* Block protect 2 */
#define SR_SRWD                 0x80U   /* SR write protect */
#define SR3_ADR                 0x01U   /* 4-byte u32Address mode */

#define SCUR_4BYTE              0x04U   /* 4-byte u32Address mode */

/** @endcond HIDDEN_SYMBOLS */

/*@}*/ /* end of group SPIM_EXPORTED_CONSTANTS */


/** @addtogroup SPIM_EXPORTED_FUNCTIONS SPIM Exported Functions
  @{
*/


/*---------------------------------------------------------------------------------------------------------*/
/*  Define Macros and functions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/

/**
 * @details    Enable cipher.
 * \hideinitializer
 */
#define SPIM_ENABLE_CIPHER()       (SPIM->CTL0 &= ~SPIM_CTL0_CIPHOFF_Msk)

/**
 * @details    Disable cipher.
 * \hideinitializer
 */
#define SPIM_DISABLE_CIPHER()      (SPIM->CTL0 |= SPIM_CTL0_CIPHOFF_Msk)

/**
 * @details    Enable cipher balance
 * \hideinitializer
 */
#define SPIM_ENABLE_BALEN()        (SPIM->CTL0 |= SPIM_CTL0_BALEN_Msk)

/**
 * @details    Disable cipher balance
 * \hideinitializer
 */
#define SPIM_DISABLE_BALEN()       (SPIM->CTL0 &= ~SPIM_CTL0_BALEN_Msk)

/**
 * @details    Set 4-byte address to be enabled/disabled.
 * \hideinitializer
 */
#define SPIM_SET_4BYTE_ADDR_EN(x) \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~SPIM_CTL0_B4ADDREN_Msk)) | (((x) ? 1UL : 0UL) << SPIM_CTL0_B4ADDREN_Pos); \
    } while (0)

/**
 * @details    Enable SPIM interrupt
 * \hideinitializer
 */
#define SPIM_ENABLE_INT()       (SPIM->CTL0 |= SPIM_CTL0_IEN_Msk)

/**
 * @details    Disable SPIM interrupt
 * \hideinitializer
 */
#define SPIM_DISABLE_INT()      (SPIM->CTL0 &= ~SPIM_CTL0_IEN_Msk)

/**
 * @details    Is interrupt flag on.
 * \hideinitializer
 */
#define SPIM_IS_IF_ON()    ((SPIM->CTL0 & SPIM_CTL0_IF_Msk) != 0UL)

/**
 * @details    Clear interrupt flag.
 * \hideinitializer
 */
#define SPIM_CLR_INT() \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~SPIM_CTL0_IF_Msk)) | (1UL << SPIM_CTL0_IF_Pos);  \
    } while (0)

/**
 * @details    Set transmit/receive bit length
 * \hideinitializer
 */
#define SPIM_SET_DATA_WIDTH(x)   \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~SPIM_CTL0_DWIDTH_Msk)) | (((x) - 1U) << SPIM_CTL0_DWIDTH_Pos);  \
    } while (0)

/**
 * @details    Get data transmit/receive bit length setting
 * \hideinitializer
 */
#define SPIM_GET_DATA_WIDTH()   \
    (((SPIM->CTL0 & SPIM_CTL0_DWIDTH_Msk) >> SPIM_CTL0_DWIDTH_Pos)+1U)

/**
 * @details    Set data transmit/receive burst number
 * \hideinitializer
 */
#define SPIM_SET_DATA_NUM(x) \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~SPIM_CTL0_BURSTNUM_Msk)) | (((x) - 1U) << SPIM_CTL0_BURSTNUM_Pos);  \
    } while (0)

/**
 * @details    Get data transmit/receive burst number
 * \hideinitializer
 */
#define SPIM_GET_DATA_NUM() \
    (((SPIM->CTL0 & SPIM_CTL0_BURSTNUM_Msk) >> SPIM_CTL0_BURSTNUM_Pos)+1U)

/**
 * @details    Enable Single Input mode.
 * \hideinitializer
 */
#define SPIM_ENABLE_SING_INPUT_MODE()  \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~(SPIM_CTL0_BITMODE_Msk | SPIM_CTL0_QDIODIR_Msk))) | (SPIM_CTL0_BITMODE_SING | SPIM_CTL0_RW_IN(1));    \
    } while (0)

/**
 * @details    Enable Single Output mode.
 * \hideinitializer
 */
#define SPIM_ENABLE_SING_OUTPUT_MODE() \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~(SPIM_CTL0_BITMODE_Msk | SPIM_CTL0_QDIODIR_Msk))) | (SPIM_CTL0_BITMODE_SING | SPIM_CTL0_RW_IN(0));    \
    } while (0)

/**
 * @details    Enable Dual Input mode.
 * \hideinitializer
 */
#define SPIM_ENABLE_DUAL_INPUT_MODE()  \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~(SPIM_CTL0_BITMODE_Msk | SPIM_CTL0_QDIODIR_Msk))) | (SPIM_CTL0_BITMODE_DUAL | SPIM_CTL0_RW_IN(1U));    \
    } while (0)

/**
 * @details    Enable Dual Output mode.
 * \hideinitializer
 */
#define SPIM_ENABLE_DUAL_OUTPUT_MODE() \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~(SPIM_CTL0_BITMODE_Msk | SPIM_CTL0_QDIODIR_Msk))) | (SPIM_CTL0_BITMODE_DUAL | SPIM_CTL0_RW_IN(0U));    \
    } while (0)

/**
 * @details    Enable Quad Input mode.
 * \hideinitializer
 */
#define SPIM_ENABLE_QUAD_INPUT_MODE()  \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~(SPIM_CTL0_BITMODE_Msk | SPIM_CTL0_QDIODIR_Msk))) | (SPIM_CTL0_BITMODE_QUAD | SPIM_CTL0_RW_IN(1U));    \
    } while (0)

/**
 * @details    Enable Quad Output mode.
 * \hideinitializer
 */
#define SPIM_ENABLE_QUAD_OUTPUT_MODE() \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~(SPIM_CTL0_BITMODE_Msk | SPIM_CTL0_QDIODIR_Msk))) | (SPIM_CTL0_BITMODE_QUAD | SPIM_CTL0_RW_IN(0U));    \
    } while (0)

/**
 * @details    Set suspend interval which ranges between 0 and 15.
 * \hideinitializer
 */
#define SPIM_SET_SUSP_INTVL(x) \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~SPIM_CTL0_SUSPITV_Msk)) | ((x) << SPIM_CTL0_SUSPITV_Pos);    \
    } while (0)

/**
 * @details    Get suspend interval setting
 * \hideinitializer
 */
#define SPIM_GET_SUSP_INTVL() \
    ((SPIM->CTL0 & SPIM_CTL0_SUSPITV_Msk) >> SPIM_CTL0_SUSPITV_Pos)

/**
 * @details    Set operation mode.
 * \hideinitializer
 */
#define SPIM_SET_OPMODE(x)  \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~SPIM_CTL0_OPMODE_Msk)) | (x); \
    } while (0)

/**
 * @details    Get operation mode.
 * \hideinitializer
 */
#define SPIM_GET_OP_MODE()         (SPIM->CTL0 & SPIM_CTL0_OPMODE_Msk)

/**
 * @details    Set SPIM mode.
 * \hideinitializer
 */
#define SPIM_SET_SPIM_MODE(x)    \
    do {    \
        SPIM->CTL0 = (SPIM->CTL0 & (~SPIM_CTL0_CMDCODE_Msk)) | (x);   \
    } while (0)

/**
 * @details    Get SPIM mode.
 * \hideinitializer
 */
#define SPIM_GET_SPIM_MODE()       (SPIM->CTL0 & SPIM_CTL0_CMDCODE_Msk)

/**
 * @details    Start operation.
 * \hideinitializer
 */
#define SPIM_SET_GO()              (SPIM->CTL1 |= SPIM_CTL1_SPIMEN_Msk)

/**
 * @details    Is engine busy.
 * \hideinitializer
 */
#define SPIM_IS_BUSY()             (SPIM->CTL1 & SPIM_CTL1_SPIMEN_Msk)

/**
 * @details    Wait for free.
 * \hideinitializer
 */
#define SPIM_WAIT_FREE()   \
    do {    \
        while (SPIM->CTL1 & SPIM_CTL1_SPIMEN_Msk) { }   \
    } while (0)

/**
 * @details    Enable cache.
 * \hideinitializer
 */
#define SPIM_ENABLE_CACHE()        (SPIM->CTL1 &= ~SPIM_CTL1_CACHEOFF_Msk)

/**
 * @details    Disable cache.
 * \hideinitializer
 */
#define SPIM_DISABLE_CACHE()       (SPIM->CTL1 |= SPIM_CTL1_CACHEOFF_Msk)

/**
 * @details    Is cache enabled.
 * \hideinitializer
 */
#define SPIM_IS_CACHE_EN()         ((SPIM->CTL1 & SPIM_CTL1_CACHEOFF_Msk) ? 0 : 1)

/**
 * @details    Enable CCM
 * \hideinitializer
 */
#define SPIM_ENABLE_CCM()          (SPIM->CTL1 |= SPIM_CTL1_CCMEN_Msk)

/**
 * @details    Disable CCM.
 * \hideinitializer
 */
#define SPIM_DISABLE_CCM()         (SPIM->CTL1 &= ~SPIM_CTL1_CCMEN_Msk)

/**
 * @details    Is CCM enabled.
 * \hideinitializer
 */
#define SPIM_IS_CCM_EN()           ((SPIM->CTL1 & SPIM_CTL1_CCMEN_Msk) >> SPIM_CTL1_CCMEN_Pos)

/**
 * @details    Invalidate cache.
 * \hideinitializer
 */
#define SPIM_INVALID_CACHE()       (SPIM->CTL1 |= SPIM_CTL1_CDINVAL_Msk)

/**
 * @details    Set SS(Select Active) to active level.
 * \hideinitializer
 */
#define SPIM_SET_SS_EN(x) \
    do {    \
        (SPIM->CTL1 = (SPIM->CTL1 & (~SPIM_CTL1_SS_Msk)) |  ((! (x) ? 1UL : 0UL) << SPIM_CTL1_SS_Pos)); \
    } while (0)

/**
 * @details    Is SS(Select Active) in active level.
 * \hideinitializer
 */
#define SPIM_GET_SS_EN() \
    (!(SPIM->CTL1 & SPIM_CTL1_SS_Msk))

/**
 * @details    Set active level of slave select to be high/low.
 * \hideinitializer
 */
#define SPIM_SET_SS_ACTLVL(x) \
    do {    \
        (SPIM->CTL1 = (SPIM->CTL1 & (~SPIM_CTL1_SSACTPOL_Msk)) | ((!! (x) ? 1UL : 0UL) << SPIM_CTL1_SSACTPOL_Pos));   \
    } while (0)

/**
 * @details    Set idle time interval
 * \hideinitializer
 */
#define SPIM_SET_IDL_INTVL(x) \
    do {    \
       SPIM->CTL1 = (SPIM->CTL1 & (~SPIM_CTL1_IDLETIME_Msk)) | ((x) << SPIM_CTL1_IDLETIME_Pos);  \
    } while (0)

/**
 * @details    Get idle time interval setting
 * \hideinitializer
 */
#define SPIM_GET_IDL_INTVL() \
    ((SPIM->CTL1 & SPIM_CTL1_IDLETIME_Msk) >> SPIM_CTL1_IDLETIME_Pos)

/**
 * @details    Set SPIM clock divider
 * \hideinitializer
 */
#define SPIM_SET_CLOCK_DIVIDER(x)    \
    do {    \
       SPIM->CTL1 = (SPIM->CTL1 & (~SPIM_CTL1_DIVIDER_Msk)) | ((x) << SPIM_CTL1_DIVIDER_Pos);    \
    } while (0)

/**
 * @details    Get SPIM current clock divider setting
 * \hideinitializer
 */
#define SPIM_GET_CLOCK_DIVIDER()   \
    ((SPIM->CTL1 & SPIM_CTL1_DIVIDER_Msk) >> SPIM_CTL1_DIVIDER_Pos)

/**
 * @details    Set SPI flash deselect time interval of DMA write mode
 * \hideinitializer
 */
#define SPIM_SET_RXCLKDLY_DWDELSEL(x) \
    do {    \
        (SPIM->RXCLKDLY = (SPIM->RXCLKDLY & (~SPIM_RXCLKDLY_DWDELSEL_Msk)) |  ((x) << SPIM_RXCLKDLY_DWDELSEL_Pos)); \
    } while (0)

/**
 * @details    Get SPI flash deselect time interval of DMA write mode
 * \hideinitializer
 */
#define SPIM_GET_RXCLKDLY_DWDELSEL() \
    ((SPIM->RXCLKDLY & SPIM_RXCLKDLY_DWDELSEL_Msk) >> SPIM_RXCLKDLY_DWDELSEL_Pos)

/**
 * @details    Set sampling clock delay selection for received data
 * \hideinitializer
 */
#define SPIM_SET_RXCLKDLY_RDDLYSEL(x) \
    do {    \
        (SPIM->RXCLKDLY = (SPIM->RXCLKDLY & (~SPIM_RXCLKDLY_RDDLYSEL_Msk)) |  ((x) << SPIM_RXCLKDLY_RDDLYSEL_Pos)); \
    } while (0)

/**
 * @details    Get sampling clock delay selection for received data
 * \hideinitializer
 */
#define SPIM_GET_RXCLKDLY_RDDLYSEL() \
    ((SPIM->RXCLKDLY & SPIM_RXCLKDLY_RDDLYSEL_Msk) >> SPIM_RXCLKDLY_RDDLYSEL_Pos)

/**
 * @details    Set sampling clock edge selection for received data
 * \hideinitializer
 */
#define SPIM_SET_RXCLKDLY_RDEDGE() \
    (SPIM->RXCLKDLY |= SPIM_RXCLKDLY_RDEDGE_Msk); \

/**
 * @details    Get sampling clock edge selection for received data
 * \hideinitializer
 */
#define SPIM_CLR_RXCLKDLY_RDEDGE() \
    (SPIM->RXCLKDLY &= ~SPIM_RXCLKDLY_RDEDGE_Msk)

/**
 * @details    Set mode bits data for continuous read mode
 * \hideinitializer
 */
#define SPIM_SET_DMMCTL_CRMDAT(x) \
    do {    \
        (SPIM->DMMCTL = (SPIM->DMMCTL & (~SPIM_DMMCTL_CRMDAT_Msk)) |  ((x) << SPIM_DMMCTL_CRMDAT_Pos)) | SPIM_DMMCTL_CREN_Msk; \
    } while (0)

/**
 * @details    Get mode bits data for continuous read mode
 * \hideinitializer
 */
#define SPIM_GET_DMMCTL_CRMDAT() \
    ((SPIM->DMMCTL & SPIM_DMMCTL_CRMDAT_Msk) >> SPIM_DMMCTL_CRMDAT_Pos)

/**
 * @details    Set DMM mode SPI flash deselect time
 * \hideinitializer
 */
#define SPIM_DMM_SET_DESELTIM(x) \
    do {    \
        SPIM->DMMCTL = (SPIM->DMMCTL & ~SPIM_DMMCTL_DESELTIM_Msk) | (((x) & 0x1FUL) << SPIM_DMMCTL_DESELTIM_Pos);   \
    } while (0)

/**
 * @details    Get current DMM mode SPI flash deselect time setting
 * \hideinitializer
 */
#define SPIM_DMM_GET_DESELTIM() \
        ((SPIM->DMMCTL & SPIM_DMMCTL_DESELTIM_Msk) >> SPIM_DMMCTL_DESELTIM_Pos)

/**
 * @details    Enable DMM mode burst wrap mode
 * \hideinitializer
 */
#define SPIM_DMM_ENABLE_BWEN()         (SPIM->DMMCTL |= SPIM_DMMCTL_BWEN_Msk)

/**
 * @details    Disable DMM mode burst wrap mode
 * \hideinitializer
 */
#define SPIM_DMM_DISABLE_BWEN()        (SPIM->DMMCTL &= ~SPIM_DMMCTL_BWEN_Msk)

/**
 * @details    Enable DMM mode continuous read mode
 * \hideinitializer
 */
#define SPIM_DMM_ENABLE_CREN()         (SPIM->DMMCTL |= SPIM_DMMCTL_CREN_Msk)

/**
 * @details    Disable DMM mode continuous read mode
 * \hideinitializer
 */
#define SPIM_DMM_DISABLE_CREN()        (SPIM->DMMCTL &= ~SPIM_DMMCTL_CREN_Msk)

/**
 * @details    Set DMM mode SPI flash active SCLK time
 * \hideinitializer
 */
#define SPIM_DMM_SET_ACTSCLKT(x) \
    do {    \
        SPIM->DMMCTL = (SPIM->DMMCTL & ~SPIM_DMMCTL_ACTSCLKT_Msk) | (((x) & 0xFUL) << SPIM_DMMCTL_ACTSCLKT_Pos) | SPIM_DMMCTL_UACTSCLK_Msk;   \
    } while (0)

/**
 * @details    Set SPI flash active SCLK time as SPIM default
 * \hideinitializer
 */
#define SPIM_DMM_SET_DEFAULT_ACTSCLK()     (SPIM->DMMCTL &= ~SPIM_DMMCTL_UACTSCLK_Msk)

/**
 * @details    Set dummy cycle number (Only for DMM mode and DMA mode)
 * \hideinitializer
 */
#define SPIM_SET_DCNUM(x) \
    do {    \
        SPIM->CTL2 = (SPIM->CTL2 & ~SPIM_CTL2_DCNUM_Msk) | (((x) & 0x1FUL) << SPIM_CTL2_DCNUM_Pos) | SPIM_CTL2_USETEN_Msk;   \
    } while (0)

/**
 * @details    Set dummy cycle number (Only for DMM mode and DMA mode) as SPIM default
 * \hideinitializer
 */
#define SPIM_SET_DEFAULT_DCNUM(x)           (SPIM->CTL2 &= ~SPIM_CTL2_USETEN_Msk)



/*---------------------------------------------------------------------------------------------------------*/
/* Define Function Prototypes                                                                              */
/*---------------------------------------------------------------------------------------------------------*/


int  SPIM_InitFlash(int clrWP);
uint32_t SPIM_GetSClkFreq(void);
void SPIM_ReadJedecId(uint8_t idBuf[], uint32_t u32NRx, uint32_t u32NBit);
int  SPIM_Enable_4Bytes_Mode(int isEn, uint32_t u32NBit);
int  SPIM_Is4ByteModeEnable(uint32_t u32NBit);

void SPIM_ChipErase(uint32_t u32NBit, int isSync);
void SPIM_EraseBlock(uint32_t u32Addr, int is4ByteAddr, uint8_t u8ErsCmd, uint32_t u32NBit, int isSync);

void SPIM_IO_Write(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx, uint8_t pu8TxBuf[], uint8_t wrCmd, uint32_t u32NBitCmd, uint32_t u32NBitAddr, uint32_t u32NBitDat);
void SPIM_IO_Read(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NRx, uint8_t pu8RxBuf[], uint8_t rdCmd, uint32_t u32NBitCmd, uint32_t u32NBitAddr, uint32_t u32NBitDat, int u32NDummy);

void SPIM_DMA_Write(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx, uint8_t pu8TxBuf[], uint32_t wrCmd);
void SPIM_DMA_Read(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NRx, uint8_t pu8RxBuf[], uint32_t u32RdCmd, int isSync);

void SPIM_EnterDirectMapMode(int is4ByteAddr, uint32_t u32RdCmd, uint32_t u32IdleIntvl);
void SPIM_ExitDirectMapMode(void);

void SPIM_SetQuadEnable(int isEn, uint32_t u32NBit);

void SPIM_WinbondUnlock(uint32_t u32NBit);

/*@}*/ /* end of group SPIM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SPIM_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_SPIM_H__ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
