/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_rcc.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the RCC firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ------------ RCC registers bit address in the alias region ----------- */
#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)

/* --- CR Register ---*/
/* Alias word address of HSION bit */
#define CR_OFFSET                 (RCC_OFFSET + 0x00)
#define HSION_BitNumber           0x00
#define CR_HSION_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (HSION_BitNumber * 4))

/* Alias word address of PLLON bit */
#define PLLON_BitNumber           0x18
#define CR_PLLON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PLLON_BitNumber * 4))

/* Alias word address of CSSON bit */
#define CSSON_BitNumber           0x13
#define CR_CSSON_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (CSSON_BitNumber * 4))

/* --- CFGR Register ---*/
/* Alias word address of USBPRE bit */
#define CFGR_OFFSET               (RCC_OFFSET + 0x04)
#define USBPRE_BitNumber          0x16
#define CFGR_USBPRE_BB            (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (USBPRE_BitNumber * 4))

/* --- BDCR Register ---*/
/* Alias word address of RTCEN bit */
#define BDCR_OFFSET               (RCC_OFFSET + 0x20)
#define RTCEN_BitNumber           0x0F
#define BDCR_RTCEN_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (RTCEN_BitNumber * 4))

/* Alias word address of BDRST bit */
#define BDRST_BitNumber           0x10
#define BDCR_BDRST_BB             (PERIPH_BB_BASE + (BDCR_OFFSET * 32) + (BDRST_BitNumber * 4))

/* --- CSR Register ---*/
/* Alias word address of LSION bit */
#define CSR_OFFSET                (RCC_OFFSET + 0x24)
#define LSION_BitNumber           0x00
#define CSR_LSION_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (LSION_BitNumber * 4))

/* ---------------------- RCC registers bit mask ------------------------ */
/* CR register bit mask */
#define CR_HSEBYP_Reset           ((u32)0xFFFBFFFF)
#define CR_HSEBYP_Set             ((u32)0x00040000)
#define CR_HSEON_Reset            ((u32)0xFFFEFFFF)
#define CR_HSEON_Set              ((u32)0x00010000)
#define CR_HSITRIM_Mask           ((u32)0xFFFFFF07)

/* CFGR register bit mask */
#define CFGR_PLL_Mask             ((u32)0xFFC0FFFF)
#define CFGR_PLLMull_Mask         ((u32)0x003C0000)
#define CFGR_PLLSRC_Mask          ((u32)0x00010000)
#define CFGR_PLLXTPRE_Mask        ((u32)0x00020000)
#define CFGR_SWS_Mask             ((u32)0x0000000C)
#define CFGR_SW_Mask              ((u32)0xFFFFFFFC)
#define CFGR_HPRE_Reset_Mask      ((u32)0xFFFFFF0F)
#define CFGR_HPRE_Set_Mask        ((u32)0x000000F0)
#define CFGR_PPRE1_Reset_Mask     ((u32)0xFFFFF8FF)
#define CFGR_PPRE1_Set_Mask       ((u32)0x00000700)
#define CFGR_PPRE2_Reset_Mask     ((u32)0xFFFFC7FF)
#define CFGR_PPRE2_Set_Mask       ((u32)0x00003800)
#define CFGR_ADCPRE_Reset_Mask    ((u32)0xFFFF3FFF)
#define CFGR_ADCPRE_Set_Mask      ((u32)0x0000C000)

/* CSR register bit mask */
#define CSR_RMVF_Set              ((u32)0x01000000)

/* RCC Flag Mask */
#define FLAG_Mask                 ((u8)0x1F)

/* Typical Value of the HSI in Hz */
#define HSI_Value                 ((u32)8000000)

/* CIR register byte 2 (Bits[15:8]) base address */
#define CIR_BYTE2_ADDRESS         ((u32)0x40021009)
/* CIR register byte 3 (Bits[23:16]) base address */
#define CIR_BYTE3_ADDRESS         ((u32)0x4002100A)

/* CFGR register byte 4 (Bits[31:24]) base address */
#define CFGR_BYTE4_ADDRESS        ((u32)0x40021007)

/* BDCR register base address */
#define BDCR_ADDRESS              (PERIPH_BASE + BDCR_OFFSET)

