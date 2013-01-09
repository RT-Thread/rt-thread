/**************************************************************************//**
 * @file
 * @brief Board Control register definitions
 * @author Energy Micro AS
 * @version 2.0.1
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#ifndef __DVK_BCREGISTERS_H
#define __DVK_BCREGISTERS_H

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************//**
 * Defines FPGA register bank for Energy Micro Development Kit (DVK) board,
 * i.e. board control registers
 *****************************************************************************/
#define BC_REGISTER_BASE    0x80000000  /**< Board Controller registers base address */
#define BC_SSD2119_BASE     0x84000000  /**< TFT-LCD controller */
#define BC_PSRAM_BASE       0x88000000  /**< PSRAM base address */
#define BC_FLASH_BASE       0x8C000000  /**< External Flash base address */


/**************************************************************************//**
 * Defines bit fields for board control registers
 *****************************************************************************/

/* Define registers in a similar manner to CMSIS standards */
/** Read/Write board controller register */
#define __IO    volatile

/** Board Controller Register definiton */
typedef struct
{
  __IO uint16_t RESERVERD0;        /**< 0x00 - Reserved */
  __IO uint16_t EM;                /**< 0x02 - Energy Mode indicator  */
  __IO uint16_t MAGIC;             /**< 0x04 - Should always read 0xEF32 */

  __IO uint16_t UIF_LEDS;          /**< 0x06 - On board LEDs */
  __IO uint16_t UIF_PB;            /**< 0x08 - Push button PB0-PB4 status */
  __IO uint16_t UIF_DIP;           /**< 0x0A - DIP switch status */
  __IO uint16_t UIF_JOYSTICK;      /**< 0x0C - Joystick presses */
  __IO uint16_t UIF_AEM;           /**< 0x0E - AEM button */
  __IO uint16_t UIF_CTRL;          /**< 0x10 - CPLD control register */
  __IO uint16_t DISPLAY_CTRL;      /**< 0x12 - SSD2119 TFT display control */
  __IO uint16_t EBI_CTRL;          /**< 0x14 - Extended Address Mode control */
  __IO uint16_t ARB_CTRL;          /**< 0x16 - Arbiter control, board control or EFM32GG access to display */
  __IO uint16_t PERICON;           /**< 0x18 - Peripheral Control, on board switches */
  __IO uint16_t SPI_DEMUX;         /**< 0x1A - SPI DEMUX */
  __IO uint16_t RESERVERD1[0x02];  /**< 0x1C - Reserved */

  __IO uint16_t ADC_WRITE;         /**< 0x20 - AEM ADC SPI interface */
  __IO uint16_t ADC_STATUS;        /**< 0x22 - AEM ADC SPI interface */
  __IO uint16_t ADC_READ;          /**< 0x24 - AEM ADC SPI interface */

  __IO uint16_t CLKRST;            /**< 0x26 - Clock and reset control */

  __IO uint16_t HW_VERSION;        /**< 0x28 - Hardware version */
  __IO uint16_t FW_BUILDNO;        /**< 0x2A - Firmware build number */
  __IO uint16_t FW_VERSION;        /**< 0x2C - Firmware version */

  __IO uint16_t SCRATCH_COMMON;    /**< 0x2E - Shared register between board controller and EFM32 */

  __IO uint16_t SCRATCH_EFM0;      /**< 0x30 - EFM32 accessible registers */
  __IO uint16_t SCRATCH_EFM1;      /**< 0x32 */
  __IO uint16_t SCRATCH_EFM2;      /**< 0x34 */
  __IO uint16_t SCRATCH_EFM3;      /**< 0x36 */

  __IO uint16_t SCRATCH_BC0;       /**< 0x38 - Board Control registers */
  __IO uint16_t SCRATCH_BC1;       /**< 0x3A */
  __IO uint16_t SCRATCH_BC2;       /**< 0x3C */
  __IO uint16_t SCRATCH_BC3;       /**< 0x3E */

  __IO uint16_t INTFLAG;           /**< 0x40 - Interrupt Status flags */
  __IO uint16_t INTEN;             /**< 0x42 - Interrupt Enable flags */

  __IO uint16_t RESERVERD3[0x1e];  /**< 0x44 - Reserved */

  __IO uint16_t BC_MBOX_TXCTRL;    /**< 0x80 - BC <-> EFM32 communication channel */
  __IO uint16_t BC_MBOX_TXDATA;    /**< 0x82 */
  __IO uint16_t BC_MBOX_TXSTATUS0; /**< 0x84 */
  __IO uint16_t BC_MBOX_TXSTATUS1; /**< 0x86 */

  __IO uint16_t RESERVED4[0x0d];   /**< 0xa0 - Reserved */

  __IO uint16_t MBOX_TXCTRL;       /**< 0xa2 - BC <-> EFM32 communication channel */
  __IO uint16_t MBOX_TXDATA;       /**< 0xa4 */
  __IO uint16_t MBOX_TXSTATUS0;    /**< 0xa6 */
  __IO uint16_t MBOX_TXSTATUS1;    /**< 0xa8 */

  __IO uint16_t RESERVED5[0x0b];   /**< 0xaa - Reserved */

  __IO uint16_t BUF_CTRL;          /**< 0xc0 - Buffer Controller Control */
} BC_TypeDef;

