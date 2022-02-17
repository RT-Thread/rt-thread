


#ifndef __CH57x_SYS_H__
#define __CH57x_SYS_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"



/**
  * @brief  rtc interrupt event define
  */
typedef enum
{
    RST_STATUS_SW = 0,          // 软件复位
    RST_STATUS_RPOR,            // 上电复位
    RST_STATUS_WTR,             // 看门狗超时复位
    RST_STATUS_MR,              // 外部手动复位
    RST_STATUS_LRM0,            // 唤醒复位-软复位引起
    RST_STATUS_GPWSM,           // 下电模式唤醒复位
    RST_STATUS_LRM1,            //  唤醒复位-看门狗引起
    RST_STATUS_LRM2,            //  唤醒复位-手动复位引起

}SYS_ResetStaTypeDef;

/**
  * @brief  rtc interrupt event define
  */
typedef enum
{
    INFO_ROM_READ = 0,          // FlashROM 代码和数据区 是否可读
    INFO_RESET_EN = 2,          // RST#外部手动复位输入功能是否开启
    INFO_BOOT_EN,               // 系统引导程序 BootLoader 是否开启
    INFO_DEBUG_EN,              // 系统仿真调试接口是否开启
    INFO_LOADER,                // 当前系统是否处于Bootloader 区
    STA_SAFEACC_ACT,            // 当前系统是否处于安全访问状态，否则RWA属性区域不可访问

}SYS_InfoStaTypeDef;


#define SYS_GetChipID()             R8_CHIP_ID                                  /* 获取芯片ID类，一般为固定值 */
#define SYS_GetAccessID()           R8_SAFE_ACCESS_ID                           /* 获取安全访问ID，一般为固定值 */
UINT8 SYS_GetInfoSta( SYS_InfoStaTypeDef i );                                   /* 获取当前系统信息状态 */
// refer to SYS_ResetStaTypeDef
#define SYS_GetLastResetSta()       (R8_RESET_STATUS&RB_RESET_FLAG)             /* 获取系统上次复位状态 */
void SYS_ResetExecute( void );                                                  /* 执行系统软件复位 */
#define SYS_ResetKeepBuf( d )       (R8_GLOB_RESET_KEEP = d)                    /* 不受手动复位、 软件复位、 看门狗复位或者普通唤醒复位的影响 */

void SYS_DisableAllIrq( PUINT32 pirqv);                                         /* 关闭所有中断，并保留当前中断值 */
void SYS_RecoverIrq( UINT32 irq_status );                                       /* 恢复之前关闭的中断值 */
UINT32 SYS_GetSysTickCnt( void );                                               /* 获取当前系统(SYSTICK)计数值 */

#define  WWDG_SetCounter( c )       (R8_WDOG_COUNT = c)                         /* 加载看门狗计数初值，递增型 */
void  WWDG_ITCfg( UINT8 s );                            /* 看门狗溢出中断使能 */
void  WWDG_ResetCfg( UINT8 s );                         /* 看门狗溢出复位使能 */
#define  WWDG_GetFlowFlag()         (R8_RST_WDOG_CTRL&RB_WDOG_INT_FLAG)         /* 获取当前看门狗定时器溢出标志 */
void WWDG_ClearFlag(void);                                                      /* 清除看门狗中断标志，重新加载计数值也可清除 */


void mDelayuS( UINT16 t );      /* uS 延时 */
void mDelaymS( UINT16 t );      /* mS 延时 */



#ifdef __cplusplus
}
#endif

#endif  // __CH57x_SYS_H__

