/***************************************************************************//**
* \file cy_keyscan.c
* \version 1.0
*
* \brief
* Provides an API declaration of the KEYSCAN driver
*
********************************************************************************
* \copyright
* Copyright 2020-2021, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cy_device.h"
#if defined (CY_IP_MXKEYSCAN)
/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "cy_keyscan.h"
#include <string.h>

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/


/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/


/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_GetEventsFromHWFifo(MXKEYSCAN_Type *base, cy_stc_keyscan_context_t *context);
static cy_en_ks_status_t Cy_Keyscan_Fq_Flush(cy_stc_keyscan_context_t* context);
static cy_en_ks_status_t Cy_Keyscan_Fq_GetCurNumElements(cy_stc_keyscan_context_t* context, uint8_t *numElements);
static cy_en_ks_status_t Cy_Keyscan_Fq_PutIncludeOverflowSlot(cy_stc_keyscan_context_t* context, cy_stc_key_event *element);
static cy_en_ks_status_t Cy_Keyscan_Fq_GetCurElmPtr(cy_stc_keyscan_context_t* context, cy_stc_key_event **current_element);
static cy_en_ks_status_t Cy_Keyscan_Fq_RemoveCurElement(cy_stc_keyscan_context_t* context);
static cy_en_ks_status_t Cy_Keyscan_Fq_Put(cy_stc_keyscan_context_t* context, cy_stc_key_event *element);
static cy_en_ks_status_t Cy_Keyscan_Fq_MarkCurrentEventForRollBack (cy_stc_keyscan_context_t* context);
static cy_en_ks_status_t Cy_Keyscan_Fq_RollbackUptoMarkedEvents(cy_stc_keyscan_context_t* context);
static cy_en_ks_status_t Cy_Keyscan_PutEvent(cy_stc_keyscan_context_t* context, cy_stc_key_event *event);
static cy_en_ks_status_t Cy_Keyscan_GetEvent(cy_stc_keyscan_context_t* context, cy_stc_key_event *event);
static cy_en_ks_status_t Cy_Keyscan_Mia_FreezeClk(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context);
static cy_en_ks_status_t Cy_Keyscan_Mia_UnfreezeClk(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context);
static cy_en_ks_status_t Cy_Keyscan_HwResetOnce(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context);
static cy_en_ks_status_t Cy_Keyscan_Init_Context( cy_stc_keyscan_context_t* context);

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 *****************************************************************************
 ** Discards elements from Keyscan FW circular FIFO.
 ** This Function Discards all elements from the FIFO, including any elements in the overflow slot.
 **
 ** [in]  context     Pointer to the context.
 **
 **
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_Flush(cy_stc_keyscan_context_t* context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == context)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        context->readIndex = context->writeIndex = context->curNumElements = 0U;
    }
    return status;
}

/**
 *****************************************************************************
 ** Returns no of elements in the keyscan FW circular FIFO.
 ** This function discards all elements from the FIFO, including any elements in the overflow slot.
 **
 ** [in]  context      Pointer to the context.
 **
 ** [out] numElements  Pointer to the number of elements.
 **
 **
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_GetCurNumElements(cy_stc_keyscan_context_t* context, uint8_t *numElements)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ((NULL == context) || (NULL == numElements))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        *numElements = context->curNumElements;
    }
    return status;
}
/**
 *****************************************************************************
 ** Puts an element into the FIFO as long as there is room for 1 element or more, i.e.
 **         this method will fill in the overflow slot if that is the
 **         last slot left. Should be used if (a) overflow slots are not needed (b)
 **         for queuing an overflow event.
 **
 ** [in]  context      Pointer to the context.
 **
 ** [in]  element      pointer to the element to be placed in the FIFO
 **
 ** [in]  length       length number of bytes in element. This number of bytes is copied into the
 **                           internal storage of the FIFO. This must be <= the maximum element size
 **                           specified when the FIFO was constructed, otherwise the results are undefined.
 **
 **
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_PutIncludeOverflowSlot(cy_stc_keyscan_context_t* context, cy_stc_key_event *element)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == element) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Check if we have room including the overflow slot
        if (context->curNumElements < context->maxNumElements)
        {
            // We can put it in. Use the local put function to add the element in
            status = Cy_Keyscan_Fq_Put(context, element);
        }
        else
        {
            // We have an overflow condition. Inform the caller
            status = CY_KEYSCAN_QUEUE_OVERFLOW;
        }
    }
    return status;
}

/**
 *****************************************************************************
 ** Returns pointer to the first element in the FIFO. If the FIFO is empty returns NULL.
 **
 ** [in]  context      Pointer to the context.
 **
 ** [out]  element     pointer to the next element in the FIFO if the FIFO is not empty
 **                           NULL if the FIFO is empty.
 **
 **
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_GetCurElmPtr(cy_stc_keyscan_context_t* context, cy_stc_key_event **current_element)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == current_element) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Check if the FIFO has an element
        if (context->curNumElements != 0U)
        {
            // Return pointer to the element
            *current_element = &(context->bufStart[context->readIndex]);
        }
        else
        {
            // If we get here, the FIFO doesn't have any elements. Return NULL
            current_element = NULL;
            status = CY_KEYSCAN_EVENT_NONE;
        }

    }
    return status;
}
/**
 *****************************************************************************
 ** Removes the current element from the FIFO. Does nothing if the FIFO is empty.
 **
 ** [in]  context     Pointer to the context.
 **
 **
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_RemoveCurElement(cy_stc_keyscan_context_t* context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == context)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Check if the FIFO has any elements
        if ((context->curNumElements) != 0U)
        {
            // Reduce the number of elements by 1
            (context->curNumElements)--;

            // Advance the read index and read pointer
            (context->readIndex)++;

            // Check for wraparound
            if (context->readIndex >= context->maxNumElements)
            {
                // We have wraparound. Move the read index to the top of the buffer
                context->readIndex = 0;
            }
        }
    }
    return status;
}
/**
 *****************************************************************************
 ** Puts an element into the FIFO.
 ** This function puts an element into the FIFO. Does not perform any bound checking.
 **
 ** [in]  context      Pointer to the context.
 **
 ** [in]  element      Pointer to the element to be placed in the FIFO
 **
 ** [in]  length       Number of bytes in element. This number of bytes is copied into the
 **                    internal storage of the FIFO. This must be <= the maximum element size
 **                    specified when the FIFO was constructed, otherwise the results are undefined.
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_Put(cy_stc_keyscan_context_t* context, cy_stc_key_event *element)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == element) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Copy the element at the current write location
        (void)memcpy( &context->bufStart[context->writeIndex], element, sizeof(cy_stc_key_event)); /* Suppress a compiler warning about unused return value */

        // Update the number of elements in the FIFO
        (context->curNumElements)++;

        // Next increment the write index
        (context->writeIndex)++;

        // Now check for wraparound
        if (context->writeIndex >= context->maxNumElements)
        {
            // We need to wraparound. Set the write index to zero
            context->writeIndex = 0;
        }
    }
    return status;
}

