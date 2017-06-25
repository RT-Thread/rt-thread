/*************************************************************************!     
 *     技术讨论：QQ群  123763203
 *     官网    ：www.navota.com
 *
 * @file       uart.c
 * @brief      uart通讯接口函数库
 * @author     Navota
 * @date       2017-1-1
 *************************************************************************/
#include "nv32f100.h"


/*!
 * @brief 存放回调入口
 *
 */
UART_CallbackType UART_Callback = NULL;

/******************************************************************************
* 定义UART的接口函数
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief 初始化UART,关中断,无硬件流控制.
*        
* @param[in] pUART       指向三个UART其中一个的基址
* @param[in] pConfig     配置UART的结构体
*
* @return none
*
*****************************************************************************/
void UART_Init(UART_Type *pUART, UART_ConfigType *pConfig)
{
    uint16_t u16Sbr;
    uint8_t u8Temp;
    uint32_t u32SysClk = pConfig->u32SysClkHz;//定义系统时钟
    uint32_t u32Baud = pConfig->u32Baudrate;//定义波特率

    /* 合法性检查 */
    ASSERT((pUART == UART0) || (pUART == UART1) || (pUART == UART2));
  
	/* 设置时钟选通控制用来选择相应的 UART 口 */
    if (pUART == UART0)
	{
		SIM->SCGC |= SIM_SCGC_UART0_MASK;//使能相应功能位， 选通对应 UART
	}
#if defined(CPU_NV32)  
	else if (pUART == UART1)
	{
        SIM->SCGC |= SIM_SCGC_UART1_MASK;
	}
    else
	{
        SIM->SCGC |= SIM_SCGC_UART2_MASK;
	}
#endif    
    /*确保在我们进行配置时， 禁止发送和接收*/
    pUART->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
    
    /* 配置 UART 为 8 位模式, 无奇偶校验位 */
    pUART->C1 = 0;
    
    /* 波特率计算 */
    u16Sbr = (((u32SysClk)>>4) + (u32Baud>>1))/u32Baud;
    
    /*把当前数据存放在串口波特率寄存器中， 且SBR位清0，即波特率发生器被禁止*/
    u8Temp = pUART->BDH & ~(UART_BDH_SBR_MASK);
    
    pUART->BDH = u8Temp |  UART_BDH_SBR(u16Sbr >> 8);
    pUART->BDL = (uint8_t)(u16Sbr & UART_BDL_SBR_MASK);

    /*使能 UART 接收和发送 */
    pUART->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
}

/*****************************************************************************//*!
*
* @brief 接收一个字符.
*        
* @param[in] pUART        指向三个UART其中一个的基址
* 
* @return 接收到的字符
*
*****************************************************************************/
uint8_t UART_GetChar(UART_Type *pUART)
{

    /* 合法性检测 */
    ASSERT((pUART == UART0) || (pUART == UART1) || (pUART == UART2));
 
    /* 等待直到一个字符被接收 */
    while (!(pUART->S1 & UART_S1_RDRF_MASK));
    
    /* 返回接收到的8位数据 */
    return pUART->D;
}
/*****************************************************************************//*!
*
* @brief 发送一个字符.
*        
* @param[in] pUART       指向三个UART其中一个的基址
* @param[in] u8Char      要发送的字符
*
* @return none
*
*****************************************************************************/
void UART_PutChar(UART_Type *pUART, uint8_t u8Char)
{    
    /* 一直等待， 直到缓冲区为空 */
    while (!(pUART->S1 & UART_S1_TDRE_MASK));
    
    /* 发送字符到数据寄存器 */
    pUART->D = (uint8_t)u8Char;
}

/*****************************************************************************//*!
*
* @brief 波特率设置.
*        
* @param[in] pUART       指向三个UART其中一个的基址
* @param[in] pConfig     波特率相关配置结构体
*
* @return none
*
*****************************************************************************/
void UART_SetBaudrate(UART_Type *pUART, UART_ConfigBaudrateType *pConfig)
{
    uint8_t u8Temp;
    uint16_t u16Sbr;
    uint32_t u32SysClk    = pConfig->u32SysClkHz;
    uint32_t u32baud       = pConfig->u32Baudrate;
 
    /* 合法性检测 */
    ASSERT((pUART == UART0) || (pUART == UART1) || (pUART == UART2));

    /*计算波特率，四舍五入提高精度 */
    u16Sbr = (((u32SysClk)>>4) + (u32baud>>1))/u32baud;

  
    u8Temp = pUART->BDH & ~(UART_BDH_SBR_MASK);
    
    pUART->BDH = u8Temp |  UART_BDH_SBR(u16Sbr >> 8);
    pUART->BDL = (uint8_t)(u16Sbr & UART_BDL_SBR_MASK);


    pUART->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

}

