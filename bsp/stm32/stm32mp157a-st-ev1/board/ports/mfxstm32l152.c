/** 
  ******************************************************************************
  * @file    mfxstm32l152.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the MFXSTM32L152
  *          IO Expander devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "mfxstm32l152.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Component
  * @{
  */ 
  
/** @defgroup MFXSTM32L152
  * @{
  */   
  
/* Private typedef -----------------------------------------------------------*/

/** @defgroup MFXSTM32L152_Private_Types_Definitions
  * @{
  */ 
 
/* Private define ------------------------------------------------------------*/

/** @defgroup MFXSTM32L152_Private_Defines
  * @{
  */ 
#define MFXSTM32L152_MAX_INSTANCE         3

/* Private macro -------------------------------------------------------------*/

/** @defgroup MFXSTM32L152_Private_Macros
  * @{
  */ 
  
/* Private variables ---------------------------------------------------------*/

/** @defgroup MFXSTM32L152_Private_Variables
  * @{
  */ 

/* Touch screen driver structure initialization */  
TS_DrvTypeDef mfxstm32l152_ts_drv = 
{
  mfxstm32l152_Init,
  mfxstm32l152_ReadID,
  mfxstm32l152_Reset,
  
  mfxstm32l152_TS_Start,
  mfxstm32l152_TS_DetectTouch,
  mfxstm32l152_TS_GetXY,
  
  mfxstm32l152_TS_EnableIT,
  mfxstm32l152_TS_ClearIT,
  mfxstm32l152_TS_ITStatus,
  mfxstm32l152_TS_DisableIT,
};

/* IO driver structure initialization */ 
IO_DrvTypeDef mfxstm32l152_io_drv = 
{
  mfxstm32l152_Init,
  mfxstm32l152_ReadID,
  mfxstm32l152_Reset,
  
  mfxstm32l152_IO_Start,
  mfxstm32l152_IO_Config,
  mfxstm32l152_IO_WritePin,
  mfxstm32l152_IO_ReadPin,
  
  mfxstm32l152_IO_EnableIT,
  mfxstm32l152_IO_DisableIT,
  mfxstm32l152_IO_ITStatus,
  mfxstm32l152_IO_ClearIT,
};

/* IDD driver structure initialization */
IDD_DrvTypeDef mfxstm32l152_idd_drv =
{
  mfxstm32l152_Init,
  mfxstm32l152_DeInit,
  mfxstm32l152_ReadID,
  mfxstm32l152_Reset,
  mfxstm32l152_LowPower,
  mfxstm32l152_WakeUp,

  mfxstm32l152_IDD_Start,
  mfxstm32l152_IDD_Config,
  mfxstm32l152_IDD_GetValue,

  mfxstm32l152_IDD_EnableIT,
  mfxstm32l152_IDD_ClearIT,
  mfxstm32l152_IDD_GetITStatus,
  mfxstm32l152_IDD_DisableIT,

  mfxstm32l152_Error_EnableIT,
  mfxstm32l152_Error_ClearIT,
  mfxstm32l152_Error_GetITStatus,
  mfxstm32l152_Error_DisableIT,
  mfxstm32l152_Error_ReadSrc,
  mfxstm32l152_Error_ReadMsg
};


/* mfxstm32l152 instances by address */
uint8_t mfxstm32l152[MFXSTM32L152_MAX_INSTANCE] = {0};
/**
  * @}
  */ 
    
/* Private function prototypes -----------------------------------------------*/

/** @defgroup MFXSTM32L152_Private_Function_Prototypes
  * @{
  */
static uint8_t mfxstm32l152_GetInstance(uint16_t DeviceAddr); 
static uint8_t  mfxstm32l152_ReleaseInstance(uint16_t DeviceAddr);
static void mfxstm32l152_reg24_setPinValue(uint16_t DeviceAddr, uint8_t RegisterAddr, uint32_t PinPosition, uint8_t PinValue );

/* Private functions ---------------------------------------------------------*/

/** @defgroup MFXSTM32L152_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the mfxstm32l152 and configure the needed hardware resources
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void mfxstm32l152_Init(uint16_t DeviceAddr)
{
  uint8_t instance;
  uint8_t empty;
  
  /* Check if device instance already exists */
  instance = mfxstm32l152_GetInstance(DeviceAddr);
  
  /* To prevent double initialization */
  if(instance == 0xFF)
  {
    /* Look for empty instance */
    empty = mfxstm32l152_GetInstance(0);
    
    if(empty < MFXSTM32L152_MAX_INSTANCE)
    {
      /* Register the current device instance */
      mfxstm32l152[empty] = DeviceAddr;
      
      /* Initialize IO BUS layer */
      MFX_IO_Init();
    }
  }
  
  mfxstm32l152_SetIrqOutPinPolarity(DeviceAddr, MFXSTM32L152_OUT_PIN_POLARITY_HIGH);
  mfxstm32l152_SetIrqOutPinType(DeviceAddr, MFXSTM32L152_OUT_PIN_TYPE_PUSHPULL);
}

/**
  * @brief  DeInitialize the mfxstm32l152 and unconfigure the needed hardware resources
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void mfxstm32l152_DeInit(uint16_t DeviceAddr)
{
  uint8_t instance;
  
  /* release existing instance */
  instance = mfxstm32l152_ReleaseInstance(DeviceAddr);
  
  /* De-Init only if instance was previously registered */
  if(instance != 0xFF)
  {
    /* De-Initialize IO BUS layer */
    MFX_IO_DeInit();
  }
}

/**
  * @brief  Reset the mfxstm32l152 by Software.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void mfxstm32l152_Reset(uint16_t DeviceAddr)
{
  /* Soft Reset */  
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL, MFXSTM32L152_SWRST);

  /* Wait for a delay to ensure registers erasing */
  rt_thread_delay(10);
}

/**
  * @brief  Put mfxstm32l152 Device in Low Power standby mode
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void  mfxstm32l152_LowPower(uint16_t DeviceAddr)
{
  /* Enter standby mode */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL, MFXSTM32L152_STANDBY);

  /* enable wakeup pin */
  MFX_IO_EnableWakeupPin();
}