/* Cast into register structure */
#define BC_REGISTER                         ((BC_TypeDef *) BC_REGISTER_BASE) /**< Register block base */

/* Energy Mode indicator */
#define BC_EM_EM0                           (0)  /**< Indicate EM0 */
#define BC_EM_EM1                           (1)  /**< Indicate EM1 */
#define BC_EM_EM2                           (2)  /**< Indicate EM2 */
#define BC_EM_EM3                           (3)  /**< Indicate EM3 */
#define BC_EM_EM4                           (4)  /**< Indicate EM4 */

/* Magic value */
#define BC_MAGIC_VALUE                      (0xef32)  /**< Magic */

/* Push buttons, PB1-PB4 */
#define BC_UIF_PB_MASK                      (0x000f) /**< Push button mask */
#define BC_UIF_PB1                          (1 << 0) /**< Push button PB1 */
#define BC_UIF_PB2                          (1 << 1) /**< Push button PB2 */
#define BC_UIF_PB3                          (1 << 2) /**< Push button PB3 */
#define BC_UIF_PB4                          (1 << 3) /**< Push button PB4 */

/* Dip switch */
#define BC_DIPSWITCH_MASK                   (0x000f)  /**< Dip switch mask */

/* Joystick directions */
#define BC_UIF_JOYSTICK_MASK                (0x001f)      /**< Joystick mask */
#define BC_UIF_JOYSTICK_DOWN                (1 << 0)      /**< Joystick down */
#define BC_UIF_JOYSTICK_RIGHT               (1 << 1)      /**< Joystick right */
#define BC_UIF_JOYSTICK_UP                  (1 << 2)      /**< Joystick up */
#define BC_UIF_JOYSTICK_LEFT                (1 << 3)      /**< Joystick left */
#define BC_UIF_JOYSTICK_CENTER              (1 << 4)      /**< Joystick center button */

/* AEM state */
#define BC_UIF_AEM_BC                       (0) /**< AEM button state, BC controls buttons */
#define BC_UIF_AEM_EFM                      (1) /**< AEM button state, EFM32 controls buttons */

/* Display control */
#define BC_DISPLAY_CTRL_RESET               (1 << 1)                          /**< Reset */
#define BC_DISPLAY_CTRL_POWER_ENABLE        (1 << 0)                          /**< Display Control Power and Backlight Enable */
#define BC_DISPLAY_CTRL_MODE_SHIFT          2                                 /**< Bit offset value for Display_Mode setting */
#define BC_DISPLAY_CTRL_MODE_8080           (0 << BC_DISPLAY_CTRL_MODE_SHIFT) /**< Address mapped mode */
#define BC_DISPLAY_CTRL_MODE_GENERIC        (1 << BC_DISPLAY_CTRL_MODE_SHIFT) /**< Direct Drive + SPI mode */

/* EBI control - extended address range enable bit  */
#define BC_EBI_CTRL_EXTADDR_MASK            (0x0001) /**< Enable extended addressing support */

/* Arbiter control - directs access to display controller  */
#define BC_ARB_CTRL_SHIFT                   0 /**< Bit offset value for ARB_CTRL setting */
#define BC_ARB_CTRL_BC                      (0 << BC_ARB_CTRL_SHIFT) /**< BC drives display */
#define BC_ARB_CTRL_EBI                     (1 << BC_ARB_CTRL_SHIFT) /**< EFM32GG EBI drives display, memory mapped or direct drive */
#define BC_ARB_CTRL_SPI                     (2 << BC_ARB_CTRL_SHIFT) /**< EFM32GG SPI drives display */

/* Interrupt flag registers, INTEN and INTFLAG */
#define BC_INTEN_MASK                       (0x000f)  /**< Interrupt enable mask */
#define BC_INTEN_PB                         (1 << 0)  /**< Push Button Interrupt enable */
#define BC_INTEN_DIP                        (1 << 1)  /**< DIP Switch Interrupt enable */
#define BC_INTEN_JOYSTICK                   (1 << 2)  /**< Joystick Interrupt enable */
#define BC_INTEN_AEM                        (1 << 3)  /**< AEM Interrupt enable */
#define BC_INTEN_ETH                        (1 << 4)  /**< Ethernet Interrupt enable */

