/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#ifndef __FSL_HWTIMER_H__
#define __FSL_HWTIMER_H__

#include <stdint.h>
#include "fsl_clock_manager.h"

/*!
 * @addtogroup hwtimer_driver
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief HwTimer error codes definition.
 */
typedef enum _hwtimer_error_code
{
    kHwtimerSuccess,                /*!< success */
    kHwtimerInvalidInput,           /*!< invalid input parameter */
    kHwtimerInvalidPointer,         /*!< invalid pointer */
    kHwtimerClockManagerError,      /*!< clock manager return error */
    kHwtimerRegisterHandlerError,   /*!< Interrupt handler registration returns error */
    kHwtimerUnknown,                /*!< unknown error*/
} _hwtimer_error_code_t;

/*!
 * @brief HwTimer low level context data length definition.
 */
#define HWTIMER_LL_CONTEXT_LEN 5U

/*!
 * @brief Definition for low level context data length.
 */
typedef void (* hwtimer_callback_t)(void *p);

/*!
 * @brief HwTimer structure.
 *
 * This structure defines a HwTimer.
 * The context structure is passed to all API functions (besides other parameters).
 *
 * @warning Application should not access members of this structure directly.
 *
 * @see HWTIMER_SYS_init
 * @see HWTIMER_SYS_deinit
 * @see HWTIMER_SYS_start
 * @see HWTIMER_SYS_stop
 * @see HWTIMER_SYS_set_period
 * @see HWTIMER_SYS_get_period
 * @see HWTIMER_SYS_get_modulo
 * @see HWTIMER_SYS_get_time
 * @see HWTIMER_SYS_get_ticks
 * @see HWTIMER_SYS_callback_reg
 * @see HWTIMER_SYS_callback_block
 * @see HWTIMER_SYS_callback_unblock
 * @see HWTIMER_SYS_callback_cancel
 */
typedef struct Hwtimer
{
    /*! @brief Pointer to a device interface structure */
    const struct Hwtimer_devif *    devif;
    /*! @brief Timer's source clock frequency */
    uint32_t                        clockFreq;
    /*! @brief Actual total divider */
    uint32_t                        divider;
    /*! @brief Determine how many sub ticks are in one tick */
    uint32_t                        modulo;
    /*! @brief Number of elapsed ticks */
    volatile uint64_t               ticks;
    /*! @brief Function pointer to be called when the timer expires. */
    hwtimer_callback_t              callbackFunc;
    /*! @brief Arbitrary pointer passed as parameter to the callback function. */
    void                            *callbackData;
    /*! @brief Indicate pending callback.
     *  If the timer overflows when callbacks are blocked the callback becomes pending. */
    volatile int                    callbackPending;
    /*! @brief Indicate blocked callback. */
    int                             callbackBlocked;
    /*! @brief Private storage locations for arbitrary data keeping the context of the lower layer driver. */
    uint32_t                        llContext[HWTIMER_LL_CONTEXT_LEN];
} hwtimer_t, * hwtimer_ptr_t;

/*!
 * @brief Hwtimer_time structure.
 *
 * HwTimer time structure represents a time stamp consisting of timer elapsed periods (TICKS) and current value of the timer counter (subTicks).
 *
 * @see HWTIMER_SYS_GetTime
 */
typedef struct Hwtimer_time
{
    /*! @brief Ticks of timer */
    uint64_t ticks;
    /*! @brief Sub ticks of timer */
    uint32_t subTicks;
} hwtimer_time_t, * hwtimer_time_ptr_t;

/*!
 * @brief Type defines initialization function for devif structure.
 */
typedef _hwtimer_error_code_t (*  hwtimer_devif_init_t)(hwtimer_t *hwtimer, uint32_t id, void *data);

/*!
 * @brief Type defines deinitialization function for devif structure.
 */
typedef _hwtimer_error_code_t (*  hwtimer_devif_deinit_t)(hwtimer_t *hwtimer);

/*!
 * @brief Type defines set_div function for devif structure.
 */
typedef _hwtimer_error_code_t (*  hwtimer_devif_set_div_t)(hwtimer_t *hwtimer, uint32_t period);

/*!
 * @brief Type defines start function for devif structure.
 */
typedef _hwtimer_error_code_t (*  hwtimer_devif_start_t)(hwtimer_t *hwtimer);

/*!
 * @brief Type defines stop function for devif structure.
 */
