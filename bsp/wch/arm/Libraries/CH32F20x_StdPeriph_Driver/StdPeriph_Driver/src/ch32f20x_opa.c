/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_opa.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the OPA firmware functions.
***************************************************************************************/
#include "ch32f20x_opa.h"


#define OPA_MASK        ((uint32_t)0x000F)
#define OPA_Total_NUM   4
/********************************************************************************
* Function Name  : OPA_DeInit
* Description    : Deinitializes the OPA peripheral registers to their default
*                  reset values.
* Input          : None
* Return         : None
*********************************************************************************/	
void OPA_DeInit(void)
{
   OPA->CR=0;
}

/********************************************************************************
* Function Name  : OPA_Init
* Description    : Initializes the OPA peripheral according to the specified
*                  parameters in the OPA_InitStruct.
* Input          : OPA_InitStruct: pointer to a OPA_InitTypeDef structure
* Return         : None
*********************************************************************************/	
void OPA_Init(OPA_InitTypeDef* OPA_InitStruct)
{
    uint32_t tmp=0;
    tmp=OPA->CR;
    tmp &=~(OPA_MASK<<(OPA_InitStruct->OPA_NUM*OPA_Total_NUM));
    tmp |= (( (OPA_InitStruct->PSEL<<OPA_PSEL_OFFSET)
             |(OPA_InitStruct->NSEL<<OPA_NSEL_OFFSET)
             |(OPA_InitStruct->Mode<<OPA_MODE_OFFSET))<<(OPA_InitStruct->OPA_NUM*OPA_Total_NUM));
    OPA->CR=tmp;
}

/********************************************************************************
* Function Name  : OPA_StructInit
* Description    : Fills each OPA_StructInit member with its reset value.
* Input          : OPA_StructInit: pointer to a OPA_InitTypeDef structure
* Return         : None
*********************************************************************************/
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct)
{
    OPA_InitStruct->Mode    = OUT_IO;
    OPA_InitStruct->PSEL    = CHP0;
    OPA_InitStruct->NSEL    = CHN0;
    OPA_InitStruct->OPA_NUM = OPA1;
}

/********************************************************************************
* Function Name  : OPA_Cmd
* Description    : Enables or disables the specified OPA peripheral.
* Input          : OPA_NUM : Select OPA
*                  NewState: ENABLE or DISABLE.
* Return         : None
*********************************************************************************/
void OPA_Cmd(OPA_Num_TypeDef OPA_NUM, FunctionalState NewState)
{
    if(NewState==ENABLE)
    {
        OPA->CR |= ((uint32_t)1<<(OPA_NUM*OPA_Total_NUM));
    }
    else
    {
        OPA->CR &= ~((uint32_t)1<<(OPA_NUM*OPA_Total_NUM));
    }
}

