/**************************************************************************//**
 * @file     pwm.h
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 15/05/19 10:16a $
 * @brief    NUC980 series PWM driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_PWM_H__
#define __NU_PWM_H__
#include "nuc980.h"
#include "nu_sys.h"
#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PWM_Driver PWM Driver
  @{
*/

/** @addtogroup PWM_EXPORTED_CONSTANTS PWM Exported Constants
  @{
*/

#define PWM_OFFSET      0xc ///< each channel has 3 control registers which occupies 12 bytes

// Timer channel identity information
#define PWM_TIMER_NUM   8   ///< Total PWM channel count
#define PWM_TIMER_MIN   0   ///< Min PWM channel number
#define PWM_TIMER_MAX   7   ///< Max PWM channel number
#define PWM0_TIMER0     0   ///< PWM0 channel 0
#define PWM0_TIMER1     1   ///< PWM0 channel 1
#define PWM0_TIMER2     2   ///< PWM0 channel 2
#define PWM0_TIMER3     3   ///< PWM0 channel 3
#define PWM1_TIMER0     4   ///< PWM1 channel 0
#define PWM1_TIMER1     5   ///< PWM1 channel 1
#define PWM1_TIMER2     6   ///< PWM1 channel 2
#define PWM1_TIMER3     7   ///< PWM1 channel 3

//ioctl command
#define START_PWMTIMER          0   ///< Start PWM ioctl command 
#define STOP_PWMTIMER           1   ///< Stop PWM ioctl command
#define SET_CSR                 2   ///< Set CSR ioctl command
#define SET_CP                  3   ///< Set CP ioctl command
#define SET_DZI                 4   ///< Set dead zone ioctl command
#define SET_INVERTER            5   ///< Set inverter ioctl command
#define SET_MODE                6   ///< Set OP mode ioctl command
#define ENABLE_DZ_GENERATOR     7   ///< Enable dead zone ioctl command
#define DISABLE_DZ_GENERATOR    8   ///< Disable dead zone ioctl command
#define ENABLE_PWMGPIOOUTPUT    9   ///< Enable PWM output ioctl command

#define PWM_STOP_METHOD1    1        ///< PWM stop method 1
#define PWM_STOP_METHOD2    2        ///< PWM stop method 2
//#define PWM_STOP_METHOD3  3 not recommended

//Timer default value
#define DEFAULT_CSR     CSRD16        ///< Default CSR value
#define DEFAULT_CP      255            ///< Default CP value
#define DEFAULT_DZI     50            ///< Default DZI value
#define DEFAULT_CNR     19531        ///< Default CNR value
#define DEFAULT_CMR     (19531/4)    ///< Default CMR value
#define DEFAULT_MODE    PWM_TOGGLE    ///< Default OP mode

// for PWM_PPR
#define DZI_MIN     0        ///< Min DZI value
#define DZI_MAX     255        ///< Max DZI value
#define CP_MIN      0        ///< Min CP value
#define CP_MAX      255        ///< Max CP value

// for PWM_CSR
#define CSR_MIN     0        ///< Min CSR value
#define CSR_MAX     4        ///< Mac SCR value
#define CSRD2       0x0        ///< Div by 2
#define CSRD4       0x1        ///< Div by 4
#define CSRD8       0x2        ///< Div by 8
#define CSRD16      0x3        ///< Div by 16
#define CSRD1       0x4        ///< Div by 1

// for PWM_PCR
#define PWMDZG_ENABLE   1    ///< Enable PWM dead zone
#define PWMDZG_DISABLE  0    ///< Disable PWM dead zone
#define PWM_ENABLE      1   ///< Enable PWM channel
#define PWM_DISABLE     0   ///< Disable PWM channel
#define PWM_TOGGLE      1    ///< PWM toggle mode
#define PWM_ONESHOT     0    ///< PWM one-shot mode
#define PWM_INVON       1    ///< Enable PWM inverter
#define PWM_INVOFF      0    ///< Disable PWM inverter

// for PWM_CNR
#define CNR_MIN     0        ///< Min CNR value
#define CNR_MAX     65535    ///< Mac CNR value

// for PWM_CMR
#define CMR_MIN     0        ///< Min CMR value
#define CMR_MAX     65535    ///< Max CMR value

// for pin control
#define PWM00_GPF5      0       ///< PWM00 output on GPF5
#define PWM01_GPF6      1       ///< PWM01 output on GPF6
#define PWM02_GPF7      2       ///< PWM02 output on GPF7
#define PWM03_GPF8      3       ///< PWM03 output on GPF8
#define PWM00_GPG0      4       ///< PWM00 output on GPG0
#define PWM01_GPG1      5       ///< PWM01 output on GPG1
#define PWM02_GPG2      6       ///< PWM02 output on GPG2
#define PWM03_GPG3      7       ///< PWM03 output on GPG3
#define PWM00_GPD12     8       ///< PWM00 output on GPD12
#define PWM01_GPD13     9       ///< PWM01 output on GPD13
#define PWM02_GPD14     10      ///< PWM02 output on GPD14
#define PWM03_GPD15     11      ///< PWM03 output on GPD15
#define PWM00_GPG10     12      ///< PWM00 output on GPG10
#define PWM01_GPA15     13      ///< PWM01 output on GPA15
#define PWM02_GPA14     14      ///< PWM02 output on GPA14
#define PWM03_GPA13     15      ///< PWM03 output on GPA13
#define PWM02_GPB13     16      ///< PWM02 output on GPB13

