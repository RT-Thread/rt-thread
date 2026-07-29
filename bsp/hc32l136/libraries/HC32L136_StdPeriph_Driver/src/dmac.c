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
/** \file dmac.c
**
** A detailed description is available at
** @link DmacGroup Dmac description @endlink
**
**   - 2018-03-09  1.0  Hongjh First version for Device Driver Library of Dmac.
**
******************************************************************************/

/*******************************************************************************
* Include files
******************************************************************************/
#include "dmac.h"

/**
*******************************************************************************
** \addtogroup DmacGroup
******************************************************************************/
//@{

/*******************************************************************************
* Local type definitions ('typedef')
******************************************************************************/

/*******************************************************************************
* Local pre-processor symbols/macros ('#define')
******************************************************************************/

/******************************************************************************/
/*                                     DMA                                    */
/******************************************************************************/
/*****************  Bits definition for DMA_INTSTAT0 register  ****************/
#define DMA_INTSTAT0_TRNERR_Pos             (0U)                                /*!< DMA_INTSTAT0: TRNERR Position */
#define DMA_INTSTAT0_REQERR_Pos             (16U)                               /*!< DMA_INTSTAT0: REQERR Position */

/*****************  Bits definition for DMA_INTSTAT1 register  ****************/
#define DMA_INTSTAT1_TC_Pos                 (0U)                                /*!< DMA_INTSTAT1: TC Position */
#define DMA_INTSTAT1_BTC_Pos                (16U)                               /*!< DMA_INTSTAT1: BTC Position */

/*****************  Bits definition for DMA_INTMASK0 register  ****************/
#define DMA_INTMASK0_MSKTRNERR_Pos          (0U)                                /*!< DMA_INTMASK0: MSKTRNERR Position */
#define DMA_INTMASK0_MSKREQERR_Pos          (16U)                               /*!< DMA_INTMASK0: MSKREQERR Position */

/*****************  Bits definition for DMA_INTMASK1 register  ****************/
#define DMA_INTMASK1_MSKTC_Pos              (0U)                                /*!< DMA_INTMASK1: MSKTC Position */
#define DMA_INTMASK1_MSKBTC_Pos             (16U)                               /*!< DMA_INTMASK1: MSKBTC Position */

/*****************  Bits definition for DMA_INTCLR0 register  *****************/
#define DMA_INTCLR0_CLRTRNERR_Pos           (0U)                                /*!< DMA_INTCLR0: CLRTRNERR Position */
#define DMA_INTCLR0_CLRREQERR_Pos           (16U)                               /*!< DMA_INTCLR0: CLRREQERR Position */

/*****************  Bits definition for DMA_INTCLR1 register  *****************/
#define DMA_INTCLR1_CLRTC_Pos               (0U)                                /*!< DMA_INTCLR1: CLRTC Position */
#define DMA_INTCLR1_CLRBTC_Pos              (16U)                               /*!< DMA_INTCLR1: CLRBTC Position */

/*******************  Bits definition for DMA_CHEN register  ******************/
#define DMA_CHEN_CHEN_Pos                   (0U)                                /*!< DMA_CHEN: CHEN Position */

/**************  Bits definition for DMA_TRGSELx(x=0~7) register  *************/
#define DMA_TRGSEL_TRGSEL_Pos               (0U)                                /*!< DMA_TRGSELx: TRGSEL Position */
#define DMA_TRGSEL_TRGSEL_Msk               (0x1FFU << DMA_TRGSEL_TRGSEL_Pos)   /*!< DMA_TRGSELx: TRGSEL Mask 0x000001FF */
#define DMA_TRGSEL_TRGSEL                   DMA_TRGSEL_TRGSEL_Msk
/**************  Bits definition for DMA_DTCTLx(x=0~7) register  **************/
#define DMA_DTCTL_BLKSIZE_Pos               (0U)                                /*!< DMA_DTCTLx: BLKSIZE Position */
#define DMA_DTCTL_BLKSIZE_Msk               (0x3FFU << DMA_DTCTL_BLKSIZE_Pos)   /*!< DMA_DTCTLx: BLKSIZE Mask 0x000003FF */
#define DMA_DTCTL_BLKSIZE                   DMA_DTCTL_BLKSIZE_Msk

#define DMA_DTCTL_CNT_Pos                   (16U)                               /*!< DMA_DTCTLx: CNT Position */
#define DMA_DTCTL_CNT_Msk                   (0xFFFFU << DMA_DTCTL_CNT_Pos)      /*!< DMA_DTCTLx: CNT Mask 0xFFFF0000 */
#define DMA_DTCTL_CNT                       DMA_DTCTL_CNT_Msk

