/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32f20x_rcc.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the RCC firmware functions.
*******************************************************************************/ 
#include "ch32f20x_rcc.h"

/* RCC registers bit address in the alias region */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)

/* CFGR0 Register */

/* Alias word address of USBPRE bit */
#define CFGR0_OFFSET              (RCC_OFFSET + 0x04)
#define USBPRE_BitNumber          0x16
#define CFGR0_USBPRE_BB           (PERIPH_BB_BASE + (CFGR0_OFFSET * 32) + (USBPRE_BitNumber * 4))


/* BDCTLR Register */
#define BDCTLR_OFFSET             (RCC_OFFSET + 0x20)

/* RCC registers bit mask */

/* CTLR register bit mask */
#define CTLR_HSEBYP_Reset           ((uint32_t)0xFFFBFFFF)
#define CTLR_HSEBYP_Set             ((uint32_t)0x00040000)
#define CTLR_HSEON_Reset            ((uint32_t)0xFFFEFFFF)
#define CTLR_HSEON_Set              ((uint32_t)0x00010000)
#define CTLR_HSITRIM_Mask           ((uint32_t)0xFFFFFF07)

#define CFGR0_PLL_Mask              ((uint32_t)0xFFC0FFFF)
#define CFGR0_PLLMull_Mask          ((uint32_t)0x003C0000)
#define CFGR0_PLLSRC_Mask           ((uint32_t)0x00010000)
#define CFGR0_PLLXTPRE_Mask         ((uint32_t)0x00020000)
#define CFGR0_SWS_Mask              ((uint32_t)0x0000000C)
#define CFGR0_SW_Mask               ((uint32_t)0xFFFFFFFC)
#define CFGR0_HPRE_Reset_Mask       ((uint32_t)0xFFFFFF0F)
#define CFGR0_HPRE_Set_Mask         ((uint32_t)0x000000F0)
#define CFGR0_PPRE1_Reset_Mask      ((uint32_t)0xFFFFF8FF)
#define CFGR0_PPRE1_Set_Mask        ((uint32_t)0x00000700)
#define CFGR0_PPRE2_Reset_Mask      ((uint32_t)0xFFFFC7FF)
#define CFGR0_PPRE2_Set_Mask        ((uint32_t)0x00003800)
#define CFGR0_ADCPRE_Reset_Mask     ((uint32_t)0xFFFF3FFF)
#define CFGR0_ADCPRE_Set_Mask       ((uint32_t)0x0000C000)

/* RSTSCKR register bit mask */
#define RSTSCKR_RMVF_Set            ((uint32_t)0x01000000)

/* CFGR2 register bit mask */
#define CFGR2_PREDIV1SRC            ((uint32_t)0x00010000)
#define CFGR2_PREDIV1               ((uint32_t)0x0000000F)
#define CFGR2_PREDIV2               ((uint32_t)0x000000F0)
#define CFGR2_PLL2MUL               ((uint32_t)0x00000F00)
#define CFGR2_PLL3MUL               ((uint32_t)0x0000F000)

/* RCC Flag Mask */
#define FLAG_Mask                   ((uint8_t)0x1F)

/* INTR register byte 2 (Bits[15:8]) base address */
#define INTR_BYTE2_ADDRESS          ((uint32_t)0x40021009)

/* INTR register byte 3 (Bits[23:16]) base address */
#define INTR_BYTE3_ADDRESS          ((uint32_t)0x4002100A)

/* CFGR0 register byte 4 (Bits[31:24]) base address */
#define CFGR0_BYTE4_ADDRESS         ((uint32_t)0x40021007)

/* BDCTLR register base address */
#define BDCTLR_ADDRESS              (PERIPH_BASE + BDCTLR_OFFSET)


static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

/*******************************************************************************
* Function Name  : RCC_DeInit
* Description    : Resets the RCC clock configuration to the default reset state.
* Input          : None
* Return         : None
*******************************************************************************/
void RCC_DeInit(void)
{
  RCC->CTLR |= (uint32_t)0x00000001;
  RCC->CFGR0 &= (uint32_t)0xF8FF0000;  
  RCC->CTLR &= (uint32_t)0xFEF6FFFF;
  RCC->CTLR &= (uint32_t)0xFFFBFFFF;
  RCC->CFGR0 &= (uint32_t)0xFF80FFFF;
  RCC->INTR = 0x009F0000;
}

/*******************************************************************************
* Function Name  : RCC_HSEConfig
* Description    : Configures the External High Speed oscillator (HSE).
* Input          : RCC_HSE:
*                    RCC_HSE_OFF: HSE oscillator OFF.
*                    RCC_HSE_ON: HSE oscillator ON.
*                    RCC_HSE_Bypass: HSE oscillator bypassed with external clock.
* Return         : None
*******************************************************************************/
void RCC_HSEConfig(uint32_t RCC_HSE)
{
  RCC->CTLR &= CTLR_HSEON_Reset;
  RCC->CTLR &= CTLR_HSEBYP_Reset;

  switch(RCC_HSE)
  {
    case RCC_HSE_ON:
      RCC->CTLR |= CTLR_HSEON_Set;
      break;
      
    case RCC_HSE_Bypass:
      RCC->CTLR |= CTLR_HSEBYP_Set | CTLR_HSEON_Set;
      break;
      
    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : RCC_WaitForHSEStartUp
* Description    : Waits for HSE start-up.
* Input          : None
* Return         : SUCCESS: HSE oscillator is stable and ready to use.
*                  ERROR: HSE oscillator not yet ready.
*******************************************************************************/
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  __IO uint32_t StartUpCounter = 0;
	
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));
  
  if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }  
	
  return (status);
}

