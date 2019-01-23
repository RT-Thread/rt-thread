/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-31     ZYH          first version
 * 2018-12-10     Zohar_Lee    format file
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <SWM320_port.h>
#include <rthw.h>

int rt_hw_sram_init(void)
{
    int i;
    PORT->PORTP_SEL0 = 0xAAAAAAAA; /* PP0-23 => ADDR0-23 */
    PORT->PORTP_SEL1 = 0xAAAA;
    PORT->PORTM_SEL0 = 0xAAAAAAAA; /* PM0-15 => DATA15-0 */
    PORT->PORTM_INEN |= 0xFFFF;
    PORT->PORTM_SEL1 = 0x2AA; /* PM16 => OEN、PM17 => WEN、PM18 => NORFL_CSN、PM19 => SDRAM_CSN、PM20 => SRAM_CSN、PM21 => SDRAM_CKE */

    /* 配置SRAM前需要刷新下SDRAM控制器 */

    SYS->CLKEN |= (1 << SYS_CLKEN_SDRAM_Pos);

    while (SDRAMC->REFDONE == 0);
    SDRAMC->REFRESH &= ~(1 << SDRAMC_REFRESH_EN_Pos);

    for (i = 0; i < 1000; i++)
    {
    }
    SYS->CLKEN &= ~(1 << SYS_CLKEN_SDRAM_Pos);

    SYS->CLKEN |= (1 << SYS_CLKEN_RAMC_Pos);

    SRAMC->CR = (9 << SRAMC_CR_RWTIME_Pos) |
                (0 << SRAMC_CR_BYTEIF_Pos) | // 16位接口
                (0 << SRAMC_CR_HBLBDIS_Pos); // 使能字节、半字访问

    return 0;
}
