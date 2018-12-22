/******************************************************************************
*
* @brief  ICS 驱动头文件.  
*
******************************************************************************/
#ifndef ICS_H_
#define ICS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
/****************************************************************************!
 * @brief 时钟模式常量定义
 *
 ***************************************************************************/
enum
{
    ICS_CLK_MODE_FEI = 1,       /*!< FEI 模式 */
    ICS_CLK_MODE_FEE,           /*!< FEE 模式 */
    ICS_CLK_MODE_FEE_OSC,       /*!< FEE 模式 OSC输出时钟源选择来自EXTAL引脚的外部时钟源 */    
    ICS_CLK_MODE_FBE,           /*!< FBE 模式 */
    ICS_CLK_MODE_FBE_OSC,       /*!< FBE 模式 OSC输出时钟源选择来自EXTAL引脚的外部时钟源  */    
    ICS_CLK_MODE_FBI,           /*!< FBI 模式 */
    ICS_CLK_MODE_FBILP,         /*!< FBILP 模式 */    
    ICS_CLK_MODE_FBELP,         /*!< FBELP 模式 */        
};			
  
/*****************************************************************************//*!
   *
   * @brief 将时钟模式从当前模式切换到另一个时钟模式.
   *
   *  时钟模式宏观定义如下:
   *      FEI, FBI, FEE, FBE, FBILP, FBELP, FEE_OSC, FBE_OSC
   *   注：FEE_OSC, FBE_OSC 不能用作当前时钟模式. 当前时钟模式和要切换到的时钟模式组合如下： 
   *    < 当前时钟模式，要切换到的时钟模式>     
   *    <FEI,FEE>, <FEI,FBI>, <FEI,FBE>, <FEI,FBE_OSC>, <FEI,FEE_OSC>, <FEE,FEI>,
   *    <FEE,FBI>, <FEE,FBE>, <FBI,FBE>, <FBI,FEE>, <FBI,FBILP>, <FBI,FEI>,
   *    <FBE,FBI>, <FBE,FEE>, <FBE,FEI>, <FBE,FBELP>, <FBELP,FBE>, <FBILP,FBI>.
   *    
   * @param[in] CurMode   当前时钟模式
   * @param[in] NewMode   要切换到的时钟模式
   * @param[in] clkFreq     参考时钟频率
   *       
   * @return none
   * @warning   FEE_OSC, FBE_OSC 不能用作当前时钟模式. 
   *
   *****************************************************************************/

#define ICS_SwitchMode(CurMode, NewMode, clkFreq)   CurMode##_to_##NewMode(clkFreq)
       
 
/******************************************************************************
* 定义 OSC 配置结构体
*
*******************************************************************************/
typedef struct
{
	uint8_t bRange      : 1;        /*!< 1: 高频范围, 0: 低频范围 */
	uint8_t bGain       : 1;        /*!< 1: 高增益, 0:低增益 */
	uint8_t bEnable     : 1;        /*!< 1: 使能OSC, 0: 禁用OSC */
	uint8_t bStopEnable : 1;        /*!< 1: 停止模式下OSC使能, 0: 停止模式下OSC禁用 */
	uint8_t bIsCryst    : 1;        /*!< 1: OSC输出选择振荡器时钟, 0: OSC输出选择来自extal引脚的外部时钟 */
	uint8_t bWaitInit   : 1;        /*!< 1: 等待振荡器初始化完成, 0: 不等待 */
} OSC_ConfigType, *OSC_ConfigPtr;



/******************************************************************************
* 
* ICS配置结构体
*
*******************************************************************************/
typedef struct
{
   uint8_t    u8ClkMode;        /*!< 选择时钟模式*/
   uint8_t    bLPEnable;        /*!< 低功耗模式下使能 */
   uint32_t   u32ClkFreq;       /*!< 参考时钟频率 */  
   OSC_ConfigType  oscConfig;   /*!< OSC 配置 */
} ICS_ConfigType ;

/*****************************************************************************//*!
*
* @brief 使能中断.
*        
* @param   none
*
* @return none
* 
* @see    ICS_DisableInt
*****************************************************************************/
__STATIC_INLINE void ICS_EnableInt(void)
{
    ICS->C4 |= (ICS_C4_LOLIE_MASK);    
}

/*****************************************************************************//*!
*
* @brief 禁用中断
*        
* @param   none
*
* @return none
*
* @see    ICS_EnableInt
*****************************************************************************/
__STATIC_INLINE void ICS_DisableInt(void)
{
    ICS->C4 &= ~(ICS_C4_LOLIE_MASK);    
}

/*****************************************************************************//*!
*
* @brief 使能时钟监控
*        
* @param   none
*
* @return none
*
* @see    ICS_DisableClockMonitor
*****************************************************************************/
__STATIC_INLINE void ICS_EnableClockMonitor(void)
{
    ICS->C4 |= (ICS_C4_CME_MASK);    
}

