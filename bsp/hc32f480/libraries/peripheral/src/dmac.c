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

/****************  Bits definition for DMA_LLPx(x=0~7) register  **************/
#define DMA_LLP_LLP_Pos                     (2U)                                /*!< DMA_LLPx: LLP Position */
#define DMA_LLP_LLP_Msk                     (0x3FFFFFFFU << DMA_LLP_LLP_Pos)    /*!< DMA_LLPx: LLP Mask 0xFFFFFFC */
#define DMA_LLP_LLP                         DMA_LLP_LLP_Msk

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

#define WRITE_DMA_CH_REG(reg_base, ch, val)         (_DMA_CH_REG(reg_base, ch) = (val))
#define READ_DMA_CH_REG(reg_base, ch)               (_DMA_CH_REG(reg_base, ch))

#define SET_DMA_CH_REG_BIT(reg_base, ch, pos)       (_DMA_CH_REG(reg_base, ch) |= (1U << (pos)))
#define CLR_DMA_CH_REG_BIT(reg_base, ch, pos)       (_DMA_CH_REG(reg_base, ch) &= (~(1U << (pos))))

#define MODIFY_DMA_CH_REG(reg_base, ch, msk, val)   do { \
    WRITE_DMA_CH_REG(reg_base, ch, ((READ_DMA_CH_REG(reg_base, ch) & (~(msk))) | (val << (msk##_Pos)))); \
} while(0);

/***********************  SET DMA_TRGSELx(x=0~7) register  ********************/
#define __SET_DMA_TRGSEL(_CH_,_TRGSEL_)     do { \
    DMA_TRGSEL(_CH_) = (_TRGSEL_) & DMA_TRGSEL_TRGSEL_Msk; \
} while(0)

/*****************************  SET FCG0 register  ****************************/
#define SET_FCG0_PTDIS()                    do { \
    M4_MSTP->FCG0PC = 0xA5A50001u; \
    M4_MSTP->FCG0_f.AOS = 1u;      \
} while(0)
#define __CLEAR_FCG0_PTDIS()                do { \
    M4_MSTP->FCG0PC = 0xA5A50001u; \
    M4_MSTP->FCG0_f.AOS = 0u;      \
} while(0)

#define SET_FCG0_DMA()                      do { \
    M4_MSTP->FCG0PC = 0xA5A50001u; \
    M4_MSTP->FCG0_f.DMA = 1u;      \
} while(0)

#define CLEAR_FCG0_DMA()                    do { \
    M4_MSTP->FCG0PC = 0xA5A50001u; \
    M4_MSTP->FCG0_f.DMA = 0u;      \
} while(0)

/**********************  SET DMA_TRGSELx(x=0~7) register  *********************/
#define SET_DMA_TRGSEL(CH, TRGSEL)          __CLEAR_FCG0_PTDIS(); \
                                            __SET_DMA_TRGSEL(CH, TRGSEL)

#define SET_DMA_CHCTL_PROT(CH, PROT)        SET_DMA_CHCTL_PROT(CH, PROT)

/**************************  SET INTSFTTRG register  **************************/
#define SOFTWARE_TRIGGER_DMA()                 (INTC_INTSFTTRG = 1U)

/*! Parameter valid check for Dmac Channel. */
#define IS_VALID_CH(x)                      \
(   (DmaCh0 == (x))                      || \
    (DmaCh1 == (x))                      || \
    (DmaCh2 == (x))                      || \
    (DmaCh3 == (x))                      || \
    (DmaCh4 == (x))                      || \
    (DmaCh5 == (x))                      || \
    (DmaCh6 == (x))                      || \
    (DmaCh7 == (x)))

/*! Parameter valid check for Dmac irq selection. */
#define IS_VALID_IRQ_SEL(x)                 \
(   (TrnErrIrq == (x))                   || \
    (TrnReqErrIrq == (x))                || \
    (TrnCpltIrq == (x))                  || \
    (BlkTrnCpltIrq == (x)))

