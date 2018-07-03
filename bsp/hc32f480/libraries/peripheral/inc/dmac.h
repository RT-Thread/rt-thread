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
/** \file dma.h
 **
 ** A detailed description is available at
 ** @link DmacGroup Dmac description @endlink
 **
 **   - 2018-03-09  1.0  Hongjh First version for Device Driver Library of Dmac.
 **
 ******************************************************************************/
#ifndef __DMAC_H__
#define __DMAC_H__

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
 ** \defgroup DmacGroup Direct Memory Access Control(DMAC)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief DMA Channel
 **
 ******************************************************************************/
typedef enum en_dma_channel
{
    DmaCh0                          = 0U,    ///< DMA channel 0
    DmaCh1                          = 1U,    ///< DMA channel 1
    DmaCh2                          = 2U,    ///< DMA channel 2
    DmaCh3                          = 3U,    ///< DMA channel 3
    DmaCh4                          = 4U,    ///< DMA channel 4
    DmaCh5                          = 5U,    ///< DMA channel 5
    DmaCh6                          = 6U,    ///< DMA channel 6
    DmaCh7                          = 7U,    ///< DMA channel 7
    DmaChMax                        = 8U     ///< DMA channel max
} en_dma_channel_t;

/**
 *******************************************************************************
 ** \brief DMA transfer data width
 **
 ******************************************************************************/
typedef enum en_dma_transfer_width
{
    Dma8Bit                         = 0U,    ///< 8 bit transfer via DMA
    Dma16Bit                        = 1U,    ///< 16 bit transfer via DMA
    Dma32Bit                        = 2U     ///< 32 bit transfer via DMA
} en_dma_transfer_width_t;

/**
 *******************************************************************************
 ** \brief DMA flag
 **
 ******************************************************************************/
typedef enum en_dma_flag
{
    DmaTransferComplete             = 0U,    ///< DMA transfer complete
    DmaBlockComplete                = 1U,    ///< DMA block transfer complete
    DmaTransferErr                  = 2U,    ///< DMA transfer error
    DmaReqErr                       = 3U,    ///< DMA transfer request error
    DmaFlagMax                      = 4U
} en_dma_flag_t;

/**
 *******************************************************************************
 ** \brief DMA address mode
 **
 ******************************************************************************/
typedef enum en_address_mode
{
    AddressFix                      = 0U,    ///< Address fixed
    AddressIncrease                 = 1U,    ///< Address increased
    AddressDecrease                 = 2U,    ///< Address decreased
} en_address_mode_t;

/**
 *******************************************************************************
 ** \brief DMA link list pointer mode
 **
 ******************************************************************************/
typedef enum en_link_list_pointer_mode
{
    LlpWaitNextReq                  = 0U,    ///< DMA trigger transfer after wait next request
    LlpRunNow                       = 1U,    ///< DMA trigger transfer now
} en_link_list_pointer_mode_t;

/**
 *******************************************************************************
 ** \brief DMA interrupt selection
 **
 ******************************************************************************/
typedef enum stc_dma_irq_sel
{
    TrnErrIrq                       = 0U,    ///< Select DMA transfer error interrupt
    TrnReqErrIrq                    = 1U,    ///< Select DMA transfer req over error interrupt
    TrnCpltIrq                      = 2U,    ///< Select DMA transfer completion interrupt
    BlkTrnCpltIrq                   = 3U,    ///< Select DMA block completion interrupt
    DmaIrqSelMax                    = 4U
}en_dma_irq_sel_t;

/**
 *******************************************************************************
 ** \brief DMA llp descriptor
 **
 ******************************************************************************/
typedef struct stc_dma_llp_descriptor
{
    uint32_t SARx;                               ///< DMA source address register
    uint32_t DARx;                               ///< DMA destination address register
    union
    {
        uint32_t DTCTLx;
        stc_dmac_dtctl0_field_t DTCTLx_f;        ///< DMA data control register
    };
    union
    {
        uint32_t RPTx;
        stc_dmac_rpt0_field_t RPTx_f;            ///< DMA repeat control register
    };
    union
    {
        uint32_t SNSEQCTLx;
        stc_dmac_snseqctl0_field_t SNSEQCTLx_f;  ///< DMA source no-sequence control register
    };
    union
    {
        __IO uint32_t DNSEQCTLx;
        stc_dmac_dnseqctl0_field_t DNSEQCTLx_f;  ///< DMA destination no-sequence control register
    };
    union
    {
        uint32_t LLPx;
        stc_dmac_llp0_field_t LLPx_f;            ///< DMA link-list-pointer register
    };
    union
    {
        uint32_t CHxCTL;
        stc_dmac_ch0ctl_field_t CHxCTL_f;       ///< DMA channel control register
    };
}stc_dma_llp_descriptor_t;

/**
 *******************************************************************************
 ** \brief DMA no-sequence function configuration
 **
 ******************************************************************************/
typedef struct stc_nseq_ctl
{
    uint32_t u32Offset;                 ///< DMA no-sequence offset.
    uint16_t u16Cnt;                    ///< DMA no-sequence count.
    boolean_t bEnable;                  ///< Enable DMA no-sequence function or not.
} stc_nseq_ctl_t;

/**
 *******************************************************************************
 ** \brief DMA repeat function configuration
 **
 ******************************************************************************/
typedef struct stc_rpt_ctl
{
    uint16_t u16RptSize;                ///< DMA repeat size.
    boolean_t bEnable;                  ///< Enable DMA repeat function or not.
} stc_rpt_ctl_t;

/**
 *******************************************************************************
 ** \brief DMA link list pointer function configuration
 **
 ******************************************************************************/
