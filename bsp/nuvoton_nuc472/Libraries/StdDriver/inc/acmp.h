/**************************************************************************//**
 * @file     acmp.h
 * @version  V1.00
 * $Revision: 5 $
 * $Date: 15/11/04 7:29p $
 * @brief    NUC472/NUC442 Analog Comparator(ACMP) driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __ACMP_H__
#define __ACMP_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_ACMP_Driver ACMP Driver
  @{
*/

/** @addtogroup NUC472_442_ACMP_EXPORTED_CONSTANTS ACMP Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* ACMP_CR constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ACMP_VNEG_PIN             (0xFFUL)                         ///< Selecting the voltage of ACMP negative input pin as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_BANDGAP         (0x00UL)                         ///< Selecting band-gap voltage as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_4_OVER_24_VDD   (0x80UL)                         ///< Selecting 4/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_5_OVER_24_VDD   (0x81UL)                         ///< Selecting 5/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_6_OVER_24_VDD   (0x82UL)                         ///< Selecting 6/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_7_OVER_24_VDD   (0x83UL)                         ///< Selecting 7/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_8_OVER_24_VDD   (0x84UL)                         ///< Selecting 8/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_9_OVER_24_VDD   (0x85UL)                         ///< Selecting 9/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_10_OVER_24_VDD  (0x86UL)                         ///< Selecting 10/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_11_OVER_24_VDD  (0x87UL)                         ///< Selecting 11/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_12_OVER_24_VDD  (0x88UL)                         ///< Selecting 12/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_13_OVER_24_VDD  (0x89UL)                         ///< Selecting 13/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_14_OVER_24_VDD  (0x8AUL)                         ///< Selecting 14/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_15_OVER_24_VDD  (0x8BUL)                         ///< Selecting 15/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_16_OVER_24_VDD  (0x8CUL)                         ///< Selecting 16/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_17_OVER_24_VDD  (0x8DUL)                         ///< Selecting 17/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_18_OVER_24_VDD  (0x8EUL)                         ///< Selecting 18/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_19_OVER_24_VDD  (0x8FUL)                         ///< Selecting 19/24 VDD as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_4_OVER_24_IREF  (0xC0UL)                         ///< Selecting 4/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_5_OVER_24_IREF  (0xC1UL)                         ///< Selecting 5/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_6_OVER_24_IREF  (0xC2UL)                         ///< Selecting 6/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_7_OVER_24_IREF  (0xC3UL)                         ///< Selecting 7/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_8_OVER_24_IREF  (0xC4UL)                         ///< Selecting 8/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_9_OVER_24_IREF  (0xC5UL)                         ///< Selecting 9/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_10_OVER_24_IREF (0xC6UL)                         ///< Selecting 10/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_11_OVER_24_IREF (0xC7UL)                         ///< Selecting 11/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_12_OVER_24_IREF (0xC8UL)                         ///< Selecting 12/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_13_OVER_24_IREF (0xC9UL)                         ///< Selecting 13/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_14_OVER_24_IREF (0xCAUL)                         ///< Selecting 14/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_15_OVER_24_IREF (0xCBUL)                         ///< Selecting 15/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_16_OVER_24_IREF (0xCCUL)                         ///< Selecting 16/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_17_OVER_24_IREF (0xCDUL)                         ///< Selecting 17/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_18_OVER_24_IREF (0xCEUL)                         ///< Selecting 18/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_VNEG_19_OVER_24_IREF (0xCFUL)                         ///< Selecting 19/24 IREF as the source of ACMP V- \hideinitializer
#define ACMP_HYSTERESIS_ENABLE    (1UL << ACMP_CTL_HYSEN_Pos)      ///< Enable hysteresis function \hideinitializer
#define ACMP_HYSTERESIS_DISABLE   (0UL)                            ///< Disable hysteresis function \hideinitializer
#define ACMP_CH0_POSPIN_P0       (0UL)                             ///< Selecting ACMP0_P0 as ACMP Channel 0 positive input source \hideinitializer
#define ACMP_CH0_POSPIN_P1       (1UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP0_P1 as ACMP Channel 0 positive input source \hideinitializer
#define ACMP_CH0_POSPIN_P2       (2UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP0_P2 as ACMP Channel 0 positive input source \hideinitializer
#define ACMP_CH0_POSPIN_P3       (3UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP0_P3 as ACMP Channel 0 positive input source \hideinitializer
#define ACMP_CH0_POS_OPA0        (4UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting OPA0 as ACMP Channel 0 positive input source \hideinitializer
#define ACMP_CH1_POSPIN_P0       (0UL)                             ///< Selecting ACMP1_P0 as ACMP Channel 1 positive input source \hideinitializer
#define ACMP_CH1_POSPIN_P1       (1UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP1_P1 as ACMP Channel 1 positive input source \hideinitializer
#define ACMP_CH1_POSPIN_P2       (2UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP1_P2 as ACMP Channel 1 positive input source \hideinitializer
#define ACMP_CH1_POSPIN_P3       (3UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP1_P3 as ACMP Channel 1 positive input source \hideinitializer
#define ACMP_CH1_POS_OPA1        (4UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting OPA1 as ACMP Channel 1 positive input source \hideinitializer
#define ACMP_CH2_POSPIN_P0       (0UL)                             ///< Selecting ACMP2_P0 as ACMP Channel 2 positive input source \hideinitializer
#define ACMP_CH2_POSPIN_P1       (1UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP2_P1 as ACMP Channel 2 positive input source \hideinitializer
#define ACMP_CH2_POSPIN_P2       (2UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP2_P2 as ACMP Channel 2 positive input source \hideinitializer
#define ACMP_CH2_POSPIN_P3       (3UL << ACMP_CTL_POSSEL_Pos)      ///< Selecting ACMP2_P3 as ACMP Channel 2 positive input source \hideinitializer


/*@}*/ /* end of group NUC472_442_ACMP_EXPORTED_CONSTANTS */


