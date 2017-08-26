/******************************************************************************
*
* @brief  PIT 驱动头文件.  
*
******************************************************************************/
#ifndef PIT_H_
#define PIT_H_
#include"common.h"
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
* PIT 通道号列表
*
*//*!
*******************************************************************************/
enum
{
    PIT_CHANNEL0 = 0,       /*!< PIT 通道 0 */
    PIT_CHANNEL1            /*!< PIT 通道 1 */
};

/*!                                                                           */


/*!
 * @brief PIT 回调类型.
 *
 */

typedef void (*PIT_CallbackType)(void);            





/* PIT 配置结构体体
 */  
/*!
 * @brief PIT 配置参数.
 *
 */
typedef struct
{   
    uint8_t bFreeze         : 1;    /*!< 1: 在调试模式时冻结, 0: 在调试模式时仍然运行 */
    uint8_t bModuleDis      : 1;    /*!< 1: 禁用PIT模块, 0: 使能PIT模块 */    
    uint8_t bReserved0      : 1;    /*!< 保留 */ 
    uint8_t bReserved1      : 5;    /*!< 保留 */ 
    uint8_t bETMerEn        : 1;    /*!< 1: 使能PIT通道, 0: 禁止PIT通道 */ 
    uint8_t bInterruptEn    : 1;    /*!< 1: 使能PIT通道中断, 0: 禁止PIT通道中断 */ 
    uint8_t bChainMode      : 1;    /*!< 1: 使能链模式, 0: 禁止链模式 */ 
    uint8_t bReserved2      : 5;    /*!< 保留 */ 
    uint8_t bFlag           : 1;    /*!< 1: PIT中断标志位置位,写1清0, 0: PIT中断标志位没有置位 */
    uint8_t bReserved3      : 7;    /*!< 保留 */   
    uint32_t u32LoadValue      ;    /*!< 32位通道加载模值 */  
} PIT_ConfigType, *PIT_ConfigPtr; 


/******************************************************************************
******************************************************************************/

/*!
 * 内联函数
 */
/*****************************************************************************//*!
*
* @brief 使能PIT模块.
*        
* @param none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_Enable(void)
{

    PIT->MCR &= ~PIT_MCR_MDIS_MASK; 
    
}

/*****************************************************************************//*!
*
* @brief 禁用PIT模块.
*        
* @param none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_Disable(void)
{

    PIT->MCR |= PIT_MCR_MDIS_MASK; 
}


/*****************************************************************************//*!
*
* @brief 设置PIT在调试模式下禁止运行.
*        
* @param none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_SetDebugFreeze(void)
{

    PIT->MCR |= PIT_MCR_FRZ_MASK;
}


/*****************************************************************************//*!
*
* @brief 设置PIT在调试模式下继续运行.
*        
* @param none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_SetDebugOn(void)
{

    PIT->MCR &= ~PIT_MCR_FRZ_MASK;
}


/*****************************************************************************//*!
*
* @brief PIT定时器通道使能.
*        
* @param[in]   u8Channel   通道号.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_ChannelEnable(uint8_t u8Channel)

{

    PIT->CHANNEL[u8Channel].TCTRL |= PIT_TCTRL_TEN_MASK; 
}


/*****************************************************************************//*!
*
* @brief 禁用PIT定时器通道.
*        
* @param[in]   u8Channel   通道号.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_ChannelDisable(uint8_t u8Channel)
{

    PIT->CHANNEL[u8Channel].TCTRL &= ~PIT_TCTRL_TEN_MASK; 
}


/*****************************************************************************//*!
*
* @brief 使能PIT定时器通道中断.
*        
* @param[in]   u8Channel   通道号.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_ChannelEnableInt(uint8_t u8Channel)

{

    PIT->CHANNEL[u8Channel].TCTRL |= PIT_TCTRL_TIE_MASK; 
}


/*****************************************************************************//*!
*
* @brief 禁用PIT定时器通道中断.
*        
* @param[in]   u8Channel   通道号.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_ChannelDisableInt(uint8_t u8Channel)

{

    PIT->CHANNEL[u8Channel].TCTRL &= ~PIT_TCTRL_TIE_MASK; 
}


/*****************************************************************************//*!
*
* @brief 使能PIT定时器通道链模式.
*        
* @param[in]   u8Channel   通道号.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_ChannelEnableChain(uint8_t u8Channel)
{
    PIT->CHANNEL[u8Channel].TCTRL |= PIT_TCTRL_CHN_MASK;
}


/*****************************************************************************//*!
*
* @brief 禁用PIT定时器通道链模式.
*        
* @param[in]   u8Channel   通道号.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_ChannelDisableChain(uint8_t u8Channel)

{
    PIT->CHANNEL[u8Channel].TCTRL &= ~PIT_TCTRL_CHN_MASK;
}


/*****************************************************************************//*!
*
* @brief 获取PIT通道中断标志位.
*        
* @param[in]   u8Channel   通道号.
*
* @return PIT通道中断标志位.
*
*****************************************************************************/
__STATIC_INLINE uint8_t PIT_ChannelGetFlags(uint8_t u8Channel)

{
    uint8_t bflag;  
    
    bflag = (PIT->CHANNEL[u8Channel].TFLG & PIT_TFLG_TIF_MASK);    
    
    return bflag;
    
}


/*****************************************************************************//*!
*
* @brief 清除PIT通道中断标志位.
*        
* @param[in]   u8Channel   通道号.
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void PIT_ChannelClrFlags(uint8_t u8Channel)
{
    PIT->CHANNEL[u8Channel].TFLG |= PIT_TFLG_TIF_MASK;       
}


/******************************************************************************
******************************************************************************/
void PIT_Init(uint8_t u8Channel_No, PIT_ConfigType *pConfig);
void PIT_SetLoadVal(uint8_t u8Channel, uint32_t u32loadvalue);
void PIT_SetCallback(uint8_t u8Channel_No, PIT_CallbackType pfnCallback);
void PIT_DeInit(void);
                                          
#ifdef __cplusplus
}
#endif
#endif /* PIT_H_ */
