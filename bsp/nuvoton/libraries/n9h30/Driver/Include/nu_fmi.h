/**************************************************************************//**
 * @file     fmi.h
 * @brief    N9H30 FMI eMMC driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#ifndef __NU_FMI_H__
#define __NU_FMI_H__

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_FMI_Driver FMI Driver
  @{
*/


/** @addtogroup N9H30_FMI_EXPORTED_CONSTANTS FMI Exported Constants
  @{
*/


#ifdef __cplusplus
    #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
    #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */

typedef struct
{
    __IO uint32_t FB[32];                /*!< Shared Buffer (FIFO)                                                      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[224];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DMACTL;                /*!< [0x0400] DMA Control and Status Register                                  */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DMASA;                 /*!< [0x0408] DMA Transfer Starting Address Register                           */
    __I  uint32_t DMABCNT;               /*!< [0x040c] DMA Transfer Byte Count Register                                 */
    __IO uint32_t DMAINTEN;              /*!< [0x0410] DMA Interrupt Enable Control Register                            */
    __IO uint32_t DMAINTSTS;             /*!< [0x0414] DMA Interrupt Status Register                                    */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[250];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t GCTL;                  /*!< [0x0800] Global Control and Status Register                               */
    __IO uint32_t GINTEN;                /*!< [0x0804] Global Interrupt Control Register                                */
    __I  uint32_t GINTSTS;               /*!< [0x0808] Global Interrupt Status Register                                 */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CTL;                   /*!< [0x0820] SD Control and Status Register                                   */
    __IO uint32_t CMDARG;                /*!< [0x0824] SD Command Argument Register                                     */
    __IO uint32_t INTEN;                 /*!< [0x0828] SD Interrupt Control Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x082c] SD Interrupt Status Register                                     */
    __I  uint32_t RESP0;                 /*!< [0x0830] SD Receiving Response Token Register 0                           */
    __I  uint32_t RESP1;                 /*!< [0x0834] SD Receiving Response Token Register 1                           */
    __IO uint32_t BLEN;                  /*!< [0x0838] SD Block Length Register                                         */
    __IO uint32_t TOUT;                  /*!< [0x083c] SD Response/Data-in Time-out Register                            */
    __IO uint32_t ECTL;                  /*!< [0x0840] SD Host Extend Control Register                                  */

    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[24];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t NANDCTL;               /*!< [0x08A0] NAND Flash Control Register                                      */
    __IO uint32_t NANDTMCTL;             /*!< [0x08A4] NAND Flash Timing Control Register                               */
    __IO uint32_t NANDINTEN;             /*!< [0x08A8] NAND Flash Interrupt Enable Register                             */
    __IO uint32_t NANDINTSTS;            /*!< [0x08AC] NAND Flash Interrupt Status Register                             */
    __O  uint32_t NANDCMD;               /*!< [0x08B0] NAND Flash Command Port Registe                                  */
    __O  uint32_t NANDADDR;              /*!< [0x08B4] NAND Flash Address Port Register                                 */
    __IO uint32_t NANDDATA;              /*!< [0x08B8] NAND Flash Data Port Registe                                     */
    __IO uint32_t NANDRACTL;             /*!< [0x08BC] NAND Flash Redundant Area Control Register                       */
    __IO uint32_t NANDECTL;              /*!< [0x08C0] NAND Flash Extend Control Register                               */
    __I  uint32_t NANDECCES[4];          /*!< [0x08D0] NAND Flash ECC Error Status Register                             */
    __IO uint32_t NANDPROTA[2];          /*!< [0x08E0] NAND Flash Protect Region End Address Register                   */

    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE5[6];
    /// @endcond //HIDDEN_SYMBOLS

    __I  uint32_t NANDECCEA[12];         /*!< [0x0900] NAND Flash ECC Error Byte Address n Register                     */

    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE6[12];
    /// @endcond //HIDDEN_SYMBOLS

   __I  uint32_t NANDECCED[6];           /*!< [0x0960] NAND Flash ECC Error Data Register N                             */

    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE7[34];
    /// @endcond //HIDDEN_SYMBOLS

    __IO uint32_t NANDRA[118];           /*!< [0x0A00]NAND Flash Redundant Area Word n = 0, 1..117                      */

} FMI_T;