/*******************************************************************************
* Function Name  : RCC_AdjustHSICalibrationValue
* Description    : Adjusts the Internal High Speed oscillator (HSI) calibration value.
* Input          : HSICalibrationValue: specifies the calibration trimming value.
*                    This parameter must be a number between 0 and 0x1F.
* Return         : None
*******************************************************************************/
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CTLR;
  tmpreg &= CTLR_HSITRIM_Mask;
  tmpreg |= (uint32_t)HSICalibrationValue << 3;
  RCC->CTLR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_HSICmd
* Description    : Enables or disables the Internal High Speed oscillator (HSI).
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_HSICmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->CTLR |= ((uint32_t)1<<0);
	}
	else{
		RCC->CTLR &= ~((uint32_t)1<<0);		
	}
}

/*******************************************************************************
* Function Name  : RCC_PLLConfig
* Description    : Configures the PLL clock source and multiplication factor.
* Input          : RCC_PLLSource: specifies the PLL entry clock source.
*                    RCC_PLLSource_HSI_Div2: HSI oscillator clock divided by 2 
*      selected as PLL clock entry.
*                    RCC_PLLSource_HSE_Div1: HSE oscillator clock selected as PLL 
*      clock entry.
*                    RCC_PLLSource_HSE_Div2: HSE oscillator clock divided by 2 
*      selected as PLL clock entry.
*                  RCC_PLLMul: specifies the PLL multiplication factor.
*                    This parameter can be RCC_PLLMul_x where x:[2,16].
*                  For CH32F207:
*                    RCC_PLLMul_18_EXTEN
*                    RCC_PLLMul_3_EXTEN
*                    RCC_PLLMul_4_EXTEN
*                    RCC_PLLMul_5_EXTEN
*                    RCC_PLLMul_6_EXTEN
*                    RCC_PLLMul_7_EXTEN
*                    RCC_PLLMul_8_EXTEN
*                    RCC_PLLMul_9_EXTEN
*                    RCC_PLLMul_10_EXTEN
*                    RCC_PLLMul_11_EXTEN
*                    RCC_PLLMul_12_EXTEN
*                    RCC_PLLMul_13_EXTEN
*                    RCC_PLLMul_14_EXTEN
*                    RCC_PLLMul_6_5_EXTEN
*                    RCC_PLLMul_15_EXTEN
*                    RCC_PLLMul_16_EXTEN
*                  For other CH32F20x:
*                    RCC_PLLMul_2
*                    RCC_PLLMul_3
*                    RCC_PLLMul_4
*                    RCC_PLLMul_5
*                    RCC_PLLMul_6
*                    RCC_PLLMul_7
*                    RCC_PLLMul_8
*                    RCC_PLLMul_9
*                    RCC_PLLMul_10
*                    RCC_PLLMul_11
*                    RCC_PLLMul_12
*                    RCC_PLLMul_13
*                    RCC_PLLMul_14
*                    RCC_PLLMul_15
*                    RCC_PLLMul_16
*                    RCC_PLLMul_18
* Return         : None
*******************************************************************************/
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_PLL_Mask;
  tmpreg |= RCC_PLLSource | RCC_PLLMul;
  RCC->CFGR0 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PLLCmd
* Description    : Enables or disables the PLL.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_PLLCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->CTLR |= ((uint32_t)1<<24);
	}
	else{
		RCC->CTLR &= ~((uint32_t)1<<24);		
	}
}

/*******************************************************************************
* Function Name  : RCC_SYSCLKConfig
* Description    : Configures the system clock (SYSCLK).
* Input          : RCC_SYSCLKSource: specifies the clock source used as system clock.
*                    RCC_SYSCLKSource_HSI: HSI selected as system clock.
*                    RCC_SYSCLKSource_HSE: HSE selected as system clock.
*                    RCC_SYSCLKSource_PLLCLK: PLL selected as system clock.
* Return         : None
*******************************************************************************/
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_SW_Mask;
  tmpreg |= RCC_SYSCLKSource;
  RCC->CFGR0 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_GetSYSCLKSource
* Description    : Returns the clock source used as system clock.
* Input          : None
* Return         : 0x00: HSI used as system clock.
*                  0x04: HSE used as system clock.
*                  0x08: PLL used as system clock.
*******************************************************************************/
uint8_t RCC_GetSYSCLKSource(void)
{
  return ((uint8_t)(RCC->CFGR0 & CFGR0_SWS_Mask));
}

/*******************************************************************************
* Function Name  : RCC_HCLKConfig
* Description    : Configures the AHB clock (HCLK).
* Input          : RCC_SYSCLK: defines the AHB clock divider. This clock is derived from
*     the system clock (SYSCLK).        
*                    RCC_SYSCLK_Div1: AHB clock = SYSCLK.
*                    RCC_SYSCLK_Div2: AHB clock = SYSCLK/2.
*                    RCC_SYSCLK_Div4: AHB clock = SYSCLK/4.
*                    RCC_SYSCLK_Div8: AHB clock = SYSCLK/8.
*                    RCC_SYSCLK_Div16: AHB clock = SYSCLK/16.
*                    RCC_SYSCLK_Div64: AHB clock = SYSCLK/64.
*                    RCC_SYSCLK_Div128: AHB clock = SYSCLK/128.
*                    RCC_SYSCLK_Div256: AHB clock = SYSCLK/256.
*                    RCC_SYSCLK_Div512: AHB clock = SYSCLK/512.
* Return         : None
*******************************************************************************/
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_HPRE_Reset_Mask;
  tmpreg |= RCC_SYSCLK;
  RCC->CFGR0 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PCLK1Config
