/**
 * @file n32h76x_78x_cfg.c
 * @author N32cube
 */

#include "n32h76x_78x_cfg.h"
/* NTFx CODE START */
__IO uint32_t mwTick;
void SysTick_Delayms(uint32_t Delayms)
{
  uint32_t tickstart = mwTick;
  uint32_t wait=Delayms;
  /* Add 1 to guarantee minimum wait */
  if (wait < 0xFFFFFFFFU)
  {
    wait +=1;
  }
  while ((mwTick - tickstart) < wait)
  {
  }
}
 /**
 *@name  DMA_SetSrcDstAddr.
 *@brief Set peripher address and memory address of DMA
 *param   DMAy (The input parameters must be the following values):
 *          - DMA1
 *          - DMA2
 *          - DMA3
 *param   ChNum (The input parameters must be the following values):
 *          - DMA_CHANNEL_0
 *          - DMA_CHANNEL_1
 *          - DMA_CHANNEL_2
 *          - DMA_CHANNEL_3
 *          - DMA_CHANNEL_4
 *          - DMA_CHANNEL_5
 *          - DMA_CHANNEL_6
 *          - DMA_CHANNEL_7
 *@param SrcAddr   Source address
 *@param DstAddr   Destination address
 *@return status
 */
 void DMA_SetSrcDstAddr(DMA_Module *const DMAy,DMA_ChNumType ChNum, uint32_t SrcAddr,uint32_t DstAddr )
 {
    /* Sets channel n source address register */
    WRITE_REG(DMAy->CH[ChNum].SA, SrcAddr);
    /* Sets channel n destination address register */
    WRITE_REG(DMAy->CH[ChNum].DA, DstAddr);
 }
  /**
 *@name  MDMA_SetSrcDstAddr.
 *@brief Set peripher address and memory address of MDMA
 *param   MDMAy (The input parameters must be the following values):
 *          - MDMA
 *param   ChNum (The input parameters must be the following values):
 *          - MDMA_CHANNEL_0
 *          - MDMA_CHANNEL_1
 *          - MDMA_CHANNEL_2
 *          - MDMA_CHANNEL_3
 *          - MDMA_CHANNEL_4
 *          - MDMA_CHANNEL_5
 *          - MDMA_CHANNEL_6
 *          - MDMA_CHANNEL_7
 *          - MDMA_CHANNEL_8
 *          - MDMA_CHANNEL_9
 *          - MDMA_CHANNEL_10
 *          - MDMA_CHANNEL_11
 *          - MDMA_CHANNEL_12
 *          - MDMA_CHANNEL_13
 *          - MDMA_CHANNEL_14
 *          - MDMA_CHANNEL_15
 *@param SrcAddr   Source address
 *@param DstAddr   Destination address
 *@return status
 */
 void MDMA_SetSrcDstAddr(MDMA_Module *const MDMAy,MDMA_ChNumType ChNum, uint32_t SrcAddr,uint32_t DstAddr )
 {
    /* Sets channel n source address register */
    WRITE_REG(MDMAy->CH[ChNum].SA, SrcAddr);
    /* Sets channel n destination address register */
    WRITE_REG(MDMAy->CH[ChNum].DA, DstAddr);
 }
/* NTFx CODE END */
 /* NTFx CODE START */
/**
 *@brief Initializes the clock tree
 *@param null
 *@return status
 */
