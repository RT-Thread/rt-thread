/***************************************************************************//**
* \file cy_ephy.h
* \version 1.0
*
* Provides an API declaration of the Ethernet Generic PHY driver
*
********************************************************************************
* \copyright
* Copyright 2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_ephy
* \{
* The PHY chip is outside of SoC. It has 15 IEEE specified standard registers.
* The EPHY driver implements those standard registers. It provides an API for
* PHY management abstraction layer.
*
* The functions and other declarations used in this driver are in cy_ephy.h.
* You can include cy_pdl.h (ModusToolbox only) to get access to all functions
* and declarations in the PDL.
*
* \note Apart from IEEE standard registers, optionally it has some vendor
* specific extended registers. The EPHY driver does not implement extended
* registers. Any access to PHY registers can be done by using MAC driver APIs,
* i.e, \ref Cy_ETHIF_PhyRegRead() and \ref Cy_ETHIF_PhyRegWrite().
*
*
* \section group_ephy_configuration Configuration Considerations
* Code snippet for Initializing DP83867IR PHY chip
*
* \snippet ethernet/snippet/main.c snippet_Cy_EPHY_DP83867IR_Init
*
* \section group_ephy_more_information More Information
*
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_ephy_MISRA MISRA-C Compliance
* The EPHY driver does not have any specific deviation
*
* \section group_ephy_Changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_ephy_macros Macros
* \defgroup group_ephy_functions Functions
* \defgroup group_ephy_enums Enumerated Types
* \defgroup group_ephy_data_structures Data Structures
*/

#if !defined (CY_EPHY_H)
#define CY_EPHY_H

#include "cy_device.h"

#if defined (CY_IP_MXETH)