typedef _hwtimer_error_code_t (*  hwtimer_devif_stop_t)(hwtimer_t *hwtimer);

/*!
 * @brief Type defines reset function for devif structure.
 */
typedef _hwtimer_error_code_t (*  hwtimer_devif_reset_t)(hwtimer_t *hwtimer);

/*!
 * @brief Type defines get_time function for devif structure.
 */
typedef _hwtimer_error_code_t (*  hwtimer_devif_get_time_t)(hwtimer_t *hwtimer, hwtimer_time_t *time);

/*!
 * @brief hwtimer_devif structure.
 *
 * Each low layer driver exports an instance of this structure initialized with pointers to API functions that the driver implements.
 * The functions should be declared as static (not exported directly).
 *
 * @see HWTIMER_SYS_Init
 * @see HWTIMER_SYS_Deinit
 */
typedef struct Hwtimer_devif
{
     /*! @brief Function pointer to lower layer initialization */
    hwtimer_devif_init_t             init;
     /*! @brief Function pointer to lower layer de-initialization */
    hwtimer_devif_deinit_t           deinit;
     /*! @brief Function pointer to lower layer set divider functionality */
    hwtimer_devif_set_div_t          setDiv;
     /*! @brief Function pointer to lower layer start functionality */
    hwtimer_devif_start_t            start;
     /*! @brief Function pointer to lower layer stop functionality */
    hwtimer_devif_stop_t             stop;
     /*! @brief Function pointer to lower layer get time functionality */
    hwtimer_devif_get_time_t         getTime;
} hwtimer_devif_t, * hwtimer_devif_ptr_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes a caller allocated structure according to given parameters.
 *
 * The device interface pointer determines the low layer driver to be used.
 * Device interface structure is exported by each low layer driver and is opaque to the applications.
 * See a chapter about the low layer driver below for details.
 * Meaning of the numerical identifier varies depending on the low layer driver used.
 * Typically, it identifies a particular timer channel to initialize.
 * The initialization function has to be called prior to using any other API function.
 *
 * @param hwtimer [out]  Returns initialized HwTimer structure handle.
 * @param kDevif [in]    Structure determines low layer driver to be used.
 * @param id [in]        Numerical identifier of the timer.
 * @param data [in]      Specific data for low level of interrupt.
 *
 * @return success or an error code returned from low level initialization function.
 * @retval kHwtimerSuccess          Success
 * @retval kHwtimerInvalidInput     When input parameter HwTimer is a NULL pointer
 * @retval kHwtimerInvalidPointer   When device structure points to NULL.
 *
 * @warning The initialization function has to be called prior using any other API function.
 *
 * @see HWTIMER_SYS_deinit
 * @see HWTIMER_SYS_start
 * @see HWTIMER_SYS_stop
 */
_hwtimer_error_code_t HWTIMER_SYS_Init(hwtimer_t *hwtimer, const hwtimer_devif_t * kDevif, uint32_t id, void *data);

/*!
 * @brief Deinitializes the HwTimer.
 *
 * Calls the lower layer stop function to stop the timer. Then, calls the low layer de-initialization function
 * and afterwards invalidates HwTimer structure by clearing it.
 *
 * @param hwtimer [in] Pointer to HwTimer structure.
 *
 * @return success or an error code returned from low level DEINIT function.
 * @retval kHwtimerSuccess          Success
 * @retval kHwtimerInvalidInput     When input parameter HwTimer is a NULL pointer
 * @retval kHwtimerInvalidPointer   When device structure points to NULL.
 *
 * @see HWTIMER_SYS_Init
 * @see HWTIMER_SYS_Start
 * @see HWTIMER_SYS_Stop
 */
_hwtimer_error_code_t HWTIMER_SYS_Deinit(hwtimer_t *hwtimer);

/*!
 * @brief Sets the period of the HwTimer.
 *
 * The function provides a way to set up the timer to a desired period specified in microseconds.
 * Calls the low layer driver to set up the timer divider according to the specified period.
 *
 * @param hwtimer [in]   Pointer to HwTimer structure.
 * @param period [in]    Required period of timer in micro seconds.
 *
 * @return success or an error code returned from low level SETDIV function.
 * @retval kHwtimerSuccess           Success
 * @retval kHwtimerInvalidInput      When input parameter HwTimer or his device structure are NULL pointers.
 * @retval kHwtimerInvalidPointer    When low level SETDIV function point to NULL.
 * @retval kHwtimerClockManagerError When Clock manager returns error.
 *
 * @see HWTIMER_SYS_GetPeriod
 * @see HWTIMER_SYS_GetModulo
 * @see HWTIMER_SYS_GetTime
 * @see HWTIMER_SYS_GetTicks
 */
