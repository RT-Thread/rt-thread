/**************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       gpio.c
 * @brief      通用输入输出模块(GPIO)函数库
 * @author     Navota
 * @date       2017-1-1
 **************************************************************************/
#include "nv32f100.h"



/*****************************************************************************//*!
* @brief    复位GPIO模块.
*        
* @param[in] pGPIO    指向GPIO模块 GPIOA/GPIOB.
*
* @return none
*
*****************************************************************************/
void GPIO_DeInit(GPIO_Type *pGPIO)
{
    /* Sanity check */
#if defined(CPU_NV32)
     ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB));
#endif
#if defined(CPU_NV32M3)
    ASSERT(pGPIO == GPIOA);
#endif
#if defined(CPU_NV32M4)
      ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB) || (pGPIO == GPIOC));
#endif

    pGPIO->PCOR = 0x00000000;   /* 端口清零输出寄存器 */
    pGPIO->PDDR = 0x00000000;   /* 端口数据方向寄存器 */
    //pGPIO->PDIR = 0x00000000;   /* 端口数据输入寄存器 */
    pGPIO->PDOR = 0x00000000;   /* 端口数据输出寄存器 */
    pGPIO->PIDR = 0xFFFFFFFF;   /* 端口输入禁用寄存器 */
    pGPIO->PSOR = 0x00000000;   /* 端口置位输出寄存器 */
    pGPIO->PTOR = 0x00000000;   /* 端口切换输出寄存器 */
}

/*****************************************************************************//*!
* @brief    初始化GPIO引脚--通过32位引脚掩码确定要初始化的引脚
*        
* @param[in] pGPIO       指向GPIO模块 GPIOA/GPIOB.
* @param[in] u32PinMask  32位引脚掩码  ( GPIO_PTA0_MASK, GPIO_PTA1_MASK ............)
* @param[in] sGpioType   引脚属性 （输入、输入、高电流驱动、内部上拉）
*
* @return   none
*
* @ 注：
*   . 如果引脚配置为输入，禁用高电流驱动
*   . 如果引脚配置为输出，禁用内部上拉
*     仅PTH1/0, PTE1/0, PTD1/0, PTB5/4 支持高电流驱动.
*****************************************************************************/
void GPIO_Init(GPIO_Type *pGPIO, uint32_t u32PinMask, GPIO_PinConfigType sGpioType)
{
    /* Sanity check */
#if defined(CPU_NV32)
     ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB));
#endif
#if defined(CPU_NV32M3)
    ASSERT(pGPIO == GPIOA);
#endif
#if defined(CPU_NV32M4)
      ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB) || (pGPIO == GPIOC));
#endif
    
    /* 配置GPIO为输入或者输出 */
    if ((sGpioType == GPIO_PinOutput) || (sGpioType == GPIO_PinOutput_HighCurrent))
    {
        pGPIO->PDDR |= u32PinMask;      /* 引脚配置为通用输出*/
        pGPIO->PIDR |= u32PinMask;      /* 置位端口输入禁用寄存器*/   
    }
    else if ((sGpioType == GPIO_PinInput) || (sGpioType == GPIO_PinInput_InternalPullup))
    {
        pGPIO->PDDR &= ~u32PinMask;   /* 引脚配置为通用输入 */
        pGPIO->PIDR &= ~u32PinMask;   /* 清零端口输入禁用寄存器 */
    }
    /* 设置GPIO端口输入上拉 */
#if defined(CPU_NV32)
    switch((uint32_t)pGPIO)
    {
        case GPIOA_BASE:
            (sGpioType == GPIO_PinInput_InternalPullup)?(PORT->PUEL |= u32PinMask):(PORT->PUEL &= ~u32PinMask);
            break;
        case GPIOB_BASE:
            (sGpioType == GPIO_PinInput_InternalPullup)?(PORT->PUEH |= u32PinMask):(PORT->PUEH &= ~u32PinMask);
            break;
        default:
            break;
     }
