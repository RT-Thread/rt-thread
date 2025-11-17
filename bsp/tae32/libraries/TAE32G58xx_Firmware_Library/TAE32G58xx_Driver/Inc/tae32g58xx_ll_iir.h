/**
  ******************************************************************************
  * @file    tae32g58xx_ll_iir.h
  * @author  MCD Application Team
  * @brief   Header file for IIR LL module
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
#ifndef _TAE32G58XX_LL_IIR_H_
#define _TAE32G58XX_LL_IIR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup IIR_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Macros IIR LL Exported Macros
  * @brief    IIR LL Exported Macros
  * @{
  */

/**
  * @brief  IIR Coef Register offset
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Offset in IIR_Coef_TypeDef type
  * @return IIR_Coef_TypeDef type struct
  */
#define __LL_IIR_COEF_REG_OFFSET(__REG__, offset)        \
    (*((__IO IIR_Coef_TypeDef *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) * (sizeof(IIR_Coef_TypeDef)))))))


/**
  * @brief  IIR Soft Reset
  * @param  __IIR__ Specifies IIR peripheral
  * @return None
  */
#define __LL_IIR_SoftReset(__IIR__)                     SET_BIT((__IIR__)->CR, IIR0_CR_RST_Msk)

/**
  * @brief  Error Interrupt Enable
  * @param  __IIR__ Specifies IIR peripheral
  * @return None
  */
#define __LL_IIR_Err_INT_En(__IIR__)                    SET_BIT((__IIR__)->CR, IIR0_CR_IEE_Msk)

/**
  * @brief  Error Interrupt Disable
  * @param  __IIR__ Specifies IIR peripheral
  * @return None
  */
#define __LL_IIR_Err_INT_Dis(__IIR__)                   CLEAR_BIT((__IIR__)->CR, IIR0_CR_IEE_Msk)

/**
  * @brief  Judge is Error Interrupt Enable or not
  * @param  __IIR__ Specifies IIR peripheral
  * @retval 0 Error Interrupt is Disable
  * @retval 1 Error Interrupt is Enable
  */
#define __LL_IIR_IsErrIntEn(__IIR__)                    READ_BIT_SHIFT((__IIR__)->CR, IIR0_CR_IEE_Msk, IIR0_CR_IEE_Pos)

/**
  * @brief  IIR Ordef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @parma  order IIR Order
  * @return None
  */
#define __LL_IIR_Order_Set(__IIR__, order)              \
        MODIFY_REG((__IIR__)->CR, IIR0_CR_ORD_Msk, (((order) & 0x3UL) << IIR0_CR_ORD_Pos))


/**
  * @brief  IIR Enable
  * @param  __IIR__ Specifies IIR peripheral
  * @return None
  */
#define __LL_IIR_En(__IIR__)                            SET_BIT((__IIR__)->CR, IIR0_CR_IEN_Msk)


/**
  * @brief  IIR Disable
  * @param  __IIR__ Specifies IIR peripheral
  * @return None
  */
#define __LL_IIR_Dis(__IIR__)                           CLEAR_BIT((__IIR__)->CR, IIR0_CR_IEN_Msk)


/**
  * @brief  Judge is IIR Busy or not
  * @param  __IIR__ Specifies IIR peripheral
  * @retval 0 IIR is Idle
  * @retval 1 IIR is Busy
  */
#define __LL_IIR_IsBusy(__IIR__)                        READ_BIT_SHIFT((__IIR__)->ISR, IIR0_ISR_BSY_Msk, IIR0_ISR_BSY_Pos)

/**
  * @brief  Judge is Error Interrupt Pending or not
  * @param  __IIR__ Specifies IIR peripheral
  * @retval 0 isn't Error Interrupt Pending
  * @retval 1 is Error Interrupt Pending
  */
#define __LL_IIR_IsErrIntPnd(__IIR__)                   READ_BIT_SHIFT((__IIR__)->ISR, IIR0_ISR_ERR_Msk, IIR0_ISR_ERR_Pos)

