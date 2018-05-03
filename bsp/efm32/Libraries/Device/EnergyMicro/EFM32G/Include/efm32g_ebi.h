/**************************************************************************//**
 * @file
 * @brief efm32g_ebi Register and Bit Field definitions
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
 * @defgroup EFM32G_EBI
 * @{
 * @brief EFM32G_EBI Register Declaration
 *****************************************************************************/
typedef struct
{
  __IO uint32_t CTRL;       /**< Control Register  */
  __IO uint32_t ADDRTIMING; /**< Address Timing Register  */
  __IO uint32_t RDTIMING;   /**< Read Timing Register  */
  __IO uint32_t WRTIMING;   /**< Write Timing Register  */
  __IO uint32_t POLARITY;   /**< Polarity Register  */
  __IO uint32_t ROUTE;      /**< I/O Routing Register  */
} EBI_TypeDef;              /** @} */

/**************************************************************************//**
 * @defgroup EFM32G_EBI_BitFields
 * @{
 *****************************************************************************/

/* Bit fields for EBI CTRL */
#define _EBI_CTRL_RESETVALUE                 0x00000000UL                        /**< Default value for EBI_CTRL */
#define _EBI_CTRL_MASK                       0x00030F03UL                        /**< Mask for EBI_CTRL */
#define _EBI_CTRL_MODE_SHIFT                 0                                   /**< Shift value for EBI_MODE */
#define _EBI_CTRL_MODE_MASK                  0x3UL                               /**< Bit mask for EBI_MODE */
#define _EBI_CTRL_MODE_DEFAULT               0x00000000UL                        /**< Mode DEFAULT for EBI_CTRL */
#define _EBI_CTRL_MODE_D8A8                  0x00000000UL                        /**< Mode D8A8 for EBI_CTRL */
#define _EBI_CTRL_MODE_D16A16ALE             0x00000001UL                        /**< Mode D16A16ALE for EBI_CTRL */
#define _EBI_CTRL_MODE_D8A24ALE              0x00000002UL                        /**< Mode D8A24ALE for EBI_CTRL */
#define EBI_CTRL_MODE_DEFAULT                (_EBI_CTRL_MODE_DEFAULT << 0)       /**< Shifted mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_MODE_D8A8                   (_EBI_CTRL_MODE_D8A8 << 0)          /**< Shifted mode D8A8 for EBI_CTRL */
#define EBI_CTRL_MODE_D16A16ALE              (_EBI_CTRL_MODE_D16A16ALE << 0)     /**< Shifted mode D16A16ALE for EBI_CTRL */
#define EBI_CTRL_MODE_D8A24ALE               (_EBI_CTRL_MODE_D8A24ALE << 0)      /**< Shifted mode D8A24ALE for EBI_CTRL */
#define EBI_CTRL_BANK0EN                     (0x1UL << 8)                        /**< Bank 0 Enable */
#define _EBI_CTRL_BANK0EN_SHIFT              8                                   /**< Shift value for EBI_BANK0EN */
#define _EBI_CTRL_BANK0EN_MASK               0x100UL                             /**< Bit mask for EBI_BANK0EN */
#define _EBI_CTRL_BANK0EN_DEFAULT            0x00000000UL                        /**< Mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_BANK0EN_DEFAULT             (_EBI_CTRL_BANK0EN_DEFAULT << 8)    /**< Shifted mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_BANK1EN                     (0x1UL << 9)                        /**< Bank 1 Enable */
#define _EBI_CTRL_BANK1EN_SHIFT              9                                   /**< Shift value for EBI_BANK1EN */
#define _EBI_CTRL_BANK1EN_MASK               0x200UL                             /**< Bit mask for EBI_BANK1EN */
#define _EBI_CTRL_BANK1EN_DEFAULT            0x00000000UL                        /**< Mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_BANK1EN_DEFAULT             (_EBI_CTRL_BANK1EN_DEFAULT << 9)    /**< Shifted mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_BANK2EN                     (0x1UL << 10)                       /**< Bank 2 Enable */
#define _EBI_CTRL_BANK2EN_SHIFT              10                                  /**< Shift value for EBI_BANK2EN */
#define _EBI_CTRL_BANK2EN_MASK               0x400UL                             /**< Bit mask for EBI_BANK2EN */
#define _EBI_CTRL_BANK2EN_DEFAULT            0x00000000UL                        /**< Mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_BANK2EN_DEFAULT             (_EBI_CTRL_BANK2EN_DEFAULT << 10)   /**< Shifted mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_BANK3EN                     (0x1UL << 11)                       /**< Bank 3 Enable */
#define _EBI_CTRL_BANK3EN_SHIFT              11                                  /**< Shift value for EBI_BANK3EN */
#define _EBI_CTRL_BANK3EN_MASK               0x800UL                             /**< Bit mask for EBI_BANK3EN */
#define _EBI_CTRL_BANK3EN_DEFAULT            0x00000000UL                        /**< Mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_BANK3EN_DEFAULT             (_EBI_CTRL_BANK3EN_DEFAULT << 11)   /**< Shifted mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_ARDYEN                      (0x1UL << 16)                       /**< ARDY Enable */
#define _EBI_CTRL_ARDYEN_SHIFT               16                                  /**< Shift value for EBI_ARDYEN */
#define _EBI_CTRL_ARDYEN_MASK                0x10000UL                           /**< Bit mask for EBI_ARDYEN */
#define _EBI_CTRL_ARDYEN_DEFAULT             0x00000000UL                        /**< Mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_ARDYEN_DEFAULT              (_EBI_CTRL_ARDYEN_DEFAULT << 16)    /**< Shifted mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_ARDYTODIS                   (0x1UL << 17)                       /**< ARDY Timeout Disable */
#define _EBI_CTRL_ARDYTODIS_SHIFT            17                                  /**< Shift value for EBI_ARDYTODIS */
#define _EBI_CTRL_ARDYTODIS_MASK             0x20000UL                           /**< Bit mask for EBI_ARDYTODIS */
#define _EBI_CTRL_ARDYTODIS_DEFAULT          0x00000000UL                        /**< Mode DEFAULT for EBI_CTRL */
#define EBI_CTRL_ARDYTODIS_DEFAULT           (_EBI_CTRL_ARDYTODIS_DEFAULT << 17) /**< Shifted mode DEFAULT for EBI_CTRL */

