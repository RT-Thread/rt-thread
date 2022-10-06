/**
 * \file  edma.c
 *
 * \brief This file contains device abstraction layer APIs for the EDMA device.
 *        There are APIs here to enable the EDMA instance, set the required
 *        configurations for communication, transmit or receive data.
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


/* Driver APIs */
#include "edma.h"

#include "hw_types.h"

/****************************************************************************/
/*                         GLOBAL VARIABLES                                 */
/****************************************************************************/
unsigned int regionId;

/****************************************************************************/
/*                     API FUNCTION DEFINITIONS                             */
/****************************************************************************/

/**
 *  \brief   EDMA3 Initialization
 *  
 *  This function initializes the EDMA3 Driver
 *  Clears the error specific registers (EMCR/EMCRh, QEMCR, CCERRCLR) &
 *  initialize the Queue Number Registers
 *
 *  \param  baseAdd                  Memory address of the EDMA instance used.\n
 *
 *  \param  queNum                   Event Queue Number to which the channel
 *                                   will be mapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  \return None
 *
 *  \note   The regionId is the shadow region(0 or 1) used and the,
 *          Event Queue used is either (0 or 1). There are only four shadow 
 *          regions and only two event Queues
 */
void EDMA3Init(unsigned int baseAdd,
           unsigned int queNum)
{
    unsigned int count = 0;
    unsigned int i = 0;
    
#ifdef _TMS320C6X
    /* For DSP, regionId is assigned here and used globally in the driver */
    regionId = (unsigned int)1u;
#else
    /* FOR ARM, regionId is assigned here and used globally in the driver   */
    regionId = (unsigned int)0u;
#endif

    /* Clear the Event miss Registers                                       */
    HWREG(baseAdd + EDMA3CC_EMCR) = EDMA3_SET_ALL_BITS;
    HWREG(baseAdd + EDMA3CC_EMCRH) = EDMA3_SET_ALL_BITS;

    HWREG(baseAdd + EDMA3CC_QEMCR) = EDMA3_SET_ALL_BITS;

    /* Clear CCERR register                                                 */
    HWREG(baseAdd + EDMA3CC_CCERRCLR) = EDMA3_SET_ALL_BITS;

    /* FOR TYPE EDMA*/ 
    /* Enable the DMA (0 - 64) channels in the DRAE and DRAEH register */
       
    HWREG(baseAdd + EDMA3CC_DRAE(regionId)) = EDMA3_SET_ALL_BITS;
    HWREG(baseAdd + EDMA3CC_DRAEH(regionId)) = EDMA3_SET_ALL_BITS;


    if((EDMA_REVID_AM335X == EDMAVersionGet()))
    {           
         for(i = 0; i < 64; i++)
         {
              /* All events are one to one mapped with the channels */
              HWREG(baseAdd + EDMA3CC_DCHMAP(i)) = i << 5;
         }

    }
    /* Initialize the DMA Queue Number Registers                            */
    for (count = 0;count < SOC_EDMA3_NUM_DMACH; count++)
    {
         HWREG(baseAdd + EDMA3CC_DMAQNUM(count >> 3u)) &= 
                                                    EDMA3CC_DMAQNUM_CLR(count);
         HWREG(baseAdd + EDMA3CC_DMAQNUM(count >> 3u)) |= 
                                                    EDMA3CC_DMAQNUM_SET(count,queNum);
    }

    /* FOR TYPE QDMA */
    /* Enable the DMA (0 - 64) channels in the DRAE register                */
    HWREG(baseAdd + EDMA3CC_QRAE(regionId)) = EDMA3_SET_ALL_BITS;

    /* Initialize the QDMA Queue Number Registers                           */
    for (count = 0;count < SOC_EDMA3_NUM_QDMACH; count++)
    {
        HWREG(baseAdd + EDMA3CC_QDMAQNUM) &= EDMA3CC_QDMAQNUM_CLR(count);
        HWREG(baseAdd + EDMA3CC_QDMAQNUM) |= 
                       EDMA3CC_QDMAQNUM_SET(count,queNum);
    }
}

/**
 * \brief   This API return the revision Id of the peripheral.
 *
 * \param   baseAdd     Memory address of the EDMA instance used.\n
 *
 *  \return  None
 */
unsigned int EDMA3PeripheralIdGet(unsigned int baseAdd)
{
    return (HWREG(baseAdd + EDMA3CC_REVID));
}

/**
 * \brief  Enable channel to Shadow region mapping
 *
 * This API allocates DMA/QDMA channels or TCCs, and the same resources are 
 * enabled in the shadow region specific register (DRAE/DRAEH/QRAE).
 * Here only one shadow region is used since, there is only one Master.
 *
 *  \param   baseAdd     Memory address of the EDMA instance used.\n
 *
 *  \param   chtype      (DMA/QDMA) Channel
 *                        For Example: For DMA it is,
 *                        EDMA3_CHANNEL_TYPE_DMA.\n
 *
 *  \param   chNum       Allocated channel number.\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void EDMA3EnableChInShadowReg(unsigned int baseAdd, 
                              unsigned int chType, 
                              unsigned int chNum)
{
    /* Allocate the DMA/QDMA channel */
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
         /* FOR TYPE EDMA*/ 
         if(chNum < 32)
         {
              /* Enable the DMA channel in the DRAE registers */
              HWREG(baseAdd + EDMA3CC_DRAE(regionId)) |= (0x01u << chNum);
         }
         else
         {
              /* Enable the DMA channel in the DRAEH registers */
              HWREG(baseAdd + EDMA3CC_DRAEH(regionId)) |= (0x01u << (chNum - 32));
         }
        
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA== chType)
    {
        /* FOR TYPE QDMA */
        /* Enable the QDMA channel in the DRAE/DRAEH registers */
        HWREG(baseAdd + EDMA3CC_QRAE(regionId)) |= 0x01u << chNum;
    }
}

/**
 * \brief  Disable channel to Shadow region mapping
 *
 * This API allocates DMA/QDMA channels or TCCs, and the same resources are 
 * enabled in the shadow region specific register (DRAE/DRAEH/QRAE).
 * Here only one shadow region is used since, there is only one Master.
 *
 * \param   baseAdd   Memory address of the EDMA instance used.\n
 *
 * \param   chtype    (DMA/QDMA) Channel
 *                      For Example: For DMA it is,
 *                      EDMA3_CHANNEL_TYPE_DMA.\n
 *
 * \param   chNum      Allocated channel number.\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void EDMA3DisableChInShadowReg(unsigned int baseAdd, 
                               unsigned int chType, 
                               unsigned int chNum)
{
    /* Allocate the DMA/QDMA channel */
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
        /* FOR TYPE EDMA*/
         if(chNum < 32)
         { 
              /* Enable the DMA channel in the DRAE registers */
              HWREG(baseAdd + EDMA3CC_DRAE(regionId)) &= ~(0x01u << chNum);
         }
         else
         {
              /* Enable the DMA channel in the DRAEH registers */
              HWREG(baseAdd + EDMA3CC_DRAEH(regionId)) &= ~(0x01u << (chNum - 32));
         }
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA== chType)
    {
        /* FOR TYPE QDMA */
        /* Enable the QDMA channel in the DRAE/DRAEH registers */
        HWREG(baseAdd + EDMA3CC_QRAE(regionId)) &= ((~0x01u) << chNum);
    }
}

