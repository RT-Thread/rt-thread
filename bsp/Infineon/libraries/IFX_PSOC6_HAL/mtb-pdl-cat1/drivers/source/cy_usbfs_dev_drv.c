/***************************************************************************//**
* \file cy_usbfs_dev_drv.c
* \version 2.20.3
*
* Provides general API implementation of the USBFS driver.
*
********************************************************************************
* \copyright
* Copyright 2018-2020 Cypress Semiconductor Corporation
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

#if defined (CY_IP_MXUSBFS) && defined (CY_IP_MXPERI)

#include "cy_usbfs_dev_drv.h"
#include "cy_usbfs_dev_drv_pvt.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*                        Internal Constants
*******************************************************************************/

/* After suspend, disable wait 2 us */
#define WAIT_SUSPEND_DISABLE    (2U)

/* The bus reset counter is driven by the 100 kHz clock and detects a bus reset
* condition after 100 us.
*/
#define BUS_RESET_PERIOD        (10UL)


/*******************************************************************************
*                        Internal Functions Prototypes
*******************************************************************************/

static void LpmIntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context);
static void SofIntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context);
static void Ep0IntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context);
static void BusResetIntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context);
static void ArbiterIntrHandler (USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context);
static void SieEnpointIntrHandler(USBFS_Type *base, uint32_t endpoint, cy_stc_usbfs_dev_drv_context_t *context);

static uint32_t WriteEp0Buffer(USBFS_Type *base, uint8_t const *buffer, uint32_t size);
static uint32_t ReadEp0Buffer (USBFS_Type const *base, uint8_t *buffer, uint32_t size);

static void RestoreDeviceConfiguration(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context);

static void EndpointTransferComplete(USBFS_Type *base, uint32_t endpoint,
                                    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData,
                                    cy_stc_usbfs_dev_drv_context_t *context);

