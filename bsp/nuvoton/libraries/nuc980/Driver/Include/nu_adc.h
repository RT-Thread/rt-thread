/**************************************************************************//**
* @file     adc.h
* @version  V1.00
* $Revision: 6 $
* $Date: 15/10/05 7:00p $
* @brief    NUC980 ADC driver header file
*
* @note
 * SPDX-License-Identifier: Apache-2.0
* Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __NU_ADC_H__
#define __NU_ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/

/** @addtogroup ADC_EXPORTED_CONSTANTS ADC Exported Constants
  @{
*/

#define ADC_ERR_ARGS            1   /*!< The arguments is wrong */
#define ADC_ERR_CMD             2   /*!< The command is wrong */

/// @cond HIDDEN_SYMBOLS
typedef int32_t(*ADC_CALLBACK)(uint32_t status, uint32_t userData);
/// @endcond HIDDEN_SYMBOLS
/*---------------------------------------------------------------------------------------------------------*/
/* ADC_CTL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_CTL_ADEN            0x00000001  /*!< ADC Power Control */
#define ADC_CTL_VBGEN       0x00000002  /*!< ADC Internal Bandgap Power Control */
#define ADC_CTL_PWKPEN      0x00000004  /*!< ADC Keypad Power Enable Control */
#define ADC_CTL_MST             0x00000100  /*!< Menu Start Conversion */
#define ADC_CTL_PEDEEN      0x00000200  /*!< Pen Down Event Enable */
#define ADC_CTL_WKPEN       0x00000400  /*!< Keypad Press Wake Up Enable */
#define ADC_CTL_WKTEN       0x00000800  /*!< Touch Wake Up Enable */
#define ADC_CTL_WMSWCH      0x00010000  /*!< Wire Mode Switch For 5-Wire/4-Wire Configuration */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_CONF constant definitions                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_CONF_TEN                0x00000001  /*!< Touch Enable */
#define ADC_CONF_ZEN                0x00000002  /*!< Press Enable */
#define ADC_CONF_NACEN          0x00000004  /*!< Normal AD Conversion Enable */
#define ADC_CONF_VBATEN         0x00000100  /*!< Voltage Battery Enable */
#define ADC_CONF_KPCEN          0x00000200  /*!< Keypad Press Conversion Enable */
#define ADC_CONF_SELFTEN        0x00000400  /*!< Selft Test Enable */
#define ADC_CONF_DISTMAVEN  (1<<20)     /*!< Display T Mean Average Enable */
#define ADC_CONF_DISZMAVEN  (1<<21)     /*!< Display Z Mean Average Enable */
#define ADC_CONF_HSPEED         (1<<22)     /*!< High Speed Enable */

#define ADC_CONF_CHSEL_Pos  3            /*!< Channel Selection Position */
#define ADC_CONF_CHSEL_Msk  (7<<3)       /*!< Channel Selection Mask */
#define ADC_CONF_CHSEL_VBT  (0<<3)       /*!< ADC input channel select VBT */
#define ADC_CONF_CHSEL_VHS  (1<<3)       /*!< ADC input channel select VHS */
#define ADC_CONF_CHSEL_A2       (2<<3)       /*!< ADC input channel select A2 */
#define ADC_CONF_CHSEL_A3       (3<<3)       /*!< ADC input channel select A3 */
#define ADC_CONF_CHSEL_YM       (4<<3)       /*!< ADC input channel select YM */
#define ADC_CONF_CHSEL_YP       (5<<3)       /*!< ADC input channel select YP */
#define ADC_CONF_CHSEL_XM       (6<<3)       /*!< ADC input channel select XM */
#define ADC_CONF_CHSEL_XP       (7<<3)       /*!< ADC input channel select XP */

#define ADC_CONF_REFSEL_Pos  6             /*!< Reference Selection Position */
#define ADC_CONF_REFSEL_Msk     (3<<6)     /*!< Reference Selection Mask */
#define ADC_CONF_REFSEL_VREF    (0<<6)     /*!< ADC reference select VREF input or 2.5v buffer output */
#define ADC_CONF_REFSEL_YMYP    (1<<6)     /*!< ADC reference select YM vs YP */
#define ADC_CONF_REFSEL_XMXP    (2<<6)     /*!< ADC reference select XM vs XP */
#define ADC_CONF_REFSEL_AVDD33  (3<<6)     /*!< ADC reference select AGND33 vs AVDD33 */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_IER constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_IER_MIEN                0x00000001  /*!< Menu Interrupt Enable */
#define ADC_IER_KPEIEN          0x00000002  /*!< Keypad Press Event Interrupt Enable */
#define ADC_IER_PEDEIEN         0x00000004  /*!< Pen Down Even Interrupt Enable */
#define ADC_IER_WKTIEN          0x00000008  /*!< Wake Up Touch Interrupt Enable */
#define ADC_IER_WKPIEN          0x00000010  /*!< Wake Up Keypad Press Interrupt Enable */
#define ADC_IER_KPUEIEN         0x00000020  /*!< Keypad Press Up Event Interrupt Enable */
#define ADC_IER_PEUEIEN         0x00000040  /*!< Pen Up Event Interrupt Enable */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_ISR constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ISR_MF              0x00000001  /*!< Menu Complete Flag */
#define ADC_ISR_KPEF            0x00000002  /*!< Keypad Press Event Flag */
#define ADC_ISR_PEDEF           0x00000004  /*!< Pen Down Event Flag */
#define ADC_ISR_KPUEF           0x00000008  /*!< Keypad Press Up Event Flag */
#define ADC_ISR_PEUEF           0x00000010  /*!< Pen Up Event Flag */
#define ADC_ISR_TF              0x00000100  /*!< Touch Conversion Finish */
#define ADC_ISR_ZF              0x00000200  /*!< Press Conversion Finish */
#define ADC_ISR_NACF            0x00000400  /*!< Normal AD Conversion Finish */
#define ADC_ISR_VBF             0x00000800  /*!< Voltage Battery Conversion Finish */
#define ADC_ISR_KPCF            0x00001000  /*!< Keypad Press Conversion Finish */
#define ADC_ISR_SELFTF          0x00002000  /*!< Self-Test Conversion Finish */
#define ADC_ISR_INTKP           0x00010000  /*!< Interrupt Signal For Keypad Detection */
#define ADC_ISR_INTTC           0x00020000  /*!< Interrupt Signal For Touch Screen Touching Detection */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_WKISR constant definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_WKISR_WKPEF     0x00000001  /*!< Wake Up Pen Down Event Flag */
#define ADC_WKISR_WPEDEF    0x00000002  /*!< Wake Up Keypad Press Event Flage */

