/**
  ******************************************************************************
  * @file    lib_adc_tiny.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   ADC_TINY library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_ADC_TINY_H
#define __LIB_ADC_TINY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

typedef struct
{
  uint32_t SignalSel; 
  uint32_t ADTREF1;
  uint32_t ADTREF2;  
  uint32_t ADTREF3;
} TADCInitType;

//SelADT
#define ADCTINY_SIGNALSEL_IOE6   0
#define ADCTINY_SIGNALSEL_IOE7   ANA_REGF_ADTSEL
#define IS_ADCTINY_SELADT(__SELADT__)  (((__SELADT__) == ADCTINY_SIGNALSEL_IOE6) ||\
                                        ((__SELADT__) == ADCTINY_SIGNALSEL_IOE7))

//ADTREF1
#define ADCTINY_REF1_0_9   0
#define ADCTINY_REF1_0_7   ANA_REGF_ADTREF1SEL
#define IS_ADCTINY_ADTREF1(__ADTREF1__)  (((__ADTREF1__) == ADCTINY_REF1_0_9) ||\
                                          ((__ADTREF1__) == ADCTINY_REF1_0_7))

//ADTREF2
#define ADCTINY_REF2_1_8   0
#define ADCTINY_REF2_1_6   ANA_REGF_ADTREF2SEL
#define IS_ADCTINY_ADTREF2(__ADTREF2__)  (((__ADTREF2__) == ADCTINY_REF2_1_8) ||\
                                          ((__ADTREF2__) == ADCTINY_REF2_1_6))

//ADTREF3
#define ADCTINY_REF3_2_7   0
#define ADCTINY_REF3_2_5   ANA_REGF_ADTREF3SEL
#define IS_ADCTINY_ADTREF3(__ADTREF3__)  (((__ADTREF3__) == ADCTINY_REF3_2_7) ||\
                                          ((__ADTREF3__) == ADCTINY_REF3_2_5))

//THSel
#define ADCTINY_THSEL_0  (0x00UL << ANA_MISC_TADCTH_Pos)
#define ADCTINY_THSEL_1  (0x01UL << ANA_MISC_TADCTH_Pos)
#define ADCTINY_THSEL_2  (0x02UL << ANA_MISC_TADCTH_Pos)
#define ADCTINY_THSEL_3  (0x03UL << ANA_MISC_TADCTH_Pos)
#define IS_ADCTINY_THSEL(__THSEL__)  (((__THSEL__) == ADCTINY_THSEL_0) ||\
                                      ((__THSEL__) == ADCTINY_THSEL_1) ||\
                                      ((__THSEL__) == ADCTINY_THSEL_2) ||\
                                      ((__THSEL__) == ADCTINY_THSEL_3))

/* Exported Functions ------------------------------------------------------- */
void TADC_DeInit(void);
void TADC_StructInit(TADCInitType* TADC_InitStruct);
void TADC_Init(TADCInitType* TADC_InitStruct);
void TADC_Cmd(uint32_t NewState);
uint8_t TADC_GetOutput(void);
void TADC_IntTHConfig(uint32_t THSel);
void TADC_INTConfig(uint32_t NewState);
uint8_t TADC_GetINTStatus(void);
void TADC_ClearINTStatus(void);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_ADC_TINY_H */

/*********************************** END OF FILE ******************************/