#ifndef HSEStartUp_TimeOut
/* Time out for HSE start up */
#define HSEStartUp_TimeOut        ((u16)0x0500)
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uc8 APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static uc8 ADCPrescTable[4] = {2, 4, 6, 8};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : RCC_DeInit
* Description    : Resets the RCC clock configuration to the default reset state.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_DeInit(void)
{
  /* Set HSION bit */
  RCC->CR |= (u32)0x00000001;

  /* Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], ADCPRE[1:0] and MCO[2:0] bits */
  RCC->CFGR &= (u32)0xF8FF0000;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (u32)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (u32)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE bits */
  RCC->CFGR &= (u32)0xFF80FFFF;

  /* Disable all interrupts */
  RCC->CIR = 0x00000000;
}

/*******************************************************************************
* Function Name  : RCC_HSEConfig
* Description    : Configures the External High Speed oscillator (HSE).
*                  HSE can not be stopped if it is used directly or through the 
*                  PLL as system clock.
* Input          : - RCC_HSE: specifies the new state of the HSE.
*                    This parameter can be one of the following values:
*                       - RCC_HSE_OFF: HSE oscillator OFF
*                       - RCC_HSE_ON: HSE oscillator ON
*                       - RCC_HSE_Bypass: HSE oscillator bypassed with external
*                         clock
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_HSEConfig(u32 RCC_HSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSE(RCC_HSE));

  /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
  /* Reset HSEON bit */
  RCC->CR &= CR_HSEON_Reset;

  /* Reset HSEBYP bit */
  RCC->CR &= CR_HSEBYP_Reset;

  /* Configure HSE (RCC_HSE_OFF is already covered by the code section above) */
  switch(RCC_HSE)
  {
    case RCC_HSE_ON:
      /* Set HSEON bit */
      RCC->CR |= CR_HSEON_Set;
      break;
      
    case RCC_HSE_Bypass:
      /* Set HSEBYP and HSEON bits */
      RCC->CR |= CR_HSEBYP_Set | CR_HSEON_Set;
      break;            
      
    default:
      break;      
  }
}

/*******************************************************************************
* Function Name  : RCC_WaitForHSEStartUp
* Description    : Waits for HSE start-up.
* Input          : None
* Output         : None
* Return         : An ErrorStatus enumuration value:
*                         - SUCCESS: HSE oscillator is stable and ready to use
*                         - ERROR: HSE oscillator not yet ready
*******************************************************************************/
ErrorStatus RCC_WaitForHSEStartUp(void)
{
  vu32 StartUpCounter = 0;
  ErrorStatus status = ERROR;
  FlagStatus HSEStatus = RESET;
  
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
    StartUpCounter++;  
  } while((HSEStatus == RESET) && (StartUpCounter != HSEStartUp_TimeOut));


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
* Description    : Adjusts the Internal High Speed oscillator (HSI) calibration
*                  value.
* Input          : - HSICalibrationValue: specifies the calibration trimming value.
*                    This parameter must be a number between 0 and 0x1F.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_AdjustHSICalibrationValue(u8 HSICalibrationValue)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_CALIBRATION_VALUE(HSICalibrationValue));

  tmpreg = RCC->CR;

  /* Clear HSITRIM[4:0] bits */
  tmpreg &= CR_HSITRIM_Mask;

  /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
  tmpreg |= (u32)HSICalibrationValue << 3;

  /* Store the new value */
  RCC->CR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_HSICmd
* Description    : Enables or disables the Internal High Speed oscillator (HSI).
*                  HSI can not be stopped if it is used directly or through the 
*                  PLL as system clock.
* Input          : - NewState: new state of the HSI.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_HSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CR_HSION_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : RCC_PLLConfig
* Description    : Configures the PLL clock source and multiplication factor.
*                  This function must be used only when the PLL is disabled.
* Input          : - RCC_PLLSource: specifies the PLL entry clock source.
*                    This parameter can be one of the following values:
*                       - RCC_PLLSource_HSI_Div2: HSI oscillator clock divided
*                         by 2 selected as PLL clock entry
*                       - RCC_PLLSource_HSE_Div1: HSE oscillator clock selected
*                         as PLL clock entry
*                       - RCC_PLLSource_HSE_Div2: HSE oscillator clock divided
*                         by 2 selected as PLL clock entry
*                  - RCC_PLLMul: specifies the PLL multiplication factor.
*                    This parameter can be RCC_PLLMul_x where x:[2,16]
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_PLLConfig(u32 RCC_PLLSource, u32 RCC_PLLMul)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PLL_SOURCE(RCC_PLLSource));
  assert_param(IS_RCC_PLL_MUL(RCC_PLLMul));

  tmpreg = RCC->CFGR;

  /* Clear PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
  tmpreg &= CFGR_PLL_Mask;

  /* Set the PLL configuration bits */
  tmpreg |= RCC_PLLSource | RCC_PLLMul;

  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PLLCmd
