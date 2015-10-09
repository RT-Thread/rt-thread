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
#include <assert.h>
#include <string.h> 
#include "fsl_enet_driver.h"
#include "fsl_enet_hal.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_ENET_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Define global value for ISR input parameter*/
enet_dev_if_t *enetIfHandle[ENET_INSTANCE_COUNT];

#if FSL_FEATURE_ENET_SUPPORT_PTP
/*! @brief Define ptp mastertimer information*/
enet_mac_ptp_master_time_t g_ptpMasterTime;
/*! @brief Define clk frequency for 1588 timer*/
uint32_t g_ptpClkFrq;
#if FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT_ERRATA_2579
#define ENET_TIMER_CHANNEL_NUM      kEnetTimerChannel3
#endif
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#if FSL_FEATURE_ENET_SUPPORT_PTP
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_1588Init
 * Return Value: The execution status.
 * Description:Initialize the ENET private ptp(Precision Time Synchronization Protocol)
 * data structure.
 *
 *END*********************************************************************/
enet_status_t ENET_DRV_1588Init(enet_dev_if_t *enetIfPtr, enet_mac_ptp_ts_data_t *ptpTsRxDataPtr,uint32_t rxBuffNum, 
                        enet_mac_ptp_ts_data_t *ptpTsTxDataPtr, uint32_t txBuffNum, bool isSlaveEnabled)
{
    enet_private_ptp_buffer_t *privatePtpPtr;
    
    /* Check the input parameters */
    if ((!enetIfPtr) || (!ptpTsRxDataPtr) || (!ptpTsTxDataPtr))
    {
        return kStatus_ENET_InvalidInput;
    }

    privatePtpPtr = &enetIfPtr->privatePtp;
    enetIfPtr->privatePtp.firstflag = true;

    /* Initialize ptp receive and transmit ring buffers*/
    privatePtpPtr->rxTimeStamp.ptpTsDataPtr = ptpTsRxDataPtr;
    privatePtpPtr->rxTimeStamp.size = rxBuffNum;
    privatePtpPtr->rxTimeStamp.front = 0;
    privatePtpPtr->rxTimeStamp.end = 0;
    privatePtpPtr->txTimeStamp.ptpTsDataPtr = ptpTsTxDataPtr;
    privatePtpPtr->txTimeStamp.size = txBuffNum;
    privatePtpPtr->txTimeStamp.front = 0;
    privatePtpPtr->txTimeStamp.end = 0;

    /* Start 1588 timer and enable timer interrupt*/
    ENET_DRV_Start1588Timer(enetIfPtr->deviceNumber, isSlaveEnabled);
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_1588Deinit
 * Return Value: The execution status.
 * Description:Initialize the ENET private ptp(Precision Time Synchronization Protocol)
 * data structure.
 *
 *END*********************************************************************/
enet_status_t ENET_DRV_1588Deinit(enet_dev_if_t *enetIfPtr)
{
    /* Check the input parameters */
    if (!enetIfPtr)
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Initialize ptp receive and transmit ring buffers*/
    enetIfPtr->privatePtp.rxTimeStamp.ptpTsDataPtr = NULL;
    enetIfPtr->privatePtp.rxTimeStamp.size = 0;
    enetIfPtr->privatePtp.rxTimeStamp.front = 0;
    enetIfPtr->privatePtp.rxTimeStamp.end = 0;
    enetIfPtr->privatePtp.txTimeStamp.ptpTsDataPtr = NULL;
    enetIfPtr->privatePtp.txTimeStamp.size = 0;
    enetIfPtr->privatePtp.txTimeStamp.front = 0;
    enetIfPtr->privatePtp.txTimeStamp.end = 0;

    ENET_DRV_Stop1588Timer(enetIfPtr->deviceNumber);

    return kStatus_ENET_Success;
}


/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Start1588Timer
 * Return Value: The execution status.
 * Description: Start the ENET ptp(Precision Time Synchronization Protocol)
 * timer. After this, the timer is ready for 1588 synchronization.  
 *
 *END*********************************************************************/
enet_status_t ENET_DRV_Start1588Timer(uint32_t instance, bool isSlaveEnabled)
{
    uint32_t clockFreq = 0;
    ENET_Type * base;
    enet_config_ptp_timer_t ptpCfg;

    /* Check if this is the master ptp timer*/
    if (!isSlaveEnabled)
    {
        g_ptpMasterTime.masterPtpInstance = instance;
    }

    base = g_enetBase[instance]; 
    
    /* Initialize ptp timer */
    clockFreq = CLOCK_SYS_GetEnetTimeStampFreq(instance);
    if (!clockFreq)
    {
        return kStatus_ENET_GetClockFreqFail;
    }
    ptpCfg.isSlaveEnabled = isSlaveEnabled;
    ptpCfg.period = kEnetPtpAtperValue;
    ptpCfg.clockIncease = ptpCfg.period/clockFreq;
#if FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT_ERRATA_2579
    ptpCfg.channel = ENET_TIMER_CHANNEL_NUM;
#endif
    ENET_HAL_Start1588Timer(base, &ptpCfg);
    
    /* Set the gloabl 1588 timer frequency*/
    g_ptpClkFrq = clockFreq;
        
    /* Enable master ptp timer interrupt */
    if (!ptpCfg.isSlaveEnabled)
    {
        ENET_HAL_SetIntMode(base, kEnetTsTimerInterrupt, true);
        INT_SYS_EnableIRQ(g_enetTsIrqId[instance]);
    }

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Stop1588Timer
 * Return Value: None.
 * Description:Stop ENET ptp timer. 
 *
 *END*********************************************************************/
void ENET_DRV_Stop1588Timer(uint32_t instance)
{
    ENET_Type * base; 

    base = g_enetBase[instance]; 
    /* Disable ptp timer*/
    ENET_HAL_Stop1588Timer(base);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Get1588timer
 * Return Value: None.
 * Description: Get current ENET ptp time. 
 * This interface is use by 1588 stack to get the current value from the ptp timer
 * through ioctl interface.
 *END*********************************************************************/
enet_status_t ENET_DRV_Get1588timer(enet_mac_ptp_time_t *ptpTimerPtr)
{
    ENET_Type * base;

    /* Check input parameters*/
    if (!ptpTimerPtr)
    {
        return kStatus_ENET_InvalidInput;
    }
    base = g_enetBase[g_ptpMasterTime.masterPtpInstance]; 

    /* Interrupt disable*/
    INT_SYS_DisableIRQGlobal();

    /* Get the current value of the master time*/
    ptpTimerPtr->second = g_ptpMasterTime.second;
    ptpTimerPtr->nanosecond = ENET_HAL_Get1588TimerCurrentTime(base);

    /* Enable interrupt*/
    INT_SYS_EnableIRQGlobal();

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Set1588timer
 * Return Value: None.
 * Description: Set ENET ptp time. 
 * This interface is use by 1588 stack to set the current ptp timer
 * through ioctl interface.
 *END*********************************************************************/
enet_status_t ENET_DRV_Set1588timer(enet_mac_ptp_time_t *ptpTimerPtr)
{
    ENET_Type * base;
    /* Check input parameters*/
    if (!ptpTimerPtr)
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Disable interrupt*/
    INT_SYS_DisableIRQGlobal();
    /* Set ptp timer*/
    g_ptpMasterTime.second = ptpTimerPtr->second;
    base = g_enetBase[g_ptpMasterTime.masterPtpInstance]; 
    ENET_HAL_Set1588TimerNewTime(base, ptpTimerPtr->nanosecond);

    /* Enable interrupt*/
    INT_SYS_EnableIRQGlobal();
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Adjust1588timer
 * Return Value: The execution status.
 * Description: Adjust ENET ptp timer. 
 * This interface is mainly the adjust algorithm for ptp timer synchronize.
 * this function is used to adjust ptp timer to synchronize with master timer.
 *END*********************************************************************/
enet_status_t ENET_DRV_Adjust1588timer(uint32_t instance, int32_t drift)
{
    uint32_t clockIncrease,adjIncrease,corrPeriod = 0,corrIncrease = 0,count = 0;
    uint32_t gapMax = 0xFFFFFFFF,gapTemp,adjPeriod = 1;
    ENET_Type * base;
    base = g_enetBase[instance]; 

    /* Calculate clock period of the ptp timer*/
    clockIncrease = kEnetPtpAtperValue / g_ptpClkFrq ;

    if (drift != 0)
    {
        if (abs(drift) >= g_ptpClkFrq)
        {
            /* Drift is greater than the 1588 clock frequency the correction should be done every tick of the timer*/   
            corrPeriod = 1;	
            corrIncrease = (uint32_t)(abs(drift)/g_ptpClkFrq);
        }
        else
        {
            /* Drift is smaller than the 1588 clock frequency*/
            if (abs(drift) > (g_ptpClkFrq / clockIncrease))
            {
                adjIncrease = clockIncrease / kEnetBaseIncreaseUnit;
            }
            else if (abs(drift) > (g_ptpClkFrq / (2*kEnetBaseIncreaseUnit*clockIncrease)))
            {
                adjIncrease = clockIncrease / (2*kEnetBaseIncreaseUnit);
                adjPeriod =  kEnetBaseIncreaseUnit;
            }
            else
            {
                adjIncrease = clockIncrease / (2*kEnetBaseIncreaseUnit);
                adjPeriod = 2*kEnetBaseIncreaseUnit;
            }
            for(count = 1; count < adjIncrease; count++)
            {
                gapTemp = (g_ptpClkFrq * adjPeriod * count) % abs(drift);
                if (!gapTemp)
                {
                    corrIncrease = count;
                    corrPeriod = (uint32_t)((g_ptpClkFrq * adjPeriod * count) / abs(drift));
                    break;
                }
                else if (gapTemp < gapMax)
                { 
                    corrIncrease = count;
                    corrPeriod = (uint32_t)((g_ptpClkFrq * adjPeriod * count) / abs(drift));
                    gapMax = gapTemp;
                }
            }
        }
        /* Calculate the clock correction increase value*/
        if (drift < 0)
        {
            corrIncrease = clockIncrease - corrIncrease;
        }
        else
        {
            corrIncrease = clockIncrease + corrIncrease;
        }
        /* Adjust the ptp timer*/	
        ENET_HAL_Adjust1588Timer(base, corrPeriod, corrIncrease);
    }
    else
    {
        /* Adjust the ptp timer*/
        ENET_HAL_Adjust1588Timer(base, 0, clockIncrease);
    }
   
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_ptp_store_tx_timestamp
 * Return Value: The execution status.
 * Description: Store the transmit ptp timestamp. 
 * This interface is to store transmit ptp timestamp and is called by transmit function.
 *END*********************************************************************/
enet_status_t ENET_DRV_GetTxTs(enet_private_ptp_buffer_t *ptpBuffer, volatile enet_bd_struct_t *firstBdPtr, volatile enet_bd_struct_t *lastBdPtr)
{
    bool isPtpMsg,ptpTimerWrap;
    enet_mac_ptp_ts_data_t ptpTsData;
    enet_mac_ptp_time_t ptpTimerPtr;
    uint8_t * bdBufferPtr;
    enet_status_t result = kStatus_ENET_Success;
    ENET_Type * base;
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    
    /* Check input parameter*/
    if (!ptpBuffer)
    {
        return kStatus_ENET_InvalidInput;
    }
    /* Parse the message packet to check if there is a ptp message*/	
    bdBufferPtr = ENET_HAL_GetBuffDescripData(firstBdPtr);
    result = ENET_DRV_Parse1588Packet(bdBufferPtr, &ptpTsData, &isPtpMsg, false);
    if (result != kStatus_ENET_Success)
    {
        return result;
    }

    /* Store transmit timestamp of the ptp message*/
    if (isPtpMsg)
    {
        base = g_enetBase[g_ptpMasterTime.masterPtpInstance];
        /* Get transmit timestamp nanosecond*/
        mask |= ENET_BD_TIMESTAMP_MASK;
        ENET_HAL_GetBufDescripAttr(lastBdPtr, mask, &bdAttr);
        ptpTsData.timeStamp.nanosecond = bdAttr.bdTimestamp;

        /* Get current ptp timer nanosecond value*/
        ENET_DRV_Get1588timer(&ptpTimerPtr);
        INT_SYS_DisableIRQGlobal();
        
        /* Get ptp timer wrap event */
        ptpTimerWrap = ENET_HAL_GetIntStatusFlag(base, kEnetTsTimerInterrupt);

        /* Get transmit timestamp second */
        if ((ptpTimerPtr.nanosecond > ptpTsData.timeStamp.nanosecond) || 
            ((ptpTimerPtr.nanosecond < ptpTsData.timeStamp.nanosecond) && ptpTimerWrap))
        {
            ptpTsData.timeStamp.second = g_ptpMasterTime.second;
        }
        else 
        {
            ptpTsData.timeStamp.second = g_ptpMasterTime.second - 1;
        }
     
        INT_SYS_EnableIRQGlobal();

        /* Add the new timestamp data into the ptp ring buffer*/
        result = ENET_DRV_Update1588TsBuff(&(ptpBuffer->txTimeStamp), &ptpTsData);
    }

    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_GetRxTs
 * Return Value: The execution status.
 * Description: Store the receive ptp packet timestamp. 
 * This interface is to store receive ptp packet timestamp and is called by receive function.
 *END*********************************************************************/
enet_status_t ENET_DRV_GetRxTs(enet_private_ptp_buffer_t *ptpBuffer, uint8_t *packet, volatile enet_bd_struct_t *bdPtr)
{
    enet_mac_ptp_ts_data_t ptpTsData;
    enet_mac_ptp_time_t ptpTimerPtr;
    bool  isPtpMsg = false, ptpTimerWrap;
    enet_status_t result;
    ENET_Type * base;
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    
    /* Check input parameter*/
    if ((!ptpBuffer) || (!packet) || (!bdPtr))
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Check if the message is a ptp message */
    result = ENET_DRV_Parse1588Packet(packet, &ptpTsData, &isPtpMsg, false);
    if (result != kStatus_ENET_Success)
    {
        return result;
    }

    /* Store the receive timestamp of the ptp message*/
    if (isPtpMsg)
    {
        base = g_enetBase[g_ptpMasterTime.masterPtpInstance];

        /* Get the timestamp from the bd buffer*/
        mask |= ENET_BD_TIMESTAMP_MASK;
        ENET_HAL_GetBufDescripAttr(bdPtr, mask, &bdAttr);
        ptpTsData.timeStamp.nanosecond = bdAttr.bdTimestamp;

        /* Get current ptp timer nanosecond value*/
        ENET_DRV_Get1588timer(&ptpTimerPtr);

        INT_SYS_DisableIRQGlobal();  
   
        /* Get ptp timer wrap event*/
        ptpTimerWrap = ENET_HAL_GetIntStatusFlag(base, kEnetTsTimerInterrupt);

        /* Get transmit timestamp second*/
        if ((ptpTimerPtr.nanosecond > ptpTsData.timeStamp.nanosecond) || 
            ((ptpTimerPtr.nanosecond < ptpTsData.timeStamp.nanosecond) && ptpTimerWrap))
        {
            ptpTsData.timeStamp.second = g_ptpMasterTime.second;
        }
        else 
        {
            ptpTsData.timeStamp.second = g_ptpMasterTime.second - 1;
        }	
        INT_SYS_EnableIRQGlobal();

        /* Add the new timestamp data into the ptp ring buffer*/
        result = ENET_DRV_Update1588TsBuff(&(ptpBuffer->rxTimeStamp), &ptpTsData);

    }
        
    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Parse1588Packet
 * Return Value: The execution status.
 * Description: Parse the message and store the ptp message information if 
 * it is a ptp message. this is called by the tx/rx store timestamp interface. 
 *
 *END*********************************************************************/
enet_status_t ENET_DRV_Parse1588Packet(uint8_t *packet, enet_mac_ptp_ts_data_t *ptpTsPtr, 
                         bool *isPtpMsg, bool isFastEnabled)
{   
    uint8_t *buffer = packet;
    uint16_t ptpType;

    /* Check input parameter*/
    if((!packet) || (!isPtpMsg) || ((!ptpTsPtr) && (!isFastEnabled)))
    {
        return kStatus_ENET_InvalidInput;
    }
    
    *isPtpMsg = false;

    /* Check for vlan frame*/
    if (*(uint16_t *)(buffer + kEnetPtpEtherL2PktTypeOffset) == ENET_HTONS(kEnetProtocol8021QVlan))
    {
        buffer += (sizeof(enet_8021vlan_header_t) - kEnetEthernetHeadLen);
    }

    ptpType = *(uint16_t *)(buffer + kEnetPtpEtherL2PktTypeOffset);
    switch(ENET_HTONS(ptpType))
    {
        case kEnetProtocoll2ptpv2:
            if (*(uint8_t *)(buffer + kEnetPtpEtherL2MsgTypeOffset) <= kEnetPtpEventMsgType)
            {
                /* Set the ptp message flag*/
                *isPtpMsg = true; 
                if(!isFastEnabled)
                {
                    /* It's a ptpv2 message and store the ptp header information*/
                    ptpTsPtr->version = (*(uint8_t *)(buffer + kEnetPtpEtherL2VersionOffset))&0x0F;
                    ptpTsPtr->messageType = (*(uint8_t *)(buffer + kEnetPtpEtherL2MsgTypeOffset))& 0x0F;
                    ptpTsPtr->sequenceId = ENET_HTONS(*(uint16_t *)(buffer + kEnetPtpEtherL2SequenceIdOffset));
                    memcpy((void *)&ptpTsPtr->sourcePortId[0],(void *)(buffer + kEnetPtpEtherL2ClockIdOffset),kEnetPtpSourcePortIdLen);
                }
            }
        break;

        case kEnetProtocolIpv4:
            if ((*(uint8_t *)(buffer + kEnetPtpIpVersionOffset) >> 4 ) == kEnetPacketIpv4Version)
            {
                if (((*(uint16_t *)(buffer + kEnetPtpIpv4UdpPortOffset)) == ENET_HTONS(kEnetPtpEventPort))&&
                (*(uint8_t *)(buffer + kEnetPtpIpv4UdpProtocolOffset) == kEnetPacketUdpVersion))
                {
                    /* Set the ptp message flag*/
                    *isPtpMsg = true;  
                    if(!isFastEnabled)
                    {
                        /* It's a IPV4 ptp message and store the ptp header information*/
                        ptpTsPtr->version = (*(uint8_t *)(buffer + kEnetPtpIpv4UdpVersionoffset))&0x0F;
                        ptpTsPtr->messageType = (*(uint8_t *)(buffer + kEnetPtpIpv4UdpMsgTypeOffset))& 0x0F;
                        ptpTsPtr->sequenceId = ENET_HTONS(*(uint16_t *)(buffer + kEnetPtpIpv4UdpSequenIdOffset));
                        memcpy(( void *)&ptpTsPtr->sourcePortId[0],( void *)(buffer + kEnetPtpIpv4UdpClockIdOffset),kEnetPtpSourcePortIdLen);
                    }
                }
            }        
        break;
        case kEnetProtocolIpv6:
            if ((*(uint8_t *)(buffer + kEnetPtpIpVersionOffset) >> 4 ) == kEnetPacketIpv6Version)
            {
                if (((*(uint16_t *)(buffer + kEnetPtpIpv6UdpPortOffset)) == ENET_HTONS(kEnetPtpEventPort))&&
                  (*(uint8_t *)(buffer + kEnetPtpIpv6UdpProtocolOffset) == kEnetPacketUdpVersion))
                {
                    /* Set the ptp message flag*/
                    *isPtpMsg = true;
                    if(!isFastEnabled)
                    {
                        /* It's a IPV6 ptp message and store the ptp header information*/
                        ptpTsPtr->version = (*(uint8_t *)(buffer + kEnetPtpIpv6UdpVersionOffset))&0x0F;
                        ptpTsPtr->messageType = (*(uint8_t *)(buffer + kEnetPtpIpv6UdpMsgTypeOffset))& 0x0F;
                        ptpTsPtr->sequenceId = ENET_HTONS(*(uint16_t *)(buffer + kEnetPtpIpv6UdpSequenceIdOffset));
                        memcpy(( void *)&ptpTsPtr->sourcePortId[0],( void *)(buffer + kEnetPtpIpv6UdpClockIdOffset),kEnetPtpSourcePortIdLen);
                    }  
                }
            }
        break;
        default:
        break;

    }

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_ptp_l2queue_init
 * Return Value: The execution status.
 * Description: Initialize dara buffer queue for ptp Ethernet layer2 packets.
 *END*********************************************************************/
enet_status_t ENET_DRV_1588l2queueInit(enet_dev_if_t *enetIfPtr, enet_mac_ptp_l2buffer_t *ptpL2BufferPtr,
                                       uint32_t ptpL2BuffNum)
{
    uint32_t index;
    enet_mac_ptp_l2buffer_queue_t *ptpL2queuePtr;
    /* Check input parameters*/
    if ((!enetIfPtr) || (!ptpL2BufferPtr))
    {
        return kStatus_ENET_InvalidInput;
    }

    ptpL2queuePtr = &enetIfPtr->privatePtp.layer2Queue;

    /* Initialize the queue*/
    ptpL2queuePtr->l2bufferPtr = ptpL2BufferPtr;
    ptpL2queuePtr->l2bufferNum = ptpL2BuffNum;
    ptpL2queuePtr->writeIdx = 0;
    ptpL2queuePtr->readIdx = 0;
    for (index = 0; index < ptpL2BuffNum; index++)
    {
        ptpL2queuePtr->l2bufferPtr[index].length = 0;
    }

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Service_l2packet
 * Return Value: The execution status.
 * Description: Add the ptp layer2 Ethernet packet to the queue.
 * This interface is the call back for Ethernet 1588 layer2 packets to 
 * add queue for ptp layer2 Ethernet packets. 
 *END*********************************************************************/
enet_status_t ENET_DRV_Service_l2packet(enet_dev_if_t * enetIfPtr, enet_mac_packet_buffer_t *packBuffer)
{
    enet_mac_ptp_l2buffer_queue_t * ptpQuePtr;
    uint16_t type, length = 0;
    enet_mac_packet_buffer_t *frame;
    /* Check input parameter*/
    if ((!enetIfPtr) || (!packBuffer))
    {
        return kStatus_ENET_InvalidInput;
    }
    ptpQuePtr = &enetIfPtr->privatePtp.layer2Queue;

    if(!ptpQuePtr->l2bufferPtr)
    {
        return kStatus_ENET_Layer2UnInitialized;
    }
    /* Check for protocol type*/
    type = ((enet_ethernet_header_t *)(packBuffer->data))->type;
    if(ENET_NTOHS(type) == kEnetProtocol8021QVlan)
    {
        type = ((enet_8021vlan_header_t *)(packBuffer->data))->type;
    }
    if(ENET_NTOHS(type) != kEnetProtocoll2ptpv2)
    {
        return kStatus_ENET_Layer2TypeError;
    }

    /* Check if the queue is full*/
    if (ptpQuePtr->l2bufferPtr[ptpQuePtr->writeIdx].length != 0 )
    {
        return kStatus_ENET_Layer2BufferFull;
    }

    frame = packBuffer;
    do
    {
        /* Store the packet*/
        memcpy((void *)(ptpQuePtr->l2bufferPtr[ptpQuePtr->writeIdx].packet + length), (void *)(frame->data), length);
        length += frame->length;
        frame = frame->next;
    }while(frame != NULL);
    ptpQuePtr->l2bufferPtr[ptpQuePtr->writeIdx].length = length;

    /* Increase the index to the next one*/
    ptpQuePtr->writeIdx = (ptpQuePtr->writeIdx + 1) % enetIfPtr->privatePtp.layer2Queue.l2bufferNum;

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_ptp_send_l2packet
 * Return Value: The execution status.
 * Description: Send the ptp layer2 Ethernet packet to the net.
 * This interface is used to send the ptp layer2 Ethernet packet and 
 * this interface is called by 1588 stack. 
 *END*********************************************************************/
enet_status_t ENET_DRV_Send_l2packet(enet_dev_if_t * enetIfPtr, enet_mac_ptp_l2_packet_t *paramPtr)
{
    uint32_t datalen, dataoffset = 0;
    uint8_t headlen;
    uint16_t vlanTag, bdNumUsed = 0;
    volatile enet_bd_struct_t *bdTemp;
    uint8_t *packet;
    /* Check input parameters*/
    if ((!enetIfPtr) || (!paramPtr))
    {
        return kStatus_ENET_InvalidInput;
    }
    
    bdTemp = enetIfPtr->bdContext.txBdCurPtr;
    packet = ENET_HAL_GetBuffDescripData(bdTemp);
    /* Add Ethernet MAC address*/
    memcpy(packet, &(paramPtr->hwAddr[0]), kEnetMacAddrLen);
    memcpy(packet + kEnetMacAddrLen, enetIfPtr->macAddr, kEnetMacAddrLen);
     
    if(!enetIfPtr->isVlanTagEnabled)
    {
         headlen = kEnetEthernetHeadLen;
        ((enet_ethernet_header_t *)packet)->type = ENET_HTONS(kEnetProtocoll2ptpv2);
    }
    else
    {
         headlen = kEnetEthernetVlanHeadLen;
         vlanTag = (uint16_t)((uint16_t)paramPtr->vlanPrior << 13) | paramPtr->vlanId;        
        ((enet_8021vlan_header_t *)packet)->tpidtag = ENET_HTONS(kEnetProtocol8021QVlan);
        ((enet_8021vlan_header_t *)packet)->othertag = ENET_HTONS(vlanTag);
        ((enet_8021vlan_header_t *)packet)->type = ENET_HTONS(kEnetProtocoll2ptpv2);
    }

    datalen = paramPtr->length + headlen;
    /* Check transmit packets*/
    if (datalen > enetIfPtr->maxFrameSize)
    {
#if ENET_ENABLE_DETAIL_STATS
       enetIfPtr->stats.statsTxLarge++;
       enetIfPtr->stats.statsTxDiscard++;
#endif
       return kStatus_ENET_Layer2OverLarge;
    }
    /* Send a whole frame with a signal buffer*/
    if(datalen <= enetIfPtr->bdContext.txBuffSizeAlign)
    { 
        bdNumUsed = 1;
        memcpy((void *)(packet + headlen), (void *)(paramPtr->ptpMsg), paramPtr->length);
        /* Send packet to the device*/
        return ENET_DRV_SendData(enetIfPtr, datalen, bdNumUsed);
    }
    /* Send a whole frame with multiple buffer descriptors*/
    while((datalen - bdNumUsed * enetIfPtr->bdContext.txBuffSizeAlign) > enetIfPtr->bdContext.txBuffSizeAlign)
    {
        if(bdNumUsed == 0)
        {
            memcpy((void *)(packet + headlen), (void *)(paramPtr->ptpMsg), enetIfPtr->bdContext.txBuffSizeAlign - headlen);
            dataoffset += enetIfPtr->bdContext.txBuffSizeAlign - headlen;
        }
        else
        {
            memcpy((void *)packet, (void *)(paramPtr->ptpMsg + dataoffset), enetIfPtr->bdContext.txBuffSizeAlign);  
            dataoffset += enetIfPtr->bdContext.txBuffSizeAlign;
        }
        /* Incremenet the buffer descriptor*/
        bdTemp = ENET_DRV_IncrTxBuffDescripIndex(enetIfPtr, bdTemp);
        packet = ENET_HAL_GetBuffDescripData(bdTemp);
        bdNumUsed ++;
    }
     memcpy((void *)packet, (void *)(paramPtr->ptpMsg + dataoffset), 
         datalen - bdNumUsed* enetIfPtr->bdContext.txBuffSizeAlign);     
     bdNumUsed ++;

    /* Send packet to the device*/
    return ENET_DRV_SendData(enetIfPtr, datalen, bdNumUsed);
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Receive_l2packet
 * Return Value: The execution status.
 * Description: Receive the ptp layer2 Ethernet packet to the net.
 * This interface is used to receive the ptp layer2 Ethernet packet and 
 * this interface is called by 1588 stack. 
 *END*********************************************************************/
enet_status_t ENET_DRV_Receive_l2packet(enet_dev_if_t * enetIfPtr, enet_mac_ptp_l2_packet_t *paramPtr)
{
    enet_private_ptp_buffer_t *ptpBuffer;
    enet_status_t result = kStatus_ENET_Success;
    uint16_t len;
   
    /* Check input parameters*/
    if ((!enetIfPtr) || (!paramPtr))
    {
        return kStatus_ENET_InvalidInput;
    }

    ptpBuffer = &(enetIfPtr->privatePtp);

    /* Check if the queue is full*/
    if (ptpBuffer->layer2Queue.readIdx == ptpBuffer->layer2Queue.writeIdx)
    {
        result = kStatus_ENET_Layer2BufferFull;
    }
    else
    {
        /* Data process*/
        len = ptpBuffer->layer2Queue.l2bufferPtr[ptpBuffer->layer2Queue.readIdx].length;
        memcpy((void *)paramPtr->ptpMsg, (void *)ptpBuffer->layer2Queue.l2bufferPtr[ptpBuffer->layer2Queue.readIdx].packet, len);

        /* Clear the queue parameter*/
        ptpBuffer->layer2Queue.l2bufferPtr[ptpBuffer->layer2Queue.readIdx].length = 0;
        ptpBuffer->layer2Queue.readIdx = 
          (ptpBuffer->layer2Queue.readIdx + 1)% enetIfPtr->privatePtp.layer2Queue.l2bufferNum;
    }

    memcpy(&(paramPtr->hwAddr[0]), enetIfPtr->macAddr, kEnetMacAddrLen);
    
    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Update1588TsBuff
 * Return Value: The execution status.
 * Description: Update the ring buffers. 
 *
 *END*********************************************************************/
enet_status_t ENET_DRV_Update1588TsBuff(enet_mac_ptp_ts_ring_t *ptpTsRingPtr, enet_mac_ptp_ts_data_t *data)
{
    /* Check input parameter*/
    if ((!ptpTsRingPtr) || (!data))
    {
        return kStatus_ENET_InvalidInput;
    }

    /* Return if the buffers ring is full*/
    if (ENET_DRV_Is1588TsBuffFull(ptpTsRingPtr))
    {
        return kStatus_ENET_PtpringBufferFull;
    }

    /* Copy the new data into the buffer*/
    memcpy((ptpTsRingPtr->ptpTsDataPtr + ptpTsRingPtr->end), data, 
        sizeof(enet_mac_ptp_ts_data_t));

    /* Increase the buffer pointer to the next empty one*/
    ptpTsRingPtr->end = ENET_DRV_Incr1588TsBuffRing(ptpTsRingPtr->size, ptpTsRingPtr->end, 1);

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Search1588TsBuff
 * Return Value: The execution status.
 * Description: Search the element in the ring buffers with the message 
 * sequence Id, Clock Id, ptp message version etc. 
 *
 *END*********************************************************************/
enet_status_t ENET_DRV_Search1588TsBuff(enet_mac_ptp_ts_ring_t *ptpTsRingPtr, enet_mac_ptp_ts_data_t *data)
{
    uint32_t index,size; 

    /* Check input parameter*/
    if ((!ptpTsRingPtr) || (!data))
    {
        return kStatus_ENET_InvalidInput;
    } 

    /* Check the ring buffer*/
    if (ptpTsRingPtr->front == ptpTsRingPtr->end)
    {
        return kStatus_ENET_PtpringBufferEmpty;
    }

    /* Search the element in the ring buffer*/
    index = ptpTsRingPtr->front;
    size = ptpTsRingPtr->size;
    while (index != ptpTsRingPtr->end)
    {
        if (((ptpTsRingPtr->ptpTsDataPtr + index)->sequenceId == data->sequenceId)&&
        (!memcmp((( void *)&(ptpTsRingPtr->ptpTsDataPtr + index)->sourcePortId[0]),
             ( void *)&data->sourcePortId[0],kEnetPtpSourcePortIdLen))&&
        ((ptpTsRingPtr->ptpTsDataPtr + index)->version == data->version)&&
        ((ptpTsRingPtr->ptpTsDataPtr + index)->messageType == data->messageType))
        {
            break;
        }

        /* Increase the ptp ring index*/
        index = ENET_DRV_Incr1588TsBuffRing(size, index, 1);
    }

    if (index == ptpTsRingPtr->end)
    {
        /* Check if buffers is full*/
        if (ENET_DRV_Is1588TsBuffFull(ptpTsRingPtr))
        {
            /* Drop one in the front*/
            ptpTsRingPtr->front = ENET_DRV_Incr1588TsBuffRing(size, ptpTsRingPtr->front, 1);
        }
        return kStatus_ENET_PtpringBufferFull;
    }

    /* Get the right timestamp of the required ptp message*/
    data->timeStamp.second = (ptpTsRingPtr->ptpTsDataPtr + index)->timeStamp.second;
    data->timeStamp.nanosecond = 
       (ptpTsRingPtr->ptpTsDataPtr + index)->timeStamp.nanosecond;

    /* Increase the index*/
    ptpTsRingPtr->front = ENET_DRV_Incr1588TsBuffRing(size, index, 1);

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Is1588TsBuffFull
 * Return Value: true if the ptp ring is full, false if not.
 * Description: Calculate the number of used ring buffers to see if the 
 * ring buffer queue is full. 
 *
 *END*********************************************************************/
bool ENET_DRV_Is1588TsBuffFull(enet_mac_ptp_ts_ring_t *ptpTsRingPtr)
{
    uint32_t availBuffer = 0;

    if (ptpTsRingPtr->end > ptpTsRingPtr->front)
    {
        availBuffer =  ptpTsRingPtr->end - ptpTsRingPtr->front;       
    }
    else if (ptpTsRingPtr->end < ptpTsRingPtr->front)
    {
        availBuffer = ptpTsRingPtr->size - (ptpTsRingPtr->front - ptpTsRingPtr->end);
    }

    if (availBuffer == (ptpTsRingPtr->size - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_1588Ioctl
 * Return Value: The execution status.
 * Description: The function provides the handler for 1588 stack to do ptp ioctl.
 * This interface provides ioctl for 1588 stack to get or set timestamp and do ptp  
 * version2 packets process. Additional user specified driver functionality may be 
 * added if necessary. This api will be changed to stack adapter.
 *END*********************************************************************/
enet_status_t ENET_DRV_1588Ioctl(enet_dev_if_t * enetIfPtr, uint32_t commandId, void *inOutPtr)
{
   
    enet_status_t result = kStatus_ENET_Success;
    enet_private_ptp_buffer_t *buffer;
    enet_mac_ptp_time_t ptpTimer;

    /*Check input parameters*/
    if (!enetIfPtr)
    {
        return kStatus_ENET_InvalidInput;
    }

    /*Check private PTP buffer*/
    buffer =  &enetIfPtr->privatePtp;
    if (!buffer)
    {
        return kStatus_ENET_InvalidInput;
    }

    switch (commandId)
    {
        case kEnetPtpGetRxTimestamp:
            /* Get receive timestamp*/
            result = ENET_DRV_Search1588TsBuff(&buffer->rxTimeStamp,
                (enet_mac_ptp_ts_data_t *)inOutPtr); 
            break;
        case kEnetPtpGetTxTimestamp:
            /* Get transmit timestamp*/
            result = ENET_DRV_Search1588TsBuff(&buffer->txTimeStamp,
                (enet_mac_ptp_ts_data_t *)inOutPtr);
            break;
        case kEnetPtpGetCurrentTime:
            /* Get current time*/
            result = ENET_DRV_Get1588timer(&ptpTimer);
            inOutPtr = (enet_mac_ptp_time_t *)&ptpTimer;
            break;
        case kEnetPtpSetCurrentTime:
            /* Set current time*/
            ptpTimer.second = ((enet_mac_ptp_time_t *)inOutPtr)->second;
            ptpTimer.nanosecond = ((enet_mac_ptp_time_t *)inOutPtr)->nanosecond;
            result = ENET_DRV_Set1588timer(&ptpTimer);
            break;
        case kEnetPtpFlushTimestamp:
            /* Reset receive and transmit buffer*/
            buffer->rxTimeStamp.end = 0;
            buffer->rxTimeStamp.front = 0;
            buffer->txTimeStamp.end = 0;
            buffer->txTimeStamp.front = 0;
            break;
        case kEnetPtpCorrectTime:
            /* Adjust time*/
            result = ENET_DRV_Adjust1588timer(enetIfPtr->deviceNumber, 
                ((enet_ptp_drift_t *)inOutPtr)->drift);
            break;
        case kEnetPtpSendEthernetPtpV2:
            /* Send layer2 packet*/
            result = ENET_DRV_Send_l2packet(enetIfPtr, (enet_mac_ptp_l2_packet_t*)inOutPtr);
            break;
        case kEnetPtpReceiveEthernetPtpV2:
            /* Receive layer2 packet*/
            result = ENET_DRV_Receive_l2packet(enetIfPtr, (enet_mac_ptp_l2_packet_t*)inOutPtr);
            break;
        default:
            result = kStatus_ENET_UnknownCommand;
            break;
    }
    return result;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_TsIRQHandler
 * Description: ENET timer ISR.
 * This interface is the ptp timer interrupt handler.
 *END*********************************************************************/
void ENET_DRV_TsIRQHandler(uint32_t instance)
{
    ENET_Type * base;
    enet_dev_if_t *enetIfPtr;

    enetIfPtr = enetIfHandle[instance];
    /*Check input parameter*/
    if (!enetIfPtr)
    {
        return;
    }
    base = g_enetBase[instance];
    /*Get interrupt status*/
    if (ENET_HAL_GetIntStatusFlag(base, kEnetTsTimerInterrupt))
    {
#if FSL_FEATURE_ENET_PTP_TIMER_CHANNEL_INTERRUPT_ERRATA_2579
      ENET_HAL_Rst1588TimerCmpValAndClrFlag(base, ENET_TIMER_CHANNEL_NUM, \
      (kEnetPtpAtperValue - kEnetPtpAtperValue/g_ptpClkFrq));
#else
        /*Clear interrupt events*/
        ENET_HAL_ClearIntStatusFlag(base, kEnetTsTimerInterrupt);
#endif
        /* Increase timer second counter*/
        g_ptpMasterTime.second++;
    }
}

#endif

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Init
 * Return Value: The execution status.
 * Description:Initialize the ENET device with the basic configuration
 * When ENET is used, this function need to be called by the NET initialize 
 * interface.
 *END*********************************************************************/
enet_status_t ENET_DRV_Init(enet_dev_if_t * enetIfPtr, const enet_user_config_t* userConfig)
{   
    enet_status_t result;
    uint32_t  frequency; 
    ENET_Type * base;
    uint32_t statusMask = 0;
    enet_cur_status_t curStatus;
    const enet_mac_config_t* macCfgPtr = userConfig->macCfgPtr;
    const enet_buff_config_t* buffCfgPtr = userConfig->buffCfgPtr;
    
    enet_bd_config bdConfig = {0};
    /* Check the input parameters*/
    if ((!enetIfPtr) || (!macCfgPtr) || (!buffCfgPtr))
    {
        return kStatus_ENET_InvalidInput;
    }
#if !ENET_RECEIVE_ALL_INTERRUPT
    /* POLL mode needs the extended buffer for data buffer update*/
    if((!buffCfgPtr->extRxBuffQue) || (!buffCfgPtr->extRxBuffNum))
    {
        return kStatus_ENET_InvalidInput;
    }
#endif
    base = g_enetBase[enetIfPtr->deviceNumber];

    /* Store the global ENET structure for ISR input parameter*/
    enetIfHandle[enetIfPtr->deviceNumber] = enetIfPtr;

    /* Turn on ENET module clock gate */
    CLOCK_SYS_EnableEnetClock( 0U);
    frequency = CLOCK_SYS_GetSystemClockFreq();
    bdConfig.rxBds = buffCfgPtr->rxBdPtrAlign;
    bdConfig.rxBuffer = buffCfgPtr->rxBufferAlign;
    bdConfig.rxBdNumber = buffCfgPtr->rxBdNumber;
    bdConfig.rxBuffSizeAlign = buffCfgPtr->rxBuffSizeAlign;
    bdConfig.txBds = buffCfgPtr->txBdPtrAlign;
    bdConfig.txBuffer = buffCfgPtr->txBufferAlign;
    bdConfig.txBdNumber = buffCfgPtr->txBdNumber;
    bdConfig.txBuffSizeAlign = buffCfgPtr->txBuffSizeAlign;
    /* Init ENET MAC to reset status*/
    ENET_HAL_Init(base);
    /* Configure MAC controller*/
    ENET_HAL_Config(base, macCfgPtr, frequency, &bdConfig);
    
#if FSL_FEATURE_ENET_SUPPORT_PTP
    result = ENET_DRV_1588Init(enetIfPtr, buffCfgPtr->ptpTsRxDataPtr, buffCfgPtr->ptpTsRxBuffNum,
            buffCfgPtr->ptpTsTxDataPtr, buffCfgPtr->ptpTsTxBuffNum, macCfgPtr->isSlaveMode);
    if(result != kStatus_ENET_Success)
    {
        return result;
    }
#endif
    /* Enable Ethernet rx and tx interrupt*/
    ENET_HAL_SetIntMode(base, kEnetTxByteInterrupt, true);
    ENET_HAL_SetIntMode(base, kEnetRxFrameInterrupt, true);

    INT_SYS_EnableIRQ(g_enetRxIrqId[enetIfPtr->deviceNumber]);
    INT_SYS_EnableIRQ(g_enetTxIrqId[enetIfPtr->deviceNumber]);
    
    /* Enable Ethernet module after all configuration except the bd active*/
    ENET_HAL_Enable(base);

    /* Active Receive buffer descriptor must be done after module enable*/
    ENET_HAL_SetRxBdActive(base);

    /* Store data in bdContext*/
    /* Set crc enable when tx crc forward disable and tx buffer descriptor crc enabled*/	
    if((!(macCfgPtr->macCtlConfigure & kEnetTxCrcFwdEnable))&&(macCfgPtr->macCtlConfigure & kEnetTxCrcBdEnable))
    {
        enetIfPtr->isTxCrcEnable = true;
    }
    else
    {
        enetIfPtr->isTxCrcEnable = false;
    }
    enetIfPtr->isRxCrcFwdEnable = (macCfgPtr->macCtlConfigure & kEnetRxCrcFwdEnable) ? 1U : 0U;
    memcpy(enetIfPtr->macAddr, macCfgPtr->macAddr, kEnetMacAddrLen);
    enetIfPtr->isVlanTagEnabled = (macCfgPtr->macCtlConfigure & kEnetVlanTagEnabled) ? 1U : 0U;
    enetIfPtr->bdContext.rxBdBasePtr = buffCfgPtr->rxBdPtrAlign;
    enetIfPtr->bdContext.rxBdCurPtr = buffCfgPtr->rxBdPtrAlign;
    enetIfPtr->bdContext.rxBdDirtyPtr = buffCfgPtr->rxBdPtrAlign;
    enetIfPtr->bdContext.txBdBasePtr = buffCfgPtr->txBdPtrAlign;
    enetIfPtr->bdContext.txBdCurPtr = buffCfgPtr->txBdPtrAlign;
    enetIfPtr->bdContext.txBdDirtyPtr = buffCfgPtr->txBdPtrAlign;
    enetIfPtr->bdContext.rxBuffSizeAlign = buffCfgPtr->rxBuffSizeAlign;
    enetIfPtr->bdContext.txBuffSizeAlign = buffCfgPtr->txBuffSizeAlign;
    statusMask |= ENET_GET_MAX_FRAME_LEN_MASK;
    ENET_HAL_GetStatus(base, statusMask, &curStatus);
    enetIfPtr->maxFrameSize = curStatus.maxFrameLen;
    /* Extend buffer for data buffer update*/
    if(buffCfgPtr->extRxBuffQue != NULL)
    {
        uint16_t counter = 0;
        enetIfPtr->bdContext.extRxBuffQue = NULL;
        for(counter = 0; counter < buffCfgPtr->extRxBuffNum; counter++)
        {
            enet_mac_enqueue_buffer((void **)&enetIfPtr->bdContext.extRxBuffQue, 
                (buffCfgPtr->extRxBuffQue + counter * buffCfgPtr->rxBuffSizeAlign));
        }   
        enetIfPtr->bdContext.extRxBuffNum = buffCfgPtr->extRxBuffNum;
    } 

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Deinit
 * Return Value: The execution status.
 * Description: Close ENET device.
 * This function is used to shut down ENET device.
 *END*********************************************************************/
enet_status_t ENET_DRV_Deinit(enet_dev_if_t * enetIfPtr)
{
    ENET_Type * base;

    /*Check input parameter*/
    if (!enetIfPtr)
    {
        return kStatus_ENET_InvalidInput;
    }
    base = g_enetBase[enetIfPtr->deviceNumber];
    /* Reset ENET module and disable ENET module*/
    ENET_HAL_Init(base);
#if FSL_FEATURE_ENET_SUPPORT_PTP
     ENET_DRV_1588Deinit(enetIfPtr);
#endif
    /* Disable irq*/
    INT_SYS_DisableIRQ(g_enetTxIrqId[enetIfPtr->deviceNumber]);
    INT_SYS_DisableIRQ(g_enetRxIrqId[enetIfPtr->deviceNumber]);
    INT_SYS_DisableIRQ(g_enetTsIrqId[enetIfPtr->deviceNumber]);
    INT_SYS_DisableIRQ(g_enetErrIrqId[enetIfPtr->deviceNumber]);

    /* Clear the global ENET structure*/
    enetIfHandle[enetIfPtr->deviceNumber] = NULL;
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_UpdateRxBuffDescrip
 * Return Value: The execution status.
 * Description: ENET receive buffer descriptor update.
 * This interface provides the receive buffer descriptor update and increase 
 * the current buffer descriptor pointer to the next one.
 *END*********************************************************************/
enet_status_t ENET_DRV_UpdateRxBuffDescrip(enet_dev_if_t * enetIfPtr, bool isBuffUpdate)
{
    ENET_Type * base;
    uint8_t *bufferTemp = NULL;
    base = g_enetBase[enetIfPtr->deviceNumber];

    while((enetIfPtr->bdContext.rxBdDirtyPtr != enetIfPtr->bdContext.rxBdCurPtr) ||
        (enetIfPtr->bdContext.isRxBdFull))
    {
        if(isBuffUpdate)
        {
            /* get the data buffer for update*/
            bufferTemp = (unsigned char*)enet_mac_dequeue_buffer((void **)&enetIfPtr->bdContext.extRxBuffQue); 
            if(!bufferTemp)
            {
                return kStatus_ENET_NoRxBufferLeft;
            }       
        }

        ENET_HAL_ClrRxBdAfterHandled(enetIfPtr->bdContext.rxBdDirtyPtr, bufferTemp, isBuffUpdate);

        /* Increase the buffer descriptor to the next one*/
        enetIfPtr->bdContext.rxBdDirtyPtr = 
            ENET_DRV_IncrRxBuffDescripIndex(enetIfPtr, enetIfPtr->bdContext.rxBdDirtyPtr);
        enetIfPtr->bdContext.isRxBdFull = false;

        /* Active the receive buffer descriptor*/
        ENET_HAL_SetRxBdActive(base);
    }

    return kStatus_ENET_Success;
}
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_CleanupTxBuffDescrip
 * Return Value: The execution status.
 * Description: First, store transmit frame error statistic and ptp timestamp 
 * of transmitted packets. Second, clean up the used transmit buffer descriptors.
 * If the ptp 1588 feature is open, this interface will do capture 1588 timestamp. 
 * It is called by transmit interrupt handler.
 *END*********************************************************************/
enet_status_t ENET_DRV_CleanupTxBuffDescrip(enet_dev_if_t * enetIfPtr)
{
    volatile enet_bd_struct_t *curBd;
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    mask |= (ENET_TX_BD_READY_FLAG_MASK | ENET_TX_BD_LAST_FLAG_MASK | ENET_TX_BD_TIMESTAMP_FLAG_MASK);
    
    while ((enetIfPtr->bdContext.txBdDirtyPtr != enetIfPtr->bdContext.txBdCurPtr)
           || (enetIfPtr->bdContext.isTxBdFull))
    {
        curBd = enetIfPtr->bdContext.txBdDirtyPtr;
        /* Get the control status data, If the bd has not been processed break out*/     
        ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
        if(bdAttr.flags & ENET_TX_BD_READY_FLAG)
        {
            break;
        }
#if FSL_FEATURE_ENET_SUPPORT_PTP
        if(enetIfPtr->privatePtp.firstflag)
        {
            enetIfPtr->privatePtp.firstBdPtr = curBd;
            enetIfPtr->privatePtp.firstflag = false;
        }
#endif
        /* If the transmit buffer descriptor is ready, store packet statistic*/
        if(bdAttr.flags & ENET_TX_BD_LAST_FLAG)
        {
#if ENET_ENABLE_DETAIL_STATS
             ENET_DRV_TxErrorStats(enetIfPtr,curBd);
#endif
#if FSL_FEATURE_ENET_SUPPORT_PTP
            /* Do ptp timestamp store*/
            if (bdAttr.flags & ENET_TX_BD_TIMESTAMP_FLAG)
            {
                ENET_DRV_GetTxTs(&enetIfPtr->privatePtp, enetIfPtr->privatePtp.firstBdPtr, curBd);
                enetIfPtr->privatePtp.firstflag = true;
            }
#endif
        }

        /* Clear the buffer descriptor buffer address*/
        ENET_HAL_ClrTxBdAfterSend(curBd);

        /* Update the buffer address*/
        enetIfPtr->bdContext.txBdDirtyPtr = 
           ENET_DRV_IncrTxBuffDescripIndex(enetIfPtr, enetIfPtr->bdContext.txBdDirtyPtr);

        /* Clear the buffer full flag*/
        enetIfPtr->bdContext.isTxBdFull = false;
    }
    
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_IncrRxBuffDescripIndex
 * Return Value: The new rx buffer descriptor which number is increased one from old buffer descriptor.
 * Description: Increases the receive buffer descriptor to the next one.
 *END*********************************************************************/
volatile enet_bd_struct_t * ENET_DRV_IncrRxBuffDescripIndex(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd)
{
    assert(enetIfPtr);
    assert(curBd);
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    mask |= ENET_RX_BD_WRAP_FLAG_MASK;
    ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
    /* Increase the buffer descriptor, if it is the last one, increase to first one of the ring buffer*/
    if (bdAttr.flags & ENET_RX_BD_WRAP_FLAG)
    {
        curBd = enetIfPtr->bdContext.rxBdBasePtr;
    }
    else
    {
        curBd ++;
    }
    return curBd;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_IncrTxBuffDescripIndex
 * Return Value: The new tx buffer descriptor which number is increased one from old buffer descriptor..
 * Description: Increases the transmit buffer descriptor to the next one.
 *END*********************************************************************/
volatile enet_bd_struct_t * ENET_DRV_IncrTxBuffDescripIndex(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd)
{
    /* Increase the buffer descriptor*/
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    mask |= ENET_TX_BD_WRAP_FLAG_MASK;
    ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
    if (bdAttr.flags & ENET_TX_BD_WRAP_FLAG)
    {
        curBd = enetIfPtr->bdContext.txBdBasePtr;
    }
    else
    {
        curBd ++;
    }
    return curBd;
}
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_TxErrorStats
 * Return Value: None.
 * Description: ENET frame receive stats process.
 * This interface is used to process packet error statistic 
 * in the last buffer descriptor of each frame.
 *END*********************************************************************/
void ENET_DRV_TxErrorStats(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd)
{
#if ENET_ENABLE_DETAIL_STATS
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    mask.b.txBdTxErr = mask.b.txBdExcColErr = mask.b.txBdLateColErr \
         = mask.b.txBdTxUnderFlowErr = mask.b.txBdOverFlowErr = 1;
    mask |= (ENET_TX_BD_TX_ERR_FLAG_MASK | ENET_TX_BD_EXC_COL_FLAG_MASK | \
      ENET_TX_BD_LATE_COL_FLAG_MASK | ENET_TX_BD_UNDERFLOW_FLAG_MASK | ENET_TX_BD_OVERFLOW_FLAG_MASK);
    ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
    
    if (bdAttr.flags & ENET_TX_BD_TX_ERR_FLAG)
    {
        /* Transmit error*/
        enetIfPtr->stats.statsTxError++;

        if (bdAttr.flags & ENET_TX_BD_EXC_COL_FLAG)
        {
            /* Transmit excess collision*/
            enetIfPtr->stats.statsTxExcessCollision++;
        }
        else if (bdAttr.flags & ENET_TX_BD_LATE_COL_FLAG)
        {   
            /* Transmit late collision*/
            enetIfPtr->stats.statsTxLateCollision++;
        }
        else if (bdAttr.flags & ENET_TX_BD_UNDERFLOW_FLAG)
        {
            /* Transmit underflow*/
            enetIfPtr->stats.statsTxUnderFlow++;
        }
        else if (bdAttr.flags & ENET_TX_BD_OVERFLOW_FLAG)
        {
            /* Transmit overflow*/
            enetIfPtr->stats.statsTxOverFlow++;
        }
    }
#endif	 
    enetIfPtr->stats.statsTxTotal++;
}
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_RxErrorStats
 * Return Value: true if the frame is error else false.
 * Description: ENET frame receive stats process.
 * This interface is used to process packet statistic in the last buffer
 * descriptor of each frame.
 *END*********************************************************************/
bool ENET_DRV_RxErrorStats(enet_dev_if_t * enetIfPtr, volatile enet_bd_struct_t *curBd)
{
    assert(enetIfPtr);
    assert(curBd);
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    /* The last bd in the frame check the stauts of the received frame*/
    mask |= (ENET_RX_BD_OVERRUN_FLAG_MASK | ENET_RX_BD_LEN_VIOLAT_FLAG_MASK | \
      ENET_RX_BD_NO_OCTET_FLAG_MASK | ENET_RX_BD_CRC_ERR_FLAG_MASK | ENET_RX_BD_COLLISION_FLAG_MASK);
    ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);    
   
    if ((bdAttr.flags & ENET_RX_BD_OVERRUN_FLAG) || (bdAttr.flags & ENET_RX_BD_LEN_VIOLAT_FLAG) \
      || (bdAttr.flags & ENET_RX_BD_NO_OCTET_FLAG) || (bdAttr.flags & ENET_RX_BD_CRC_ERR_FLAG)\
        || (bdAttr.flags & ENET_RX_BD_COLLISION_FLAG))
    {
#if ENET_ENABLE_DETAIL_STATS         
        /* Discard error packets*/
        enetIfPtr->stats.statsRxError++;
        enetIfPtr->stats.statsRxDiscard++;

        /* Receive error*/
        if (bdAttr.flags & ENET_RX_BD_OVERRUN_FLAG)
        {
            /* Receive over run*/
            enetIfPtr->stats.statsRxOverRun++;
        }
        else if (bdAttr.flags & ENET_RX_BD_LEN_VIOLAT_FLAG)
        {
            /* Receive length greater than max frame*/
            enetIfPtr->stats.statsRxLengthGreater++;
        }
        else if (bdAttr.flags & ENET_RX_BD_NO_OCTET_FLAG)
        {
            /* Receive non-octet aligned frame*/
            enetIfPtr->stats.statsRxAlign++;
        }
        else if (bdAttr.flags & ENET_RX_BD_CRC_ERR_FLAG)
        {
            /* Receive crc error*/
            enetIfPtr->stats.statsRxFcs++;
        }
        else if (bdAttr.flags & ENET_RX_BD_COLLISION_FLAG)
        { 
            /* late collision frame discard*/
            enetIfPtr->stats.statsRxCollision++;
        }
#endif
        return true;
    }
    else
    {
        /* Add the right packets*/            
        enetIfPtr->stats.statsRxTotal++;
        return false;
    }
}

#if ENET_RECEIVE_ALL_INTERRUPT
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_ReceiveData
 * Return Value: The execution status.
 * Description: ENET frame receive function.
 * This interface receive the frame from ENET deviece and returns the address 
 * of the received data. This is used to do receive data in receive interrupt
 * handler. This is the pure interrupt mode
 *END*********************************************************************/
enet_status_t ENET_DRV_ReceiveData(enet_dev_if_t * enetIfPtr)
{
    volatile enet_bd_struct_t *curBd;
    uint16_t bdNumTotal = 0, lenTotal = 0;
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    enet_mac_packet_buffer_t packetBuffer[kEnetMaxFrameBdNumbers] = {{0}};
    /* Check input parameters*/
    if ((!enetIfPtr) || (!enetIfPtr->bdContext.rxBdCurPtr))
    {
        return kStatus_ENET_InvalidInput;
    }
   
    /* Check the current buffer descriptor address*/
    curBd = enetIfPtr->bdContext.rxBdCurPtr;
    /* Return if the current buffer descriptor is empty*/	
    mask |= (ENET_RX_BD_EMPTY_FLAG_MASK | ENET_RX_BD_TRUNC_FLAG_MASK | ENET_RX_BD_LAST_FLAG_MASK | ENET_BD_LEN_MASK);
    ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
    while(!(bdAttr.flags & ENET_RX_BD_EMPTY_FLAG))
    {
        /* Check if receive buffer is full*/
        if(enetIfPtr->bdContext.isRxBdFull)
        {
#if ENET_ENABLE_DETAIL_STATS 
            enetIfPtr->stats.statsRxDiscard++;
#endif
            ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
            return kStatus_ENET_RxBdFull;
        }

        /* Increase current buffer descriptor to the next one*/
        enetIfPtr->bdContext.rxBdCurPtr = 
            ENET_DRV_IncrRxBuffDescripIndex(enetIfPtr, enetIfPtr->bdContext.rxBdCurPtr);
        /* Check if the buffer is full*/
        if (enetIfPtr->bdContext.rxBdCurPtr == enetIfPtr->bdContext.rxBdDirtyPtr)
        {
            enetIfPtr->bdContext.isRxBdFull = true;
        }

         /* Discard packets with truncate error*/
        if (bdAttr.flags & ENET_RX_BD_TRUNC_FLAG)
        {
#if ENET_ENABLE_DETAIL_STATS 
            enetIfPtr->stats.statsRxTruncate++;
            enetIfPtr->stats.statsRxDiscard++;
#endif
            ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
            return kStatus_ENET_RxbdTrunc;
        }
        
       if (bdAttr.flags & ENET_RX_BD_LAST_FLAG) 
       {
           /* The last bd in the frame check the stauts of the received frame*/
           if (ENET_DRV_RxErrorStats(enetIfPtr, curBd))
           {
               ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
               return kStatus_ENET_RxbdError;
           }
           else
           {
                packetBuffer[bdNumTotal].data = ENET_HAL_GetBuffDescripData(curBd);
                packetBuffer[bdNumTotal].length = bdAttr.bdLen - lenTotal;
                /* Crc length check */
                if(enetIfPtr->isRxCrcFwdEnable)
                {
                    packetBuffer[bdNumTotal].length -= kEnetFrameFcsLen;
                }
                packetBuffer[bdNumTotal].next = NULL;
#if FSL_FEATURE_ENET_SUPPORT_PTP
                ENET_DRV_GetRxTs(&enetIfPtr->privatePtp, 
                    packetBuffer[0].data, curBd);
#endif
                if(enetIfPtr->enetNetifcall)
                {
                    enetIfPtr->enetNetifcall(enetIfPtr, &packetBuffer[0]);
                }

               /* Update receive buffer descriptor*/
               ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
               bdNumTotal = 0;
           }
        }
        else
        {
            packetBuffer[bdNumTotal].data = ENET_HAL_GetBuffDescripData(curBd);
            packetBuffer[bdNumTotal].length = enetIfPtr->bdContext.rxBuffSizeAlign;
            lenTotal += packetBuffer[bdNumTotal].length;
            packetBuffer[bdNumTotal].next = &packetBuffer[bdNumTotal + 1];
            bdNumTotal ++;
            /* Check a frame with total bd numbers */
            if (bdNumTotal == kEnetMaxFrameBdNumbers)
            {
#if ENET_ENABLE_DETAIL_STATS 
                enetIfPtr->stats.statsRxDiscard++;
#endif
                ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
                return kStatus_ENET_SmallRxBuffSize;
            }
        }

        /* Check the current buffer descriptor address*/
        curBd = enetIfPtr->bdContext.rxBdCurPtr;
        ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
    }

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_InstallNetIfCall
 * Return Value: The execution status. 
 * Description: Install ENET TCP/IP stack net interface callback function .
 * This interface call the net interface of the TCP/IP stack to deliver the 
 * received data to stack.
 *END*********************************************************************/
enet_status_t ENET_DRV_InstallNetIfCall(enet_dev_if_t * enetIfPtr, enet_netif_callback_t function)
{
    if(!enetIfPtr)
    {
        return kStatus_ENET_InvalidInput;  
    } 
 
    enetIfPtr->enetNetifcall = function;
    return kStatus_ENET_Success;
}

#else
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_ReceiveData
 * Return Value: The execution status.
 * Description: ENET frame receive function.
 * This interface receive the frame from ENET device and returns the address 
 * of the received data. This is used to do receive data on polling +
 * interrupt mode.
 * we recommend to use the sync signal in receive interrupt handler to 
 * wakeup the blocked polling or for sync signal flag check when receive 
 * data on polling mode.
 * To avoid the receive buffer descriptor overflow due to the latency 
 * of the stack process task, extended data buffers in enetIfPtr->bdContext.extRxBuffQue
 * are used to update the receive buffer descriptor. please make sure
 * the data buffers are immediately enqueued back to the enetIfPtr->bdContext.extRxBuffQue  
 * after the data is copied to upper layer buffer. enet_mac_enqueue_buffer should be
 * called to do the data buffer enqueue process in your receive adaptor application. 
 *
 *END*********************************************************************/
enet_status_t ENET_DRV_ReceiveData(enet_dev_if_t * enetIfPtr, enet_mac_packet_buffer_t *packBuffer)
{
    volatile enet_bd_struct_t *curBd;
    bool isLastFrame = true;
    uint16_t totalLen = 0;
    uint64_t mask = 0;
    enet_bd_attr_t bdAttr;
    enet_mac_packet_buffer_t *TempBuff = NULL;
    /* Check input parameters*/
    if ((!enetIfPtr) || (!packBuffer) || (!enetIfPtr->bdContext.rxBdCurPtr))
    {
        return kStatus_ENET_InvalidInput;
    }
    mask |= (ENET_RX_BD_EMPTY_FLAG_MASK | ENET_RX_BD_TRUNC_FLAG_MASK | ENET_RX_BD_LAST_FLAG_MASK | ENET_BD_LEN_MASK);
    /* Check if the bd is full*/
    if (!enetIfPtr->bdContext.isRxBdFull)
    {
        /* Check the current buffer descriptor's empty flag*/
        curBd = enetIfPtr->bdContext.rxBdCurPtr;        
        ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
        if (bdAttr.flags & ENET_RX_BD_EMPTY_FLAG)
        {
            return kStatus_ENET_RxbdEmpty;
        }
    
        /* Increase current buffer descriptor to the next one*/
        enetIfPtr->bdContext.rxBdCurPtr = 
            ENET_DRV_IncrRxBuffDescripIndex(enetIfPtr, enetIfPtr->bdContext.rxBdCurPtr);
        if (enetIfPtr->bdContext.rxBdCurPtr == enetIfPtr->bdContext.rxBdDirtyPtr)
        {
            enetIfPtr->bdContext.isRxBdFull = true;
        }

        /* Discard packets with truncate error*/
        if (bdAttr.flags & ENET_RX_BD_TRUNC_FLAG)
        {
#if ENET_ENABLE_DETAIL_STATS 
            enetIfPtr->stats.statsRxTruncate++;
            enetIfPtr->stats.statsRxDiscard++;
#endif
            ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
            return kStatus_ENET_RxbdTrunc;
        }

        if (bdAttr.flags & ENET_RX_BD_LAST_FLAG)
        {
            /*This is valid frame */
            isLastFrame = true;

            /* The last bd in the frame check the status of the received frame*/
            if (!ENET_DRV_RxErrorStats(enetIfPtr, curBd))
            {
                packBuffer->data = ENET_HAL_GetBuffDescripData(curBd);
                packBuffer->length = bdAttr.bdLen;
                /* Crc length check */
                if(enetIfPtr->isRxCrcFwdEnable)
                {
                    packBuffer->length -= kEnetFrameFcsLen;
                }
#if FSL_FEATURE_ENET_SUPPORT_PTP
                ENET_DRV_GetRxTs(&enetIfPtr->privatePtp, packBuffer->data, curBd);
#endif
                /* Update receive buffer descriptor*/
                return ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, true);
            }
            else
            {
                ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
                return kStatus_ENET_RxbdError;
            }
        }
        else
        {
            /* Store the fragments of a frame on several buffer descriptors*/
            isLastFrame = false;
            packBuffer->data = ENET_HAL_GetBuffDescripData(curBd);
            packBuffer->length = enetIfPtr->bdContext.rxBuffSizeAlign;
            totalLen = packBuffer->length;
            if(packBuffer->next)
            {
                TempBuff = packBuffer->next;
            }
            else
            {
#if ENET_ENABLE_DETAIL_STATS 
                enetIfPtr->stats.statsRxMissed++;
#endif
                return kStatus_ENET_NoEnoughRxBuffers;
            }
        }
    }
    else
    {
#if ENET_ENABLE_DETAIL_STATS 
         enetIfPtr->stats.statsRxMissed++;
#endif
         ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
         return kStatus_ENET_RxBdFull;
    }

    /*process the frame stored on several bds*/
    while (!isLastFrame)
    {
        if (!enetIfPtr->bdContext.isRxBdFull)
        {
            /* Get the current buffer descriptor address*/
            curBd = enetIfPtr->bdContext.rxBdCurPtr;
            ENET_HAL_GetBufDescripAttr(curBd, mask, &bdAttr);
            if (bdAttr.flags & ENET_RX_BD_EMPTY_FLAG)
            {
                return kStatus_ENET_RxbdEmpty;
            }
    
            /* Increase current buffer descriptor to the next one*/
            enetIfPtr->bdContext.rxBdCurPtr = 
                ENET_DRV_IncrRxBuffDescripIndex(enetIfPtr, enetIfPtr->bdContext.rxBdCurPtr);
            if (enetIfPtr->bdContext.rxBdCurPtr == enetIfPtr->bdContext.rxBdDirtyPtr)
            {
                enetIfPtr->bdContext.isRxBdFull = true;
            }

            /* Discard packets with truncate error*/
            if (bdAttr.flags & ENET_RX_BD_TRUNC_FLAG)
            {
#if ENET_ENABLE_DETAIL_STATS 
                enetIfPtr->stats.statsRxTruncate++;
                enetIfPtr->stats.statsRxDiscard++;
#endif
                ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
                return kStatus_ENET_RxbdTrunc;
            }
    
            if (bdAttr.flags & ENET_RX_BD_LAST_FLAG)
            {
                /*This is the last bd in a frame*/     
                isLastFrame = true;
    
                /* The last bd in the frame check the status of the received frame*/
                if (ENET_DRV_RxErrorStats(enetIfPtr, curBd))
                {
                    ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
                    return kStatus_ENET_RxbdError;
                }
                else
                {
                    TempBuff->data = ENET_HAL_GetBuffDescripData(curBd);
                    TempBuff->length = bdAttr.bdLen - totalLen;
                    /* Crc length check */
                    if(enetIfPtr->isRxCrcFwdEnable)
                    {
                        TempBuff->length -= kEnetFrameFcsLen;
                    }                   
                    /* Delivery the last part data to the packet*/
#if FSL_FEATURE_ENET_SUPPORT_PTP
                    ENET_DRV_GetRxTs(&enetIfPtr->privatePtp, packBuffer->data, curBd);
#endif
                    /* Update receive buffer descriptor*/         
                    return ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, true);
                }
            }
            else
            {
                isLastFrame = false;
                TempBuff->data = ENET_HAL_GetBuffDescripData(curBd);
                TempBuff->length = enetIfPtr->bdContext.rxBuffSizeAlign;
                totalLen += TempBuff->length;             
                if(TempBuff->next)
                {
                    TempBuff = TempBuff->next;
                }
                else
                {
#if ENET_ENABLE_DETAIL_STATS 
                    enetIfPtr->stats.statsRxMissed++;
#endif
                    return kStatus_ENET_NoEnoughRxBuffers;
                }
            }  
        }
        else
        {
#if ENET_ENABLE_DETAIL_STATS 
            enetIfPtr->stats.statsRxMissed++;
#endif
            ENET_DRV_UpdateRxBuffDescrip(enetIfPtr, false);
            return kStatus_ENET_RxBdFull;
        }
    }

    return kStatus_ENET_Success;
}
#endif
/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_SendData
 * Return Value: The execution status.
 * Description: ENET frame send function.
 * This interface send the frame to ENET device. If the transmit buffer size
 * is less than the maximum frame size 1518/1522, please make sure the buffer
 * size larger than 256. 
 *END*********************************************************************/
enet_status_t ENET_DRV_SendData(enet_dev_if_t * enetIfPtr, uint32_t dataLen, uint32_t bdNumUsed)
{
    volatile enet_bd_struct_t *curBd;
    bool isPtpMsg = false;
    uint16_t bdIdx = 0;
    uint32_t size = 0;
    uint8_t *packet;
    ENET_Type * base;
    
    /* Check input parameters*/
    if ((!enetIfPtr ) || (!bdNumUsed))
    {
        return kStatus_ENET_InvalidInput;
    }

    if(enetIfPtr->bdContext.isTxBdFull)
    {
#if ENET_ENABLE_DETAIL_STATS
        enetIfPtr->stats.statsTxMissed ++;
#endif
        return kStatus_ENET_TxbdFull;
    }

    /* Get the current buffer descriptor address*/
    curBd = enetIfPtr->bdContext.txBdCurPtr;
#if FSL_FEATURE_ENET_SUPPORT_PTP
    /* Check ptp message only for the first part including ptp head information*/ 
    packet = ENET_HAL_GetBuffDescripData(curBd);
    ENET_DRV_Parse1588Packet(packet, NULL, &isPtpMsg, true);
#endif
    base = g_enetBase[enetIfPtr->deviceNumber];
    /* Bd number need for the data transmit*/
    if(bdNumUsed == 1)
    {  
        /* Packet the transmit frame to the buffer descriptor*/
        ENET_HAL_SetTxBdBeforeSend(curBd, dataLen, isPtpMsg, enetIfPtr->isTxCrcEnable, true);

        /* Increase the buffer descriptor address*/
        enetIfPtr->bdContext.txBdCurPtr = 
            ENET_DRV_IncrTxBuffDescripIndex(enetIfPtr, enetIfPtr->bdContext.txBdCurPtr);

        /* Return if the transmit buffer ring is full*/
        if (enetIfPtr->bdContext.txBdCurPtr == enetIfPtr->bdContext.txBdDirtyPtr)
        {
            enetIfPtr->bdContext.isTxBdFull = true;
        }
        else
        {
            enetIfPtr->bdContext.isTxBdFull = false;
        }
        /* Active the transmit buffer descriptor*/
        ENET_HAL_SetTxBdActive(base);   

   }
   else
   {
        for(bdIdx = 0; bdIdx < bdNumUsed; bdIdx ++)
        {

            if(enetIfPtr->bdContext.isTxBdFull)
            {
#if ENET_ENABLE_DETAIL_STATS
                enetIfPtr->stats.statsTxMissed ++;
#endif
                return kStatus_ENET_TxbdFull;
            }

            /* Get the current buffer descriptor address*/
            curBd = enetIfPtr->bdContext.txBdCurPtr;

            /* Last Buffer Descriptor */
            if(bdIdx == bdNumUsed - 1) 
            {
                /* Set the transmit flag in the buffer descriptor before the frame 
                is sent and indicate it is the last one. */
                ENET_HAL_SetTxBdBeforeSend(curBd, dataLen - size, isPtpMsg, enetIfPtr->isTxCrcEnable, true);
            }
            else
            {
                /* Set the transmit flag in the buffer descriptor before the frame 
                is sent and indicate it is not the last one. */
                ENET_HAL_SetTxBdBeforeSend(curBd, enetIfPtr->bdContext.txBuffSizeAlign, isPtpMsg, enetIfPtr->isTxCrcEnable, false);
                size += enetIfPtr->bdContext.txBuffSizeAlign;
            }

            /* Increase the buffer address*/
            enetIfPtr->bdContext.txBdCurPtr = 
                ENET_DRV_IncrTxBuffDescripIndex(enetIfPtr, enetIfPtr->bdContext.txBdCurPtr);
  
            /* Return if the transmit buffer ring is full*/
            if (enetIfPtr->bdContext.txBdCurPtr == enetIfPtr->bdContext.txBdDirtyPtr)
            {
                 enetIfPtr->bdContext.isTxBdFull = true;
            }
            else
            {
                 enetIfPtr->bdContext.isTxBdFull = false;   
            }
            /* Active the transmit buffer descriptor*/
            ENET_HAL_SetTxBdActive(base);
        }
    
   }
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_RxIRQHandler
 * Description: ENET receive isr.
 * This interface is the receive interrupt handler.
 *END*********************************************************************/
void ENET_DRV_RxIRQHandler(uint32_t instance)
{
    enet_dev_if_t *enetIfPtr;
    ENET_Type * base;
    enetIfPtr = enetIfHandle[instance];
#if !ENET_RECEIVE_ALL_INTERRUPT
    event_flags_t flag = 0x1;
#endif
    /*Check input parameter*/
    if (!enetIfPtr)
    {
        return;
    }
    base = g_enetBase[enetIfPtr->deviceNumber];
    /* Get interrupt status.*/
    while ((ENET_HAL_GetIntStatusFlag(base, kEnetRxFrameInterrupt)) || (ENET_HAL_GetIntStatusFlag(base, kEnetRxByteInterrupt)))
    {
        /*Clear interrupt*/
        ENET_HAL_ClearIntStatusFlag(base, kEnetRxFrameInterrupt);
        ENET_HAL_ClearIntStatusFlag(base, kEnetRxByteInterrupt);
#if !ENET_RECEIVE_ALL_INTERRUPT
        /* Release sync signal-----------------*/
        OSA_EventSet(&enetIfPtr->enetReceiveSync, flag);
#else
        /* Receive peripheral driver*/
        ENET_DRV_ReceiveData(enetIfPtr);
#endif    
    }
    
}


/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_TxIRQHandler
 * Description: ENET transmit isr.
 * This interface is the transmit interrupt handler.
 *END*********************************************************************/
void ENET_DRV_TxIRQHandler(uint32_t instance)
{
    enet_dev_if_t *enetIfPtr;
    ENET_Type * base;
    enetIfPtr = enetIfHandle[instance];

    /*Check input parameter*/
    if (!enetIfPtr)
    {
        return;
    }

    base = g_enetBase[enetIfPtr->deviceNumber];

    /* Get interrupt status.*/
    while ((ENET_HAL_GetIntStatusFlag(base, kEnetTxFrameInterrupt)) ||
        (ENET_HAL_GetIntStatusFlag(base, kEnetTxByteInterrupt)))   
    {
        /*Clear interrupt*/
        ENET_HAL_ClearIntStatusFlag(base, kEnetTxFrameInterrupt);
        ENET_HAL_ClearIntStatusFlag(base, kEnetTxByteInterrupt);
       
        /*Clean up the transmit buffers*/
        ENET_DRV_CleanupTxBuffDescrip(enetIfPtr);
    }   

    /* Active the transmit buffer descriptor*/
    /* Needed for Kinetis: otherwise last packet in ring buffer may be not sent.*/
    ENET_HAL_SetTxBdActive(base); 
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Calc_Crc32
 * Description: Calculate crc-32.
 * This function is called by the enet_mac_add_multicast_group and 
 * enet_mac_leave_multicast_group.
 *END*********************************************************************/
void ENET_DRV_Calc_Crc32(uint8_t *address, uint32_t *crcValue)
{
    uint32_t crc = ENET_ORIGINAL_CRC32, count1,count2;

    if ((!address) || (!crcValue))
    {
        return ;
    }
  
    /* Calculate the CRC-32 polynomial on the multicast group address*/
    for (count1 = 0; count1 < kEnetMacAddrLen; count1++)
    {
        uint8_t c = address[count1];
        for (count2 = 0; count2 < kEnetCrcOffset; count2++)
        {
            if ((c ^ crc)& 1U)
            {
                crc >>= 1U;
                c >>= 1U;
                crc ^= ENET_CRC32_POLYNOMIC;
            }
            else
            {
               crc >>= 1U;
               c >>= 1U;
            }
        }
    }

    *crcValue = crc;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_AddMulticastGroup
 * Return Value: The execution status.
 * Description: ADD ENET to the specific multicast group.
 * This function is used to add ENET device to specific multicast
 * group and it is called by the upper TCP/IP stack.
 *END*********************************************************************/
 enet_status_t ENET_DRV_AddMulticastGroup(uint32_t instance, uint8_t *address, uint32_t *hash)
{
    uint32_t crcValue;
    ENET_Type * base;

    /* Check input parameters*/
    if (!address)
    {
        return kStatus_ENET_InvalidInput;
    }
    base = g_enetBase[instance];
    /* Calculate the CRC-32 polynomial on the multicast group address*/
    ENET_DRV_Calc_Crc32(address, &crcValue);

    /* Set the hash table*/
    ENET_HAL_SetMulticastAddrHash(base, crcValue, kEnetSpecialAddressEnable);

    /* Store the hash value in the right address structure*/
    *hash = (crcValue >>= 26U) & kEnetCrcMask1;

    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: ENET_DRV_Leave_MulticastGroup
 * Return Value: The execution status.
 * Description: ENET Leave specific multicast group.
 * This function is used to remove ENET device from specific multicast
 * group and it is called by the upper TCP/IP stack.
 *END*********************************************************************/
 enet_status_t ENET_DRV_LeaveMulticastGroup(uint32_t instance, uint8_t *address)
{
    uint32_t crcValue;
    ENET_Type * base;
    /* Check input parameters*/
    if (!address)
    {
        return kStatus_ENET_InvalidInput;
    }
    base = g_enetBase[instance];
    /* Calculate the CRC-32 polynomial on the multicast group address*/
    ENET_DRV_Calc_Crc32(address, &crcValue);

    /* Set the hash table*/
    ENET_HAL_SetMulticastAddrHash(base, crcValue, kEnetSpecialAddressDisable);
    
    return kStatus_ENET_Success;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_enqueue_buffer
 * Return Value: 
 * Description: ENET mac enqueue buffers.
 * This function is used to enqueue buffers to buffer queue.
 *END*********************************************************************/
void enet_mac_enqueue_buffer( void **queue, void *buffer)
{
    *((void **)buffer) = *queue;
    *queue = buffer;
}

/*FUNCTION****************************************************************
 *
 * Function Name: enet_mac_dequeue_buffer
 * Return Value: The dequeued buffer pointer
 * Description: ENET mac dequeue buffers.
 * This function is used to dequeue a buffer from buffer queue.
 *END*********************************************************************/
void *enet_mac_dequeue_buffer( void **queue)
{
    void *buffer = *queue;

    if (buffer) 
    {
        *queue = *((void **)buffer);
    }
    
    return buffer;
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