#define FMI0                  ((FMI_T *)   FMI_BA)

/**
    @addtogroup FMI_CONST FMI Bit Field Definition
    Constant Definitions for FMI Controller
@{ */

#define FMI_DMACTL_DMAEN_Pos             (0)                                               /*!< FMI DMACTL: DMAEN Position             */
#define FMI_DMACTL_DMAEN_Msk             (0x1ul << FMI_DMACTL_DMAEN_Pos)                   /*!< FMI DMACTL: DMAEN Mask                 */

#define FMI_DMACTL_DMARST_Pos            (1)                                               /*!< FMI DMACTL: DMARST Position            */
#define FMI_DMACTL_DMARST_Msk            (0x1ul << FMI_DMACTL_DMARST_Pos)                  /*!< FMI DMACTL: DMARST Mask                */

#define FMI_DMACTL_SGEN_Pos              (3)                                               /*!< FMI DMACTL: SGEN Position              */
#define FMI_DMACTL_SGEN_Msk              (0x1ul << FMI_DMACTL_SGEN_Pos)                    /*!< FMI DMACTL: SGEN Mask                  */

#define FMI_DMACTL_DMABUSY_Pos           (9)                                               /*!< FMI DMACTL: DMABUSY Position           */
#define FMI_DMACTL_DMABUSY_Msk           (0x1ul << FMI_DMACTL_DMABUSY_Pos)                 /*!< FMI DMACTL: DMABUSY Mask               */

#define FMI_DMASA_ORDER_Pos              (0)                                               /*!< FMI DMASA: ORDER Position              */
#define FMI_DMASA_ORDER_Msk              (0x1ul << FMI_DMASA_ORDER_Pos)                    /*!< FMI DMASA: ORDER Mask                  */

#define FMI_DMASA_DMASA_Pos              (1)                                               /*!< FMI DMASA: DMASA Position              */
#define FMI_DMASA_DMASA_Msk              (0x7ffffffful << FMI_DMASA_DMASA_Pos)             /*!< FMI DMASA: DMASA Mask                  */

#define FMI_DMABCNT_BCNT_Pos             (0)                                               /*!< FMI DMABCNT: BCNT Position             */
#define FMI_DMABCNT_BCNT_Msk             (0x3fffffful << FMI_DMABCNT_BCNT_Pos)             /*!< FMI DMABCNT: BCNT Mask                 */

#define FMI_DMAINTEN_ABORTIEN_Pos        (0)                                               /*!< FMI DMAINTEN: ABORTIEN Position        */
#define FMI_DMAINTEN_ABORTIEN_Msk        (0x1ul << FMI_DMAINTEN_ABORTIEN_Pos)              /*!< FMI DMAINTEN: ABORTIEN Mask            */

#define FMI_DMAINTEN_WEOTIEN_Pos         (1)                                               /*!< FMI DMAINTEN: WEOTIEN Position         */
#define FMI_DMAINTEN_WEOTIEN_Msk         (0x1ul << FMI_DMAINTEN_WEOTIEN_Pos)               /*!< FMI DMAINTEN: WEOTIEN Mask             */

#define FMI_DMAINTSTS_ABORTIF_Pos        (0)                                               /*!< FMI DMAINTSTS: ABORTIF Position        */
#define FMI_DMAINTSTS_ABORTIF_Msk        (0x1ul << FMI_DMAINTSTS_ABORTIF_Pos)              /*!< FMI DMAINTSTS: ABORTIF Mask            */

#define FMI_DMAINTSTS_WEOTIF_Pos         (1)                                               /*!< FMI DMAINTSTS: WEOTIF Position         */
#define FMI_DMAINTSTS_WEOTIF_Msk         (0x1ul << FMI_DMAINTSTS_WEOTIF_Pos)               /*!< FMI DMAINTSTS: WEOTIF Mask             */