/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Init
****************************************************************************//**
*
* Initializes the USBFS in device mode. If DMAs are used, initialize the DMAs.
*
* \param base
* The pointer to the USBFS instance.
*
* \param config
* The pointer to the configuration structure \ref cy_stc_usbfs_dev_drv_config_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* The status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
cy_en_usbfs_dev_drv_status_t Cy_USBFS_Dev_Drv_Init(USBFS_Type *base,
                                                   cy_stc_usbfs_dev_drv_config_t const *config,
                                                   cy_stc_usbfs_dev_drv_context_t      *context)
{
    cy_en_usbfs_dev_drv_status_t retStatus = CY_USBFS_DEV_DRV_BAD_PARAM;

    /* Input parameters verification */
    if ((NULL == base) || (NULL == config) || (NULL == context))
    {
        return CY_USBFS_DEV_DRV_BAD_PARAM;
    }

    CY_ASSERT_L3(CY_USBFS_DEV_DRV_IS_MODE_VALID(config->mode));

    /* Enables clock to mxusb IP */
    USBFS_DEV_USB_CLK_EN(base) = CY_USBFS_DEV_DRV_WRITE_ODD(USBFS_USBDEV_USB_CLK_EN_CSR_CLK_EN_Msk);

    /* Clears register (except reserved): the IOMODE = 0 means usb IP controls the usb pins */
    USBFS_DEV_USBIO_CR1(base) = (USBFS_DEV_USBIO_CR1(base) & USBFS_USBDEV_USBIO_CR1_RESERVED_2_Msk);

    /* Sets the number of clocks (divided version of Clk_Peri) to detect bus reset */
    USBFS_DEV_BUS_RST_CNT(base) = BUS_RESET_PERIOD;

    /* Enable PHY detector and single-ended and differential receivers */
    USBFS_DEV_LPM_POWER_CTL(base) = (USBFS_USBLPM_POWER_CTL_SUSPEND_Msk    |
                                     USBFS_USBLPM_POWER_CTL_ENABLE_DPO_Msk |
                                     USBFS_USBLPM_POWER_CTL_ENABLE_DMO_Msk);
    (void) USBFS_DEV_LPM_POWER_CTL(base);

    /* Suspends a clear sequence */
    Cy_SysLib_DelayUs(WAIT_SUSPEND_DISABLE);
    USBFS_DEV_LPM_POWER_CTL(base) &= ~USBFS_USBLPM_POWER_CTL_SUSPEND_Msk;
    (void) USBFS_DEV_LPM_POWER_CTL(base);

    /* Clears the register (except reserved) and enable IMO lock */
    USBFS_DEV_CR1(base) = USBFS_USBDEV_CR1_ENABLE_LOCK_Msk |
                      (USBFS_DEV_CR1(base) & USBFS_USBDEV_CR1_RESERVED_3_Msk);

    /* Configures the level selection (HI, MED, LO) for each interrupt source */
    USBFS_DEV_LPM_INTR_LVL_SEL(base) = config->intrLevelSel;

    /* Enables the interrupt sources: Bus Reset and EP0 */
    USBFS_DEV_LPM_INTR_SIE_MASK(base) = (USBFS_USBLPM_INTR_SIE_BUS_RESET_INTR_Msk |
                                         USBFS_USBLPM_INTR_SIE_EP0_INTR_Msk);

    /* Clears the LPM register (disable LPM response) */
    USBFS_DEV_LPM_LPM_CTL(base) = 0UL;

    if (config->enableLpm)
    {
        /* Enables the device to ACK LPM requests */
        USBFS_DEV_LPM_LPM_CTL(base) = (USBFS_USBLPM_LPM_CTL_LPM_EN_Msk |
                                       USBFS_USBLPM_LPM_CTL_LPM_ACK_RESP_Msk);
    }

    /* Copies the configuration in the context */
    context->mode     = config->mode;
    context->useReg16 = (config->epAccess == CY_USBFS_DEV_DRV_USE_16_BITS_DR);
    context->epSharedBuf     = config->epBuffer;
    context->epSharedBufSize = config->epBufferSize;

    /* Initializes the pointers to functions that work with data endpoint */
    switch(config->mode)
    {
        case CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU:
        {
            context->addEndpoint     = &AddEndpointHwBuffer;
            context->loadInEndpoint  = &LoadInEndpointCpu;
            context->readOutEndpoint = &ReadOutEndpointCpu;

            USBFS_DEV_ARB_CFG(base) = _VAL2FLD(USBFS_USBDEV_ARB_CFG_DMA_CFG,
                                            CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU);

            retStatus = CY_USBFS_DEV_DRV_SUCCESS;
        }
        break;

        case CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA:
        {
            context->addEndpoint     = &AddEndpointHwBuffer;
            context->loadInEndpoint  = &LoadInEndpointDma;
            context->readOutEndpoint = &ReadOutEndpointDma;

            USBFS_DEV_ARB_CFG(base) = _VAL2FLD(USBFS_USBDEV_ARB_CFG_DMA_CFG,
                                            CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA);
        }
        break;

        case CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO:
        {
            context->addEndpoint     = &AddEndpointRamBuffer;
            context->loadInEndpoint  = &LoadInEndpointDmaAuto;
            context->readOutEndpoint = &ReadOutEndpointDmaAuto;

            USBFS_DEV_ARB_CFG(base) = (_VAL2FLD(USBFS_USBDEV_ARB_CFG_DMA_CFG,
                                             CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO) |
                                             USBFS_USBDEV_ARB_CFG_AUTO_MEM_Msk);
        }
        break;

        default:
            /* Unknown mode */
            break;
    }

    /* Configure DMA and store info about DMA channels */
    if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU != context->mode)
    {
        retStatus = DmaInit(config, context);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_DeInit
****************************************************************************//**
*
* De-initializes the USBFS Device hardware (returns the register values to
* default) and removes all registered callbacks.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_DeInit(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t regVal;
    uint32_t endpoint;

    /* Set USBLPM registers into the default state */
    USBFS_DEV_LPM_POWER_CTL(base)     = 0UL;
    USBFS_DEV_LPM_USBIO_CTL(base)     = 0UL;
    USBFS_DEV_LPM_FLOW_CTL(base)      = 0UL;
    USBFS_DEV_LPM_LPM_CTL(base)       = 0UL;
    USBFS_DEV_LPM_INTR_SIE(base)      = 0UL;
    USBFS_DEV_LPM_INTR_SIE_SET(base)  = 0UL;
    USBFS_DEV_LPM_INTR_SIE_MASK(base) = 0UL;
    USBFS_DEV_LPM_INTR_LVL_SEL(base)  = 0UL;

    /* Set USBDEV registers into the default state */
    USBFS_DEV_CR0(base) = 0UL;
    USBFS_DEV_CR1(base) = (USBFS_DEV_CR1(base) & USBFS_USBDEV_CR1_RESERVED_3_Msk);
    USBFS_DEV_USBIO_CR0(base) = 0UL;
    USBFS_DEV_USBIO_CR1(base) = (USBFS_DEV_USBIO_CR1(base) & USBFS_USBDEV_USBIO_CR1_RESERVED_2_Msk);
    regVal = CY_USBFS_DEV_READ_ODD(USBFS_DEV_USBIO_CR2(base));
    USBFS_DEV_USBIO_CR2(base) = (CY_USBFS_DEV_DRV_WRITE_ODD(regVal) & USBFS_USBDEV_USBIO_CR2_RESERVED_7_Msk);

    USBFS_DEV_BUS_RST_CNT(base) = BUS_RESET_PERIOD;
    USBFS_DEV_USB_CLK_EN(base)  = CY_USBFS_DEV_DRV_WRITE_ODD(0UL);

    USBFS_DEV_EP0_CR(base)  = 0UL;
    USBFS_DEV_EP0_CNT(base) = CY_USBFS_DEV_DRV_WRITE_ODD(0UL);

    USBFS_DEV_ARB_CFG(base)    = 0UL;
    USBFS_DEV_ARB_INT_EN(base) = 0UL;

    USBFS_DEV_DYN_RECONFIG(base) = 0UL;
    USBFS_DEV_BUF_SIZE(base)     = 0UL;
    USBFS_DEV_DMA_THRES16(base)  = 0UL;
    USBFS_DEV_EP_ACTIVE(base)    = 0UL;
    USBFS_DEV_EP_TYPE(base)      = CY_USBFS_DEV_DRV_WRITE_ODD(0UL);
    USBFS_DEV_CWA16(base)        = 0UL;

    USBFS_DEV_SIE_EP_INT_EN(base) = 0UL;
    USBFS_DEV_SIE_EP_INT_SR(base) = 0UL;

    for (endpoint = 0UL; endpoint < CY_USBFS_DEV_DRV_NUM_EPS_MAX; ++endpoint)
    {
        /* Sets the SIE endpoint register into the default state */
        USBFS_DEV_SIE_EP_CR0(base, endpoint)  = 0UL;
        USBFS_DEV_SIE_EP_CNT0(base, endpoint) = 0UL;
        USBFS_DEV_SIE_EP_CNT1(base, endpoint) = 0UL;

        /* Sets the ARBITER endpoint register into the default state */
        USBFS_DEV_ARB_EP_CFG(base, endpoint)    = 0UL;
        USBFS_DEV_ARB_EP_INT_EN(base, endpoint) = 0UL;
        USBFS_DEV_ARB_RW_WA16(base, endpoint)   = 0UL;
        USBFS_DEV_ARB_RW_RA16(base, endpoint)   = 0UL;
    }

    /* Cleans the context callbacks */
    context->cbSof = NULL;
    context->cbLpm = NULL;

    for (endpoint = 0UL; endpoint < CY_USBFS_DEV_DRV_NUM_EPS_MAX; ++endpoint)
    {
        context->epPool[endpoint].address    = 0U;
        context->epPool[endpoint].copyData   = NULL;
        context->epPool[endpoint].epComplete = NULL;
        context->epPool[endpoint].buffer     = NULL;
    }
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Enable
****************************************************************************//**
*
* Enables the USBFS Device operation.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_Enable(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t const *context)
{
    /* Suppresses a compiler warning about unused variables */
    (void) context;

    /* Clears the  EP0 count register */
    USBFS_DEV_EP0_CNT(base) = CY_USBFS_DEV_DRV_WRITE_ODD(0UL);

    /* Sets EP0.CR: ACK Setup, NAK IN/OUT */
    USBFS_DEV_EP0_CR(base)  = CY_USBFS_DEV_DRV_EP_CR_NAK_INOUT;

    /* Enables D+ pull-up, the device appears on the bus */
    USBFS_DEV_LPM_POWER_CTL(base) |= USBFS_USBLPM_POWER_CTL_DP_UP_EN_Msk;
    (void) USBFS_DEV_LPM_POWER_CTL(base);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Disable
****************************************************************************//**
*
* Disables the USBFS Device operation. If DMAs are used, disables the DMAs.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_Disable(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Suppresses a compiler warning about unused variables */
    (void) context;

    /* Disables D+ pull-up */
    USBFS_DEV_LPM_POWER_CTL(base) &= ~USBFS_USBLPM_POWER_CTL_DP_UP_EN_Msk;
    (void) USBFS_DEV_LPM_POWER_CTL(base);

    /* Disables the device to respond to usb traffic */
    USBFS_DEV_CR0(base) &= ~USBFS_USBDEV_CR0_USB_ENABLE_Msk;

    /* Disables the DMA channels */
    if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU != context->mode)
    {
        DmaDisable(context);
    }
}


/*******************************************************************************
* Function Name: LpmIntrHandler
****************************************************************************//**
*
* LPM (Link Power Manager) interrupt handler.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void LpmIntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    if (context->cbLpm != NULL)
    {
        context->cbLpm(base, context);
    }
}


/*******************************************************************************
* Function Name: SofIntrHandler
****************************************************************************//**
*
* SOF (Start Of Frame) interrupt handler.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void SofIntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    if (context->cbSof != NULL)
    {
        context->cbSof(base, context);
    }
}


/*******************************************************************************
* Function Name: Ep0IntrHandler
****************************************************************************//**
*
* Endpoint 0 (Control Endpoint) interrupt handler.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void Ep0IntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Reads the CR register */
    uint32_t ep0Cr = Cy_USBFS_Dev_Drv_ReadEp0Mode(base);

    /* Checks whether the packet was ACKed */
    if (0U != (ep0Cr & USBFS_USBDEV_EP0_CR_ACKED_TXN_Msk))
    {
        /* Checks the packet direction */
        if (_FLD2BOOL(USBFS_USBDEV_EP0_CR_SETUP_RCVD, ep0Cr))
        {
            /* A setup packet received */
            context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_SETUP;

            /* Handles SETUP */
            if (_FLD2VAL(USBFS_USBDEV_EP0_CR_MODE, ep0Cr) == CY_USBFS_DEV_DRV_EP_CR_NAK_INOUT)
            {
                /* Tries to unlock the CR0 register: read and then write.
                * The success write clears 8-4 bits in the register.
                */
                Cy_USBFS_Dev_Drv_WriteEp0Mode(base, ep0Cr);

                /* Checks whether the CR0 register unlocked (bits cleared) */
                ep0Cr = Cy_USBFS_Dev_Drv_ReadEp0Mode(base);
                if (false == _FLD2BOOL(USBFS_USBDEV_EP0_CR_SETUP_RCVD, ep0Cr))
                {
                    /* Resets the EP0 data toggle */
                    context->ep0DataToggle = 0U;

                    /* Calls Device layer to service a request */
                    context->ep0Setup(base, context);
                }
                else
                {
                    /* CR0 is still locked, sets an interrupt pending to retry */
                    Cy_USBFS_Dev_Drv_SetSieInterrupt(base, USBFS_USBLPM_INTR_CAUSE_EP0_INTR_Msk);
                }
            }
        }
        /* Handles IN */
        else if (_FLD2BOOL(USBFS_USBDEV_EP0_CR_IN_RCVD, ep0Cr))
        {
            if (CY_USBFS_DEV_DRV_EP0_CTRL_STATE_DATA == context->ep0CtrlState)
            {
                /* Data stage: invokes a callback to proceed the control transfer */
                context->ep0In(base, context);
            }
            else if (CY_USBFS_DEV_DRV_EP0_CTRL_STATE_STATUS_IN == context->ep0CtrlState)
            {
                /* Sets an address after the Status stage completion */
                if (context->setAddress)
                {
                    Cy_USBFS_Dev_Drv_SetDeviceAddress(base, context->address);
                    context->setAddress = false;
                }

                /* Completes the control transfer */
                context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_IDLE;
            }
            else if (CY_USBFS_DEV_DRV_EP0_CTRL_STATE_STATUS_OUT == context->ep0CtrlState)
            {
                /* Updates the CNT and CR registers to continue the IN/OUT transfer */
                Cy_USBFS_Dev_Drv_SetEp0Count (base, 0U, USBFS_USBDEV_EP0_CNT_DATA_TOGGLE_Msk);
                Cy_USBFS_Dev_Drv_WriteEp0Mode(base, CY_USBFS_DEV_DRV_EP_CR_STATUS_OUT_ONLY);

                /* The transfer is completed */
                context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_IDLE;
            }
            else
            {
                /* Nothing to handle in this state */
            }
        }
        /* Handles OUT */
        else if (_FLD2BOOL(USBFS_USBDEV_EP0_CR_OUT_RCVD, ep0Cr))
        {
            if (CY_USBFS_DEV_DRV_EP0_CTRL_STATE_DATA == context->ep0CtrlState)
            {
                /* Data stage: invokes a callback to proceed the control transfer */
                context->ep0Out(base, context);
            }
        }
        else
        {
            /* Does nothing - an unknown source */
        }
    }
}


/*******************************************************************************
* Function Name: BusResetIntrHandler
****************************************************************************//**
*
* Bus Reset interrupt handler.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void BusResetIntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Resets the driver variables if any */

    /* Cypress ID# 293217: write CR0 when pull-up is enabled */
    if (_FLD2BOOL(USBFS_USBLPM_POWER_CTL_DP_UP_EN, USBFS_DEV_LPM_POWER_CTL(base)))
    {
        /* Passes an event to the Device layer */
        context->busReset(base, context);

        /* Clears the EP0 count register */
        USBFS_DEV_EP0_CNT(base) = CY_USBFS_DEV_DRV_WRITE_ODD(0UL);

        /* Sets EP0.CR: ACK Setup, NAK IN/OUT */
        USBFS_DEV_EP0_CR(base) = CY_USBFS_DEV_DRV_EP_CR_NAK_INOUT;

        /* Resets the driver context variables into the default state */
        context->setAddress   = false;
        context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_IDLE;
        context->curBufAddr   = 0U;
        context->activeEpMask = 0U;
        context->epAbortMask  = 0U;

        /* Enable device to responds to USB traffic with address 0 */
        USBFS_DEV_CR0(base) = USBFS_USBDEV_CR0_USB_ENABLE_Msk;
        (void) USBFS_DEV_CR0(base);
    }
}


