/**************************************************************************//**
* @file     sys.h
* @brief    N9H30 SYS driver header file
*
* @note
* SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_SYS_H__
#define __NU_SYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_SYS_Driver SYS Driver
  @{
*/

/** @addtogroup N9H30_SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/

/**
 * @details  Interrupt Number Definition.
 */
typedef enum IRQn
{

    /******  N9H30 Specific Interrupt Numbers *****************************************/

    WDT_IRQn                = 1,       /*!< Watch Dog Timer Interrupt                  */
    WWDT_IRQn               = 2,       /*!< Windowed-WDT Interrupt                     */
    LVD_IRQn                = 3,       /*!< Low Voltage Detect Interrupt               */
    EINT0_IRQn              = 4,       /*!< External Interrupt 0                       */
    EINT1_IRQn              = 5,       /*!< External Interrupt 1                       */
    EINT2_IRQn              = 6,       /*!< External Interrupt 2                       */
    EINT3_IRQn              = 7,       /*!< External Interrupt 3                       */
    EINT4_IRQn              = 8,       /*!< External Interrupt 4                       */
    EINT5_IRQn              = 9,       /*!< External Interrupt 5                       */
    EINT6_IRQn              = 10,      /*!< External Interrupt 6                       */
    EINT7_IRQn              = 11,      /*!< External Interrupt 7                       */
    ACTL_IRQn               = 12,      /*!< Audio Controller Interrupt                 */
    LCD_IRQn                = 13,      /*!< LCD Controller Interrupt                   */
    CAP_IRQn                = 14,      /*!< Sensor Interface Controller Interrupt      */
    RTC_IRQn                = 15,      /*!< Real Time Clock Interrupt                  */
    TMR0_IRQn               = 16,      /*!< Timer 0 Interrupt                          */
    TMR1_IRQn               = 17,      /*!< Timer 1 Interrupt                          */
    ADC_IRQn                = 18,      /*!< ADC Interrupt                              */
    EMC0_RX_IRQn            = 19,      /*!< EMC 0 RX Interrupt                         */
    EMC1_RX_IRQn            = 20,      /*!< EMC 1 RX Interrupt                         */
    EMC0_TX_IRQn            = 21,      /*!< EMC 0 TX Interrupt                         */
    EMC1_TX_IRQn            = 22,      /*!< EMC 1 TX Interrupt                         */
    EHCI_IRQn               = 23,      /*!< USB 2.0 Host Controller Interrupt          */
    OHCI_IRQn               = 24,      /*!< USB 1.1 Host Controller Interrupt          */
    GDMA0_IRQn              = 25,      /*!< GDMA Channel 0 Interrupt                   */
    GDMA1_IRQn              = 26,      /*!< GDMA Channel 1 Interrupt                   */
    SDH_IRQn                = 27,      /*!< SD/SDIO Host Interrupt                     */
    FMI_IRQn                = 28,      /*!< FMI Interrupt                              */
    USBD_IRQn               = 29,      /*!< USB Device Interrupt                       */
    TMR2_IRQn               = 30,      /*!< Timer 2 Interrupt                          */
    TMR3_IRQn               = 31,      /*!< Timer 3 Interrupt                          */
    TMR4_IRQn               = 32,      /*!< Timer 4 Interrupt                          */
    JPEG_IRQn               = 33,      /*!< JPEG Engine Interrupt                      */
    GE2D_IRQn               = 34,      /*!< 2D Graphic Engine Interrupt                */
    CRPT_IRQn               = 35,      /*!< Cryptographic Accelerator Interrupt        */
    UART0_IRQn              = 36,      /*!< UART 0 Interrupt                           */
    UART1_IRQn              = 37,      /*!< UART 1 Interrupt                           */
    UART2_IRQn              = 38,      /*!< UART 2 Interrupt                           */
    UART4_IRQn              = 39,      /*!< UART 4 Interrupt                           */
    UART6_IRQn              = 40,      /*!< UART 6 Interrupt                           */
    UART8_IRQn              = 41,      /*!< UART 8 Interrupt                           */
    UART10_IRQn             = 42,      /*!< UART 10 Interrupt                          */
    UART3_IRQn              = 43,      /*!< UART 3 Interrupt                           */
    UART5_IRQn              = 44,      /*!< UART 5 Interrupt                           */
    UART7_IRQn              = 45,      /*!< UART 7 Interrupt                           */
    UART9_IRQn              = 46,      /*!< UART 9 Interrupt                           */
    ETMR0_IRQn              = 47,      /*!< Enhanced Timer 0 Interrupt                 */
    ETMR1_IRQn              = 48,      /*!< Enhanced Timer 1 Interrupt                 */
    ETMR2_IRQn              = 49,      /*!< Enhanced Timer 2 Interrupt                 */
    ETMR3_IRQn              = 50,      /*!< Enhanced Timer 3 Interrupt                 */
    SPI0_IRQn               = 51,      /*!< SPI 0 Interrupt                            */
    SPI1_IRQn               = 52,      /*!< SPI 1 Interrupt                            */
    I2C0_IRQn               = 53,      /*!< I2C 0 Interrupt                            */
    I2C1_IRQn               = 54,      /*!< I2C 1 Interrupt                            */
    SC0_IRQn                = 55,      /*!< Smart Card 0 Interrupt                     */
    SC1_IRQn                = 56,      /*!< Smart Card 1 Interrupt                     */
    GPIO_IRQn               = 57,      /*!< GPIO Interrupt                             */
    CAN0_IRQn               = 58,      /*!< CAN 0 Interrupt                            */
    CAN1_IRQn               = 59,      /*!< CAN 1 Interrupt                            */
    PWM_IRQn                = 60,      /*!< PWM Interrupt                              */

    /* Renaming for RTT porting */
    IRQ_WDT                = 1,       /*!< Watch Dog Timer Interrupt                  */
    IRQ_WWDT               = 2,       /*!< Windowed-WDT Interrupt                     */
    IRQ_LVD                = 3,       /*!< Low Voltage Detect Interrupt               */
    IRQ_EINT0              = 4,       /*!< External Interrupt 0                       */
    IRQ_EINT1              = 5,       /*!< External Interrupt 1                       */
    IRQ_EINT2              = 6,       /*!< External Interrupt 2                       */
    IRQ_EINT3              = 7,       /*!< External Interrupt 3                       */
    IRQ_EINT4              = 8,       /*!< External Interrupt 4                       */
    IRQ_EINT5              = 9,       /*!< External Interrupt 5                       */
    IRQ_EINT6              = 10,      /*!< External Interrupt 6                       */
    IRQ_EINT7              = 11,      /*!< External Interrupt 7                       */
    IRQ_ACTL               = 12,      /*!< Audio Controller Interrupt                 */
    IRQ_LCD                = 13,      /*!< LCD Controller Interrupt                   */
    IRQ_CAP                = 14,      /*!< Sensor Interface Controller Interrupt      */
    IRQ_RTC                = 15,      /*!< Real Time Clock Interrupt                  */
    IRQ_TMR0               = 16,      /*!< Timer 0 Interrupt                          */
    IRQ_TMR1               = 17,      /*!< Timer 1 Interrupt                          */
    IRQ_ADC                = 18,      /*!< ADC Interrupt                              */
    IRQ_EMC0_RX            = 19,      /*!< EMC 0 RX Interrupt                         */
    IRQ_EMC1_RX            = 20,      /*!< EMC 1 RX Interrupt                         */
    IRQ_EMC0_TX            = 21,      /*!< EMC 0 TX Interrupt                         */
    IRQ_EMC1_TX            = 22,      /*!< EMC 1 TX Interrupt                         */
    IRQ_EHCI               = 23,      /*!< USB 2.0 Host Controller Interrupt          */
    IRQ_OHCI               = 24,      /*!< USB 1.1 Host Controller Interrupt          */
    IRQ_GDMA0              = 25,      /*!< GDMA Channel 0 Interrupt                   */
    IRQ_GDMA1              = 26,      /*!< GDMA Channel 1 Interrupt                   */
    IRQ_SDH                = 27,      /*!< SD/SDIO Host Interrupt                     */
    IRQ_FMI                = 28,      /*!< FMI Interrupt                              */
    IRQ_USBD               = 29,      /*!< USB Device Interrupt                       */
    IRQ_TMR2               = 30,      /*!< Timer 2 Interrupt                          */
    IRQ_TMR3               = 31,      /*!< Timer 3 Interrupt                          */
    IRQ_TMR4               = 32,      /*!< Timer 4 Interrupt                          */
    IRQ_JPEG               = 33,      /*!< JPEG Engine Interrupt                      */
    IRQ_GE2D               = 34,      /*!< 2D Graphic Engine Interrupt                */
    IRQ_CRPT               = 35,      /*!< Cryptographic Accelerator Interrupt        */
    IRQ_UART0              = 36,      /*!< UART 0 Interrupt                           */
    IRQ_UART1              = 37,      /*!< UART 1 Interrupt                           */
    IRQ_UART2              = 38,      /*!< UART 2 Interrupt                           */
    IRQ_UART4              = 39,      /*!< UART 4 Interrupt                           */
    IRQ_UART6              = 40,      /*!< UART 6 Interrupt                           */
    IRQ_UART8              = 41,      /*!< UART 8 Interrupt                           */
    IRQ_UART10             = 42,      /*!< UART 10 Interrupt                          */
    IRQ_UART3              = 43,      /*!< UART 3 Interrupt                           */
    IRQ_UART5              = 44,      /*!< UART 5 Interrupt                           */
    IRQ_UART7              = 45,      /*!< UART 7 Interrupt                           */
    IRQ_UART9              = 46,      /*!< UART 9 Interrupt                           */
    IRQ_ETMR0              = 47,      /*!< Enhanced Timer 0 Interrupt                 */
    IRQ_ETMR1              = 48,      /*!< Enhanced Timer 1 Interrupt                 */
    IRQ_ETMR2              = 49,      /*!< Enhanced Timer 2 Interrupt                 */
    IRQ_ETMR3              = 50,      /*!< Enhanced Timer 3 Interrupt                 */
    IRQ_SPI0               = 51,      /*!< SPI 0 Interrupt                            */
    IRQ_SPI1               = 52,      /*!< SPI 1 Interrupt                            */
    IRQ_I2C0               = 53,      /*!< I2C 0 Interrupt                            */
    IRQ_I2C1               = 54,      /*!< I2C 1 Interrupt                            */
    IRQ_SC0                = 55,      /*!< Smart Card 0 Interrupt                     */
    IRQ_SC1                = 56,      /*!< Smart Card 1 Interrupt                     */
    IRQ_GPIO               = 57,      /*!< GPIO Interrupt                             */
    IRQ_CAN0               = 58,      /*!< CAN 0 Interrupt                            */
    IRQ_CAN1               = 59,      /*!< CAN 1 Interrupt                            */
    IRQ_PWM                = 60,      /*!< PWM Interrupt                              */
}
IRQn_Type;