_hwtimer_error_code_t HWTIMER_SYS_SetPeriod(hwtimer_t *hwtimer, uint32_t period);

/*!
 * @brief Gets the period of the HwTimer.
 *
 * The function returns the current period of the timer in microseconds calculated from the base frequency and actual divider settings of the timer.
 *
 * @param hwtimer [in]   Pointer to HwTimer structure.
 *
 * @return already set period of HwTimer.
 * @retval 0  Input parameter HwTimer is NULL pointer or clock manager returns error.
 *
 * @see HWTIMER_SYS_SetPeriod
 * @see HWTIMER_SYS_GetModulo
 * @see HWTIMER_SYS_GetTime
 * @see HWTIMER_SYS_GetTicks
 */
uint32_t HWTIMER_SYS_GetPeriod(hwtimer_t *hwtimer);

/*!
 * @brief Enables the timer and leaves it running.
 *
 * The timer starts counting a new period generating interrupts every time the timer rolls over.
 *
 * @param hwtimer [in] Pointer to HwTimer structure.
 *
 * @return success or an error code returned from low level START function.
 * @retval kHwtimerSuccess           Success
 * @retval kHwtimerInvalidInput      When input parameter HwTimer is a NULL pointer
 * @retval kHwtimerInvalidPointer    When device structure points to NULL.
 *
 * @see HWTIMER_SYS_Init
 * @see HWTIMER_SYS_Deinit
 * @see HWTIMER_SYS_Stop
 */
_hwtimer_error_code_t HWTIMER_SYS_Start(hwtimer_t *hwtimer);

/*!
 * @brief The timer stops counting after this function is called.
 *
 * Pending interrupts and callbacks are cancelled.
 *
 * @param hwtimer [in] Pointer to HwTimer structure.
 *
 * @return success or an error code returned from low level STOP function.
 * @retval kHwtimerSuccess           Success
 * @retval kHwtimerInvalidInput      When input parameter HwTimer is a NULL pointer
 * @retval kHwtimerInvalidPointer    When device structure points to NULL.
 *
 * @see HWTIMER_SYS_Init
 * @see HWTIMER_SYS_Deinit
 * @see HWTIMER_SYS_Start
 */
_hwtimer_error_code_t HWTIMER_SYS_Stop(hwtimer_t *hwtimer);

/*!
 * @brief The function returns period of the timer in sub-ticks.
 *
 * It is typically called after HWTIMER_SYS_SetPeriod() to obtain actual resolution of the timer in the current configuration.
 *
 * @param hwtimer [in]   Pointer to HwTimer structure.
 *
 * @return resolution of HwTimer.
 * @retval 0 Input parameter HwTimer is NULL pointer.
 *
 * @see HWTIMER_SYS_SetPeriod
 * @see HWTIMER_SYS_GetPeriod
 * @see HWTIMER_SYS_GetTime
 * @see HWTIMER_SYS_GetTicks
 */
uint32_t HWTIMER_SYS_GetModulo(hwtimer_t *hwtimer);

/*!
 * @brief The function reads the current value of the HwTimer.
 *
 * Elapsed periods(ticks) and current value of the timer counter (sub-ticks) are filled into the Hwtimer_time structure.
 * The sub-ticks number always counts up and is reset to zero when the timer overflows regardless of the counting direction of the underlying device.
 *
 * @param hwtimer [in]   Pointer to HwTimer structure.
 * @param time [out]     Pointer to time structure. This value is filled with current value of the timer.
 *
 * @return success or an error code returned from low level GET_TIME function.
 * @retval kHwtimerSuccess        Success
 * @retval kHwtimerInvalidInput   When input parameter HwTimer or input parameter time are NULL pointers.
 * @retval kHwtimerInvalidPointer When device structure points to NULL.
 *
 * @see HWTIMER_SYS_SetPeriod
 * @see HWTIMER_SYS_GetPeriod
 * @see HWTIMER_SYS_GetModulo
 * @see HWTIMER_SYS_GetTicks
 */
