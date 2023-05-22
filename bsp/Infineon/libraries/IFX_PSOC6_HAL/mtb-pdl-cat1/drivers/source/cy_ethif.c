/***************************************************************************//**
* \file cy_ethif.c
* \version 1.0
*
* Provides an API implementation of the ETHIF driver
*
********************************************************************************
* \copyright
* Copyright 2021 Cypress Semiconductor Corporation
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

#include "cy_ethif.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.1', 42, 'Overrunning array expected.');
CY_MISRA_DEVIATE_BLOCK_START('OVERRUN', 43, 'Overrunning array expected.');


/***************************************
*       Local Variables
***************************************/
/** Cadence driver instantiation    */
static CEDI_OBJ *cyp_ethif_gemgxlobj;

/** Ethernet configurations */
static CEDI_Config  cy_ethif_cfg[CY_ETH_DEFINE_NUM_IP];

/** Cadence driver memory requirements */
static CEDI_SysReq  cy_ethif_sysreq;

/** Private data structures required for each instance of Ethernet IPs  */
static CEDI_PrivateData * cyp_ethif_pd[CY_ETH_DEFINE_NUM_IP];

/** Variables holding Statistics register values    */
static CEDI_Statistics  * cyp_ethif_statistic[CY_ETH_DEFINE_NUM_IP];

/** Private data memory allocation  */
static uint8_t cy_ethif_privatedata[CY_ETH_DEFINE_NUM_IP][1800] = {{0,},};

/** Tx descriptors */
/** CY_ETH_DEFINE_NUM_TXQS * CY_ETH_DEFINE_NUM_IP to avoid race condition in hardware; each BD list for particular queue must have 1 more BD */
CY_SECTION_SHAREDMEM
CY_ALIGN(32) static uint8_t cy_ethif_tx_desc_list[CY_ETH_DEFINE_NUM_IP][CY_ETH_DEFINE_NUM_TXQS][CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE + 1][CY_ETH_BD_SIZE] = {{{{0,},},},};

/** Rx descriptors */
/** Cadence driver requires another set of buffers to replace the existing
* buffers after a frame has been received. so, number of required BDs would not
* be same as number of buffers */
CY_SECTION_SHAREDMEM
CY_ALIGN(32) static uint8_t cy_ethif_rx_desc_list[CY_ETH_DEFINE_NUM_IP][CY_ETH_DEFINE_NUM_RXQS][((CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE + 1) * 2)][CY_ETH_BD_SIZE] = {{{{0,},},},};

/** Statistics registers    */
static uint8_t cy_ethif_statistic[CY_ETH_DEFINE_NUM_IP][160] = {{0,},};

static cy_stc_ethif_cb_t stccallbackfunctions[CY_ETH_DEFINE_NUM_IP] = {{NULL, NULL, NULL, NULL, NULL},};
static cy_stc_ethif_queue_disablestatus_t stcQueueDisStatus[CY_ETH_DEFINE_NUM_IP] = {{{0,},{0,}},};
CY_SECTION_SHAREDMEM
CY_ALIGN(32) static volatile uint8_t g_tx_bdcount[CY_ETH_DEFINE_NUM_IP] = {0,};

/*****************************************************************************
* Local function prototypes ('static')
*****************************************************************************/
static void Cy_ETHIF_EnableInterrupts(uint8_t u8EthIfInstance, cy_stc_ethif_intr_config_t * pstcInterruptList);
static void Cy_ETHIF_PrepareConfiguration(uint8_t u8EthIfInstance, cy_stc_ethif_mac_config_t * pstcEthIfConfig);
static void Cy_ETHIF_AssignMemory(uint8_t u8EthIfInstance);
static uint8_t Cy_ETHIF_GetEthIfInstance(void *pcy_privatedata);
static void Cy_ETHIF_EventTx(void *pcy_privatedata, uint32_t u32event, uint8_t u8qnum);
static void Cy_ETHIF_EventTxError(void *pcy_privatedata, uint32_t u32event, uint8_t u8qnum);
static void Cy_ETHIF_EventRxFrame(void *pcy_privatedata, uint8_t u8qnum);
static void Cy_ETHIF_EventRxError(void *pcy_privatedata, uint32_t a_event, uint8_t a_qnum);
static void Cy_ETHIF_EventPhyManComplete(void *pcy_privatedata, uint8_t u8read, uint16_t u16ReadData);
static void Cy_ETHIF_EventhrespError(void *pcy_privatedata, uint8_t u8qnum);
static void Cy_ETHIF_EventLpPageRx(void* pcy_privatedata, struct CEDI_LpPageRx* pageRx);
static void Cy_ETHIF_EventAn(void* pcy_privatedata, struct CEDI_NetAnStatus* netStat);
static void Cy_ETHIF_EventLinkChange(void *pcy_privatedata, uint8_t a_linkstate);
static void Cy_ETHIF_EventTsu(void *pcy_privatedata, uint32_t u32event);
static void Cy_ETHIF_EventPauseFrame(void *pcy_privatedata, uint32_t u32event);
static void Cy_ETHIF_EventPtp(void* pcy_privatedata, uint32_t u32type, struct CEDI_1588TimerVal* time);
static void Cy_ETHIF_EventExternalInt(void * pcy_privatedata);
static void Cy_ETHIF_EventWol(void * pcy_privatedata);
static void Cy_ETHIF_EventLpi(void * pcy_privatedata);
static void Cy_ETHIF_InitializeBuffers(void);
static cy_en_ethif_status_t Cy_ETHIF_WrapperConfig(uint8_t u8EthIfInstance, cy_stc_ethif_wrapper_config_t * pstcWrapperConfig);
static void Cy_ETHIF_IPEnable(ETH_Type *base);
static void Cy_ETHIF_IPDisable(ETH_Type *base);
static cy_en_ethif_status_t Cy_ETHIF_TSUInit(uint8_t u8EthIfInstance, cy_stc_ethif_tsu_config_t * pstcTSUConfig);
static cy_en_ethif_status_t Cy_ETHIF_DisableQueues(ETH_Type *base, cy_stc_ethif_mac_config_t * pstcEthIfConfig);

/*****************************************************************************
* Local Call back function supplied to Cadence driver
*****************************************************************************/
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 8.4', 1, 'Intentional definition');
CEDI_Callbacks Cy_ETHIF_Callbacks = {
  .phyManComplete = (CEDI_CbPhyManComplete)Cy_ETHIF_EventPhyManComplete,
  .txEvent        = (CEDI_CbTxEvent)Cy_ETHIF_EventTx,
  .txError        = (CEDI_CbTxError)Cy_ETHIF_EventTxError,
  .rxFrame        = (CEDI_CbRxFrame)Cy_ETHIF_EventRxFrame,
  .rxError        = (CEDI_CbRxError)Cy_ETHIF_EventRxError,
  .hrespError     = (CEDI_CbHrespError)Cy_ETHIF_EventhrespError,
  .lpPageRx       = (CEDI_CbLpPageRx)Cy_ETHIF_EventLpPageRx,
  .anComplete     = (CEDI_CbAnComplete)Cy_ETHIF_EventAn,
  .linkChange     = (CEDI_CbLinkChange)Cy_ETHIF_EventLinkChange,
  .tsuEvent       = (CEDI_CbTsuEvent)Cy_ETHIF_EventTsu,
  .pauseEvent     = (CEDI_CbPauseEvent)Cy_ETHIF_EventPauseFrame,
  .ptpPriFrameTx  = (CEDI_CbPtpPriFrameTx)Cy_ETHIF_EventPtp,
  .ptpPeerFrameTx = (CEDI_CbPtpPeerFrameTx)Cy_ETHIF_EventPtp,
  .ptpPriFrameRx  = (CEDI_CbPtpPriFrameRx)Cy_ETHIF_EventPtp,
  .ptpPeerFrameRx = (CEDI_CbPtpPeerFrameRx)Cy_ETHIF_EventPtp,
  .lpiStatus      = (CEDI_CbLpiStatus)Cy_ETHIF_EventLpi,
  .wolEvent       = (CEDI_CbWolEvent)Cy_ETHIF_EventWol,
  .extInpIntr     = (CEDI_CbExtInpIntr)Cy_ETHIF_EventExternalInt
};
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.4');

