/**
 *  \file   phy.c
 *
 *  \brief  APIs for configuring ethernet PHYs
 *
 *   This file contains the device abstraction APIs for ethernet PHYs.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "hw_types.h"
#include "mdio.h"
#include "phy.h"

#define PHY_ADV_VAL_MASK                 (0x01e0)
#define PHY_GIG_ADV_VAL_MASK             (0x0300)

/*******************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/
/**
 * \brief   Reads the PHY ID.
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 *
 * \return  32 bit PHY ID (ID1:ID2)
 *
 **/
unsigned int PhyIDGet(unsigned int mdioBaseAddr, unsigned int phyAddr)
{
    unsigned int id = 0;
    unsigned short data;

    /* read the ID1 register */
    MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_ID1, &data);

    /* update the ID1 value */
    id = data << PHY_ID_SHIFT;
 
    /* read the ID2 register */
    MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_ID2, &data);

    /* update the ID2 value */
    id |= data; 

    /* return the ID in ID1:ID2 format */
    return id;
}

/**
 * \brief   Reads a register from the the PHY
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 * \param   regIdx        Index of the register to be read
 * \param   regValAdr     address where value of the register will be written
 *
 * \return  status of the read
 *
 **/
unsigned int PhyRegRead(unsigned int mdioBaseAddr, unsigned int phyAddr,
                        unsigned int regIdx, unsigned short *regValAdr)
{
    return (MDIOPhyRegRead(mdioBaseAddr, phyAddr, regIdx, regValAdr));
}

/**
 * \brief   Writes a register with the input
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 * \param   regIdx        Index of the register to be read
 * \param   regValAdr     value to be written
 *
 * \return  None
 *
 **/
void PhyRegWrite(unsigned int mdioBaseAddr, unsigned int phyAddr,
                 unsigned int regIdx, unsigned short regVal)
{
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, regIdx, regVal);
}

/**
 * \brief   Enables Loop Back mode
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 *
 * \return  status after enabling.  \n
 *          TRUE if loop back is enabled \n
 *          FALSE if not able to enable
 *
 **/
unsigned int PhyLoopBackEnable(unsigned int mdioBaseAddr, unsigned int phyAddr)
{
    unsigned short data;

    if(MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_BCR, &data) != TRUE )
    {
        return FALSE;
    }

    data |= PHY_LPBK_ENABLE;

    /* Enable loop back */
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_BCR, data);

    return TRUE;
}

/**
 * \brief   Disables Loop Back mode
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 *
 * \return  status after enabling.  \n
 *          TRUE if loop back is disabled \n
 *          FALSE if not able to disable
 *
 **/
unsigned int PhyLoopBackDisable(unsigned int mdioBaseAddr, unsigned int phyAddr)
{
    unsigned short data;

    if(MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_BCR, &data) != TRUE )
    {
        return FALSE;
    }

    data &= ~(PHY_LPBK_ENABLE);

    /* Disable loop back */
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_BCR, data);

    return TRUE;
}

/**
 * \brief   Resets the PHY
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 * \param   speed         Speed to be enabled
 * \param   duplexMode    Duplex Mode
 *
 * \return  status after configuring \n
 *          TRUE if configuration successful
 *          FALSE if configuration failed
 *
 **/
unsigned int PhyReset(unsigned int mdioBaseAddr, unsigned int phyAddr)
{
    unsigned short data;

    data = PHY_SOFTRESET;

    /* Reset the phy */
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_BCR, data);

    /* wait till the reset bit is auto cleared */
    while(data & PHY_SOFTRESET)
    {
        /* Read the reset */
        if(MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_BCR, &data) != TRUE)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/**
 * \brief   Configures the PHY for a given speed and duplex mode.
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 * \param   speed         Speed to be enabled
 * \param   duplexMode    Duplex Mode
 *
 * \return  status after configuring \n
 *          TRUE if configuration successful
 *          FALSE if configuration failed
 *
 **/
unsigned int PhyConfigure(unsigned int mdioBaseAddr, unsigned int phyAddr,
                          unsigned short speed, unsigned short duplexMode)
{
    /* Set the configurations */
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_BCR, (speed | duplexMode));

    return TRUE;
}

/**
 * \brief   This function ask the phy device to start auto negotiation.
 *          
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 * \param   advVal        Autonegotiation advertisement value
 * \param   gigAdvVal     Gigabit capability advertisement value
 *          advVal can take the following any OR combination of the values \n
 *               PHY_100BTX - 100BaseTX \n
 *               PHY_100BTX_FD - Full duplex capabilty for 100BaseTX \n
 *               PHY_10BT - 10BaseT \n
 *               PHY_10BT_FD - Full duplex capability for 10BaseT \n
 *          gigAdvVal can take one of the following values \n
 *               PHY_NO_1000BT - No 1000Base-T capability\n
 *               PHY_1000BT_FD - Full duplex capabilty for 1000 Base-T \n
 *               PHY_1000BT_HD - Half duplex capabilty for 1000 Base-T \n
 *               FALSE - It is passed as an argument if phy dosen't support
 *                       Giga bit capability 
 *
 * \return  status after autonegotiation \n
 *          TRUE if autonegotiation started
 *          FALSE if autonegotiation not started
 *
 **/
