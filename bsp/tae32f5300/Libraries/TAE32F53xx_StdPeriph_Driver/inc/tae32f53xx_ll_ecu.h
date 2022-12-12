/**
  ******************************************************************************
  * @file    tae32f53xx_ll_ecu.h
  * @author  MCD Application Team
  * @brief   Header file of ECU LL module
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
#ifndef _TAE32F53XX_LL_ECU_H_
#define _TAE32F53XX_LL_ECU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup ECU_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup ECU_LL_Exported_Constants ECU LL Exported Constants
  * @brief    ECU LL Exported Constants
  * @{
  */

/** @defgroup LL_ECU_ENABLE ECU enable define
  * @brief    ECU Enable Bit Set and Bit Reset
  * @{
  */
#define ECU_DISABLE                         (0x00000000U)       /*!<ECU module disable          */
#define ECU_ENABLE                          (ECU_CON_ENABLE)    /*!<ECU module enable           */
/**
  * @}
  */

/** @defgroup LL_ECU_IT_ENABLE ECU enable interrupt define
  * @brief    ECU Interrupt Enable Bit Set and Bit Reset
  * @{
  */
#define ECU_IT_DISABLE                      (0x00000000U)       /*!<ECU module disable          */
#define ECU_IT_ENABLE                       (ECU_CON_INTEN)     /*!<ECU module interrupt enable */
/**
  * @}
  */

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup ECU_LL_Exported_Types ECU LL Exported Types
  * @brief    ECU LL Exported Types
  * @{
  */

/** @defgroup LL_ECU_AVERAGE ECU average period define
  * @brief  ECU Enumerate the number of periods to be averaged
  * @{
  */
typedef enum {
    ECU_AVERAGE_DISABLE = 0x0,  /*!<Instead of averaging the results of the periodic data, one result is produced per period    */
    ECU_AVERAGE_2PERIOD = ECU_CON_AVGSEL_0,                     /*!<Two cycles of data produce a result                         */
    ECU_AVERAGE_4PERIOD = ECU_CON_AVGSEL_1,                     /*!<Four cycles of data produce a result                        */
    ECU_AVERAGE_8PERIOD = ECU_CON_AVGSEL_1 | ECU_CON_AVGSEL_0,  /*!<Eight cycles of data produce a result                       */
} ECU_AverageETypedef;
/**
  * @}
  */

/** @defgroup LL_ECU_ACPOWER_LEFT_SHIFT ECU active power left shift define
  * @brief  ECU Enumerate the left shift number of active power
  * @{
  */
typedef enum {
    ECU_ACPOWER_LEFT_SHIFT_DISABLE = 0x0,
    ECU_ACPOWER_LEFT_SHIFT_1       = ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_2       = ECU_CON_ACSFT_1,
    ECU_ACPOWER_LEFT_SHIFT_3       = ECU_CON_ACSFT_1 | ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_4       = ECU_CON_ACSFT_2,
    ECU_ACPOWER_LEFT_SHIFT_5       = ECU_CON_ACSFT_2 | ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_6       = ECU_CON_ACSFT_2 | ECU_CON_ACSFT_1,
    ECU_ACPOWER_LEFT_SHIFT_7       = ECU_CON_ACSFT_2 | ECU_CON_ACSFT_1 | ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_8       = ECU_CON_ACSFT_3,
    ECU_ACPOWER_LEFT_SHIFT_9       = ECU_CON_ACSFT_3 | ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_10      = ECU_CON_ACSFT_3 | ECU_CON_ACSFT_1,
    ECU_ACPOWER_LEFT_SHIFT_11      = ECU_CON_ACSFT_3 | ECU_CON_ACSFT_1 | ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_12      = ECU_CON_ACSFT_3 | ECU_CON_ACSFT_2,
    ECU_ACPOWER_LEFT_SHIFT_13      = ECU_CON_ACSFT_3 | ECU_CON_ACSFT_2 | ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_14      = ECU_CON_ACSFT_3 | ECU_CON_ACSFT_2 | ECU_CON_ACSFT_1,
    ECU_ACPOWER_LEFT_SHIFT_15      = ECU_CON_ACSFT_3 | ECU_CON_ACSFT_2 | ECU_CON_ACSFT_1 | ECU_CON_ACSFT_0,
    ECU_ACPOWER_LEFT_SHIFT_16      = ECU_CON_ACSFT_4,
} ECU_ACPowerLeftETypeDef;
/**
  * @}
  */

/** @defgroup LL_ECU_APPOWER_RIGHT_SHIFT ECU apparent power right shift define
  * @brief  ECU Enumerate the right shift number of the apparent power
  * @{
  */
typedef enum {
    ECU_APPOWER_RIGHT_SHIFT_DISABLE = 0x0,
    ECU_APPOWER_RIGHT_SHIFT_1       = ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_2       = ECU_CON_APSFT_1,
    ECU_APPOWER_RIGHT_SHIFT_3       = ECU_CON_APSFT_1 | ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_4       = ECU_CON_APSFT_2,
    ECU_APPOWER_RIGHT_SHIFT_5       = ECU_CON_APSFT_2 | ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_6       = ECU_CON_APSFT_2 | ECU_CON_APSFT_1,
    ECU_APPOWER_RIGHT_SHIFT_7       = ECU_CON_APSFT_2 | ECU_CON_APSFT_1 | ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_8       = ECU_CON_APSFT_3,
    ECU_APPOWER_RIGHT_SHIFT_9       = ECU_CON_APSFT_3 | ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_10      = ECU_CON_APSFT_3 | ECU_CON_APSFT_1,
    ECU_APPOWER_RIGHT_SHIFT_11      = ECU_CON_APSFT_3 | ECU_CON_APSFT_1 | ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_12      = ECU_CON_APSFT_3 | ECU_CON_APSFT_2,
    ECU_APPOWER_RIGHT_SHIFT_13      = ECU_CON_APSFT_3 | ECU_CON_APSFT_2 | ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_14      = ECU_CON_APSFT_3 | ECU_CON_APSFT_2 | ECU_CON_APSFT_1,
    ECU_APPOWER_RIGHT_SHIFT_15      = ECU_CON_APSFT_3 | ECU_CON_APSFT_2 | ECU_CON_APSFT_1 | ECU_CON_APSFT_0,
    ECU_APPOWER_RIGHT_SHIFT_16      = ECU_CON_APSFT_4,
} ECU_APPowerRightETypeDef;
/**
  * @}
  */

/** @defgroup LL_ECU_PSR_DATSEL ECU data external event define
  * @brief  ECU Enumerate data event selection to select from 16 events
  * @note   These three types of events must be selected in the same ECR register in the same ADC and cannot be mixed
  * @{
  */
typedef enum {
    /*!<ECU Data trigger from external peripheral : ADC0_ECR[0]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC0_DTFLAG0          = 0x0,
    /*!<ECU Data trigger from external peripheral : ADC0_ECR[1]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC0_DTFLAG1          = ECU_PRC_DATSEL_0,
    /*!<ECU Data trigger from external peripheral : ADC0_ECR[2]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC0_DTFLAG2          = ECU_PRC_DATSEL_1,
    /*!<ECU Data trigger from external peripheral : ADC0_ECR[3]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC0_DTFLAG3          = ECU_PRC_DATSEL_1 | ECU_PRC_DATSEL_0,
    /*!<ECU Data trigger from external peripheral : ADC1_ECR[0]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC1_DTFLAG0          = ECU_PRC_DATSEL_2,
    /*!<ECU Data trigger from external peripheral : ADC1_ECR[1]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC1_DTFLAG1          = ECU_PRC_DATSEL_2 | ECU_PRC_DATSEL_0,
    /*!<ECU Data trigger from external peripheral : ADC1_ECR[2]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC1_DTFLAG2          = ECU_PRC_DATSEL_2 | ECU_PRC_DATSEL_1,
    /*!<ECU Data trigger from external peripheral : ADC1_ECR[3]->ADDR_DATA_FLAG */
    ECU_PSR_DATSEL_ADC1_DTFLAG3          = ECU_PRC_DATSEL_2 | ECU_PRC_DATSEL_1 | ECU_PRC_DATSEL_0,
    /*!<ECU Data trigger from external peripheral : TIM0_OC                     */
    ECU_PSR_DATSEL_TIM0_OC               = ECU_PRC_DATSEL_3,
    /*!<ECU Data trigger from external peripheral : TIM1_OC                     */
    ECU_PSR_DATSEL_TIM1_OC               = ECU_PRC_DATSEL_3 | ECU_PRC_DATSEL_0,
    /*!<ECU Data trigger from external peripheral : TIM2_OC                     */
    ECU_PSR_DATSEL_TIM2_OC               = ECU_PRC_DATSEL_3 | ECU_PRC_DATSEL_1,
    /*!<ECU Data trigger from external peripheral : TIM3_OC                     */
    ECU_PSR_DATSEL_TIM3_OC               = ECU_PRC_DATSEL_3 | ECU_PRC_DATSEL_1 | ECU_PRC_DATSEL_0,
    /*!<ECU Data trigger from external peripheral : TIM4_OC                     */
    ECU_PSR_DATSEL_TIM4_OC               = ECU_PRC_DATSEL_3 | ECU_PRC_DATSEL_2,
    /*!<ECU Data trigger from external peripheral : TIM5_OC                     */
    ECU_PSR_DATSEL_TIM5_OC               = ECU_PRC_DATSEL_3 | ECU_PRC_DATSEL_2 | ECU_PRC_DATSEL_0,
    /*!<ECU Data trigger from external peripheral : TIM6_OC                     */
    ECU_PSR_DATSEL_TIM6_OC               = ECU_PRC_DATSEL_3 | ECU_PRC_DATSEL_2 | ECU_PRC_DATSEL_1,
    /*!<ECU Data trigger from external peripheral : TIM7_OC                     */
    ECU_PSR_DATSEL_TIM7_OC               = ECU_PRC_DATSEL_3 | ECU_PRC_DATSEL_2 | ECU_PRC_DATSEL_1 | ECU_PRC_DATSEL_0,
} ECU_DataSelETypeDef;
/**
  * @}
  */

/** @defgroup LL_ECU_PSR_ADRSEL ECU address external event define
  * @brief  ECU Enumerate the address event (the channel for waveform data) to select from 16 events.
  * @note   These three types of events must be selected in the same ECR register in the same ADC and cannot be mixed
  * @{
  */
typedef enum {
    /*!<ECU Address trigger from external peripheral : ADC0_ECR[0]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC0_ADFLAG0          = 0x0,
    /*!<ECU Address trigger from external peripheral : ADC0_ECR[1]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC0_ADFLAG1          = ECU_PRC_ADRSEL_0,
    /*!<ECU Address trigger from external peripheral : ADC0_ECR[2]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC0_ADFLAG2          = ECU_PRC_ADRSEL_1,
    /*!<ECU Address trigger from external peripheral : ADC0_ECR[3]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC0_ADFLAG3          = ECU_PRC_ADRSEL_1 | ECU_PRC_ADRSEL_0,
    /*!<ECU Address trigger from external peripheral : ADC1_ECR[0]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC1_ADFLAG0          = ECU_PRC_ADRSEL_2,
    /*!<ECU Address trigger from external peripheral : ADC1_ECR[1]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC1_ADFLAG1          = ECU_PRC_ADRSEL_2 | ECU_PRC_ADRSEL_0,
    /*!<ECU Address trigger from external peripheral : ADC1_ECR[2]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC1_ADFLAG2          = ECU_PRC_ADRSEL_2 | ECU_PRC_ADRSEL_1,
    /*!<ECU Address trigger from external peripheral : ADC1_ECR[3]->ADDR_DATA_FLAG*/
    ECU_PSR_ADRSEL_ADC1_ADFLAG3          = ECU_PRC_ADRSEL_2 | ECU_PRC_ADRSEL_1 | ECU_PRC_ADRSEL_0,
    /*!<ECU Address trigger from external peripheral : TIM0_OC*/
    ECU_PSR_ADRSEL_TIM0_OC               = ECU_PRC_ADRSEL_3,
    /*!<ECU Address trigger from external peripheral : TIM1_OC*/
    ECU_PSR_ADRSEL_TIM1_OC               = ECU_PRC_ADRSEL_3 | ECU_PRC_ADRSEL_0,
    /*!<ECU Address trigger from external peripheral : TIM2_OC*/
    ECU_PSR_ADRSEL_TIM2_OC               = ECU_PRC_ADRSEL_3 | ECU_PRC_ADRSEL_1,
    /*!<ECU Address trigger from external peripheral : TIM3_OC*/
    ECU_PSR_ADRSEL_TIM3_OC               = ECU_PRC_ADRSEL_3 | ECU_PRC_ADRSEL_1 | ECU_PRC_ADRSEL_0,
    /*!<ECU Address trigger from external peripheral : TIM4_OC*/
    ECU_PSR_ADRSEL_TIM4_OC               = ECU_PRC_ADRSEL_3 | ECU_PRC_ADRSEL_2,
    /*!<ECU Address trigger from external peripheral : TIM5_OC*/
    ECU_PSR_ADRSEL_TIM5_OC               = ECU_PRC_ADRSEL_3 | ECU_PRC_ADRSEL_2 | ECU_PRC_ADRSEL_0,
    /*!<ECU Address trigger from external peripheral : TIM6_OC*/
    ECU_PSR_ADRSEL_TIM6_OC               = ECU_PRC_ADRSEL_3 | ECU_PRC_ADRSEL_2 | ECU_PRC_ADRSEL_1,
    /*!<ECU Address trigger from external peripheral : TIM7_OC*/
    ECU_PSR_ADRSEL_TIM7_OC               = ECU_PRC_ADRSEL_3 | ECU_PRC_ADRSEL_2 | ECU_PRC_ADRSEL_1 | ECU_PRC_ADRSEL_0,
} ECU_AddrSelETypeDef;
/**
  * @}
  */

/** @defgroup LL_ECU_PSR_CRSSEL ECU cross zero external event define
  * @brief  ECU Enumerate zero crossing events (monitoring events for sinusoidal waveform zero crossing) and select from 16 events.
  * @note   These three types of events must be selected in the same ECR register in the same ADC and cannot be mixed
  * @{
  */
typedef enum {
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC0_ECR[0]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC0_PPFLAG0          = 0x0,
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC0_ECR[1]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC0_PPFLAG1          = ECU_PRC_CRSSEL_0,
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC0_ECR[2]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC0_PPFLAG2          = ECU_PRC_CRSSEL_1,
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC0_ECR[3]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC0_PPFLAG3          = ECU_PRC_CRSSEL_1  | ECU_PRC_CRSSEL_0,
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC1_ECR[0]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC1_PPFLAG0          = ECU_PRC_CRSSEL_2,
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC1_ECR[1]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC1_PPFLAG1          = ECU_PRC_CRSSEL_2 | ECU_PRC_CRSSEL_0,
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC1_ECR[2]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC1_PPFLAG2          = ECU_PRC_CRSSEL_2 | ECU_PRC_CRSSEL_1,
    /*!<ECU Crossing zero signal trigger from external peripheral : ADC1_ECR[3]->PSRCU/PSRCD    */
    ECU_PSR_CRSSEL_ADC1_PPFLAG3          = ECU_PRC_CRSSEL_2 | ECU_PRC_CRSSEL_1 | ECU_PRC_CRSSEL_0,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM0_OC                     */
    ECU_PSR_CRSSEL_TIM0_OC               = ECU_PRC_CRSSEL_3,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM1_OC                     */
    ECU_PSR_CRSSEL_TIM1_OC               = ECU_PRC_CRSSEL_3 | ECU_PRC_CRSSEL_0,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM2_OC                     */
    ECU_PSR_CRSSEL_TIM2_OC               = ECU_PRC_CRSSEL_3 | ECU_PRC_CRSSEL_1,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM3_OC                     */
    ECU_PSR_CRSSEL_TIM3_OC               = ECU_PRC_CRSSEL_3 | ECU_PRC_CRSSEL_1 | ECU_PRC_CRSSEL_0,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM4_OC                     */
    ECU_PSR_CRSSEL_TIM4_OC               = ECU_PRC_CRSSEL_3 | ECU_PRC_CRSSEL_2,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM5_OC                     */
    ECU_PSR_CRSSEL_TIM5_OC               = ECU_PRC_CRSSEL_3 | ECU_PRC_CRSSEL_2 | ECU_PRC_CRSSEL_0,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM6_OC                     */
    ECU_PSR_CRSSEL_TIM6_OC               = ECU_PRC_CRSSEL_3 | ECU_PRC_CRSSEL_2 | ECU_PRC_CRSSEL_1,
    /*!<ECU Crossing zero signal trigger from external peripheral : TIM7_OC                     */
    ECU_PSR_CRSSEL_TIM7_OC               = ECU_PRC_CRSSEL_3 | ECU_PRC_CRSSEL_2 | ECU_PRC_CRSSEL_1 | ECU_PRC_CRSSEL_0,
} ECU_CrossZeroSelETypeDef;
/**
  * @}
  */

/**
  * @brief ECU Init structure definition
  */
typedef struct __ECU_InitTypeDef {
    LL_FuncStatusETypeDef ModuleEnable;     /*!< Specifies ECU module enablement Bit.
                                                This parameter can be any value of @ref ENABLE or DISABLE*/

    LL_FuncStatusETypeDef InterruptEn;      /*!< Specifies ECU module enable interrupt.
                                                This parameter can be any value of @ref ENABLE or DISABLE */

    ECU_AverageETypedef AverageSel;         /*!< Setting the result requires averaging the data over several cycles.
                                                This parameter can be a value of @ref LL_ECU_AVERAGE */

    ECU_APPowerRightETypeDef APRightShift;  /*!< Set the number of right shifts of the ECU view Apparent power.
                                                This parameter can be a value of @ref LL_ECU_APPOWER_RIGHT_SHIFT */

    ECU_ACPowerLeftETypeDef ACLeftShift;    /*!< Set the number of left shift of active power and the maximum left shift is 16 bits.
                                                This parameter can be a value of @ref LL_ECU_ACPOWER_LEFT_SHIFT*/

    ECU_CrossZeroSelETypeDef CrossZeroSel;  /*!< Set zero crossing events (monitoring events for sinusoidal waveform zero crossing)
                                                 and select from 16 events. This parameter can be a value of @ref LL_ECU_PSR_CRSSEL */

    ECU_AddrSelETypeDef AddressSel;         /*!< Set the address event (the channel for waveform data) to select from 16 events.
                                                This parameter can be a value of @ref LL_ECU_PSR_ADRSEL */

    ECU_DataSelETypeDef DataSel;            /*!< Set data event selection to select from 16 events.
                                                This parameter can be a value of @ref LL_ECU_PSR_DATSEL */

    uint32_t VStartAddr;                    /*!< Set the starting address for voltage (pingpong) data storage.*/

    uint32_t VOffsetAddr;                   /*!< Set voltage (pingpong) data to store offset address.*/

    uint32_t IStartAddr;                    /*!< Set the starting address for current (pingpong) data storage.*/

    uint32_t IOffsetAddr;                   /*!< Set current (pingpong) data to store offset address.*/

} ECU_InitTypeDef;

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup ECU_LL_Exported_Macros ECU LL Exported Macros
  * @brief    ECU LL Exported Macros
  * @{
  */

/**
  * @brief  Enable the ECU module.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return None
  */
#define __LL_ECU_MODULE_ENABLE(__INSTANCE__)                    SET_BIT((__INSTANCE__)->CON, ECU_CON_ENABLE)

/**
  * @brief  Disable the ECU module.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return None
  */
#define __LL_ECU_MODULE_DISABLE(__INSTANCE__)                   CLEAR_BIT((__INSTANCE__)->CON, ECU_CON_ENABLE)

/**
  * @brief  Get the ECU module states.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return ENABLE : the module is enable
  *         DISABLE : the module is disable
  */
#define __LL_ECU_GET_STA(__INSTANCE__)              ((((__INSTANCE__)->CON & (ECU_CON_ENABLE)) == 0x1UL) ? ENABLE : DISABLE)

/**
  * @brief  Enable the specified ECU Calculate complete interrupt.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return None
  */
#define __LL_ECU_DONE_IT_ENABLE(__INSTANCE__)                   SET_BIT((__INSTANCE__)->CON, ECU_CON_INTEN)

/**
  * @brief  Disable the specified ECU Calculate complete interrupt.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return None
  */
#define __LL_ECU_DONE_IT_DISABLE(__INSTANCE__)                  CLEAR_BIT((__INSTANCE__)->CON, ECU_CON_INTEN)

/**
  * @brief  Check the ECU Calculate complete interrupts are enabled or disable.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return SET : the interrupt is enable
  *         RESET : the interrupt is disable
  */
#define __LL_ECU_DONE_GET_IT(__INSTANCE__)                      ((((__INSTANCE__)->CON & (ECU_CON_INTEN)) == 0x02UL) ? SET : RESET)

/**
  * @brief  Check whether the specified ECU Calculate complete pending flag is set or not.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return SET : the interrupt flag is set
  *         RESET : the interrupt flag is reset
  */
#define __LL_ECU_DONE_GET_FLAG(__INSTANCE__)                    ((((__INSTANCE__)->CON & (ECU_CON_INT)) == 0x8000UL) ? SET : RESET)

/**
  * @brief  Clear the specified  ECU Calculate complete pending flags.
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return None
  */
#define __LL_ECU_DONE_CLEAR_FLAG(__INSTANCE__)                  SET_BIT((__INSTANCE__)->CON, ECU_CON_INT)

/**
  * @brief  Input data square enable, after the completion of the calculation automatically reset
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return None
  */
#define __LL_ECU_SQRT_ENABLE(__INSTANCE__)                      SET_BIT((__INSTANCE__)->CON, ECU_CON_SQRT)

/**
  * @brief  Gets the square root completion flag
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return RESET That means the square root is complete
  *         SET   That means the square root is not complete
  */
#define __LL_ECU_SQRT_DONE_FLAG(__INSTANCE__)                   ((((__INSTANCE__)->CON & (ECU_CON_SQRT)) == 0x4000UL) ? SET : RESET)

/**
  * @brief  Sets the zero crossing event that needs to be selected
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @param  __EVENT__ cross zero event as follow:
  *         @arg @ref ECU_PSR_CRSSEL_ADC0_PPFLAF0
  *         @arg @ref ECU_PSR_CRSSEL_ADC0_PPFLAG1
  *         @arg @ref ECU_PSR_CRSSEL_ADC0_PPFLAG2
  *         @arg @ref ECU_PSR_CRSSEL_ADC0_PPFLAG3
  *         @arg @ref ECU_PSR_CRSSEL_ADC1_PPFLAG0
  *         @arg @ref ECU_PSR_CRSSEL_ADC1_PPFLAG1
  *         @arg @ref ECU_PSR_CRSSEL_ADC1_PPFLAG2
  *         @arg @ref ECU_PSR_CRSSEL_ADC1_PPFLAG3
  *         @arg @ref ECU_PSR_CRSSEL_TIM0_OC
  *         @arg @ref ECU_PSR_CRSSEL_TIM1_OC
  *         @arg @ref ECU_PSR_CRSSEL_TIM2_OC
  *         @arg @ref ECU_PSR_CRSSEL_TIM3_OC
  *         @arg @ref ECU_PSR_CRSSEL_TIM4_OC
  *         @arg @ref ECU_PSR_CRSSEL_TIM5_OC
  *         @arg @ref ECU_PSR_CRSSEL_TIM6_OC
  *         @arg @ref ECU_PSR_CRSSEL_TIM7_OC
  * @return None
  */
#define __LL_ECU_CROSS_ZERO_EVENT(__INSTANCE__, __EVENT__)      MODIFY_REG((__INSTANCE__)->PRC, ECU_PRC_CRSSEL, __EVENT__)

/**
  * @brief  Sets the data event that needs to be selected
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @param  __EVENT__ cross zero event as follow:
  *         @arg @ref ECU_PSR_DATSEL_ADC0_PPFLAF0
  *         @arg @ref ECU_PSR_DATSEL_ADC0_PPFLAG1
  *         @arg @ref ECU_PSR_DATSEL_ADC0_PPFLAG2
  *         @arg @ref ECU_PSR_DATSEL_ADC0_PPFLAG3
  *         @arg @ref ECU_PSR_DATSEL_ADC1_PPFLAG0
  *         @arg @ref ECU_PSR_DATSEL_ADC1_PPFLAG1
  *         @arg @ref ECU_PSR_DATSEL_ADC1_PPFLAG2
  *         @arg @ref ECU_PSR_DATSEL_ADC1_PPFLAG3
  *         @arg @ref ECU_PSR_DATSEL_TIM0_OC
  *         @arg @ref ECU_PSR_DATSEL_TIM1_OC
  *         @arg @ref ECU_PSR_DATSEL_TIM2_OC
  *         @arg @ref ECU_PSR_DATSEL_TIM3_OC
  *         @arg @ref ECU_PSR_DATSEL_TIM4_OC
  *         @arg @ref ECU_PSR_DATSEL_TIM5_OC
  *         @arg @ref ECU_PSR_DATSEL_TIM6_OC
  *         @arg @ref ECU_PSR_DATSEL_TIM7_OC
  * @return None
  */
#define __LL_ECU_DATA_FLAG_EVENT(__INSTANCE__, __EVENT__)       MODIFY_REG((__INSTANCE__)->PRC, ECU_PRC_DATSEL, __EVENT__)


/**
  * @brief  Sets the addr_data flag event that needs to be selected
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @param  __EVENT__ cross zero event as follow:
  *         @arg @ref ECU_PSR_ADRSEL_ADC0_PPFLAF0
  *         @arg @ref ECU_PSR_ADRSEL_ADC0_PPFLAG1
  *         @arg @ref ECU_PSR_ADRSEL_ADC0_PPFLAG2
  *         @arg @ref ECU_PSR_ADRSEL_ADC0_PPFLAG3
  *         @arg @ref ECU_PSR_ADRSEL_ADC1_PPFLAG0
  *         @arg @ref ECU_PSR_ADRSEL_ADC1_PPFLAG1
  *         @arg @ref ECU_PSR_ADRSEL_ADC1_PPFLAG2
  *         @arg @ref ECU_PSR_ADRSEL_ADC1_PPFLAG3
  *         @arg @ref ECU_PSR_ADRSEL_TIM0_OC
  *         @arg @ref ECU_PSR_ADRSEL_TIM1_OC
  *         @arg @ref ECU_PSR_ADRSEL_TIM2_OC
  *         @arg @ref ECU_PSR_ADRSEL_TIM3_OC
  *         @arg @ref ECU_PSR_ADRSEL_TIM4_OC
  *         @arg @ref ECU_PSR_ADRSEL_TIM5_OC
  *         @arg @ref ECU_PSR_ADRSEL_TIM6_OC
  *         @arg @ref ECU_PSR_ADRSEL_TIM7_OC
  * @return None
  */
#define __LL_ECU_ADDR_FLAG_EVENT(__INSTANCE__, __EVENT__)       MODIFY_REG((__INSTANCE__)->PRC, ECU_PRC_ADRSEL, __EVENT__)

/**
  * @brief  Get the average effective value of the voltage
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return The result of the voltage
  */
#define __LL_ECU_GET_VRMS(__INSTANCE__)                         READ_BIT((__INSTANCE__)->V, ECU_V_VRMS)

/**
  * @brief  Get the average effective value of the current
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return The result of the current
  */
#define __LL_ECU_GET_IRMS(__INSTANCE__)                         READ_BIT((__INSTANCE__)->I, ECU_I_IRMS)

/**
  * @brief  Get the average active power
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return The result of average active power
  */
#define __LL_ECU_P_PAVG(__INSTANCE__)                           READ_REG((__INSTANCE__)->P)

/**
  * @brief  Get the average reactive power
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return The result of average reactive power
  */
#define __LL_ECU_Q_QAVG(__INSTANCE__)                           READ_REG((__INSTANCE__)->Q)

/**
  * @brief  Get the apparent power value
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return The result of apparent power
  */
#define __LL_ECU_S_SCAL(__INSTANCE__)                           READ_REG((__INSTANCE__)->S)

/**
  * @brief  Get the power factor value
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return The result of power factor
  */
#define __LL_ECU_PF_PFCAL(__INSTANCE__)                         READ_REG((__INSTANCE__)->PF)

/**
  * @brief  Get the fundamental frequency value
  * @param  __INSTANCE__ Specifies ECU peripheral
  * @return The result of fundamental frequency
  */
#define __LL_ECU_F_FCNT(__INSTANCE__)                           READ_BIT((__INSTANCE__)->F, ECU_F_FCNT)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup ECU_LL_Exported_Functions
  * @{
  */

/** @addtogroup ECU_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_ECU_Init(ECU_TypeDef *Instance, ECU_InitTypeDef *ECU_Init);
LL_StatusETypeDef LL_ECU_DeInit(ECU_TypeDef *Instance);
void LL_ECU_MspInit(ECU_TypeDef *Instance);
void LL_ECU_MspDeInit(ECU_TypeDef *Instance);
/**
  * @}
  */

/** @addtogroup ECU_LL_Exported_Functions_Group2
  * @{
  */
void LL_ECU_WriteSqrtInData(ECU_TypeDef *Instance, uint32_t SqrtValue);
uint32_t LL_ECU_ReadSqrtOutData(ECU_TypeDef *Instance);
/**
  * @}
  */

/** @addtogroup ECU_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_ECU_IRQHandler(ECU_TypeDef *Instance);
void LL_ECU_CalDoneCallback(ECU_TypeDef *Instance);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup ECU_LL_Private_Macros ECU LL Private Macros
  * @brief    ECU LL Private Macros
  * @{
  */

/**
  * @brief  Judge is ECU enable/disable mode or not
  * @param  __MODE__ mode to judge
  * @retval 0 isn't ECU enable/disable mode
  * @retval 1 is ECU enable/disable mode
  */
#define IS_ECU_MODULE(__MODE__)                            \
    (   ((__MODE__) == ECU_DISABLE)                        \
        || ((__MODE__) == ECU_ENABLE)                      \
    )

/**
  * @brief  Judge is ECU average or not
  * @param  __AVERAGE__ average to judge
  * @retval 0 isn't ECU average
  * @retval 1 is ECU average
  */
#define IS_ECU_AVERAGE(__AVERAGE__)                        \
    (   ((__AVERAGE__) == ECU_AVERAGE_DISABLE)             \
        || ((__AVERAGE__) == ECU_AVERAGE_2PERIOD)          \
        || ((__AVERAGE__) == ECU_AVERAGE_4PERIOD)          \
        || ((__AVERAGE__) == ECU_AVERAGE_8PERIOD)          \
    )

/**
  * @brief  Judge is ECU acsft or not
  * @param  __ACSFT__ acsft to judge
  * @retval 0 isn't ECU acsft
  * @retval 1 is ECU acsft
  */
#define IS_ECU_ACSFT(__ACSFT__)                            \
    (   ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_DISABLE)    \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_1)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_2)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_3)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_4)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_5)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_6)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_7)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_8)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_9)       \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_10)      \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_11)      \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_12)      \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_13)      \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_14)      \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_15)      \
        || ((__ACSFT__) == ECU_ACPOWER_LEFT_SHIFT_16)      \
    )