/* Define constants for use timer in service parameters.  */
#define TIMER0            0     /*!< Select Timer0 */
#define TIMER1            1     /*!< Select Timer1 */

#define ONE_SHOT_MODE     0     /*!< Timer Operation Mode - One Shot */
#define PERIODIC_MODE     1     /*!< Timer Operation Mode - Periodic */
#define TOGGLE_MODE       2     /*!< Timer Operation Mode - Toggle */

/* The parameters for sysSetInterruptPriorityLevel() and
   sysInstallISR() use */
#define FIQ_LEVEL_0     0       /*!< FIQ Level 0 */
#define IRQ_LEVEL_1     1       /*!< IRQ Level 1 */
#define IRQ_LEVEL_2     2       /*!< IRQ Level 2 */
#define IRQ_LEVEL_3     3       /*!< IRQ Level 3 */
#define IRQ_LEVEL_4     4       /*!< IRQ Level 4 */
#define IRQ_LEVEL_5     5       /*!< IRQ Level 5 */
#define IRQ_LEVEL_6     6       /*!< IRQ Level 6 */
#define IRQ_LEVEL_7     7       /*!< IRQ Level 7 */

#define ONE_HALF_SECS     0     /*!< WDT interval - 1.5s */
#define FIVE_SECS         1     /*!< WDT interval - 5s */
#define TEN_SECS          2     /*!< WDT interval - 10s */
#define TWENTY_SECS       3     /*!< WDT interval - 20s */