/** @addtogroup NUC472_442_ACMP_EXPORTED_FUNCTIONS ACMP Exported Functions
  @{
*/

/**
  * @brief This macro is used to select ACMP negative input source
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @param[in] u32Src is comparator negative input selection.  Including :
  *                  - \ref ACMP_VNEG_PIN
  *                  - \ref ACMP_VNEG_BANDGAP
  *                  - \ref ACMP_VNEG_4_OVER_24_VDD
  *                  - \ref ACMP_VNEG_5_OVER_24_VDD
  *                  - \ref ACMP_VNEG_6_OVER_24_VDD
  *                  - \ref ACMP_VNEG_7_OVER_24_VDD
  *                  - \ref ACMP_VNEG_8_OVER_24_VDD
  *                  - \ref ACMP_VNEG_9_OVER_24_VDD
  *                  - \ref ACMP_VNEG_10_OVER_24_VDD
  *                  - \ref ACMP_VNEG_11_OVER_24_VDD
  *                  - \ref ACMP_VNEG_12_OVER_24_VDD
  *                  - \ref ACMP_VNEG_13_OVER_24_VDD
  *                  - \ref ACMP_VNEG_14_OVER_24_VDD
  *                  - \ref ACMP_VNEG_15_OVER_24_VDD
  *                  - \ref ACMP_VNEG_16_OVER_24_VDD
  *                  - \ref ACMP_VNEG_17_OVER_24_VDD
  *                  - \ref ACMP_VNEG_18_OVER_24_VDD
  *                  - \ref ACMP_VNEG_19_OVER_24_VDD
  *                  - \ref ACMP_VNEG_4_OVER_24_IREF
  *                  - \ref ACMP_VNEG_5_OVER_24_IREF
  *                  - \ref ACMP_VNEG_6_OVER_24_IREF
  *                  - \ref ACMP_VNEG_7_OVER_24_IREF
  *                  - \ref ACMP_VNEG_8_OVER_24_IREF
  *                  - \ref ACMP_VNEG_9_OVER_24_IREF
  *                  - \ref ACMP_VNEG_10_OVER_24_IREF
  *                  - \ref ACMP_VNEG_11_OVER_24_IREF
  *                  - \ref ACMP_VNEG_12_OVER_24_IREF
  *                  - \ref ACMP_VNEG_13_OVER_24_IREF
  *                  - \ref ACMP_VNEG_14_OVER_24_IREF
  *                  - \ref ACMP_VNEG_15_OVER_24_IREF
  *                  - \ref ACMP_VNEG_16_OVER_24_IREF
  *                  - \ref ACMP_VNEG_17_OVER_24_IREF
  *                  - \ref ACMP_VNEG_18_OVER_24_IREF
  *                  - \ref ACMP_VNEG_19_OVER_24_IREF
  *
  * @return None
  * @note The V- setting is shared by all comparators if input source is not coming from PIN
  * \hideinitializer
  */