/* Bit fields for EBI ADDRTIMING */
#define _EBI_ADDRTIMING_RESETVALUE           0x00000100UL                             /**< Default value for EBI_ADDRTIMING */
#define _EBI_ADDRTIMING_MASK                 0x00000303UL                             /**< Mask for EBI_ADDRTIMING */
#define _EBI_ADDRTIMING_ADDRSETUP_SHIFT      0                                        /**< Shift value for EBI_ADDRSETUP */
#define _EBI_ADDRTIMING_ADDRSETUP_MASK       0x3UL                                    /**< Bit mask for EBI_ADDRSETUP */
#define _EBI_ADDRTIMING_ADDRSETUP_DEFAULT    0x00000000UL                             /**< Mode DEFAULT for EBI_ADDRTIMING */
#define EBI_ADDRTIMING_ADDRSETUP_DEFAULT     (_EBI_ADDRTIMING_ADDRSETUP_DEFAULT << 0) /**< Shifted mode DEFAULT for EBI_ADDRTIMING */
#define _EBI_ADDRTIMING_ADDRHOLD_SHIFT       8                                        /**< Shift value for EBI_ADDRHOLD */
#define _EBI_ADDRTIMING_ADDRHOLD_MASK        0x300UL                                  /**< Bit mask for EBI_ADDRHOLD */
#define _EBI_ADDRTIMING_ADDRHOLD_DEFAULT     0x00000001UL                             /**< Mode DEFAULT for EBI_ADDRTIMING */
#define EBI_ADDRTIMING_ADDRHOLD_DEFAULT      (_EBI_ADDRTIMING_ADDRHOLD_DEFAULT << 8)  /**< Shifted mode DEFAULT for EBI_ADDRTIMING */

