/******************************************************************************
*
* @brief  WDG 驱动头文件.  
*
******************************************************************************/

#ifndef __WDOG_H__
#define __WDOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "nv32f100_sim.h"
/*****************************************************************************/
/******************************************************************************
* 定义WDG时钟源
*
*//*! @WDG时钟源
* @{
*******************************************************************************/

#define WDOG_CLK_BUS                    0   /*!< 总线时钟 */
#define WDOG_CLK_INTERNAL_32KHZ         2   /*!< 内部 32 kHz (ICSIRCLK) */
#define WDOG_CLK_INTERNAL_1KHZ	        1   /*!< 内部 LPO 1 KHz */
#define WDOG_CLK_EXTERNAL               3   /*!< 外部时钟  */
/*! @}                                					*/

/* 看门狗时钟源选择 */
#define WDOG_CLK  (WDOG_CLK_INTERNAL_1KHZ)
    
/* 看门狗寄存器默认值设置 */
#define WDOG_CS1_DEFAULT_VALUE      0x80
#define WDOG_CS2_DEFAULT_VALUE      0x01
#define WDOG_TOVAL_DEFAULT_VALUE    0x0400
#define WDOG_WIN_DEFAULT_VALUE      0x0000
     

/*! 
 * @brief 看门狗解锁.
 */
#define WDOG_Unlock()        WDOG->CNT = 0x20C5; WDOG->CNT = 0x28D9        
//#define WDOG_Unlock()       DisableInterrupts; WDOG->CNT = 0x20C5; WDOG->CNT = 0x28D9; EnableInterrupts        
/*! @}                            					*/

/******************************************************************************
* define 看门狗配置结构体
*
*//*! @看门狗配置结构体
* @{
*******************************************************************************/
typedef struct {	
    struct {
	uint16_t    bIntEnable      : 1;    /*!< 看门狗中断使能 */
	uint16_t    bDisable        : 1;    /*!< 禁用看门狗 */
	uint16_t    bWaitEnable     : 1;    /*!< 使能看门狗等待模式 */
	uint16_t    bStopEnable     : 1;    /*!< 使能看门狗停止模式 */
	uint16_t    bDbgEnable      : 1;    /*!< 使能看门狗调试模式 */
	uint16_t    bWinEnable      : 1;    /*!< 使能看门狗窗口模式 */
	uint16_t    bUpdateEnable   : 1;    /*!< 使能允许看门狗更新 */
	uint16_t    bClkSrc         : 2;    /*!< 看门狗时钟源选择 */  
	uint16_t    bPrescaler      : 1;    /*!< 预分频系数 */  
    }sBits;                             /*!< 位域结构体  */
    uint16_t    u16ETMeOut;             /*!< 看门狗超时值 */
    uint16_t    u16WinETMe;             /*!< 看门狗窗口值 */
} WDOG_ConfigType, *WDOG_ConfigPtr;  /*!< 看门狗配置结构体类型 */
/*! @}                               					*/

/******************************************************************************
******************************************************************************/

/*!
 * 内联函数
 */

/*****************************************************************************//*!
*
* @brief 设置看门狗超时值.
*        
* @param[in]   u16ETMeOut    超时值.
*
* @return none
*
*****************************************************************************/

__STATIC_INLINE void WDOG_SetETMeOut(uint16_t u16ETMeOut)
{
    WDOG->CNT = 0x20C5; 
    WDOG->CNT = 0x28D9;
    WDOG->TOVAL8B.TOVALL  = u16ETMeOut;
    WDOG->TOVAL8B.TOVALH  = u16ETMeOut >> 8;
}


/*****************************************************************************//*!
*
* @brief 设置看门狗窗口.
*        
* @param[in]   u16WinETMe    看门狗窗口值.
*
* @return none
*
*****************************************************************************/

__STATIC_INLINE void WDOG_SetWindow(uint16_t u16WinETMe)
{
    WDOG->CNT = 0x20C5; 
    WDOG->CNT = 0x28D9;
    WDOG->WIN8B.WINL  = u16WinETMe;
    WDOG->WIN8B.WINH  = u16WinETMe >> 8;
}

/*****************************************************************************//*!
*
* @brief 检查看门狗是否复位.
*        
* @param    none.
*
* @return   TRUE 当看门狗复位发生, FALSE 无.
*
*****************************************************************************/

__STATIC_INLINE uint8_t WDOG_IsReset(void)
{
    if(SIM_GetStatus(SIM_SRSID_WDOG_MASK))
    {
        return (TRUE);
    }
    return (FALSE);
}

/*! @}                                       					*/


void WDOG_Init(WDOG_ConfigPtr pConfig);
void WDOG_DeInit(void);
void WDOG_Disable(void);
void WDOG_DisableWDOGEnableUpdate(void);
void WDOG_Enable(void);
void WDOG_Feed(void);
void WDOG_SetETMeOut(uint16_t u16ETMeOut);
void WDOG_SetWindow(uint16_t u16WinETMe);
void WDOG_EnableUpdate(void);
void WDOG_DisableUpdate(void);
uint8_t WDOG_IsReset(void);

#ifdef __cplusplus
}
#endif

/********************************************************************/
#endif /* __WDOG_H__ */

