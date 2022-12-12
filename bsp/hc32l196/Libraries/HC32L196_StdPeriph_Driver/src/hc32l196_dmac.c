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
#include "hc32l196_dmac.h"

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

/**************  Bits definition for DMA_CONFBx(x=0~1) register  *************/
#define DMA_TRANSFER_WIDTH_Pos              (26U)                                 /*!< DMAC_CONFBx: ERR_IE Position */
#define DMA_TRANSFER_WIDTH_Msk              (0x03U << DMA_TRANSFER_WIDTH_Pos)     /*!< DMAC_CONFBx: ERR_IE Mask 0x0C000000 */

/**************  Bits definition for DMA_CONFBx(x=0~1) register  *************/
#define DMA_ERR_IE_Pos                      (20U)                                 /*!< DMAC_CONFBx: ERR_IE Position */
#define DMA_ERR_IE_Msk                      (0x01U << DMA_ERR_IE_Pos)             /*!< DMAC_CONFBx: ERR_IE Mask 0x00000010 */

/**************  Bits definition for DMA_CONFBx(x=0~1) register  *************/
#define DMA_FIS_IE_Pos                      (19U)                                 /*!< DMAC_CONFBx: FIS_IE Position */
#define DMA_FIS_IE_Msk                      (0x01U << DMA_FIS_IE_Pos)             /*!< DMAC_CONFBx: FIS_IE Mask 0x00000010 */

/**************  Bits definition for DMA_CONFBx(x=0~1) register  *************/
#define DMA_STAT_Pos                        (16U)                                 /*!< DMAC_CONFBx: STAT Position */
#define DMA_STAT_Msk                        (0x07U << DMA_STAT_Pos)               /*!< DMAC_CONFBx: STAT Mask 0x00070000 */

/**************  Bits definition for DMA_CONFBx(x=0~1) register  *************/
#define DMA_TRANSFER_RELOAD_Pos             (0U)                                   /*!< DMAC_CONFBx: MSK Position */
#define DMA_TRANSFER_RELOAD_Msk             (0x01U << DMA_TRANSFER_RELOAD_Pos)     /*!< DMAC_CONFBx: MSK Mask 0x00000010 */

/**************  Bits definition for DMA_CONFAx(x=0~1) register  *************/
#define DMA_CH_ENABLE_Pos                   (31U)                                  /*!< DMAC_CONFAx: ENS Position */
#define DMA_CH_ENABLE_Msk                   (0x01U << DMA_CH_ENABLE_Pos)           /*!< DMAC_CONFAx: ENS Mask 0x80000000 */

/**************  Bits definition for DMA_CONFAx(x=0~1) register  *************/
#define DMA_CH_PAUSE_Pos                    (30U)                                  /*!< DMAC_CONFAx: PAS Position */
#define DMA_CH_PAUSE_Msk                    (0x01U << DMA_CH_PAUSE_Pos)            /*!< DMAC_CONFAx: PAS Mask 0x40000000 */

/**************  Bits definition for DMA_CONFAx(x=0~1) register  *************/
#define DMA_SOFTWARE_START_Pos              (29U)                                  /*!< DMAC_CONFAx: ENS Position */
#define DMA_SOFTWARE_START_Msk              (0x01U << DMA_SOFTWARE_START_Pos)      /*!< DMAC_CONFAx: ENS Mask 0x20000000 */

/**************  Bits definition for DMA_CONFAx(x=0~1) register  *************/
#define DMA_TRI_SEL_Pos                     (22U)                                  /*!< DMAC_CONFAx: TRISEL Position */
#define DMA_TRI_SEL_Msk                     (0x7FU << DMA_TRI_SEL_Pos)             /*!< DMAC_CONFAx: TRISEL Mask 0x1FC00000 */

/**************  Bits definition for DMA_CONFAx(x=0~1) register  *************/
#define DMA_BC_SEL_Pos                      (16U)                                  /*!< DMAC_CONFAx: TRISEL Position */
#define DMA_BC_SEL_Msk                      (0x0FU << DMA_BC_SEL_Pos)              /*!< DMAC_CONFAx: TRISEL Mask 0x000F0000 */