bool RCC_Configuration(void)
{
    ErrorStatus ClockStatus;
     
    RCC_ConfigHSIclkDivider(RCC_HSICLK_DIV1);
    RCC_EnableHsi(ENABLE);
    /* Wait till HSI is ready */
    ClockStatus = RCC_WaitHsiStable();
    if (ClockStatus != SUCCESS) return false;
    RCC_ConfigSysclkDivider(RCC_SYSCLK_DIV1);
    RCC_ConfigSysbusDivider(RCC_BUSCLK_DIV2);
    /*Configures the Periph clock source as HSI*/
    RCC_ConfigPeriphClk(RCC_PERIPHCLK_SRC_HSI);
     
    /* Configure APB1 clock is AHB1/2 = 150.000M */
    /* Configure APB2 clock is AHB2/2 = 150.000M */
    /* Configure APB5 clock is AHB5/2 = 150.000M */
    /* Configure APB6 clock is AHB6/2 = 150.000M */
    RCC_ConfigAPBclkDivider(RCC_APB1CLK_DIV2, RCC_APB2CLK_DIV2, RCC_APB5CLK_DIV2, RCC_APB6CLK_DIV2);
    /*Configures the PLL1 clock source and multiplication factor,Fin=64M,Fout=600M*/
    //RCC_ConfigPll1(RCC_PLL_SRC_HSI,64000000,600000000,ENABLE);
    RCC_ConfigPll1_NoCalculate(RCC_PLL_SRC_HSI,0,153600,3,ENABLE);
    /*Configure PLL1 divider value to Pll1A*/
    RCC_ConfigPLL1ADivider(RCC_PLLA_DIV1);
    /*Configure PLL1 divider value to Pll1B*/
    RCC_ConfigPLL1BDivider(RCC_PLLB_DIV2);
    /*Configure PLL1 divider value to Pll1C*/
    RCC_ConfigPLL1CDivider(RCC_PLLC_DIV2);
    /*Configure AXI clock source and divider*/
    RCC_ConfigAXIClk(RCC_AXIHYPERCLK_SRC_PLL1A);
    RCC_ConfigAXIclkDivider(RCC_AXICLK_DIV2);
    /*Configure M7 clock source and divider*/
    RCC_ConfigM7SystickClkDivider(RCC_STCLK_DIV1);
    RCC_ConfigM7Clk(RCC_M7HYPERCLK_SRC_PLL1A);
    /* configure sys_clk source is PLL1A */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL1A);
    /* Check if sys_clk source is PLL1A */
    while(RCC_GetSysclkSrc() != RCC_SYSCLK_STS_PLL1A);
     
    /*Config the USART1/2 PCLK divider from ahb1*/
    RCC_ConfigUSARTPClk(RCC_USARTPCLK_AHB1_DIV1);
    
    /*Config the TRNG clock*/
    RCC_ConfigTRNGClk(RCC_TRNGCLK_SRC_SYSBUSDIV,RCC_TRNGCLK_SYSBUSDIV2);
    
     
    /*Enables the APB1 peripheral clock 3 .*/
    RCC_EnableAPB1PeriphClk3(RCC_APB1_PERIPHEN_M7_USART1 ,ENABLE);
/* NTFx CODE END */

    return true;
}
/* NTFx CODE START */
/**
 *@brief Initializes the NVIC
 *@param null
 *@return status
 */
bool NVIC_Configuration(void)
{
     
/* NTFx CODE END */

    return true;
}
/* NTFx CODE START */
/**
 *@brief Initializes the DMA
 *@param null
 *@return status
 */
bool DMA_Configuration(void)
{
     
/* NTFx CODE END */

    return true;
}
/* NTFx CODE START */
/**
 *@brief Initializes the GPIO
 *@param null
 *@return status
 */
bool GPIO_Configuration(void)
{
     
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable the GPIO clock*/
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOA | RCC_AHB5_PERIPHEN_M4_GPIOA, ENABLE);
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_AFIO|RCC_AHB5_PERIPHEN_M4_AFIO,ENABLE);
    
     
    /*Initialize AF_PP GPIO */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_2mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF7;
    GPIO_InitStructure.Pin            = GPIO_PIN_9;
    GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
     
    /*Initialize input GPIO */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5;
    GPIO_InitStructure.Pin            = GPIO_PIN_10;
    GPIO_InitPeripheral(GPIOA,&GPIO_InitStructure);
     
/* NTFx CODE END */

    return true;
}
/* NTFx CODE START */
/**
 *@brief Initializes the USART
 *@param null
 *@return status
 */
bool USART_Configuration(void)
{
    USART_InitType USART_InitStructure;
    USART_StructInit(&USART_InitStructure);
     
     
    /*********initialize the USART1************/
    USART_DeInit(USART1);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO; 
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE; 
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX; 
    USART_InitStructure.OverSampling        = USART_16OVER ; 
    /* Configure USART1 */
    USART_Init(USART1, &USART_InitStructure);
     
     
    /* Enable the USART1 */
    USART_Enable(USART1, ENABLE);
/* NTFx CODE END */

    return true;
}