/* Define constants for use AIC in service parameters.  */
#define SYS_SWI           0     /*!< Exception - SWI */
#define SYS_D_ABORT       1     /*!< Exception - Data abort */
#define SYS_I_ABORT       2     /*!< Exception - Instruction abort */
#define SYS_UNDEFINE      3     /*!< Exception - undefine */

/* The parameters for sysSetLocalInterrupt() use */
#define ENABLE_IRQ        0x7F  /*!< Enable I-bit of CP15  */
#define ENABLE_FIQ        0xBF  /*!< Enable F-bit of CP15  */
#define ENABLE_FIQ_IRQ    0x3F  /*!< Enable I-bit and F-bit of CP15  */
#define DISABLE_IRQ       0x80  /*!< Disable I-bit of CP15  */
#define DISABLE_FIQ       0x40  /*!< Disable F-bit of CP15  */
#define DISABLE_FIQ_IRQ   0xC0  /*!< Disable I-bit and F-bit of CP15  */

/* Define Cache type  */
#define CACHE_WRITE_BACK        0     /*!< Cache Write-back mode  */
#define CACHE_WRITE_THROUGH     1     /*!< Cache Write-through mode  */
#define CACHE_DISABLE           -1    /*!< Cache Disable  */

/** \brief  Structure type of clock source
 */
