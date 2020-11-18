/*!
    \file  gd32vf103_eclic.h
    \brief definitions for the ECLIC(Enhancement Core-Local Interrupt Controller)

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

#ifndef GD32VF103_ECLIC_H
#define GD32VF103_ECLIC_H

#include "gd32vf103.h"

/* constants definitions */
#define ECLIC_PRIGROUP_LEVEL0_PRIO4        0    /*!< 0 bits for level 4 bits for priority */
#define ECLIC_PRIGROUP_LEVEL1_PRIO3        1    /*!< 1 bits for level 3 bits for priority */
#define ECLIC_PRIGROUP_LEVEL2_PRIO2        2    /*!< 2 bits for level 2 bits for priority */
#define ECLIC_PRIGROUP_LEVEL3_PRIO1        3    /*!< 3 bits for level 1 bits for priority */
#define ECLIC_PRIGROUP_LEVEL4_PRIO0        4    /*!< 4 bits for level 0 bits for priority */

#define __SEV           eclic_send_event

/* function declarations */
/* set the priority group */
void eclic_priority_group_set(uint32_t prigroup);
/* enable the interrupt request */
void eclic_irq_enable(uint32_t source, uint8_t level, uint8_t priority);
/* disable the interrupt request */
void eclic_irq_disable(uint32_t source);

/* reset system */
void eclic_system_reset(void);
/* send event(SEV) */
void eclic_send_event(void);

#endif /* GD32VF103_ECLIC_H */