/*******************************************************************************
* Function Name: EndpointTransferComplete
****************************************************************************//**
*
* Handles the endpoint transfer complete: updates  the endpoint state,
* calls a transfer completion callback, handles the abort.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The data endpoint index.
*
* \param endpointData
* The pointer to the endpoint data structure.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void EndpointTransferComplete(USBFS_Type *base, uint32_t endpoint,
                                    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData,
                                    cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Updates the toggle (exclude ISOC endpoints) */
    if (false == IS_EP_ISOC(endpointData->sieMode))
    {
        endpointData->toggle ^= (uint8_t) USBFS_USBDEV_SIE_EP_DATA_TOGGLE_Msk;
    }

    if (0U != (context->epAbortMask & EP2MASK(endpoint)))
    {
        /* Clears the endpoint abort: Do not invoke callback, the state was set to idle */
        context->epAbortMask &= (uint8_t) ~EP2MASK(endpoint);
    }
    else
    {
        /* Data has been transferred to the bus set-endpoint complete state */
        endpointData->state = CY_USB_DEV_EP_COMPLETED;

        /* Involves a callback if it is registered */
        if (NULL != endpointData->epComplete)
        {
            uint32_t errorType = 0UL;

            /* Checks transfer errors (detect by hardware) */
            if (0U != Cy_USBFS_Dev_Drv_GetSieEpError(base, endpoint))
            {
                errorType = CY_USBFS_DEV_ENDPOINT_TRANSFER_ERROR;
            }

            /* Checks the data toggle bit of current transfer (exclude ISOC endpoints) */
            if (false == IS_EP_ISOC(endpointData->sieMode))
            {
                /* This may fail only for OUT endpoints */
                if (endpointData->toggle == Cy_USBFS_Dev_Drv_GetSieEpToggle(base, endpoint))
                {
                    errorType |= CY_USBFS_DEV_ENDPOINT_SAME_DATA_TOGGLE;

                    /* Restores the data toggle to recover it in the next OUT transfer */
                    endpointData->toggle ^= (uint8_t) USBFS_USBDEV_SIE_EP_DATA_TOGGLE_Msk;
                }
            }

            /* Calls the endpoint complete callback */
            endpointData->epComplete(base, (uint32_t) endpointData->address, errorType, context);
        }
    }
}


