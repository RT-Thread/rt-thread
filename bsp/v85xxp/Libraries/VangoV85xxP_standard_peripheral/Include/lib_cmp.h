/**
  ******************************************************************************
  * @file    lib_cmp.h
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   CMP library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_CMP_H
#define __LIB_CMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/* CMP Time struct */
typedef struct
{
  uint32_t DebSel;
  uint32_t SignalSourceSel;
  uint32_t BiasSel;
} CMP_TypeDef;

typedef struct
{
  uint32_t ModeSel;
  uint32_t CheckPeriod;
  uint32_t CheckNum;
} CMP_CountTypeDef;

typedef struct
{
  uint32_t DebSel;
  uint32_t OutputSel;
} CMP_OutputTypeDef;

typedef struct
{
  uint32_t INTNumSel;
  uint32_t SubSel;
  uint32_t THRNum;
} CMP_INTTypeDef;

/* Macros --------------------------------------------------------------------*/

/***** CMP_DEBConfig *****/
//CMPx
#define CMP_1                   (0x00U)
#define CMP_2                   (0x02U)
#define IS_CMP(__CMP__)  (((__CMP__) == CMP_1) || ((__CMP__) == CMP_2))
/**************  Bits definition for ANA_REG2 register       ******************/
#define ANA_REG2_CMP1SEL_0           (0x0U << ANA_REG2_CMP1SEL_Pos)
#define ANA_REG2_CMP1SEL_1           (0x1U << ANA_REG2_CMP1SEL_Pos)
#define ANA_REG2_CMP1SEL_2           (0x2U << ANA_REG2_CMP1SEL_Pos)
#define ANA_REG2_CMP1SEL_3           (0x3U << ANA_REG2_CMP1SEL_Pos)
#define ANA_REG2_CMP2SEL_0           (0x0U << ANA_REG2_CMP2SEL_Pos)
#define ANA_REG2_CMP2SEL_1           (0x1U << ANA_REG2_CMP2SEL_Pos)
#define ANA_REG2_CMP2SEL_2           (0x2U << ANA_REG2_CMP2SEL_Pos)
#define ANA_REG2_CMP2SEL_3           (0x3U << ANA_REG2_CMP2SEL_Pos)
/**************  Bits definition for ANA_REG5 register       ******************/
#define ANA_REG5_CMP1IT_0            (0x0U << ANA_REG5_CMP1IT_Pos)
#define ANA_REG5_CMP1IT_1            (0x1U << ANA_REG5_CMP1IT_Pos)
#define ANA_REG5_CMP1IT_2            (0x2U << ANA_REG5_CMP1IT_Pos)
#define ANA_REG5_CMP1IT_3            (0x3U << ANA_REG5_CMP1IT_Pos)
#define ANA_REG5_CMP2IT_0            (0x0U << ANA_REG5_CMP2IT_Pos)
#define ANA_REG5_CMP2IT_1            (0x1U << ANA_REG5_CMP2IT_Pos)
#define ANA_REG5_CMP2IT_2            (0x2U << ANA_REG5_CMP2IT_Pos)
#define ANA_REG5_CMP2IT_3            (0x3U << ANA_REG5_CMP2IT_Pos)
/**************  Bits definition for ANA_CTRL register       ******************/
//Debounce
#define CMP_DEB_NONE                    (0x0U)
#define CMP_DEB_RTCCLK_2                (0x1U)
#define CMP_DEB_RTCCLK_3                (0x2U)
#define CMP_DEB_RTCCLK_4                (0x3U)
#define IS_CMP_DEB(__DEB__)           (((__DEB__) == CMP_DEB_NONE)     ||\
                                       ((__DEB__) == CMP_DEB_RTCCLK_2) ||\
                                       ((__DEB__) == CMP_DEB_RTCCLK_3) ||\
                                       ((__DEB__) == CMP_DEB_RTCCLK_4))

/***** SourceSelect (CMP_ConfigSignalSource) *****/
#define CMP_SIGNALSRC_PPIN_TO_VREF       0x00
#define CMP_SIGNALSRC_PPIN_TO_BGPREF     0x01
#define CMP_SIGNALSRC_PBAT_TO_VREF       0x80
#define CMP_SIGNALSRC_PBAT_TO_BGPREF     0x81
#define CMP_SIGNALSRC_NPIN_TO_VREF       0x10
#define CMP_SIGNALSRC_NPIN_TO_BGPREF     0x11
#define CMP_SIGNALSRC_PPIN_TO_NPIN       0x20
#define CMP_SIGNALSRC_PBAT_TO_NPIN       0xA0

#define IS_CMP_SIGNALSRC(__SIGNALSRC__)  (((__SIGNALSRC__) == CMP_SIGNALSRC_PPIN_TO_VREF)   ||\
                                          ((__SIGNALSRC__) == CMP_SIGNALSRC_PPIN_TO_BGPREF) ||\
                                          ((__SIGNALSRC__) == CMP_SIGNALSRC_PPIN_TO_NPIN)   ||\
                                          ((__SIGNALSRC__) == CMP_SIGNALSRC_PBAT_TO_NPIN)   ||\
                                          ((__SIGNALSRC__) == CMP_SIGNALSRC_PBAT_TO_VREF)   ||\
                                          ((__SIGNALSRC__) == CMP_SIGNALSRC_PBAT_TO_BGPREF) ||\
                                          ((__SIGNALSRC__) == CMP_SIGNALSRC_NPIN_TO_VREF)   ||\
                                          ((__SIGNALSRC__) == CMP_SIGNALSRC_NPIN_TO_BGPREF))

