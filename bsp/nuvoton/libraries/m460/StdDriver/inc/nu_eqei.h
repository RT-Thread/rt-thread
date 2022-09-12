/**************************************************************************//**
 * @file     nu_eqei.h
 * @version  V3.00
 * @brief    Enhanced Quadrature Encoder Interface (EQEI) driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_EQEI_H__
#define __NU_EQEI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EQEI_Driver EQEI Driver
  @{
*/

/** @addtogroup EQEI_EXPORTED_CONSTANTS EQEI Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* EQEI counting mode selection constants definitions                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define EQEI_CTL_X4_FREE_COUNTING_MODE       (0x0<<EQEI_CTL_MODE_Pos) /*!<EQEI operate in X4 free-counting mode      \hideinitializer */
#define EQEI_CTL_X2_FREE_COUNTING_MODE       (0x1<<EQEI_CTL_MODE_Pos) /*!<EQEI operate in X2 free-counting mode      \hideinitializer */
#define EQEI_CTL_X4_COMPARE_COUNTING_MODE    (0x2<<EQEI_CTL_MODE_Pos) /*!<EQEI operate in X4 compare-counting mode   \hideinitializer */
#define EQEI_CTL_X2_COMPARE_COUNTING_MODE    (0x3<<EQEI_CTL_MODE_Pos) /*!<EQEI operate in X2 compare-counting mode   \hideinitializer */
#define EQEI_CTL_PHASE_COUNTING_MODE_TYPE1   (0x4<<EQEI_CTL_MODE_Pos) /*!<EQEI operate in phase counting mode type 1 \hideinitializer */
#define EQEI_CTL_PHASE_COUNTING_MODE_TYPE2   (0x5<<EQEI_CTL_MODE_Pos) /*!<EQEI operate in phase counting mode type 1 \hideinitializer */
#define EQEI_CTL_DIRECTIONAL_COUNTING_MODE   (0x6<<EQEI_CTL_MODE_Pos) /*!<EQEI operate in directional counting mode  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EQEI noise filter clock pre-divide selection constants definitions                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define EQEI_CTL_NFCLKSEL_DIV1   (0x0<<EQEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is EQEI_CLK    \hideinitializer */
#define EQEI_CTL_NFCLKSEL_DIV2   (0x1<<EQEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is EQEI_CLK/2  \hideinitializer */
#define EQEI_CTL_NFCLKSEL_DIV4   (0x2<<EQEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is EQEI_CLK/4  \hideinitializer */
#define EQEI_CTL_NFCLKSEL_DIV16  (0x3<<EQEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is EQEI_CLK/16 \hideinitializer */
#define EQEI_CTL_NFCLKSEL_DIV32  (0x4<<EQEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is EQEI_CLK/32 \hideinitializer */
#define EQEI_CTL_NFCLKSEL_DIV64  (0x5<<EQEI_CTL_NFCLKSEL_Pos) /*!< The sampling frequency of the noise filter is EQEI_CLK/64 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EQEI Clock Rate Setting without Quadrature Mode definitions                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define EQEI_CTL2_X1_COUNT_FALLING             (0x0<<EQEI_CTL2_CRS_Pos)  /*!<EQEI counter only counts the falling edge       \hideinitializer */
#define EQEI_CTL2_X1_COUNT_RISING              (0x1<<EQEI_CTL2_CRS_Pos)  /*!<EQEI counter only counts the rising  edge       \hideinitializer */
#define EQEI_CTL2_X2_COUNT_FALLING_AND_RISING  (0x2<<EQEI_CTL2_CRS_Pos)  /*!<EQEI counter counts the rising and falling edge \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/* EQEI Direction Signal Source Select definitions                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#define EQEI_CTL2_DIRCTION_FROM_EQEI_CALC   (0x0<<EQEI_CTL2_DIRSRC_Pos)  /*!<Direction signal is determined from EQEI system calculation   \hideinitializer */
#define EQEI_CTL2_DIRCTION_TIED_HIGH        (0x2<<EQEI_CTL2_DIRSRC_Pos)  /*!<Direction signal is tied 1 only for direction up count mode   \hideinitializer */
#define EQEI_CTL2_DIRCTION_TIED_LOW         (0x3<<EQEI_CTL2_DIRSRC_Pos)  /*!<Direction signal is tied 0 only for direction down count mode \hideinitializer */

