/**************************************************************************//**
 * @file
 * @brief efm32g_pcnt Register and Bit Field definitions
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
 * @defgroup EFM32G_PCNT
 * @{
 * @brief EFM32G_PCNT Register Declaration
 *****************************************************************************/
typedef struct
{
  __IO uint32_t CTRL;     /**< Control Register  */
  __IO uint32_t CMD;      /**< Command Register  */
  __I uint32_t  STATUS;   /**< Status Register  */
  __I uint32_t  CNT;      /**< Counter Value Register  */
  __I uint32_t  TOP;      /**< Top Value Register  */
  __IO uint32_t TOPB;     /**< Top Value Buffer Register  */
  __I uint32_t  IF;       /**< Interrupt Flag Register  */
  __IO uint32_t IFS;      /**< Interrupt Flag Set Register  */
  __IO uint32_t IFC;      /**< Interrupt Flag Clear Register  */
  __IO uint32_t IEN;      /**< Interrupt Enable Register  */
  __IO uint32_t ROUTE;    /**< I/O Routing Register  */

  __IO uint32_t FREEZE;   /**< Freeze Register  */
  __I uint32_t  SYNCBUSY; /**< Synchronization Busy Register  */
} PCNT_TypeDef;           /** @} */

/**************************************************************************//**
 * @defgroup EFM32G_PCNT_BitFields
 * @{
 *****************************************************************************/