/***************  Bits definition for DMA_RPTx(x=0~7) register  ***************/
#define DMA_RPT_SRPT_Pos                    (0U)                                /*!< DMA_RPTx: SRPT Position */
#define DMA_RPT_SRPT_Msk                    (0x1FFU << DMA_RPT_SRPT_Pos)        /*!< DMA_RPTx: SRPT Mask 0x000001FF */
#define DMA_RPT_SRPT                        DMA_RPT_SRPT_Msk

#define DMA_RPT_DRPT_Pos                    (16U)                               /*!< DMA_RPTx: DRPT Position */
#define DMA_RPT_DRPT_Msk                    (0x1FFU << DMA_RPT_DRPT_Pos)        /*!< DMA_RPTx: DRPT Mask 0x01FF0000 */
#define DMA_RPT_DRPT                        DMA_RPT_DRPT_Msk

/*************  Bits definition for DMA_SNSEQCTLx(x=0~7) register  ************/
#define DMA_SNSEQCTL_SOFFSET_Pos            (0U)                                /*!< DMA_SNSEQCTLx: SOFFSET Position */
#define DMA_SNSEQCTL_SOFFSET_Msk            (0xFFFFFU << DMA_SNSEQCTL_SOFFSET_Pos)    /*!< DMA_SNSEQCTLx: SOFFSET Mask 0x000FFFFF */
#define DMA_SNSEQCTL_SOFFSET                DMA_SNSEQCTL_SOFFSET_Msk

#define DMA_SNSEQCTL_SNSCNT_Pos             (20U)                               /*!< DMA_SNSEQCTLx: SNSCNT Position */
#define DMA_SNSEQCTL_SNSCNT_Msk             (0xFFFU << DMA_SNSEQCTL_SNSCNT_Pos)      /*!< DMA_SNSEQCTLx: SNSCNT Mask 0xFFF00000 */
#define DMA_SNSEQCTL_SNSCNT                 DMA_SNSEQCTL_SNSCNT_Msk

/*************  Bits definition for DMA_DNSEQCTLx(x=0~7) register  ************/
#define DMA_DNSEQCTL_DOFFSET_Pos            (0U)                                /*!< DMA_DNSEQCTLx: DOFFSET Position */
#define DMA_DNSEQCTL_DOFFSET_Msk            (0xFFFFFU << DMA_DNSEQCTL_DOFFSET_Pos)   /*!< DMA_DNSEQCTLx: DOFFSET Mask 0x000FFFFF */
#define DMA_DNSEQCTL_DOFFSET                DMA_DNSEQCTL_DOFFSET_Msk

#define DMA_DNSEQCTL_DNSCNT_Pos             (20U)                               /*!< DMA_DNSEQCTLx: DNSCNT Position */
#define DMA_DNSEQCTL_DNSCNT_Msk             (0xFFFU << DMA_DNSEQCTL_DNSCNT_Pos)      /*!< DMA_DNSEQCTLx: DNSCNT Mask 0xFFF00000 */
#define DMA_DNSEQCTL_DNSCNT                 DMA_DNSEQCTL_DNSCNT_Msk

/***************  Bits definition for DMA_CHxCTL(x=0~7) register  *************/
#define DMA_CHCTL_SINC_Pos                  (0U)                                /*!< DMA_CHxCTL: SINC Position */
#define DMA_CHCTL_SINC_Msk                  (0x3u << DMA_CHCTL_SINC_Pos)        /*!< DMA_CHxCTL: SINC Mask 0x00000003 */
#define DMA_CHCTL_SINC                      DMA_CHCTL_SINC_Msk

#define DMA_CHCTL_DINC_Pos                  (2U)                                /*!< DMA_CHxCTL: DINC Position */
#define DMA_CHCTL_DINC_Msk                  (0x3U << DMA_CHCTL_DINC_Pos)        /*!< DMA_CHxCTL: DINC Mask 0x0000000C */
#define DMA_CHCTL_DINC                      DMA_CHCTL_DINC_Msk

#define DMA_CHCTL_SRPTEN_Pos                (4U)                                /*!< DMA_CHxCTL: SRPTEN Position */
#define DMA_CHCTL_DRPTEN_Pos                (5U)                                /*!< DMA_CHxCTL: DRPTEN Position */
#define DMA_CHCTL_SNSEQEN_Pos               (6U)                                /*!< DMA_CHxCTL: SNSEQEN Position */
#define DMA_CHCTL_DNSEQEN_Pos               (7U)                                /*!< DMA_CHxCTL: DNSEQEN Position */

#define DMA_CHCTL_HSIZE_Pos                 (8U)                                /*!< DMA_CHxCTL: HSIZE Position */
#define DMA_CHCTL_HSIZE_Msk                 (0x3U << DMA_CHCTL_HSIZE_Pos)       /*!< DMA_CHxCTL: HSIZE Mask 0x00000300 */
#define DMA_CHCTL_HSIZE                     DMA_CHCTL_HSIZE_Msk

