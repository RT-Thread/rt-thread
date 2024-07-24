/*!
    \file    gd32h7xx_rameccmu.c
    \brief   RAMECCMU driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32h7xx_rameccmu.h"

#define RAMECCMU_REG_RESET_VALUE        0x00000000U

/*!
    \brief      deinit RAMECCMU unit
    \param[in]  rameccmu_periph: RAMECCMUx(x=0,1)
    \param[out] none
    \retval     none
*/
void rameccmu_deinit(uint32_t rameccmu_periph)
{
    RAMECCMU_INT(rameccmu_periph) = RAMECCMU_REG_RESET_VALUE;
    if(RAMECCMU0 == rameccmu_periph)
    {
        /* reset RAMECCMU0_MONITOR0 registers */
        RAMECCMU_MXCTL(RAMECCMU0_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU0_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU0_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU0_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU0_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU0_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        /* reset RAMECCMU0_MONITOR1 registers */
        RAMECCMU_MXCTL(RAMECCMU0_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU0_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU0_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU0_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU0_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU0_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        /* reset RAMECCMU0_MONITOR2 registers */
        RAMECCMU_MXCTL(RAMECCMU0_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU0_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU0_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU0_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU0_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU0_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        /* reset RAMECCMU0_MONITOR3 registers */
        RAMECCMU_MXCTL(RAMECCMU0_MONITOR3) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU0_MONITOR3) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU0_MONITOR3) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU0_MONITOR3) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU0_MONITOR3) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU0_MONITOR3) = RAMECCMU_REG_RESET_VALUE;
        /* reset RAMECCMU0_MONITOR4 registers */
        RAMECCMU_MXCTL(RAMECCMU0_MONITOR4) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU0_MONITOR4) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU0_MONITOR4) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU0_MONITOR4) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU0_MONITOR4) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU0_MONITOR4) = RAMECCMU_REG_RESET_VALUE;
    }else{
        /* reset RAMECCMU1_MONITOR0 registers */
        RAMECCMU_MXCTL(RAMECCMU1_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU1_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU1_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU1_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU1_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU1_MONITOR0) = RAMECCMU_REG_RESET_VALUE;
        /* reset RAMECCMU1_MONITOR1 registers */
        RAMECCMU_MXCTL(RAMECCMU1_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU1_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU1_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU1_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU1_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU1_MONITOR1) = RAMECCMU_REG_RESET_VALUE;
        /* reset RAMECCMU1_MONITOR2 registers */
        RAMECCMU_MXCTL(RAMECCMU1_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXSTAT(RAMECCMU1_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFADDR(RAMECCMU1_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDL(RAMECCMU1_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFDH(RAMECCMU1_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
        RAMECCMU_MXFECODE(RAMECCMU1_MONITOR2) = RAMECCMU_REG_RESET_VALUE;
    }
}

/*!
    \brief      get RAMECCMU monitor ECC failing address
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[out] none
    \retval     ECC error failing address
*/
uint32_t rameccmu_monitor_failing_address_get(rameccmu_monitor_enum rameccmu_monitor)
{
    return RAMECCMU_MXFADDR(rameccmu_monitor);
}

/*!
    \brief      get RAMECCMU monitor ECC failing data low 32 bits
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[out] none
    \retval     ECC failing data low 32 bits
*/
uint32_t rameccmu_monitor_failing_data_low_bits_get(rameccmu_monitor_enum rameccmu_monitor)
{
    return RAMECCMU_MXFDL(rameccmu_monitor);
}

/*!
    \brief      get RAMECCMU monitor ECC failing data high 32 bits
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[out] none
    \retval     ECC failing data high 32 bits
*/
uint32_t rameccmu_monitor_failing_data_high_bits_get(rameccmu_monitor_enum rameccmu_monitor)
{
    return RAMECCMU_MXFDH(rameccmu_monitor);
}

/*!
    \brief      get RAMECCMU monitor failing ECC error code
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[out] none
    \retval     ECC failing error code
*/
uint32_t rameccmu_monitor_failing_ecc_error_code_get(rameccmu_monitor_enum rameccmu_monitor)
{
    return RAMECCMU_MXFECODE(rameccmu_monitor);
}

/*!
    \brief      enable RAMECCMU global ECC interruput
    \param[in]  rameccmu_periph: RAMECCMU
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0: RAMECCMU for region 0
      \arg        RAMECCMU1: RAMECCMU for region 1
    \param[in]  interrupt: global ECC interruput
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_INT_ECC_GLOBAL_ERROR: ECC global error interrupt
      \arg        RAMECCMU_INT_ECC_SINGLE_ERROR: ECC single error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR: ECC double error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write interrupt
    \param[out] none
    \retval     none
*/
void rameccmu_global_interrupt_enable(uint32_t rameccmu_periph, uint32_t interrupt)
{
    RAMECCMU_INT(rameccmu_periph) |= interrupt;
}

/*!
    \brief      disable RAMECCMU global ECC interruput
    \param[in]  rameccmu_periph: RAMECCMU
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0: RAMECCMU for region 0
      \arg        RAMECCMU1: RAMECCMU for region 1
    \param[in]  interrupt: global ECC interruput
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_INT_ECC_GLOBAL_ERROR: ECC global error interrupt
      \arg        RAMECCMU_INT_ECC_SINGLE_ERROR: ECC single error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR: ECC double error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write interrupt
    \param[out] none
    \retval     none
*/
void rameccmu_global_interrupt_disable(uint32_t rameccmu_periph, uint32_t interrupt)
{
    RAMECCMU_INT(rameccmu_periph) &= (uint32_t)(~interrupt);
}

/*!
    \brief      enable RAMECCMU monitor ECC error interruput
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[in]  monitor_interrupt: RAMECCMU monitor interruput
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_INT_ECC_SINGLE_ERROR: ECC single error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR: ECC double error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write interrupt
      \arg        RAMECCMU_INT_ECC_ERROR_LATCHING: ECC error latching
    \param[out] none
    \retval     none
*/
void rameccmu_monitor_interrupt_enable(rameccmu_monitor_enum rameccmu_monitor, uint32_t monitor_interrupt)
{
    RAMECCMU_MXCTL(rameccmu_monitor) |= (uint32_t)monitor_interrupt << 1U;
}

/*!
    \brief      disable RAMECCMU monitor ECC error interruput
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[in]  monitor_interrupt: RAMECCMU monitor interruput
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_INT_ECC_SINGLE_ERROR: ECC single error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR: ECC double error interrupt
      \arg        RAMECCMU_INT_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write interrupt
      \arg        RAMECCMU_INT_ECC_ERROR_LATCHING: ECC error latching
    \param[out] none
    \retval     none
*/
void rameccmu_monitor_interrupt_disable(rameccmu_monitor_enum rameccmu_monitor, uint32_t monitor_interrupt)
{
    RAMECCMU_MXCTL(rameccmu_monitor) &= (uint32_t)~((uint32_t)monitor_interrupt << 1U);
}

/*!
    \brief      get RAMECCMU monitor ECC error flag
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[in]  flag: RAMECCMU monitor flag
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_FLAG_ECC_SINGLE_ERROR: ECC single error detected and corrected flag
      \arg        RAMECCMU_FLAG_ECC_DOUBLE_ERROR: ECC double error detected flag
      \arg        RAMECCMU_FLAG_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write detected flag
    \param[out] none
    \retval     RESET or SET
*/
FlagStatus rameccmu_monitor_flag_get(rameccmu_monitor_enum rameccmu_monitor, uint32_t flag)
{
    if(RESET != ((RAMECCMU_MXSTAT(rameccmu_monitor)) & flag))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear RAMECCMU monitor ECC error flag
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[in]  flag: RAMECCMU monitor flag
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_FLAG_ECC_SINGLE_ERROR: ECC single error detected and corrected flag
      \arg        RAMECCMU_FLAG_ECC_DOUBLE_ERROR: ECC double error detected flag
      \arg        RAMECCMU_FLAG_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write detected flag
    \param[out] none
    \retval     none
*/
void rameccmu_monitor_flag_clear(rameccmu_monitor_enum rameccmu_monitor, uint32_t flag)
{
    RAMECCMU_MXSTAT(rameccmu_monitor) &= (uint32_t)(~flag);
}

/*!
    \brief      get RAMECCMU monitor ECC interrupt error flag
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[in]  int_flag: RAMECCMU monitor flag
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_INT_FLAG_ECC_SINGLE_ERROR: ECC single error detected and corrected flag
      \arg        RAMECCMU_INT_FLAG_ECC_DOUBLE_ERROR: ECC double error detected flag
      \arg        RAMECCMU_INT_FLAG_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write detected flag
    \param[out] none
    \retval     none
*/
FlagStatus rameccmu_monitor_interrupt_flag_get(rameccmu_monitor_enum rameccmu_monitor, uint32_t int_flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;

    /* get the status of interrupt enable bit */
    ret1 = RAMECCMU_MXCTL(rameccmu_monitor) & (uint32_t)(int_flag << 2U);
    /* get the status of interrupt flag */
    ret2 = RAMECCMU_MXSTAT(rameccmu_monitor) & int_flag;

    if(ret1 && ret2)
    {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    \brief      clear RAMECCMU monitor interrupt ECC error flag
    \param[in]  rameccmu_monitor: RAMECCMU monitor
                only one parameter can be selected which is shown as below:
      \arg        RAMECCMU0_MONITOR0: RAMECCMU0 monitor 0
      \arg        RAMECCMU0_MONITOR1: RAMECCMU0 monitor 1
      \arg        RAMECCMU0_MONITOR2: RAMECCMU0 monitor 2
      \arg        RAMECCMU0_MONITOR3: RAMECCMU0 monitor 3
      \arg        RAMECCMU0_MONITOR4: RAMECCMU0 monitor 4
      \arg        RAMECCMU1_MONITOR0: RAMECCMU1 monitor 0
      \arg        RAMECCMU1_MONITOR1: RAMECCMU1 monitor 1
      \arg        RAMECCMU1_MONITOR2: RAMECCMU1 monitor 2
    \param[in]  int_flag: RAMECCMU monitor flag
                one or more parameters can be selected which are shown as below:
      \arg        RAMECCMU_INT_FLAG_ECC_SINGLE_ERROR: ECC single error detected and corrected flag
      \arg        RAMECCMU_INT_FLAG_ECC_DOUBLE_ERROR: ECC double error detected flag
      \arg        RAMECCMU_INT_FLAG_ECC_DOUBLE_ERROR_BYTE_WRITE: ECC double error on byte write detected flag
    \param[out] none
    \retval     none
*/
void rameccmu_monitor_interrupt_flag_clear(rameccmu_monitor_enum rameccmu_monitor, uint32_t int_flag)
{
    RAMECCMU_MXSTAT(rameccmu_monitor) &= (uint32_t)(~int_flag);
}