/**
  * @brief  WakeUp mfxstm32l152 from standby mode
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void  mfxstm32l152_WakeUp(uint16_t DeviceAddr)
{
  uint8_t instance;
  
  /* Check if device instance already exists */
  instance = mfxstm32l152_GetInstance(DeviceAddr);
  
  /* if instance does not exist, first initialize pins*/
  if(instance == 0xFF)
  {
    /* enable wakeup pin */
    MFX_IO_EnableWakeupPin();
  }

  /* toggle wakeup pin */
  MFX_IO_Wakeup();
}

/**
  * @brief  Read the MFXSTM32L152 IO Expander device ID.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval The Device ID (two bytes).
  */
uint16_t mfxstm32l152_ReadID(uint16_t DeviceAddr)
{
  uint8_t id;
  
  /* Wait for a delay to ensure the state of registers */
  rt_thread_mdelay(1);

  /* Initialize IO BUS layer */
  MFX_IO_Init();
  
  id = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_ID);
  
  /* Return the device ID value */
  return (id);
}

/**
  * @brief  Read the MFXSTM32L152 device firmware version.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval The Device FW version (two bytes).
  */
uint16_t mfxstm32l152_ReadFwVersion(uint16_t DeviceAddr)
{
  uint8_t  data[2];

  MFX_IO_ReadMultiple((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_FW_VERSION_MSB, data, sizeof(data)) ;

  /* Recompose MFX firmware value */
  return ((data[0] << 8) | data[1]);
}

/**
  * @brief  Enable the interrupt mode for the selected IT source
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param Source: The interrupt source to be configured, could be:
  *   @arg  MFXSTM32L152_IRQ_GPIO: IO interrupt 
  *   @arg  MFXSTM32L152_IRQ_IDD : IDD interrupt    
  *   @arg  MFXSTM32L152_IRQ_ERROR : Error interrupt    
  *   @arg  MFXSTM32L152_IRQ_TS_DET : Touch Screen Controller Touch Detected interrupt  
  *   @arg  MFXSTM32L152_IRQ_TS_NE : Touch Screen FIFO Not Empty  
  *   @arg  MFXSTM32L152_IRQ_TS_TH : Touch Screen FIFO threshold triggered  
  *   @arg  MFXSTM32L152_IRQ_TS_FULL : Touch Screen FIFO Full  
  *   @arg  MFXSTM32L152_IRQ_TS_OVF : Touch Screen FIFO Overflow  
  * @retval None
  */  
void mfxstm32l152_EnableITSource(uint16_t DeviceAddr, uint8_t Source)
{
  uint8_t tmp = 0;
  
  /* Get the current value of the INT_EN register */
  tmp = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_SRC_EN);

  /* Set the interrupts to be Enabled */    
  tmp |= Source; 
  
  /* Set the register */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_SRC_EN, tmp);
}

/**
  * @brief  Disable the interrupt mode for the selected IT source
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  Source: The interrupt source to be configured, could be:
  *   @arg  MFXSTM32L152_IRQ_GPIO: IO interrupt 
  *   @arg  MFXSTM32L152_IRQ_IDD : IDD interrupt    
  *   @arg  MFXSTM32L152_IRQ_ERROR : Error interrupt    
  *   @arg  MFXSTM32L152_IRQ_TS_DET : Touch Screen Controller Touch Detected interrupt  
  *   @arg  MFXSTM32L152_IRQ_TS_NE : Touch Screen FIFO Not Empty  
  *   @arg  MFXSTM32L152_IRQ_TS_TH : Touch Screen FIFO threshold triggered  
  *   @arg  MFXSTM32L152_IRQ_TS_FULL : Touch Screen FIFO Full  
  *   @arg  MFXSTM32L152_IRQ_TS_OVF : Touch Screen FIFO Overflow  
  * @retval None
  */
void mfxstm32l152_DisableITSource(uint16_t DeviceAddr, uint8_t Source)
{
  uint8_t tmp = 0;
  
  /* Get the current value of the INT_EN register */
  tmp = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_SRC_EN);

  /* Set the interrupts to be Enabled */    
  tmp &= ~Source; 
  
  /* Set the register */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_SRC_EN, tmp);
}


/**
  * @brief  Returns the selected Global interrupt source pending bit value
  * @param  DeviceAddr: Device address on communication Bus. 
  * @param  Source: the Global interrupt source to be checked, could be:
  *   @arg  MFXSTM32L152_IRQ_GPIO: IO interrupt 
  *   @arg  MFXSTM32L152_IRQ_IDD : IDD interrupt    
  *   @arg  MFXSTM32L152_IRQ_ERROR : Error interrupt    
  *   @arg  MFXSTM32L152_IRQ_TS_DET : Touch Screen Controller Touch Detected interrupt  
  *   @arg  MFXSTM32L152_IRQ_TS_NE : Touch Screen FIFO Not Empty  
  *   @arg  MFXSTM32L152_IRQ_TS_TH : Touch Screen FIFO threshold triggered  
  *   @arg  MFXSTM32L152_IRQ_TS_FULL : Touch Screen FIFO Full  
  *   @arg  MFXSTM32L152_IRQ_TS_OVF : Touch Screen FIFO Overflow  
  * @retval The value of the checked Global interrupt source status.
  */
uint8_t mfxstm32l152_GlobalITStatus(uint16_t DeviceAddr, uint8_t Source)
{
  /* Return the global IT source status (pending or not)*/
  return((MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_PENDING) & Source));
}

/**
  * @brief  Clear the selected Global interrupt pending bit(s)
  * @param  DeviceAddr: Device address on communication Bus. 
  * @param  Source: the Global interrupt source to be cleared, could be any combination
  *         of the below values. The acknowledge signal for MFXSTM32L152_GPIOs configured in input 
  *         with interrupt is not on this register but in IRQ_GPI_ACK1, IRQ_GPI_ACK2 registers.          
  *   @arg  MFXSTM32L152_IRQ_IDD : IDD interrupt    
  *   @arg  MFXSTM32L152_IRQ_ERROR : Error interrupt    
  *   @arg  MFXSTM32L152_IRQ_TS_DET : Touch Screen Controller Touch Detected interrupt  
  *   @arg  MFXSTM32L152_IRQ_TS_NE : Touch Screen FIFO Not Empty  
  *   @arg  MFXSTM32L152_IRQ_TS_TH : Touch Screen FIFO threshold triggered  
  *   @arg  MFXSTM32L152_IRQ_TS_FULL : Touch Screen FIFO Full  
  *   @arg  MFXSTM32L152_IRQ_TS_OVF : Touch Screen FIFO Overflow  
  *  /\/\ IMPORTANT NOTE /\/\ must not use MFXSTM32L152_IRQ_GPIO as argument, see IRQ_GPI_ACK1 and IRQ_GPI_ACK2 registers 
  * @retval None
  */