/**
  * @brief  Error Interrupt Pending Clear
  * @param  __IIR__ Specifies IIR peripheral
  * @return None
  */
#define __LL_IIR_ErrIntPnd_Clr(__IIR__)                 WRITE_REG((__IIR__)->ISR, IIR0_ISR_ERR_Msk)


/**
  * @brief  Input Data Write
  * @param  __IIR__ Specifies IIR peripheral
  * @param  dat Input Data
  * @return None
  */
#define __LL_IIR_InputDat_Write(__IIR__, dat)           WRITE_REG((__IIR__)->IDR, ((dat) & 0xffffUL))


/**
  * @brief  Output Data Read
  * @param  __IIR__ Specifies IIR peripheral
  * @return 16 bits Output Data
  */
#define __LL_IIR_OutputDat_Read(__IIR__)                READ_BIT_SHIFT((__IIR__)->ODR, IIR0_ODR_OD_Msk, IIR0_ODR_OD_Pos)


/**
  * @brief  High-order Output Scale Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  scale High-order Output Scale
  * @return None
  */
#define __LL_IIR_HighOrderOutputScale_Set(__IIR__, scale)             \
        MODIFY_REG((__IIR__)->SCL, IIR0_SCL_OSCL1_Msk, (((scale) & 0x1fUL) << IIR0_SCL_OSCL1_Pos))

/**
  * @brief  High-order Output Scale Get
  * @param  __IIR__ Specifies IIR peripheral
  * @param  scale High-order Output Scale
  * @return None
  */
#define __LL_IIR_HighOrderOutputScale_Get(__IIR__)             \
        READ_BIT_SHIFT((__IIR__)->SCL, IIR0_SCL_OSCL1_Msk, IIR0_SCL_OSCL1_Pos)

/**
  * @brief  High-order Feedback Scale Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  scale High-order Feedback Scale
  * @return None
  */
#define __LL_IIR_HighOrderFbScale_Set(__IIR__, scale)                 \
        MODIFY_REG((__IIR__)->SCL, IIR0_SCL_FSCL1_Msk, (((scale) & 0x1fUL) << IIR0_SCL_FSCL1_Pos))

/**
  * @brief  High-order Feedback Scale Get
  * @param  __IIR__ Specifies IIR peripheral
  * @return High-order Feedback Scale
  */
#define __LL_IIR_HighOrderFbScale_Get(__IIR__)                        \
        READ_BIT_SHIFT((__IIR__)->SCL, IIR0_SCL_FSCL1_Msk, IIR0_SCL_FSCL1_Pos)

/**
  * @brief  Output Scale Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  scale Output Scale
  * @return None
  */
#define __LL_IIR_OutputScale_Set(__IIR__, scale)                      \
        MODIFY_REG((__IIR__)->SCL, IIR0_SCL_OSCL0_Msk, (((scale) & 0x1fUL) << IIR0_SCL_OSCL0_Pos))

/**
  * @brief  Feedback Scale Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  scale Feedback Scale
  * @return None
  */
#define __LL_IIR_FbScale_Set(__IIR__, scale)                                 \
        MODIFY_REG((__IIR__)->SCL, IIR0_SCL_FSCL0_Msk, (((scale) & 0x1fUL) << IIR0_SCL_FSCL0_Pos))

/**
  * @brief  B0 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  b0 B0 Coef
  * @return None
  */
#define __LL_IIR_B0Coef_Set(__IIR__, b0)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNB0R, ((b0) & 0x7ffffffUL))


/**
  * @brief  B1 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  b1 B1 Coef
  * @return None
  */
#define __LL_IIR_B1Coef_Set(__IIR__, b1)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNB1R, ((b1) & 0x7ffffffUL))


/**
  * @brief  B2 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  b2 B2 Coef
  * @return None
  */
#define __LL_IIR_B2Coef_Set(__IIR__, b2)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNB2R, ((b2) & 0x7ffffffUL))


/**
  * @brief  B3 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  b3 B3 Coef
  * @return None
  */