/* Bit fields for EBI RDTIMING */
#define _EBI_RDTIMING_RESETVALUE             0x00000000UL                         /**< Default value for EBI_RDTIMING */
#define _EBI_RDTIMING_MASK                   0x00030F03UL                         /**< Mask for EBI_RDTIMING */
#define _EBI_RDTIMING_RDSETUP_SHIFT          0                                    /**< Shift value for EBI_RDSETUP */
#define _EBI_RDTIMING_RDSETUP_MASK           0x3UL                                /**< Bit mask for EBI_RDSETUP */
#define _EBI_RDTIMING_RDSETUP_DEFAULT        0x00000000UL                         /**< Mode DEFAULT for EBI_RDTIMING */
#define EBI_RDTIMING_RDSETUP_DEFAULT         (_EBI_RDTIMING_RDSETUP_DEFAULT << 0) /**< Shifted mode DEFAULT for EBI_RDTIMING */
#define _EBI_RDTIMING_RDSTRB_SHIFT           8                                    /**< Shift value for EBI_RDSTRB */
#define _EBI_RDTIMING_RDSTRB_MASK            0xF00UL                              /**< Bit mask for EBI_RDSTRB */
#define _EBI_RDTIMING_RDSTRB_DEFAULT         0x00000000UL                         /**< Mode DEFAULT for EBI_RDTIMING */
#define EBI_RDTIMING_RDSTRB_DEFAULT          (_EBI_RDTIMING_RDSTRB_DEFAULT << 8)  /**< Shifted mode DEFAULT for EBI_RDTIMING */
#define _EBI_RDTIMING_RDHOLD_SHIFT           16                                   /**< Shift value for EBI_RDHOLD */
#define _EBI_RDTIMING_RDHOLD_MASK            0x30000UL                            /**< Bit mask for EBI_RDHOLD */
#define _EBI_RDTIMING_RDHOLD_DEFAULT         0x00000000UL                         /**< Mode DEFAULT for EBI_RDTIMING */
#define EBI_RDTIMING_RDHOLD_DEFAULT          (_EBI_RDTIMING_RDHOLD_DEFAULT << 16) /**< Shifted mode DEFAULT for EBI_RDTIMING */

/* Bit fields for EBI WRTIMING */
#define _EBI_WRTIMING_RESETVALUE             0x00010000UL                         /**< Default value for EBI_WRTIMING */
#define _EBI_WRTIMING_MASK                   0x00030F03UL                         /**< Mask for EBI_WRTIMING */
#define _EBI_WRTIMING_WRSETUP_SHIFT          0                                    /**< Shift value for EBI_WRSETUP */
#define _EBI_WRTIMING_WRSETUP_MASK           0x3UL                                /**< Bit mask for EBI_WRSETUP */
#define _EBI_WRTIMING_WRSETUP_DEFAULT        0x00000000UL                         /**< Mode DEFAULT for EBI_WRTIMING */
#define EBI_WRTIMING_WRSETUP_DEFAULT         (_EBI_WRTIMING_WRSETUP_DEFAULT << 0) /**< Shifted mode DEFAULT for EBI_WRTIMING */
#define _EBI_WRTIMING_WRSTRB_SHIFT           8                                    /**< Shift value for EBI_WRSTRB */
#define _EBI_WRTIMING_WRSTRB_MASK            0xF00UL                              /**< Bit mask for EBI_WRSTRB */
#define _EBI_WRTIMING_WRSTRB_DEFAULT         0x00000000UL                         /**< Mode DEFAULT for EBI_WRTIMING */
#define EBI_WRTIMING_WRSTRB_DEFAULT          (_EBI_WRTIMING_WRSTRB_DEFAULT << 8)  /**< Shifted mode DEFAULT for EBI_WRTIMING */
#define _EBI_WRTIMING_WRHOLD_SHIFT           16                                   /**< Shift value for EBI_WRHOLD */
#define _EBI_WRTIMING_WRHOLD_MASK            0x30000UL                            /**< Bit mask for EBI_WRHOLD */
#define _EBI_WRTIMING_WRHOLD_DEFAULT         0x00000001UL                         /**< Mode DEFAULT for EBI_WRTIMING */
#define EBI_WRTIMING_WRHOLD_DEFAULT          (_EBI_WRTIMING_WRHOLD_DEFAULT << 16) /**< Shifted mode DEFAULT for EBI_WRTIMING */

