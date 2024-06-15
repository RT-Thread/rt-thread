/**********************************************************************
* $Id$      lpc177x_8x_pinsel.h         2011-06-02
*//**
* @file     lpc177x_8x_pinsel.h
* @brief    Contains all macro definitions and function prototypes
*           support for Pin-connection block firmware library on LPC177x_8x
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
*
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup PINSEL    Pin Selection
 * @ingroup LPC177x_8xCMSIS_FwLib_Drivers
 * @{
 */

#ifndef __LPC177X_8X_PINSEL_H
#define __LPC177X_8X_PINSEL_H

/* Includes ------------------------------------------------------------------- */
#include "LPC177x_8x.h"
#include "lpc_types.h"


/* Public Macros -------------------------------------------------------------- */
/** @defgroup PINSEL_Public_Macros
 * @{
 */

/* Macros define IOCON bits */
#define IOCON_MODE_PLAIN            ((0<<3))
#define IOCON_MODE_PULLDOWN         ((1<<3))
#define IOCON_MODE_PULLUP           ((2<<3))
#define IOCON_MODE_REPEATER         ((3<<3))
#define IOCON_HYS                   ((1<<5))
#define IOCON_SLEW                  ((1<<6))
#define IOCON_INBUF                 ((1<<7))
#define IOCON_I2CMODE_FAST          ((0<<8))
#define IOCON_I2CMODE_OPENDRAIN     ((1<<8))
#define IOCON_I2CMODE_FASTPLUS      ((2<<8))
#define IOCON_I2CMODE_HIGHOPENDRAIN ((3<<8))
#define IOCON_ODMODE                ((1<<10))


