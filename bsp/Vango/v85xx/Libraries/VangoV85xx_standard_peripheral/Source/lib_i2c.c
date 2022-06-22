/**
  ******************************************************************************
  * @file    lib_i2c.c 
  * @author  Application Team
  * @version V4.5.0
  * @date    2019-05-14
  * @brief   IIC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_i2c.h"

//registers default reset values
#define I2C_ADDR_RSTValue       0
#define I2C_CTRL_RSTValue       0
#define I2C_CTRL2_RSTValue      0

/* Private Functions -------------------------------------------------------- */
static uint16_t I2C_CheckState(uint8_t State);
static void I2C_SendStart(void);
static void I2C_SendRestart(void);
static void I2C_SendByte(uint8_t dat);
static void I2C_SendStop(void);
static uint8_t I2C_ReceiveByte(void);
static void I2C_ClearBus(uint32_t remap);
static void I2C_WaitForCrossPage(uint8_t sla);

/**
  * @brief  Check required state.
  * @param  State: 
                Required state.
  * @retval 0: state OK
            !0: state Error, [15:8]Required status code, [7:0] real status code.
  */
static uint16_t I2C_CheckState(uint8_t State)
{
  uint16_t ret;
  if (I2C_GetStatusCode() != State)
  {
    ret = (State<<8)|(I2C_GetStatusCode());
    return ret;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Send start signal.
  * @param  None
  * @retval None
  */
static void I2C_SendStart(void)
{
  I2C_GenerateSTART(ENABLE);
  while (I2C_GetINTStatus() == 0);
  I2C_GenerateSTART(DISABLE);
}

/**
  * @brief  Send restart signal.
  * @param  None
  * @retval None
  */
static void I2C_SendRestart(void)
{
  I2C_GenerateSTART(ENABLE);
  I2C_ClearINTStatus();
  while (I2C_GetINTStatus() == 0);
  I2C_GenerateSTART(DISABLE);
}

/**
  * @brief  Send stop signal.
  * @param  None
  * @retval None
  */
static void I2C_SendStop(void)
{
  I2C_GenerateSTOP(ENABLE);
  I2C_ClearINTStatus();
  I2C_GenerateSTOP(DISABLE);
}

/**
  * @brief  Send data.
  * @param  dat:data to send.
  * @retval None
  */
static void I2C_SendByte(uint8_t dat)
{
  I2C_SendData(dat);
  I2C_ClearINTStatus();
  while (I2C_GetINTStatus() == 0);
}

/**
  * @brief  Receive byte.
  * @param  None
  * @retval Byte received
  */
static uint8_t I2C_ReceiveByte(void)
{
  I2C_ClearINTStatus();
  while (I2C_GetINTStatus() == 0);
  return I2C_ReceiveData();
}

/**
  * @brief  Wait for cross page operation done.
  * @param  None
  * @retval None
  */
static void I2C_WaitForCrossPage(uint8_t sla)
{
  do
  {
    I2C_SendRestart();
    I2C_SendByte(sla);  //device address
  }while (I2C_GetStatusCode() !=0x18);
  I2C_SendStop();                 //stop
}

static void I2C_ClearBus(uint32_t remap)
{
  __IO uint8_t i, j;
  
  if (remap) // I2C remap enable, SCL IOC4
  {
    GPIOC->DAT &= ~BIT4;
    GPIOC->ATT |= BIT4;
    GPIOC->OEN &= ~BIT4;
    for (i=0; i<9; i++)
    {
      GPIOC->DAT |= BIT4;
      for (j=0; j<100; j++)
        __NOP();
      GPIOC->DAT &= ~BIT4;
      for (j=0; j<100; j++)
        __NOP();
    }
    GPIOC->DAT |= BIT4;
    GPIOC->OEN |= BIT4;
    GPIOC->IE &= ~BIT4;
  }
  else       // I2C remap disable, SCL IOB13
  {
    GPIOB->DAT &= ~BIT13;
    GPIOB->ATT |= BIT13;
    GPIOB->OEN &= ~BIT13;
    for (i=0; i<9; i++)
    {
      GPIOB->DAT |= BIT13;
      for (j=0; j<100; j++)
        __NOP();
      GPIOB->DAT &= ~BIT13;
      for (j=0; j<100; j++)
        __NOP();
    }
    GPIOB->DAT |= BIT13;
    GPIOB->OEN |= BIT13;
    GPIOB->IE &= ~BIT13;  
  }
}

/* Exported Functions ------------------------------------------------------- */

/**
  * @brief  Initializes the I2C peripheral registers to their default reset values.
  * @param  remap: I2C_REMAP_ENABLE or I2C_REMAP_DISABLE       
  * @retval None
  */
void I2C_DeInit(uint32_t remap)
{
  I2C->CTRL &= ~I2C_CTRL_EN;
    
  I2C->ADDR = I2C_ADDR_RSTValue;
  I2C->CTRL = I2C_CTRL_RSTValue;
  I2C->CTRL2 = I2C_CTRL2_RSTValue;
  
  I2C_ClearBus(remap);
}

/**
  * @brief  Fills each InitStruct member with its default value.
  * @param  InitStruct: pointer to an I2C_InitType structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitType *InitStruct)
{
  /*--------------- Reset I2C init structure parameters values ---------------*/
  /* Initialize the AssertAcknowledge member */  
  InitStruct->AssertAcknowledge = I2C_ASSERTACKNOWLEDGE_DISABLE;
  /* Initialize the ClockSource member */  
  InitStruct->ClockSource = I2C_CLOCKSOURCE_APBD256; 
  /* Initialize the GeneralCallAck member */  
  InitStruct->GeneralCallAck = I2C_GENERALCALLACK_DISABLE;
  /* Initialize the SlaveAddr member */  
  InitStruct->SlaveAddr = 0;  
}

/**
  * @brief  I2C initialization.
  * @param  InitStruct: I2C configuration.
                SlaveAddr: Own I2C slave address (7 bit)
                GeneralCallAck:
                    I2C_GENERALCALLACK_ENABLE
                    I2C_GENERALCALLACK_DISABLE
                AssertAcknowledge:
                    I2C_ASSERTACKNOWLEDGE_ENABLE
                    I2C_ASSERTACKNOWLEDGE_DISABLE
                ClockSource:
                    I2C_CLOCKSOURCE_APBD256
                    I2C_CLOCKSOURCE_APBD224
                    I2C_CLOCKSOURCE_APBD192
                    I2C_CLOCKSOURCE_APBD160
                    I2C_CLOCKSOURCE_APBD960
                    I2C_CLOCKSOURCE_APBD120
                    I2C_CLOCKSOURCE_APBD60
                    I2C_CLOCKSOURCE_TIM3OFD8
  * @retval None.
  */
void I2C_Init(I2C_InitType *InitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_I2C_GC(InitStruct->GeneralCallAck));
  assert_parameters(IS_I2C_AA(InitStruct->AssertAcknowledge));
  assert_parameters(IS_I2C_CLKSRC(InitStruct->ClockSource));
  
  I2C->ADDR = InitStruct->SlaveAddr\
             |InitStruct->GeneralCallAck;
  tmp = I2C->CTRL;
  tmp &= ~(I2C_CTRL_CR\
          |I2C_CTRL_AA);
  tmp |= (InitStruct->ClockSource\
         |InitStruct->AssertAcknowledge);
  I2C->CTRL = tmp;
}
           