/**************  Bits definition for DMA_CONFAx(x=0~1) register  *************/
#define DMA_TC_SEL_Pos                      (0U)                                   /*!< DMAC_CONFAx: TRISEL Position */
#define DMA_TC_SEL_Msk                      (0xFFFFU << DMA_TC_SEL_Pos)            /*!< DMAC_CONFAx: TRISEL Mask 0x0000FFFF */

/**************  Bits definition for DMA_CONF register  *************/
#define DMA_ENABLE_Pos                      (31U)                                  /*!< DMAC_CONF: TRISEL Position */
#define DMA_ENABLE_Msk                      (0x01U << DMA_ENABLE_Pos)              /*!< DMAC_CONF: TRISEL Mask 0x80000000 */

/**************  Bits definition for DMA_CONF register  *************/
#define DMA_PRIORITY_Pos                    (28U)                                  /*!< DMAC_CONF: TRISEL Position */
#define DMA_PRIORITY_Msk                    (0x01U << DMA_PRIORITY_Pos)            /*!< DMAC_CONF: TRISEL Mask 0x10000000 */


/*! Dmac通道参数有效性检查. */
#define IS_VALID_CH(x)                      \
(   (DmaCh0 == (x))                      || \
  (DmaCh1 == (x)))

/*! DMA 传输数据宽度，参数有效性检查. */
#define IS_VALID_TRN_WIDTH(x)               \
(   (DmaMsk8Bit == (x))                     || \
  (DmaMsk16Bit == (x))                    || \
    (DmaMsk32Bit == (x)))

/*! DMA源地址控制模式，参数有效性检查. */
#define IS_VALID_SRC_ADDR_MODE(x)               \
(   (DmaMskSrcAddrFix == (x))                  || \
  (DmaMskSrcAddrInc == (x)))

/*! DMA目的地址控制模式，参数有效性检查. */
#define IS_VALID_DST_ADDR_MODE(x)               \
(   (DmaMskDstAddrFix == (x))                  || \
  (DmaMskDstAddrInc == (x)))

/*! DMA 优先级, 参数有效性检查. */
#define IS_VALID_PRIO_MODE(x)               \
(   (DmaMskPriorityFix == (x))                  || \
  (DmaMskPriorityLoop == (x)))

/*! DMA 传输模式，参数有效性检查. */
#define IS_VALID_TRANSFER_MODE(x)           \
(   (DmaMskOneTransfer == (x))                  || \
    (DmaMskContinuousTransfer == (x)))

/*! 块传输大小，参数有效性检查.  */
#define IS_VALID_BLKSIZE(x)                 ((!((x) & ~(DMA_BC_SEL_Msk >> DMA_BC_SEL_Pos)))&&((x)>0))

