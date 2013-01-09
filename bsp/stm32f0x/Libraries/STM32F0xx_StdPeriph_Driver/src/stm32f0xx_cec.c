/**
  ******************************************************************************
  * @file    stm32f0xx_cec.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Consumer Electronics Control (CEC) peripheral:
  *            + Initialization and Configuration
  *            + Data transfers functions
  *            + Interrupts and flags management
  *               
  *  @verbatim
  ==============================================================================
                            ##### CEC features #####
  ==============================================================================
      [..] This device provides some features:
           (#) Supports HDMI-CEC specification 1.4.
           (#) Supports two source clocks(HSI/244 or LSE).
           (#) Works in stop mode(without APB clock, but with CEC clock 32KHz).
               It can genarate an interrupt in the CEC clock domain that the CPU 
               wakes up from the low power mode.
           (#) Configurable Signal Free Time before of transmission start. The 
               number of nominal data bit periods waited before transmission can be
               ruled by Hardware or Software.
           (#) Configurable Peripheral Address (multi-addressing configuration).
           (#) Supports listen mode.The CEC Messages addressed to different destination
               can be received without interfering with CEC bus when Listen mode option is enabled.
           (#) Configurable Rx-Tolerance(Standard and Extended tolerance margin).
           (#) Error detection with configurable error bit generation.
           (#) Arbitration lost error in the case of two CEC devices starting at the same time.

                            ##### How to use this driver ##### 
  ==============================================================================
      [..] This driver provides functions to configure and program the CEC device,
       follow steps below:
           (#) The source clock can be configured using:
               (++) RCC_CECCLKConfig(RCC_CECCLK_HSI_Div244) for HSI(Default) 
               (++) RCC_CECCLKConfig(RCC_CECCLK_LSE) for LSE.
           (#) Enable CEC peripheral clock using RCC_APBPeriphClockCmd(RCC_APBPeriph_CEC, ENABLE).
           (#) Peripherals alternate function.
               (++) Connect the pin to the desired peripherals' Alternate Function (AF) using 
               GPIO_PinAFConfig() function.
               (++) Configure the desired pin in alternate function by:
               GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
               (++) Select the type open-drain and output speed via GPIO_OType 
               and GPIO_Speed members.
               (++) Call GPIO_Init() function.
           (#) Configure the Signal Free Time, Rx Tolerance, Stop reception generation 
               and Bit error generation using the CEC_Init() function.
               The function CEC_Init() must be called when the CEC peripheral is disabled.
           (#) Configure the CEC own address by calling the fuction CEC_OwnAddressConfig().
           (#) Optionally, you can configure the Listen mode using the function CEC_ListenModeCmd().
           (#) Enable the NVIC and the corresponding interrupt using the function 
               CEC_ITConfig() if you need to use interrupt mode.
               CEC_ITConfig() must be called before enabling the CEC peripheral.
           (#) Enable the CEC using the CEC_Cmd() function.
           (#) Charge the first data byte in the TXDR register using CEC_SendDataByte().
           (#) Enable the transmission of the Byte of a CEC message using CEC_StartOfMessage() 
           (#) Transmit single data through the CEC peripheral using CEC_SendDataByte() 
               and Receive the last transmitted byte using CEC_ReceiveDataByte().
           (#) Enable the CEC_EndOfMessage() in order to indicate the last byte of the message.
      [..]
           (@) If the listen mode is enabled, Stop reception generation and Bit error generation 
               must be in reset state.
           (@) If the CEC message consists of only 1 byte, the function CEC_EndOfMessage()
               must be called before CEC_StartOfMessage().
  
   @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_cec.h"
#include "stm32f0xx_rcc.h"

/** @addtogroup STM32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup CEC 
  * @brief CEC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BROADCAST_ADDRESS      ((uint32_t)0x0000F)
#define CFGR_CLEAR_MASK        ((uint32_t)0x7000FE00)   /* CFGR register Mask */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CEC_Private_Functions 
  * @{
  */

/** @defgroup CEC_Group1 Initialization and Configuration functions
 *  @brief   Initialization and Configuration functions
 *
@verbatim  
 ===============================================================================
                            ##### Initialization and Configuration functions #####
 ===============================================================================
      [..] This section provides functions allowing to initialize:
            (+) CEC own addresses
            (+) CEC Signal Free Time
            (+) CEC Rx Tolerance
            (+) CEC Stop Reception
            (+) CEC Bit Rising Error
            (+) CEC Long Bit Period Error
      [..] This section provides also a function to configure the CEC peripheral in Listen Mode.
           Messages addressed to different destination can be received when Listen mode is 
           enabled without interfering with CEC bus.
@endverbatim
  * @{
  */

/**
  * @brief  Deinitializes the CEC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CEC_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, DISABLE);
}

/**
  * @brief  Initializes the CEC peripheral according to the specified parameters
  *         in the CEC_InitStruct.
  * @note   The CEC parameters must be configured before enabling the CEC peripheral.
  * @param  CEC_InitStruct: pointer to an CEC_InitTypeDef structure that contains
  *         the configuration information for the specified CEC peripheral.
  * @retval None
  */
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_CEC_SIGNAL_FREE_TIME(CEC_InitStruct->CEC_SignalFreeTime));
  assert_param(IS_CEC_RX_TOLERANCE(CEC_InitStruct->CEC_RxTolerance));
  assert_param(IS_CEC_STOP_RECEPTION(CEC_InitStruct->CEC_StopReception));
  assert_param(IS_CEC_BIT_RISING_ERROR(CEC_InitStruct->CEC_BitRisingError));
  assert_param(IS_CEC_LONG_BIT_PERIOD_ERROR(CEC_InitStruct->CEC_LongBitPeriodError));
  assert_param(IS_CEC_BDR_NO_GEN_ERROR(CEC_InitStruct->CEC_BRDNoGen));
  assert_param(IS_CEC_SFT_OPTION(CEC_InitStruct->CEC_SFTOption));

  /* Get the CEC CFGR value */
  tmpreg = CEC->CFGR;

  /* Clear CFGR bits */
  tmpreg &= CFGR_CLEAR_MASK;

  /* Configure the CEC peripheral */
  tmpreg |= (CEC_InitStruct->CEC_SignalFreeTime | CEC_InitStruct->CEC_RxTolerance |
             CEC_InitStruct->CEC_StopReception  | CEC_InitStruct->CEC_BitRisingError |
             CEC_InitStruct->CEC_LongBitPeriodError| CEC_InitStruct->CEC_BRDNoGen |
             CEC_InitStruct->CEC_SFTOption);

  /* Write to CEC CFGR  register */
  CEC->CFGR = tmpreg;
}

