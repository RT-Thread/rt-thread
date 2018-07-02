/*****************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co.,Ltd ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */
/******************************************************************************/
/** \file exmc.h
 **
 ** A detailed description is available at
 ** @link ExmcGroup Exmc description @endlink
 **
 **   - 2018-03-13  1.0  chengy First version for Device Driver Library of Exmc.
 **
 ******************************************************************************/

#ifndef __EXMC_H__
#define __EXMC_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup ExmcGroup External Memory Controller(Exmc)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
typedef enum
{
    Chip0       = 0,
    Chip1       = 1,
    Chip2       = 2,
    Chip3       = 3,
}en_ExmcCmdChip_t;

typedef enum
{
    Bank0       = 0,
    Bank1       = 1,
    Bank2       = 2,
    Bank3       = 3,
}en_DmcCmdBank_t;
/**
 *******************************************************************************
 ** \brief SMC CMD
 **
 ******************************************************************************/
typedef enum
{
    invalid             = 0,
    MdRegConfig         = 1,
    UpdataRegs          = 2,
    MdRegandUpRegs      = 3,
}en_SmcCmd_t;
/**
 *******************************************************************************
 ** \brief SMC Read/Write Burst length
 **
 ******************************************************************************/
typedef enum
{
    Length_one           = 0,
    Length_four          = 1,
    Length_eight         = 2,
    Length_sixteen       = 3,
    Length_thirty_two    = 4,
    Length_unlimited     = 5,
}en_SmcBurstLength_t;

/**
 *******************************************************************************
 ** \brief External Memory Device Width
 **
 ******************************************************************************/
typedef enum
{
    SWidth16 = 1,
    SWidth32 = 2,
}en_SmcMemWidth_t;

typedef enum
{
    AsynEn     = 0,
    SynEn      = 1,
}en_SmcSynEn_t;

typedef enum
{
    SynCs       = 0,    /*!< Bls state synchronous with Cs.*/
    SynWe       = 1,    /*!< Bls state synchronous with We.*/
}en_SmcBlsState_t;
/**
 *******************************************************************************
 ** \brief Base parameters For SMC.
 **
 ******************************************************************************/
typedef struct
{
    en_SmcMemWidth_t                 mw;        /*!< the external memory device width.*/
    en_SmcSynEn_t                    rsyn;      /*!< ennable read asynchronous or synchronous.*/
    en_SmcBurstLength_t              rbl;       /*!< read burst length.*/
    en_SmcSynEn_t                    wsyn;      /*!< ennable wirte asynchronous or synchronous.*/
    en_SmcBurstLength_t              wbl;       /*!< write burst length.*/
    en_functional_state_t            baas;      /*!< ennable or disable BAA.*/
    en_functional_state_t            advs;      /*!<    */
    en_SmcBlsState_t                 blss;      /*!<    */
}stc_SmcBacr_Typedef;
/**
 *******************************************************************************
 ** \brief CMD parameters For SMC.
 **
 ******************************************************************************/
typedef struct
{
    en_ExmcCmdChip_t            cmdchip;     /*!< Choose chip0 ~chip3.*/
    en_SmcCmd_t                 cmd;         /*!< SMC cmd.*/
    en_functional_state_t       cres;        /*!< enable: SMC_CRE out high when cmd == MdRegConfig.*/
    uint32_t                    cmdaddr;     /*!< when cmd is UpdataRegs & MdRegandUpRegs, cmdaddr indicate external mem addr.*/
}stc_SmcCmdr_Typedef;
/**
 *******************************************************************************
 ** \brief Timing parameters For SMC(NOR/SRAM)
 **
 ******************************************************************************/
typedef struct
{
    uint32_t rc         : 4;    /*!< Read cycle time.*/
    uint32_t wc         : 4;    /*!< Write cycle time.*/
    uint32_t ceoe       : 3;
    uint32_t wp         : 3;
    uint32_t pc         : 3;
    uint32_t tr         : 3;
    uint32_t resvd      :12;
}stc_SmcTm_f;

typedef union {
    uint32_t smc_tmcr_byte;
    stc_SmcTm_f smc_tmcr_bit;
}un_SmcTmcr_Typedef;

/**
 *******************************************************************************
 ** \brief SMC Init structure definition
 **
 ******************************************************************************/