typedef enum CLKn
{

    SYS_UPLL     = 1,   /*!< UPLL clock */
    SYS_APLL     = 2,   /*!< APLL clock */
    SYS_SYSTEM   = 3,   /*!< System clock */
    SYS_HCLK1    = 4,   /*!< HCLK1 clock */
    SYS_HCLK234  = 5,   /*!< HCLK234 clock */
    SYS_PCLK     = 6,   /*!< PCLK clock */
    SYS_CPU      = 7,   /*!< CPU clock */

}  CLK_Type;



/// @cond HIDDEN_SYMBOLS
typedef struct datetime_t
{
    UINT32  year;
    UINT32  mon;
    UINT32  day;
    UINT32  hour;
    UINT32  min;
    UINT32  sec;
} DateTime_T;

/* The parameters for sysSetInterruptType() use */
#define LOW_LEVEL_SENSITIVE        0x00
#define HIGH_LEVEL_SENSITIVE       0x40
#define NEGATIVE_EDGE_TRIGGER      0x80
#define POSITIVE_EDGE_TRIGGER      0xC0

/* The parameters for sysSetGlobalInterrupt() use */
#define ENABLE_ALL_INTERRUPTS      0
#define DISABLE_ALL_INTERRUPTS     1

#define MMU_DIRECT_MAPPING  0
#define MMU_INVERSE_MAPPING 1


/* Define constants for use Cache in service parameters.  */
#define CACHE_4M        2
#define CACHE_8M        3
#define CACHE_16M       4
#define CACHE_32M       5
#define I_CACHE         6
#define D_CACHE         7
#define I_D_CACHE       8


/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  */
static __inline void SYS_UnlockReg(void)
{
    do
    {
        outpw(0xB00001FC, 0x59UL);
        outpw(0xB00001FC, 0x16UL);
        outpw(0xB00001FC, 0x88UL);
    }
    while (inpw(0xB00001FC) == 0UL);
}

/**
  * @brief      Enable register write-protection function
  * @param      None
  * @return     None
  * @details    This function is used to enable register write-protection function.
  *             To lock the protected register to forbid write access.
  */
static __inline void SYS_LockReg(void)
{
    outpw(0xB00001FC, 0);
}


/// @endcond HIDDEN_SYMBOLS

/*@}*/ /* end of group N9H30_SYS_EXPORTED_CONSTANTS */