/**
 *****************************************************************************
 ** Save the current FW FIFO write index. This is useful for rolling
 **         back what we added in case we encounter a ghost/overflow condition.
 **
 ** [in]  context     Pointer to the context.
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_MarkCurrentEventForRollBack (cy_stc_keyscan_context_t* context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        /// Save the current FW FIFO write index. This is useful for rolling
        /// back what we added in case we encounter a ghost/overflow condition
        context->savedWriteIndexForRollBack = context->writeIndex;
        context->savedNumElements = context->curNumElements;

    }
    return status;
}

/**
 *****************************************************************************
 ** Rollback upto the marked events.
 **
 ** [in]  context     Pointer to the context.
 **
 **
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Fq_RollbackUptoMarkedEvents(cy_stc_keyscan_context_t* context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == context)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        context->curNumElements = context->savedNumElements;
        // rollback upto the marked event
        context->writeIndex = context->savedWriteIndexForRollBack;
    }
    return status;
}

/**
 *****************************************************************************
 ** Put an event into the Keyscan data FIFO.
 **
 ** [in]  context   Pointer to the context.
 **
 ** [in]  event     Pointer to the event.
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_PutEvent(cy_stc_keyscan_context_t* context, cy_stc_key_event *event)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    uint8_t numElements;
    /* Check if pointers are valid */
    if ((NULL == event) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        status = Cy_Keyscan_Fq_GetCurNumElements( context, &numElements);
        if(status == CY_KEYSCAN_SUCCESS)
        {
            // Check if the FIFO has room
            if(numElements == ((uint8_t)(KEYSCAN_FW_FIFO_SIZE - 1U)))
            {
                // Overflow! FIFO a rollover event; discard whatever was given to us
                event->keyCode = ((uint8_t)KEYSCAN_KEYCODE_ROLLOVER);
            }
            // if not overflow the event is put into FIFO
            status = Cy_Keyscan_Fq_PutIncludeOverflowSlot(context, event);
        }
    }
    return status;
}

