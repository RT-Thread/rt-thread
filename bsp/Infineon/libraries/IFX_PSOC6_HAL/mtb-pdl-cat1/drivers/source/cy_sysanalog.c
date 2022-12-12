/***************************************************************************//**
* \file cy_sysanalog.c
* \version 2.10
*
* Provides the public functions for the API for the SysAnalog driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2020 Cypress Semiconductor Corporation
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
#include "cy_sysanalog.h"

#ifdef CY_IP_MXS40PASS

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 5, \
'PASS_Type will typecast to either PASS_V1_Type or PASS_V2_Type but not both on PDL initialization based on the target device at compile time.');

#define IS_TMR_CLK_VALID(clock)             (((clock) == CY_SYSANALOG_TIMER_CLK_PERI) || \
                                             ((clock) == CY_SYSANALOG_TIMER_CLK_DEEPSLEEP) || \
                                             ((clock) == CY_SYSANALOG_TIMER_CLK_LF))

#define IS_TMR_PERIOD_VALID(period)         ((period) <= PASS_TIMER_V2_PERIOD_PER_VAL_Msk)

#define IS_DSMODE_VALID(dsmode)             (((dsmode) == CY_SYSANALOG_LPOSC_DUTY_CYCLED) || \
                                             ((dsmode) == CY_SYSANALOG_LPOSC_ALWAYS_ON))

#define IS_SRC_VALID(src)                   (((src) == CY_SYSANALOG_DEEPSLEEP_SRC_LPOSC) || \
                                             ((src) == CY_SYSANALOG_DEEPSLEEP_SRC_CLK_MF))

#define IS_DIV_VALID(div)                   (((div) == CY_SYSANALOG_DEEPSLEEP_CLK_NO_DIV) || \
                                             ((div) == CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_2) || \
                                             ((div) == CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_4) || \
                                             ((div) == CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_8) || \
                                             ((div) == CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_16))

/* Configure the AREF to use the local Vref and local IZTAT. Can be used with \ref Cy_SysAnalog_Init. */
const cy_stc_sysanalog_config_t Cy_SysAnalog_Fast_Local =
{
    /*.startup    */ CY_SYSANALOG_STARTUP_FAST,
    /*.iztat      */ CY_SYSANALOG_IZTAT_SOURCE_LOCAL,
    /*.vref       */ CY_SYSANALOG_VREF_SOURCE_LOCAL_1_2V,
    /*.deepSleep  */ CY_SYSANALOG_DEEPSLEEP_DISABLE,
};

/* Configure the AREF to use the SRSS Vref and SRSS IZTAT. Can be used with \ref Cy_SysAnalog_Init. */
const cy_stc_sysanalog_config_t Cy_SysAnalog_Fast_SRSS =
{
    /*.startup    */ CY_SYSANALOG_STARTUP_FAST,
    /*.iztat      */ CY_SYSANALOG_IZTAT_SOURCE_SRSS,
    /*.vref       */ CY_SYSANALOG_VREF_SOURCE_SRSS,
    /*.deepSleep  */ CY_SYSANALOG_DEEPSLEEP_DISABLE,
};

/* Configure the AREF to use the external Vref and local IZTAT. Can be used with \ref Cy_SysAnalog_Init. */
const cy_stc_sysanalog_config_t Cy_SysAnalog_Fast_External =
{
    /*.startup    */ CY_SYSANALOG_STARTUP_FAST,
    /*.iztat      */ CY_SYSANALOG_IZTAT_SOURCE_LOCAL,
    /*.vref       */ CY_SYSANALOG_VREF_SOURCE_EXTERNAL,
    /*.deepSleep  */ CY_SYSANALOG_DEEPSLEEP_DISABLE,
};