/** @addtogroup N9H30_SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/* Define system library Timer functions */
UINT32  sysGetTicks(INT32 nTimeNo);
INT32   sysResetTicks(INT32 nTimeNo);
INT32   sysUpdateTickCount(INT32 nTimeNo, UINT32 uCount);
INT32   sysSetTimerReferenceClock(INT32 nTimeNo, UINT32 uClockRate);
INT32   sysStartTimer(INT32 nTimeNo, UINT32 uTicksPerSecond, INT32 nOpMode);
INT32   sysStopTimer(INT32 nTimeNo);
void    sysClearWatchDogTimerCount(void);
void    sysClearWatchDogTimerInterruptStatus(void);
void    sysDisableWatchDogTimer(void);
void    sysDisableWatchDogTimerReset(void);
void    sysEnableWatchDogTimer(void);
void    sysEnableWatchDogTimerReset(void);
PVOID   sysInstallWatchDogTimerISR(INT32 nIntTypeLevel, PVOID pvNewISR);
INT32   sysSetWatchDogTimerInterval(INT32 nWdtInterval);
INT32   sysSetTimerEvent(INT32 nTimeNo, UINT32 uTimeTick, PVOID pvFun);
void    sysClearTimerEvent(INT32 nTimeNo, UINT32 uTimeEventNo);
void    sysSetLocalTime(DateTime_T ltime);          /*!< Set local time \hideinitializer */
void    sysGetCurrentTime(DateTime_T *curTime);     /*!< Get current time \hideinitializer */
void    sysDelay(UINT32 uTicks);

/* Define system library UART functions */
//INT8    sysGetChar(void);
//INT32   sysInitializeUART(void);
//void    sysprintf(PINT8 pcStr, ...);
//void    sysPutChar(UINT8 ucCh);
//INT     sysIsKbHit(void);

/* Define system library AIC functions */
INT32   sysDisableInterrupt(IRQn_Type eIntNo);
INT32   sysEnableInterrupt(IRQn_Type eIntNo);
BOOL    sysGetIBitState(void);              /*!< Get I bit state \hideinitializer */
UINT32  sysGetInterruptEnableStatus(void);  /*!< Get interrupt enable status \hideinitializer */
UINT32  sysGetInterruptEnableStatusH(void); /*!< Get interrupt enable status \hideinitializer */
PVOID   sysInstallExceptionHandler(INT32 nExceptType, PVOID pvNewHandler);
PVOID   sysInstallFiqHandler(PVOID pvNewISR);
PVOID   sysInstallIrqHandler(PVOID pvNewISR);
PVOID   sysInstallISR(INT32 nIntTypeLevel, IRQn_Type eIntNo, PVOID pvNewISR);
INT32   sysSetGlobalInterrupt(INT32 nIntState);     /*!< Enable/Disable all interrupt \hideinitializer */
INT32   sysSetInterruptPriorityLevel(IRQn_Type eIntNo, UINT32 uIntLevel);
INT32   sysSetInterruptType(IRQn_Type eIntNo, UINT32 uIntSourceType);       /*!< Change interrupt type \hideinitializer */
INT32   sysSetLocalInterrupt(INT32 nIntState);


/* Define system library Cache functions */
void    sysDisableCache(void);
INT32   sysEnableCache(UINT32 uCacheOpMode);
void    sysFlushCache(INT32 nCacheType);    /*!< flush cache \hideinitializer */
BOOL    sysGetCacheState(void);             /*!< get cache state \hideinitializer */
INT32   sysGetSdramSizebyMB(void);          /*!< Get DRAM size \hideinitializer */
void    sysInvalidCache(void);              /*!< invalid cache \hideinitializer */
INT32   sysSetCachePages(UINT32 addr, INT32 size, INT32 cache_mode);    /*!< set cache page \hideinitializer */

int sysSetMMUMappingMethod(int mode);   /*!< MMU mapping \hideinitializer */

UINT32 sysGetClock(CLK_Type clk);

typedef void (*sys_pvFunPtr)();   /* function pointer */
/// @cond HIDDEN_SYMBOLS
extern sys_pvFunPtr sysIrqHandlerTable[];
extern BOOL volatile _sys_bIsAICInitial;
/// @endcond
#ifdef __cplusplus
}
#endif

/*@}*/ /* end of group N9H30_SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_SYS_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#endif //__NU_SYS_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