* Description    : Enables or disables the PLL.
*                  The PLL can not be disabled if it is used as system clock.
* Input          : - NewState: new state of the PLL.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_PLLCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CR_PLLON_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : RCC_SYSCLKConfig
* Description    : Configures the system clock (SYSCLK).
* Input          : - RCC_SYSCLKSource: specifies the clock source used as system
*                    clock. This parameter can be one of the following values:
*                       - RCC_SYSCLKSource_HSI: HSI selected as system clock
*                       - RCC_SYSCLKSource_HSE: HSE selected as system clock
*                       - RCC_SYSCLKSource_PLLCLK: PLL selected as system clock
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_SYSCLKConfig(u32 RCC_SYSCLKSource)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));

  tmpreg = RCC->CFGR;

  /* Clear SW[1:0] bits */
  tmpreg &= CFGR_SW_Mask;

  /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
  tmpreg |= RCC_SYSCLKSource;

  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_GetSYSCLKSource
* Description    : Returns the clock source used as system clock.
* Input          : None
* Output         : None
* Return         : The clock source used as system clock. The returned value can
*                  be one of the following:
*                       - 0x00: HSI used as system clock
*                       - 0x04: HSE used as system clock
*                       - 0x08: PLL used as system clock
*******************************************************************************/
u8 RCC_GetSYSCLKSource(void)
{
  return ((u8)(RCC->CFGR & CFGR_SWS_Mask));
}

/*******************************************************************************
* Function Name  : RCC_HCLKConfig
* Description    : Configures the AHB clock (HCLK).
* Input          : - RCC_SYSCLK: defines the AHB clock divider. This clock is
*                    derived from the system clock (SYSCLK).
*                    This parameter can be one of the following values:
*                       - RCC_SYSCLK_Div1: AHB clock = SYSCLK
*                       - RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
*                       - RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
*                       - RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
*                       - RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
*                       - RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
*                       - RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
*                       - RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
*                       - RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_HCLKConfig(u32 RCC_SYSCLK)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_HCLK(RCC_SYSCLK));

  tmpreg = RCC->CFGR;

  /* Clear HPRE[3:0] bits */
  tmpreg &= CFGR_HPRE_Reset_Mask;

  /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
  tmpreg |= RCC_SYSCLK;

  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PCLK1Config
* Description    : Configures the Low Speed APB clock (PCLK1).
* Input          : - RCC_HCLK: defines the APB1 clock divider. This clock is
*                    derived from the AHB clock (HCLK).
*                    This parameter can be one of the following values:
*                       - RCC_HCLK_Div1: APB1 clock = HCLK
*                       - RCC_HCLK_Div2: APB1 clock = HCLK/2
*                       - RCC_HCLK_Div4: APB1 clock = HCLK/4
*                       - RCC_HCLK_Div8: APB1 clock = HCLK/8
*                       - RCC_HCLK_Div16: APB1 clock = HCLK/16
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_PCLK1Config(u32 RCC_HCLK)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));

  tmpreg = RCC->CFGR;

  /* Clear PPRE1[2:0] bits */
  tmpreg &= CFGR_PPRE1_Reset_Mask;

  /* Set PPRE1[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK;

  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_PCLK2Config
* Description    : Configures the High Speed APB clock (PCLK2).
* Input          : - RCC_HCLK: defines the APB2 clock divider. This clock is
*                    derived from the AHB clock (HCLK).
*                    This parameter can be one of the following values:
*                       - RCC_HCLK_Div1: APB2 clock = HCLK
*                       - RCC_HCLK_Div2: APB2 clock = HCLK/2
*                       - RCC_HCLK_Div4: APB2 clock = HCLK/4
*                       - RCC_HCLK_Div8: APB2 clock = HCLK/8
*                       - RCC_HCLK_Div16: APB2 clock = HCLK/16
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_PCLK2Config(u32 RCC_HCLK)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_PCLK(RCC_HCLK));

  tmpreg = RCC->CFGR;

  /* Clear PPRE2[2:0] bits */
  tmpreg &= CFGR_PPRE2_Reset_Mask;

  /* Set PPRE2[2:0] bits according to RCC_HCLK value */
  tmpreg |= RCC_HCLK << 3;

  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_ITConfig
