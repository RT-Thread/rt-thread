/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdmmc_osa.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Initialize OSA.
 */
void SDMMC_OSAInit(void)
{
    /* Intentional empty */
}

/*!
 * brief OSA Create event.
 * param event handle.
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAEventCreate(void *eventHandle)
{
    assert(eventHandle != NULL);

#if defined(SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE) && SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE
    (void)OSA_SemaphoreCreate(&(((sdmmc_osa_event_t *)eventHandle)->handle), 0U);
#else
    (void)OSA_EventCreate(&(((sdmmc_osa_event_t *)eventHandle)->handle), true);
#endif

    return kStatus_Success;
}

/*!
 * brief Wait event.
 *
 * param eventHandle The event type
 * param eventType Timeout time in milliseconds.
 * param timeoutMilliseconds timeout value in ms.
 * param event event flags.
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAEventWait(void *eventHandle, uint32_t eventType, uint32_t timeoutMilliseconds, uint32_t *event)
{
    assert(eventHandle != NULL);

    osa_status_t status = KOSA_StatusError;

#if defined(SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE) && SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE
    while (true)
    {
        status = OSA_SemaphoreWait(&(((sdmmc_osa_event_t *)eventHandle)->handle), timeoutMilliseconds);
        if (KOSA_StatusTimeout == status)
        {
            break;
        }

        if (KOSA_StatusSuccess == status)
        {
            (void)SDMMC_OSAEventGet(eventHandle, eventType, event);
            if ((*event & eventType) != 0U)
            {
                return kStatus_Success;
            }
        }
    }

#else
    while (true)
    {
        status = OSA_EventWait(&(((sdmmc_osa_event_t *)eventHandle)->handle), eventType, 0, timeoutMilliseconds, event);
        if ((KOSA_StatusSuccess == status) || (KOSA_StatusTimeout == status))
        {
            break;
        }
    }

    if (KOSA_StatusSuccess == status)
    {
        return kStatus_Success;
    }
#endif

    return kStatus_Fail;
}

/*!
 * brief set event.
 * param event event handle.
 * param eventType The event type
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAEventSet(void *eventHandle, uint32_t eventType)
{
    assert(eventHandle != NULL);

#if defined(SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE) && SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE
    OSA_SR_ALLOC();
    OSA_ENTER_CRITICAL();
    ((sdmmc_osa_event_t *)eventHandle)->eventFlag |= eventType;
    OSA_EXIT_CRITICAL();

    (void)OSA_SemaphorePost(&(((sdmmc_osa_event_t *)eventHandle)->handle));
#else
    (void)OSA_EventSet(&(((sdmmc_osa_event_t *)eventHandle)->handle), eventType);
#endif

    return kStatus_Success;
}

/*!
 * brief Get event flag.
 * param eventHandle event handle.
 * param eventType The event type
 * param flag pointer to store event value.
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAEventGet(void *eventHandle, uint32_t eventType, uint32_t *flag)
{
    assert(eventHandle != NULL);
    assert(flag != NULL);

#if defined(SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE) && SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE
    *flag = ((sdmmc_osa_event_t *)eventHandle)->eventFlag;
#else
    (void)OSA_EventGet(&(((sdmmc_osa_event_t *)eventHandle)->handle), eventType, flag);
#endif

    return kStatus_Success;
}

/*!
 * brief clear event flag.
 * param eventHandle event handle.
 * param eventType The event type
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAEventClear(void *eventHandle, uint32_t eventType)
{
    assert(eventHandle != NULL);

#if defined(SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE) && SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE
    OSA_SR_ALLOC();
    OSA_ENTER_CRITICAL();
    ((sdmmc_osa_event_t *)eventHandle)->eventFlag &= ~eventType;
    OSA_EXIT_CRITICAL();
#else
    (void)OSA_EventClear(&(((sdmmc_osa_event_t *)eventHandle)->handle), eventType);
#endif

    return kStatus_Success;
}

/*!
 * brief Delete event.
 * param event The event handle.
 */
status_t SDMMC_OSAEventDestroy(void *eventHandle)
{
    assert(eventHandle != NULL);

#if defined(SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE) && SDMMC_OSA_POLLING_EVENT_BY_SEMPHORE
    (void)OSA_SemaphoreDestroy(&(((sdmmc_osa_event_t *)eventHandle)->handle));
#else
    (void)OSA_EventDestroy(&(((sdmmc_osa_event_t *)eventHandle)->handle));
#endif

    return kStatus_Success;
}

/*!
 * brief Create a mutex.
 * param mutexHandle mutex handle.
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAMutexCreate(void *mutexHandle)
{
    assert(mutexHandle != NULL);

    (void)OSA_MutexCreate(&((sdmmc_osa_mutex_t *)mutexHandle)->handle);

    return kStatus_Success;
}

/*!
 * brief set event.
 * param mutexHandle mutex handle.
 * param millisec The maximum number of milliseconds to wait for the mutex.
 *                 If the mutex is locked, Pass the value osaWaitForever_c will
 *                 wait indefinitely, pass 0 will return KOSA_StatusTimeout
 *                 immediately.
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAMutexLock(void *mutexHandle, uint32_t millisec)
{
    assert(mutexHandle != NULL);

    (void)OSA_MutexLock(&((sdmmc_osa_mutex_t *)mutexHandle)->handle, millisec);

    return kStatus_Success;
}

/*!
 * brief Get event flag.
 * param mutexHandle mutex handle.
 * retval kStatus_Fail or kStatus_Success.
 */
status_t SDMMC_OSAMutexUnlock(void *mutexHandle)
{
    assert(mutexHandle != NULL);

    (void)OSA_MutexUnlock(&((sdmmc_osa_mutex_t *)mutexHandle)->handle);

    return kStatus_Success;
}

/*!
 * brief Delete mutex.
 * param mutexHandle The mutex handle.
 */
status_t SDMMC_OSAMutexDestroy(void *mutexHandle)
{
    assert(mutexHandle != NULL);

    (void)OSA_MutexDestroy(&((sdmmc_osa_mutex_t *)mutexHandle)->handle);

    return kStatus_Success;
}

/*!
 * brief sdmmc delay.
 * param milliseconds time to delay
 */
void SDMMC_OSADelay(uint32_t milliseconds)
{
#if (defined FSL_OSA_BM_TIMER_CONFIG) && (FSL_OSA_BM_TIMER_CONFIG == FSL_OSA_BM_TIMER_NONE)
    SDK_DelayAtLeastUs(milliseconds * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
#else
    OSA_TimeDelay(milliseconds);
#endif
}

/*!
 * brief sdmmc delay us.
 * param microseconds time to delay
 * return actual delayed microseconds
 */
uint32_t SDMMC_OSADelayUs(uint32_t microseconds)
{
#if (defined FSL_OSA_BM_TIMER_CONFIG) && (FSL_OSA_BM_TIMER_CONFIG == FSL_OSA_BM_TIMER_NONE)
    SDK_DelayAtLeastUs(microseconds, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    return microseconds;
#else
    uint32_t milliseconds = microseconds / 1000U + ((microseconds % 1000U) == 0U ? 0U : 1U);
    OSA_TimeDelay(milliseconds);
    return milliseconds * 1000U;
#endif
}