/**
 *  \brief   This function maps DMA channel to any of the PaRAM sets
 *           in the PaRAM memory map.
 *
 *  \param   baseAdd   Memory address of the EDMA instance used.
 *
 *  \param   channel   The DMA channel number required to be mapped.
 *
 *  \param   paramSet  It specifies the paramSet to which DMA channel
 *                     required to be mapped.
 *
 *  \return  None
 */
void EDMA3ChannelToParamMap(unsigned int baseAdd,
                            unsigned int channel,
                            unsigned int paramSet)
{
    HWREG(baseAdd + EDMA3CC_DCHMAP(channel)) = paramSet << 5;
} 

/**
 *  \brief  Map channel to Event Queue
 *
 *  This API maps DMA/QDMA channels to the Event Queue
 *
 *  \param  baseAdd    Memory address of the EDMA instance used.\n
 *
 *  \param  chtype     (DMA/QDMA) Channel
 *                     For Example: For QDMA it is
 *                     EDMA3_CHANNEL_TYPE_QDMA.\n
 *
 *  \param  chNum      Allocated channel number.\n
 *
 *  \param  evtQNum    Event Queue Number to which the channel
 *                     will be mapped (valid only for the
 *                     Master Channel (DMA/QDMA) request).\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void EDMA3MapChToEvtQ(unsigned int baseAdd, 
                      unsigned int chType, 
                      unsigned int chNum, 
                      unsigned int evtQNum)
{
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
        /* Associate DMA Channel to Event Queue                             */
        HWREG(baseAdd + EDMA3CC_DMAQNUM((chNum) >> 3u)) &= 
                             EDMA3CC_DMAQNUM_CLR(chNum);

        HWREG(baseAdd + EDMA3CC_DMAQNUM((chNum) >> 3u)) |= 
                      EDMA3CC_DMAQNUM_SET((chNum), evtQNum);
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
    {
        /* Associate QDMA Channel to Event Queue                            */
        HWREG(baseAdd + EDMA3CC_QDMAQNUM) |= 
                       EDMA3CC_QDMAQNUM_SET(chNum, evtQNum);
    }
}

/**
 *  \brief  Remove Mapping of channel to Event Queue
 *
 *  This API Unmaps DMA/QDMA channels to the Event Queue allocated
 *
 *  \param  baseAdd    Memory address of the EDMA instance used.\n
 *
 *  \param  chtype     (DMA/QDMA) Channel
 *                     For Example: For DMA it is
 *                     EDMA3_CHANNEL_TYPE_DMA.\n
 *
 *  \param  chNum      Allocated channel number.\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void EDMA3UnmapChToEvtQ(unsigned int baseAdd, 
                        unsigned int chType, 
                        unsigned int chNum)
{
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
        /* Unmap DMA Channel to Event Queue                                */
        HWREG(baseAdd + EDMA3CC_DMAQNUM((chNum) >> 3u)) |= 
                          EDMA3CC_DMAQNUM_CLR(chNum);
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
    {
        /* Unmap QDMA Channel to Event Queue                               */
        HWREG(baseAdd + EDMA3CC_QDMAQNUM) |= 
                             EDMA3CC_QDMAQNUM_CLR(chNum);
    }
}

/**
 *  \brief  Enables the user to map a QDMA channel to PaRAM set
 *          This API Needs to be called before programming the paRAM sets for
 *          the QDMA Channels.Application needs to maitain the paRAMId 
 *          provided by this API.This paRAMId is used to set paRAM and get
 *          paRAM. Refer corresponding API's for more details.
 *
 *  \param  baseAdd                  Memory address of the EDMA instance used.\n
 *
 *  \param  chNum                    Allocated QDMA channel number.\n
 *
 *  \param  paRaMID                  PaRAM Id to which the QDMA channel will be
 *                                   mapped to.
 *
 *  \return None
 *
 *  Note : The PaRAMId requested must be greater than 32(SOC_EDMA3_NUM_DMACH). 
 *         and lesser than SOC_EDMA3_NUM_DMACH + chNum  Because, the first 
 *         32 PaRAM's are directly mapped to first 32 DMA channels and (32 - 38)
 *         for QDMA Channels. (32 - 38) is assigned by driver in this API. 
 *
 */
void EDMA3MapQdmaChToPaRAM(unsigned int baseAdd,
                           unsigned int chNum,
                           unsigned int *paRAMId)
{
    /* First 32 channels are for DMA only                                   */
    /* if (((*paRAMId) > SOC_EDMA3_NUM_DMACH) &&
            ((*paRAMId) < SOC_EDMA3_NUM_DMACH+SOC_EDMA3_NUM_QDMACH))  */ 
    if ((SOC_EDMA3_NUM_DMACH + chNum) == (*paRAMId))
    {
        /* Map Parameter RAM Set Number for specified channelId             */
        HWREG(baseAdd + EDMA3CC_QCHMAP(chNum)) &= EDMA3CC_QCHMAP_PAENTRY_CLR;
        HWREG(baseAdd + EDMA3CC_QCHMAP(chNum)) |= EDMA3CC_QCHMAP_PAENTRY_SET(*paRAMId);
    }
    else
    {
    (*paRAMId) = (SOC_EDMA3_NUM_DMACH + chNum);
        /* Map Parameter RAM Set Number for specified channelId             */
        HWREG(baseAdd + EDMA3CC_QCHMAP(chNum)) &= EDMA3CC_QCHMAP_PAENTRY_CLR;
        HWREG(baseAdd + EDMA3CC_QCHMAP(chNum)) |= EDMA3CC_QCHMAP_PAENTRY_SET(*paRAMId);
    }
}

/**
 * \brief  Assign a Trigger Word to the specified QDMA channel
 *
 * This API sets the Trigger word for the specific QDMA channel in the QCHMAP
 * Register. Default QDMA trigger word is CCNT.
 *
 * \param  baseAdd             Memory address of the EDMA instance used.\n
 *
 * \param  chNum               QDMA Channel which needs to be assigned
 *                             the Trigger Word
 *
 * \param  trigWord            The Trigger Word for the QDMA channel.
 *                             Trigger Word is the word in the PaRAM
 *                             Register Set which, when written to by CPU,
 *                             will start the QDMA transfer automatically.
 *
 * \return  None
 */