/* Macros define for LOC registers */
#define LOC_CAN_RD_1_P0_0           ((0))   /**< Input for CAN_RD_1 comes from P0.0 */
#define LOC_CAN_RD_1_P0_21          ((1))   /**< Input for CAN_RD_1 comes from P0.21 */
#define LOC_CAN_RD_2_P2_7           ((0))   /**< Input for CAN_RD_2 comes from P2.7 */
#define LOC_CAN_RD_2_P0_4           ((1))   /**< Input for CAN_RD_2 comes from P0.4 */
#define LOC_ENET_MDIO_P2_9          ((0))   /**< Input for ENET_MDIO comes from P2.9 */
#define LOC_ENET_MDIO_P1_17         ((1))   /**< Input for ENET_MDIO comes from P1.17 */
#define LOC_EINT_0_P0_29            ((0))   /**< Input for EINT_0 comes from P0.29 */
#define LOC_EINT_0_P2_10            ((1))   /**< Input for EINT_0 comes from P2.10 */
#define LOC_EINT_1_P0_30            ((0))   /**< Input for EINT_1 comes from P0.30 */
#define LOC_EINT_1_P2_11            ((1))   /**< Input for EINT_1 comes from P2.11 */
#define LOC_I2C0_SCL_P1_31          ((0))   /**< Input for I2C0_SCL comes from P1.31 */
#define LOC_I2C0_SCL_P0_28          ((1))   /**< Input for I2C0_SCL comes from P0.28 */
#define LOC_I2C0_SCL_P5_3           ((2))   /**< Input for I2C0_SCL comes from P5.3 */
#define LOC_I2C0_SDA_P1_30          ((0))   /**< Input for I2C0_SDA comes from P1.30 */
#define LOC_I2C0_SDA_P0_27          ((1))   /**< Input for I2C0_SDA comes from P0.27 */
#define LOC_I2C0_SDA_P5_2           ((2))   /**< Input for I2C0_SDA comes from P5.2 */
#define LOC_I2C1_SCL_P0_1           ((0))   /**< Input for I2C1_SCL comes from P0.1 */
#define LOC_I2C1_SCL_P2_15          ((1))   /**< Input for I2C1_SCL comes from P2.15 */
#define LOC_I2C1_SCL_P0_20          ((2))   /**< Input for I2C1_SCL comes from P0.20 */
#define LOC_I2C1_SDA_P2_14          ((0))   /**< Input for I2C1_SDA comes from P2.14 */
#define LOC_I2C1_SDA_P0_0           ((1))   /**< Input for I2C1_SDA comes from P0.0 */
#define LOC_I2C1_SDA_P0_19          ((2))   /**< Input for I2C1_SDA comes from P0.19 */
#define LOC_I2C2_SCL_P2_31          ((0))   /**< Input for I2C2_SCL comes from P2.31 */
#define LOC_I2C2_SCL_P0_11          ((1))   /**< Input for I2C2_SCL comes from P0.11 */
#define LOC_I2C2_SCL_P4_21          ((2))   /**< Input for I2C2_SCL comes from P4.21 */
#define LOC_I2C2_SCL_P4_29          ((3))   /**< Input for I2C2_SCL comes from P4.29 */
#define LOC_I2C2_SDA_P2_30          ((0))   /**< Input for I2C2_SDA comes from P2.30 */
#define LOC_I2C2_SDA_P0_10          ((1))   /**< Input for I2C2_SDA comes from P0.10 */
#define LOC_I2C2_SDA_P4_20          ((2))   /**< Input for I2C2_SDA comes from P4.20 */
#define LOC_I2C2_SDA_P1_15          ((3))   /**< Input for I2C2_SDA comes from P1.15 */
#define LOC_I2S_RX_SCK_P0_23        ((0))   /**< Input for I2S_RX_SCK comes from P0.23 */
#define LOC_I2S_RX_SCK_P0_4         ((1))   /**< Input for I2S_RX_SCK comes from P0.4 */
#define LOC_I2S_RX_SDA_P0_25        ((0))   /**< Input for I2S_RX_SDA comes from P0.25 */
#define LOC_I2S_RX_SDA_P0_6         ((1))   /**< Input for I2S_RX_SDA comes from P0.6 */
#define LOC_I2S_RX_WS_P0_24         ((0))   /**< Input for I2S_RX_WS comes from P0.24 */
#define LOC_I2S_RX_WS_P0_5          ((1))   /**< Input for I2S_RX_WS comes from P0.5 */
#define LOC_I2S_TX_SCK_P2_11        ((0))   /**< Input for I2S_TX_SCK comes from P2.11 */
#define LOC_I2S_TX_SCK_P0_7         ((1))   /**< Input for I2S_TX_SCK comes from P0.7 */
#define LOC_I2S_TX_WS_P2_12         ((0))   /**< Input for I2S_TX_WS comes from P2.12 */
#define LOC_I2S_TX_WS_P0_8          ((1))   /**< Input for I2S_TX_WS comes from P0.8 */
#define LOC_PWM0_CAP_0_P1_12        ((0))   /**< Input for PWM0_CAP_0 comes from P1.12 */
#define LOC_PWM0_CAP_0_P3_22        ((1))   /**< Input for PWM0_CAP_0 comes from P3.22 */
#define LOC_PWM1_CAP_0_P3_23        ((0))   /**< Input for PWM1_CAP_0 comes from P3.23 */
#define LOC_PWM1_CAP_0_P1_28        ((1))   /**< Input for PWM1_CAP_0 comes from P1.28 */
#define LOC_PWM1_CAP_0_P2_6         ((2))   /**< Input for PWM1_CAP_0 comes from P2.6 */
#define LOC_SD_CMD_P0_20            ((0))   /**< Input for SD_CMD comes from P0.20 */
#define LOC_SD_CMD_P1_3             ((1))   /**< Input for SD_CMD comes from P1.3 */
#define LOC_SD_DAT_0_P0_22          ((0))   /**< Input for SD_DAT_0 comes from P0.22 */
#define LOC_SD_DAT_0_P1_6           ((1))   /**< Input for SD_DAT_0 comes from P1.6 */
#define LOC_SD_DAT_1_P2_11          ((0))   /**< Input for SD_DAT_1 comes from P2.11 */
#define LOC_SD_DAT_1_P1_7           ((1))   /**< Input for SD_DAT_1 comes from P1.7 */
#define LOC_SD_DAT_2_P2_12          ((0))   /**< Input for SD_DAT_2 comes from P2.12 */
#define LOC_SD_DAT_2_P1_11          ((1))   /**< Input for SD_DAT_2 comes from P1.11 */
#define LOC_SD_DAT_3_P2_13          ((0))   /**< Input for SD_DAT_3 comes from P2.13 */
#define LOC_SD_DAT_3_P1_12          ((1))   /**< Input for SD_DAT_3 comes from P1.12 */
#define LOC_SSP0_MISO_P2_26         ((0))   /**< Input for SSP0_MISO comes from P2.26 */
#define LOC_SSP0_MISO_P1_23         ((1))   /**< Input for SSP0_MISO comes from P1_23 */
#define LOC_SSP0_MISO_P0_17         ((2))   /**< Input for SSP0_MISO comes from P0_17 */
#define LOC_SSP0_MOSI_P2_27         ((0))   /**< Input for SSP0_MOSI comes from P2.27 */
#define LOC_SSP0_MOSI_P1_24         ((1))   /**< Input for SSP0_MOSI comes from P1.24 */
#define LOC_SSP0_MOSI_P0_18         ((2))   /**< Input for SSP0_MOSI comes from P0.18 */
#define LOC_SSP0_SCK_P1_20          ((0))   /**< Input for SSP0_SCK comes from P1.20 */
#define LOC_SSP0_SCK_P2_22          ((1))   /**< Input for SSP0_SCK comes from P2.22 */
#define LOC_SSP0_SCK_P0_15          ((2))   /**< Input for SSP0_SCK comes from P0_15 */
#define LOC_SSP0_SSEL_P2_23         ((0))   /**< Input for SSP0_SSEL comes from P2.23 */
#define LOC_SSP0_SSEL_P1_21         ((1))   /**< Input for SSP0_SSEL comes from P1.21 */
#define LOC_SSP0_SSEL_P1_28         ((2))   /**< Input for SSP0_SSEL comes from P1.28 */
#define LOC_SSP0_SSEL_P0_16         ((3))   /**< Input for SSP0_SSEL comes from P0.16 */
#define LOC_SSP1_MISO_P0_12         ((0))   /**< Input for SSP1_MISO comes from P0.12 */
#define LOC_SSP1_MISO_P1_18         ((1))   /**< Input for SSP1_MISO comes from P1.18 */
#define LOC_SSP1_MISO_P4_22         ((2))   /**< Input for SSP1_MISO comes from P4_22 */
#define LOC_SSP1_MISO_P0_8          ((3))   /**< Input for SSP1_MISO comes from P0.8 */
#define LOC_SSP1_MOSI_P0_13         ((0))   /**< Input for SSP1_MOSI comes from P0.13 */
#define LOC_SSP1_MOSI_P1_22         ((1))   /**< Input for SSP1_MOSI comes from P1.22 */
#define LOC_SSP1_MOSI_P4_23         ((2))   /**< Input for SSP1_MOSI comes from P4.23 */
#define LOC_SSP1_MOSI_P0_9          ((3))   /**< Input for SSP1_MOSI comes from P0.9 */
#define LOC_SSP1_SCK_P1_31          ((0))   /**< Input for SSP1_SCK comes from P1.31 */
#define LOC_SSP1_SCK_P1_19          ((1))   /**< Input for SSP1_SCK comes from P1.19 */
#define LOC_SSP1_SCK_P4_20          ((2))   /**< Input for SSP1_SCK comes from P4_20 */
#define LOC_SSP1_SCK_P0_7           ((3))   /**< Input for SSP1_SCK comes from P0_7 */
#define LOC_SSP1_SSEL_P0_14         ((0))   /**< Input for SSP1_SSEL comes from P0.14 */
#define LOC_SSP1_SSEL_P1_26         ((1))   /**< Input for SSP1_SSEL comes from P1.26 */
#define LOC_SSP1_SSEL_P4_21         ((2))   /**< Input for SSP1_SSEL comes from P4.21 */
#define LOC_SSP1_SSEL_P0_6          ((3))   /**< Input for SSP1_SSEL comes from P0.6 */
#define LOC_SSP2_MISO_P1_4          ((1))   /**< Input for SSP2_MISO comes from P1.4 */
#define LOC_SSP2_MOSI_P1_1          ((1))   /**< Input for SSP2_MOSI comes from P1.1 */
#define LOC_SSP2_SCK_P1_0           ((1))   /**< Input for SSP2_SCK comes from P1.0 */
#define LOC_SSP2_SSEL_P1_8          ((1))   /**< Input for SSP2_SSEL comes from P1.8 */
#define LOC_T0_CAP_0_P3_23          ((0))   /**< Input for T0_CAP_0 comes from P3.23 */
#define LOC_T0_CAP_0_P1_26          ((1))   /**< Input for T0_CAP_0 comes from P1.26 */
#define LOC_T0_CAP_1_P3_24          ((0))   /**< Input for T0_CAP_1 comes from P3.24 */
#define LOC_T0_CAP_1_P1_27          ((1))   /**< Input for T0_CAP_1 comes from P1.27 */
#define LOC_T1_CAP_0_P1_18          ((0))   /**< Input for T1_CAP_0 comes from P1.18 */
#define LOC_T1_CAP_0_P3_27          ((1))   /**< Input for T1_CAP_0 comes from P3.27 */
#define LOC_T1_CAP_1_P3_28          ((0))   /**< Input for T1_CAP_1 comes from P3.28 */
#define LOC_T1_CAP_1_P1_19          ((1))   /**< Input for T1_CAP_1 comes from P1.19 */
#define LOC_T2_CAP_0_P2_14          ((0))   /**< Input for T2_CAP_0 comes from P2.14 */
#define LOC_T2_CAP_0_P2_6           ((1))   /**< Input for T2_CAP_0 comes from P2.6 */
#define LOC_T2_CAP_0_P0_4           ((2))   /**< Input for T2_CAP_0 comes from P0.4 */
#define LOC_T2_CAP_0_P1_14          ((3))   /**< Input for T2_CAP_0 comes from P1.14 */
#define LOC_T2_CAP_1_P2_15          ((0))   /**< Input for T2_CAP_1 comes from P2.15 */
#define LOC_T2_CAP_1_P0_5           ((1))   /**< Input for T2_CAP_1 comes from P0.5 */
#define LOC_T3_CAP_0_P0_23          ((0))   /**< Input for T3_CAP_0 comes from P0.23 */
#define LOC_T3_CAP_0_P2_22          ((1))   /**< Input for T3_CAP_0 comes from P2.22 */
#define LOC_T3_CAP_0_P1_10          ((2))   /**< Input for T3_CAP_0 comes from P1.10 */
#define LOC_T3_CAP_1_P0_24          ((0))   /**< Input for T3_CAP_1 comes from P0.24 */
#define LOC_T3_CAP_1_P2_23          ((1))   /**< Input for T3_CAP_1 comes from P2.23 */
#define LOC_T3_CAP_1_P1_0           ((2))   /**< Input for T3_CAP_1 comes from P1.0 */
#define LOC_U0_RXD_P0_1             ((0))   /**< Input for U0_RXD comes from P0.1 */
#define LOC_U0_RXD_P0_3             ((1))   /**< Input for U0_RXD comes from P0.3 */
#define LOC_U1_CTS_P0_17            ((0))   /**< Input for U1_CTS comes from P0.17 */
#define LOC_U1_CTS_P2_8             ((1))   /**< Input for U1_CTS comes from P2.8 */
#define LOC_U1_CTS_P2_2             ((2))   /**< Input for U1_CTS comes from P2.2 */
#define LOC_U1_CTS_P3_18            ((3))   /**< Input for U1_CTS comes from P3.18 */
#define LOC_U1_DCD_P0_18            ((0))   /**< Input for U1_DCD comes from P0.18 */
#define LOC_U1_DCD_P2_3             ((1))   /**< Input for U1_DCD comes from P2.3 */
#define LOC_U1_DCD_P3_19            ((2))   /**< Input for U1_DCD comes from P3_19 */
#define LOC_U1_DSR_P0_19            ((0))   /**< Input for U1_DSR comes from P0.19 */
#define LOC_U1_DSR_P2_4             ((1))   /**< Input for U1_DSR comes from P2.4 */
#define LOC_U1_DSR_P3_20            ((2))   /**< Input for U1_DSR comes from P0.19 */
#define LOC_U1_RI_P0_21             ((0))   /**< Input for U1_RI comes from P0.21 */
#define LOC_U1_RI_P2_6              ((1))   /**< Input for U1_RI comes from P2.6 */
#define LOC_U1_RI_P3_22             ((2))   /**< Input for U1_RI comes from P3.22 */
#define LOC_U1_RXD_P0_16            ((0))   /**< Input for U1_RXD comes from P0.16 */
#define LOC_U1_RXD_P3_17            ((1))   /**< Input for U1_RXD comes from P3.17 */
#define LOC_U1_RXD_P2_1             ((2))   /**< Input for U1_RXD comes from P2.1 */
#define LOC_U2_RXD_P0_11            ((0))   /**< Input for U2_RXD comes from P0.11 */
#define LOC_U2_RXD_P4_23            ((1))   /**< Input for U2_RXD comes from P4.23 */
#define LOC_U2_RXD_P2_9             ((2))   /**< Input for U2_RXD comes from P2.9 */
#define LOC_U3_RXD_P0_26            ((0))   /**< Input for U3_RXD comes from P0.26 */
#define LOC_U3_RXD_P0_1             ((1))   /**< Input for U3_RXD comes from P0.1 */
#define LOC_U3_RXD_P4_29            ((2))   /**< Input for U3_RXD comes from P4.29 */
#define LOC_U3_RXD_P0_3             ((3))   /**< Input for U3_RXD comes from P0.3 */
#define LOC_U4_RXD_P2_9             ((0))   /**< Input for U4_RXD comes from P2.9 */
#define LOC_U4_RXD_P5_3             ((1))   /**< Input for U4_RXD comes from P5.3 */
#define LOC_USB_SCL_P0_28           ((0))   /**< Input for USB_SCL comes from P0.28 */
#define LOC_USB_SCL_P1_28           ((1))   /**< Input for USB_SCL comes from P1.28 */
#define LOC_USB_SDA_P0_27           ((0))   /**< Input for USB_SDA comes from P0.27 */
#define LOC_USB_SDA_P1_29           ((1))   /**< Input for USB_SDA comes from P1.29 */