void mfxstm32l152_ClearGlobalIT(uint16_t DeviceAddr, uint8_t Source)
{
  /* Write 1 to the bits that have to be cleared */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_ACK, Source);
}

/**
  * @brief  Set the global interrupt Polarity of IRQ_OUT_PIN.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  Polarity: the IT mode polarity, could be one of the following values:
  *   @arg  MFXSTM32L152_OUT_PIN_POLARITY_LOW: Interrupt output line is active Low edge      
  *   @arg  MFXSTM32L152_OUT_PIN_POLARITY_HIGH: Interrupt line output is active High edge              
  * @retval None
  */
void mfxstm32l152_SetIrqOutPinPolarity(uint16_t DeviceAddr, uint8_t Polarity)
{
  uint8_t tmp = 0;
  
  /* Get the current register value */ 
  tmp = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_MFX_IRQ_OUT);
  
  /* Mask the polarity bits */
  tmp &= ~(uint8_t)0x02;
    
  /* Modify the Interrupt Output line configuration */
  tmp |= Polarity;
  
  /* Set the new register value */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_MFX_IRQ_OUT, tmp);

  /* Wait for 1 ms for MFX to change IRQ_out pin config, before activate it */
  rt_thread_delay(1);
  
}

/**
  * @brief  Set the global interrupt Type of IRQ_OUT_PIN. 
  * @param  DeviceAddr: Device address on communication Bus.      
  * @param  Type: Interrupt line activity type, could be one of the following values:
  *   @arg  MFXSTM32L152_OUT_PIN_TYPE_OPENDRAIN: Open Drain output Interrupt line          
  *   @arg  MFXSTM32L152_OUT_PIN_TYPE_PUSHPULL: Push Pull output Interrupt line            
  * @retval None
  */
void mfxstm32l152_SetIrqOutPinType(uint16_t DeviceAddr, uint8_t Type)
{
  uint8_t tmp = 0;
  
  /* Get the current register value */ 
  tmp = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_MFX_IRQ_OUT);
  
  /* Mask the type bits */
  tmp &= ~(uint8_t)0x01;
    
  /* Modify the Interrupt Output line configuration */
  tmp |= Type;
  
  /* Set the new register value */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_MFX_IRQ_OUT, tmp);

  /* Wait for 1 ms for MFX to change IRQ_out pin config, before activate it */
  rt_thread_delay(1);
  
}


/* ------------------------------------------------------------------ */
/* ----------------------- GPIO ------------------------------------- */
/* ------------------------------------------------------------------ */


/**
  * @brief  Start the IO functionality used and enable the AF for selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  AF_en: 0 to disable, else enabled. 
  * @retval None
  */
void mfxstm32l152_IO_Start(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint8_t mode;
  
  /* Get the current register value */
  mode = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL);
  
  /* Set the IO Functionalities to be Enabled */    
  mode |= MFXSTM32L152_GPIO_EN;  
  
  /* Enable ALTERNATE functions */
  /* AGPIO[0..3] can be either IDD or GPIO */ 
  /* AGPIO[4..7] can be either TS or GPIO */ 
  /* if IDD or TS are enabled no matter the value this bit GPIO are not available for those pins */
  /*  however the MFX will waste some cycles to to handle these potential GPIO (pooling, etc) */ 
  /* so if IDD and TS are both active it is better to let ALTERNATE off (0) */
  /* if however IDD or TS are not connected then set it on gives more GPIOs availability */
  /* remind that AGPIO are less efficient then normal GPIO (They use pooling rather then EXTI */
  if (IO_Pin > 0xFFFF)
  {
    mode |= MFXSTM32L152_ALTERNATE_GPIO_EN;  
  }
  else
  {
    mode &= ~MFXSTM32L152_ALTERNATE_GPIO_EN;  
  }  

  /* Write the new register value */  
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL, mode);
  
  /* Wait for 1 ms for MFX to change IRQ_out pin config, before activate it */
  rt_thread_delay(1);
}

/**
  * @brief  Configures the IO pin(s) according to IO mode structure value.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  IO_Pin: The output pin to be set or reset. This parameter can be one 
  *         of the following values:   
  *   @arg  MFXSTM32L152_GPIO_PIN_x: where x can be from 0 to 23.
  * @param  IO_Mode: The IO pin mode to configure, could be one of the following values:
  *   @arg  IO_MODE_INPUT
  *   @arg  IO_MODE_OUTPUT
  *   @arg  IO_MODE_IT_RISING_EDGE
  *   @arg  IO_MODE_IT_FALLING_EDGE
  *   @arg  IO_MODE_IT_LOW_LEVEL
  *   @arg  IO_MODE_IT_HIGH_LEVEL            
  *   @arg  IO_MODE_INPUT_PU,
  *   @arg  IO_MODE_INPUT_PD,
  *   @arg  IO_MODE_OUTPUT_OD_PU,
  *   @arg  IO_MODE_OUTPUT_OD_PD,
  *   @arg  IO_MODE_OUTPUT_PP_PU,
  *   @arg  IO_MODE_OUTPUT_PP_PD,
  *   @arg  IO_MODE_IT_RISING_EDGE_PU
  *   @arg  IO_MODE_IT_FALLING_EDGE_PU
  *   @arg  IO_MODE_IT_LOW_LEVEL_PU
  *   @arg  IO_MODE_IT_HIGH_LEVEL_PU
  *   @arg  IO_MODE_IT_RISING_EDGE_PD
  *   @arg  IO_MODE_IT_FALLING_EDGE_PD
  *   @arg  IO_MODE_IT_LOW_LEVEL_PD
  *   @arg  IO_MODE_IT_HIGH_LEVEL_PD
  * @retval None
  */
