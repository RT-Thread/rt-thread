/**
  ******************************************************************************
  * @file    tae32f53xx_ll_lvdctrl.h
  * @author  MCD Application Team
  * @brief   Head file for LVDCTRL LL Module
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
#ifndef _TAE32F53XX_LL_LVDCTRL_H_
#define _TAE32F53XX_LL_LVDCTRL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup LVDCTRL_LL
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup LVDCTRL_LL_Exported_Macros LVDCTRL LL Exported Macros
  * @brief    LVDCTRL LL Exported Macros
  * @{
  */

/**
  * @brief  Judge VDD Over Current or not
  * @param  __LVD__ Specifies LVD peripheral
  * @retval 0 VDD isn't Over Current
  * @retval 1 VDD is Over Current
  */
#define __LL_LVDCTRL_IsVDDOverCur(__LVD__)      (READ_BIT((__LVD__)->LACR, LVDCTRL_VDDOC_ST_Msk) >> LVDCTRL_VDDOC_ST_Pos)

/**
  * @brief  Judge VDD Low Voltage or not
  * @param  __LVD__ Specifies LVD peripheral
  * @retval 0 VDD isn't Low Voltage
  * @retval 1 VDD is Low Voltage
  */
#define __LL_LVDCTRL_IsVDDLowVol(__LVD__)       (READ_BIT((__LVD__)->LACR, LVDCTRL_VDDLV_ST_Msk) >> LVDCTRL_VDDLV_ST_Pos)

/**
  * @brief  Judge VCC Low Voltage or not
  * @param  __LVD__ Specifies LVD peripheral
  * @retval 0 VCC isn't Low Voltage
  * @retval 1 VCC is Low Voltage
  */
#define __LL_LVDCTRL_IsVCCLowVol(__LVD__)       (READ_BIT((__LVD__)->LACR, LVDCTRL_VCCLV_ST_Msk) >> LVDCTRL_VCCLV_ST_Pos)

/**
  * @brief  Judge AVCC Low Voltage or not
  * @param  __LVD__ Specifies LVD peripheral
  * @retval 0 AVCC isn't Low Voltage
  * @retval 1 AVCC is Low Voltage
  */
#define __LL_LVDCTRL_IsAVCCLowVol(__LVD__)      (READ_BIT((__LVD__)->LACR, LVDCTRL_AVCCLV_ST_Msk) >> LVDCTRL_AVCCLV_ST_Pos)

/**
  * @brief  VDD Over Current Bypass Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurByp_En(__LVD__)             SET_BIT((__LVD__)->LACR, LVDCTRL_VDDOC_BYP_EN_Msk)

/**
  * @brief  VDD Over Current Bypass Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurByp_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LACR, LVDCTRL_VDDOC_BYP_EN_Msk)

/**
  * @brief  VDD Low Voltage Bypass Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolByp_En(__LVD__)              SET_BIT((__LVD__)->LACR, LVDCTRL_VDDLV_BYP_EN_Msk)

/**
  * @brief  VDD Low Voltage Bypass Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolByp_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LACR, LVDCTRL_VDDLV_BYP_EN_Msk)

/**
  * @brief  VCC Low Voltage Bypass Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolByp_En(__LVD__)              SET_BIT((__LVD__)->LACR, LVDCTRL_VCCLV_BYP_EN_Msk)

/**
  * @brief  VCC Low Voltage Bypass Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolByp_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LACR, LVDCTRL_VCCLV_BYP_EN_Msk)

/**
  * @brief  AVCC Low Voltage Bypass Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolByp_En(__LVD__)             SET_BIT((__LVD__)->LACR, LVDCTRL_AVCCLV_BYP_EN_Msk)

/**
  * @brief  AVCC Low Voltage Bypass Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolByp_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LACR, LVDCTRL_AVCCLV_BYP_EN_Msk)

/**
  * @brief  Analog Input Signal Debounce Limit Set
  * @param  __LVD__ Specifies LVD peripheral
  * @param  limit  Analog Input Signal Debounce Limit
  * @return None
  */
