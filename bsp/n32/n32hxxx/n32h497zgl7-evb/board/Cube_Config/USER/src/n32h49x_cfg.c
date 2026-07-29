/**
 * @file n32h49x_cfg.c
 * @author N32cube
 */

#include "n32h49x_cfg.h"

/* NTFx CODE START */
__IO uint32_t mwTick;
void SysTick_Delayms(uint32_t Delayms)
{
    uint32_t tickstart = mwTick;
    uint32_t wait = Delayms;
    /* Add 1 to guarantee minimum wait */
    if (wait < 0xFFFFFFFFU)
    {
        wait += 1;
    }
    while ((mwTick - tickstart) < wait)
    {
    }
}
/**
*@name  DMA_SetPerMemAddr.
*@brief Set peripher address and memory address of DMA
*@param DMAChx (The input parameters must be the following values):
*          - DMA1_CH1
*          - DMA1_CH2
*          - DMA1_CH3
*          - DMA1_CH4
*          - DMA1_CH5
*          - DMA1_CH6
*          - DMA1_CH7
*          - DMA1_CH8
*          - DMA2_CH1
*          - DMA2_CH2
*          - DMA2_CH3
*          - DMA2_CH4
*          - DMA2_CH5
*          - DMA2_CH6
*          - DMA2_CH7
*          - DMA2_CH8
*@param periphAddr   peripher address
*@param memAddr   memory address
*@param bufSize   buff size
*@return status
*/
void DMA_SetPerMemAddr(DMA_ChannelType* DMAChx, uint32_t periphAddr, uint32_t memAddr, uint32_t bufSize)
{
    /* DMAy Channelx TXNUM Configuration */
    /* Write to DMAy Channelx TXNUM */
    DMAChx->TXNUM = bufSize;

    /* DMAy Channelx PADDR Configuration */
    /* Write to DMAy Channelx PADDR */
    DMAChx->PADDR = periphAddr;

    /* DMAy Channelx MADDR Configuration */
    /* Write to DMAy Channelx MADDR */
    DMAChx->MADDR = memAddr;
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
    RCC_DeInit();

    RCC_EnableHsi(ENABLE);
    /* Wait till HSI is ready */
    ClockStatus = RCC_WaitHsiStable();
    if (ClockStatus != SUCCESS) return false;

    RCC_ConfigPll(RCC_PLL_SRC_HSI, RCC_PLL_PRE_2, RCC_PLL_MUL_60, RCC_PLLOUT_DIV_1);
    /* Enable PLL */
    RCC_EnablePll(ENABLE);
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDF) != SET);
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);
    RCC_ConfigPclk2(RCC_HCLK_DIV2);
    RCC_ConfigPclk1(RCC_HCLK_DIV2);
    RCC_ConfigPeriphClk(RCC_PERIPH_HCLK_DIV1);

    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);
    /* Flash wait state */
    FLASH_SetLatency(FLASH_LATENCY_4);

    /*config RNG clock*/
    RCC_ConfigTrng1mClk(RCC_TRNG1MCLK_SRC_HSI, RCC_TRNG1MCLK_DIV8);
    RCC_EnableTrng1mClk(ENABLE);
    RCC_ConfigRngcClk(RCC_RNGCCLK_SYSCLK_DIV1);

    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL);
    /* Wait till PLL is used as system clock source */
    while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL) ;
    /*  Configure the SysTick to have interrupt in 1ms time basis*/
    SysTick_Config(240000);
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
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOH | RCC_AHB_PERIPHEN_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO, ENABLE);



    /*********Initialize USART1 GPIO function *********/
    /********PA9->USART1.TX********/
    /********PA10->USART1.RX********/
    /*Initialize AF_PP GPIO */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_2mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5;
    GPIO_InitStructure.Pin            = GPIO_PIN_9;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /*Initialize input GPIO */
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5;
    GPIO_InitStructure.Pin            = GPIO_PIN_10;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(0, 0, GPIO_RMP_SWJ_SWD);


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
    /*Configure the preemption priority and subpriority:
    - 4 bits for pre-emption priority: possible value are 0..15
    - 0 bits for subpriority: possible value are 0
    - Lower values gives higher priority
    */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(4, 15, 0));
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
 *@brief Initializes the USART
 *@param null
 *@return status
 */
bool USART_Configuration(void)
{
    USART_InitType USART_InitStructure;
    USART_StructInit(&USART_InitStructure);
    /* Enable USART1 clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_USART1, ENABLE);


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