/**
 *****************************************************************************
 ** Get the next element in the FIFO
 **
 ** [in]  context    Pointer to the context.
 **
 ** [out]  event     Pointer to the event.
 *****************************************************************************/
static cy_en_ks_status_t  Cy_Keyscan_GetEvent(cy_stc_keyscan_context_t* context, cy_stc_key_event *event)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    cy_stc_key_event *current_event;
    uint8_t numElements;
    /* Check if pointers are valid */
    if ((NULL == event) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        status = Cy_Keyscan_Fq_GetCurNumElements( context, &numElements);
        if(status == CY_KEYSCAN_SUCCESS)
        {
            // Check if FIFO is empty
            if (numElements == 0U)
            {
                 event->keyCode = (uint8_t)KEYSCAN_KEYCODE_NONE;
                 status = CY_KEYSCAN_EVENT_NONE;
            }
            else
            {
                status = Cy_Keyscan_Fq_GetCurElmPtr(context, &current_event);
                if(status == CY_KEYSCAN_SUCCESS)
                {
                event->keyCode = current_event->keyCode;
                event->upDownFlag = current_event->upDownFlag;
                event->scanCycleFlag = current_event->scanCycleFlag;

                (void)Cy_Keyscan_Fq_RemoveCurElement(context); /* Suppress a compiler warning about unused return value */
                }

            }

        }
    }
    return status;
}

/**
 *****************************************************************************
 ** Freeze the MIA clock. Wait until the HW accepts the command, then
 ** generate an event indicating that the MIA clock is unfrozen for anyone
 ** who desires to catch it.
 **
 ** [in]  context    Pointer to the context.
 ** [in]  base       Pointer to KeyScan instance register area
 **
 **
 *****************************************************************************/
static cy_en_ks_status_t  Cy_Keyscan_Mia_FreezeClk(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ((NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Issue the freeze command to the HW
        KEYSCAN_MIA_CTL(base) |= _VAL2FLD(MXKEYSCAN_MIA_CTL_FREEZE_MIA, 1U);
        Cy_SysLib_DelayUs(100U);
        // Wait till mia_clk_freezed bit in MIA_STATUS register to go high
        while (_FLD2VAL(MXKEYSCAN_MIA_STATUS_MIA_CLOCK_FREEZED_STATUS, KEYSCAN_MIA_STATUS(base)) != 1U)
        {
        }

        // Notify application that clock is frozen. This allows workarounds for clock freeze related MIA
        // bugs, specifically key event loss when clock is frozen/unfrozen without reading the key event FIFO
        // Poll the event FIFO only if the freeze didn't come from us
        if (!context->keyscan_pollingKeyscanHw)
        {
            // Retrieve any pending events from the HW FIFO
            status = Cy_Keyscan_GetEventsFromHWFifo(base, context);
        }
    }
    return status;
}
/**
 *****************************************************************************
 ** Unfreeze the MIA clock. Wait until the HW accepts the command, then
 ** generate an event indicating that the MIA clock is unfrozen for anyone
 ** who desires to catch it.
 **
 ** [in]  context    Pointer to the context.
 ** [in]  base       Pointer to KeyScan instance register area
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Mia_UnfreezeClk(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ((NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Unfreeze the clock
        KEYSCAN_MIA_CTL(base) &= ~MXKEYSCAN_MIA_CTL_FREEZE_MIA_Msk;

        // Wait until it is unfrozen
        while (_FLD2VAL(MXKEYSCAN_MIA_STATUS_MIA_CLOCK_FREEZED_STATUS, KEYSCAN_MIA_STATUS(base)) != 0U)
        {
        }
        KEYSCAN_CTL(base) &= ~MXKEYSCAN_KEYSCAN_CTL_KYS_RST_EN_Msk;
    }
    return status;
}

/**
 *****************************************************************************
 ** Reset the Keyscan HW once.
 **
 ** [in]  context    Pointer to the context.
 ** [in]  base       Pointer to KeyScan instance register area
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_HwResetOnce(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ((NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Freeze the MIA clock
        status = Cy_Keyscan_Mia_FreezeClk(base, context);

        if(status == CY_KEYSCAN_SUCCESS)
        {
            // Set the "clear reported keys" bit. This is necessary or the HW reset will not be accepted
            KEYSCAN_MIA_CTL(base)  |= MXKEYSCAN_MIA_CTL_REPORTED_CLEAR_KYS_Msk;

            // Set the reset bit
            KEYSCAN_CTL(base) |= MXKEYSCAN_KEYSCAN_CTL_KYS_RST_EN_Msk;

            // Unfreeze the MIA clock. This will clear the reset bit
            status = Cy_Keyscan_Mia_UnfreezeClk(base, context);

            // Delay to ensure that the reset takes effect
            // SOme more information on why 2550 delay to be gathered.
            Cy_SysLib_DelayUs(2550U);
        }

    }
    return status;
}


/**
 *****************************************************************************
 ** Flush Events
 **
 ** [in]  context    Pointer to the context.
 ** [in]  base       Pointer to KeyScan instance register area
 **
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_FlushEvents(MXKEYSCAN_Type *base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ((NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Freeze the MIA clock
        status = Cy_Keyscan_Mia_FreezeClk(base, context);

        if(status == CY_KEYSCAN_SUCCESS)
        {
            // Unfreeze the MIA clock.
            status = Cy_Keyscan_Mia_UnfreezeClk(base, context);
            // Flush the FW FIFO
            (void)Cy_Keyscan_Fq_Flush(context); /* Suppress a compiler warning about unused return value */

            // no keys currently pressed
            context->keysPressedCount = 0U;
        }

    }
    return status;
}

