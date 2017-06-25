/******************************************************************************
*
* @brief  KBI 驱动头文件.  
*
******************************************************************************/
#ifndef _KBI_H_
#define _KBI_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
/********************************************************!
*
* @brief KBI模块中断输入信号检测模式选择
*
***********************************************************/
typedef enum
{
    KBI_MODE_EDGE_ONLY = 0,             /*!< 选择  边沿检测  */         
    KBI_MODE_EDGE_LEVEL                 /*!< 选择  边沿和电平检测*/
}KBI_ModeType;


typedef enum
{
    KBI_FALLING_EDGE_LOW_LEVEL = 0,     /*!< 选择 下降沿或低电平 */
    KBI_RISING_EDGE_HIGH_LEVEL          /*!< 选择 上升沿或高电平 */
}KBI_EdgeType;


/******************************************************************************
* 
* 定义KBI模块个数和中断输入引脚个数
*
*******************************************************************************/
#define KBI_MAX_NO              2                  /*!< KBI模块个数 */

#if defined(CPU_NV32)|| defined(CPU_NV32M3)
   #define KBI_MAX_PINS_PER_PORT   8                  /*!< KBI中断输入引脚个数 */
#elif defined(CPU_NV32M4)
   #define KBI_MAX_PINS_PER_PORT   32                  /*!< KBI中断输入引脚个数 */
#endif


/******************************************************************************
* KBI回调函数声明
******************************************************************************/
typedef void (*KBI_CallbackType)(void);                     




/******************************************************************************
* 
* KBI引脚配置结构体
*
*******************************************************************************/

typedef struct
{
    uint8_t     bEdge   : 1;                                /*!< 边沿/电平选择为*/
    uint8_t     bEn     : 1;                                /*!< 引脚使能位*/
    uint8_t     bRsvd   : 6;                                /*!< 保留 */
} KBI_PinConfigType;

/******************************************************************************
*
* KBI配置结构体
*
*******************************************************************************/
/*!
 * @brief KBI状态和控制寄存器结构体.
 *
 */

typedef struct
{
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
    struct
    {
        uint8_t     bMode   : 1;                            /*!< 选择KBI检测模式 */
        uint8_t     bIntEn  : 1;                            /*!< 使能KBI中断位 */
        uint8_t     bRsvd   : 6;                            /*!< 保留 */
    } sBits;
#elif  defined(CPU_NV32M4)
    struct
    {
        uint32_t     bMode   : 1;                          /*!< 选择KBI检测模式 */
        uint32_t     bIntEn  : 1;                          /*!< 使能KBI中断位 */
        uint32_t     bRsvd2  : 2;                          /*!< 保留 */
        uint32_t     bKbspEn : 1;							            /*!<Real KBI_SP register enable*/
		uint32_t     bRstKbsp: 1;                             /*!<Reset KBI_SP register*/
        uint32_t     bRsvd26 : 26;                        /*!< reserved */
    } sBits;
#endif
    KBI_PinConfigType   sPin[KBI_MAX_PINS_PER_PORT];
} KBI_ConfigType, *KBI_ConfigTypePtr;


