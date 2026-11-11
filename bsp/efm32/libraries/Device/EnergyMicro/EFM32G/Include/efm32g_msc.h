/**************************************************************************//**
 * @file
 * @brief efm32g_msc Register and Bit Field definitions
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
 * @defgroup EFM32G_MSC
 * @{
 * @brief EFM32G_MSC Register Declaration
 *****************************************************************************/
typedef struct
{
  __IO uint32_t CTRL;         /**< Memory System Control Register  */
  __IO uint32_t READCTRL;     /**< Read Control Register  */
  __IO uint32_t WRITECTRL;    /**< Write Control Register  */
  __IO uint32_t WRITECMD;     /**< Write Command Register  */
  __IO uint32_t ADDRB;        /**< Page Erase/Write Address Buffer  */

  uint32_t      RESERVED0[1]; /**< Reserved for future use **/
  __IO uint32_t WDATA;        /**< Write Data Register  */
  __I uint32_t  STATUS;       /**< Status Register  */

  uint32_t      RESERVED1[3]; /**< Reserved for future use **/
  __I uint32_t  IF;           /**< Interrupt Flag Register  */
  __IO uint32_t IFS;          /**< Interrupt Flag Set Register  */
  __IO uint32_t IFC;          /**< Interrupt Flag Clear Register  */
  __IO uint32_t IEN;          /**< Interrupt Enable Register  */
  __IO uint32_t LOCK;         /**< Configuration Lock Register  */
} MSC_TypeDef;                /** @} */

/**************************************************************************//**
 * @defgroup EFM32G_MSC_BitFields
 * @{
 *****************************************************************************/

/* Bit fields for MSC CTRL */
#define _MSC_CTRL_RESETVALUE                    0x00000001UL                       /**< Default value for MSC_CTRL */
#define _MSC_CTRL_MASK                          0x00000001UL                       /**< Mask for MSC_CTRL */
#define MSC_CTRL_BUSFAULT                       (0x1UL << 0)                       /**< Bus Fault Response Enable */
#define _MSC_CTRL_BUSFAULT_SHIFT                0                                  /**< Shift value for MSC_BUSFAULT */
#define _MSC_CTRL_BUSFAULT_MASK                 0x1UL                              /**< Bit mask for MSC_BUSFAULT */
#define _MSC_CTRL_BUSFAULT_GENERATE             0x00000000UL                       /**< Mode GENERATE for MSC_CTRL */
#define _MSC_CTRL_BUSFAULT_DEFAULT              0x00000001UL                       /**< Mode DEFAULT for MSC_CTRL */
#define _MSC_CTRL_BUSFAULT_IGNORE               0x00000001UL                       /**< Mode IGNORE for MSC_CTRL */
#define MSC_CTRL_BUSFAULT_GENERATE              (_MSC_CTRL_BUSFAULT_GENERATE << 0) /**< Shifted mode GENERATE for MSC_CTRL */
#define MSC_CTRL_BUSFAULT_DEFAULT               (_MSC_CTRL_BUSFAULT_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_CTRL */
#define MSC_CTRL_BUSFAULT_IGNORE                (_MSC_CTRL_BUSFAULT_IGNORE << 0)   /**< Shifted mode IGNORE for MSC_CTRL */

/* Bit fields for MSC READCTRL */
#define _MSC_READCTRL_RESETVALUE                0x00000001UL                       /**< Default value for MSC_READCTRL */
#define _MSC_READCTRL_MASK                      0x00000007UL                       /**< Mask for MSC_READCTRL */
#define _MSC_READCTRL_MODE_SHIFT                0                                  /**< Shift value for MSC_MODE */
#define _MSC_READCTRL_MODE_MASK                 0x7UL                              /**< Bit mask for MSC_MODE */
#define _MSC_READCTRL_MODE_WS0                  0x00000000UL                       /**< Mode WS0 for MSC_READCTRL */
#define _MSC_READCTRL_MODE_DEFAULT              0x00000001UL                       /**< Mode DEFAULT for MSC_READCTRL */
#define _MSC_READCTRL_MODE_WS1                  0x00000001UL                       /**< Mode WS1 for MSC_READCTRL */
#define _MSC_READCTRL_MODE_WS0SCBTP             0x00000002UL                       /**< Mode WS0SCBTP for MSC_READCTRL */
#define _MSC_READCTRL_MODE_WS1SCBTP             0x00000003UL                       /**< Mode WS1SCBTP for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS0                   (_MSC_READCTRL_MODE_WS0 << 0)      /**< Shifted mode WS0 for MSC_READCTRL */
#define MSC_READCTRL_MODE_DEFAULT               (_MSC_READCTRL_MODE_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS1                   (_MSC_READCTRL_MODE_WS1 << 0)      /**< Shifted mode WS1 for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS0SCBTP              (_MSC_READCTRL_MODE_WS0SCBTP << 0) /**< Shifted mode WS0SCBTP for MSC_READCTRL */
#define MSC_READCTRL_MODE_WS1SCBTP              (_MSC_READCTRL_MODE_WS1SCBTP << 0) /**< Shifted mode WS1SCBTP for MSC_READCTRL */