/** \brief  Structure type of ADC_CHAN
 */
typedef enum
{
    AIN0  = ADC_CONF_CHSEL_VBT,    /*!< ADC input channel select \ref ADC_CONF_CHSEL_VBT */
    AIN1  = ADC_CONF_CHSEL_VHS,    /*!< ADC input channel select \ref ADC_CONF_CHSEL_VHS */
    AIN2  = ADC_CONF_CHSEL_A2,     /*!< ADC input channel select \ref ADC_CONF_CHSEL_A2 */
    AIN3  = ADC_CONF_CHSEL_A3,     /*!< ADC input channel select \ref ADC_CONF_CHSEL_A3 */
    AIN4  = ADC_CONF_CHSEL_YM,     /*!< ADC input channel select \ref ADC_CONF_CHSEL_YM */
    AIN5  = ADC_CONF_CHSEL_XP,     /*!< ADC input channel select \ref ADC_CONF_CHSEL_XP */
    AIN6  = ADC_CONF_CHSEL_XM,     /*!< ADC input channel select \ref ADC_CONF_CHSEL_XM */
    AIN7  = ADC_CONF_CHSEL_XP      /*!< ADC input channel select \ref ADC_CONF_CHSEL_XP */
} ADC_CHAN;

/** \brief  Structure type of ADC_CMD
 */
typedef enum
{
    START_MST,                  /*!<Menu Start Conversion with interrupt */
    START_MST_POLLING,          /*!<Menu Start Conversion with polling */
    VBPOWER_ON,                 /*!<Enable ADC Internal Bandgap Power */
    VBPOWER_OFF,                    /*!<Disable ADC Internal Bandgap Power */
    VBAT_ON,                            /*!<Enable Voltage Battery conversion function */
    VBAT_OFF,                       /*!<Disable Voltage Battery conversion function */

    KPPOWER_ON,                 /*!<Enable ADC Keypad power */
    KPPOWER_OFF,                    /*!<Disable ADC Keypad power */
    KPCONV_ON,                      /*!<Enable Keypad conversion function */
    KPCONV_OFF,                 /*!<Disable Keypad conversion function */
    KPPRESS_ON,                 /*!<Enable Keypad press event */
    KPPRESS_OFF,                    /*!<Disable Keypad press event */
    KPUP_ON,                            /*!<Enable Keypad up event */
    KPUP_OFF,                       /*!<Disable Keypad up event */

    PEPOWER_ON,                 /*!<Enable Pen Down Power ,It can control pen down event */
    PEPOWER_OFF,                    /*!<Disable Pen Power */
    PEDEF_ON,                       /*!<Enable Pen Down Event Flag */
    PEDEF_OFF,                      /*!<Disable Pen Down Event Flag */

    WKP_ON,                         /*!<Enable Keypad Press Wake Up */
    WKP_OFF,                            /*!<Disable Keypad Press Wake Up */
    WKT_ON,                         /*!<Enable Pen Down Wake Up */
    WKT_OFF,                        /*!<Disable Pen Down Wake Up */
    SWITCH_5WIRE_ON,            /*!<Wire Mode Switch to 5-Wire Configuration */
    SWITCH_5WIRE_OFF,       /*!<Wire Mode Switch to 4-Wire Configuration */

    T_ON,                               /*!<Enable Touch detection function */
    T_OFF,                              /*!<Disable Touch detection function */
    TAVG_ON,                            /*!<Enable Touch Mean average for X and Y function */
    TAVG_OFF,                       /*!<Disable Touch Mean average for X and Y function */
    Z_ON,                               /*!<Enable Press measure function */
    Z_OFF,                              /*!<Disable Press measure function */
    TZAVG_ON,                       /*!<Enable Pressure Mean average for Z1 and Z2 function */
    TZAVG_OFF,                      /*!<Disable Pressure Mean average for Z1 and Z2 function */

    NAC_ON,                         /*!<Enable Normal AD Conversion */
    NAC_OFF,                            /*!<Disable Normal AD Conversion */
    SWITCH_CH,                       /*!<Switch Channel */
} ADC_CMD;

/*@}*/ /* end of group ADC_EXPORTED_CONSTANTS */

/** @addtogroup ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

int adcOpen(void);
int adcOpen2(uint32_t freq);
int adcClose(void);
int adcReadXY(short *bufX, short *bufY, int dataCnt);
int adcReadZ(short *bufZ1, short *bufZ2, int dataCnt);
int adcIoctl(ADC_CMD cmd, int arg1, int arg2);
int adcChangeChannel(int channel);

/*@}*/ /* end of group ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ADC_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_ADC_H__