typedef struct
{
    en_functional_state_t       SmcMux;         /*!< Whether the address and data values are multiplexed on the databus or not.*/
    stc_SmcCmdr_Typedef         SmcCmdr;        /*!< Cmd parameters for SMC.*/
    un_SmcTmcr_Typedef          SmcTmcr;        /*!< Timing parameters For SMC.*/
    stc_SmcBacr_Typedef         SmcBacr;        /*!< Base parameters For SMC.*/
    uint32_t                    SmcRfcr;        /*!< Refresh time.*/
}stc_SMCInit_TypeDef;
/**
 *******************************************************************************
 ** \brief DMC row bit width.
 **
 ******************************************************************************/
typedef enum
{
    RowbitWidth11            = 0,
    RowbitWidth12            = 1,
    RowbitWidth13            = 2,
    RowbitWidth14            = 3,
    RowbitWidth15            = 4,
    RowbitWidth16            = 5,
}en_DmcRowbitWidth_t;
/**
 *******************************************************************************
 ** \brief DMC column bit width.
 **
 ******************************************************************************/
typedef enum
{
    ColbitWidth8             = 0,
    ColbitWidth9             = 1,
    ColbitWidth10            = 2,
    ColbitWidth11            = 3,
    ColbitWidth12            = 4,
}en_DmcColbitWidth_t;
/**
 *******************************************************************************
 ** \brief DMC Read/Write Burst length
 **
 ******************************************************************************/
typedef enum
{
    Lone           = 0,
    Ltwo           = 1,
    Lfour          = 2,
    Leight         = 3,
    Lsixteen       = 4,
}en_DmcBurstLength_t;
/**
 *******************************************************************************
 ** \brief DMC memory width
 **
 ******************************************************************************/
typedef enum
{
    DWidth16 = 0,
    DWidth32 = 1,
}en_DmcMemWidth_t;
/**
 *******************************************************************************
 ** \brief DMC choose add10 or add8 as aotu precharge bit.
 **
 ******************************************************************************/
typedef enum
{
    Apbs10      = 0,
    Apbs8       = 1,
}en_DmcApbs_t;

/**
 *******************************************************************************
 ** \brief DMC auto refresh chip number.
 **
 ******************************************************************************/
typedef enum
{
    Actcp0              = 0,    /*!< chip0 auto refresh. */
    Actcp01             = 1,    /*!< chip0~1 auto refresh. */
    Actcp012            = 2,    /*!< chip0~2 auto refresh. */
    Actcp0123           = 3,    /*!< chip0~3 auto refresh. */
}en_DmcActcp_t;

/**
 *******************************************************************************
 ** \brief DMC CMD
 **
 ******************************************************************************/
typedef enum
{
    PrechargeAll         = 0,
    AutoRefresh          = 1,
    MdRegconfig          = 2,
    Nop                  = 3,
}en_DmcCmd_t;

/**
 *******************************************************************************
 ** \brief DMC address decodging mode
 **
 ******************************************************************************/
typedef enum
{
    RowBaCol    = 0,
    BaRowCol    = 1,
}en_DmcBrc_t;
/**
 *******************************************************************************
 ** \brief Base parameters For DMC.
 **
 ******************************************************************************/
typedef struct
{
    en_DmcColbitWidth_t         colbs;
    en_DmcRowbitWidth_t         rowbs;
    en_DmcApbs_t                apbs;
    uint8_t                     ckedisprd;
    en_functional_state_t       ckedis;
    en_functional_state_t       ckstp;
    en_DmcBurstLength_t         burst;
    en_DmcActcp_t               actcp;
}stc_DmcBacr_Typedef;

/**
 *******************************************************************************
 ** \brief CMDR For DMC.
 **
 ******************************************************************************/
typedef struct
{
    uint16_t                    cmdadd;
    en_DmcCmdBank_t             cmdba;
    en_DmcCmd_t                 cmd;
    en_ExmcCmdChip_t            cmdchip;
}stc_DmcCmdr_Typedef;
/**
 *******************************************************************************
 ** \brief CPCR For DMC.
 **
 ******************************************************************************/