/*****************************************************************************//*!
*
* @brief 设置仅下降沿检测.
*        
* @param[in]   pKBI          指向KBI模块.
* @param[in]   PinMasks      KBI中断输入引脚号.
*
* @return none.
*
* @see KBI_DetectRisingEdge.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectFallingEdge(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectFallingEdge(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC &= ~KBI_SC_KBMOD_MASK;
    pKBI->ES &= ~(PinMasks);
}

/*****************************************************************************//*!
*
* @brief 设置仅高电平检测
*        
* @param[in]   pKBI          指向KBI模块.
* @param[in]   PinMasks      KBI中断输入引脚号.
*
* @return none.
*
* @see KBI_DetectFallingEdge.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectRisingEdge(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectRisingEdge(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC &= ~KBI_SC_KBMOD_MASK;
    pKBI->ES |= (PinMasks);    
}

/*****************************************************************************//*!
*
* @brief 设置上升沿和高电平检测
*        
* @param[in]   pKBI          指向KBI模块.
* @param[in]   PinMasks      KBI中断输入引脚号.
*
* @return none.
*
* @see KBI_DetectFallingEdgeLowLevel.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectRisingEdgeHighLevel(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectRisingEdgeHighLevel(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC |= KBI_SC_KBMOD_MASK;
    pKBI->ES |= (PinMasks);    
}

/*****************************************************************************//*!
*
* @brief 设置下降沿和低电平检测
*        
* @param[in]   pKBI          指向KBI模块.
* @param[in]   PinMasks      KBI中断输入引脚号.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_DetectRisingEdgeHighLevel.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_DetectFallingEdgeLowLevel(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_DetectFallingEdgeLowLevel(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->SC |= KBI_SC_KBMOD_MASK;
    pKBI->ES &= ~(PinMasks);        
}

/*****************************************************************************//*!
*
* @brief 使能KBI中断输入引脚
*        
* @param[in]   pKBI          指向KBI模块..
* @param[in]   PinMasks      KBI中断输入引脚号.
*
* @return none.
*
* @see KBI_Disable.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_Enable(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_Enable(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->PE |= (PinMasks);        
}

/*****************************************************************************//*!
*
* @brief 禁用KBI中断输入引脚.
*        
* @param[in]   pKBI         指向KBI模块..
* @param[in]   PinMasks     KBI中断输入引脚号.
*
* @return none.
*
* @see KBI_Enable.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  void KBI_Disable(KBI_Type *pKBI, uint8_t PinMasks)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  void KBI_Disable(KBI_Type *pKBI, uint32_t PinMasks)
#endif
{
    pKBI->PE &= ~(PinMasks);        
}

/*****************************************************************************//*!
*
* @brief 使能KBI中断
*        
* @param[in]   pKBI          指向KBI模块..
*          
* @return none.
*
*
* @see KBI_DisableInt.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_EnableInt(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_KBIE_MASK;        
}


/*****************************************************************************//*!
*
* @brief 禁用KBI中断
*        
* @param[in]  pKBI          指向KBI模块.
*          
* @return none.
*
*
* @see KBI_EnableInt.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_DisableInt(KBI_Type *pKBI)
{
    pKBI->SC &= ~KBI_SC_KBIE_MASK;        
}

/*****************************************************************************//*!
*
* @brief 获取中断标志位
*        
* @param[in]   pKBI         指向KBI模块.
*          
* @return uint8_t.
*
* @see KBI_ClrFlags.
*
*****************************************************************************/
#if defined(CPU_NV32)|| defined(CPU_NV32M3)
__STATIC_INLINE  uint8_t KBI_GetFlags(KBI_Type *pKBI)
#elif defined(CPU_NV32M4)
__STATIC_INLINE  uint32_t KBI_GetFlags(KBI_Type *pKBI)
#endif
{
    return (pKBI->SC & KBI_SC_KBF_MASK);        
}

/*****************************************************************************//*!
*
* @brief 清除中断标志位.
*        
* @param[in]   pKBI          指向KBI模块.
*          
* @return none.
*
*
* @see KBI_GetFlags.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_ClrFlags(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_KBACK_MASK;        
}

#if defined(CPU_NV32M4)
/*****************************************************************************//*!
*
* @brief Real KBI_SP register enable.
*        
* @param[in]   pKBI         pointer to KBI module
*          
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see The real ETMe value of Keyboard source pin to be read.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_SPEnable(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_KBSPEN_MASK;        
}

/*****************************************************************************//*!
*
* @brief Get KBI source pin register fields.
*        
* @param[in]   pKBI         pointer to KBI module.
*          
* @return uint32_t.
*
* @ Pass/ Fail criteria: none.
*
* @see KBI_GetSP.
*
*****************************************************************************/
__STATIC_INLINE  uint32_t KBI_GetSP(KBI_Type *pKBI)
{
    return (pKBI->SP & KBI_SP_SP_MASK);        
}

/*****************************************************************************//*!
*
* @brief Reset KBI_SP register.
*        
* @param[in]   pKBI         pointer to KBI module
*          
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see KBI_RstSP.
*
*****************************************************************************/
__STATIC_INLINE  void KBI_RstSP(KBI_Type *pKBI)
{
    pKBI->SC |= KBI_SC_RSTKBSP_MASK;        
}
#endif


/******************************************************************************
* Global functions
******************************************************************************/

void KBI_Init(KBI_Type *pKBI, KBI_ConfigType *pConfig);
void KBI_SetCallback(KBI_Type *pKBI, KBI_CallbackType pfnCallback);

#ifdef __cplusplus
}
#endif
#endif 
