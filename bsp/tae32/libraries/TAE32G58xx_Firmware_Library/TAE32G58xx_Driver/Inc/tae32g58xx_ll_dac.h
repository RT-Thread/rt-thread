/**
  ******************************************************************************
  * @file    tae32g58xx_ll_dac.h
  * @author  MCD Application Team
  * @brief   Header file for DAC LL module
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
#ifndef _TAE32G58XX_LL_DAC_H_
#define _TAE32G58XX_LL_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup DAC_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Macros DAC LL Exported Macros
  * @brief    DAC LL Exported Macros
  * @{
  */

/**
  * @brief  Sawtooth Update Mode Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  mode Sawtooth Update Mode @ref DAC_SAW_UpdateModeETypeDef
  * @return None
  */
#define __LL_DAC_SAW_UpdMode_Set(__DAC__, mode)  \
        MODIFY_REG((__DAC__)->CR, DAC0_CR_STM_Msk, (((mode) & 0x1UL) << DAC0_CR_STM_Pos))

/**
  * @brief  Sawtooth Update Mode Get
  * @param  __DAC__ Specifies DAC peripheral
  * @return Sawtooth Update Mode @ref DAC_SAW_UpdateModeETypeDef
  */
#define __LL_DAC_SAW_UpdMode_Get(__DAC__)           READ_BIT_SHIFT((__DAC__)->CR, DAC0_CR_STM_Msk, DAC0_CR_STM_Pos)

/**
  * @brief  Sawtooth Generate Enable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_SAW_Gen_En(__DAC__)                SET_BIT((__DAC__)->CR, DAC0_CR_STE_Msk)

/**
  * @brief  Sawtooth Generate Disable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_SAW_Gen_Dis(__DAC__)               CLEAR_BIT((__DAC__)->CR, DAC0_CR_STE_Msk)

/**
  * @brief  Sawtooth Generate Direction Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  dir Sawtooth Generate Direction
  * @return None
  */
#define __LL_DAC_SAW_GenDir_Set(__DAC__, dir)       \
        MODIFY_REG((__DAC__)->CR, DAC0_CR_STDIR_Msk, (((dir) & 0x1UL) << DAC0_CR_STDIR_Pos))

/**
  * @brief  Sawtooth Step Trigger Source Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  src Sawtooth Step Trigger Source
  * @return None
  */
#define __LL_DAC_SAW_StepTrigSrc_Set(__DAC__, src)  \
        MODIFY_REG((__DAC__)->CR, DAC0_CR_STINCTRIG_Msk, (((src) & 0xfUL) << DAC0_CR_STINCTRIG_Pos))

/**
  * @brief  Sawtooth Reset Trigger Source Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  src Sawtooth Reset Trigger Source
  * @return None
  */
#define __LL_DAC_SAW_RstTrigSrc_Set(__DAC__, src)   \
        MODIFY_REG((__DAC__)->CR, DAC0_CR_STRSTTRIG_Msk, (((src) & 0xfUL) << DAC0_CR_STRSTTRIG_Pos))

/**
  * @brief  Triangle Generate Enable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_TRI_Gen_En(__DAC__)                SET_BIT((__DAC__)->CR, DAC0_CR_TGE_Msk)

/**
  * @brief  Triangle Generate Disable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_TRI_Gen_Dis(__DAC__)               CLEAR_BIT((__DAC__)->CR, DAC0_CR_TGE_Msk)

/**
  * @brief  Triangle Generate Direction Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  dir Triangle Generate Direction
  * @return None
  */
#define __LL_DAC_TRI_GenDir_Set(__DAC__, dir)       \
        MODIFY_REG((__DAC__)->CR, DAC0_CR_TGDIR_Msk, (((dir) & 0x1UL) << DAC0_CR_TGDIR_Pos))

/**
  * @brief  Triangle Max Amplitude Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  amp Triangle Max Amplitude
  * @return None
  */
#define __LL_DAC_TRI_MaxAmp_Set(__DAC__, amp)       \
        MODIFY_REG((__DAC__)->CR, DAC0_CR_TGAMP_Msk, (((amp) & 0xfUL) << DAC0_CR_TGAMP_Pos))