#define FMI_CTL_CTLRST_Pos               (0)                                               /*!< FMI CTL: CTLRST Position               */
#define FMI_CTL_CTLRST_Msk               (0x1ul << FMI_CTL_CTLRST_Pos)                     /*!< FMI CTL: CTLRST Mask                   */

#define FMI_CTL_EMMCEN_Pos               (1)                                               /*!< FMI CTL: EMMCEN Position               */
#define FMI_CTL_EMMCEN_Msk               (0x1ul << FMI_CTL_EMMCEN_Pos)                     /*!< FMI CTL: EMMCEN Mask                   */

#define FMI_CTL_NANDEN_Pos               (1)                                               /*!< FMI CTL: NANDEN Position               */
#define FMI_CTL_NANDEN_Msk               (0x1ul << FMI_CTL_NANDEN_Pos)                     /*!< FMI CTL: NANDEN Mask                   */

#define FMI_INTEN_DTAIEN_Pos             (0)                                               /*!< FMI INTEN: DTAIEN Position             */
#define FMI_INTEN_DTAIEN_Msk             (0x1ul << FMI_INTEN_DTAIEN_Pos)                   /*!< FMI INTEN: DTAIEN Mask                 */

#define FMI_INTSTS_DTAIF_Pos            (0)                                                /*!< FMI INTSTS: DTAIF Position             */
#define FMI_INTSTS_DTAIF_Msk            (0x1ul << FMI_INTSTS_DTAIF_Pos)                    /*!< FMI INTSTS: DTAIF Mask                 */

#define FMI_EMMCCTL_COEN_Pos            (0)                                                /*!< FMI EMMCCTL: COEN Position             */
#define FMI_EMMCCTL_COEN_Msk            (0x1ul << FMI_EMMCCTL_COEN_Pos)                    /*!< FMI EMMCCTL: COEN Mask                 */

#define FMI_EMMCCTL_RIEN_Pos            (1)                                                /*!< FMI EMMCCTL: RIEN Position             */
#define FMI_EMMCCTL_RIEN_Msk            (0x1ul << FMI_EMMCCTL_RIEN_Pos)                    /*!< FMI EMMCCTL: RIEN Mask                 */

#define FMI_EMMCCTL_DIEN_Pos            (2)                                                /*!< FMI EMMCCTL: DIEN Position             */
#define FMI_EMMCCTL_DIEN_Msk            (0x1ul << FMI_EMMCCTL_DIEN_Pos)                    /*!< FMI EMMCCTL: DIEN Mask                 */

#define FMI_EMMCCTL_DOEN_Pos            (3)                                                /*!< FMI EMMCCTL: DOEN Position             */
#define FMI_EMMCCTL_DOEN_Msk            (0x1ul << FMI_EMMCCTL_DOEN_Pos)                    /*!< FMI EMMCCTL: DOEN Mask                 */

#define FMI_EMMCCTL_R2EN_Pos            (4)                                                /*!< FMI EMMCCTL: R2EN Position             */
#define FMI_EMMCCTL_R2EN_Msk            (0x1ul << FMI_EMMCCTL_R2EN_Pos)                    /*!< FMI EMMCCTL: R2EN Mask                 */

#define FMI_EMMCCTL_CLK74OEN_Pos        (5)                                                /*!< FMI EMMCCTL: CLK74OEN Position         */
#define FMI_EMMCCTL_CLK74OEN_Msk        (0x1ul << FMI_EMMCCTL_CLK74OEN_Pos)                /*!< FMI EMMCCTL: CLK74OEN Mask             */

#define FMI_EMMCCTL_CLK8OEN_Pos         (6)                                                /*!< FMI EMMCCTL: CLK8OEN Position          */
#define FMI_EMMCCTL_CLK8OEN_Msk         (0x1ul << FMI_EMMCCTL_CLK8OEN_Pos)                 /*!< FMI EMMCCTL: CLK8OEN Mask              */

