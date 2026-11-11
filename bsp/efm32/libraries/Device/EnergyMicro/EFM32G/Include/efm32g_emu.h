/**************************************************************************//**
 * @file
 * @brief efm32g_emu Register and Bit Field definitions
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
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
/**************************************************************************//**
 * @defgroup EFM32G_EMU
 * @{
 * @brief EFM32G_EMU Register Declaration
 *****************************************************************************/
typedef struct
{
  __IO uint32_t CTRL;         /**< Control Register  */
  __IO uint32_t MEMCTRL;      /**< Memory Control Register  */
  __IO uint32_t LOCK;         /**< Configuration Lock Register  */

  uint32_t      RESERVED0[6]; /**< Reserved for future use **/
  __IO uint32_t AUXCTRL;      /**< Auxiliary Control Register  */
} EMU_TypeDef;                /** @} */

/**************************************************************************//**
 * @defgroup EFM32G_EMU_BitFields
 * @{
 *****************************************************************************/

/* Bit fields for EMU CTRL */
#define _EMU_CTRL_RESETVALUE              0x00000000UL                      /**< Default value for EMU_CTRL */
#define _EMU_CTRL_MASK                    0x0000000FUL                      /**< Mask for EMU_CTRL */
#define EMU_CTRL_EMVREG                   (0x1UL << 0)                      /**< Energy Mode Voltage Regulator Control */
#define _EMU_CTRL_EMVREG_SHIFT            0                                 /**< Shift value for EMU_EMVREG */
#define _EMU_CTRL_EMVREG_MASK             0x1UL                             /**< Bit mask for EMU_EMVREG */
#define _EMU_CTRL_EMVREG_DEFAULT          0x00000000UL                      /**< Mode DEFAULT for EMU_CTRL */
#define _EMU_CTRL_EMVREG_REDUCED          0x00000000UL                      /**< Mode REDUCED for EMU_CTRL */
#define _EMU_CTRL_EMVREG_FULL             0x00000001UL                      /**< Mode FULL for EMU_CTRL */
#define EMU_CTRL_EMVREG_DEFAULT           (_EMU_CTRL_EMVREG_DEFAULT << 0)   /**< Shifted mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EMVREG_REDUCED           (_EMU_CTRL_EMVREG_REDUCED << 0)   /**< Shifted mode REDUCED for EMU_CTRL */
#define EMU_CTRL_EMVREG_FULL              (_EMU_CTRL_EMVREG_FULL << 0)      /**< Shifted mode FULL for EMU_CTRL */
#define EMU_CTRL_EM2BLOCK                 (0x1UL << 1)                      /**< Energy Mode 2 Block */
#define _EMU_CTRL_EM2BLOCK_SHIFT          1                                 /**< Shift value for EMU_EM2BLOCK */
#define _EMU_CTRL_EM2BLOCK_MASK           0x2UL                             /**< Bit mask for EMU_EM2BLOCK */
#define _EMU_CTRL_EM2BLOCK_DEFAULT        0x00000000UL                      /**< Mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM2BLOCK_DEFAULT         (_EMU_CTRL_EM2BLOCK_DEFAULT << 1) /**< Shifted mode DEFAULT for EMU_CTRL */
#define _EMU_CTRL_EM4CTRL_SHIFT           2                                 /**< Shift value for EMU_EM4CTRL */
#define _EMU_CTRL_EM4CTRL_MASK            0xCUL                             /**< Bit mask for EMU_EM4CTRL */
#define _EMU_CTRL_EM4CTRL_DEFAULT         0x00000000UL                      /**< Mode DEFAULT for EMU_CTRL */
#define EMU_CTRL_EM4CTRL_DEFAULT          (_EMU_CTRL_EM4CTRL_DEFAULT << 2)  /**< Shifted mode DEFAULT for EMU_CTRL */