/* Bit fields for EBI POLARITY */
#define _EBI_POLARITY_RESETVALUE             0x00000000UL                            /**< Default value for EBI_POLARITY */
#define _EBI_POLARITY_MASK                   0x0000001FUL                            /**< Mask for EBI_POLARITY */
#define EBI_POLARITY_CSPOL                   (0x1UL << 0)                            /**< Chip Select Polarity */
#define _EBI_POLARITY_CSPOL_SHIFT            0                                       /**< Shift value for EBI_CSPOL */
#define _EBI_POLARITY_CSPOL_MASK             0x1UL                                   /**< Bit mask for EBI_CSPOL */
#define _EBI_POLARITY_CSPOL_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for EBI_POLARITY */
#define _EBI_POLARITY_CSPOL_ACTIVELOW        0x00000000UL                            /**< Mode ACTIVELOW for EBI_POLARITY */
#define _EBI_POLARITY_CSPOL_ACTIVEHIGH       0x00000001UL                            /**< Mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_CSPOL_DEFAULT           (_EBI_POLARITY_CSPOL_DEFAULT << 0)      /**< Shifted mode DEFAULT for EBI_POLARITY */
#define EBI_POLARITY_CSPOL_ACTIVELOW         (_EBI_POLARITY_CSPOL_ACTIVELOW << 0)    /**< Shifted mode ACTIVELOW for EBI_POLARITY */
#define EBI_POLARITY_CSPOL_ACTIVEHIGH        (_EBI_POLARITY_CSPOL_ACTIVEHIGH << 0)   /**< Shifted mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_REPOL                   (0x1UL << 1)                            /**< Read Enable Polarity */
#define _EBI_POLARITY_REPOL_SHIFT            1                                       /**< Shift value for EBI_REPOL */
#define _EBI_POLARITY_REPOL_MASK             0x2UL                                   /**< Bit mask for EBI_REPOL */
#define _EBI_POLARITY_REPOL_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for EBI_POLARITY */
#define _EBI_POLARITY_REPOL_ACTIVELOW        0x00000000UL                            /**< Mode ACTIVELOW for EBI_POLARITY */
#define _EBI_POLARITY_REPOL_ACTIVEHIGH       0x00000001UL                            /**< Mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_REPOL_DEFAULT           (_EBI_POLARITY_REPOL_DEFAULT << 1)      /**< Shifted mode DEFAULT for EBI_POLARITY */
#define EBI_POLARITY_REPOL_ACTIVELOW         (_EBI_POLARITY_REPOL_ACTIVELOW << 1)    /**< Shifted mode ACTIVELOW for EBI_POLARITY */
#define EBI_POLARITY_REPOL_ACTIVEHIGH        (_EBI_POLARITY_REPOL_ACTIVEHIGH << 1)   /**< Shifted mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_WEPOL                   (0x1UL << 2)                            /**< Write Enable Polarity */
#define _EBI_POLARITY_WEPOL_SHIFT            2                                       /**< Shift value for EBI_WEPOL */
#define _EBI_POLARITY_WEPOL_MASK             0x4UL                                   /**< Bit mask for EBI_WEPOL */
#define _EBI_POLARITY_WEPOL_DEFAULT          0x00000000UL                            /**< Mode DEFAULT for EBI_POLARITY */
#define _EBI_POLARITY_WEPOL_ACTIVELOW        0x00000000UL                            /**< Mode ACTIVELOW for EBI_POLARITY */
#define _EBI_POLARITY_WEPOL_ACTIVEHIGH       0x00000001UL                            /**< Mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_WEPOL_DEFAULT           (_EBI_POLARITY_WEPOL_DEFAULT << 2)      /**< Shifted mode DEFAULT for EBI_POLARITY */
#define EBI_POLARITY_WEPOL_ACTIVELOW         (_EBI_POLARITY_WEPOL_ACTIVELOW << 2)    /**< Shifted mode ACTIVELOW for EBI_POLARITY */
#define EBI_POLARITY_WEPOL_ACTIVEHIGH        (_EBI_POLARITY_WEPOL_ACTIVEHIGH << 2)   /**< Shifted mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_ALEPOL                  (0x1UL << 3)                            /**< Address Latch Polarity */
#define _EBI_POLARITY_ALEPOL_SHIFT           3                                       /**< Shift value for EBI_ALEPOL */
#define _EBI_POLARITY_ALEPOL_MASK            0x8UL                                   /**< Bit mask for EBI_ALEPOL */
#define _EBI_POLARITY_ALEPOL_DEFAULT         0x00000000UL                            /**< Mode DEFAULT for EBI_POLARITY */
#define _EBI_POLARITY_ALEPOL_ACTIVELOW       0x00000000UL                            /**< Mode ACTIVELOW for EBI_POLARITY */
#define _EBI_POLARITY_ALEPOL_ACTIVEHIGH      0x00000001UL                            /**< Mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_ALEPOL_DEFAULT          (_EBI_POLARITY_ALEPOL_DEFAULT << 3)     /**< Shifted mode DEFAULT for EBI_POLARITY */
#define EBI_POLARITY_ALEPOL_ACTIVELOW        (_EBI_POLARITY_ALEPOL_ACTIVELOW << 3)   /**< Shifted mode ACTIVELOW for EBI_POLARITY */
#define EBI_POLARITY_ALEPOL_ACTIVEHIGH       (_EBI_POLARITY_ALEPOL_ACTIVEHIGH << 3)  /**< Shifted mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_ARDYPOL                 (0x1UL << 4)                            /**< ARDY Polarity */
#define _EBI_POLARITY_ARDYPOL_SHIFT          4                                       /**< Shift value for EBI_ARDYPOL */
#define _EBI_POLARITY_ARDYPOL_MASK           0x10UL                                  /**< Bit mask for EBI_ARDYPOL */
#define _EBI_POLARITY_ARDYPOL_DEFAULT        0x00000000UL                            /**< Mode DEFAULT for EBI_POLARITY */
#define _EBI_POLARITY_ARDYPOL_ACTIVELOW      0x00000000UL                            /**< Mode ACTIVELOW for EBI_POLARITY */
#define _EBI_POLARITY_ARDYPOL_ACTIVEHIGH     0x00000001UL                            /**< Mode ACTIVEHIGH for EBI_POLARITY */
#define EBI_POLARITY_ARDYPOL_DEFAULT         (_EBI_POLARITY_ARDYPOL_DEFAULT << 4)    /**< Shifted mode DEFAULT for EBI_POLARITY */
#define EBI_POLARITY_ARDYPOL_ACTIVELOW       (_EBI_POLARITY_ARDYPOL_ACTIVELOW << 4)  /**< Shifted mode ACTIVELOW for EBI_POLARITY */
#define EBI_POLARITY_ARDYPOL_ACTIVEHIGH      (_EBI_POLARITY_ARDYPOL_ACTIVEHIGH << 4) /**< Shifted mode ACTIVEHIGH for EBI_POLARITY */

