/******************************************************************************
*
* @brief  PMC 驱动头文件.  
*
******************************************************************************/
#ifndef PMC_H_
#define PMC_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
/******************************************************************************
* PCM系统（MCU工作模式）模式定义
*
*******************************************************************************/
#define PmcModeRun     0                     /*!< 运行模式 */
#define PmcModeWait    1                     /*!< 等到模式 */
#define PmcModeStop4   2                     /*!< 停止模式4 */
#define PmcModeStop3   3                     /*!< 停止模式3 */


/******************************************************************************
* PMC 低压检测和低压报警电压定义
*
*******************************************************************************/
#define PmcLVDTrip_Low   0                     /*!< LVD 低电平调变点 */
#define PmcLVDTrip_High  1                     /*!< LVD 高电平调变点 */

#define PmcLVWTrip_Low   0                     /*!< LVW 低电平跳变点 */
#define PmcLVWTrip_Mid1  1                     /*!< LVW 中间电平1跳变点 */
#define PmcLVWTrip_Mid2  2                     /*!< LVW 中间电平2跳变点*/
#define PmcLVWTrip_High  3                     /*!< LVW 高电平跳变点*/

/******************************************************************************
* PMC 控制结构体
*******************************************************************************/
/*!
 * @brief PMC控制结构体类型
 *
 */

typedef union 
{
   uint8_t byte;						  /*!< 联合体的类型-字节*/
   struct 
   {     
       uint8_t bBandgapEn        :1;      /*!< 使能带隙缓冲区 */
       uint8_t bBandgapDrv       :1;      /*!< 选择带隙驱动*/
       uint8_t bLvdEn            :1;      /*!< 使能低压检测*/
       uint8_t bLvdStopEn        :1;      /*!< 低压检测在停止模式下使能*/
       uint8_t bLvdRstEn         :1;      /*!< 使能低压检测复位 */
       uint8_t bLvwIrqEn         :1;      /*!< 使能低压报警中断 */
       uint8_t bLvwAck           :1;      /*!< 低压报警应答 */
       uint8_t bLvwFlag          :1;      /*!< 低压报警标志 */
   }bits; 								                /*!< 联合体类型-位 */
}PMC_Ctrl1Type, *PMC_Ctrl1Ptr;		  /*!< PMC 控制寄存器1结构体 */


/******************************************************************************
* PMC 控制-- 低压选择.
*******************************************************************************/
/*!
 * @brief PMC 控制-- 电压类型选择.
 *
 */
typedef union 
{
   uint8_t byte;						   /*!< 联合体类型-字节 */
   struct 
   {     
       uint8_t           :4;               /*!< none */  
       uint8_t bLVWV     :2;               /*!< 低压报警电压选择 */  
       uint8_t bLVDV     :1;               /*!< 低压复位电压选择 */  
       uint8_t           :1;               /*!< none */                 
   }bits;  								   /*!< 结构体类型——位 */
}PMC_Ctrl2Type, *PMC_Ctrl2Ptr;		   /*!< PMC 控制寄存器2结构体*/

/******************************************************************************
* PMC 配置结构体
*******************************************************************************/

typedef struct 
{
    PMC_Ctrl1Type    sCtrlstatus;          /*!< PMC 控制和状态 */  
    PMC_Ctrl2Type    sDetectVoltSelect;    /*!< 低压报警电压和低压复位电压选择*/  
}PMC_ConfigType, *PMC_ConfigPtr;		   /*!< PMC 配置结构体 */