/*@}*/ /* end of group EQEI_EXPORTED_CONSTANTS */


/** @addtogroup EQEI_EXPORTED_FUNCTIONS EQEI Exported Functions
  @{
*/

/**
  * @brief      Disable EQEI compare function
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     None
  * @details    This macro disable EQEI counter compare function.
  * \hideinitializer
  */
#define EQEI_DISABLE_CNT_CMP(eqei)    ((eqei)->CTL &= (~EQEI_CTL_CMPEN_Msk))

/**
  * @brief      Enable EQEI compare function
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     None
  * @details    This macro enable EQEI counter compare function.
  * \hideinitializer
  */
#define EQEI_ENABLE_CNT_CMP(eqei)     ((eqei)->CTL |= EQEI_CTL_CMPEN_Msk)

/**
  * @brief      Disable EQEI index latch function
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     None
  * @details    This macro disable EQEI index trigger counter latch function.
  * \hideinitializer
  */
#define EQEI_DISABLE_INDEX_LATCH(eqei)     ((eqei)->CTL &= (~EQEI_CTL_IDXLATEN_Msk))

/**
  * @brief      Enable EQEI index latch function
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     None
  * @details    This macro enable EQEI index trigger counter latch function.
  * \hideinitializer
  */
#define EQEI_ENABLE_INDEX_LATCH(eqei)     ((eqei)->CTL |= EQEI_CTL_IDXLATEN_Msk)

/**
  * @brief      Disable EQEI index reload function
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     None
  * @details    This macro disable EQEI index trigger counter reload function.
  * \hideinitializer
  */
#define EQEI_DISABLE_INDEX_RELOAD(eqei)    ((eqei)->CTL &= (~EQEI_CTL_IDXRLDEN_Msk))

/**
  * @brief      Enable EQEI index reload function
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     None
  * @details    This macro enable EQEI index trigger counter reload function.
  * \hideinitializer
  */
#define EQEI_ENABLE_INDEX_RELOAD(eqei)    ((eqei)->CTL |= EQEI_CTL_IDXRLDEN_Msk)

/**
  * @brief      Disable EQEI input
  * @param[in]  eqei             The pointer of the specified EQEI module.
  * @param[in]  u32InputType    Input signal type.
  *                             - \ref EQEI_CTL_CHAEN_Msk    : QEA input
  *                             - \ref EQEI_CTL_CHAEN_Msk    : QEB input
  *                             - \ref EQEI_CTL_IDXEN_Msk    : IDX input
  * @return     None
  * @details    This macro disable specified EQEI signal input.
  * \hideinitializer
  */
#define EQEI_DISABLE_INPUT(eqei, u32InputType)     ((eqei)->CTL &= ~(u32InputType))

/**
  * @brief      Enable EQEI input
  * @param[in]  eqei             The pointer of the specified EQEI module.
  * @param[in]  u32InputType    Input signal type .
  *                             - \ref EQEI_CTL_CHAEN_Msk    : QEA input
  *                             - \ref EQEI_CTL_CHBEN_Msk    : QEB input
  *                             - \ref EQEI_CTL_IDXEN_Msk    : IDX input
  * @return     None
  * @details    This macro enable specified EQEI signal input.
  * \hideinitializer
  */
#define EQEI_ENABLE_INPUT(eqei, u32InputType)     ((eqei)->CTL |= (u32InputType))

/**
  * @brief      Disable inverted input polarity
  * @param[in]  eqei             The pointer of the specified EQEI module.
  * @param[in]  u32InputType    Input signal type .
  *                             - \ref EQEI_CTL_CHAINV_Msk   : QEA Input
  *                             - \ref EQEI_CTL_CHBINV_Msk   : QEB Input
  *                             - \ref EQEI_CTL_IDXINV_Msk   : IDX Input
  * @return     None
  * @details    This macro disable specified EQEI signal inverted input polarity.
  * \hideinitializer
  */
#define EQEI_DISABLE_INPUT_INV(eqei, u32InputType)    ((eqei)->CTL &= ~(u32InputType))