void EDMA3SetQdmaTrigWord(unsigned int baseAdd,
                          unsigned int chNum,
                          unsigned int trigWord)
{
     /* Set the Trigger Word */
     HWREG(baseAdd + EDMA3CC_QCHMAP(chNum)) |= EDMA3CC_QCHMAP_TRWORD_SET(trigWord);
}

/**
 *  \brief   Enables the user to Clear any missed event
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 * 
 *  \return  None
 */
void EDMA3ClrMissEvt(unsigned int baseAdd, 
                     unsigned int chNum)
{
    if(chNum < 32)
    {
         /*clear SECR to clean any previous NULL request                         */
         HWREG(baseAdd + EDMA3CC_S_SECR(regionId)) = (0x01u << chNum);
         /*clear EMCR to clean any previous NULL request                         */
         HWREG(baseAdd + EDMA3CC_EMCR) |= (0x01u <<  chNum);
    }
    else
    { 
         HWREG(baseAdd + EDMA3CC_S_SECRH(regionId)) = (0x01u << (chNum - 32));
         /*clear EMCRH to clean any previous NULL request                         */
         HWREG(baseAdd + EDMA3CC_EMCRH) |= (0x01u <<  (chNum - 32));
    }
}

/**
 *  \brief   Enables the user to Clear any QDMA missed event
 *
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 * 
 *  \return  None
 */
void EDMA3QdmaClrMissEvt(unsigned int baseAdd, 
                         unsigned int chNum)
{
    /*clear SECR to clean any previous NULL request                         */
    HWREG(baseAdd + EDMA3CC_S_QSECR(regionId)) = (0x01u << chNum);
    
    /*clear EMCR to clean any previous NULL request                         */
    HWREG(baseAdd + EDMA3CC_QEMCR) |= (0x01u <<  chNum);
}

/**
 *  \brief   Enables the user to Clear any Channel controller Errors
 *
 *  \param   baseAdd              Memory address of the EDMA instance used.\n
 *
 *  \param   Flags                Masks to be passed.\n
 *
 *  Flags can have values:
 *
 *  EDMA3CC_CLR_TCCERR            Clears the TCCERR bit in the EDMA3CC 
 *                                ERR Reg\n
 *  EDMA3CC_CLR_QTHRQ0            Queue threshold error clear for queue 0.\n
 *  EDMA3CC_CLR_QTHRQ1            Queue threshold error clear for queue 1.
 *
 *  \return  None
 */
void EDMA3ClrCCErr(unsigned int baseAdd, 
                   unsigned int Flags)
{
    /* (CCERRCLR) - clear channel controller error register                 */
    HWREG(baseAdd + EDMA3CC_CCERRCLR) = Flags;
}

/**
 *  \brief   Enables the user to Set an event. This API helps user to manually 
 *           set events to initiate DMA transfer requests.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   This API is generally used during Manual transfers.\n
 */
void EDMA3SetEvt(unsigned int baseAdd, 
                 unsigned int chNum)
{
    if(chNum < 32)
    { 
         /* (ESR) - set corresponding bit to set a event                         */
         HWREG(baseAdd + EDMA3CC_S_ESR(regionId)) |= (0x01u <<  chNum);
    }
    else
    {
         /* (ESRH) - set corresponding bit to set a event                         */
         HWREG(baseAdd + EDMA3CC_S_ESRH(regionId)) |= (0x01u << (chNum - 32));
    }
}

/**
 *  \brief   Enables the user to Clear an event.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   This API is generally used during Manual transfers.\n
 */
void EDMA3ClrEvt(unsigned int baseAdd, 
                 unsigned int chNum) 
{
    if(chNum < 32)
    {
         /* (ECR) - set corresponding bit to clear a event                       */
         HWREG(baseAdd + EDMA3CC_S_ECR(regionId)) |= (0x01u <<  chNum);
    }
    else
    {
         /* (ECRH) - set corresponding bit to clear a event                       */
         HWREG(baseAdd + EDMA3CC_S_ECRH(regionId)) |= (0x01u << (chNum - 32));
    }
}

/**
 *  \brief   Enables the user to enable an DMA event.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in EESR sets the corresponding event 
 *           bits in EER. This is generally used for Event Based transfers.\n
 */
void EDMA3EnableDmaEvt(unsigned int baseAdd, 
                       unsigned int chNum)
{
    if(chNum < 32)
    { 
         /* (EESR) - set corresponding bit to enable DMA event                   */
         HWREG(baseAdd + EDMA3CC_S_EESR(regionId)) |= (0x01u <<  chNum);
    }
    else
    { 
         /* (EESRH) - set corresponding bit to enable DMA event                   */
         HWREG(baseAdd + EDMA3CC_S_EESRH(regionId)) |= (0x01u << (chNum - 32));
    }
}

/**
 *  \brief   Enables the user to Disable an DMA event.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in EECR clear the corresponding event bits 
 *           in EER; writes of 0 have no effect.. This is generally used for 
 *           Event Based transfers.\n
 */
void EDMA3DisableDmaEvt(unsigned int baseAdd, 
                        unsigned int chNum)
{
    if(chNum < 32)
    {
         /* (EECR) - set corresponding bit to disable event                      */
         HWREG(baseAdd + EDMA3CC_S_EECR(regionId)) |= (0x01u <<  chNum);
    }
    else
    {
         /* (EECRH) - set corresponding bit to disable event                      */
         HWREG(baseAdd + EDMA3CC_S_EECRH(regionId)) |= (0x01u <<  chNum);
    }
}

/**
 *  \brief   Enables the user to enable an QDMA event.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in QEESR sets the corresponding event 
              bits in QEER.\n
 */
void EDMA3EnableQdmaEvt(unsigned int baseAdd, 
                        unsigned int chNum)
{
    /* (QEESR) - set corresponding bit to enable QDMA event                 */
    HWREG(baseAdd + EDMA3CC_S_QEESR(regionId)) = (0x01u << chNum);
}

/**
 *  \brief   Enables the user to disable an QDMA event.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in QEECR clears the corresponding event 
              bits in QEER.\n
 */
void EDMA3DisableQdmaEvt(unsigned int baseAdd, 
                         unsigned int chNum)
{
    /* (QEESR) - set corresponding bit to enable QDMA event                 */
    HWREG(baseAdd + EDMA3CC_S_QEECR(regionId)) = (0x01u << chNum);
}