uint8_t mfxstm32l152_IO_Config(uint16_t DeviceAddr, uint32_t IO_Pin, IO_ModeTypedef IO_Mode)
{
  uint8_t error_code = 0;

  /* Configure IO pin according to selected IO mode */
  switch(IO_Mode)
  {
  case IO_MODE_OFF: /* Off or analog mode */
  case IO_MODE_ANALOG: /* Off or analog mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITHOUT_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    break;

  case IO_MODE_INPUT: /* Input mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITHOUT_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    break;
    
  case IO_MODE_INPUT_PU: /* Input mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    break;
    
  case IO_MODE_INPUT_PD: /* Input mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    break;

  case IO_MODE_OUTPUT: /* Output mode */
  case IO_MODE_OUTPUT_PP_PD: /* Output mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_OUT);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPO_PUSH_PULL);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    break;

  case IO_MODE_OUTPUT_PP_PU: /* Output mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_OUT);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPO_PUSH_PULL);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    break;

  case IO_MODE_OUTPUT_OD_PD: /* Output mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_OUT);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPO_OPEN_DRAIN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    break;

  case IO_MODE_OUTPUT_OD_PU: /* Output mode */
    mfxstm32l152_IO_DisablePinIT(DeviceAddr, IO_Pin); /* first disable IT */
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_OUT);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPO_OPEN_DRAIN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    break;

  case IO_MODE_IT_RISING_EDGE: /* Interrupt rising edge mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN); 
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITHOUT_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_EDGE);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_HLRE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin); /* last to do: enable IT */
    break;

  case IO_MODE_IT_RISING_EDGE_PU: /* Interrupt rising edge mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_EDGE);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_HLRE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_RISING_EDGE_PD: /* Interrupt rising edge mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_EDGE);      
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_HLRE); 
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_FALLING_EDGE: /* Interrupt falling edge mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITHOUT_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_EDGE);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_LLFE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_FALLING_EDGE_PU: /* Interrupt falling edge mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_EDGE);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_LLFE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_FALLING_EDGE_PD: /* Interrupt falling edge mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN); 
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_EDGE);    
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_LLFE); 
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_LOW_LEVEL: /* Low level interrupt mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN); 
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITHOUT_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_LEVEL);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_LLFE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_LOW_LEVEL_PU: /* Low level interrupt mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_LEVEL);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_LLFE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_LOW_LEVEL_PD: /* Low level interrupt mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_LEVEL);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_LLFE);      
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;
    
  case IO_MODE_IT_HIGH_LEVEL: /* High level interrupt mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN); 
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITHOUT_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_LEVEL);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_HLRE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_HIGH_LEVEL_PU: /* High level interrupt mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_UP);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_LEVEL);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_HLRE);
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;

  case IO_MODE_IT_HIGH_LEVEL_PD: /* High level interrupt mode */
    mfxstm32l152_IO_EnableIT(DeviceAddr);
    mfxstm32l152_IO_InitPin(DeviceAddr, IO_Pin, MFXSTM32L152_GPIO_DIR_IN);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_TYPE1, IO_Pin, MFXSTM32L152_GPI_WITH_PULL_RESISTOR);
    mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_PUPD1, IO_Pin, MFXSTM32L152_GPIO_PULL_DOWN);
    mfxstm32l152_IO_SetIrqEvtMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_EVT_LEVEL);
    mfxstm32l152_IO_SetIrqTypeMode(DeviceAddr, IO_Pin, MFXSTM32L152_IRQ_GPI_TYPE_HLRE);  
    mfxstm32l152_IO_EnablePinIT(DeviceAddr, IO_Pin);  /* last to do: enable IT */
    break;    
  
  default:
    error_code = (uint8_t) IO_Mode;
    break;    
  } 

  return error_code;
}

/**
  * @brief  Initialize the selected IO pin direction.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  IO_Pin: The IO pin to be configured. This parameter could be any 
  *         combination of the following values:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: Where x can be from 0 to 23.   
  * @param  Direction: could be MFXSTM32L152_GPIO_DIR_IN or MFXSTM32L152_GPIO_DIR_OUT.      
  * @retval None
  */
void mfxstm32l152_IO_InitPin(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t Direction)
{
  mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_DIR1, IO_Pin, Direction);
}

/**
  * @brief  Set the global interrupt Type. 
  * @param  DeviceAddr: Device address on communication Bus.      
  * @param  IO_Pin: The IO pin to be configured. This parameter could be any 
  *         combination of the following values:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: Where x can be from 0 to 23.   
  * @param  Evt: Interrupt line activity type, could be one of the following values:
  *   @arg  MFXSTM32L152_IRQ_GPI_EVT_LEVEL: Interrupt line is active in level model         
  *   @arg  MFXSTM32L152_IRQ_GPI_EVT_EDGE: Interrupt line is active in edge model           
  * @retval None
  */
void mfxstm32l152_IO_SetIrqEvtMode(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t Evt)
{
  mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_EVT1, IO_Pin, Evt);
  rt_thread_delay(1);
}

/**
  * @brief  Configure the Edge for which a transition is detectable for the
  *         selected pin.
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  IO_Pin: The IO pin to be configured. This parameter could be any 
  *         combination of the following values:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: Where x can be from 0 to 23.  
  * @param  Evt: Interrupt line activity type, could be one of the following values:
  *   @arg  MFXSTM32L152_IRQ_GPI_TYPE_LLFE: Interrupt line is active in Low Level or Falling Edge         
  *   @arg  MFXSTM32L152_IRQ_GPI_TYPE_HLRE: Interrupt line is active in High Level or Rising Edge           
  * @retval None
  */
void mfxstm32l152_IO_SetIrqTypeMode(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t Type)
{
  mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_TYPE1, IO_Pin, Type);
  rt_thread_delay(1);
}

/**
  * @brief  When GPIO is in output mode, puts the corresponding GPO in High (1) or Low (0) level.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  IO_Pin: The output pin to be set or reset. This parameter can be one 
  *         of the following values:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: where x can be from 0 to 23. 
  * @param PinState: The new IO pin state.
  * @retval None
  */
void mfxstm32l152_IO_WritePin(uint16_t DeviceAddr, uint32_t IO_Pin, uint8_t PinState)
{
  /* Apply the bit value to the selected pin */
  if (PinState != 0)
  {
    /* Set the SET register */
	mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPO_SET1, IO_Pin, 1);
  }
  else
  {
    /* Set the CLEAR register */
	mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_GPO_CLR1, IO_Pin, 1);
  } 
}

/**
  * @brief  Return the state of the selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus.  
  * @param  IO_Pin: The output pin to be set or reset. This parameter can be one 
  *         of the following values:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: where x can be from 0 to 23. 
  * @retval IO pin(s) state.
  */
