/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		eeprom(Dflash)
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 

#include "IfxScuWdt.h"
#include "IfxFlash.h"
#include "zf_assert.h"
#include "zf_eeprom.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      校验FLASH是否有数据
//  @param      sector_num 		需要写入的扇区编号   参数范围0-11
//  @param      page_num	 	当前扇区页的编号     参数范围0-1023
//  @return     				返回1有数据，返回0没有数据，如果需要对有数据的区域写入新的数据则应该对所在扇区进行擦除操作
//  @since      v1.0
//  Sample usage:               flash_check(0,0);//校验0号扇区，第0页是否有数据
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_check(uint32 sector_num, uint32 page_num)
{
	ZF_ASSERT(EEPROM_SECTOR_NUM>sector_num);
	ZF_ASSERT(EEPROM_SECTOR_PAGE_NUM>page_num);
	uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;
	uint32 page_addr = sector_addr + page_num * IFXFLASH_DFLASH_PAGE_LENGTH;

	uint32 temp = *(uint32 *)page_addr;
	if(0 != temp)	return 1;

	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      擦除扇区
//  @param      sector_num 		需要写入的扇区编号   参数范围0-11
//  @return     void
//  @since      v1.0
//  Sample usage:               eeprom_erase_sector(0);
//-------------------------------------------------------------------------------------------------------------------
void eeprom_erase_sector(uint32 sector_num)
{
	ZF_ASSERT(EEPROM_SECTOR_NUM>sector_num);

	uint32 flash = 0;
	uint16 end_init_sfty_pw;
	uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;

	end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

	IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
    IfxFlash_eraseSector(sector_addr);
    IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);

    IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编程一页
//  @param      sector_num 		需要写入的扇区编号   参数范围0-11
//  @param      page_num 		需要写入的页编号     参数范围0-1023
//  @param      buf 		   	需要写入的数据地址   传入的数组类型必须为uint32
//  @return     void
//  @since      v1.0
//  Sample usage:				eeprom_page_program(0,0, &buf);
//-------------------------------------------------------------------------------------------------------------------
void eeprom_page_program(uint32 sector_num, uint32 page_num, uint32 *buf)
{
	ZF_ASSERT(EEPROM_SECTOR_NUM>sector_num);
	ZF_ASSERT(EEPROM_SECTOR_PAGE_NUM>page_num);

	uint32 errors = 0;
	uint32 flash = 0;
	uint16 end_init_sfty_pw;
	uint32 sector_addr = IfxFlash_dFlashTableEepLog[sector_num].start;

	end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

	uint32 page_addr = sector_addr + page_num * IFXFLASH_DFLASH_PAGE_LENGTH;
	errors = IfxFlash_enterPageMode(page_addr);
	ZF_ASSERT(0 == errors);

	IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);

	IfxFlash_loadPage(page_addr, buf[0], 0);

	IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
	IfxFlash_writePage(page_addr);
	IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);

	IfxFlash_waitUnbusy(flash, IfxFlash_FlashType_D0);
}