* Description    : Enables or disables the specified RCC interrupts.
* Input          : - RCC_IT: specifies the RCC interrupt sources to be enabled
*                    or disabled.
*                    This parameter can be any combination of the following values:
*                       - RCC_IT_LSIRDY: LSI ready interrupt
*                       - RCC_IT_LSERDY: LSE ready interrupt
*                       - RCC_IT_HSIRDY: HSI ready interrupt
*                       - RCC_IT_HSERDY: HSE ready interrupt
*                       - RCC_IT_PLLRDY: PLL ready interrupt
*                  - NewState: new state of the specified RCC interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_ITConfig(u8 RCC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_IT(RCC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Perform Byte access to RCC_CIR[12:8] bits to enable the selected interrupts */
    *(vu8 *) CIR_BYTE2_ADDRESS |= RCC_IT;
  }
  else
  {
    /* Perform Byte access to RCC_CIR[12:8] bits to disable the selected interrupts */
    *(vu8 *) CIR_BYTE2_ADDRESS &= (u8)~RCC_IT;
  }
}

/*******************************************************************************
* Function Name  : RCC_USBCLKConfig
* Description    : Configures the USB clock (USBCLK).
* Input          : - RCC_USBCLKSource: specifies the USB clock source. This clock
*                    is derived from the PLL output.
*                    This parameter can be one of the following values:
*                       - RCC_USBCLKSource_PLLCLK_1Div5: PLL clock divided by 1,5
*                         selected as USB clock source
*                       - RCC_USBCLKSource_PLLCLK_Div1: PLL clock selected as USB
*                         clock source
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_USBCLKConfig(u32 RCC_USBCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_USBCLK_SOURCE(RCC_USBCLKSource));

  *(vu32 *) CFGR_USBPRE_BB = RCC_USBCLKSource;
}

/*******************************************************************************
* Function Name  : RCC_ADCCLKConfig
* Description    : Configures the ADC clock (ADCCLK).
* Input          : - RCC_PCLK2: defines the ADC clock divider. This clock is
*                    derived from the APB2 clock (PCLK2).
*                    This parameter can be one of the following values:
*                       - RCC_PCLK2_Div2: ADC clock = PCLK2/2
*                       - RCC_PCLK2_Div4: ADC clock = PCLK2/4
*                       - RCC_PCLK2_Div6: ADC clock = PCLK2/6
*                       - RCC_PCLK2_Div8: ADC clock = PCLK2/8
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_ADCCLKConfig(u32 RCC_PCLK2)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RCC_ADCCLK(RCC_PCLK2));

  tmpreg = RCC->CFGR;

  /* Clear ADCPRE[1:0] bits */
  tmpreg &= CFGR_ADCPRE_Reset_Mask;

  /* Set ADCPRE[1:0] bits according to RCC_PCLK2 value */
  tmpreg |= RCC_PCLK2;

  /* Store the new value */
  RCC->CFGR = tmpreg;
}

/*******************************************************************************
* Function Name  : RCC_LSEConfig
* Description    : Configures the External Low Speed oscillator (LSE).
* Input          : - RCC_LSE: specifies the new state of the LSE.
*                    This parameter can be one of the following values:
*                       - RCC_LSE_OFF: LSE oscillator OFF
*                       - RCC_LSE_ON: LSE oscillator ON
*                       - RCC_LSE_Bypass: LSE oscillator bypassed with external
*                         clock
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_LSEConfig(u8 RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));

  /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
  /* Reset LSEON bit */
  *(vu8 *) BDCR_ADDRESS = RCC_LSE_OFF;

  /* Reset LSEBYP bit */
  *(vu8 *) BDCR_ADDRESS = RCC_LSE_OFF;

  /* Configure LSE (RCC_LSE_OFF is already covered by the code section above) */
  switch(RCC_LSE)
  {
    case RCC_LSE_ON:
      /* Set LSEON bit */
      *(vu8 *) BDCR_ADDRESS = RCC_LSE_ON;
      break;
      
    case RCC_LSE_Bypass:
      /* Set LSEBYP and LSEON bits */
      *(vu8 *) BDCR_ADDRESS = RCC_LSE_Bypass | RCC_LSE_ON;
      break;            
      
    default:
      break;      
  }
}

