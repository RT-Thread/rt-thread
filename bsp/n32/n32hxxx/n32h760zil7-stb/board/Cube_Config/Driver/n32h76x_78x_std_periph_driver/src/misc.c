/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file misc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "misc.h"


/**
*\*\name    NVIC_PriorityGroupConfig
*\*\fun     Configures the priority grouping: pre-emption priority and subpriority.
*\*\param   NVIC_PriorityGroup :
*\*\            - NVIC_PriorityGroup_0    0 bits for pre-emption priority 4 bits for subpriority
*\*\            - NVIC_PriorityGroup_1    1 bits for pre-emption priority 3 bits for subpriority
*\*\            - NVIC_PriorityGroup_2    2 bits for pre-emption priority 2 bits for subpriority
*\*\            - NVIC_PriorityGroup_3    3 bits for pre-emption priority 1 bits for subpriority
*\*\            - NVIC_PriorityGroup_4    4 bits for pre-emption priority 0 bits for subpriority
*\*\return  none
**/
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
    /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
*\*\name    NVIC_Init
*\*\fun     Initializes the NVIC peripheral according to the specified parameters in the NVIC_structure_initializes.
*\*\param   NVIC_InitStruct :
*\*\              - NVIC_IRQChannel :
*\*\                   -  IRQn_Type    Interrupt Number Definition
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_0 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\                   -  NVIC_SUB_PRIORITY_1
*\*\                   -  NVIC_SUB_PRIORITY_2
*\*\                   -  NVIC_SUB_PRIORITY_3
*\*\                   -  NVIC_SUB_PRIORITY_4
*\*\                   -  NVIC_SUB_PRIORITY_5
*\*\                   -  NVIC_SUB_PRIORITY_6
*\*\                   -  NVIC_SUB_PRIORITY_7
*\*\                   -  NVIC_SUB_PRIORITY_8
*\*\                   -  NVIC_SUB_PRIORITY_9
*\*\                   -  NVIC_SUB_PRIORITY_10
*\*\                   -  NVIC_SUB_PRIORITY_11
*\*\                   -  NVIC_SUB_PRIORITY_12
*\*\                   -  NVIC_SUB_PRIORITY_13
*\*\                   -  NVIC_SUB_PRIORITY_14
*\*\                   -  NVIC_SUB_PRIORITY_15
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_1 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0
*\*\                   -  NVIC_PRE_PRIORITY_1
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0 to NVIC_SUB_PRIORITY_7
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_2 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0 to NVIC_PRE_PRIORITY_3
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0 to NVIC_SUB_PRIORITY_3
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_3 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0 to NVIC_PRE_PRIORITY_7
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\                   -  NVIC_SUB_PRIORITY_1
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_4 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0
*\*\                   -  NVIC_PRE_PRIORITY_1
*\*\                   -  NVIC_PRE_PRIORITY_2
*\*\                   -  NVIC_PRE_PRIORITY_3
*\*\                   -  NVIC_PRE_PRIORITY_4
*\*\                   -  NVIC_PRE_PRIORITY_5
*\*\                   -  NVIC_PRE_PRIORITY_6
*\*\                   -  NVIC_PRE_PRIORITY_7
*\*\                   -  NVIC_PRE_PRIORITY_8
*\*\                   -  NVIC_PRE_PRIORITY_9
*\*\                   -  NVIC_PRE_PRIORITY_10
*\*\                   -  NVIC_PRE_PRIORITY_11
*\*\                   -  NVIC_PRE_PRIORITY_12
*\*\                   -  NVIC_PRE_PRIORITY_13
*\*\                   -  NVIC_PRE_PRIORITY_14
*\*\                   -  NVIC_PRE_PRIORITY_15
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\              - NVIC_IRQChannelCmd :
*\*\                   -  ENABLE
*\*\                   -  DISABLE
*\*\return  none
**/
void NVIC_Init(NVIC_InitType* NVIC_InitStruct)
{
    uint32_t tmppriority;
    uint32_t tmppre;
    uint32_t tmpsub = 0x0FU;

    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
    {
        /* Compute the Corresponding IRQ Priority --------------------------------*/
        tmppriority = (0x700U - ((SCB->AIRCR) & (uint32_t)0x700U)) >> 0x08U;
        tmppre      = (0x4U - tmppriority) & ((uint32_t)0x07U);
        tmpsub      = tmpsub >> tmppriority;

        tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
        tmppriority |= NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
        tmppriority = tmppriority << 0x04;

        NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = (uint8_t)tmppriority;

        /* Enable the Selected IRQ Channels --------------------------------------*/
        NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05U] = (uint32_t)0x01U
                                                               << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1FU);
    }
    else
    {
        /* Disable the Selected IRQ Channels -------------------------------------*/
        NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] = (uint32_t)0x01
                                                               << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
}