/* Bit fields for PCNT CTRL */
#define _PCNT_CTRL_RESETVALUE             0x00000000UL                        /**< Default value for PCNT_CTRL */
#define _PCNT_CTRL_MASK                   0x0000003FUL                        /**< Mask for PCNT_CTRL */
#define _PCNT_CTRL_MODE_SHIFT             0                                   /**< Shift value for PCNT_MODE */
#define _PCNT_CTRL_MODE_MASK              0x3UL                               /**< Bit mask for PCNT_MODE */
#define _PCNT_CTRL_MODE_DEFAULT           0x00000000UL                        /**< Mode DEFAULT for PCNT_CTRL */
#define _PCNT_CTRL_MODE_DISABLE           0x00000000UL                        /**< Mode DISABLE for PCNT_CTRL */
#define _PCNT_CTRL_MODE_OVSSINGLE         0x00000001UL                        /**< Mode OVSSINGLE for PCNT_CTRL */
#define _PCNT_CTRL_MODE_EXTCLKSINGLE      0x00000002UL                        /**< Mode EXTCLKSINGLE for PCNT_CTRL */
#define _PCNT_CTRL_MODE_EXTCLKQUAD        0x00000003UL                        /**< Mode EXTCLKQUAD for PCNT_CTRL */
#define PCNT_CTRL_MODE_DEFAULT            (_PCNT_CTRL_MODE_DEFAULT << 0)      /**< Shifted mode DEFAULT for PCNT_CTRL */
#define PCNT_CTRL_MODE_DISABLE            (_PCNT_CTRL_MODE_DISABLE << 0)      /**< Shifted mode DISABLE for PCNT_CTRL */
#define PCNT_CTRL_MODE_OVSSINGLE          (_PCNT_CTRL_MODE_OVSSINGLE << 0)    /**< Shifted mode OVSSINGLE for PCNT_CTRL */
#define PCNT_CTRL_MODE_EXTCLKSINGLE       (_PCNT_CTRL_MODE_EXTCLKSINGLE << 0) /**< Shifted mode EXTCLKSINGLE for PCNT_CTRL */
#define PCNT_CTRL_MODE_EXTCLKQUAD         (_PCNT_CTRL_MODE_EXTCLKQUAD << 0)   /**< Shifted mode EXTCLKQUAD for PCNT_CTRL */
#define PCNT_CTRL_CNTDIR                  (0x1UL << 2)                        /**< Non-Quadrature Mode Counter Direction Control */
#define _PCNT_CTRL_CNTDIR_SHIFT           2                                   /**< Shift value for PCNT_CNTDIR */
#define _PCNT_CTRL_CNTDIR_MASK            0x4UL                               /**< Bit mask for PCNT_CNTDIR */
#define _PCNT_CTRL_CNTDIR_DEFAULT         0x00000000UL                        /**< Mode DEFAULT for PCNT_CTRL */
#define _PCNT_CTRL_CNTDIR_UP              0x00000000UL                        /**< Mode UP for PCNT_CTRL */
#define _PCNT_CTRL_CNTDIR_DOWN            0x00000001UL                        /**< Mode DOWN for PCNT_CTRL */
#define PCNT_CTRL_CNTDIR_DEFAULT          (_PCNT_CTRL_CNTDIR_DEFAULT << 2)    /**< Shifted mode DEFAULT for PCNT_CTRL */
#define PCNT_CTRL_CNTDIR_UP               (_PCNT_CTRL_CNTDIR_UP << 2)         /**< Shifted mode UP for PCNT_CTRL */
#define PCNT_CTRL_CNTDIR_DOWN             (_PCNT_CTRL_CNTDIR_DOWN << 2)       /**< Shifted mode DOWN for PCNT_CTRL */
#define PCNT_CTRL_EDGE                    (0x1UL << 3)                        /**< Edge Select */
#define _PCNT_CTRL_EDGE_SHIFT             3                                   /**< Shift value for PCNT_EDGE */
#define _PCNT_CTRL_EDGE_MASK              0x8UL                               /**< Bit mask for PCNT_EDGE */
#define _PCNT_CTRL_EDGE_DEFAULT           0x00000000UL                        /**< Mode DEFAULT for PCNT_CTRL */
#define _PCNT_CTRL_EDGE_POS               0x00000000UL                        /**< Mode POS for PCNT_CTRL */
#define _PCNT_CTRL_EDGE_NEG               0x00000001UL                        /**< Mode NEG for PCNT_CTRL */
#define PCNT_CTRL_EDGE_DEFAULT            (_PCNT_CTRL_EDGE_DEFAULT << 3)      /**< Shifted mode DEFAULT for PCNT_CTRL */
#define PCNT_CTRL_EDGE_POS                (_PCNT_CTRL_EDGE_POS << 3)          /**< Shifted mode POS for PCNT_CTRL */
#define PCNT_CTRL_EDGE_NEG                (_PCNT_CTRL_EDGE_NEG << 3)          /**< Shifted mode NEG for PCNT_CTRL */
#define PCNT_CTRL_FILT                    (0x1UL << 4)                        /**< Enable Digital Pulse Width Filter */
#define _PCNT_CTRL_FILT_SHIFT             4                                   /**< Shift value for PCNT_FILT */
#define _PCNT_CTRL_FILT_MASK              0x10UL                              /**< Bit mask for PCNT_FILT */
#define _PCNT_CTRL_FILT_DEFAULT           0x00000000UL                        /**< Mode DEFAULT for PCNT_CTRL */
#define PCNT_CTRL_FILT_DEFAULT            (_PCNT_CTRL_FILT_DEFAULT << 4)      /**< Shifted mode DEFAULT for PCNT_CTRL */
#define PCNT_CTRL_RSTEN                   (0x1UL << 5)                        /**< Enable PCNT Clock Domain Reset */
#define _PCNT_CTRL_RSTEN_SHIFT            5                                   /**< Shift value for PCNT_RSTEN */
#define _PCNT_CTRL_RSTEN_MASK             0x20UL                              /**< Bit mask for PCNT_RSTEN */
#define _PCNT_CTRL_RSTEN_DEFAULT          0x00000000UL                        /**< Mode DEFAULT for PCNT_CTRL */
#define PCNT_CTRL_RSTEN_DEFAULT           (_PCNT_CTRL_RSTEN_DEFAULT << 5)     /**< Shifted mode DEFAULT for PCNT_CTRL */