/**
  * @brief  Fills each CEC_InitStruct member with its default value.
  * @param  CEC_InitStruct: pointer to a CEC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void CEC_StructInit(CEC_InitTypeDef* CEC_InitStruct)
{
  CEC_InitStruct->CEC_SignalFreeTime = CEC_SignalFreeTime_Standard;
  CEC_InitStruct->CEC_RxTolerance = CEC_RxTolerance_Standard;
  CEC_InitStruct->CEC_StopReception = CEC_StopReception_Off;
  CEC_InitStruct->CEC_BitRisingError = CEC_BitRisingError_Off;
  CEC_InitStruct->CEC_LongBitPeriodError = CEC_LongBitPeriodError_Off;
  CEC_InitStruct->CEC_BRDNoGen = CEC_BRDNoGen_Off;
  CEC_InitStruct->CEC_SFTOption = CEC_SFTOption_Off;
}

/**
  * @brief  Enables or disables the CEC peripheral.
  * @param  NewState: new state of the CEC peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_Cmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the CEC peripheral */
    CEC->CR |= CEC_CR_CECEN;
  }
  else
  {
    /* Disable the CEC peripheral */
    CEC->CR &= ~CEC_CR_CECEN;
  }
}

/**
  * @brief  Enables or disables the CEC Listen Mode.
  * @param  NewState: new state of the Listen Mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_ListenModeCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Listen Mode */
    CEC->CFGR |= CEC_CFGR_LSTN;
  }
  else
  {
    /* Disable the Listen Mode */
    CEC->CFGR &= ~CEC_CFGR_LSTN;
  }
}

/**
  * @brief  Defines the Own Address of the CEC device.
  * @param  CEC_OwnAddress: The CEC own address.
  * @retval None
  */
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress)
{
  uint32_t tmp =0x00;
  /* Check the parameters */
  assert_param(IS_CEC_ADDRESS(CEC_OwnAddress));
  tmp = 1 <<(CEC_OwnAddress + 16);
  /* Set the CEC own address */
  CEC->CFGR |= tmp;
}

/**
  * @brief  Clears the Own Address of the CEC device.
  * @param  CEC_OwnAddress: The CEC own address.
  * @retval None
  */
