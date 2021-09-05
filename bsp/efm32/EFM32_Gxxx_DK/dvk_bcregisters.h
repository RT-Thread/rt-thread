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

/**************************************************************************//**
 * Defines FPGA register bank for Energy Micro Development Kit (DVK) board,
 * i.e. board control registers
 *****************************************************************************/
#define BC_FLASH_BASE        0x80000000 /**< FLASH memory base address */
#define BC_SRAM_BASE         0x84000000 /**< SRAM base address */
#define BC_SSD2119_BASE      0x88000000 /**< TFT Controller base address */
#define BC_REGISTER_BASE     0x8c000000 /**< Board Controller registers base address */

#define BC_CFG               ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x00)) /**< CFG */
#define BC_EM                ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x01)) /**< EM */
#define BC_MAGIC             ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x02)) /**< MAGIC */
#define BC_LED               ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x03)) /**< LEDs */
#define BC_PUSHBUTTON        ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x04)) /**< Push Buttons */
#define BC_DIPSWITCH         ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x05)) /**< Dip switches */
#define BC_JOYSTICK          ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x06)) /**< Joystick */
#define BC_AEM               ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x07)) /**< AEM push button status */
#define BC_DISPLAY_CTRL      ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x08)) /**< Display Control */
#define BC_EBI_CFG           ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x09)) /**< EBI config */
#define BC_BUS_CFG           ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x0a)) /**< BUS config */
#define BC_PERCTRL           ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x0c)) /**< Peripheral Control */
#define BC_AEMSTATE          ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x0d)) /**< AEM state of push button switch */
#define BC_SPI_CFG           ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x0e)) /**< SPI config */
#define BC_RESET             ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x0f)) /**< Reset */
#define BC_ADC_START         ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x10)) /**< ADC start */
#define BC_ADC_STATUS        ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x11)) /**< ADC status */
#define BC_ADC_DATA          ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x12)) /**< ADC data */
#define BC_HW_VERSION        ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x14)) /**< HW version */
#define BC_FW_BUILDNO        ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x15)) /**< FW build number */
#define BC_FW_VERSION        ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x16)) /**< FW version */
#define BC_SCRATCH_COMMON    ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x17)) /**< Scratch common */
#define BC_SCRATCH_EFM0      ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x18)) /**< Scratch EFM0 */
#define BC_SCRATCH_EFM1      ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x19)) /**< Scratch EFM1 */
#define BC_SCRATCH_EFM2      ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x1A)) /**< Scratch EFM2 */
#define BC_SCRATCH_EFM3      ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x1B)) /**< Scratch EFM3 */
#define BC_SCRATCH_BC0       ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x1C)) /**< Scratch BC0 */
#define BC_SCRATCH_BC1       ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x1D)) /**< Scratch BC1 */
#define BC_SCRATCH_BC2       ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x1E)) /**< Scratch BC2 */
#define BC_SCRATCH_BC3       ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x1f)) /**< Scratch BC3 */
#define BC_INTFLAG           ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x20)) /**< Interrupt flag */
#define BC_INTEN             ((volatile uint16_t *)(BC_REGISTER_BASE + sizeof(uint16_t) * 0x21)) /**< Interrupt enable */

/**************************************************************************//**
 * Defines bit fields for board control registers
 *****************************************************************************/

#define BC_CFG_SPI                           (0) /**< SPI mode */
#define BC_CFG_EBI                           (1) /**< EBI mode */

#define BC_EM_EM0                            (0) /**< Indicate EM0 */
#define BC_EM_EM1                            (1) /**< Indicate EM1 */
#define BC_EM_EM2                            (2) /**< Indicate EM2 */
#define BC_EM_EM3                            (3) /**< Indicate EM3 */
#define BC_EM_EM4                            (4) /**< Indicate EM4 */

#define BC_MAGIC_VALUE                       (0xef32) /**< Magic */

#define BC_PUSHBUTTON_MASK                   (0x000f) /**< Push button mask */
#define BC_PUSHBUTTON_SW1                    (1 << 0) /**< Push button SW1 */
#define BC_PUSHBUTTON_SW2                    (1 << 1) /**< Push button SW2 */
#define BC_PUSHBUTTON_SW3                    (1 << 2) /**< Push button SW3 */
#define BC_PUSHBUTTON_SW4                    (1 << 3) /**< Push button SW4 */

#define BC_DIPSWITCH_MASK                    (0x00ff) /**< Dip switch mask */

#define BC_JOYSTICK_MASK                     (0x001f) /**< Joystick mask */
#define BC_JOYSTICK_DOWN                     (1 << 0) /**< Joystick down */
#define BC_JOYSTICK_RIGHT                    (1 << 1) /**< Joystick right */
#define BC_JOYSTICK_UP                       (1 << 2) /**< Joystick up */
#define BC_JOYSTICK_LEFT                     (1 << 3) /**< Joystick left */
#define BC_JOYSTICK_CENTER                   (1 << 4) /**< Joystick center button */

#define BC_DISPCTRL_RESET                    (1 << 0) /**< Reset */
#define BC_DISPCTRL_POWER_ENABLE             (1 << 1) /**< Display Control Power Enable */