/*******************************************************************************
* Function Name: Cy_ETHIF_MdioInit
****************************************************************************//**
*
* \brief Initializes the Ethernet MAC with minimal parameters which is required to
*        enable mdio interface.
*
* \param base
* Pointer to register area of Ethernet MAC
*
* \param pstcEthIfConfig
* Pointer to Ethernet configuration parameters
*
* \return CY_ETHIF_SUCCESS      Ethernet MAC has been initialized along with
*                               Cadence driver and external PHY
* \return CY_ETHIF_BAD_PARAM    If following conditions are met:
*                               pstcEth == NULL
*                               pstcEthIfConfig == NULL
*                               GEM_GXL Object could not be created.
*
* \note
* This function Initializes the Ethernet MAC partially. This function is only
* required if user wants to access PHY registers before \ref Cy_ETHIF_Init().
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_MdioInit(ETH_Type *base, cy_stc_ethif_mac_config_t * pstcEthIfConfig)
{
    uint8_t u8EthIfInstance;
    uint32_t u32RetValue;
    cy_en_ethif_status_t status = CY_ETHIF_SUCCESS;

    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base) || (pstcEthIfConfig == NULL))
    {
        return CY_ETHIF_BAD_PARAM;
    }
    else if (pstcEthIfConfig->pstcWrapperConfig == NULL)
    {
        return CY_ETHIF_BAD_PARAM;
    }
    else
    {
        /**/
    }

    cyp_ethif_gemgxlobj = CEDI_GetInstance();
    if (cyp_ethif_gemgxlobj == NULL)
    {
        status = CY_ETHIF_BAD_PARAM;
    }

    if (status == CY_ETHIF_SUCCESS)
    {
        /** Load the Ethernet instance */
        u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

        /* Load Init parameter */
        Cy_ETHIF_PrepareConfiguration(u8EthIfInstance, pstcEthIfConfig);

        /* Initialize ENET MAC Wrapper */
        if (CY_ETHIF_BAD_PARAM == Cy_ETHIF_WrapperConfig(u8EthIfInstance, pstcEthIfConfig->pstcWrapperConfig))
        {
            Cy_ETHIF_IPDisable(base);
            return CY_ETHIF_BAD_PARAM;
        }

        /* Enable the IP to access EMAC registers set */
        Cy_ETHIF_IPEnable(base);

        /* assign starting addresses to local variable */
        Cy_ETHIF_AssignMemory(u8EthIfInstance);

        /* Initialization EMAC registers */
        u32RetValue = cyp_ethif_gemgxlobj->init((void *)cyp_ethif_pd[u8EthIfInstance], &cy_ethif_cfg[u8EthIfInstance], &Cy_ETHIF_Callbacks);
        if (u32RetValue == ((uint32_t)EINVAL) || u32RetValue == ((uint32_t)ENOTSUP))
        {
            Cy_ETHIF_IPDisable(base);
            return CY_ETHIF_BAD_PARAM;
        }

        /* Enable MDIO */
        cyp_ethif_gemgxlobj->setMdioEnable((void *)(void *)cyp_ethif_pd[u8EthIfInstance], CY_ETH_ENABLE_1);
    }
    return status;
}