/**
  * @brief      Enable inverted input polarity
  * @param[in]  eqei             The pointer of the specified EQEI module.
  * @param[in]  u32InputType    Input signal type.
  *                             - \ref EQEI_CTL_CHAINV_Msk   : QEA Input
  *                             - \ref EQEI_CTL_CHBINV_Msk   : QEB Input
  *                             - \ref EQEI_CTL_IDXINV_Msk   : IDX Input
  * @return     None
  * @details    This macro inverse specified EQEI signal input polarity.
  * \hideinitializer
  */
#define EQEI_ENABLE_INPUT_INV(eqei, u32InputType)     ((qei)->CTL |= (u32InputType))

/**
  * @brief      Disable EQEI interrupt
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref EQEI_CTL_DIRIEN_Msk   : Direction change interrupt
  *                         - \ref EQEI_CTL_OVUNIEN_Msk  : Counter overflow or underflow interrupt
  *                         - \ref EQEI_CTL_CMPIEN_Msk   : Compare-match interrupt
  *                         - \ref EQEI_CTL_IDXIEN_Msk   : Index detected interrupt
  * @return     None
  * @details    This macro disable specified EQEI interrupt.
  * \hideinitializer
  */
#define EQEI_DISABLE_INT(eqei, u32IntSel)     ((eqei)->CTL &= ~(u32IntSel))

/**
  * @brief      Enable EQEI interrupt
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref EQEI_CTL_DIRIEN_Msk   : Direction change interrupt
  *                         - \ref EQEI_CTL_OVUNIEN_Msk  : Counter overflow or underflow interrupt
  *                         - \ref EQEI_CTL_CMPIEN_Msk   : Compare-match interrupt
  *                         - \ref EQEI_CTL_IDXIEN_Msk   : Index detected interrupt
  * @return     None
  * @details    This macro enable specified EQEI interrupt.
  * \hideinitializer
  */
#define EQEI_ENABLE_INT(eqei, u32IntSel)      ((eqei)->CTL |= (u32IntSel))

/**
  * @brief      Disable EQEI noise filter
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @return     None
  * @details    This macro disable EQEI noise filter function.
  * \hideinitializer
  */
#define EQEI_DISABLE_NOISE_FILTER(eqei)       ((eqei)->CTL |= EQEI_CTL_NFDIS_Msk)

/**
  * @brief      Enable EQEI noise filter
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32ClkSel   The sampling frequency of the noise filter clock.
  *                         - \ref EQEI_CTL_NFCLKSEL_DIV1
  *                         - \ref EQEI_CTL_NFCLKSEL_DIV2
  *                         - \ref EQEI_CTL_NFCLKSEL_DIV4
  *                         - \ref EQEI_CTL_NFCLKSEL_DIV16
  *                         - \ref EQEI_CTL_NFCLKSEL_DIV32
  *                         - \ref EQEI_CTL_NFCLKSEL_DIV64
  * @return     None
  * @details    This macro enable EQEI noise filter function and select noise filter clock.
  * \hideinitializer
  */
#define EQEI_ENABLE_NOISE_FILTER(eqei, u32ClkSel)     ((eqei)->CTL = ((eqei)->CTL & (~(EQEI_CTL_NFDIS_Msk|EQEI_CTL_NFCLKSEL_Msk))) | (u32ClkSel))

/**
  * @brief      Get EQEI counter value
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     EQEI pulse counter register value.
  * @details    This macro get EQEI pulse counter value.
  * \hideinitializer
  */
#define EQEI_GET_CNT_VALUE(eqei)      ((eqei)->CNT)

/**
  * @brief      Get EQEI counting direction
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @retval     0       EQEI counter is in down-counting.
  * @retval     1       EQEI counter is in up-counting.
  * @details    This macro get EQEI counting direction.
  * \hideinitializer
  */
#define EQEI_GET_DIR(eqei)    (((eqei)->STATUS & (EQEI_STATUS_DIRF_Msk))?1:0)

/**
  * @brief      Get EQEI counter hold value
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     EQEI pulse counter hold register value.
  * @details    This macro get EQEI pulse counter hold value, which is updated with counter value in hold counter value control.
  * \hideinitializer
  */
#define EQEI_GET_HOLD_VALUE(eqei)     ((eqei)->CNTHOLD)

