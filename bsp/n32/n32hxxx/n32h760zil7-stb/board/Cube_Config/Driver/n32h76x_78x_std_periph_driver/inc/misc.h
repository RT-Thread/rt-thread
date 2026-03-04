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
 * @file misc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __MISC_H__
#define __MISC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/** MISC Driving Functions Declaration **/

/** NVIC Init Structure definition **/
typedef struct
{
    uint8_t NVIC_IRQChannel; /* Specifies the IRQ channel to be enabled or disabled. */

    uint8_t NVIC_IRQChannelPreemptionPriority; /* Specifies the pre-emption priority for the IRQ channel
                                                  specified in NVIC_IRQChannel. */

    uint8_t NVIC_IRQChannelSubPriority; /* Specifies the subpriority level for the IRQ channel specified
                                           in NVIC_IRQChannel. */

    FunctionalState NVIC_IRQChannelCmd; /* Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                           will be enabled or disabled. */
} NVIC_InitType;

#if (__MPU_PRESENT == 1)

/** MPU Region initialization structure **/
typedef struct
{
	uint8_t                Enable;                /* Specifies the status of the region.                             */
	uint8_t                Number;                /* Specifies the number of the region to protect.                  */
	uint32_t               BaseAddress;           /* Specifies the base address of the region to protect.            */
	uint8_t                Size;                  /* Specifies the size of the region to protect.                    */
	uint8_t                SubRegionDisable;      /* Specifies the number of the subregion protection to disable.    */
	uint8_t                TypeExtField;          /* Specifies the TEX field level.                                  */
	uint8_t                AccessPermission;      /* Specifies the region access permission type.                    */
	uint8_t                DisableExec;           /* Specifies the instruction access status.                        */
	uint8_t                IsShareable;           /* Specifies the shareability status of the protected region.	     */
	uint8_t                IsCacheable;           /* Specifies the cacheable status of the region protected.         */
	uint8_t                IsBufferable;          /* Specifies the bufferable status of the protected region.        */
}MPU_Region_InitType;


/** CORTEX_MPU_HFNMI_PRIVDEF_Control MPU HFNMI and PRIVILEGED Access control */
#define  MPU_HFNMI_PRIVDEF_NONE      ((uint32_t)0x00000000UL)
#define  MPU_HARDFAULT_NMI           ((uint32_t)0x00000002UL)
#define  MPU_PRIVILEGED_DEFAULT      ((uint32_t)0x00000004UL)
#define  MPU_HFNMI_PRIVDEF           ((uint32_t)0x00000006UL)


/** CORTEX_MPU_Region_Enable CORTEX MPU Region Enable */
#define  MPU_REGION_ENABLE     				((uint8_t)0x01u)
#define  MPU_REGION_DISABLE    				((uint8_t)0x00u)

/** CORTEX_MPU_Instruction_Access CORTEX MPU Instruction Access */
#define  MPU_INSTRUCTION_ACCESS_ENABLE      ((uint8_t)0x00u)
#define  MPU_INSTRUCTION_ACCESS_DISABLE     ((uint8_t)0x01u)


/** CORTEX_MPU_Access_Shareable CORTEX MPU Instruction Access Shareable */
#define  MPU_ACCESS_SHAREABLE               ((uint8_t)0x01u)
#define  MPU_ACCESS_NOT_SHAREABLE           ((uint8_t)0x00u)

/** CORTEX_MPU_Access_Cacheable CORTEX MPU Instruction Access Cacheable */
#define  MPU_ACCESS_CACHEABLE	            ((uint8_t)0x01u)
#define  MPU_ACCESS_NOT_CACHEABLE           ((uint8_t)0x00u)


/** CORTEX_MPU_Access_Bufferable CORTEX MPU Instruction Access Bufferable */
#define  MPU_ACCESS_BUFFERABLE              ((uint8_t)0x01u)
#define  MPU_ACCESS_NOT_BUFFERABLE          ((uint8_t)0x00u)

/** CORTEX_MPU_TEX_Levels MPU TEX Levels */
#define  MPU_TEX_LEVEL0    					((uint8_t)0x00u)
#define  MPU_TEX_LEVEL1    					((uint8_t)0x01u)
#define  MPU_TEX_LEVEL2    					((uint8_t)0x02u)

