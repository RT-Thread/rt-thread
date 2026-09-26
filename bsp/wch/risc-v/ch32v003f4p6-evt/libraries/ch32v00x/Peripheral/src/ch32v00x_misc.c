/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v00x_misc.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/25
 * Description        : This file provides all the miscellaneous firmware functions .
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/
#include <ch32v00x_misc.h>

__IO uint32_t NVIC_Priority_Group = 0;

/*********************************************************************
 * @fn      NVIC_PriorityGroupConfig
 *
 * @brief   Configures the priority grouping - pre-emption priority and subpriority.
 *
 * @param   NVIC_PriorityGroup - specifies the priority grouping bits length.
 *            NVIC_PriorityGroup_0 - 0 bits for pre-emption priority
 *                                   2 bits for subpriority
 *            NVIC_PriorityGroup_1 - 1 bits for pre-emption priority
 *                                   1 bits for subpriority
 *
 * @return  none
 */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
    NVIC_Priority_Group = NVIC_PriorityGroup;
}

/*********************************************************************
 * @fn      NVIC_Init
 *
 * @brief   Initializes the NVIC peripheral according to the specified parameters in
 *        the NVIC_InitStruct.
 *
 * @param   NVIC_InitStruct - pointer to a NVIC_InitTypeDef structure that contains the
 *        configuration information for the specified NVIC peripheral.
 *              interrupt nesting enable(CSR-0x804 bit1 = 1)
 *            NVIC_IRQChannelPreemptionPriority - range from 0 to 1.
 *            NVIC_IRQChannelSubPriority - range from 0 to 1.
 *
 *              interrupt nesting disable(CSR-0x804 bit1 = 0)
 *            NVIC_IRQChannelPreemptionPriority - range is 0.
 *            NVIC_IRQChannelSubPriority - range from 0 to 3.
 *
 * @return  none
 */
void NVIC_Init(NVIC_InitTypeDef *NVIC_InitStruct)
{
#if (INTSYSCR_INEST == INTSYSCR_INEST_NoEN)
    if(NVIC_Priority_Group == NVIC_PriorityGroup_0)
    {
        NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, NVIC_InitStruct->NVIC_IRQChannelSubPriority << 6);
    }
#else
    if(NVIC_Priority_Group == NVIC_PriorityGroup_1)
    {
        if(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority == 1)
        {
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (1 << 7) | (NVIC_InitStruct->NVIC_IRQChannelSubPriority << 6));
        }
        else if(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority == 0)
        {
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (0 << 7) | (NVIC_InitStruct->NVIC_IRQChannelSubPriority << 6));
        }
    }
#endif

    if(NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
    {
        NVIC_EnableIRQ(NVIC_InitStruct->NVIC_IRQChannel);
    }
    else
    {
        NVIC_DisableIRQ(NVIC_InitStruct->NVIC_IRQChannel);
    }
}
