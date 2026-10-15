/**
  ******************************************************************************
  * @file    tae32g58xx_ll_spi.h
  * @author  MCD Application Team
  * @brief   Header file for SPI LL module
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32G58XX_LL_SPI_H_
#define _TAE32G58XX_LL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"
#ifdef LL_DMA_MODULE_ENABLED
#include "tae32g58xx_ll_dma.h"
#endif


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup SPI_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Macros SPI LL Exported Macros
  * @brief    SPI LL Exported Macros
  * @{
  */

/**
  * @brief  Slave CS Software Input Status Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return Slave CS Software Input Status
  */
#define __LL_SPI_CS_SlvSwInputSta_Get(__SPI__)          READ_BIT_SHIFT((__SPI__)->ENABLE, SPI0_ENABLE_CSI_Msk, SPI0_ENABLE_CSI_Pos)

/**
  * @brief  Slave CS Input Mode Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  mode Slave CS Input Mode
  * @return None
  */
#define __LL_SPI_CS_SlvInputMode_Set(__SPI__, mode)     \
        MODIFY_REG((__SPI__)->ENABLE, SPI0_ENABLE_CSIS_Msk, (((mode) & 0x1UL) << SPI0_ENABLE_CSIS_Pos))

/**
  * @brief  CS Software Output Inactive
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_CS_SwOut_Inactive(__SPI__)             SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_CSO_Msk)

/**
  * @brief  CS Software Output Active
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_CS_SwOut_Active(__SPI__)               CLEAR_BIT((__SPI__)->ENABLE, SPI0_ENABLE_CSO_Msk)

/**
  * @brief  CS Software Output Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_CS_SwOut_En(__SPI__)                   SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_CSOS_Msk)

/**
  * @brief  CS Software Output Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_CS_SwOut_Dis(__SPI__)                  CLEAR_BIT((__SPI__)->ENABLE, SPI0_ENABLE_CSOS_Msk)

/**
  * @brief  Judge is CS Software Output Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 CS Software Output Disable
  * @retval 1 CS Software Output Enable
  */
#define __LL_SPI_CS_IsSwOutEn(__SPI__)                  READ_BIT_SHIFT((__SPI__)->ENABLE, SPI0_ENABLE_CSOS_Msk, SPI0_ENABLE_CSOS_Pos)

/**
  * @brief  TX DMA Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxDMA_En(__SPI__)                      SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_DTE_Msk)

/**
  * @brief  TX DMA Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxDMA_Dis(__SPI__)                     CLEAR_BIT((__SPI__)->ENABLE, SPI0_ENABLE_DTE_Msk)

/**
  * @brief  RX DMA Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxDMA_En(__SPI__)                      SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_DRE_Msk)

/**
  * @brief  RX DMA Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxDMA_Dis(__SPI__)                     CLEAR_BIT((__SPI__)->ENABLE, SPI0_ENABLE_DRE_Msk)

/**
  * @brief  Loopback Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Loopback_En(__SPI__)                   SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_LOOP_Msk)

/**
  * @brief  Loopback Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Loopback_Dis(__SPI__)                  CLEAR_BIT((__SPI__)->ENABLE, SPI0_ENABLE_LOOP_Msk)

/**
  * @brief  Judge is Loopback Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_IsLoopbackEn(__SPI__)                  READ_BIT_SHIFT((__SPI__)->ENABLE, SPI0_ENABLE_LOOP_Msk, SPI0_ENABLE_LOOP_Pos)

/**
  * @brief  MOSI/MISO Pin Swap Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_MOSI_MISO_Swap_En(__SPI__)             SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_SWAP_Msk)

/**
  * @brief  MOSI/MISO Pin Swap Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_MOSI_MISO_Swap_Dis(__SPI__)            CLEAR_BIT((__SPI__)->ENABLE, SPI0_ENABLE_SWAP_Msk)

/**
  * @brief  CS Polarity Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  pol CS Polarity
  * @return None
  */
#define __LL_SPI_CSPol_Set(__SPI__, pol)                \
        MODIFY_REG((__SPI__)->ENABLE, SPI0_ENABLE_CSPOL_Msk, (((pol) & 0x1UL) << SPI0_ENABLE_CSPOL_Pos))

/**
  * @brief  CS Mode Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  mode CS Mode
  * @return None
  */
#define __LL_SPI_CSMode_Set(__SPI__, mode)              \
        MODIFY_REG((__SPI__)->ENABLE, SPI0_ENABLE_CSSEL_Msk, (((mode) & 0x1UL) << SPI0_ENABLE_CSSEL_Pos))

/**
  * @brief  Wire Mode Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  mode Wire Mode @ref SPI_WireModeETypeDef
  * @return None
  */
#define __LL_SPI_WireMode_Set(__SPI__, mode)            \
        MODIFY_REG((__SPI__)->ENABLE, SPI0_ENABLE_TWE_Msk, (((mode) & 0x1UL) << SPI0_ENABLE_TWE_Pos))