_hwtimer_error_code_t HWTIMER_SYS_GetTime(hwtimer_t *hwtimer, hwtimer_time_t *time);

/*!
 * @brief The function reads the current value of the HwTimer
 *
 * The returned value corresponds to the lower 32 bits of elapsed periods (ticks).
 * The value is guaranteed to be obtained without needing to mask timer interrupt.
 * Lower layer driver is not involved at all and calling this function is considerably faster than HWTIMER_SYS_GetTime.
 *
 * @param hwtimer [in]   Pointer to HwTimer structure.
 *
 * @return low 32 bits of 64 bit tick value.
 * @retval 0  When input parameter HwTimer is NULL pointer.
 *
 * @see HWTIMER_SYS_SetPeriod
 * @see HWTIMER_SYS_GetPeriod
 * @see HWTIMER_SYS_GetModulo
 * @see HWTIMER_SYS_GetTime
 */
uint32_t HWTIMER_SYS_GetTicks(hwtimer_t *hwtimer);

/*!
 * @brief Registers function to be called when the timer expires.
 *
 * The callback_data is arbitrary pointer passed as parameter to the callback function.
 *
 * @param hwtimer [in]        Pointer to HwTimer structure.
 * @param callbackFunc [in] Function pointer to be called when the timer expires.
 * @param callbackData [in] Data pointer for the function callback_func.
 *
 * @return success or an error code
 * @retval kHwtimerInvalidInput When input parameter HwTimer is NULL pointer.
 * @retval kHwtimerSuccess      When registration callback succeed.
 *
 * @warning This function must not be called from a callback routine.
 *
 * @see HWTIMER_SYS_BlockCallback
 * @see HWTIMER_SYS_UnblockCallback
 * @see HWTIMER_SYS_CancelCallback
 */
_hwtimer_error_code_t HWTIMER_SYS_RegisterCallback(hwtimer_t *hwtimer, hwtimer_callback_t callbackFunc, void *callbackData);

/*!
 * @brief The function is used to block callbacks in circumstances when execution of the callback function is undesired.
 *
 * If the timer overflows when callbacks are blocked the callback becomes pending.
 *
 * @param hwtimer [in] Pointer to HwTimer structure.
 *
 * @return success or an error code
 * @retval kHwtimerInvalidInput When input parameter HwTimer is NULL pointer.
 * @retval kHwtimerSuccess      When callback block succeed.
 *
 * @warning This function must not be called from a callback routine.
 *
 * @see HWTIMER_SYS_RegCallback
 * @see HWTIMER_SYS_UnblockCallback
 * @see HWTIMER_SYS_CancelCallback
 */
_hwtimer_error_code_t HWTIMER_SYS_BlockCallback(hwtimer_t *hwtimer);

/*!
 * @brief The function is used to unblock previously blocked callbacks.
 *
 * If there is a callback pending, it gets immediately executed.
 * This function must not be called from a callback routine (it does not make sense to do so anyway as callback function never gets executed while callbacks are blocked).
 *
 * @param hwtimer [in] Pointer to HwTimer structure.
 *
 * @return success or an error code
 * @retval kHwtimerInvalidInput When input parameter HwTimer is NULL pointer.
 * @retval kHwtimerSuccess      When callback unblock succeed.
 *
 * @warning This function must not be called from a callback routine.
 *
 * @see HWTIMER_SYS_RegCallback
 * @see HWTIMER_SYS_BlockCallback
 * @see HWTIMER_SYS_CancelCallback
 */
_hwtimer_error_code_t HWTIMER_SYS_UnblockCallback(hwtimer_t *hwtimer);

/*!
 * @brief The function cancels pending callback, if any.
 *
 * @param hwtimer [in] Pointer to HwTimer structure.
 *
 * @return success or an error code
 * @retval kHwtimerInvalidInput When input parameter HwTimer is NULL pointer.
 * @retval kHwtimerSuccess      When callback cancel succeed.
 *
 * @warning This function must not be called from a callback routine (it does not make sense to do so anyway as callback function never gets executed while callbacks are blocked).
 *
 * @see HWTIMER_SYS_RegCallback
 * @see HWTIMER_SYS_BlockCallback
 * @see HWTIMER_SYS_UnblockCallback
 */
_hwtimer_error_code_t HWTIMER_SYS_CancelCallback(hwtimer_t *hwtimer);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_HWTIMER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