/**
  * @brief  Triangle Trigger Source Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  src Triangle Trigger Source
  * @return None
  */
#define __LL_DAC_TRI_TrigSrc_Set(__DAC__, src)      \
        MODIFY_REG((__DAC__)->CR, DAC0_CR_TGTRIG_Msk, (((src) & 0xfUL) << DAC0_CR_TGTRIG_Pos))

/**
  * @brief  DAC Trigger Enable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_Trig_En(__DAC__)                   SET_BIT((__DAC__)->CR, DAC0_CR_TEN_Msk)

/**
  * @brief  DAC Trigger Disable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_Trig_Dis(__DAC__)                  CLEAR_BIT((__DAC__)->CR, DAC0_CR_TEN_Msk)

/**
  * @brief  DAC Buffer Output Enable
  * @param  __DAC__ Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
#define __LL_DAC_BufOutput_En(__DAC__)              SET_BIT((__DAC__)->CR, DAC0_CR_OEN_Msk)

/**
  * @brief  DAC Buffer Output Disable
  * @param  __DAC__ Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
#define __LL_DAC_BufOutput_Dis(__DAC__)             CLEAR_BIT((__DAC__)->CR, DAC0_CR_OEN_Msk)

/**
  * @brief  DAC Bypass Buffer Output Enable
  * @param  __DAC__ Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
#define __LL_DAC_BypassBufOutput_En(__DAC__)        SET_BIT((__DAC__)->CR, DAC0_CR_BEN_Msk)

/**
  * @brief  DAC Bypass Buffer Output Disable
  * @param  __DAC__ Specifies DAC peripheral
  * @note   Only DAC0/1/2 Config Valid
  * @return None
  */
#define __LL_DAC_BypassBufOutput_Dis(__DAC__)       CLEAR_BIT((__DAC__)->CR, DAC0_CR_BEN_Msk)

/**
  * @brief  DAC Enable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_En(__DAC__)                        SET_BIT((__DAC__)->CR, DAC0_CR_PEN_Msk)

/**
  * @brief  DAC Disable
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_Dis(__DAC__)                       CLEAR_BIT((__DAC__)->CR, DAC0_CR_PEN_Msk)


/**
  * @brief  DAC Data Write
  * @param  __DAC__ Specifies DAC peripheral
  * @param  dat Write Data
  * @return None
  */
#define __LL_DAC_Dat_Write(__DAC__, dat)            WRITE_REG((__DAC__)->WDR, ((dat) & 0xfffUL))

/**
  * @brief  Triangle Initial Value Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  val Triangle Initial Value
  * @return None
  */
#define __LL_DAC_TRI_InitVal_Set(__DAC__, val)      WRITE_REG((__DAC__)->WDR, ((val) & 0xfffUL))


/**
  * @brief  DAC Data Read
  * @param  __DAC__ Specifies DAC peripheral
  * @return Read Data
  */
#define __LL_DAC_Dat_Read(__DAC__)                  READ_BIT_SHIFT((__DAC__)->RDR, DAC0_RDR_RDAT_Msk, DAC0_RDR_RDAT_Pos)


/**
  * @brief  Sawtooth Wave Step Data Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  dat Sawtooth Wave Step Data
  * @return None
  */
#define __LL_DAC_SAW_StepDat_Set(__DAC__, dat)      WRITE_REG((__DAC__)->SIDR, ((dat) & 0xffffUL))


/**
  * @brief  Sawtooth Wave Reset Data Set
  * @param  __DAC__ Specifies DAC peripheral
  * @param  dat Sawtooth Wave Reset Data
  * @return None
  */
#define __LL_DAC_SAW_RstDat_Set(__DAC__, dat)       \
        MODIFY_REG((__DAC__)->SRDR, DAC0_SRDR_SRD_Msk, (((dat) & 0xfffUL) << DAC0_SRDR_SRD_Pos))

/**
  * @brief  Sawtooth Wave Reset Data Integer Part Get
  * @param  __DAC__ Specifies DAC peripheral
  * @param  dat Sawtooth Wave Reset Data
  * @return None
  */