/*******************************************************************************
* Function Name: Cy_ETHIF_Init
****************************************************************************//**
*
* \brief Initializes the Ethernet MAC, Cadence Driver, EthIf and PHY
*
* \param base
* Pointer to register area of Ethernet MAC
*
* \param pstcEthIfConfig
* Pointer to Ethernet configuration parameters
*
* \param pstcInterruptList
* List of Interrupts to enable
*
* \return CY_ETHIF_SUCCESS      Ethernet MAC has been initialized along with
*                               Cadence driver and external PHY
* \return CY_ETHIF_BAD_PARAM    If following conditions are met:
*                               pstcEth == NULL
*                               pstcEthIfConfig == NULL
*                               pstcInterruptList == NULL
*                               GEM_GXL Object could not be created
*                               Memory assigned by Interface layer is not enough
*                               Cadence driver could not initialize Ethernet MAC
* \return CY_ETHIF_MEMORY_NOT_ENOUGH
*                               Assigned memory for BDs or for Private data is
*                               not enough
*
* \note
* This function Initializes the Ethernet MAC, Cadence driver, EthIf layer and
* external PHY with the provided parameters. Port init for the Ethernet must be
* done before calling Cy_ETHIF_Init function. Buffer configuration parameters
* shall be done in cy_ethif.h file
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_Init(ETH_Type *base, cy_stc_ethif_mac_config_t * pstcEthIfConfig, cy_stc_ethif_intr_config_t * pstcInterruptList)
{
    // local variable declaration
    uint32_t u32RetValue = 0;
    uint8_t u8EthIfInstance = 255;
    uint8_t u8tmpcounter = 0;
    uint8_t u8tmpintrcntr = 0;
    uint16_t u16SysReqTxBDLength = 0;
    uint16_t u16SysReqRxBDLength = 0;
    static bool bBufferInitialized = false;
    CEDI_BuffAddr rx_buff_addr;

    /* Parameter checks */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base) || (pstcEthIfConfig == NULL) || (pstcInterruptList == NULL))
    {
        return CY_ETHIF_BAD_PARAM;
    }
    else if (pstcEthIfConfig->pstcWrapperConfig == NULL)
    {
        return CY_ETHIF_BAD_PARAM;
    }
    else
    {
        /**/
    }

    if (bBufferInitialized == false)
    {
        /* Create GEM_GXL object  */
        cyp_ethif_gemgxlobj = CEDI_GetInstance();
        if (cyp_ethif_gemgxlobj == NULL)
        {
            return CY_ETHIF_BAD_PARAM;
        }
    }

    /** Load the Ethernet instance */
    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    /* Load Init parameter */
    Cy_ETHIF_PrepareConfiguration(u8EthIfInstance, pstcEthIfConfig);

    if (pstcEthIfConfig->bintrEnable == true)
    {
        /* Configure Interrupts */
        Cy_ETHIF_EnableInterrupts(u8EthIfInstance, pstcInterruptList);

        /* Init Callback functions */
        stccallbackfunctions[u8EthIfInstance].rxframecb       = NULL;
        stccallbackfunctions[u8EthIfInstance].txerrorcb       = NULL;
        stccallbackfunctions[u8EthIfInstance].txcompletecb    = NULL;
        stccallbackfunctions[u8EthIfInstance].tsuSecondInccb  = NULL;
        stccallbackfunctions[u8EthIfInstance].rxgetbuff  = NULL;
    }

    /* Initialize ENET MAC Wrapper */
    if (CY_ETHIF_BAD_PARAM == Cy_ETHIF_WrapperConfig(u8EthIfInstance, pstcEthIfConfig->pstcWrapperConfig))
    {
        Cy_ETHIF_IPDisable(base);
        return CY_ETHIF_BAD_PARAM;
    }

    /* Enable the IP to access EMAC registers set */
    Cy_ETHIF_IPEnable(base);

    /* Probe for checking configuration parameters and calculating memory size */
    (void)cyp_ethif_gemgxlobj->probe(&cy_ethif_cfg[u8EthIfInstance], &cy_ethif_sysreq);

    /* Check for assigned memory and required memory match */
    u16SysReqTxBDLength = (uint16_t)((cy_ethif_sysreq.txDescListSize /  CY_ETH_DEFINE_NUM_TXQS)/(CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE + 1U));
    u16SysReqRxBDLength = (uint16_t)((cy_ethif_sysreq.rxDescListSize /  CY_ETH_DEFINE_NUM_RXQS)/(CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE + 1U));

    if ((u16SysReqTxBDLength != CY_ETH_BD_SIZE) || (u16SysReqRxBDLength != CY_ETH_BD_SIZE))
    {
        /* Memory not enough */
        return CY_ETHIF_MEMORY_NOT_ENOUGH;
    }

    /* assign starting addresses to local variable */
    Cy_ETHIF_AssignMemory(u8EthIfInstance);

    if (sizeof(cy_ethif_privatedata[u8EthIfInstance])< cy_ethif_sysreq.privDataSize)
    {
        /* Memory not enough */
        return CY_ETHIF_MEMORY_NOT_ENOUGH;
    }


    /* Initialization EMAC registers */
    u32RetValue = cyp_ethif_gemgxlobj->init((void *)cyp_ethif_pd[u8EthIfInstance], &cy_ethif_cfg[u8EthIfInstance], &Cy_ETHIF_Callbacks);
    if (u32RetValue == ((uint32_t)EINVAL) || u32RetValue == ((uint32_t)ENOTSUP))
    {
        Cy_ETHIF_IPDisable(base);
        return CY_ETHIF_BAD_PARAM;
    }

    /* Disable Transmit and Receive Queues */
    (void)Cy_ETHIF_DisableQueues(base, pstcEthIfConfig);

    /* TSU Initialization */
    if (NULL != pstcEthIfConfig->pstcTSUConfig)
    {
        if (CY_ETHIF_BAD_PARAM == Cy_ETHIF_TSUInit(u8EthIfInstance, pstcEthIfConfig->pstcTSUConfig))
        {
            Cy_ETHIF_IPDisable(base);
            return CY_ETHIF_BAD_PARAM;
        }
    }

    /* Initialize Buffer status */
    if (bBufferInitialized == false)
    {
        Cy_ETHIF_InitializeBuffers();
        bBufferInitialized = true;
    }

    for (u8tmpcounter = 0; u8tmpcounter < cy_ethif_cfg[u8EthIfInstance].rxQs; u8tmpcounter++)
    {
        if (pstcEthIfConfig->pRxQbuffPool[u8tmpcounter] != NULL)
        {
            for (u8tmpintrcntr = 0; u8tmpintrcntr < cy_ethif_cfg[u8EthIfInstance].rxQLen[u8tmpcounter]; u8tmpintrcntr++)
            {
                rx_buff_addr.vAddr = (uintptr_t)((*pstcEthIfConfig->pRxQbuffPool)[u8tmpcounter][u8tmpintrcntr]);
                rx_buff_addr.pAddr = rx_buff_addr.vAddr;
                (void)cyp_ethif_gemgxlobj->addRxBuf((void *)cyp_ethif_pd[u8EthIfInstance],
                                                u8tmpcounter,
                                            (CEDI_BuffAddr *)&rx_buff_addr,
                                                0);
            }
        }
    }


    /* additional Receive configurations */
    cyp_ethif_gemgxlobj->setCopyAllFrames((void *)cyp_ethif_pd[u8EthIfInstance], CY_ETH_ENABLE_1);
    cyp_ethif_gemgxlobj->setRxBadPreamble((void *)cyp_ethif_pd[u8EthIfInstance], CY_ETH_ENABLE_1);

    /* Do not drop frames with CRC error */
    cyp_ethif_gemgxlobj->setIgnoreFcsRx((void *)cyp_ethif_pd[u8EthIfInstance], CY_ETH_ENABLE_1);

    // Optional: Setting Filter configuration
    // Optional: setting screen registers

    /* Enable MDIO */
    cyp_ethif_gemgxlobj->setMdioEnable((void *)(void *)cyp_ethif_pd[u8EthIfInstance], CY_ETH_ENABLE_1);
    /* driver start */
    cyp_ethif_gemgxlobj->start((void *)cyp_ethif_pd[u8EthIfInstance]);

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_RegisterCallbacks
****************************************************************************//**
*
* \brief Function loads callback functions to its local data structures.
*        The callback functions are called from ISR context.
*
* \param base
* Pointer to register area of Ethernet MAC
*
* \param cbFuncsList pointer to callback function list
*
*******************************************************************************/
void Cy_ETHIF_RegisterCallbacks(ETH_Type *base, cy_stc_ethif_cb_t *cbFuncsList)
{
    uint8_t u8EthIfInstance;
    /* Load the Ethernet instance */
    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    /* Load Callback functions */
    stccallbackfunctions[u8EthIfInstance].rxframecb       = cbFuncsList->rxframecb;
    stccallbackfunctions[u8EthIfInstance].txerrorcb       = cbFuncsList->txerrorcb;
    stccallbackfunctions[u8EthIfInstance].txcompletecb    = cbFuncsList->txcompletecb;
    stccallbackfunctions[u8EthIfInstance].tsuSecondInccb  = cbFuncsList->tsuSecondInccb;
    stccallbackfunctions[u8EthIfInstance].rxgetbuff       = cbFuncsList->rxgetbuff;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_TransmitFrame
****************************************************************************//**
*
* \brief Function initiates transmission of frame data
*
* \param base
* Pointer to register area of Ethernet MAC
*
* \param pu8TxBuffer pointer to Transmit source buffer. Its caller's responsibility to
*                    make sure this buffer is not overwritten until transmit is not
*                    completed. \ref Cy_ETHIF_RegisterCallbacks for Tx completion callback.
* \param u16Length Length of data to transmit from source buffer, Length should include source
*                  and destination buffer address. CRC bytes shall not be included in the length
* \param u8QueueIndex Queue to be used to transmit the frame
* \param bEndBuffer True - Last buffer of the frame to be transmitted.
*                   False - Other Buffers to be provided after function call
*                           IP will not start transmitting until it gets EndBuffer True.
*
* \return CY_ETHIF_SUCCESS Frame transmission started
* \return CY_ETHIF_BAD_PARAM Parameter passed contains invalid values
* \return CY_ETHIF_BUFFER_NOT_AVAILABLE Buffer not available to load the source data
*
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_TransmitFrame(ETH_Type *base, uint8_t * pu8TxBuffer, uint16_t u16Length, uint8_t u8QueueIndex, bool bEndBuffer)
{
    uint8_t u8EthIfInstance;
    uint8_t u8flags = 0;
    uint32_t u32result = 0;
    CEDI_BuffAddr tmpBuffAdd;

    /* Check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    /* Check for arguments */
    if ((pu8TxBuffer == NULL) || (u16Length > CY_ETH_SIZE_MAX_FRAME) || (u8QueueIndex > CY_ETH_QS2_2))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    /* Check requested queue enabled or not */
    if (stcQueueDisStatus[u8EthIfInstance].bTxQueueDisable[u8QueueIndex] == true)
    {
        /* Requested Queue is disabled */
        return CY_ETHIF_BAD_PARAM;
    }

    tmpBuffAdd.pAddr = (uintptr_t)pu8TxBuffer;
    tmpBuffAdd.vAddr = tmpBuffAdd.pAddr;

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    SCB_CleanDCache_by_Addr((void*) (tmpBuffAdd.pAddr), (int32_t)u16Length);
#endif /* (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE) */

    /* Typecast bEndBuffer to Flag type    */
    // TODO: adapt function for CEDI_TXB_NO_AUTO_CRC and CEDI_TXB_NO_AUTO_START
    if (bEndBuffer == true)
    {
        u8flags = CEDI_TXB_LAST_BUFF;
    }

    /* Clear transmit status register before begin to transmit */
    cyp_ethif_gemgxlobj->clearTxStatus((void *)cyp_ethif_pd[u8EthIfInstance], CY_ETHIF_TX_STATUS_CLEAR);

    g_tx_bdcount[u8EthIfInstance]++;

    /* wait until tx done successfully */
    while (g_tx_bdcount[u8EthIfInstance] > CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE)
    {
        /* Do Nothing */
        //Cy_SysLib_DelayUs(1);
    }

    /* Trigger Internal transmit function  */
    u32result = cyp_ethif_gemgxlobj->queueTxBuf((void *)cyp_ethif_pd[u8EthIfInstance],
                                       u8QueueIndex,
                                       (CEDI_BuffAddr*)&tmpBuffAdd,
                                       u16Length,
                                       u8flags);
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

    if (0UL != u32result)
    {
        /* error   */
        return CY_ETHIF_BAD_PARAM;
    }

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_TxPauseFrame
****************************************************************************//**
*
* \brief Transmits IEEE 802.3X standard Pause Frame
*
* \param base
* Pointer to register area of Ethernet MAC
*
* \param bZeroTQ  True - Zero Time Quanta
*        bZeroTQ  False - Transmit pause frame with set time quanta
*
* \return CY_ETHIF_SUCCESS for success
* \return CY_ETHIF_BAD_PARAM for wrong input parameters
* \note If interrupt enabled, interrupt will be triggered at the end of the transmission
*
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_TxPauseFrame(ETH_Type *base, bool bZeroTQ)
{
    uint8_t u8EthIfInstance;
    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    if (bZeroTQ == true)
    {
        /* trigger Pause frame with Zero Time Quanta */
        cyp_ethif_gemgxlobj->txZeroQPause((void *)cyp_ethif_pd[u8EthIfInstance]);
    }
    else
    {
        cyp_ethif_gemgxlobj->txPauseFrame((void *)cyp_ethif_pd[u8EthIfInstance]);
    }

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_ConfigPause
****************************************************************************//**
*
* \brief Configures the Pause Frame transmission according to IEEE 802.3X standard
*
* \param base
* Pointer to register area of Ethernet MAC
* \param u16PauseQuanta Time Quanta
*
* \return CY_ETHIF_SUCCESS for success
* \return CY_ETHIF_BAD_PARAM for wrong input parameters
*
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_ConfigPause(ETH_Type *base, uint16_t u16PauseQuanta)
{
    uint8_t u8EthIfInstance;
    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    /* Set Tx Pause Quanta for Priority 0   */
    if (((uint32_t)EOK) != cyp_ethif_gemgxlobj->setTxPauseQuantum((void *)cyp_ethif_pd[u8EthIfInstance], u16PauseQuanta, CY_ETHIF_PAUSE_P0))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    /* Enable Receive Pause Frames */
    cyp_ethif_gemgxlobj->setCopyPauseDisable((void *)cyp_ethif_pd[u8EthIfInstance], CY_ETH_DISABLE_0);

    /* Enable Pause Frames */
    cyp_ethif_gemgxlobj->setPauseEnable((void *)cyp_ethif_pd[u8EthIfInstance], CY_ETH_ENABLE_1);

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_SetNoBroadCast
****************************************************************************//**
*
* \brief Enable/Disable receive of broadcast frames
*
* \param base
* Pointer to register area of Ethernet MAC
*
* \param rejectBC if =0 broadcasts are accepted, if =1 they are rejected.
*
*******************************************************************************/
void Cy_ETHIF_SetNoBroadCast(ETH_Type *base, bool rejectBC)
{
    uint8_t u8EthIfInstance;
    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        CY_ASSERT(0UL);
    }
    else
    {
        u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

        cyp_ethif_gemgxlobj->setNoBroadcast((void *)cyp_ethif_pd[u8EthIfInstance],rejectBC);
    }
}


/*******************************************************************************
* Function Name: Cy_ETHIF_SetPromiscuousMode
****************************************************************************//**
*
* \brief Enable/Disable to capture all frames
*
* \param  base Pointer to register area of Ethernet MAC
* \param  toBeEnabled if =1 enables copy all frames mode, if =0 then this is disabled
*
*******************************************************************************/
void Cy_ETHIF_SetPromiscuousMode(ETH_Type *base, bool toBeEnabled)
{
    uint8_t u8EthIfInstance;
    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        CY_ASSERT(0UL);
    }
    else
    {
        u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

        cyp_ethif_gemgxlobj->setCopyAllFrames((void *)cyp_ethif_pd[u8EthIfInstance],toBeEnabled);
    }
}

/*******************************************************************************
* Function : Cy_ETHIF_SetFilterAddress
****************************************************************************//**
*
* \brief Set Filter Address with specific filter number
*
* \param base Pointer to register area of Ethernet MAC
*
* \param  filterNo Filter number
*         config Filter configuration for Ethernet MAC
*
* \param  config config
*
* \return CY_ETHIF_SUCCESS Filter is set
* \return CY_ETHIF_BAD_PARAM Parameter passed contains invalid values
*
* \note
* Maximum 4 filters can be set
*
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_SetFilterAddress(ETH_Type *base, cy_en_ethif_filter_num_t filterNo, const cy_stc_ethif_filter_config_t* config)
{
    uint8_t u8EthIfInstance;
    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    if(filterNo >= CY_ETHIF_FILTER_NUM_INV)
    {
        return CY_ETHIF_BAD_PARAM;
    }

    if(config == NULL)
    {
        return CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    /* add some address filters */

    CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 1, 'Intentional typecast of &config->filterAddr to CEDI_MacAddress* struct type.');
    (void)cyp_ethif_gemgxlobj->setSpecificAddr((void *)cyp_ethif_pd[u8EthIfInstance],
                                        filterNo,
                                        (CEDI_MacAddress*)&config->filterAddr,
                                        config->typeFilter,
                                        config->ignoreBytes);
    CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_PhyRegRead
****************************************************************************//**
*
* \brief Local function used by other APIs to read the PHY register.
*
* \param base
* Pointer to register area of Ethernet MAC
*
* \param u8RegNo Register to read
*
* \param u8PHYAddr u8PHYAddr
*
* \return read data from the register
*
* \note
* CY_ETH_PHY_ADDR must match with PHY.
* PHY data-sheet and hardware schematic shall be checked
*
*******************************************************************************/
uint32_t Cy_ETHIF_PhyRegRead(ETH_Type *base, uint8_t u8RegNo, uint8_t u8PHYAddr)
{
    uint32_t    u32result;
    uint16_t    u16ReadData;
    uint8_t u8EthIfInstance;

    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return (uint32_t)CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    cyp_ethif_gemgxlobj->phyStartMdioRead( (void *)cyp_ethif_pd[u8EthIfInstance], CY_ETHIF_PHY_FLAG, u8PHYAddr, u8RegNo);

    while(cyp_ethif_gemgxlobj->getMdioIdle((void *)cyp_ethif_pd[u8EthIfInstance]) != CY_ETH_MDIO_BUSY_0)
    {
        /* poll till operation completes */
    }

    /* additional wait before read data */
    Cy_SysLib_DelayUs(800);

    u32result = cyp_ethif_gemgxlobj->getMdioReadData((void *)cyp_ethif_pd[u8EthIfInstance], &u16ReadData);
    if (0UL != u32result)
    {
        u16ReadData = 0;
        CY_ASSERT(0UL);
    }

    return (uint32_t)u16ReadData;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_PhyRegWrite
****************************************************************************//**
*
* \brief Local function used by other APIs to write the PHY register
*
* \param base Pointer to register area of Ethernet MAC
* \param u8RegNo Register to write
* \param u16Data data to write
* \param u8PHYAddr u8PHYAddr
*
* \return CY_ETHIF_SUCCESS Filter is set
* \return CY_ETHIF_BAD_PARAM Parameter passed contains invalid values
*
* \note
* u8PHYAddr must match with PHY.
* PHY data-sheet and hardware schematic shall be checked
*
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_PhyRegWrite(ETH_Type *base, uint8_t u8RegNo, uint16_t u16Data, uint8_t u8PHYAddr)
{
    uint8_t u8EthIfInstance;

    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    cyp_ethif_gemgxlobj->phyStartMdioWrite( (void *)cyp_ethif_pd[u8EthIfInstance], CY_ETHIF_PHY_FLAG, u8PHYAddr, u8RegNo, u16Data );
    /* poll till operation completes */
    while (cyp_ethif_gemgxlobj->getMdioIdle((void *)cyp_ethif_pd[u8EthIfInstance]) != CY_ETH_MDIO_BUSY_0)
    {
        /* */
    }

    /* additional wait */
    Cy_SysLib_DelayUs(200);
    return CY_ETHIF_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_ETHIF_GetTimerValue
****************************************************************************//**
*
* \brief Returns the current timer value from TSU register
*
* \param base Pointer to register area of Ethernet MAC
* \param stcRetTmrValue [out] pointer to data structure to return the values
*
* \return CY_ETHIF_SUCCESS Filter is set
* \return CY_ETHIF_BAD_PARAM Parameter passed contains invalid values
*
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_Get1588TimerValue(ETH_Type *base, cy_stc_ethif_1588_timer_val_t *stcRetTmrValue)
{
    uint8_t u8EthIfInstance;

    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    if (stcRetTmrValue == NULL)
    {
        return CY_ETHIF_BAD_PARAM;
    }

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional typecast of stcRetTmrValue to CEDI_1588TimerVal* struct type.');
    (void)cyp_ethif_gemgxlobj->get1588Timer((void *)cyp_ethif_pd[u8EthIfInstance], (CEDI_1588TimerVal*)stcRetTmrValue);

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_SetTimerValue
****************************************************************************//**
*
* \brief Setting the current timer value in TSU register
*
* \param base Pointer to register area of Ethernet MAC
* \param pstcTmrValue pointer to data structure to configure register with
*
* \return CY_ETHIF_SUCCESS Filter is set
* \return CY_ETHIF_BAD_PARAM Parameter passed contains invalid values
*
*******************************************************************************/
cy_en_ethif_status_t Cy_ETHIF_Set1588TimerValue(ETH_Type *base, cy_stc_ethif_1588_timer_val_t *pstcTmrValue)
{
    uint8_t u8EthIfInstance;

    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        return CY_ETHIF_BAD_PARAM;
    }

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    if (pstcTmrValue == NULL)
    {
        return CY_ETHIF_BAD_PARAM;
    }

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional typecast of stcRetTmrValue to CEDI_1588TimerVal* struct type.');
    if (((uint32_t)EOK) != cyp_ethif_gemgxlobj->set1588Timer((void *)cyp_ethif_pd[u8EthIfInstance], (CEDI_1588TimerVal*)pstcTmrValue))
    {
        /* Reason could be Null pointer, hardware does not support TSU or pstcTimerValue.nanosecs>0x3FFFFFFF */
        return CY_ETHIF_BAD_PARAM;
    }

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_DecodeEvent
****************************************************************************//**
*
* \brief Interrupt handler for a particular Ethernet instance. It decodes the
* interrupt cause and calls the appropriate registered callback functions.
*
* \param base Pointer to register area of Ethernet MAC
*
*******************************************************************************/
void Cy_ETHIF_DecodeEvent(ETH_Type *base)
{
    uint8_t u8EthIfInstance;

    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        CY_ASSERT(0UL);
    }
    else
    {
        u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

        (void)cyp_ethif_gemgxlobj->isr((void *)cyp_ethif_pd[u8EthIfInstance]);
    }
}


/*******************************************************************************
* Function Name: Cy_ETHIF_DiscardNonVLANFrames
****************************************************************************//**
*
* \brief With VLAN tagged frame processing setup, this function configure
* MAC to receive only VLAN tagged frames and discard all.
*
* \param base Pointer to Ethernet Instance
* \param enable if =1 reject non-VLAN-tagged frames, if =0 then accept
*
*******************************************************************************/
void Cy_ETHIF_DiscardNonVLANFrames(ETH_Type *base, bool enable)
{
    uint8_t u8EthIfInstance;

    /* check for arguments */
    if (!CY_ETHIF_IS_IP_INSTANCE_VALID(base))
    {
        CY_ASSERT(0UL);
    }
    else
    {
        u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

        cyp_ethif_gemgxlobj->setVlanOnly((void *)cyp_ethif_pd[u8EthIfInstance], (uint8_t)(enable ? 1 : 0));
    }

}


/*##############################################################################
 *      Internal Functions
 *############################################################################*/


/*******************************************************************************
* Function Name: Cy_ETHIF_EnableInterrupts
****************************************************************************//**
*
* \brief Function initializes enabled Interrupt
*
* \param u8EthIfInstance Ethernet Instance
* \param pstcInterruptList pointer to structure list
*
*******************************************************************************/
static void Cy_ETHIF_EnableInterrupts (uint8_t u8EthIfInstance, cy_stc_ethif_intr_config_t * pstcInterruptList)
{
    uint32_t u32InterruptEn = 0;

    if (pstcInterruptList->btsu_time_match == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_TSU_TIME_MATCH);
    }
    if (pstcInterruptList->bwol_rx == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_WOL_RX);
    }
    if (pstcInterruptList->blpi_ch_rx == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_LPI_CH_RX);
    }
    if (pstcInterruptList->btsu_sec_inc == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_TSU_SEC_INC);
    }
    if (pstcInterruptList->bptp_tx_pdly_rsp == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_TX_PDLY_RSP);
    }
    if (pstcInterruptList->bptp_tx_pdly_req == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_TX_PDLY_REQ);
    }
    if (pstcInterruptList->bptp_rx_pdly_rsp == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_RX_PDLY_RSP);
    }
    if (pstcInterruptList->bptp_rx_pdly_req == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_RX_PDLY_REQ);
    }
    if (pstcInterruptList->bptp_tx_sync == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_TX_SYNC);
    }
    if (pstcInterruptList->bptp_tx_dly_req == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_TX_DLY_REQ);
    }
    if (pstcInterruptList->bptp_rx_sync == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_RX_SYNC);
    }
    if (pstcInterruptList->bptp_rx_dly_req == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PTP_RX_DLY_REQ);
    }
    if (pstcInterruptList->bpause_frame_tx == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PAUSE_FRAME_TX);
    }
    if (pstcInterruptList->bpause_time_zero == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PAUSE_TIME_ZERO);
    }
    if (pstcInterruptList->bpause_nz_qu_rx == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_PAUSE_NZ_QU_RX);
    }
    if (pstcInterruptList->bhresp_not_ok == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_HRESP_NOT_OK);
    }
    if (pstcInterruptList->brx_overrun == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_RX_OVERRUN);
    }
    if (pstcInterruptList->btx_complete == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_TX_COMPLETE);
    }
    if (pstcInterruptList->btx_fr_corrupt == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_TX_FR_CORRUPT);
    }
    if (pstcInterruptList->btx_retry_ex_late_coll == true)
    {
        u32InterruptEn |=((uint32_t)CEDI_EV_TX_RETRY_EX_LATE_COLL);
    }
    if (pstcInterruptList->btx_underrun == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_TX_UNDERRUN);
    }
    if (pstcInterruptList->btx_used_read == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_TX_USED_READ);
    }
    if (pstcInterruptList->brx_used_read == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_RX_USED_READ);
    }
    if (pstcInterruptList->brx_complete == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_RX_COMPLETE);
    }
    if (pstcInterruptList->bman_frame == true)
    {
        u32InterruptEn |= ((uint32_t)CEDI_EV_MAN_FRAME);
    }

    cy_ethif_cfg[u8EthIfInstance].intrEnable = u32InterruptEn;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_PrepareConfiguration
