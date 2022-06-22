/**************************************************************************//**
 * @file     nu_qei.h
 * @version  V3.00
 * @brief    Quadrature Encoder Interface (QEI) driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_QEI_H__
#define __NU_QEI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup QEI_Driver QEI Driver
  @{
*/

/** @addtogroup QEI_EXPORTED_CONSTANTS QEI Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* QEI counting mode selection constants definitions                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define QEI_CTL_X4_FREE_COUNTING_MODE       (0x0<<QEI_CTL_MODE_Pos) /*!< QEI operate in X4 free-counting mode \hideinitializer */
#define QEI_CTL_X2_FREE_COUNTING_MODE       (0x1<<QEI_CTL_MODE_Pos) /*!< QEI operate in X2 free-counting mode \hideinitializer */
#define QEI_CTL_X4_COMPARE_COUNTING_MODE    (0x2<<QEI_CTL_MODE_Pos) /*!< QEI operate in X4 compare-counting mode \hideinitializer */
#define QEI_CTL_X2_COMPARE_COUNTING_MODE    (0x3<<QEI_CTL_MODE_Pos) /*!< QEI operate in X2 compare-counting mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* QEI noise filter clock pre-divide selection constants definitions                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define QEI_CTL_NFCLKSEL_DIV1   (0x0<<QEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is QEI_CLK \hideinitializer */
#define QEI_CTL_NFCLKSEL_DIV2   (0x1<<QEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is QEI_CLK/2 \hideinitializer */
#define QEI_CTL_NFCLKSEL_DIV4   (0x2<<QEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is QEI_CLK/4 \hideinitializer */
#define QEI_CTL_NFCLKSEL_DIV16  (0x3<<QEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is QEI_CLK/16 \hideinitializer */
#define QEI_CTL_NFCLKSEL_DIV32  (0x4<<QEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is QEI_CLK/32 \hideinitializer */
#define QEI_CTL_NFCLKSEL_DIV64  (0x5<<QEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is QEI_CLK/64 \hideinitializer */




/*@}*/ /* end of group QEI_EXPORTED_CONSTANTS */


/** @addtogroup QEI_EXPORTED_FUNCTIONS QEI Exported Functions
  @{
*/

/**
  * @brief      Disable QEI compare function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This macro disable QEI counter compare function.
  * \hideinitializer
  */
#define QEI_DISABLE_CNT_CMP(qei)    ((qei)->CTL &= (~QEI_CTL_CMPEN_Msk))

/**
  * @brief      Enable QEI compare function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This macro enable QEI counter compare function.
  * \hideinitializer
  */
#define QEI_ENABLE_CNT_CMP(qei)     ((qei)->CTL |= QEI_CTL_CMPEN_Msk)

/**
  * @brief      Disable QEI index latch function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This macro disable QEI index trigger counter latch function.
  * \hideinitializer
  */
#define QEI_DISABLE_INDEX_LATCH(qei)     ((qei)->CTL &= (~QEI_CTL_IDXLATEN_Msk))

/**
  * @brief      Enable QEI index latch function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This macro enable QEI index trigger counter latch function.
  * \hideinitializer
  */
#define QEI_ENABLE_INDEX_LATCH(qei)     ((qei)->CTL |= QEI_CTL_IDXLATEN_Msk)

/**
  * @brief      Disable QEI index reload function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This macro disable QEI index trigger counter reload function.
  * \hideinitializer
  */
#define QEI_DISABLE_INDEX_RELOAD(qei)    ((qei)->CTL &= (~QEI_CTL_IDXRLDEN_Msk))

/**
  * @brief      Enable QEI index reload function
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     None
  * @details    This macro enable QEI index trigger counter reload function.
  * \hideinitializer
  */
#define QEI_ENABLE_INDEX_RELOAD(qei)    ((qei)->CTL |= QEI_CTL_IDXRLDEN_Msk)