/*******************************************************************************
* Function Name  : RCC_LSICmd
* Description    : Enables or disables the Internal Low Speed oscillator (LSI).
*                  LSI can not be disabled if the IWDG is running.
* Input          : - NewState: new state of the LSI.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_LSICmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CSR_LSION_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : RCC_RTCCLKConfig
* Description    : Configures the RTC clock (RTCCLK).
*                  Once the RTC clock is selected it can’t be changed unless the
*                  Backup domain is reset.
* Input          : - RCC_RTCCLKSource: specifies the RTC clock source.
*                    This parameter can be one of the following values:
*                       - RCC_RTCCLKSource_LSE: LSE selected as RTC clock
*                       - RCC_RTCCLKSource_LSI: LSI selected as RTC clock
*                       - RCC_RTCCLKSource_HSE_Div128: HSE clock divided by 128
*                         selected as RTC clock
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_RTCCLKConfig(u32 RCC_RTCCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));

  /* Select the RTC clock source */
  RCC->BDCR |= RCC_RTCCLKSource;
}

/*******************************************************************************
* Function Name  : RCC_RTCCLKCmd
* Description    : Enables or disables the RTC clock.
*                  This function must be used only after the RTC clock was
*                  selected using the RCC_RTCCLKConfig function.
* Input          : - NewState: new state of the RTC clock.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_RTCCLKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) BDCR_RTCEN_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : RCC_GetClocksFreq
* Description    : Returns the frequencies of different on chip clocks.
* Input          : - RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which
*                    will hold the clocks frequencies.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
  u32 tmp = 0, pllmull = 0, pllsource = 0, presc = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & CFGR_SWS_Mask;

  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;

    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = HSE_Value;
      break;

    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & CFGR_PLLMull_Mask;
      pllmull = ( pllmull >> 18) + 2;

      pllsource = RCC->CFGR & CFGR_PLLSRC_Mask;

      if (pllsource == 0x00)
      {/* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Frequency = (HSI_Value >> 1) * pllmull;
      }
      else
      {/* HSE selected as PLL clock entry */

        if ((RCC->CFGR & CFGR_PLLXTPRE_Mask) != (u32)RESET)
        {/* HSE oscillator clock divided by 2 */

          RCC_Clocks->SYSCLK_Frequency = (HSE_Value >> 1) * pllmull;
        }
        else
        {
          RCC_Clocks->SYSCLK_Frequency = HSE_Value * pllmull;
        }
      }
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = HSI_Value;
      break;
  }

  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & CFGR_HPRE_Set_Mask;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];

  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE1_Set_Mask;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];

  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & CFGR_PPRE2_Set_Mask;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];

  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;

  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & CFGR_ADCPRE_Set_Mask;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];

  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