/**
  * @brief  Wire Mode Set
  * @param  __SPI__ Specifies SPI peripheral
  * @return Wire Mode @ref SPI_WireModeETypeDef 
  */
#define __LL_SPI_WireMode_Get(__SPI__)            \
        READ_BIT_SHIFT((__SPI__)->ENABLE, SPI0_ENABLE_TWE_Msk, SPI0_ENABLE_TWE_Pos)

/**
  * @brief  TXFIFO Reset
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxFIFO_Reset(__SPI__)                  SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_TFR_Msk)

/**
  * @brief  RXFIFO Reset
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxFIFO_Reset(__SPI__)                  SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_RFR_Msk)

/**
  * @brief  SPI Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_En(__SPI__)                            SET_BIT((__SPI__)->ENABLE, SPI0_ENABLE_SPIEN_Msk)

/**
  * @brief  SPI Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Dis(__SPI__)                           CLEAR_BIT((__SPI__)->ENABLE, SPI0_ENABLE_SPIEN_Msk)


/**
  * @brief  Master RX Delay Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  pclk_cnt RX Delay pclk count
  * @return None
  */
#define __LL_SPI_Mst_RxDelay_Set(__SPI__, pclk_cnt)     \
        MODIFY_REG((__SPI__)->CTRL, SPI0_CTRL_RXDLY_Msk, (((pclk_cnt) & 0x7UL) << SPI0_CTRL_RXDLY_Pos))

/**
  * @brief  Serial Data Length Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  len Serial Data Length
  * @return None
  */
#define __LL_SPI_SerialDataLen_Set(__SPI__, len)        \
        MODIFY_REG((__SPI__)->CTRL, SPI0_CTRL_LEN_Msk, (((len) & 0xfUL) << SPI0_CTRL_LEN_Pos))

/**
  * @brief  Serial Data Length Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return Serial Data Length
  */
#define __LL_SPI_SerialDataLen_Get(__SPI__)             READ_BIT_SHIFT((__SPI__)->CTRL, SPI0_CTRL_LEN_Msk, SPI0_CTRL_LEN_Pos)

/**
  * @brief  SPI Slave Tx underrun last frame
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Slv_TxUnderrun_LastFrame(__SPI__)      SET_BIT((__SPI__)->CTRL, SPI0_CTRL_UDRCFG_Msk)

/**
  * @brief  SPI Slave Tx underrun user data
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Slv_TxUnderrun_UserDat(__SPI__)        CLEAR_BIT((__SPI__)->CTRL, SPI0_CTRL_UDRCFG_Msk)

/**
  * @brief  Bit Order Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  order Bit Order
  * @return None
  */
#define __LL_SPI_BitOrder_Set(__SPI__, order)           \
        MODIFY_REG((__SPI__)->CTRL, SPI0_CTRL_LSB_Msk, (((order) & 0x1UL) << SPI0_CTRL_LSB_Pos))

/**
  * @brief  TX Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Tx_En(__SPI__)                         SET_BIT((__SPI__)->CTRL, SPI0_CTRL_TXEN_Msk)

/**
  * @brief  TX Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Tx_Dis(__SPI__)                        CLEAR_BIT((__SPI__)->CTRL, SPI0_CTRL_TXEN_Msk)

/**
  * @brief  RX Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Rx_En(__SPI__)                         SET_BIT((__SPI__)->CTRL, SPI0_CTRL_RXEN_Msk)

/**
  * @brief  RX Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Rx_Dis(__SPI__)                        CLEAR_BIT((__SPI__)->CTRL, SPI0_CTRL_RXEN_Msk)

/**
  * @brief  Slave High-Z Output Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Slv_HighZOut_En(__SPI__)               SET_BIT((__SPI__)->CTRL, SPI0_CTRL_SHZOE_Msk)

/**
  * @brief  Slave High-Z Output Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Slv_HighZOut_Dis(__SPI__)              CLEAR_BIT((__SPI__)->CTRL, SPI0_CTRL_SHZOE_Msk)

/**
  * @brief  SCLK Polarity Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  pol SCLK Polarity
  * @return None
  */
#define __LL_SPI_SclkPolarity_Set(__SPI__, pol)         \
        MODIFY_REG((__SPI__)->CTRL, SPI0_CTRL_CPOL_Msk, (((pol) & 0x1UL) << SPI0_CTRL_CPOL_Pos))

/**
  * @brief  SCLK Phase Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  phase SCLK Phase
  * @return None
  */
#define __LL_SPI_SclkPhase_Set(__SPI__, phase)          \
        MODIFY_REG((__SPI__)->CTRL, SPI0_CTRL_CPHA_Msk, (((phase) & 0x1UL) << SPI0_CTRL_CPHA_Pos))

/**
  * @brief  SPI Role Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  role SPI Role
  * @return None
  */
#define __LL_SPI_Role_Set(__SPI__, role)                \
        MODIFY_REG((__SPI__)->CTRL, SPI0_CTRL_MSTEN_Msk, (((role) & 0x1UL) << SPI0_CTRL_MSTEN_Pos))