#endif
    
#if defined(CPU_NV32M3)
    switch((uint32_t)pGPIO)
    {
        case GPIOA_BASE:
            (sGpioType == GPIO_PinInput_InternalPullup)?(PORT->PUEL |= u32PinMask):(PORT->PUEL &= ~u32PinMask);
            break;
        default:
            break;
     }
#endif
    
#if defined(CPU_NV32M4)
    switch((uint32_t)pGPIO)
    {
        case GPIOA_BASE:
            (sGpioType == GPIO_PinInput_InternalPullup)?(PORT->PUE0 |= u32PinMask):(PORT->PUE0 &= ~u32PinMask);
            break;
        case GPIOB_BASE:
            (sGpioType == GPIO_PinInput_InternalPullup)?(PORT->PUE1 |= u32PinMask):(PORT->PUE1 &= ~u32PinMask);
            break;
        case GPIOC_BASE:
            (sGpioType == GPIO_PinInput_InternalPullup)?(PORT->PUE2 |= u32PinMask):(PORT->PUE2 &= ~u32PinMask);
            break;
        default:
            break;
     }
#endif   
    
    /* 配置GPIO端口输出高电流驱动 */
#if defined(CPU_NV32M3)
    if (u32PinMask & GPIO_PTC5_MASK)    
    {   
        PORT->HDRVE |= PORT_HDRVE_PTC5_MASK;
    }   
    if (u32PinMask & GPIO_PTC1_MASK)
    {   
        PORT->HDRVE |= PORT_HDRVE_PTC1_MASK;
    }   
    if (u32PinMask & GPIO_PTB5_MASK)
    {   
        PORT->HDRVE |= PORT_HDRVE_PTB5_MASK;
    }   
#endif
    
#if defined(CPU_NV32) | defined(CPU_NV32M4)
    if (pGPIO == GPIOA)
    {
        if (u32PinMask & GPIO_PTB4_MASK)    //PB4 高电流驱动输出
        {   
            PORT->HDRVE |= PORT_HDRVE_PTB4_MASK;
        }   
        if (u32PinMask & GPIO_PTB5_MASK)
        {   
            PORT->HDRVE |= PORT_HDRVE_PTB5_MASK;
        }   
        if (u32PinMask & GPIO_PTD0_MASK)
        {   
            PORT->HDRVE |= PORT_HDRVE_PTD0_MASK;
        }   
        if (u32PinMask & GPIO_PTD1_MASK)
        {   
            PORT->HDRVE |= PORT_HDRVE_PTD1_MASK;
        }   
    }
    if (pGPIO == GPIOB)
    {
        if (u32PinMask & GPIO_PTE0_MASK)
        {   
            PORT->HDRVE |= PORT_HDRVE_PTE0_MASK;
        }   
        if (u32PinMask & GPIO_PTE1_MASK)
        {   
            PORT->HDRVE |= PORT_HDRVE_PTE1_MASK;
        }   
        if (u32PinMask & GPIO_PTH0_MASK)
        {   
            PORT->HDRVE |= PORT_HDRVE_PTH0_MASK;
        }   
        if (u32PinMask & GPIO_PTH1_MASK)
        {   
            PORT->HDRVE |= PORT_HDRVE_PTH1_MASK;
        }   
    }

#endif
    
}

/*****************************************************************************//*!
* @brief    切换GPIO端口数据输出————通过32位引脚掩码确定要切换输出的引脚
*        
* @param[in] pGPIO       指向GPIO模块  GPIOA/GPIOB.
* @param[in] u32PinMask  32位引脚掩码  ( GPIO_PTA0_MASK, GPIO_PTA1_MASK ............)
*
* @return none
*
*****************************************************************************/
void GPIO_Toggle(GPIO_Type *pGPIO, uint32_t u32PinMask)
{
    /* Sanity check */
#if defined(CPU_NV32)
     ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB));