/* Bit fields for PCNT CMD */
#define _PCNT_CMD_RESETVALUE              0x00000000UL                     /**< Default value for PCNT_CMD */
#define _PCNT_CMD_MASK                    0x00000003UL                     /**< Mask for PCNT_CMD */
#define PCNT_CMD_LCNTIM                   (0x1UL << 0)                     /**< Load CNT Immediately */
#define _PCNT_CMD_LCNTIM_SHIFT            0                                /**< Shift value for PCNT_LCNTIM */
#define _PCNT_CMD_LCNTIM_MASK             0x1UL                            /**< Bit mask for PCNT_LCNTIM */
#define _PCNT_CMD_LCNTIM_DEFAULT          0x00000000UL                     /**< Mode DEFAULT for PCNT_CMD */
#define PCNT_CMD_LCNTIM_DEFAULT           (_PCNT_CMD_LCNTIM_DEFAULT << 0)  /**< Shifted mode DEFAULT for PCNT_CMD */
#define PCNT_CMD_LTOPBIM                  (0x1UL << 1)                     /**< Load TOPB Immediately */
#define _PCNT_CMD_LTOPBIM_SHIFT           1                                /**< Shift value for PCNT_LTOPBIM */
#define _PCNT_CMD_LTOPBIM_MASK            0x2UL                            /**< Bit mask for PCNT_LTOPBIM */
#define _PCNT_CMD_LTOPBIM_DEFAULT         0x00000000UL                     /**< Mode DEFAULT for PCNT_CMD */
#define PCNT_CMD_LTOPBIM_DEFAULT          (_PCNT_CMD_LTOPBIM_DEFAULT << 1) /**< Shifted mode DEFAULT for PCNT_CMD */

/* Bit fields for PCNT STATUS */
#define _PCNT_STATUS_RESETVALUE           0x00000000UL                    /**< Default value for PCNT_STATUS */
#define _PCNT_STATUS_MASK                 0x00000001UL                    /**< Mask for PCNT_STATUS */
#define PCNT_STATUS_DIR                   (0x1UL << 0)                    /**< Current Counter Direction */
#define _PCNT_STATUS_DIR_SHIFT            0                               /**< Shift value for PCNT_DIR */
#define _PCNT_STATUS_DIR_MASK             0x1UL                           /**< Bit mask for PCNT_DIR */
#define _PCNT_STATUS_DIR_DEFAULT          0x00000000UL                    /**< Mode DEFAULT for PCNT_STATUS */
#define _PCNT_STATUS_DIR_UP               0x00000000UL                    /**< Mode UP for PCNT_STATUS */
#define _PCNT_STATUS_DIR_DOWN             0x00000001UL                    /**< Mode DOWN for PCNT_STATUS */
#define PCNT_STATUS_DIR_DEFAULT           (_PCNT_STATUS_DIR_DEFAULT << 0) /**< Shifted mode DEFAULT for PCNT_STATUS */
#define PCNT_STATUS_DIR_UP                (_PCNT_STATUS_DIR_UP << 0)      /**< Shifted mode UP for PCNT_STATUS */
#define PCNT_STATUS_DIR_DOWN              (_PCNT_STATUS_DIR_DOWN << 0)    /**< Shifted mode DOWN for PCNT_STATUS */

/* Bit fields for PCNT CNT */
#define _PCNT_CNT_RESETVALUE              0x00000000UL                 /**< Default value for PCNT_CNT */
#define _PCNT_CNT_MASK                    0x000000FFUL                 /**< Mask for PCNT_CNT */
#define _PCNT_CNT_CNT_SHIFT               0                            /**< Shift value for PCNT_CNT */
#define _PCNT_CNT_CNT_MASK                0xFFUL                       /**< Bit mask for PCNT_CNT */
#define _PCNT_CNT_CNT_DEFAULT             0x00000000UL                 /**< Mode DEFAULT for PCNT_CNT */
#define PCNT_CNT_CNT_DEFAULT              (_PCNT_CNT_CNT_DEFAULT << 0) /**< Shifted mode DEFAULT for PCNT_CNT */

/* Bit fields for PCNT TOP */
#define _PCNT_TOP_RESETVALUE              0x000000FFUL                 /**< Default value for PCNT_TOP */
#define _PCNT_TOP_MASK                    0x000000FFUL                 /**< Mask for PCNT_TOP */
#define _PCNT_TOP_TOP_SHIFT               0                            /**< Shift value for PCNT_TOP */
#define _PCNT_TOP_TOP_MASK                0xFFUL                       /**< Bit mask for PCNT_TOP */
#define _PCNT_TOP_TOP_DEFAULT             0x000000FFUL                 /**< Mode DEFAULT for PCNT_TOP */
#define PCNT_TOP_TOP_DEFAULT              (_PCNT_TOP_TOP_DEFAULT << 0) /**< Shifted mode DEFAULT for PCNT_TOP */

