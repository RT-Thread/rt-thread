/**
  ******************************************************************************
  * @file    lib_comp.h
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   COMP library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_COMP_H
#define __LIB_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/* Macros --------------------------------------------------------------------*/

/***** COMP_DEBConfig *****/
//COMPx
#define COMP_1                   (0x00U)
#define COMP_2                   (0x02U)
#define IS_COMP(__COMP__)  (((__COMP__) == COMP_1) || ((__COMP__) == COMP_2))
//Debounce
#define COMP_DEB_0                ANA_CTRL_CMP1DEB_0
#define COMP_DEB_1                ANA_CTRL_CMP1DEB_1
#define COMP_DEB_2                ANA_CTRL_CMP1DEB_2
#define COMP_DEB_3                ANA_CTRL_CMP1DEB_3
#define IS_COMP_DEB(__DEB__)  (((__DEB__) == COMP_DEB_0) ||\
                               ((__DEB__) == COMP_DEB_1) ||\
                               ((__DEB__) == COMP_DEB_2) ||\
                               ((__DEB__) == COMP_DEB_3))

/***** Mode (COMP_ModeConfig) *****/
#define COMP_MODE_OFF             ANA_CTRL_COMP1_SEL_0
#define COMP_MODE_RISING          ANA_CTRL_COMP1_SEL_1
#define COMP_MODE_FALLING         ANA_CTRL_COMP1_SEL_2
#define COMP_MODE_BOTH            ANA_CTRL_COMP1_SEL_3
#define IS_COMP_MODE(__MODE__)  (((__MODE__) == COMP_MODE_OFF)     ||\
                                 ((__MODE__) == COMP_MODE_RISING)  ||\
                                 ((__MODE__) == COMP_MODE_FALLING) ||\
                                 ((__MODE__) == COMP_MODE_BOTH))

/***** SourceSelect (COMP_ConfigSignalSource) *****/
#define COMP_SIGNALSRC_P_TO_REF   ANA_REG2_CMP1_SEL_0
#define COMP_SIGNALSRC_N_TO_REF   ANA_REG2_CMP1_SEL_1
#define COMP_SIGNALSRC_P_TO_N     ANA_REG2_CMP1_SEL_2
#define IS_COMP_SIGNALSRC(__SIGNALSRC__)  (((__SIGNALSRC__) == COMP_SIGNALSRC_P_TO_REF) ||\
                                           ((__SIGNALSRC__) == COMP_SIGNALSRC_N_TO_REF) ||\
                                           ((__SIGNALSRC__) == COMP_SIGNALSRC_P_TO_N))

/***** REFSelect (COMP_ConfigREF) *****/
#define COMP_REF_VREF            (0)
#define COMP_REF_BGPREF           ANA_REG2_REFSEL_CMP1
#define IS_COMP_REF(__REF__)  (((__REF__) == COMP_REF_VREF)  ||\
                               ((__REF__) == COMP_REF_BGPREF))

/***** BiasSel (COMP_BiasConfig) *****/
#define COMP_BIAS_20nA             ANA_REG5_IT_CMP1_0
#define COMP_BIAS_100nA            ANA_REG5_IT_CMP1_1
#define COMP_BIAS_500nA            ANA_REG5_IT_CMP1_2
#define IS_COMP_BIAS(__BIAS__)  (((__BIAS__) == COMP_BIAS_20nA) ||\
                                 ((__BIAS__) == COMP_BIAS_100nA)||\
                                 ((__BIAS__) == COMP_BIAS_500nA))

/* Exported Functions ------------------------------------------------------- */

void COMP_DEBConfig(uint32_t COMPx, uint32_t Debounce);  
void COMP_ModeConfig(uint32_t COMPx, uint32_t Mode);
void COMP_SignalSourceConfig(uint32_t COMPx, uint32_t SourceSelect);
void COMP_REFConfig(uint32_t COMPx, uint32_t REFSelect);
void COMP_BiasConfig(uint32_t COMPx, uint32_t BiasSel);

void COMP_INTConfig(uint32_t COMPx, uint32_t NewState);
uint8_t COMP_GetINTStatus(uint32_t COMPx);
void COMP_ClearINTStatus(uint32_t COMPx);

void COMP_Output_Cmd(uint32_t COMPx, uint32_t NewState);
void COMP_Cmd(uint32_t COMPx, uint32_t NewState);

uint32_t COMP_GetCNTValue(uint32_t COMPx);
void COMP_ClearCNTValue(uint32_t COMPx);
uint8_t COMP1_GetOutputLevel(void);
uint8_t COMP2_GetOutputLevel(void);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_COMP_H */

/*********************************** END OF FILE ******************************/