#define __LL_LVDCTRL_AnalogInDbcLimit_Set(__LVD__, limit)   \
        MODIFY_REG((__LVD__)->LACR, LVDCTRL_ANAIN_DBC_LIMIT_Msk, ((limit & 0xffUL) << LVDCTRL_ANAIN_DBC_LIMIT_Pos))

/**
  * @brief  VCC Low Voltage Threshold Set
  * @param  __LVD__ Specifies LVD peripheral
  * @param  thres VCC Low Voltage Threshold
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolThres_Set(__LVD__, thres)    MODIFY_REG((__LVD__)->LACR, LVDCTRL_VCCLV_SET_Msk, thres)

/**
  * @brief  AVCC Low Voltage Threshold Set
  * @param  __LVD__ Specifies LVD peripheral
  * @param  thres AVCC Low Voltage Threshold
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolThres_Set(__LVD__, thres)   MODIFY_REG((__LVD__)->LACR, LVDCTRL_AVCCLV_SET_Msk, thres)

/**
  * @brief  VDD Over Current Threshold Set
  * @param  __LVD__ Specifies LVD peripheral
  * @param  thres VDD Over Current Threshold
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurThres_Set(__LVD__, thres)   MODIFY_REG((__LVD__)->LACR, LVDCTRL_VDDOC_SET_Msk, thres)

/**
  * @brief  VDD Low Voltage Threshold Set
  * @param  __LVD__ Specifies LVD peripheral
  * @param  thres VDD Low Voltage Threshold
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolThres_Set(__LVD__, thres)    MODIFY_REG((__LVD__)->LACR, LVDCTRL_VDDLV_SET_Msk, thres)

/**
  * @brief  VCC Low Voltage Detect Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolDet_En(__LVD__)              SET_BIT((__LVD__)->LACR, LVDCTRL_VCCLV_EN_Msk)

/**
  * @brief  VCC Low Voltage Detect Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolDet_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LACR, LVDCTRL_VCCLV_EN_Msk)

/**
  * @brief  AVCC Low Voltage Detect Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolDet_En(__LVD__)             SET_BIT((__LVD__)->LACR, LVDCTRL_AVCCLV_EN_Msk)

/**
  * @brief  AVCC Low Voltage Detect Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolDet_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LACR, LVDCTRL_AVCCLV_EN_Msk)

/**
  * @brief  VDD Over Current Detect Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurDet_En(__LVD__)             SET_BIT((__LVD__)->LACR, LVDCTRL_VDDOC_EN_Msk)

/**
  * @brief  VDD Over Current Detect Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurDet_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LACR, LVDCTRL_VDDOC_EN_Msk)

/**
  * @brief  VDD Low Voltage Detect Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolDet_En(__LVD__)              SET_BIT((__LVD__)->LACR, LVDCTRL_VDDLV_EN_Msk)

/**
  * @brief  VDD Low Voltage Detect Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolDet_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LACR, LVDCTRL_VDDLV_EN_Msk)


/**
  * @brief  VDD Over Current Braking Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurBrk_En(__LVD__)             SET_BIT((__LVD__)->LCR, LVDCTRL_VDDOC_BRK_EN_Msk)

/**
  * @brief  VDD Over Current Braking Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurBrk_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VDDOC_BRK_EN_Msk)

/**
  * @brief  VDD Low Voltage Braking Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolBrk_En(__LVD__)              SET_BIT((__LVD__)->LCR, LVDCTRL_VDDLV_BRK_EN_Msk)

/**
  * @brief  VDD Low Voltage Braking Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolBrk_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VDDLV_BRK_EN_Msk)

/**
  * @brief  VCC Low Voltage Braking Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolBrk_En(__LVD__)              SET_BIT((__LVD__)->LCR, LVDCTRL_VCCLV_BRK_EN_Msk)

/**
  * @brief  VCC Low Voltage Braking Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolBrk_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VCCLV_BRK_EN_Msk)

/**
  * @brief  AVCC Low Voltage Braking Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolBrk_En(__LVD__)             SET_BIT((__LVD__)->LCR, LVDCTRL_AVCCLV_BRK_EN_Msk)

/**
  * @brief  AVCC Low Voltage Braking Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolBrk_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LCR, LVDCTRL_AVCCLV_BRK_EN_Msk)

/**
  * @brief  VDD Over Current Interrupt Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurInt_En(__LVD__)             SET_BIT((__LVD__)->LCR, LVDCTRL_VDDOC_INT_EN_Msk)

/**
  * @brief  VDD Over Current Interrupt Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurInt_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VDDOC_INT_EN_Msk)

/**
  * @brief  VDD Low Voltage Interrupt Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolInt_En(__LVD__)              SET_BIT((__LVD__)->LCR, LVDCTRL_VDDLV_INT_EN_Msk)

/**
  * @brief  VDD Low Voltage Interrupt Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolInt_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VDDLV_INT_EN_Msk)

/**
  * @brief  VCC Low Voltage Interrupt Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolInt_En(__LVD__)              SET_BIT((__LVD__)->LCR, LVDCTRL_VCCLV_INT_EN_Msk)

/**
  * @brief  VCC Low Voltage Interrupt Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolInt_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VCCLV_INT_EN_Msk)

/**
  * @brief  AVCC Low Voltage Interrupt Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolInt_En(__LVD__)             SET_BIT((__LVD__)->LCR, LVDCTRL_AVCCLV_INT_EN_Msk)

/**
  * @brief  AVCC Low Voltage Interrupt Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolInt_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LCR, LVDCTRL_AVCCLV_INT_EN_Msk)

/**
  * @brief  VDD Over Current Reset Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurRst_En(__LVD__)             SET_BIT((__LVD__)->LCR, LVDCTRL_VDDOC_RST_EN_Msk)

/**
  * @brief  VDD Over Current Reset Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_OverCurRst_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VDDOC_RST_EN_Msk)

/**
  * @brief  VDD Low Voltage Reset Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolRst_En(__LVD__)              SET_BIT((__LVD__)->LCR, LVDCTRL_VDDLV_RST_EN_Msk)

/**
  * @brief  VDD Low Voltage Reset Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VDD_LowVolRst_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VDDLV_RST_EN_Msk)

/**
  * @brief  VCC Low Voltage Reset Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolRst_En(__LVD__)              SET_BIT((__LVD__)->LCR, LVDCTRL_VCCLV_RST_EN_Msk)

/**
  * @brief  VCC Low Voltage Reset Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_VCC_LowVolRst_Dis(__LVD__)             CLEAR_BIT((__LVD__)->LCR, LVDCTRL_VCCLV_RST_EN_Msk)

/**
  * @brief  AVCC Low Voltage Reset Enable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolRst_En(__LVD__)             SET_BIT((__LVD__)->LCR, LVDCTRL_AVCCLV_RST_EN_Msk)

/**
  * @brief  AVCC Low Voltage Reset Disable
  * @param  __LVD__ Specifies LVD peripheral
  * @return None
  */
#define __LL_LVDCTRL_AVCC_LowVolRst_Dis(__LVD__)            CLEAR_BIT((__LVD__)->LCR, LVDCTRL_AVCCLV_RST_EN_Msk)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup LVDCTRL_LL_Exported_Functions
  * @{
  */

/** @addtogroup LVDCTRL_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_LVD_Init(LVD_TypeDef *Instance);
LL_StatusETypeDef LL_LVD_DeInit(LVD_TypeDef *Instance);
void LL_LVD_MspInit(LVD_TypeDef *Instance);
void LL_LVD_MspDeInit(LVD_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup LVDCTRL_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_LVD_CtrlIRQHandler(LVD_TypeDef *Instance);
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


#endif /* _TAE32F53XX_LL_LVDCTRL_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

