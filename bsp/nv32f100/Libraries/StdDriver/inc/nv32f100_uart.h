/******************************************************************************
*
* @brief  UART 驱动头文件.  
*
******************************************************************************/
#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "nv32f100_wdog.h"

#define MAX_UART_NO             3


/*!
* @brief UART 设置类型.
*
*/ 

typedef struct
{
    uint32_t bEnable      : 1;                /*!< 1: 使能, 0: 禁用 */
    uint32_t resvd        : 31;               /*!< 1: 保留位域 */
} UART_SettingType;
/*! @}                                                                        */

 /*!
 * @brief UART 配置结构体.
 *
 */   
typedef struct 
{
    UART_SettingType    sSettings;              /*!< UART 设置 */
    uint32_t    u32SysClkHz;        /*!< 系统时钟 */
    uint32_t    u32Baudrate;        /*!< UART 波特率 */
} UART_ConfigType;
/*! @}                                                                        */

 /*!
 * @brief UART 波特率配置结构体.
 *
 */   
typedef struct
{
    uint32_t    u32SysClkHz;        /*!< 系统时钟 */
    uint32_t    u32Baudrate;        /*!< UART 波特率 */
} UART_ConfigBaudrateType;
/*! @}                                                                        */

/******************************************************************************
*define uart配置模式列表
*
*//*! @uart配置模式列表
* @{
******************************************************************************/
typedef enum
{
    UART_Mode8Bit,                  /*!< 8位模式 */
    UART_Mode9Bit,                  /*!< 9位模式 */
    UART_ModeEnableLoopback,        /*!< 使能环回模式 */
    UART_ModeDisableLoopback,       /*!< 禁用环回模式*/
    UART_ModeEnableSingleWire,      /*!< 使能UART单线模式 */
    UART_ModeDisableSingleWire,     /*!< 禁用UART单线模式 */
} UART_ModeType;
/*! @}                                                                        */

/******************************************************************************
*define uart中断类型
*
*//*! @uart中断类型列表
* @{
******************************************************************************/

typedef enum
{
    UART_TxBuffEmptyInt,            /*!< 发送中断 */
    UART_TxCompleteInt,             /*!< 传输完成中断 */
    UART_RxBuffFullInt,             /*!< 接收器中断 */

    UART_IdleLineInt,               /*!< 空闲线中断 */

    UART_RxOverrunInt,              /*!< 过载中断 */
    UART_NoiseErrorInt,             /*!< 噪声错误中断 */
    UART_FramingErrorInt,           /*!< /帧错误中断 */
    UART_ParityErrorInt,            /*!< 奇偶校验中断 */
} UART_InterruptType;
/*! @}                                                                        */

/******************************************************************************
*define uart标志类型定义
*
*//*! @uart标志类型定义列表
* @{
******************************************************************************/
typedef enum
{
    UART_FlagPF = 0,        /*!< 奇数 */
    UART_FlagFE,            /*!< 帧错误标志 */
    UART_FlagNF,            /*!< 噪声标志 */
    UART_FlagOR,            /*!< 接收过载 */
    UART_FlagIDLE,          /*!< 空闲线标志 */
    UART_FlagRDRF,          /*!< 接收数据满标志 */
    UART_FlagTC,            /*!< 发送完成标志 */
    UART_FlagTDRE,          /*!< 发送寄存器空标志 */

    UART_FlagRAF,           /*!< 有效接收器标志 */
    UART_FlagLBKDE,         /*!< LIN间隔检测使能 */
    UART_FlagBRK13,         /*!< 间隔字符长度 */ 
    UART_FlagRWUID,         /*!< 接收唤醒空闲检测 */
    UART_FlagRXINV,         /*!< 接收数据反转 */
    UART_FlagRev1,          /*!< 保留 */
    UART_FlagRXEDGIF,       /*!< RXD引脚的有效边沿中断标志 */
    UART_FlagLBKDIF,        /*!< LIN终止检测中断标志 */
} UART_FlagType;
/*! @}                                                                        */

/*!
 * @brief UART 回调类型.
 *
 */
typedef void (*UART_CallbackType)(UART_Type *pUART);

/******************************************************************************
******************************************************************************/

/*!
 * 内联函数
 */
/******************************************************************************
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief 读取接收数据
*        
* @param[in] pUART        指向三个UART其中一个的基址
*
* @return 接收到的字符
*
*****************************************************************************/
__STATIC_INLINE uint8_t UART_ReadDataReg(UART_Type *pUART)
{
    return pUART->D;
}