#endif
#if defined(CPU_NV32M3)
    ASSERT(pGPIO == GPIOA);
#endif
#if defined(CPU_NV32M4)
      ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB) || (pGPIO == GPIOC));
#endif

    pGPIO->PTOR = u32PinMask;   /* 32位引脚掩码确定要切换输出的引脚 */
}

/*****************************************************************************//*!
* @brief  读取端口数据输入寄存器 
*        
* @param[in] pGPIO      指向GPIO模块  GPIOA/GPIOB.
*
* @return   端口输入寄存器32位数值
*
*****************************************************************************/
uint32_t GPIO_Read(GPIO_Type *pGPIO)
{
    /* Sanity check */
#if defined(CPU_NV32)
     ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB));
#endif
#if defined(CPU_NV32M3)
    ASSERT(pGPIO == GPIOA);
#endif
#if defined(CPU_NV32M4)
      ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB) || (pGPIO == GPIOC));
#endif

    return (pGPIO->PDIR);   /* 读端口数据输入寄存器 */
  
}

/*****************************************************************************//*!
* @brief 读取端口数据寄存器的某一位————通过定义的GPIO引脚名确定要读取的位。
*        
* @param[in] pGPIO      指向GPIO模块  GPIOA/GPIOB.
* @param[in] GPIO_Pin   GPIO引脚名 (GPIO_PTA0PIO_PTA1..............)
*
* @return  端口数据寄存器某一位的值
*
*****************************************************************************/
uint8_t GPIO_BitRead(GPIO_PinType GPIO_Pin)
{
  uint8_t data;  
  /* Sanity check */
    ASSERT(GPIO_Pin <= GPIO_PTI7);
    

      if (GPIO_Pin < GPIO_PTE0)
      {
            if(((1<<GPIO_Pin) & GPIOA->PDIR) > 0)       /*判断要读取的位，对应的数值是1还是0*/
                data = 0x1;                             /* 如果是1返回1，是0则返回0 */
            else 
                data = 0x0;
          
      }
      
      else if (GPIO_Pin < GPIO_PTI0)
      {
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - 32);
        
            if(((1<<GPIO_Pin) & GPIOB->PDIR) > 0)       /*判断要读取的位，对应的数值是1还是0*/
                data = 0x1;                             /* 如果是1返回1，是0则返回0 */
            else 
	       data = 0x0;
          
      }

     return data;
		    
}


/*****************************************************************************//*!
* @brief  写数据到端口数据输出寄存器 
*        
* @param[in] pGPIO      指向GPIO模块  GPIOA/GPIOB.
* @param[in] u32Value   写入到端口数据输出寄存器的值
*
* @return   none
*
*****************************************************************************/
void GPIO_Write(GPIO_Type *pGPIO, uint32_t u32Value)
{
    /* Sanity check */
#if defined(CPU_NV32)
     ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB));
#endif
#if defined(CPU_NV32M3)
    ASSERT(pGPIO == GPIOA);
#endif
#if defined(CPU_NV32M4)
      ASSERT((pGPIO == GPIOA) || (pGPIO == GPIOB) || (pGPIO == GPIOC));
#endif
    
    pGPIO->PDOR = u32Value;    /* 写数据到端口数据输出寄存器 */
  
}