uint32_t mfxstm32l152_IO_ReadPin(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  uint32_t  tmp1 = 0;
  uint32_t  tmp2 = 0;
  uint32_t  tmp3 = 0;
  
  if(IO_Pin & 0x000000FF)
  {
    tmp1 = (uint32_t) MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_STATE1);
  }
  if(IO_Pin & 0x0000FF00)
  {
    tmp2 = (uint32_t) MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_STATE2);
  }
  if(IO_Pin & 0x00FF0000)
  {
    tmp3 = (uint32_t) MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_GPIO_STATE3);
  }

  tmp3 = tmp1 + (tmp2 << 8) + (tmp3 << 16);
  
  return(tmp3 & IO_Pin);
}

/**
  * @brief  Enable the global IO interrupt source.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void mfxstm32l152_IO_EnableIT(uint16_t DeviceAddr)
{ 
  MFX_IO_ITConfig();
    
  /* Enable global IO IT source */
  mfxstm32l152_EnableITSource(DeviceAddr, MFXSTM32L152_IRQ_GPIO);
}

/**
  * @brief  Disable the global IO interrupt source.
  * @param  DeviceAddr: Device address on communication Bus.   
  * @retval None
  */
void mfxstm32l152_IO_DisableIT(uint16_t DeviceAddr)
{
  /* Disable global IO IT source */
  mfxstm32l152_DisableITSource(DeviceAddr, MFXSTM32L152_IRQ_GPIO);    
}
  
/**
  * @brief  Enable interrupt mode for the selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  IO_Pin: The IO interrupt to be enabled. This parameter could be any 
  *         combination of the following values:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: where x can be from 0 to 23.
  * @retval None
  */
void mfxstm32l152_IO_EnablePinIT(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_SRC1, IO_Pin, 1);
}

/**
  * @brief  Disable interrupt mode for the selected IO pin(s).
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  IO_Pin: The IO interrupt to be disabled. This parameter could be any 
  *         combination of the following values:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: where x can be from 0 to 23.
  * @retval None
  */
void mfxstm32l152_IO_DisablePinIT(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  mfxstm32l152_reg24_setPinValue(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_SRC1, IO_Pin, 0);
}


/**
  * @brief  Check the status of the selected IO interrupt pending bit
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  IO_Pin: The IO interrupt to be checked could be:
  *   @arg  MFXSTM32L152_GPIO_PIN_x Where x can be from 0 to 23.             
  * @retval Status of the checked IO pin(s).
  */
uint32_t mfxstm32l152_IO_ITStatus(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  /* Get the Interrupt status */
  uint8_t   tmp1 = 0;
  uint16_t  tmp2 = 0;
  uint32_t  tmp3 = 0;
  
  if(IO_Pin & 0xFF)
  {
    tmp1 = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_PENDING1);
  }
  if(IO_Pin & 0xFFFF00)
  {
    tmp2 = (uint16_t) MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_PENDING2);
  }
  if(IO_Pin & 0xFFFF0000)
  {
    tmp3 = (uint32_t) MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_PENDING3);
  } 
  
  tmp3 = tmp1 + (tmp2 << 8) + (tmp3 << 16);
  
  return(tmp3 & IO_Pin);
}

/**
  * @brief  Clear the selected IO interrupt pending bit(s). It clear automatically also the general MFXSTM32L152_REG_ADR_IRQ_PENDING
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  IO_Pin: the IO interrupt to be cleared, could be:
  *   @arg  MFXSTM32L152_GPIO_PIN_x: Where x can be from 0 to 23.            
  * @retval None
  */
void mfxstm32l152_IO_ClearIT(uint16_t DeviceAddr, uint32_t IO_Pin)
{
  /* Clear the IO IT pending bit(s) by acknowledging */
  /* it cleans automatically also the Global IRQ_GPIO */
  /* normally this function is called under interrupt */
  uint8_t pin_0_7, pin_8_15, pin_16_23;

  pin_0_7   = IO_Pin & 0x0000ff;
  pin_8_15  = IO_Pin >> 8;
  pin_8_15   = pin_8_15 & 0x00ff;
  pin_16_23 = IO_Pin >> 16;

  if (pin_0_7)
  {
    MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_ACK1, pin_0_7);
  }
  if (pin_8_15)
  {
    MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_ACK2, pin_8_15);
  }
  if (pin_16_23)
  {
    MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_IRQ_GPI_ACK3, pin_16_23);
  }
}


/**
  * @brief  Enable the AF for aGPIO.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void mfxstm32l152_IO_EnableAF(uint16_t DeviceAddr)
{
  uint8_t mode;

  /* Get the current register value */
  mode = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL);
  
  /* Enable ALTERNATE functions */
  /* AGPIO[0..3] can be either IDD or GPIO */ 
  /* AGPIO[4..7] can be either TS or GPIO */ 
  /* if IDD or TS are enabled no matter the value this bit GPIO are not available for those pins */
  /*  however the MFX will waste some cycles to to handle these potential GPIO (pooling, etc) */ 
  /* so if IDD and TS are both active it is better to let ALTERNATE disabled (0) */
  /* if however IDD or TS are not connected then set it on gives more GPIOs availability */
  /* remind that AGPIO are less efficient then normal GPIO (they use pooling rather then EXTI) */
  mode |= MFXSTM32L152_ALTERNATE_GPIO_EN;  
 
  /* Write the new register value */  
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL, mode);
}

/**
  * @brief  Disable the AF for aGPIO.
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
 void mfxstm32l152_IO_DisableAF(uint16_t DeviceAddr)
{
  uint8_t mode;

  /* Get the current register value */
  mode = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL);
  
  /* Enable ALTERNATE functions */
  /* AGPIO[0..3] can be either IDD or GPIO */ 
  /* AGPIO[4..7] can be either TS or GPIO */ 
  /* if IDD or TS are enabled no matter the value this bit GPIO are not available for those pins */
  /*  however the MFX will waste some cycles to to handle these potential GPIO (pooling, etc) */ 
  /* so if IDD and TS are both active it is better to let ALTERNATE disabled (0) */
  /* if however IDD or TS are not connected then set it on gives more GPIOs availability */
  /* remind that AGPIO are less efficient then normal GPIO (they use pooling rather then EXTI) */
  mode &= ~MFXSTM32L152_ALTERNATE_GPIO_EN;  
 
  /* Write the new register value */  
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL, mode);
  
}