/* Bit fields for PCNT TOPB */
#define _PCNT_TOPB_RESETVALUE             0x000000FFUL                   /**< Default value for PCNT_TOPB */
#define _PCNT_TOPB_MASK                   0x000000FFUL                   /**< Mask for PCNT_TOPB */
#define _PCNT_TOPB_TOPB_SHIFT             0                              /**< Shift value for PCNT_TOPB */
#define _PCNT_TOPB_TOPB_MASK              0xFFUL                         /**< Bit mask for PCNT_TOPB */
#define _PCNT_TOPB_TOPB_DEFAULT           0x000000FFUL                   /**< Mode DEFAULT for PCNT_TOPB */
#define PCNT_TOPB_TOPB_DEFAULT            (_PCNT_TOPB_TOPB_DEFAULT << 0) /**< Shifted mode DEFAULT for PCNT_TOPB */

/* Bit fields for PCNT IF */
#define _PCNT_IF_RESETVALUE               0x00000000UL                   /**< Default value for PCNT_IF */
#define _PCNT_IF_MASK                     0x00000007UL                   /**< Mask for PCNT_IF */
#define PCNT_IF_UF                        (0x1UL << 0)                   /**< Underflow Interrupt Read Flag */
#define _PCNT_IF_UF_SHIFT                 0                              /**< Shift value for PCNT_UF */
#define _PCNT_IF_UF_MASK                  0x1UL                          /**< Bit mask for PCNT_UF */
#define _PCNT_IF_UF_DEFAULT               0x00000000UL                   /**< Mode DEFAULT for PCNT_IF */
#define PCNT_IF_UF_DEFAULT                (_PCNT_IF_UF_DEFAULT << 0)     /**< Shifted mode DEFAULT for PCNT_IF */
#define PCNT_IF_OF                        (0x1UL << 1)                   /**< Overflow Interrupt Read Flag */
#define _PCNT_IF_OF_SHIFT                 1                              /**< Shift value for PCNT_OF */
#define _PCNT_IF_OF_MASK                  0x2UL                          /**< Bit mask for PCNT_OF */
#define _PCNT_IF_OF_DEFAULT               0x00000000UL                   /**< Mode DEFAULT for PCNT_IF */
#define PCNT_IF_OF_DEFAULT                (_PCNT_IF_OF_DEFAULT << 1)     /**< Shifted mode DEFAULT for PCNT_IF */
#define PCNT_IF_DIRCNG                    (0x1UL << 2)                   /**< Direction Change Detect Interrupt Flag */
#define _PCNT_IF_DIRCNG_SHIFT             2                              /**< Shift value for PCNT_DIRCNG */
#define _PCNT_IF_DIRCNG_MASK              0x4UL                          /**< Bit mask for PCNT_DIRCNG */
#define _PCNT_IF_DIRCNG_DEFAULT           0x00000000UL                   /**< Mode DEFAULT for PCNT_IF */
#define PCNT_IF_DIRCNG_DEFAULT            (_PCNT_IF_DIRCNG_DEFAULT << 2) /**< Shifted mode DEFAULT for PCNT_IF */