#define DMA_CHCTL_LLPEN_Pos                 (10U)                               /*!< DMA_CHxCTL: LLPEN Position */
#define DMA_CHCTL_LLPRUN_Pos                (11U)                               /*!< DMA_CHxCTL: LLPRUN Position */
#define DMA_CHCTL_IE_Pos                    (12U)                               /*!< DMA_CHxCTL: IE Position */
#define DMA_CHCTL_PROT_Pos                  (13U)                               /*!< DMA_CHxCTL: PROT Position */

/************************  DMA_TRGSELx(x=0~7) register  ***********************/
#define DMA_TRGSEL_BASE                     (0x40010854U)
#define DMA_TRGSEL(x)                       (*(volatile uint32_t *)((x) * 0x4U + DMA_TRGSEL_BASE))

#define INTC_INTSFTTRG_BASE                 (0x40010800U)
#define INTC_INTSFTTRG                      (*(volatile uint32_t *)INTC_INTSFTTRG_BASE)

/***********************  DMA REGISTERx(x=0~7) register  **********************/
#define _DMA_CH_REG_OFFSET(ch)              ((ch) * 0x40U)
#define _DMA_CH_REG(reg_base, ch)           (*(volatile uint32_t *)((reg_base) + _DMA_CH_REG_OFFSET(ch)))

#define WRITE_DMA_CH_REG(reg_base, ch, val)         (_DMA_CH_REG((reg_base), (ch)) = (val))
#define READ_DMA_CH_REG(reg_base, ch)               (_DMA_CH_REG((reg_base), (ch)))

#define SET_DMA_CH_REG_BIT(reg_base, ch, pos)       (_DMA_CH_REG((reg_base), (ch)) |= (1U << (pos)))
#define CLR_DMA_CH_REG_BIT(reg_base, ch, pos)       (_DMA_CH_REG((reg_base), (ch)) &= (~(1U << (pos))))


/**********************  SET DMA_TRGSELx(x=0~7) register  *********************/

#define SET_DMA_CHCTL_PROT(CH, PROT)        SET_DMA_CHCTL_PROT((CH), (PROT))

/**************************  SET INTSFTTRG register  **************************/
#define SOFTWARE_TRIGGER_DMA()                 (INTC_INTSFTTRG = 1U)

/*! Parameter valid check for Dmac Channel. */
#define IS_VALID_CH(x)                      \
(   (DmaCh0 == (x))                      || \
  (DmaCh1 == (x)))

/*! Parameter valid check for Dmac transfer data width. */
#define IS_VALID_TRN_WIDTH(x)               \
(   (Dma8Bit == (x))                     || \
  (Dma16Bit == (x))                    || \
    (Dma32Bit == (x)))

/*! Parameter valid check for Dmac address mode. */
#define IS_VALID_ADDR_MODE(x)               \
(   (AddressFix == (x))                  || \
  (AddressIncrease == (x)))

#define IS_VALID_PRIO_MODE(x)               \
(   (DmaPriorityFix == (x))                  || \
  (DmaPriorityLoop == (x)))

/*! Parameter valid check for Dmac transfer block size. */
#define IS_VALID_BLKSIZE(x)                 (!((x) & ~(DMA_DTCTL_BLKSIZE_Msk >> DMA_DTCTL_BLKSIZE_Pos)))

/*! Parameter valid check for Dmac transfer count. */
#define IS_VALID_TRNCNT(x)                  (!((x) & ~(DMA_DTCTL_CNT_Msk >> DMA_DTCTL_CNT_Pos)))

/*! Parameter valid check for Dmac destination repeat size. */
#define IS_VALID_DRPT_SIZE(x)               (!((x) & ~(DMA_RPT_DRPT_Msk >> DMA_RPT_DRPT_Pos)))

/*! Parameter valid check for Dmac source no-sequence count. */
#define IS_VALID_SNSCNT(x)                  (!((x) & ~(DMA_SNSEQCTL_SNSCNT_Msk >> DMA_SNSEQCTL_SNSCNT_Pos)))

/*! Parameter valid check for Dmac source no-sequence offset. */
#define IS_VALID_SNSOFFSET(x)               (!((x) & ~(DMA_SNSEQCTL_SOFFSET_Msk >> DMA_SNSEQCTL_SOFFSET_Pos)))

/*! Parameter valid check for Dmac destination no-sequence count. */
#define IS_VALID_DNSCNT(x)                  (!((x) & ~(DMA_DNSEQCTL_DNSCNT_Msk >> DMA_DNSEQCTL_DNSCNT_Pos)))

/*! Parameter valid check for Dmac destination no-sequence offset. */
#define IS_VALID_DNSOFFSET(x)               (!((x) & ~(DMA_DNSEQCTL_DOFFSET_Msk >> DMA_DNSEQCTL_DOFFSET_Pos)))

