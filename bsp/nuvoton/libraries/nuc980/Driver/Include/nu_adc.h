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
typedef INT32(*ADC_CALLBACK)(UINT32 status, UINT32 userData);
/// @endcond HIDDEN_SYMBOLS
/*---------------------------------------------------------------------------------------------------------*/
/* ADC_CTL constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_CTL_ADEN            0x00000001  /*!< ADC Power Control */
#define ADC_CTL_VBGEN           0x00000002  /*!< ADC Internal Bandgap Power Control */
#define ADC_CTL_MST             0x00000100  /*!< Menu Start Conversion */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_CONF constant definitions                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_CONF_NACEN          0x00000004  /*!< Normal AD Conversion Enable */
#define ADC_CONF_SELFTEN        0x00000400  /*!< Selft Test Enable */
#define ADC_CONF_HSPEED         (1<<22)     /*!< High Speed Enable */

#define ADC_CONF_CHSEL_Pos      12          /*!< Channel Selection Position */
#define ADC_CONF_CHSEL_Msk      (0xF<<ADC_CONF_CHSEL_Pos)   /*!< Channel Selection Mask */

#define ADC_CONF_REFSEL_Pos     6           /*!< Reference Selection Position */
#define ADC_CONF_REFSEL_Msk     (3<<6)      /*!< Reference Selection Mask */
#define ADC_CONF_REFSEL_VREF    (0<<6)      /*!< ADC reference select VREF input */
#define ADC_CONF_REFSEL_AVDD33  (3<<6)      /*!< ADC reference select AGND33 vs AVDD33 */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_IER constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_IER_MIEN            0x00000001  /*!< Menu Interrupt Enable */

/*---------------------------------------------------------------------------------------------------------*/
/* ADC_ISR constant definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define ADC_ISR_MF              0x00000001  /*!< Menu Complete Flag */
#define ADC_ISR_NACF            0x00000400  /*!< Normal AD Conversion Finish */


/** \brief  Structure type of ADC_CMD
 */
typedef enum
{
    START_MST,                       /*!<Menu Start Conversion */
    VBPOWER_ON,                      /*!<Enable ADC Internal Bandgap Power */
    VBPOWER_OFF,                     /*!<Disable ADC Internal Bandgap Power */
    NAC_ON,                          /*!<Enable Normal AD Conversion */
    NAC_OFF,                         /*!<Disable Normal AD Conversion */
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