/**
  * @brief  SPI Baud Rate Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  br SPI Baud Rate Reg Value
  * @return None
  */
#define __LL_SPI_BaudRate_Set(__SPI__, br)              \
        MODIFY_REG((__SPI__)->BAUD, SPI0_BAUD_BAUD_Msk, (((br) & 0x7ffUL) << SPI0_BAUD_BAUD_Pos))


/**
  * @brief  RxFIFO Full Threshold Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  thres RxFIFO Full Threshold
  * @return None
  */
#define __LL_SPI_RxFIFOFullThres_Set(__SPI__, thres)    \
        MODIFY_REG((__SPI__)->FIFOCTRL, SPI0_FIFOCTRL_RXFTLR_Msk, (((thres-1) & 0xfUL) << SPI0_FIFOCTRL_RXFTLR_Pos))

/**
  * @brief  RxFIFO Full Threshold Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return RxFIFO Full Threshold
  */
#define __LL_SPI_RxFIFOFullThres_Get(__SPI__)           \
        (READ_BIT_SHIFT((__SPI__)->FIFOCTRL, SPI0_FIFOCTRL_RXFTLR_Msk, SPI0_FIFOCTRL_RXFTLR_Pos) + 1)

/**
  * @brief  TxFIFO Empty Threshold Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  thres TxFIFO Empty Threshold
  * @return None
  */
#define __LL_SPI_TxFIFOEmptyThres_Set(__SPI__, thres)   \
        MODIFY_REG((__SPI__)->FIFOCTRL, SPI0_FIFOCTRL_TXFTLR_Msk, (((thres) & 0xfUL) << SPI0_FIFOCTRL_TXFTLR_Pos))

/**
  * @brief  TxFIFO Empty Threshold Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return TxFIFO Empty Threshold
  */
#define __LL_SPI_TxFIFOEmptyThres_Get(__SPI__)          \
        READ_BIT_SHIFT((__SPI__)->FIFOCTRL, SPI0_FIFOCTRL_TXFTLR_Msk, SPI0_FIFOCTRL_TXFTLR_Pos)


/**
  * @brief  Master TxRx Count Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  cnt TxRx Count
  * @return None
  */
#define __LL_SPI_Mst_TxRxCnt_Set(__SPI__, cnt)          \
        MODIFY_REG((__SPI__)->CNT, SPI0_CNT_DCNT_Msk, (((cnt) & 0xffffUL) << SPI0_CNT_DCNT_Pos))


/**
  * @brief  Master TxRx Remain Count Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return Master TxRx Remain Count
  */
#define __LL_SPI_Mst_TxRxRemainCnt_Get(__SPI__)         READ_REG((__SPI__)->RCNT)


/**
  * @brief  Master TxRx Stop
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Mst_TxRx_Stop(__SPI__)                 SET_BIT((__SPI__)->START, SPI0_START_STOP_Msk)

/**
  * @brief  Master TxRx Start
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Mst_TxRx_Start(__SPI__)                SET_BIT((__SPI__)->START, SPI0_START_START_Msk)


/**
  * @brief  Master SS Idleness Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  idle Master SS Idleness
  * @return None
  */
#define __LL_SPI_Mst_SSIdleness_Set(__SPI__, idle)          \
        MODIFY_REG((__SPI__)->TIMING, SPI0_TIMING_MCSI_Msk, (((idle - 1) & 0x1fUL) << SPI0_TIMING_MCSI_Pos))

/**
  * @brief  Master Inter-Data Idleness Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  idle Master SS Idleness
  * @return None
  */
#define __LL_SPI_Mst_InterDatIdleness_Set(__SPI__, idle)    \
        MODIFY_REG((__SPI__)->TIMING, SPI0_TIMING_MIDI_Msk, (((idle - 1) & 0x1fUL) << SPI0_TIMING_MIDI_Pos))