/**
 *****************************************************************************
 ** Initialization of the keyscan FW circular FIFO.
 ** This function initializes circular FIFO to maintain the key codes for each key event generated.
 **
 ** [in]  context     Pointer to the context.
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_Init_Context( cy_stc_keyscan_context_t* context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == context)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        /* Save max elements, and buffer */
        context->maxNumElements = KEYSCAN_FW_FIFO_SIZE;
        context->readIndex = context->writeIndex = context->curNumElements = 0;
    }
    return status;
}

/**
 *****************************************************************************
 ** Registers for callback
 **
 ** [in]  cbEvents    Pointer to the callback function.
 **
 ** [in]  context     Pointer to the context.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_Register_Callback(cy_cb_keyscan_handle_events_t cbEvents, cy_stc_keyscan_context_t* context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ((NULL == context) || (NULL == cbEvents))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        /* Save callback function in context */
        context->cbEvents = cbEvents;
    }
    return status;
}


/**
 *****************************************************************************
 ** Register Context with the driver
 ** This Function registers for the event callback and FW FIFO buffer.
 **
 ** The Application must configure corresponding keyscan pins
 **      according to requirements and settings of keyscan instance.
 **
 ** [in] base       Pointer to KeyScan instance register area
 ** [in] config     KeyScan module configuration. See #cy_stc_ks_config_t.
 ** [out] context    Pointer to the context.
 *****************************************************************************/
cy_en_ks_status_t  Cy_Keyscan_Init(MXKEYSCAN_Type* base, const cy_stc_ks_config_t* config, cy_stc_keyscan_context_t *context )
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == context) || (NULL == config))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        (void)Cy_Keyscan_Init_Context(context);
        // Reset the keyscan HW to ensure we start from a known state
        status = Cy_Keyscan_DeInit(base, context);

        if(status == CY_KEYSCAN_SUCCESS)
        {
            CY_ASSERT_L3(CY_KEYSCAN_IS_ROW_COUNT_VALID(config->noofRows));
            CY_ASSERT_L3(CY_KEYSCAN_IS_COLUMN_COUNT_VALID(config->noofColumns));
            CY_ASSERT_L3(CY_KEYSCAN_IS_MD_DEBOUNCE_VALID(config->macroDownDebCnt));
            CY_ASSERT_L3(CY_KEYSCAN_IS_MU_DEBOUNCE_VALID(config->macroUpDebCnt));
            CY_ASSERT_L3(CY_KEYSCAN_IS_U_DEBOUNCE_VALID(config->microDebCnt));

            context->keyscan_pollingKeyscanHw  = false;
            context->keysPressedCount = 0U;

            KEYSCAN_DEBOUNCE(base) =  (_VAL2FLD(MXKEYSCAN_DEBOUNCE_MD_DEBOUNCE, config->macroDownDebCnt) | \
                                       _VAL2FLD(MXKEYSCAN_DEBOUNCE_MU_DEBOUNCE, config->macroUpDebCnt)   | \
                                       _VAL2FLD(MXKEYSCAN_DEBOUNCE_U_DEBOUNCE,  config->microDebCnt));

            // Configure the control register except for the enable bit
            KEYSCAN_CTL(base) =       (_VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_GHOST_EN,     config->ghostEnable)                       | \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_KS_INT_EN,    config->cpuWakeupEnable)                   | \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_KYS_RST_EN,   MXKEYSCAN_KEYSCAN_CTL_KYS_RST_EN_DEFAULT)  | \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_RC_EXT,       MXKEYSCAN_KEYSCAN_CTL_RC_EXT_DEFAULT)      | \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_RCTC_ROW,     ((uint32_t)(config->noofRows)-1U))                      | \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_RCTC_COLUMN,  ((uint32_t)(config->noofColumns)-1U))                   | \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_PULL_HIGH,    MXKEYSCAN_KEYSCAN_CTL_PULL_HIGH_DEFAULT)   | \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_KSI_DRV_HIGH, MXKEYSCAN_KEYSCAN_CTL_KSI_DRV_HIGH_DEFAULT)| \
                                       _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_KYSCLK_STAYON,config->clkStayOn));

            // Configure the control register and enable the KS HW
            KEYSCAN_CTL(base)  |= _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_KS_EN, MXKEYSCAN_KEYSCAN_CTL_KS_EN_Msk);
        }

    }
    return status;
}