/***** BiasSel (CMP_BiasConfig) *****/
#define CMP_BIAS_20nA             (0x0U)
#define CMP_BIAS_100nA            (0x1U)
#define CMP_BIAS_500nA            (0x2U)
#define IS_CMP_BIAS(__BIAS__)  (((__BIAS__) == CMP_BIAS_20nA)   ||\
                                ((__BIAS__) == CMP_BIAS_100nA)  ||\
                                ((__BIAS__) == CMP_BIAS_500nA))

/***** CheckPeriod (CMP_CheckFrequecnyConfig) *****/
#define CMP_PERIOD_30US                0
#define CMP_PERIOD_7_8125MS            1
#define CMP_PERIOD_125MS               2
#define CMP_PERIOD_250MS               3
#define CMP_PERIOD_500MS               4
#define IS_CMP_CHECKPERIOD(__CHECKPERIOD__)  (((__CHECKPERIOD__) == CMP_PERIOD_30US)    ||\
                                              ((__CHECKPERIOD__) == CMP_PERIOD_7_8125MS)||\
                                              ((__CHECKPERIOD__) == CMP_PERIOD_125MS)   ||\
                                              ((__CHECKPERIOD__) == CMP_PERIOD_250MS)   ||\
                                              ((__CHECKPERIOD__) == CMP_PERIOD_500MS))

/***** Mode (CMP_ModeConfig) *****/
#define CMP_MODE_OFF             (0x0U)
#define CMP_MODE_RISING          (0x1U)
#define CMP_MODE_FALLING         (0x2U)
#define CMP_MODE_BOTH            (0x3U)
#define IS_CMP_MODE(__MODE__)   (((__MODE__) == CMP_MODE_OFF)     ||\
                                 ((__MODE__) == CMP_MODE_RISING)  ||\
                                 ((__MODE__) == CMP_MODE_FALLING) ||\
                                 ((__MODE__) == CMP_MODE_BOTH))

//CountSel
#define CMP_COUNT_NOSUB                0
#define CMP_COUNT_SUB                  1
#define IS_CMP_COUNT(__COUNT__)  (((__COUNT__) == CMP_COUNT_NOSUB)  ||\
                                  ((__COUNT__) == CMP_COUNT_SUB))

//SubSel
#define CMP_INTNUM_EVERY                0
#define CMP_INTNUM_1                    1
#define IS_CMP_INTNUM(__INTNUM__)   (((__INTNUM__) == CMP_INTNUM_EVERY)  ||\
                                     ((__INTNUM__) == CMP_INTNUM_1))

//THRNum
#define IS_CMP_THRNUM(__THRNUM__)  ((__THRNUM__) < 65536UL)

#define CMP_CHKNUM_1                   0
#define CMP_CHKNUM_2                   1
#define CMP_CHKNUM_3                   2
#define CMP_CHKNUM_4                   3
#define CMP_CHKNUM_5                   4
#define CMP_CHKNUM_6                   5
#define CMP_CHKNUM_7                   6
#define CMP_CHKNUM_8                   7
#define CMP_CHKNUM_9                   8
#define CMP_CHKNUM_10                  9
#define CMP_CHKNUM_11                  10
#define CMP_CHKNUM_12                  11
#define CMP_CHKNUM_13                  12
#define CMP_CHKNUM_14                  13
#define CMP_CHKNUM_15                  14
#define CMP_CHKNUM_16                  15
#define IS_CMP_CHKNUM(__CHKNUM__)  (__CHKNUM__ < 16)

//DebSel
//SubSel
#define CMP_OUTPUT_DEB                0
#define CMP_OUTPUT_NODEB              1
#define IS_CMP_OUTPUTDEB(__OUTPUTDEB__)   (((__OUTPUTDEB__) == CMP_OUTPUT_DEB)  ||\
                                           ((__OUTPUTDEB__) == CMP_OUTPUT_NODEB))

/* Exported Functions ------------------------------------------------------- */
/* CMP Exported Functions Group1: 
                                   (De)Initialization ------------------------*/
void CMP_DeInit(uint32_t CMPx);
void CMP_Init(uint32_t CMPx, CMP_TypeDef *InitStruct);
void CMP_StructInit(CMP_TypeDef *InitStruct);
void CMP_CountStructInit(CMP_CountTypeDef *InitStruct);
void CMP_CountInit(uint32_t CMPx, CMP_CountTypeDef *InitStruct);
void CMP_INTStructInit(CMP_INTTypeDef *InitStruct);
void CMP_INTInit(uint32_t CMPx, CMP_INTTypeDef *InitStruct);
void CMP_OutputStructInit(CMP_OutputTypeDef *InitStruct);
void CMP_OutputInit(uint32_t CMPx, CMP_OutputTypeDef *InitStruct);
/* CMP Exported Functions Group2: 
                                   Interrupt (flag) --------------------------*/
void CMP_INTConfig(uint32_t CMPx, uint32_t NewState);
uint8_t CMP_GetINTStatus(uint32_t CMPx);
void CMP_ClearINTStatus(uint32_t CMPx);
/* CMP Exported Functions Group3:
                                   MISC Configuration ------------------------*/
void CMP_Cmd(uint32_t CMPx, uint32_t NewState);
uint32_t CMP_GetCNTValue(uint32_t CMPx);
void CMP_ClearCNTValue(uint32_t CMPx);
uint8_t CMP_GetOutputValue(uint32_t CMPx);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_CMP_H */

/*********************************** END OF FILE ******************************/