#define BC_INTFLAG_MASK                     (0x000f)  /**< Interrupt flag mask */
#define BC_INTFLAG_PB                       (1 << 0)  /**< Push Button interrupt triggered */
#define BC_INTFLAG_DIP                      (1 << 1)  /**< DIP interrupt triggered */
#define BC_INTFLAG_JOYSTICK                 (1 << 2)  /**< Joystick interrupt triggered */
#define BC_INTFLAG_AEM                      (1 << 3)  /**< AEM Interrupt triggered */
#define BC_INTFLAG_ETH                      (1 << 4)  /**< Ethernet Interrupt triggered */

/* Peripheral control registers */
#define BC_PERICON_RS232_SHUTDOWN_SHIFT     13 /**< RS232 enable MUX bit */
#define BC_PERICON_RS232_UART_SHIFT         12 /**< UART enable */
#define BC_PERICON_RS232_LEUART_SHIFT       11 /**< LEUART enable */
#define BC_PERICON_I2C_SHIFT                10 /**< I2C enable */
#define BC_PERICON_I2S_ETH_SEL_SHIFT        9 /**< I2S/ETH/TFT SPI enable */
#define BC_PERICON_I2S_ETH_SHIFT            8 /**< I2S/ETH mux select */
#define BC_PERICON_TRACE_SHIFT              7 /**< ETM Trace enable */
#define BC_PERICON_TOUCH_SHIFT              6 /**< Touch enable */
#define BC_PERICON_AUDIO_IN_SHIFT           5 /**< Audio In enable */
#define BC_PERICON_AUDIO_OUT_SEL_SHIFT      4 /**< Audio Out I2S/DAC select */
#define BC_PERICON_AUDIO_OUT_SHIFT          3 /**< Audio Out enable */
#define BC_PERICON_ANALOG_DIFF_SHIFT        2 /**< Analog Diff enable */
#define BC_PERICON_ANALOG_SE_SHIFT          1 /**< Anallog SE enable */
#define BC_PERICON_SPI_SHIFT                0 /**< Micro-SD SPI enable */

/* SPI DEMUX control */
#define BC_SPI_DEMUX_SLAVE_MASK             (0x0003) /**< Mask for SPI MUX bits */
#define BC_SPI_DEMUX_SLAVE_AUDIO            (0) /**< SPI interface to I2S Audio */
#define BC_SPI_DEMUX_SLAVE_ETHERNET         (1) /**< SPI interface to Ethernet controller */
#define BC_SPI_DEMUX_SLAVE_DISPLAY          (2) /**< SPI interface to TFT-LCD-SSD2119 controller */

/* ADC */
#define BC_ADC_STATUS_DONE                  (0)  /**< ADC Status Done */
#define BC_ADC_STATUS_BUSY                  (1)  /**< ADC Status Busy */

/* Clock and Reset Control */
#define BC_CLKRST_FLASH_SHIFT               (1 << 1) /**< Flash Reset Control */
#define BC_CLKRST_ETH_SHIFT                 (1 << 2) /**< Ethernet Reset Control */

/* Hardware version information */
#define BC_HW_VERSION_PCB_MASK              (0x07f0)  /**< PCB Version mask */
#define BC_HW_VERSION_PCB_SHIFT             (4)       /**< PCB Version shift */
#define BC_HW_VERSION_BOARD_MASK            (0x000f)  /**< Board version mask */
#define BC_HW_VERSION_BOARD_SHIFT           (0)       /**< Board version shift  */

/* Firmware version information */
#define BC_FW_VERSION_MAJOR_MASK            (0xf000) /**< FW Version major mask */
#define BC_FW_VERSION_MAJOR_SHIFT           (12)     /**< FW version major shift */
#define BC_FW_VERSION_MINOR_MASK            (0x0f00) /**< FW version minor mask */
#define BC_FW_VERSION_MINOR_SHIFT           (8)      /**< FW version minor shift */
#define BC_FW_VERSION_PATCHLEVEL_MASK       (0x00ff) /**< FW Patchlevel mask */
#define BC_FW_VERSION_PATCHLEVEL_SHIFT      (0)      /**< FW Patchlevel shift */

/* MBOX - BC <-> EFM32 communication */
#define BC_MBOX_TXSTATUS0_FIFOEMPTY         (1 << 0) /**< BC/EFM32 communication register */
#define BC_MBOX_TXSTATUS0_FIFOFULL          (1 << 1) /**< BC/EFM32 communication register */
#define BC_MBOX_TXSTATUS0_FIFOUNDERFLOW     (1 << 4) /**< BC/EFM32 communication register */
#define BC_MBOX_TXSTATUS0_FIFOOVERFLOW      (1 << 5) /**< BC/EFM32 communication register */

#define BC_MBOX_TXSTATUS1_WORDCOUNT_MASK    (0x07FF) /**< BC/EFM32 communication register */

/* Buffer Controller */
#define BC_BUF_CTRL_CS_ENABLE               (1 << 0) /**< BC/EFM32 communication register */

#ifdef __cplusplus
}
#endif

/** @} (end group BSP) */

#endif