#define __LL_IIR_B3Coef_Set(__IIR__, b3)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNB3R, ((b3) & 0x7ffffffUL))


/**
  * @brief  B4 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  b4 B4 Coef
  * @return None
  */
#define __LL_IIR_B4Coef_Set(__IIR__, b4)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNB4R, ((b4) & 0x7ffffffUL))


/**
  * @brief  B5 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  b5 B5 Coef
  * @return None
  */
#define __LL_IIR_B5Coef_Set(__IIR__, b5)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNB5R, ((b5) & 0x7ffffffUL))


/**
  * @brief  A1 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  a1 A1 Coef
  * @return None
  */
#define __LL_IIR_A1Coef_Set(__IIR__, a1)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNA1R, ((a1) & 0x7ffffffUL))


/**
  * @brief  A2 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  a2 A2 Coef
  * @return None
  */
#define __LL_IIR_A2Coef_Set(__IIR__, a2)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNA2R, ((a2) & 0x7ffffffUL))


/**
  * @brief  A3 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  a3 A3 Coef
  * @return None
  */
#define __LL_IIR_A3Coef_Set(__IIR__, a3)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNA3R, ((a3) & 0x7ffffffUL))


/**
  * @brief  A4 Coef Set
  * @param  __IIR__ Specifies IIR peripheral
  * @param  a4 A4 Coef
  * @return None
  */
