/**
  ******************************************************************************
  * @file    tae32g58xx_ll_cordic.h
  * @author  MCD Application Team
  * @brief   Header file for CORDIC LL module
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
#ifndef _TAE32G58XX_LL_CORDIC_H_
#define _TAE32G58XX_LL_CORDIC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup CORDIC_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Constants CORDIC LL Exported Constants
  * @brief    CORDIC LL Exported Constants
  * @{
  */

/**
  * @brief CORDIC Scale Max Definition
  */
#define CORDIC_SCALE_MAX        (7U)
#define CORDIC_SCALE_MAX_VD     (31U)

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Macros CORDIC LL Exported Macros
  * @brief    CORDIC LL Exported Macros
  * @{
  */

/**
  * @brief  CORDIC Channel Register offset
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Offset in CORDIC_CH_TypeDef type
  * @return CORDIC_CH_TypeDef type struct
  */
#define __LL_CORDIC_CH_REG_OFFSET(__REG__, offset)              \
    (*((__IO CORDIC_CH_TypeDef *)((uint32_t) ((uint32_t)(&(__REG__)) + ((offset) * (sizeof(CORDIC_CH_TypeDef)))))))



/**
  * @brief  Judge is Complete pending or not
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @retval 0 isn't Complete pending
  * @retval 1 is Complete pending
  */
#define __LL_CORDIC_IsCpltPnd(__CORDIC__, ch)                   \
        READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_RRDY_Msk, CORDIC_CSR0_RRDY_Pos)

/**
  * @brief  Complete pending clear
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return None
  */
#define __LL_CORDIC_CpltPnd_Clr(__CORDIC__, ch)                 \
        MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_RRDYCLR_Msk | CORDIC_CSR0_ERRCLR_Msk, CORDIC_CSR0_RRDYCLR_Msk)

/**
  * @brief  Judge is Error pending or not
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @retval 0 isn't Error pending
  * @retval 1 is Error pending
  */
#define __LL_CORDIC_IsErrtPnd(__CORDIC__, ch)                   \
        READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_ERR_Msk, CORDIC_CSR0_ERR_Pos)

/**
  * @brief  Error pending clear
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return None
  */
#define __LL_CORDIC_ErrPnd_Clr(__CORDIC__, ch)                  \
        MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_RRDYCLR_Msk | CORDIC_CSR0_ERRCLR_Msk, CORDIC_CSR0_ERRCLR_Msk)

/**
  * @brief  Input data width set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  width Input data width
  * @return None
  */
#define __LL_CORDIC_InputDatWidth_Set(__CORDIC__, ch, width)    \
        MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_ARGSIZE_Msk, (((width) & 0x1UL) << CORDIC_CSR0_ARGSIZE_Pos))

/**
  * @brief  Input data width Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @retval 0 Input data width is 32bit
  * @retval 1 Input data width is 16bit
  */
#define __LL_CORDIC_InputDatWidth_Get(__CORDIC__, ch)           \
        READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_ARGSIZE_Msk, CORDIC_CSR0_ARGSIZE_Pos)

/**
  * @brief  Output data width set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  width Output data width
  * @return None
  */
#define __LL_CORDIC_OutputDatWidth_Set(__CORDIC__, ch, width)   \
        MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_RESSIZE_Msk, (((width) & 0x1UL) << CORDIC_CSR0_RESSIZE_Pos))

/**
  * @brief  Output data width Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @retval 0 Output data width is 32bit
  * @retval 1 Output data width is 16bit
  */
#define __LL_CORDIC_OutputDatWidth_Get(__CORDIC__, ch)          \
        READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_RESSIZE_Msk, CORDIC_CSR0_RESSIZE_Pos)

/**
  * @brief  Input data number set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  num Input data number
  * @return None
  */
#define __LL_CORDIC_InputDatNum_Set(__CORDIC__, ch, num)        \
        MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_NARGS_Msk, (((num) & 0x1UL) << CORDIC_CSR0_NARGS_Pos))

/**
  * @brief  Input data number Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @retval 0 Input data number is one 32bit or two 16bit
  * @retval 1 Input data number is two 32bit
  */
#define __LL_CORDIC_InputDatNum_Get(__CORDIC__, ch)             \
        READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_NARGS_Msk, CORDIC_CSR0_NARGS_Pos)

/**
  * @brief  Output data number set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  num Output data number
  * @return None
  */
#define __LL_CORDIC_OutputDatNum_Set(__CORDIC__, ch, num)       \
        MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_NRES_Msk, (((num) & 0x1UL) << CORDIC_CSR0_NRES_Pos))

/**
  * @brief  Output data number Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @retval 0 Output data number is one 32bit or two 16bit
  * @retval 1 Output data number is two 32bit
  */