/**
 *  \brief   This returns EDMA3 CC error status.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
unsigned int EDMA3GetCCErrStatus(unsigned int baseAdd)
{
    unsigned int IntrStatusVal = 0;
    IntrStatusVal = (unsigned int)HWREG(baseAdd + EDMA3CC_CCERR);

    return IntrStatusVal;
}

/**
 *  \brief   This function returns interrupts status of those events
 *           which is less than 32.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
unsigned int EDMA3GetIntrStatus(unsigned int baseAdd)
{
    unsigned int IntrStatusVal = 0;

    IntrStatusVal = (unsigned int)HWREG(baseAdd + EDMA3CC_S_IPR(regionId));

    return IntrStatusVal;
}

/**
 *  \brief   This function returns interrupts status of those events
 *           which is greater than 32.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
unsigned int EDMA3IntrStatusHighGet(unsigned int baseAdd)
{
    unsigned int IntrStatusVal = 0;

    IntrStatusVal = (unsigned int)HWREG(baseAdd + EDMA3CC_S_IPRH(regionId));

    return IntrStatusVal;
}

/**
 *  \brief   This returns error interrupt status for those events whose
 *           event number is less than 32.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
unsigned int EDMA3GetErrIntrStatus(unsigned int baseAdd)
{
    unsigned int IntrStatusVal = 0;

    IntrStatusVal = (unsigned int)HWREG(baseAdd + EDMA3CC_EMR);

    return IntrStatusVal;
}

/**
 *  \brief   This returns error interrupt status for those events whose
 *           event number is greater than 32.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
unsigned int EDMA3ErrIntrHighStatusGet(unsigned int baseAdd)
{
    unsigned int IntrStatusVal = 0;

    IntrStatusVal = (unsigned int)HWREG(baseAdd + EDMA3CC_EMRH);

    return IntrStatusVal;
}

/**
 *  \brief   This returns QDMA error interrupt status.
 *
 *  \param   baseAdd            Memory address of the EDMA instance used.\n
 *
 *  \return  value              Status of the QDMA Interrupt Pending Register
 *
 */
unsigned int EDMA3QdmaGetErrIntrStatus(unsigned int baseAdd)
{
    unsigned int IntrStatusVal = 0;
    IntrStatusVal = (unsigned int)HWREG(baseAdd + EDMA3CC_QEMR);

    return IntrStatusVal;
}

/**
 *  \brief   Enables the user to enable the transfer completion interrupt 
 *           generation by the EDMA3CC for all DMA/QDMA channels.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   To set any interrupt bit in IER, a 1 must be written to the 
 *           corresponding interrupt bit in the interrupt enable set register.
 */
void EDMA3EnableEvtIntr(unsigned int baseAdd, 
                        unsigned int chNum) 
{
    if(chNum < 32)
    {
         /*  Interrupt Enable Set Register (IESR)                                */
         HWREG(baseAdd + EDMA3CC_S_IESR(regionId)) |= (0x01u <<  chNum);
    }
    else
    {
         /*  Interrupt Enable Set Register (IESRH)                                */
         HWREG(baseAdd + EDMA3CC_S_IESRH(regionId)) |= (0x01u << (chNum - 32));
    }
}

/**
 *  \brief   Enables the user to clear CC interrupts
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in IECR clear the corresponding interrupt 
 *           bits in the interrupt enable registers (IER); writes of 0 have 
 *           no effect.\n
 */
void EDMA3DisableEvtIntr(unsigned int baseAdd, 
                         unsigned int chNum)
{
    if(chNum < 32)
    {
         /* Interrupt Enable Clear Register (IECR)                               */
         HWREG(baseAdd + EDMA3CC_S_IECR(regionId)) |= (0x01u <<  chNum);
    }
    else
    {
         /* Interrupt Enable Clear Register (IECRH)                               */
         HWREG(baseAdd + EDMA3CC_S_IECRH(regionId)) |= (0x01u << (chNum - 32));
    }
}

/**
 *  \brief   Enables the user to Clear an Interrupt.
 *
 *  \param   baseAdd                Memory address of the EDMA instance used.
 *
 *  \param   value                  Value to be set to clear the Interrupt Status.
 *
 *  \return  None
 *
 */
void EDMA3ClrIntr(unsigned int baseAdd, unsigned int value)
{
    if(value < 32)
    {
         HWREG(baseAdd + EDMA3CC_S_ICR(regionId)) = (1u << value);
    }
    else
    {
         HWREG(baseAdd + EDMA3CC_S_ICRH(regionId)) = (1u << (value - 32));
    }
}


/**
 *  \brief   Retrieve existing PaRAM set associated with specified logical
 *           channel (DMA/Link).
 *  
 *  \param   baseAdd                Memory address of the EDMA instance used.\n
 *  
 *  \param   chNum                  Logical Channel whose PaRAM set is
 *                                  requested.\n
 *  
 *  \param   currPaRAM              User gets the existing PaRAM here.\n
 *  
 *  \return  None
 */
void EDMA3GetPaRAM(unsigned int baseAdd, 
                   unsigned int PaRAMId, 
                   EDMA3CCPaRAMEntry* currPaRAM)
{
    unsigned int i = 0;
    unsigned int *sr;
    unsigned int *ds = (unsigned int *)currPaRAM;

    sr = (unsigned int *)(baseAdd + EDMA3CC_OPT(PaRAMId));

    for(i=0;i<EDMA3CC_PARAM_ENTRY_FIELDS;i++)
    {
        *ds++ = *sr++;
    }
}

/**
 * \brief   Retrieve existing PaRAM set associated with specified logical
 *          channel (QDMA).
 * 
 * \param   baseAdd                Memory address of the EDMA instance used.\n
 * 
 * \param   chNum                  Logical Channel whose PaRAM set is
 *                                 requested.\n
 * 
 * \param   currPaRAM              User gets the existing PaRAM here.\n
 * 
 * \return  None
 */
void EDMA3QdmaGetPaRAM(unsigned int baseAdd, 
                       unsigned int chNum,
                       unsigned int paRAMId, 
                       EDMA3CCPaRAMEntry* currPaRAM)
{
    unsigned int i = 0;
    unsigned int *sr;
    unsigned int *ds = (unsigned int *)currPaRAM;

    sr = (unsigned int *)(baseAdd + EDMA3CC_OPT(paRAMId));

    for(i=0;i<EDMA3CC_PARAM_ENTRY_FIELDS;i++)
    {
        *ds=*sr;
        ds++;
        sr++;
    }
}

/**
 * \brief   Copy the user specified PaRAM Set onto the PaRAM Set associated 
 *          with the logical channel (DMA/Link).
 *
 * This API takes a PaRAM Set as input and copies it onto the actual PaRAM Set
 * associated with the logical channel. OPT field of the PaRAM Set is written
 * first and the CCNT field is written last.
 *
 *
 * \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 * \param   chNum                  Logical Channel whose PaRAM set is
 *                                 requested.\n
 *
 * \param   newPaRAM               Parameter RAM set to be copied onto existing
 *                                 PaRAM.\n
 *
 * \return  None
 */
void EDMA3SetPaRAM(unsigned int baseAdd, 
                   unsigned int chNum,
                   EDMA3CCPaRAMEntry* newPaRAM)
{
    unsigned int PaRAMId = chNum; /* PaRAM mapped to channel Number         */
    unsigned int i = 0;
    unsigned int *sr = (unsigned int *)newPaRAM;
    volatile unsigned int *ds;
 
    ds = (unsigned int *)(baseAdd + EDMA3CC_OPT(PaRAMId));

    for(i=0; i < EDMA3CC_PARAM_ENTRY_FIELDS; i++)
    {
        *ds = *sr;
        ds++;
        sr++;
    }
}