/*! Parameter valid check for Dmac transfer data width. */
#define IS_VALID_TRN_WIDTH(x)               \
(   (Dma8Bit == (x))                     || \
    (Dma16Bit == (x))                    || \
    (Dma32Bit == (x)))

/*! Parameter valid check for Dmac address mode. */
#define IS_VALID_ADDR_MODE(x)               \
(   (AddressFix == (x))                  || \
    (AddressIncrease == (x))             || \
    (AddressDecrease == (x)))

/*! Parameter valid check for Dmac link-list-pointer mode. */
#define IS_VALID_LLP_MODE(x)                \
(   (LlpWaitNextReq == (x))              || \
    (LlpRunNow == (x)))

/*! Parameter valid check for Dmac trigger selection. */
#define IS_VALID_TRG_SEL(x)                 (!((x) & ~(DMA_TRGSEL_TRGSEL_Msk >> DMA_TRGSEL_TRGSEL_Pos)))

/*! Parameter valid check for Dmac transfer block size. */
#define IS_VALID_BLKSIZE(x)                 (!((x) & ~(DMA_DTCTL_BLKSIZE_Msk >> DMA_DTCTL_BLKSIZE_Pos)))

/*! Parameter valid check for Dmac transfer count. */
#define IS_VALID_TRNCNT(x)                  (!((x) & ~(DMA_DTCTL_CNT_Msk >> DMA_DTCTL_CNT_Pos)))

/*! Parameter valid check for Dmac source repeat size. */
#define IS_VALID_SRPT_SIZE(x)               (!((x) & ~(DMA_RPT_SRPT_Msk >> DMA_RPT_SRPT_Pos)))

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

