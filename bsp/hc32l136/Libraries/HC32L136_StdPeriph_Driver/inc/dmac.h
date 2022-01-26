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
    DmaChMax                        = 2U     ///< DMA channel max
  } en_dma_channel_t;
  /**
  *******************************************************************************
  ** \brief DMA priority
  **
  ******************************************************************************/
  typedef enum en_dma_priority
  {
    DmaPriorityFix                          = 0U,    ///< DMA channel priority fix (CH0>CH1)
    DmaPriorityLoop                         = 1U,    ///< DMA channel priority loop
  } en_dma_priority_t;
  
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
  ** \brief DMA transfer mode
  **
  ******************************************************************************/
  typedef enum en_dma_transfer_mode
  {
    DmaBlock                        = 0U,    ///< block transfer via DMA
    DmaBurst                        = 1U,    ///< burst transfer via DMA
  } en_dma_transfer_mode_t;
  
  /**
  *******************************************************************************
  ** \brief DMA flag
  **
  ******************************************************************************/
  typedef enum en_dma_stat
  {
    DEFAULT							            = 0U,    ///< Reserve
    DmaAddOverflow									= 1U,   ///< DMA address overflow
    DmaHALT                         = 2U,    ///< DMA HALT
    DmaAccSCRErr                    = 3U,    ///< DMA access source address error
    DmaAccDestErr                   = 4U,    ///< DMA access dest address error
    DmaTransferComplete             = 5U,    ///< DMA transfer complete
    DmaTransferPause                = 7U,    ///< DMA transfer pause      
  } en_dma_stat_t;
  
  /**
  *******************************************************************************
  ** \brief DMA address mode
  **
  ******************************************************************************/
  typedef enum en_address_mode
  {    
    AddressIncrease                 = 0U,    ///< Address increased
    AddressFix                      = 1U,    ///< Address fixed
  } en_address_mode_t;
  
  /**
  *******************************************************************************
  ** \brief DMA repeat tranfer
  **
  ******************************************************************************/
  typedef enum en_dma_msk
  {
    OneTranfer                      = 0U,    ///< One Tranfer
    ContinuousTranfer               = 1U,    ///< Continuous Tranfer 
  } en_dma_msk_t;
  /**
  *******************************************************************************
  ** \brief DMA trigger selection
  **
  ******************************************************************************/  
  typedef enum stc_dma_trig_sel
  {
    SWTrig                         = 0U,     ///< Select DMA software trig 
    SPI0RXTrig                     = 32U,    ///< Select DMA hardware trig 0
    SPI0TXTrig                     = 33U,    ///< Select DMA hardware trig 1
    SPI1RXTrig                     = 34U,    ///< Select DMA hardware trig 2
    SPI1TXTrig                     = 35U,    ///< Select DMA hardware trig 3
    ADCJQRTrig                     = 36U,    ///< Select DMA hardware trig 4
    ADCSQRTrig                     = 37U,    ///< Select DMA hardware trig 5
    LCDTxTrig                      = 38U,    ///< Select DMA hardware trig 6
    Uart0RxTrig                    = 40U,    ///< Select DMA hardware trig 8
    Uart0TxTrig                    = 41U,    ///< Select DMA hardware trig 9             
    Uart1RxTrig                    = 42U,    ///< Select DMA hardware trig 10
    Uart1TxTrig                    = 43U,    ///< Select DMA hardware trig 11
    LpUart0RxTrig                  = 44U,    ///< Select DMA hardware trig 12
    LpUart0TxTrig                  = 45U,    ///< Select DMA hardware trig 13
    LpUart1RxTrig                  = 46U,    ///< Select DMA hardware trig 14
    LpUart1TxTrig                  = 47U,    ///< Select DMA hardware trig 15
    TIM0ATrig                      = 50U,    ///< Select DMA hardware trig 18
    TIM0BTrig                      = 51U,    ///< Select DMA hardware trig 19
    TIM1ATrig                      = 52U,    ///< Select DMA hardware trig 20
    TIM1BTrig                      = 53U,    ///< Select DMA hardware trig 21
    TIM2ATrig                      = 54U,    ///< Select DMA hardware trig 22   
    TIM2BTrig                      = 55U,    ///< Select DMA hardware trig 23   
    TIM3ATrig                      = 56U,    ///< Select DMA hardware trig 24    
    TIM3BTrig                      = 57U,    ///< Select DMA hardware trig 25   
    TIM4ATrig                      = 58U,    ///< Select DMA hardware trig 26    
    TIM4BTrig                      = 59U,    ///< Select DMA hardware trig 27   
    TIM5ATrig                      = 60U,    ///< Select DMA hardware trig 28    
    TIM5BTrig                      = 61U,    ///< Select DMA hardware trig 29   
    TIM6ATrig                      = 62U,    ///< Select DMA hardware trig 30    
    TIM6BTrig                      = 63U,    ///< Select DMA hardware trig 31   
  }en_dma_trig_sel_t;  
  /**
  *******************************************************************************
  ** \brief DMA interrupt selection
  **
  ******************************************************************************/