/**
  * @brief      Get EQEI counter index latch value
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @return     EQEI pulse counter index latch value
  * @details    This macro get EQEI pulse counter index latch value, which is updated with counter value when the index is detected.
  * \hideinitializer
  */
#define EQEI_GET_INDEX_LATCH_VALUE(eqei)     ((eqei)->CNTLATCH)

/**
  * @brief      Set EQEI counter index latch value
  * @param[in]  eqei     The pointer of the specified EQEI module.
  * @param[in]  u32Val  The latch value.
  * @return     EQEI pulse counter index latch value
  * @details    This macro set EQEI pulse counter index latch value, which is updated with counter value when the index is detected.
  * \hideinitializer
  */
#define EQEI_SET_INDEX_LATCH_VALUE(eqei,u32Val)     ((eqei)->CNTLATCH = (u32Val))

/**
  * @brief      Get EQEI interrupt flag status
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
*                           - \ref EQEI_STATUS_DIRF_Msk      : Counting direction flag
  *                         - \ref EQEI_STATUS_DIRCHGF_Msk   : Direction change flag
  *                         - \ref EQEI_STATUS_OVUNF_Msk     : Counter overflow or underflow flag
  *                         - \ref EQEI_STATUS_CMPF_Msk      : Compare-match flag
  *                         - \ref EQEI_STATUS_IDXF_Msk      : Index detected flag
  * @retval     0           EQEI specified interrupt flag is not set.
  * @retval     1           EQEI specified interrupt flag is set.
  * @details    This macro get EQEI specified interrupt flag status.
  * \hideinitializer
  */
#define EQEI_GET_INT_FLAG(eqei, u32IntSel)        (((eqei)->STATUS & (u32IntSel))?1:0)


/**
  * @brief      Clear EQEI interrupt flag
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32IntSel   Interrupt type selection.
  *                         - \ref EQEI_STATUS_DIRCHGF_Msk   : Direction change flag
  *                         - \ref EQEI_STATUS_OVUNF_Msk     : Counter overflow or underflow flag
  *                         - \ref EQEI_STATUS_CMPF_Msk      : Compare-match flag
  *                         - \ref EQEI_STATUS_IDXF_Msk      : Index detected flag
  * @return     None
  * @details    This macro clear EQEI specified interrupt flag.
  * \hideinitializer
  */
#define EQEI_CLR_INT_FLAG(eqei, u32IntSel)     ((eqei)->STATUS = (u32IntSel))

/**
  * @brief      Set EQEI counter compare value
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Value    The counter compare value.
  * @return     None
  * @details    This macro set EQEI pulse counter compare value.
  * \hideinitializer
  */
#define EQEI_SET_CNT_CMP(eqei, u32Value)      ((eqei)->CNTCMP = (u32Value))

/**
  * @brief      Set EQEI counter value
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Value    The counter compare value.
  * @return     None
  * @details    This macro set EQEI pulse counter value.
  * \hideinitializer
  */
#define EQEI_SET_CNT_VALUE(eqei, u32Value)      ((eqei)->CNT = (u32Value))

/**
  * @brief      Enable EQEI counter hold mode
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Type     The triggered type.
  *                         - \ref EQEI_CTL_HOLDCNT_Msk      : Hold EQEI_CNT control
  *                         - \ref EQEI_CTL_HOLDTMR0_Msk     : Hold EQEI_CNT by Timer0
  *                         - \ref EQEI_CTL_HOLDTMR1_Msk     : Hold EQEI_CNT by Timer1
  *                         - \ref EQEI_CTL_HOLDTMR2_Msk     : Hold EQEI_CNT by Timer2
  *                         - \ref EQEI_CTL_HOLDTMR3_Msk     : Hold EQEI_CNT by Timer3
  * @return     None
  * @details    This macro enable EQEI counter hold mode.
  * \hideinitializer
  */
#define EQEI_ENABLE_HOLD_TRG_SRC(eqei, u32Type)      ((eqei)->CTL |= (u32Type))

