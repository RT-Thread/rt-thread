/******************************************************************************
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
/** \file exmc.c
 **
 ** A detailed description is available at
 ** @link ExmcGroup Exmc description @endlink
 **
 **   - 2017-03-13  1.0  chengy First version for Device Driver Library of Exmc.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "exmc.h"

/**
 *******************************************************************************
 ** \addtogroup ExmcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief  Initial SMC
 **
 ** \retval  none
 **
 ******************************************************************************/
void exmc_smc_init(stc_SMCInit_TypeDef* pstcSmcInit)
{
    uint32_t u32SmcBacr = 0;
    /* exit low power mode. */
    SMC_EXIT_LPWOR();
    /* set addr and data whether reuse or not. */
    M4_EXMC->EXMC_EXCR1_f.SMCMUX = pstcSmcInit->SmcMux;
    /* set time parameters for SMC*/
    M4_EXMC->SMC_TMCR = pstcSmcInit->SmcTmcr.smc_tmcr_byte;
    /* set base parameters for SMC,include memrory width, syn or asyn read/write.*/
    u32SmcBacr = (uint32_t)pstcSmcInit->SmcBacr.mw |
                 (pstcSmcInit->SmcBacr.rsyn << 2)|
                 (pstcSmcInit->SmcBacr.rbl << 3) |
                 (pstcSmcInit->SmcBacr.wsyn << 6) |
                 (pstcSmcInit->SmcBacr.wbl << 7) |
                 (pstcSmcInit->SmcBacr.baas << 10) |
                 (pstcSmcInit->SmcBacr.advs << 11) |
                 (pstcSmcInit->SmcBacr.blss << 12);
    M4_EXMC->SMC_BACR = u32SmcBacr;
    /* chip0~3 UpdataRegs cmd*/
    M4_EXMC->SMC_CMDR = (uint32_t)pstcSmcInit->SmcCmdr.cmdaddr |
                        (pstcSmcInit->SmcCmdr.cres << 20) |
                        (pstcSmcInit->SmcCmdr.cmd << 21) |
                        (CMD_CHIP0 << 23);
    M4_EXMC->SMC_CMDR = (uint32_t)pstcSmcInit->SmcCmdr.cmdaddr |
                        (pstcSmcInit->SmcCmdr.cres << 20) |
                        (pstcSmcInit->SmcCmdr.cmd << 21) |
                        (CMD_CHIP1 << 23);
    M4_EXMC->SMC_CMDR = (uint32_t)pstcSmcInit->SmcCmdr.cmdaddr |
                        (pstcSmcInit->SmcCmdr.cres << 20) |
                        (pstcSmcInit->SmcCmdr.cmd << 21) |
                        (CMD_CHIP2 << 23);
    M4_EXMC->SMC_CMDR = (uint32_t)pstcSmcInit->SmcCmdr.cmdaddr |
                        (pstcSmcInit->SmcCmdr.cres << 20) |
                        (pstcSmcInit->SmcCmdr.cmd << 21) |
                        (CMD_CHIP3 << 23);

    while(pstcSmcInit->SmcTmcr.smc_tmcr_byte != M4_EXMC->SMC_TMSR0);
    while((u32SmcBacr | SMC_CHIP0_ADD | (SMC_CHIP_SEZE << 16))!= M4_EXMC->SMC_BASR0);

    while(pstcSmcInit->SmcTmcr.smc_tmcr_byte != M4_EXMC->SMC_TMSR1);
    while((u32SmcBacr | SMC_CHIP1_ADD | (SMC_CHIP_SEZE << 16))!= M4_EXMC->SMC_BASR1);

    while(pstcSmcInit->SmcTmcr.smc_tmcr_byte != M4_EXMC->SMC_TMSR2);
    while((u32SmcBacr | SMC_CHIP2_ADD | (SMC_CHIP_SEZE << 16))!= M4_EXMC->SMC_BASR2);

    while(pstcSmcInit->SmcTmcr.smc_tmcr_byte != M4_EXMC->SMC_TMSR3);
    while((u32SmcBacr | SMC_CHIP3_ADD | (SMC_CHIP_SEZE << 16))!= M4_EXMC->SMC_BASR3);

}

/**
 *******************************************************************************
 ** \brief  Disable SMC
 **
 ** \retval  none
 **
 ******************************************************************************/
void exmc_smc_disable(void)
{
    /* Disable SMC function. */
    M4_EXMC->EXMC_EXCR0_f.SMCEN = Disable;
}

/**
 *******************************************************************************
 ** \brief  Enable SMC
 **
 ** \retval  none
 **
 ******************************************************************************/
