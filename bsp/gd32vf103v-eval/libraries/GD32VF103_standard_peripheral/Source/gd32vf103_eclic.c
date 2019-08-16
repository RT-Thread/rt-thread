/*!
    \file  gd32vf103_eclic.c
    \brief ECLIC(Enhancement Core-Local Interrupt Controller) driver

    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#include "gd32vf103_eclic.h"
#include "riscv_encoding.h"

#define REG_DBGMCU2       ((uint32_t)0xE0042008)
#define REG_DBGMCU2EN     ((uint32_t)0xE004200C)

/*!
    \brief      set the priority group
    \param[in]  prigroup: specify the priority group
      \arg        ECLIC_PRIGROUP_LEVEL0_PRIO4
      \arg        ECLIC_PRIGROUP_LEVEL1_PRIO3
      \arg        ECLIC_PRIGROUP_LEVEL2_PRIO2
      \arg        ECLIC_PRIGROUP_LEVEL3_PRIO1
      \arg        ECLIC_PRIGROUP_LEVEL4_PRIO0
    \param[out] none
    \retval     none
*/
void eclic_priority_group_set(uint32_t prigroup) {
    eclic_set_nlbits(prigroup);
}

/*!
    \brief      enable the interrupt request
    \param[in]  source: interrupt request, detailed in IRQn_Type
    \param[in]  level: the level needed to set (maximum is 16)
    \param[in]  priority: the priority needed to set (maximum is 16)
    \param[out] none
    \retval     none
*/
void eclic_irq_enable(uint32_t source, uint8_t level, uint8_t priority) {
    eclic_enable_interrupt(source);
    eclic_set_int_level(source, level);
    eclic_set_int_priority(source, priority);
}

/*!
    \brief      disable the interrupt request
    \param[in]  source: interrupt request, detailed in IRQn_Type
    \param[out] none
    \retval     none
*/
void eclic_irq_disable(uint32_t source) {
    eclic_disable_interrupt(source);
}

/*!
    \brief      reset system
    \param[in]  none
    \param[out] none
    \retval     none
*/
void eclic_system_reset(void) {
    REG32(REG_DBGMCU2EN) = 0x4b5a6978;
    REG32(REG_DBGMCU2) = 0x1;
}

/*!
    \brief      send event(SEV)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void eclic_send_event(void) {
    set_csr(0x812, 0x1);
}