void CEC_OwnAddressClear(void)
{
  /* Set the CEC own address */
  CEC->CFGR = 0x0;
}

/**
  * @}
  */

/** @defgroup CEC_Group2 Data transfers functions
 *  @brief    Data transfers functions
 *
@verbatim
 ===============================================================================
                            ##### Data transfers functions #####
 ===============================================================================
    [..] This section provides functions allowing the CEC data transfers.The read 
         access of the CEC_RXDR register can be done using the CEC_ReceiveData()function 
         and returns the Rx buffered value. Whereas a write access to the CEC_TXDR can be 
         done using CEC_SendData() function.
@endverbatim
  * @{
  */

/**
  * @brief  Transmits single data through the CEC peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void CEC_SendData(uint8_t Data)
{
  /* Transmit Data */
  CEC->TXDR = Data;
}

/**
  * @brief  Returns the most recent received data by the CEC peripheral.
  * @param  None
  * @retval The received data.
  */
uint8_t CEC_ReceiveData(void)
{
  /* Receive Data */
  return (uint8_t)(CEC->RXDR);
}

/**
  * @brief  Starts a new message.
  * @param  None
  * @retval None
  */
void CEC_StartOfMessage(void)
{
  /* Starts of new message */
  CEC->CR |= CEC_CR_TXSOM; 
}

/**
  * @brief  Transmits message with an EOM bit.
  * @param  None.
  * @retval None
  */
void CEC_EndOfMessage(void)
{
  /* The data byte will be transmitted with an EOM bit */
  CEC->CR |= CEC_CR_TXEOM;
}

/**
  * @}
  */

/** @defgroup CEC_Group3 Interrupts and flags management functions
 *  @brief    Interrupts and flags management functions
*
@verbatim
 ===============================================================================
                            ##### Interrupts and flags management functions ##### 
 ===============================================================================
    [..] This section provides functions allowing to configure the CEC Interrupts
         sources and check or clear the flags or pending bits status.
    [..] The user should identify which mode will be used in his application to manage
         the communication: Polling mode or Interrupt mode.
  
    [..] In polling mode, the CEC can be managed by the following flags:
            (+) CEC_FLAG_TXACKE : to indicate a missing acknowledge in transmission mode.
            (+) CEC_FLAG_TXERR  : to indicate an error occurs during transmission mode.
                                  The initiator detects low impedance in the CEC line.
            (+) CEC_FLAG_TXUDR  : to indicate if an underrun error occurs in transmission mode.
                                  The transmission is enabled while the software has not yet 
                                  loaded any value into the TXDR register.
            (+) CEC_FLAG_TXEND  : to indicate the end of successful transmission.
            (+) CEC_FLAG_TXBR   : to indicate the next transmission data has to be written to TXDR.
            (+) CEC_FLAG_ARBLST : to indicate arbitration lost in the case of two CEC devices
                                  starting at the same time.
            (+) CEC_FLAG_RXACKE : to indicate a missing acknowledge in receive mode.
            (+) CEC_FLAG_LBPE   : to indicate a long bit period error generated during receive mode.
            (+) CEC_FLAG_SBPE   : to indicate a short bit period error generated during receive mode.
            (+) CEC_FLAG_BRE    : to indicate a bit rising error generated during receive mode.
            (+) CEC_FLAG_RXOVR  : to indicate if an overrun error occur while receiving a CEC message.
                                  A byte is not yet received while a new byte is stored in the RXDR register.
            (+) CEC_FLAG_RXEND  : to indicate the end Of reception
            (+) CEC_FLAG_RXBR   : to indicate a new byte has been received from the CEC line and 
                                  stored into the RXDR buffer.
    [..]
           (@)In this Mode, it is advised to use the following functions:
              FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG);
              void CEC_ClearFlag(uint16_t CEC_FLAG);

    [..] In Interrupt mode, the CEC can be managed by the following interrupt sources:
           (+) CEC_IT_TXACKE : to indicate a TX Missing acknowledge 
           (+) CEC_IT_TXACKE : to indicate a missing acknowledge in transmission mode.
           (+) CEC_IT_TXERR  : to indicate an error occurs during transmission mode.
                               The initiator detects low impedance in the CEC line.
           (+) CEC_IT_TXUDR  : to indicate if an underrun error occurs in transmission mode.
                               The transmission is enabled while the software has not yet 
                               loaded any value into the TXDR register.
           (+) CEC_IT_TXEND  : to indicate the end of successful transmission.
           (+) CEC_IT_TXBR   : to indicate the next transmission data has to be written to TXDR register.
           (+) CEC_IT_ARBLST : to indicate arbitration lost in the case of two CEC devices
                                starting at the same time.
           (+) CEC_IT_RXACKE : to indicate a missing acknowledge in receive mode.
           (+) CEC_IT_LBPE   : to indicate a long bit period error generated during receive mode.
           (+) CEC_IT_SBPE   : to indicate a short bit period error generated during receive mode.
           (+) CEC_IT_BRE    : to indicate a bit rising error generated during receive mode.
           (+) CEC_IT_RXOVR  : to indicate if an overrun error occur while receiving a CEC message.
                               A byte is not yet received while a new byte is stored in the RXDR register.
           (+) CEC_IT_RXEND  : to indicate the end Of reception
           (+) CEC_IT_RXBR   : to indicate a new byte has been received from the CEC line and 
                                stored into the RXDR buffer.
    [..]
           (@)In this Mode it is advised to use the following functions:
              void CEC_ITConfig( uint16_t CEC_IT, FunctionalState NewState);
              ITStatus CEC_GetITStatus(uint16_t CEC_IT);
              void CEC_ClearITPendingBit(uint16_t CEC_IT);
              

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the selected CEC interrupts.
  * @param  CEC_IT: specifies the CEC interrupt source to be enabled.
  *         This parameter can be any combination of the following values:
  *     @arg CEC_IT_TXACKE: Tx Missing acknowledge Error
  *     @arg CEC_IT_TXERR: Tx Error.
  *     @arg CEC_IT_TXUDR: Tx-Buffer Underrun.
  *     @arg CEC_IT_TXEND: End of Transmission (successful transmission of the last byte).
  *     @arg CEC_IT_TXBR: Tx-Byte Request.
  *     @arg CEC_IT_ARBLST: Arbitration Lost
  *     @arg CEC_IT_RXACKE: Rx-Missing Acknowledge
  *     @arg CEC_IT_LBPE: Rx Long period Error
  *     @arg CEC_IT_SBPE: Rx Short period Error
  *     @arg CEC_IT_BRE: Rx Bit Rising Error
  *     @arg CEC_IT_RXOVR: Rx Overrun.
  *     @arg CEC_IT_RXEND: End Of Reception
  *     @arg CEC_IT_RXBR: Rx-Byte Received
  * @param  NewState: new state of the selected CEC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_ITConfig(uint16_t CEC_IT, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_CEC_IT(CEC_IT));

  if (NewState != DISABLE)
  {
    /* Enable the selected CEC interrupt */
    CEC->IER |= CEC_IT;
  }
  else
  {
    CEC_IT =~CEC_IT;
    /* Disable the selected CEC interrupt */
    CEC->IER &= CEC_IT;
  }
}