/**
  * @brief  RX Complete Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxCplt_INT_En(__SPI__)                 SET_BIT((__SPI__)->INTEN, SPI0_INTEN_RXCIE_Msk)

/**
  * @brief  RX Complete Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxCplt_INT_Dis(__SPI__)                CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_RXCIE_Msk)

/**
  * @brief  TX Complete Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxCplt_INT_En(__SPI__)                 SET_BIT((__SPI__)->INTEN, SPI0_INTEN_TXCIE_Msk)

/**
  * @brief  TX Complete Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxCplt_INT_Dis(__SPI__)                CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_TXCIE_Msk)

/**
  * @brief  RX Done Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxDone_INT_En(__SPI__)                 SET_BIT((__SPI__)->INTEN, SPI0_INTEN_RXDEIE_Msk)

/**
  * @brief  RX Done Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxDone_INT_Dis(__SPI__)                CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_RXDEIE_Msk)

/**
  * @brief  TX Done Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxDone_INT_En(__SPI__)                 SET_BIT((__SPI__)->INTEN, SPI0_INTEN_TXDEIE_Msk)

/**
  * @brief  TX Done Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxDone_INT_Dis(__SPI__)                CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_TXDEIE_Msk)

/**
  * @brief  Transmission Operation Fault Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TransOptFault_INT_En(__SPI__)          SET_BIT((__SPI__)->INTEN, SPI0_INTEN_OPFIE_Msk)

/**
  * @brief  Transmission Operation Fault Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TransOptFault_INT_Dis(__SPI__)         CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_OPFIE_Msk)

/**
  * @brief  Judge is Transmission Operation Fault Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_IsTransOptFaultIntEn(__SPI__)          READ_BIT_SHIFT((__SPI__)->INTEN, SPI0_INTEN_OPFIE_Msk, SPI0_INTEN_OPFIE_Pos)

/**
  * @brief  Transmission Mode Fault Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TransModeFault_INT_En(__SPI__)         SET_BIT((__SPI__)->INTEN, SPI0_INTEN_MDFIE_Msk)

/**
  * @brief  Transmission Mode Fault Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TransModeFault_INT_Dis(__SPI__)        CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_MDFIE_Msk)

/**
  * @brief  Judge is Transmission Mode Fault Interrupt Enable or not
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_IsTransModeFaultIntEn(__SPI__)         READ_BIT_SHIFT((__SPI__)->INTEN, SPI0_INTEN_MDFIE_Msk, SPI0_INTEN_MDFIE_Pos)

/**
  * @brief  Slave TxFIFO Underflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Slv_TxFIFOUnderflow_INT_En(__SPI__)    SET_BIT((__SPI__)->INTEN, SPI0_INTEN_TXUFIE_Msk)

/**
  * @brief  Slave TxFIFO Underflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Slv_TxFIFOUnderflow_INT_Dis(__SPI__)   CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_TXUFIE_Msk)

/**
  * @brief  TxFIFO Overflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxFIFOOverflow_INT_En(__SPI__)         SET_BIT((__SPI__)->INTEN, SPI0_INTEN_TXOFIE_Msk)

/**
  * @brief  TxFIFO Overflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxFIFOOverflow_INT_Dis(__SPI__)        CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_TXOFIE_Msk)

/**
  * @brief  RxFIFO Underflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxFIFOUnderflow_INT_En(__SPI__)        SET_BIT((__SPI__)->INTEN, SPI0_INTEN_RXUFIE_Msk)

/**
  * @brief  RxFIFO Underflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxFIFOUnderflow_INT_Dis(__SPI__)       CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_RXUFIE_Msk)

/**
  * @brief  RxFIFO Overflow Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxFIFOOverflow_INT_En(__SPI__)         SET_BIT((__SPI__)->INTEN, SPI0_INTEN_RXOFIE_Msk)

/**
  * @brief  RxFIFO Overflow Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxFIFOOverflow_INT_Dis(__SPI__)        CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_RXOFIE_Msk)

/**
  * @brief  TxFIFO Empty Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxFIFOEmpty_INT_En(__SPI__)            SET_BIT((__SPI__)->INTEN, SPI0_INTEN_TXEIE_Msk)

/**
  * @brief  TxFIFO Empty Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxFIFOEmpty_INT_Dis(__SPI__)           CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_TXEIE_Msk)

/**
  * @brief  RxFIFO Full Interrupt Enable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxFIFOFull_INT_En(__SPI__)             SET_BIT((__SPI__)->INTEN, SPI0_INTEN_RXFIE_Msk)

/**
  * @brief  RxFIFO Full Interrupt Disable
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxFIFOFull_INT_Dis(__SPI__)            CLEAR_BIT((__SPI__)->INTEN, SPI0_INTEN_RXFIE_Msk)

/**
  * @brief  All Interrupt Enable Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return All Interrupt Enable
  */
#define __LL_SPI_AllIntEn_Get(__SPI__)                  READ_REG((__SPI__)->INTEN)


/**
  * @brief  Judge is RX Complete Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX hasn't Complete
  * @retval 1 RX has Complete
  */
#define __LL_SPI_IsRxCpltIntPnd(__SPI__)                READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_RXCI_Msk, SPI0_INT_RXCI_Pos)

/**
  * @brief  RX Complete Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxCpltIntPnd_Clr(__SPI__)              WRITE_REG((__SPI__)->INT, SPI0_INT_RXCI_Msk)

/**
  * @brief  Judge is TX Complete Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX hasn't Complete
  * @retval 1 TX has Complete
  */
#define __LL_SPI_IsTxCpltIntPnd(__SPI__)                READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_TXCI_Msk, SPI0_INT_TXCI_Pos)

/**
  * @brief  TX Complete Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxCpltIntPnd_Clr(__SPI__)              WRITE_REG((__SPI__)->INT, SPI0_INT_TXCI_Msk)

/**
  * @brief  Judge is RX Done Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX hasn't Done
  * @retval 1 RX has Done
  */
#define __LL_SPI_IsRxDoneIntPnd(__SPI__)                READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_RXDEI_Msk, SPI0_INT_RXDEI_Pos)

