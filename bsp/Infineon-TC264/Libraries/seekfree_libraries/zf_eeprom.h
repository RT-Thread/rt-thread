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
 
#ifndef _zf_eeprom_h
#define _zf_eeprom_h

#include "common.h"
#include "IfxFlash_cfg.h"


#define EEPROM_BASE_ADDR             IFXFLASH_DFLASH_START					
#define EEPROM_SIZE                  IFXFLASH_DFLASH_SIZE					//一共有96KB
#define EEPROM_SECTOR_SIZE           (EEPROM_SIZE / IFXFLASH_DFLASH_NUM_LOG_SECTORS)
#define EEPROM_SECTOR_NUM            (IFXFLASH_DFLASH_NUM_LOG_SECTORS)		//一共有12个扇区

#define EEPROM_PAGE_SIZE             IFXFLASH_DFLASH_PAGE_LENGTH
#define EEPROM_SECTOR_PAGE_NUM       (EEPROM_SECTOR_SIZE/EEPROM_PAGE_SIZE)	//每个扇区有1024页


//-------------------------------------------------------------------------------------------------------------------
//  @brief      使用宏定义对flash进行数据读取
//  @param      sector_num 		需要写入的扇区编号
//  @param      page_num	 	需要读取的页
//  @param      type		 	读取的数据类型
//  @return     				返回给定地址的数据
//  @since      v1.0
//  Sample usage:               flash_read(0,0,uint32);//读取0号扇区  第0也数据 类型为uint32
//-------------------------------------------------------------------------------------------------------------------
#define     flash_read(sector_num,page_num,type)      (*(type *)((uint32)((EEPROM_BASE_ADDR + (sector_num)*EEPROM_SECTOR_SIZE) + (page_num*8))))

//-------------------------------------------------------------------------------------------------------------------
//  @brief      将浮点数转换为二进制数据
//  @param      float_data 		需要转换的浮点数
//  @return     				返回整型数据
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)




uint8 flash_check(uint32 sector_num, uint32 page_num);
void eeprom_erase_sector(uint32 sector_num);
void eeprom_page_program(uint32 sector_num, uint32 page_num, uint32 *buf);

#endif