* Description    : Configures the Low Speed APB clock (PCLK1).
* Input          : RCC_HCLK: defines the APB1 clock divider. This clock is derived from
*     the AHB clock (HCLK).        
*                    RCC_HCLK_Div1: APB1 clock = HCLK.
*                    RCC_HCLK_Div2: APB1 clock = HCLK/2.
*                    RCC_HCLK_Div4: APB1 clock = HCLK/4.
*                    RCC_HCLK_Div8: APB1 clock = HCLK/8.
*                    RCC_HCLK_Div16: APB1 clock = HCLK/16.
* Return         : None
*******************************************************************************/
void RCC_PCLK1Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_PPRE1_Reset_Mask;
  tmpreg |= RCC_HCLK;
  RCC->CFGR0 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PCLK2Config
* Description    : Configures the High Speed APB clock (PCLK2).
* Input          : RCC_HCLK: defines the APB2 clock divider. This clock is derived from 
*     the AHB clock (HCLK).        
*                    RCC_HCLK_Div1: APB2 clock = HCLK.
*                    RCC_HCLK_Div2: APB2 clock = HCLK/2.
*                    RCC_HCLK_Div4: APB2 clock = HCLK/4.
*                    RCC_HCLK_Div8: APB2 clock = HCLK/8.
*                    RCC_HCLK_Div16: APB2 clock = HCLK/16.
* Return         : None
*******************************************************************************/
void RCC_PCLK2Config(uint32_t RCC_HCLK)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_PPRE2_Reset_Mask;
  tmpreg |= RCC_HCLK << 3;
  RCC->CFGR0 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_ITConfig
* Description    : Enables or disables the specified RCC interrupts.
* Input          : RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
*                    RCC_IT_LSIRDY: LSI ready interrupt.
*                    RCC_IT_LSERDY: LSE ready interrupt.
*                    RCC_IT_HSIRDY: HSI ready interrupt.
*                    RCC_IT_HSERDY: HSE ready interrupt.
*                    RCC_IT_PLLRDY: PLL ready interrupt.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    *(__IO uint8_t *) INTR_BYTE2_ADDRESS |= RCC_IT;
  }
  else
  {
    *(__IO uint8_t *) INTR_BYTE2_ADDRESS &= (uint8_t)~RCC_IT;
  }
}

/*******************************************************************************
* Function Name  : RCC_USBCLKConfig
* Description    : Configures the USB clock (USBCLK).
* Input          : RCC_USBCLKSource: specifies the USB clock source. This clock is
*      derived from the PLL output.
*                    RCC_USBCLKSource_PLLCLK_Div1: PLL clock selected as USB clock source(48Mhz).
*                    RCC_USBCLKSource_PLLCLK_Div2: PLL clock selected as USB clock source(96MHz).
*                    RCC_USBCLKSource_PLLCLK_Div3: PLL clock selected as USB clock source(144MHz).
* Return         : None
*******************************************************************************/
void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource)
{
    RCC->CFGR0 &= ~((uint32_t)3<<22);
    RCC->CFGR0 |= RCC_USBCLKSource<<22;
}

/*******************************************************************************
* Function Name  : RCC_ADCCLKConfig
* Description    : Configures the ADC clock (ADCCLK).
* Input          : RCC_PCLK2: defines the ADC clock divider. This clock is derived from 
*      the APB2 clock (PCLK2).
*                    RCC_PCLK2_Div2: ADC clock = PCLK2/2.
*                    RCC_PCLK2_Div4: ADC clock = PCLK2/4.
*                    RCC_PCLK2_Div6: ADC clock = PCLK2/6.
*                    RCC_PCLK2_Div8: ADC clock = PCLK2/8.
* Return         : None
********************************************************************************/
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR0;
  tmpreg &= CFGR0_ADCPRE_Reset_Mask;
  tmpreg |= RCC_PCLK2;
  RCC->CFGR0 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_LSEConfig
* Description    : Configures the External Low Speed oscillator (LSE).
* Input          : RCC_LSE: specifies the new state of the LSE.
*                    RCC_LSE_OFF: LSE oscillator OFF.
*                    RCC_LSE_ON: LSE oscillator ON.
*                    RCC_LSE_Bypass: LSE oscillator bypassed with external clock.
* Return         : None
********************************************************************************/
void RCC_LSEConfig(uint8_t RCC_LSE)
{
  *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_OFF;
  *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_OFF;
	
  switch(RCC_LSE)
  {
    case RCC_LSE_ON:
      *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_ON;
      break;
      
    case RCC_LSE_Bypass:
      *(__IO uint8_t *) BDCTLR_ADDRESS = RCC_LSE_Bypass | RCC_LSE_ON;
      break;            
      
    default:
      break;      
  }
}

/*******************************************************************************
* Function Name  : RCC_LSICmd
* Description    : Enables or disables the Internal Low Speed oscillator (LSI).
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
********************************************************************************/
void RCC_LSICmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->RSTSCKR |= ((uint32_t)1<<0);
	}
	else{
		RCC->RSTSCKR &= ~((uint32_t)1<<0);		
	}	
}