/**
  * @brief  Judge is ECU apsft or not
  * @param  __APSFT__ apsft to judge
  * @retval 0 isn't ECU apsft
  * @retval 1 is ECU apsft
  */
#define IS_ECU_APSFT(__APSFT__)                            \
    (   ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_DISABLE)   \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_1)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_2)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_3)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_4)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_5)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_6)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_7)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_8)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_9)      \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_10)     \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_11)     \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_12)     \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_13)     \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_14)     \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_15)     \
        || ((__APSFT__) == ECU_APPOWER_RIGHT_SHIFT_16)     \
    )

/**
  * @brief  Judge is ECU datsel or not
  * @param  __DATSEL__ datsel to judge
  * @retval 0 isn't ECU datsel
  * @retval 1 is ECU datsel
  */
#define IS_ECU_DATSEL(__DATSEL__)                          \
    (   ((__DATSEL__) == ECU_PSR_DATSEL_ADC0_DTFLAG0)      \
        || ((__DATSEL__) == ECU_PSR_DATSEL_ADC0_DTFLAG1)   \
        || ((__DATSEL__) == ECU_PSR_DATSEL_ADC0_DTFLAG2)   \
        || ((__DATSEL__) == ECU_PSR_DATSEL_ADC0_DTFLAG3)   \
        || ((__DATSEL__) == ECU_PSR_DATSEL_ADC1_DTFLAG0)   \
        || ((__DATSEL__) == ECU_PSR_DATSEL_ADC1_DTFLAG1)   \
        || ((__DATSEL__) == ECU_PSR_DATSEL_ADC1_DTFLAG2)   \
        || ((__DATSEL__) == ECU_PSR_DATSEL_ADC1_DTFLAG3)   \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM0_OC)        \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM1_OC)        \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM2_OC)        \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM3_OC)        \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM4_OC)        \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM5_OC)        \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM6_OC)        \
        || ((__DATSEL__) == ECU_PSR_DATSEL_TIM7_OC)        \
    )

/**
  * @brief  Judge is ECU crssel or not
  * @param  __CRSSEL__ crssel to judge
  * @retval 0 isn't ECU crssel
  * @retval 1 is ECU crssel
  */
#define IS_ECU_CRSSEL(__CRSSEL__)                          \
    (   ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC0_PPFLAG0)      \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC0_PPFLAG1)   \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC0_PPFLAG2)   \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC0_PPFLAG3)   \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC1_PPFLAG0)   \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC1_PPFLAG1)   \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC1_PPFLAG2)   \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_ADC1_PPFLAG3)   \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM0_OC)        \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM1_OC)        \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM2_OC)        \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM3_OC)        \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM4_OC)        \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM5_OC)        \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM6_OC)        \
        || ((__CRSSEL__) == ECU_PSR_CRSSEL_TIM7_OC)        \
    )

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_ECU_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