/*******************************************************************************
* Function Name: Cy_SysAnalog_Init
****************************************************************************//**
*
* Initialize the AREF block.
*
* \param config
* Pointer to structure containing configuration data. See \ref cy_stc_sysanalog_config_t
*
* \return
* - \ref CY_SYSANALOG_SUCCESS : initialization complete
* - \ref CY_SYSANALOG_BAD_PARAM : input pointers are null, initialization incomplete
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_INIT
*
*******************************************************************************/
cy_en_sysanalog_status_t Cy_SysAnalog_Init(const cy_stc_sysanalog_config_t * config)
{
    CY_ASSERT_L1(NULL != config);

    cy_en_sysanalog_status_t result = CY_SYSANALOG_BAD_PARAM;

    if (NULL != config)
    {
        CY_ASSERT_L3(CY_SYSANALOG_DEEPSLEEP(config->deepSleep));
        CY_ASSERT_L3(CY_SYSANALOG_VREF(config->vref));
        CY_ASSERT_L3(CY_SYSANALOG_IZTAT(config->iztat));

        PASS_AREF_AREF_CTRL = (uint32_t) CY_SYSANALOG_STARTUP_FAST \
                            | (uint32_t) CY_SYSANALOG_DEFAULT_BIAS_SCALE \
                            | (uint32_t) config->iztat \
                            | (uint32_t) config->vref \
                            | (uint32_t) config->deepSleep;

        result = CY_SYSANALOG_SUCCESS;
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SysAnalog_DeepSleepInit
****************************************************************************//**
*
* Initialize PASS_ver2 Deep Sleep features such as Low Power Oscillator, Deep Sleep Clock, Timer.
*
* \param base Pointer to the PASS register structure.
*
* \param config
* Pointer to structure containing configuration data. See \ref cy_stc_sysanalog_deep_sleep_config_t
*
* \return
* - \ref CY_SYSANALOG_SUCCESS : initialization complete
* - \ref CY_SYSANALOG_BAD_PARAM : input pointers are null, initialization incomplete
*
* \funcusage \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_INIT_DS
*
*******************************************************************************/
cy_en_sysanalog_status_t Cy_SysAnalog_DeepSleepInit(PASS_Type * base, const cy_stc_sysanalog_deep_sleep_config_t * config)
{
    cy_en_sysanalog_status_t result = CY_SYSANALOG_UNSUPPORTED;

    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L1(NULL != config);

    if(!CY_PASS_V1)
    {
        if ((NULL == base) || (NULL == config))
        {
            result = CY_SYSANALOG_BAD_PARAM;
        }
        else
        {
            uint32_t locPeriod = config->timerPeriod - 1UL;  /* Convert the user value into the machine value */

            CY_ASSERT_L3(IS_DSMODE_VALID(config->lpOscDsMode));
            CY_ASSERT_L3(IS_SRC_VALID(config->dsClkSource));
            CY_ASSERT_L3(IS_DIV_VALID(config->dsClkdivider));
            CY_ASSERT_L3(IS_TMR_CLK_VALID(config->timerClock));
            CY_ASSERT_L2(IS_TMR_PERIOD_VALID(locPeriod));

            PASS_LPOSC_CONFIG(base)    = _VAL2FLD(PASS_LPOSC_V2_CONFIG_DEEPSLEEP_MODE    , config->lpOscDsMode);
            PASS_DPSLP_CLOCK_SEL(base) = _VAL2FLD(PASS_V2_DPSLP_CLOCK_SEL_DPSLP_CLOCK_SEL, config->dsClkSource) |
                                         _VAL2FLD(PASS_V2_DPSLP_CLOCK_SEL_DPSLP_CLOCK_DIV, config->dsClkdivider);
            PASS_TIMER_CONFIG(base)    = _VAL2FLD(PASS_TIMER_V2_CONFIG_CLOCK_SEL         , config->timerClock);
            PASS_TIMER_PERIOD(base)    = _VAL2FLD(PASS_TIMER_V2_PERIOD_PER_VAL           , locPeriod);

            result = CY_SYSANALOG_SUCCESS;
        }
    }

    return result;
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS40PASS */

/* [] END OF FILE */