void exmc_smc_enable(void)
{
    /* Enable SMC function. */
    M4_EXMC->EXMC_EXCR0_f.SMCEN = Enable;
}
/**
 *******************************************************************************
 ** \brief  SMC Chip addr
 **
 ** \retval  none
 **
 ******************************************************************************/
uint32_t exmc_smc_chip_addr(en_ExmcCmdChip_t enSmcChip)
{
    uint32_t u32chip_addr = 0;
    if(Chip0 == enSmcChip)
    {
        u32chip_addr = SMC_CHIP0_ADD;
    }
    else if(Chip1 == enSmcChip)
    {
        u32chip_addr = SMC_CHIP1_ADD;
    }
    else if(Chip2 == enSmcChip)
    {
        u32chip_addr = SMC_CHIP2_ADD;
    }
    else if(Chip3 == enSmcChip)
    {
        u32chip_addr = SMC_CHIP3_ADD;
    }    
    return u32chip_addr;
}
/**
 *******************************************************************************
 ** \brief  Initial DMC
 **
 ** \retval  none
 **
 ** \note dmc must initialize after enable dmc
 **
 ******************************************************************************/
void exmc_dmc_init(stc_DMCInit_TypeDef* pstcDmcInit)
{
    uint32_t u32DmcBacr = 0;            
    /* set memrory width(16bit or 32bit) for DMC.*/
    M4_EXMC->EXMC_EXCR1_f.DMCMW = pstcDmcInit->DmcMw;

    M4_EXMC->DMC_STCR = DMC_CONFIG;
    /* set timing parameters for DMC.*/
    M4_EXMC->DMC_TMCR_T_CASL = pstcDmcInit->DmcTime.tcasl << 1;
    M4_EXMC->DMC_TMCR_T_DQSS = pstcDmcInit->DmcTime.tdqss;
    M4_EXMC->DMC_TMCR_T_MRD = pstcDmcInit->DmcTime.tmrd;
    M4_EXMC->DMC_TMCR_T_RAS = pstcDmcInit->DmcTime.tras;
    M4_EXMC->DMC_TMCR_T_RC = pstcDmcInit->DmcTime.trc;
    M4_EXMC->DMC_TMCR_T_RCD = pstcDmcInit->DmcTime.trcd | (0x03 << 3);
    M4_EXMC->DMC_TMCR_T_RFC = pstcDmcInit->DmcTime.trfc | (1 << 9);
    M4_EXMC->DMC_TMCR_T_RP = pstcDmcInit->DmcTime.trp | (0x03 << 3);
    M4_EXMC->DMC_TMCR_T_RRD = pstcDmcInit->DmcTime.trrd;
    M4_EXMC->DMC_TMCR_T_WR = pstcDmcInit->DmcTime.twr;
    M4_EXMC->DMC_TMCR_T_WTR = pstcDmcInit->DmcTime.twtr;
    M4_EXMC->DMC_TMCR_T_XP = pstcDmcInit->DmcTime.txp;
    M4_EXMC->DMC_TMCR_T_XSR = pstcDmcInit->DmcTime.txsr;
    M4_EXMC->DMC_TMCR_T_ESR = pstcDmcInit->DmcTime.tesr;
    /* set base parameters for DMC,include burst lenth, Rowbitwidth,ColbitWidth.*/
    u32DmcBacr = (uint32_t)pstcDmcInit->DmcBacr.colbs |
                 (pstcDmcInit->DmcBacr.rowbs << 3) |
                 (pstcDmcInit->DmcBacr.apbs << 6) |
                 (pstcDmcInit->DmcBacr.ckedisprd << 7) |
                 (pstcDmcInit->DmcBacr.ckedis << 13) |
                 (pstcDmcInit->DmcBacr.ckstp << 14) |
                 (pstcDmcInit->DmcBacr.burst << 15) |
                 ( pstcDmcInit->DmcBacr.actcp << 21);
    M4_EXMC->DMC_BACR = u32DmcBacr;
    /* set auto refresh period*/
    M4_EXMC->DMC_RFCR = pstcDmcInit->DmcRefprd;
    
    /* set chip0~chip3 chip_size, addr, address decoding mode*/
    M4_EXMC->DMC_CPCR0 = (uint32_t)pstcDmcInit->DmcCpcr0.addmsk |
                         (pstcDmcInit->DmcCpcr0.addmat << 8) |
                         (pstcDmcInit->DmcCpcr0.brc << 16);
    M4_EXMC->DMC_CPCR1 = (uint32_t)pstcDmcInit->DmcCpcr1.addmsk |
                         (pstcDmcInit->DmcCpcr1.addmat << 8) |
                         (pstcDmcInit->DmcCpcr1.brc << 16);
    M4_EXMC->DMC_CPCR2 = (uint32_t)pstcDmcInit->DmcCpcr2.addmsk |
                         (pstcDmcInit->DmcCpcr2.addmat << 8) |
                         (pstcDmcInit->DmcCpcr2.brc << 16);
    M4_EXMC->DMC_CPCR3 = (uint32_t)pstcDmcInit->DmcCpcr3.addmsk |
                         (pstcDmcInit->DmcCpcr3.addmat << 8) |
                         (pstcDmcInit->DmcCpcr3.brc << 16);
    /*chip0 cmd nop->PrechargeAll->AutoRefresh->AutoRefresh->MdRegConfig->nop.*/
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP0 << 20) |
                        DMC_CMD_NOP;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP0 << 20) |
                        DMC_CMD_PRECHARGEALL;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP0 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP0 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)pstcDmcInit->DmcCmdr.cmdadd |
                        (DMC_BANK0 << 16) |
                        (CMD_CHIP0 << 20) |
                        DMC_CMD_MDREGCONFIG;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP0 << 20) |
                        DMC_CMD_NOP;
    /* chip1 cmd nop->PrechargeAll->AutoRefresh->MdRegConfig. */
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP1 << 20) |
                        DMC_CMD_NOP;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP1 << 20) |
                        DMC_CMD_PRECHARGEALL;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP1 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP1 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)pstcDmcInit->DmcCmdr.cmdadd |
                        (DMC_BANK0 << 16) |
                        (CMD_CHIP1 << 20) |
                        DMC_CMD_MDREGCONFIG;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP1 << 20) |
                        DMC_CMD_NOP;
    /* chip2 cmd nop->PrechargeAll->AutoRefresh->MdRegConfig. */
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP2 << 20) |
                        DMC_CMD_NOP;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP2 << 20) |
                        DMC_CMD_PRECHARGEALL;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP2 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP2 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)pstcDmcInit->DmcCmdr.cmdadd |
                        (DMC_BANK0 << 16) |
                        (CMD_CHIP2 << 20) |
                        DMC_CMD_MDREGCONFIG;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP2 << 20) |
                        DMC_CMD_NOP;
    /* chip3 cmd nop->PrechargeAll->AutoRefresh->MdRegConfig. */
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP3 << 20) |
                        DMC_CMD_NOP;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP3 << 20) |
                        DMC_CMD_PRECHARGEALL;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP3 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP3 << 20) |
                        DMC_CMD_AUTOREFRESH;
    M4_EXMC->DMC_CMDR = (uint32_t)pstcDmcInit->DmcCmdr.cmdadd |
                        (DMC_BANK0 << 16) |
                        (CMD_CHIP3 << 20) |
                        DMC_CMD_MDREGCONFIG;
    M4_EXMC->DMC_CMDR = (uint32_t)(DMC_BANK0 << 16) |
                        (CMD_CHIP3 << 20) |
                        DMC_CMD_NOP;
    /* switch config to ready.*/
    M4_EXMC->DMC_STCR = DMC_GO;
    M4_EXMC->DMC_STCR = DMC_WAKEUP;
    M4_EXMC->DMC_STCR = DMC_GO;
}
/**
 *******************************************************************************
 ** \brief  DMC Chip addr
 **
 ** \retval  none
 **
 ******************************************************************************/