/*******************************************************************************
* Function Name  : RCC_RTCCLKConfig
* Description    : Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
* Input          : RCC_RTCCLKSource: specifies the RTC clock source.
*                    RCC_RTCCLKSource_LSE: LSE selected as RTC clock.
*                    RCC_RTCCLKSource_LSI: LSI selected as RTC clock.
*                    RCC_RTCCLKSource_HSE_Div128: HSE clock divided by 128 selected as RTC clock.
* Return         : None
********************************************************************************/
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
  RCC->BDCTLR |= RCC_RTCCLKSource;
}

/*******************************************************************************
* Function Name  : RCC_RTCCLKCmd
* Description    : This function must be used only after the RTC clock was selected 
*      using the RCC_RTCCLKConfig function.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
********************************************************************************/
void RCC_RTCCLKCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->BDCTLR |= ((uint32_t)1<<15);
	}
	else{
		RCC->BDCTLR &= ~((uint32_t)1<<15);		
	}	
}

/*******************************************************************************
* Function Name  : RCC_GetClocksFreq
* Description    : The result of this function could be not correct when using
*      fractional value for HSE crystal.
* Input          : RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
*      the clocks frequencies.
* Return         : None
********************************************************************************/
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0, Pll_6_5 = 0;

    tmp = RCC->CFGR0 & CFGR0_SWS_Mask;

    switch (tmp)
    {
      case 0x00:
        RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
        break;

      case 0x04:
        RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
        break;

      case 0x08:
        pllmull = RCC->CFGR0 & CFGR0_PLLMull_Mask;
        pllsource = RCC->CFGR0 & CFGR0_PLLSRC_Mask;

        pllmull = ( pllmull >> 18) + 2;

        if(((*(uint32_t*)0x1FFFF70C) & (1<<14)) != (1<<14)){ /* for other CH32F20x */
            if(pllmull == 17) pllmull = 18;
        }
        else{  /* for CH32F207 */
            if(pllmull == 2) pllmull = 18;
            if(pllmull == 15){
                pllmull = 13;  /* *6.5 */
                Pll_6_5 = 1;
            }
            if(pllmull == 16) pllmull = 15;
            if(pllmull == 17) pllmull = 16;
        }


        if (pllsource == 0x00)
        {
                  if(EXTEN->EXTEN_CTR & EXTEN_PLL_HSI_PRE){
                   RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE) * pllmull;
                  }
                  else{
                   RCC_Clocks->SYSCLK_Frequency = (HSI_VALUE >>1) * pllmull;
                  }
        }
        else
        {
          if ((RCC->CFGR0 & CFGR0_PLLXTPRE_Mask) != (uint32_t)RESET)
          {
            RCC_Clocks->SYSCLK_Frequency = (HSE_VALUE >> 1) * pllmull;
          }
          else
          {
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE * pllmull;
          }
        }

        if(Pll_6_5 == 1) RCC_Clocks->SYSCLK_Frequency = (RCC_Clocks->SYSCLK_Frequency / 2);

        break;

      default:
        RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
        break;
    }

    tmp = RCC->CFGR0 & CFGR0_HPRE_Set_Mask;
    tmp = tmp >> 4;
    presc = APBAHBPrescTable[tmp];
    RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
    tmp = RCC->CFGR0 & CFGR0_PPRE1_Set_Mask;
    tmp = tmp >> 8;
    presc = APBAHBPrescTable[tmp];
    RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    tmp = RCC->CFGR0 & CFGR0_PPRE2_Set_Mask;
    tmp = tmp >> 11;
    presc = APBAHBPrescTable[tmp];
    RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
    tmp = RCC->CFGR0 & CFGR0_ADCPRE_Set_Mask;
    tmp = tmp >> 14;
    presc = ADCPrescTable[tmp];
    RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