/*******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/

/*******************************************************************************
* Local function prototypes ('static')
******************************************************************************/

/*******************************************************************************
* Local variable definitions ('static')
******************************************************************************/
static stc_dma_irq_calbakfn_pt_t stcDmaIrqCalbaks = {NULL, NULL,NULL, NULL};
/*******************************************************************************
* Function implementation - global ('extern') and local ('static')
******************************************************************************/

/**
*******************************************************************************
** \brief Initializes a DMA channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] pstcConfig             The structure pointer of DMA module configuration.
**
** \retval Ok                          Initializes successfully.
** \retval ErrorInvalidParameter       enCh is invalid or the pstcConfig is NULL.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_config_t* pstcConfig)
{
  ASSERT(IS_VALID_CH(enCh));
  ASSERT(NULL != pstcConfig);
  ASSERT(IS_VALID_BLKSIZE(pstcConfig->u16BlockSize));
  ASSERT(IS_VALID_TRNCNT(pstcConfig->u16TransferCnt));
  ASSERT(IS_VALID_TRN_WIDTH(pstcConfig->enTransferWidth));
  ASSERT(IS_VALID_ADDR_MODE(pstcConfig->enSrcAddrMode));
  ASSERT(IS_VALID_ADDR_MODE(pstcConfig->enDstAddrMode));
  
  /* Check for channel and NULL pointer */
  if (!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {   
    M0P_DMAC->CONFB0_f.FIS_IE = 0;
    M0P_DMAC->CONFB0_f.ERR_IE = 0; /* Disable DMAC interrupt */
    
    /*******************  SET DMA MODE   ******************/    
    M0P_DMAC->CONFB0_f.MODE = pstcConfig->enMode;
    /*******************  SET DMA_TRGSELx register  ******************/
    M0P_DMAC->CONFA0_f.TRI_SEL = pstcConfig->enRequestNum;
    /*******************  SET DMA_DTCTLx(x=0~7) register  ******************/
    /* Block size */
    M0P_DMAC->CONFA0_f.BC = pstcConfig->u16BlockSize - 1;
    /* Transfer count */
    M0P_DMAC->CONFA0_f.TC = pstcConfig->u16TransferCnt - 1;
    
    /*******************  SET DMA_CHxCTL(x=0~7) register  ******************/
    /* Transfer width */
    M0P_DMAC->CONFB0_f.WIDTH = pstcConfig->enTransferWidth;
    
    /****************************** source address contrl *******************/
    /* source address mode */
    M0P_DMAC->CONFB0_f.FS = pstcConfig->enSrcAddrMode;
    /* Source address */
    M0P_DMAC->SRCADR0_f.SRCADR = pstcConfig->u32SrcAddress;
    
    /*************************** destination address contrl *******************/
    /* destination address mode */
    M0P_DMAC->CONFB0_f.FD = pstcConfig->enDstAddrMode;
    /* Destination address */
    M0P_DMAC->DSTADR0_f.DSTADR = pstcConfig->u32DstAddress;
    /*********************  Source address reload control  ********************/
    M0P_DMAC ->CONFB0_f.RS = pstcConfig->bSrcAddrReloadCtl;
    
    /*******************  Destination address reload control  *****************/
    M0P_DMAC ->CONFB0_f.RD = pstcConfig->bDestAddrReloadCtl;
    
    /*******************  Destination bc/tc reload control  *****************/
    M0P_DMAC ->CONFB0_f.RC = pstcConfig->bSrcBcTcReloadCtl;
    
   /*******************  MSK control  *****************/    
    M0P_DMAC->CONFB0_f.MSK = pstcConfig->bMsk;
    
  }
  else{
    M0P_DMAC->CONFB1_f.FIS_IE = 0;
    M0P_DMAC->CONFB1_f.ERR_IE = 0; /* Disable DMAC interrupt */
    /*******************  SET DMA MODE   ******************/    
    M0P_DMAC->CONFB1_f.MODE = pstcConfig->enMode;
    /*******************  SET DMA_TRGSELx register  ******************/
    M0P_DMAC->CONFA1_f.TRI_SEL = pstcConfig->enRequestNum;
    /*******************  SET DMA_DTCTLx(x=0~7) register  ******************/
    /* Block size */
    M0P_DMAC->CONFA1_f.BC = pstcConfig->u16BlockSize - 1;
    /* Transfer count */
    M0P_DMAC->CONFA1_f.TC = pstcConfig->u16TransferCnt - 1;
    
    /*******************  SET DMA_CHxCTL(x=0~7) register  ******************/
    /* Transfer width */
    M0P_DMAC->CONFB1_f.WIDTH = pstcConfig->enTransferWidth;
    
    /****************************** source address contrl *******************/
    /* source address mode */
    M0P_DMAC->CONFB1_f.FS =  pstcConfig->enSrcAddrMode;
    /* Source address */
    M0P_DMAC->SRCADR1_f.SRCADR = pstcConfig->u32SrcAddress;
    
    /*************************** destination address contrl *******************/
    /* destination address mode */
    M0P_DMAC->CONFB1_f.FD = pstcConfig->enDstAddrMode;
    /* Destination address */
    M0P_DMAC->DSTADR1_f.DSTADR = pstcConfig->u32DstAddress;
    
    /*********************  Source address reload control  ********************/
    M0P_DMAC ->CONFB1_f.RS = pstcConfig->bSrcAddrReloadCtl;
    
    /*******************  Destination address reload control  *****************/
    M0P_DMAC ->CONFB1_f.RD = pstcConfig->bDestAddrReloadCtl;
    
    /*******************  Destination bc/tc reload control  *****************/
    M0P_DMAC ->CONFB1_f.RC = pstcConfig->bSrcBcTcReloadCtl; 
    
    /*******************  MSK control  *****************/    
    M0P_DMAC->CONFB1_f.MSK = pstcConfig->bMsk;
  }
  return Ok;
}