/**
  * @brief      Disable QEI input
  * @param[in]  qei             The pointer of the specified QEI module.
  * @param[in]  u32InputType    Input signal type.
  *                             - \ref QEI_CTL_CHAEN_Msk    : QEA input
  *                             - \ref QEI_CTL_CHAEN_Msk    : QEB input
  *                             - \ref QEI_CTL_IDXEN_Msk    : IDX input
  * @return     None
  * @details    This macro disable specified QEI signal input.
  * \hideinitializer
  */
#define QEI_DISABLE_INPUT(qei, u32InputType)     ((qei)->CTL &= ~(u32InputType))

/**
  * @brief      Enable QEI input
  * @param[in]  qei             The pointer of the specified QEI module.
  * @param[in]  u32InputType    Input signal type .
  *                             - \ref QEI_CTL_CHAEN_Msk    : QEA input
  *                             - \ref QEI_CTL_CHBEN_Msk    : QEB input
  *                             - \ref QEI_CTL_IDXEN_Msk    : IDX input
  * @return     None
  * @details    This macro enable specified QEI signal input.
  * \hideinitializer
  */
#define QEI_ENABLE_INPUT(qei, u32InputType)     ((qei)->CTL |= (u32InputType))

/**
  * @brief      Disable inverted input polarity
  * @param[in]  qei             The pointer of the specified QEI module.
  * @param[in]  u32InputType    Input signal type .
  *                             - \ref QEI_CTL_CHAINV_Msk   : QEA Input
  *                             - \ref QEI_CTL_CHBINV_Msk   : QEB Input
  *                             - \ref QEI_CTL_IDXINV_Msk   : IDX Input
  * @return     None
  * @details    This macro disable specified QEI signal inverted input polarity.
  * \hideinitializer
  */
#define QEI_DISABLE_INPUT_INV(qei, u32InputType)    ((qei)->CTL &= ~(u32InputType))

/**
  * @brief      Enable inverted input polarity
  * @param[in]  qei             The pointer of the specified QEI module.
  * @param[in]  u32InputType    Input signal type.
  *                             - \ref QEI_CTL_CHAINV_Msk   : QEA Input
  *                             - \ref QEI_CTL_CHBINV_Msk   : QEB Input
  *                             - \ref QEI_CTL_IDXINV_Msk   : IDX Input
  * @return     None
  * @details    This macro inverse specified QEI signal input polarity.
  * \hideinitializer
  */
#define QEI_ENABLE_INPUT_INV(qei, u32InputType)     ((qei)->CTL |= (u32InputType))

/**
  * @brief      Disable QEI interrupt
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref QEI_CTL_DIRIEN_Msk   : Direction change interrupt
  *                         - \ref QEI_CTL_OVUNIEN_Msk  : Counter overflow or underflow interrupt
  *                         - \ref QEI_CTL_CMPIEN_Msk   : Compare-match interrupt
  *                         - \ref QEI_CTL_IDXIEN_Msk   : Index detected interrupt
  * @return     None
  * @details    This macro disable specified QEI interrupt.
  * \hideinitializer
  */
#define QEI_DISABLE_INT(qei, u32IntSel)     ((qei)->CTL &= ~(u32IntSel))

/**
  * @brief      Enable QEI interrupt
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref QEI_CTL_DIRIEN_Msk   : Direction change interrupt
  *                         - \ref QEI_CTL_OVUNIEN_Msk  : Counter overflow or underflow interrupt
  *                         - \ref QEI_CTL_CMPIEN_Msk   : Compare-match interrupt
  *                         - \ref QEI_CTL_IDXIEN_Msk   : Index detected interrupt
  * @return     None
  * @details    This macro enable specified QEI interrupt.
  * \hideinitializer
  */
#define QEI_ENABLE_INT(qei, u32IntSel)      ((qei)->CTL |= (u32IntSel))

/**
  * @brief      Disable QEI noise filter
  * @param[in]  qei         The pointer of the specified QEI module.
  * @return     None
  * @details    This macro disable QEI noise filter function.
  * \hideinitializer
  */
#define QEI_DISABLE_NOISE_FILTER(qei)       ((qei)->CTL |= QEI_CTL_NFDIS_Msk)

