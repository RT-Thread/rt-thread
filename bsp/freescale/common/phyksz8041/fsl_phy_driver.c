/*
* Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "fsl_phy_driver.h"


/*******************************************************************************
 * Variables
 ******************************************************************************/
uint16_t oldPhyStatus, newPhyStatus;
/*! @brief Array for ENET module register base address. */
extern ENET_Type * const g_enetBase[];

/*******************************************************************************
 * Code
 ******************************************************************************/
 /*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_Write
 * Return Value: The execution status.
 * Description: PHY Write function.
 * This interface write data over the SMI to the specified PHY register.   
 * This function is called by all PHY interfaces.
 *END*********************************************************************/
enet_status_t PHY_DRV_Write(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
    uint32_t counter;
    ENET_Type * base = g_enetBase[instance];
    uint64_t mask = 0;
    enet_cur_status_t curStatus;
    mask |= ENET_GET_SMI_CONFIG_MASK;
    ENET_HAL_GetStatus(base, mask, &curStatus);
    /* Check if the mii is enabled*/
    if (!(curStatus.statusFlags & ENET_SMI_CONFIG_FLAG))
    {
        return kStatus_ENET_SMIUninitialized;
    }

    /* Clear the SMI interrupt event*/
    ENET_HAL_ClearIntStatusFlag(base, kEnetMiiInterrupt);

    /* Set write command*/
    ENET_HAL_SetSMIWrite(base, phyAddr, phyReg, kEnetWriteValidFrame, data);

    /* Wait for MII complete*/
    for(counter = kEnetMaxTimeout; counter > 0; counter --)
    {
        if(!ENET_HAL_GetIntStatusFlag(base, kEnetMiiInterrupt))
        {
            break;
        }
    }

    /* Check for timeout*/
    if (!counter)
    {
        return kStatus_ENET_SMIVisitTimeout;
    }

    /* Clear MII intrrupt event*/
    ENET_HAL_ClearIntStatusFlag(base, kEnetMiiInterrupt);
	
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_Read
 * Return Value: The execution status.
 * Description: Read function.
 * This interface read data over the SMI from the specified PHY register,
 * This function is called by all PHY interfaces.
 *END*********************************************************************/
enet_status_t PHY_DRV_Read(uint32_t instance, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
    ENET_Type * base;
    uint32_t  counter = kEnetMaxTimeout;    
    uint64_t mask = 0;
    enet_cur_status_t curStatus;
	
    /* Check the input parameters*/
    if (!dataPtr)
    {
        return kStatus_ENET_InvalidInput;
    }

    base = g_enetBase[instance];
    mask |= ENET_GET_SMI_CONFIG_MASK;
    ENET_HAL_GetStatus(base, mask, &curStatus);
    /* Check if the mii is enabled*/
    if (!(curStatus.statusFlags & ENET_SMI_CONFIG_FLAG))
    {
        return kStatus_ENET_SMIUninitialized;
    }

    /* Clear the MII interrupt event*/
    ENET_HAL_ClearIntStatusFlag(base, kEnetMiiInterrupt);

    /* Read command operation*/
    ENET_HAL_SetSMIRead(base, phyAddr, phyReg, kEnetReadValidFrame);

    /* Wait for MII complete*/
    for(counter = kEnetMaxTimeout; counter > 0; counter --)
    {
        if(ENET_HAL_GetIntStatusFlag(base, kEnetMiiInterrupt))
        {
            break;
        }
    }

    /* Check for timeout*/
    if (!counter)
    {
        return kStatus_ENET_SMIVisitTimeout;
    }

    /* Get data from mii register*/
    *dataPtr = ENET_HAL_GetSMIData(base);

    /* Clear MII interrupt event*/
    ENET_HAL_ClearIntStatusFlag(base, kEnetMiiInterrupt);
	
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_Init
 * Return Value: The execution status.
 * Description: Initialize Phy.
 * This interface provides initialize functions for PHY, This is called by enet  
 * initialize function. PHY is usually deault auto-negotiation. so there is no 
 * need to do the intialize about this. we just need to check the loop mode.
 *END*********************************************************************/
enet_status_t PHY_DRV_Init(uint32_t instance, uint32_t phyAddr, bool isLoopEnabled)
{
    uint32_t data,dataStatus;
    uint32_t counter = kEnetMaxTimeout;
    enet_status_t result;

    /* Reset Phy*/
    result = PHY_DRV_Write(instance, phyAddr, kEnetPhyCR, kEnetPhyReset);
    if(result != kStatus_ENET_Success)
    {
        return result;
    }
    else
    {
        do{
            counter --;
            /* Wait for complete*/
            result = PHY_DRV_Read(instance, phyAddr, kEnetPhyCR, &data);
            if(result != kStatus_ENET_Success)
            {
                return result;
            }
        }while((data & kEnetPhyReset) && (counter > 0));
        /* Check for timeout */
        if (!counter)
        {
            return kStatus_ENET_SMIVisitTimeout;
        }
    }
   
    result = PHY_DRV_Read(instance, phyAddr, kEnetPhySR, &dataStatus);
    if(result != kStatus_ENET_Success)
    {
        return result;
    }

    if (((dataStatus & kEnetPhyAutoNegAble) != 0) && ((dataStatus & kEnetPhyAutoNegComplete) == 0))		
    {
        /* Set Autonegotiation*/
       if(PHY_DRV_Write(instance, phyAddr, kEnetPhyCR, data | kEnetPhyAutoNeg)== kStatus_ENET_Success)
        for (counter = 0; counter < kEnetMaxTimeout; counter++)
        {
            if (PHY_DRV_Read(instance, phyAddr, kEnetPhySR, &dataStatus)== kStatus_ENET_Success)
            {
                if ((dataStatus & kEnetPhyAutoNegComplete) != 0)
                {
                    break;
                }
            }
        }
    }

    if (isLoopEnabled)
    {
        /* First read the current status in control register*/ 
        if (PHY_DRV_Read(instance, phyAddr, kEnetPhyCR, &data) == kStatus_ENET_Success)
        {
            result = PHY_DRV_Write(instance, phyAddr,kEnetPhyCR,(data|kEnetPhyLoop));
            return result;
        }
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_Autodiscover
 * Return Value: The execution status.
 * Description: Phy address auto discover.
 * This function provides a interface to get phy address using phy address auto 
 * discovering, this interface is used when the phy address is unknown.
 *END*********************************************************************/
enet_status_t PHY_DRV_Autodiscover(uint32_t instance, uint32_t *phyAddr)
{
    uint32_t addrIdx,data;
    enet_status_t result = kStatus_ENET_PHYAutoDiscoverFail;

    /* Check input param*/
    if(!phyAddr)
    {
        return kStatus_ENET_InvalidInput;
    }
    
    for (addrIdx = 0; addrIdx <= ENET_PHY_MAX_ADDRESS; addrIdx++)
    {
        result = PHY_DRV_Read(instance, addrIdx, kEnetPhyId1, &data);
        if ((result == kStatus_ENET_Success) && (data != 0) && (data != 0xffff) )
        {
            *phyAddr = addrIdx;
            return kStatus_ENET_Success;
        }
    }
    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_GetLinkSpeed
 * Return Value: The execution status.
 * Description: Get phy link speed.
 * This function provides a interface to get link speed.
 *END*********************************************************************/
enet_status_t PHY_DRV_GetLinkSpeed(uint32_t instance, uint32_t phyAddr, enet_phy_speed_t *speed)
{
    enet_status_t result = kStatus_ENET_Success;
    uint32_t data;

    /* Check input parameters*/
    if (!speed)
    {
        return kStatus_ENET_InvalidInput;
    }

    result = PHY_DRV_Read(instance, phyAddr, kEnetPhyCt2,&data);
    if (result == kStatus_ENET_Success)
    {
        data &= kEnetPhySpeedDulpexMask; 
        if ((kEnetPhy100HalfDuplex == data) || (kEnetPhy100FullDuplex == data))
        {
            *speed = kEnetSpeed100M;
        }
        else
        {
            *speed = kEnetSpeed10M;
        }
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_GetLinkStatus
 * Return Value: The execution status.
 * Description: Get phy link status.
 * This function provides a interface to get link status to see if the link 
 * status is on or off.
 *END*********************************************************************/
 enet_status_t PHY_DRV_GetLinkStatus(uint32_t instance, uint32_t phyAddr, bool *status)
{
    enet_status_t result = kStatus_ENET_Success;
    uint32_t data;

    /* Check input parameters*/
    if (!status)
    {
        return kStatus_ENET_InvalidInput;
    }

    result = PHY_DRV_Read(instance, phyAddr, kEnetPhyCR, &data);
    if ((result == kStatus_ENET_Success) && (!(data & kEnetPhyReset)))
    {
        data = 0;
        result = PHY_DRV_Read(instance, phyAddr, kEnetPhySR, &data);
        if (result == kStatus_ENET_Success)
        {
            if (!(kEnetPhyLinkStatus & data))
            {
                *status = false;
            }
            else
            {
                *status = true;
            }
        }
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_GetLinkDuplex
 * Return Value: The execution status.
 * Description: Get phy link duplex.
 * This function provides a interface to get link duplex to see if the link 
 * duplex is full or half.
 *END*********************************************************************/
enet_status_t PHY_DRV_GetLinkDuplex(uint32_t instance, uint32_t phyAddr, enet_phy_duplex_t *status)
{
    enet_status_t result = kStatus_ENET_Success;
    uint32_t data;

    /* Check input parameters*/
    if (!status)
    {
        return kStatus_ENET_InvalidInput;
    }

    result = PHY_DRV_Read(instance, phyAddr,kEnetPhyCt2,&data);
    if (result == kStatus_ENET_Success)
    {
        data &= kEnetPhySpeedDulpexMask; 
        if ((kEnetPhy10FullDuplex == data) || (kEnetPhy100FullDuplex == data))
        {
            *status = kEnetFullDuplex;
        }
        else
        {
            *status = kEnetHalfDuplex;
        }
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: PHY_DRV_UpdateSpeed
 * Return Value: The execution status.
 * Description: Poll Phy speed change.
 * This function provides a interface to moniter the change of the link speed.
 *END*********************************************************************/
bool PHY_DRV_UpdateSpeed(uint32_t instance, uint32_t phyAddr, enet_phy_speed_t *status)
{
    bool link;

    if(PHY_DRV_GetLinkSpeed(instance, phyAddr, status)== kStatus_ENET_Success)
    {
        if(status)
        {
            newPhyStatus |= kPhyLinkSpeed;
        }
        else
        {
            newPhyStatus &= ~kPhyLinkSpeed;
        }
    }
    if(PHY_DRV_GetLinkStatus(instance, phyAddr, &link)== kStatus_ENET_Success)
    {
        if(link)
        {
            newPhyStatus |= kPhyLinkon;
        }
        else
        {
            newPhyStatus &= ~kPhyLinkon;
        }
    }

    if(newPhyStatus != oldPhyStatus)
    {
        oldPhyStatus = newPhyStatus;
    
        if(newPhyStatus & kPhyLinkon)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    return false;
}
/*******************************************************************************
 * EOF
 ******************************************************************************/