/** CORTEX_MPU_Region_Size CORTEX MPU Region Size */
#define   MPU_REGION_SIZE_32B      			((uint8_t)0x04u)
#define   MPU_REGION_SIZE_64B      			((uint8_t)0x05u)
#define   MPU_REGION_SIZE_128B     			((uint8_t)0x06u)
#define   MPU_REGION_SIZE_256B     			((uint8_t)0x07u)
#define   MPU_REGION_SIZE_512B     			((uint8_t)0x08u)
#define   MPU_REGION_SIZE_1KB      			((uint8_t)0x09u)
#define   MPU_REGION_SIZE_2KB      			((uint8_t)0x0Au)
#define   MPU_REGION_SIZE_4KB      			((uint8_t)0x0Bu)
#define   MPU_REGION_SIZE_8KB      			((uint8_t)0x0Cu)
#define   MPU_REGION_SIZE_16KB     			((uint8_t)0x0Du)
#define   MPU_REGION_SIZE_32KB     			((uint8_t)0x0Eu)
#define   MPU_REGION_SIZE_64KB     			((uint8_t)0x0Fu)
#define   MPU_REGION_SIZE_128KB    			((uint8_t)0x10u)
#define   MPU_REGION_SIZE_256KB    			((uint8_t)0x11u)
#define   MPU_REGION_SIZE_512KB    			((uint8_t)0x12u)
#define   MPU_REGION_SIZE_1MB      			((uint8_t)0x13u)
#define   MPU_REGION_SIZE_2MB      			((uint8_t)0x14u)
#define   MPU_REGION_SIZE_4MB      			((uint8_t)0x15u)
#define   MPU_REGION_SIZE_8MB      			((uint8_t)0x16u)
#define   MPU_REGION_SIZE_16MB     			((uint8_t)0x17u)
#define   MPU_REGION_SIZE_32MB     			((uint8_t)0x18u)
#define   MPU_REGION_SIZE_64MB     			((uint8_t)0x19u)
#define   MPU_REGION_SIZE_128MB    			((uint8_t)0x1Au)
#define   MPU_REGION_SIZE_256MB    			((uint8_t)0x1Bu)
#define   MPU_REGION_SIZE_512MB    			((uint8_t)0x1Cu)
#define   MPU_REGION_SIZE_1GB      			((uint8_t)0x1Du)
#define   MPU_REGION_SIZE_2GB      			((uint8_t)0x1Eu)
#define   MPU_REGION_SIZE_4GB      			((uint8_t)0x1Fu)


/** @defgroup CORTEX_MPU_Region_Permission_Attributes CORTEX MPU Region Permission Attributes
  * @{
  */
#define  MPU_REGION_NO_ACCESS      			((uint8_t)0x00u)
#define  MPU_REGION_PRIV_RW        			((uint8_t)0x01u)
#define  MPU_REGION_PRIV_RW_URO    			((uint8_t)0x02u)
#define  MPU_REGION_FULL_ACCESS    			((uint8_t)0x03u)
#define  MPU_REGION_PRIV_RO        			((uint8_t)0x05u)
#define  MPU_REGION_PRIV_RO_URO    			((uint8_t)0x06u)


/**CORTEX_MPU_Region_Number CORTEX MPU Region Number   */

#define  MPU_REGION_NUMBER0    				((uint8_t)0x00u)
#define  MPU_REGION_NUMBER1    				((uint8_t)0x01u)
#define  MPU_REGION_NUMBER2    				((uint8_t)0x02u)
#define  MPU_REGION_NUMBER3    				((uint8_t)0x03u)
#define  MPU_REGION_NUMBER4    				((uint8_t)0x04u)
#define  MPU_REGION_NUMBER5    				((uint8_t)0x05u)
#define  MPU_REGION_NUMBER6    				((uint8_t)0x06u)
#define  MPU_REGION_NUMBER7    				((uint8_t)0x07u)
#if !defined(CORE_CM4)
#define  MPU_REGION_NUMBER8    				((uint8_t)0x08u)
#define  MPU_REGION_NUMBER9    				((uint8_t)0x09u)
#define  MPU_REGION_NUMBER10   				((uint8_t)0x0Au)
#define  MPU_REGION_NUMBER11   				((uint8_t)0x0Bu)
#define  MPU_REGION_NUMBER12   				((uint8_t)0x0Cu)
#define  MPU_REGION_NUMBER13   				((uint8_t)0x0Du)
#define  MPU_REGION_NUMBER14   				((uint8_t)0x0Eu)
#define  MPU_REGION_NUMBER15   				((uint8_t)0x0Fu)
#endif /* !defined(CORE_CM4) */


#endif /* __MPU_PRESENT */



/** MISC driver modules **/
#define AIRCR_VECTKEY_MASK       ((uint32_t)0x05FA0000U) /* access key */

/** Vector_Table_Base **/
#define NVIC_VectTab_RAM         ((uint32_t)0x20000000U) /* RAM start address*/
#define NVIC_VectTab_FLASH       ((uint32_t)0x08000000U) /* FLASH start address*/

