/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef IOMUX_H_
#define IOMUX_H_



#include "fh_def.h"

#define PMU_PAD_RESETN           (0)
#define PMU_PAD_TEST             (1)
#define PMU_PAD_CIS_CLK          (2)
#define PMU_PAD_CIS_HSYNC        (3)
#define PMU_PAD_CIS_VSYNC        (4)
#define PMU_PAD_CIS_PCLK         (5)
#define PMU_PAD_CIS_D_0          (6)
#define PMU_PAD_CIS_D_1          (7)
#define PMU_PAD_CIS_D_2          (8)
#define PMU_PAD_CIS_D_3          (9)
#define PMU_PAD_CIS_D_4          (10)
#define PMU_PAD_CIS_D_5          (11)
#define PMU_PAD_CIS_D_6          (12)
#define PMU_PAD_CIS_D_7          (13)
#define PMU_PAD_CIS_D_8          (14)
#define PMU_PAD_CIS_D_9          (15)
#define PMU_PAD_CIS_D_10         (16)
#define PMU_PAD_CIS_D_11         (17)
#define PMU_PAD_MAC_REF_CLK      (18)
#define PMU_PAD_MAC_MDC          (19)
#define PMU_PAD_MAC_MDIO         (20)
#define PMU_PAD_MAC_COL          (21)
#define PMU_PAD_MAC_CRS          (22)
#define PMU_PAD_MAC_RXCK         (23)
#define PMU_PAD_MAC_RXD0         (24)
#define PMU_PAD_MAC_RXD1         (25)
#define PMU_PAD_MAC_RXD2         (26)
#define PMU_PAD_MAC_RXD3         (27)
#define PMU_PAD_MAC_RXDV         (28)
#define PMU_PAD_MAC_TXCK         (29)
#define PMU_PAD_MAC_TXD0         (30)
#define PMU_PAD_MAC_TXD1         (31)
#define PMU_PAD_MAC_TXD2         (32)
#define PMU_PAD_MAC_TXD3         (33)
#define PMU_PAD_MAC_TXEN         (34)
#define PMU_PAD_MAC_RXER         (35)
#define PMU_PAD_GPIO_0           (36)
#define PMU_PAD_GPIO_1           (37)
#define PMU_PAD_GPIO_2           (38)
#define PMU_PAD_GPIO_3           (39)
#define PMU_PAD_GPIO_4           (40)
#define PMU_PAD_GPIO_5           (41)
#define PMU_PAD_GPIO_6           (42)
#define PMU_PAD_GPIO_7           (43)
#define PMU_PAD_GPIO_8           (44)
#define PMU_PAD_GPIO_9           (45)
#define PMU_PAD_GPIO_10          (46)
#define PMU_PAD_GPIO_11          (47)
#define PMU_PAD_GPIO_12          (48)
#define PMU_PAD_GPIO_13          (49)
#define PMU_PAD_GPIO_14          (50)
#define PMU_PAD_GPIO_15          (51)
#define PMU_PAD_GPIO_16          (52)
#define PMU_PAD_GPIO_17          (53)
#define PMU_PAD_GPIO_18          (54)
#define PMU_PAD_GPIO_19          (55)
#define PMU_PAD_UART0_IN         (56)
#define PMU_PAD_UART0_OUT        (57)
#define PMU_PAD_CIS_SCL          (58)
#define PMU_PAD_CIS_SDA          (59)
#define PMU_PAD_SCL1             (60)
#define PMU_PAD_SDA1             (61)
#define PMU_PAD_SSI0_CLK         (62)
#define PMU_PAD_SSI0_TXD         (63)
#define PMU_PAD_SSI0_CSN_0       (64)
#define PMU_PAD_SSI0_CSN_1       (65)
#define PMU_PAD_SSI0_RXD         (66)
#define PMU_PAD_SD0_CD           (67)
#define PMU_PAD_SD0_WP           (68)
#define PMU_PAD_SD0_CLK          (69)
#define PMU_PAD_SD0_CMD_RSP      (70)
#define PMU_PAD_SD0_DATA_0       (71)
#define PMU_PAD_SD0_DATA_1       (72)
#define PMU_PAD_SD0_DATA_2       (73)
#define PMU_PAD_SD0_DATA_3       (74)
#define PMU_PAD_SD1_CLK          (75)
#define PMU_PAD_SD1_CD           (76)
#define PMU_PAD_SD1_WP           (77)
#define PMU_PAD_SD1_DATA_0       (78)
#define PMU_PAD_SD1_DATA_1       (79)
#define PMU_PAD_SD1_DATA_2       (80)
#define PMU_PAD_SD1_DATA_3       (81)
#define PMU_PAD_SD1_CMD_RSP      (82)
#define PMU_PAD_GPIO_60          (83)
#define PMU_PAD_GPIO_61          (84)
#define PMU_PAD_GPIO_62          (85)
#define PMU_PAD_GPIO_63          (86)
#define PMU_PAD_CLK_SW0          (87)
#define PMU_PAD_CLK_SW1          (88)
#define PMU_PAD_CLK_SW2          (89)
#define PMU_PAD_CLK_SW3          (90)
#define PMU_PAD_CRYSTAL          (91)
#define PMU_PAD_MAC_TXER         (92)