/**
  * @brief  RX Done Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxDoneIntPnd_Clr(__SPI__)              WRITE_REG((__SPI__)->INT, SPI0_INT_RXDEI_Msk)

/**
  * @brief  Judge is TX Done Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX hasn't Done
  * @retval 1 TX has Done
  */
#define __LL_SPI_IsTxDoneIntPnd(__SPI__)                READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_TXDEI_Msk, SPI0_INT_TXDEI_Pos)

/**
  * @brief  TX Done Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxDoneIntPnd_Clr(__SPI__)              WRITE_REG((__SPI__)->INT, SPI0_INT_TXDEI_Msk)

/**
  * @brief  Judge is Transmission Mode Fault Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Transmission Mode hasn't Fault
  * @retval 1 Transmission Mode has Fault
  */
#define __LL_SPI_IsTransModeFaultIntPnd(__SPI__)        READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_MDFI_Msk, SPI0_INT_MDFI_Pos)

/**
  * @brief  Transmission Mode Fault Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TransModeFaultIntPnd_Clr(__SPI__)      WRITE_REG((__SPI__)->INT, SPI0_INT_MDFI_Msk)

/**
  * @brief  Judge is Transmission Operation Fault Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Transmission Operation hasn't Fault
  * @retval 1 Transmission Operation has Fault
  */
#define __LL_SPI_IsTransOptFaultIntPnd(__SPI__)         READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_OPFI_Msk, SPI0_INT_OPFI_Pos)

/**
  * @brief  Transmission Operation Fault Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TransOptFaultIntPnd_Clr(__SPI__)       WRITE_REG((__SPI__)->INT, SPI0_INT_OPFI_Msk)

/**
  * @brief  Judge is Slave TX Underflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 Slave TX isn't Underflow
  * @retval 1 Slave TX is Underflow
  */
#define __LL_SPI_Slv_IsTxUnderflowIntPnd(__SPI__)       READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_TXUFI_Msk, SPI0_INT_TXUFI_Pos)

/**
  * @brief  TX Underflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_Slv_TxUnderflowIntPnd_Clr(__SPI__)     WRITE_REG((__SPI__)->INT, SPI0_INT_TXUFI_Msk)

/**
  * @brief  Judge is TX Overflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX isn't Overflow
  * @retval 1 TX is Overflow
  */
#define __LL_SPI_IsTxOverflowIntPnd(__SPI__)            READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_TXOFI_Msk, SPI0_INT_TXOFI_Pos)

/**
  * @brief  TX Overflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_TxOverflowIntPnd_Clr(__SPI__)          WRITE_REG((__SPI__)->INT, SPI0_INT_TXOFI_Msk)

/**
  * @brief  Judge is RX Underflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX isn't Underflow
  * @retval 1 RX is Underflow
  */
#define __LL_SPI_IsRxUnderflowIntPnd(__SPI__)           READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_RXUFI_Msk, SPI0_INT_RXUFI_Pos)

/**
  * @brief  RX Underflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxUnderflowIntPnd_Clr(__SPI__)         WRITE_REG((__SPI__)->INT, SPI0_INT_RXUFI_Msk)

/**
  * @brief  Judge is RX Overflow Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX isn't Overflow
  * @retval 1 RX is Overflow
  */
#define __LL_SPI_IsRxOverflowIntPnd(__SPI__)            READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_RXOFI_Msk, SPI0_INT_RXOFI_Pos)

/**
  * @brief  RX Overflow Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_RxOverflowIntPnd_Clr(__SPI__)          WRITE_REG((__SPI__)->INT, SPI0_INT_RXOFI_Msk)

/**
  * @brief  Judge is TX Empty Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TX isn't Empty
  * @retval 1 TX is Empty
  */
#define __LL_SPI_IsTxEmptyIntPnd(__SPI__)               READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_TXEI_Msk, SPI0_INT_TXEI_Pos)

/**
  * @brief  Judge is RX Full Interrupt Pending or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RX isn't Full
  * @retval 1 RX is Full
  */
#define __LL_SPI_IsRxFullIntPnd(__SPI__)                READ_BIT_SHIFT((__SPI__)->INT, SPI0_INT_RXFI_Msk, SPI0_INT_RXFI_Pos)

/**
  * @brief  All Interrupt Pending Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return All Interrupt Pending
  */
#define __LL_SPI_AllIntPnd_Get(__SPI__)                 READ_REG((__SPI__)->INT)

/**
  * @brief  All Interrupt Pending Clear
  * @param  __SPI__ Specifies SPI peripheral
  * @return None
  */
#define __LL_SPI_AllIntPnd_Clr(__SPI__)                 WRITE_REG((__SPI__)->INT, 0xffffffffUL)


/**
  * @brief  Judge RxFIFO is Full or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RxFIFO isn't Full
  * @retval 1 RxFIFO is Full
  */
#define __LL_SPI_IsRxFIFOFull(__SPI__)                  READ_BIT_SHIFT((__SPI__)->STATUS, SPI0_STATUS_RFF_Msk, SPI0_STATUS_RFF_Pos)