/**
  * @brief  Gets the CEC flag status.
  * @param  CEC_FLAG: specifies the CEC flag to check.
  *     This parameter can be one of the following values:
  *     @arg CEC_FLAG_TXACKE: Tx Missing acknowledge Error
  *     @arg CEC_FLAG_TXERR: Tx Error.
  *     @arg CEC_FLAG_TXUDR: Tx-Buffer Underrun.
  *     @arg CEC_FLAG_TXEND: End of transmission (successful transmission of the last byte).
  *     @arg CEC_FLAG_TXBR: Tx-Byte Request.
  *     @arg CEC_FLAG_ARBLST: Arbitration Lost
  *     @arg CEC_FLAG_RXACKE: Rx-Missing Acknowledge 
  *     @arg CEC_FLAG_LBPE: Rx Long period Error
  *     @arg CEC_FLAG_SBPE: Rx Short period Error
  *     @arg CEC_FLAG_BRE: Rx Bit Rissing Error
  *     @arg CEC_FLAG_RXOVR: Rx Overrun.
  *     @arg CEC_FLAG_RXEND: End Of Reception.
  *     @arg CEC_FLAG_RXBR: Rx-Byte Received.
  * @retval The new state of CEC_FLAG (SET or RESET)
  */
FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG) 
{
  FlagStatus bitstatus = RESET;
  
  assert_param(IS_CEC_GET_FLAG(CEC_FLAG));
  
  /* Check the status of the specified CEC flag */
  if ((CEC->ISR & CEC_FLAG) != (uint16_t)RESET)
  {
    /* CEC flag is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC flag is reset */
    bitstatus = RESET;
  }

  /* Return the CEC flag status */
  return  bitstatus;
}