/**
 * \brief   Copy the user specified PaRAM Set onto the PaRAM Set associated 
 *          with the logical channel (QDMA only).
 *
 * This API takes a PaRAM Set as input and copies it onto the actual PaRAM Set
 * associated with the logical channel. OPT field of the PaRAM Set is written
 * first and the CCNT field is written last.
 *
 *
 * \param   baseAdd                Memory address of the EDMA instance used.\n
 *
 * \param   chNum                  Logical Channel whose PaRAM set is
 *                                 requested.\n
 *
 * \param  paRaMID                 PaRAM Id to which the QDMA channel is
 *                        mapped to. 
 *
 * \param   newPaRAM               Parameter RAM set to be copied onto existing
 *                                 PaRAM.\n
 *
 * \return  None
 */
void EDMA3QdmaSetPaRAM(unsigned int baseAdd, 
                       unsigned int chNum,
                       unsigned int paRAMId,
                       EDMA3CCPaRAMEntry* newPaRAM)
{
    unsigned int i = 0;
    unsigned int *sr = (unsigned int *)newPaRAM;
    unsigned int *ds;
 
    ds = (unsigned int *)(baseAdd + EDMA3CC_OPT(paRAMId));

    for(i=0;i<EDMA3CC_PARAM_ENTRY_FIELDS;i++)
    {
        *ds=*sr;
         ds++;
         sr++;
    }
}

/**
 * \brief   Set a particular PaRAM set entry of the specified PaRAM set
 *
 * \param   baseAdd           Memory address of the EDMA instance used.\n
 *
 * \param   paRaMID           PaRAM Id to which the QDMA channel is
 *                            mapped to.
 *
 * \param   paRAMEntry        Specify the PaRAM set entry which needs
 *                            to be set.
 *
 * \param   newPaRAMEntryVal  The new field setting. Make sure this field is 
 *                            packed for setting certain fields in paRAM.
 *
 *  paRAMEntry can have values:
 *
 *  EDMA3CC_PARAM_ENTRY_OPT
 *  EDMA3CC_PARAM_ENTRY_SRC
 *  EDMA3CC_PARAM_ENTRY_ACNT_BCNT
 *  EDMA3CC_PARAM_ENTRY_DST
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_BIDX
 *  EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX
 *  EDMA3CC_PARAM_ENTRY_CCNT
 * 
 * \return  None
 *
 * \note    This API should be used while setting the PaRAM set entry
 *          for QDMA channels. If EDMA3QdmaSetPaRAMEntry() used,
 *          it will trigger the QDMA channel before complete
 *          PaRAM set entry is written.
 */
void EDMA3QdmaSetPaRAMEntry(unsigned int baseAdd,
                            unsigned int paRAMId,
                            unsigned int paRAMEntry,
                            unsigned int newPaRAMEntryVal)
{
    if((paRAMEntry > EDMA3CC_PARAM_ENTRY_OPT) || 
            (paRAMEntry < EDMA3CC_PARAM_ENTRY_CCNT))
    {
        HWREG(baseAdd + EDMA3CC_OPT(paRAMId) + 
                    (unsigned int)(paRAMEntry * 0x04)) = newPaRAMEntryVal;
    }
}

/**
 * \brief   Get a particular PaRAM entry of the specified PaRAM set
 *
 * \param   baseAdd           Memory address of the EDMA instance used.\n
 *
 * \param   paRaMID           PaRAM Id to which the QDMA channel is
 *                            mapped to.
 *
 * \param   paRAMEntry        Specify the PaRAM set entry which needs
 *                            to be read.
 *
 *  paRAMEntry can have values:
 *
 *  EDMA3CC_PARAM_ENTRY_OPT
 *  EDMA3CC_PARAM_ENTRY_SRC
 *  EDMA3CC_PARAM_ENTRY_ACNT_BCNT
 *  EDMA3CC_PARAM_ENTRY_DST
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_BIDX
 *  EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX
 *  EDMA3CC_PARAM_ENTRY_CCNT
 *
 * \return  paRAMEntryVal     The value of the paRAM field pointed by the  
 *                            paRAMEntry.
 *
 * \note    This API should be used while reading the PaRAM set entry
 *          for QDMA channels. And the paRAMEntryVal is a packed value for
 *          certain fields of paRAMEntry.The user has to make sure the value 
 *          is unpacked appropriately.
 *          For example, the third field is A_B_CNT. Hence he will have to
 *          unpack it to two 16 bit fields to get ACNT and BCNT.
 */
unsigned int EDMA3QdmaGetPaRAMEntry(unsigned int baseAdd,
                                    unsigned int paRAMId,
                                    unsigned int paRAMEntry)
{
    unsigned int paRAMEntryVal = 0;
    if((paRAMEntry > EDMA3CC_PARAM_ENTRY_OPT) ||
            (paRAMEntry < EDMA3CC_PARAM_ENTRY_CCNT))
    {
        paRAMEntryVal = HWREG(baseAdd + EDMA3CC_OPT(paRAMId) +
                                (unsigned int)(paRAMEntry * 0x04));
    }
    return(paRAMEntryVal);
}

/**
 *  \brief Request a DMA/QDMA/Link channel.
 *
 *  Each channel (DMA/QDMA/Link) must be requested  before initiating a DMA
 *  transfer on that channel.
 *
 *  This API is used to allocate a logical channel (DMA/QDMA/Link) along with
 *  the associated resources. For DMA and QDMA channels, TCC and PaRAM Set are
 *  also allocated along with the requested channel.
 *  
 *  User can request a specific logical channel by passing the channel number
 *  in 'chNum'.
 *  
 *  For DMA/QDMA channels, after allocating all the EDMA3 resources, this API
 *  sets the TCC field of the OPT PaRAM Word with the allocated TCC. It also sets
 *  the event queue for the channel allocated. The event queue needs to be
 *  specified by the user.
 *  
 *  For DMA channel, it also sets the DCHMAP register.
 *  
 *  For QDMA channel, it sets the QCHMAP register and CCNT as trigger word and
 *  enables the QDMA channel by writing to the QEESR register.
 *
 *  \param  baseAdd                  Memory address of the EDMA instance used.\n
 *
 *  \param  chtype                   (DMA/QDMA) Channel
 *                                    For Example: For DMA it is
 *                                    EDMA3_CHANNEL_TYPE_DMA.\n
 *
 *  \param  chNum                    This is the channel number requested for a
 *                                   particular event.\n
 *
 *  \param  tccNum                   The channel number on which the
 *                                   completion/error interrupt is generated.
 *                                   Not used if user requested for a Link
 *                                   channel.\n
 *
 *  \param  evtQNum                  Event Queue Number to which the channel
 *                                   will be mapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  \return  TRUE if parameters are valid, else FALSE
 */