/*****************************************************************************//*!
*
* @brief 使能UART中断.
*        
* @param[in] pUART               指向三个UART其中一个的基址
* @param[in] InterruptType       中断的类型
*
* @return none
*
*****************************************************************************/
void UART_EnableInterrupt(UART_Type *pUART, UART_InterruptType InterruptType)
{

    /* 通道合法性检查 */
    ASSERT((pUART == UART0) || (pUART == UART1) || (pUART == UART2));

    if (InterruptType == UART_TxBuffEmptyInt)      //发送中断使能
    {
        pUART->C2 |= UART_C2_TIE_MASK;
    }
    else if (InterruptType == UART_TxCompleteInt)  //传输完成中断使能
    {
        pUART->C2 |= UART_C2_TCIE_MASK;
    }
    else if (InterruptType == UART_RxBuffFullInt)  //接收器中断使能
    {
        pUART->C2 |= UART_C2_RIE_MASK;
    }
    else if (InterruptType == UART_IdleLineInt)    //空闲线中断使能
    {
        pUART->C2 |= UART_C2_ILIE_MASK;
    }
    else if (InterruptType == UART_RxOverrunInt)   //过载中断使能
    {
        pUART->C3 |= UART_C3_ORIE_MASK;
    }
    else if (InterruptType == UART_NoiseErrorInt)  //噪声错误中断使能
    {
        pUART->C3 |= UART_C3_NEIE_MASK;
    }
    else if (InterruptType == UART_FramingErrorInt) //帧错误中断使能
    {
        pUART->C3 |= UART_C3_FEIE_MASK;
    } 
    else if (InterruptType == UART_ParityErrorInt)  //奇偶校验中断使能
    {
        pUART->C3 |= UART_C3_FEIE_MASK;
    } 
    else
    {
        //其他暂不支持类型的中断
    }  
}

/*****************************************************************************//*!
*
* @brief 禁用UART中断.
*        
* @param[in]      指向三个UART其中一个的基址
* @param[in]      中断的类型
*
* @return none
*
*****************************************************************************/
void UART_DisableInterrupt(UART_Type *pUART, UART_InterruptType InterruptType)
{
     /* 通道合法性检查 */
    ASSERT((pUART == UART0) || (pUART == UART1) || (pUART == UART2));


    if (InterruptType == UART_TxBuffEmptyInt)       //发送中断禁用
    {
        pUART->C2 &= (~UART_C2_TIE_MASK);
    }
    else if (InterruptType == UART_TxCompleteInt)  //传输完成中断禁用
    {
        pUART->C2 &= (~UART_C2_TCIE_MASK);
    }
    else if (InterruptType == UART_RxBuffFullInt)  //接收器中断禁用
    {
        pUART->C2 &= (~UART_C2_RIE_MASK);
    }
    else if (InterruptType == UART_IdleLineInt)    //空闲线中断禁用
    {
        pUART->C2 &= (~UART_C2_ILIE_MASK);
    }
    else if (InterruptType == UART_RxOverrunInt)    //过载中断禁用
    {
        pUART->C3 &= (~UART_C3_ORIE_MASK);
    }
    else if (InterruptType == UART_NoiseErrorInt)   //噪声错误中断禁用
    {
        pUART->C3 &= (~UART_C3_NEIE_MASK);
    }
    else if (InterruptType == UART_FramingErrorInt)  //帧错误中断禁用
    {
        pUART->C3 &= (~UART_C3_FEIE_MASK);
    } 
    else if (InterruptType == UART_ParityErrorInt)   //奇偶校验中断禁用
    {
        pUART->C3 &= (~UART_C3_FEIE_MASK);
    } 
    else
    {
       //其他暂不支持类型的中断
    }  
}