/*! Parameter valid check for Dmac link-list-pointer. */
#define IS_VALID_LLP(x)                     (!((x) & ~DMA_LLP_LLP_Msk))

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
 ** \brief Initializes a DMA channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] pstcConfig             The structure pointer of DMA module configuration.
 **
 ** \retval Ok                          Initializes successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid or the pstcConfig is NULL.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_InitChannel(uint8_t u8Ch, stc_dma_config_t* pstcConfig)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(NULL != pstcConfig);
    DDL_ASSERT(IS_VALID_BLKSIZE(pstcConfig->u16BlockSize));
    DDL_ASSERT(IS_VALID_TRNCNT(pstcConfig->u16TransferCnt));
    DDL_ASSERT(IS_VALID_TRN_WIDTH(pstcConfig->enTransferWidth));
    DDL_ASSERT(IS_VALID_ADDR_MODE(pstcConfig->stcSrcAddrCtl.enMode));
    DDL_ASSERT(IS_VALID_ADDR_MODE(pstcConfig->stcDstAddrCtl.enMode));
    DDL_ASSERT(IS_VALID_SRPT_SIZE(pstcConfig->stcSrcRptCtl.u16RptSize));
    DDL_ASSERT(IS_VALID_DRPT_SIZE(pstcConfig->stcDstRptCtl.u16RptSize));
    DDL_ASSERT(IS_VALID_SNSCNT(pstcConfig->stcSrcNseqCtl.u16Cnt));
    DDL_ASSERT(IS_VALID_SNSOFFSET(pstcConfig->stcSrcNseqCtl.u32Offset));
    DDL_ASSERT(IS_VALID_DNSCNT(pstcConfig->stcDstNseqCtl.u16Cnt));
    DDL_ASSERT(IS_VALID_DNSOFFSET(pstcConfig->stcDstNseqCtl.u32Offset));
    DDL_ASSERT(IS_VALID_LLP(pstcConfig->stcLlpCtl.u32Pointer));
    DDL_ASSERT(IS_VALID_LLP_MODE(pstcConfig->stcLlpCtl.enMode));

    /* Check for channel and NULL pointer */
    if ((!IS_VALID_CH(u8Ch)) ||
        (NULL == pstcConfig))
    {
        return ErrorInvalidParameter;
    }

    Dma_EnableFuncClk();   /* Enable DMAC clock */
    M4_DMAC->EN_f.EN = 1;  /* Enable DMAC function */
    CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_IE_Pos); /* Disable DMAC interrupt */

    /*******************  SET DMA_TRGSELx(x=0~7) register  ******************/
    SET_DMA_TRGSEL(u8Ch, pstcConfig->u16ReqNum);

    /*******************  SET DMA_DTCTLx(x=0~7) register  ******************/
    /* Block size */
    MODIFY_DMA_CH_REG(&M4_DMAC->DTCTL0, u8Ch, DMA_DTCTL_BLKSIZE, pstcConfig->u16BlockSize);
    /* Transfer count */
    MODIFY_DMA_CH_REG(&M4_DMAC->DTCTL0, u8Ch, DMA_DTCTL_CNT, pstcConfig->u16TransferCnt);

    /*******************  SET DMA_CHxCTL(x=0~7) register  ******************/
    /* Transfer width */
    MODIFY_DMA_CH_REG(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_HSIZE, pstcConfig->enTransferWidth);

    /****************************** source address contrl *******************/
    /* source address mode */
    MODIFY_DMA_CH_REG(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_SINC, pstcConfig->stcSrcAddrCtl.enMode);
    /* Source address */
    WRITE_DMA_CH_REG(&M4_DMAC->SAR0, u8Ch, pstcConfig->stcSrcAddrCtl.u32Address);

    /*************************** destination address contrl *******************/
    /* destination address mode */
    MODIFY_DMA_CH_REG(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_DINC, pstcConfig->stcDstAddrCtl.enMode);
    /* Destination address */
    WRITE_DMA_CH_REG(&M4_DMAC->DAR0, u8Ch, pstcConfig->stcDstAddrCtl.u32Address);

    /*********************  Source address repeat control  ********************/
    /* SET DMA_RPTx(x=0~7) register */
    MODIFY_DMA_CH_REG(&M4_DMAC->RPT0, u8Ch, DMA_RPT_SRPT, pstcConfig->stcSrcRptCtl.u16RptSize);
    (pstcConfig->stcSrcRptCtl.bEnable == TRUE)? SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_SRPTEN_Pos): CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_SRPTEN_Pos);

    /*******************  Destination address repeat control  *****************/
    /* SET DMA_RPTx(x=0~7) register */
    MODIFY_DMA_CH_REG(&M4_DMAC->RPT0, u8Ch, DMA_RPT_DRPT, pstcConfig->stcDstRptCtl.u16RptSize);
    (pstcConfig->stcDstRptCtl.bEnable == TRUE)? SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_DRPTEN_Pos):CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_DRPTEN_Pos);

    /***********************  Source no sequence control  *********************/
    /* SET DMA_SNSEQCTLx(x=0~7) register: SNSEQCTL Offset */
    MODIFY_DMA_CH_REG(&M4_DMAC->SNSEQCTL0, u8Ch, DMA_SNSEQCTL_SOFFSET, pstcConfig->stcSrcNseqCtl.u32Offset);
    /* SET DMA_SNSEQCTLx(x=0~7) register: SNSEQCTL Cnt */
    MODIFY_DMA_CH_REG(&M4_DMAC->SNSEQCTL0, u8Ch, DMA_SNSEQCTL_SNSCNT, pstcConfig->stcSrcNseqCtl.u16Cnt);
    /* Source no-sequence enable */
    (pstcConfig->stcSrcNseqCtl.bEnable == TRUE)? SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_SNSEQEN_Pos): CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_SNSEQEN_Pos);

    /*********************  Destination no sequence control  ******************/
    /* SET DMA_DNSEQCTLx(x=0~7) register: DNSEQCTL Offset */
    MODIFY_DMA_CH_REG(&M4_DMAC->DNSEQCTL0, u8Ch, DMA_DNSEQCTL_DOFFSET, pstcConfig->stcDstNseqCtl.u32Offset);
    /* SET DMA_DNSEQCTLx(x=0~7) register: DNSEQCTL Cnt */
    MODIFY_DMA_CH_REG(&M4_DMAC->DNSEQCTL0, u8Ch, DMA_DNSEQCTL_DNSCNT, pstcConfig->stcDstNseqCtl.u16Cnt);
    /* Destination no-sequence enable */
    (pstcConfig->stcDstNseqCtl.bEnable == TRUE)? SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_DNSEQEN_Pos): CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_DNSEQEN_Pos);

    /***************************** link list pointer contrl *******************/
    /* SET DMA_LLPx(x=0~7) register */
    WRITE_DMA_CH_REG(&M4_DMAC->LLP0, u8Ch, pstcConfig->stcLlpCtl.u32Pointer);
    /* llp mode */
    (pstcConfig->stcLlpCtl.enMode == LlpRunNow)? SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPRUN_Pos): CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPRUN_Pos);
    /* llp enable */
    (pstcConfig->stcLlpCtl.bEnable == TRUE)? SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPEN_Pos): CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief Trigger dma transfer by software.
 **
 ** \param  None
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Dma_SwTrigger(void)
{
    SOFTWARE_TRIGGER_DMA();
}