/**
  * @brief  Interrupt configure.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void I2C_INTConfig(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    I2C->CTRL2 |= I2C_CTRL2_INTEN;
  else
    I2C->CTRL2 &= ~I2C_CTRL2_INTEN;
}

/**
  * @brief  Get interrupt status.
  * @param  None
  * @retval Interrupt status.
  */
uint8_t I2C_GetINTStatus(void)
{
  if (I2C->CTRL&I2C_CTRL_SI)
    return 1;
  else
    return 0;
}
           
/**
  * @brief  Clear interrupt status.
  * @param  None
  * @retval None.
  */
void I2C_ClearINTStatus(void)
{
  I2C->CTRL &= ~I2C_CTRL_SI;
}

/**
  * @brief  Read a packge of data from slave device.
  * @param  InitStruct: I2C_WRType
                SlaveAddr  : Slave device address
                SubAddress : start of slave device sub-address
                PageRange  : maximum range of page to Read operation
                pBuffer    : Read data pointer
                Length     : sum of Read datas
                SubAddrType:
                    I2C_SUBADDR_1BYTE   (Slave device sub-address type: 1 byte)
                    I2C_SUBADDR_2BYTE   (Slave device sub-address type: 2 bytes)
                    I2C_SUBADDR_OTHER   (Slave device sub-address type: othres)
  * @retval 0: true
            £¡0£ºstatus code
                bit15~8    status code(true)
                bit7~0     status code(false)
  */