/**
*\*\name    NVIC_SetVectorTable
*\*\fun     Sets the vector table location and Offset.
*\*\param   NVIC_vecter_table specifies if the vector table is in RAM or FLASH memory.
*\*\        This parameter can be one of the following values:
*\*\            - NVIC_VectTab_RAM
*\*\            - NVIC_VectTab_FLASH
*\*\param   offset Vector Table base offset field. This value must be a multiple of 0x200.
*\*\return  none
**/
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80U);
}


/**
*\*\name    NVIC_SystemLPConfig
*\*\fun     Selects the condition for the system to enter low power mode.
*\*\param   LowPowerMode    Specifies the new mode for the system to enter low power mode.
*\*\        This parameter can be one of the following values:
*\*\            - NVIC_LP_SEVONPEND
*\*\            - NVIC_LP_SLEEPDEEP
*\*\            - NVIC_LP_SLEEPONEXIT
*\*\param   - Cmd :
*\*\             -  ENABLE
*\*\             -  DISABLE
*\*\return  none
**/
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SCB->SCR |= LowPowerMode;
    }
    else
    {
        SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
    }
}

/**
*\*\name  SysTick_CLKSourceConfig
*\*\fun   Configures the SysTick clock source.
*\*\param SysTick_CLKSource :
*\*\       - SysTick_CLKSource_HCLK_Div8    External clock selected as SysTick clock source.
*\*\       - SysTick_CLKSource_HCLK         AHB clock selected as SysTick clock source.
*\*\return  none
**/
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
    if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
    {
        SysTick->CTRL |= SysTick_CLKSource_HCLK;
    }
    else
    {
        SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
    }
}



#if (__MPU_PRESENT == 1)


/**
*\*\name  MPU_Disable
*\*\fun   Disables the MPU.
*\*\return  none
**/
void MPU_Disable(void)
{
  /* Make sure outstanding transfers are done */
  __DMB();

  /* Disable fault exceptions */
  SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;

  /* Disable the MPU and clear the control register*/
  MPU->CTRL = 0;
}


/**
*\*\name  MPU_Enable
*\*\fun   Enables the MPU.
*\*\param MPU_Control :
  *        - MPU_HFNMI_PRIVDEF_NONE
  *        - MPU_HARDFAULT_NMI
  *        - MPU_PRIVILEGED_DEFAULT
  *        - MPU_HFNMI_PRIVDEF
*\*\return  none
**/
void MPU_Enable(uint32_t MPU_Control)
{
  /* Enable the MPU */
  MPU->CTRL = MPU_Control | MPU_CTRL_ENABLE_Msk;

  /* Enable fault exceptions */
  SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

  /* Ensure MPU setting take effects */
  __DSB();
  __ISB();
}