unsigned int PhyAutoNegotiate(unsigned int mdioBaseAddr, unsigned int phyAddr,
                              unsigned short *advPtr, unsigned short *gigAdvPtr)
{
    volatile unsigned short data;
    volatile unsigned short anar;

    if(MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_BCR, &data) != TRUE )
    {
        return FALSE;
    }
   
    data |= PHY_AUTONEG_ENABLE;

    if (*gigAdvPtr != 0)
    {
        /* Set phy for gigabit speed */
        data &= PHY_SPEED_MASK;
        data |= PHY_SPEED_1000MBPS;
    }
   
    /* Enable Auto Negotiation */
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_BCR, data);

    if(MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_BCR, &data) != TRUE )
    {
        return FALSE;
    }

    /* Write Auto Negotiation capabilities */
    MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_AUTONEG_ADV, &anar);
    anar &= ~PHY_ADV_VAL_MASK;
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_AUTONEG_ADV, (anar |(*advPtr)));

    /* Write Auto Negotiation Gigabyte capabilities */
    anar = 0;
    MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_1000BT_CONTROL, &anar);
    anar &= ~PHY_GIG_ADV_VAL_MASK;
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_1000BT_CONTROL,
                    (anar |(*gigAdvPtr)));

    data |= PHY_AUTONEG_RESTART;

    /* Start Auto Negotiation */
    MDIOPhyRegWrite(mdioBaseAddr, phyAddr, PHY_BCR, data);

    return TRUE;
}

/**
 * \brief   Returns the status of Auto Negotiation completion.
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 *
 * \return  Auto negotiation completion status \n
 *          TRUE if auto negotiation is completed
 *          FALSE if auto negotiation is not completed
 **/
unsigned int PhyAutoNegStatusGet(unsigned int mdioBaseAddr, unsigned int phyAddr)
{
    volatile unsigned short data;

    MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_BSR, &data);

    /* Auto negotiation completion status */
    if(PHY_AUTONEG_COMPLETE == (data & (PHY_AUTONEG_STATUS)))
    {
        return TRUE;
    }
  
    return FALSE;
}

/**
 * \brief   Reads the Link Partner Ability register of the PHY.
 *
 * \param   mdioBaseAddr    Base Address of the MDIO Module Registers.
 * \param   phyAddr         PHY Adress.
 * \param   ptnerAblty      Pointer to which partner ability will be written.
 * \param   gbpsPtnerAblty  Pointer to which Giga bit capability will be written.
 *
 *          gbpsPtnerAblty can take following Macros.\n
 *
 *          TRUE  - It is passed as argument if phy supports Giga bit capability.\n
 *          FALSE - It is passed as argument if phy dosen't supports Giga bit
 *                  capability.\n
 *
 * \return  status after reading \n
 *          TRUE if reading successful
 *          FALSE if reading failed
 **/
unsigned int PhyPartnerAbilityGet(unsigned int mdioBaseAddr, 
                                  unsigned int phyAddr,
                                  unsigned short *ptnerAblty,
                                  unsigned short *gbpsPtnerAblty)
{
    unsigned int status;

    status = MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_LINK_PARTNER_ABLTY,
                           ptnerAblty);

    if (*gbpsPtnerAblty != 0)
    {
        status = status | MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_1000BT_STATUS,
                                         gbpsPtnerAblty);
    }

    return status;
}

/**
 * \brief   Reads the link status of the PHY.
 *
 * \param   mdioBaseAddr  Base Address of the MDIO Module Registers.
 * \param   phyAddr       PHY Adress.
 * \param   retries       The number of retries before indicating down status
 *
 * \return  link status after reading \n
 *          TRUE if link is up
 *          FALSE if link is down \n
 *
 * \note    This reads both the basic status register of the PHY and the
 *          link register of MDIO for double check
 **/
unsigned int PhyLinkStatusGet(unsigned int mdioBaseAddr,
                              unsigned int phyAddr,
                              volatile unsigned int retries)
{
    volatile unsigned short linkStatus;
 
    retries++;   
    while (retries)
    {
        /* First read the BSR of the PHY */
        MDIOPhyRegRead(mdioBaseAddr, phyAddr, PHY_BSR, &linkStatus);

        if(linkStatus & PHY_LINK_STATUS)
        {
            return TRUE;
        }
   
        retries--;
    }

    return FALSE;
}

/**************************** End Of File ***********************************/