unsigned int EDMA3RequestChannel(unsigned int baseAdd, 
                                 unsigned int chType, 
                                 unsigned int chNum, 
                                 unsigned int tccNum, 
                                 unsigned int evtQNum)
{
    unsigned int retVal = FALSE;
    if (chNum < SOC_EDMA3_NUM_DMACH)
    {
        /* Enable the DMA channel in the enabled in the shadow region
         * specific register
         */
        EDMA3EnableChInShadowReg(baseAdd, chType, chNum);

        EDMA3MapChToEvtQ( baseAdd, chType, chNum, evtQNum);
        if (EDMA3_CHANNEL_TYPE_DMA == chType)
        {
            /* Interrupt channel nums are < 32 */
            if (tccNum < SOC_EDMA3_NUM_DMACH)
            {
            /* Enable the Event Interrupt                             */
                EDMA3EnableEvtIntr(baseAdd, chNum);
                retVal = TRUE;
            }
            HWREG(baseAdd + EDMA3CC_OPT(chNum)) &= EDMA3CC_OPT_TCC_CLR;
            HWREG(baseAdd + EDMA3CC_OPT(chNum)) |= EDMA3CC_OPT_TCC_SET(tccNum);
        }
        else if (EDMA3_CHANNEL_TYPE_QDMA== chType)
        {
            /* Interrupt channel nums are < 8 */
            if (tccNum < SOC_EDMA3_NUM_QDMACH)
            {
                /* Enable the Event Interrupt                             */
                EDMA3EnableEvtIntr(baseAdd, chNum);
                retVal = TRUE;
            } 
            HWREG(baseAdd + EDMA3CC_OPT(chNum)) &= EDMA3CC_OPT_TCC_CLR;
            HWREG(baseAdd + EDMA3CC_OPT(chNum)) |= EDMA3CC_OPT_TCC_SET(tccNum);
        }
    }
    return retVal;
}

/**
 *  \brief    Free the specified channel (DMA/QDMA/Link) and its associated
 *            resources (PaRAM Set, TCC etc) and removes various mappings.
 *  
 *  For Link channels, this API only frees the associated PaRAM Set.
 *  
 *  For DMA/QDMA channels, it does the following operations:
 *  1) Disable any ongoing transfer on the channel,\n
 *  2) Remove the channel to Event Queue mapping,\n
 *  3) For DMA channels, clear the DCHMAP register, if available\n
 *  4) For QDMA channels, clear the QCHMAP register,\n
 *  5) Frees the DMA/QDMA channel in the end.\n
 *
 *  \param  baseAdd                  Memory address of the EDMA instance used.\n
 *
 *  \param  chtype              (DMA/QDMA) Channel
 *                     For Example: For QDMA it is,
 *                     EDMA3_CHANNEL_TYPE_QDMA.\n
 *
 *  \param  chNum                    This is the channel number requested for a
 *                      particular event.\n
 *
 *  \param  trigMode                 Mode of triggering start of transfer.\n
 *
 *  \param  tccNum                   The channel number on which the
 *                                   completion/error interrupt is generated.
 *                                   Not used if user requested for a Link
 *                                   channel.\n
 *
 *  \param  evtQNum                  Event Queue Number to which the channel
 *                                   will be unmapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  trigMode can have values:
 *        EDMA3_TRIG_MODE_MANUAL\n
 *        EDMA3_TRIG_MODE_QDMA\n
 *        EDMA3_TRIG_MODE_EVENT
 *
 *  \return  TRUE if parameters are valid else return FALSE
 */
unsigned int EDMA3FreeChannel(unsigned int baseAdd, unsigned int chType, 
                              unsigned int chNum, unsigned int trigMode,
                              unsigned int tccNum, unsigned int evtQNum)
{
    unsigned int retVal = FALSE;
    if (chNum < SOC_EDMA3_NUM_DMACH)
    {
        EDMA3DisableTransfer(baseAdd, chNum, trigMode);
        /* Disable the DMA channel in the shadow region specific register 
         */
        EDMA3DisableChInShadowReg(baseAdd, chType, chNum);

        EDMA3UnmapChToEvtQ( baseAdd, chType, chNum);
        if (EDMA3_CHANNEL_TYPE_DMA == chType)
        {
            /* Interrupt channel nums are < 32 */
            if (tccNum < SOC_EDMA3_NUM_DMACH)
            {
            /* Disable the DMA Event Interrupt                            */
                EDMA3DisableEvtIntr(baseAdd, chNum);
                retVal = TRUE;
            }
        }
        else if (EDMA3_CHANNEL_TYPE_QDMA== chType)
        {
            /* Interrupt channel nums are < 8 */
            if (tccNum < SOC_EDMA3_NUM_QDMACH)
            {
                /* Disable the QDMA Event Interrupt                           */
                EDMA3DisableEvtIntr(baseAdd, chNum);
                retVal = TRUE;
            }
        }
    }
    return retVal;
}

/**
 *  \brief    Start EDMA transfer on the specified channel.
 *
 *  There are multiple ways to trigger an EDMA3 transfer. The triggering mode
 *  option allows choosing from the available triggering modes: Event,
 *  Manual or QDMA.
 *  
 *  In event triggered, a peripheral or an externally generated event triggers
 *  the transfer. This API clears the Event and Event Miss Register and then
 *  enables the DMA channel by writing to the EESR.
 *  
 *  In manual triggered mode, CPU manually triggers a transfer by writing a 1
 *  in the Event Set Register ESR. This API writes to the ESR to start the 
 *  transfer.
 *  
 *  In QDMA triggered mode, a QDMA transfer is triggered when a CPU (or other
 *  EDMA3 programmer) writes to the trigger word of the QDMA channel PaRAM set
 *  (auto-triggered) or when the EDMA3CC performs a link update on a PaRAM set
 *  that has been mapped to a QDMA channel (link triggered). This API enables
 *  the QDMA channel by writing to the QEESR register.
 *
 *  \param  baseAdd         Memory address of the EDMA instance used.\n
 *
 *  \param  chNum           Channel being used to enable transfer.\n
 *
 *  \param  trigMode        Mode of triggering start of transfer (Manual,
 *                          QDMA or Event).\n
 *
 *  trigMode can have values:
 *        EDMA3_TRIG_MODE_MANUAL\n
 *        EDMA3_TRIG_MODE_QDMA\n
 *        EDMA3_TRIG_MODE_EVENT\n
 *
 *  \return  retVal         TRUE or FALSE depending on the param passed.\n
 *
 */