/*****************************************************************************//*!
*
* @brief  在停止模式下使能低压检测.
* 
* @param[in]  pPMC              指向PMC模块
*
* @return none.
*
* @see PMC_DisableLVDInStopMode.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVDInStopMode(PMC_Type *pPMC)
{
    pPMC->SPMSC1 |= PMC_SPMSC1_LVDSE_MASK;
}

/*****************************************************************************//*!
*
* @brief  在停止模式下禁用低压检测
* 
* @param[in]  pPMC           指向PMC模块
*
* @return none.
*
* @see PMC_EnableLVDInStopMode.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVDInStopMode(PMC_Type *pPMC)
{
    pPMC->SPMSC1 &= ~PMC_SPMSC1_LVDSE_MASK;
}

/*****************************************************************************//*!
*
* @brief  使能低压检测复位  注: 复位后该字段仅可写一次
* 
* @param[in]  pPMC           指向PMC模块.
*
* @return none.
*
* @see PMC_DisableLVDRst.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVDRst(PMC_Type *pPMC)
{
    pPMC->SPMSC1 |= PMC_SPMSC1_LVDRE_MASK;
}

/*****************************************************************************//*!
*
* @brief  禁用低压检测复位   注: 复位后该字段仅可写一次
* 
* @param[in]  pPMC             指向PMC模块
*
* @return none.
*
* @see PMC_EnableLVDRst.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVDRst(PMC_Type *pPMC)
{
    pPMC->SPMSC1 &= ~PMC_SPMSC1_LVDRE_MASK;
}

/*****************************************************************************//*!
*
* @brief  使能低压检测,  注: 复位后该字段仅可写一次
* 
* @param[in]  pPMC            指向PMC模块
*
* @return none.
*
* @see PMC_DisableLVD.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVD(PMC_Type *pPMC)
{
    pPMC->SPMSC1 |= PMC_SPMSC1_LVDE_MASK;
}

/*****************************************************************************//*!
*
* @brief  禁用低压检测,   注: 复位后该字段仅可写一次
* 
* @param[in]  pPMC           指向PMC模块
*
* @return none.
*
* @see PMC_EnableLVD.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVD(PMC_Type *pPMC)
{
    pPMC->SPMSC1 &= ~PMC_SPMSC1_LVDE_MASK;
}

/*****************************************************************************//*!
*
* @brief   设置低压检测跳变点，
* 
* @param[in]  pPMC              指向PMC模块
* @param[in]  Trippoint         电压检测跳变点选择，1-高电平跳变 0-低电平跳变
*
* @return none.
*
* @see PMC_SetLVWTripVolt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_SetLVDTripVolt(PMC_Type *pPMC, uint8_t Trippoint)
{
    if(Trippoint)
        pPMC->SPMSC2 |= PMC_SPMSC2_LVDV_MASK;
    else
        pPMC->SPMSC2 &= ~PMC_SPMSC2_LVDV_MASK;
}

/*****************************************************************************//*!
*
* @brief  选择电压报警跳变点电压
* 
* @param[in]  pPMC              指向PMC模块
* @param[in]  Trippoint         低压报警跳变点电压  0 低电平跳变     1 中间电平1跳变 
*                                                   2 中间电平2跳变  3 高电平跳变
*
* @return none.
*
* @see PMC_SetLVDTripVolt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_SetLVWTripVolt(PMC_Type *pPMC, uint8_t Trippoint)
{
    pPMC->SPMSC2 &= ~PMC_SPMSC2_LVWV_MASK;
    pPMC->SPMSC2 |= PMC_SPMSC2_LVWV(Trippoint);
}

/*****************************************************************************//*!
*
* @brief  使能低压报警中断
* 
* @param[in]  pPMC        指向PMC模块
*
* @return none.
*
* @see PMC_DisableLVWInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_EnableLVWInterrupt(PMC_Type *pPMC)
{
   pPMC->SPMSC1 |= PMC_SPMSC1_LVWIE_MASK;
}

/*****************************************************************************//*!
*
* @brief 禁用低压报警中断
* 
* @param[in]  pPMC              指向PMC模块.
*
* @return none.
*
*
* @see PMC_EnableLVWInterrupt.
*
*****************************************************************************/
__STATIC_INLINE void PMC_DisableLVWInterrupt(PMC_Type *pPMC)
{
   pPMC->SPMSC1 &= ~PMC_SPMSC1_LVWIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  读取低压报警标志位.
* 
* @param[in]  pPMC           指向PMC模块.
*
* @return  低压报警标志位值
*
* @see PMC_ClrLVWFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t PMC_GetLVWFlag(PMC_Type *pPMC)
{
   return (pPMC->SPMSC1 & PMC_SPMSC1_LVWF_MASK);
}

/*****************************************************************************//*!
*
* @brief  清除低压报警标志位
* 
* @param[in]  pPMC            指向PMC模块.
*
* @return none.
*
* @see PMC_GetLVWFlag.
*
*****************************************************************************/
__STATIC_INLINE void PMC_ClrLVWFlag(PMC_Type *pPMC)
{
   pPMC->SPMSC1 |= PMC_SPMSC1_LVWACK_MASK;
}  

/**************************************************************************/

void PMC_Init(PMC_Type *pPMC, PMC_ConfigType *pPMC_Config);
void PMC_DeInit(PMC_Type *pPMC);
void PMC_SetMode(PMC_Type *pPMC,uint8_t u8PmcMode);

#ifdef __cplusplus
}
#endif
#endif 
