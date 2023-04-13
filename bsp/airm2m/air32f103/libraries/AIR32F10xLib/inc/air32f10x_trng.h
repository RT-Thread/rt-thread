/************************ (C) COPYRIGHT Megahuntmicro *************************
 * @file                : air32f103_trng.h
 * @author              : Megahuntmicro
 * @version             : V1.0.0
 * @date                :
 * @brief               :
 *****************************************************************************/

#ifndef __AIR32F10x_TRNG_H
#define __AIR32F10x_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air32f10x.h"

typedef enum
{
    TRNG_PDSource_0 = 0xE,
    TRNG_PDSource_1 = 0xD,
    TRNG_PDSource_2 = 0xB,
    TRNG_PDSource_3 = 0x7,
} TRNG_PDSourceTypeDef;

#define TRNG_Periph_Div_None                       ((uint32_t)0x00)
#define TRNG_Periph_Div2                           ((uint32_t)0x01)
#define TRNG_Periph_Div4                           ((uint32_t)0x10)
#define TRNG_Periph_Div8                           ((uint32_t)0x11)

#define IS_TRNG_DIV(DIV)                            (((DIV) == TRNG_Periph_Div_None)  || \
                                                    ((DIV) == TRNG_Periph_Div2)  || \
                                                    ((DIV) == TRNG_Periph_Div4)  || \
                                                    ((DIV) == TRNG_Periph_Div8))


#define IS_TRNG_PDSource(PDSOURCE)          (((PDSOURCE) == TRNG_PDSource_0) ||\
                                             ((PDSOURCE) == TRNG_PDSource_1) ||\
                                             ((PDSOURCE) == TRNG_PDSource_2) ||\
                                             ((PDSOURCE) == TRNG_PDSource_3))

#define TRNG_IT_RNG0_S128           ((uint32_t)0x00000001)
#define TRNG_IT_RNG0_ATTACK         ((uint32_t)0x00000004)
#define IS_TRNG_GET_IT(IT)          (((IT) == TRNG_IT_RNG0_S128) || \
                                    ((IT) == TRNG_IT_RNG0_ATTACK))



/************ bit definition for TRNG RNG_INDEX REGISTER ************/

#define RNG_FIFO_INDEX_Mask                         BIT(31)
/************ bit definition for TRNG RNG_CSR REGISTER ************/
#define TRNG_RNG_CSR_INTP_EN_Mask                   ((uint32_t)0x0010)
#define TRNG_RNG_CSR_ATTACK_TRNG0_Mask              ((uint32_t)0x0004)
#define TRNG_RNG_CSR_S128_TRNG0_Mask                ((uint32_t)0x0001)

/************ bit definition for TRNG RNG_AMA REGISTER ************/
#define TRNG_RNG_AMA_OUT_TRNG0_Mask                 ((uint32_t)0x10000000)
#define TRNG_RNG_AMA_PD_TRNG0_Mask                  ((uint32_t)0x00001000)
#define TRNG_RNG_AMA_PD_TRNG1_Mask                  ((uint32_t)0x00002000)
#define TRNG_RNG_AMA_PD_TRNG2_Mask                  ((uint32_t)0x00004000)
#define TRNG_RNG_AMA_PD_TRNG3_Mask                  ((uint32_t)0x00008000)
#define TRNG_RNG_AMA_PD_ALL_Mask                    ((uint32_t)0x0000F000)
/************ bit definition for TRNG ENABLE REGISTER ************/
#define TRNG_RNG_ENABLE                                     ((uint32_t)0x00000001)

/** @defgroup RNG_Exported_Functions
  * @{
  */
void TRNG_Start(void);
void TRNG_Stop(void);
uint32_t TRNG_Get(uint32_t TRNG_Data[4]);
void TRNG_SetPseudoRandom(uint32_t TRNG_PseudoRandom);;
void TRNG_DirectOutANA(FunctionalState NewState);

void TRNG_ITConfig(FunctionalState NewState);
ITStatus TRNG_GetITStatus(uint32_t TRNG_IT);
void TRNG_ClearITPendingBit(uint32_t TRNG_IT);
void TRNG_SelectPDSource(TRNG_PDSourceTypeDef TRNG_Source);
void TRNG_Out(FunctionalState NewState);
#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
