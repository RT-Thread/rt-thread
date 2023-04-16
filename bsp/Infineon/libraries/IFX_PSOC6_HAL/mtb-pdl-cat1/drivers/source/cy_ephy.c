/***************************************************************************//**
* \file cy_ephy.c
* \version 1.0
*
* Provides an API implementation of the Ethernet PHY driver
*
********************************************************************************
* \copyright
* Copyright 2020, Cypress Semiconductor Corporation
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

#include "cy_device.h"

#if defined (CY_IP_MXETH)

#include "cy_ephy.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define DEFAULT_PHY_ADDRESS     0x0
#define CY_EPHY_INVALID_VALUE   0xFFFFUL


/*******************************************************************************
* Function Name: Cy_EPHY_Init
****************************************************************************//**
*
* This function initializes the private structure and assign a PHY-read,
* PHY-write function handle to its private data structure.
*
* \param phy pointer to PHY private data structure.
* \param fnRead pointer to read function implemented in application
* \param fnWrite pointer to write function implemented in application
*
* \return Initialization status
* \return CY_EPHY_SUCCESS for successfully initializes the internal data structures.
*
*******************************************************************************/
cy_en_ephy_status_t Cy_EPHY_Init( cy_stc_ephy_t *phy, phy_read_handle fnRead, phy_write_handle fnWrite )
{
    CY_ASSERT_L2(phy != NULL);
    CY_ASSERT_L2(fnRead != NULL);
    CY_ASSERT_L2(fnWrite != NULL);

    phy->fnPhyRead = fnRead;
    phy->fnPhyWrite = fnWrite;
    phy->phyId = CY_EPHY_INVALID_VALUE;
    phy->state = CY_EPHY_DOWN;
    phy->anar=0;
    phy->bmcr=0;

    return CY_EPHY_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_EPHY_Discover
****************************************************************************//**
*
* Discovers connected PHY at address zero. Reads ID1 and ID2 register to form
* PHY ID.
*
* \param phy pointer to PHY private data structure
*
* \return CY_EPHY_ERROR PHY chip contains invalid PHY ID
* \return CY_EPHY_SUCCESS PHY chip contains a valid PHY ID
*
*******************************************************************************/
cy_en_ephy_status_t Cy_EPHY_Discover( cy_stc_ephy_t *phy )
{
    uint32_t phyAddress = DEFAULT_PHY_ADDRESS;
    uint32_t ulLowerID = 0;
    uint32_t ulUpperID = 0;
    uint32_t ulPhyID = 0;

    CY_ASSERT_L2(phy->fnPhyRead != NULL);
    CY_ASSERT_L2(phy->fnPhyWrite != NULL);

    phy->fnPhyRead( phyAddress, PHYREG_03_PHYSID2, &ulLowerID );
    if ( CY_EPHY_INVALID_VALUE == ulLowerID )
    {
        return CY_EPHY_ERROR;
    }
    /* A valid PHY id can not be all zeros or all ones. */
    if( ulLowerID != ( uint16_t )0UL )
    {
        phy->fnPhyRead( phyAddress, PHYREG_02_PHYSID1, &ulUpperID );
        if ( CY_EPHY_INVALID_VALUE == ulUpperID )
        {
            return CY_EPHY_ERROR;
        }
        ulPhyID = ( _VAL2FLD( PHYID_ID1, ulUpperID ) | _VAL2FLD( PHYID_ID2, ulLowerID ) );
    }
    phy->phyId = ulPhyID;
    return CY_EPHY_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_EPHY_Reset
****************************************************************************//**
* Soft reset PHY by enabling 15th bit of BMCR register
*
* \param phy pointer to PHY private data structure
*
* \return CY_EPHY_SUCCESS for successful soft reset
*
*******************************************************************************/
cy_en_ephy_status_t Cy_EPHY_Reset(cy_stc_ephy_t *phy)
{
    uint32_t ulConfig;
    uint32_t phyAddress = DEFAULT_PHY_ADDRESS;
    uint32_t delay, max_delay=10;

    CY_ASSERT_L2(phy->fnPhyRead != NULL);
    CY_ASSERT_L2(phy->fnPhyWrite != NULL);

    /* Read Control register. */
    phy->fnPhyRead( phyAddress, PHYREG_00_BMCR, &ulConfig );
    phy->fnPhyWrite( phyAddress, PHYREG_00_BMCR, ( ulConfig | PHYBMCR_RESET_Msk ) );
    /* The reset should last less than a second. */
    for( delay=0; delay < max_delay; delay++ )
    {
        phy->fnPhyRead( phyAddress, PHYREG_00_BMCR, &ulConfig );
        if(_FLD2VAL(PHYBMCR_RESET, ulConfig) == 0UL)
        {
            break;
        }
        Cy_SysLib_Delay(100);
    }

    /* Clear the reset bits. */
    phy->fnPhyRead( phyAddress, PHYREG_00_BMCR, &ulConfig );
    phy->fnPhyWrite( phyAddress, PHYREG_00_BMCR, ( ulConfig & ( ~PHYBMCR_RESET_Msk ) ) );
    Cy_SysLib_Delay(50);
    return CY_EPHY_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_EPHY_Configure
****************************************************************************//**
*
* Configures PHY with user provided speed and duplex mode
*
* \param phy pointer to PHY private data structure
* \param config pointer to PHY configuration structure
*
* \return CY_EPHY_SUCCESS
* Successfully configure PHY registers
* \return CY_EPHY_AN_NOT_SUPPORTED
* PHY does not support Auto-Negotiation.
*
* \note For Auto-Negotiation configure the speed and duplex mode to
*       CY_EPHY_SPEED_AUTO and CY_EPHY_DUPLEX_AUTO respectively. In this configuration
*       PHY will advertise with highest capabilities. Also if vendor specific registers
*       are supported then user may needs to configure the vendor specific registers to
*       highest capabilities. For more details please refer to the PHY datasheet.
*
*******************************************************************************/
cy_en_ephy_status_t Cy_EPHY_Configure( cy_stc_ephy_t *phy, cy_stc_ephy_config_t *config )
{
    uint32_t ulConfig, ulAdvertise = 0, reg;
    uint32_t phyAddress = DEFAULT_PHY_ADDRESS;
    cy_en_ephy_status_t ret = CY_EPHY_SUCCESS;

    CY_ASSERT_L2(phy->fnPhyRead != NULL);
    CY_ASSERT_L2(phy->fnPhyWrite != NULL);

    /* Read Control register. */
    phy->fnPhyRead( phyAddress, PHYREG_00_BMCR, &ulConfig );

    if ((config->speed == ((uint32_t)CY_EPHY_SPEED_AUTO)) || (config->duplex == ((uint32_t)CY_EPHY_DUPLEX_AUTO)))
    {
        /* check AN is supported */
        phy->fnPhyRead( phyAddress, PHYREG_01_BMSR, &reg);
        if (_FLD2VAL(PHYBMSR_AN_ABILITY,reg) == 1UL)
        {
            /* 1. BMCR enable AN */
            ulConfig |= PHYBMCR_AN_ENABLE_Msk;
            /* 2. BMCR restart AN */
            ulConfig |= PHYBMCR_AN_RESTART_Msk;
        }
        else
        {
            ret = CY_EPHY_AN_NOT_SUPPORTED;
        }
    }
    else
    {
        ulConfig &= ~( PHYBMCR_SPEED_1000_Msk | PHYBMCR_SPEED_100_Msk | PHYBMCR_FULL_DUPLEX_Msk | PHYBMCR_AN_ENABLE_Msk);

        if( config->speed == ((uint32_t)CY_EPHY_SPEED_100))
        {
            ulConfig |= PHYBMCR_SPEED_100_Msk;
        }
        else if (config->speed == ((uint32_t)CY_EPHY_SPEED_1000))
        {
            ulConfig |= PHYBMCR_AN_ENABLE_Msk;
            ulConfig |= PHYBMCR_SPEED_1000_Msk;
        }
        else if( config->speed == ((uint32_t)CY_EPHY_SPEED_10))
        {
            ulConfig &= ~PHYBMCR_SPEED_100_Msk;
        }
        else
        {
            /* Invalid speed */
            ret = CY_EPHY_INVALID_SPEED;
        }

        if( config->duplex == ((uint32_t)CY_EPHY_DUPLEX_FULL))
        {
            ulConfig |= PHYBMCR_FULL_DUPLEX_Msk;
        }
        else if( config->duplex == ((uint32_t)CY_EPHY_DUPLEX_HALF))
        {
            ulConfig &= ~PHYBMCR_FULL_DUPLEX_Msk;
        }
        else
        {
            /* invalid duplex mode */
            ret = CY_EPHY_INVALID_DUPLEX;
        }
    }

    if (ret == CY_EPHY_SUCCESS)
    {
        /* Keep these values for later use. */
        phy->bmcr = ulConfig & ~PHYBMCR_ISOLATE_Msk;
        phy->anar = ulAdvertise;

        /* configure bmcr */
        phy->fnPhyWrite( phyAddress, PHYREG_00_BMCR, phy->bmcr);
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_EPHY_GetLinkStatus
****************************************************************************//**
*
* Get current link status of PHY.
*
* \param phy pointer to PHY private data structure
*
* \return
* link status of PHY (0=down, 1=up)
*
*******************************************************************************/
uint32_t Cy_EPHY_GetLinkStatus(cy_stc_ephy_t *phy)
{
    uint32_t phyAddress=DEFAULT_PHY_ADDRESS;
    uint32_t status;

    CY_ASSERT_L2(phy->fnPhyRead != NULL);
    CY_ASSERT_L2(phy->fnPhyWrite != NULL);

    /* read bmcr */
    phy->fnPhyRead( phyAddress, PHYREG_00_BMCR, &status);

    /* check for auto-neg-restart. Autoneg is being started, therefore disregard
     * BMSR value and report link as down.
     */
    if (0UL != (status & PHYBMCR_AN_RESTART_Msk))
    {
        return 0UL;
    }

    /* Read link and Auto-Negotiation status */
    status = 0;
    phy->fnPhyRead( phyAddress, PHYREG_01_BMSR, &status);

    if (CY_EPHY_INVALID_VALUE == status)
    {
        return 0UL;
    }
    else
    {
        return _FLD2VAL( PHYBMSR_LINK_STATUS, status);
    }
}


/*******************************************************************************
* Function Name: Cy_EPHY_GetAutoNegotiationStatus
****************************************************************************//**
*
* Get current Auto-Negotiation status (completed or In-progress).
*
* \param phy pointer to PHY private data structure
*
* \return
* Auto-Negotiation status of PHY.
* 0 = Auto-Negotiation process is not completed.
* 1 = Auto-Negotiation process is completed.
*
*******************************************************************************/
uint32_t Cy_EPHY_GetAutoNegotiationStatus(cy_stc_ephy_t *phy)
{
    uint32_t reg;
    uint32_t phyAddress=DEFAULT_PHY_ADDRESS;

    CY_ASSERT_L2(phy->fnPhyRead != NULL);
    CY_ASSERT_L2(phy->fnPhyWrite != NULL);

    phy->fnPhyRead(phyAddress, PHYREG_01_BMSR, &reg);

    return _FLD2VAL(PHYBMSR_AN_COMPLETE, reg);
}


/*******************************************************************************
* Function Name: Cy_EPHY_getLinkPartnerCapabilities
****************************************************************************//**
*
* Gets Link partner capabilities (speed and duplex)
*
* \param phy Pointer to PHY private data structure
* \param lpConfig [Output] Speed and duplex information
*
* \return CY_EPHY_SUCCESS : Success in processing the link capability.
* \return CY_EPHY_ERROR : Error in processing the link capability. Ignore the lpConfig output parameter.
* \note This function should be called after Auto-Negotiation is completed ( \ref Cy_EPHY_GetAutoNegotiationStatus )
*
*******************************************************************************/
cy_en_ephy_status_t Cy_EPHY_getLinkPartnerCapabilities(cy_stc_ephy_t *phy, cy_stc_ephy_config_t *lpConfig)
{
    uint32_t reg;
    cy_en_ephy_status_t ret = CY_EPHY_SUCCESS;
    uint32_t phyAddress = DEFAULT_PHY_ADDRESS;

    CY_ASSERT_L2(phy->fnPhyRead != NULL);
    CY_ASSERT_L2(phy->fnPhyWrite != NULL);

    /* default assignment */
    lpConfig->speed = (uint32_t)CY_EPHY_SPEED_10;
    lpConfig->duplex = (uint32_t)CY_EPHY_DUPLEX_HALF;

    /* Check Extended Register is supported */
    phy->fnPhyRead( phyAddress, PHYREG_01_BMSR, &reg);
    if (_FLD2VAL( PHYBMSR_EXT_CAPABILITY, reg) == 1UL)
    {
        /* 1. check gigabit is supported or not */
        phy->fnPhyRead( phyAddress, PHYREG_10_MSSR, &reg);
        if (_FLD2VAL( MSSR_1000BASE_T_FULLDUPLEX, reg) == 1UL)
        {
            lpConfig->speed = (uint32_t)CY_EPHY_SPEED_1000;
            lpConfig->duplex = (uint32_t)CY_EPHY_DUPLEX_FULL;
        }
        else if (_FLD2VAL( MSSR_1000BASE_T_HALFDUPLEX, reg) == 1UL)
        {
            lpConfig->speed = (uint32_t)CY_EPHY_SPEED_1000;
            lpConfig->duplex = (uint32_t)CY_EPHY_DUPLEX_HALF;
        }
        else
        {
            /* 2. if not then check 10 and 100 Mbps */
            phy->fnPhyRead( phyAddress, PHYREG_05_ANLPAR, &reg);
            if (_FLD2VAL( ANLPAR_TXFD, reg) == 1UL)
            {
                lpConfig->speed = (uint32_t)CY_EPHY_SPEED_100;
                lpConfig->duplex = (uint32_t)CY_EPHY_DUPLEX_FULL;
            }
            else if ((_FLD2VAL( ANLPAR_T4, reg) == 1UL) || (_FLD2VAL( ANLPAR_TX, reg) == 1UL))
            {
                lpConfig->speed = (uint32_t)CY_EPHY_SPEED_100;
                lpConfig->duplex = (uint32_t)CY_EPHY_DUPLEX_HALF;
            }
            else if (_FLD2VAL( ANLPAR_10FD, reg) == 1UL)
            {
                lpConfig->speed = (uint32_t)CY_EPHY_SPEED_10;
                lpConfig->duplex = (uint32_t)CY_EPHY_DUPLEX_FULL;
            }
            else if (_FLD2VAL( ANLPAR_10, reg) == 1UL)
            {
                lpConfig->speed = (uint32_t)CY_EPHY_SPEED_10;
                lpConfig->duplex = (uint32_t)CY_EPHY_DUPLEX_HALF;
            }
            else
            {
                ret = CY_EPHY_ERROR;
            }
        }
    }
    else
    {
        ret = CY_EPHY_ERROR;
    }

    return ret;
}


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXETH */

/* [] END OF FILE */