/*******************************************************************************
* Function Name  : RCC_AHBPeriphClockCmd
* Description    : Enables or disables the AHB peripheral clock.
* Input          : RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
*                    RCC_AHBPeriph_DMA1.
*                    RCC_AHBPeriph_DMA2.
*                    RCC_AHBPeriph_SRAM.
*                    RCC_AHBPeriph_FLITF.
*                    RCC_AHBPeriph_CRC.
*                    RCC_AHBPeriph_FSMC
*                    RCC_AHBPeriph_RNG
*                    RCC_AHBPeriph_SDIO
*                    RCC_AHBPeriph_USBHS
*                    RCC_AHBPeriph_USBOTG
*                    RCC_AHBPeriph_DVP
*                    RCC_AHBPeriph_ETH_MAC
*                    RCC_AHBPeriph_ETH_MAC_Tx
*                    RCC_AHBPeriph_ETH_MAC_Rx
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/	
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->AHBPCENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBPCENR &= ~RCC_AHBPeriph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB2PeriphClockCmd
* Description    : Enables or disables the High Speed APB (APB2) peripheral clock.
* Input          : RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
*                    RCC_APB2Periph_AFIO.
*                    RCC_APB2Periph_GPIOA.
*                    RCC_APB2Periph_GPIOB.
*                    RCC_APB2Periph_GPIOC.
*                    RCC_APB2Periph_GPIOD.
*                    RCC_APB2Periph_GPIOE
*                    RCC_APB2Periph_ADC1.
*                    RCC_APB2Periph_ADC2
*                    RCC_APB2Periph_TIM1.
*                    RCC_APB2Periph_SPI1.
*                    RCC_APB2Periph_TIM8
*                    RCC_APB2Periph_TIM9
*                    RCC_APB2Periph_TIM10
*                    RCC_APB2Periph_USART1.
*                  NewState: ENABLE or DISABLE
* Return         : None
*******************************************************************************/	
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB2PCENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2PCENR &= ~RCC_APB2Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB1PeriphClockCmd
* Description    : Enables or disables the Low Speed APB (APB1) peripheral clock.
* Input          : RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
*                    RCC_APB1Periph_TIM2.
*                    RCC_APB1Periph_TIM3.
*                    RCC_APB1Periph_TIM4.
*                    RCC_APB1Periph_TIM5
*                    RCC_APB1Periph_TIM6
*                    RCC_APB1Periph_TIM7
*                    RCC_APB1Periph_UART6
*                    RCC_APB1Periph_UART7
*                    RCC_APB1Periph_UART8
*                    RCC_APB1Periph_WWDG.
*                    RCC_APB1Periph_SPI2.
*                    RCC_APB1Periph_USART2.
*                    RCC_APB1Periph_USART3.
*                    RCC_APB1Periph_UART4
*                    RCC_APB1Periph_UART5
*                    RCC_APB1Periph_I2C1.
*                    RCC_APB1Periph_I2C2.
*                    RCC_APB1Periph_USB.
*                    RCC_APB1Periph_CAN1.
*                    RCC_APB1Periph_BKP.
*                    RCC_APB1Periph_PWR.
*                    RCC_APB1Periph_DAC.                
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/	
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB1PCENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1PCENR &= ~RCC_APB1Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB2PeriphResetCmd
* Description    : Forces or releases High Speed APB (APB2) peripheral reset.
* Input          : RCC_APB2Periph: specifies the APB2 peripheral to reset.
*                    RCC_APB2Periph_AFIO.
*                    RCC_APB2Periph_GPIOA.
*                    RCC_APB2Periph_GPIOB.
*                    RCC_APB2Periph_GPIOC.
*                    RCC_APB2Periph_GPIOD.
*                    RCC_APB2Periph_GPIOE
*                    RCC_APB2Periph_ADC1.
*                    RCC_APB2Periph_ADC2
*                    RCC_APB2Periph_TIM1.
*                    RCC_APB2Periph_SPI1.
*                    RCC_APB2Periph_TIM8
*                    RCC_APB2Periph_TIM9
*                    RCC_APB2Periph_TIM10
*                    RCC_APB2Periph_USART1.                
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/	
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB2PRSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2PRSTR &= ~RCC_APB2Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB1PeriphResetCmd
* Description    : Forces or releases Low Speed APB (APB1) peripheral reset.
* Input          : RCC_APB1Periph: specifies the APB1 peripheral to reset.
*                    RCC_APB1Periph_TIM2.
*                    RCC_APB1Periph_TIM3.
*                    RCC_APB1Periph_TIM4.
*                    RCC_APB1Periph_TIM5
*                    RCC_APB1Periph_TIM6
*                    RCC_APB1Periph_TIM7
*                    RCC_APB1Periph_UART6
*                    RCC_APB1Periph_UART7
*                    RCC_APB1Periph_UART8
*                    RCC_APB1Periph_WWDG.
*                    RCC_APB1Periph_SPI2.
*                    RCC_APB1Periph_USART2.
*                    RCC_APB1Periph_USART3.
*                    RCC_APB1Periph_UART4
*                    RCC_APB1Periph_UART5
*                    RCC_APB1Periph_I2C1.
*                    RCC_APB1Periph_I2C2.
*                    RCC_APB1Periph_USB.
*                    RCC_APB1Periph_CAN1.
*                    RCC_APB1Periph_BKP.
*                    RCC_APB1Periph_PWR.
*                    RCC_APB1Periph_DAC.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/	
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->APB1PRSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1PRSTR &= ~RCC_APB1Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_BackupResetCmd
* Description    : Forces or releases the Backup domain reset.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/	
void RCC_BackupResetCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->BDCTLR |= ((uint32_t)1<<16);
	}
	else{
		RCC->BDCTLR &= ~((uint32_t)1<<16);		
	}		
}

/*******************************************************************************
* Function Name  : RCC_ClockSecuritySystemCmd
* Description    : Enables or disables the Clock Security System.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/	
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
	if(NewState)
	{
		RCC->CTLR |= ((uint32_t)1<<19);
	}
	else{
		RCC->CTLR &= ~((uint32_t)1<<19);		
	}		
}

/*******************************************************************************
* Function Name  : RCC_MCOConfig
* Description    : Selects the clock source to output on MCO pin.
* Input          : RCC_MCO: specifies the clock source to output.
*                    RCC_MCO_NoClock: No clock selected.
*                    RCC_MCO_SYSCLK: System clock selected.
*                    RCC_MCO_HSI: HSI oscillator clock selected.
*                    RCC_MCO_HSE: HSE oscillator clock selected.
*                    RCC_MCO_PLLCLK_Div2: PLL clock divided by 2 selected.
*                    RCC_MCO_PLL2CLK: PLL2 clock selected
*                    RCC_MCO_PLL3CLK_Div2: PLL3 clock divided by 2 selected
*                    RCC_MCO_XT1: External 3-25 MHz oscillator clock selected
*                      RCC_MCO_PLL3CLK: PLL3 clock selected
* Return         : None
*******************************************************************************/
void RCC_MCOConfig(uint8_t RCC_MCO)
{
  *(__IO uint8_t *) CFGR0_BYTE4_ADDRESS = RCC_MCO;
}