/**
 *****************************************************************************
 **  DeInit Keyscan.
 **
 **  base     [in]        Pointer to KEYSCAN instance register area.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_DeInit(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        uint32_t savedKeyscanCtrl;

        // Save the current value of the control register
        savedKeyscanCtrl = KEYSCAN_CTL(base);

        // Flag that we are polling the keyscan HW.
        // Avoids potentially infinite recursion
        context->keyscan_pollingKeyscanHw = true;
        /* Reset the Hardware if keyscan is in enabled state.*/
        if(_FLD2VAL(MXKEYSCAN_KEYSCAN_CTL_KS_EN, KEYSCAN_CTL(base)) != 0UL)
        {
            // Reset the HW multiple times to ensure that any partial counts are cleared
            status = Cy_Keyscan_HwResetOnce(base, context);
            status = Cy_Keyscan_HwResetOnce(base, context);
        }

        if(status == CY_KEYSCAN_SUCCESS)
        {
            // Disable keyscan HW
            KEYSCAN_CTL(base) &= ~MXKEYSCAN_KEYSCAN_CTL_KS_EN_Msk;

            // Delay to ensure that the HW is actually disabled
            Cy_SysLib_DelayUs(100U);
            // Clear FW event FIFO after a HW reset. Doesn't seem to be any reason
            // to keep events around in the FW FIFO
            status = Cy_Keyscan_Fq_Flush(context);

            // no keys currently pressed
            context->keysPressedCount = 0U;

            // Clear the polling flag
            context->keyscan_pollingKeyscanHw = false;
        }

        // Restore the control register and enable scans if they were enabled before this function was called
        KEYSCAN_CTL(base) = savedKeyscanCtrl;
    }
    return status;
}

/**
 *****************************************************************************
 **  Enable Keyscan.
 **
 **  base    [in]  Pointer to KeyScan instance register area.
 **  context [in]  Pointer to the context.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_Enable(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        KEYSCAN_CTL(base)  |= _VAL2FLD(MXKEYSCAN_KEYSCAN_CTL_KS_EN, MXKEYSCAN_KEYSCAN_CTL_KS_EN_Msk);
    }
    return status;
}

/**
 *****************************************************************************
 **  Disable keyscan
 **
 **  base    [in]  Pointer to KeyScan instance register area.
 **  context [in]  Pointer to the context.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_Disable(MXKEYSCAN_Type* base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Disable keyscan HW
        KEYSCAN_CTL(base) &= ~MXKEYSCAN_KEYSCAN_CTL_KS_EN_Msk;
    }
    return status;
}

/**
 *****************************************************************************
 **  Events pending
 **
 **  base          [in]  Pointer to KeyScan instance register area.
 **  context       [in]  Pointer to the context.
 **  eventsPending [out]  Pointer to the eventsPending.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_EventsPending(MXKEYSCAN_Type* base, bool *eventsPending, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    uint8_t numElements = 0U;
    /* Check if pointers are valid */
    if ((NULL == base) || (NULL == context) || (NULL == eventsPending))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Return whether any events are in the FW FIFO or not
        status = Cy_Keyscan_Fq_GetCurNumElements( context, &numElements);
        if(numElements == 0U)
        {
            *eventsPending = false;
        }
        else
        {
            *eventsPending = true;
        }
    }
    return status;
}

