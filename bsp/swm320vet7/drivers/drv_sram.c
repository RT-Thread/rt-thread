/*
 * File      : drv_sram.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-27     ZYH          first version
 */
#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <SWM320_port.h>
#include <rthw.h>
#ifdef BSP_USING_EXT_SRAM
int drv_sram_init(void)
{
    int i;
    PORT->PORTP_SEL0 = 0xAAAAAAAA;		//PP0-23 => ADDR0-23
	PORT->PORTP_SEL1 = 0xAAAA;
	PORT->PORTM_SEL0 = 0xAAAAAAAA;		//PM0-15 => DATA15-0
	PORT->PORTM_INEN |= 0xFFFF;
	PORT->PORTM_SEL1 = 0x2AA;			//PM16 => OEN、PM17 => WEN、PM18 => NORFL_CSN、PM19 => SDRAM_CSN、PM20 => SRAM_CSN、PM21 => SDRAM_CKE
	
	
	// 配置SRAM前需要刷新下SDRAM控制器
	do {
		SYS->CLKEN |=  (1 << SYS_CLKEN_SDRAM_Pos);
		
		while(SDRAMC->REFDONE == 0);
		SDRAMC->REFRESH &= ~(1 << SDRAMC_REFRESH_EN_Pos);
		
		for(i = 0; i < 1000; i++) 
        {
            
        }
		SYS->CLKEN &= ~(1 << SYS_CLKEN_SDRAM_Pos);
	} while(0);
	
	
	SYS->CLKEN |= (1 << SYS_CLKEN_RAMC_Pos);
	
	SRAMC->CR = (9 << SRAMC_CR_RWTIME_Pos) |
				(0 << SRAMC_CR_BYTEIF_Pos) |	// 16位接口
			    (0 << SRAMC_CR_HBLBDIS_Pos);	// 使能字节、半字访问

	return 0;
}
#endif