/**
  * @brief  Clears the CEC's pending flags.
  * @param  CEC_FLAG: specifies the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg CEC_FLAG_TXACKE: Tx Missing acknowledge Error
  *     @arg CEC_FLAG_TXERR: Tx Error
  *     @arg CEC_FLAG_TXUDR: Tx-Buffer Underrun
  *     @arg CEC_FLAG_TXEND: End of transmission (successful transmission of the last byte).
  *     @arg CEC_FLAG_TXBR: Tx-Byte Request
  *     @arg CEC_FLAG_ARBLST: Arbitration Lost
  *     @arg CEC_FLAG_RXACKE: Rx Missing Acknowledge 
  *     @arg CEC_FLAG_LBPE: Rx Long period Error
  *     @arg CEC_FLAG_SBPE: Rx Short period Error
  *     @arg CEC_FLAG_BRE: Rx Bit Rising Error
  *     @arg CEC_FLAG_RXOVR: Rx Overrun
  *     @arg CEC_FLAG_RXEND: End Of Reception
  *     @arg CEC_FLAG_RXBR: Rx-Byte Received
  * @retval None
  */
void CEC_ClearFlag(uint32_t CEC_FLAG)
{
  assert_param(IS_CEC_CLEAR_FLAG(CEC_FLAG));

  /* Clear the selected CEC flag */
  CEC->ISR = CEC_FLAG;
}

/**
  * @brief  Checks whether the specified CEC interrupt has occurred or not.
  * @param  CEC_IT: specifies the CEC interrupt source to check. 
  *   This parameter can be one of the following values:
  *     @arg CEC_IT_TXACKE: Tx Missing acknowledge Error
  *     @arg CEC_IT_TXERR: Tx Error.
  *     @arg CEC_IT_TXUDR: Tx-Buffer Underrun.
  *     @arg CEC_IT_TXEND: End of transmission (successful transmission of the last byte).
  *     @arg CEC_IT_TXBR: Tx-Byte Request.
  *     @arg CEC_IT_ARBLST: Arbitration Lost.
  *     @arg CEC_IT_RXACKE: Rx-Missing Acknowledge.
  *     @arg CEC_IT_LBPE: Rx Long period Error.
  *     @arg CEC_IT_SBPE: Rx Short period Error.
  *     @arg CEC_IT_BRE: Rx Bit Rising Error.
  *     @arg CEC_IT_RXOVR: Rx Overrun.
  *     @arg CEC_IT_RXEND: End Of Reception.
  *     @arg CEC_IT_RXBR: Rx-Byte Received 
  * @retval The new state of CEC_IT (SET or RESET).
  */
ITStatus CEC_GetITStatus(uint16_t CEC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_CEC_GET_IT(CEC_IT));

  /* Get the CEC IT enable bit status */
  enablestatus = (CEC->IER & CEC_IT);

  /* Check the status of the specified CEC interrupt */
  if (((CEC->ISR & CEC_IT) != (uint32_t)RESET) && enablestatus)
  {
    /* CEC interrupt is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC interrupt is reset */
    bitstatus = RESET;
  }

  /* Return the CEC interrupt status */
  return  bitstatus;
}

/**
  * @brief  Clears the CEC's interrupt pending bits.
  * @param  CEC_IT: specifies the CEC interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg CEC_IT_TXACKE: Tx Missing acknowledge Error
  *     @arg CEC_IT_TXERR: Tx Error
  *     @arg CEC_IT_TXUDR: Tx-Buffer Underrun
  *     @arg CEC_IT_TXEND: End of Transmission
  *     @arg CEC_IT_TXBR: Tx-Byte Request
  *     @arg CEC_IT_ARBLST: Arbitration Lost
  *     @arg CEC_IT_RXACKE: Rx-Missing Acknowledge
  *     @arg CEC_IT_LBPE: Rx Long period Error
  *     @arg CEC_IT_SBPE: Rx Short period Error
  *     @arg CEC_IT_BRE: Rx Bit Rising Error
  *     @arg CEC_IT_RXOVR: Rx Overrun
  *     @arg CEC_IT_RXEND: End Of Reception
  *     @arg CEC_IT_RXBR: Rx-Byte Received
  * @retval None
  */
void CEC_ClearITPendingBit(uint16_t CEC_IT)
{
  assert_param(IS_CEC_IT(CEC_IT));

  /* Clear the selected CEC interrupt pending bits */
  CEC->ISR = CEC_IT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
