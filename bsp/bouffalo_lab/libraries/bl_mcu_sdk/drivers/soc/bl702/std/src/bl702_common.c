/**
  ******************************************************************************
  * @file    bl702_common.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "l1c_reg.h"
#include "bl702_common.h"

/** @addtogroup  BL702_Periph_Driver
 *  @{
 */

/****************************************************************************/ /**
 * @brief      delay us
 *
 * @param[in]  core:  systemcoreclock
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
#ifdef ARCH_ARM
#ifndef __GNUC__
__WEAK
__ASM void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core, uint32_t cnt)
{
    lsrs r0, #0x10 muls r0, r1, r0 mov r2, r0 lsrs r2, #0x04 lsrs r2, #0x03 cmp r2, #0x01 beq end cmp r2, #0x00 beq end loop mov r0, r0 mov r0, r0 mov r0, r0 mov r0, r0 mov r0, r0 subs r2, r2, #0x01 cmp r2, #0x00 bne loop end bx lr
}
#else
__WEAK
void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core, uint32_t cnt)
{
    __asm__ __volatile__(
        "lsr r0,#0x10\n\t"
        "mul r0,r1,r0\n\t"
        "mov r2,r0\n\t"
        "lsr r2,#0x04\n\t"
        "lsr r2,#0x03\n\t"
        "cmp r2,#0x01\n\t"
        "beq end\n\t"
        "cmp r2,#0x00\n\t"
        "beq end\n"
        "loop :"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "mov r0,r0\n\t"
        "sub r2,r2,#0x01\n\t"
        "cmp r2,#0x00\n\t"
        "bne loop\n"
        "end :"
        "mov r0,r0\n\t");
}
#endif
#endif
#ifdef ARCH_RISCV
__WEAK
void ATTR_TCM_SECTION ASM_Delay_Us(uint32_t core, uint32_t cnt)
{
    uint32_t codeAddress = 0;
    uint32_t divVal = 40;

    codeAddress = (uint32_t)&ASM_Delay_Us;

    /* 1M=100K*10, so multiple is 10 */
    /* loop function take 4 instructions, so instructionNum is 4 */
    /* if codeAddress locate at IROM space and irom_2t_access is 1, then irom2TAccess=2, else irom2TAccess=1 */
    /* divVal = multiple*instructionNum*irom2TAccess */
    if (((codeAddress & (0xF << 24)) >> 24) == 0x01) {
        /* IROM space */
        if (BL_GET_REG_BITS_VAL(BL_RD_REG(L1C_BASE, L1C_CONFIG), L1C_IROM_2T_ACCESS)) {
            /* instruction 2T */
            divVal = 80;
        }
    }

    __asm__ __volatile__(
        ".align 4\n\t"
        "lw       a4,%1\n\t"
        "lui   a5,0x18\n\t"
        "addi  a5,a5,1696\n\t"
        "divu  a5,a4,a5\n\t"
        "sw       a5,%1\n\t"
        "lw       a4,%1\n\t"
        "lw       a5,%0\n\t"
        "mul   a5,a4,a5\n\t"
        "sw       a5,%1\n\t"
        "lw       a4,%1\n\t"
        "lw       a5,%2\n\t"
        "divu  a5,a4,a5\n\t"
        "sw    a5,%1\n\t"
        "lw    a5,%1\n\t"
        "li    a4,0x1\n\t"
        "beq   a5,zero,end\n\t"
        "beq   a5,a4,end\n\t"
        "nop\n\t"
        "nop\n\t"
        ".align 4\n\t"
        "loop  :\n"
        "addi  a4,a5,-1\n\t"
        "mv    a5,a4\n\t"
        "bnez  a5,loop\n\t"
        "nop\n\t"
        "end   :\n\t"
        "nop\n"
        :                                  /* output */
        : "m"(cnt), "m"(core), "m"(divVal) /* input */
        : "t1", "a4", "a5"                 /* destruct description */
    );
}
#endif
#endif

/****************************************************************************/ /**
 * @brief      delay us
 *
 * @param[in]  cnt:  delay cnt us
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION BL702_Delay_US(uint32_t cnt)
{
    ASM_Delay_Us(SystemCoreClockGet(), cnt);
}
#endif
/****************************************************************************/ /**
 * @brief      delay ms
 *
 * @param[in]  cnt:  delay cnt ms
 *
 * @return none
 *
 *******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION BL702_Delay_MS(uint32_t cnt)
{
    uint32_t i = 0;
    uint32_t count = 0;

    if (cnt >= 1024) {
        /* delay (n*1024) ms */
        count = 1024;

        for (i = 0; i < (cnt / 1024); i++) {
            BL702_Delay_US(1024 * 1000);
        }
    }

    if (cnt & 0x3FF) {
        /* delay (1-1023)ms */
        count = cnt & 0x3FF;
        BL702_Delay_US(count * 1000);
    }

    //BL702_Delay_US(((cnt<<10)-(cnt<<4)-(cnt<<3)));
}
#endif

/*
char *_sbrk(int incr)
{}
*/
/*@} end of group DRIVER_Public_Functions */

/*@} end of group DRIVER_COMMON */

/*@} end of group BL702_Periph_Driver */
