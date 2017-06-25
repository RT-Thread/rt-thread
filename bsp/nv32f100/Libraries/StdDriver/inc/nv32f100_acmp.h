/******************************************************************************
*
* @brief  ACMP 驱动头文件.  
*
******************************************************************************/
#ifndef _MY_ACMP_H_
#define _MY_ACMP_H_
#ifdef __cplusplus
extern "C" {
#endif
	
#include "common.h"
/* 选择DAC基准 */
enum
{
    DAC_REF_BANDGAP = 0,
    DAC_REF_VDDA
};

/******************************************************************************
 * ACMP 模块数定义                                             
 ******************************************************************************/
#define     MAX_ACMP_NO             2

/******************************************************************************* 
*
* 定义ACMP 正输入和负输入引脚
*
*******************************************************************************/
#define     ACMP_INPUT_P_EXT0       (0<<4)  /*!< ACMP正输入选择外部基准0 */
#define     ACMP_INPUT_P_EXT1       (1<<4)  /*!< ACMP正输入选择外部基准1 */
#define     ACMP_INPUT_P_EXT2       (2<<4)  /*!< ACMP正输入选择外部基准2 */
#define     ACMP_INPUT_P_DAC        (3<<4)  /*!< ACMP正输入选择DAC输出 */
#define     ACMP_INPUT_N_EXT0       0       /*!< ACMP负输入选择外部基准0 */
#define     ACMP_INPUT_N_EXT1       1       /*!< ACMP负输入选择外部基准1 */
#define     ACMP_INPUT_N_EXT2       2       /*!< ACMP负输入选择外部基准2 */
#define     ACMP_INPUT_N_DAC        3       /*!< ACMP负输入选择DAC输出 */

/******************************************************************************
*
* 定义ACMP中断触发器的触发模式
*
*******************************************************************************/
#define     ACMP_SENSITIVITYMODE_FALLING   0    /*!< ACMP中断在输出下降沿发生  */
#define     ACMP_SENSITIVITYMODE_RISING    1    /*!< ACMP中断在输出上升沿发生  */
#define     ACMP_SENSITIVITYMODE_ANY       3    /*!< ACMP中断在输出上升沿或下降沿触发 */ 

/******************************************************************************
*
* 定义ACMP 迟滞
*
*******************************************************************************/
#define     ACMP_HYST_20MV                 (0<<6)  /*!< 20mv */
#define     ACMP_HYST_30MV                 (1<<6)  /*!< 30mv */

/******************************************************************************
*
* 定义内部DAC参考基准
*
*******************************************************************************/
#define     ACMP_DAC_REFERENCE_BANDGAP     (0<<6)  /*!< 选择带隙为基准 */
#define     ACMP_DAC_REFERENCE_VDDA        (1<<6)  /*!< 选择VDDA为基准 */

/******************************************************************************
*
* ACMP回调函数声明
*
******************************************************************************/
typedef void (*ACMP_CallbackPtr)(void);

/******************************************************************************
*
* ACMP 控制和状态字寄存器结构体
*
*******************************************************************************/
typedef union 
{
    uint8_t byte;    				 /*!<联合体类型-字节*/
    struct 
    {
        uint8_t bMod        : 2;     /*!< 中断触发模式 */
        uint8_t bOutEn      : 1;     /*!< ACMP输出置于外部引脚 */
        uint8_t bOutState   : 1;     /*!< 模拟比较强输出的当前值 */
        uint8_t bIntEn      : 1;     /*!< 使能ACMP中断 */
        uint8_t bIntFlag    : 1;     /*!< ACMP 中断标志位 */
        uint8_t bHyst       : 1;     /*!< 选择ACMP迟滞 */
        uint8_t bEn         : 1;     /*!< 使能ACMP模块 */
    }bits;      				     /*!< 联合体类型-位域 */
}ACMP_CtrlStatusType, *ACMP_CtrlStatusPtr;  /*!< ACMP 控制和状态寄存器结构*/

/******************************************************************************
*
* ACMP 外部输入引脚控制结构体
*
*******************************************************************************/
typedef union 
{
    uint8_t byte;    				 /*!<联合体类型-字节*/
    struct 
    {
        uint8_t bNegPin  : 2;        /*!< 负输入选择*/
        uint8_t          : 2;
        uint8_t bPosPin  : 2;        /*!< 正输入选择 */
        uint8_t          : 2;
    }bits;      				     /*!< 联合体类型-位域 */
}ACMP_PinSelType, *ACMP_PinSelPtr; 	     /*!< ACMP 输入选择结构体 */ 

/******************************************************************************
*
* ACMP 内部DAC控制结构体
*
*******************************************************************************/
typedef union 
{
    uint8_t byte;    					 /*!<联合体类型-字节*/
    struct 
    {
        uint8_t bVal  : 6;           /*!< DAC输出电平选择*/
        uint8_t bRef  : 1;           /*!< DAC基准选择 */
        uint8_t bEn   : 1;           /*!< DAC使能 */
    }bits;      				     /*!< 联合体类型-位域 */
}ACMP_DACType, *ACMP_DACPtr;	     /*!< ACMP DAC 控制结构体 */ 

/******************************************************************************
*
* ACMP 外部输入引脚使能控制结构体
*
*******************************************************************************/
typedef union 
{
    uint8_t byte;    				 /*!<联合体类型-字节*/
	  struct 
    {
        uint8_t bEn   : 3;           /*!< ACMP 外部输入引脚使能 */
        uint8_t bRsvd : 5;
    }bits;      				    /*!< 联合体类型-位域 */
}ACMP_PinEnType, *ACMP_PinEnPtr;	 /*!< ACMP 引脚使能结构体 */ 

/******************************************************************************
*
* ACMP 模块配置结构体
*
*******************************************************************************/
typedef struct 
{
    ACMP_CtrlStatusType  sCtrlStatus;     /*!< ACMP 控制和状体 */
    ACMP_PinSelType      sPinSelect;      /*!< ACMP 输入选择 */
    ACMP_DACType         sDacSet;         /*!< ACMP 内部DAC控制 */
    ACMP_PinEnType       sPinEnable;      /*!< ACMP 外部输入引脚使能控制 */
}ACMP_ConfigType, *ACMP_ConfigPtr;

/*****************************************************************************//*!
*
* @brief  使能ACMP模块
*        
* @param[in]  pACMPx     指向ACMP模块
*              
* @return none.
*
* @see    ACMP_Disable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_Enable(ACMP_Type *pACMPx)
{
    pACMPx->CS |= ACMP_CS_ACE_MASK;
}

/*****************************************************************************//*!
*
* @brief  禁用ACMP模块
*        
* @param[in]  pACMPx     指向ACMP模块
*              
* @return none.
*
* @see    ACMP_Enable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_Disable(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACE_MASK;
}

/*****************************************************************************//*!
*
* @brief  选择ACMP中断触发器的触发模式.
*        
* @param[in]  pACMPx         指向ACMP模块
* @param[in]  u8EdgeSelect   上升沿或下降沿选择, 0~3. 
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_SelectIntMode(ACMP_Type *pACMPx, uint8_t u8EdgeSelect)
{
    pACMPx->CS &= ~ACMP_CS_ACMOD_MASK;
    pACMPx->CS |= ACMP_CS_ACMOD(u8EdgeSelect & 0x3);
}

/*****************************************************************************//*!
*
* @brief  使能ACMP输出置于外部引脚上
*        
* @param[in]  pACMPx     指向ACMP模块
*              
* @return none.
*
* @see    ACMP_DisablePinOut.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_EnablePinOut(ACMP_Type *pACMPx)
{
    pACMPx->CS |= ACMP_CS_ACOPE_MASK;
}

/*****************************************************************************//*!
*
* @brief  禁用ACMP输出置于外部引脚上
*        
* @param[in]  pACMPx    指向ACMP模块
*              
* @return none.
*
* @see    ACMP_EnablePinOut.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DisablePinOut(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACOPE_MASK;
}

/*****************************************************************************//*!
*
* @brief  选择ACMP迟滞 
*        
* @param[in]  pACMPx           指向ACMP模块.
* @param[in]  u8HystSelect     2mv or 30mv.   
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_SelectHyst(ACMP_Type *pACMPx, uint8_t u8HystSelect)
{
    pACMPx->CS &= ~ACMP_CS_HYST_MASK;
    pACMPx->CS |= u8HystSelect;
}

/*****************************************************************************//*!
*
* @brief  使能ACMP模块中断
*        
* @param[in]  pACMPx      指向ACMP模块.
*              
* @return none.
*
*
* @see    ACMP_DisableInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_EnableInterrupt(ACMP_Type *pACMPx)
{
    pACMPx->CS |= ACMP_CS_ACIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  禁用ACMP模块中断
*        
* @param[in]  pACMPx     指向ACMP模块
*              
* @return none.
*
* @see    ACMP_EnableInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DisableInterrupt(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  读取中断标志位
*        
* @param[in]  pACMPx      指向ACMP模块.
*              
* @return none.
*
* @see    ACMP_ClrFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t ACMP_GetFlag(ACMP_Type *pACMPx)
{
    return (pACMPx->CS & ACMP_CS_ACF_MASK);
}

/*****************************************************************************//*!
*
* @brief  清除中断标志位
*        
* @param[in]  pACMPx      指向ACMP模块
*              
* @return none.
*
* @see    ACMP_GetFlag.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_ClrFlag(ACMP_Type *pACMPx)
{
    pACMPx->CS &= ~ACMP_CS_ACF_MASK;
}

/*****************************************************************************//*!
*
* @brief  ACMP正输入选择
*        
* @param[in]  pACMPx        指向ACMP模块
* @param[in]  u8PosPinSel   正输入选择, 外部基准0~2 或DAC输出.     
*
* @return none.
*
* @see    ACMP_NegativeInputSelect.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_PositiveInputSelect(ACMP_Type *pACMPx, uint8_t u8PosPinSel)
{
    pACMPx->C0 &= ~ACMP_C0_ACPSEL_MASK;
    pACMPx->C0 |= u8PosPinSel;
}

/*****************************************************************************//*!
*
* @brief ACMP负输入选择.
*         
* @param[in]  pACMPx       指向ACMP模块
* @param[in]  u8NegPinSel   负输入选择,  外部基准0~2 或DAC输出.     
*
* @return none.
*
* @see    ACMP_PositiveInputSelect.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_NegativeInputSelect(ACMP_Type *pACMPx, uint8_t u8NegPinSel)
{
    pACMPx->C0 &= ~ACMP_C0_ACNSEL_MASK;
    pACMPx->C0 |= u8NegPinSel;
}

/*****************************************************************************//*!
*
* @brief  使能内部DAC
*        
* @param[in]  pACMPx     指向ACMP模块
*              
* @return none.
*
* @see    ACMP_DacDisable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacEnable(ACMP_Type *pACMPx)
{
    pACMPx->C1 |= ACMP_C1_DACEN_MASK;
}

/*****************************************************************************//*!
*
* @brief 禁用内部DAC
*        
* @param[in]  pACMPx     指向ACMP模块.
*              
* @return none.
*
* @see    ACMP_DacEnable.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacDisable(ACMP_Type *pACMPx)
{
    pACMPx->C1 &= ~ACMP_C1_DACEN_MASK;
}

/*****************************************************************************//*!
*
* @brief  DAC基准选择
*        
* @param[in]  pACMPx        指向ACMP模块.
* @param[in]  u8RefSelect   DAC参考选择: 带隙 or VDDA.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacReferenceSelect(ACMP_Type *pACMPx, uint8_t u8RefSelect)
{
    pACMPx->C1 &= ~ACMP_C1_DACREF_MASK;
    pACMPx->C1 |= u8RefSelect;
}

/*****************************************************************************//*!
*
* @brief  DAC输出电平选择
*        
* @param[in]  pACMPx        指向ACMP模块.
* @param[in]  u8DacValue    DAC输出选择, Voutput= (Vin/64)x(DACVAL[5:0]+1).
*
* @return none.
*
*
*****************************************************************************/
__STATIC_INLINE void ACMP_DacOutputSet(ACMP_Type *pACMPx, uint8_t u8DacValue)
{
    ASSERT(!(u8DacValue & (~ACMP_C1_DACVAL_MASK)));
    pACMPx->C1 &= ~ACMP_C1_DACVAL_MASK;
    pACMPx->C1 |= ACMP_C1_DACVAL(u8DacValue);
}

/*****************************************************************************//*!
*
* @brief  使能ACMP外部输入引脚.
*        
* @param[in]  pACMPx        指向ACMP模块.
* @param[in]  u8InputPin    ACMP 外部输入引脚, 0~2.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_InputPinEnable(ACMP_Type *pACMPx, uint8_t u8InputPin)
{
    ASSERT(!(u8InputPin & (~ACMP_C2_ACIPE_MASK)));
    pACMPx->C2 |= ACMP_C2_ACIPE(u8InputPin);
}

/*****************************************************************************//*!
*
* @brief  禁用ACMP外部输入引脚.
*        
* @param[in]  pACMPx        指向ACMP模块.
* @param[in]  u8InputPin    ACMP 外部输入引脚, 0~2.
*
* @return none.
*
*****************************************************************************/
__STATIC_INLINE void ACMP_InputPinDisable(ACMP_Type *pACMPx, uint8_t u8InputPin)
{
    ASSERT(!(u8InputPin & (~ACMP_C2_ACIPE_MASK)));
    pACMPx->C2 &= ~ACMP_C2_ACIPE(u8InputPin);
}

/******************************************************************************/
void ACMP_Init(ACMP_Type *pACMPx, ACMP_ConfigType *pConfig);
void ACMP_DeInit(ACMP_Type *pACMPx); 
void ACMP_ConfigDAC(ACMP_Type *pACMPx, ACMP_DACType *pDACConfig);
void ACMP_SetCallback(ACMP_Type *pACMPx, ACMP_CallbackPtr pfnCallback);
#ifdef __cplusplus
}
#endif
#endif 
