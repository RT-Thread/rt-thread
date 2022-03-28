/**
  ******************************************************************************
  * @file    lib_ana.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   Analog library.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
#ifndef __LIB_ANA_H
#define __LIB_ANA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/***** StatusMask (ANA_GetStatus) *****/
#define ANA_STATUS_AVCCLV       ANA_CMPOUT_AVCCLV
#define ANA_STATUS_VDCINDROP    ANA_CMPOUT_VDCINDROP
#define ANA_STATUS_VDDALARM     ANA_CMPOUT_VDDALARM
#define ANA_STATUS_COMP2        ANA_CMPOUT_CMP2
#define ANA_STATUS_COMP1        ANA_CMPOUT_CMP1
#define ANA_STATUS_LOCKL        ANA_CMPOUT_LOCKL
#define ANA_STATUS_LOCKH        ANA_CMPOUT_LOCKH

/***** IntMask (ANA_GetINTStatus / ANA_ClearINTStatus / ANA_INTConfig) *****/
#define ANA_INT_UPPER_TH3       ANA_INTEN_INTEN21
#define ANA_INT_LOWER_TH3       ANA_INTEN_INTEN20
#define ANA_INT_UPPER_TH2       ANA_INTEN_INTEN19
#define ANA_INT_LOWER_TH2       ANA_INTEN_INTEN18
#define ANA_INT_UPPER_TH1       ANA_INTEN_INTEN17
#define ANA_INT_LOWER_TH1       ANA_INTEN_INTEN16
#define ANA_INT_UPPER_TH0       ANA_INTEN_INTEN15
#define ANA_INT_LOWER_TH0       ANA_INTEN_INTEN14
#define ANA_INT_TADC_OVER       ANA_INTEN_INTEN13
#define ANA_INT_REGERR          ANA_INTEN_INTEN12
#define ANA_INT_SLPFAIL_VDCIN   ANA_INTEN_INTEN11
#define ANA_INT_AVCCLV          ANA_INTEN_INTEN10
#define ANA_INT_VDCINDROP       ANA_INTEN_INTEN8
#define ANA_INT_VDDALARM        ANA_INTEN_INTEN7
#define ANA_INT_COMP2           ANA_INTEN_INTEN3
#define ANA_INT_COMP1           ANA_INTEN_INTEN2
#define ANA_INT_ADCA            ANA_INTEN_INTEN1
#define ANA_INT_ADCM            ANA_INTEN_INTEN0
#define ANA_INT_Msk             (ANA_INTSTS_INTSTS21     \
                                |ANA_INTSTS_INTSTS20    \
                                |ANA_INTSTS_INTSTS19    \
                                |ANA_INTSTS_INTSTS18    \
                                |ANA_INTSTS_INTSTS17    \
                                |ANA_INTSTS_INTSTS16    \
                                |ANA_INTSTS_INTSTS15    \
                                |ANA_INTSTS_INTSTS14    \
                                |ANA_INTSTS_INTSTS13    \
                                |ANA_INTSTS_INTSTS12   \
                                |ANA_INTSTS_INTSTS11   \
                                |ANA_INTSTS_INTSTS10   \
                                |ANA_INTSTS_INTSTS8    \
                                |ANA_INTSTS_INTSTS7    \
                                |ANA_INTSTS_INTSTS3    \
                                |ANA_INTSTS_INTSTS2    \
                                |ANA_INTSTS_INTSTS1    \
                                |ANA_INTSTS_INTSTS0)

/****************************** ANA Instances *********************************/
#define IS_ANA_ALL_INSTANCE(INSTANCE) ((INSTANCE) == ANA)

/* Private macros ------------------------------------------------------------*/
#define IS_ANA_STATUS(__STATUS__)  (((__STATUS__) == ANA_STATUS_AVCCLV)    ||\
                                    ((__STATUS__) == ANA_STATUS_VDCINDROP) ||\
                                    ((__STATUS__) == ANA_STATUS_VDDALARM)  ||\
                                    ((__STATUS__) == ANA_STATUS_COMP2)     ||\
                                    ((__STATUS__) == ANA_STATUS_COMP1)     ||\
                                    ((__STATUS__) == ANA_STATUS_LOCKL)     ||\
                                    ((__STATUS__) == ANA_STATUS_LOCKH))

#define IS_ANA_INTSTSR(__INTSTSR__)  (((__INTSTSR__) == ANA_INT_UPPER_TH3)     ||\
                                      ((__INTSTSR__) == ANA_INT_LOWER_TH3)     ||\
                                      ((__INTSTSR__) == ANA_INT_UPPER_TH2)     ||\
                                      ((__INTSTSR__) == ANA_INT_LOWER_TH2)     ||\
                                      ((__INTSTSR__) == ANA_INT_UPPER_TH1)     ||\
                                      ((__INTSTSR__) == ANA_INT_LOWER_TH1)     ||\
                                      ((__INTSTSR__) == ANA_INT_UPPER_TH0)     ||\
                                      ((__INTSTSR__) == ANA_INT_LOWER_TH0)     ||\
                                      ((__INTSTSR__) == ANA_INT_TADC_OVER)     ||\
                                      ((__INTSTSR__) == ANA_INT_REGERR)        ||\
                                      ((__INTSTSR__) == ANA_INT_SLPFAIL_VDCIN) ||\
                                      ((__INTSTSR__) == ANA_INT_AVCCLV)        ||\
                                      ((__INTSTSR__) == ANA_INT_VDCINDROP)     ||\
                                      ((__INTSTSR__) == ANA_INT_VDDALARM)      ||\
                                      ((__INTSTSR__) == ANA_INT_COMP2)         ||\
                                      ((__INTSTSR__) == ANA_INT_COMP1)         ||\
                                      ((__INTSTSR__) == ANA_INT_ADCA)          ||\
                                      ((__INTSTSR__) == ANA_INT_ADCM))

#define IS_ANA_INTSTSC(__INTSTSC__)  ((((__INTSTSC__) & ANA_INT_Msk) != 0U) &&\
                                      (((__INTSTSC__) & ~ANA_INT_Msk) == 0U))

#define IS_ANA_INT(__INT__)  IS_ANA_INTSTSC(__INT__)

/* Exported Functions ------------------------------------------------------- */
uint8_t ANA_GetStatus(uint32_t StatusMask);
uint8_t ANA_GetINTStatus(uint32_t IntMask);
void ANA_ClearINTStatus(uint32_t IntMask);
void ANA_INTConfig(uint32_t IntMask, uint32_t NewState);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_ANA_H */

/*********************************** END OF FILE ******************************/