uint16_t I2C_MasterReadBytes(I2C_WRType *InitStruct)
{
  uint32_t i;
  uint16_t ret_val;
  
  /* Check parameters */ 
  assert_parameters(I2C_SUBADDR_TYPE(InitStruct->SubAddrType));
    
  I2C_AssertAcknowledgeConfig(ENABLE); //Enable AA 
  /*-------------------------------- START -----------------------------------*/
  I2C_SendStart();
  ret_val = I2C_CheckState(0x08);
  if (ret_val)    return ret_val;

  /*------------------------------ Send SLA+W --------------------------------*/
  /* Slave device sub-address type: 1 byte */
  if (InitStruct->SubAddrType == I2C_SUBADDR_1BYTE)
  {
    I2C_SendByte(InitStruct->SlaveAddr);
    ret_val = I2C_CheckState(0x18);
    if (ret_val)    return ret_val;
        
    I2C_SendByte(InitStruct->SubAddress&0xFF);
    ret_val = I2C_CheckState(0x28);
    if (ret_val)    return ret_val;
  }
  /* Slave device sub-address type: 2 bytes */
  if (InitStruct->SubAddrType == I2C_SUBADDR_2BYTE)
  {
    I2C_SendByte(InitStruct->SlaveAddr);
    ret_val = I2C_CheckState(0x18);
    if (ret_val)    return ret_val;
        
    I2C_SendByte((InitStruct->SubAddress>>8)&0xFF);
    ret_val = I2C_CheckState(0x28);
    if (ret_val)    return ret_val;
        
    I2C_SendByte(InitStruct->SubAddress&0xFF);
    ret_val = I2C_CheckState(0x28);
    if (ret_val)    return ret_val;
  }
  /* Slave device sub-address type: othres */
  if (InitStruct->SubAddrType == I2C_SUBADDR_OTHER)
  {
    if (InitStruct->PageRange < 256) // 8 + x
    {
      I2C_SendByte(InitStruct->SlaveAddr|((InitStruct->SubAddress>>7)&0xE));
      ret_val = I2C_CheckState(0x18);
      if (ret_val)    return ret_val;
            
      I2C_SendByte(InitStruct->SubAddress&0xFF);
      ret_val = I2C_CheckState(0x28); 
      if (ret_val)    return ret_val;
    }
    else                             // 16 + x
    {
      I2C_SendByte(InitStruct->SlaveAddr|((InitStruct->SubAddress>>15)&0xE));
      ret_val = I2C_CheckState(0x18);
      if (ret_val)    return ret_val;
    
      I2C_SendByte((InitStruct->SubAddress>>8)&0xFF);
      ret_val = I2C_CheckState(0x28); 
      if (ret_val)    return ret_val;
    
      I2C_SendByte(InitStruct->SubAddress&0xFF);
      ret_val = I2C_CheckState(0x28); 
      if (ret_val)    return ret_val;    
    }
  }
    
  /*------------------------------- Restart ----------------------------------*/
  I2C_SendRestart();  //restart
  ret_val = I2C_CheckState(0x10);
  if (ret_val)    return ret_val;
   
  /*----------------------------- Send SLA+R ---------------------------------*/
    /* Slave device sub-address type: othres */
  if (InitStruct->SubAddrType == I2C_SUBADDR_OTHER)
  {
    if (InitStruct->PageRange < 256) // 8 + x
      I2C_SendByte(InitStruct->SlaveAddr|0x01|((InitStruct->SubAddress>>7)&0xE));
    else // 16 + x
      I2C_SendByte(InitStruct->SlaveAddr|0x01|((InitStruct->SubAddress>>15)&0xE));
  }
  else
    I2C_SendByte(InitStruct->SlaveAddr|0x01);
  
  ret_val = I2C_CheckState(0x40);
  if (ret_val)    return ret_val;
   
  /*----------------------------- Read datas ---------------------------------*/
  for (i=0; i<(InitStruct->Length-1); i++)
  {
    *InitStruct->pBuffer = I2C_ReceiveByte();
    InitStruct->pBuffer++;
    ret_val = I2C_CheckState(0x50);
    if (ret_val)    return ret_val;
  }
  /*-------------------- Read the last data, disable AA ----------------------*/  
  I2C_AssertAcknowledgeConfig(DISABLE);
  *InitStruct->pBuffer = I2C_ReceiveByte();
  ret_val = I2C_CheckState(0x58);
  if (ret_val)    return ret_val;
  /*--------------------------------- Stop -----------------------------------*/  
  I2C_SendStop();  //stop
  return 0;
}