unsigned int EDMA3EnableTransfer(unsigned int baseAdd, 
                                 unsigned int chNum, 
                                 unsigned int trigMode)
{
    unsigned int retVal = FALSE;
    switch (trigMode)
    {
        case EDMA3_TRIG_MODE_MANUAL :
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                EDMA3SetEvt(baseAdd, chNum);
                retVal = TRUE;
            }
           break;
    
        case EDMA3_TRIG_MODE_QDMA :
            if (chNum < SOC_EDMA3_NUM_QDMACH)
            {
                EDMA3EnableQdmaEvt(baseAdd, chNum);
                retVal = TRUE;
            }
        break;
    
        case EDMA3_TRIG_MODE_EVENT :
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                /*clear SECR & EMCR to clean any previous NULL request    */
                EDMA3ClrMissEvt(baseAdd, chNum);

                /* Set EESR to enable event                               */
                EDMA3EnableDmaEvt(baseAdd, chNum);
                retVal = TRUE;
            }
        break;
    
        default :
            retVal = FALSE;
        break;
    }
    return retVal;
}

/**
 *  \brief   Disable DMA transfer on the specified channel
 *  
 *  There are multiple ways by which an EDMA3 transfer could be triggered.
 *  The triggering mode option allows choosing from the available triggering
 *  modes.
 *  
 *  To disable a channel which was previously triggered in manual mode,
 *  this API clears the Secondary Event Register and Event Miss Register,
 *  if set, for the specific DMA channel.
 *  
 *  To disable a channel which was previously triggered in QDMA mode, this
 *  API clears the QDMA Event Enable Register, for the specific QDMA channel.
 *  
 *  To disable a channel which was previously triggered in event mode, this API
 *  clears the Event Enable Register, Event Register, Secondary Event Register
 *  and Event Miss Register, if set, for the specific DMA channel.
 *
 *
 *  \param  baseAdd         Memory address of the EDMA instance used.\n
 *
 *  \param  chNum           Channel being used to enable transfer.\n
 *
 *  \param  trigMode        Mode of triggering start of transfer (Manual,
 *                          QDMA or Event).\n
 *
 *  trigMode can have values:
 *        EDMA3_TRIG_MODE_MANUAL
 *        EDMA3_TRIG_MODE_QDMA
 *        EDMA3_TRIG_MODE_EVENT
 *
 *  \return  retVal         TRUE or FALSE depending on the param passed.\n
 *
 */
unsigned int EDMA3DisableTransfer(unsigned int baseAdd, 
                                  unsigned int chNum, 
                                  unsigned int trigMode)
{
    unsigned int retVal = FALSE;
    switch (trigMode)
    {
        case EDMA3_TRIG_MODE_MANUAL :
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                EDMA3ClrEvt(baseAdd, chNum);
                retVal = TRUE;
            }
        break;
    
        case EDMA3_TRIG_MODE_QDMA :
            if (chNum < SOC_EDMA3_NUM_QDMACH)
            {
                EDMA3DisableQdmaEvt(baseAdd, chNum);
                retVal = TRUE;
            }
        break;
    
        case EDMA3_TRIG_MODE_EVENT :
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                /*clear SECR & EMCR to clean any previous NULL request    */
                EDMA3ClrMissEvt(baseAdd, chNum);

                /* Set EESR to enable event                               */
                EDMA3DisableDmaEvt(baseAdd, chNum);
                retVal = TRUE;
            }
        break;
    
        default :
            retVal = FALSE;
        break;
    }
    return retVal;
}


/**
 *  \brief  Clears Event Register and Error Register for a specific
 *          DMA channel and brings back EDMA3 to its initial state.
 *
 *  This API clears the Event register, Event Miss register, Event Enable
 *  register for a specific DMA channel. It also clears the CC Error register.
 *
 *  \param  baseAdd         Memory address of the EDMA instance used.\n
 *
 *  \param  chNum           This is the channel number requested for a
 *                          particular event.\n
 *
 *  \param  evtQNum         Event Queue Number to which the channel
 *                          will be unmapped (valid only for the
 *                          Master Channel (DMA/QDMA) request).\n
 *
 *  \return none.\n
 */
void EDMA3ClearErrorBits(unsigned int baseAdd, 
             unsigned int chNum, 
             unsigned int evtQNum)
{
    if(chNum < SOC_EDMA3_NUM_DMACH)
    {
         if(chNum < 32)
         {
              HWREG(baseAdd + EDMA3CC_S_EECR(regionId)) = (0x01u << chNum);
              /* Write to EMCR to clear the corresponding EMR bit */
              HWREG(baseAdd + EDMA3CC_EMCR) = (0x01u << chNum);
              /* Clears the SER */
              HWREG(baseAdd + EDMA3CC_S_SECR(regionId)) = (0x01u << chNum);
         }
         else
         {
              HWREG(baseAdd + EDMA3CC_S_EECRH(regionId)) = (0x01u << (chNum - 32));
              /* Write to EMCR to clear the corresponding EMR bit */
              HWREG(baseAdd + EDMA3CC_EMCRH) = (0x01u << (chNum - 32));
              /* Clears the SER */
              HWREG(baseAdd + EDMA3CC_S_SECRH(regionId)) = (0x01u << (chNum - 32));
         }

    }

    /* Clear the global CC Error Register */
    if (0 == evtQNum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD0 | 
                                EDMA3CC_CCERRCLR_TCCERR);
    }
    else if(1 == evtQNum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD1 | 
                                EDMA3CC_CCERRCLR_TCCERR);
    }
    else if(2 == evtQNum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD2 | 
                                EDMA3CC_CCERRCLR_TCCERR);
    }
    else if(3 == evtQNum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD2 | 
                                EDMA3CC_CCERRCLR_TCCERR);
    }
}

/**
 *  \brief   This API enables to evaluate the subsequent errors. On writing 
 *           to the EEVAL register EDMA3CC error interrupt will be reasserted, 
 *           if there are any outstanding error bits set due to subsequent 
 *           error conditions.
 *
 *  \param  baseAddr         Memory address of the EDMA instance used.
 *
 *  \return  None
 */
void EDMA3CCErrorEvaluate(unsigned int baseAddr)
{
    HWREG(baseAddr + EDMA3CC_EEVAL) = 
                            EDMA3CC_EEVAL_EVAL << EDMA3CC_EEVAL_EVAL_SHIFT;
}

/**
 *  \brief   EDMA3 Deinitialization
 *  
 *  This function deinitializes the EDMA3 Driver
 *  Clears the error specific registers (EMCR/EMCRh, QEMCR, CCERRCLR) &
 *  deinitialize the Queue Number Registers
 *  
 *  \param  baseAdd         Memory address of the EDMA instance used.\n
 *  
 *  \param  queNum          Event Queue used 
 *  
 *  \return  None
 *  
 *  \note     The regionId is the shadow region(0 or 1) used and the,
 *            Event Queue used is either (0 or 1). There are only two shadow regions
 *            and only two event Queues
 */