/* Bit fields for MSC WRITECTRL */
#define _MSC_WRITECTRL_RESETVALUE               0x00000000UL                                /**< Default value for MSC_WRITECTRL */
#define _MSC_WRITECTRL_MASK                     0x00000003UL                                /**< Mask for MSC_WRITECTRL */
#define MSC_WRITECTRL_WREN                      (0x1UL << 0)                                /**< Enable Write/Erase Controller  */
#define _MSC_WRITECTRL_WREN_SHIFT               0                                           /**< Shift value for MSC_WREN */
#define _MSC_WRITECTRL_WREN_MASK                0x1UL                                       /**< Bit mask for MSC_WREN */
#define _MSC_WRITECTRL_WREN_DEFAULT             0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL */
#define MSC_WRITECTRL_WREN_DEFAULT              (_MSC_WRITECTRL_WREN_DEFAULT << 0)          /**< Shifted mode DEFAULT for MSC_WRITECTRL */
#define MSC_WRITECTRL_IRQERASEABORT             (0x1UL << 1)                                /**< Abort Page Erase on Interrupt */
#define _MSC_WRITECTRL_IRQERASEABORT_SHIFT      1                                           /**< Shift value for MSC_IRQERASEABORT */
#define _MSC_WRITECTRL_IRQERASEABORT_MASK       0x2UL                                       /**< Bit mask for MSC_IRQERASEABORT */
#define _MSC_WRITECTRL_IRQERASEABORT_DEFAULT    0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL */
#define MSC_WRITECTRL_IRQERASEABORT_DEFAULT     (_MSC_WRITECTRL_IRQERASEABORT_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_WRITECTRL */

/* Bit fields for MSC WRITECMD */
#define _MSC_WRITECMD_RESETVALUE                0x00000000UL                           /**< Default value for MSC_WRITECMD */
#define _MSC_WRITECMD_MASK                      0x0000001FUL                           /**< Mask for MSC_WRITECMD */
#define MSC_WRITECMD_LADDRIM                    (0x1UL << 0)                           /**< Load MSC_ADDRB into ADDR */
#define _MSC_WRITECMD_LADDRIM_SHIFT             0                                      /**< Shift value for MSC_LADDRIM */
#define _MSC_WRITECMD_LADDRIM_MASK              0x1UL                                  /**< Bit mask for MSC_LADDRIM */
#define _MSC_WRITECMD_LADDRIM_DEFAULT           0x00000000UL                           /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_LADDRIM_DEFAULT            (_MSC_WRITECMD_LADDRIM_DEFAULT << 0)   /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEPAGE                  (0x1UL << 1)                           /**< Erase Page */
#define _MSC_WRITECMD_ERASEPAGE_SHIFT           1                                      /**< Shift value for MSC_ERASEPAGE */
#define _MSC_WRITECMD_ERASEPAGE_MASK            0x2UL                                  /**< Bit mask for MSC_ERASEPAGE */
#define _MSC_WRITECMD_ERASEPAGE_DEFAULT         0x00000000UL                           /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_ERASEPAGE_DEFAULT          (_MSC_WRITECMD_ERASEPAGE_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEEND                   (0x1UL << 2)                           /**< End Write Mode */
#define _MSC_WRITECMD_WRITEEND_SHIFT            2                                      /**< Shift value for MSC_WRITEEND */
#define _MSC_WRITECMD_WRITEEND_MASK             0x4UL                                  /**< Bit mask for MSC_WRITEEND */
#define _MSC_WRITECMD_WRITEEND_DEFAULT          0x00000000UL                           /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEEND_DEFAULT           (_MSC_WRITECMD_WRITEEND_DEFAULT << 2)  /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEONCE                  (0x1UL << 3)                           /**< Word Write-Once Trigger */
#define _MSC_WRITECMD_WRITEONCE_SHIFT           3                                      /**< Shift value for MSC_WRITEONCE */
#define _MSC_WRITECMD_WRITEONCE_MASK            0x8UL                                  /**< Bit mask for MSC_WRITEONCE */
#define _MSC_WRITECMD_WRITEONCE_DEFAULT         0x00000000UL                           /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITEONCE_DEFAULT          (_MSC_WRITECMD_WRITEONCE_DEFAULT << 3) /**< Shifted mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITETRIG                  (0x1UL << 4)                           /**< Word Write Sequence Trigger */
#define _MSC_WRITECMD_WRITETRIG_SHIFT           4                                      /**< Shift value for MSC_WRITETRIG */
#define _MSC_WRITECMD_WRITETRIG_MASK            0x10UL                                 /**< Bit mask for MSC_WRITETRIG */
#define _MSC_WRITECMD_WRITETRIG_DEFAULT         0x00000000UL                           /**< Mode DEFAULT for MSC_WRITECMD */
#define MSC_WRITECMD_WRITETRIG_DEFAULT          (_MSC_WRITECMD_WRITETRIG_DEFAULT << 4) /**< Shifted mode DEFAULT for MSC_WRITECMD */