/**
 *****************************************************************************
 **  Get Next event from FW FIFO
 **
 **  base          [in]  Pointer to KeyScan instance register area.
 **  context       [in]  Pointer to the context.
 **  event         [out] Pointer to the next event.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_GetNextEvent(MXKEYSCAN_Type* base, cy_stc_key_event *event, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ((NULL == base) || (NULL == context) || (NULL == event))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        // Get the next event from the FW FIFO and return it.
        // The get function returns CY_KEYSCAN_EVENT_NONE if the FW FIFO is empty
        status = Cy_Keyscan_GetEvent(context, event);
    }
    return status;
}

/**
 *****************************************************************************
 **  Setup interrupt source to be accepted.
 **
 **  base    [in]  Pointer to KeyScan instance register area.
 **  mask    [in]  The mask with the OR of the interrupt source to be accepted.
 **                       See \ group_keyscan_intr_mask_macro for the set of constants.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_SetInterruptMask(MXKEYSCAN_Type* base, uint32_t mask)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == base)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        KEYSCAN_INTR_MASK(base)  = mask;
    }
    return status;
}

/**
 *****************************************************************************
 **  Return interrupt mask setting.
 **
 **  base [in]  Pointer to KeyScan instance register area.
 **  mask  [out] The mask with the OR of the interrupt source which is masked.
 **                       See \ group_keyscan_intr_mask_macro for the set of constants.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_GetInterruptMask(MXKEYSCAN_Type* base, uint32_t *mask)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == mask))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        *mask = KEYSCAN_INTR_MASK(base);
    }
    return status;
}

/**
 *****************************************************************************
 **  Return interrupt masked status.
 **
 **  base    [in]  Pointer to KeyScan instance register area.
 **  status  [out] The mask with the OR of the interrupt source which occurs.
 **                       See \ group_keyscan_intr_mask_macro for the set of constants.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_GetInterruptMaskedStatus(MXKEYSCAN_Type* base, uint32_t *status)
{
    cy_en_ks_status_t return_status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == status))
    {
        return_status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        *status = KEYSCAN_INTR_MASKED(base);
    }
    return return_status;
}

/**
 *****************************************************************************
 **  Return interrupt raw status.
 **
 **  base    [in]  Pointer to Keyscan instance register area.
 **  status  [out] The mask with the OR of the interrupt source which occurs.
 **                       See \ group_keyscan_intr_mask_macro for the set of constants.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_GetInterruptStatus(MXKEYSCAN_Type* base, uint32_t *status)
{
    cy_en_ks_status_t return_status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == status))
    {
        return_status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        *status = KEYSCAN_INTR(base) ;
    }
    return return_status;
}

/**
 *****************************************************************************
 **  Clear interrupt status.
 **
 **  base    [in]  Pointer to Keyscan instance register area.
 **  mask    [in]  The mask with the OR of the interrupt source to be cleared.
 **                       See \ group_keyscan_intr_mask_macro for the set of constants.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_ClearInterrupt(MXKEYSCAN_Type* base, uint32_t mask)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == base)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        KEYSCAN_INTR(base) = mask;
    }
    return status;
}

/**
 *****************************************************************************
 **  Handler for keyscan interrupts.
 ** Applications have to call this function from keyscan interrupt handler.
 **
 **  base    [in]  Pointer to Keyscan instance register area.
 **  context [in]  Pointer to the context.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_Interrupt_Handler(MXKEYSCAN_Type *base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        while(_FLD2VAL(MXKEYSCAN_MIA_STATUS_KEYCODE_SET_STATUS, KEYSCAN_MIA_STATUS(base)) != 0UL)
        {
            /* internally calls Cy_Keyscan_getEventsFromHWFifo to read from the FIFO. */
            (void)Cy_Keyscan_Mia_FreezeClk(base, context); /* Suppress a compiler warning about unused return value */

            /* Unfreeze the clock once read from FIFO is complete */
            (void)Cy_Keyscan_Mia_UnfreezeClk(base, context); /* Suppress a compiler warning about unused return value */

            /* notify application to read from the FW FIFO.
               Application has to call Cy_Keyscan_getNextEvent() in a loop till the
               the return value is CY_KEYSCAN_EVENT_NONE */

            context->cbEvents();
        }

       /* Clear all the interrupts */
        status = Cy_Keyscan_ClearInterrupt(MXKEYSCAN, MXKEYSCAN_INTR_ALL);
    }
    return status;
}