/* Bit fields for EMU MEMCTRL */
#define _EMU_MEMCTRL_RESETVALUE           0x00000000UL                          /**< Default value for EMU_MEMCTRL */
#define _EMU_MEMCTRL_MASK                 0x00000007UL                          /**< Mask for EMU_MEMCTRL */
#define _EMU_MEMCTRL_POWERDOWN_SHIFT      0                                     /**< Shift value for EMU_POWERDOWN */
#define _EMU_MEMCTRL_POWERDOWN_MASK       0x7UL                                 /**< Bit mask for EMU_POWERDOWN */
#define _EMU_MEMCTRL_POWERDOWN_DEFAULT    0x00000000UL                          /**< Mode DEFAULT for EMU_MEMCTRL */
#define _EMU_MEMCTRL_POWERDOWN_BLK3       0x00000004UL                          /**< Mode BLK3 for EMU_MEMCTRL */
#define _EMU_MEMCTRL_POWERDOWN_BLK23      0x00000006UL                          /**< Mode BLK23 for EMU_MEMCTRL */
#define _EMU_MEMCTRL_POWERDOWN_BLK123     0x00000007UL                          /**< Mode BLK123 for EMU_MEMCTRL */
#define EMU_MEMCTRL_POWERDOWN_DEFAULT     (_EMU_MEMCTRL_POWERDOWN_DEFAULT << 0) /**< Shifted mode DEFAULT for EMU_MEMCTRL */
#define EMU_MEMCTRL_POWERDOWN_BLK3        (_EMU_MEMCTRL_POWERDOWN_BLK3 << 0)    /**< Shifted mode BLK3 for EMU_MEMCTRL */
#define EMU_MEMCTRL_POWERDOWN_BLK23       (_EMU_MEMCTRL_POWERDOWN_BLK23 << 0)   /**< Shifted mode BLK23 for EMU_MEMCTRL */
#define EMU_MEMCTRL_POWERDOWN_BLK123      (_EMU_MEMCTRL_POWERDOWN_BLK123 << 0)  /**< Shifted mode BLK123 for EMU_MEMCTRL */

/* Bit fields for EMU LOCK */
#define _EMU_LOCK_RESETVALUE              0x00000000UL                      /**< Default value for EMU_LOCK */
#define _EMU_LOCK_MASK                    0x0000FFFFUL                      /**< Mask for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_SHIFT           0                                 /**< Shift value for EMU_LOCKKEY */
#define _EMU_LOCK_LOCKKEY_MASK            0xFFFFUL                          /**< Bit mask for EMU_LOCKKEY */
#define _EMU_LOCK_LOCKKEY_DEFAULT         0x00000000UL                      /**< Mode DEFAULT for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_LOCK            0x00000000UL                      /**< Mode LOCK for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_UNLOCKED        0x00000000UL                      /**< Mode UNLOCKED for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_LOCKED          0x00000001UL                      /**< Mode LOCKED for EMU_LOCK */
#define _EMU_LOCK_LOCKKEY_UNLOCK          0x0000ADE8UL                      /**< Mode UNLOCK for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_DEFAULT          (_EMU_LOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_LOCK             (_EMU_LOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_UNLOCKED         (_EMU_LOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_LOCKED           (_EMU_LOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for EMU_LOCK */
#define EMU_LOCK_LOCKKEY_UNLOCK           (_EMU_LOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for EMU_LOCK */

/* Bit fields for EMU AUXCTRL */
#define _EMU_AUXCTRL_RESETVALUE           0x00000000UL                       /**< Default value for EMU_AUXCTRL */
#define _EMU_AUXCTRL_MASK                 0x00000001UL                       /**< Mask for EMU_AUXCTRL */
#define EMU_AUXCTRL_HRCCLR                (0x1UL << 0)                       /**< Hard Reset Cause Clear */
#define _EMU_AUXCTRL_HRCCLR_SHIFT         0                                  /**< Shift value for EMU_HRCCLR */
#define _EMU_AUXCTRL_HRCCLR_MASK          0x1UL                              /**< Bit mask for EMU_HRCCLR */
#define _EMU_AUXCTRL_HRCCLR_DEFAULT       0x00000000UL                       /**< Mode DEFAULT for EMU_AUXCTRL */
#define EMU_AUXCTRL_HRCCLR_DEFAULT        (_EMU_AUXCTRL_HRCCLR_DEFAULT << 0) /**< Shifted mode DEFAULT for EMU_AUXCTRL */

/** @} End of group EFM32G_EMU */