****************************************************************************//**
*
* \brief prepares configuration based on the parameter passed to Cy_ETHIF_Init
* function. This prepared configuration which is dedicated for specific Ethernet
* instance would be used to initialize Ethernet MAC
*
* \param u8EthIfInstance Ethernet Instance
* \param config Pointer to Ethernet configuration passed from Application layer
*
*******************************************************************************/
static void Cy_ETHIF_PrepareConfiguration(uint8_t u8EthIfInstance, cy_stc_ethif_mac_config_t * pstcEthIfConfig )
{
    uint8_t u8QueueCounter = 0u;

    #if defined(CY_IP_MXETH_INSTANCES) && (CY_IP_MXETH_INSTANCES > 1u)
    CY_ASSERT(u8EthIfInstance <= 1u);
    #else
    CY_ASSERT(u8EthIfInstance == 0u);
    #endif

    /** Clear configuration table   */
    (void)memset((void *)&cy_ethif_cfg[u8EthIfInstance], 0, sizeof(cy_ethif_cfg[u8EthIfInstance]));

    /** Load GEM_GXL register base address  */
    cy_ethif_cfg[u8EthIfInstance].regBase = CY_ETHIF_GEMGXL_ADDR_REGBASE(u8EthIfInstance);
     //(u8EthIfInstance == CY_ETHIF_INSTANCE_0) ? CY_ETH0_GEMGXL_ADDR_REGBASE : CY_ETH1_GEMGXL_ADDR_REGBASE;

    /** Prepare Queues  */
    cy_ethif_cfg[u8EthIfInstance].rxQs = CY_ETH_DEFINE_NUM_RXQS;
    cy_ethif_cfg[u8EthIfInstance].txQs = CY_ETH_DEFINE_NUM_TXQS;

    for (u8QueueCounter=0; u8QueueCounter<cy_ethif_cfg[u8EthIfInstance].rxQs; u8QueueCounter++) {
        cy_ethif_cfg[u8EthIfInstance].rxQLen[u8QueueCounter] = CY_ETH_DEFINE_TOTAL_BD_PER_RXQUEUE;
    }

    for (u8QueueCounter=0; u8QueueCounter<cy_ethif_cfg[u8EthIfInstance].txQs; u8QueueCounter++) {
        cy_ethif_cfg[u8EthIfInstance].txQLen[u8QueueCounter] = CY_ETH_DEFINE_TOTAL_BD_PER_TXQUEUE;
    }

    /** Prepare Network control Register    */
    cy_ethif_cfg[u8EthIfInstance].pfcMultiQuantum    = 0;                                       /* bit25    pfc_ctrl              */
    cy_ethif_cfg[u8EthIfInstance].enExtTsuPort       = 0;                                       /* bit23    ext_tsu_port_enable, Not supported by hardware  */
    cy_ethif_cfg[u8EthIfInstance].storeUdpTcpOffset  = 0;                                       /* bit22    store_udp_offset      */
    cy_ethif_cfg[u8EthIfInstance].altSgmiiEn         = 0;                                       /* bit21    alt_sgmii_mode, Not supported by hardware       */
    cy_ethif_cfg[u8EthIfInstance].enableMdio         = 0;                                       /* bit4     man_port_en, Bit is separately enabled during MDIO operation  */

    /** Prepare Network Configuration Register    */
    cy_ethif_cfg[u8EthIfInstance].uniDirEnable       = 0;                                       /* bit31    uni_direction_enable, Not supported by hardware    */
    cy_ethif_cfg[u8EthIfInstance].ignoreIpgRxEr      = 0;                                       /* bit30    ignore_ipg_rx_er, Not supported by hardware        */
    cy_ethif_cfg[u8EthIfInstance].enRxBadPreamble    = pstcEthIfConfig->u8enRxBadPreamble;      /* bit29    nsp_change           */
    // cy_ethif_cfg[u8EthIfInstance].ifTypeSel          = pstcEthIfConfig->ifTypeSel;              /* bit27    sgmii_mode_enable  (reserved)  */
                                                                                                /*          (see the following)  */
    // don't care                                                                               /* bit26    ignore_rx_fcs        */
    cy_ethif_cfg[u8EthIfInstance].enRxHalfDupTx      = 0;                                       /* bit25    en_half_duplex_rx, not supported by hardware    */
    cy_ethif_cfg[u8EthIfInstance].chkSumOffEn        = pstcEthIfConfig->u8chkSumOffEn;          /* bit24    receive_checksum_offload_enable */
    cy_ethif_cfg[u8EthIfInstance].disCopyPause       = pstcEthIfConfig->u8disCopyPause;         /* bit23    disable_copy_of_pause_frames */
    #if defined(ETH_AXI_MASTER_PRESENT) && (ETH_AXI_MASTER_PRESENT == 1U)
        cy_ethif_cfg[u8EthIfInstance].dmaBusWidth    = CEDI_DMA_BUS_WIDTH_64;                   /* bit22:21 data bus with        */
    #else
        cy_ethif_cfg[u8EthIfInstance].dmaBusWidth    = CEDI_DMA_BUS_WIDTH_32;                   /* bit22:21 data bus with        */
    #endif
                                                                                                /* 00:32bit 01:64bit    */
    cy_ethif_cfg[u8EthIfInstance].mdcPclkDiv         = (CEDI_MdcClkDiv)pstcEthIfConfig->mdcPclkDiv;             /* bit20:18 mdc_clock_division   */
                                                                                                /*          010: Divide 32       */
                                                                                                /*          011: Divide 48       */
    // don't care                                                                               /* bit17    fcs_remove           */
    cy_ethif_cfg[u8EthIfInstance].rxLenErrDisc       = pstcEthIfConfig->u8rxLenErrDisc;         /* bit16    length_field_error_frame_discard */
    cy_ethif_cfg[u8EthIfInstance].rxBufOffset        = 0;                                       /* bit15:14 receive_buffer_offset */
    // don't care                                                                               /* bit13    pause_enable         */
    // don't care                                                                               /* bit12    retry_test           */
    //cy_ethif_cfg[u8EthIfInstance].ifTypeSel        = pstcEthIfConfig->ifTypeSel               /* bit11    pcs_select (reserved)*/
                                                                                                /*          (see the following)  */
    //cy_ethif_cfg[u8EthIfInstance].ifTypeSel        = pstcEthIfConfig->ifTypeSel               /* bit10    gigabit_mode_enable  */
                                                                                                /*          (see the following)  */
    cy_ethif_cfg[u8EthIfInstance].extAddrMatch       = 0;                                       /* bit9     external_address_match_enable, not supported by hardware */
    cy_ethif_cfg[u8EthIfInstance].rx1536ByteEn       = pstcEthIfConfig->u8rx1536ByteEn;         /* bit8     receive_1536_byte_frames */
    // don't care                                                                               /* bit7     unicast_hash_enable  */
    // don't care                                                                               /* bit6     multicast_hash_enable  */
    // don't care                                                                               /* bit5     no_broadcast         */
    // don't care                                                                               /* bit4     copy_all_frames      */
    cy_ethif_cfg[u8EthIfInstance].rxJumboFrEn        = pstcEthIfConfig->u8rxJumboFrEn;          /* bit3     jumbo_frames         */
    // don't care                                                                               /* bit2     discard_non_vlan_frames */
    cy_ethif_cfg[u8EthIfInstance].fullDuplex         = 1;                                       /* bit1     full_duplex          */
    //cy_ethif_cfg[u8EthIfInstance].ifTypeSel        = pstcEthIfConfig->ifTypeSel               /* bit0     speed                */

    /** configuration for cy_ethif_cfg[u8EthIfInstance].ifTypeSel    */
    if ((pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_MII_10) ||
       (pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RGMII_10) ||
       (pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RMII_10))
    {
       cy_ethif_cfg[u8EthIfInstance].ifTypeSel = CEDI_IFSP_10M_MII;
    }
    else if ((pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_MII_100) ||
        (pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RMII_100) ||
        (pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RGMII_100))
    {
        cy_ethif_cfg[u8EthIfInstance].ifTypeSel = CEDI_IFSP_100M_MII;
    }
    else
    {
        if ((pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_GMII_1000) ||
            (pstcEthIfConfig->pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RGMII_1000))
        {
            cy_ethif_cfg[u8EthIfInstance].ifTypeSel = CEDI_IFSP_1000M_GMII;
        }
        else
        {
            /* */
        }
    }

    /*=================================================================================================*/
    /* CTL.ETH_MODE   | Network_config[0] |  Network_config[10]   |     PHY mode                       */
    /*                |     (speed)       | (gigabit_mode_enable) |                                    */
    /*=================================================================================================*/
    /*       2’d0     |          0        |          0            |   MII - 10Mbps                     */
    /*       2’d0     |          1        |          0            |   MII – 100Mbps                    */
    /*       2’d1     |          0        |          1            |   GMII – 1000Mbps                  */
    /*       2’d2     |          0        |          0            |   RGMII – 10Mbps (4bits/Cycle)     */
    /*       2’d2     |          1        |          0            |   RGMII – 100Mbps (4bits/Cycle)    */
    /*       2’d2     |          0        |          1            |   RGMII – 1000Mbps (8bits/Cycle)   */
    /*       2’d3     |          0        |          0            |   RMII – 10Mbps                    */
    /*       2’d3     |          1        |          0            |   RMII – 100Mbps                   */
    /*=================================================================================================*/

    /** Prepare DMA Config register */
    cy_ethif_cfg[u8EthIfInstance].dmaAddrBusWidth    = 0;                                       /* bit30  DMA address bus width. 0 =32b , 1=64b    */
                                                                                                /* 0:32bit 1:64bit         */
    cy_ethif_cfg[u8EthIfInstance].enTxExtBD          = CY_ETH_DEFINE_BD;                               /* bit29  tx_bd_extended_mode_en  */
    cy_ethif_cfg[u8EthIfInstance].enRxExtBD          = CY_ETH_DEFINE_BD;                               /* bit28  rx_bd_extended_mode_en  */
    cy_ethif_cfg[u8EthIfInstance].dmaCfgFlags        = pstcEthIfConfig->u8dmaCfgFlags;          /* bit26  force_max_amba_burst_tx */
                                                                                                /* bit25  force_max_amba_burst_rx */
                                                                                                /* bit24  force_discard_on_err    */
    for (u8QueueCounter=0; u8QueueCounter<cy_ethif_cfg[u8EthIfInstance].rxQs; u8QueueCounter++) {
        cy_ethif_cfg[u8EthIfInstance].rxBufLength[u8QueueCounter] = CY_ETH_SIZE_BUF_TXQ_RXQ >> 6;            /* bit23:16 rx_buf_size       */
    }

    cy_ethif_cfg[u8EthIfInstance].txPktBufSize       = CY_ETH_TX_PBUF_SIZE;                     /* bit10  tx_pbuf_size            */
    cy_ethif_cfg[u8EthIfInstance].rxPktBufSize       = CY_ETH_RX_PBUF_SIZE;                     /* bit9:8 rx_pbuf_size            */
    cy_ethif_cfg[u8EthIfInstance].dmaEndianism       = 0;                                       /* bit7   endian_swap_packet  */
                                                                                                /*        0: little endian mode */
                                                                                                /*        1: endian swap mode enable for packet data (CEDI_END_SWAP_DATA) */
                                                                                                /* bit6   endian_swap_management   */
                                                                                                /*        0: little endian mode    */
                                                                                                /*        1: endian swap mode enable for management descriptor (CEDI_END_SWAP_DESC) */
    cy_ethif_cfg[u8EthIfInstance].dmaDataBurstLen    = (CEDI_DmaDatBLen)pstcEthIfConfig->dmaDataBurstLen;        /* bit4:0   amba_burst_length                                         */
                                                                                                /* 1xxxx: attempt use burst up to 16 (CEDI_DMA_DBUR_LEN_16)  */
                                                                                                /* 01xxx: attempt use burst up to  8 (CEDI_DMA_DBUR_LEN_8)   */
                                                                                                /* 001xx: attempt use burst up to  4 (CEDI_DMA_DBUR_LEN_4)   */
                                                                                                /* 0001x: always use single burst                            */
                                                                                                /* 00001: always use single burst    (CEDI_AMBD_BURST_LEN_1) */
                                                                                                /* 00000: best AXI burst up to 256 beats                     */

    /** Prepare upper_tx_q_base_addr and upper_rx_q_base_addr register (0x4c8, 0x4D4)   */
    cy_ethif_cfg[u8EthIfInstance].upper32BuffTxQAddr = 0;                                       /* bit31:0  not used              */
    cy_ethif_cfg[u8EthIfInstance].upper32BuffRxQAddr = 0;                                       /* bit31:0  not used              */

    /** axi_max_pipeline register    */
    cy_ethif_cfg[u8EthIfInstance].aw2wMaxPipeline    = pstcEthIfConfig->u8aw2wMaxPipeline;      /* bit15:8  aw2w_max_pipeline     */
    cy_ethif_cfg[u8EthIfInstance].ar2rMaxPipeline    = pstcEthIfConfig->u8ar2rMaxPipeline;      /* bit 7:0  ar2r_max_pipeline     */
}