/*****************************************************************************//*!
*
* @brief 禁用时钟监控
*        
* @param   none
*
* @return none
*
* @see    ICS_EnableClockMonitor
*****************************************************************************/
__STATIC_INLINE void ICS_DisableClockMonitor(void)
{
    ICS->C4 &= ~(ICS_C4_CME_MASK);    
}

/*****************************************************************************//*!
   *
   * @brief 设置ICS输出时钟源分频
   *        
   * @param[in] busDivide   -- 分频值
   *
   * @return  depends on commands
   *****************************************************************************/
__STATIC_INLINE void ICS_SetBusDivider(uint8_t u8BusDivide)
{
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(u8BusDivide);
}


/*****************************************************************************//*!
*
* @brief 使能OSC
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_Enable(void)
{
    OSC->CR |= (OSC_CR_OSCEN_MASK);    
}

/*****************************************************************************//*!
*
* @brief 禁用OSC
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_Disable(void)
{
    OSC->CR &= ~(OSC_CR_OSCEN_MASK);    
}

/*****************************************************************************//*!
*
* @brief 设置OSC模块的频率范围为低频范围
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetLowRange(void)
{
    OSC->CR &= ~(OSC_CR_RANGE_MASK);    
}

/*!***************************************************************************//*!
+FUNCTION----------------------------------------------------------------
*
* @brief 设置OSC模块的频率范围为高频范围
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetHighRange(void)
{
    OSC->CR |= (OSC_CR_RANGE_MASK);    
}


/*****************************************************************************//*!
*
* @brief 设置OSC的工作模式为高增益模式
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetHighGain(void)
{
    OSC->CR |= (OSC_CR_HGO_MASK);    
}

/*****************************************************************************//*!
*
* @brief 设置OSC的工作模式为低功耗模式
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetLowGain(void)
{
    OSC->CR &= ~(OSC_CR_HGO_MASK);    
}

/*****************************************************************************//*!
*
* @brief 选择OSC模块的输出时钟源为振荡器时钟源
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SelectCrystal(void)
{
    OSC->CR |= (OSC_CR_OSCOS_MASK);    
}


/*****************************************************************************//*!
*
* @brief OSC输出选择来自extal引脚的外部时钟 
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SelectClock(void)
{
    OSC->CR &= ~(OSC_CR_OSCOS_MASK);    
}

/*****************************************************************************//*!
*
* @brief 在停止模式下OSC模块使能
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_ActiveInStop(void)
{
    OSC->CR |= (OSC_CR_OSCSTEN_MASK);    
}

/*****************************************************************************//*!
*
* @brief 在停止模式下OSC模块禁用
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_InactiveInStop(void)
{
    OSC->CR &= ~(OSC_CR_OSCSTEN_MASK);    
}

/******************************************************************************/

void ICS_Init(ICS_ConfigType *pConfig);
void ICS_DeInit(void);
void ICS_SetClkDivider(uint32_t u32ClkFreqKHz);
void ICS_Trim(uint16 u16TrimValue);
void OSC_Init(OSC_ConfigType *pConfig);
void OSC_DeInit(void);

/************** 内联函数 ******************/
void ICS_DisableClockMonitor(void);
void ICS_DisableInt(void);
void ICS_EnableClockMonitor(void);
void ICS_EnableInt(void);
void ICS_SetBusDivider(uint8_t u8BusDivide);
void OSC_ActiveInStop(void);
void OSC_Enable(void);
void OSC_Disable(void);
void OSC_InactiveInStop(void);
void OSC_SelectClock(void);
void OSC_SelectCrystal(void);
void OSC_SetHighGain(void);
void OSC_SetHighRange(void);
void OSC_SetLowGain(void);
void OSC_SetLowRange(void);

/* do not touch the following functions */
void FEI_to_FEE(ICS_ConfigType *pConfig);
void FEI_to_FBI(ICS_ConfigType *pConfig);
void FEI_to_FBE(ICS_ConfigType *pConfig);
void FEE_to_FBI(ICS_ConfigType *pConfig);
void FEE_to_FEI(ICS_ConfigType *pConfig);
void FEE_to_FBE(ICS_ConfigType *pConfig);
void FBE_to_FEE(ICS_ConfigType *pConfig);
void FBE_to_FEI(ICS_ConfigType *pConfig);
void FBE_to_FBI(ICS_ConfigType *pConfig);
void FBE_to_FBELP(ICS_ConfigType *pConfig);
void FBI_to_FEI(ICS_ConfigType *pConfig);
void FBI_to_FBE(ICS_ConfigType *pConfig);
void FBI_to_FEE(ICS_ConfigType *pConfig);
void FBI_to_FBILP(ICS_ConfigType *pConfig);
void FBILP_to_FBI(ICS_ConfigType *pConfig);
void FBELP_to_FBE(ICS_ConfigType *pConfig);
void FEI_to_FBE_OSC(ICS_ConfigType *pConfig);
void FEI_to_FEE_OSC(ICS_ConfigType *pConfig);
#ifdef __cplusplus
}
#endif
#endif 