/**
*******************************************************************************
** \brief Trigger dma transfer by software.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SwTrigger(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.TRI_SEL = 0x0000;
  }
  else{
    M0P_DMAC->CONFA1_f.TRI_SEL = 0x0000;   	
  }
}

/**
*******************************************************************************
** \brief Enable dma function.
**
** \param  None
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_Enable(void)
{
  M0P_DMAC->CONF_f.EN = 1;
}

/**
*******************************************************************************
** \brief Disable dma function.
**
** \param  None
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_Disable(void)
{
  M0P_DMAC->CONF_f.EN = 0;
}
/**
*******************************************************************************
** \brief Start dma function.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_Start(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.ST = 1;
  }
  else{
    M0P_DMAC->CONFA1_f.ST = 1;   	
  }  
}

/**
*******************************************************************************
** \brief Disable dma function.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_Stop(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.ST = 0;
  }
  else{
    M0P_DMAC->CONFA1_f.ST = 0;   	
  }  
}
/**
*******************************************************************************
** \brief  Enable the specified dma interrupt.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] enIrqSel               The specified dma flag.
** \arg    TrnErrIrq                   The DMA transfer error interrupt.
** \arg    TrnReqErrIrq                DMA transfer req over error interrupt.
** \arg    TrnCpltIrq                  DMA transfer completion interrupt.
** \arg    BlkTrnCpltIrq               DMA block completion interrupt.
**
** \retval Ok                          Interrupt enabled normally.
** \retval ErrorInvalidParameter       enCh or enIrqSel is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableIrq(en_dma_channel_t enCh, stc_dma_irq_sel_t stcIrqSel)
{
  en_result_t enRet = Ok;
  
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if (TRUE == stcIrqSel.TrnCpltIrq)
  {
     Dma_EnableChannelIrq(enCh);
  }
  if(TRUE == stcIrqSel.TrnErrIrq)
  {
    Dma_EnableChannelErrIrq(enCh);  
  }
  
  return enRet;
}

/**
*******************************************************************************
** \brief  Enable the specified dma interrupt.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] enIrqSel               The specified dma flag.
** \arg    TrnErrIrq                   The DMA transfer error interrupt.
** \arg    TrnReqErrIrq                DMA transfer req over error interrupt.
** \arg    TrnCpltIrq                  DMA transfer completion interrupt.
** \arg    BlkTrnCpltIrq               DMA block completion interrupt.
**
** \retval Ok                          Interrupt disabled normally.
** \retval ErrorInvalidParameter       enCh or enIrqSel is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableIrq(en_dma_channel_t enCh, stc_dma_irq_sel_t stcIrqSel)
{
  en_result_t enRet = Ok;
  
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if (TRUE == stcIrqSel.TrnCpltIrq)
  {
     Dma_DisableChannelIrq(enCh);
  }
  if(TRUE == stcIrqSel.TrnErrIrq)
  {
    Dma_DisableChannelErrIrq(enCh);  
  }
  
  return enRet;
}

/**
*******************************************************************************
** \brief  Enable the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Enable channel successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableChannel(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.ENS = 1;
  }
  else{
    M0P_DMAC->CONFA1_f.ENS = 1;  	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Disable the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable channel successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableChannel(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.ENS = 0;;
  }
  else {
    M0P_DMAC->CONFA1_f.ENS = 0;;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the specified dma trigger.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u16TrgSel              The trigger selection number.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16TrgSel is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetTriggerSel(en_dma_channel_t enCh, en_dma_trig_sel_t enTrgSel)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.TRI_SEL = enTrgSel;;
  }
  else{
    M0P_DMAC->CONFA1_f.TRI_SEL = enTrgSel;;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Setthe source address of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u32Address             The source address.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->SRCADR0_f.SRCADR = u32Address;
  }
  else
  {
    M0P_DMAC->SRCADR1_f.SRCADR = u32Address;;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the destination address of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u32Address             The destination address.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->DSTADR0_f.DSTADR = u32Address;
  }
  else
  {
    M0P_DMAC->DSTADR1_f.DSTADR = u32Address;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the block size of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u32Address             The block size.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16BlkSize is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize)
{
  ASSERT(IS_VALID_CH(enCh));
  ASSERT(IS_VALID_BLKSIZE(u16BlkSize));
  
  if((!IS_VALID_CH(enCh)) || (!IS_VALID_BLKSIZE(u16BlkSize)))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.BC = u16BlkSize - 1;
  }
  else
  {
    M0P_DMAC->CONFA1_f.BC = u16BlkSize - 1;   	
  }
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the transfer count of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u32Address             The transfer count.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16TrnCnt is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt)
{
  ASSERT(IS_VALID_CH(enCh));
  ASSERT(IS_VALID_TRNCNT(u16TrnCnt));
  
  if((!IS_VALID_CH(enCh)) || (!IS_VALID_TRNCNT(u16TrnCnt)))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.TC = u16TrnCnt - 1;
  }
  else
  {
    M0P_DMAC->CONFA1_f.TC = u16TrnCnt - 1;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the source repeat size of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u16Size                The source repeat size.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16Size is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableSourceRload(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if((!IS_VALID_CH(enCh)))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC ->CONFB0_f.RS = 1;
  }
  else
  {
    M0P_DMAC ->CONFB1_f.RS = 1;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the destination repeat size of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u16Size                The destination repeat size.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16Size is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableSourceRload(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC ->CONFB0_f.RS = 0;
  }
  else{
    M0P_DMAC ->CONFB1_f.RS = 0;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the source repeat size of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u16Size                The source repeat size.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16Size is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableDestinationRload(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if((!IS_VALID_CH(enCh)))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC ->CONFB0_f.RD = 1;
  }
  else {
    M0P_DMAC ->CONFB1_f.RD = 1;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the destination repeat size of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u16Size                The destination repeat size.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16Size is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableDestinationRload(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC ->CONFB0_f.RD = 0;
  }
  else{
    M0P_DMAC ->CONFB1_f.RD = 0;   	
  }
  
  return Ok;
}
/**
*******************************************************************************
** \brief  Set the source repeat size of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u16Size                The source repeat size.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16Size is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableBcTcReload(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if((!IS_VALID_CH(enCh)))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC ->CONFB0_f.RC = 1;
  }
  else{
    M0P_DMAC ->CONFB1_f.RC = 1;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the destination repeat size of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] u16Size                The destination repeat size.
**
** \retval Ok                          Set successfully.
** \retval ErrorInvalidParameter       enCh or u16Size is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableBcTcReload(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC ->CONFB0_f.RC = 0;
  }
  else{
    M0P_DMAC ->CONFB1_f.RC = 0;   	
  }
  
  return Ok;
}
/**
*******************************************************************************
** \brief  Set the source address mode of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] enMode                 The specified dma address mode.
** \arg    AddressFix                  Address fixed.
** \arg    AddressIncrease             Address increased.
** \arg    AddressDecrease             Address decreased.
**
** \retval Ok                          Set successfully
** \retval ErrorInvalidParameter       enCh or enMode is invalid
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetSourceIncMode(en_dma_channel_t enCh, en_address_mode_t enMode)
{
  ASSERT(IS_VALID_CH(enCh));
  ASSERT(IS_VALID_ADDR_MODE(enMode));
  
  if((!IS_VALID_CH(enCh)) || (!IS_VALID_ADDR_MODE(enMode)))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.FS = enMode;
  }
  else{
    M0P_DMAC->CONFB1_f.FS = enMode;   	
  }
  
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Set the destination address mode of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] enMode                 The specified dma address mode.
** \arg    AddressFix                  Address fixed.
** \arg    AddressIncrease             Address increased.
** \arg    AddressDecrease             Address decreased.
**
** \retval Ok                          Set successfully
** \retval ErrorInvalidParameter       enCh or enMode is invalid
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetDestinationIncMode(en_dma_channel_t enCh, en_address_mode_t enMode)
{
  ASSERT(IS_VALID_CH(enCh));
  ASSERT(IS_VALID_ADDR_MODE(enMode));
  
  if((!IS_VALID_CH(enCh)) || (!IS_VALID_ADDR_MODE(enMode)))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.FD = enMode;
  }
  else{
    M0P_DMAC->CONFB1_f.FD = enMode;   	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Enable source repeat function of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Enable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableContinusTranfer(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.MSK = 1;
  }
  else{
    M0P_DMAC->CONFB1_f.MSK = 1;  	
  }
  return Ok;
}

/**
*******************************************************************************
** \brief  Disable source repeat function of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableContinusTranfer(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.MSK = 0;
  }
  else{
    M0P_DMAC->CONFB1_f.MSK = 0;  	
  }
  
  return Ok;
}
/**
*******************************************************************************
** \brief  Halt the all dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
void Dma_HaltTranfer(void)
{
  M0P_DMAC->CONF_f.HALT = 0x1;
}
/**
*******************************************************************************
** \brief  Recover all dma channel from HALT.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
void Dma_RecoverTranfer(void)
{
  M0P_DMAC->CONF_f.HALT = 0x0;
}
/**
*******************************************************************************
** \brief  Pause the  specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_PauseChannelTranfer(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if((!IS_VALID_CH(enCh)))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.PAS = 1;
  }
  else{
    M0P_DMAC->CONFA1_f.PAS = 1;  	
  }
  return Ok;
}
/**
*******************************************************************************
** \brief  Recover  the  specified dma channel from PAUSE.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_RecoverChannelTranfer(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if((!IS_VALID_CH(enCh)))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFA0_f.PAS = 0;
  }
  else{
    M0P_DMAC->CONFA1_f.PAS = 0;  	
  }
  return Ok;
}
/**
*******************************************************************************
** \brief  Set transfer data width of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] enWidth                The specified transfer data width.
** \arg    Dma8Bit                     The 8 bit transfer via DMA.
** \arg    Dma16Bit                    The 16 bit transfer via DMA.
** \arg    Dma32Bit                    The 32 bit transfer via DMA.
**
** \retval Ok                          Set successfully
** \retval ErrorInvalidParameter       enCh or enWidth is invalid
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth)
{
  ASSERT(IS_VALID_CH(enCh));
  ASSERT(IS_VALID_TRN_WIDTH(enWidth));
  
  if((!IS_VALID_CH(enCh)) || (!IS_VALID_TRN_WIDTH(enWidth)))
  {
    return ErrorInvalidParameter;
  }
  
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.WIDTH = enWidth;
  }
  else{
    M0P_DMAC->CONFB1_f.WIDTH = enWidth;  	
  }
  
  return Ok;
}
/**
*******************************************************************************
** \brief  Set priority of  dma channel.
**
** \param  [in] enCh                   The specified dma channel.
** \param  [in] enWidth                The specified transfer data width.
** \arg    Dma8Bit                     The 8 bit transfer via DMA.
** \arg    Dma16Bit                    The 16 bit transfer via DMA.
** \arg    Dma32Bit                    The 32 bit transfer via DMA.
**
** \retval Ok                          Set successfully
** \retval ErrorInvalidParameter       enCh or enWidth is invalid
**
** \note   None
**
******************************************************************************/
en_result_t Dma_SetChPriority(en_dma_priority_t enPrio)
{
  ASSERT(IS_VALID_PRIO_MODE(enPrio));
  
  if(!IS_VALID_PRIO_MODE(enPrio))
  {
    return ErrorInvalidParameter;
  }
  
  M0P_DMAC->CONF_f.PRIO = enPrio;
  return Ok;
}
/**
*******************************************************************************
** \brief  Enable interrupt of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Enable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableChannelIrq(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.FIS_IE = 1;
  }
  else{
    M0P_DMAC->CONFB1_f.FIS_IE = 1;  	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Disable interrupt of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableChannelIrq(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.FIS_IE = 0;
  }
  else{
    M0P_DMAC->CONFB1_f.FIS_IE = 0;  	
  }
  
  return Ok;
}
/**
*******************************************************************************
** \brief  Enable error interrupt of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Enable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_EnableChannelErrIrq(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.ERR_IE = 1;
  }
  else{
    M0P_DMAC->CONFB1_f.ERR_IE = 1;  	
  }
  
  return Ok;
}

/**
*******************************************************************************
** \brief  Disable error interrupt of the specified dma channel.
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval Ok                          Disable successfully.
** \retval ErrorInvalidParameter       enCh is invalid.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_DisableChannelErrIrq(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  if(enCh == DmaCh0)
  {
    M0P_DMAC->CONFB0_f.ERR_IE = 0;
  }
  else{
    M0P_DMAC->CONFB1_f.ERR_IE = 0;  	
  }
  
  return Ok;
}

/**
 * \brief   
 *          Dma中断服务程序
 *
 * \param   [in]  u8Param  未使用
 *
 * \retval  无
 */