/*****************************************************************************//*!
* @brief   初始化GPIO引脚--通过定义的GPIO引脚名确定要初始化的引脚
*        
* @param[in] GPIO_Pin        GPIO引脚名 (GPIO_PTA0PIO_PTA1..............)
* @param[in] GPIO_PinConfig  配置输入、输出
*
* @return   none
*
*****************************************************************************/
void GPIO_PinInit(GPIO_PinType GPIO_Pin, GPIO_PinConfigType GPIO_PinConfig)
{
    /* Sanity check */
    ASSERT(GPIO_Pin <= GPIO_PTI7);
      

#if defined(CPU_NV32)
      if (GPIO_Pin < GPIO_PTE0)
      {
        switch (GPIO_PinConfig)
        {
        case GPIO_PinOutput:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出 */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一*/
            PORT->PUEL &= ~(1<<GPIO_Pin);      /* 禁用内部上拉 */
          break;
        case GPIO_PinInput:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入 */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零 */
            PORT->PUEL &= ~(1<<GPIO_Pin);      /*  禁用上拉*/
          break;
        case GPIO_PinInput_InternalPullup:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入  */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零  */
            PORT->PUEL |= (1<<GPIO_Pin);       /* 使能内部上拉 */
          break;
        case GPIO_PinOutput_HighCurrent:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出  */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一 */
            PORT->PUEL &= ~(1<<GPIO_Pin);       /* 禁用内部上拉*/
          break;
        }
      }
      else if (GPIO_Pin < GPIO_PTI0)
      {
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - 32);
        switch (GPIO_PinConfig)
        {
        case GPIO_PinOutput:
            GPIOB->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出 */
            GPIOB->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一 */
            PORT->PUEH &= ~(1<<GPIO_Pin);      /* 禁用内部上拉*/
          break;
        case GPIO_PinInput:
            GPIOB->PDDR &= ~(1<<GPIO_Pin);      /* 引脚配置为通用输入 */
            GPIOB->PIDR &= ~(1<<GPIO_Pin);      /* 端口输入禁用寄存器清零  */
            PORT->PUEH &= ~(1<<GPIO_Pin);      /* 禁用内部上拉*/
          break;
        case GPIO_PinInput_InternalPullup:
            GPIOB->PDDR &= ~(1<<GPIO_Pin);    /* 引脚配置为通用输入 */
            GPIOB->PIDR &= ~(1<<GPIO_Pin);    /* 端口输入禁用寄存器清零  */
            PORT->PUEH |= (1<<GPIO_Pin);      /* 使能内部上拉*/
          break;
        case GPIO_PinOutput_HighCurrent:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出  */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一 */
            PORT->PUEL &= ~(1<<GPIO_Pin);       /* 禁用内部上拉*/
          break;
        }
      }
#endif
      
#if defined(CPU_NV32M3)
      if (GPIO_Pin < GPIO_PTE0)
      {
        switch (GPIO_PinConfig)
        {
        case GPIO_PinOutput:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出 */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一*/
            PORT->PUEL &= ~(1<<GPIO_Pin);      /* 禁用内部上拉 */
          break;
        case GPIO_PinInput:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入 */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零 */
            PORT->PUEL &= ~(1<<GPIO_Pin);      /*  禁用上拉*/
          break;
        case GPIO_PinInput_InternalPullup:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入  */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零  */
            PORT->PUEL |= (1<<GPIO_Pin);       /* 使能内部上拉 */
          break;
        case GPIO_PinOutput_HighCurrent:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出  */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一 */
            PORT->PUEL &= ~(1<<GPIO_Pin);       /* 禁用内部上拉*/
          break;
        }
      }