/**
 * @}
 */

/** @defgroup PINSEL_Public_Types PINSEL Public Types
 * @{
 */


typedef enum
{
    PINSEL_BASICMODE_PLAINOUT  = 0, /**< Plain output */
    PINSEL_BASICMODE_PULLDOWN,      /**< Pull-down enabled */
    PINSEL_BASICMODE_PULLUP,        /**< Pull-up enabled (default) */
    PINSEL_BASICMODE_REPEATER       /**< Repeater mode */
}PinSel_BasicMode;

typedef enum
{
    /** Fast mode (400 kHz clock rate) and standard (100 kHz clock rate) */
    PINSEL_I2CMODE_FAST_STANDARD  = 0,
    /** Open drain I/O (not I2C). No glitch filter, 3 mA typical output drive */
    PINSEL_I2CMODE_OPENDRAINIO,
    /** Fast Mode Plus I2C. This includes a filter for <50 ns glitches */
    PINSEL_I2CMODE_FASTMODEPLUS,
    /** High drive open drain I/O (not I2C). No glitch filter, 20 mA typical output drive */
    PINSEL_I2CMODE_HIDRIVE_OPENDRAIN
}PinSel_I2cMode;

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup PINSEL_Public_Functions
 * @{
 */
void PINSEL_ConfigPin(uint8_t portnum, uint8_t pinnum, uint8_t funcnum);
void PINSEL_SetPinMode(uint8_t portnum, uint8_t pinnum, PinSel_BasicMode modenum);
void PINSEL_SetHysMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetSlewMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetInBufMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetI2CMode(uint8_t portnum, uint8_t pinnum, PinSel_I2cMode I2CMode);
void PINSEL_SetOpenDrainMode(uint8_t portnum, uint8_t pinnum, FunctionalState NewState);
void PINSEL_SetAnalogPinMode (uint8_t portnum, uint8_t pinnum, uint8_t enable);
void PINSEL_DacEnable (uint8_t portnum, uint8_t pinnum, uint8_t enable);
void PINSEL_SetFilter (uint8_t portnum, uint8_t pinnum, uint8_t enable);


/**
 * @}
 */

#endif /* LPC177x_8x_PINSEL_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

