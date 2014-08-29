/**
	*****************************************************************************
	* @file     cmem7_misc.c
	*
	* @brief    CMEM7 miscellaneous file
	*
	*
	* @version  V1.0
	* @date     3. September 2013
	*
	* @note               
	*           
	*****************************************************************************
	* @attention
	*
	* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
	* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
	* TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT, 
	* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
	* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
	* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
	*
	* <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
	*****************************************************************************
	*/

#include "cmem7_misc.h"

#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
  /* Check the parameters */
  assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));
  
  /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
  SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct)
{
  uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
  
  /* Check the parameters */
  assert_param(IS_NVIC_PREEMPTION_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority));  
  assert_param(IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority));
    
  if (NVIC_InitStruct->NVIC_IRQChannelCmd != FALSE)
  {
    /* Compute the Corresponding IRQ Priority --------------------------------*/    
    tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

    tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
    tmppriority |=  NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
    tmppriority = tmppriority << 0x04;
        
    NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;
    
    /* Enable the Selected IRQ Channels --------------------------------------*/
    NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
  else
  {
    /* Disable the Selected IRQ Channels -------------------------------------*/
    NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
      (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
  }
}

void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{ 
  /* Check the parameters */
  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
  assert_param(IS_NVIC_OFFSET(Offset));  
   
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

void NVIC_SystemLPConfig(uint8_t LowPowerMode, BOOL NewState)
{
  /* Check the parameters */
  assert_param(IS_NVIC_LP(LowPowerMode));
  
  if (!NewState)
  {
    SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
  } else {
		SCB->SCR |= LowPowerMode;
	}
}

void GLB_MMAP(uint32_t from, uint32_t to, BOOL isIcacheOn) {
	int n;
	
	GLOBAL_CTRL->IBUSOFF = GLOBAL_CTRL->DBUSOFF = (from - to);
	GLOBAL_CTRL->EXTADDR = to;
	
	// Delay several cycles 
	for (n = 0; n < 100; n++);
	GLOBAL_CTRL->ICACHE_b.EN = isIcacheOn;
	for (n = 0; n < 100; n++);
}

void GLB_SetNmiIrqNum(uint32_t irq) {
	GLOBAL_CTRL->NMI_SEL_b.NMI = irq;
}

void GLB_SelectSysClkSource(uint8_t source) {
	switch (source) {
	case SYS_CLK_SEL_DLL :
		// M7's DLL clock should be fixed at PLL loation 2
		// In constrast, it's C2R1.
		// Wait DLL clock stable
		while (PDLOCK->GCLK_b.C2R1D == 0) ;
		GLOBAL_CTRL->CLK_SEL_1_b.SYS_CLK = SYS_CLK_SEL_DLL;
		break;
	case SYS_CLK_SEL_CRYSTAL :
		GLOBAL_CTRL->CLK_SEL_1_b.SYS_CLK = SYS_CLK_SEL_CRYSTAL;
		break;
	case SYS_CLK_SEL_EXTERNAL :
		// TODO, Add the condition that makes sure input
		// external clock is stable
		// For example :
		//	PLL location 0
		// 	while (PDLOCK->GCLK_b.C1R1P == 0) ;
		// 	DLL location 0
		// 	while (PDLOCK->GCLK_b.C1R1D == 0) ;
		GLOBAL_CTRL->CLK_SEL_1_b.SYS_CLK = SYS_CLK_SEL_EXTERNAL;
		break;
	case SYS_CLK_SEL_OSC :
		// Fall through
	default :
		GLOBAL_CTRL->CLK_SEL_1_b.SYS_CLK = SYS_CLK_SEL_OSC;
		break;		
	}
}