#define ACMP_SET_NEG_SRC(acmp, u32ChNum, u32Src) do{\
                                                     if(u32Src == ACMP_VNEG_PIN)\
                                                         ACMP->CTL[u32ChNum] &= ~ACMP_CTL_NEGSEL_Msk;\
                                                     else {\
                                                         ACMP->CTL[u32ChNum] |= ACMP_CTL_NEGSEL_Msk;\
                                                         ACMP->VREF = u32Src;\
                                                     }\
                                                 }while(0)

/**
  * @brief This macro is used to enable hysteresis function
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return None
  * \hideinitializer
  */
#define ACMP_ENABLE_HYSTERESIS(acmp, u32ChNum) (ACMP->CTL[u32ChNum] |= ACMP_CTL_HYSEN_Msk)

/**
  * @brief This macro is used to disable hysteresis function
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return None
  * \hideinitializer
  */
#define ACMP_DISABLE_HYSTERESIS(acmp, u32ChNum) (ACMP->CTL[u32ChNum] &= ~ACMP_CTL_HYSEN_Msk)

/**
  * @brief This macro is used to enable interrupt
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return None
  * \hideinitializer
  */
#define ACMP_ENABLE_INT(acmp, u32ChNum) (ACMP->CTL[u32ChNum] |= ACMP_CTL_ACMPIE_Msk)

/**
  * @brief This macro is used to disable interrupt
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return None
  * \hideinitializer
  */
#define ACMP_DISABLE_INT(acmp, u32ChNum) (ACMP->CTL[u32ChNum] &= ~ACMP_CTL_ACMPIE_Msk)


/**
  * @brief This macro is used to enable ACMP
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return None
  * \hideinitializer
  */
#define ACMP_ENABLE(acmp, u32ChNum) (ACMP->CTL[u32ChNum] |= ACMP_CTL_ACMPEN_Msk)

/**
  * @brief This macro is used to disable ACMP
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return None
  * \hideinitializer
  */
#define ACMP_DISABLE(acmp, u32ChNum) (ACMP->CTL[u32ChNum] &= ~ACMP_CTL_ACMPEN_Msk)

/**
  * @brief This macro is used to get ACMP output value
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return  1 or 0
  * \hideinitializer
  */
#define ACMP_GET_OUTPUT(acmp, u32ChNum) (ACMP->STATUS & (ACMP_STATUS_ACMPO0_Msk<<(u32ChNum))?1:0)

/**
  * @brief This macro is used to get ACMP interrupt flag
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return   ACMP interrupt occurred or not
  * \hideinitializer
  */
#define ACMP_GET_INT_FLAG(acmp, u32ChNum) (ACMP->STATUS & (ACMP_STATUS_ACMPIF0_Msk<<(u32ChNum))?1:0)

/**
  * @brief This macro is used to clear ACMP interrupt flag
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return   None
  * \hideinitializer
  */
#define ACMP_CLR_INT_FLAG(acmp, u32ChNum) (ACMP->STATUS = (ACMP_STATUS_ACMPIF0_Msk<<(u32ChNum)))

/**
  * @brief This macro is used to select the V+ pin of ACMP
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @param[in] u32Pin The input pin. For channel 0, valid values are \ref ACMP_CH0_POSPIN_P0,
  *            \ref ACMP_CH0_POSPIN_P1, \ref ACMP_CH0_POSPIN_P2, \ref ACMP_CH0_POSPIN_P3, and \ref ACMP_CH0_POS_OPA0. 
  *            For channel 1, valid values are , \ref ACMP_CH1_POSPIN_P0, \ref ACMP_CH1_POSPIN_P1, \ref ACMP_CH1_POSPIN_P2, 
  *            \ref ACMP_CH1_POSPIN_P3, and \ref ACMP_CH1_POS_OPA1. For channel 2, valid values are , \ref ACMP_CH2_POSPIN_P0, 
  *            \ref ACMP_CH2_POSPIN_P1, \ref ACMP_CH2_POSPIN_P2, and \ref ACMP_CH2_POSPIN_P3.
  * @return   None
  * @note   Except this setting, multi-function pin also needs to be configured
  * \hideinitializer
  */