typedef struct
{
    uint8_t             addmsk;
    uint8_t             addmat;
    en_DmcBrc_t         brc;
}stc_DmcCpcr_Typedef;
/**
 *******************************************************************************
 ** \brief Timing parameters For DMC
 **
 ******************************************************************************/
typedef struct
{
    uint32_t        tcasl;
    uint32_t        tdqss;
    uint32_t        tmrd;
    uint32_t        tras;
    uint32_t        trc;
    uint32_t        trcd;
    uint32_t        trfc;
    uint32_t        trp;
    uint32_t        trrd;
    uint32_t        twr;
    uint32_t        twtr;
    uint32_t        txp;
    uint32_t        txsr;
    uint32_t        tesr;
}stc_DmcTime_Typedef;
/**
 *******************************************************************************
 ** \brief DMC Init structure definition
 **
 ******************************************************************************/
typedef struct
{
    en_DmcMemWidth_t            DmcMw;          /*!< DMC memory width. 0->16,1->32 */
    stc_DmcBacr_Typedef         DmcBacr;
    stc_DmcCmdr_Typedef         DmcCmdr;
    uint32_t                    DmcRefprd;
    stc_DmcCpcr_Typedef         DmcCpcr0;
    stc_DmcCpcr_Typedef         DmcCpcr1;
    stc_DmcCpcr_Typedef         DmcCpcr2;
    stc_DmcCpcr_Typedef         DmcCpcr3;
    stc_DmcTime_Typedef         DmcTime;
    en_ExmcCmdChip_t            DmcChip;
}stc_DMCInit_TypeDef;
/**
 *******************************************************************************
 ** \brief nfc memory size
 **
 ******************************************************************************/
typedef enum
{
    NfcSize16G          = 0,
    NfcSize32G          = 1,
    NfcSize64G          = 2,
    NfcSize512M         = 3,
    NfcSize1G           = 4,
    NfcSize2G           = 5,
    NfcSize4G           = 6,
    NfcSize8G           = 8,
}en_NfcSize_t;
/**
 *******************************************************************************
 ** \brief nfc bit width
 **
 ******************************************************************************/
typedef enum
{
    NfcWidth8   = 0,
    NfcWidth16  = 1,
}en_NfcBWidth_t;
/**
 *******************************************************************************
 ** \brief number of nfc bank
 **
 ******************************************************************************/
typedef enum
{
    NfcOneBank          = 0,
    NfcTwoBank          = 1,
    NfcFourBank         = 2,
    NfcEightBank        = 3,
}en_NfcBankNum_t;
/**
 *******************************************************************************
 ** \brief nfc page size
 **
 ******************************************************************************/
typedef enum
{
    NfcPSize2k          = 1,
    NfcPSize4k          = 2,
    NfcPSize8k          = 3,
}en_NfcPageSize_t;
/**
 *******************************************************************************
 ** \brief nfc ecc mode, 1bit or 4 bit
 **
 ******************************************************************************/
typedef enum
{
    NfcEccBit1          = 0,
    NfcEccBit4          = 1,
}en_NfcEcc_t;
/**
 *******************************************************************************
 ** \brief nfc row address cycle
 **
 ******************************************************************************/
typedef enum
{
    NfcRac2          = 0,       /*!< 2 row address cycle.*/
    NfcRac3          = 1,       /*!< 3 row address cycle.*/
}en_NfcRac_t;
/**
 *******************************************************************************
 ** \brief nfc write protect
 **
 ******************************************************************************/
typedef enum
{
    NfcWpOn          = 0,       /*!< write protect on.*/
    NfcWpOff         = 1,       /*!< write protect off.*/
}en_NfcWp_t;
/**
 *******************************************************************************
 ** \brief NFC Init structure definition
 **
 ******************************************************************************/
typedef struct
{
    en_functional_state_t       NfcOpenP;       /*!< Enable the NFC send a read cmd after reset or disable.*/
    en_NfcSize_t                NfcSize;        /*!< nfc memory size.*/
    en_NfcBWidth_t              NfcbitWidth;    /*!< nfc data bit width.*/
    en_NfcBankNum_t             NfcBankNum;     /*!< number of nfc bank.*/
    en_NfcPageSize_t            NfcPageSize;    /*!< page size.*/
    en_NfcWp_t                  NfcWp;          /*!< nfc write protect.*/
    en_NfcEcc_t                 NfcEccBit;      /*!< ECC mode 1bit or 4bit.*/
    en_NfcRac_t                 NfcRac;         /*!< row address cycle.*/
    uint8_t                     NfcScs;         /*!< spare byte.*/
}stc_NFCInit_TypeDef;
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CMD_CHIP0               0x00
#define CMD_CHIP1               0x01
#define CMD_CHIP2               0x02
#define CMD_CHIP3               0x03

