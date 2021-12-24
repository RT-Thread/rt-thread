/**
  ******************************************************************************
  * @file    lib_ana.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
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
#define ANA_STATUS_AVCCLV       ANA_COMPOUT_AVCCLV
#define ANA_STATUS_VDCINDROP    ANA_COMPOUT_VDCINDROP
#define ANA_STATUS_VDDALARM     ANA_COMPOUT_VDDALARM
#define ANA_STATUS_COMP2        ANA_COMPOUT_COMP2
#define ANA_STATUS_COMP1        ANA_COMPOUT_COMP1
#define ANA_STATUS_LOCKL        ANA_COMPOUT_LOCKL
#define ANA_STATUS_LOCKH        ANA_COMPOUT_LOCKH

/***** IntMask (ANA_GetINTStatus / ANA_ClearINTStatus / ANA_INTConfig) *****/
#define ANA_INT_TADC_OVER       ANA_INTSTS_INTSTS13
#define ANA_INT_REGERR          ANA_INTSTS_INTSTS12
#define ANA_INT_SME             ANA_INTSTS_INTSTS11  
#define ANA_INT_AVCCLV          ANA_INTSTS_INTSTS10
#define ANA_INT_VDCINDROP       ANA_INTSTS_INTSTS8
#define ANA_INT_VDDALARM        ANA_INTSTS_INTSTS7
#define ANA_INT_COMP2           ANA_INTSTS_INTSTS3
#define ANA_INT_COMP1           ANA_INTSTS_INTSTS2
#define ANA_INT_ADCA            ANA_INTSTS_INTSTS1
#define ANA_INT_ADCM            ANA_INTSTS_INTSTS0
#define ANA_INT_Msk            (0x3DEFUL)
   
/* Private macros ------------------------------------------------------------*/
#define IS_ANA_STATUS(__STATUS__)  (((__STATUS__) == ANA_STATUS_AVCCLV)    ||\
                                    ((__STATUS__) == ANA_STATUS_VDCINDROP) ||\
                                    ((__STATUS__) == ANA_STATUS_VDDALARM)  ||\
                                    ((__STATUS__) == ANA_STATUS_COMP2)     ||\
                                    ((__STATUS__) == ANA_STATUS_COMP1)     ||\
                                    ((__STATUS__) == ANA_STATUS_LOCKL)     ||\
                                    ((__STATUS__) == ANA_STATUS_LOCKH))

#define IS_ANA_INTSTSR(__INTSTSR__)  (((__INTSTSR__) == ANA_INT_TADC_OVER) ||\
                                      ((__INTSTSR__) == ANA_INT_REGERR)    ||\
                                      ((__INTSTSR__) == ANA_INT_SME)       ||\
                                      ((__INTSTSR__) == ANA_INT_AVCCLV)    ||\
                                      ((__INTSTSR__) == ANA_INT_VDCINDROP) ||\
                                      ((__INTSTSR__) == ANA_INT_VDDALARM)  ||\
                                      ((__INTSTSR__) == ANA_INT_COMP2)     ||\
                                      ((__INTSTSR__) == ANA_INT_COMP1)     ||\
                                      ((__INTSTSR__) == ANA_INT_ADCA)      ||\
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