/*******************************************************************************
* Function Name: Cy_ETHIF_WrapperConfig
****************************************************************************//**
*
* \brief Function initializes Ethernet Wrapper to configure Interface mode, reference clock/divider etc
*
* \param u8EthIfInstance Ethernet Instance
* \param pstcInterruptList pointer to structure list
*
* \return CY_ETHIF_SUCCESS Filter is set
* \return CY_ETHIF_BAD_PARAM Parameter passed contains invalid values
*
*******************************************************************************/
static cy_en_ethif_status_t Cy_ETHIF_WrapperConfig(uint8_t u8EthIfInstance, cy_stc_ethif_wrapper_config_t * pstcWrapperConfig )
{
    ETH_Type *base;
    uint32_t mode, srcSel, clkDiv;

    if (pstcWrapperConfig->stcInterfaceSel > CY_ETHIF_CTL_RMII_100)
    {
        return CY_ETHIF_BAD_PARAM;
    }

    //pstcEthConfig = (u8EthIfInstance == CY_ETHIF_INSTANCE_0) ? (stc_ETH_t*)CY_ETH0_ADDR_REG_BASE : (stc_ETH_t*)CY_ETH1_ADDR_REG_BASE;
    base = CY_ETHIF_IP_ADDR_REGBASE(u8EthIfInstance);

    if ((pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_MII_10) ||
       (pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_MII_100))
    {
       mode = 0;
    }
    else if (pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_GMII_1000)
    {
        mode = 1;
    }
    else if ((pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RGMII_10) ||
            (pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RGMII_100) ||
            (pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RGMII_1000))
    {
        mode = 2;
    }
    else if ((pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RMII_10) ||
            (pstcWrapperConfig->stcInterfaceSel == CY_ETHIF_CTL_RMII_100))
    {
        mode = 3;
    }
    else
    {
        mode = 0;
    }

    srcSel =  (uint32_t)(pstcWrapperConfig->bRefClockSource);
    clkDiv = (((uint32_t)pstcWrapperConfig->u8RefClkDiv) - 1U);        /** NOTE: This bits are not part of eth header file as of now   */

    //pstcEthConfig->unCTL.u32Register = unEthCtl.u32Register;
    ETH_CTL(base) = _VAL2FLD(ETH_CTL_ETH_MODE, mode) |
                    _VAL2FLD(ETH_CTL_REFCLK_SRC_SEL, srcSel) |
                    _VAL2FLD(ETH_CTL_REFCLK_DIV, clkDiv);

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_IPEnable
****************************************************************************//**
*
* \brief Function enables Ethernet MAC
*
* \param base Ethernet Instance
*
*******************************************************************************/
static void Cy_ETHIF_IPEnable(ETH_Type *base)
{
    ETH_CTL(base) |=_VAL2FLD(ETH_CTL_ENABLED, CY_ETH_ENABLE_1);
}

/*******************************************************************************
* Function Name: Cy_ETHIF_IPDisable
****************************************************************************//**
*
* \brief Function Disables Ethernet MAC
*
* \param base Ethernet Instance
*
*******************************************************************************/
static void Cy_ETHIF_IPDisable(ETH_Type *base)
{
    ETH_CTL(base) &= (uint32_t)~(ETH_CTL_ENABLED_Msk);
}

/*******************************************************************************
* Function Name: Cy_ETHIF_AssignMemory
****************************************************************************//**
*
* \brief Local function is used to initialize private data structure, tx and rx queue start address
*
* \param u8EthIfInstance Ethernet Instance number
*
*******************************************************************************/
static void Cy_ETHIF_AssignMemory(uint8_t u8EthIfInstance)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional typecast of cy_ethif_privatedata[u8EthIfInstance] to CEDI_PrivateData* struct type.');
    cyp_ethif_pd[u8EthIfInstance] = (CEDI_PrivateData *)cy_ethif_privatedata[u8EthIfInstance];
    cy_ethif_cfg[u8EthIfInstance].rxQAddr   = (uintptr_t)cy_ethif_rx_desc_list[u8EthIfInstance];
    cy_ethif_cfg[u8EthIfInstance].txQAddr   = (uintptr_t)cy_ethif_tx_desc_list[u8EthIfInstance];
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional typecast of cy_ethif_statistic[u8EthIfInstance] to CEDI_Statistics* struct type.');
    cyp_ethif_statistic[u8EthIfInstance] = (CEDI_Statistics *)cy_ethif_statistic[u8EthIfInstance];
    cy_ethif_cfg[u8EthIfInstance].statsRegs = (uintptr_t)cyp_ethif_statistic[u8EthIfInstance];
    /** get the physical address */
    cy_ethif_cfg[u8EthIfInstance].rxQPhyAddr = cy_ethif_cfg[u8EthIfInstance].rxQAddr;
    /** get the physical address */
    cy_ethif_cfg[u8EthIfInstance].txQPhyAddr = cy_ethif_cfg[u8EthIfInstance].txQAddr;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_DisableQueues
****************************************************************************//**
* \brief By default all activated queues in the IP are enabled. However, only required
* queues for tx and rx shall be enabled to make internal process faster.
*
* \brief Function Disables Ethernet MAC
*
* \param base Ethernet Instance
*
*******************************************************************************/
static cy_en_ethif_status_t Cy_ETHIF_DisableQueues (ETH_Type *base, cy_stc_ethif_mac_config_t * pstcEthIfConfig)
{
    uint8_t u8EthIfInstance;

    u8EthIfInstance = CY_ETHIF_IP_INSTANCE(base);

    /* Transmit Queue 0 */
    if (pstcEthIfConfig->btxq0enable == false)
    {
        /* Disable the queue pointer */
        ETH_TX_Q_PTR(base) = (ETH_TX_Q_PTR(base) & (uint32_t)~(ETH_TRANSMIT_Q_PTR_DMA_TX_DIS_Q_Msk)) | _VAL2FLD(ETH_TRANSMIT_Q_PTR_DMA_TX_DIS_Q, 1UL);
        stcQueueDisStatus[u8EthIfInstance].bTxQueueDisable[0] = true;
    }

    /* Transmit Queue 1 */
    if (pstcEthIfConfig->btxq1enable == false)
    {
        /* Disable the queue pointer */
        ETH_TX_Q1_PTR(base) = (ETH_TX_Q1_PTR(base) & (uint32_t)~(ETH_TRANSMIT_Q1_PTR_DMA_TX_DIS_Q_Msk)) | _VAL2FLD(ETH_TRANSMIT_Q1_PTR_DMA_TX_DIS_Q, 1UL);
        stcQueueDisStatus[u8EthIfInstance].bTxQueueDisable[1] = true;
    }

    /* Transmit Queue 2 */
    if (pstcEthIfConfig->btxq2enable == false)
    {
        /* Disable the queue pointer */
        ETH_TX_Q2_PTR(base) = (ETH_TX_Q2_PTR(base) & (uint32_t)~(ETH_TRANSMIT_Q2_PTR_DMA_TX_DIS_Q_Msk)) | _VAL2FLD(ETH_TRANSMIT_Q2_PTR_DMA_TX_DIS_Q, 1UL);
        stcQueueDisStatus[u8EthIfInstance].bTxQueueDisable[2] = true;
    }

    /* Receive Queue 0 */
    if (pstcEthIfConfig->brxq0enable == false)
    {
        /* Disable the queue pointer */
        ETH_RX_Q_PTR(base) = (ETH_RX_Q_PTR(base) & (uint32_t)~(ETH_RECEIVE_Q_PTR_DMA_RX_DIS_Q_Msk)) | _VAL2FLD(ETH_RECEIVE_Q_PTR_DMA_RX_DIS_Q, 1UL);
        stcQueueDisStatus[u8EthIfInstance].bRxQueueDisable[0] = true;
    }

    /* Receive Queue 1 */
    if (pstcEthIfConfig->brxq1enable == false)
    {
        /* Disable the queue pointer */
        ETH_RX_Q1_PTR(base) = (ETH_RX_Q1_PTR(base) & (uint32_t)~(ETH_RECEIVE_Q1_PTR_DMA_RX_DIS_Q_Msk)) | _VAL2FLD(ETH_RECEIVE_Q1_PTR_DMA_RX_DIS_Q, 1UL);
        stcQueueDisStatus[u8EthIfInstance].bRxQueueDisable[1] = true;
    }

    /* Receive Queue 2 */
    if (pstcEthIfConfig->brxq2enable == false)
    {
        /* Disable the queue pointer */
        ETH_RX_Q2_PTR(base) = (ETH_RX_Q2_PTR(base) & (uint32_t)~(ETH_RECEIVE_Q2_PTR_DMA_RX_DIS_Q_Msk)) | _VAL2FLD(ETH_RECEIVE_Q2_PTR_DMA_RX_DIS_Q, 1UL);
        stcQueueDisStatus[u8EthIfInstance].bRxQueueDisable[2] = true;
    }

    /* TODO: Temporarily in the driver. MUST be removed once IP is updated || Q3 for both Transmit and Receive has been removed from the IP
        Changes will apply to bitfile after 0513 release */

    /* TODO: Idea of cross checking BD memory vs enabled queues */

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_TSUInit
****************************************************************************//**
*
* \brief Function enables Time stamp unit in EMAC
*
* \param pstcTSUConfig Pointer to TSU parameters
*
* \return CY_ETHIF_SUCCESS Filter is set
* \return CY_ETHIF_BAD_PARAM Parameter passed contains invalid values
*
*******************************************************************************/
static cy_en_ethif_status_t Cy_ETHIF_TSUInit (uint8_t u8EthIfInstance, cy_stc_ethif_tsu_config_t * pstcTSUConfig)
{
    /* set 1588 timer value */
    /* Load Timer Value */

    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional typecast of pstcTSUConfig->pstcTimerValue to CEDI_1588TimerVal* struct type.');
    if (((uint32_t)EOK) != cyp_ethif_gemgxlobj->set1588Timer((void *)cyp_ethif_pd[u8EthIfInstance], (CEDI_1588TimerVal*)pstcTSUConfig->pstcTimerValue))
    {
        /* Reason could be Null pointer, hardware does not support TSU or pstcTimerValue.nanosecs>0x3FFFFFFF */
        return CY_ETHIF_BAD_PARAM;
    }

    /* Timer increment register to achieve 1 second as precise as possible */
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional typecast of pstcTSUConfig->pstcTimerIncValue to CEDI_TimerIncrement* struct type.');
    if (((uint32_t)EOK) != cyp_ethif_gemgxlobj->set1588TimerInc((void *)cyp_ethif_pd[u8EthIfInstance], (CEDI_TimerIncrement*)pstcTSUConfig->pstcTimerIncValue))
    {
        /* Reason could be Null pointer, hardware does not support TSU */
        return CY_ETHIF_BAD_PARAM;
    }

    /* one step sync enabled    */
    if (((uint32_t)EOK) != cyp_ethif_gemgxlobj->set1588OneStepTxSyncEnable((void *)cyp_ethif_pd[u8EthIfInstance], (uint8_t) pstcTSUConfig->bOneStepTxSyncEnable))
    {
        /* Reason could be Null pointer, hardware does not support TSU or bOneStepTxSyncEnable > 1 */
        return CY_ETHIF_BAD_PARAM;
    }

    /* Set the descriptor time stamp Mode */
    if (((uint32_t)EOK) != cyp_ethif_gemgxlobj->setDescTimeStampMode((void *)cyp_ethif_pd[u8EthIfInstance],
               (CEDI_TxTsMode)pstcTSUConfig->enTxDescStoreTimeStamp, (CEDI_RxTsMode)pstcTSUConfig->enRxDescStoreTimeStamp))
    {
        /** Reason could be Null pointer, hardware does not support TSU, enTxDescStoreTimeStamp > CEDI_TX_TS_ALL, enRxDescStoreTimeStamp > CEDI_RX_TS_ALL  */
        return CY_ETHIF_BAD_PARAM;
    }

    /* disabled storing nanosecond in CRC field of received frame */
    if (((uint32_t)EOK) != cyp_ethif_gemgxlobj->setStoreRxTimeStamp((void *)cyp_ethif_pd[u8EthIfInstance], (uint8_t) pstcTSUConfig->bStoreNSinRxDesc))
    {
        /* Reason could be Null pointer, hardware does not support TSU or bStoreNSinRxDesc > 1 */
        return CY_ETHIF_BAD_PARAM;
    }

    return CY_ETHIF_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_InitializeBuffers
****************************************************************************//**
*
* \brief Function initializes the buffer status and clears the memory with
*        CY_EHTIF_EMPTYVALUE value.
*
* \param none
*
*******************************************************************************/
static void Cy_ETHIF_InitializeBuffers (void)
{
    for (uint32_t index=0; index<CY_ETH_DEFINE_NUM_IP; index++)
    {
        g_tx_bdcount[index] = 0;
    }
}


/*******************************************************************************
* Function Name: Cy_ETHIF_GetEthIfInstance
****************************************************************************//**
*
* \brief To derive the instance number.
*
* \param pcy_privatedata     Instance specific private data
* \return Ethernet instance (ETH0=0 or ETH1=1)
*
*******************************************************************************/
static uint8_t Cy_ETHIF_GetEthIfInstance(void *pcy_privatedata)
{
    uint8_t u8EthIfInstance = 0U;

    if (pcy_privatedata == cyp_ethif_pd[0])
    {
        u8EthIfInstance = CY_ETHIF_INSTANCE_0;
    }
    else
    {
        #if defined(CY_IP_MXETH_INSTANCES) && (CY_IP_MXETH_INSTANCES > 1u)
            if(pcy_privatedata == cyp_ethif_pd[1])
            {
                u8EthIfInstance = CY_ETHIF_INSTANCE_1;
            }
            else
            {
                CY_ASSERT(0UL);
            }
        #else
        CY_ASSERT(0UL);
        #endif
    }
    return u8EthIfInstance;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventTx
****************************************************************************//**
*
* \brief Function called by cadence driver upon getting Tx Event
*
* \param pcy_privatedata    Instance specific private data
* \param u32event occurred event
* \param u8qnum Queue number
*
*******************************************************************************/
static void Cy_ETHIF_EventTx(void *pcy_privatedata, uint32_t u32event, uint8_t u8qnum)
{
    CEDI_TxDescData Tx_DescData;
    ETH_Type *base;
    uint8_t u8EthIfInstance;

    /** derive the instance */
    u8EthIfInstance = Cy_ETHIF_GetEthIfInstance(pcy_privatedata);

    base = CY_ETHIF_IP_ADDR_REGBASE(u8EthIfInstance);

    if (0UL != (u32event & ((uint32_t)CEDI_EV_TX_COMPLETE)))
    {
        (void)cyp_ethif_gemgxlobj->freeTxDesc((void *)cyp_ethif_pd[u8EthIfInstance], u8qnum, &Tx_DescData);

        g_tx_bdcount[u8EthIfInstance]--;

        /* application callback function */
        if (stccallbackfunctions[u8EthIfInstance].txcompletecb != NULL)
        {
            stccallbackfunctions[u8EthIfInstance].txcompletecb(base, u8qnum);
        }

    }

    return;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventTxError
****************************************************************************//**
*
* \brief Function called by cadence driver upon getting Tx Error Event
*
* \param pcy_privatedata    Instance specific private data
* \param u32event occurred event
* \param u8qnum Queue number
*
*******************************************************************************/
static void Cy_ETHIF_EventTxError(void *pcy_privatedata, uint32_t u32event, uint8_t u8qnum)
{
    CEDI_TxDescData Tx_DescData;
    uint8_t u8EthIfInstance;
    ETH_Type *base;

    /** derive the instance */
    u8EthIfInstance = Cy_ETHIF_GetEthIfInstance(pcy_privatedata);

    base = CY_ETHIF_IP_ADDR_REGBASE(u8EthIfInstance);

    (void)cyp_ethif_gemgxlobj->freeTxDesc((void *)cyp_ethif_pd[u8EthIfInstance], u8qnum, &Tx_DescData);

    /** application callback function */
    if (stccallbackfunctions[u8EthIfInstance].txerrorcb != NULL)
    {
        stccallbackfunctions[u8EthIfInstance].txerrorcb(base, u8qnum);
    }

    g_tx_bdcount[u8EthIfInstance]--;

    CY_UNUSED_PARAMETER(u32event); /* Suppress a compiler warning about unused variables */

    return;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventRxFrame
****************************************************************************//**
*
* \brief Function called by cadence driver upon getting Rx Event
*
* \param pcy_privatedata    Instance specific private data
* \param u8qnum Queue number
*
*******************************************************************************/
static void Cy_ETHIF_EventRxFrame(void *pcy_privatedata, uint8_t u8qnum)
{
    uint32_t        u32RxNum;
    CEDI_BuffAddr   tmpBufAddr;
    CEDI_RxDescData Rx_DescData;
    CEDI_RxDescStat Rx_DescStat;
    uint8_t u8EthIfInstance = 255;
    ETH_Type *base;
    uint32_t bufLen;
    bool noData = false;
    uint8_t *rxBufAddr;

    /* derive the instance */
    u8EthIfInstance = Cy_ETHIF_GetEthIfInstance(pcy_privatedata);

    base = CY_ETHIF_IP_ADDR_REGBASE(u8EthIfInstance);
    /* number of used buffers */
    u32RxNum = cyp_ethif_gemgxlobj->numRxUsed((void *)cyp_ethif_pd[u8EthIfInstance], u8qnum);

    /** read receive queue */
    while (0UL != u32RxNum)
    {
        tmpBufAddr.pAddr = 0;
        tmpBufAddr.vAddr = tmpBufAddr.pAddr;
        bufLen = 0;
        if (stccallbackfunctions[u8EthIfInstance].rxgetbuff != NULL)
        {
            stccallbackfunctions[u8EthIfInstance].rxgetbuff(base, (uint8_t**)&rxBufAddr, &bufLen);
            tmpBufAddr.pAddr = (uintptr_t)rxBufAddr;
            tmpBufAddr.vAddr = tmpBufAddr.pAddr;
        }

        (void)cyp_ethif_gemgxlobj->readRxBuf((void *)cyp_ethif_pd[u8EthIfInstance],
                                          u8qnum,
                                          &tmpBufAddr,
                                          CY_ETHIF_BUFFER_CLEARED_0,
                                          &Rx_DescData);

        switch ((CEDI_RxRdStat)Rx_DescData.status)
        {
          case CEDI_RXDATA_SOF_EOF:     // 0
            /* receive start and end frame */
            cyp_ethif_gemgxlobj->getRxDescStat((void *)cyp_ethif_pd[u8EthIfInstance],
                                         Rx_DescData.rxDescStat,
                                         &Rx_DescStat);

            /* application callback function */
            if (stccallbackfunctions[u8EthIfInstance].rxframecb != NULL)
            {
                stccallbackfunctions[u8EthIfInstance].rxframecb(base, (uint8_t*)tmpBufAddr.pAddr, Rx_DescStat.bufLen);
            }
            break;
          case CEDI_RXDATA_SOF_ONLY:    // 1
            /* fragment start */
            // debug_printf("[ETH] (SOF)Don't use fragment yet...\r\n");
            break; //return;
          case CEDI_RXDATA_NO_FLAG:     // 2
            /* fragment */
            // debug_printf("[ETH] (NOF)Don't use fragment yet...\r\n");
            break; //return;
          case CEDI_RXDATA_EOF_ONLY:    // 3
            /* fragment end */
            // debug_printf("[ETH] (EOF)Don't use fragment yet...\r\n");
            break;
          case CEDI_RXDATA_NODATA:      // 4
            /* normal leaving */
            // debug_printf("[ETH] NG5 RXDATA_NODATA\r\n");
            noData = true;
            break;
          default:
            /* Unknown status */
            break;
        }
        if(noData)
        {
            break;/* from here it breaks while loop   */
        }
        u32RxNum--;
    }
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventRxError
****************************************************************************//**
*
* \brief Function called by cadence driver upon getting Rx Error Event
*
* \param pcy_privatedata    Instance specific private data
* \param u32event occurred event
* \param u8qnum Queue number
*
*******************************************************************************/
static void Cy_ETHIF_EventRxError(void *pcy_privatedata, uint32_t a_event, uint8_t a_qnum)
{
    //printf("[ETH] (Event) RxError received.\r\n");
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(a_event); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(a_qnum); /* Suppress a compiler warning about unused variables */

    return;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventPhyManComplete
****************************************************************************//**
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventPhyManComplete(void *pcy_privatedata, uint8_t u8read, uint16_t u16ReadData)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(u8read); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(u16ReadData); /* Suppress a compiler warning about unused variables */

    return;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventhrespError
****************************************************************************//**
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventhrespError(void *pcy_privatedata, uint8_t u8qnum)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(u8qnum); /* Suppress a compiler warning about unused variables */

    return;
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventLpPageRx
****************************************************************************//**
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventLpPageRx(void* pcy_privatedata, struct CEDI_LpPageRx* pageRx)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(pageRx); /* Suppress a compiler warning about unused variables */
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventAn
****************************************************************************//**
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventAn(void* pcy_privatedata, struct CEDI_NetAnStatus* netStat)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(netStat); /* Suppress a compiler warning about unused variables */
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventLinkChange
****************************************************************************//**
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventLinkChange(void *pcy_privatedata, uint8_t a_linkstate)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(a_linkstate); /* Suppress a compiler warning about unused variables */

    return;
}
/*******************************************************************************
* Function Name: Cy_ETHIF_EventTsu
****************************************************************************//**
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventTsu (void *pcy_privatedata, uint32_t u32event)
{
    uint8_t u8EthIfInstance = 255;
    ETH_Type *base = NULL;

    /* derive the instance */
    u8EthIfInstance = Cy_ETHIF_GetEthIfInstance(pcy_privatedata);

    base = CY_ETHIF_IP_ADDR_REGBASE(u8EthIfInstance);

    /* Event generated if second count of the timer has incremented */
    if (0UL != (u32event & ((uint32_t)CEDI_EV_TSU_SEC_INC)))
    {
        /* application callback function     */
        if (stccallbackfunctions[u8EthIfInstance].tsuSecondInccb != NULL)
        {
            stccallbackfunctions[u8EthIfInstance].tsuSecondInccb(base);
        }
    }
}
/*******************************************************************************
* Function Name: Cy_ETHIF_EventPauseFrame
****************************************************************************//**
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventPauseFrame(void *pcy_privatedata, uint32_t u32event)
{
    if (0UL != (u32event & ((uint32_t)CEDI_EV_PAUSE_FRAME_TX)))
    {
        // debug_printf("Pause frame transmitted");
    }

    if (0UL != (u32event & ((uint32_t)CEDI_EV_PAUSE_NZ_QU_RX)))
    {
        // debug_printf("Pause frame received");
    }
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
}
/*******************************************************************************
* Function Name: Cy_ETHIF_EventPtp
********************************************************************************
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventPtp (void* pcy_privatedata, uint32_t u32type, struct CEDI_1588TimerVal* time)
{
    if (0UL != (u32type & ((uint32_t)CEDI_EV_PTP_TX_SYNC)))
    {
        // printf("Sync frame transmitted");
    }

    if (0UL != (u32type & ((uint32_t)CEDI_EV_PTP_TX_PDLY_REQ)))
    {
        // printf("PTP PDelay Req frame transmitted");
    }

    if (0UL != (u32type & ((uint32_t)CEDI_EV_PTP_TX_PDLY_RSP)))
    {
        // printf("PTP PDelay Resp frame transmitted");
    }

    if (0UL != (u32type & ((uint32_t)CEDI_EV_PTP_RX_SYNC)))
    {
        // printf("Sync frame received");
    }

    if (0UL != (u32type & ((uint32_t)CEDI_EV_PTP_RX_PDLY_REQ)))
    {
        // printf("PTP PDelay Req frame received");
    }

    if (0UL != (u32type & ((uint32_t)CEDI_EV_PTP_RX_PDLY_RSP)))
    {
        // printf("PTP PDelay Resp frame received");
    }
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
    CY_UNUSED_PARAMETER(time); /* Suppress a compiler warning about unused variables */
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventExternalInt
********************************************************************************
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventExternalInt(void * pcy_privatedata)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
}

/*******************************************************************************
* Function Name: Cy_ETHIF_EventWol
********************************************************************************
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventWol(void * pcy_privatedata)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
}
/*******************************************************************************
* Function Name: Cy_ETHIF_EventLpi
********************************************************************************
*
* \brief
*
* \param
*
*
*******************************************************************************/
static void Cy_ETHIF_EventLpi(void * pcy_privatedata)
{
    CY_UNUSED_PARAMETER(pcy_privatedata); /* Suppress a compiler warning about unused variables */
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.1');
CY_MISRA_BLOCK_END('OVERRUN');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXETH */
/* [] END OF FILE */