#define FMI_EMMCCTL_CLKKEEP0_Pos        (7)                                                /*!< FMI EMMCCTL: CLKKEEP0 Position         */
#define FMI_EMMCCTL_CLKKEEP0_Msk        (0x1ul << FMI_EMMCCTL_CLKKEEP0_Pos)                /*!< FMI EMMCCTL: CLKKEEP0 Mask             */

#define FMI_EMMCCTL_CMDCODE_Pos         (8)                                                /*!< FMI EMMCCTL: CMDCODE Position          */
#define FMI_EMMCCTL_CMDCODE_Msk         (0x3ful << FMI_EMMCCTL_CMDCODE_Pos)                /*!< FMI EMMCCTL: CMDCODE Mask              */

#define FMI_EMMCCTL_CTLRST_Pos          (14)                                               /*!< FMI EMMCCTL: CTLRST Position           */
#define FMI_EMMCCTL_CTLRST_Msk          (0x1ul << FMI_EMMCCTL_CTLRST_Pos)                  /*!< FMI EMMCCTL: CTLRST Mask               */

#define FMI_EMMCCTL_DBW_Pos             (15)                                               /*!< FMI EMMCCTL: DBW Position              */
#define FMI_EMMCCTL_DBW_Msk             (0x1ul << FMI_EMMCCTL_DBW_Pos)                     /*!< FMI EMMCCTL: DBW Mask                  */

#define FMI_EMMCCTL_BLKCNT_Pos          (16)                                               /*!< FMI EMMCCTL: BLKCNT Position           */
#define FMI_EMMCCTL_BLKCNT_Msk          (0xfful << FMI_EMMCCTL_BLKCNT_Pos)                 /*!< FMI EMMCCTL: BLKCNT Mask               */

#define FMI_EMMCCTL_SDNWR_Pos           (24)                                               /*!< FMI EMMCCTL: SDNWR Position            */
#define FMI_EMMCCTL_SDNWR_Msk           (0xful << FMI_EMMCCTL_SDNWR_Pos)                   /*!< FMI EMMCCTL: SDNWR Mask                */

#define FMI_EMMCCMD_ARGUMENT_Pos        (0)                                                /*!< FMI EMMCCMD: ARGUMENT Position         */
#define FMI_EMMCCMD_ARGUMENT_Msk        (0xfffffffful << FMI_EMMCCMD_ARGUMENT_Pos)         /*!< FMI EMMCCMD: ARGUMENT Mask             */

#define FMI_EMMCINTEN_BLKDIEN_Pos       (0)                                                /*!< FMI EMMCINTEN: BLKDIEN Position        */
#define FMI_EMMCINTEN_BLKDIEN_Msk       (0x1ul << FMI_EMMCINTEN_BLKDIEN_Pos)               /*!< FMI EMMCINTEN: BLKDIEN Mask            */

#define FMI_EMMCINTEN_CRCIEN_Pos        (1)                                                /*!< FMI EMMCINTEN: CRCIEN Position         */
#define FMI_EMMCINTEN_CRCIEN_Msk        (0x1ul << FMI_EMMCINTEN_CRCIEN_Pos)                /*!< FMI EMMCINTEN: CRCIEN Mask             */

#define FMI_EMMCINTEN_RTOIEN_Pos        (12)                                               /*!< FMI EMMCINTEN: RTOIEN Position         */
#define FMI_EMMCINTEN_RTOIEN_Msk        (0x1ul << FMI_EMMCINTEN_RTOIEN_Pos)                /*!< FMI EMMCINTEN: RTOIEN Mask             */

#define FMI_EMMCINTEN_DITOIEN_Pos       (13)                                               /*!< FMI EMMCINTEN: DITOIEN Position        */
#define FMI_EMMCINTEN_DITOIEN_Msk       (0x1ul << FMI_EMMCINTEN_DITOIEN_Pos)               /*!< FMI EMMCINTEN: DITOIEN Mask            */

#define FMI_EMMCINTSTS_BLKDIF_Pos       (0)                                                /*!< FMI EMMCINTSTS: BLKDIF Position        */
#define FMI_EMMCINTSTS_BLKDIF_Msk       (0x1ul << FMI_EMMCINTSTS_BLKDIF_Pos)               /*!< FMI EMMCINTSTS: BLKDIF Mask            */