/* Bit fields for EBI ROUTE */
#define _EBI_ROUTE_RESETVALUE                0x00000000UL                      /**< Default value for EBI_ROUTE */
#define _EBI_ROUTE_MASK                      0x0000007FUL                      /**< Mask for EBI_ROUTE */
#define EBI_ROUTE_EBIPEN                     (0x1UL << 0)                      /**< EBI Pin Enable */
#define _EBI_ROUTE_EBIPEN_SHIFT              0                                 /**< Shift value for EBI_EBIPEN */
#define _EBI_ROUTE_EBIPEN_MASK               0x1UL                             /**< Bit mask for EBI_EBIPEN */
#define _EBI_ROUTE_EBIPEN_DEFAULT            0x00000000UL                      /**< Mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_EBIPEN_DEFAULT             (_EBI_ROUTE_EBIPEN_DEFAULT << 0)  /**< Shifted mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS0PEN                     (0x1UL << 1)                      /**< EBI_CS0 Pin Enable */
#define _EBI_ROUTE_CS0PEN_SHIFT              1                                 /**< Shift value for EBI_CS0PEN */
#define _EBI_ROUTE_CS0PEN_MASK               0x2UL                             /**< Bit mask for EBI_CS0PEN */
#define _EBI_ROUTE_CS0PEN_DEFAULT            0x00000000UL                      /**< Mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS0PEN_DEFAULT             (_EBI_ROUTE_CS0PEN_DEFAULT << 1)  /**< Shifted mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS1PEN                     (0x1UL << 2)                      /**< EBI_CS1 Pin Enable */
#define _EBI_ROUTE_CS1PEN_SHIFT              2                                 /**< Shift value for EBI_CS1PEN */
#define _EBI_ROUTE_CS1PEN_MASK               0x4UL                             /**< Bit mask for EBI_CS1PEN */
#define _EBI_ROUTE_CS1PEN_DEFAULT            0x00000000UL                      /**< Mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS1PEN_DEFAULT             (_EBI_ROUTE_CS1PEN_DEFAULT << 2)  /**< Shifted mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS2PEN                     (0x1UL << 3)                      /**< EBI_CS2 Pin Enable */
#define _EBI_ROUTE_CS2PEN_SHIFT              3                                 /**< Shift value for EBI_CS2PEN */
#define _EBI_ROUTE_CS2PEN_MASK               0x8UL                             /**< Bit mask for EBI_CS2PEN */
#define _EBI_ROUTE_CS2PEN_DEFAULT            0x00000000UL                      /**< Mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS2PEN_DEFAULT             (_EBI_ROUTE_CS2PEN_DEFAULT << 3)  /**< Shifted mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS3PEN                     (0x1UL << 4)                      /**< EBI_CS3 Pin Enable */
#define _EBI_ROUTE_CS3PEN_SHIFT              4                                 /**< Shift value for EBI_CS3PEN */
#define _EBI_ROUTE_CS3PEN_MASK               0x10UL                            /**< Bit mask for EBI_CS3PEN */
#define _EBI_ROUTE_CS3PEN_DEFAULT            0x00000000UL                      /**< Mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_CS3PEN_DEFAULT             (_EBI_ROUTE_CS3PEN_DEFAULT << 4)  /**< Shifted mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_ALEPEN                     (0x1UL << 5)                      /**< EBI_ALE Pin Enable */
#define _EBI_ROUTE_ALEPEN_SHIFT              5                                 /**< Shift value for EBI_ALEPEN */
#define _EBI_ROUTE_ALEPEN_MASK               0x20UL                            /**< Bit mask for EBI_ALEPEN */
#define _EBI_ROUTE_ALEPEN_DEFAULT            0x00000000UL                      /**< Mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_ALEPEN_DEFAULT             (_EBI_ROUTE_ALEPEN_DEFAULT << 5)  /**< Shifted mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_ARDYPEN                    (0x1UL << 6)                      /**< EBI_ARDY Pin Enable */
#define _EBI_ROUTE_ARDYPEN_SHIFT             6                                 /**< Shift value for EBI_ARDYPEN */
#define _EBI_ROUTE_ARDYPEN_MASK              0x40UL                            /**< Bit mask for EBI_ARDYPEN */
#define _EBI_ROUTE_ARDYPEN_DEFAULT           0x00000000UL                      /**< Mode DEFAULT for EBI_ROUTE */
#define EBI_ROUTE_ARDYPEN_DEFAULT            (_EBI_ROUTE_ARDYPEN_DEFAULT << 6) /**< Shifted mode DEFAULT for EBI_ROUTE */

/** @} End of group EFM32G_EBI */


