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
  ** \brief DMA 通道
  **
  ******************************************************************************/
  typedef enum en_dma_channel
  {
    DmaCh0                          = 0x00,    ///< DMA 通道0
    DmaCh1                          = 0x04,    ///< DMA 通道1 
  } en_dma_channel_t;
  /**
  *******************************************************************************
  ** \brief DMA 优先级
  **
  ******************************************************************************/
  typedef enum en_dma_priority
  {
    DmaMskPriorityFix                          = 0x00000000,    ///< DMA 各通道优先级固定 (CH0>CH1)
    DmaMskPriorityLoop                         = 0x10000000,    ///< DMA 各通道优先级采用轮询方式
  } en_dma_priority_t;
  
  /**
  *******************************************************************************
  ** \brief DMA 传输数据宽度
  **
  ******************************************************************************/
  typedef enum en_dma_transfer_width
  {
    DmaMsk8Bit                         = 0x00000000,    ///< 8 bit  字节传输
    DmaMsk16Bit                        = 0x04000000,    ///< 16 bit 半字传输
    DmaMsk32Bit                        = 0x08000000     ///< 32 bit 字传输
  } en_dma_transfer_width_t;
  
  /**
  *******************************************************************************
  ** \brief DMA 传输模式：块(Block)传输或者突发(Burst)传输
  **
  ******************************************************************************/
  typedef enum en_dma_transfer_mode
  {
    DmaMskBlock                        = 0x00000000,    ///< 块(Block)传输
    DmaMskBurst                        = 0x10000000,    ///< 突发(Burst)传输
  } en_dma_transfer_mode_t;
  
  /**
  *******************************************************************************
  ** \brief DMA传输当前状态
  **
  ******************************************************************************/
  typedef enum en_dma_stat
  {
    DmaDefault                      = 0U,    ///< 初始值
    DmaAddOverflow                  = 1U,    ///< 传输错误引起中止（地址溢出）
    DmaHALT                         = 2U,    ///< 传输停止请求引起中止（外设停止请求引起的停止或者EB/DE位引起的禁止传输）
    DmaAccSCRErr                    = 3U,    ///< 传输错误引起中止（传输源地址访问错误）
    DmaAccDestErr                   = 4U,    ///< 传输错误引起中止（传输目的地址访问错误）
    DmaTransferComplete             = 5U,    ///< 成功传输完成
    DmaTransferPause                = 7U,    ///< 传输暂停      
  } en_dma_stat_t;
  
  /**
  *******************************************************************************
  ** \brief DMA源地址控制模式：自增或固定
  **
  ******************************************************************************/
  typedef enum en_src_address_mode
  {    
    DmaMskSrcAddrInc                 = 0x00000000,    ///< 地址自增
    DmaMskSrcAddrFix                 = 0x02000000,    ///< 地址固定
  } en_src_address_mode_t;
  
  /**
  *******************************************************************************
  ** \brief DMA目的地址控制模式：自增或固定
  **
  ******************************************************************************/
  typedef enum en_dst_address_mode
  {    
    DmaMskDstAddrInc                 = 0x00000000,    ///< 地址自增
    DmaMskDstAddrFix                 = 0x01000000,    ///< 地址固定
  } en_dst_address_mode_t;
  
  /**
  *******************************************************************************
  ** \brief DMA CONFA:BC[3:0]和CONFA:TC[15:0]的重载功能
  **
  ******************************************************************************/
  typedef enum en_bc_tc_reload_mode
  {    
    DmaMskBcTcReloadDisable                = 0x00000000,    ///< 禁止重载
    DmaMskBcTcReloadEnable                 = 0x00800000,    ///< 使能重载
  } en_bc_tc_reload_mode_t;
  
  /**
  *******************************************************************************
  ** \brief DMA源地址重载功能：使能或禁止
  **
  ******************************************************************************/
  typedef enum en_src_address_reload_mode
  {    
    DmaMskSrcAddrReloadDisable                = 0x00000000,    ///< 禁止DMA源地址重载
    DmaMskSrcAddrReloadEnable                 = 0x00400000,    ///< 使能DMA源地址重载
  } en_src_address_reload_mode_t;
  
  /**
  *******************************************************************************
  ** \brief DMA目的地址重载功能：使能或禁止
  **
  ******************************************************************************/
  typedef enum en_dst_address_reload_mode
  {    
    DmaMskDstAddrReloadDisable                = 0x00000000,    ///< 禁止DMA目的地址重载
    DmaMskDstAddrReloadEnable                 = 0x00200000,    ///< 使能DMA目的地址重载
  } en_dst_address_reload_mode_t;

  
  
  /**
  *******************************************************************************
  ** \brief DMA 连续传输设置
  **
  ******************************************************************************/
  typedef enum en_dma_msk
  {
    DmaMskOneTransfer                      = 0x00000000,    ///< 传输一次，DMAC传输完成时清除CONFA:ENS位
    DmaMskContinuousTransfer               = 0x00000001,    ///< 连续传输，DMAC传输完成时不清除CONFA:ENS位
  } en_dma_msk_t;
  /**
  *******************************************************************************
  ** \brief DMA 触发源选择
  **
  ******************************************************************************/  
  typedef enum stc_dma_trig_sel
  {
    DmaSWTrig                         = 0U,     ///< Select DMA software trig
    DmaSPI0RXTrig                     = 64U,    ///< Select DMA hardware trig 0
    DmaSPI0TXTrig                     = 65U,    ///< Select DMA hardware trig 1
    DmaSPI1RXTrig                     = 66U,    ///< Select DMA hardware trig 2
    DmaSPI1TXTrig                     = 67U,    ///< Select DMA hardware trig 3
    DmaADCJQRTrig                     = 68U,    ///< Select DMA hardware trig 4
    DmaADCSQRTrig                     = 69U,    ///< Select DMA hardware trig 5
    DmaLCDTxTrig                      = 70U,    ///< Select DMA hardware trig 6
    DmaUart0RxTrig                    = 72U,    ///< Select DMA hardware trig 8
    DmaUart0TxTrig                    = 73U,    ///< Select DMA hardware trig 9
    DmaUart1RxTrig                    = 74U,    ///< Select DMA hardware trig 10
    DmaUart1TxTrig                    = 75U,    ///< Select DMA hardware trig 11
    DmaLpUart0RxTrig                  = 76U,    ///< Select DMA hardware trig 12
    DmaLpUart0TxTrig                  = 77U,    ///< Select DMA hardware trig 13
    DmaLpUart1RxTrig                  = 78U,    ///< Select DMA hardware trig 14
    DmaLpUart1TxTrig                  = 79U,    ///< Select DMA hardware trig 15
    DmaDAC0Trig                       = 80U,    ///< Select DMA hardware trig 16
    DmaDAC1Trig                       = 81U,    ///< Select DMA hardware trig 17
    DmaTIM0ATrig                      = 82U,    ///< Select DMA hardware trig 18
    DmaTIM0BTrig                      = 83U,    ///< Select DMA hardware trig 19
    DmaTIM1ATrig                      = 84U,    ///< Select DMA hardware trig 20
    DmaTIM1BTrig                      = 85U,    ///< Select DMA hardware trig 21
    DmaTIM2ATrig                      = 86U,    ///< Select DMA hardware trig 22
    DmaTIM2BTrig                      = 87U,    ///< Select DMA hardware trig 23
    DmaTIM3ATrig                      = 88U,    ///< Select DMA hardware trig 24
    DmaTIM3BTrig                      = 89U,    ///< Select DMA hardware trig 25
    DmaTIM4ATrig                      = 90U,    ///< Select DMA hardware trig 26
    DmaTIM4BTrig                      = 91U,    ///< Select DMA hardware trig 27
    DmaTIM5ATrig                      = 92U,    ///< Select DMA hardware trig 28
    DmaTIM5BTrig                      = 93U,    ///< Select DMA hardware trig 29
    DmaTIM6ATrig                      = 94U,    ///< Select DMA hardware trig 30
    DmaTIM6BTrig                      = 95U,    ///< Select DMA hardware trig 31
    DmaUart2RxTrig                    = 96U,    ///< Select DMA hardware trig 32
    DmaUart2TxTrig                    = 97U,    ///< Select DMA hardware trig 33
    DmaUart3RxTrig                    = 98U,    ///< Select DMA hardware trig 34
    DmaUart3TxTrig                    = 99U,    ///< Select DMA hardware trig 35
  }en_dma_trig_sel_t;  
  
  /**
  *******************************************************************************
  ** \brief DMA通道初始化配置结构体
  **
  ******************************************************************************/
  typedef struct stc_dma_cfg
  {
    en_dma_transfer_mode_t enMode;
    
    uint16_t u16BlockSize;                           ///< 块传输个数
    uint16_t u16TransferCnt;                         ///< 传输块次数
    en_dma_transfer_width_t enTransferWidth;         ///< 传输数据字节宽度 具体参考枚举定义:en_dma_transfer_width_t
    
    en_src_address_mode_t enSrcAddrMode;             ///< DMA源地址控制模式：自增或固定
    en_dst_address_mode_t enDstAddrMode;             ///< DMA目的地址控制模式：自增或固定  
    
    en_src_address_reload_mode_t enSrcAddrReloadCtl; ///< 源地址重载  具体参考枚举定义:en_src_address_reload_mode_t
    en_dst_address_reload_mode_t enDestAddrReloadCtl;///< 目的地址重载 具体参考枚举定义:en_dst_address_reload_mode_t
    en_bc_tc_reload_mode_t enSrcBcTcReloadCtl;       ///< Bc/Tc值重载功能 具体参考枚举定义:en_bc_tc_reload_mode_t
        
    uint32_t u32SrcAddress;                          ///< 源地址>
    uint32_t u32DstAddress;                          ///< 目的地址>
        
    en_dma_msk_t enTransferMode;                     ///DMA 连续传输设置 具体参考枚举定义:en_dma_msk_t
    en_dma_priority_t enPriority;                    ///DMA 优先级设定 具体参考枚举定义:en_dma_priority_t
    en_dma_trig_sel_t enRequestNum;                  ///<DMA 触发源选择 具体参考枚举定义:en_dma_trig_sel_t
  } stc_dma_cfg_t;

  /*******************************************************************************
  * Global pre-processor symbols/macros ('#define')
  ******************************************************************************/
  
  /*******************************************************************************
  * Global variable definitions ('extern')
  ******************************************************************************/
  
  /*******************************************************************************
  * Global function prototypes (definition in C source)
  ******************************************************************************/
  ///< 初始化DMAC通道
  en_result_t Dma_InitChannel(en_dma_channel_t enCh, stc_dma_cfg_t* pstcCfg);  
    
  ///< DMA模块使能函数，使能所有通道的操作，每个通道按照各自设置工作
  void Dma_Enable(void);   
  ///< DMA模块功能禁止函数，所有通道禁止工作.
  void Dma_Disable(void);  
  
  ///< 触发指定DMA通道软件传输功能.
  void Dma_SwStart(en_dma_channel_t enCh);  
  ///< 停止指定DMA通道软件传输功能.
  void Dma_SwStop(en_dma_channel_t enCh);

  ///< 使能指定dma通道的（传输完成）中断.
  void Dma_EnableChannelIrq(en_dma_channel_t enCh);
  ///< 禁用指定dma通道的（传输完成）中断.
  void Dma_DisableChannelIrq(en_dma_channel_t enCh);
  ///< 使能指定dma通道的（传输错误）中断..
  void Dma_EnableChannelErrIrq(en_dma_channel_t enCh);
  ///< 禁用指定dma通道的（传输错误）中断..
  void Dma_DisableChannelErrIrq(en_dma_channel_t enCh);
  
  ///< 使能指定dma通道
  void Dma_EnableChannel(en_dma_channel_t enCh);
  ///< 禁用指定dma通道
  void Dma_DisableChannel(en_dma_channel_t enCh);
  
  ///< 设定指定通道的块(Block)尺寸
  void Dma_SetBlockSize(en_dma_channel_t enCh, uint16_t u16BlkSize);
  ///< 设定指定通道块(Block)传输次数
  void Dma_SetTransferCnt(en_dma_channel_t enCh, uint16_t u16TrnCnt);
  
  ///< 允许指定通道可连续传输，即DMAC在传输完成时不清除CONFA:ENS位.
  void Dma_EnableContinusTranfer(en_dma_channel_t enCh);
  ///< 禁止指定通道连续传输，即DMAC在传输完成时清除.
  void Dma_DisableContinusTranfer(en_dma_channel_t enCh);

  ///< 暂停所有dma通道.
  void Dma_HaltTranfer(void);
  ///< 恢复（之前暂停的）所有dma通道.
  void Dma_RecoverTranfer(void);
  ///< 暂停指定dma通道.
  void Dma_PauseChannelTranfer(en_dma_channel_t enCh);
  ///< 恢复（之前暂定的）指定dma通道.
  void Dma_RecoverChannelTranfer(en_dma_channel_t enCh);

  ///< 设定指定通道传输数据宽度.
  void Dma_SetTransferWidth(en_dma_channel_t enCh, en_dma_transfer_width_t enWidth);  
  ///< 设定dma通道优先级.
  void Dma_SetChPriority(en_dma_priority_t enPrio);
  
  ///< 获取指定DMA通道的状态.
  en_dma_stat_t Dma_GetStat(en_dma_channel_t enCh);  
  ///< 清除指定DMA通道的状态值.
  void Dma_ClrStat(en_dma_channel_t enCh);
  
  ///<设定指定通道源地址
  void Dma_SetSourceAddress(en_dma_channel_t enCh, uint32_t u32Address);
  ///<设定指定通道目标地址.
  void Dma_SetDestinationAddress(en_dma_channel_t enCh, uint32_t u32Address);
  //@} // DmacGroup
  
#ifdef __cplusplus
}
#endif

#endif /* __DMAC_H__ */

/*******************************************************************************
* EOF (not truncated)
******************************************************************************/
