/**
  ******************************************************************************
  * @file    tae32g58xx_ll_pdm.h
  * @author  MCD Application Team
  * @brief   Header file for PDM LL module
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
#ifndef _TAE32G58XX_LL_PDM_H_
#define _TAE32G58XX_LL_PDM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup PDM_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup PDM_LL_Exported_Constants PDM LL Exported Constants
  * @brief    PDM LL Exported Constants
  * @{
  */

/**
  * @brief PDM Data Filter Shift Bit Max Definition
  */
#define PDM_DAT_FIL_SHIFT_MAX       (13)

/**
  * @brief PDM Data Filter Over Sample Rate Max Definition
  */
#define PDM_DAT_FIL_OSR_MAX         (256)

/**
  * @brief PDM Comparator Filter Over Sample Rate Max Definition
  */
#define PDM_CMP_FIL_OSR_MAX         (32)

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup PDM_LL_Exported_Macros PDM LL Exported Macros
  * @brief    PDM LL Exported Macros
  * @{
  */

/**
  * @brief  PDM Input Mode Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  mode PDM Input Mode
  * @return None
  */
#define __LL_PDM_InputMode_Set(__PDM__, mode)           \
        MODIFY_REG((__PDM__)->ENABLE, PDM0_ENABLE_INMOD_Msk, (((mode) & 0x1UL) << PDM0_ENABLE_INMOD_Pos))

/**
  * @brief  PDM Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_En(__PDM__)                            SET_BIT((__PDM__)->ENABLE, PDM0_ENABLE_PDMEN_Msk)

/**
  * @brief  PDM Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_Dis(__PDM__)                           CLEAR_BIT((__PDM__)->ENABLE, PDM0_ENABLE_PDMEN_Msk)


/**
  * @brief  PDM Master SPI RX Delay Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  pclk_cnt RX Delay pclk count
  * @return None
  */
#define __LL_PDM_Mst_SpiRxDelay_Set(__PDM__, pclk_cnt)  \
        MODIFY_REG((__PDM__)->CTRL, PDM0_CTRL_RXDLY_Msk, (((pclk_cnt) & 0x7U) << PDM0_CTRL_RXDLY_Pos))

/**
  * @brief  PDM DMA Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define LL_PDM_DMA_En(__PDM__)                          SET_BIT((__PDM__)->CTRL, PDM0_CTRL_DMAEN_Msk)

/**
  * @brief  PDM DMA Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define LL_PDM_DMA_Dis(__PDM__)                         CLEAR_BIT((__PDM__)->CTRL, PDM0_CTRL_DMAEN_Msk)

/**
  * @brief  PDM Slave Sample Mode Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  mode PDM Slave Sample Mode @ref PDM_Slv_SampleEdgeETypeDef
  * @return None
  */
#define __LL_PDM_Slv_SampleMode_Set(__PDM__, mode)      \
        MODIFY_REG((__PDM__)->CTRL, PDM0_CTRL_SAMPMODE_Msk, (((mode) & 0x1UL) << PDM0_CTRL_SAMPMODE_Pos))

/**
  * @brief  Serial Clock Polarity Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  pol Serial Clock Polarity @ref PDM_SerialClkPolETypeDef
  * @return None
  */
#define __LL_PDM_SerialClkPol_Set(__PDM__, pol)         \
        MODIFY_REG((__PDM__)->CTRL, PDM0_CTRL_SCPOL_Msk, (((pol) & 0x1UL) << PDM0_CTRL_SCPOL_Pos))

/**
  * @brief  PDM Role Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  role PDM Role @ref PDM_RoleETypeDef
  * @return None
  */
#define __LL_PDM_Role_Set(__PDM__, role)                \
        MODIFY_REG((__PDM__)->CTRL, PDM0_CTRL_MSTEN_Msk, (((role) & 0x1UL) << PDM0_CTRL_MSTEN_Pos))

/**
  * @brief  Baud Rate Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  br PDM Baud Rate
  * @return None
  */
#define __LL_PDM_BaudRate_Set(__PDM__, br)              \
        MODIFY_REG((__PDM__)->CTRL, PDM0_CTRL_BAUD_Msk, (((br) & 0xfffUL) << PDM0_CTRL_BAUD_Pos))


/**
  * @brief  Data Filter Shift Control Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  shift PDM Data Filter Shift
  * @return None
  */
#define __LL_PDM_DatFil_Shift_Set(__PDM__, shift)       \
        MODIFY_REG((__PDM__)->DFCR, PDM0_DFCR_SHIFT_Msk, (((shift) & 0xfUL) << PDM0_DFCR_SHIFT_Pos))

/**
  * @brief  Data Filter SDSYNC Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_SDSYNC_En(__PDM__)              SET_BIT((__PDM__)->DFCR, PDM0_DFCR_SDSYNCEN_Msk)

/**
  * @brief  Data Filter SDSYNC Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_SDSYNC_Dis(__PDM__)             CLEAR_BIT((__PDM__)->DFCR, PDM0_DFCR_SDSYNCEN_Msk)

/**
  * @brief  Data Filter Output Data Length Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  len Data Filter Output Data Length @ref PDM_DatFil_DatLenETypeDef
  * @return None
  */
#define __LL_PDM_DatFil_OutputDatLen_Set(__PDM__, len)  \
        MODIFY_REG((__PDM__)->DFCR, PDM0_DFCR_DFDR_Msk, (((len) & 0x1UL) << PDM0_DFCR_DFDR_Pos))

/**
  * @brief  Data Filter Bypass Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_Bypass_En(__PDM__)              SET_BIT((__PDM__)->DFCR, PDM0_DFCR_DFBYPASS_Msk)

/**
  * @brief  Data Filter Bypass Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_Bypass_Dis(__PDM__)             CLEAR_BIT((__PDM__)->DFCR, PDM0_DFCR_DFBYPASS_Msk)

/**
  * @brief  Data Filter Structure Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  stru Data Filter Structure
  * @return None
  */
#define __LL_PDM_DatFil_Structure_Set(__PDM__, stru)    \
        MODIFY_REG((__PDM__)->DFCR, PDM0_DFCR_DFSST_Msk, (((stru & 0x7U) << PDM0_DFCR_DFSST_Pos)))

/**
  * @brief  Data Filter Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_En(__PDM__)                     SET_BIT((__PDM__)->DFCR, PDM0_DFCR_DFEN_Msk)

/**
  * @brief  Data Filter Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_Dis(__PDM__)                    CLEAR_BIT((__PDM__)->DFCR, PDM0_DFCR_DFEN_Msk)

/**
  * @brief  Data Filter Over Sample Rate Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param sr Data Filter Over Sample Rate
  * @return None
  */
#define __LL_PDM_DatFil_OverSampleRate_Set(__PDM__, sr) \
        MODIFY_REG((__PDM__)->DFCR, PDM0_DFCR_DOSR_Msk, (((sr-1) & 0xffUL) << PDM0_DFCR_DOSR_Pos))


/**
  * @brief  Comparator Filter Output Select
  * @param  __PDM__ Specifies PDM peripheral
  * @param  out Comparator Filter Output
  * @return None
  */
#define __LL_PDM_CmpFil_Output_Sel(__PDM__, out)        \
        MODIFY_REG((__PDM__)->CFCR, PDM0_CFCR_COMPSEL_Msk, (((out) & 0x1UL) << PDM0_CFCR_COMPSEL_Pos))

/**
  * @brief  Comparator Filter Bypass Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_Bypass_En(__PDM__)              SET_BIT((__PDM__)->CFCR, PDM0_CFCR_CFBYPASS_Msk)

/**
  * @brief  Comparator Filter Bypass Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_Bypass_Dis(__PDM__)             CLEAR_BIT((__PDM__)->CFCR, PDM0_CFCR_CFBYPASS_Msk)

/**
  * @brief  Comparator Filter Structure Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  stru Comparator Filter Structure
  * @return None
  */
#define __LL_PDM_CmpFil_Structure_Set(__PDM__, stru)    \
        MODIFY_REG((__PDM__)->CFCR, PDM0_CFCR_CFSST_Msk, (((stru) & 0x7U) << PDM0_CFCR_CFSST_Pos))

/**
  * @brief  Comparator Filter Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_En(__PDM__)                     SET_BIT((__PDM__)->CFCR, PDM0_CFCR_CFEN_Msk)

/**
  * @brief  Comparator Filter Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_Dis(__PDM__)                    CLEAR_BIT((__PDM__)->CFCR, PDM0_CFCR_CFEN_Msk)

/**
  * @brief  Comparator Filter Over Sample Rate Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param sr Comparator Filter Over Sample Rate
  * @return None
  */
#define __LL_PDM_CmpFil_OverSampleRate_Set(__PDM__, sr) \
        MODIFY_REG((__PDM__)->CFCR, PDM0_CFCR_COSR_Msk, (((sr-1) & 0x1fU) << PDM0_CFCR_COSR_Pos))


/**
  * @brief  FIFO Reset
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_FIFO_Rst(__PDM__)                      SET_BIT((__PDM__)->FCSR, PDM0_FCSR_FIFORST_Msk)

/**
  * @brief  Judge is FIFO Full or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 FIFO isn't Full
  * @retval 1 FIFO is Full
  */
#define __LL_PDM_IsFIFOFull(__PDM__)                    READ_BIT_SHIFT((__PDM__)->FCSR, PDM0_FCSR_FIFOFULL_Msk, PDM0_FCSR_FIFOFULL_Pos)

/**
  * @brief  Judge is FIFO Empty or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 FIFO isn't Empty
  * @retval 1 FIFO is Empty
  */
#define __LL_PDM_IsFIFOEmpty(__PDM__)                   READ_BIT_SHIFT((__PDM__)->FCSR, PDM0_FCSR_FIFOEMPTY_Msk, PDM0_FCSR_FIFOEMPTY_Pos)

/**
  * @brief  FIFO Level Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return FIFO Level
  */
#define __LL_PDM_FIFOLvl_Get(__PDM__)                   READ_BIT_SHIFT((__PDM__)->FCSR, PDM0_FCSR_PDMFST_Msk, PDM0_FCSR_PDMFST_Pos)

/**
  * @brief  FIFO Full Threshold Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  thres FIFO Full Threshold
  * @return None
  */
#define __LL_PDM_FIFOFullThres_Set(__PDM__, thres)      \
        MODIFY_REG((__PDM__)->FCSR, PDM0_FCSR_PDMFIL_Msk, (((thres-1) & 0x7U) << PDM0_FCSR_PDMFIL_Pos))


/**
  * @brief  Data Filter FIFO Underflow Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOUnderflow_INT_En(__PDM__)    SET_BIT((__PDM__)->IER, PDM0_IER_FIUIE_Msk)

/**
  * @brief  Data Filter FIFO Underflow Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOUnderflow_INT_Dis(__PDM__)   CLEAR_BIT((__PDM__)->IER, PDM0_IER_FIUIE_Msk)

/**
  * @brief  Judge is Data Filter FIFO Underflow Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Data Filter FIFO Underflow Interrupt is Disable
  * @retval 1 Data Filter FIFO Underflow Interrupt is Enable
  */
#define __LL_PDM_DatFil_IsFIFOUnderflowIntEn(__PDM__)   READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_FIUIE_Msk, PDM0_IER_FIUIE_Pos)

/**
  * @brief  PDM Slave Clock Timeout Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_Slv_ClkTimeout_INT_En(__PDM__)         SET_BIT((__PDM__)->IER, PDM0_IER_CTIE_Msk)

/**
  * @brief  PDM Slave Clock Timeout Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_Slv_ClkTimeout_INT_Dis(__PDM__)        CLEAR_BIT((__PDM__)->IER, PDM0_IER_CTIE_Msk)

/**
  * @brief  Judge is PDM Slave Clock Timeout Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 PDM Slave Clock Timeout Interrupt is Disable
  * @retval 1 PDM Slave Clock Timeout Interrupt is Enable
  */
#define __LL_PDM_Slv_IsClkTimeoutIntEn(__PDM__)         READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_CTIE_Msk, PDM0_IER_CTIE_Pos)

/**
  * @brief  Data Filter FIFO Full Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOFull_INT_En(__PDM__)        SET_BIT((__PDM__)->IER, PDM0_IER_FFIE_Msk)

/**
  * @brief  Data Filter FIFO Full Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOFull_INT_Dis(__PDM__)       CLEAR_BIT((__PDM__)->IER, PDM0_IER_FFIE_Msk)

/**
  * @brief  Judge is Data Filter FIFO Full Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Data Filter FIFO Full Interrupt is Disable
  * @retval 1 Data Filter FIFO Full Interrupt is Enable
  */
#define __LL_PDM_DatFil_IsFIFOFullIntEn(__PDM__)        READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_FFIE_Msk, PDM0_IER_FFIE_Pos)

/**
  * @brief  Data Filter FIFO Overflow Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOOverflow_INT_En(__PDM__)    SET_BIT((__PDM__)->IER, PDM0_IER_FIOIE_Msk)

/**
  * @brief  Data Filter FIFO Overflow Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOOverflow_INT_Dis(__PDM__)   CLEAR_BIT((__PDM__)->IER, PDM0_IER_FIOIE_Msk)

/**
  * @brief  Judge is Data Filter FIFO Overflow Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Data Filter FIFO Overflow Interrupt is Disable
  * @retval 1 Data Filter FIFO Overflow Interrupt is Enable
  */
#define __LL_PDM_DatFil_IsFIFOOverflowIntEn(__PDM__)    READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_FIOIE_Msk, PDM0_IER_FIOIE_Pos)

/**
  * @brief  Comparator Filter Data Overflow Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_DatOverflow_INT_En(__PDM__)     SET_BIT((__PDM__)->IER, PDM0_IER_DOFIE_Msk)

/**
  * @brief  Comparator Filter Data Overflow Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_DatOverflow_INT_Dis(__PDM__)    CLEAR_BIT((__PDM__)->IER, PDM0_IER_DOFIE_Msk)

/**
  * @brief  Judge is Comparator Filter Data Overflow Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Comparator Filter Data Overflow Interrupt is Disable
  * @retval 1 Comparator Filter Data Overflow Interrupt is Enable
  */
#define __LL_PDM_CmpFil_IsDatOverflowIntEn(__PDM__)     READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_DOFIE_Msk, PDM0_IER_DOFIE_Pos)

/**
  * @brief  Comparator Filter Data Finish Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_DatFinish_INT_En(__PDM__)       SET_BIT((__PDM__)->IER, PDM0_IER_DFIE_Msk)

/**
  * @brief  Comparator Filter Data Finish Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_DatFinish_INT_Dis(__PDM__)      CLEAR_BIT((__PDM__)->IER, PDM0_IER_DFIE_Msk)

/**
  * @brief  Judge is Comparator Filter Data Finish Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Comparator Filter Data Finish Interrupt is Disable
  * @retval 1 Comparator Filter Data Finish Interrupt is Enable
  */
#define __LL_PDM_CmpFil_IsDatFinishIntEn(__PDM__)       READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_DFIE_Msk, PDM0_IER_DFIE_Pos)

/**
  * @brief  Comparator Filter Low Level Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_LowLvl_INT_En(__PDM__)          SET_BIT((__PDM__)->IER, PDM0_IER_LLIE_Msk)

/**
  * @brief  Comparator Filter Low Level Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_LowLvl_INT_Dis(__PDM__)         CLEAR_BIT((__PDM__)->IER, PDM0_IER_LLIE_Msk)

/**
  * @brief  Judge is Comparator Filter Low Level Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Comparator Filter Low Level Interrupt  is Disable
  * @retval 1 Comparator Filter Low Level Interrupt  is Enable
  */
#define __LL_PDM_CmpFil_IsLowLvlIntEn(__PDM__)          READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_LLIE_Msk, PDM0_IER_LLIE_Pos)

/**
  * @brief  Comparator Filter High Level Interrupt Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_HighLvl_INT_En(__PDM__)         SET_BIT((__PDM__)->IER, PDM0_IER_HLIE_Msk)

/**
  * @brief  Comparator Filter High Level Interrupt Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_HighLvl_INT_Dis(__PDM__)        CLEAR_BIT((__PDM__)->IER, PDM0_IER_HLIE_Msk)

/**
  * @brief  Judge is Comparator Filter High Level Interrupt Enable or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Comparator Filter High Level Interrupt is Disable
  * @retval 1 Comparator Filter High Level Interrupt is Enable
  */
#define __LL_PDM_CmpFil_IsHighLvlIntEn(__PDM__)         READ_BIT_SHIFT((__PDM__)->IER, PDM0_IER_HLIE_Msk, PDM0_IER_HLIE_Pos)

/**
  * @brief  All Interrupt Enable Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return All Interrupt Enable
  */
#define __LL_PDM_AllIntEn_Get(__PDM__)                  READ_REG((__PDM__)->IER)


/**
  * @brief  Judge is Data Filter FIFO Underflow Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't Data Filter FIFO Underflow Interrupt Pending
  * @retval 1 is Data Filter FIFO Underflow Interrupt Pending
  */
#define __LL_PDM_DatFil_IsFIFOUnderflowIntPnd(__PDM__)   READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_FIUINTR_Msk, PDM0_ISR_FIUINTR_Pos)

/**
  * @brief  Data Filter FIFO Underflow Interrupt Pending Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOUnderflowIntPnd_Clr(__PDM__) WRITE_REG((__PDM__)->ISR, PDM0_ISR_FIUINTR_Msk)

/**
  * @brief  Judge is PDM Slave Clock Timeout Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't PDM Slave Clock Timeout Interrupt Pending
  * @retval 1 is PDM Slave Clock Timeout Interrupt Pending
  */
#define __LL_PDM_Slv_IsClkTimeoutIntPnd(__PDM__)        READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_CTOINTR_Msk, PDM0_ISR_CTOINTR_Pos)

/**
  * @brief  PDM Slave Clock Timeout Interrupt Pending Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_Slv_ClkTimeoutIntPnd_Clr(__PDM__)      WRITE_REG((__PDM__)->ISR, PDM0_ISR_CTOINTR_Msk)

/**
  * @brief  Judge is Data Filter FIFO Full Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't Data Filter FIFO Full Interrupt Pending
  * @retval 1 is Data Filter FIFO Full Interrupt Pending
  */
#define __LL_PDM_DatFil_IsFIFOFullIntPnd(__PDM__)       READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_FIFINTR_Msk, PDM0_ISR_FIFINTR_Pos)

/**
  * @brief  Judge is Data Filter FIFO Overflow Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't Data Filter FIFO Overflow Interrupt Pending
  * @retval 1 is Data Filter FIFO Overflow Interrupt Pending
  */
#define __LL_PDM_DatFil_IsFIFOOverflowIntPnd(__PDM__)   READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_FIOINTR_Msk, PDM0_ISR_FIOINTR_Pos)

/**
  * @brief  Data Filter FIFO Overflow Interrupt Pending Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOOverflowIntPnd_Clr(__PDM__) WRITE_REG((__PDM__)->ISR, PDM0_ISR_FIOINTR_Msk)

/**
  * @brief  Judge is Comparator Filter Data Overflow Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't Comparator Filter Data Overflow Interrupt Pending
  * @retval 1 is Comparator Filter Data Overflow Interrupt Pending
  */
#define __LL_PDM_CmpFil_IsDatOverflowIntPnd(__PDM__)    READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_DOINTR_Msk, PDM0_ISR_DOINTR_Pos)

/**
  * @brief  Comparator Filter Data Overflow Interrupt Pending Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_DatOverflowIntPnd_Clr(__PDM__)  WRITE_REG((__PDM__)->ISR, PDM0_ISR_DOINTR_Msk)

/**
  * @brief  Judge is Comparator Filter Data Finish Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't Comparator Filter Data Finish Interrupt Pending
  * @retval 1 is Comparator Filter Data Finish Interrupt Pending
  */
#define __LL_PDM_CmpFil_IsDatFinishIntPnd(__PDM__)      READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_DFINTR_Msk, PDM0_ISR_DFINTR_Pos)

/**
  * @brief  Comparator Filter Data Finish Interrupt Pending Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_DatFinishIntPnd_Clr(__PDM__)    WRITE_REG((__PDM__)->ISR, PDM0_ISR_DFINTR_Msk)

/**
  * @brief  Judge is Comparator Filter Low Level Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't Comparator Filter Low Level Interrupt Pending
  * @retval 1 is Comparator Filter Low Level Interrupt Pending
  */
#define __LL_PDM_CmpFil_IsLowLvlIntPnd(__PDM__)         READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_LLINTR_Msk, PDM0_ISR_LLINTR_Pos)

/**
  * @brief  Comparator Filter Low Level Interrupt Pending Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_LowLvlIntPnd_Clr(__PDM__)       WRITE_REG((__PDM__)->ISR, PDM0_ISR_LLINTR_Msk)

/**
  * @brief  Judge is Comparator Filter High Level Interrupt Pending or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 isn't Comparator Filter High Level Interrupt Pending
  * @retval 1 is Comparator Filter High Level Interrupt Pending
  */
#define __LL_PDM_CmpFil_IsHighLvlIntPnd(__PDM__)        READ_BIT_SHIFT((__PDM__)->ISR, PDM0_ISR_HLINTR_Msk, PDM0_ISR_HLINTR_Pos)

/**
  * @brief  Comparator Filter High Level Interrupt Pending Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_CmpFil_HighLvlIntPnd_Clr(__PDM__)      WRITE_REG((__PDM__)->ISR, PDM0_ISR_HLINTR_Msk)

/**
  * @brief  All Interrupt Pending Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return All Interrupt Pending
  */
#define __LL_PDM_AllIntPnd_Get(__PDM__)                 READ_REG((__PDM__)->ISR)


/**
  * @brief  Data Filter Data Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return Data Filter Data
  */
#define __LL_PDM_DatFil_Dat_Get(__PDM__)                READ_BIT_SHIFT((__PDM__)->DDAT, PDM0_DDAT_DDAT_Msk, PDM0_DDAT_DDAT_Pos)


/**
  * @brief  Comparator Filter Data Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return Comparator Filter Data
  */
#define __LL_PDM_CmpFil_Dat_Get(__PDM__)                READ_BIT_SHIFT((__PDM__)->CDAT, PDM0_CDAT_CDAT_Msk, PDM0_CDAT_CDAT_Pos)


/**
  * @brief  FIFO Data Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return FIFO Data
  */
#define __LL_PDM_FIFODat_Get(__PDM__)                   READ_BIT_SHIFT((__PDM__)->FDAT, PDM0_FDAT_FDAT_Msk, PDM0_FDAT_FDAT_Pos)


/**
  * @brief  Comparator Filter High Level Threshold Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  thres Comparator Filter High Level Threshold
  * @return None
  */
#define __LL_PDM_CmpFil_HighLvlThres_Set(__PDM__, thres)    \
        MODIFY_REG((__PDM__)->CMPH, PDM0_CMPH_HLT_Msk, (((thres) & 0xffffUL) << PDM0_CMPH_HLT_Pos))

/**
  * @brief  Comparator Filter High Level Threshold Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return Comparator Filter High Level Threshold
  */
#define __LL_PDM_CmpFil_HighLvlThres_Get(__PDM__)           READ_BIT_SHIFT((__PDM__)->CMPH, PDM0_CMPH_HLT_Msk, PDM0_CMPH_HLT_Pos)


/**
  * @brief  Comparator Filter Low Level Threshold Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  thres Comparator Filter Low Level Threshold
  * @return None
  */
#define __LL_PDM_CmpFil_LowLvlThres_Set(__PDM__, thres)     \
        MODIFY_REG((__PDM__)->CMPL, PDM0_CMPL_LLT_Msk, (((thres) & 0xffffUL) << PDM0_CMPL_LLT_Pos))

/**
  * @brief  Comparator Filter Low Level Threshold Get
  * @param  __PDM__ Specifies PDM peripheral
  * @return Comparator Filter Low Level Threshold
  */
#define __LL_PDM_CmpFil_LowLvlThres_Get(__PDM__)            READ_BIT_SHIFT((__PDM__)->CMPL, PDM0_CMPL_LLT_Msk, PDM0_CMPL_LLT_Pos)


/**
  * @brief  PDM Slave Clock Rollover Timeout Set
  * @param  __PDM__ Specifies PDM peripheral
  * @param  cnt PDM Slave Clock Rollover Timeout pclk count
  * @return None
  */
#define __LL_PDM_Slv_ClkRolloverTimeout_Set(__PDM__, cnt)   \
        MODIFY_REG((__PDM__)->CLKTO, PDM0_CLKTO_CLKTOT_Msk, (((cnt) & 0x3ffffUL) << PDM0_CLKTO_CLKTOT_Pos))


/**
  * @brief  Data Filter FIFO Full Interrupt Clear WTSYNFLG Flag Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOFullIntClrWTSYNFLG_En(__PDM__)  SET_BIT((__PDM__)->SDSYNC, PDM0_SDSYNC_WTSCLREN_Msk)

/**
  * @brief  Data Filter FIFO Full Interrupt Clear WTSYNFLG Flag Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_FIFOFullIntClrWTSYNFLG_Dis(__PDM__) CLEAR_BIT((__PDM__)->SDSYNC, PDM0_SDSYNC_WTSCLREN_Msk)

/**
  * @brief  Data Filter SDSYNC Reset FIFO Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_SDSYNC_RstFIFO_En(__PDM__)          SET_BIT((__PDM__)->SDSYNC, PDM0_SDSYNC_FFSYNCCLREN_Msk)

/**
  * @brief  Data Filter SDSYNC Reset FIFO Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_SDSYNC_RstFIFO_Dis(__PDM__)         CLEAR_BIT((__PDM__)->SDSYNC, PDM0_SDSYNC_FFSYNCCLREN_Msk)

/**
  * @brief  Data Filter WTSYNFLG Clear
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_WTSYNFLG_Clr(__PDM__)               SET_BIT((__PDM__)->SDSYNC, PDM0_SDSYNC_WTSYNCLR_Msk)

/**
  * @brief  Judge is Data Filter Receive SDSYNC Flag(WTSYNFLG) or not
  * @param  __PDM__ Specifies PDM peripheral
  * @retval 0 Data Filter isn't Receive SDSYNC Flag(WTSYNFLG)
  * @retval 1 Data Filter is Receive SDSYNC Flag(WTSYNFLG)
  */
#define __LL_PDM_DatFil_IsWTSYNFLG(__PDM__)                 \
        READ_BIT_SHIFT((__PDM__)->SDSYNC, PDM0_SDSYNC_WTSYNFLG_Msk, PDM0_SDSYNC_WTSYNFLG_Pos)

/**
  * @brief  Data Filter WTSYNFLG Control FIFO Write Enable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_WTSYNFLG_CtrlFIFOWrite_En(__PDM__)  SET_BIT((__PDM__)->SDSYNC, PDM0_SDSYNC_WTSYNCEN_Msk)

/**
  * @brief  Data Filter WTSYNFLG Control FIFO Write Disable
  * @param  __PDM__ Specifies PDM peripheral
  * @return None
  */
#define __LL_PDM_DatFil_WTSYNFLG_CtrlFIFOWrite_Dis(__PDM__) CLEAR_BIT((__PDM__)->SDSYNC, PDM0_SDSYNC_WTSYNCEN_Msk)

/**
  * @brief  Data Filter SDSYNC Event Select
  * @param  __PDM__ Specifies PDM peripheral
  * @param  evt SDSYNC Event @ref PDM_SDSYNC_EvtETypeDef
  * @return None
  */
#define __LL_PDM_DatFil_SDSYNC_Evt_Sel(__PDM__, evt)        \
        MODIFY_REG((__PDM__)->SDSYNC, PDM0_SDSYNC_SYNCSEL_Msk, (((evt) & 0x3fUL) << PDM0_SDSYNC_SYNCSEL_Pos))


/**
  * @brief  Software Input Data Write
  * @param  __PDM__ Specifies PDM peripheral
  * @param  dat Software Input Data
  * @return None
  */
#define __LL_PDM_SwInputDat_Write(__PDM__, dat)             WRITE_REG((__PDM__)->IDAT, dat)


/**
  * @brief  Judge is PDM Data Filter Shift Bit Valid or not
  * @param  shift PDM Data Filter Shift Bit
  * @retval 0 PDM Data Filter Shift Bit is Invalid
  * @retval 1 PDM Data Filter Shift Bit is Valid
  */
#define __LL_PDM_DatFil_IsShiftValid(shift)                 ((shift) <= PDM_DAT_FIL_SHIFT_MAX)

/**
  * @brief  Judge is PDM Data Filter Over Sample Rate Valid or not
  * @param  osr PDM Data Filter Over Sample Rate
  * @retval 0 PDM Data Filter Over Sample Rate is Invalid
  * @retval 1 PDM Data Filter Over Sample Rate is Valid
  */
#define __LL_PDM_DatFil_IsOSR_Valid(osr)                    \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?         \
        ((osr) > 1 && (osr) <= PDM_DAT_FIL_OSR_MAX) :       \
        ((osr) > 0 && (osr) <= PDM_DAT_FIL_OSR_MAX))