void Dma_IRQHandler(uint8_t u8Param)
{
    if((DmaAddOverflow == M0P_DMAC->CONFB0_f.STAT)||(DmaHALT == M0P_DMAC->CONFB0_f.STAT)||(DmaAccSCRErr == M0P_DMAC->CONFB0_f.STAT) ||(DmaAccDestErr == M0P_DMAC->CONFB0_f.STAT))
    {
        if (NULL != stcDmaIrqCalbaks.pfnDma0TranferErrIrq)
        {
            stcDmaIrqCalbaks.pfnDma0TranferCompleteIrq();
        }
        M0P_DMAC->CONFB0_f.STAT = 0u;
    }
    if((DmaAddOverflow == M0P_DMAC->CONFB1_f.STAT)||(DmaHALT == M0P_DMAC->CONFB1_f.STAT)||(DmaAccSCRErr == M0P_DMAC->CONFB1_f.STAT) ||(DmaAccDestErr == M0P_DMAC->CONFB1_f.STAT))
    {
        if (NULL != stcDmaIrqCalbaks.pfnDma1TranferErrIrq)
        {
            stcDmaIrqCalbaks.pfnDma1TranferCompleteIrq();
        }
        M0P_DMAC->CONFB1_f.STAT = 0u;
    }	
    if(DmaTransferComplete == M0P_DMAC->CONFB0_f.STAT)
    {
        if (NULL != stcDmaIrqCalbaks.pfnDma0TranferCompleteIrq)
        {
            stcDmaIrqCalbaks.pfnDma0TranferCompleteIrq();
        }
        M0P_DMAC->CONFB0_f.STAT = 0u;
    }
    if(DmaTransferComplete == M0P_DMAC->CONFB1_f.STAT)
    {
        if (NULL != stcDmaIrqCalbaks.pfnDma1TranferCompleteIrq)
        {
            stcDmaIrqCalbaks.pfnDma1TranferCompleteIrq();
        }
        M0P_DMAC->CONFB1_f.STAT = 0u;
    }	
			
}
/**
 * \brief   
 *          配置ADC中断函数入口
 *
 * \param   [in]  pstcAdcIrqCfg  ADC中断配置指针
 * \param   [in]  pstcAdcIrqCalbaks  ADC中断回调函数指针
 *
 * \retval  无
 */