/* Bit fields for PCNT IFS */
#define _PCNT_IFS_RESETVALUE              0x00000000UL                    /**< Default value for PCNT_IFS */
#define _PCNT_IFS_MASK                    0x00000007UL                    /**< Mask for PCNT_IFS */
#define PCNT_IFS_UF                       (0x1UL << 0)                    /**< Underflow interrupt set */
#define _PCNT_IFS_UF_SHIFT                0                               /**< Shift value for PCNT_UF */
#define _PCNT_IFS_UF_MASK                 0x1UL                           /**< Bit mask for PCNT_UF */
#define _PCNT_IFS_UF_DEFAULT              0x00000000UL                    /**< Mode DEFAULT for PCNT_IFS */
#define PCNT_IFS_UF_DEFAULT               (_PCNT_IFS_UF_DEFAULT << 0)     /**< Shifted mode DEFAULT for PCNT_IFS */
#define PCNT_IFS_OF                       (0x1UL << 1)                    /**< Overflow Interrupt Set */
#define _PCNT_IFS_OF_SHIFT                1                               /**< Shift value for PCNT_OF */
#define _PCNT_IFS_OF_MASK                 0x2UL                           /**< Bit mask for PCNT_OF */
#define _PCNT_IFS_OF_DEFAULT              0x00000000UL                    /**< Mode DEFAULT for PCNT_IFS */
#define PCNT_IFS_OF_DEFAULT               (_PCNT_IFS_OF_DEFAULT << 1)     /**< Shifted mode DEFAULT for PCNT_IFS */
#define PCNT_IFS_DIRCNG                   (0x1UL << 2)                    /**< Direction Change Detect Interrupt Set */
#define _PCNT_IFS_DIRCNG_SHIFT            2                               /**< Shift value for PCNT_DIRCNG */
#define _PCNT_IFS_DIRCNG_MASK             0x4UL                           /**< Bit mask for PCNT_DIRCNG */
#define _PCNT_IFS_DIRCNG_DEFAULT          0x00000000UL                    /**< Mode DEFAULT for PCNT_IFS */
#define PCNT_IFS_DIRCNG_DEFAULT           (_PCNT_IFS_DIRCNG_DEFAULT << 2) /**< Shifted mode DEFAULT for PCNT_IFS */

/* Bit fields for PCNT IFC */
#define _PCNT_IFC_RESETVALUE              0x00000000UL                    /**< Default value for PCNT_IFC */
#define _PCNT_IFC_MASK                    0x00000007UL                    /**< Mask for PCNT_IFC */
#define PCNT_IFC_UF                       (0x1UL << 0)                    /**< Underflow Interrupt Clear */
#define _PCNT_IFC_UF_SHIFT                0                               /**< Shift value for PCNT_UF */
#define _PCNT_IFC_UF_MASK                 0x1UL                           /**< Bit mask for PCNT_UF */
#define _PCNT_IFC_UF_DEFAULT              0x00000000UL                    /**< Mode DEFAULT for PCNT_IFC */
#define PCNT_IFC_UF_DEFAULT               (_PCNT_IFC_UF_DEFAULT << 0)     /**< Shifted mode DEFAULT for PCNT_IFC */
#define PCNT_IFC_OF                       (0x1UL << 1)                    /**< Overflow Interrupt Clear */
#define _PCNT_IFC_OF_SHIFT                1                               /**< Shift value for PCNT_OF */
#define _PCNT_IFC_OF_MASK                 0x2UL                           /**< Bit mask for PCNT_OF */
#define _PCNT_IFC_OF_DEFAULT              0x00000000UL                    /**< Mode DEFAULT for PCNT_IFC */
#define PCNT_IFC_OF_DEFAULT               (_PCNT_IFC_OF_DEFAULT << 1)     /**< Shifted mode DEFAULT for PCNT_IFC */
#define PCNT_IFC_DIRCNG                   (0x1UL << 2)                    /**< Direction Change Detect Interrupt Clear */
#define _PCNT_IFC_DIRCNG_SHIFT            2                               /**< Shift value for PCNT_DIRCNG */
#define _PCNT_IFC_DIRCNG_MASK             0x4UL                           /**< Bit mask for PCNT_DIRCNG */
#define _PCNT_IFC_DIRCNG_DEFAULT          0x00000000UL                    /**< Mode DEFAULT for PCNT_IFC */
#define PCNT_IFC_DIRCNG_DEFAULT           (_PCNT_IFC_DIRCNG_DEFAULT << 2) /**< Shifted mode DEFAULT for PCNT_IFC */