/*******************************************************************************
* Function Name  : RCC_GetFlagStatus
* Description    : Checks whether the specified RCC flag is set or not.
* Input          : RCC_FLAG: specifies the flag to check.
*                    RCC_FLAG_HSIRDY: HSI oscillator clock ready.
*                    RCC_FLAG_HSERDY: HSE oscillator clock ready.
*                    RCC_FLAG_PLLRDY: PLL clock ready.
*                    RCC_FLAG_PLL2RDY: PLL2 clock ready.
*                    RCC_FLAG_PLL3RDY: PLL3 clock ready.
*                    RCC_FLAG_LSERDY: LSE oscillator clock ready.
*                    RCC_FLAG_LSIRDY: LSI oscillator clock ready.
*                    RCC_FLAG_PINRST: Pin reset.
*                    RCC_FLAG_PORRST: POR/PDR reset.
*                    RCC_FLAG_SFTRST: Software reset.
*                    RCC_FLAG_IWDGRST: Independent Watchdog reset.  
*                    RCC_FLAG_WWDGRST: Window Watchdog reset.
*                    RCC_FLAG_LPWRRST: Low Power reset.
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/	
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
  uint32_t tmp = 0;
  uint32_t statusreg = 0;
	
  FlagStatus bitstatus = RESET;
  tmp = RCC_FLAG >> 5;
	
  if (tmp == 1)            
  {
    statusreg = RCC->CTLR;
  }
  else if (tmp == 2)       
  {
    statusreg = RCC->BDCTLR;
  }
  else                    
  {
    statusreg = RCC->RSTSCKR;
  }

  tmp = RCC_FLAG & FLAG_Mask;
	
  if ((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*******************************************************************************
* Function Name  : RCC_ClearFlag
* Description    : Clears the RCC reset flags.
* Input          : None
* Return         : None
*******************************************************************************/
void RCC_ClearFlag(void)
{
  RCC->RSTSCKR |= RSTSCKR_RMVF_Set;
}