#define IOMUX_PADTYPE(n)		(Iomux_PadType##n *)
#define IOMUX_PUPD_NONE			0
#define IOMUX_PUPD_DOWN			1
#define IOMUX_PUPD_UP			2
#define IOMUX_PUPD_KEEPER		3
//#define IOMUX_DEBUG


typedef union
{
	struct
	{
		UINT32	sr								:1;
		UINT32	reserved_3_1					:3;

		UINT32	e8_e4							:2;
		UINT32	reserved_31_6					:24;

	}bit;
	UINT32 dw;
}Iomux_PadType5;

typedef union
{
	struct
	{
		UINT32	sr								:1;
		UINT32	reserved_3_1					:3;

		UINT32	e8_e4							:2;
		UINT32	reserved_7_6					:2;

		UINT32	mfs								:1;
		UINT32	reserved_31_9					:23;

	}bit;
	UINT32 dw;
}Iomux_PadType8;


typedef union
{
	struct
	{
		UINT32	smt								:1;
		UINT32	reserved_3_1					:3;

		UINT32	ie								:1;
		UINT32	reserved_7_5					:3;

		UINT32	pu_pd							:2;
		UINT32	reserved_31_10					:22;

	}bit;
	UINT32 dw;
}Iomux_PadType9;


typedef union
{
	struct
	{
		UINT32	e4_e2							:2;
		UINT32	reserved_3_2					:2;

		UINT32	smt								:1;
		UINT32	reserved_7_5					:3;

		UINT32	ie								:1;
		UINT32	reserved_11_9					:3;

		UINT32	mfs								:2;
		UINT32	reserved_31_14					:18;

	}bit;
	UINT32 dw;
}Iomux_PadType13;

typedef union
{
	struct
	{
		UINT32	sr								:1;
		UINT32	reserved_3_1					:3;

		UINT32	e8_e4							:2;
		UINT32	reserved_7_6					:2;

		UINT32	smt								:1;
		UINT32	reserved_11_9					:3;

		UINT32	ie								:1;
		UINT32	e								:1;	//only for PAD_MAC_REF_CLK_CFG (0x00a4)
		UINT32	reserved_15_12					:2;

		UINT32	pu_pd							:2;
		UINT32	reserved_31_18					:14;

	}bit;
	UINT32 dw;
}Iomux_PadType17;

typedef union
{
	struct
	{
		UINT32	sr								:1;
		UINT32	reserved_3_1					:3;

		UINT32	e4_e2							:2;
		UINT32	reserved_7_6					:2;

		UINT32	smt								:1;
		UINT32	reserved_11_9					:3;

		UINT32	ie								:1;
		UINT32	reserved_15_13					:3;

		UINT32	pu_pd							:2;
		UINT32	reserved_19_18					:2;

		UINT32	mfs								:1;
		UINT32	reserved_31_21					:11;

	}bit;
	UINT32 dw;
}Iomux_PadType20;


typedef union
{
	struct
	{
		UINT32	sr								:1;
		UINT32	reserved_3_1					:3;

		UINT32	e4_e2							:2;
		UINT32	reserved_7_6					:2;

		UINT32	smt								:1;
		UINT32	reserved_11_9					:3;

		UINT32	ie								:1;
		UINT32	reserved_15_13					:3;

		UINT32	pu_pd							:2;
		UINT32	reserved_19_18					:2;

		UINT32	mfs								:2;
		UINT32	reserved_31_21					:10;

	}bit;
	UINT32 dw;
}Iomux_PadType21;

typedef struct
{
    int id;
	UINT32* reg;
	UINT32 reg_offset;
	char* func_name[4];
	int reg_type;
	int func_sel;
	int drv_cur;
	int pupd;
	//UINT32 value;
}Iomux_Pad;

typedef struct
{
	void  *vbase;
	void  *pbase;
	Iomux_Pad *pads;
}Iomux_Object;


void fh_iomux_init(UINT32 base);
void fh_iomux_pin_switch(int pin_num, int func_num);





#endif /* IOMUX_H_ */


