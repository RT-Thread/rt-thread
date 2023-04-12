/**
    *****************************************************************************
    * @file     cmem7_aes.c
    *
    * @brief    CMEM7 AES source file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_aes.h"

BOOL AES_Decrypt(const void *src, void *dst, uint32_t len)
{
    uint32_t *po = dst;
    const uint32_t *pi = src;

    if (len & 0xF)
        return FALSE;

    AES->FIFO_CLEAR = 1;
    AES->FIFO_CLEAR = 0;
    GLOBAL_CTRL->AES_BURST_TYPE = 0x1;                      // Cannot be 0
    while (len > 0) {
        while (0 == GLOBAL_CTRL->AES_STATUS_b.IDLE);        // 0x41007010
        udelay(2);
        GLOBAL_CTRL->AES_TARGET_ADDR = (uint32_t)po;        // 0x41800000;
        po += 4;
        len -= 4 * sizeof(uint32_t);
        while (0 == GLOBAL_CTRL->AES_STATUS_b.RD_EMPTY);    // 0x41007010
        AES->FIFO = *pi++;
        AES->FIFO = *pi++;
        AES->FIFO = *pi++;
        AES->FIFO = *pi++;
    }
    return TRUE;
}
