/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v00x_opa.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : This file contains all the functions prototypes for the
 *                      OPA firmware library.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#ifndef __CH32V00x_OPA_H
#define __CH32V00x_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch32v00x.h"

/* OPA PSEL enumeration */
typedef enum
{
    CHP0 = 0,
    CHP1
} OPA_PSEL_TypeDef;

/* OPA NSEL enumeration */
typedef enum
{
    CHN0 = 0,
    CHN1
} OPA_NSEL_TypeDef;


/* OPA Init Structure definition */
typedef struct
{
    OPA_PSEL_TypeDef PSEL;    /* Specifies the positive channel of OPA */
    OPA_NSEL_TypeDef NSEL;    /* Specifies the negative channel of OPA */
} OPA_InitTypeDef;

void OPA_DeInit(void);
void OPA_Init(OPA_InitTypeDef *OPA_InitStruct);
void OPA_StructInit(OPA_InitTypeDef *OPA_InitStruct);
void OPA_Cmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