/**
  * @brief  Judge is PDM Comparator Filter Over Sample Rate Valid or not
  * @param  osr PDM Comparator Filter Over Sample Rate
  * @retval 0 PDM Comparator Filter Over Sample Rate is Invalid
  * @retval 1 PDM Comparator Filter Over Sample Rate is Valid
  */
#define __LL_PDM_CmpFil_IsOSR_Valid(osr)                    \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?         \
        ((osr) > 1 && (osr) <= PDM_CMP_FIL_OSR_MAX) :       \
        ((osr) > 0 && (osr) <= PDM_CMP_FIL_OSR_MAX))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup PDM_LL_Exported_Types PDM LL Exported Types
  * @brief    PDM LL Exported Types
  * @{
  */

/**
  * @brief PDM Input Mode Definition
  */
typedef enum {
    PDM_INPUT_MODE_HW = 0,              /*!< PDM Input Mode Hardware    */
    PDM_INPUT_MODE_SW,                  /*!< PDM Input Mode Software    */
} PDM_InputModeETypeDef;

/**
  * @brief PDM Slave Sample Egde Definition
  */
typedef enum {
    PDM_SLV_SAMPLE_FALLING_EDGE = 0,    /*!< PDM Slave Sample Falling Edge  */
    PDM_SLV_SAMPLE_RISING_EDGE,         /*!< PDM Slave Sample Rising Edge   */
} PDM_Slv_SampleEdgeETypeDef;

/**
  * @brief PDM Serial Clock Polarity Definition
  */
typedef enum {
    PDM_SERIAL_CLK_POL_INACT_LOW  = 0,  /*!< PDM Serial Clock Inactive Low     */
    PDM_SERIAL_CLK_POL_INACT_HIGH,      /*!< PDM Serial Clock Inactive High    */
} PDM_SerialClkPolETypeDef;

/**
  * @brief PDM Role Definition
  */
typedef enum {
    PDM_ROLE_SLAVE  = 0,                /*!< PDM Role Slave    */
    PDM_ROLE_MASTER,                    /*!< PDM Role Master   */
} PDM_RoleETypeDef;

/**
  * @brief PDM Data Filter Output Data Length Definition
  */
typedef enum {
    PDM_DAT_FIL_DAT_LEN_16BIT = 0,      /*!< PDM Data Filter Output Data Length 16Bit   */
    PDM_DAT_FIL_DAT_LEN_24BIT,          /*!< PDM Data Filter Output Data Length 24Bit   */
} PDM_DatFil_DatLenETypeDef;

/**
  * @brief PDM Data/Comparator Filter Structure Definition
  */
typedef enum {
    PDM_FIL_STRU_FAST_SINC = 0,         /*!< PDM Data/Comparator Filter Structure Fast Sinc */
    PDM_FIL_STRU_SINC1,                 /*!< PDM Data/Comparator Filter Structure Sinc1     */
    PDM_FIL_STRU_SINC2,                 /*!< PDM Data/Comparator Filter Structure Sinc2     */
    PDM_FIL_STRU_SINC3,                 /*!< PDM Data/Comparator Filter Structure Sinc3     */
    PDM_FIL_STRU_SINC4,                 /*!< PDM Data/Comparator Filter Structure Sinc4     */
} PDM_FilStruETypeDef;

/**
  * @brief PDM Comparator Filter Output Definition
  */
typedef enum {
    PDM_CMP_FIL_OUT_CMPL_CMPH_SEP = 0,  /*!< PDM Comparator Filter Output CMPL/CMPH Separate    */
    PDM_CMP_FIL_OUT_CMPL_CMPH_OR,       /*!< PDM Comparator Filter Output CMPL/CMPH OR          */
} PDM_CmpFil_OutputETypeDef;

/**
  * @brief PDM SDSYNC Event Definition
  */
typedef enum {
    PDM_SDSYNC_EVT_ADCTRIG0 = 0,        /*!< PDM SDSYNC Event HRPWM ADCTRIG0    */
    PDM_SDSYNC_EVT_ADCTRIG1,            /*!< PDM SDSYNC Event HRPWM ADCTRIG1    */
    PDM_SDSYNC_EVT_TMR7_TRGO,           /*!< PDM SDSYNC Event TMR7_TRGO         */
    PDM_SDSYNC_EVT_TMR8_TRGO,           /*!< PDM SDSYNC Event TMR8_TRGO         */

    PDM_SDSYNC_EVT_ADCTRIG2,            /*!< PDM SDSYNC Event HRPWM ADCTRIG2    */
    PDM_SDSYNC_EVT_ADCTRIG3,            /*!< PDM SDSYNC Event HRPWM ADCTRIG3    */
    PDM_SDSYNC_EVT_TMR0_CC0,            /*!< PDM SDSYNC Event TMR0_CC0          */
    PDM_SDSYNC_EVT_TMR0_TRGO,           /*!< PDM SDSYNC Event TMR0_TRGO         */

    PDM_SDSYNC_EVT_ADCTRIG4,            /*!< PDM SDSYNC Event HRPWM ADCTRIG4    */
    PDM_SDSYNC_EVT_ADCTRIG5,            /*!< PDM SDSYNC Event HRPWM ADCTRIG5    */
    PDM_SDSYNC_EVT_TMR1_CC0,            /*!< PDM SDSYNC Event TMR1_CC0          */
    PDM_SDSYNC_EVT_TMR1_TRGO,           /*!< PDM SDSYNC Event TMR1_TRGO         */

    PDM_SDSYNC_EVT_ADCTRIG6,            /*!< PDM SDSYNC Event HRPWM ADCTRIG6    */
    PDM_SDSYNC_EVT_ADCTRIG7,            /*!< PDM SDSYNC Event HRPWM ADCTRIG7    */
    PDM_SDSYNC_EVT_TMR2_CC0,            /*!< PDM SDSYNC Event TMR2_CC0          */
    PDM_SDSYNC_EVT_TMR2_TRGO,           /*!< PDM SDSYNC Event TMR2_TRGO         */

    PDM_SDSYNC_EVT_ADCTRIG8,            /*!< PDM SDSYNC Event HRPWM ADCTRIG8    */
    PDM_SDSYNC_EVT_ADCTRIG9,            /*!< PDM SDSYNC Event HRPWM ADCTRIG9    */
    PDM_SDSYNC_EVT_TMR3_CC0,            /*!< PDM SDSYNC Event TMR3_CC0          */
    PDM_SDSYNC_EVT_TMR3_TRGO,           /*!< PDM SDSYNC Event TMR3_TRGO         */

    PDM_SDSYNC_EVT_DACTRIG0 = 0x15,     /*!< PDM SDSYNC Event HRPWM DACTRIG0    */
    PDM_SDSYNC_EVT_TMR4_CC0,            /*!< PDM SDSYNC Event TMR4_CC0          */
    PDM_SDSYNC_EVT_TMR4_TRGO,           /*!< PDM SDSYNC Event TMR4_TRGO         */

    PDM_SDSYNC_EVT_DACTRIG1 = 0x19,     /*!< PDM SDSYNC Event HRPWM DACTRIG1    */
    PDM_SDSYNC_EVT_TMR9_CC0,            /*!< PDM SDSYNC Event TMR9_CC0          */
    PDM_SDSYNC_EVT_TMR9_TRGO,           /*!< PDM SDSYNC Event TMR9_TRGO         */

    PDM_SDSYNC_EVT_DACTRIG2 = 0x1d,     /*!< PDM SDSYNC Event HRPWM DACTRIG2    */
    PDM_SDSYNC_EVT_TMR10_CC0,           /*!< PDM SDSYNC Event TMR10_CC0         */
    PDM_SDSYNC_EVT_TMR10_TRGO,          /*!< PDM SDSYNC Event TMR10_TRGO        */
} PDM_SDSYNC_EvtETypeDef;


/**
  * @brief PDM Data Filter Initialization Related Configuration Definition
  */
typedef struct __PDM_DatFil_InitTypeDef {
    //Common Config
    bool     enable;                        /*!< Data Filter Enable                         */
    bool     bypass_en;                     /*!< Data Filter BypPass Enable                 */
    uint8_t  shift_bit;                     /*!< Shift Control bit, set when output 16bit   */
    uint16_t over_sample_rate;              /*!< Over Sample Rate: 1~256                    */

    PDM_FilStruETypeDef       fil_stru;     /*!< Filter Structure                           */
    PDM_DatFil_DatLenETypeDef dat_len;      /*!< Output Data Length                         */

    //SDSYNC Config
    bool sdsync_en;                         /*!< SDSYNC Enable                              */
    PDM_SDSYNC_EvtETypeDef sync_evt;        /*!< Synchronous event signal selection         */
} PDM_DatFil_InitTypeDef;

/**
  * @brief PDM Comparator Filter Initialization Related Configuration Definition
  */
typedef struct __PDM_CmpFil_InitTypeDef {
    bool     enable;                        /*!< Comparator Filter Enable               */
    bool     bypass_en;                     /*!< Comparator Filter BypPass Enable       */
    uint8_t  over_sample_rate;              /*!< Over Sample Rate: 1~32                 */
    uint16_t high_lvl_thres;                /*!< High level threshold: 0x0 to 0xffff    */
    uint16_t low_lvl_thres;                 /*!< Low level threshold: 0x0 to 0xffff     */

    PDM_FilStruETypeDef       fil_stru;     /*!< Filter Structure                       */
    PDM_CmpFil_OutputETypeDef output;       /*!< output signal select                   */
} PDM_CmpFil_InitTypeDef;

/**
  * @brief PDM LL Initialization Related Configuration Definition
  */
typedef struct __PDM_LLCfgTypeDef {
    //PDM Common Config
    uint8_t  mst_rx_delay;                  /*!< Rx delay system clock period: 0x0~0x7  */
    uint32_t slv_clk_timeout;               /*!< Slave clock timeout: 0x0 to 0x3ffff    */

    //Data Filter Config
    uint8_t fifo_full_thres;                /*!< FIFO Full Threshold                    */
    bool fifo_w_sync_en;                    /*!< FIFO Write Sync with WTSYNFLG Enable   */
    bool fifo_rst_sync_en;                  /*!< FIFO Reset with WTSYNFLG Enable        */
    bool fifo_full_clr_sync_en;             /*!< FIFO Full Clear WTSYNFLG Enable        */
} PDM_LLCfgypeDef;


/**
  * @brief PDM Data Filter Initialization Related Configuration Definition
  */
typedef struct __PDM_InitTypeDef {
    //Comon Config
    bool                   dma_en;              /*!< DMA Enable                 */
    PDM_RoleETypeDef       role;                /*!< Master or Slave            */
    PDM_InputModeETypeDef  input_mode;          /*!< Input Mode                 */
    PDM_DatFil_InitTypeDef dat_fil_init;        /*!< Data Filter Init           */
    PDM_CmpFil_InitTypeDef cmp_fil_init;        /*!< Comparator Filter Init     */
    PDM_LLCfgypeDef       *ll_cfg;              /*!< Optional LL Config Pointer */

    //Master Config
    uint32_t mst_baudrate;                      /*!< Master baudrate            */
    PDM_SerialClkPolETypeDef mst_sclk_pol;      /*!< Master SCLK Polarity       */

    //Slave Config
    PDM_Slv_SampleEdgeETypeDef slv_sample_edge; /*!< Slave sample edge          */
} PDM_InitTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup PDM_LL_Exported_Functions
  * @{
  */

/** @addtogroup PDM_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_PDM_Init(PDM_TypeDef *Instance, PDM_InitTypeDef *init);
LL_StatusETypeDef LL_PDM_DeInit(PDM_TypeDef *Instance);
void LL_PDM_MspInit(PDM_TypeDef *Instance);
void LL_PDM_MspDeInit(PDM_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup PDM_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_PDM_DatFil_Cfg(PDM_TypeDef *Instance, PDM_DatFil_InitTypeDef *cfg);
LL_StatusETypeDef LL_PDM_CmpFil_Cfg(PDM_TypeDef *Instance, PDM_CmpFil_InitTypeDef *cfg);
/**
  * @}
  */


/** @addtogroup PDM_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_PDM_En(PDM_TypeDef *Instance);
LL_StatusETypeDef LL_PDM_Dis(PDM_TypeDef *Instance);
uint32_t LL_PDM_SwInputDat_Write(PDM_TypeDef *Instance, uint16_t *buf, uint32_t size);
/**
  * @}
  */


/** @addtogroup PDM_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_PDM_IRQHandler(PDM_TypeDef *Instance);

void LL_PDM_DatFil_FIFOUnderflowCallback(PDM_TypeDef *Instance);
void LL_PDM_Slv_ClkTimeOutCallback(PDM_TypeDef *Instance);
void LL_PDM_DatFil_FIFOFullCallback(PDM_TypeDef *Instance);
void LL_PDM_DatFil_FIFOOverflowCallback(PDM_TypeDef *Instance);
void LL_PDM_CmpFil_DatOverFlowCallback(PDM_TypeDef *Instance);
void LL_PDM_CmpFil_DatFinishCallback(PDM_TypeDef *Instance);
void LL_PDM_CmpFil_LowLvlCallback(PDM_TypeDef *Instance);
void LL_PDM_CmpFil_HighLvlCallback(PDM_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_PDM_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