/* ------------------------------------------------------------------ */
/* --------------------- TOUCH SCREEN ------------------------------- */
/* ------------------------------------------------------------------ */

/**
  * @brief  Configures the touch Screen Controller (Single point detection)
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None.
  */
void mfxstm32l152_TS_Start(uint16_t DeviceAddr)
{
  uint8_t mode;

  /* Get the current register value */
  mode = MFX_IO_Read(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL);
  
  /* Set the Functionalities to be Enabled */    
  mode |= MFXSTM32L152_TS_EN;  
  
  /* Set the new register value */  
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL, mode);
     
  /* Wait for 2 ms */
  rt_thread_delay(2); 
  
  /* Select 2 nF filter capacitor */
  /* Configuration: 
     - Touch average control    : 4 samples
     - Touch delay time         : 500 uS
     - Panel driver setting time: 500 uS 
  */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_TS_SETTLING, 0x32);
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_TS_TOUCH_DET_DELAY, 0x5);
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_TS_AVE, 0x04);
  
  /* Configure the Touch FIFO threshold: single point reading */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_TS_FIFO_TH, 0x01);
  
  /* Clear the FIFO memory content. */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_TS_FIFO_TH, MFXSTM32L152_TS_CLEAR_FIFO);

  /* Touch screen control configuration :
     - No window tracking index
   */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_TS_TRACK, 0x00);
  
 
  /*  Clear all the IT status pending bits if any */
  mfxstm32l152_IO_ClearIT(DeviceAddr, 0xFFFFFF);

  /* Wait for 1 ms delay */
  rt_thread_delay(1);
}

/**
  * @brief  Return if there is touch detected or not.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Touch detected state.
  */
uint8_t mfxstm32l152_TS_DetectTouch(uint16_t DeviceAddr)
{
  uint8_t state;
  uint8_t ret = 0;
 
  state = MFX_IO_Read(DeviceAddr, MFXSTM32L152_TS_FIFO_STA);
  state = ((state & (uint8_t)MFXSTM32L152_TS_CTRL_STATUS) == (uint8_t)MFXSTM32L152_TS_CTRL_STATUS);
  
  if(state > 0)
  {
    if(MFX_IO_Read(DeviceAddr, MFXSTM32L152_TS_FIFO_LEVEL) > 0)
    {
      ret = 1;
    }
  }
  
  return ret;
}

/**
  * @brief  Get the touch screen X and Y positions values
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  X: Pointer to X position value
  * @param  Y: Pointer to Y position value   
  * @retval None.
  */
void mfxstm32l152_TS_GetXY(uint16_t DeviceAddr, uint16_t *X, uint16_t *Y)
{
  uint8_t  data_xy[3];

  MFX_IO_ReadMultiple(DeviceAddr, MFXSTM32L152_TS_XY_DATA, data_xy, sizeof(data_xy)) ;
  
  /* Calculate positions values */
  *X = (data_xy[1]<<4) + (data_xy[0]>>4); 
  *Y = (data_xy[2]<<4) + (data_xy[0]&4); 

  /* Reset the FIFO memory content. */
  MFX_IO_Write(DeviceAddr, MFXSTM32L152_TS_FIFO_TH, MFXSTM32L152_TS_CLEAR_FIFO);
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void mfxstm32l152_TS_EnableIT(uint16_t DeviceAddr)
{
  MFX_IO_ITConfig();
  
  /* Enable global TS IT source */
  mfxstm32l152_EnableITSource(DeviceAddr, MFXSTM32L152_IRQ_TS_DET);
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval None
  */
void mfxstm32l152_TS_DisableIT(uint16_t DeviceAddr)
{
  /* Disable global TS IT source */
  mfxstm32l152_DisableITSource(DeviceAddr, MFXSTM32L152_IRQ_TS_DET);    
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.    
  * @retval TS interrupts status
  */
uint8_t mfxstm32l152_TS_ITStatus(uint16_t DeviceAddr)
{
  /* Return TS interrupts status */
  return(mfxstm32l152_GlobalITStatus(DeviceAddr, MFXSTM32L152_IRQ_TS));
}

/**
  * @brief  Configure the selected source to generate a global interrupt or not
  * @param  DeviceAddr: Device address on communication Bus.  
  * @retval None
  */
void mfxstm32l152_TS_ClearIT(uint16_t DeviceAddr)
{
  /* Clear the global TS IT source */
  mfxstm32l152_ClearGlobalIT(DeviceAddr, MFXSTM32L152_IRQ_TS);
}

/* ------------------------------------------------------------------ */
/* --------------------- IDD MEASUREMENT ---------------------------- */
/* ------------------------------------------------------------------ */

/**
  * @brief  Launch IDD current measurement
  * @param  DeviceAddr: Device address on communication Bus
  * @retval None.
  */
void mfxstm32l152_IDD_Start(uint16_t DeviceAddr)
{
  uint8_t mode = 0;

  /* Get the current register value */
  mode = MFX_IO_Read((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_CTRL);

  /* Set the Functionalities to be enabled */
  mode |= MFXSTM32L152_IDD_CTRL_REQ;

  /* Start measurement campaign */
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_CTRL, mode);
}

/**
  * @brief  Configures the IDD current measurement
  * @param  DeviceAddr: Device address on communication Bus.
  * @param  MfxIddConfig: Parameters depending on hardware config.
  * @retval None
  */
void mfxstm32l152_IDD_Config(uint16_t DeviceAddr, IDD_ConfigTypeDef MfxIddConfig)
{
  uint8_t value = 0;
  uint8_t mode = 0;

  /* Get the current register value */
  mode = MFX_IO_Read((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL);

  if((mode & MFXSTM32L152_IDD_EN) != MFXSTM32L152_IDD_EN)
  {
    /* Set the Functionalities to be enabled */
    mode |= MFXSTM32L152_IDD_EN;

    /* Set the new register value */
    MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_SYS_CTRL, mode);
  }

  /* Control register setting: number of shunts */
  value =  ((MfxIddConfig.ShuntNbUsed << 1) & MFXSTM32L152_IDD_CTRL_SHUNT_NB);
  value |= (MfxIddConfig.VrefMeasurement & MFXSTM32L152_IDD_CTRL_VREF_DIS);
  value |= (MfxIddConfig.Calibration & MFXSTM32L152_IDD_CTRL_CAL_DIS);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_CTRL, value);

  /* Idd pre delay configuration: unit and value*/
  value = (MfxIddConfig.PreDelayUnit & MFXSTM32L152_IDD_PREDELAY_UNIT) |
          (MfxIddConfig.PreDelayValue & MFXSTM32L152_IDD_PREDELAY_VALUE);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_PRE_DELAY, value);

  /* Shunt 0 register value: MSB then LSB */
  value = (uint8_t) (MfxIddConfig.Shunt0Value >> 8);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT0_MSB, value);
  value = (uint8_t) (MfxIddConfig.Shunt0Value);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT0_LSB, value);

  /* Shunt 1 register value: MSB then LSB */
  value = (uint8_t) (MfxIddConfig.Shunt1Value >> 8);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT1_MSB, value);
  value = (uint8_t) (MfxIddConfig.Shunt1Value);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT1_LSB, value);

  /* Shunt 2 register value: MSB then LSB */
  value = (uint8_t) (MfxIddConfig.Shunt2Value >> 8);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT2_MSB, value);
  value = (uint8_t) (MfxIddConfig.Shunt2Value);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT2_LSB, value);

  /* Shunt 3 register value: MSB then LSB */
  value = (uint8_t) (MfxIddConfig.Shunt3Value >> 8);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT3_MSB, value);
  value = (uint8_t) (MfxIddConfig.Shunt3Value);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT3_LSB, value);

  /* Shunt 4 register value: MSB then LSB */
  value = (uint8_t) (MfxIddConfig.Shunt4Value >> 8);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT4_MSB, value);
  value = (uint8_t) (MfxIddConfig.Shunt4Value);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT4_LSB, value);

  /* Shunt 0 stabilization delay */
  value = MfxIddConfig.Shunt0StabDelay;
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SH0_STABILIZATION, value);

  /* Shunt 1 stabilization delay */
  value = MfxIddConfig.Shunt1StabDelay;
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SH1_STABILIZATION, value);

  /* Shunt 2 stabilization delay */
  value = MfxIddConfig.Shunt2StabDelay;
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SH2_STABILIZATION, value);

  /* Shunt 3 stabilization delay */
  value = MfxIddConfig.Shunt3StabDelay;
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SH3_STABILIZATION, value);

  /* Shunt 4 stabilization delay */
  value = MfxIddConfig.Shunt4StabDelay;
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SH4_STABILIZATION, value);

  /* Idd ampli gain value: MSB then LSB */
  value = (uint8_t) (MfxIddConfig.AmpliGain >> 8);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_GAIN_MSB, value);
  value = (uint8_t) (MfxIddConfig.AmpliGain);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_GAIN_LSB, value);

  /* Idd VDD min value: MSB then LSB */
  value = (uint8_t) (MfxIddConfig.VddMin >> 8);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_VDD_MIN_MSB, value);
  value = (uint8_t) (MfxIddConfig.VddMin);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_VDD_MIN_LSB, value);

  /* Idd number of measurements */
  value = MfxIddConfig.MeasureNb;
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_NBR_OF_MEAS, value);

  /* Idd delta delay configuration: unit and value */
  value = (MfxIddConfig.DeltaDelayUnit & MFXSTM32L152_IDD_DELTADELAY_UNIT) |
          (MfxIddConfig.DeltaDelayValue & MFXSTM32L152_IDD_DELTADELAY_VALUE);
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_MEAS_DELTA_DELAY, value);

  /* Idd number of shut on board */
  value = MfxIddConfig.ShuntNbOnBoard;
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNTS_ON_BOARD, value);
}