/**
*\*\name  MPU_ConfigRegion
*\*\fun   Initializes and configures the Region and the memory to be protected.
*\*\param MPU_Init :
*\*\     - DisableExec
*\*\       - MPU_INSTRUCTION_ACCESS_ENABLE
*\*\       - MPU_INSTRUCTION_ACCESS_DISABLE
*\*\     - AccessPermission
*\*\       - MPU_REGION_NO_ACCESS
*\*\       - MPU_REGION_PRIV_RW
*\*\       - MPU_REGION_PRIV_RW_URO
*\*\       - MPU_REGION_FULL_ACCESS
*\*\       - MPU_REGION_PRIV_RO
*\*\       - MPU_REGION_PRIV_RO_URO
*\*\      - TypeExtField
*\*\       - MPU_TEX_LEVEL0
*\*\       - MPU_TEX_LEVEL1
*\*\       - MPU_TEX_LEVEL2
*\*\     - IsShareable
*\*\       - MPU_ACCESS_SHAREABLE
*\*\       - MPU_ACCESS_NOT_SHAREABLE
*\*\     - IsCacheable
*\*\       - MPU_ACCESS_CACHEABLE
*\*\       - MPU_ACCESS_NOT_CACHEABLE
*\*\     - IsBufferable
*\*\       - MPU_ACCESS_BUFFERABLE
*\*\       - MPU_ACCESS_NOT_BUFFERABLE
*\*\     - SubRegionDisable : 
*\*\       - This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF
*\*\     - SubRegionDisable
*\*\       - MPU_REGION_SIZE_32B
*\*\       - MPU_REGION_SIZE_64B
*\*\       - MPU_REGION_SIZE_128B
*\*\       - MPU_REGION_SIZE_256B
*\*\       - MPU_REGION_SIZE_512B
*\*\       - MPU_REGION_SIZE_1KB
*\*\       - MPU_REGION_SIZE_2KB
*\*\       - MPU_REGION_SIZE_4KB
*\*\       - MPU_REGION_SIZE_8KB
*\*\       - MPU_REGION_SIZE_16KB
*\*\       - MPU_REGION_SIZE_32KB
*\*\       - MPU_REGION_SIZE_64KB
*\*\       - MPU_REGION_SIZE_128KB
*\*\       - MPU_REGION_SIZE_256KB
*\*\       - MPU_REGION_SIZE_512KB
*\*\       - MPU_REGION_SIZE_1MB
*\*\       - MPU_REGION_SIZE_2MB
*\*\       - MPU_REGION_SIZE_4MB
*\*\       - MPU_REGION_SIZE_8MB
*\*\       - MPU_REGION_SIZE_16MB
*\*\       - MPU_REGION_SIZE_32MB
*\*\       - MPU_REGION_SIZE_64MB
*\*\       - MPU_REGION_SIZE_128MB
*\*\       - MPU_REGION_SIZE_256MB
*\*\       - MPU_REGION_SIZE_512MB
*\*\       - MPU_REGION_SIZE_1GB
*\*\       - MPU_REGION_SIZE_2GB
*\*\       - MPU_REGION_SIZE_4GB
*\*\return  none
**/
void MPU_ConfigRegion(MPU_Region_InitType *MPU_Init)
{
	/* Set the Region number */
	MPU->RNR = MPU_Init->Number;

	if ((MPU_Init->Enable) != 0UL)
	{
		MPU->RBAR = MPU_Init->BaseAddress;
		MPU->RASR = ((uint32_t)MPU_Init->DisableExec             << MPU_RASR_XN_Pos)   |
					((uint32_t)MPU_Init->AccessPermission        << MPU_RASR_AP_Pos)   |
					((uint32_t)MPU_Init->TypeExtField            << MPU_RASR_TEX_Pos)  |
					((uint32_t)MPU_Init->IsShareable             << MPU_RASR_S_Pos)    |
					((uint32_t)MPU_Init->IsCacheable             << MPU_RASR_C_Pos)    |
					((uint32_t)MPU_Init->IsBufferable            << MPU_RASR_B_Pos)    |
					((uint32_t)MPU_Init->SubRegionDisable        << MPU_RASR_SRD_Pos)  |
					((uint32_t)MPU_Init->Size                    << MPU_RASR_SIZE_Pos) |
					((uint32_t)MPU_Init->Enable                  << MPU_RASR_ENABLE_Pos);
	}
	else
	{
		MPU->RBAR = 0x00;
		MPU->RASR = 0x00;
	}
}

#endif


/**
*\*\name    CopyVectTable.
*\*\fun     Copy the vector table from flash to TCM.
*\*\param   SrcAddr none
*\*\param   SrcAddr none
*\*\param   size : the size of VECTABLE
*\*\return  none
**/
void CopyVectTable(uint32_t SrcAddr, uint32_t DesAddr, uint32_t size)
{
    uint32_t i;
    volatile  uint32_t* pSrcVect = (uint32_t*)(SrcAddr);
    volatile uint32_t* pDestVect = (uint32_t*)(DesAddr); 
    uint32_t numVECT = (size / 4);
    for(i = 0; i < numVECT; i++)
    {
        pDestVect[i] = pSrcVect[i];
    }
    #ifndef CORE_CM4
    pDestVect[15] = pSrcVect[250];
    #endif
    
    SCB->VTOR = DesAddr;
    __ISB();
    __DSB();
}


#if defined(DUAL_CORE)
/**
*\*\name  Get_CurrentCPU
*\*\fun   Returns the current CPU.
*\*\param none
*\*\return  CPU ID
**/
uint32_t Get_CurrentCPU(void)
{
    if (((SCB->CPUID & 0x000000F0U) >> 4 )== 0x7U)
    {
        return CM7_CPU;
    }
    else
    {
        return CM4_CPU;
    }
}
#else
/**
*\*\name  Get_CurrentCPU
*\*\fun   Returns the current CPU.
*\*\param none
*\*\return  CPU ID
**/
uint32_t Get_CurrentCPU(void)
{
  return  CM7_CPU;
}

#endif /*DUAL_CORE*/