typedef struct stc_dma_irq
  {
    boolean_t TrnErrIrq;                        ///< Select DMA transfer error interrupt
    boolean_t TrnCpltIrq;                      ///< Select DMA transfer completion interrupt
  }stc_dma_irq_sel_t;
  
 
  
  /**
  *******************************************************************************
  ** \brief DMA configuration
  **
  ******************************************************************************/
  typedef struct stc_dma_config
  {
    en_dma_transfer_mode_t enMode;
    
    uint16_t u16BlockSize;                      ///< Transfer Block counter
    uint16_t u16TransferCnt;                    ///< Transfer counter
    en_dma_transfer_width_t enTransferWidth;    ///< DMA transfer width (see #en_dma_transfer_width_t for details)
    
    en_address_mode_t enSrcAddrMode;            ///< Source address mode(see #en_source_address_mode_t for details)
    en_address_mode_t enDstAddrMode;            ///< Destination address mode(see #en_dest_address_mode_t for details)  
    
    boolean_t bSrcAddrReloadCtl;  ///< Source address reload(TRUE: reload;FALSE: reload forbidden)
    boolean_t bDestAddrReloadCtl;  ///< Dest address reload(TRUE: reload;FALSE: reload forbidden)
    boolean_t bSrcBcTcReloadCtl;  ///< Bc/Tc address reload(TRUE: reload;FALSE: reload forbidden)
    uint32_t u32SrcAddress;           ///< Source address>
    uint32_t u32DstAddress;           ///< Dest address>
    boolean_t bMsk;                   ///0: clear the bit (CONFA:ENS) after tarnfer;1: remain the bit (CONFA:ENS) after tarnfer
    
    en_dma_trig_sel_t enRequestNum;     ///< DMA trigger request number
  } stc_dma_config_t;
  /**
 ******************************************************************************
 ** \brief  DMA中断回调函数
 *****************************************************************************/
typedef struct stc_dma_irq_calbakfn_pt
{
    /*! Dma传输完成中断回调函数指针*/
    func_ptr_t  pfnDma0TranferCompleteIrq;
     /*! Dma传输完成中断回调函数指针*/
    func_ptr_t  pfnDma1TranferCompleteIrq;
    /*! Dma传输错误中断回调函数指针*/
    func_ptr_t  pfnDma0TranferErrIrq;
    /*! Dma传输错误中断回调函数指针*/
    func_ptr_t  pfnDma1TranferErrIrq;
}stc_dma_irq_calbakfn_pt_t;
  /*******************************************************************************
  * Global pre-processor symbols/macros ('#define')
  ******************************************************************************/
  
  /*******************************************************************************
  * Global variable definitions ('extern')
  ******************************************************************************/
  
  /*******************************************************************************
  * Global function prototypes (definition in C source)
  ******************************************************************************/
  en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_config_t* pstcConfig);
  
  void Dma_SwTrigger(en_dma_channel_t enCh);
  
  void Dma_Enable(void);
  void Dma_Disable(void);
  
  void Dma_Start(en_dma_channel_t enCh);
  void Dma_Stop(en_dma_channel_t enCh);
  
  en_result_t Dma_EnableChannel(en_dma_channel_t enCh);
  en_result_t Dma_DisableChannel(en_dma_channel_t enCh);
  
  en_result_t Dma_SetTriggerSel(en_dma_channel_t enCh, en_dma_trig_sel_t enTrgSel);
  
  en_result_t Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address);
  en_result_t Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address);
  
  en_result_t Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize);
  en_result_t Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt);
  
  
  en_result_t Dma_SetSourceIncMode(en_dma_channel_t enCh, en_address_mode_t enMode);
  en_result_t Dma_SetDestinationIncMode(en_dma_channel_t enCh, en_address_mode_t enMode);
  
  en_result_t Dma_EnableSourceRload(en_dma_channel_t enCh);
  en_result_t Dma_DisableSourceRload(en_dma_channel_t enCh);
  
  en_result_t Dma_EnableDestinationRload(en_dma_channel_t enCh);
  en_result_t Dma_DisableDestinationRload(en_dma_channel_t enCh);
  
  en_result_t Dma_EnableContinusTranfer(en_dma_channel_t enCh);
  en_result_t Dma_DisableContinusTranfer(en_dma_channel_t enCh);
  
  en_result_t Dma_EnableBcTcReload(en_dma_channel_t enCh);
  en_result_t Dma_DisableBcTcReload(en_dma_channel_t enCh);
  
  void Dma_HaltTranfer(void);
  void Dma_RecoverTranfer(void);
  en_result_t Dma_PauseChannelTranfer(en_dma_channel_t enCh);
  en_result_t Dma_RecoverChannelTranfer(en_dma_channel_t enCh);

  en_result_t Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth);
  
  en_result_t Dma_SetChPriority(en_dma_priority_t enPrio);
  
  en_result_t Dma_EnableChannelIrq(en_dma_channel_t enCh);
  en_result_t Dma_DisableChannelIrq(en_dma_channel_t enCh);
  
  en_result_t Dma_EnableChannelErrIrq(en_dma_channel_t enCh);
  en_result_t Dma_DisableChannelErrIrq(en_dma_channel_t enCh);
  
  en_result_t Dma_ConfigIrq(en_dma_channel_t enCh,stc_dma_irq_sel_t* stcDmaIrqCfg,stc_dma_irq_calbakfn_pt_t* pstcDmaIrqCalbaks);

  
  en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh);
  
  void Dma_ClrStat(en_dma_channel_t enCh);
  //@} // DmacGroup
  
#ifdef __cplusplus
}
#endif

#endif /* __DMAC_H__ */

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/