#define PWM10_GPB12     17      ///< PWM10 output on GPB12
#define PWM11_GPB11     18      ///< PWM11 output on GPB11
#define PWM12_GPB10     19      ///< PWM12 output on GPB10
#define PWM13_GPB9      20      ///< PWM13 output on GPB9
#define PWM10_GPG6      21      ///< PWM10 output on GPG6
#define PWM11_GPG7      22      ///< PWM11 output on GPG7
#define PWM12_GPG8      23      ///< PWM12 output on GPG8
#define PWM13_GPG9      24      ///< PWM13 output on GPG9
#define PWM10_GPG11     25      ///< PWM10 output on GPG11
#define PWM11_GPG12     26      ///< PWM11 output on GPG12
#define PWM12_GPG13     27      ///< PWM12 output on GPG13
#define PWM13_GPG14     28      ///< PWM13 output on GPG14
#define PWM10_GPF9      29      ///< PWM10 output on GPF9
#define PWM11_GPF10     30      ///< PWM11 output on GPF10
#define PWM12_GPE10     31      ///< PWM12 output on GPE10
#define PWM13_GPE12     32      ///< PWM13 output on GPE12

#define PWM_ERR_ID      0xFFFF1300  ///< PWM library ID

//PWM Error code
#define pwmInvalidTimerChannel  (PWM_ERR_ID|1)    ///< Invalid channel number
#define pwmInvalidStructLength  (PWM_ERR_ID|2)    ///< Invalid structure length
#define pwmInvalidIoctlCommand  (PWM_ERR_ID|3)    ///< Invalid ioctl command
#define pwmInvalidStopMethod    (PWM_ERR_ID|4)    ///< Invalid stop mode
#define pwmInvalidCPValue       (PWM_ERR_ID|5)    ///< Invalid CP value
#define pwmInvalidDZIValue      (PWM_ERR_ID|6)    ///< Invalid DZI value
#define pwmInvalidCSRValue      (PWM_ERR_ID|7)    ///< Invalid CSR value
#define pwmInvalidDZGStatus     (PWM_ERR_ID|8)    ///< Invalid DZ status
#define pwmInvalidTimerStatus   (PWM_ERR_ID|9)    ///< Invalid timer status
#define pwmInvalidInverterValue (PWM_ERR_ID|10)    ///< Invalid inverter value
#define pwmInvalidModeStatus    (PWM_ERR_ID|11)    ///< Invalid OP mode
#define pwmInvalidCNRValue      (PWM_ERR_ID|12)    ///< Invalid CNR value
#define pwmInvalidCMRValue      (PWM_ERR_ID|13)    ///< Invalid CMR value
#define pwmTimerNotOpen         (PWM_ERR_ID|14)    ///< PWM channel not stop
#define pwmTimerBusy            (PWM_ERR_ID|15)    ///< PWM channel is busy
#define pwmInvalidPin           (PWM_ERR_ID|16)    ///< Invalid PWM output pin

/*@}*/ /* end of group PWM_EXPORTED_CONSTANTS */

/// @cond HIDDEN_SYMBOLS
/** @addtogroup PWM_EXPORTED_STRUCTS PWM Exported Structs
  @{
*/

typedef union
{
    UINT value;
    struct
    {
        UINT cp0: 8, cp1: 8, dzi0: 8, dzi1: 8;
    } field;
} typePPR;

typedef union
{
    UINT value;
    struct
    {
        UINT   csr0: 3, _reserved3: 1,
               csr1: 3, _reserved7: 1,
               csr2: 3, _reserved11: 1,
               csr3: 3, _reserved15: 1,
               _reserved16_31: 16;
    } field;
} typeCSR;

typedef union
{
    UINT value;
    struct
    {
        UINT   ch0_en: 1, _reserved1: 1, ch0_inverter: 1, ch0_mode: 1,
               grpup0_dzen: 1, grpup1_dzen: 1,
               _reserved6_7: 2,
               ch1_en: 1, _reserved9: 1, ch1_inverter: 1, ch1_mode: 1,
               ch2_en: 1, _reserved13: 1, ch2_inverter: 1, ch2_mode: 1,
               ch3_en: 1, _reserved17: 1, ch3_inverter: 1, ch3_mode: 1,
               _reserved20_31: 12;
    } field;
} typePCR;

typedef union
{
    UINT value;
    struct
    {
        UINT cnr: 16, _reserved16_31: 16;
    } field;
} typeCNR;

typedef union
{
    UINT value;
    struct
    {
        UINT cmr: 16, _reserved16_31: 16;
    } field;
} typeCMR;

// for write operation
typedef union
{
    UINT value;
    struct
    {
        UINT cnr: 16, cmr: 16;
    } field;
} typePWMVALUE;

// for read operation
typedef struct
{
    UINT volatile PDR;
    BOOL volatile InterruptFlag;
    BOOL _reversed0;
    BOOL _reversed1;
    BOOL _reversed2;
} typePWMSTATUS;

/*@}*/ /* end of group PWM_EXPORTED_STRUCTS */
/// @endcond /* HIDDEN_SYMBOLS */

/** @addtogroup PWM_EXPORTED_FUNCTIONS PWM Exported Functions
  @{
*/

// function definition
INT pwmInit(const INT nTimerIdentity);
INT pwmExit(void);
INT pwmOpen(const INT nTimerIdentity);
INT pwmClose(const INT nTimerIdentity);
INT pwmRead(const INT nTimerIdentity, PUCHAR pucStatusValue, const UINT uLength);
INT pwmWrite(const INT nTimerIdentity, PUCHAR pucCNRCMRValue, const UINT uLength);
INT pwmIoctl(const INT nTimerIdentity, const UINT uCommand, const UINT uIndication, UINT uValue);

/*@}*/ /* end of group PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PWM_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_PWM_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