#define BC_EBI_CFG_MASK                      (0x0003) /**< EBI Config */
#define BC_EBI_CFG_16X16                     (0) /**< 16x16 address/data mode */
#define BC_EBI_CFG_8X8                       (1) /**< 8x8 address/data mode */
#define BC_EBI_CFG_24X8                      (2) /**< 24x8 address/data mode */

#define BC_BUS_CFG_MASK                      (0x0003) /**< Bus config */
#define BC_BUS_CFG_FSMC                      (0) /**< Kit Board Controller owns bus */
#define BC_BUS_CFG_EBI                       (1) /**< EBI drives bus */
#define BC_BUS_CFG_SPI                       (2) /**< SPI drives bus */

#define BC_PERCTRL_ACCEL                     (1 << 0) /**< Accelerometer enable */
#define BC_PERCTRL_AMBIENT                   (1 << 1) /**< Ambient light sensor enable */
#define BC_PERCTRL_POTMETER                  (1 << 2) /**< Potentiometer enable */
#define BC_PERCTRL_RS232A                    (1 << 3) /**< RS232A enable */
#define BC_PERCTRL_RS232B                    (1 << 4) /**< RS232B enable */
#define BC_PERCTRL_SPI                       (1 << 5) /**< SPI enable */
#define BC_PERCTRL_I2C                       (1 << 6) /**< I2C enable */
#define BC_PERCTRL_IRDA                      (1 << 7) /**< IRDA enable */
#define BC_PERCTRL_ANALOG_SE                 (1 << 8) /**< Analog SE enable */
#define BC_PERCTRL_ANALOG_DIFF               (1 << 9) /**< Analog Diff enable */
#define BC_PERCTRL_AUDIO_OUT                 (1 << 10) /**< Audio Out enable */
#define BC_PERCTRL_AUDIO_IN                  (1 << 11) /**< Audio In enable */
#define BC_PERCTRL_ACCEL_GSEL                (1 << 12) /**< Accel Gsel enable */
#define BC_PERCTRL_ACCEL_SELFTEST            (1 << 13) /**< Accel Self test enable */
#define BC_PERCTRL_RS232_SHUTDOWN            (1 << 14) /**< RS232 shutdown */
#define BC_PERCTRL_IRDA_SHUTDOWN             (1 << 15) /**< IRDA shutdown */

#define BC_AEMSTATE_BC                       (0) /**< AEM button state, BC controls buttons */
#define BC_AEMSTATE_EFM                      (1) /**< AEM button state, EFM32 controls buttons */

#define BC_SPI_CFG_FLASH                     (0) /**< SPI Flash config */
#define BC_SPI_CFG_MICROSD                   (1) /**< SPI MicroSD config */

#define BC_RESET_FLASH                       (1 << 0) /**< Reset Flash */
#define BC_RESET_EFM                         (1 << 1) /**< Reset EFM */

#define BC_ADC_START_MASK                    (0x00ff) /**< ADC Start mask */

#define BC_ADC_STATUS_DONE                   (0) /**< ADC Status Done */
#define BC_ADC_STATUS_BUSY                   (1) /**< ADC Status Busy */

#define BC_HW_VERSION_PCB_MASK               (0x07f0) /**< PCB Version mask */
#define BC_HW_VERSION_PCB_SHIFT              (4) /**< PCB Version shift */
#define BC_HW_VERSION_BOARD_MASK             (0x000f) /**< Board version mask */
#define BC_HW_VERSION_BOARD_SHIFT            (0) /**< Board version shift  */

#define BC_HW_FW_VERSION_MAJOR_MASK          (0xf000) /**< FW Version major mask */
#define BC_HW_FW_VERSION_MAJOR_SHIFT         (12) /**< FW version major shift */
#define BC_HW_FW_VERSION_MINOR_MASK          (0x0f00) /**< FW version minor mask */
#define BC_HW_FW_VERSION_MINOR_SHIFT         (8) /**< FW version minor shift */
#define BC_HW_FW_VERSION_PATCHLEVEL_MASK     (0x00ff) /**< FW Patchlevel mask */
#define BC_HW_FW_VERSION_PATCHLEVEL_SHIFT    (0) /**< FW Patchlevel shift */

#define BC_INTEN_MASK                        (0x000f) /**< Interrupt enable mask */
#define BC_INTEN_PB                          (1 << 0) /**< Push Button Interrupt enable */
#define BC_INTEN_DIP                         (1 << 1) /**< DIP Switch Interrupt enable */
#define BC_INTEN_JOYSTICK                    (1 << 2) /**< Joystick Interrupt enable */
#define BC_INTEN_AEM                         (1 << 3) /**< AEM Interrupt enable */

#define BC_INTFLAG_MASK                      (0x000f) /**< Interrupt flag mask */
#define BC_INTFLAG_PB                        (1 << 0) /**< Push Button interrupt triggered */
#define BC_INTFLAG_DIP                       (1 << 1) /**< DIP interrupt triggered */
#define BC_INTFLAG_JOYSTICK                  (1 << 2) /**< Joystick interrupt triggered */
#define BC_INTFLAG_AEM                       (1 << 3) /**< AEM interrupt triggered */

#endif

/** @} (end group BSP) */
