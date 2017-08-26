/******************************************************************************
*
* @brief  RTC 驱动头文件.  
*
******************************************************************************/
#ifndef RTC_H_
#define RTC_H_
#ifdef __cplusplus
extern "C" {
#endif
	
#include "common.h"
/******************************************************************************
* RTC控制位定义
*
*//*! 
* @{
*******************************************************************************/

#define RTC_OUTPUT_ENABLE           1	/*!< 使能RTC输出引脚  */ 
#define RTC_INTERRUPT_ENABLE        1	/*!< 使能RTC中断  */ 
#define RTC_CLKSRC_EXTERNAL         0	/*!< 选择外部时钟作为RTC时钟源  */
#define RTC_CLKSRC_1KHZ             1	/*!< 选择LPO时钟作为RTC时钟源  */
#define RTC_CLKSRC_IREF             2	/*!< 选择内部参考时钟ICSIRCLK作为RTC时钟源  */
#define RTC_CLKSRC_BUS              3	/*!< 选择总线时钟作为RTC时钟源  */
#define RTC_CLK_PRESCALER_128       1	/*!< 根据RTCLKS位选择是1还是128分频 */
#define RTC_CLK_PRESCALER_256       2	/*!< 根据RTCLKS位选择是2还是256分频 */
#define RTC_CLK_PRESCALER_512       3	/*!< 根据RTCLKS位选择是4还是512分频 */
#define RTC_CLK_PRESCALER_1024      4	/*!< 根据RTCLKS位选择是8还是1024分频 */
#define RTC_CLK_PRESCALER_2048      5	/*!< 根据RTCLKS位选择是16还是2048分频 */
#define RTC_CLK_PRESCALER_100       6	/*!< 根据RTCLKS位选择是32还是100分频 */
#define RTC_CLK_PRESCALER_1000      7	/*!< 根据RTCLKS位选择是64还是1000分频 */


/*! @}                                                                        */


/*!
 * @brief RTC 回调类型.
 *
 */

typedef void (*RTC_CallbackType)(void);



/* RTC 配置结构体体
 */  
/*!
 * @brief RTC 配置参数.
 *
 */
typedef struct
{   
    uint16_t bReserved                  : 4;    /*!< 保留 */     
    uint16_t bRTCOut                    : 1;    /*!< 1: 使能RTC输出, 0: 禁止RTC输出 */
    uint16_t bReserved1                 : 1;    /*!< 保留 */ 
    uint16_t bInterruptEn               : 1;    /*!< 1: 使能RTC中断, 0: RTC 禁止RTC中断 */
    uint16_t bFlag                      : 1;    /*!< 1: RTC实时中断标志 */   
    uint16_t bClockPresaler             : 3;    /*!< 3: RTC分频系数选择 */    
    uint16_t bReserved2                 : 3;    /*!< 保留*/ 
    uint16_t bClockSource               : 2;    /*!< 2:RTC时钟源选择 */
    uint16_t u16ModuloValue                ;    /*!< 16位RTC模值 */
} RTC_ConfigType, *RTC_ConfigPtr; 


/******************************************************************************
******************************************************************************/

/*!
 * 内联函数
 */
/*****************************************************************************//*!
*
* @brief 使能RTC中断.
*        
* @param none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void RTC_EnableInt(void)
{
    RTC->SC |= RTC_SC_RTIE_MASK;
}

/*****************************************************************************//*!
*
* @brief 禁止RTC中断.
*        
* @param none
*
* @return non
*
*****************************************************************************/
__STATIC_INLINE void RTC_DisableInt(void)
{
    RTC->SC &= ~RTC_SC_RTIE_MASK;
}

/*****************************************************************************//*!
*
* @brief 设置16位RTC模值.
*        
* @param[in]   u16Mod_Value   16位模值
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void RTC_SetModulo(uint16_t u16Mod_Value)
{
 
    RTC->MOD = u16Mod_Value;
}

/*****************************************************************************//*!
*
* @brief 设置RTC时钟以及分频系数.
*        
* @param[in]   u16Clock_Number   选择时钟源
* @param[in]   u16Presalcer      分频系数
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void RTC_SetClock(uint16_t u16Clock_Number, uint16_t u16Presalcer)
{
    uint32_t u32rtc_sc;
        
    u32rtc_sc  = RTC->SC; 
    u32rtc_sc &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
    u32rtc_sc |= RTC_SC_RTCLKS(u16Clock_Number) | RTC_SC_RTCPS(u16Presalcer); 
    RTC->SC   = u32rtc_sc;
}

/*****************************************************************************//*!
*
* @brief 获取RTC中断标志位.
*        
* @param none 
*
* @return RTC中断标志位.
*
*****************************************************************************/
__STATIC_INLINE uint8_t RTC_GetFlags(void)
{
  uint8_t bflag;
  
  bflag = RTC->SC & RTC_SC_RTIF_MASK; 
  
  return bflag;  
}


/*****************************************************************************//*!
*
* @brief 清除RTC中断标志位.
*        
* @param none 
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void RTC_ClrFlags(void)
{
    RTC->SC |= RTC_SC_RTIF_MASK; 
}


/******************************************************************************
******************************************************************************/


void RTC_Init(RTC_ConfigType *pConfig);
void RTC_SetCallback(RTC_CallbackType pfnCallback);
void RTC_DeInit(void);


#ifdef __cplusplus
}
#endif
#endif /* RTC_H_ */