#define FMI_EMMCINTSTS_CRCIF_Pos        (1)                                                /*!< FMI EMMCINTSTS: CRCIF Position         */
#define FMI_EMMCINTSTS_CRCIF_Msk        (0x1ul << FMI_EMMCINTSTS_CRCIF_Pos)                /*!< FMI EMMCINTSTS: CRCIF Mask             */

#define FMI_EMMCINTSTS_CRC7_Pos         (2)                                                /*!< FMI EMMCINTSTS: CRC7 Position          */
#define FMI_EMMCINTSTS_CRC7_Msk         (0x1ul << FMI_EMMCINTSTS_CRC7_Pos)                 /*!< FMI EMMCINTSTS: CRC7 Mask              */

#define FMI_EMMCINTSTS_CRC16_Pos        (3)                                                /*!< FMI EMMCINTSTS: CRC16 Position         */
#define FMI_EMMCINTSTS_CRC16_Msk        (0x1ul << FMI_EMMCINTSTS_CRC16_Pos)                /*!< FMI EMMCINTSTS: CRC16 Mask             */

#define FMI_EMMCINTSTS_CRCSTS_Pos       (4)                                                /*!< FMI EMMCINTSTS: CRCSTS Position        */
#define FMI_EMMCINTSTS_CRCSTS_Msk       (0x7ul << FMI_EMMCINTSTS_CRCSTS_Pos)               /*!< FMI EMMCINTSTS: CRCSTS Mask            */

#define FMI_EMMCINTSTS_DAT0STS_Pos      (7)                                                /*!< FMI EMMCINTSTS: DAT0STS Position       */
#define FMI_EMMCINTSTS_DAT0STS_Msk      (0x1ul << FMI_EMMCINTSTS_DAT0STS_Pos)              /*!< FMI EMMCINTSTS: DAT0STS Mask           */

#define FMI_EMMCINTSTS_RTOIF_Pos        (12)                                               /*!< FMI EMMCINTSTS: RTOIF Position         */
#define FMI_EMMCINTSTS_RTOIF_Msk        (0x1ul << FMI_EMMCINTSTS_RTOIF_Pos)                /*!< FMI EMMCINTSTS: RTOIF Mask             */

#define FMI_EMMCINTSTS_DINTOIF_Pos      (13)                                               /*!< FMI EMMCINTSTS: DINTOIF Position       */
#define FMI_EMMCINTSTS_DINTOIF_Msk      (0x1ul << FMI_EMMCINTSTS_DINTOIF_Pos)              /*!< FMI EMMCINTSTS: DINTOIF Mask           */

#define FMI_EMMCRESP0_RESPTK0_Pos       (0)                                                /*!< FMI EMMCRESP0: RESPTK0 Position        */
#define FMI_EMMCRESP0_RESPTK0_Msk       (0xfffffffful << FMI_EMMCRESP0_RESPTK0_Pos)        /*!< FMI EMMCRESP0: RESPTK0 Mask            */

#define FMI_EMMCRESP1_RESPTK1_Pos       (0)                                                /*!< FMI EMMCRESP1: RESPTK1 Position        */
#define FMI_EMMCRESP1_RESPTK1_Msk       (0xfful << FMI_EMMCRESP1_RESPTK1_Pos)              /*!< FMI EMMCRESP1: RESPTK1 Mask            */

#define FMI_EMMCBLEN_BLKLEN_Pos         (0)                                                /*!< FMI EMMCBLEN: BLKLEN Position          */
#define FMI_EMMCBLEN_BLKLEN_Msk         (0x7fful << FMI_EMMCBLEN_BLKLEN_Pos)               /*!< FMI EMMCBLEN: BLKLEN Mask              */

#define FMI_EMMCTOUT_TOUT_Pos           (0)                                                /*!< FMI EMMCTOUT: TOUT Position            */
#define FMI_EMMCTOUT_TOUT_Msk           (0xfffffful << FMI_EMMCTOUT_TOUT_Pos)              /*!< FMI EMMCTOUT: TOUT Mask                */