/**
  * @brief  Judge RxFIFO is Empty or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 RxFIFO isn't Empty
  * @retval 1 RxFIFO is Empty
  */
#define __LL_SPI_IsRxFIFOEmpty(__SPI__)                 READ_BIT_SHIFT((__SPI__)->STATUS, SPI0_STATUS_RFE_Msk, SPI0_STATUS_RFE_Pos)

/**
  * @brief  RxFIFO Level Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return RxFIFO Level
  */
#define __LL_SPI_RxFIFOLevel_Get(__SPI__)               READ_BIT_SHIFT((__SPI__)->STATUS, SPI0_STATUS_RXFLR_Msk, SPI0_STATUS_RXFLR_Pos)

/**
  * @brief  Judge TxFIFO is Full or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TxFIFO isn't Full
  * @retval 1 TxFIFO is Full
  */
#define __LL_SPI_IsTxFIFOFull(__SPI__)                  READ_BIT_SHIFT((__SPI__)->STATUS, SPI0_STATUS_TFF_Msk, SPI0_STATUS_TFF_Pos)

/**
  * @brief  Judge TxFIFO is Empty or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 TxFIFO isn't Empty
  * @retval 1 TxFIFO is Empty
  */
#define __LL_SPI_IsTxFIFOEmpty(__SPI__)                 READ_BIT_SHIFT((__SPI__)->STATUS, SPI0_STATUS_TFE_Msk, SPI0_STATUS_TFE_Pos)

/**
  * @brief  TxFIFO Level Get
  * @param  __SPI__ Specifies SPI peripheral
  * @return TxFIFO Level
  */
#define __LL_SPI_TxFIFOLevel_Get(__SPI__)               READ_BIT_SHIFT((__SPI__)->STATUS, SPI0_STATUS_TXFLR_Msk, SPI0_STATUS_TXFLR_Pos)

/**
  * @brief  Judge is SPI Busy or not
  * @param  __SPI__ Specifies SPI peripheral
  * @retval 0 SPI isn't Busy
  * @retval 1 SPI is Busy
  */
#define __LL_SPI_IsBusy(__SPI__)                        READ_BIT_SHIFT((__SPI__)->STATUS, SPI0_STATUS_BUSY_Msk, SPI0_STATUS_BUSY_Pos)


/**
  * @brief  SPI Data Write
  * @param  __SPI__ Specifies SPI peripheral
  * @param  dat data to write
  * @return None
  */
#define __LL_SPI_DAT_Write(__SPI__, dat)                WRITE_REG((__SPI__)->TDR, (dat & 0xffffUL))


/**
  * @brief  SPI Data Read
  * @param  __SPI__ Specifies SPI peripheral
  * @return Read data
  */
#define __LL_SPI_DAT_Read(__SPI__)                      READ_BIT_SHIFT((__SPI__)->RDR, SPI0_RDR_RD_Msk, SPI0_RDR_RD_Pos)


/**
  * @brief  Slave Underrun Data Set
  * @param  __SPI__ Specifies SPI peripheral
  * @param  dat Slave Underrun Data
  * @return None
  */
