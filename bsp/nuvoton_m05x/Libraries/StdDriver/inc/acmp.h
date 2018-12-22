/**************************************************************************//**
 * @file     acmp.h
 * @version  V3.00
 * $Revision: 6 $
 * $Date: 1/28/14 11:32a $
 * @brief    M051 series Analog Comparator(ACMP) driver header file
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


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_ACMP_Driver ACMP Driver
  @{
*/

/** @addtogroup M051_ACMP_EXPORTED_CONSTANTS ACMP Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* ACMP_CR constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ACMP_CR_OUTPUT_INV           (1UL << ACMP_CR_ACMPOINV_Pos) /*!< ACMP_CR setting for ACMP output inverse function. */
#define ACMP_CR_VNEG_BANDGAP         (1UL << ACMP_CR_NEGSEL_Pos)   /*!< ACMP_CR setting for selecting band-gap voltage as the source of ACMP V-. */
#define ACMP_CR_VNEG_PIN             (0UL << ACMP_CR_NEGSEL_Pos)   /*!< ACMP_CR setting for selecting the voltage of ACMP negative input pin as the source of ACMP V-. */
#define ACMP_CR_HYSTERESIS_ENABLE    (1UL << ACMP_CR_HYSEN_Pos)    /*!< ACMP_CR setting for enabling the hysteresis function. */
#define ACMP_CR_HYSTERESIS_DISABLE   (0UL << ACMP_CR_HYSEN_Pos)    /*!< ACMP_CR setting for disabling the hysteresis function. */
#define ACMP_CR_INT_ENABLE           (1UL << ACMP_CR_ACMPIE_Pos)   /*!< ACMP_CR setting for enabling the interrupt function. */
#define ACMP_CR_INT_DISABLE          (0UL << ACMP_CR_ACMPIE_Pos)   /*!< ACMP_CR setting for disabling the interrupt function. */
#define ACMP_CR_ACMP_ENABLE          (1UL << ACMP_CR_ACMPEN_Pos)   /*!< ACMP_CR setting for enabling the ACMP analog circuit. */
#define ACMP_CR_ACMP_DISABLE         (0UL << ACMP_CR_ACMPEN_Pos)   /*!< ACMP_CR setting for disabling the ACMP analog circuit. */

/*@}*/ /* end of group M051_ACMP_EXPORTED_CONSTANTS */


/** @addtogroup M051_ACMP_EXPORTED_FUNCTIONS ACMP Exported Functions
  @{
*/

/**
  * @brief This macro is used to enable output inverse
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_ENABLE_OUTPUT_INVERSE(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] |= ACMP_CR_ACMPOINV_Msk)

/**
  * @brief This macro is used to disable output inverse
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_DISABLE_OUTPUT_INVERSE(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] &= ~ACMP_CR_ACMPOINV_Msk)

/**
  * @brief This macro is used to select ACMP negative input source
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @param[in] u32Src is comparator0 negative input selection.  Including :
  *                  - \ref ACMP_CR_VNEG_PIN
  *                  - \ref ACMP_CR_VNEG_BANDGAP
  * @return None
  */
#define ACMP_SET_NEG_SRC(acmp, u32ChNum, u32Src) ((acmp)->CR[(u32ChNum)%2] = ((acmp)->CR[(u32ChNum)%2] & ~ACMP_CR_NEGSEL_Msk) | (u32Src))

/**
  * @brief This macro is used to enable hysteresis function
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_ENABLE_HYSTERESIS(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] |= ACMP_CR_HYSEN_Msk)

/**
  * @brief This macro is used to disable hysteresis function
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_DISABLE_HYSTERESIS(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] &= ~ACMP_CR_HYSEN_Msk)

/**
  * @brief This macro is used to enable interrupt
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_ENABLE_INT(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] |= ACMP_CR_ACMPIE_Msk)

/**
  * @brief This macro is used to disable interrupt
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_DISABLE_INT(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] &= ~ACMP_CR_ACMPIE_Msk)


/**
  * @brief This macro is used to enable ACMP
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_ENABLE(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] |= ACMP_CR_ACMPEN_Msk)

/**
  * @brief This macro is used to disable ACMP
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return None
  */
#define ACMP_DISABLE(acmp, u32ChNum) ((acmp)->CR[(u32ChNum)%2] &= ~ACMP_CR_ACMPEN_Msk)

/**
  * @brief This macro is used to get ACMP output value
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return  1 or 0
  */
#define ACMP_GET_OUTPUT(acmp, u32ChNum) (((acmp)->SR & (ACMP_SR_ACMPO0_Msk<<((u32ChNum)%2)))?1:0)

/**
  * @brief This macro is used to get ACMP interrupt flag
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return   ACMP interrupt occurred or not
  */
#define ACMP_GET_INT_FLAG(acmp, u32ChNum) (((acmp)->SR & (ACMP_SR_ACMPF0_Msk<<((u32ChNum)%2)))?1:0)

/**
  * @brief This macro is used to clear ACMP interrupt flag
  * @param[in] acmp The base address of ACMP module
  * @param[in] u32ChNum The ACMP number
  * @return   None
  */
#define ACMP_CLR_INT_FLAG(acmp, u32ChNum) ((acmp)->SR = (ACMP_SR_ACMPF0_Msk<<((u32ChNum)%2)))

void ACMP_Open(ACMP_T *, uint32_t u32ChNum, uint32_t u32NegSrc, uint32_t u32HysteresisEn);
void ACMP_Close(ACMP_T *, uint32_t u32ChNum);

/*@}*/ /* end of group M051_ACMP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_ACMP_Driver */

/*@}*/ /* end of group M051_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__ACMP_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