/*******************************************************************************
* Function Name: ArbiterIntrHandler
****************************************************************************//**
*
* Arbiter interrupt handler (enabled for operation with DMAs).
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void ArbiterIntrHandler(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t endpoint = 0UL;
    uint32_t intrMask = Cy_USBFS_Dev_Drv_GetArbAllEpsInterruptStatus(base);

    /* Handle active interrupt sources */
    while (0U != intrMask)
    {
        if (0U != (intrMask & 0x01U))
        {
            /* Get the endpoint enable interrupt sources */
            uint32_t sourceMask = Cy_USBFS_Dev_Drv_GetArbEpInterruptStatusMasked(base, endpoint);

            /* Gets the pointer to the endpoint data */
            cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

            Cy_USBFS_Dev_Drv_ClearArbEpInterrupt(base, endpoint, sourceMask);

            /* Mode 2/3: Handle IN endpoint buffer full event: trigger after
            * endpoint buffer has been loaded
            */
            if (0U != (sourceMask & USBFS_USBDEV_ARB_EP_IN_BUF_FULL_Msk))
            {
                Cy_USBFS_Dev_Drv_ClearArbCfgEpInReady(base, endpoint);

                /* Mode 2: Notifies the LoadInEndpointDma function that data has been copied into the endpoint buffer.
                *  Mode 3: No impact, the endpoint pending state is set in LoadInEndpointDmaAuto before.
                */
                endpointData->state = CY_USB_DEV_EP_PENDING;

                /* Arm IN endpoint */
                Cy_USBFS_Dev_Drv_SetSieEpMode(base, endpoint, (uint32_t) endpointData->sieMode);
            }

            /* Mode 2: Handle DMA completion event for OUT endpoints */
            if (0U != (sourceMask & USBFS_USBDEV_ARB_EP_DMA_GNT_Msk))
            {
                /* Notifies the ReadOutEndpointDma function that the data has been copied from endpoint buffer
                * into the user buffer.
                */
                endpointData->state = CY_USB_DEV_EP_COMPLETED;
            }

            /* Mode 3: Handles a DMA completion event for OUT endpoints */
            if (0U != (sourceMask & USBFS_USBDEV_ARB_EP_DMA_TERMIN_Msk))
            {
                /* Sets a DMA channel to start a new transfer */
                DmaOutEndpointRestore(endpointData);

                /* Completes an endpoint transfer */
                EndpointTransferComplete(base, endpoint, endpointData, context);
            }

            /* This error condition indicates system failure */
            if (0U != (sourceMask & USBFS_USBDEV_ARB_EP_BUF_OVER_Msk))
            {
                /* The DMA cannot move the data from the mxusbfs IP
                * hardware buffer fast enough and so caused an overflow. Give a DMA
                * channel for this endpoint greater priority or increase the clock
                * at which it operates.
                */
                CY_ASSERT_L1(false);
            }

            /* This error condition indicates system failure */
            if (0U != (sourceMask & USBFS_USBDEV_ARB_EP_BUF_UNDER_Msk))
            {
                /* The DMA cannot move the data into the mxusbfs IP
                * hardware buffer fast enough and so caused an underflow. Give a DMA
                * channel for this endpoint greater priority or increase the clock
                * at which it operates.
                */
                CY_ASSERT_L1(false);
            }
        }

        /* Moves to a next endpoint */
        intrMask >>= 1UL;
        ++endpoint;
    }
}