/* Bit fields for MSC ADDRB */
#define _MSC_ADDRB_RESETVALUE                   0x00000000UL                    /**< Default value for MSC_ADDRB */
#define _MSC_ADDRB_MASK                         0xFFFFFFFFUL                    /**< Mask for MSC_ADDRB */
#define _MSC_ADDRB_ADDRB_SHIFT                  0                               /**< Shift value for MSC_ADDRB */
#define _MSC_ADDRB_ADDRB_MASK                   0xFFFFFFFFUL                    /**< Bit mask for MSC_ADDRB */
#define _MSC_ADDRB_ADDRB_DEFAULT                0x00000000UL                    /**< Mode DEFAULT for MSC_ADDRB */
#define MSC_ADDRB_ADDRB_DEFAULT                 (_MSC_ADDRB_ADDRB_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_ADDRB */

/* Bit fields for MSC WDATA */
#define _MSC_WDATA_RESETVALUE                   0x00000000UL                    /**< Default value for MSC_WDATA */
#define _MSC_WDATA_MASK                         0xFFFFFFFFUL                    /**< Mask for MSC_WDATA */
#define _MSC_WDATA_WDATA_SHIFT                  0                               /**< Shift value for MSC_WDATA */
#define _MSC_WDATA_WDATA_MASK                   0xFFFFFFFFUL                    /**< Bit mask for MSC_WDATA */
#define _MSC_WDATA_WDATA_DEFAULT                0x00000000UL                    /**< Mode DEFAULT for MSC_WDATA */
#define MSC_WDATA_WDATA_DEFAULT                 (_MSC_WDATA_WDATA_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_WDATA */