#endif
    
    
#if defined(CPU_NV32M4)
      if (GPIO_Pin < GPIO_PTE0)
      {
         switch (GPIO_PinConfig)
        {
        case GPIO_PinOutput:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出 */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一*/
            PORT->PUEL &= ~(1<<GPIO_Pin);      /* 禁用内部上拉 */
          break;
        case GPIO_PinInput:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入 */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零 */
            PORT->PUEL &= ~(1<<GPIO_Pin);      /*  禁用上拉*/
          break;
        case GPIO_PinInput_InternalPullup:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入  */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零  */
            PORT->PUEL |= (1<<GPIO_Pin);       /* 使能内部上拉 */
          break;
        case GPIO_PinOutput_HighCurrent:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出  */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一 */
            PORT->PUEL &= ~(1<<GPIO_Pin);       /* 禁用内部上拉*/
          break;
        }
      }
      else if (GPIO_Pin < GPIO_PTI0)
      {
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - 32);
        switch (GPIO_PinConfig)
        {
        case GPIO_PinOutput:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出 */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一*/
            PORT->PUEL &= ~(1<<GPIO_Pin);      /* 禁用内部上拉 */
          break;
        case GPIO_PinInput:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入 */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零 */
            PORT->PUEL &= ~(1<<GPIO_Pin);      /*  禁用上拉*/
          break;
        case GPIO_PinInput_InternalPullup:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入  */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零  */
            PORT->PUEL |= (1<<GPIO_Pin);       /* 使能内部上拉 */
          break;
        case GPIO_PinOutput_HighCurrent:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出  */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一 */
            PORT->PUEL &= ~(1<<GPIO_Pin);       /* 禁用内部上拉*/
          break;
        }
      }
      else
      {
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - 64);
        switch (GPIO_PinConfig)
        {
        case GPIO_PinOutput:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出 */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一*/
            PORT->PUEL &= ~(1<<GPIO_Pin);      /* 禁用内部上拉 */
          break;
        case GPIO_PinInput:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入 */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零 */
            PORT->PUEL &= ~(1<<GPIO_Pin);      /*  禁用上拉*/
          break;
        case GPIO_PinInput_InternalPullup:
            GPIOA->PDDR &= ~(1<<GPIO_Pin);     /* 引脚配置为通用输入  */
            GPIOA->PIDR &= ~(1<<GPIO_Pin);     /* 端口输入禁用寄存器清零  */
            PORT->PUEL |= (1<<GPIO_Pin);       /* 使能内部上拉 */
          break;
        case GPIO_PinOutput_HighCurrent:
            GPIOA->PDDR |= (1<<GPIO_Pin);      /* 引脚配置为通用输出  */
            GPIOA->PIDR |= (1<<GPIO_Pin);      /* 端口输入禁用寄存器置一 */
            PORT->PUEL &= ~(1<<GPIO_Pin);       /* 禁用内部上拉*/
          break;
      }
#endif
      
    /* 配置GPIO输出高电流驱动 */
    if(GPIO_PinConfig == GPIO_PinOutput_HighCurrent)
    {
#if defined(CPU_NV32M3)
        switch (GPIO_Pin)
        {
            case GPIO_PTB5:
                PORT->HDRVE |= PORT_HDRVE_PTB5_MASK;
                break;
            case GPIO_PTC1:
                PORT->HDRVE |= PORT_HDRVE_PTC1_MASK;
                break;
            case GPIO_PTC5:
                PORT->HDRVE |= PORT_HDRVE_PTC5_MASK;
                break;
            default:
                break;
        }
#endif
    
#if defined(CPU_NV32M4) | defined(CPU_NV32)
        switch (GPIO_Pin)
        {
            case GPIO_PTB4:
                PORT->HDRVE |= PORT_HDRVE_PTB4_MASK;
                break;
            case GPIO_PTB5:
                PORT->HDRVE |= PORT_HDRVE_PTB5_MASK;
                break;
            case GPIO_PTD0:
                PORT->HDRVE |= PORT_HDRVE_PTD0_MASK;
                break;
            case GPIO_PTD1:
                PORT->HDRVE |= PORT_HDRVE_PTD1_MASK;
                break;
            case GPIO_PTE0:
                PORT->HDRVE |= PORT_HDRVE_PTE0_MASK;
                break;
            case GPIO_PTE1:
                PORT->HDRVE |= PORT_HDRVE_PTE1_MASK;
                break;
            case GPIO_PTH0:
                PORT->HDRVE |= PORT_HDRVE_PTH0_MASK;
                break;
            case GPIO_PTH1:
                PORT->HDRVE |= PORT_HDRVE_PTH1_MASK;
                break;
            default:
                break; 
        }
#endif
    }
}