uint32_t exmc_dmc_chip_addr(stc_DMCInit_TypeDef* pstcDmcInit)
{
    uint32_t u32DmcChipaddr;
    if(Chip0 == pstcDmcInit->DmcChip)
    {
        u32DmcChipaddr = pstcDmcInit->DmcCpcr0.addmat << 24;
    }
    else if(Chip1 == pstcDmcInit->DmcChip)
    {
        u32DmcChipaddr = pstcDmcInit->DmcCpcr1.addmat << 24;
    }
    else if(Chip2 == pstcDmcInit->DmcChip)
    {
        u32DmcChipaddr = pstcDmcInit->DmcCpcr2.addmat << 24;
    }
    else if(Chip3 == pstcDmcInit->DmcChip)
    {
        u32DmcChipaddr = pstcDmcInit->DmcCpcr3.addmat << 24;
    }
    return u32DmcChipaddr;
}
/**
 *******************************************************************************
 ** \brief  Disable DMC
 **
 ** \retval  none
 **
 ******************************************************************************/
void exmc_dmc_disable(void)
{
    /* disable DMC function*/
    M4_EXMC->EXMC_EXCR0_f.DMCEN = Disable;       
}
/**
 *******************************************************************************
 ** \brief  Enable DMC
 **
 ** \retval  none
 **
 ******************************************************************************/
void exmc_dmc_enable(void)
{
    /* Enable DMC function*/
    M4_EXMC->EXMC_EXCR0_f.DMCEN = Enable;       
}


/**
 *******************************************************************************
 ** \brief  Initial nfc
 **
 ** \retval none
 **
 ******************************************************************************/