/*! 块传输次数，参数有效性检查.  */
#define IS_VALID_TRNCNT(x)                  (!((x) & ~(DMA_TC_SEL_Msk >> DMA_TC_SEL_Pos)))

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
** \brief 初始化DMAC通道
**
** \param  [in] enCh                   指定通道.
** \param  [in] pstcCfg             DMAC通道初始化配置结构体指针.
**
** \retval Ok                          初始化成功.
** \retval ErrorInvalidParameter       pstcCfg是空指针.
**
** \note   None
**
******************************************************************************/
en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t* pstcCfg)
{
    ASSERT(IS_VALID_CH(enCh));
    ASSERT(NULL != pstcCfg);
    ASSERT(IS_VALID_BLKSIZE(pstcCfg->u16BlockSize));
    ASSERT(IS_VALID_TRNCNT(pstcCfg->u16TransferCnt));
    ASSERT(IS_VALID_TRN_WIDTH(pstcCfg->enTransferWidth));
    ASSERT(IS_VALID_SRC_ADDR_MODE(pstcCfg->enSrcAddrMode));
    ASSERT(IS_VALID_DST_ADDR_MODE(pstcCfg->enDstAddrMode));
    ASSERT(IS_VALID_PRIO_MODE(pstcCfg->enPriority));
    ASSERT(IS_VALID_TRANSFER_MODE(pstcCfg->enTransferMode));
      
    /* 检查通道值有效性和pstcCfg是否空指针 */
    if (NULL == pstcCfg)
    {
      return ErrorInvalidParameter;
    }
  
  *(&M0P_DMAC->CONFB0+enCh) = 0;
    *(&M0P_DMAC->CONFB0+enCh) = (uint32_t)pstcCfg->enMode             |
                                  (uint32_t)pstcCfg->enTransferWidth    |
                                  (uint32_t)pstcCfg->enSrcAddrMode      |
                                  (uint32_t)pstcCfg->enDstAddrMode      |
                                  (uint32_t)pstcCfg->enSrcAddrReloadCtl |
                                  (uint32_t)pstcCfg->enDestAddrReloadCtl|
                                  (uint32_t)pstcCfg->enSrcBcTcReloadCtl |
                                  (uint32_t)pstcCfg->enTransferMode;

    /*首先把TRI_SEL[6:0]     BC[3:0] TC[15:0]这些位清零，然后再赋值*/
    *(&M0P_DMAC->CONFA0+enCh) &= ((uint32_t)~(DMA_TRI_SEL_Msk | DMA_BC_SEL_Msk | DMA_TC_SEL_Msk));
    *(&M0P_DMAC->CONFA0+enCh)    |= (uint32_t)(pstcCfg->u16TransferCnt - 1)    |
                                   ((uint32_t)(pstcCfg->u16BlockSize - 1)<<16)|
                                   (uint32_t)(pstcCfg->enRequestNum<<22);        

    M0P_DMAC->CONF |= (uint32_t)(pstcCfg->enPriority);                           
    
  *(&M0P_DMAC->SRCADR0+enCh) = (uint32_t)(pstcCfg->u32SrcAddress);
    *(&M0P_DMAC->DSTADR0+enCh) = (uint32_t)(pstcCfg->u32DstAddress);
    
  return Ok;
}
/**
*******************************************************************************
** \brief  DMA模块使能函数，使能所有通道的操作，每个通道按照各自设置工作.
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
  M0P_DMAC->CONF |= DMA_ENABLE_Msk;
}

/**
*******************************************************************************
** \brief  DMA模块功能禁止函数，所有通道禁止工作.
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
  M0P_DMAC->CONF &= (~DMA_ENABLE_Msk);
}
/**
*******************************************************************************
** \brief  触发指定DMA通道软件传输功能.
**
** \param  [输入] enCh                     指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SwStart(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFA0+enCh) |= DMA_SOFTWARE_START_Msk;
}

/**
*******************************************************************************
** \brief  停止指定DMA通道软件传输功能.
**
** \param  [输入] enCh                   指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SwStop(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFA0+enCh) &= (~DMA_SOFTWARE_START_Msk);
}
/**
*******************************************************************************
** \brief  使能指定dma通道的（传输完成）中断.
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_EnableChannelIrq(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFB0+enCh) |= DMA_FIS_IE_Msk; 
}

/**
*******************************************************************************
** \brief  禁用指定dma通道的（传输完成）中断.
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_DisableChannelIrq(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFB0+enCh) &= (~DMA_FIS_IE_Msk);
}
/**
*******************************************************************************
** \brief  使能指定dma通道的（传输错误）中断..
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_EnableChannelErrIrq(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFB0+enCh) |= DMA_ERR_IE_Msk;
}

/**
*******************************************************************************
** \brief  禁用指定dma通道的（传输错误）中断..
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_DisableChannelErrIrq(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFB0+enCh) &= (~DMA_ERR_IE_Msk);
}

/**
*******************************************************************************
** \brief  使能指定dma通道
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_EnableChannel(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFA0+enCh) |= DMA_CH_ENABLE_Msk;
}

/**
*******************************************************************************
** \brief  禁用指定dma通道
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_DisableChannel(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFA0+enCh) &= (~DMA_CH_ENABLE_Msk);
}

/**
*******************************************************************************
** \brief  设定指定通道的块(Block)尺寸
**
** \param  [输入] enCh                 指定通道
** \param  [输入] u16BlkSize           块(Block)尺寸.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize)
{
  volatile uint32_t *pReg = (&M0P_DMAC->CONFA0+enCh);
    
  *pReg = ((*pReg) & ((uint32_t)~DMA_BC_SEL_Msk)) | ((((uint32_t)u16BlkSize-1)&0x0f)<<DMA_BC_SEL_Pos);
}

/**
*******************************************************************************
** \brief  设定指定通道块(Block)传输次数
**
** \param  [in] enCh                   指定通道.
** \param  [in] u16TrnCnt              块(Block)传输次数.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt)
{
  volatile uint32_t *pReg = (&M0P_DMAC->CONFA0+enCh);
    
  *pReg = ((*pReg)&((uint32_t)~DMA_TC_SEL_Msk))|(((uint32_t)(u16TrnCnt-1)<<DMA_TC_SEL_Pos));
}

/**
*******************************************************************************
** \brief  允许指定通道可连续传输，即DMAC在传输完成时不清除CONFA:ENS位.
**
** \param  [in] enCh                   指定通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_EnableContinusTranfer(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFB0+enCh) |= DMA_TRANSFER_RELOAD_Msk;
}

/**
*******************************************************************************
** \brief  禁止指定通道连续传输，即DMAC在传输完成时清除.
**
** \param  [输入] enCh                 指定通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_DisableContinusTranfer(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFB0+enCh) &= (~DMA_TRANSFER_RELOAD_Msk);
}
/**
*******************************************************************************
** \brief  暂停所有dma通道.
**
** \param  None
**
** \retval None.
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
** \brief  恢复（之前暂停的）所有dma通道.
**
** \param  None
**
** \retval None
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
** \brief  暂停指定dma通道.
**
** \param  [输入] enCh                 指定通道.
**
** \retval void
**
** \note   None
**
******************************************************************************/
void Dma_PauseChannelTranfer(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFA0+enCh) |= DMA_CH_PAUSE_Msk;
}
/**
*******************************************************************************
** \brief  恢复（之前暂定的）指定dma通道.
**
** \param  [输入] enCh                 指定通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_RecoverChannelTranfer(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFA0+enCh) &= (~DMA_CH_PAUSE_Msk);
}
/**
*******************************************************************************
** \brief  设定指定通道传输数据宽度.
**
** \param  [输入] enCh                 指定dma通道.
** \param  [输入] enWidth              指定数据宽度.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth)
{
  volatile uint32_t *pReg = (&M0P_DMAC->CONFA0+enCh);
    
  *pReg = ((*pReg)&((uint32_t)~DMA_TRANSFER_WIDTH_Msk))|((uint32_t)enWidth);
}
/**
*******************************************************************************
** \brief  设定dma通道优先级.
**
** \param  [输入] enPrio               通道优先级设定参数.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SetChPriority(en_dma_priority_t enPrio)
{
  M0P_DMAC->CONF = ((M0P_DMAC->CONF)&((uint32_t)~DMA_PRIORITY_Msk))|((uint32_t)enPrio);
}
/**
*******************************************************************************
** \brief  获取指定DMA通道的状态.
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval en_dma_stat_t               DMA传输当前状态
**
** \note   None
**
******************************************************************************/
en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh)
{
  return (en_dma_stat_t)((*(&M0P_DMAC->CONFB0+enCh)&(DMA_STAT_Msk))>>DMA_STAT_Pos);
}
/**
*******************************************************************************
** \brief  清除指定DMA通道的状态值.
**
** \param  [输入] enCh                 指定dma通道.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_ClrStat(en_dma_channel_t enCh)
{
  *(&M0P_DMAC->CONFB0+enCh) &= (~DMA_STAT_Msk);
}


/**
*******************************************************************************
** \brief  设定指定通道源地址
**
** \param  [输入] enCh                  指定dma通道.
** \param  [输入] u32Address            传输源地址.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
  *(&M0P_DMAC->SRCADR0+enCh) = u32Address;
}

/**
*******************************************************************************
** \brief  设定指定通道目标地址.
**
** \param  [输入] enCh                  指定dma通道.
** \param  [输入] u32Address            传输目标地址.
**
** \retval None
**
** \note   None
**
******************************************************************************/
void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address)
{
  *(&M0P_DMAC->DSTADR0+enCh) = u32Address;
}

//@} // DmacGroup

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/