#define SMC_EXIT_LPWOR()          (M4_EXMC->SMC_STCR1 = 0x04)
#define SMC_ENTER_LPWOR()         (M4_EXMC->SMC_STCR0 = 0x04)

#define SMC_ADDR                0x60000000
#define SMC_CHIP_SEZE           0xF8
#define SMC_CHIP0_ADD           0x60000000
#define SMC_CHIP1_ADD           0x68000000
#define SMC_CHIP2_ADD           0x70000000
#define SMC_CHIP3_ADD           0x78000000

#define DMC_ADDR                0x80000000
#define DMC_CMD_PRECHARGEALL    0x00000000
#define DMC_CMD_AUTOREFRESH     0x00040000
#define DMC_CMD_MDREGCONFIG     0x00080000
#define DMC_CMD_NOP             0x000C0000
#define DMC_GO                  0x00000000
#define DMC_SLEEP               0x00000001
#define DMC_WAKEUP              0x00000002
#define DMC_PAUSE               0x00000003
#define DMC_CONFIG              0x00000004
#define DMC_BANK0               0x00
#define DMC_BANK1               0x01
#define DMC_BANK2               0x02
#define DMC_BANK3               0x03
#define DMC_CHIP_SIZE_16M       0xFF
#define DMC_CHIP_SIZE_32M       0xFE
#define DMC_CHIP_SIZE_64M       0xFC
#define DMC_CHIP_SIZE_128M      0xF8



#define NFC_BANK0               0x00
#define NFC_BANK1               0x01
#define NFC_BANK2               0x02
#define NFC_BANK3               0x03
#define NFC_BANK4               0x04
#define NFC_BANK5               0x05
#define NFC_BANK6               0x06
#define NFC_BANK7               0x07
#define NFC_CMD_ARG1            0x00000000
#define NFC_CMD_ARG2            0x40000000
#define NFC_CMD_ARG3            0x81000000
#define NFC_CMD_RELEASE         0x000000FE
#define NFC_CMD_RESET           0x000000FF
#define NFC_CMD_BLOCKERASE1     0x60
#define NFC_CMD_BLOCKERASE2     0xD0
#define NFC_CMD_READ1           0x00
#define NFC_CMD_READ2           0x30
#define NFC_CMD_STARTREAD       0xE0
#define NFC_CMD_READID          0x90
#define NFC_CMD_READSTATUS      0x70
#define NFC_CMD_PAGEREAD        0x00
#define NFC_CMD_PAGEWRITE1      0x80
#define NFC_CMD_PAGEWRITE2      0x10

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern void exmc_smc_init(stc_SMCInit_TypeDef* pstcSmcInit);
extern void exmc_smc_disable(void);
extern void exmc_smc_enable(void);
extern uint32_t exmc_smc_chip_addr(en_ExmcCmdChip_t enSmcChip);

extern void exmc_dmc_init(stc_DMCInit_TypeDef* pstcDmcInit);
extern void exmc_dmc_disable(void);
extern void exmc_dmc_enable(void);
extern uint32_t exmc_dmc_chip_addr(stc_DMCInit_TypeDef* pstcDmcInit);

extern void exmc_nfcinit(stc_NFCInit_TypeDef* pstcNfcInit);
extern void exmc_nfc_reset(void);
extern void exmc_nfc_release(void);
extern void exmc_nfc_block_erase(uint8_t bank, uint8_t addr);
extern uint32_t exmc_nfc_readid(uint8_t bank, uint8_t addr);
extern uint32_t exmc_nfc_pageread(uint32_t addr);
extern void exmc_nfc_pagewrite(uint32_t addr, uint32_t data);
extern uint32_t exmc_nfc_readstatus(uint8_t bank);
//@} // ExmcGroup

#ifdef __cplusplus
}
#endif

#endif /* __EXMC_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