en_result_t Dma_ConfigIrq(en_dma_channel_t enCh,stc_dma_irq_sel_t* stcDmaIrqCfg,stc_dma_irq_calbakfn_pt_t* pstcDmaIrqCalbaks)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return ErrorInvalidParameter;
  }
  if(DmaCh0 == enCh)
  {
    if (TRUE == stcDmaIrqCfg->TrnErrIrq)
    {  
      if (NULL != pstcDmaIrqCalbaks->pfnDma0TranferCompleteIrq)
        {
            stcDmaIrqCalbaks.pfnDma0TranferErrIrq = pstcDmaIrqCalbaks->pfnDma0TranferErrIrq;
        }
    }
    if (TRUE == stcDmaIrqCfg->TrnCpltIrq)
    {
        if (NULL != pstcDmaIrqCalbaks->pfnDma0TranferCompleteIrq)
        {
            stcDmaIrqCalbaks.pfnDma0TranferCompleteIrq = pstcDmaIrqCalbaks->pfnDma0TranferCompleteIrq;
        }
    }
  }
  else if(DmaCh1 == enCh) 
  {
    if (TRUE == stcDmaIrqCfg->TrnErrIrq)
    {  
      if (NULL != pstcDmaIrqCalbaks->pfnDma1TranferCompleteIrq)
        {
            stcDmaIrqCalbaks.pfnDma1TranferErrIrq = pstcDmaIrqCalbaks->pfnDma1TranferErrIrq;
        }
    }
    if (TRUE == stcDmaIrqCfg->TrnCpltIrq)
    {
        if (NULL != pstcDmaIrqCalbaks->pfnDma1TranferCompleteIrq)
        {
            stcDmaIrqCalbaks.pfnDma1TranferCompleteIrq = pstcDmaIrqCalbaks->pfnDma1TranferCompleteIrq;
        }
    }    
  }else
  {}
  return Ok;
}
/**
** \brief   
**          获取DMA状态
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval en_dma_stat_t              
** 
**
** \retval  无
**/
en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(!IS_VALID_CH(enCh))
  {
    return DEFAULT;
  }
  if(enCh == DmaCh0)
  {
    return (en_dma_stat_t)M0P_DMAC->CONFB0_f.STAT ;
  }
  else{
    return (en_dma_stat_t)M0P_DMAC->CONFB1_f.STAT ;  	
  }	
}
/**
** \brief   
**          获取DMA状态
**
** \param  [in] enCh                   The specified dma channel.
**
** \retval en_dma_stat_t              
** 
**
** \retval  无
**/
void Dma_ClrStat(en_dma_channel_t enCh)
{
  ASSERT(IS_VALID_CH(enCh));
  
  if(enCh == DmaCh0)
  {
     M0P_DMAC->CONFB0_f.STAT = 0x0;
  }
  else{
     M0P_DMAC->CONFB1_f.STAT = 0x0;  	
  }
}

//@} // DmacGroup

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/
