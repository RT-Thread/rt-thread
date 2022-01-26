////////////////////////////////////////////////////////////////////////////////
/// @file     reg_sdio.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion

#ifndef __REG_SDIO_H
#define __REG_SDIO_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
//#include "types.h"
#include "mm32_reg.h"

//#if defined ( __CC_ARM )
//#pragma anon_unions
//#endif


////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_BASE                        (0x40018000U)                            ///< Base Address: 0x40018000


////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO Register Structure Definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    __IO u32 MMC_CTRL;                                                          ///< SDIO transmit data register,                    offset: 0x00
    __IO u32 MMC_IO;                                                            ///< SDIO receive data register,                     offset: 0x04
    __IO u32 MMC_BYTECNTL;                                                      ///< SDIO current state register,                    offset: 0x08
    __IO u32 MMC_TR_BLOCKCNT;                                                   ///< SDIO interruput state register,                 offset: 0x0C
    __IO u32 MMC_CRCCTL;                                                        ///< SDIO interruput enable register,                offset: 0x10
    __IO u32 CMD_CRC;                                                           ///< SDIO interruput control register,               offset: 0x14
    __IO u32 DAT_CRCL;                                                          ///< SDIO global control register,                   offset: 0x18
    __IO u32 DAT_CRCH;                                                          ///< SDIO common control register,                   offset: 0x1C
    __IO u32 MMC_PORT;                                                          ///< SDIO baud rate control register,                offset: 0x20
    __IO u32 MMC_INT_MASK;                                                      ///< SDIO receive data number register,              offset: 0x24
    __IO u32 CLR_MMC_INT;                                                       ///< SDIO chip select register,                      offset: 0x28
    __IO u32 MMC_CARDSEL;                                                       ///< SDIO extand control register,                   offset: 0x2C
    __IO u32 MMC_SIG;                                                           ///<                                                 0ffset: 0x30
    __IO u32 MMC_IO_MBCTL;                                                      ///<                                                 0ffset: 0x34
    __IO u32 MMC_BLOCKCNT;                                                      ///<                                                 0ffset: 0x38
    __IO u32 MMC_TIMEOUTCNT;                                                    ///<                                                 0ffset: 0x3C
    __IO u32 CMD_BUF0;                                                          ///<                                                 0ffset: 0x40
    __IO u32 CMD_BUF1;                                                          ///<                                                 0ffset: 0x44
    __IO u32 CMD_BUF2;                                                          ///<                                                 0ffset: 0x48
    __IO u32 CMD_BUF3;                                                          ///<                                                 0ffset: 0x4C
    __IO u32 CMD_BUF4;                                                          ///<                                                 0ffset: 0x50
    __IO u32 CMD_BUF5;                                                          ///<                                                 0ffset: 0x54
    __IO u32 CMD_BUF6;                                                          ///<                                                 0ffset: 0x58
    __IO u32 CMD_BUF7;                                                          ///<                                                 0ffset: 0x5C
    __IO u32 CMD_BUF8;                                                          ///<                                                 0ffset: 0x60
    __IO u32 CMD_BUF9;                                                          ///<                                                 0ffset: 0x64
    __IO u32 CMD_BUF10;                                                         ///<                                                 0ffset: 0x68
    __IO u32 CMD_BUF11;                                                         ///<                                                 0ffset: 0x6C
    __IO u32 CMD_BUF12;                                                         ///<                                                 0ffset: 0x70
    __IO u32 CMD_BUF13;                                                         ///<                                                 0ffset: 0x74
    __IO u32 CMD_BUF14;                                                         ///<                                                 0ffset: 0x78
    __IO u32 CMD_BUF15;                                                         ///<                                                 0ffset: 0x7C
    __IO u32 BUF_CTL;                                                           ///<                                                 0ffset: 0x80

    __IO u32 RESERVED[31];                                                      ///<                                                 0ffset: 0x84
    union {
        __IO u32 DATA_BUF0;                                                         ///<                                                 0ffset: 0x100
        __IO u32 FIFO;
    };
    __IO u32 DATA_BUF1;                                                         ///<                                                 0ffset: 0x104
    __IO u32 DATA_BUF2;                                                         ///<                                                 0ffset: 0x108
    __IO u32 DATA_BUF3;                                                         ///<                                                 0ffset: 0x10C
    __IO u32 DATA_BUF4;                                                         ///<                                                 0ffset: 0x110
} SDIO_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO                            ((SDIO_TypeDef*) SDIO_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_CTRL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_CTRL_OPMSel_Pos               (0)
#define SDIO_MMC_CTRL_OPMSel                   (0x01U << SDIO_MMC_CTRL_OPMSel_Pos)      ///< SD/MMC/SDIO port operation mode select
#define SDIO_MMC_CTRL_SelSM_Pos                (1)
#define SDIO_MMC_CTRL_SelSM                    (0x01U << SDIO_MMC_CTRL_SelSM_Pos)      ///< Select automatic mode
#define SDIO_MMC_CTRL_OUTM_Pos                 (2)
#define SDIO_MMC_CTRL_OUTM                     (0x01U << SDIO_MMC_CTRL_OUTM_Pos)      ///< SD/MMC/SDIO port CMD line output driver mode selection Open drain
#define SDIO_MMC_CTRL_CLKSP_Pos                (3)
#define SDIO_MMC_CTRL_CLKSP2                   (0x00U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/2  baseclock
#define SDIO_MMC_CTRL_CLKSP4                   (0x01U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/4  baseclock
#define SDIO_MMC_CTRL_CLKSP6                   (0x02U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/6  baseclock
#define SDIO_MMC_CTRL_CLKSP8                   (0x03U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/8  baseclock
#define SDIO_MMC_CTRL_CLKSP10                  (0x04U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/10 baseclock
#define SDIO_MMC_CTRL_CLKSP12                  (0x05U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/12 baseclock
#define SDIO_MMC_CTRL_CLKSP14                  (0x06U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/14 baseclock
#define SDIO_MMC_CTRL_CLKSP16                  (0x07U << SDIO_MMC_CTRL_CLKSP_Pos)      ///< SD/MMC/SDIO port CLK linespeedselection 1/16 baseclock
#define SDIO_MMC_CTRL_SelPTSM_Pos              (6)
#define SDIO_MMC_CTRL_SelPTSM                  (0x01U << SDIO_MMC_CTRL_SelPTSM_Pos)    ///< SelectSD/MMC/SDIO port transfer high speed mode
#define SDIO_MMC_CTRL_DATWT_Pos                (7)
#define SDIO_MMC_CTRL_DATWT                    (0x01U << SDIO_MMC_CTRL_DATWT_Pos)      ///< Definethe bus width of SD/MMC/SDIO port DAT line
#define SDIO_MMC_CTRL_MDEN_Pos                 (8)
#define SDIO_MMC_CTRL_MDEN                     (0x01U << SDIO_MMC_CTRL_MDEN_Pos)       ///< SDIO mode enable
#define SDIO_MMC_CTRL_INTEN_Pos                (9)
#define SDIO_MMC_CTRL_INTEN                    (0x01U << SDIO_MMC_CTRL_INTEN_Pos)      ///< SDIO interrupt enale signal
#define SDIO_MMC_CTRL_RDWTEN_Pos               (10)
#define SDIO_MMC_CTRL_RDWTEN                   (0x01U << SDIO_MMC_CTRL_RDWTEN_Pos)     ///< SDIO read wait enable signal
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_IO Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_IO_AUTODATTR_Pos               (0)
#define SDIO_MMC_IO_AUTODATTR                   (0x01U << SDIO_MMC_IO_AUTODATTR_Pos)      ///< Set up automatic data transfer
#define SDIO_MMC_IO_TRANSFDIR_Pos               (1)
#define SDIO_MMC_IO_TRANSFDIR                   (0x01U << SDIO_MMC_IO_TRANSFDIR_Pos)      ///< Set the direction of data transfer
#define SDIO_MMC_IO_AUTOTR_Pos                  (2)
#define SDIO_MMC_IO_AUTOTR                      (0x01U << SDIO_MMC_IO_AUTOTR_Pos)        ///< Set up automatic 8-bit/command/response transmission.
#define SDIO_MMC_IO_RESPCMDSEL_Pos              (3)
#define SDIO_MMC_IO_RESPCMDSEL                  (0x01U << SDIO_MMC_IO_RESPCMDSEL_Pos)    ///< Receive response
#define SDIO_MMC_IO_CID_CSDRD_Pos               (4)
#define SDIO_MMC_IO_CID_CSDRD                   (0x01U << SDIO_MMC_IO_CID_CSDRD_Pos)     ///< CID and CSD reads
#define SDIO_MMC_IO_PCLKG_Pos                   (5)
#define SDIO_MMC_IO_PCLKG                       (0x01U << SDIO_MMC_IO_PCLKG_Pos)         ///< SD/MMC/SDIO port CLK line 8 empty clock generated
#define SDIO_MMC_IO_ENRRESP_Pos                 (6)
#define SDIO_MMC_IO_ENRRESP                     (0x01U << SDIO_MMC_IO_ENRRESP_Pos)       ///< Enable automatic receiving of responses after a command
#define SDIO_MMC_IO_AUTOCLKG_Pos                (7)
#define SDIO_MMC_IO_AUTOCLKG                    (0x01U << SDIO_MMC_IO_AUTOCLKG_Pos)      ///< Enable automatic conversion of the 8 empty clock after a response/command or a single block of data
#define SDIO_MMC_IO_CMDCH_Pos                   (8)
#define SDIO_MMC_IO_CMDCH                       (0x01U << SDIO_MMC_IO_CMDCH_Pos)         ///< SDIO mode enable
#define SDIO_MMC_IO_CMDAF_Pos                   (9)
#define SDIO_MMC_IO_CMDAF                       (0x01U << SDIO_MMC_IO_CMDAF_Pos)        ///< SDIO CMD12 / IO abort flag
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_BYTECNTL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_BYTECNTL_CNT                    (0xFFFFU)                              ///< Data transfer byte count register
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_TR_BLOCKCNT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_TR_BLOCKCNT_CNT                 (0xFFFFU)                              ///< The value of the counter that completes the transfer when multiple blocks are transferred.
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_CRCCTL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_CRCCTL_DAT_CRCE_Pos             (0)
#define SDIO_MMC_CRCCTL_DAT_CRCE                 (0x01U << SDIO_MMC_CRCCTL_DAT_CRCE_Pos)      ///< DAT CRC error
#define SDIO_MMC_CRCCTL_CMD_CRCE_Pos             (1)
#define SDIO_MMC_CRCCTL_CMD_CRCE                 (0x01U << SDIO_MMC_CRCCTL_CMD_CRCE_Pos)      ///< CMD CRC error
#define SDIO_MMC_CRCCTL_DAT_CRCS_Pos             (2)
#define SDIO_MMC_CRCCTL_DAT_CRCS                 (0x03U << SDIO_MMC_CRCCTL_DAT_CRCS_Pos)      ///< DAT CRC selection
#define SDIO_MMC_CRCCTL_ENRDMB_Pos               (4)
#define SDIO_MMC_CRCCTL_ENRDMB                   (0x01U << SDIO_MMC_CRCCTL_ENRDMB_Pos)        ///< Enable reading multiple blocks of data before responding
#define SDIO_MMC_CRCCTL_ENCHK_Pos                (5)
#define SDIO_MMC_CRCCTL_ENCHK                    (0x01U << SDIO_MMC_CRCCTL_ENCHK_Pos)         ///< Enable automatic checking 
#define SDIO_MMC_CRCCTL_DAT_CRCEN_Pos            (6)
#define SDIO_MMC_CRCCTL_DAT_CRCEN                (0x01U << SDIO_MMC_CRCCTL_DAT_CRCEN_Pos)     ///< SD/MMC/SDIO PORT DAT line CRC circuit enablement
#define SDIO_MMC_CRCCTL_CMD_CRCEN_Pos            (7)
#define SDIO_MMC_CRCCTL_CMD_CRCEN                (0x01U << SDIO_MMC_CRCCTL_CMD_CRCEN_Pos)     ///< SD/MMC/SDIO port CMD line CRC circuit enablement
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_CRC Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_CRC_CMD_CRCV                    (0x7FU)                                 ///< CMD_CRCV register value
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_DAT_CRCL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_DAT_CRCL_DAT_CRCLV                  (0xFFU)                                 ///< CMD_CRCV low  register value
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_DAT_CRCH Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_DAT_CRCL_DAT_CRCHV                  (0xFFU)                                 ///< CMD_CRCV high register value
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_PORT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_PORT_NTCR_Pos                   (0)
#define SDIO_MMC_PORT_NTCR                       (0x0FU << SDIO_MMC_PORT_NTCR_Pos)      ///< Ncr timeout count register
#define SDIO_MMC_PORT_AUTONTEN_Pos               (4)
#define SDIO_MMC_PORT_AUTONTEN                   (0x01U << SDIO_MMC_PORT_AUTONTEN_Pos)  ///< Automatic Ncr timer output enablement
#define SDIO_MMC_PORT_PDATS_Pos                  (5)
#define SDIO_MMC_PORT_PDATS                      (0x01U << SDIO_MMC_PORT_PDATS_Pos)     ///< SD/MMC/SDIO port DAT line signal
#define SDIO_MMC_PORT_PCMDS_Pos                  (6)
#define SDIO_MMC_PORT_PCMDS                      (0x01U << SDIO_MMC_PORT_PCMDS_Pos)     ///< SD/MMC/SDIO port CMD line signal
#define SDIO_MMC_PORT_PCLKS_Pos                  (7)
#define SDIO_MMC_PORT_PCLKS                      (0x01U << SDIO_MMC_PORT_PCLKS_Pos)     ///< SD/MMC/SDIO port CLK line signal
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_INT_MASK Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_INT_MASK_CMDDINT_Pos             (0)
#define SDIO_MMC_INT_MASK_CMDDINT                 (0x01U << SDIO_MMC_INT_MASK_CMDDINT_Pos)      ///<CMD completes interrupt shielding
#define SDIO_MMC_INT_MASK_DATDINT_Pos             (1)
#define SDIO_MMC_INT_MASK_DATDINT                 (0x01U << SDIO_MMC_INT_MASK_DATDINT_Pos)      ///< DAT completes interrupt shielding
#define SDIO_MMC_INT_MASK_DATEINT_Pos             (2)
#define SDIO_MMC_INT_MASK_DATEINT                 (0x01U << SDIO_MMC_INT_MASK_DATEINT_Pos)      ///< DAT CRC error interrupt masking
#define SDIO_MMC_INT_MASK_CMDEINT_Pos             (3)
#define SDIO_MMC_INT_MASK_CMDEINT                 (0x01U << SDIO_MMC_INT_MASK_CMDEINT_Pos)     ///< CMD CRC error interrupt masking
#define SDIO_MMC_INT_MASK_MBDINTM_Pos             (4)
#define SDIO_MMC_INT_MASK_MBDINTM                 (0x01U << SDIO_MMC_INT_MASK_MBDINTM_Pos)     ///< Multiple blocks complete interrupt shielding 
#define SDIO_MMC_INT_MASK_MBTINTM_Pos             (5)
#define SDIO_MMC_INT_MASK_MBTINTM                 (0x01U << SDIO_MMC_INT_MASK_MBTINTM_Pos)     ///< Multiblock timeout interrupt shielding
#define SDIO_MMC_INT_MASK_CRTINTM_Pos             (6)
#define SDIO_MMC_INT_MASK_CRTINTM                 (0x01U << SDIO_MMC_INT_MASK_CRTINTM_Pos)     ///< Cmd and Resp Ncr timeout interrupt shielding
#define SDIO_MMC_INT_MASK_CRCINTM_Pos             (7)
#define SDIO_MMC_INT_MASK_CRCINTM                 (0x01U << SDIO_MMC_INT_MASK_CRCINTM_Pos)     ///< CRC status token error interrupt masking
#define SDIO_MMC_INT_MASK_D1INTM_Pos              (8)
#define SDIO_MMC_INT_MASK_D1INTM                  (0x01U << SDIO_MMC_INT_MASK_D1INTM_Pos)     ///< SDIO Data 1 Line Interrupt Mask
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CLR_MMC_INT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CLR_MMC_INT_CMDDMC_Pos             (0)
#define SDIO_CLR_MMC_INT_CMDDMC                 (0x01U << SDIO_CLR_MMC_INT_CMDDMC_Pos)      ///< CMD completes interrupt mask bit
#define SDIO_CLR_MMC_INT_DATDMC_Pos             (1)
#define SDIO_CLR_MMC_INT_DATDMC                 (0x01U << SDIO_CLR_MMC_INT_DATDMC_Pos)      ///< DAT completes interrupt mask bit
#define SDIO_CLR_MMC_INT_DATEMC_Pos             (2)
#define SDIO_CLR_MMC_INT_DATEMC                 (0x01U << SDIO_CLR_MMC_INT_DATEMC_Pos)      ///< DAT CRC error interrupt mask bit
#define SDIO_CLR_MMC_INT_CMDEMC_Pos             (3)
#define SDIO_CLR_MMC_INT_CMDEMC                 (0x01U << SDIO_CLR_MMC_INT_CMDEMC_Pos)     ///< CMD CRC error interrupt mask bit
#define SDIO_CLR_MMC_INT_MBDMC_Pos              (4)
#define SDIO_CLR_MMC_INT_MBDMC                  (0x01U << SDIO_CLR_MMC_INT_MBDMC_Pos)      ///< Multi - block transmission completion interrupt mask bit 
#define SDIO_CLR_MMC_INT_MBTMC_Pos              (5)
#define SDIO_CLR_MMC_INT_MBTMC                  (0x01U << SDIO_CLR_MMC_INT_MBTMC_Pos)      ///< Multiblock transmission timeout interrupt mask bit
#define SDIO_CLR_MMC_INT_CRNTMC_Pos             (6)
#define SDIO_CLR_MMC_INT_CRNTMC                 (0x01U << SDIO_CLR_MMC_INT_CRNTMC_Pos)     ///< Command and response Ncr timeout interrupt mask bit
#define SDIO_CLR_MMC_INT_CRCEMC_Pos             (7)
#define SDIO_CLR_MMC_INT_CRCEMC                 (0x01U << SDIO_CLR_MMC_INT_CRCEMC_Pos)     ///< CRC status error marks the interrupt mask bit
#define SDIO_CLR_MMC_INT_D1MC_Pos               (8)
#define SDIO_CLR_MMC_INT_D1MC                   (0x01U << SDIO_CLR_MMC_INT_D1MC_Pos)       ///< SDIO DatA1 line interrupt flag/clear bit
#define SDIO_CLR_MMC_INT_MASK                   (0XFFU)
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_CARDSEL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_CARDSEL_TSCALE_Pos             (0)
#define SDIO_MMC_CARDSEL_TSCALE                 (0x01U << SDIO_MMC_CARDSEL_TSCALE_Pos)      ///< SD/MMC/SDIO clock frequency division factor (based on 1MHz
#define SDIO_MMC_CARDSEL_ENPCLK_Pos             (6)
#define SDIO_MMC_CARDSEL_ENPCLK                 (0x01U << SDIO_MMC_CARDSEL_ENPCLK_Pos)      ///< Enabling card's SD/MMC/SDIO port CLK clock
#define SDIO_MMC_CARDSEL_CTREN_Pos              (7)
#define SDIO_MMC_CARDSEL_CTREN                  (0x01U << SDIO_MMC_CARDSEL_CTREN_Pos)      ///< SD/MMC/SDIO controller enablement bit
#define SDIO_MMC_CARDSEL_MASK                   (0XFFU)
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_SIQ Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_SIQ_PDAT0S_Pos                 (0)
#define SDIO_MMC_SIQ_PDAT0S                     (0x01U << SDIO_MMC_SIQ_PDAT0S_Pos)         ///< SD/MMC/SDIO port DAT0 line signal
#define SDIO_MMC_SIQ_PDAT1S_Pos                 (1)
#define SDIO_MMC_SIQ_PDAT1S                     (0x01U << SDIO_MMC_SIQ_PDAT1S_Pos)         ///< SD/MMC/SDIO port DAT1 line signal
#define SDIO_MMC_SIQ_PDAT2S_Pos                 (2)
#define SDIO_MMC_SIQ_PDAT2S                     (0x01U << SDIO_MMC_SIQ_PDAT2S_Pos)         ///< SD/MMC/SDIO port DAT2 line signal
#define SDIO_MMC_SIQ_PDAT3S_Pos                 (3)
#define SDIO_MMC_SIQ_PDAT3S                     (0x01U << SDIO_MMC_SIQ_PDAT3S_Pos)         ///< SD/MMC/SDIO port DAT3 line signal
#define SDIO_MMC_SIQ_CRC_status_Pos             (4)
#define SDIO_MMC_SIQ_CRC_status                 (0x07U << SDIO_MMC_SIQ_CRC_status_Pos)     ///< CRC state
#define SDIO_MMC_SIQ_PCMDS_Pos                  (7)
#define SDIO_MMC_SIQ_PCMDS                      (0x01U << SDIO_MMC_SIQ_PCMDS_Pos)          ///< SD/MMC/SDIO port CMD line signal
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_IO_MBCTL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_IO_MBCTL_SPMBDTR_Pos           (0)
#define SDIO_MMC_IO_MBCTL_SPMBDTR               (0x01U << SDIO_MMC_IO_MBCTL_SPMBDTR_Pos)   ///< Set the SD/MMC/SDIO port to automatically multiblock data transfer bit
#define SDIO_MMC_IO_MBCTL_SMBDTD_Pos            (1)
#define SDIO_MMC_IO_MBCTL_SMBDTD                (0x01U << SDIO_MMC_IO_MBCTL_SMBDTD_Pos)    //< Multi - block data transfer direction selection bit
#define SDIO_MMC_IO_MBCTL_PAUTOTR_Pos           (2)
#define SDIO_MMC_IO_MBCTL_PAUTOTR               (0x01U << SDIO_MMC_IO_MBCTL_PAUTOTR_Pos)   ///< Set up SD/MMC/SDIO port automatic command and multi - block data transfer
#define SDIO_MMC_IO_MBCTL_PCLKP_Pos             (3)
#define SDIO_MMC_IO_MBCTL_PCLKP                 (0x01U << SDIO_MMC_IO_MBCTL_PCLKP_Pos)     ///< SD/MMC/SDIO port CLK line polarity selection bit
#define SDIO_MMC_IO_MBCTL_BTSSel_Pos            (4)
#define SDIO_MMC_IO_MBCTL_BTSSel                (0x03U << SDIO_MMC_SIQ_CRC_status_Pos)     ///< SD/MMC/SDIO BUSY Timeout level selects bits
#define SDIO_MMC_IO_MBCTL_BTSSel_2              (0x02U << SDIO_MMC_SIQ_CRC_status_Pos)     ///< SD/MMC/SDIO BUSY Timeout level selects bits
#define SDIO_MMC_IO_MBCTL_NTSSel_Pos            (6)
#define SDIO_MMC_IO_MBCTL_NTSSel                (0x03U << SDIO_MMC_IO_MBCTL_NTSSel_Pos)    ///< SD/MMC/SDIO NAC timeout level selection bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_BLOCKCNT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_BLOCKCNT_EN                    (0xFFFFU)                                 ///< Block count register
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_MMC_TIMEOUTCNT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_MMC_TIMEOUTCNT_DTCNT                (0xFFU)                                 ///< Data transfer timeout count register
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF0 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF0_DAT                        (0xFFU)                                 ///< Cmd_buf0 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF1_DAT                        (0xFFU)                                 ///< Cmd_buf1 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF2_DAT                        (0xFFU)                                 ///< Cmd_buf2 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF3 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF3_DAT                        (0xFFU)                                 ///< Cmd_buf3 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF4 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF4_DAT                        (0xFFU)                                 ///< Cmd_buf4 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF5 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF5_DAT                        (0xFFU)                                 ///< Cmd_buf5 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF6 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF6_DAT                        (0xFFU)                                 ///< Cmd_buf6 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF7 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF7_DAT                        (0xFFU)                                 ///< Cmd_buf7 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF8 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF8_DAT                        (0xFFU)                                 ///< Cmd_buf8 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF9 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF9_DAT                        (0xFFU)                                 ///< Cmd_buf9 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF10 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF10_DAT                        (0xFFU)                                 ///< Cmd_buf10 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF11 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF11_DAT                        (0xFFU)                                 ///< Cmd_buf11 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF12 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF12_DAT                        (0xFFU)                                 ///< Cmd_buf12 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF13 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF13_DAT                        (0xFFU)                                 ///< Cmd_buf13 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF14 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF14_DAT                        (0xFFU)                                 ///< Cmd_buf14 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_CMD_BUF15 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_CMD_BUF15_DAT                        (0xFFU)                                 ///< Cmd_buf15 byte mapping bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_BUF_CTLL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_BUF_CTLL_DBF_Pos                     (0)
#define SDIO_BUF_CTLL_DBF                         (0x01U << SDIO_BUF_CTLL_DBF_Pos)        ///< The data cache is full
#define SDIO_BUF_CTLL_DBE_Pos                     (1)
#define SDIO_BUF_CTLL_DBE                         (0x01U << SDIO_BUF_CTLL_DBE_Pos)        ///< Data buff is null
#define SDIO_BUF_CTLL_DBML_Pos                    (2)
#define SDIO_BUF_CTLL_DBML                        (0xFFU << SDIO_BUF_CTLL_DBML_Pos)       ////< Data buff tags
#define SDIO_BUF_CTLL_DMAHEN_Pos                  (10)
#define SDIO_BUF_CTLL_DMAHEN                      (0x01U << SDIO_BUF_CTLL_DMAHEN_Pos)     ///< DMA hardware interface enablement
#define SDIO_BUF_CTLL_SBAD_Pos                    (11)
#define SDIO_BUF_CTLL_SBAD                        (0x01U << SDIO_BUF_CTLL_SBAD_Pos)       ///< Sets the access direction of the buff
#define SDIO_BUF_CTLL_DFIFOSM_Pos                 (12)
#define SDIO_BUF_CTLL_DFIFOSM                     (0x01U << SDIO_BUF_CTLL_DFIFOSM_Pos)    ///< Data FIFO status signal shielding bit
#define SDIO_BUF_CTLL_DRM_Pos                     (14)
#define SDIO_BUF_CTLL_DRM                         (0x01U << SDIO_BUF_CTLL_DRM_Pos)        ///< DMA request masking
#define SDIO_BUF_CTLL_DBFEN_Pos                   (15)
#define SDIO_BUF_CTLL_DBFEN                       (0x01U << SDIO_BUF_CTLL_DBFEN_Pos)      ///< Data Buf empty enable bit
////////////////////////////////////////////////////////////////////////////////
/// @brief SDIO_DATA_BUF Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SDIO_DATA_BUF_DB                         (0xFFFFFFFFU)                            ///< Data buffer






/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