/**
  * @brief      Disable EQEI counter hold mode
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Type     The triggered type.
  *                         - \ref EQEI_CTL_HOLDCNT_Msk      : Hold EQEI_CNT control
  *                         - \ref EQEI_CTL_HOLDTMR0_Msk     : Hold EQEI_CNT by Timer0
  *                         - \ref EQEI_CTL_HOLDTMR1_Msk     : Hold EQEI_CNT by Timer1
  *                         - \ref EQEI_CTL_HOLDTMR2_Msk     : Hold EQEI_CNT by Timer2
  *                         - \ref EQEI_CTL_HOLDTMR3_Msk     : Hold EQEI_CNT by Timer3
  * @return     None
  * @details    This macro disable EQEI counter hold mode.
  * \hideinitializer
  */
#define EQEI_DISABLE_HOLD_TRG_SRC(eqei, u32Type)      ((eqei)->CTL &= ~(u32Type))

/**
  * @brief      Set EQEI maximum count value
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Value    The counter maximum value.
  * @return     EQEI maximum count value
  * @details    This macro set EQEI maximum count value.
  * \hideinitializer
  */
#define EQEI_SET_CNT_MAX(eqei, u32Value)      ((eqei)->CNTMAX = (u32Value))

/**
  * @brief      Set EQEI counting mode
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Mode     EQEI counting mode.
  *                         - \ref EQEI_CTL_X4_FREE_COUNTING_MODE
  *                         - \ref EQEI_CTL_X2_FREE_COUNTING_MODE
  *                         - \ref EQEI_CTL_X4_COMPARE_COUNTING_MODE
  *                         - \ref EQEI_CTL_X2_COMPARE_COUNTING_MODE
  *                         - \ref EQEI_CTL_PHASE_COUNTING_MODE_TYPE1
  *                         - \ref EQEI_CTL_PHASE_COUNTING_MODE_TYPE2
  *                         - \ref EQEI_CTL_DIRECTIONAL_COUNTING_MODE
  * @return     None
  * @details    This macro set EQEI counting mode.
  * \hideinitializer
  */
#define EQEI_SET_CNT_MODE(eqei, u32Mode)       ((eqei)->CTL = ((eqei)->CTL & (~EQEI_CTL_MODE_Msk)) | (u32Mode))

/**
  * @brief      Set EQEI clock rate setting without quadrature mode
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Mode     EQEI clock rate setting without quadrature mode.
  *                         - \ref EQEI_CTL2_X1_COUNT_FALLING
  *                         - \ref EQEI_CTL2_X1_COUNT_RISING
  *                         - \ref EQEI_CTL2_X2_COUNT_FALLING_AND_RISING
  * @return     None
  * @details    This macro set EQEI clock rate setting without quadrature mode.
  * \hideinitializer
  */
#define EQEI_SET_CRS_MODE(eqei, u32Mode)       ((eqei)->CTL2 = ((eqei)->CTL2 & (~EQEI_CTL2_CRS_Msk)) | (u32Mode))

/**
  * @brief      Set EQEI direction signal source select
  * @param[in]  eqei         The pointer of the specified EQEI module.
  * @param[in]  u32Mode     EQEI direction signal source select.
  *                         - \ref EQEI_CTL2_DIRCTION_FROM_EQEI_CALC
  *                         - \ref EQEI_CTL2_DIRCTION_TIED_HIGH
  *                         - \ref EQEI_CTL2_DIRCTION_TIED_LOW
  * @return     None
  * @details    This macro set EQEI direction signal source select.
  * \hideinitializer
  */
#define EQEI_SET_DIRSRC_MODE(eqei, u32Mode)       ((eqei)->CTL2 = ((eqei)->CTL2 & (~EQEI_CTL2_DIRSRC_Msk)) | (u32Mode))



void EQEI_Close(EQEI_T *eqei);
void EQEI_DisableInt(EQEI_T *eqei, uint32_t u32IntSel);
void EQEI_EnableInt(EQEI_T *eqei, uint32_t u32IntSel);
void EQEI_Open(EQEI_T *eqei, uint32_t u32Mode, uint32_t u32Value);
void EQEI_Start(EQEI_T *eqei);
void EQEI_Stop(EQEI_T *eqei);


/*@}*/ /* end of group EQEI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EQEI_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_EQEI_H__ */

/*** (C) COPYRIGHT 2021 Nuvoton Technology Corp. ***/