/**
  * @brief  Write a packge of data to slave device.
  * @param  InitStruct: I2C_WRType
                SlaveAddr  : Slave device address
                SubAddress : start of slave device sub-address
                PageRange  : maximum range of page to write operation
                pBuffer    : write data pointer
                Length     : sum of write datas
                SubAddrType:
                    I2C_SUBADDR_1BYTE   (Slave device sub-address type: 1 byte)
                    I2C_SUBADDR_2BYTE   (Slave device sub-address type: 2 bytes)
                    I2C_SUBADDR_OTHER   (Slave device sub-address type: othres)
  * @retval 0: true
            £¡0£ºstatus code
                bit15~8    status code(true)
                bit7~0     status code(false)
  */
uint16_t I2C_MasterWriteBytes(I2C_WRType *InitStruct)
{
  uint16_t ret_val;
  uint32_t i;
  
  /* Check parameters */ 
  assert_parameters(I2C_SUBADDR_TYPE(InitStruct->SubAddrType));  
  
  I2C_AssertAcknowledgeConfig(ENABLE); //Enable AA 
  /*-------------------------------- START -----------------------------------*/
  I2C_SendStart();
  ret_val = I2C_CheckState(0x08);
  if (ret_val)    return ret_val;
    
  /*------------------------------ Send SLA+W --------------------------------*/
  /* Slave device sub-address type: 1 byte */
  if (InitStruct->SubAddrType == I2C_SUBADDR_1BYTE)
  {
    I2C_SendByte(InitStruct->SlaveAddr);
    ret_val = I2C_CheckState(0x18);
    if (ret_val)    return ret_val;
        
    I2C_SendByte(InitStruct->SubAddress&0xFF);
    ret_val = I2C_CheckState(0x28);
    if (ret_val)    return ret_val;
  }
  /* Slave device sub-address type: 2 bytes */
  else if (InitStruct->SubAddrType == I2C_SUBADDR_2BYTE)
  {
    I2C_SendByte(InitStruct->SlaveAddr);      //device address
    ret_val = I2C_CheckState(0x18);
    if (ret_val)    return ret_val;
        
    I2C_SendByte((InitStruct->SubAddress>>8)&0xFF);   //first word address
    ret_val = I2C_CheckState(0x28);
    if (ret_val)    return ret_val;
        
    I2C_SendByte(InitStruct->SubAddress&0xFF);        //second word address
    ret_val = I2C_CheckState(0x28);
    if (ret_val)    return ret_val;       
  }
  /* Slave device sub-address type: othres */
  else
  {
    if (InitStruct->PageRange < 256) // 8 + x
    {
      I2C_SendByte(InitStruct->SlaveAddr|((InitStruct->SubAddress>>7)&0xE));
      ret_val = I2C_CheckState(0x18);
      if (ret_val)    return ret_val;
            
      I2C_SendByte(InitStruct->SubAddress&0xFF);
      ret_val = I2C_CheckState(0x28); 
      if (ret_val)    return ret_val;
    }
    else                             // 16 + x
    {
      I2C_SendByte(InitStruct->SlaveAddr|((InitStruct->SubAddress>>15)&0xE));
      ret_val = I2C_CheckState(0x18);
      if (ret_val)    return ret_val;
    
      I2C_SendByte((InitStruct->SubAddress>>8)&0xFF);
      ret_val = I2C_CheckState(0x28); 
      if (ret_val)    return ret_val;
    
      I2C_SendByte(InitStruct->SubAddress&0xFF);
      ret_val = I2C_CheckState(0x28); 
      if (ret_val)    return ret_val;    
    }      
  }
    
  /*----------------------------- Write datas --------------------------------*/    
  for (i=0; i<(InitStruct->Length); i++)
  {
    /* Reach the page boundary */
    if ((i > 0) && ((InitStruct->SubAddress+i)%InitStruct->PageRange == 0))
    {   
      I2C_SendStop();
      I2C_WaitForCrossPage(InitStruct->SlaveAddr);
      I2C_SendStart();                //start
      ret_val = I2C_CheckState(0x08);
      if (ret_val)    return ret_val;
      /* WriteAddr: 1 byte */
      if (InitStruct->SubAddrType == I2C_SUBADDR_1BYTE)
      {
        I2C_SendByte(InitStruct->SlaveAddr);
        ret_val = I2C_CheckState(0x18);
        if (ret_val)    return ret_val;
                
        I2C_SendByte((InitStruct->SubAddress+i)&0xFF);
        ret_val = I2C_CheckState(0x28);
        if (ret_val)    return ret_val;
      }
      /* WriteAddr: 2 byte */
      if (InitStruct->SubAddrType == I2C_SUBADDR_2BYTE)
      {
        I2C_SendByte(InitStruct->SlaveAddr);      //device address
        ret_val = I2C_CheckState(0x18);
        if (ret_val)    return ret_val;
                
        I2C_SendByte(((InitStruct->SubAddress+i)>>8)&0xFF);   //first word address
        ret_val = I2C_CheckState(0x28);
        if (ret_val)    return ret_val;
                
        I2C_SendByte((InitStruct->SubAddress+i)&0xFF);        //second word address
        ret_val = I2C_CheckState(0x28);
        if (ret_val)    return ret_val;      
      }
      /* WriteAddr: (16 or 8)+x*/
      if (InitStruct->SubAddrType == I2C_SUBADDR_OTHER)
      {
        if (InitStruct->PageRange < 256) // 8 + x
        {
          I2C_SendByte(InitStruct->SlaveAddr|(((InitStruct->SubAddress+i)>>7)&0xE));
          ret_val = I2C_CheckState(0x18);
          if (ret_val)    return ret_val;
            
          I2C_SendByte((InitStruct->SubAddress+i)&0xFF);
          ret_val = I2C_CheckState(0x28); 
          if (ret_val)    return ret_val;
        }
        else                             // 16 + x
        {
          I2C_SendByte(InitStruct->SlaveAddr|(((InitStruct->SubAddress+i)>>15)&0xE));
          ret_val = I2C_CheckState(0x18);
          if (ret_val)    return ret_val;
    
          I2C_SendByte(((InitStruct->SubAddress+i)>>8)&0xFF);
          ret_val = I2C_CheckState(0x28); 
          if (ret_val)    return ret_val;
    
          I2C_SendByte((InitStruct->SubAddress+i)&0xFF);
          ret_val = I2C_CheckState(0x28); 
          if (ret_val)    return ret_val;    
        }     
      }
            
      I2C_SendByte(*InitStruct->pBuffer);
      InitStruct->pBuffer++;
      ret_val = I2C_CheckState(0x28);
      if (ret_val)    return ret_val;
    }
    /* Not reaching the page boundary */
    else
    {
      I2C_SendByte(*InitStruct->pBuffer);
      InitStruct->pBuffer++;
      ret_val = I2C_CheckState(0x28);
      if (ret_val)    return ret_val;            
    }                   
  }
  
  I2C_SendStop();
  I2C_WaitForCrossPage(InitStruct->SlaveAddr);
  return 0;    
}
           