/**
 *****************************************************************************
 ** Reads from Hardware FIFO.
 ** Called when Applications call keyscan interrupt handler.
 **
 **  base    [in]  Pointer to Keyscan instance register area.
 **  context [in]  Pointer to the context.
 **
 *****************************************************************************/
static cy_en_ks_status_t Cy_Keyscan_GetEventsFromHWFifo(MXKEYSCAN_Type *base, cy_stc_keyscan_context_t *context)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if ( (NULL == base) || (NULL == context))
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        bool ghostDetected;
        uint8_t keyCode;
        uint8_t numEvents;
        uint32_t scanCycleOfLastEvent = 0;
        bool firstEvent;
        cy_stc_key_event event = {.keyCode = 0, .upDownFlag = 0, .scanCycleFlag = 0};

        // No ghost events detected to begin with
        ghostDetected = false;

        // Processing for first event is slightly different from subsequent
        // events. Set the first event flag on
        firstEvent = true;

        (void)Cy_Keyscan_Fq_MarkCurrentEventForRollBack(context); /* Suppress a compiler warning about unused return value */

        // Get the number of events present in the event FIFO
        numEvents = (uint8_t)(_FLD2VAL(MXKEYSCAN_KEYFIFO_CNT_KEYFIFO_CNT, KEYSCAN_KEYFIFO_CNT(base)));

        // Now read and copy the events into the FW FIFO.
        while (numEvents > 0U)
        {
            // Read another event from the HW FIFO
            uint32_t fifo_val = KEYSCAN_KEYFIFO(base);
            keyCode = (uint8_t)(_FLD2VAL(MXKEYSCAN_KEYFIFO_KEYFIFO, fifo_val));

            // HW can spit out 0xff events that don't mean anything. This happens
            // after a reset when the FW and HW get out of sync. The simplest way to deal
            // with them is to treat them like a ghost since we have no idea what the actual HW state
            // is. The caller should then generate a reset.

            // Did we see a ghost?
            if ((keyCode  == ((uint8_t)KEYSCAN_KEYCODE_GHOST)) || (keyCode  == 0xFFU))
            {
                // Yes. Set the ghost detected flag
                ghostDetected = true;
            }

            // If we detect a ghost we discard all events, even those belonging
            // to subsequent scan cycles.
            if (!ghostDetected)
            {
                // So we don't have a ghost

                // Check if this event belongs to a different scan cycle than the previous event
                if (!firstEvent &&
                    ((_FLD2VAL(MXKEYSCAN_KEYFIFO_TRACK_SCAN_CYCLE, fifo_val) ^ scanCycleOfLastEvent) != 0UL))
                {
                    // It does. Add an end of scan cycle event to the FW FIFO
                    event.keyCode = (uint8_t)KEYSCAN_KEYCODE_END_OF_SCAN_CYCLE;
                    (void)Cy_Keyscan_PutEvent(context, &event); /* Suppress a compiler warning about unused return value */

                    // Save the current FIFO index for rollback to the last scan cycle
                    (void)Cy_Keyscan_Fq_MarkCurrentEventForRollBack(context); /* Suppress a compiler warning about unused return value */
                }

                // Subsequent events are not first events
                firstEvent = false;

                // Save the scan cycle of the new event for later use
                scanCycleOfLastEvent = (_FLD2VAL(MXKEYSCAN_KEYFIFO_TRACK_SCAN_CYCLE, fifo_val));

                // Add new event to the FW FIFO
                event.keyCode       = keyCode;
                event.upDownFlag    = (uint8_t)(_FLD2VAL(MXKEYSCAN_KEYFIFO_KEY_UP_DOWN, fifo_val));
                event.scanCycleFlag = (uint8_t)(_FLD2VAL(MXKEYSCAN_KEYFIFO_TRACK_SCAN_CYCLE, fifo_val));

                // keep track of the number of unmatched key down events by
                // incrementing every time get key down event, and decrementing
                // every time get a key up event
                if (event.upDownFlag != 0U)
                {
                    // since should never get a key up event without a key
                    // down  event, don't decrement if already 0
                    if (context->keysPressedCount > 0U)
                    {
                        context->keysPressedCount--; // detected key up event
                    }
                }
                else
                {
                    context->keysPressedCount++; // detected key down event
                }

                (void)Cy_Keyscan_PutEvent(context, &event); /* Suppress a compiler warning about unused return value */
            }
            numEvents -= 1U;
        }

        // Note that we are ignoring the case where the FW scans the HW just
        // as its in the middle of detecting an overflow condition. If
        // an overflow is detected, we really don't know what is the current
        // state of the matrix. It probably doesn't matter that we don't catch
        // all the keys. Current plan is to reset the HW in case of an overflow
        // to allow it to accurately capture the current state of the keyboard
        // This seems adequate at this time.

        // Check if an overflow or ghost condition has been detected
        if ( ghostDetected || ((_FLD2VAL(MXKEYSCAN_MIA_STATUS_OVERFLOW_STATUS, KEYSCAN_MIA_STATUS(base))) != 0UL) )
        {
            // Rollback the FW FIFO to the last save point
            (void)Cy_Keyscan_Fq_RollbackUptoMarkedEvents(context); /* Suppress a compiler warning about unused return value */

            // Now place a rollover event into the FW fifo
            event.keyCode = ((uint8_t)KEYSCAN_KEYCODE_ROLLOVER);
            (void)Cy_Keyscan_PutEvent(context, &event); /* Suppress a compiler warning about unused return value */

            if ((_FLD2VAL(MXKEYSCAN_KEYSCAN_CTL_GHOST_EN, KEYSCAN_CTL(base))) != 0UL)
            {
                // Enable the HW reset bit. After the reset the HW will capture
                // the current state of the system
                KEYSCAN_CTL(base) |= MXKEYSCAN_KEYSCAN_CTL_KYS_RST_EN_Msk;
            }
            // clear the pressed key count.
            context->keysPressedCount = 0;
        }
        else
        {
            // If we queued any events, add an end of scan cycle marker to the end
            // We can use the first event flag; it will be cleared if we
            // added any events
            if (!firstEvent)
            {
                // Now place a rollover event into the FW FIFO
                event.keyCode = (uint8_t)KEYSCAN_KEYCODE_END_OF_SCAN_CYCLE;
                (void)Cy_Keyscan_PutEvent(context, &event); /* Suppress a compiler warning about unused return value */
            }
        }

        // Set the "clear reported keys" bit. This will clear the HW when the MIA clock is unfrozen
            KEYSCAN_MIA_CTL(base)  |= MXKEYSCAN_MIA_CTL_REPORTED_CLEAR_KYS_Msk;
    }
    return status;
}