/**
  * @brief      Enable QEI noise filter
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32ClkSel   The sampling frequency of the noise filter clock.
  *                         - \ref QEI_CTL_NFCLKSEL_DIV1
  *                         - \ref QEI_CTL_NFCLKSEL_DIV2
  *                         - \ref QEI_CTL_NFCLKSEL_DIV4
  *                         - \ref QEI_CTL_NFCLKSEL_DIV16
  *                         - \ref QEI_CTL_NFCLKSEL_DIV32
  *                         - \ref QEI_CTL_NFCLKSEL_DIV64
  * @return     None
  * @details    This macro enable QEI noise filter function and select noise filter clock.
  * \hideinitializer
  */
#define QEI_ENABLE_NOISE_FILTER(qei, u32ClkSel)     ((qei)->CTL = ((qei)->CTL & (~(QEI_CTL_NFDIS_Msk|QEI_CTL_NFCLKSEL_Msk))) | (u32ClkSel))

/**
  * @brief      Get QEI counter value
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     QEI pulse counter register value.
  * @details    This macro get QEI pulse counter value.
  * \hideinitializer
  */
#define QEI_GET_CNT_VALUE(qei)      ((qei)->CNT)

/**
  * @brief      Get QEI counting direction
  * @param[in]  qei     The pointer of the specified QEI module.
  * @retval     0       QEI counter is in down-counting.
  * @retval     1       QEI counter is in up-counting.
  * @details    This macro get QEI counting direction.
  * \hideinitializer
  */
#define QEI_GET_DIR(qei)    (((qei)->STATUS & (QEI_STATUS_DIRF_Msk))?1:0)

/**
  * @brief      Get QEI counter hold value
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     QEI pulse counter hold register value.
  * @details    This macro get QEI pulse counter hold value, which is updated with counter value in hold counter value control.
  * \hideinitializer
  */
#define QEI_GET_HOLD_VALUE(qei)     ((qei)->CNTHOLD)

/**
  * @brief      Get QEI counter index latch value
  * @param[in]  qei     The pointer of the specified QEI module.
  * @return     QEI pulse counter index latch value
  * @details    This macro get QEI pulse counter index latch value, which is updated with counter value when the index is detected.
  * \hideinitializer
  */
#define QEI_GET_INDEX_LATCH_VALUE(qei)     ((qei)->CNTLATCH)

/**
  * @brief      Set QEI counter index latch value
  * @param[in]  qei     The pointer of the specified QEI module.
  * @param[in]  u32Val  The latch value.
  * @return     QEI pulse counter index latch value
  * @details    This macro set QEI pulse counter index latch value, which is updated with counter value when the index is detected.
  * \hideinitializer
  */
#define QEI_SET_INDEX_LATCH_VALUE(qei,u32Val)     ((qei)->CNTLATCH = (u32Val))

/**
  * @brief      Get QEI interrupt flag status
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
*                           - \ref QEI_STATUS_DIRF_Msk      : Counting direction flag
  *                         - \ref QEI_STATUS_DIRCHGF_Msk   : Direction change flag
  *                         - \ref QEI_STATUS_OVUNF_Msk     : Counter overflow or underflow flag
  *                         - \ref QEI_STATUS_CMPF_Msk      : Compare-match flag
  *                         - \ref QEI_STATUS_IDXF_Msk      : Index detected flag
  * @retval     0           QEI specified interrupt flag is not set.
  * @retval     1           QEI specified interrupt flag is set.
  * @details    This macro get QEI specified interrupt flag status.
  * \hideinitializer
  */
#define QEI_GET_INT_FLAG(qei, u32IntSel)        (((qei)->STATUS & (u32IntSel))?1:0)


/**
  * @brief      Clear QEI interrupt flag
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref QEI_STATUS_DIRCHGF_Msk   : Direction change flag
  *                         - \ref QEI_STATUS_OVUNF_Msk     : Counter overflow or underflow flag
  *                         - \ref QEI_STATUS_CMPF_Msk      : Compare-match flag
  *                         - \ref QEI_STATUS_IDXF_Msk      : Index detected flag
  * @return     None
  * @details    This macro clear QEI specified interrupt flag.
  * \hideinitializer
  */
