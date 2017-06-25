/**************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       kbi.c
 * @brief      键盘中断(KBI)函数库
 * @author     Navota
 * @date       2017-1-1
 ****************************************************************************/
#include "nv32f100.h"

/****************************************************************************!
 * @ 存放KBI回调函数接口
 ****************************************************************************/
KBI_CallbackType KBI_Callback[KBI_MAX_NO] = {(KBI_CallbackType)NULL};

/*****************************************************************************//*!
*
* @brief 初始化KBI模块.
*        
* @param[in]  pKBI       指向KBI模块.
* @param[in]  pConfig    指向KBI配置结构体
*
* @return none.
*
* @see KBI_DeInit.
*
*****************************************************************************/
void KBI_Init(KBI_Type *pKBI, KBI_ConfigType *pConfig)
{
#if defined(CPU_NV32)
    uint16_t    i;
    uint8_t     sc = 0;
    uint8_t     u8Port;
    uint8_t     u8PinPos;
    uint16_t    u16PinMapping[KBI_MAX_NO][8] = 
    {
        {
            0, 1, 2, 3, 8, 9, 10, 11           /* KBI0中断输入引脚在GPIOA寄存器中的位置*/
        },
        {
            24, 25, 26, 27, 28, 29, 30, 31      /*KBI1中断输入引脚在GPIOA寄存器中的位置*/
        }
    };
#elif defined(CPU_NV32M3)
    uint16_t    i;
    uint8_t     sc = 0;
    uint8_t     u8Port;
    uint8_t     u8PinPos;
    uint16_t    u16PinMapping[KBI_MAX_NO][8] = 
    {
        {
            0, 1, 2, 3, 8, 9, 10, 11           /* KBI0中断输入引脚在GPIOA寄存器中的位置*/
        },
        {
            20, 21, 16, 17, 18, 19, 12, 13     /* KBI1中断输入引脚在GPIOA寄存器中的位置*/
        }
    };
#elif defined(CPU_NV32M4)
     uint32_t    i;
     uint32_t     sc = 0;
     uint32_t     u8Port;
     uint32_t     u8PinPos;

     uint32_t    u16PinMapping[KBI_MAX_NO][KBI_MAX_PINS_PER_PORT] =
    {
        {/* KBI0P0~KBI0P31 中断输入引脚在GPIOA寄存器中的位置 */
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31           
        },
        {/* KBI1P0~KBI1P31中断输入引脚在GPIOA寄存器中的位置 */
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31		   
        }
    };
#endif	 
 
    
    if(KBI0 == pKBI)
    {
        SIM->SCGC   |= SIM_SCGC_KBI0_MASK;             /* 使能KBI0模块的总线时钟 */
        u8Port      =  0;
    }
    else if (KBI1 == pKBI)
    {        
        SIM->SCGC   |= SIM_SCGC_KBI1_MASK;             /* 使能KBI1模块的总线时钟 */
        u8Port      =  1;
    }
    
    /*设定KBI中断检测模式*/
    sc          = pConfig->sBits.bMode;
    pKBI->SC    = sc;

    /* 配置KBI中断输入引脚 */
    for (i = 0; i < KBI_MAX_PINS_PER_PORT; i++)
    {
        if(pConfig->sPin[i].bEn)
        {
            pKBI->PE    |= (1<<i);                      /* 使能I/O引脚为KBI中断输入引脚*/
            pKBI->ES    = (pKBI->ES & ~(1<<i)) | (pConfig->sPin[i].bEdge << i);     
            u8PinPos = u16PinMapping[u8Port][i];
            ASSERT(!(u8PinPos & 0x80));
		#if defined(CPU_NV32)|| defined(CPU_NV32M3)	
            FGPIOA->PIDR  &= ~(1<<u8PinPos);              /* 使能GPIO输入*/     
            FGPIOA->PDDR  &= ~(1<<u8PinPos);              /* 引脚配置为通用输入  */  
            PORT->PUEL  |= (1<<u8PinPos);                 /* 使能内部上拉*/
        #elif defined(CPU_NV32M4)
		   if (u8Port == 0)   /* KBI0 */
           {
		   	FGPIOA->PIDR  &= ~(1<<u8PinPos);                 /* 使能GPIO输入*/       
            FGPIOA->PDDR  &= ~(1<<u8PinPos);             /* 引脚配置为通用输入  */  
            PORT->PUE0  |= (1<<u8PinPos);                /* 使能内部上拉*/
           }
		   else if (u8Port == 1)   /* KBI1 */
           {
		   	FGPIOB->PIDR  &= ~(1<<u8PinPos);                /* 使能GPIO输入*/      
            FGPIOB->PDDR  &= ~(1<<u8PinPos);            /* 引脚配置为通用输入  */  
            PORT->PUE1  |= (1<<u8PinPos);               /* 使能内部上拉*/
           }
		#endif  
		}
    }
    
    #if defined(CPU_NV32M4)
    /*Reset KBI_SP register*/
	sc = pConfig->sBits.bRstKbsp<<KBI_SC_RSTKBSP_SHIFT;
	pKBI->SC    |= sc;
	
    /*Real KBI_SP register enable*/
	sc = pConfig->sBits.bKbspEn<<KBI_SC_KBSPEN_SHIFT;
	pKBI->SC    |= sc;
	#endif
  
	/*清除中断标志位*/
    pKBI->SC    = sc;
    
    /* 使能KBI中断 */
    if(pConfig->sBits.bIntEn)
    {
        pKBI->SC    |=  KBI_SC_KBIE_MASK;
        
        if(KBI0 == pKBI)
        {
            NVIC_EnableIRQ(KBI0_IRQn);
        }
        else
        {
            NVIC_EnableIRQ(KBI1_IRQn);            
        }
    }
}