/**
 *******************************************************************************
 ** \brief Enable dma clock.
 **
 ** \param  None
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Dma_EnableFuncClk(void)
{
    CLEAR_FCG0_DMA();
}

/**
 *******************************************************************************
 ** \brief Disable dma clock.
 **
 ** \param  None
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void Dma_DisableFuncClk(void)
{
    SET_FCG0_DMA();
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
    M4_DMAC->EN_f.EN = 1;
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
    M4_DMAC->EN_f.EN = 0;
}

/**
 *******************************************************************************
 ** \brief  Enable the specified dma interrupt.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enIrqSel               The specified dma flag.
 ** \arg    TrnErrIrq                   The DMA transfer error interrupt.
 ** \arg    TrnReqErrIrq                DMA transfer req over error interrupt.
 ** \arg    TrnCpltIrq                  DMA transfer completion interrupt.
 ** \arg    BlkTrnCpltIrq               DMA block completion interrupt.
 **
 ** \retval Ok                          Interrupt enabled normally.
 ** \retval ErrorInvalidParameter       u8Ch or enIrqSel is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableIrq(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_IRQ_SEL(enIrqSel));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    switch(enIrqSel)
    {
        case TrnErrIrq:
            M4_DMAC->INTMASK0 &= ~(1ul << (u8Ch + DMA_INTMASK0_MSKTRNERR_Pos));
            break;
        case TrnReqErrIrq:
            M4_DMAC->INTMASK0 &= ~(1ul << (u8Ch + DMA_INTMASK0_MSKREQERR_Pos));
            break;
        case TrnCpltIrq:
            M4_DMAC->INTMASK1 &= ~(1ul << (u8Ch + DMA_INTMASK1_MSKTC_Pos));
            break;
        case BlkTrnCpltIrq:
            M4_DMAC->INTMASK1 &= ~(1ul << (u8Ch + DMA_INTMASK1_MSKBTC_Pos));
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Enable the specified dma interrupt.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enIrqSel               The specified dma flag.
 ** \arg    TrnErrIrq                   The DMA transfer error interrupt.
 ** \arg    TrnReqErrIrq                DMA transfer req over error interrupt.
 ** \arg    TrnCpltIrq                  DMA transfer completion interrupt.
 ** \arg    BlkTrnCpltIrq               DMA block completion interrupt.
 **
 ** \retval Ok                          Interrupt disabled normally.
 ** \retval ErrorInvalidParameter       u8Ch or enIrqSel is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableIrq(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_IRQ_SEL(enIrqSel));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    switch(enIrqSel)
    {
        case TrnErrIrq:
            M4_DMAC->INTMASK0 |= (1ul << (u8Ch + DMA_INTMASK0_MSKTRNERR_Pos));
            break;
        case TrnReqErrIrq:
            M4_DMAC->INTMASK0 |= (1ul << (u8Ch + DMA_INTMASK0_MSKREQERR_Pos));
            break;
        case TrnCpltIrq:
            M4_DMAC->INTMASK1 |= (1ul << (u8Ch + DMA_INTMASK1_MSKTC_Pos));
            break;
        case BlkTrnCpltIrq:
            M4_DMAC->INTMASK1 |= (1ul << (u8Ch + DMA_INTMASK1_MSKBTC_Pos));
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Get the specified dma flag status.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enIrqSel               The specified dma flag.
 ** \arg    TrnErrIrq                   The DMA transfer error interrupt.
 ** \arg    TrnReqErrIrq                DMA transfer req over error interrupt.
 ** \arg    TrnCpltIrq                  DMA transfer completion interrupt.
 ** \arg    BlkTrnCpltIrq               DMA block completion interrupt.
 **
 ** \retval the specified dma flag status
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t Dma_GetIrqFlag(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel)
{
    uint32_t u32IntStat = 0;

    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_IRQ_SEL(enIrqSel));

    if(!IS_VALID_CH(u8Ch))
    {
        return Reset;
    }

    switch(enIrqSel)
    {
        case TrnErrIrq:
            u32IntStat = (M4_DMAC->INTSTAT0 & (1ul << (u8Ch + DMA_INTSTAT0_TRNERR_Pos)));
            break;
        case TrnReqErrIrq:
            u32IntStat = (M4_DMAC->INTSTAT0 & (1ul << (u8Ch + DMA_INTSTAT0_REQERR_Pos)));
            break;
        case TrnCpltIrq:
            u32IntStat = (M4_DMAC->INTSTAT1 & (1ul << (u8Ch + DMA_INTSTAT1_TC_Pos)));
            break;
        case BlkTrnCpltIrq:
            u32IntStat = (M4_DMAC->INTSTAT1 & (1ul << (u8Ch + DMA_INTSTAT1_BTC_Pos)));
            break;
        default:
            break;
     }

    return (u32IntStat ? Set:Reset);
}

/**
 *******************************************************************************
 ** \brief  Clear the specified dma interrupt.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enIrqSel               The specified dma flag.
 ** \arg    TrnErrIrq                   The DMA transfer error interrupt.
 ** \arg    TrnReqErrIrq                DMA transfer req over error interrupt.
 ** \arg    TrnCpltIrq                  DMA transfer completion interrupt.
 ** \arg    BlkTrnCpltIrq               DMA block completion interrupt.
 **
 ** \retval Ok                          Clear flag successfully.
 ** \retval ErrorInvalidParameter       u8Ch or enIrqSel is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_ClearIrqFlag(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_IRQ_SEL(enIrqSel));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    switch(enIrqSel)
    {
        case TrnErrIrq:
            M4_DMAC->INTCLR0 |= (1ul << (u8Ch + DMA_INTCLR0_CLRTRNERR_Pos));
            break;
        case TrnReqErrIrq:
            M4_DMAC->INTCLR0 |= (1ul << (u8Ch + DMA_INTCLR0_CLRREQERR_Pos));
            break;
        case TrnCpltIrq:
            M4_DMAC->INTCLR1 |= (1ul << (u8Ch + DMA_INTCLR1_CLRTC_Pos));
            break;
        case BlkTrnCpltIrq:
            M4_DMAC->INTCLR1 |= (1ul << (u8Ch + DMA_INTCLR1_CLRBTC_Pos));
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Enable the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Enable channel successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableChannel(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    M4_DMAC->CHEN |= (1ul << (u8Ch + DMA_CHEN_CHEN_Pos));

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Disable the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Disable channel successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableChannel(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    M4_DMAC->CHEN &= (~(1ul << (u8Ch + DMA_CHEN_CHEN_Pos)));

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the specified dma trigger.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u16TrgSel              The trigger selection number.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u16TrgSel is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetTriggerSel(uint8_t u8Ch, uint16_t u16TrgSel)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_TRG_SEL(u16TrgSel));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_TRG_SEL(u16TrgSel)))
    {
        return ErrorInvalidParameter;
    }

    SET_DMA_TRGSEL(u8Ch, u16TrgSel);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Setthe source address of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u32Address             The source address.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetSourceAddress(uint8_t u8Ch, uint32_t u32Address)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    WRITE_DMA_CH_REG(&M4_DMAC->SAR0, u8Ch, u32Address);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the destination address of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u32Address             The destination address.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetDestinationAddress(uint8_t u8Ch, uint32_t u32Address)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    WRITE_DMA_CH_REG(&M4_DMAC->DAR0, u8Ch, u32Address);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the block size of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u32Address             The block size.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u16BlkSize is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetBlockSize(uint8_t u8Ch, uint16_t u16BlkSize)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_BLKSIZE(u16BlkSize));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_BLKSIZE(u16BlkSize)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->DTCTL0, u8Ch, DMA_DTCTL_BLKSIZE, u16BlkSize);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the transfer count of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u32Address             The transfer count.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u16TrnCnt is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetTransferCnt(uint8_t u8Ch, uint16_t u16TrnCnt)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_TRNCNT(u16TrnCnt));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_TRNCNT(u16TrnCnt)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->DTCTL0, u8Ch, DMA_DTCTL_CNT, u16TrnCnt);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the source repeat size of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u16Size                The source repeat size.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u16Size is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetSourceRptSize(uint8_t u8Ch, uint16_t u16Size)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_SRPT_SIZE(u16Size));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_SRPT_SIZE(u16Size)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->RPT0, u8Ch, DMA_RPT_SRPT, u16Size);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the destination repeat size of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u16Size                The destination repeat size.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u16Size is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetDestinationRptSize(uint8_t u8Ch, uint16_t u16Size)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_DRPT_SIZE(u16Size));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_DRPT_SIZE(u16Size)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->RPT0, u8Ch, DMA_RPT_DRPT, u16Size);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the source no-sequence offset of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u32Offset              The source no-sequence offset.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u32Offset is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetSourceNseqOffset(uint8_t u8Ch, uint32_t u32Offset)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_SNSOFFSET(u32Offset));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_SNSOFFSET(u32Offset)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->SNSEQCTL0, u8Ch, DMA_SNSEQCTL_SOFFSET, u32Offset);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the source no-sequence count of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u16Cnt                 The source no-sequence count.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u16Cnt is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetSourceNseqCnt(uint8_t u8Ch, uint16_t u16Cnt)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_SNSCNT(u16Cnt));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_SNSCNT(u16Cnt)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->SNSEQCTL0, u8Ch, DMA_SNSEQCTL_SNSCNT, u16Cnt);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the destination no-sequence offset of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u32Offset              The destination no-sequence offset.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u32Offset is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetDestinationNseqOffset(uint8_t u8Ch, uint32_t u32Offset)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_DNSOFFSET(u32Offset));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_DNSOFFSET(u32Offset)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->DNSEQCTL0, u8Ch, DMA_DNSEQCTL_DOFFSET, u32Offset);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the destination no-sequence count of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u16Cnt                 The destination no-sequence count.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u16Cnt is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetDestinationNseqCnt(uint8_t u8Ch, uint16_t u16Cnt)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_DNSCNT(u16Cnt));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_DNSCNT(u16Cnt)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->DNSEQCTL0, u8Ch, DMA_DNSEQCTL_DNSCNT, u16Cnt);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the source address mode of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enMode                 The specified dma address mode.
 ** \arg    AddressFix                  Address fixed.
 ** \arg    AddressIncrease             Address increased.
 ** \arg    AddressDecrease             Address decreased.
 **
 ** \retval Ok                          Set successfully
 ** \retval ErrorInvalidParameter       u8Ch or enMode is invalid
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetSourceIncMode(uint8_t u8Ch, en_address_mode_t enMode)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_ADDR_MODE(enMode));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_ADDR_MODE(enMode)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_SINC, enMode);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set the destination address mode of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enMode                 The specified dma address mode.
 ** \arg    AddressFix                  Address fixed.
 ** \arg    AddressIncrease             Address increased.
 ** \arg    AddressDecrease             Address decreased.
 **
 ** \retval Ok                          Set successfully
 ** \retval ErrorInvalidParameter       u8Ch or enMode is invalid
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetDestinationIncMode(uint8_t u8Ch, en_address_mode_t enMode)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_ADDR_MODE(enMode));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_ADDR_MODE(enMode)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_DINC, enMode);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Enable source repeat function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Enable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableSourceRpt(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_SRPTEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Disable source repeat function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Disable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableSourceRpt(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_SRPTEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Enable destination repeat function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Enable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableDestinationRpt(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_DRPTEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Disable destination repeat function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Disable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableDestinationRpt(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_DRPTEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Enable source no-sequence function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Enable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableSourceNseq(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_SNSEQEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Disable source no-sequence function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Disable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableSourceNseq(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_SNSEQEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Enable destination no-sequence function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Enable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableDestinationNseq(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_DNSEQEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Disable destination no-sequence function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Disable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableDestinationNseq(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL , u8Ch, DMA_CHCTL_DNSEQEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set linked list pointer of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] u32Pointer             The decriptor pointer.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or u32Pointer is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetLinkedListPointer(uint8_t u8Ch, uint32_t u32Pointer)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_LLP(u32Pointer));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_LLP(u32Pointer)))
    {
        return ErrorInvalidParameter;
    }

    WRITE_DMA_CH_REG(&M4_DMAC->LLP0, u8Ch, u32Pointer);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set transfer data width of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enWidth                The specified transfer data width.
 ** \arg    Dma8Bit                     The 8 bit transfer via DMA.
 ** \arg    Dma16Bit                    The 16 bit transfer via DMA.
 ** \arg    Dma32Bit                    The 32 bit transfer via DMA.
 **
 ** \retval Ok                          Set successfully
 ** \retval ErrorInvalidParameter       u8Ch or enWidth is invalid
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetTransferWidth(uint8_t u8Ch, en_dma_transfer_width_t enWidth)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_TRN_WIDTH(enWidth));

    if((!IS_VALID_CH(u8Ch)) || (!IS_VALID_TRN_WIDTH(enWidth)))
    {
        return ErrorInvalidParameter;
    }

    MODIFY_DMA_CH_REG(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_HSIZE, enWidth);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Enable linked list pointer function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Enable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableLinkedListPointer(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Disable linked list pointer function of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Disable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableLinkedListPointer(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPEN_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Set link list pointer mode of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 ** \param  [in] enMode                The specified link list pointer mode.
 ** \arg    LlpRunWaitNextReq           DMA trigger transfer after wait next request.
 ** \arg    LlpRunNow                   DMA trigger transfer now.
 **
 ** \retval Ok                          Set successfully.
 ** \retval ErrorInvalidParameter       u8Ch or enMode is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_SetLinkListPointerMode(uint8_t u8Ch, en_link_list_pointer_mode_t enMode)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_VALID_CH(u8Ch));
    DDL_ASSERT(IS_VALID_LLP_MODE(enMode));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    switch(enMode)
    {
        case LlpWaitNextReq:
            CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPRUN_Pos);
            break;
        case LlpRunNow:
            SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_LLPRUN_Pos);
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Enable interrupt of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Enable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_EnableChannelIrq(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    SET_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_IE_Pos);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Disable interrupt of the specified dma channel.
 **
 ** \param  [in] u8Ch                   The specified dma channel.
 **
 ** \retval Ok                          Disable successfully.
 ** \retval ErrorInvalidParameter       u8Ch is invalid.
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t Dma_DisableChannelIrq(uint8_t u8Ch)
{
    DDL_ASSERT(IS_VALID_CH(u8Ch));

    if(!IS_VALID_CH(u8Ch))
    {
        return ErrorInvalidParameter;
    }

    CLR_DMA_CH_REG_BIT(&M4_DMAC->CH0CTL, u8Ch, DMA_CHCTL_IE_Pos);

    return Ok;
}

//@} // DmacGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