/**@}*/ /* FMI_CONST */

//--- define type of SD card or MMC
#define EMMC_TYPE_UNKNOWN     0           /*!< Card Type - Unknoen \hideinitializer */
#define EMMC_TYPE_SD_HIGH     1           /*!< Card Type - SDH \hideinitializer */
#define EMMC_TYPE_SD_LOW      2           /*!< Card Type - SD \hideinitializer */
#define EMMC_TYPE_MMC         3           /*!< Card Type - MMC \hideinitializer */
#define EMMC_TYPE_EMMC        4           /*!< Card Type - eMMC \hideinitializer */

#define EMMC_ERR_ID       0xFFFF0180                /*!< FMI Error ID          \hideinitializer */
#define EMMC_TIMEOUT          (EMMC_ERR_ID|0x01)    /*!< FMI Error - Timeout   \hideinitializer */
#define EMMC_NO_MEMORY        (EMMC_ERR_ID|0x02)    /*!< FMI Error - No Memory \hideinitializer */
/* EMMC error */
#define EMMC_NO_CARD          (EMMC_ERR_ID|0x10)    /*!< FMI Error - No card   \hideinitializer */
#define EMMC_ERR_DEVICE       (EMMC_ERR_ID|0x11)    /*!< FMI Error - device err \hideinitializer */
#define EMMC_INIT_TIMEOUT     (EMMC_ERR_ID|0x12)    /*!< FMI Error - init timeout \hideinitializer */
#define EMMC_SELECT_ERROR     (EMMC_ERR_ID|0x13)    /*!< FMI Error - select err \hideinitializer */
#define EMMC_WRITE_PROTECT    (EMMC_ERR_ID|0x14)    /*!< FMI Error - write protect \hideinitializer */
#define EMMC_INIT_ERROR       (EMMC_ERR_ID|0x15)    /*!< FMI Error - init err \hideinitializer */
#define EMMC_CRC7_ERROR       (EMMC_ERR_ID|0x16)    /*!< FMI Error - crc7 err \hideinitializer */
#define EMMC_CRC16_ERROR      (EMMC_ERR_ID|0x17)    /*!< FMI Error - crc16 err \hideinitializer */
#define EMMC_CRC_ERROR        (EMMC_ERR_ID|0x18)    /*!< FMI Error - crc err \hideinitializer */
#define EMMC_CMD8_ERROR       (EMMC_ERR_ID|0x19)    /*!< FMI Error - CMD8 err \hideinitializer */

#define SD_FREQ         25000      /*!< Unit: kHz. Output 25MHz to SD  \hideinitializer */
#define SDHC_FREQ       50000      /*!< Unit: kHz. Output 50MHz to SDH  \hideinitializer */
#define MMC_FREQ        20000      /*!< Unit: kHz. Output 20MHz to MMC  \hideinitializer */
#define EMMC_FREQ       26000      /*!< Unit: kHz. Output 26MHz to eMMC  \hideinitializer */

/*@}*/ /* end of group N9H30_FMI_EXPORTED_CONSTANTS */

/** @addtogroup N9H30_FMI_EXPORTED_TYPEDEF FMI Exported Type Defines
  @{
*/
/** \brief  Structure type of Card information.
 */
typedef struct eMMC_info_t
{
    unsigned int    CardType;       /*!< SDHC, SD, or MMC */
    unsigned int    RCA;            /*!< relative card address */
    unsigned char   IsCardInsert;   /*!< card insert state */
    unsigned int    totalSectorN;   /*!< total sector number */
    unsigned int    diskSize;       /*!< disk size in Kbytes */
    int             sectorSize;     /*!< sector size in bytes */
} EMMC_INFO_T;

/*@}*/ /* end of group N9H30_FMI_EXPORTED_TYPEDEF */

/// @cond HIDDEN_SYMBOLS
extern EMMC_INFO_T eMMC;
extern unsigned char volatile _fmi_eMMCDataReady;

/// @endcond HIDDEN_SYMBOLS