/**
  * @brief  This function allows to modify number of shunt used for a measurement
  * @param  DeviceAddr: Device address on communication Bus
  * @retval None.
  */
void mfxstm32l152_IDD_ConfigShuntNbLimit(uint16_t DeviceAddr, uint8_t ShuntNbLimit)
{
  uint8_t mode = 0;

  /* Get the current register value */
  mode = MFX_IO_Read((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_CTRL);

  /* Clear number of shunt limit */
  mode &= ~(MFXSTM32L152_IDD_CTRL_SHUNT_NB);

  /* Clear number of shunt limit */
  mode |= ((ShuntNbLimit << 1) & MFXSTM32L152_IDD_CTRL_SHUNT_NB);

  /* Write noewx desired limit */
  MFX_IO_Write((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_CTRL, mode);
}

/**
  * @brief  Get Idd current value
  * @param  DeviceAddr: Device address on communication Bus
  * @param  ReadValue: Pointer on value to be read
  * @retval Idd value in 10 nA.
  */
void mfxstm32l152_IDD_GetValue(uint16_t DeviceAddr, uint32_t *ReadValue)
{
  uint8_t  data[3];

  MFX_IO_ReadMultiple((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_VALUE_MSB, data, sizeof(data)) ;

  /* Recompose Idd current value */
  *ReadValue = (data[0] << 16) | (data[1] << 8) | data[2];

}

/**
  * @brief  Get Last shunt used for measurement
  * @param  DeviceAddr: Device address on communication Bus
  * @retval Last shunt used 
  */
uint8_t  mfxstm32l152_IDD_GetShuntUsed(uint16_t DeviceAddr)
{
  return(MFX_IO_Read((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_IDD_SHUNT_USED));
}

/**
  * @brief  Configure mfx to enable Idd interrupt
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void mfxstm32l152_IDD_EnableIT(uint16_t DeviceAddr)
{
  MFX_IO_ITConfig();

  /* Enable global IDD interrupt source */
  mfxstm32l152_EnableITSource(DeviceAddr, MFXSTM32L152_IRQ_IDD);
}

/**
  * @brief  Clear Idd global interrupt
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void mfxstm32l152_IDD_ClearIT(uint16_t DeviceAddr)
{
  /* Clear the global IDD interrupt source */
  mfxstm32l152_ClearGlobalIT(DeviceAddr, MFXSTM32L152_IRQ_IDD);
}

/**
  * @brief  get Idd interrupt status
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval IDD interrupts status
  */
uint8_t mfxstm32l152_IDD_GetITStatus(uint16_t DeviceAddr)
{
  /* Return IDD interrupt status */
  return(mfxstm32l152_GlobalITStatus(DeviceAddr, MFXSTM32L152_IRQ_IDD));
}

/**
  * @brief  disable Idd interrupt
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None.
  */
void mfxstm32l152_IDD_DisableIT(uint16_t DeviceAddr)
{
  /* Disable global IDD interrupt source */
  mfxstm32l152_DisableITSource(DeviceAddr, MFXSTM32L152_IRQ_IDD);
}


/* ------------------------------------------------------------------ */
/* --------------------- ERROR MANAGEMENT --------------------------- */
/* ------------------------------------------------------------------ */

/**
  * @brief  Read Error Source.
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Error message code with error source
  */
uint8_t mfxstm32l152_Error_ReadSrc(uint16_t DeviceAddr)
{
  /* Get the current source register value */
  return(MFX_IO_Read((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_ERROR_SRC));
}

/**
  * @brief  Read Error Message
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Error message code with error source
  */
uint8_t mfxstm32l152_Error_ReadMsg(uint16_t DeviceAddr)
{
  /* Get the current message register value */
  return(MFX_IO_Read((uint8_t) DeviceAddr, MFXSTM32L152_REG_ADR_ERROR_MSG));
}

/**
  * @brief  Enable Error global interrupt
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */

void mfxstm32l152_Error_EnableIT(uint16_t DeviceAddr)
{
  MFX_IO_ITConfig();

  /* Enable global Error interrupt source */
  mfxstm32l152_EnableITSource(DeviceAddr, MFXSTM32L152_IRQ_ERROR);
}

/**
  * @brief  Clear Error global interrupt
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None
  */
void mfxstm32l152_Error_ClearIT(uint16_t DeviceAddr)
{
  /* Clear the global Error interrupt source */
  mfxstm32l152_ClearGlobalIT(DeviceAddr, MFXSTM32L152_IRQ_ERROR);
}

/**
  * @brief  get Error interrupt status
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Error interrupts status
  */
uint8_t mfxstm32l152_Error_GetITStatus(uint16_t DeviceAddr)
{
  /* Return Error interrupt status */
  return(mfxstm32l152_GlobalITStatus(DeviceAddr, MFXSTM32L152_IRQ_ERROR));
}

/**
  * @brief  disable Error interrupt
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval None.
  */
void mfxstm32l152_Error_DisableIT(uint16_t DeviceAddr)
{
  /* Disable global Error interrupt source */
  mfxstm32l152_DisableITSource(DeviceAddr, MFXSTM32L152_IRQ_ERROR);
}

/**
  * @brief  FOR DEBUG ONLY
  */
uint8_t mfxstm32l152_ReadReg(uint16_t DeviceAddr, uint8_t RegAddr)
{
  /* Get the current register value */ 
  return(MFX_IO_Read((uint8_t) DeviceAddr, RegAddr));
}

void mfxstm32l152_WriteReg(uint16_t DeviceAddr, uint8_t RegAddr, uint8_t Value)
{
  /* set the current register value */ 
  MFX_IO_Write((uint8_t) DeviceAddr, RegAddr, Value);
}

/* ------------------------------------------------------------------ */
/* ----------------------- Private functions ------------------------ */
/* ------------------------------------------------------------------ */
/**
  * @brief  Check if the device instance of the selected address is already registered
  *         and return its index  
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Index of the device instance if registered, 0xFF if not.
  */
static uint8_t mfxstm32l152_GetInstance(uint16_t DeviceAddr)
{
  uint8_t idx = 0;
  
  /* Check all the registered instances */
  for(idx = 0; idx < MFXSTM32L152_MAX_INSTANCE ; idx ++)
  {
    if(mfxstm32l152[idx] == DeviceAddr)
    {
      return idx; 
    }
  }
  
  return 0xFF;
}

/**
  * @brief  Release registered device instance
  * @param  DeviceAddr: Device address on communication Bus.
  * @retval Index of released device instance, 0xFF if not.
  */
static uint8_t mfxstm32l152_ReleaseInstance(uint16_t DeviceAddr)
{
  uint8_t idx = 0;
  
  /* Check for all the registered instances */
  for(idx = 0; idx < MFXSTM32L152_MAX_INSTANCE ; idx ++)
  {
    if(mfxstm32l152[idx] == DeviceAddr)
    {
      mfxstm32l152[idx] = 0;
      return idx;
    }
  }
  return 0xFF;
}

/**
  * @brief  Internal routine
  * @param  DeviceAddr: Device address on communication Bus. 
  * @param  RegisterAddr: Register Address
  * @param  PinPosition: Pin [0:23]
  * @param  PinValue: 0/1
  * @retval None
  */
void mfxstm32l152_reg24_setPinValue(uint16_t DeviceAddr, uint8_t RegisterAddr, uint32_t PinPosition, uint8_t PinValue )
{
  uint8_t tmp = 0;
  uint8_t pin_0_7, pin_8_15, pin_16_23;

  pin_0_7   = PinPosition & 0x0000ff;
  pin_8_15  = PinPosition >> 8;
  pin_8_15   = pin_8_15 & 0x00ff;
  pin_16_23 = PinPosition >> 16;
  
  if (pin_0_7)
  {  
    /* Get the current register value */ 
    tmp = MFX_IO_Read(DeviceAddr, RegisterAddr);
  
    /* Set the selected pin direction */
    if (PinValue != 0)
    {
      tmp |= (uint8_t)pin_0_7;
    }  
    else 
    {
      tmp &= ~(uint8_t)pin_0_7;
    }
  
    /* Set the new register value */
    MFX_IO_Write(DeviceAddr, RegisterAddr, tmp);
  }

  if (pin_8_15)
  {
    /* Get the current register value */ 
    tmp = MFX_IO_Read(DeviceAddr, RegisterAddr+1);
  
    /* Set the selected pin direction */
    if (PinValue != 0)
    {
      tmp |= (uint8_t)pin_8_15;
    }  
    else 
    {
      tmp &= ~(uint8_t)pin_8_15;
    }
  
    /* Set the new register value */
    MFX_IO_Write(DeviceAddr, RegisterAddr+1, tmp);
  }  

  if (pin_16_23)
  {
    /* Get the current register value */ 
    tmp = MFX_IO_Read(DeviceAddr, RegisterAddr+2);
  
    /* Set the selected pin direction */
    if (PinValue != 0)
    {
      tmp |= (uint8_t)pin_16_23;
    }  
    else 
    {
      tmp &= ~(uint8_t)pin_16_23;
    }
  
    /* Set the new register value */
    MFX_IO_Write(DeviceAddr, RegisterAddr+2, tmp);
  } 
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