/*******************************************************************************
* Function Name  : RCC_GetITStatus
* Description    : Checks whether the specified RCC interrupt has occurred or not.
* Input          : RCC_IT: specifies the RCC interrupt source to check.
*                    RCC_IT_LSIRDY: LSI ready interrupt.
*                    RCC_IT_LSERDY: LSE ready interrupt.
*                    RCC_IT_HSIRDY: HSI ready interrupt.
*                    RCC_IT_HSERDY: HSE ready interrupt.
*                    RCC_IT_PLLRDY: PLL ready interrupt.
*                    RCC_IT_PLL2RDY: PLL2 ready interrupt.
*                    RCC_IT_PLL3RDY: PLL3 ready interrupt.
*                    RCC_IT_CSS: Clock Security System interrupt.
* Return         : ITStatus: SET or RESET.
*******************************************************************************/	
ITStatus RCC_GetITStatus(uint8_t RCC_IT)
{
  ITStatus bitstatus = RESET;

  if ((RCC->INTR & RCC_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : RCC_ClearITPendingBit
* Description    : Clears the RCC's interrupt pending bits.
* Input          : RCC_IT: specifies the interrupt pending bit to clear.
*                    RCC_IT_LSIRDY: LSI ready interrupt.
*                    RCC_IT_LSERDY: LSE ready interrupt.
*                    RCC_IT_HSIRDY: HSI ready interrupt.
*                    RCC_IT_HSERDY: HSE ready interrupt.
*                    RCC_IT_PLLRDY: PLL ready interrupt.
*                    RCC_IT_PLL2RDY: PLL2 ready interrupt.
*                    RCC_IT_PLL3RDY: PLL3 ready interrupt.
*                    RCC_IT_CSS: Clock Security System interrupt.
* Return         : None
*******************************************************************************/	
void RCC_ClearITPendingBit(uint8_t RCC_IT)
{
  *(__IO uint8_t *) INTR_BYTE3_ADDRESS = RCC_IT;
}

/*******************************************************************************
* Function Name  : RCC_PREDIV1Config
* Description    : Configures the PREDIV1 division factor.
* Input          : RCC_PREDIV1_Source: specifies the PREDIV1 clock source.
*                    RCC_PREDIV1_Source_HSE: HSE selected as PREDIV1 clock
*                    RCC_PREDIV1_Source_PLL2: PLL2 selected as PREDIV1 clock
*                  RCC_PREDIV1_Div: specifies the PREDIV1 clock division factor.
*   This parameter can be RCC_PREDIV1_Divx where x:[1,16]
* Return         : None
*******************************************************************************/
void RCC_PREDIV1Config(uint32_t RCC_PREDIV1_Source, uint32_t RCC_PREDIV1_Div)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR2;
  tmpreg &= ~(CFGR2_PREDIV1 | CFGR2_PREDIV1SRC);
  tmpreg |= RCC_PREDIV1_Source | RCC_PREDIV1_Div ;
  RCC->CFGR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PREDIV2Config
* Description    : Configures the PREDIV2 division factor.
* Input          : RCC_PREDIV2_Div: specifies the PREDIV2 clock division factor.
*   This parameter can be RCC_PREDIV2_Divx where x:[1,16]
* Return         : None
*******************************************************************************/
void RCC_PREDIV2Config(uint32_t RCC_PREDIV2_Div)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR2;
  tmpreg &= ~CFGR2_PREDIV2;
  tmpreg |= RCC_PREDIV2_Div;
  RCC->CFGR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PLL2Config
* Description    : Configures the PLL2 multiplication factor.
* Input          : RCC_PLL2Mul: specifies the PLL2 multiplication factor.
*         This parameter can be RCC_PLL2Mul_x where x:{[8,14], 16, 20}
* Return         : None
*******************************************************************************/
void RCC_PLL2Config(uint32_t RCC_PLL2Mul)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR2;
  tmpreg &= ~CFGR2_PLL2MUL;
  tmpreg |= RCC_PLL2Mul;
  RCC->CFGR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PLL2Cmd
* Description    : Enables or disables the PLL2.
* Input          : NewState: new state of the PLL2. This parameter can be: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_PLL2Cmd(FunctionalState NewState)
{
    if(NewState)
    {
        RCC->CTLR |= ((uint32_t)1<<26);
    }
    else{
        RCC->CTLR &= ~((uint32_t)1<<26);
    }
}

/*******************************************************************************
* Function Name  : RCC_PLL3Config
* Description    : Configures the PLL3 multiplication factor.
* Input          : RCC_PLL3Mul: specifies the PLL3 multiplication factor.
*         This parameter can be RCC_PLL3Mul_x where x:{[8,14], 16, 20}
* Return         : None
*******************************************************************************/
void RCC_PLL3Config(uint32_t RCC_PLL3Mul)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->CFGR2;
  tmpreg &= ~CFGR2_PLL3MUL;
  tmpreg |= RCC_PLL3Mul;
  RCC->CFGR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PLL3Cmd
* Description    : Enables or disables the PLL3.
* Input          : NewState: new state of the PLL3. This parameter can be: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_PLL3Cmd(FunctionalState NewState)
{
    if(NewState)
    {
        RCC->CTLR |= ((uint32_t)1<<28);
    }
    else{
        RCC->CTLR &= ~((uint32_t)1<<28);
    }
}

/*******************************************************************************
* Function Name  : RCC_OTGFSCLKConfig
* Description    : Configures the USB OTG FS clock (OTGFSCLK).
* Input          : RCC_OTGFSCLKSource: specifies the USB OTG FS clock source.
*                  RCC_OTGFSCLKSource_PLLCLK_Div1: PLL clock divided by 1 selected as USB OTG FS clock source
*                  RCC_OTGFSCLKSource_PLLCLK_Div2: PLL clock divided by 2 selected as USB OTG FS clock source
*                  RCC_OTGFSCLKSource_PLLCLK_Div3: PLL clock divided by 3 selected as USB OTG FS clock source
* Return         : None
*******************************************************************************/
void RCC_OTGFSCLKConfig(uint32_t RCC_OTGFSCLKSource)
{
    RCC->CFGR0 &= ~((uint32_t)3<<22);
    RCC->CFGR0 |= RCC_OTGFSCLKSource<<22;
}

/*******************************************************************************
* Function Name  : RCC_I2S2CLKConfig
* Description    : Configures the I2S2 clock source(I2S2CLK).
* Input          : RCC_I2S2CLKSource: specifies the I2S2 clock source.
*                  RCC_I2S2CLKSource_SYSCLK: system clock selected as I2S2 clock entry
*                  RCC_I2S2CLKSource_PLL3_VCO: PLL3 VCO clock selected as I2S2 clock entry
* Return         : None
*******************************************************************************/
void RCC_I2S2CLKConfig(uint32_t RCC_I2S2CLKSource)
{
    RCC->CFGR2 &= ~((uint32_t)1<<17);
    RCC->CFGR2 |= RCC_I2S2CLKSource<<17;
}

/*******************************************************************************
* Function Name  : RCC_I2S3CLKConfig
* Description    : Configures the I2S3 clock source(I2S2CLK).
* Input          : RCC_I2S3CLKSource: specifies the I2S3 clock source.
*                  RCC_I2S3CLKSource_SYSCLK: system clock selected as I2S3 clock entry
*                  RCC_I2S3CLKSource_PLL3_VCO: PLL3 VCO clock selected as I2S3 clock entry
* Return         : None
*******************************************************************************/
void RCC_I2S3CLKConfig(uint32_t RCC_I2S3CLKSource)
{
    RCC->CFGR2 &= ~((uint32_t)1<<18);
    RCC->CFGR2 |= RCC_I2S3CLKSource<<18;
}

/*******************************************************************************
* Function Name  : RCC_AHBPeriphResetCmd
* Description    : Forces or releases AHB peripheral reset.
* Input          : RCC_AHBPeriph: specifies the AHB peripheral to reset.
*                  RCC_AHBPeriph_OTG_FS
*                  RCC_AHBPeriph_ETH_MAC
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->AHBRSTR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBRSTR &= ~RCC_AHBPeriph;
  }
}

/*******************************************************************************
* Function Name  : RCC_ADCCLKADJcmd
* Description    : Enable ADC clock duty cycle adjustment.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_ADCCLKADJcmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->CFGR0 |= ((uint32_t)1<<31);
  }
  else
  {
    RCC->CFGR0 &= ~((uint32_t)1<<31);
  }
}

/*******************************************************************************
* Function Name  : RCC_RNGCLKConfig
* Description    : Configures the RNG clock source.
* Input          : RCC_RNGCLKSource: specifies the RNG clock source.
*                  RCC_RNGCLKSource_SYSCLK: system clock selected as RNG clock entry
*                  RCC_RNGCLKSource_PLL3_VCO: PLL3 VCO clock selected as RNG clock entry
* Return         : None
*******************************************************************************/
void RCC_RNGCLKConfig(uint32_t RCC_RNGCLKSource)
{
    RCC->CFGR2 &= ~((uint32_t)1<<19);
    RCC->CFGR2 |= RCC_RNGCLKSource<<19;
}

/*******************************************************************************
* Function Name  : RCC_ETH1GCLKConfig
* Description    : Configures the ETH1G clock source.
* Input          : RCC_RNGCLKSource: specifies the ETH1G clock source.
*                  RCC_ETH1GCLKSource_PLL2_VCO: system clock selected as ETH1G clock entry
*                  RCC_ETH1GCLKSource_PLL3_VCO: PLL3 VCO clock selected as ETH1G clock entry
*                  RCC_ETH1GCLKSource_PB1_IN£º GPIO PB1 input clock selected as ETH1G clock entry
* Return         : None
*******************************************************************************/
void RCC_ETH1GCLKConfig(uint32_t RCC_ETH1GCLKSource)
{
    RCC->CFGR2 &= ~((uint32_t)3<<20);
    RCC->CFGR2 |= RCC_ETH1GCLKSource<<20;
}

/*******************************************************************************
* Function Name  : RCC_ETH1G_125Mcmd
* Description    : Enable ETH1G 125M.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_ETH1G_125Mcmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->CFGR2 |= ((uint32_t)1<<22);
  }
  else
  {
    RCC->CFGR2 &= ~((uint32_t)1<<22);
  }
}

/*******************************************************************************
* Function Name  : RCC_USBHSConfig
* Description    : Configures the USBHS clock.
* Input          : RCC_USBHS: defines the USBHS clock divider.
*                    RCC_USBPLL_Div1: USBHS clock = USBPLL.
*                    RCC_USBPLL_Div2: USBHS clock = USBPLL/2.
*                    RCC_USBPLL_Div3: USBHS clock = USBPLL/3.
*                    RCC_USBPLL_Div4: USBHS clock = USBPLL/4.
*                    RCC_USBPLL_Div5: USBHS clock = USBPLL/5.
*                    RCC_USBPLL_Div6: USBHS clock = USBPLL/6.
*                    RCC_USBPLL_Div7: USBHS clock = USBPLL/7.
*                    RCC_USBPLL_Div8: USBHS clock = USBPLL/8.
* Return         : None
*******************************************************************************/
void RCC_USBHSConfig(uint32_t RCC_USBHS)
{
    RCC->CFGR2 &= ~((uint32_t)7<<24);
    RCC->CFGR2 |= RCC_USBHS<<24;
}

/*******************************************************************************
* Function Name  : RCC_USBHSPLLCLKConfig
* Description    : Configures the USBHSPLL clock source.
* Input          : RCC_RNGCLKSource: specifies the USBHSPLL clock source.
*                  RCC_HSBHSPLLCLKSource_HSE: HSE clock selected as USBHSPLL clock entry
*                  RCC_HSBHSPLLCLKSource_HSI: HSI clock selected as USBHSPLL clock entry
* Return         : None
*******************************************************************************/
void RCC_USBHSPLLCLKConfig(uint32_t RCC_USBHSPLLCLKSource)
{
    RCC->CFGR2 &= ~((uint32_t)1<<27);
    RCC->CFGR2 |= RCC_USBHSPLLCLKSource<<27;
}

/*******************************************************************************
* Function Name  : RCC_USBHSPLLCKREFCLKConfig
* Description    : Configures the USBHSPLL reference clock.
* Input          : RCC_USBHSPLLCKREFCLKSource: Select reference clock.
*                  RCC_USBHSPLLCKREFCLK_3M: reference clock 3Mhz.
*                  RCC_USBHSPLLCKREFCLK_4M: reference clock 4Mhz.
*                  RCC_USBHSPLLCKREFCLK_8M: reference clock 8Mhz.
*                  RCC_USBHSPLLCKREFCLK_5M: reference clock 5Mhz.
* Return         : None
*******************************************************************************/
void RCC_USBHSPLLCKREFCLKConfig(uint32_t RCC_USBHSPLLCKREFCLKSource)
{
    RCC->CFGR2 &= ~((uint32_t)3<<28);
    RCC->CFGR2 |= RCC_USBHSPLLCKREFCLKSource<<28;
}

/*******************************************************************************
* Function Name  : RCC_USBHSPHYPLLALIVEcmd
* Description    : Enable USBHS PHY control.
* Input          : NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void RCC_USBHSPHYPLLALIVEcmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->CFGR2 |= ((uint32_t)1<<30);
  }
  else
  {
    RCC->CFGR2 &= ~((uint32_t)1<<30);
  }
}

/*******************************************************************************
* Function Name  : RCC_USBCLK48MConfig
* Description    : Configures the USB clock 48MHz source.
* Input          : RCC_USBCLK48MSource: specifies the USB clock 48MHz source.
*                  RCC_USBCLK48MCLKSource_PLLCLK: PLLCLK clock selected as USB clock 48MHz clock entry
*                  RCC_USBCLK48MCLKSource_USBPHY: USBPHY clock selected as USB clock 48MHz clock entry
* Return         : None
*******************************************************************************/
void RCC_USBCLK48MConfig(uint32_t RCC_USBCLK48MSource)
{
    RCC->CFGR2 &= ~((uint32_t)1<<31);
    RCC->CFGR2 |= RCC_USBCLK48MSource<<31;
}