/* Bit fields for MSC STATUS */
#define _MSC_STATUS_RESETVALUE                  0x00000008UL                            /**< Default value for MSC_STATUS */
#define _MSC_STATUS_MASK                        0x0000003FUL                            /**< Mask for MSC_STATUS */
#define MSC_STATUS_BUSY                         (0x1UL << 0)                            /**< Erase/Write Busy */
#define _MSC_STATUS_BUSY_SHIFT                  0                                       /**< Shift value for MSC_BUSY */
#define _MSC_STATUS_BUSY_MASK                   0x1UL                                   /**< Bit mask for MSC_BUSY */
#define _MSC_STATUS_BUSY_DEFAULT                0x00000000UL                            /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_BUSY_DEFAULT                 (_MSC_STATUS_BUSY_DEFAULT << 0)         /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_LOCKED                       (0x1UL << 1)                            /**< Access Locked */
#define _MSC_STATUS_LOCKED_SHIFT                1                                       /**< Shift value for MSC_LOCKED */
#define _MSC_STATUS_LOCKED_MASK                 0x2UL                                   /**< Bit mask for MSC_LOCKED */
#define _MSC_STATUS_LOCKED_DEFAULT              0x00000000UL                            /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_LOCKED_DEFAULT               (_MSC_STATUS_LOCKED_DEFAULT << 1)       /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_INVADDR                      (0x1UL << 2)                            /**< Invalid Write Address or Erase Page */
#define _MSC_STATUS_INVADDR_SHIFT               2                                       /**< Shift value for MSC_INVADDR */
#define _MSC_STATUS_INVADDR_MASK                0x4UL                                   /**< Bit mask for MSC_INVADDR */
#define _MSC_STATUS_INVADDR_DEFAULT             0x00000000UL                            /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_INVADDR_DEFAULT              (_MSC_STATUS_INVADDR_DEFAULT << 2)      /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WDATAREADY                   (0x1UL << 3)                            /**< WDATA Write Ready */
#define _MSC_STATUS_WDATAREADY_SHIFT            3                                       /**< Shift value for MSC_WDATAREADY */
#define _MSC_STATUS_WDATAREADY_MASK             0x8UL                                   /**< Bit mask for MSC_WDATAREADY */
#define _MSC_STATUS_WDATAREADY_DEFAULT          0x00000001UL                            /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WDATAREADY_DEFAULT           (_MSC_STATUS_WDATAREADY_DEFAULT << 3)   /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WORDTIMEOUT                  (0x1UL << 4)                            /**< Flash Write Word Timeout */
#define _MSC_STATUS_WORDTIMEOUT_SHIFT           4                                       /**< Shift value for MSC_WORDTIMEOUT */
#define _MSC_STATUS_WORDTIMEOUT_MASK            0x10UL                                  /**< Bit mask for MSC_WORDTIMEOUT */
#define _MSC_STATUS_WORDTIMEOUT_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_WORDTIMEOUT_DEFAULT          (_MSC_STATUS_WORDTIMEOUT_DEFAULT << 4)  /**< Shifted mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_ERASEABORTED                 (0x1UL << 5)                            /**< The Current Flash Erase Operation Aborted */
#define _MSC_STATUS_ERASEABORTED_SHIFT          5                                       /**< Shift value for MSC_ERASEABORTED */
#define _MSC_STATUS_ERASEABORTED_MASK           0x20UL                                  /**< Bit mask for MSC_ERASEABORTED */
#define _MSC_STATUS_ERASEABORTED_DEFAULT        0x00000000UL                            /**< Mode DEFAULT for MSC_STATUS */
#define MSC_STATUS_ERASEABORTED_DEFAULT         (_MSC_STATUS_ERASEABORTED_DEFAULT << 5) /**< Shifted mode DEFAULT for MSC_STATUS */

/* Bit fields for MSC IF */
#define _MSC_IF_RESETVALUE                      0x00000000UL                 /**< Default value for MSC_IF */
#define _MSC_IF_MASK                            0x00000003UL                 /**< Mask for MSC_IF */
#define MSC_IF_ERASE                            (0x1UL << 0)                 /**< Erase Done Interrupt Read Flag */
#define _MSC_IF_ERASE_SHIFT                     0                            /**< Shift value for MSC_ERASE */
#define _MSC_IF_ERASE_MASK                      0x1UL                        /**< Bit mask for MSC_ERASE */
#define _MSC_IF_ERASE_DEFAULT                   0x00000000UL                 /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_ERASE_DEFAULT                    (_MSC_IF_ERASE_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_IF */
#define MSC_IF_WRITE                            (0x1UL << 1)                 /**< Write Done Interrupt Read Flag */
#define _MSC_IF_WRITE_SHIFT                     1                            /**< Shift value for MSC_WRITE */
#define _MSC_IF_WRITE_MASK                      0x2UL                        /**< Bit mask for MSC_WRITE */
#define _MSC_IF_WRITE_DEFAULT                   0x00000000UL                 /**< Mode DEFAULT for MSC_IF */
#define MSC_IF_WRITE_DEFAULT                    (_MSC_IF_WRITE_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_IF */

/* Bit fields for MSC IFS */
#define _MSC_IFS_RESETVALUE                     0x00000000UL                  /**< Default value for MSC_IFS */
#define _MSC_IFS_MASK                           0x00000003UL                  /**< Mask for MSC_IFS */
#define MSC_IFS_ERASE                           (0x1UL << 0)                  /**< Erase Done Interrupt Set */
#define _MSC_IFS_ERASE_SHIFT                    0                             /**< Shift value for MSC_ERASE */
#define _MSC_IFS_ERASE_MASK                     0x1UL                         /**< Bit mask for MSC_ERASE */
#define _MSC_IFS_ERASE_DEFAULT                  0x00000000UL                  /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_ERASE_DEFAULT                   (_MSC_IFS_ERASE_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_IFS */
#define MSC_IFS_WRITE                           (0x1UL << 1)                  /**< Write Done Interrupt Set */
#define _MSC_IFS_WRITE_SHIFT                    1                             /**< Shift value for MSC_WRITE */
#define _MSC_IFS_WRITE_MASK                     0x2UL                         /**< Bit mask for MSC_WRITE */
#define _MSC_IFS_WRITE_DEFAULT                  0x00000000UL                  /**< Mode DEFAULT for MSC_IFS */
#define MSC_IFS_WRITE_DEFAULT                   (_MSC_IFS_WRITE_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_IFS */