/*******************************************************************************
* Function Name  : RCC_AHBPeriphClockCmd
* Description    : Enables or disables the AHB peripheral clock.
* Input          : - RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
*                    This parameter can be any combination of the following values:
*                       - RCC_AHBPeriph_DMA1
*                       - RCC_AHBPeriph_DMA2
*                       - RCC_AHBPeriph_SRAM
*                       - RCC_AHBPeriph_FLITF
*                       - RCC_AHBPeriph_CRC
*                       - RCC_AHBPeriph_FSMC
*                       - RCC_AHBPeriph_SDIO
*                    SRAM and FLITF clock can be disabled only during sleep mode.
*                  - NewState: new state of the specified peripheral clock.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_AHBPeriphClockCmd(u32 RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB2PeriphClockCmd
* Description    : Enables or disables the High Speed APB (APB2) peripheral clock.
* Input          : - RCC_APB2Periph: specifies the APB2 peripheral to gates its
*                    clock.
*                    This parameter can be any combination of the following values:
*                       - RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
*                         RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
*                         RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
*                         RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
*                         RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3,
*                         RCC_APB2Periph_ALL
*                  - NewState: new state of the specified peripheral clock.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_APB2PeriphClockCmd(u32 RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2ENR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB1PeriphClockCmd
* Description    : Enables or disables the Low Speed APB (APB1) peripheral clock.
* Input          : - RCC_APB1Periph: specifies the APB1 peripheral to gates its
*                    clock.
*                    This parameter can be any combination of the following values:
*                       - RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
*                         RCC_APB1Periph_TIM5, RCC_APB1Periph_TIM6, RCC_APB1Periph_TIM7,
*                         RCC_APB1Periph_WWDG, RCC_APB1Periph_SPI2, RCC_APB1Periph_SPI3,
*                         RCC_APB1Periph_USART2, RCC_APB1Periph_USART3, RCC_APB1Periph_USART4, 
*                         RCC_APB1Periph_USART5, RCC_APB1Periph_I2C1, RCC_APB1Periph_I2C2,
*                         RCC_APB1Periph_USB, RCC_APB1Periph_CAN, RCC_APB1Periph_BKP,
*                         RCC_APB1Periph_PWR, RCC_APB1Periph_DAC, RCC_APB1Periph_ALL
*                  - NewState: new state of the specified peripheral clock.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_APB1PeriphClockCmd(u32 RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1ENR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1ENR &= ~RCC_APB1Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB2PeriphResetCmd
* Description    : Forces or releases High Speed APB (APB2) peripheral reset.
* Input          : - RCC_APB2Periph: specifies the APB2 peripheral to reset.
*                    This parameter can be any combination of the following values:
*                       - RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
*                         RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
*                         RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
*                         RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
*                         RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3,
*                         RCC_APB2Periph_ALL
*                  - NewState: new state of the specified peripheral reset.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_APB2PeriphResetCmd(u32 RCC_APB2Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB2RSTR |= RCC_APB2Periph;
  }
  else
  {
    RCC->APB2RSTR &= ~RCC_APB2Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_APB1PeriphResetCmd
* Description    : Forces or releases Low Speed APB (APB1) peripheral reset.
* Input          : - RCC_APB1Periph: specifies the APB1 peripheral to reset.
*                    This parameter can be any combination of the following values:
*                       - RCC_APB1Periph_TIM2, RCC_APB1Periph_TIM3, RCC_APB1Periph_TIM4,
*                         RCC_APB1Periph_TIM5, RCC_APB1Periph_TIM6, RCC_APB1Periph_TIM7,
*                         RCC_APB1Periph_WWDG, RCC_APB1Periph_SPI2, RCC_APB1Periph_SPI3,
*                         RCC_APB1Periph_USART2, RCC_APB1Periph_USART3, RCC_APB1Periph_USART4, 
*                         RCC_APB1Periph_USART5, RCC_APB1Periph_I2C1, RCC_APB1Periph_I2C2,
*                         RCC_APB1Periph_USB, RCC_APB1Periph_CAN, RCC_APB1Periph_BKP,
*                         RCC_APB1Periph_PWR, RCC_APB1Periph_DAC, RCC_APB1Periph_ALL
*                  - NewState: new state of the specified peripheral clock.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_APB1PeriphResetCmd(u32 RCC_APB1Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->APB1RSTR |= RCC_APB1Periph;
  }
  else
  {
    RCC->APB1RSTR &= ~RCC_APB1Periph;
  }
}

/*******************************************************************************
* Function Name  : RCC_BackupResetCmd
* Description    : Forces or releases the Backup domain reset.
* Input          : - NewState: new state of the Backup domain reset.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_BackupResetCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) BDCR_BDRST_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : RCC_ClockSecuritySystemCmd
* Description    : Enables or disables the Clock Security System.
* Input          : - NewState: new state of the Clock Security System..
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(vu32 *) CR_CSSON_BB = (u32)NewState;
}

/*******************************************************************************
* Function Name  : RCC_MCOConfig
* Description    : Selects the clock source to output on MCO pin.
* Input          : - RCC_MCO: specifies the clock source to output.
*                    This parameter can be one of the following values:
*                       - RCC_MCO_NoClock: No clock selected
*                       - RCC_MCO_SYSCLK: System clock selected
*                       - RCC_MCO_HSI: HSI oscillator clock selected
*                       - RCC_MCO_HSE: HSE oscillator clock selected
*                       - RCC_MCO_PLLCLK_Div2: PLL clock divided by 2 selected
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_MCOConfig(u8 RCC_MCO)
{
  /* Check the parameters */
  assert_param(IS_RCC_MCO(RCC_MCO));

  /* Perform Byte access to MCO[2:0] bits to select the MCO source */
  *(vu8 *) CFGR_BYTE4_ADDRESS = RCC_MCO;
}