/*****************************************************************************//*!
*
* @brief 写发送字符
*        
* @param[in] pUART       指向三个UART其中一个的基址
* @param[in] u8Char      需要发送的字符
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_WriteDataReg(UART_Type *pUART, uint8_t u8Char)
{
    pUART->D = (uint8_t)u8Char;
}

/*****************************************************************************//*!
*
* @brief 检测接收数据寄存器是否满
*
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return 0, 没有字符接收; 非0, 有字符接收到
*
*****************************************************************************/
__STATIC_INLINE uint8_t UART_CharPresent(UART_Type *pUART)
{  
    return (pUART->S1 & UART_S1_RDRF_MASK);
}
/*****************************************************************************//*!
*
* @brief 使能发送器
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableTx(UART_Type *pUART)
{
    
    pUART->C2 |= UART_C2_TE_MASK;
}
/*****************************************************************************//*!
*
* @brief 禁用发送器
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_DisableTx(UART_Type *pUART)
{    
    pUART->C2 &= (~UART_C2_TE_MASK);
}

/*****************************************************************************//*!
*
* @brief 使能接收器
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableRx(UART_Type *pUART)
{    
    pUART->C2 |= UART_C2_RE_MASK;
}

/*****************************************************************************//*!
*
* @brief 禁用接收器
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_DisableRx(UART_Type *pUART)
{    
    pUART->C2 &= (~UART_C2_RE_MASK);
}

/*****************************************************************************//*!
*
* @brief 使能循环模式
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableLoopback(UART_Type *pUART)
{
    pUART->C1 |= UART_C1_LOOPS_MASK;
    pUART->C1 &= (~UART_C1_RSRC_MASK);
}

/*****************************************************************************//*!
*
* @brief 使能单线模式
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableSingleWire(UART_Type *pUART)
{
    pUART->C1 |= UART_C1_LOOPS_MASK;
    pUART->C1 |= UART_C1_RSRC_MASK;
}

/*****************************************************************************//*!
*
* @brief 设置8位模式
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_Set8BitMode(UART_Type *pUART)
{
    pUART->C1 &= (~UART_C1_M_MASK);
}

/*****************************************************************************//*!
*
* @brief 设置9位模式
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_Set9BitMode(UART_Type *pUART)
{
    pUART->C1 |= UART_C1_M_MASK;
}

/*****************************************************************************//*!
*
* @brief 使能发送空中断
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableTxBuffEmptyInt(UART_Type *pUART)
{
    pUART->C2 |= UART_C2_TIE_MASK;
}

/*****************************************************************************//*!
*
* @brief 使能发送完成中断
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableTxCompleteInt(UART_Type *pUART)
{
    pUART->C2 |= UART_C2_TCIE_MASK;
}

/*****************************************************************************//*!
*
* @brief 使能接收满中断
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_EnableRxBuffFullInt(UART_Type *pUART)
{
    pUART->C2 |= UART_C2_RIE_MASK;
}

/*****************************************************************************//*!
*
* @brief 禁用发送空中断
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_DisableTxBuffEmptyInt(UART_Type *pUART)
{
        pUART->C2 &= (~UART_C2_TIE_MASK);    
}

/*****************************************************************************//*!
*
* @brief 禁用传输完成中断
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_DisableTxCompleteInt(UART_Type *pUART)
{
    pUART->C2 &= (~UART_C2_TCIE_MASK);   
}

/*****************************************************************************//*!
*
* @brief 禁用接收满中断
*        
* @param[in] pUART       指向三个UART其中一个的基址
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void UART_DisableRxBuffFullInt(UART_Type *pUART)
{
    pUART->C2 &= (~UART_C2_RIE_MASK);  
}

/*****************************************************************************//*!
*
* @brief 发送间隔字符
*        
* @param[in] pUART     指向三个UART其中一个的基址
*
* @return       none
*
*****************************************************************************/
__STATIC_INLINE void UART_PutBreak(UART_Type *pUART)
{
    pUART->C2 |= UART_C2_SBK_MASK; 
    pUART->C2 &= (~UART_C2_SBK_MASK);
}

/*****************************************************************************//*!
*
* @brief 检测发送完成标志.
*        
* @param[in] pUART    指向三个UART其中一个的基址
*
* @return       
*               1, 发送标志置位
*               0, 发送标志清除
*
*****************************************************************************/
__STATIC_INLINE uint8_t UART_IsTxComplete(UART_Type *pUART)
{
    return (pUART->S1 & UART_S1_TC_MASK);
}
/*****************************************************************************//*!
*
* @brief 检测发送寄存器是否空
*        
* @param[in] pUART    指向三个UART其中一个的基址
* 
* @return       
*               1, 发送寄存器空
*               0, 发送寄存器不为空
*
*****************************************************************************/
__STATIC_INLINE uint8_t UART_IsTxBuffEmpty(UART_Type *pUART)
{
    return (pUART->S1 & UART_S1_TDRE_MASK);
}
/*****************************************************************************//*!
*
* @brief 检测接收数据寄存器是否满
*        
* @param[in] pUART    指向三个UART其中一个的基址
*
* @return       
*               1, 接收数据寄存器满
*               0, 接收数据寄存器不为满
*
*****************************************************************************/
__STATIC_INLINE uint8_t UART_IsRxBuffFull(UART_Type *pUART)
{
    return (pUART->S1 & UART_S1_RDRF_MASK);
}
/*! @}                                                                        */


/******************************************************************************
******************************************************************************/
void UART_Init(UART_Type *pUART, UART_ConfigType *pConfig);
uint8_t UART_GetChar(UART_Type *pUART);
void UART_PutChar(UART_Type *pUART, uint8_t u8Char);
void UART_SetBaudrate(UART_Type *pUART, UART_ConfigBaudrateType *pConfig);
void UART_EnableInterrupt(UART_Type *pUART, UART_InterruptType InterruptType);
void UART_DisableInterrupt(UART_Type *pUART, UART_InterruptType InterruptType);
uint16_t UART_GetFlags(UART_Type *pUART);
uint8_t UART_CheckFlag(UART_Type *pUART, UART_FlagType FlagType);
void UART_SendWait(UART_Type *pUART, uint8_t *pSendBuff, uint32_t u32Length);
void UART_ReceiveWait(UART_Type *pUART, uint8_t *pReceiveBuff, uint32_t u32Length);
void UART_WaitTxComplete(UART_Type *pUART);
void UART_SetCallback(UART_CallbackType pfnCallback);
void UART0_Isr(void);
void UART1_Isr(void);
void UART2_Isr(void);


#ifdef __cplusplus
}
#endif
#endif /* #ifndef _UART_H_ */