#define __LL_CORDIC_OutputDatNum_Get(__CORDIC__, ch)            \
        READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_NRES_Msk, CORDIC_CSR0_NRES_Pos)

/**
  * @brief  Error Interrupt Enable
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return None
  */
#define __LL_CORDIC_Err_Int_En(__CORDIC__, ch)                  \
        SET_BIT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR, CORDIC_CSR0_ERRIEN_Msk)

/**
  * @brief  Error Interrupt Disable
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return None
  */
#define __LL_CORDIC_Err_Int_Dis(__CORDIC__, ch)                 \
        CLEAR_BIT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR, CORDIC_CSR0_ERRIEN_Msk)

/**
  * @brief  Complete Interrupt Enable
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return None
  */
#define __LL_CORDIC_Cplt_Int_En(__CORDIC__, ch)                 \
        SET_BIT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR, CORDIC_CSR0_RRDYIEN_Msk)

/**
  * @brief  Complete Interrupt Disable
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return None
  */
#define __LL_CORDIC_Cplt_Int_Dis(__CORDIC__, ch)                \
        CLEAR_BIT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR, CORDIC_CSR0_RRDYIEN_Msk)

/**
  * @brief  Argument/Result Scale Set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @param  scale Argument/Result Scale
  * @return None
  */
#define __LL_CORDIC_Scale_Set(__CORDIC__, ch, scale)            \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?             \
        (MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
                0x1f00UL, (((scale) & 0x1fUL) << 8UL))) :       \
        (MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
                0x700UL, (((scale) & 0x7UL) << 8UL))))


/**
  * @brief  Argument/Result Scale Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return Argument/Result Scale
  */
#define __LL_CORDIC_Scale_Get(__CORDIC__, ch)                   \
        ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ?             \
        (READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR, 0x1f00UL, 8UL)) : \
        (READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR, 0x700UL, 8UL)) )

/**
  * @brief  Calculate function Set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @paran  func Calculate function
  * @return None
  */
#define __LL_CORDIC_CalcFunc_Set(__CORDIC__, ch, func)          \
        MODIFY_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_FUNC_Msk, (((func) & 0xfUL) << CORDIC_CSR0_FUNC_Pos))

/**
  * @brief  Calculate function Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return Calculate function
  */
#define __LL_CORDIC_CalcFunc_Get(__CORDIC__, ch)                \
        READ_BIT_SHIFT(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_FUNC_Msk, CORDIC_CSR0_FUNC_Pos)

/**
  * @brief  All config reset
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return None
  */
#define __LL_CORDIC_ChAllCfg_Reset(__CORDIC__, ch)              \
        WRITE_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).CSR,\
        CORDIC_CSR0_RRDYCLR_Msk | CORDIC_CSR0_ERRCLR_Msk)


/**
  * @brief  Argument 1 Set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @paran  arg1 Argument 1
  * @return None
  */
#define __LL_CORDIC_Arg1_Set(__CORDIC__, ch, arg1)              \
        WRITE_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).ARX, arg1)

/**
  * @brief  Result 1 Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return Result 1
  */
#define __LL_CORDIC_Res1_Get(__CORDIC__, ch)                    \
        READ_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).ARX)


/**
  * @brief  Argument 2 Set
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @paran  arg2 Argument 2
  * @return None
  */
#define __LL_CORDIC_Arg2_Set(__CORDIC__, ch, arg2)              \
        WRITE_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).ARY, arg2)

/**
  * @brief  Result 2 Get
  * @param  __CORDIC__ Specifies CORDIC peripheral
  * @param  ch CORDIC channel
  * @return Result 2
  */
#define __LL_CORDIC_Res2_Get(__CORDIC__, ch)                    \
        READ_REG(__LL_CORDIC_CH_REG_OFFSET((__CORDIC__)->CSR0, (uint32_t)(ch) % CORDIC_CHANNEL_NUMS).ARY)


/**
  * @brief  Judge is CORDIC Channel valid or not
  * @param  ch CORDIC channel @ref CORDIC_ChannelETypeDef
  * @retval 0 CORDIC Channel is invalid
  * @retval 1 CORDIC Channel is valid
  */