#define __LL_DAC_SAW_RstDat_Get(__DAC__)            READ_BIT_SHIFT((__DAC__)->SRDR, DAC0_SRDR_SRD_Msk, DAC0_SRDR_SRD_Pos)

/**
  * @brief  Sawtooth Wave Reset Data Fractional Part Get
  * @param  __DAC__ Specifies DAC peripheral
  * @param  dat Sawtooth Wave Reset Data
  * @return None
  */
#define __LL_DAC_SAW_RstDatFra_Get(__DAC__)         READ_BIT_SHIFT((__DAC__)->SRDR, DAC0_SRDR_SRDL_Msk, DAC0_SRDR_SRDL_Pos)


/**
  * @brief  Sawtooth Step Software Trigger
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_SAW_StepSw_Trig(__DAC__)           SET_BIT((__DAC__)->SWTR, DAC0_SWTR_SWTB_Msk)

/**
  * @brief  Triangle Step Software Trigger
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_TRI_StepSw_Trig(__DAC__)           SET_BIT((__DAC__)->SWTR, DAC0_SWTR_SWT_Msk)

/**
  * @brief  Sawtooth Reset Software Trigger
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_SAW_RstSw_Trig(__DAC__)            SET_BIT((__DAC__)->SWTR, DAC0_SWTR_SWT_Msk)


/**
  * @brief  Judge is DAC Data Output DoneB Interrupt Pending or not
  * @param  __DAC__ Specifies DAC peripheral
  * @retval 0 isn't DAC Data Output DoneB Interrupt Pending
  * @retval 1 is DAC Data Output DoneB Interrupt Pending
  */
#define __LL_DAC_IsDatOutputDoneBIntPnd(__DAC__)    READ_BIT_SHIFT((__DAC__)->SR, DAC0_SR_DONB_Msk, DAC0_SR_DONB_Pos)

/**
  * @brief  DAC Data Output DoneB Interrupt Pending Clear
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_DatOutputDoneBIntPnd_Clr(__DAC__)  WRITE_REG((__DAC__)->SR, DAC0_SR_DONB_Msk)

/**
  * @brief  Judge is DAC Data Output Done Interrupt Pending or not
  * @param  __DAC__ Specifies DAC peripheral
  * @retval 0 isn't DAC Data Output Done Interrupt Pending
  * @retval 1 is DAC Data Output Done Interrupt Pending
  */
#define __LL_DAC_IsDatOutputDoneIntPnd(__DAC__)     READ_BIT_SHIFT((__DAC__)->SR, DAC0_SR_DON_Msk, DAC0_SR_DON_Pos)

/**
  * @brief  DAC Data Output Done Interrupt Pending Clear
  * @param  __DAC__ Specifies DAC peripheral
  * @return None
  */