#define __LL_IIR_A4Coef_Set(__IIR__, a4)   WRITE_REG(__LL_IIR_COEF_REG_OFFSET((__IIR__)->G0B0R, IIR_COEF_GRP_NUM_1).GNA4R, ((a4) & 0x7ffffffUL))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup IIR_LL_Exported_Types IIR LL Exported Types
  * @brief    IIR LL Exported Types
  * @{
  */

/**
  * @brief IIR Coef Group Number Definition
  * @warning Please note that the TAE32G5800 chip NO longer support the multi-group coefficient function.
  *          It means that only one group of coefficients is available for configuration.
  */
typedef enum {
    IIR_COEF_GRP_AUTO = -1,     /*!< IIR Coef Group Auto */

    IIR_COEF_GRP_NUM_1 = 0,     /*!< IIR Coef Group Number 1    */
    IIR_COEF_GRP_NUMS,          /*!< IIR Coef Group Numbers     */
} IIR_CoefGrpNumETypeDef;

/**
  * @brief IIR Order Definition
  * @note  IIR0/1/2 Max Order is 4, IIR3/4/5 Max Order is 2
  */
typedef enum {
    IIR_ORDER_1 = 0,            /*!< IIR Order 1    */
    IIR_ORDER_2,                /*!< IIR Order 2    */
    IIR_ORDER_3,                /*!< IIR Order 3    */
    IIR_ORDER_4,                /*!< IIR Order 4    */
} IIR_OrderETypeDef;

/**
  * @brief IIR Scale Definition
  */
typedef enum {
    IIR_SCALE_2_POWER_0 = 0,    /*!< IIR Scale 2 Power 0    */
    IIR_SCALE_2_POWER_1,        /*!< IIR Scale 2 Power 1    */
    IIR_SCALE_2_POWER_2,        /*!< IIR Scale 2 Power 2    */
    IIR_SCALE_2_POWER_3,        /*!< IIR Scale 2 Power 3    */
    IIR_SCALE_2_POWER_4,        /*!< IIR Scale 2 Power 4    */
    IIR_SCALE_2_POWER_5,        /*!< IIR Scale 2 Power 5    */
    IIR_SCALE_2_POWER_6,        /*!< IIR Scale 2 Power 6    */
    IIR_SCALE_2_POWER_7,        /*!< IIR Scale 2 Power 7    */
    IIR_SCALE_2_POWER_8,        /*!< IIR Scale 2 Power 8    */
    IIR_SCALE_2_POWER_9,        /*!< IIR Scale 2 Power 9    */
    IIR_SCALE_2_POWER_10,       /*!< IIR Scale 2 Power 10   */
    IIR_SCALE_2_POWER_11,       /*!< IIR Scale 2 Power 11   */
    IIR_SCALE_2_POWER_12,       /*!< IIR Scale 2 Power 12   */
    IIR_SCALE_2_POWER_13,       /*!< IIR Scale 2 Power 13   */
    IIR_SCALE_2_POWER_14,       /*!< IIR Scale 2 Power 14   */
    IIR_SCALE_2_POWER_15,       /*!< IIR Scale 2 Power 15   */
    IIR_SCALE_2_POWER_16,       /*!< IIR Scale 2 Power 16   */
    IIR_SCALE_2_POWER_17,       /*!< IIR Scale 2 Power 17   */
    IIR_SCALE_2_POWER_18,       /*!< IIR Scale 2 Power 18   */
    IIR_SCALE_2_POWER_19,       /*!< IIR Scale 2 Power 19   */
    IIR_SCALE_2_POWER_20,       /*!< IIR Scale 2 Power 20   */
    IIR_SCALE_2_POWER_21,       /*!< IIR Scale 2 Power 21   */
    IIR_SCALE_2_POWER_22,       /*!< IIR Scale 2 Power 22   */
    IIR_SCALE_2_POWER_23,       /*!< IIR Scale 2 Power 23   */
    IIR_SCALE_2_POWER_24,       /*!< IIR Scale 2 Power 24   */
    IIR_SCALE_2_POWER_25,       /*!< IIR Scale 2 Power 25   */
    IIR_SCALE_2_POWER_26,       /*!< IIR Scale 2 Power 26   */
    IIR_SCALE_2_POWER_27,       /*!< IIR Scale 2 Power 27   */
    IIR_SCALE_2_POWER_28,       /*!< IIR Scale 2 Power 28   */
    IIR_SCALE_2_POWER_29,       /*!< IIR Scale 2 Power 29   */
    IIR_SCALE_2_POWER_30,       /*!< IIR Scale 2 Power 30   */
    IIR_SCALE_2_POWER_31,       /*!< IIR Scale 2 Power 31   */
} IIR_ScaleETypeDef;


/**
  * @brief IIR Coef type definition
  */
typedef struct __IIR_CoefTypeDef {
    int32_t Bx[6];          /*!< Coef B0~B5     */
    int32_t Ax[4];          /*!< Coef A1~B4     */
} IIR_CoefTypeDef;


/**
  * @brief IIR user config type definition
  */
typedef struct __IIR_UserCfgTypeDef {
    IIR_OrderETypeDef order;                    /*!< Order Selection                  */
    IIR_ScaleETypeDef out_scale;                /*!< Output Scale                     */
    IIR_ScaleETypeDef fb_scale;                 /*!< Feedback Scale                   */
    IIR_CoefTypeDef   coef;                     /*!< GroupN Coef                      */
    IIR_ScaleETypeDef hi_out_scale;             /*!< High Order Filter Output Scale   */
    IIR_ScaleETypeDef hi_fb_scale;              /*!< High Order Filter Feedback Scale */    
} IIR_UserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup IIR_LL_Exported_Functions
  * @{
  */

/** @addtogroup IIR_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_IIR_Init(IIR_TypeDef *Instance);
LL_StatusETypeDef LL_IIR_DeInit(IIR_TypeDef *Instance);
void LL_IIR_MspInit(IIR_TypeDef *Instance);
void LL_IIR_MspDeInit(IIR_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup IIR_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_IIR_Config(IIR_TypeDef *Instance, IIR_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_IIR_Reset(IIR_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup IIR_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_IIR_Calc_Once(IIR_TypeDef *Instance, int16_t dat_in, int16_t *dat_out,
                                   uint32_t timeout);
uint32_t LL_IIR_Calc_Multi(IIR_TypeDef *Instance, const int16_t *dat_in, uint32_t dat_nums,
                           int16_t *dat_out, uint32_t timeout);
/**
  * @}
  */


/** @addtogroup IIR_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_IIR_IRQHandler(IIR_TypeDef *Instance);
void LL_IIR_ErrCallback(IIR_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_IIR_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