#define ACMP_SELECT_P(acmp, u32ChNum, u32Pin)  (ACMP->CTL[u32ChNum] = (ACMP->CTL[u32ChNum] & ~ACMP_CTL_POSSEL_Msk) | u32Pin)
/**
  * @brief This macro is used to set the level of CRV (Comparator Reference Voltage)
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32Level CRV level, possible values are
  *                  - \ref ACMP_VNEG_4_OVER_24_VDD
  *                  - \ref ACMP_VNEG_5_OVER_24_VDD
  *                  - \ref ACMP_VNEG_6_OVER_24_VDD
  *                  - \ref ACMP_VNEG_7_OVER_24_VDD
  *                  - \ref ACMP_VNEG_8_OVER_24_VDD
  *                  - \ref ACMP_VNEG_9_OVER_24_VDD
  *                  - \ref ACMP_VNEG_10_OVER_24_VDD
  *                  - \ref ACMP_VNEG_11_OVER_24_VDD
  *                  - \ref ACMP_VNEG_12_OVER_24_VDD
  *                  - \ref ACMP_VNEG_13_OVER_24_VDD
  *                  - \ref ACMP_VNEG_14_OVER_24_VDD
  *                  - \ref ACMP_VNEG_15_OVER_24_VDD
  *                  - \ref ACMP_VNEG_16_OVER_24_VDD
  *                  - \ref ACMP_VNEG_17_OVER_24_VDD
  *                  - \ref ACMP_VNEG_18_OVER_24_VDD
  *                  - \ref ACMP_VNEG_19_OVER_24_VDD
  *                  - \ref ACMP_VNEG_4_OVER_24_IREF
  *                  - \ref ACMP_VNEG_5_OVER_24_IREF
  *                  - \ref ACMP_VNEG_6_OVER_24_IREF
  *                  - \ref ACMP_VNEG_7_OVER_24_IREF
  *                  - \ref ACMP_VNEG_8_OVER_24_IREF
  *                  - \ref ACMP_VNEG_9_OVER_24_IREF
  *                  - \ref ACMP_VNEG_10_OVER_24_IREF
  *                  - \ref ACMP_VNEG_11_OVER_24_IREF
  *                  - \ref ACMP_VNEG_12_OVER_24_IREF
  *                  - \ref ACMP_VNEG_13_OVER_24_IREF
  *                  - \ref ACMP_VNEG_14_OVER_24_IREF
  *                  - \ref ACMP_VNEG_15_OVER_24_IREF
  *                  - \ref ACMP_VNEG_16_OVER_24_IREF
  *                  - \ref ACMP_VNEG_17_OVER_24_IREF
  *                  - \ref ACMP_VNEG_18_OVER_24_IREF
  *                  - \ref ACMP_VNEG_19_OVER_24_IREF
  * @return   None
  * @note This macro does not enable CRV. Please use \ref ACMP_ENABLE_CRV to enable CRV.
  * \hideinitializer
  */
#define ACMP_CRV_SEL(acmp, u32Level) (ACMP->VREF = (ACMP->VREF & ~(ACMP_VREF_CRVSSEL_Msk | ACMP_VREF_CRVCTL_Msk)) | (u32Level))
/**
  * @brief This macro is used to enable CRV(Comparator Reference Voltage)
  * @param[in] acmp The base address of ACMP module
  * @return   None
  * \hideinitializer
  */
#define ACMP_ENABLE_CRV(acmp) (ACMP->VREF |= ACMP_VREF_IREFSEL_Msk)
/**
  * @brief This macro is used to disable CRV(Comparator Reference Voltage)
  * @param[in] acmp The base address of ACMP module
  * @return   None
  * \hideinitializer
  */
#define ACMP_DISABLE_CRV(acmp) (ACMP->VREF &= ~ACMP_VREF_IREFSEL_Msk)

/**
  * @brief This macro is used to enable ACMP output inverse function
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return   None
  * \hideinitializer
  */
#define ACMP_ENABLE_OUTPUT_INVERSE(acmp, u32ChNum) (ACMP->CTL[u32ChNum] |= ACMP_CTL_ACMPOINV_Msk)

/**
  * @brief This macro is used to disable ACMP output inverse function
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number, could 0, 1, or 2
  * @return   None
  * \hideinitializer
  */
#define ACMP_DISABLE_OUTPUT_INVERSE(acmp, u32ChNum) (ACMP->CTL[u32ChNum] &= ~ACMP_CTL_ACMPOINV_Msk)


void ACMP_Open(ACMP_T *acmp, uint32_t u32ChNum, uint32_t u32NegSrc, uint32_t u32HysteresisEn);
void ACMP_Close(ACMP_T *acmp, uint32_t u32ChNum);

/*@}*/ /* end of group NUC472_442_ACMP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_ACMP_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__ACMP_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