typedef struct stc_link_list_pointer_ctl
{
    uint32_t u32Pointer;                    ///< DMA link list pointer.
    en_link_list_pointer_mode_t enMode;     ///< DMA link list pointer mode.
    boolean_t bEnable;                      ///< Enable DMA link list pointer function or not.
}stc_link_list_pointer_ctl_t;

/**
 *******************************************************************************
 ** \brief DMA address configuration
 **
 ******************************************************************************/
typedef struct stc_address_ctl
{
    uint32_t u32Address;                ///< address
    en_address_mode_t enMode;           ///< DMA address mode.
}stc_address_ctl_t;

/**
 *******************************************************************************
 ** \brief DMA configuration
 **
 ******************************************************************************/
typedef struct stc_dma_config
{
    uint16_t u16ReqNum;                         ///< DMA trigger request number

    uint16_t u16BlockSize;                      ///< Transfer block size = 1024, when 0 is set
    uint16_t u16TransferCnt;                    ///< Transfer counter
    en_dma_transfer_width_t enTransferWidth;    ///< DMA transfer width (see #en_dma_transfer_width_t for details)

    stc_address_ctl_t stcSrcAddrCtl;            ///< Source address control(see #stc_address_ctl_t for details)
    stc_address_ctl_t stcDstAddrCtl;            ///< Destination address control(see #stc_address_ctl_t for details)

    stc_rpt_ctl_t stcSrcRptCtl;                 ///< Source repeat control(see #stc_rpt_ctl_t for details)
    stc_rpt_ctl_t stcDstRptCtl;                 ///< Destination repeat control(see #stc_rpt_ctl_t for details)

    stc_nseq_ctl_t stcSrcNseqCtl;               ///< Source no-sequence control(see #stc_nseq_ctl_t for details)
    stc_nseq_ctl_t stcDstNseqCtl;               ///< Destination no-sequence control(see #stc_nseq_ctl_t for details)

    stc_link_list_pointer_ctl_t stcLlpCtl;      ///< link list pointer control(see #stc_link_list_pointer_ctl_t for details)
} stc_dma_config_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
en_result_t Dma_InitChannel(uint8_t u8Ch, stc_dma_config_t* pstcConfig);

void Dma_SwTrigger(void);

void Dma_EnableFuncClk(void);
void Dma_DisableFuncClk(void);

void Dma_Enable(void);
void Dma_Disable(void);

en_flag_status_t Dma_GetIrqFlag(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel);
en_result_t Dma_EnableIrq(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel);
en_result_t Dma_DisableIrq(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel);
en_result_t Dma_ClearIrqFlag(uint8_t u8Ch, en_dma_irq_sel_t enIrqSel);

en_result_t Dma_EnableChannel(uint8_t u8Ch);
en_result_t Dma_DisableChannel(uint8_t u8Ch);

en_result_t Dma_SetTriggerSel(uint8_t u8Ch, uint16_t u16TrgSel);

en_result_t Dma_SetSourceAddress(uint8_t u8Ch, uint32_t u32Address);
en_result_t Dma_SetDestinationAddress(uint8_t u8Ch, uint32_t u32Address);

en_result_t Dma_SetBlockSize(uint8_t u8Ch, uint16_t u16BlkSize);
en_result_t Dma_SetTransferCnt(uint8_t u8Ch, uint16_t u16TrnCnt);

en_result_t Dma_SetSourceRptSize(uint8_t u8Ch, uint16_t u16Size);
en_result_t Dma_SetDestinationRptSize(uint8_t u8Ch, uint16_t u16Size);

en_result_t Dma_SetSourceNseqOffset(uint8_t u8Ch, uint32_t u32Offset);
en_result_t Dma_SetSourceNseqCnt(uint8_t u8Ch, uint16_t u16Cnt);

en_result_t Dma_SetDestinationNseqOffset(uint8_t u8Ch, uint32_t u32Offset);
en_result_t Dma_SetDestinationNseqCnt(uint8_t u8Ch, uint16_t u16Cnt);

en_result_t Dma_SetSourceIncMode(uint8_t u8Ch, en_address_mode_t enMode);
en_result_t Dma_SetDestinationIncMode(uint8_t u8Ch, en_address_mode_t enMode);

en_result_t Dma_EnableSourceRpt(uint8_t u8Ch);
en_result_t Dma_DisableSourceRpt(uint8_t u8Ch);

en_result_t Dma_EnableDestinationRpt(uint8_t u8Ch);
en_result_t Dma_DisableDestinationRpt(uint8_t u8Ch);

en_result_t Dma_EnableSourceNseq(uint8_t u8Ch);
en_result_t Dma_DisableSourceNseq(uint8_t u8Ch);

en_result_t Dma_EnableDestinationNseq(uint8_t u8Ch);
en_result_t Dma_DisableDestinationNseq(uint8_t u8Ch);

en_result_t Dma_SetLinkPointer(uint8_t u8Ch, uint32_t u32Pointer);

en_result_t Dma_SetTransferWidth(uint8_t u8Ch, en_dma_transfer_width_t enWidth);

en_result_t Dma_EnableLinkedListPointer(uint8_t u8Ch);
en_result_t Dma_DisableLinkedListPointer(uint8_t u8Ch);
en_result_t Dma_SetLinkedListPointerMode(uint8_t u8Ch, en_link_list_pointer_mode_t enMode);

en_result_t Dma_EnableChannelIrq(uint8_t u8Ch);
en_result_t Dma_DisableChannelIrq(uint8_t u8Ch);

//@} // DmacGroup

#ifdef __cplusplus
}
#endif

#endif /* __DMAC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