/** @addtogroup N9H30_FMI_EXPORTED_FUNCTIONS FMI Exported Functions
  @{
*/


/**
 *  @brief    Enable specified interrupt.
 *
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref FMI_EMMCINTEN_BLKDIEN_Msk / \ref FMI_EMMCINTEN_CRCIEN_Msk /
 *                           \ref FMI_EMMCINTEN_RTOIEN_Msk / \ref FMI_EMMCINTEN_DITOIEN_Msk /
 *
 *  @return   None.
 * \hideinitializer
 */
#define FMI_EMMC_ENABLE_INT(u32IntMask)    (outpw(REG_FMI_EMMCINTEN, inpw(REG_FMI_EMMCINTEN)|(u32IntMask)))

/**
 *  @brief    Disable specified interrupt.
 *
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref FMI_EMMCINTEN_BLKDIEN_Msk / \ref FMI_EMMCINTEN_CRCIEN_Msk /
 *                           \ref FMI_EMMCINTEN_RTOIEN_Msk / \ref FMI_EMMCINTEN_DITOIEN_Msk /
 *
 *  @return   None.
 * \hideinitializer
 */
#define FMI_EMMC_DISABLE_INT(u32IntMask)    (outpw(REG_FMI_EMMCINTEN, inpw(REG_FMI_EMMCINTEN) & ~(u32IntMask)))

/**
 *  @brief    Get specified interrupt flag/status.
 *
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref FMI_EMMCINTSTS_BLKDIF_Msk / \ref FMI_EMMCINTSTS_CRCIF_Msk / \ref FMI_EMMCINTSTS_CRC7_Msk /
 *                           \ref FMI_EMMCINTSTS_CRC16_Msk / \ref FMI_EMMCINTSTS_CRCSTS_Msk / \ref FMI_EMMCINTSTS_DAT0STS_Msk /
 *                           \ref FMI_EMMCINTSTS_RTOIF_Msk / \ref FMI_EMMCINTSTS_DINTOIF_Msk /
 *
 *  @return  0 = The specified interrupt is not happened.
 *            1 = The specified interrupt is happened.
 * \hideinitializer
 */
#define FMI_EMMC_GET_INT_FLAG(u32IntMask) ((inpw(REG_FMI_EMMCINTSTS)&(u32IntMask))?1:0)


/**
 *  @brief    Clear specified interrupt flag/status.
 *
 *  @param[in]    u32IntMask    Interrupt type mask:
 *                           \ref FMI_EMMCINTSTS_BLKDIF_Msk / \ref FMI_EMMCINTSTS_CRCIF_Msk /
 *                           \ref FMI_EMMCINTSTS_RTOIF_Msk / \ref FMI_EMMCINTSTS_DINTOIF_Msk
 *
 *  @return   None.
 * \hideinitializer
 */
#define FMI_EMMC_CLR_INT_FLAG(u32IntMask) (outpw(REG_FMI_EMMCINTSTS, u32IntMask))


/**
 *  @brief    Check eMMC Card inserted or removed.
 *
 *  @return   1: Card inserted.
 *            0: Card removed.
 * \hideinitializer
 */
#define FMI_EMMC_IS_CARD_PRESENT() (eMMC.IsCardInsert)

/**
 *  @brief    Get eMMC Card capacity.
 *
 *  @return   eMMC Card capacity. (unit: KByte)
 * \hideinitializer
 */
#define FMI_EMMC_GET_CARD_CAPACITY()  (eMMC.diskSize)


void eMMC_Open(void);
void eMMC_Probe(void);
unsigned int eMMC_Read(unsigned char *pu8BufAddr, unsigned int u32StartSec, unsigned int u32SecCount);
unsigned int eMMC_Write(unsigned char *pu8BufAddr, unsigned int u32StartSec, unsigned int u32SecCount);
void FMI_SetReferenceClock(unsigned int u32Clock);
void eMMC_Open_Disk(void);
void eMMC_Close_Disk(void);


/*@}*/ /* end of group N9H30_FMI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_FMI_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#endif  //end of __NU_FMI_H__
/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