/** LowPowerMode **/
#define NVIC_LP_SEVONPEND        (SCB_SCR_SEVONPEND)
#define NVIC_LP_SLEEPDEEP        (SCB_SCR_SLEEPDEEP)
#define NVIC_LP_SLEEPONEXIT      (SCB_SCR_SLEEPONEXIT)

/** Preemption_Sub_Priority_Group **/
#define NVIC_PriorityGroup_0 (SCB_AIRCR_PRIGROUP7) /* 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PriorityGroup_1 (SCB_AIRCR_PRIGROUP6) /* 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PriorityGroup_2 (SCB_AIRCR_PRIGROUP5) /* 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PriorityGroup_3 (SCB_AIRCR_PRIGROUP4) /* 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PriorityGroup_4 (SCB_AIRCR_PRIGROUP3) /* 4 bits for pre-emption priority 0 bits for subpriority */

/** Preemption_Priority_Group **/
#define NVIC_PRE_PRIORITY_0           ((uint8_t)0x00U)
#define NVIC_PRE_PRIORITY_1           ((uint8_t)0x01U)
#define NVIC_PRE_PRIORITY_2           ((uint8_t)0x02U)
#define NVIC_PRE_PRIORITY_3           ((uint8_t)0x03U)
#define NVIC_PRE_PRIORITY_4           ((uint8_t)0x04U)
#define NVIC_PRE_PRIORITY_5           ((uint8_t)0x05U)
#define NVIC_PRE_PRIORITY_6           ((uint8_t)0x06U)
#define NVIC_PRE_PRIORITY_7           ((uint8_t)0x07U)
#define NVIC_PRE_PRIORITY_8           ((uint8_t)0x08U)
#define NVIC_PRE_PRIORITY_9           ((uint8_t)0x09U)
#define NVIC_PRE_PRIORITY_10          ((uint8_t)0x0AU)
#define NVIC_PRE_PRIORITY_11          ((uint8_t)0x0BU)
#define NVIC_PRE_PRIORITY_12          ((uint8_t)0x0CU)
#define NVIC_PRE_PRIORITY_13          ((uint8_t)0x0DU)
#define NVIC_PRE_PRIORITY_14          ((uint8_t)0x0EU)
#define NVIC_PRE_PRIORITY_15          ((uint8_t)0x0FU)

/** Sub_Priority_Group **/
#define NVIC_SUB_PRIORITY_0           ((uint8_t)0x00U)
#define NVIC_SUB_PRIORITY_1           ((uint8_t)0x01U)
#define NVIC_SUB_PRIORITY_2           ((uint8_t)0x02U)
#define NVIC_SUB_PRIORITY_3           ((uint8_t)0x03U)
#define NVIC_SUB_PRIORITY_4           ((uint8_t)0x04U)
#define NVIC_SUB_PRIORITY_5           ((uint8_t)0x05U)
#define NVIC_SUB_PRIORITY_6           ((uint8_t)0x06U)
#define NVIC_SUB_PRIORITY_7           ((uint8_t)0x07U)
#define NVIC_SUB_PRIORITY_8           ((uint8_t)0x08U)
#define NVIC_SUB_PRIORITY_9           ((uint8_t)0x09U)
#define NVIC_SUB_PRIORITY_10          ((uint8_t)0x0AU)
#define NVIC_SUB_PRIORITY_11          ((uint8_t)0x0BU)
#define NVIC_SUB_PRIORITY_12          ((uint8_t)0x0CU)
#define NVIC_SUB_PRIORITY_13          ((uint8_t)0x0DU)
#define NVIC_SUB_PRIORITY_14          ((uint8_t)0x0EU)
#define NVIC_SUB_PRIORITY_15          ((uint8_t)0x0FU)

#define CM7_CPU                       ((uint32_t)0x00000002)

#define VECT_SIZE                     ((uint32_t)0x400U)

#if defined(DUAL_CORE)
#define CM4_CPU        ((uint32_t)0x00000001)
#endif /*DUAL_CORE*/

/** SysTick_CLKSource **/
#define SysTick_CLKSource_HCLK_Div8  (~SysTick_CTRL_CLKSOURCE)
#define SysTick_CLKSource_HCLK       (SysTick_CTRL_CLKSOURCE)


#if (__MPU_PRESENT == 1)

void MPU_Disable(void);
void MPU_Enable(uint32_t MPU_Control);
void MPU_ConfigRegion(MPU_Region_InitType *MPU_Init);

#endif /*__MPU_PRESENT == 1*/

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitType* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState Cmd);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

void CopyVectTable(uint32_t SrcAddr, uint32_t DesAddr, uint32_t size);
uint32_t Get_CurrentCPU(void);

#ifdef __cplusplus
}
#endif

#endif /* __MISC_H__ */