/* Bit fields for PCNT IEN */
#define _PCNT_IEN_RESETVALUE              0x00000000UL                    /**< Default value for PCNT_IEN */
#define _PCNT_IEN_MASK                    0x00000007UL                    /**< Mask for PCNT_IEN */
#define PCNT_IEN_UF                       (0x1UL << 0)                    /**< Underflow Interrupt Enable */
#define _PCNT_IEN_UF_SHIFT                0                               /**< Shift value for PCNT_UF */
#define _PCNT_IEN_UF_MASK                 0x1UL                           /**< Bit mask for PCNT_UF */
#define _PCNT_IEN_UF_DEFAULT              0x00000000UL                    /**< Mode DEFAULT for PCNT_IEN */
#define PCNT_IEN_UF_DEFAULT               (_PCNT_IEN_UF_DEFAULT << 0)     /**< Shifted mode DEFAULT for PCNT_IEN */
#define PCNT_IEN_OF                       (0x1UL << 1)                    /**< Overflow Interrupt Enable */
#define _PCNT_IEN_OF_SHIFT                1                               /**< Shift value for PCNT_OF */
#define _PCNT_IEN_OF_MASK                 0x2UL                           /**< Bit mask for PCNT_OF */
#define _PCNT_IEN_OF_DEFAULT              0x00000000UL                    /**< Mode DEFAULT for PCNT_IEN */
#define PCNT_IEN_OF_DEFAULT               (_PCNT_IEN_OF_DEFAULT << 1)     /**< Shifted mode DEFAULT for PCNT_IEN */
#define PCNT_IEN_DIRCNG                   (0x1UL << 2)                    /**< Direction Change Detect Interrupt Enable */
#define _PCNT_IEN_DIRCNG_SHIFT            2                               /**< Shift value for PCNT_DIRCNG */
#define _PCNT_IEN_DIRCNG_MASK             0x4UL                           /**< Bit mask for PCNT_DIRCNG */
#define _PCNT_IEN_DIRCNG_DEFAULT          0x00000000UL                    /**< Mode DEFAULT for PCNT_IEN */
#define PCNT_IEN_DIRCNG_DEFAULT           (_PCNT_IEN_DIRCNG_DEFAULT << 2) /**< Shifted mode DEFAULT for PCNT_IEN */

/* Bit fields for PCNT ROUTE */
#define _PCNT_ROUTE_RESETVALUE            0x00000000UL                        /**< Default value for PCNT_ROUTE */
#define _PCNT_ROUTE_MASK                  0x00000300UL                        /**< Mask for PCNT_ROUTE */
#define _PCNT_ROUTE_LOCATION_SHIFT        8                                   /**< Shift value for PCNT_LOCATION */
#define _PCNT_ROUTE_LOCATION_MASK         0x300UL                             /**< Bit mask for PCNT_LOCATION */
#define _PCNT_ROUTE_LOCATION_DEFAULT      0x00000000UL                        /**< Mode DEFAULT for PCNT_ROUTE */
#define _PCNT_ROUTE_LOCATION_LOC0         0x00000000UL                        /**< Mode LOC0 for PCNT_ROUTE */
#define _PCNT_ROUTE_LOCATION_LOC1         0x00000001UL                        /**< Mode LOC1 for PCNT_ROUTE */
#define _PCNT_ROUTE_LOCATION_LOC2         0x00000002UL                        /**< Mode LOC2 for PCNT_ROUTE */
#define PCNT_ROUTE_LOCATION_DEFAULT       (_PCNT_ROUTE_LOCATION_DEFAULT << 8) /**< Shifted mode DEFAULT for PCNT_ROUTE */
#define PCNT_ROUTE_LOCATION_LOC0          (_PCNT_ROUTE_LOCATION_LOC0 << 8)    /**< Shifted mode LOC0 for PCNT_ROUTE */
#define PCNT_ROUTE_LOCATION_LOC1          (_PCNT_ROUTE_LOCATION_LOC1 << 8)    /**< Shifted mode LOC1 for PCNT_ROUTE */
#define PCNT_ROUTE_LOCATION_LOC2          (_PCNT_ROUTE_LOCATION_LOC2 << 8)    /**< Shifted mode LOC2 for PCNT_ROUTE */