/*******************************************************************************
* Function Name  : RCC_GetFlagStatus
* Description    : Checks whether the specified RCC flag is set or not.
* Input          : - RCC_FLAG: specifies the flag to check.
*                    This parameter can be one of the following values:
*                       - RCC_FLAG_HSIRDY: HSI oscillator clock ready
*                       - RCC_FLAG_HSERDY: HSE oscillator clock ready
*                       - RCC_FLAG_PLLRDY: PLL clock ready
*                       - RCC_FLAG_LSERDY: LSE oscillator clock ready
*                       - RCC_FLAG_LSIRDY: LSI oscillator clock ready
*                       - RCC_FLAG_PINRST: Pin reset
*                       - RCC_FLAG_PORRST: POR/PDR reset
*                       - RCC_FLAG_SFTRST: Software reset
*                       - RCC_FLAG_IWDGRST: Independent Watchdog reset
*                       - RCC_FLAG_WWDGRST: Window Watchdog reset
*                       - RCC_FLAG_LPWRRST: Low Power reset
* Output         : None
* Return         : The new state of RCC_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus RCC_GetFlagStatus(u8 RCC_FLAG)
{
  u32 tmp = 0;
  u32 statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_FLAG(RCC_FLAG));

  /* Get the RCC register index */
  tmp = RCC_FLAG >> 5;

  if (tmp == 1)               /* The flag to check is in CR register */
  {
    statusreg = RCC->CR;
  }
  else if (tmp == 2)          /* The flag to check is in BDCR register */
  {
    statusreg = RCC->BDCR;
  }
  else                       /* The flag to check is in CSR register */
  {
    statusreg = RCC->CSR;
  }

  /* Get the flag position */
  tmp = RCC_FLAG & FLAG_Mask;

  if ((statusreg & ((u32)1 << tmp)) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

/*******************************************************************************
* Function Name  : RCC_ClearFlag
* Description    : Clears the RCC reset flags.
*                  The reset flags are: RCC_FLAG_PINRST, RCC_FLAG_PORRST,
*                  RCC_FLAG_SFTRST, RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST,
*                  RCC_FLAG_LPWRRST
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_ClearFlag(void)
{
  /* Set RMVF bit to clear the reset flags */
  RCC->CSR |= CSR_RMVF_Set;
}

/*******************************************************************************
* Function Name  : RCC_GetITStatus
* Description    : Checks whether the specified RCC interrupt has occurred or not.
* Input          : - RCC_IT: specifies the RCC interrupt source to check.
*                    This parameter can be one of the following values:
*                       - RCC_IT_LSIRDY: LSI ready interrupt
*                       - RCC_IT_LSERDY: LSE ready interrupt
*                       - RCC_IT_HSIRDY: HSI ready interrupt
*                       - RCC_IT_HSERDY: HSE ready interrupt
*                       - RCC_IT_PLLRDY: PLL ready interrupt
*                       - RCC_IT_CSS: Clock Security System interrupt
* Output         : None
* Return         : The new state of RCC_IT (SET or RESET).
*******************************************************************************/
ITStatus RCC_GetITStatus(u8 RCC_IT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RCC_GET_IT(RCC_IT));

  /* Check the status of the specified RCC interrupt */
  if ((RCC->CIR & RCC_IT) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the RCC_IT status */
  return  bitstatus;
}

/*******************************************************************************
* Function Name  : RCC_ClearITPendingBit
* Description    : Clears the RCC’s interrupt pending bits.
* Input          : - RCC_IT: specifies the interrupt pending bit to clear.
*                    This parameter can be any combination of the following values:
*                       - RCC_IT_LSIRDY: LSI ready interrupt
*                       - RCC_IT_LSERDY: LSE ready interrupt
*                       - RCC_IT_HSIRDY: HSI ready interrupt
*                       - RCC_IT_HSERDY: HSE ready interrupt
*                       - RCC_IT_PLLRDY: PLL ready interrupt
*                       - RCC_IT_CSS: Clock Security System interrupt
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_ClearITPendingBit(u8 RCC_IT)
{
  /* Check the parameters */
  assert_param(IS_RCC_CLEAR_IT(RCC_IT));

  /* Perform Byte access to RCC_CIR[23:16] bits to clear the selected interrupt
     pending bits */
  *(vu8 *) CIR_BYTE3_ADDRESS = RCC_IT;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