#define __LL_CORDIC_IsChannelValid(ch)                          ((ch) < CORDIC_CHANNEL_NUMS)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Types CORDIC LL Exported Types
  * @brief    CORDIC LL Exported Types
  * @{
  */

/**
  * @brief CORDIC Channel definition
  */
typedef enum {
    CORDIC_CHANNEL_0 = 0,               /*!< CORDIC Channel 0       */
    CORDIC_CHANNEL_1,                   /*!< CORDIC Channel 1       */
    CORDIC_CHANNEL_NUMS,                /*!< CORDIC Channel Numbers */
    CORDIC_CHANNEL_INVALID = 0xFF,      /*!< CORDIC Channel Invalid */
} CORDIC_ChannelETypeDef;

/**
  * @brief CORDIC Data Width definition
  */
typedef enum {
    CORDIC_DAT_WIDTH_32bit = 0,         /*!< CORDIC data width 32bit */
    CORDIC_DAT_WIDTH_16bit,             /*!< CORDIC data width 16bit */
} CORDIC_DatWidthETypeDef;

/**
  * @brief CORDIC Data Number definition
  */
typedef enum {
    CORDIC_DAT_NUM_TWO_16bit = 0,       /*!< CORDIC data number Two 16bit   */
    CORDIC_DAT_NUM_ONE_32bit = 0,       /*!< CORDIC data number One 32bit   */
    CORDIC_DAT_NUM_TWO_32bit,           /*!< CORDIC data number Two 32bit   */
} CORDIC_DatNumETypeDef;

/**
  * @brief CORDIC Calculate Function definition
  */
typedef enum {
    CORDIC_FUNC_COS = 0,                /*!< CORDIC Calculate Function Cosine               */
    CORDIC_FUNC_SIN,                    /*!< CORDIC Calculate Function Sine                 */
    CORDIC_FUNC_PHASE,                  /*!< CORDIC Calculate Function Phase                */
    CORDIC_FUNC_MODULUS,                /*!< CORDIC Calculate Function Modulus              */
    CORDIC_FUNC_ARCTAN,                 /*!< CORDIC Calculate Function Arctangent           */
    CORDIC_FUNC_COSH,                   /*!< CORDIC Calculate Function Hyperbolic cosine    */
    CORDIC_FUNC_SINH,                   /*!< CORDIC Calculate Function Hyperbolic sine      */
    CORDIC_FUNC_ARCTANH,                /*!< CORDIC Calculate Function Arctanh              */
    CORDIC_FUNC_LOGN,                   /*!< CORDIC Calculate Function Natural logarithm    */
    CORDIC_FUNC_SQRT,                   /*!< CORDIC Calculate Function Square Root          */
} CORDIC_FuncETypeDef;


/**
  * @brief CORDIC user config type definition
  */
typedef struct __CORDIC_UserCfgTypeDef {
    CORDIC_DatWidthETypeDef arg_width;  /*!< Argument width     */
    CORDIC_DatWidthETypeDef res_width;  /*!< Result width       */
    CORDIC_DatNumETypeDef   arg_num;    /*!< Argument number    */
    CORDIC_DatNumETypeDef   res_num;    /*!< Result number      */
    CORDIC_FuncETypeDef     func;       /*!< Calculate function */
    uint8_t                 scale;      /*!< Scale              */
} CORDIC_UserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup CORDIC_LL_Exported_Functions
  * @{
  */

/** @addtogroup CORDIC_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_CORDIC_Init(CORDIC_TypeDef *Instance);
LL_StatusETypeDef LL_CORDIC_DeInit(CORDIC_TypeDef *Instance);
void LL_CORDIC_MspInit(CORDIC_TypeDef *Instance);
void LL_CORDIC_MspDeInit(CORDIC_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup CORDIC_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_CORDIC_Config(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, CORDIC_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_CORDIC_Reset(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch);
/**
  * @}
  */


/** @addtogroup CORDIC_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_CORDIC_Start_16(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int16_t arg1, int16_t arg2);
LL_StatusETypeDef LL_CORDIC_Start_One32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t arg1);
LL_StatusETypeDef LL_CORDIC_Start_Two32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch, int32_t arg1, int32_t arg2);
LL_StatusETypeDef LL_CORDIC_GetResult_16(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int16_t *res1, int16_t *res2, uint32_t timeout);
LL_StatusETypeDef LL_CORDIC_GetResult_One32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *res1, uint32_t timeout);
LL_StatusETypeDef LL_CORDIC_GetResult_Two32(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *res1, int32_t *res2, uint32_t timeout);

LL_StatusETypeDef LL_CORDIC_Calculate_SingleCh(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout);
LL_StatusETypeDef LL_CORDIC_Calculate_SingleCh_ZO(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout);
LL_StatusETypeDef LL_CORDIC_Calculate_MixCh(CORDIC_TypeDef *Instance,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout);
LL_StatusETypeDef LL_CORDIC_Calculate_MixCh_ZO(CORDIC_TypeDef *Instance,
        int32_t *in_buf, int32_t *out_buf, uint32_t num_calc, uint32_t timeout);
/**
  * @}
  */


/** @addtogroup CORDIC_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_CORDIC_IRQHandler(CORDIC_TypeDef *Instance);
void LL_CORDIC_CpltCallback(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch);
void LL_CORDIC_ErrCallback(CORDIC_TypeDef *Instance, CORDIC_ChannelETypeDef ch);
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

#endif /* _TAE32G58XX_LL_CORDIC_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