void EDMA3Deinit(unsigned int baseAdd,
                 unsigned int queNum)
{
    unsigned int count = 0;

    /* Disable the DMA (0 - 62) channels in the DRAE register */
    HWREG(baseAdd + EDMA3CC_DRAE(regionId)) = EDMA3_CLR_ALL_BITS;
    HWREG(baseAdd + EDMA3CC_DRAEH(regionId)) = EDMA3_CLR_ALL_BITS;
    
    EDMA3ClrCCErr(baseAdd, EDMA3CC_CLR_TCCERR);
    
    /* Clear the Event miss Registers                      */
    HWREG(baseAdd + EDMA3CC_EMCR)  = EDMA3_SET_ALL_BITS;
    HWREG(baseAdd + EDMA3CC_EMCRH) = EDMA3_SET_ALL_BITS;

    /* Clear CCERR register */
    HWREG(baseAdd + EDMA3CC_CCERRCLR) = EDMA3_SET_ALL_BITS;

    /* Deinitialize the Queue Number Registers */
    for (count = 0;count < SOC_EDMA3_NUM_DMACH; count++)
    {
        HWREG(baseAdd + EDMA3CC_DMAQNUM(count >> 3u)) &= EDMA3CC_DMAQNUM_CLR(count);
    }

    for (count = 0;count < SOC_EDMA3_NUM_QDMACH; count++)
    {
        HWREG(baseAdd + EDMA3CC_QDMAQNUM) &= EDMA3CC_QDMAQNUM_CLR(count);
    }
}

/**
 *  \brief   This API can be used to save the register context for EDMA
 *
 *  \param  baseAdd         Memory address of the EDMA instance used.\n
 *
 *  \param  edmaCntxPtr     Pointer to the structure where the context
 *                          needs to be saved.
 *
 *  \return  None
 */
void EDMA3ContextSave(unsigned int baseAddr, EDMACONTEXT *edmaCntxPtr)
{
    unsigned int i;
    unsigned int maxPar;

    /* Get the Channel mapping reg Val */
    
    for(i = 0; i < 64; i++)
    {
         /* All events are one to one mapped with the channels */        
         edmaCntxPtr->dchMap[i] = HWREG(baseAddr + EDMA3CC_DCHMAP(i));
    }
      
    /* Get DMA Queue Number Register Val */
    for(i=0; i < 8; i++)
    {    
        edmaCntxPtr->dmaQNum[i] = HWREG(baseAddr + EDMA3CC_DMAQNUM((i)));    
    }         

    /* Get the DMA Region Access Enable Register val */
               
    edmaCntxPtr->regAccEnableLow = HWREG(baseAddr + EDMA3CC_DRAE(0));            
    edmaCntxPtr->regAccEnableHigh = HWREG(baseAddr + EDMA3CC_DRAEH(0));            
    
    /* Get Event Set Register value */
        
    edmaCntxPtr->eventSetRegLow  = HWREG(baseAddr + EDMA3CC_S_ESR(0));                
    edmaCntxPtr->eventSetRegHigh = HWREG(baseAddr + EDMA3CC_S_ESRH(0));                    
                  
    /* Get Event Enable Set Register value */
      
    edmaCntxPtr->enableEvtSetRegLow = HWREG(baseAddr + EDMA3CC_S_EER(0));                   
    edmaCntxPtr->enableEvtSetRegHigh = HWREG(baseAddr + EDMA3CC_S_EERH(0));                       
          
    /* Get Interrupt Enable Set Register value */
           
    edmaCntxPtr->intEnableSetRegLow =  HWREG(baseAddr + EDMA3CC_S_IER(0));                    
    edmaCntxPtr->intEnableSetRegHigh =  HWREG(baseAddr + EDMA3CC_S_IERH(0));                        

    maxPar = 128;

    if((EDMA_REVID_AM335X == EDMAVersionGet()))
    {
        maxPar = 256;
    }

    for(i = 0; i < maxPar; i++)
    {
        /* Get the  PaRAM  values */            
        EDMA3GetPaRAM(baseAddr, i, 
                      (struct EDMA3CCPaRAMEntry *)(&(edmaCntxPtr->dmaParEntry[i])));
    }	                      
}

/**
 *  \brief   This API can be used to restore the register context for EDMA
 *
 *  \param  baseAdd         Memory address of the EDMA instance used.\n
 *
 *  \param  edmaCntxPtr     Pointer to the structure where the context
 *                          needs to be restored from.
 *
 *  \return  None
 */
void EDMA3ContextRestore(unsigned int baseAddr, EDMACONTEXT *edmaCntxPtr)
{
    unsigned int i;
    unsigned int maxPar;
    
    /* set the Channel mapping reg Val */
    for(i = 0; i < 64; i++)
    {
         /* All events are one to one mapped with the channels */        
         HWREG(baseAddr + EDMA3CC_DCHMAP(i)) = edmaCntxPtr->dchMap[i] ;
    }
      
    /* set DMA Queue Number Register Val */
    for(i=0; i < 8; i++)
    {    
	HWREG(baseAddr + EDMA3CC_DMAQNUM((i))) = edmaCntxPtr->dmaQNum[i];    
    }         

    /* set the DMA Region Access Enable Register val */
               
    HWREG(baseAddr + EDMA3CC_DRAE(0)) = edmaCntxPtr->regAccEnableLow;
    HWREG(baseAddr + EDMA3CC_DRAEH(0)) = edmaCntxPtr->regAccEnableHigh;            
    
    /* set Event Set Register value */
    HWREG(baseAddr + EDMA3CC_S_ESR(0)) = edmaCntxPtr->eventSetRegLow;                
    HWREG(baseAddr + EDMA3CC_S_ESRH(0)) = edmaCntxPtr->eventSetRegHigh;                    
                  
    /* set Event Enable Set Register value */
    HWREG(baseAddr + EDMA3CC_S_EESR(0)) = edmaCntxPtr->enableEvtSetRegLow;                   
    HWREG(baseAddr + EDMA3CC_S_EESRH(0)) = edmaCntxPtr->enableEvtSetRegHigh;                       
          
    /* set Interrupt Enable Set Register value */
    HWREG(baseAddr + EDMA3CC_S_IESR(0)) = edmaCntxPtr->intEnableSetRegLow;                    
    HWREG(baseAddr + EDMA3CC_S_IESRH(0)) = edmaCntxPtr->intEnableSetRegHigh;                        

    maxPar = 128;

    if((EDMA_REVID_AM335X == EDMAVersionGet()))
    {
        maxPar = 256;
    }

    for(i = 0; i < maxPar; i++)
    {
        /* Get the  PaRAM  values */            
        EDMA3SetPaRAM(baseAddr, i, 
             (struct EDMA3CCPaRAMEntry *)(&(edmaCntxPtr->dmaParEntry[i])));
    }	                   
}

/********************************* End of file ******************************/