void exmc_nfcinit(stc_NFCInit_TypeDef* pstcNfcInit)
{
    /* enable NFC module clk */
    M4_MSTP->FCG1 &= ~(Enable<<15);
    /* enable NFC function */
    M4_EXMC->EXMC_EXCR0_f.NFCEN = Enable;

    M4_EXMC->NFC_BACR = (uint32_t)pstcNfcInit->NfcSize |
                        (pstcNfcInit->NfcbitWidth << 3) |
                        (pstcNfcInit->NfcBankNum << 6) |
                        (pstcNfcInit->NfcPageSize << 8) |
                        (pstcNfcInit->NfcWp << 10) |
                        (pstcNfcInit->NfcEccBit << 11) |
                        (pstcNfcInit->NfcRac << 13) |
                        (pstcNfcInit->NfcScs << 16);
}

/**
 *******************************************************************************
 ** \brief  NFC reset
 **
 ** \retval none
 **
 ******************************************************************************/
void exmc_nfc_reset(void)
{
    M4_EXMC->NFC_CMDR = NFC_CMD_RESET;
    while(1 == M4_EXMC->EXMC_EXSR1);
}
/**
 *******************************************************************************
 ** \brief  Release nfc
 **
 ** \retval none
 **
 ******************************************************************************/
void exmc_nfc_release(void)
{
    M4_EXMC->NFC_CMDR = NFC_CMD_RELEASE;
    while(1 == M4_EXMC->EXMC_EXSR1);
}
/**
 *******************************************************************************
 ** \brief  NFC block erase
 **
 ** \retval none
 **
 ******************************************************************************/
void exmc_nfc_block_erase(uint8_t bank, uint8_t addr)
{
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG3 | NFC_CMD_BLOCKERASE1 | (bank << 8));
    /* least-significant bit of row address*/
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG2 | (bank << 8) | (addr & 0x01));
    /* second least-significant bit of row address*/
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG2 | (bank << 8) | (addr & 0x02));
    /*  highest-significant bit of row address*/
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG2 | (bank << 8) | (addr & 0x20));
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG1 | NFC_CMD_BLOCKERASE2| (bank << 8));
    while(1 == M4_EXMC->EXMC_EXSR1);
}
/**
 *******************************************************************************
 ** \brief  read nfc ID
 **
 ** \retval uint32_t    ID
 **
 ******************************************************************************/
uint32_t exmc_nfc_readid(uint8_t bank, uint8_t addr)
{
    uint32_t u32id;
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG3 | (bank << 8) | NFC_CMD_READID);
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG2 | (bank << 8) | addr);
    while(1 == M4_EXMC->EXMC_EXSR1);
    u32id = M4_EXMC->NFC_DATR_BASE;
    return u32id;
}
/**
 *******************************************************************************
 ** \brief  nfc page read
 **
 ** \retval uint32_t    read data
 **
 ******************************************************************************/
uint32_t exmc_nfc_pageread(uint32_t addr)
{
    uint32_t u32data;
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG1 | NFC_CMD_READ1);
    while(1 == M4_EXMC->EXMC_EXSR1);
    M4_EXMC->NFC_IDXR0 = addr;
    M4_EXMC->NFC_IDXR1 = 0;
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG1 | NFC_CMD_STARTREAD);
    while(1 == M4_EXMC->EXMC_EXSR1);
    u32data = M4_EXMC->NFC_DATR_BASE;
    M4_EXMC->NFC_CMDR = NFC_CMD_RELEASE;
    return u32data;
}
/**
 *******************************************************************************
 ** \brief  nfc page write
 **
 ** \retval uint32_t    read data
 **
 ******************************************************************************/
void exmc_nfc_pagewrite(uint32_t addr, uint32_t data)
{
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG1 | NFC_CMD_PAGEWRITE1);
    M4_EXMC->NFC_IDXR0 = addr;
    M4_EXMC->NFC_IDXR1 = 0;
    M4_EXMC->NFC_DATR_BASE = data;
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG1 | NFC_CMD_PAGEWRITE2);
    while(1 == M4_EXMC->EXMC_EXSR1);
    M4_EXMC->NFC_CMDR = NFC_CMD_RELEASE;
}
/**
 *******************************************************************************
 ** \brief  nfc page write
 **
 ** \retval uint32_t    read data
 **
 ******************************************************************************/
uint32_t exmc_nfc_readstatus(uint8_t bank)
{
    uint32_t u32status;
    M4_EXMC->NFC_CMDR = (NFC_CMD_ARG3 | NFC_CMD_READSTATUS | (bank << 8));
    u32status = M4_EXMC->NFC_DATR_BASE;
    M4_EXMC->NFC_CMDR = NFC_CMD_RELEASE;
    return u32status;
}
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

//@} // ExmcGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