#define __LL_SPI_Slv_UnderrunDat_Set(__SPI__, dat)      WRITE_REG((__SPI__)->UDRDR, (dat & 0xffffUL))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Types SPI LL Exported Types
  * @brief    SPI LL Exported Types
  * @{
  */

/**
  * @brief SPI Uer callback function type definition
  */
typedef void (*SPI_UserCallback)(void);

/**
  * @brief SPI Instance Definition
  */
typedef enum {
    SPI_INSTANCE_0 = 0,         /*!< SPI Instance 0         */
    SPI_INSTANCE_1,             /*!< SPI Instance 1         */
    SPI_INSTANCE_NUMS,          /*!< SPI Instance Numbers   */
} SPI_InstanceETypeDef;

/**
  * @brief SPI State definition
  */
typedef enum {
    SPI_STATE_RESET,            /*!< Peripheral not Initialized                         */
    SPI_STATE_READY,            /*!< Peripheral Initialized and ready for use           */
    SPI_STATE_BUSY,             /*!< an internal process is ongoing                     */
    SPI_STATE_BUSY_TX,          /*!< Data Transmission process is ongoing               */
    SPI_STATE_BUSY_RX,          /*!< Data Reception process is ongoing                  */
    SPI_STATE_ERROR,            /*!< SPI error state                                    */
} SPI_StateETypeDef;


/**
  * @brief SPI Slave CS Input Mode Definition
  */
typedef enum {
    SPI_CS_INPUT_MODE_GPIO = 0, /*!< SPI Slave CS Input Mode GPIO   */
    SPI_CS_INPUT_MODE_CSI,      /*!< SPI Slave CS Input Mode CSI    */
} SPI_CSInputModeETypeDef;

/**
  * @brief SPI CS Polarity Definition
  */
typedef enum {
    SPI_CS_POL_INACT_HIGH = 0,  /*!< SPI CS Polarity Inactive High  */
    SPI_CS_POL_INACT_LOW,       /*!< SPI CS Polarity Inactive Low   */
} SPI_CSPolETypeDef;

/**
  * @brief SPI CS Mode Definition
  */
typedef enum {
    SPI_CS_MODE_CONTINUE = 0,   /*!< SPI CS Mode Continue   */
    SPI_CS_MODE_ONE,            /*!< SPI CS Mode One        */
} SPI_CsModeETypeDef;

/**
  * @brief SPI Wire Mode Definition
  */
typedef enum {
    SPI_WIRE_MODE_4 = 0,        /*!< SPI 4 Wire Mode */
    SPI_WIRE_MODE_3,            /*!< SPI 3 Wire Mode */
} SPI_WireModeETypeDef;

/**
  * @brief SPI Data Width Definition
  */
typedef enum {
    SPI_DATA_WIDTH_RSV = 0,     /*!< SPI Data Width Reserve */
    SPI_DATA_WIDTH_2BIT,        /*!< SPI Data Width 2bit    */
    SPI_DATA_WIDTH_3BIT,        /*!< SPI Data Width 3bit    */
    SPI_DATA_WIDTH_4BIT,        /*!< SPI Data Width 4bit    */
    SPI_DATA_WIDTH_5BIT,        /*!< SPI Data Width 5bit    */
    SPI_DATA_WIDTH_6BIT,        /*!< SPI Data Width 6bit    */
    SPI_DATA_WIDTH_7BIT,        /*!< SPI Data Width 7bit    */
    SPI_DATA_WIDTH_8BIT,        /*!< SPI Data Width 8bit    */
    SPI_DATA_WIDTH_9BIT,        /*!< SPI Data Width 9bit    */
    SPI_DATA_WIDTH_10BIT,       /*!< SPI Data Width 10bit   */
    SPI_DATA_WIDTH_11BIT,       /*!< SPI Data Width 11bit   */
    SPI_DATA_WIDTH_12BIT,       /*!< SPI Data Width 12bit   */
    SPI_DATA_WIDTH_13BIT,       /*!< SPI Data Width 13bit   */
    SPI_DATA_WIDTH_14BIT,       /*!< SPI Data Width 14bit   */
    SPI_DATA_WIDTH_15BIT,       /*!< SPI Data Width 15bit   */
    SPI_DATA_WIDTH_16BIT,       /*!< SPI Data Width 16bit   */
} SPI_DataWidthETypeDef;

/**
  * @brief SPI Bit Order Definition
  */
typedef enum {
    SPI_BIT_ORDER_MSB = 0,      /*!< SPI Bit Order MSB  */
    SPI_BIT_ORDER_LSB,          /*!< SPI Bit Order LSB  */
} SPI_BitOrderETypeDef;

/**
  * @brief SPI SCLK Polarity Definition
  */
typedef enum {
    SPI_SCLK_POL_IDLE_LOW  = 0,     /*!< SPI SCLK Polarity Idle Low     */
    SPI_SCLK_POL_IDLE_HIGH,         /*!< SPI SCLK Polarity Idle High    */
} SPI_SclkPolarityETypeDef;

/**
  * @brief SPI SCLK Phase Definition
  */
typedef enum {
    SPI_SCLK_PHASE_CAP_EDGE_0 = 0,  /*!< SPI SCLK Phase Capture at 0 Edge    */
    SPI_SCLK_PHASE_CAP_EDGE_1,      /*!< SPI SCLK Phase Capture at 1 Edge    */
} SPI_SclkPhaseETypeDef;

/**
  * @brief SPI Role Definition
  */
typedef enum {
    SPI_ROLE_SLAVE  = 0,            /*!< SPI Role Slave     */
    SPI_ROLE_MASTER,                /*!< SPI Role Master    */
} SPI_RoleETypeDef;

/**
 * @brief SPI IRQ Callback ID definition
 */
typedef enum {
    SPI_TX_CPLT_CB_ID,                      /*!< SPI Tx Completed callback ID       */
    SPI_RX_CPLT_CB_ID,                      /*!< SPI Rx Completed callback ID       */
    SPI_TX_HALF_CPLT_CB_ID,                 /*!< SPI Tx Half Completed callback ID  */
    SPI_RX_HALF_CPLT_CB_ID,                 /*!< SPI Rx Half Completed callback ID  */
    SPI_ERROR_CB_ID,                        /*!< SPI Error callback ID              */
} SPI_UserCallbackIdETypeDef;


/**
  * @brief SPI IRQ Callback structure definition
  */
typedef struct __SPI_UserCallbackTypeDef {
    SPI_UserCallback TxCpltCallback;        /*!< SPI Tx Completed callback          */
    SPI_UserCallback RxCpltCallback;        /*!< SPI Rx Completed callback          */
    SPI_UserCallback TxHalfCpltCallback;    /*!< SPI Tx Half Completed callback     */
    SPI_UserCallback RxHalfCpltCallback;    /*!< SPI Rx Half Completed callback     */
    SPI_UserCallback ErrorCallback;         /*!< SPI Error callback                 */
} SPI_UserCallbackTypeDef;

/**
  * @brief SPI LL config
  */
typedef struct __SPI_LLCfgTypeDef {
    SPI_WireModeETypeDef    wire_mode;      /*!< Wire Mode                  */
    SPI_CsModeETypeDef      cs_mode;        /*!< CS Mode                    */
    SPI_CSPolETypeDef       cs_pol;         /*!< CS Polarity                */
    SPI_CSInputModeETypeDef cs_input_mode;  /*!< CS Input Mode              */
    SPI_BitOrderETypeDef    bit_order;      /*!< Bit Order                  */

    bool     cs_sw_out_en;                  /*!< CS Software Output Enable  */
    bool     mosi_miso_swap_en;             /*!< MOSI/MISO Pin Swap Enable  */
    uint8_t  tx_fifo_empty_thres;           /*!< TxFIFO Empty Threshold     */
    uint8_t  rx_fifo_full_thres;            /*!< RxFIFO Full Threshold      */
    uint8_t  mst_rx_delay;                  /*!< Master Rx Delay            */
    uint16_t mst_ss_idleness;               /*!< Master SS Idleness         */
    uint16_t mst_inter_dat_idleness;        /*!< Master Inter-Data Idleness */
    
    bool loopback_en;                       /*!< Loopback Enable            */
} SPI_LLCfgTypeDef;

/**
  * @brief SPI user config
  */
typedef struct __SPI_UserCfgTypeDef {
    SPI_RoleETypeDef         role;          /*!< Role                           */
    SPI_SclkPolarityETypeDef sclk_pol;      /*!< SCLK Polarity                  */
    SPI_SclkPhaseETypeDef    sclk_phase;    /*!< SCLK Phase                     */
    SPI_DataWidthETypeDef    data_width;    /*!< Serial data width              */
    SPI_UserCallbackTypeDef  user_callback; /*!< User Callback                  */

    uint32_t baudrate;                      /*!< Baudrate                       */
    SPI_LLCfgTypeDef *ll_cfg;               /*!< Optional LL Config Pointer     */
} SPI_UserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup SPI_LL_Exported_Functions
  * @{
  */

/** @addtogroup SPI_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_SPI_Init(SPI_TypeDef *Instance, SPI_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_SPI_DeInit(SPI_TypeDef *Instance);
LL_StatusETypeDef LL_SPI_Reset(SPI_TypeDef *Instance);
void LL_SPI_MspInit(SPI_TypeDef *Instance);
void LL_SPI_MspDeInit(SPI_TypeDef *Instance);
LL_StatusETypeDef LL_SPI_RegisterCallback(SPI_TypeDef *Instance, SPI_UserCallbackIdETypeDef CallbackID, SPI_UserCallback pCallback);
LL_StatusETypeDef LL_SPI_UnRegisterCallback(SPI_TypeDef *Instance, SPI_UserCallbackIdETypeDef CallbackID);
/**
  * @}
  */


/** @addtogroup SPI_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_SPI_Transmit_CPU(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout);
LL_StatusETypeDef LL_SPI_Receive_CPU(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout);
LL_StatusETypeDef LL_SPI_TransmitReceive_CPU(SPI_TypeDef *Instance, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size, uint32_t timeout);

LL_StatusETypeDef LL_SPI_Transmit_IT(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size);
LL_StatusETypeDef LL_SPI_Receive_IT(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size);
LL_StatusETypeDef LL_SPI_TransmitReceive_IT(SPI_TypeDef *Instance, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size);

#ifdef LL_DMA_MODULE_ENABLED
LL_StatusETypeDef LL_SPI_Transmit_DMA(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size);
LL_StatusETypeDef LL_SPI_Receive_DMA(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size);
LL_StatusETypeDef LL_SPI_TransmitReceive_DMA(SPI_TypeDef *Instance, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size);
#endif
/**
  * @}
  */


/** @addtogroup SPI_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_SPI_IRQHandler(SPI_TypeDef *Instance);

void LL_SPI_TransModeFaultCallback(SPI_TypeDef *Instance);
void LL_SPI_TransOptFaultCallback(SPI_TypeDef *Instance);
void LL_SPI_RxFullCallback(SPI_TypeDef *Instance);
void LL_SPI_TxEmptyCallback(SPI_TypeDef *Instance);
void LL_SPI_RxOverflowCallback(SPI_TypeDef *Instance);
void LL_SPI_RxUnderflowCallback(SPI_TypeDef *Instance);
void LL_SPI_TxOverflowCallback(SPI_TypeDef *Instance);
void LL_SPI_Slv_TxUnderflowCallback(SPI_TypeDef *Instance);
void LL_SPI_TxDoneCallback(SPI_TypeDef *Instance);
void LL_SPI_RxDoneCallback(SPI_TypeDef *Instance);
void LL_SPI_TxCpltCallback(SPI_TypeDef *Instance);
void LL_SPI_RxCpltCallback(SPI_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_SPI_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