/*******************************************************************************
* Function Name: SieEnpointIntrHandler
****************************************************************************//**
*
* SIE (Serial Interface Engine) endpoint interrupt handler.
* It triggers when communication was completed with data endpoint.
*
* \param base
* The pointer to the USBFS instance.
*
* \param endpoint
* The data endpoint number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void SieEnpointIntrHandler(USBFS_Type *base, uint32_t endpoint,
                                  cy_stc_usbfs_dev_drv_context_t *context)
{
    bool modeDmaAuto;
    bool inEndpoint;
    bool zeroLengthPacket;

    /* Gets the pointer to endpoint data */
    cy_stc_usbfs_dev_drv_endpoint_data_t *endpointData = &context->epPool[endpoint];

    Cy_USBFS_Dev_Drv_ClearSieEpInterrupt(base, endpoint);

    /*
    * DMA Auto requires special processing:
    * IN endpoints: Updates the endpoint state here to complete the transfer (includes a zero-length packet).
    * OUT endpoints: Updates the endpoint state in ArbiterIntrHandler when DMA is done to complete the transfer
    *                (interrupt source DMA_TERMIN).
    *                In the case of a zero-length packet, updates the endpoint state here to complete the transfer.
    * Other modes (CPU mode and DMA mode): Updates the endpoint state here to complete the transfer for the IN and OUT endpoints.
    */
    modeDmaAuto = (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO == context->mode);
    inEndpoint   = CY_USBFS_DEV_DRV_IS_EP_DIR_IN(endpointData->address);
    zeroLengthPacket = (0U == Cy_USBFS_Dev_Drv_GetSieEpCount(base, endpoint));

    CY_MISRA_FP_LINE('MISRA C-2012 Rule 14.3', 'Checked manually. No issues.');
    if ( (!modeDmaAuto) ||
         (modeDmaAuto && (inEndpoint || zeroLengthPacket)) )
    {
        EndpointTransferComplete(base, endpoint, endpointData, context);
    }
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Interrupt
****************************************************************************//**
*
* Processes interrupt events generated by the USBFS Device.
* The interrupts are mandatory for USBFS Device operation and this function
* must be called inside the user-defined interrupt service routine.
*
* \param base
* The pointer to the USBFS instance.
*
* \param intrCause
* The interrupt cause register value. Call appropriate function to get
* interrupt cause (Low, Medium or High):
* * \ref Cy_USBFS_Dev_Drv_GetInterruptCauseLo
* * \ref Cy_USBFS_Dev_Drv_GetInterruptCauseMed
* * \ref Cy_USBFS_Dev_Drv_GetInterruptCauseHi
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_Interrupt(USBFS_Type *base, uint32_t intrCause,
                                cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t endpoint = 0U;
    uint32_t intrCauseEp;

    /* Clears the SIE interrupts while the below are served */
    Cy_USBFS_Dev_Drv_ClearSieInterrupt(base, intrCause);

    /* LPM */
    if (0U != (intrCause & USBFS_USBLPM_INTR_CAUSE_LPM_INTR_Msk))
    {
        LpmIntrHandler(base, context);
    }

    /* Arbiter: Data endpoints */
    if (0U != (intrCause & USBFS_USBLPM_INTR_CAUSE_ARB_EP_INTR_Msk))
    {
        /* This interrupt is cleared inside the handler */
        ArbiterIntrHandler(base, context);
    }

    /* SIE: Data endpoints */
    intrCauseEp = (intrCause >> USBFS_USBLPM_INTR_CAUSE_EP1_INTR_Pos);
    while (0U != intrCauseEp)
    {
        if (0u != (intrCauseEp & 0x1U))
        {
            /* These interrupts are cleared inside the handler */
            SieEnpointIntrHandler(base, endpoint, context);
        }

        intrCauseEp >>= 1U;
        ++endpoint;
    }

    /* SOF */
    if (0U != (intrCause & USBFS_USBLPM_INTR_CAUSE_SOF_INTR_Msk))
    {
        SofIntrHandler(base, context);
    }

    /* Controls EP0 */
    if (0U != (intrCause & USBFS_USBLPM_INTR_CAUSE_EP0_INTR_Msk))
    {
        Ep0IntrHandler(base, context);
    }

    /* Bus Reset */
    if (0U != (intrCause & USBFS_USBLPM_INTR_CAUSE_BUS_RESET_INTR_Msk))
    {
        BusResetIntrHandler(base, context);
    }
}