/* Bit fields for MSC IFC */
#define _MSC_IFC_RESETVALUE                     0x00000000UL                  /**< Default value for MSC_IFC */
#define _MSC_IFC_MASK                           0x00000003UL                  /**< Mask for MSC_IFC */
#define MSC_IFC_ERASE                           (0x1UL << 0)                  /**< Erase Done Interrupt Clear */
#define _MSC_IFC_ERASE_SHIFT                    0                             /**< Shift value for MSC_ERASE */
#define _MSC_IFC_ERASE_MASK                     0x1UL                         /**< Bit mask for MSC_ERASE */
#define _MSC_IFC_ERASE_DEFAULT                  0x00000000UL                  /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_ERASE_DEFAULT                   (_MSC_IFC_ERASE_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_IFC */
#define MSC_IFC_WRITE                           (0x1UL << 1)                  /**< Write Done Interrupt Clear */
#define _MSC_IFC_WRITE_SHIFT                    1                             /**< Shift value for MSC_WRITE */
#define _MSC_IFC_WRITE_MASK                     0x2UL                         /**< Bit mask for MSC_WRITE */
#define _MSC_IFC_WRITE_DEFAULT                  0x00000000UL                  /**< Mode DEFAULT for MSC_IFC */
#define MSC_IFC_WRITE_DEFAULT                   (_MSC_IFC_WRITE_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_IFC */

/* Bit fields for MSC IEN */
#define _MSC_IEN_RESETVALUE                     0x00000000UL                  /**< Default value for MSC_IEN */
#define _MSC_IEN_MASK                           0x00000003UL                  /**< Mask for MSC_IEN */
#define MSC_IEN_ERASE                           (0x1UL << 0)                  /**< Erase Done Interrupt Enable */
#define _MSC_IEN_ERASE_SHIFT                    0                             /**< Shift value for MSC_ERASE */
#define _MSC_IEN_ERASE_MASK                     0x1UL                         /**< Bit mask for MSC_ERASE */
#define _MSC_IEN_ERASE_DEFAULT                  0x00000000UL                  /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_ERASE_DEFAULT                   (_MSC_IEN_ERASE_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_IEN */
#define MSC_IEN_WRITE                           (0x1UL << 1)                  /**< Write Done Interrupt Enable */
#define _MSC_IEN_WRITE_SHIFT                    1                             /**< Shift value for MSC_WRITE */
#define _MSC_IEN_WRITE_MASK                     0x2UL                         /**< Bit mask for MSC_WRITE */
#define _MSC_IEN_WRITE_DEFAULT                  0x00000000UL                  /**< Mode DEFAULT for MSC_IEN */
#define MSC_IEN_WRITE_DEFAULT                   (_MSC_IEN_WRITE_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_IEN */

/* Bit fields for MSC LOCK */
#define _MSC_LOCK_RESETVALUE                    0x00000000UL                      /**< Default value for MSC_LOCK */
#define _MSC_LOCK_MASK                          0x0000FFFFUL                      /**< Mask for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_SHIFT                 0                                 /**< Shift value for MSC_LOCKKEY */
#define _MSC_LOCK_LOCKKEY_MASK                  0xFFFFUL                          /**< Bit mask for MSC_LOCKKEY */
#define _MSC_LOCK_LOCKKEY_DEFAULT               0x00000000UL                      /**< Mode DEFAULT for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_LOCK                  0x00000000UL                      /**< Mode LOCK for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_UNLOCKED              0x00000000UL                      /**< Mode UNLOCKED for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_LOCKED                0x00000001UL                      /**< Mode LOCKED for MSC_LOCK */
#define _MSC_LOCK_LOCKKEY_UNLOCK                0x00001B71UL                      /**< Mode UNLOCK for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_DEFAULT                (_MSC_LOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_LOCK                   (_MSC_LOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_UNLOCKED               (_MSC_LOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_LOCKED                 (_MSC_LOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for MSC_LOCK */
#define MSC_LOCK_LOCKKEY_UNLOCK                 (_MSC_LOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for MSC_LOCK */

/** @} End of group EFM32G_MSC */