/*****************************************************************************//*!
*
* @brief 从两个状态寄存器获取UART状态
*        
* @param[in] pUART     指向三个UART其中一个的基址
*
* @return              16位的状态
*
*****************************************************************************/
uint16_t UART_GetFlags(UART_Type *pUART)
{
    uint16_t u16StatusFlags = 0;//先清空标志位

    u16StatusFlags = pUART->S2; //将状态寄存器 2 的值赋给标志参数
    u16StatusFlags = (u16StatusFlags<<8)| pUART->S1; //两个状态寄存器拼接赋给标志参数

    return u16StatusFlags;//返回标志参数的值
}

/*****************************************************************************//*!
*
* @brief 检查特定的位是否置位.
*        
* @param[in] pUART         指向三个UART其中一个的基址
* @param[in] FlagType      位的类型
*
* @return       
*               1, 标志置位
*               0, 标志清零
*
*****************************************************************************/
uint8_t UART_CheckFlag(UART_Type *pUART, UART_FlagType FlagType)
{
    uint16_t u16StatusFlags = 0;

    u16StatusFlags = UART_GetFlags(pUART);

    return (u16StatusFlags & (1<<FlagType));
}

/*****************************************************************************//*!
*
* @brief 用查询模式发送字符串.
*        
* @param[in] pUART          指向三个UART其中一个的基址
* @param[in] pSendBuff      字符串首地址
* @param[in] u32Length      字符串的长度
*
* @return       none
*
*****************************************************************************/
void UART_SendWait(UART_Type *pUART, uint8_t *pSendBuff, uint32_t u32Length)
{
    uint8_t u8TxChar;
    uint32_t  i;
    
    for (i = 0; i < u32Length; i++)
    {
        u8TxChar = pSendBuff[i];
        while (!UART_IsTxBuffEmpty(pUART))
        {
            #if defined(ENABLE_WDOG)
                WDOG_Feed();
            #endif        
        }
        UART_WriteDataReg(pUART, u8TxChar);        
    }
}

/*****************************************************************************//*!
*
* @brief 用查询模式接收字符串.
*        
* @param[in] pUART           指向三个UART其中一个的基址
* @param[in] pReceiveBuff    定义接收字符串的首地址
* @param[in] u32Length       所要接收字符串的长度
*
* @return       none
*
*****************************************************************************/
void UART_ReceiveWait(UART_Type *pUART, uint8_t *pReceiveBuff, uint32_t u32Length)
{
    uint8_t u8RxChar;
    uint32_t i;
    
    for (i = 0; i < u32Length; i++)
    {
        while (!UART_IsRxBuffFull(pUART))
        {
            #if defined(ENABLE_WDOG)
                WDOG_Feed();
            #endif       
        }    
        u8RxChar = UART_ReadDataReg(pUART);
        pReceiveBuff[i] = u8RxChar;
    }
}

/*****************************************************************************//*!
*
* @brief 等待发送完成.
*        
* @param[in] pUART         指向三个UART其中一个的基址
*
* @return       none
*
*****************************************************************************/
void UART_WaitTxComplete(UART_Type *pUART)
{
    while (!UART_IsTxComplete(pUART));//一直等待直到发送完成
}

/*****************************************************************************//*!
*
* @brief  设置UART模块的中断回调函数.
*        
* @param[in]  pfnCallback      回调函数的地址
*
* @return none
*
*****************************************************************************/
void UART_SetCallback(UART_CallbackType pfnCallback)
{
    UART_Callback = pfnCallback;
}


/*! @}                                                                        */


/*****************************************************************************//*!
*
* @brief uart0 中断服务函数.
*        
* @param        none
*
* @return       none
*
*****************************************************************************/
void UART0_Isr(void)
{
    UART_Callback(UART0);
}


#if defined(CPU_NV32) 
/*****************************************************************************//*!
*
* @brief uart0 中断服务函数.
*        
* @param        none
*
* @return       none
*
*****************************************************************************/
void UART1_Isr(void)
{
    UART_Callback(UART1);
}
/*****************************************************************************//*!
*
* @brief uart0 中断服务函数.
*        
* @param        none
*
* @return       none
*
*****************************************************************************/
void UART2_Isr(void)
{
    UART_Callback(UART2);
}


#endif