#define __LL_DAC_DatOutputDoneIntPnd_Clr(__DAC__)   WRITE_REG((__DAC__)->SR, DAC0_SR_DON_Msk)

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup DAC_LL_Exported_Types DAC LL Exported Types
  * @brief    DAC LL Exported Types
  * @{
  */

/**
  * @brief DAC Sawtooth/Triangle Wave Generate Direction Definition
  */
typedef enum {
    DAC_WAVE_GEN_DIR_DEC = 0,       /*!< DAC Wave Generate Direction Decrease   */
    DAC_WAVE_GEN_DIR_INC,           /*!< DAC Wave Generate Direction Increase   */
} DAC_WaveGenDirETypeDef;

/**
  * @brief DAC Trigger Source Definition
  * @note  Sawtooth Reset / Triangle Step Trigger Source
  */
typedef enum {
    DAC_TRIG_SRC_SW = 0,            /*!< DAC Trigger Source Software        */
    DAC_TRIG_SRC_TMR7_TRGO,         /*!< DAC Trigger Source TMR7 TRGO       */
    DAC_TRIG_SRC_TMR8_TRGO,         /*!< DAC Trigger Source TMR7 TRGO       */
    DAC_TRIG_SRC_TMR9_TRGO,         /*!< DAC Trigger Source TMR9 TRGO       */
    DAC_TRIG_SRC_ADCTRG0,           /*!< DAC Trigger Source ADCTRG0         */
    DAC_TRIG_SRC_ADCTRG2,           /*!< DAC Trigger Source ADCTRG2         */
    DAC_TRIG_SRC_HRPWM_DACRST0,     /*!< DAC Trigger Source HRPWM DAC Rst 0 */
    DAC_TRIG_SRC_HRPWM_DACRST1,     /*!< DAC Trigger Source HRPWM DAC Rst 1 */
    DAC_TRIG_SRC_HRPWM_DACRST2,     /*!< DAC Trigger Source HRPWM DAC Rst 2 */
    DAC_TRIG_SRC_HRPWM_DACRST3,     /*!< DAC Trigger Source HRPWM DAC Rst 3 */
    DAC_TRIG_SRC_HRPWM_DACRST4,     /*!< DAC Trigger Source HRPWM DAC Rst 4 */
    DAC_TRIG_SRC_HRPWM_DACRST5,     /*!< DAC Trigger Source HRPWM DAC Rst 5 */
    DAC_TRIG_SRC_HRPWM_DACRST6,     /*!< DAC Trigger Source HRPWM DAC Rst 6 */
    DAC_TRIG_SRC_HRPWM_DACRST7,     /*!< DAC Trigger Source HRPWM DAC Rst 7 */
    DAC_TRIG_SRC_HRPWM_DACTRGx,     /*!< DAC Trigger Source HRPWM_DAC TRG x */
    DAC_TRIG_SRC_EXT_PIN_PA10,      /*!< DAC Trigger Source Ext Pin PA10    */
} DAC_TrigSrcETypeDef;

/**
  * @brief DAC Sawtooth Step Trigger Source Definition
  */
typedef enum {
    DAC_SAW_STEP_TRIG_SRC_SW = 0,           /*!< Sawtooth Step Trigger Source Software                      */
    DAC_SAW_STEP_TRIG_SRC_TMR7_TRGO,        /*!< Sawtooth Step Trigger Source TMR7 TRGO                     */
    DAC_SAW_STEP_TRIG_SRC_TMR8_TRGO,        /*!< Sawtooth Step Trigger Source TMR8 TRGO                     */
    DAC_SAW_STEP_TRIG_SRC_TMR10_TRGO,       /*!< Sawtooth Step Trigger Source TMR10 TRGO                    */
    DAC_SAW_STEP_TRIG_SRC_ADCTRG1,          /*!< Sawtooth Step Trigger Source ADCTRG1                       */
    DAC_SAW_STEP_TRIG_SRC_ADCTRG3,          /*!< Sawtooth Step Trigger Source ADCTRG3                       */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC0,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 0 */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC1,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 1 */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC2,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 2 */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC3,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 3 */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC4,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 4 */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC5,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 5 */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC6,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 6 */
    DAC_SAW_STEP_TRIG_SRC_HRPWM_DACINC7,    /*!< Sawtooth Step Trigger Source HRPWM DAC Sawtooth Increase 7 */
    DAC_SAW_STEP_TRIG_SRC_TMR2_TRGO,        /*!< Sawtooth Step Trigger Source TMR2 TRGO                     */
    DAC_SAW_STEP_TRIG_SRC_EXT_PIN_PA11,     /*!< Sawtooth Step Trigger Source Ext Pin PA11                  */
} DAC_SAW_StepTrigSrcETypeDef;

/**
  * @brief Triangle Max Amplitude Definition
  */
typedef enum {
    DAC_TRI_MAX_AMP_1 = 0,          /*!< Triangle Max Amplitude 1       */
    DAC_TRI_MAX_AMP_3,              /*!< Triangle Max Amplitude 3       */
    DAC_TRI_MAX_AMP_7,              /*!< Triangle Max Amplitude 7       */
    DAC_TRI_MAX_AMP_15,             /*!< Triangle Max Amplitude 15      */
    DAC_TRI_MAX_AMP_31,             /*!< Triangle Max Amplitude 31      */
    DAC_TRI_MAX_AMP_63,             /*!< Triangle Max Amplitude 63      */
    DAC_TRI_MAX_AMP_127,            /*!< Triangle Max Amplitude 127     */
    DAC_TRI_MAX_AMP_255,            /*!< Triangle Max Amplitude 255     */
    DAC_TRI_MAX_AMP_511,            /*!< Triangle Max Amplitude 511     */
    DAC_TRI_MAX_AMP_1023,           /*!< Triangle Max Amplitude 1023    */
    DAC_TRI_MAX_AMP_2047,           /*!< Triangle Max Amplitude 2047    */
    DAC_TRI_MAX_AMP_4095,           /*!< Triangle Max Amplitude 4095    */
} DAC_TRI_MaxAmpETypeDef;

/**
  * @brief DAC Sawtooth Update Mode Definition
  */
typedef enum {
    DAC_SAW_UPD_MODE_CUR_PERIOD = 0,     /*!< Sawtooth Update Mode Current period    */
    DAC_SAW_UPD_MODE_NEXT_PERIOD,        /*!< Sawtooth Update Mode Next period       */
} DAC_SAW_UpdModeETypeDef;

/**
  * @brief DAC Initialization Structure Definition
  */
typedef struct __DAC_InitTypeDef {
    bool trig_en;                               /*!< DAC Trigger Enable                 */
    bool buf_out_en;                            /*!< DAC Buffer Output Enable           */
    bool bypass_buf_out_en;                     /*!< DAC Bypass Buffer Output Enable    */
} DAC_InitTypeDef;

/**
  * @brief DAC Sawtooth Config Structure Definition
  */
typedef struct __DAC_SAW_CfgTypeDef {
    uint16_t rst_val;                           /*!< Reset Value                */
    uint16_t step_val;                          /*!< Step Value                 */
    DAC_WaveGenDirETypeDef      dir;            /*!< Wave Generate Direction    */
    DAC_TrigSrcETypeDef         rst_trig_src;   /*!< Reset Trigger Source       */
    DAC_SAW_StepTrigSrcETypeDef step_trig_src;  /*!< Step Trigger Source        */
    DAC_SAW_UpdModeETypeDef     upd_mode;       /*!< Update Mode                */
} DAC_SAW_CfgTypeDef;

/**
  * @brief DAC Triangle Config Structure Definition
  */
typedef struct __DAC_TRI_CfgTypeDef {
    uint16_t                init_val;           /*!< Initial Value              */
    DAC_TRI_MaxAmpETypeDef  max_amp;            /*!< Max Amplitude              */
    DAC_WaveGenDirETypeDef  dir;                /*!< Wave Generate Direction    */
    DAC_TrigSrcETypeDef     step_trig_src;      /*!< Step Trigger Source        */
} DAC_TRI_CfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup DAC_LL_Exported_Functions
  * @{
  */

/** @addtogroup DAC_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_DAC_Init(DAC_TypeDef *Instance, DAC_InitTypeDef *init);
LL_StatusETypeDef LL_DAC_DeInit(DAC_TypeDef *Instance);
void LL_DAC_MspInit(DAC_TypeDef *Instance);
void LL_DAC_MspDeInit(DAC_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup DAC_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_DAC_SAW_Cfg(DAC_TypeDef *Instance, DAC_SAW_CfgTypeDef *cfg);
LL_StatusETypeDef LL_DAC_TRI_Cfg(DAC_TypeDef *Instance, DAC_TRI_CfgTypeDef *cfg);
/**
  * @}
  */


/** @addtogroup DAC_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_DAC_Start(DAC_TypeDef *Instance);
LL_StatusETypeDef LL_DAC_Stop(DAC_TypeDef *Instance);
LL_StatusETypeDef LL_DAC_ValueSet(DAC_TypeDef *Instance, uint16_t val);
uint16_t LL_DAC_ValueGet(DAC_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup DAC_LL_Exported_Functions_Group4
  * @{
  */
LL_StatusETypeDef LL_DAC_SAW_RstSwTrig(DAC_TypeDef *Instance);
LL_StatusETypeDef LL_DAC_SAW_StepSwTrig(DAC_TypeDef *Instance);
LL_StatusETypeDef LL_DAC_TRI_StepSwTrig(DAC_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_DAC_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

