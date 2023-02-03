/*!
 * @file        tsc_time.c
 *
 * @brief       This file contains all functions to manage the timings in general.
 *
 * @version     V1.0.0
 *
 * @date        2022-02-21
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "tsc.h"
#include "tsc_time.h"

/** @addtogroup TSC_Driver_Library TSC Driver Library
  @{
*/

/** @addtogroup TSC_Time_Driver TSC Time Driver
  @{
*/

/** @defgroup TSC_Time_Macros Macros
  @{
*/

/**@} end of group TSC_Time_Macros */

/** @defgroup TSC_Time_Enumerations Enumerations
  @{
*/

/**@} end of group TSC_Time_Enumerations */

/** @defgroup TSC_Time_Structures Structures
  @{
*/

/**@} end of group TSC_Time_Structures */

/** @defgroup TSC_Time_Variables Variables
  @{
*/

/**@} end of group TSC_Time_Variables */

/** @defgroup TSC_Time_Functions Functions
  @{
*/

/*!
 * @brief       Configurate of the timing module
 *
 * @param       None
 *
 * @retval      pointer to a TSC_STATUS_T structure
 */
TSC_STATUS_T TSC_Time_Config(void)
{
    /* Program one systick interrupt every (1 / TOUCH_TICK_FREQ) ms */
    if (SysTick_Config(SystemCoreClock / TOUCH_TICK_FREQ))
    {
        return TSC_STATUS_ERROR;
    }
    else
    {
        return TSC_STATUS_OK;
    }
}

/*!
 * @brief       Management of the timing module interrupt service routine.
 *
 * @param       None
 *
 * @retval      None
 */
void TSC_Time_ProcessInterrupt(void)
{
    static TSC_tTick_ms_T val_1s = 0;

    /* Count 1 global tick every xxx ms (defined by TOUCH_TICK_FREQ parameter) */
    TSC_Globals.Tick_ms++;

    /* Check if 1 second has elapsed */
    val_1s++;
    if (val_1s > (TOUCH_TICK_FREQ - 1))
    {
        TSC_Globals.Tick_sec++;
        if (TSC_Globals.Tick_sec > 63)
        {
            TSC_Globals.Tick_sec = 0;
        }
        val_1s = 0;
    }

    /* Callback function */
#if TOUCH_USE_TIMER_CALLBACK > 0
    TSC_CallBack_TimerTick();
#endif
}

/*!
 * @brief       Check if a delay (in ms) has elapsed
 *              This function must be called regularly due to counter Roll-over only managed one time
 *
 * @param       delay_ms: Delay in ms
 *
 * @param       last_tick: Variable holding the last tick value
 *
 * @retval      Status
 */
TSC_STATUS_T TSC_Time_Delay_ms(TSC_tTick_ms_T delay_ms, __IO TSC_tTick_ms_T* last_tick)
{
    TSC_tTick_ms_T count1, count2;

    disableInterrupts();

    count1 = TSC_Globals.Tick_ms;

    if (delay_ms == 0)
    {
        enableInterrupts();
        return TSC_STATUS_ERROR;
    }

    /* Counter Roll-over management */
    if (count1 < *last_tick)
    {
        count2 = (0xFFFF - *last_tick) + count1 + 1;

    }
    else
    {
        count2 = count1 - *last_tick;
    }

#if (TOUCH_TICK_FREQ == 125)
    if (count2 >= (TSC_tTick_ms_T)(delay_ms >> 3)) //!< Divide by 8 for 8ms tick
#endif
#if (TOUCH_TICK_FREQ == 250)
        if (count2 >= (TSC_tTick_ms_T)(delay_ms >> 2)) //!< Divide by 4 for 4ms tick
#endif
#if (TOUCH_TICK_FREQ == 500)
            if (count2 >= (TSC_tTick_ms_T)(delay_ms >> 1)) //!< Divide by 2 for 2ms tick
#endif
#if (TOUCH_TICK_FREQ == 1000)
                if (count2 >= (TSC_tTick_ms_T)delay_ms) //!< Direct value for 1ms tick
#endif
#if (TOUCH_TICK_FREQ == 2000)
                    if (count2 >= (TSC_tTick_ms_T)(delay_ms << 1)) //!< Multiply by 2 for 0.5ms tick
#endif
                    {
                        /* Save current time */
                        *last_tick = count1;
                        enableInterrupts();
                        return TSC_STATUS_OK;
                    }
    enableInterrupts();
    return TSC_STATUS_BUSY;
}

/*!
 * @brief       Check if a delay has elapsed.
 *
 * @param       delay_sec: Delay in seconds
 *
 * @param       last_tick: Variable holding the last tick value
 *
 * @retval      Status
 */
TSC_STATUS_T TSC_Time_Delay_sec(TSC_tTick_sec_T delay_sec, __IO TSC_tTick_sec_T* last_tick)
{
    TSC_tTick_sec_T count1, count2;

    disableInterrupts();

    count1 = TSC_Globals.Tick_sec;

    if (delay_sec == 0)
    {
        enableInterrupts();
        return TSC_STATUS_ERROR;
    }

    /* Counter Roll-over management */
    if (count1 < *last_tick)
    {
        count2 = (TSC_tTick_sec_T)((63 - *last_tick) + count1 + 1);

    }
    else
    {
        count2 = (TSC_tTick_sec_T)(count1 - *last_tick);
    }

    if (count2 >= delay_sec)
    {
        /* Save current time */
        *last_tick = count1;
        enableInterrupts();
        return TSC_STATUS_OK;
    }
    enableInterrupts();
    return TSC_STATUS_BUSY;
}

/**@} end of group TSC_Time_Functions */
/**@} end of group TSC_Time_Driver */
/**@} end of group TSC_Driver_Library */