/**
  * @brief  I2C enable.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void I2C_Cmd(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    I2C->CTRL |= I2C_CTRL_EN;
  else
    I2C->CTRL &= ~I2C_CTRL_EN;
}

/* I2C Exported Functions Group5: 
                                   Others ------------------------------------*/

/**
  * @brief  Assert acknowledge configure.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void I2C_AssertAcknowledgeConfig(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    I2C->CTRL |= I2C_CTRL_AA;
  else
    I2C->CTRL &= ~I2C_CTRL_AA;
}

/**
  * @brief  Receive a byte data.
  * @param  None.
  * @retval Data received.
  */
uint8_t I2C_ReceiveData(void)
{
  return I2C->DATA;
}

/**
  * @brief  Sends a byte data.
  * @param  Dat:data to transmit.
  * @retval None
  */
void I2C_SendData(uint8_t Dat)
{
  I2C->DATA = Dat;
}

/**
  * @brief  Generate start signal.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void I2C_GenerateSTART(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    I2C->CTRL |= I2C_CTRL_STA;
  else
    I2C->CTRL &= ~I2C_CTRL_STA;
}

/**
  * @brief  Generate stop signal.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void I2C_GenerateSTOP(uint32_t NewState)
{
  /* Check parameters */ 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    I2C->CTRL |= I2C_CTRL_STO;
  else
    I2C->CTRL &= ~I2C_CTRL_STO;
}

/**
  * @brief  Get status code.
  * @param  None
  * @retval status code.
  */
uint8_t I2C_GetStatusCode(void)
{
  return (I2C->STS&I2C_STS_STS);
}

/*********************************** END OF FILE ******************************/