#include <stddef.h>
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_ephy_macros
* \{
*/

/** Driver major version */
#define CY_EPHY_DRV_VERSION_MAJOR       1

/** Driver minor version */
#define CY_EPHY_DRV_VERSION_MINOR       0

/** EPHY driver ID */
#define CY_EPHY_ID CY_PDL_DRV_ID(0x70U)

/** \} group_ephy_macros */

/***************************************
*        Constants
***************************************/

/** \cond INTERNAL */

#define MIN_PHY_ADDRESS      0
#define MAX_PHY_ADDRESS      31

/** Naming and numbering of basic PHY registers. */
#define PHYREG_00_BMCR                  (0x00UL)   /**< Basic Mode Control Register. */
#define PHYREG_01_BMSR                  (0x01UL)   /**< Basic Mode Status Register. */
#define PHYREG_02_PHYSID1               (0x02UL)   /**< PHYS ID 1 */
#define PHYREG_03_PHYSID2               (0x03UL)   /**< PHYS ID 2 */
#define PHYREG_04_ANAR                  (0x04UL)   /**< Advertisement control reg */
#define PHYREG_05_ANLPAR                (0x05UL)   /**< Auto-Negotiation Link Partner Ability Register */
#define PHYREG_10_MSSR                  (0x0AUL)   /**< Master slave status register */

/** Bit fields for 'PHYREG_00_BMCR' the 'Basic Mode Control Register'. */
#define PHYBMCR_SPEED_1000_Msk          (0x0040UL) /**< Set Network speed. 1:1000Mbps 0:10Mbps */
#define PHYBMCR_SPEED_1000_Pos          (6UL)
#define PHYBMCR_FULL_DUPLEX_Msk         (0x0100UL) /**< Full duplex. */
#define PHYBMCR_FULL_DUPLEX_Pos         (8UL)
#define PHYBMCR_AN_RESTART_Msk          (0x0200UL) /**< Auto negotiation restart. */
#define PHYBMCR_AN_RESTART_Pos          (9UL)
#define PHYBMCR_ISOLATE_Msk             (0x0400UL) /**< 1 = Isolates 0 = Normal operation. */
#define PHYBMCR_ISOLATE_Pos             (10UL)
#define PHYBMCR_AN_ENABLE_Msk           (0x1000UL) /**< Enable auto negotiation. */
#define PHYBMCR_AN_ENABLE_Pos           (12UL)
#define PHYBMCR_SPEED_100_Msk           (0x2000UL) /**< Set Network speed. 1:100Mbps 0:10Mbps */
#define PHYBMCR_SPEED_100_Pos           (13UL)
#define PHYBMCR_RESET_Msk               (0x8000UL) /**< Reset the PHY. */
#define PHYBMCR_RESET_Pos               (15UL)

/** Bit fields for 'BMSR', 'Basic Mode Status Register' */
#define PHYBMSR_EXT_CAPABILITY_Msk      (0x0001UL) /**< 1 = Extended register capable */
#define PHYBMSR_EXT_CAPABILITY_Pos      (0UL)
#define PHYBMSR_JABBER_DETECTED_Msk     (0x0002UL) /**< 1 = Jabber condition detected */
#define PHYBMSR_JABBER_DETECTED_Pos     (1UL)
#define PHYBMSR_LINK_STATUS_Msk         (0x0004UL) /**< Link Status. 1=Link was good since last read of this register. (10/100/1000Mbps operation) 0=Link was lost since last read of this register.*/
#define PHYBMSR_LINK_STATUS_Pos         (2UL)
#define PHYBMSR_AN_ABILITY_Msk          (0x0008UL) /**< 1 = Device is able to perform Auto-Negotiation.*/
#define PHYBMSR_AN_ABILITY_Pos          (3UL)
#define PHYBMSR_REMOTE_FAULT_Msk        (0x0010UL) /**< 1 = Remote Fault condition detected. 0 = No remote fault condition detected */
#define PHYBMSR_REMOTE_FAULT_Pos        (4UL)
#define PHYBMSR_AN_COMPLETE_Msk         (0x0020UL) /**< 1 = Auto-Negotiation process completed. 0 = Auto-Negotiation process not complete. */
#define PHYBMSR_AN_COMPLETE_Pos         (5UL)
#define PHYBMSR_10BASE_T_HD_Msk         (0x0800UL) /**< 10BASE-T Half Duplex Capable */
#define PHYBMSR_10BASE_T_HD_Pos         (11UL)
#define PHYBMSR_10BASE_T_FD_Msk         (0x1000UL) /**< 10BASE-T Full Duplex Capable */
#define PHYBMSR_10BASE_T_FD_Pos         (12UL)
#define PHYBMSR_100BASE_TX_HD_Msk       (0x2000UL) /**< 100BASE-TX Half Duplex Capable */
#define PHYBMSR_100BASE_TX_HD_Pos       (13UL)
#define PHYBMSR_100BASE_TX_FD_Msk       (0x4000UL) /**< 100BASE-TX Full Duplex Capable */
#define PHYBMSR_100BASE_TX_FD_Pos       (14UL)
#define PHYBMSR_100BASE_T4_Msk          (0x8000UL) /**< 100BASE-T4 Capable */
#define PHYBMSR_100BASE_T4_Pos          (15UL)     /**< 100BASE-T4 Capable */

/** PHYREG_02_PHYSID1 */
#define PHYID1_OUI_Msk                  (0xFFFFUL) /**< OUI: 6-21st bits */
#define PHYID1_OUI_Pos                  (0UL)

/** PHYREG_03_PHYSID2 */
#define PHYID2_REV_NUM_Msk              (0x000FUL) /**< Revision Number */
#define PHYID2_REV_NUM_Pos              (0UL)
#define PHYID2_MODEL_NUM_Msk            (0x03F0UL) /**< Model Number */
#define PHYID2_MODEL_NUM_Pos            (4UL)
#define PHYID2_OUI_LSB_Msk              (0xFC00UL) /**< OUI_LSB: Assign to 0-5th bits of OUI */
#define PHYID2_OUI_LSB_Pos              (10UL)

#define PHYID_ID1_Msk                   (0xFFFF0000UL) /**< ID1 */
#define PHYID_ID1_Pos                   (16UL)
#define PHYID_ID2_Msk                   (0xFFFFUL) /**< ID2 */
#define PHYID_ID2_Pos                   (0UL)

/* Auto-Negotiation Advertisement Register (ANAR), Address 0x0004 */
/** Description of all capabilities that can be advertised to the peer */
#define PHYANAR_PSB_Msk                 (0x001FUL) /**< Protocol Selection Bits. <00001> indicates that this device supports IEEE 802.3. */
#define PHYANAR_PSB_Pos                 (0UL)
#define PHYANAR_10BASE_T_Msk            (0x0020UL) /**< Try for 10mbps half-duplex. */
#define PHYANAR_10BASE_T_Pos            (5UL)
#define PHYANAR_10BASE_T_FD_Msk         (0x0040UL) /**< Try for 10mbps full-duplex. */
#define PHYANAR_10BASE_T_FD_Pos         (6UL)
#define PHYANAR_100BASE_TX_Msk          (0x0080UL) /**< Try for 100mbps half-duplex. */
#define PHYANAR_100BASE_TX_Pos          (7UL)
#define PHYANAR_100BASE_TX_FD_Msk       (0x0100UL) /**< Try for 100mbps full-duplex. */
#define PHYANAR_100BASE_TX_FD_Pos       (8UL)
#define PHYANAR_ALL_Msk                 ( PHYANAR_10BASE_T_Msk | PHYANAR_10BASE_T_FD_Msk | PHYANAR_100BASE_TX_Msk | PHYANAR_100BASE_TX_FD_Msk )

/* Auto-Negotiation Link Partner Ability Register (ANLPAR), Address 0x0005 */
#define ANLPAR_10_Msk                           (0x00000020UL)  /**< 10BASE-Te Support */
#define ANLPAR_10_Pos                           (5UL)           /**< 10BASE-Te bit position */
#define ANLPAR_10FD_Msk                         (0x00000040UL)  /**< 10BASE-Te Full Duplex Support */
#define ANLPAR_10FD_Pos                         (6UL)           /**< 10BASE-Te Full Duplex bit position */

#define ANLPAR_TX_Msk                           (0x00000080UL)  /**< 100BASE-TX Support */
#define ANLPAR_TX_Pos                           (7UL)           /**< 100BASE-TX bit position */
#define ANLPAR_TXFD_Msk                         (0x00000100UL)  /**< 100BASE-TX Full Duplex Support */
#define ANLPAR_TXFD_Pos                         (8UL)           /**< 100BASE-TX Full Duplex bit position */
#define ANLPAR_T4_Msk                           (0x00000200UL)  /**< 100BASE-T4 Support */
#define ANLPAR_T4_Pos                           (9UL)           /**< 100BASE-T4 bit position */

/* MASTER-SLAVE status register (Register 10) */
#define MSSR_1000BASE_T_HALFDUPLEX_Msk          (0x00000400UL)  /**< 1000BASE-T Half-Duplex Capable */
#define MSSR_1000BASE_T_HALFDUPLEX_Pos          (10UL)          /**< 1000BASE-T Half-Duplex bit position */
#define MSSR_1000BASE_T_FULLDUPLEX_Msk          (0x00000800UL)  /**< 1000BASE-T Full-Duplex Capable */
#define MSSR_1000BASE_T_FULLDUPLEX_Pos          (11UL)          /**< 1000BASE-T Full-Duplex bit position */


/******************************************************************************
* Global Enumerations definitions
******************************************************************************/

/* PHY state machine states */
typedef enum {
    CY_EPHY_DOWN,       /**< PHY device and driver are not ready for anything */
    CY_EPHY_READY,      /** < PHY is ready to send and receive packets, but the controller is not */
    CY_EPHY_UP,         /**< The PHY and attached device are ready to do work */
    CY_EPHY_AN,         /**< The PHY is currently negotiating the link state. Link is therefore down for now */
    CY_EPHY_RUNNING,    /**< PHY is currently up, running, and possibly sending and/or receiving packets */
} cy_en_ephy_state_t;

/** \endcond */

/**
* \addtogroup group_ephy_enums
* \{
*/

/** EPHY Driver error codes */
typedef enum
{
    CY_EPHY_SUCCESS   = 0x00U,                                    /**< Returned successful */
    CY_EPHY_AN_NOT_SUPPORTED = 0x01U,                             /**< Auto Negotiation is not supported */
    CY_EPHY_INVALID_SPEED = 0x02U,                                /**< Invalid speed */
    CY_EPHY_INVALID_DUPLEX = 0x03U,                               /**< Invalid duplex */
    CY_EPHY_ERROR     = CY_EPHY_ID | CY_PDL_STATUS_ERROR | 0x01U, /**< Bad parameter or Generic Error */
} cy_en_ephy_status_t;

/** PHY Duplex Mode */
typedef enum
{
    CY_EPHY_DUPLEX_HALF,    /**< half duplex */
    CY_EPHY_DUPLEX_FULL,    /**< full duplex */
    CY_EPHY_DUPLEX_AUTO     /**< both half/full duplex */
} cy_en_ephy_duplex_t;

/** PHY Speed */
typedef enum
{
    CY_EPHY_SPEED_10,   /**< 10Mbps */
    CY_EPHY_SPEED_100,  /**< 100Mbps */
    CY_EPHY_SPEED_1000, /**< 1000Mbps */
    CY_EPHY_SPEED_AUTO  /**< All 10/100/1000 Mbps */
} cy_en_ephy_speed_t;

/** \} group_ephy_enums */

/******************************************************************************
* Global Data Structure definitions
******************************************************************************/

/**
* \addtogroup group_ephy_data_structures
* \{
*/

/** PHY read handle to application */
typedef void (*phy_read_handle)(uint32_t phyAddr, uint32_t regAddress, uint32_t *value);

/** PHY write handle to application */
typedef void (*phy_write_handle)(uint32_t phyAddr, uint32_t regAddress, uint32_t value);

/** This is the private data structure of EPHY. This has be instantiated by application */
typedef struct cy_stc_ephy
{
    phy_read_handle fnPhyRead; /**< read handle */
    phy_write_handle fnPhyWrite; /**< write handle */
    uint32_t phyId; /**< phy ID */
    cy_en_ephy_state_t state; /**< PHY state */
    uint32_t bmcr; /**< store the BMCR value while PHY configuration */
    uint32_t anar; /**< store the ANAR value while PHY configuration */
} cy_stc_ephy_t;

/** EPHY configuration */
typedef struct cy_stc_ephy_config
{
    uint32_t speed; /**< speed */
    uint32_t duplex; /**< suplex mode */
} cy_stc_ephy_config_t;

/** \} group_ephy_data_structures */


/******************************************************************************
* Global functions *
******************************************************************************/

/**
* \addtogroup group_ephy_functions
* \{
*/


cy_en_ephy_status_t Cy_EPHY_Init(cy_stc_ephy_t *phy, phy_read_handle fnRead, phy_write_handle fnWrite);

cy_en_ephy_status_t Cy_EPHY_Discover(cy_stc_ephy_t *phy);

cy_en_ephy_status_t Cy_EPHY_Configure(cy_stc_ephy_t *phy, cy_stc_ephy_config_t *config);

uint32_t Cy_EPHY_GetLinkStatus(cy_stc_ephy_t *phy);

cy_en_ephy_status_t Cy_EPHY_Reset(cy_stc_ephy_t *phy);

uint32_t Cy_EPHY_GetAutoNegotiationStatus(cy_stc_ephy_t *phy);

cy_en_ephy_status_t Cy_EPHY_getLinkPartnerCapabilities(cy_stc_ephy_t *phy, cy_stc_ephy_config_t *lpConfig);


/** \} group_ephy_functions */



#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXETH */

#endif /* CY_EPHY_H */

/** \} group_ephy */

/* [] END OF FILE */