/* Bit fields for PCNT FREEZE */
#define _PCNT_FREEZE_RESETVALUE           0x00000000UL                          /**< Default value for PCNT_FREEZE */
#define _PCNT_FREEZE_MASK                 0x00000001UL                          /**< Mask for PCNT_FREEZE */
#define PCNT_FREEZE_REGFREEZE             (0x1UL << 0)                          /**< Register Update Freeze */
#define _PCNT_FREEZE_REGFREEZE_SHIFT      0                                     /**< Shift value for PCNT_REGFREEZE */
#define _PCNT_FREEZE_REGFREEZE_MASK       0x1UL                                 /**< Bit mask for PCNT_REGFREEZE */
#define _PCNT_FREEZE_REGFREEZE_DEFAULT    0x00000000UL                          /**< Mode DEFAULT for PCNT_FREEZE */
#define _PCNT_FREEZE_REGFREEZE_UPDATE     0x00000000UL                          /**< Mode UPDATE for PCNT_FREEZE */
#define _PCNT_FREEZE_REGFREEZE_FREEZE     0x00000001UL                          /**< Mode FREEZE for PCNT_FREEZE */
#define PCNT_FREEZE_REGFREEZE_DEFAULT     (_PCNT_FREEZE_REGFREEZE_DEFAULT << 0) /**< Shifted mode DEFAULT for PCNT_FREEZE */
#define PCNT_FREEZE_REGFREEZE_UPDATE      (_PCNT_FREEZE_REGFREEZE_UPDATE << 0)  /**< Shifted mode UPDATE for PCNT_FREEZE */
#define PCNT_FREEZE_REGFREEZE_FREEZE      (_PCNT_FREEZE_REGFREEZE_FREEZE << 0)  /**< Shifted mode FREEZE for PCNT_FREEZE */

/* Bit fields for PCNT SYNCBUSY */
#define _PCNT_SYNCBUSY_RESETVALUE         0x00000000UL                       /**< Default value for PCNT_SYNCBUSY */
#define _PCNT_SYNCBUSY_MASK               0x00000007UL                       /**< Mask for PCNT_SYNCBUSY */
#define PCNT_SYNCBUSY_CTRL                (0x1UL << 0)                       /**< PCNTn_CTRL Register Busy */
#define _PCNT_SYNCBUSY_CTRL_SHIFT         0                                  /**< Shift value for PCNT_CTRL */
#define _PCNT_SYNCBUSY_CTRL_MASK          0x1UL                              /**< Bit mask for PCNT_CTRL */
#define _PCNT_SYNCBUSY_CTRL_DEFAULT       0x00000000UL                       /**< Mode DEFAULT for PCNT_SYNCBUSY */
#define PCNT_SYNCBUSY_CTRL_DEFAULT        (_PCNT_SYNCBUSY_CTRL_DEFAULT << 0) /**< Shifted mode DEFAULT for PCNT_SYNCBUSY */
#define PCNT_SYNCBUSY_CMD                 (0x1UL << 1)                       /**< PCNTn_CMD Register Busy */
#define _PCNT_SYNCBUSY_CMD_SHIFT          1                                  /**< Shift value for PCNT_CMD */
#define _PCNT_SYNCBUSY_CMD_MASK           0x2UL                              /**< Bit mask for PCNT_CMD */
#define _PCNT_SYNCBUSY_CMD_DEFAULT        0x00000000UL                       /**< Mode DEFAULT for PCNT_SYNCBUSY */
#define PCNT_SYNCBUSY_CMD_DEFAULT         (_PCNT_SYNCBUSY_CMD_DEFAULT << 1)  /**< Shifted mode DEFAULT for PCNT_SYNCBUSY */
#define PCNT_SYNCBUSY_TOPB                (0x1UL << 2)                       /**< PCNTn_TOPB Register Busy */
#define _PCNT_SYNCBUSY_TOPB_SHIFT         2                                  /**< Shift value for PCNT_TOPB */
#define _PCNT_SYNCBUSY_TOPB_MASK          0x4UL                              /**< Bit mask for PCNT_TOPB */
#define _PCNT_SYNCBUSY_TOPB_DEFAULT       0x00000000UL                       /**< Mode DEFAULT for PCNT_SYNCBUSY */
#define PCNT_SYNCBUSY_TOPB_DEFAULT        (_PCNT_SYNCBUSY_TOPB_DEFAULT << 2) /**< Shifted mode DEFAULT for PCNT_SYNCBUSY */

/** @} End of group EFM32G_PCNT */