/**
 *****************************************************************************
 **  Enables Ghost detection
 **
 **  base    [in]  Pointer to Keyscan instance register area.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_EnableGhostDetection(MXKEYSCAN_Type *base)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == base)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        /* enable ghost detection */
        KEYSCAN_CTL(base)  |=  MXKEYSCAN_KEYSCAN_CTL_GHOST_EN_Msk;
    }
    return status;
}

/**
 *****************************************************************************
 **  Disables Ghost detection
 **
 **  base    [in]  Pointer to Keyscan instance register area.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_DisableGhostDetection(MXKEYSCAN_Type *base)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == base)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        /* disable ghost detection */
        KEYSCAN_CTL(base) &= ~MXKEYSCAN_KEYSCAN_CTL_GHOST_EN_Msk;
    }
    return status;
}

/**
 *****************************************************************************
 ** Enables Clock Stay On
 ** Clock to the IP is always enabled.
 **
 ** base    [in]  Pointer to Keyscan instance register area.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_EnableClockStayOn(MXKEYSCAN_Type *base)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == base)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        /* enable clock stay on */
        KEYSCAN_CTL(base)  |= MXKEYSCAN_KEYSCAN_CTL_KYSCLK_STAYON_Msk;
    }
    return status;
}

/**
 *****************************************************************************
 **  Disables Clock Stay On
 **  When there is no activity detected, the clock to the Keyscan is gated off.
 **
 **  base    [in]  Pointer to Keyscan instance register area.
 *****************************************************************************/
cy_en_ks_status_t Cy_Keyscan_DisableClockStayOn(MXKEYSCAN_Type *base)
{
    cy_en_ks_status_t status = CY_KEYSCAN_SUCCESS;
    /* Check if pointers are valid */
    if (NULL == base)
    {
        status = CY_KEYSCAN_BAD_PARAM;
    }
    else
    {
        /* disable clock stay on */
        KEYSCAN_CTL(base) &= ~MXKEYSCAN_KEYSCAN_CTL_KYSCLK_STAYON_Msk;
    }
    return status;
}

#endif /* CY_IP_MXKEYSCAN */
/*****************************************************************************/
/* EOF (not truncated)                                                       */
/*****************************************************************************/