/*******************************************************************************
* Function Name: WriteEp0Buffer
****************************************************************************//**
*
* Writes data into the Endpoint 0 hardware buffer and returns how many bytes
* were written.
*
* \param base
* The pointer to the USBFS instance.
*
* \param buffer
* The pointer to the data to write in the Endpoint 0.
*
* \param size
* The number of bytes to write into the Endpoint 0.
*
* \return
* The number of bytes that were written.
*
*******************************************************************************/
static uint32_t WriteEp0Buffer(USBFS_Type *base, uint8_t const *buffer, uint32_t size)
{
    uint32_t idx;

    /* Cuts the message size if too many bytes are requested to write */
    if (size > CY_USBFS_DEV_DRV_EP0_BUFFER_SIZE)
    {
        size = CY_USBFS_DEV_DRV_EP0_BUFFER_SIZE;
    }

    /* Writes data into the hardware buffer */
    for (idx = 0UL; idx < size; ++idx)
    {
        Cy_USBFS_Dev_Drv_WriteEp0Data(base, idx, (uint32_t) buffer[idx]);
    }

    return idx;
}


/*******************************************************************************
* Function Name: ReadEp0Buffer
****************************************************************************//**
*
* Reads data from Endpoint 0 hardware and returns how many bytes were read.
*
* \param base
* The pointer to the USBFS instance.
*
* \param buffer
* The pointer to the buffer for data read from the Endpoint 0.
*
* \param size
* The number of bytes to read from the Endpoint 0.
*
* \return
* The number of bytes that were read.
*
*******************************************************************************/
static uint32_t ReadEp0Buffer(USBFS_Type const *base, uint8_t *buffer, uint32_t size)
{
    uint32_t idx;

    /* Gets the number of received bytes */
    uint32_t numToCopy = Cy_USBFS_Dev_Drv_GetEp0Count(base);

    /* Reads received bytes only */
    if (size > numToCopy)
    {
        size = numToCopy;
    }

    /* Gets the data from the buffer */
    for (idx = 0UL; idx < size; ++idx)
    {
        buffer[idx] = (uint8_t) Cy_USBFS_Dev_Drv_ReadEp0Data(base, idx);
    }

    return idx;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Ep0GetSetup
****************************************************************************//**
*
* Reads the setup packed from the Endpoint 0 hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param buffer
* The pointer to the buffer for data read from the Endpoint 0.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_Ep0GetSetup(USBFS_Type const *base, uint8_t *buffer,
                                  cy_stc_usbfs_dev_drv_context_t const *context)
{
    /* Suppresses a compiler warning about unused variables */
    (void) context;

    (void) ReadEp0Buffer(base, buffer, CY_USBFS_DEV_DRV_EP0_BUFFER_SIZE);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Ep0Write
****************************************************************************//**
*
* Writes data into Endpoint 0 hardware buffer and returns how many bytes were
* written.
*
* \param base
* The pointer to the USBFS instance.
*
* \param buffer
* The pointer to the buffer containing data bytes to write.
* To switch a transfer from the data stage to status, pass NULL as a pointer.
*
* \param size
* The number of bytes to write.
* Setting the size to zero sends to the bus zero-length data packet.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* The number of bytes that were written.
*
*******************************************************************************/
uint32_t Cy_USBFS_Dev_Drv_Ep0Write(USBFS_Type *base, uint8_t const *buffer, uint32_t size,
                                    cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t numBytes = 0UL;

    if (NULL != buffer)
    {
        /* Data stage (IN): Loads data to be sent */

        /* Puts the data into the buffer */
        if (size > 0U)
        {
            numBytes = WriteEp0Buffer(base, buffer, size);
        }

        /* Updates the data toggle and counter */
        context->ep0DataToggle ^= (uint8_t) USBFS_USBDEV_EP0_CNT_DATA_TOGGLE_Msk;

        /* Updates the CNT and CR registers to continue the IN transfer */
        Cy_USBFS_Dev_Drv_SetEp0Count (base, numBytes, (uint32_t) context->ep0DataToggle);
        Cy_USBFS_Dev_Drv_WriteEp0Mode(base, CY_USBFS_DEV_DRV_EP_CR_ACK_IN_STATUS_OUT);

        context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_DATA;
    }
    else
    {
        /* Status stage (IN): Completes the status stage, sends an ACK handshake */

        /* Updates the CNT and CR registers to continue the IN transfer */
        Cy_USBFS_Dev_Drv_SetEp0Count (base, numBytes, USBFS_USBDEV_EP0_CNT_DATA_TOGGLE_Msk);
        Cy_USBFS_Dev_Drv_WriteEp0Mode(base, CY_USBFS_DEV_DRV_EP_CR_STATUS_IN_ONLY);

        context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_STATUS_IN;
    }

    return numBytes;
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Ep0Read
****************************************************************************//**
*
* Start receiving a packet into the Endpoint 0 hardware buffer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param buffer
* The pointer to buffer that stores data that was read.
*
* \param size
* The number of bytes to read.
* Reading zero bytes switch control transfer to status stage.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_Ep0Read(USBFS_Type *base, uint8_t *buffer, uint32_t size,
                                cy_stc_usbfs_dev_drv_context_t *context)
{
    if (0U != size)
    {
        /* Data stage (OUT): Prepares to receive data */

        /* Stores the Endpoint 0 buffer to put read operation results */
        context->ep0Buffer     = buffer;
        context->ep0BufferSize = (uint8_t) size; /* The Endpoint 0 max packet is 8 bytes */

        /* Updates the CNT and CR registers to continue the OUT transfer */
        Cy_USBFS_Dev_Drv_SetEp0Count (base, 0U, 0U);
        Cy_USBFS_Dev_Drv_WriteEp0Mode(base, CY_USBFS_DEV_DRV_EP_CR_ACK_OUT_STATUS_IN);

        context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_DATA;
    }
    else
    {
        /* Status stage (OUT): prepare to complete status stage after IN transfer is finished */
        context->ep0CtrlState = CY_USBFS_DEV_DRV_EP0_CTRL_STATE_STATUS_OUT;
    }
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Ep0ReadResult
****************************************************************************//**
*
* Reads data from the Endpoint 0 hardware and returns the number of read bytes.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* The number of read bytes.
*
*******************************************************************************/
uint32_t Cy_USBFS_Dev_Drv_Ep0ReadResult(USBFS_Type const *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Stores received data to the buffer */
    return ReadEp0Buffer(base, context->ep0Buffer, (uint32_t) context->ep0BufferSize);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_RegisterServiceCallback
****************************************************************************//**
*
* Registers a callback function to notify about service events (Bus Reset or
* Endpoint 0 communication) in \ref Cy_USBFS_Dev_Drv_Interrupt.
* To remove callback function, pass NULL as function pointer.
*
* \param base
* The pointer to the USBFS instance.
*
* \param source
* The event that involves the callback.
*
* \param callback
* The pointer to a callback function.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return
* The status code of the function execution \ref cy_en_usbfs_dev_drv_status_t.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_RegisterServiceCallback(USBFS_Type const *base,
                                              cy_en_usb_dev_service_cb_t     source,
                                              cy_cb_usbfs_dev_drv_callback_t callback,
                                              cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Suppresses a compiler warning about unused variables */
    (void) base;

    switch(source)
    {
        case CY_USB_DEV_BUS_RESET:
            context->busReset = callback;
        break;

        case CY_USB_DEV_EP0_SETUP:
            context->ep0Setup = callback;
        break;

        case CY_USB_DEV_EP0_IN:
            context->ep0In = callback;
        break;

        case CY_USB_DEV_EP0_OUT:
            context->ep0Out = callback;
        break;

        default:
        /* Unknown callback */
        break;
    }
}

/*******************************************************************************
* Function Name: RestoreDeviceConfiguration
****************************************************************************//**
*
* Restores device configuration and data endpoints for the active mode
* operation.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
static void RestoreDeviceConfiguration(USBFS_Type *base,
                                       cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t endpoint;

    /* Due to Deep Sleep, non-retention registers are set to the default state */

    for (endpoint = 0U; endpoint < CY_USBFS_DEV_DRV_NUM_EPS_MAX; ++endpoint)
    {
        if (0U != context->epPool[endpoint].address)
        {
            /* Restores the endpoint configuration */
            if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_DMA_AUTO == context->mode)
            {
                RestoreEndpointRamBuffer(base, &context->epPool[endpoint]);
            }
            else
            {
                RestoreEndpointHwBuffer(base, context->mode, &context->epPool[endpoint]);
            }
        }
    }

    /* Completes the device configuration */
    Cy_USBFS_Dev_Drv_ConfigDevice(base, context);
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Suspend
****************************************************************************//**
*
* Prepares the USBFS component to enter Deep Sleep mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \note
* After entering low-power mode, the data that is left in the IN or OUT
* endpoint buffers is not restored after a wakeup, and is lost. Therefore, it should
* be stored in the SRAM for OUT endpoint or read by the host for the IN endpoint
* before entering low-power mode.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_Suspend(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    /* Puts PHY to suspend mode */
    USBFS_DEV_LPM_POWER_CTL(base) |= USBFS_USBLPM_POWER_CTL_SUSPEND_Msk;
    (void) USBFS_DEV_LPM_POWER_CTL(base);

    /* Disables all DMA channels: DMA registers are retention */
    if (CY_USBFS_DEV_DRV_EP_MANAGEMENT_CPU != context->mode)
    {
        DmaDisable(context);
    }
}


/*******************************************************************************
* Function Name: Cy_USBFS_Dev_Drv_Resume
****************************************************************************//**
*
* Prepares the USBFS component for operation after exiting Deep Sleep mode.
*
* \param base
* The pointer to the USBFS instance.
*
* \param context
* The pointer to the context structure \ref cy_stc_usbfs_dev_drv_context_t
* allocated by the user. The structure is used during the USBFS Device
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
*******************************************************************************/
void Cy_USBFS_Dev_Drv_Resume(USBFS_Type *base, cy_stc_usbfs_dev_drv_context_t *context)
{
    uint32_t lpmCtl;

    /* Enables the clock to mxusbfs IP */
    USBFS_DEV_USB_CLK_EN(base) = CY_USBFS_DEV_DRV_WRITE_ODD(USBFS_USBDEV_USB_CLK_EN_CSR_CLK_EN_Msk);

    /* Sets the number of clocks (divided version of Clk_Peri) to detect bus reset */
    USBFS_DEV_BUS_RST_CNT(base) = BUS_RESET_PERIOD;

    /* Sets EP0.CR: ACK Setup, NAK IN/OUT */
    USBFS_DEV_EP0_CR(base) = CY_USBFS_DEV_DRV_EP_CR_NAK_INOUT;

    /* Restores the data endpoints configuration  */
    RestoreDeviceConfiguration(base, context);

    /* Cypress ID# 337915: Restore response to LPM packets */
    lpmCtl = USBFS_DEV_LPM_LPM_CTL(base);
    USBFS_DEV_LPM_LPM_CTL(base) = lpmCtl;

    /* Releases PHY from suspend mode */
    USBFS_DEV_LPM_POWER_CTL(base) &= ~USBFS_USBLPM_POWER_CTL_SUSPEND_Msk;
    (void) USBFS_DEV_LPM_POWER_CTL(base);
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXUSBFS */


/* [] END OF FILE */