#define QEI_CLR_INT_FLAG(qei, u32IntSel)     ((qei)->STATUS = (u32IntSel))

/**
  * @brief      Set QEI counter compare value
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32Value    The counter compare value.
  * @return     None
  * @details    This macro set QEI pulse counter compare value.
  * \hideinitializer
  */
#define QEI_SET_CNT_CMP(qei, u32Value)      ((qei)->CNTCMP = (u32Value))

/**
  * @brief      Set QEI counter value
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32Value    The counter compare value.
  * @return     None
  * @details    This macro set QEI pulse counter value.
  * \hideinitializer
  */
#define QEI_SET_CNT_VALUE(qei, u32Value)      ((qei)->CNT = (u32Value))

/**
  * @brief      Enable QEI counter hold mode
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32Type     The triggered type.
  *                         - \ref QEI_CTL_HOLDCNT_Msk      : Hold QEI_CNT control
  *                         - \ref QEI_CTL_HOLDTMR0_Msk     : Hold QEI_CNT by Timer0
  *                         - \ref QEI_CTL_HOLDTMR1_Msk     : Hold QEI_CNT by Timer1
  *                         - \ref QEI_CTL_HOLDTMR2_Msk     : Hold QEI_CNT by Timer2
  *                         - \ref QEI_CTL_HOLDTMR3_Msk     : Hold QEI_CNT by Timer3
  * @return     None
  * @details    This macro enable QEI counter hold mode.
  * \hideinitializer
  */
#define QEI_ENABLE_HOLD_TRG_SRC(qei, u32Type)      ((qei)->CTL |= (u32Type))

/**
  * @brief      Disable QEI counter hold mode
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32Type     The triggered type.
  *                         - \ref QEI_CTL_HOLDCNT_Msk      : Hold QEI_CNT control
  *                         - \ref QEI_CTL_HOLDTMR0_Msk     : Hold QEI_CNT by Timer0
  *                         - \ref QEI_CTL_HOLDTMR1_Msk     : Hold QEI_CNT by Timer1
  *                         - \ref QEI_CTL_HOLDTMR2_Msk     : Hold QEI_CNT by Timer2
  *                         - \ref QEI_CTL_HOLDTMR3_Msk     : Hold QEI_CNT by Timer3
  * @return     None
  * @details    This macro disable QEI counter hold mode.
  * \hideinitializer
  */
#define QEI_DISABLE_HOLD_TRG_SRC(qei, u32Type)      ((qei)->CTL &= ~(u32Type))

/**
  * @brief      Set QEI maximum count value
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32Value    The counter maximum value.
  * @return     QEI maximum count value
  * @details    This macro set QEI maximum count value.
  * \hideinitializer
  */
#define QEI_SET_CNT_MAX(qei, u32Value)      ((qei)->CNTMAX = (u32Value))

/**
  * @brief      Set QEI counting mode
  * @param[in]  qei         The pointer of the specified QEI module.
  * @param[in]  u32Mode     QEI counting mode.
  *                         - \ref QEI_CTL_X4_FREE_COUNTING_MODE
  *                         - \ref QEI_CTL_X2_FREE_COUNTING_MODE
  *                         - \ref QEI_CTL_X4_COMPARE_COUNTING_MODE
  *                         - \ref QEI_CTL_X2_COMPARE_COUNTING_MODE
  * @return     None
  * @details    This macro set QEI counting mode.
  * \hideinitializer
  */
#define QEI_SET_CNT_MODE(qei, u32Mode)       ((qei)->CTL = ((qei)->CTL & (~QEI_CTL_MODE_Msk)) | (u32Mode))


void QEI_Close(QEI_T* qei);
void QEI_DisableInt(QEI_T* qei, uint32_t u32IntSel);
void QEI_EnableInt(QEI_T* qei, uint32_t u32IntSel);
void QEI_Open(QEI_T* qei, uint32_t u32Mode, uint32_t u32Value);
void QEI_Start(QEI_T* qei);
void QEI_Stop(QEI_T* qei);


/*@}*/ /* end of group QEI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group QEI_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_QEI_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