/*****************************************************************************//*!
* @brief 切换GPIO端口数据输出----通过定义的GPIO引脚名确定要切换输出的引脚
*        
* @param[in] GPIO_Pin        GPIO引脚名 (GPIO_PTA0PIO_PTA1..............)
*
* @return   none
*
*****************************************************************************/
void GPIO_PinToggle(GPIO_PinType GPIO_Pin)
{
    /* Sanity check */
    ASSERT(GPIO_Pin <= GPIO_PTI7);

    if (GPIO_Pin < GPIO_PTE0)
    {
        /* PTA0-7, PTB0-7, PTC0-7, PTD0-7 */
        GPIOA->PTOR = (1<<GPIO_Pin);
    }

#if (defined(CPU_NV32) | defined(CPU_NV32M4))

    else if (GPIO_Pin < GPIO_PTI0)
    {
        /* PTE0-7, PTF0-7, PTH0-7, PTI0-7 */
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - GPIO_PTE0);
        GPIOB->PTOR = (1<<GPIO_Pin);
    }
#endif

#if defined(CPU_NV32M4)  
    else if(GPIO_Pin < GPIO_PIN_MAX)
    {
        /* PTI0-7 */
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - GPIO_PTI0);
        GPIOC->PTOR = (1<<GPIO_Pin);
    }
#endif
}

/*****************************************************************************//*!
* @brief  GPIO端口数据输出置1一通过定义的GPIO引脚名确定输出要置1的引脚
*        
* @param[in] GPIO_Pin       GPIO引脚名 (GPIO_PTA0PIO_PTA1..............)
*
* @return   none
*
*****************************************************************************/
void GPIO_PinSet(GPIO_PinType GPIO_Pin)
{
    /* Sanity check */
    ASSERT(GPIO_Pin <= GPIO_PTI7);
    
    if (GPIO_Pin < GPIO_PTE0)
    {
        /* PTA0-7, PTB0-7, PTC0-7, PTD0-7 */
        GPIOA->PSOR = (1<<GPIO_Pin);
    }

#if (defined(CPU_NV32) | defined(CPU_NV32M4))

    else if (GPIO_Pin < GPIO_PTI0)
    {
        /* PTE0-7, PTF0-7, PTH0-7, PTI0-7 */
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - GPIO_PTE0);
        GPIOB->PSOR = (1<<GPIO_Pin);
    }
#endif

#if defined(CPU_NV32M4) 
    else if(GPIO_Pin < GPIO_PIN_MAX)
    {
        /* PTI0-7 */
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - GPIO_PTI0);
        GPIOC->PSOR = (1<<GPIO_Pin);
    }
#endif
}

/*****************************************************************************//*!
* @brief    GPIO端口数据输出清零——通过定义的GPIO引脚名确定要输出清零的引脚
*        
* @param[in] GPIO_Pin        GPIO引脚名 (GPIO_PTA0PIO_PTA1..............)
*
* @return   none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void GPIO_PinClear(GPIO_PinType GPIO_Pin)
{
    /* Sanity check */
    ASSERT(GPIO_Pin <= GPIO_PTI7);
    
    if (GPIO_Pin < GPIO_PTE0)
    {
        /* PTA0-7, PTB0-7, PTC0-7, PTD0-7 */
        GPIOA->PCOR = (1<<GPIO_Pin);
    }

#if (defined(CPU_NV32) | defined(CPU_NV32M4))

    else if (GPIO_Pin < GPIO_PTI0)
    {
        /* PTE0-7, PTF0-7, PTH0-7, PTI0-7 */
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - GPIO_PTE0);
        GPIOB->PCOR = (1<<GPIO_Pin);
    }
#endif

#if defined(CPU_NV32M4)
    else if(GPIO_Pin < GPIO_PIN_MAX)
    {
        /* PTI0-7 */
        GPIO_Pin = (GPIO_PinType)(GPIO_Pin - GPIO_PTI0);
        GPIOC->PCOR = (1<<GPIO_Pin);
    }
#endif
}


