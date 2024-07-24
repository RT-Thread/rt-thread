/*!
    \file    gd32h7xx_hwsem.c
    \brief   HWSEM driver

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

#include "gd32h7xx_hwsem.h"

/*!
    \brief      try to lock the specific semaphore by writing process ID
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[in]  process: the process to lock the semaphore
                only one parameter can be selected which is shown as below:
      \arg        0 - 0xFF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_lock_set(hwsem_semaphore_enum semaphore, uint8_t process)
{
    uint32_t temp_mid = 0U, temp_pid = 0U;
    ErrStatus ret = ERROR;

    /* try to lock the semaphore */
    HWSEM_CTL(semaphore) = (uint32_t)(HWSEM_LOCK | CTL_MID(HWSEM_MASTER_ID) | CTL_PID(process));

    /* read the control register to confirm the semaphore is locked by target process or not */
    temp_mid = hwsem_master_id_get(semaphore);
    temp_pid = hwsem_process_id_get(semaphore);
    if((HWSEM_MASTER_ID == temp_mid) && (process == temp_pid))
    {
        ret = SUCCESS;
    }

    return ret;
}

/*!
    \brief      try to release the lock of the semaphore by writing process ID
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[in]  process: the process to unlock the semaphore
                only one parameter can be selected which is shown as below:
      \arg        0 - 0xFF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_lock_release(hwsem_semaphore_enum semaphore, uint8_t process)
{
    uint32_t lock_state = 0U;
    ErrStatus ret = ERROR;

    HWSEM_CTL(semaphore) = (uint32_t)(CTL_MID(HWSEM_MASTER_ID) | CTL_PID(process));

    lock_state = HWSEM_CTL(semaphore) & HWSEM_CTL_LK;
    if(0U == lock_state)
    {
        ret = SUCCESS;
    }

    return ret;
}

/*!
    \brief      try to lock the semaphore by reading
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_lock_by_reading(hwsem_semaphore_enum semaphore)
{
    ErrStatus ret = ERROR;

    if((uint32_t)(HWSEM_LOCK | CTL_MID(HWSEM_MASTER_ID)) == HWSEM_RLK(semaphore))
    {
        ret = SUCCESS;
    }

    return ret;
}

/*!
    \brief      unlock all semaphores of the master ID
    \param[in]  key: key value
      \arg        0 - 0xFFFF
    \param[out] none
    \retval     none
*/
ErrStatus hwsem_unlock_all(uint16_t key)
{
    ErrStatus ret = ERROR;

    HWSEM_UNLK = UNLK_KEY(key) | UNLK_MID(HWSEM_MASTER_ID);

    if(key == hwsem_key_get())
    {
        ret = SUCCESS;
    }
    return ret;
}

/*!
    \brief      get process ID of the specific semaphore
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     uint32_t: process ID of semaphore
*/
uint32_t hwsem_process_id_get(hwsem_semaphore_enum semaphore)
{
    return (uint32_t)(GET_CTL_PID(HWSEM_CTL(semaphore)));
}

/*!
    \brief      get master ID of the specific semaphore
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     uint32_t: master ID of semaphore
*/
uint32_t hwsem_master_id_get(hwsem_semaphore_enum semaphore)
{
    return (uint32_t)(GET_CTL_MID(HWSEM_CTL(semaphore)));
}

/*!
    \brief      get the lock status of the semaphore
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_lock_status_get(hwsem_semaphore_enum semaphore)
{
    FlagStatus ret = RESET;

    if(0U != (HWSEM_CTL(semaphore) & HWSEM_LOCK))
    {
        ret = SET;
    }

    return ret;
}

/*!
    \brief      set the key
    \param[in]  key: key value
      \arg        0 - 0xFFFF
    \param[out] none
    \retval     none
*/
void hwsem_key_set(uint16_t key)
{
    HWSEM_KEY = KEY_KEY(key);
}

/*!
    \brief      get the key
    \param[in]  none
    \param[out] none
    \retval     uint16_t: key to unlock all semaphores
*/
uint16_t hwsem_key_get(void)
{
    return ((uint16_t)GET_KEY_KEY(HWSEM_KEY));
}

/*!
    \brief      get the HWSEM flag status
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_flag_get(hwsem_semaphore_enum semaphore)
{
    FlagStatus ret = RESET;

    if(RESET != ((HWSEM_STAT >> semaphore) & 0x1U))
    {
        return SET;
    }

    return ret;
}

/*!
    \brief      clear HWSEM flag status
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     none
*/
void hwsem_flag_clear(hwsem_semaphore_enum semaphore)
{
    HWSEM_INTC = (1U << semaphore);
}

/*!
    \brief      get HWSEM interrupt flag status
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_interrupt_flag_get(hwsem_semaphore_enum semaphore)
{
    FlagStatus ret = RESET;

    if(RESET != ((HWSEM_INTF >> semaphore) & 0x1U))
    {
        ret = SET;
    }

    return ret;
}

/*!
    \brief      clear HWSEM interrupt flag
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_flag_clear(hwsem_semaphore_enum semaphore)
{
    HWSEM_INTC = (1U << semaphore);
}

/*!
    \brief      enable HWSEM interrupt
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_enable(hwsem_semaphore_enum semaphore)
{
    HWSEM_INTEN |= (1U << semaphore);
}

/*!
    \brief      disable HWSEM interrupt
    \param[in]  semaphore: semaphore index, refer to hwsem_semaphore_enum
                only one parameter can be selected which is shown as below:
      \arg        SEMx (x=0..31): semaphore x
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_disable(hwsem_semaphore_enum semaphore)
{
    HWSEM_INTEN &= (uint32_t)(~((uint32_t)1U << semaphore));
}