/*****************************************************************************//*!
*
* @brief 设置KBI回调函数，通过中断服务函数调用
*        
* @param[in] pKBI          指向KBI模块.
* @param[in] pfnCallback   指向回调函数.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void KBI_SetCallback(KBI_Type *pKBI, KBI_CallbackType pfnCallback)
{
    if(KBI0 == pKBI)
    {
        KBI_Callback[0] = pfnCallback;
    }
    else
    {
        KBI_Callback[1] = pfnCallback;        
    }
}

/*****************************************************************************//*!
*
* @brief 复位KBI模块.
*        
* @param[in]  pKBI        指向KBI模块.
*         
* @return none.
*
* @see KBI_Init.
*
*****************************************************************************/
void KBI_DeInit(KBI_Type *pKBI)
{
    if(KBI0 == pKBI)
    {
        NVIC_DisableIRQ(KBI0_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(KBI1_IRQn);        
    }
    
    pKBI->PE = 0;
    pKBI->SC = 0;
    pKBI->ES = 0;
    
    if(KBI0 == pKBI)
    {
        SIM->SCGC   &= ~SIM_SCGC_KBI0_MASK;             /* 禁用KBI0模块总线时钟 */
    }
    else
    {
        SIM->SCGC   &= ~SIM_SCGC_KBI1_MASK;             /* 禁用KBI1模块总线时钟 */       
    }
}

/*****************************************************************************//*!
*
* @brief KBI0模块中断服务函数.
*        
* @param  none. 
*
* @return none.
*
*****************************************************************************/

void KBI0_Isr(void)	
{
  KBI0->SC |= KBI_SC_KBACK_MASK;                        /*清除中断标志位 */

  if(KBI_Callback[0])
  {
      KBI_Callback[0]();
  }
}



/*****************************************************************************//*!
*
* @brief KBI1模块中断服务函数
*        
* @param  none. 
*
* @return none.
*
*
*****************************************************************************/

void KBI1_Isr(void)	
{
  KBI1->SC |= KBI_SC_KBACK_MASK;                        /*清除中断标志位*/
 
  if(KBI_Callback[1])
  {
      KBI_Callback[1]();
  }
}

