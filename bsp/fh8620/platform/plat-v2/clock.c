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
 
#include "clock.h"
#include <rtdevice.h>
#include "fh_arch.h"
#include "libraries/inc/fh_timer.h"
#include "fh_pmu.h"
//#include "chip_reg.h"
//NEED_CAUTION.

#define TIMER_CLOCK 1000000
#define FH_CLK_DEBUG

#define FH_CLK_DIV_DEFAULT
//#define FH_CLK_GATE_DEFAULT

//#define FH_DBG_CLK

#define FH_CLK_DIV_DEFAULT_VALUE			0x55aaaa55
#define FH_CLK_GATE_DEFAULT_VALUE			0xaa5555aa

#define CONFIG_PAE_PTS_CLOCK   (1000000)
#define TICKS_PER_USEC         (CONFIG_PAE_PTS_CLOCK / 1000000)
#define REG_PAE_PTS_REG        (0xec100000 + 0x0040)



#define fh_clk_err(p,fmt,args...)\
		rt_kprintf("clk_err: %s->\t"fmt,p->name, ##args)

#ifdef FH_CLK_DEBUG
#define fh_clk_debug(p,fmt,args...)\
		rt_kprintf("%s:\t\t"fmt,p->name, ##args)


#define fh_clk_debug_no_handle(fmt,args...)\
		rt_kprintf(fmt, ##args)
#else
//#define fh_clk_err(p,fmt,args...)
#define fh_clk_debug(p,fmt,args...)
#define fh_clk_debug_no_handle(fmt,args...)
#endif

struct fh_clk_tree;

static struct fh_clk_tree fh_clk_tree;



#define __raw_writel(v,a)       (*(volatile unsigned int   *)(a) = (v))
#define __raw_readl(a)          (*(volatile unsigned int   *)(a))




#define FH_TIMER_WRITEL(offset,value)		__raw_writel(value,(fh_clk_tree.c_base_addr + offset))
#define FH_TIMER_READL(offset)				__raw_readl((fh_clk_tree.c_base_addr + offset))





enum clk_gate_enum{
#define CLK_GATE			(1)
#define CLK_UNGATE			(0)
	ISP_ACLK_GATE = (1<<0),
	HCLK_GATE = (1<<1),
	CPU_FCLK0_GATE = (1<<3),
	VCU_CLK_GATE = (1<<4),
	VOU_CLK_GATE = (1<<5),
	MCLK_GATE = (1<<6),
	SPI0_CLK_GATE = (1<<7),
	SPI1_CLK_GATE = (1<<8),
	SDC0_CLK_GATE = (1<<9),
	SDC1_CLK_GATE = (1<<10),
	AC_MCLK_GATE = (1<<11),  /////
	I2C0_CLK_GATE = (1<<12),
	UART0_CLK_GATE = (1<<13),
	UART1_CLK_GATE = (1<<14),
	//can't change
	WDT_CLK_GATE = (1<<15),

	PWM_CLK_GATE = (1<<16),
	TMR0_CLK_GATE = (1<<17),
	TMR1_CLK_GATE = (1<<18),
	PTS_CLK_GATE = (1<<19),
	MIPI_DPHY_CLK20M_GATE = (1<<20),
	MIPI_P32_CLK_GATE = (1<<21),
	PIX_CLK_GATE = (1<<22),			////
	CIS_CLK_OUT_GATE = (1<<23),
	I2S_SCLK_GATE = (1<<24),		//////
	ETH_REF_CLK_GATE = (1<<25),
	SADC_CLK_GATE = (1<<26),
	I2C1_CLK_GATE = (1<<27),
	ETH_RX_CLK_GATE = (1<<28), /////
	ETH_TX_CLK_GATE = (1<<29), /////
	ETH_RMII_CLK_GATE = (1<<30),////


};



//struct fh_clk;

typedef void (*clk_update)(struct fh_clk* p_clk);

//update func...
void 	clk_in_update(struct fh_clk* p_clk);
void 	pll1_clk_update(struct fh_clk* p_clk);
void	pll0_clk_update(struct fh_clk* p_clk);
void    cis_pclk_update(struct fh_clk* p_clk);
void	ddr_clk_update(struct fh_clk* p_clk);
void	ddr_clk_update(struct fh_clk* p_clk);
void	fclk_update(struct fh_clk* p_clk);
void	aclk_update(struct fh_clk* p_clk);
void	hclk_update(struct fh_clk* p_clk);
void	pclk_update(struct fh_clk* p_clk);
void	isp_aclk_update(struct fh_clk* p_clk);
void	vcu_clk_update(struct fh_clk* p_clk);
void	vou_clk_update(struct fh_clk* p_clk);
void	mipi_p32_clk_update(struct fh_clk* p_clk);
void	cis_clk_out_update(struct fh_clk* p_clk);
void	pts_update(struct fh_clk* p_clk);
void 	mipi_pix_clk_update(struct fh_clk* p_clk);
void	spi0_clk_update(struct fh_clk* p_clk);
void	spi1_clk_update(struct fh_clk* p_clk);
void	mipi_dphy_clk20m_update(struct fh_clk* p_clk);
void	i2c0_clk_update(struct fh_clk* p_clk);
void	i2c1_clk_update(struct fh_clk* p_clk);
void	uart0_clk_update(struct fh_clk* p_clk);
void	uart1_clk_update(struct fh_clk* p_clk);
void	pwm_clk_update(struct fh_clk* p_clk);
void	time0_clk_update(struct fh_clk* p_clk);
void	time1_clk_update(struct fh_clk* p_clk);
void	sadc_clk_update(struct fh_clk* p_clk);
void	sdc0_clk2x_update(struct fh_clk* p_clk);
void	sdc0_clk_update(struct fh_clk* p_clk);
void	sdc0_clk_out_update(struct fh_clk* p_clk);
void	sdc0_clk_sample_update(struct fh_clk* p_clk);
void	sdc0_clk_drv_update(struct fh_clk* p_clk);
void	sdc1_clk2x_update(struct fh_clk* p_clk);
void	sdc1_clk_update(struct fh_clk* p_clk);
void	sdc1_clk_out_update(struct fh_clk* p_clkt);
void	sdc1_clk_sample_update(struct fh_clk* p_clk);
void	sdc1_clk_drv_update(struct fh_clk* p_clk);
void 	eth_ref_clk_update(struct fh_clk* p_clk);
void	wdt_clk_update(struct fh_clk* p_clk);

rt_int32_t check_pix_clk_source(rt_uint32_t offset,rt_uint32_t mask,rt_uint32_t *value);
void	 pix_update(struct fh_clk* p_clk);

struct fh_clk_div{
//some has prediv....
//this two could have or......
#define PRE_DIV_CAL_ALREADY		(0x80000000)
#define PRE_DIV_ENABLE		(0x01)
#define DIV_ENABLE			(0x10)
	rt_uint32_t div_flag;

	rt_uint32_t pdiv_value;

	//rt_uint32_t hw_div_value;
	rt_uint32_t sw_div_value;
	rt_uint32_t sw_div_multi;
	//rt_uint32_t clk_in_hz;
	rt_uint32_t reg_offset;
	rt_uint32_t reg_mask;
	//rt_uint32_t rate;
};

struct fh_clk_mux{
//#define MUX_LEVEL_1		(1)
//#define MUX_LEVEL_2		(2)
//#define MAX_MUX_LEVEL	MUX_LEVEL_2
//	rt_uint32_t lev;
#define HAS_MUX				(0)
#define HAS_NO_MUX			(1)
	rt_uint32_t mux_flag;
	rt_uint32_t hw_mux_value;
	rt_uint32_t sw_mux_value;
	rt_uint32_t reg_offset;
	rt_uint32_t reg_mask;
};

struct fh_clk_gate{

#define HAS_GATE			(0)
#define HAS_NO_GATE			(1)
	rt_uint32_t gate_flag;
#define CLK_UNGATE			(0)
#define CLK_GATE			(1)
	//rt_uint32_t	hw_status;
	rt_uint32_t	sw_status;
	//rt_uint32_t value;

	rt_uint32_t reg_offset;
	rt_uint32_t reg_mask;

};






/***************
 *
 * level 1
 *
 ***************/
struct fh_clk_level_1{
	rt_uint32_t clk_in_out;
};


/***************
 *
 * level 2
 *
 ***************/
struct fh_clk_level_2{
	rt_uint32_t clk_in_out;
};

/***************
 *
 * level 3
 *
 ***************/
struct fh_clk_level_3_ddr{
	//rt_uint32_t mux_level;

	struct fh_clk_mux mux[2];
	struct fh_clk_gate gate;
	struct fh_clk_div div;
};

struct fh_clk_level_3_sdc{
#define DIFF_REFERENCE				(0x80000000)

	rt_uint32_t phase_diff;
	rt_uint32_t reg_offset;
	rt_uint32_t reg_mask;

};

struct fh_clk_level_3_gmac{

};

struct fh_clk_level_3_normal{
	struct fh_clk_mux mux;
	struct fh_clk_gate gate;
	struct fh_clk_div div;
};


struct fh_clk_level_3 {

#define LEVEL_PERI_NORMAL		(0x301)
#define LEVEL_PERI_DDR			(0x302)
#define LEVEL_PERI_SDC			(0x303)
#define LEVEL_PERI_GMAC			(0x304)
	rt_uint32_t peri_flag;
	union
	{
		struct fh_clk_level_3_ddr ddr;
		struct fh_clk_level_3_sdc sdc;
		struct fh_clk_level_3_gmac gmac;
		struct fh_clk_level_3_normal normal;
	}obj;

};




struct fh_clk {
	char *name;
#define LEVEL_CRYSTAL			(0x100)
#define LEVEL_PLL				(0x200)
#define LEVEL_PERIPHERAL		(0x300)
	rt_uint32_t level;

#define ROOT_NODE			(RT_NULL)
	struct fh_clk *parent;

	union
	{
		struct fh_clk_level_1 crystal;
		struct fh_clk_level_2 pll;
		struct fh_clk_level_3 peri;
	}clk;

	rt_uint32_t clk_out_rate;
#define CLK_HAS_NO_GATE				(0x80000000)
	rt_uint32_t gate;

	clk_update update_func;

	//struct fh_clk_tree *p_tree;
};

struct fh_clk_tree{
	rt_uint32_t c_base_addr;
	struct fh_clk **clk_head;
};



/*********
 *
 *
 * clk map....
 *
 *
 ********/
#define CRYSTAL_HZ			(24000000)
struct fh_clk clk_in = {
	.name = "clk_in",
	.level = LEVEL_CRYSTAL,
	.parent = ROOT_NODE,
	.clk.crystal.clk_in_out = CRYSTAL_HZ,
	//.clk_out_rate = clk_in.clk.crystal.clk_in_out,
	.clk_out_rate = CRYSTAL_HZ,
	.update_func = clk_in_update,
};



#define CIS_PCLK_HZ			(108000000)
struct fh_clk cis_pclk = {
	.name = "cis_pclk",
	.level = LEVEL_CRYSTAL,
	.parent = ROOT_NODE,
	.clk.crystal.clk_in_out = CIS_PCLK_HZ,
	//.clk_out_rate = clk_in.clk.crystal.clk_in_out,
	.clk_out_rate = CIS_PCLK_HZ,
	.update_func = cis_pclk_update,
};


#define PLL0_HZ				(864000000)
struct fh_clk pll0 = {
	.name = "pll0",
	.level = LEVEL_PLL,
	.parent = &clk_in,
	.clk.crystal.clk_in_out = PLL0_HZ,
	//.clk_out_rate = pll0.clk.crystal.clk_in_out,
	.clk_out_rate = PLL0_HZ,
	.update_func = pll0_clk_update,
};


#define PLL1_HZ				(600000000)
struct fh_clk pll1 = {
	.name = "pll1",
	.level = LEVEL_PLL,
	.parent = &clk_in,
	.clk.crystal.clk_in_out = PLL1_HZ,
	.clk_out_rate  = PLL1_HZ,
	.update_func = pll1_clk_update,

};


//NEED_CAUTION   parent not fix...
static struct fh_clk ddr_clk_normal = {
	.name = "ddr_normal",
	.level = LEVEL_PERIPHERAL,
	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_DDR,
	//0:xtal_clk
	//1:pll0_clk
#define MUX0_XTAL_CLK				(0)
#define MUX0_PLL0_CLK				(1)

	.clk.peri.obj.ddr.mux[0].reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.ddr.mux[0].reg_mask = 1<<0,

	//0:pll0 clk  default 864/2M
	//1:pll1 clk  default 600M
#define MUX1_PLL0_CLK				(0)
#define MUX1_PLL1_CLK				(1)
	.clk.peri.obj.ddr.mux[1].reg_offset = REG_PMU_CLK_SEL,
	.clk.peri.obj.ddr.mux[1].reg_mask = 1<<24,

	//gate
	//.clk.peri.obj.ddr.gate.enable_status = CLK_ENABLE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.ddr.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.ddr.gate.sw_status = CLK_UNGATE,
#endif
	.clk.peri.obj.ddr.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.ddr.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.ddr.gate.reg_mask = MCLK_GATE,



	//div
	//clk in maybe cry or pll
	.clk.peri.obj.ddr.div.div_flag = DIV_ENABLE,
	//.clk.peri.obj.ddr.div.pdiv_value = 2,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.ddr.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.ddr.div.sw_div_value = 1,
#endif
	.clk.peri.obj.ddr.div.sw_div_multi =1,
	.clk.peri.obj.ddr.div.reg_offset = REG_PMU_CLK_DIV1,
	.clk.peri.obj.ddr.div.reg_mask = 0xff <<0,

	.update_func = ddr_clk_update,
};








//NEED_CAUTION   parent not fix...
static struct fh_clk ddr_clk_div2 = {
	.name = "ddr_div2",
	.level = LEVEL_PERIPHERAL,
	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_DDR,
	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.ddr.mux[0].reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.ddr.mux[0].reg_mask = 1<<0,

	//0:pll0 clk  default 864/2M
	//1:pll1 clk  default 600M
	.clk.peri.obj.ddr.mux[1].reg_offset = REG_PMU_CLK_SEL,
	.clk.peri.obj.ddr.mux[1].reg_mask = 1<<24,

	//gate
	//.clk.peri.obj.ddr.gate.enable_status = CLK_ENABLE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.ddr.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.ddr.gate.sw_status = CLK_UNGATE,
#endif
	.clk.peri.obj.ddr.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.ddr.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.ddr.gate.reg_mask = MCLK_GATE,

	//div
	//clk in maybe cry or pll
	.clk.peri.obj.ddr.div.div_flag = PRE_DIV_ENABLE | DIV_ENABLE,
	.clk.peri.obj.ddr.div.pdiv_value = 2,
#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.ddr.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.ddr.div.sw_div_value = 1,
#endif
	.clk.peri.obj.ddr.div.sw_div_multi =1,
	.clk.peri.obj.ddr.div.reg_offset = REG_PMU_CLK_DIV1,
	.clk.peri.obj.ddr.div.reg_mask = 0xff <<0,


	.update_func = ddr_clk_update,
};



static struct fh_clk cpu_fclk = {
	.name = "cpu_fclk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_NO_GATE,
	//.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	//.clk.peri.obj.normal.gate.reg_mask = CPU_FCLK0_GATE,


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 0,
#endif

	.clk.peri.obj.normal.div.sw_div_multi =1,
	.clk.peri.obj.normal.div.reg_offset =REG_PMU_CLK_DIV0,
	.clk.peri.obj.normal.div.reg_mask = 0xff << 0,

	.update_func = fclk_update,

};


//NEED_CAUTION   parent not fix...
static struct fh_clk cpu_aclk = {
	.name = "cpu_aclk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,
//	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
//	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif


	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = CPU_FCLK0_GATE,


	//div
	.clk.peri.obj.normal.div.div_flag = PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.pdiv_value = 2,
//	.clk.peri.obj.normal.div.reg_offset =REG_PMU_CLK_DIV0,
//	.clk.peri.obj.normal.div.reg_mask = 0xff << 0,

	.update_func = aclk_update,

};




static struct fh_clk cpu_hclk = {
	.name = "cpu_hclk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_NO_GATE,
	//.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	//.clk.peri.obj.normal.gate.reg_mask = CPU_FCLK0_GATE,


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif
	.clk.peri.obj.normal.div.sw_div_multi =1,
	.clk.peri.obj.normal.div.reg_offset =REG_PMU_CLK_DIV0,
	.clk.peri.obj.normal.div.reg_mask = 0xff << 16,

	.update_func = hclk_update,
};
//NEED_CAUTION   parent not fix...

static struct fh_clk cpu_pclk = {
	.name = "cpu_pclk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif


	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = HCLK_GATE,


	//div
	.clk.peri.obj.normal.div.div_flag = PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.pdiv_value = 2,
//	.clk.peri.obj.normal.div.reg_offset =REG_PMU_CLK_DIV0,
//	.clk.peri.obj.normal.div.reg_mask = 0xff << 0,

	.update_func = pclk_update,

};


//NEED_CAUTION   parent not fix...
static struct fh_clk isp_aclk = {
	.name = "isp_aclk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = ISP_ACLK_GATE,
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif

	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV0,
	.clk.peri.obj.normal.div.reg_mask = 0x03 << 8,
	.clk.peri.obj.normal.div.sw_div_multi =1,


#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif

	.update_func = isp_aclk_update,

};

//
////NEED_CAUTION   parent not fix...
static struct fh_clk vcu_clk = {
	.name = "vcu_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = VCU_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV0,
	.clk.peri.obj.normal.div.reg_mask = 0x03 << 24,
	.clk.peri.obj.normal.div.sw_div_multi =1,



#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif


	.update_func = vcu_clk_update,

};

static struct fh_clk vou_clk = {
	.name = "vou_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = VOU_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV1,
	.clk.peri.obj.normal.div.reg_mask = 0x3f << 8,
	.clk.peri.obj.normal.div.sw_div_multi =1,


#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif

	.update_func = vou_clk_update,
};



static struct fh_clk mipi_p32_clk = {
	.name = "mipi_p32_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = MIPI_P32_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif

	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV2,
	.clk.peri.obj.normal.div.reg_mask = 0x0f << 16,
	.clk.peri.obj.normal.div.sw_div_multi =1,


#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif


	.update_func = mipi_p32_clk_update,

};



static struct fh_clk cis_clk_out = {
	.name = "cis_clk_out",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = CIS_CLK_OUT_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif



	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV1,
	.clk.peri.obj.normal.div.reg_mask = 0xff << 16,
	.clk.peri.obj.normal.div.sw_div_multi =1,


#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 3,
#endif

	.update_func = cis_clk_out_update,

};




static struct fh_clk pts_clk = {
	.name = "pts_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = PTS_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV2,
	.clk.peri.obj.normal.div.reg_mask = 0xff << 0,
	.clk.peri.obj.normal.div.sw_div_multi =1,
#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 35,
#endif

	.clk.peri.obj.normal.div.pdiv_value = 12,

	.update_func = pts_update,

};




static struct fh_clk mipi_pix_clk = {
	.name = "mipi_pix_clk_i",
	.level = LEVEL_PERIPHERAL,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_SYS_CTRL,
	.clk.peri.obj.normal.mux.reg_mask = 1<<0,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_NO_GATE,


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV2,
	.clk.peri.obj.normal.div.reg_mask = 0x0f << 24,
	.clk.peri.obj.normal.div.sw_div_multi =1,
#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 3,
#endif

	.update_func = mipi_pix_clk_update,


};



static struct fh_clk pix_clk = {
	.name = "pix_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	//0:xtal_clk
	//1:pll0_clk
#define CIS_PIX_CLK				(0)
#define CIS_PIX_CLK_OPPOSITE	(1)
#define MIPI_PIX_CLK			(2)

	.clk.peri.obj.normal.mux.reg_offset = REG_PMU_CLK_SEL,
	.clk.peri.obj.normal.mux.reg_mask = 3<<4,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = PIX_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif

	//div
	.clk.peri.obj.normal.div.div_flag = 0,



	.update_func = pix_update,

};






static struct fh_clk spi0_clk = {
	.name = "spi0_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,



	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,


	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = SPI0_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif

	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV3,
	.clk.peri.obj.normal.div.reg_mask = 0xff << 0,
	.clk.peri.obj.normal.div.sw_div_multi =1,


#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 11,
#endif

	.update_func = spi0_clk_update,

};




static struct fh_clk spi1_clk = {
	.name = "spi1_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,


	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,
	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = SPI1_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif



	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV3,
	.clk.peri.obj.normal.div.reg_mask = 0xff << 16,
	.clk.peri.obj.normal.div.sw_div_multi =1,



#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 11,
#endif

#ifdef RT_USING_SPI1
	.clk.peri.obj.normal.div.sw_div_value = 11,
#endif

	.update_func = spi1_clk_update,

};




static struct fh_clk mipi_dphy_clk20m = {
	.name = "mipi_dphy_clk20m",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = MIPI_DPHY_CLK20M_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif




	//div
	.clk.peri.obj.normal.div.div_flag = PRE_DIV_ENABLE,
//	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV3,
//	.clk.peri.obj.normal.div.reg_mask = 0xff << 16,
	.clk.peri.obj.normal.div.sw_div_multi =1,
	.clk.peri.obj.normal.div.pdiv_value = 30,
//	.clk.peri.obj.normal.div.sw_div_value = 11,

	.update_func = mipi_dphy_clk20m_update,
};



static struct fh_clk i2c0_clk = {
	.name = "i2c0_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = I2C0_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif




	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV4,
	.clk.peri.obj.normal.div.reg_mask = 0x3f << 16,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif

	.clk.peri.obj.normal.div.pdiv_value = 20,

	.update_func = i2c0_clk_update,

};


static struct fh_clk i2c1_clk = {
	.name = "i2c1_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = I2C1_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV4,
	.clk.peri.obj.normal.div.reg_mask = 0x3f << 24,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif
	.clk.peri.obj.normal.div.pdiv_value = 20,


	.update_func = i2c1_clk_update,
};


static struct fh_clk uart0_clk = {
	.name = "uart0_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = UART0_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif



	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV4,
	.clk.peri.obj.normal.div.reg_mask = 0x1f << 0,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif


	.clk.peri.obj.normal.div.pdiv_value = 10,


	.update_func = uart0_clk_update,

};

static struct fh_clk uart1_clk = {
	.name = "uart1_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = UART1_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif




	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV4,
	.clk.peri.obj.normal.div.reg_mask = 0x1f << 8,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 1,
#endif



	.clk.peri.obj.normal.div.pdiv_value = 10,

	.update_func = uart1_clk_update,

};




static struct fh_clk pwm_clk = {
	.name = "pwm_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = PWM_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif




	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV5,
	.clk.peri.obj.normal.div.reg_mask = 0x3f << 0,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 29,
#endif



	.clk.peri.obj.normal.div.pdiv_value = 20,

	.update_func = pwm_clk_update,
};



static struct fh_clk time0_clk = {
	.name = "time0_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,
	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = TMR0_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif



	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV5,
	.clk.peri.obj.normal.div.reg_mask = 0x3f << 16,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 29,
#endif



	.clk.peri.obj.normal.div.pdiv_value = 20,


	.update_func = time0_clk_update,

};


static struct fh_clk time1_clk = {
	.name = "time1_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,

	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = TMR1_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif




	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV5,
	.clk.peri.obj.normal.div.reg_mask = 0x3f << 24,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 29,
#endif


	.clk.peri.obj.normal.div.pdiv_value = 20,

	.update_func = time1_clk_update,

};




static struct fh_clk sadc_clk = {
	.name = "sadc_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = SADC_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif



	//div
	.clk.peri.obj.normal.div.div_flag = PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.sw_div_multi = 1,
	.clk.peri.obj.normal.div.pdiv_value = 120,

	.update_func = sadc_clk_update,

};



static struct fh_clk sdc0_clk2x = {
	.name = "sdc0_clk2x",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,

	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = SDC0_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif

	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV3,
	.clk.peri.obj.normal.div.reg_mask = 0x0f << 8,
	.clk.peri.obj.normal.div.sw_div_multi = 1,

#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 5,
#endif


	.clk.peri.obj.normal.div.pdiv_value = 2,

	.update_func = sdc0_clk2x_update,

};



static struct fh_clk sdc0_clk = {
	.name = "sdc0_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0 | DIFF_REFERENCE,
//	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
//	.clk.peri.obj.sdc.reg_mask = 0x0,

	.update_func = sdc0_clk_update,

};



static struct fh_clk sdc0_clk_out = {
	.name = "sdc0_clk_out",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0,
//	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
//	.clk.peri.obj.sdc.reg_mask = 0x0,

	.update_func = sdc0_clk_out_update,
};



static struct fh_clk sdc0_clk_sample = {
	.name = "sdc0_clk_sample",
	.level = LEVEL_PERIPHERAL,

	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0,
	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
	.clk.peri.obj.sdc.reg_mask = 3<16,


	.update_func = sdc0_clk_sample_update,
};

static struct fh_clk sdc0_clk_drive = {
	.name = "sdc0_clk_drive",
	.level = LEVEL_PERIPHERAL,

	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0,
	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
	.clk.peri.obj.sdc.reg_mask = 3<20,


	.update_func = sdc0_clk_drv_update,
};




static struct fh_clk sdc1_clk2x = {
	.name = "sdc1_clk2x",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = SDC1_CLK_GATE,

#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif



	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV3,
	.clk.peri.obj.normal.div.reg_mask = 0x0f << 24,
	.clk.peri.obj.normal.div.sw_div_multi = 1,
#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 5,
#endif


	.clk.peri.obj.normal.div.pdiv_value = 2,


	.update_func = sdc1_clk2x_update,
};



static struct fh_clk sdc1_clk = {
	.name = "sdc1_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0 | DIFF_REFERENCE,
//	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
//	.clk.peri.obj.sdc.reg_mask = 0x0,

	.update_func = sdc1_clk_update,
};



static struct fh_clk sdc1_clk_out = {
	.name = "sdc1_clk_out",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0,
//	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
//	.clk.peri.obj.sdc.reg_mask = 0x0,

	.update_func = sdc1_clk_out_update,
};



static struct fh_clk sdc1_clk_sample = {
	.name = "sdc1_clk_sample",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0,
	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
	.clk.peri.obj.sdc.reg_mask = 3<8,

	.update_func = sdc1_clk_sample_update,
};

static struct fh_clk sdc1_clk_drive = {
	.name = "sdc1_clk_drive",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_SDC,
	.clk.peri.obj.sdc.phase_diff = DIFF_SDC_REFCLK_0,
	.clk.peri.obj.sdc.reg_offset = REG_PMU_CLK_SEL,
	.clk.peri.obj.sdc.reg_mask = 3<12,

	.update_func = sdc1_clk_drv_update,
};





static struct fh_clk eth_ref_clk = {
	.name = "eth_ref_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,

	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_GATE,
	.clk.peri.obj.normal.gate.reg_offset = REG_PMU_CLK_GATE,
	.clk.peri.obj.normal.gate.reg_mask = ETH_REF_CLK_GATE,


#ifdef FH_CLK_GATE_DEFAULT
	.clk.peri.obj.normal.gate.sw_status = FH_CLK_GATE_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.gate.sw_status = CLK_UNGATE,
#endif


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE | PRE_DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV6,
	.clk.peri.obj.normal.div.reg_mask = 0x0f << 24,
	.clk.peri.obj.normal.div.sw_div_multi = 1,


#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 5,
#endif




	.clk.peri.obj.normal.div.pdiv_value = 2,


	.update_func = eth_ref_clk_update,
};




static struct fh_clk wdt_clk = {
	.name = "wdt_clk",
	.level = LEVEL_PERIPHERAL,
//	//.parent = &clk_in,
	.clk.peri.peri_flag = LEVEL_PERI_NORMAL,
	.clk.peri.obj.normal.mux.mux_flag = HAS_NO_MUX,

	//gate
	.clk.peri.obj.normal.gate.gate_flag = HAS_NO_GATE,


	//div
	.clk.peri.obj.normal.div.div_flag = DIV_ENABLE,
	.clk.peri.obj.normal.div.reg_offset = REG_PMU_CLK_DIV5,
	.clk.peri.obj.normal.div.reg_mask = 0x3f << 8,
	.clk.peri.obj.normal.div.sw_div_multi = 1,



#ifdef FH_CLK_DIV_DEFAULT
	.clk.peri.obj.normal.div.sw_div_value = FH_CLK_DIV_DEFAULT_VALUE,
#else
	.clk.peri.obj.normal.div.sw_div_value = 29,
#endif


	.update_func = wdt_clk_update,
};



struct fh_clk *fh_clk_array[] = {
		&clk_in,
		&cis_pclk,
		&pll0,
		&pll1,
		&ddr_clk_normal,
		&ddr_clk_div2,
		&cpu_fclk,
		&cpu_aclk,
		&cpu_hclk,
		&cpu_pclk,
		&isp_aclk,
		&vcu_clk,
		&vou_clk,
		&mipi_p32_clk,
		&cis_clk_out,
		&pts_clk,
		&mipi_pix_clk,
		&pix_clk,

		//pll1
		&sdc0_clk2x,
		&sdc0_clk,
		&sdc0_clk_out,
		&sdc0_clk_sample,
		&sdc0_clk_drive,

		&sdc1_clk2x,
		&sdc1_clk,
		&sdc1_clk_out,
		&sdc1_clk_sample,
		&sdc1_clk_drive,


		&spi0_clk,
		&spi1_clk,
		&mipi_dphy_clk20m,
		&i2c0_clk,
		&i2c1_clk,
		&uart0_clk,
		&uart1_clk,
		&pwm_clk,
		&time0_clk,
		&time1_clk,
		&sadc_clk,
		&eth_ref_clk,

		&wdt_clk,


};

static inline rt_int32_t wrap_read_reg(rt_uint32_t offset, rt_uint32_t mask,
		rt_uint32_t *value)
{
	rt_uint32_t temp_v, temp_shift;

	/*	if(fh_pmu_status() == PMU_STATUS_CLOSE)
	 return -1;*/
	temp_v = FH_TIMER_READL(offset);
	temp_v &= mask;
	temp_shift = __rt_ffs(mask);
	temp_v = temp_v >> (temp_shift - 1);
	*value = temp_v;
	return 0;
}

static inline rt_int32_t wrap_write_reg(rt_uint32_t offset, rt_uint32_t mask,
		rt_uint32_t value)
{
	rt_uint32_t temp_v, temp_shift;

	/*
	 if(fh_pmu_status() == PMU_STATUS_CLOSE)
	 return -1;
	 */

	temp_v = FH_TIMER_READL(offset);
	temp_v &= ~mask;
	temp_shift = __rt_ffs(mask);
	temp_v |= value << (temp_shift - 1);
	FH_TIMER_WRITEL(offset, temp_v);
	return 0;
}

rt_int32_t check_pix_clk_source(rt_uint32_t offset, rt_uint32_t mask,
		rt_uint32_t *value)
{
	rt_uint32_t mux0;
	rt_int32_t ret;
	ret = wrap_read_reg(offset, mask, &mux0);

	if (ret != 0) {
		return ret;
	}

	*value = mux0;
	return 0;
}

rt_int32_t check_xtal_pll0(rt_uint32_t offset, rt_uint32_t mask,
		rt_uint32_t *value)
{
	rt_uint32_t mux0;
	rt_int32_t ret;
	ret = wrap_read_reg(offset, mask, &mux0);

	if (ret != 0) {
		return ret;
	}
	if (mux0 == MUX0_PLL0_CLK)
		*value = MUX0_PLL0_CLK;
	else
		*value = MUX0_XTAL_CLK;

	return 0;
}

void cal_pll0_prediv(rt_uint32_t *div_flag, rt_uint32_t *pre_value)
{

	if (!(*div_flag & PRE_DIV_CAL_ALREADY)) {
		//before has got the prediv value..
		if (*div_flag & PRE_DIV_ENABLE) {

			*pre_value *= 2;
		} else {
			*pre_value = 2;
		}
		*div_flag |= PRE_DIV_ENABLE | PRE_DIV_CAL_ALREADY;
	}

}

rt_int32_t sw_div_process(rt_uint32_t div_flag, rt_uint32_t offset,
		rt_uint32_t mask, rt_uint32_t *div_value)
{

	//rt_kprintf("----------div go----------\n");
	rt_uint32_t div;
	rt_int32_t ret;
	if (div_flag & DIV_ENABLE) {
		ret = wrap_read_reg(offset, mask, &div);
		if (ret != 0) {
			return ret;
		}

//
//		rt_kprintf("hw value is %x\n",div);
//		rt_kprintf("sw value is %x\n",div_value);
//
//		rt_kprintf("offset is %x,value :%x\n",offset + 0xf0000000,*(rt_uint32_t*)(offset + 0xf0000000));
//		rt_kprintf("mask is %x\n",mask);

		//if use the hw default value....

		if (*div_value == FH_CLK_DIV_DEFAULT_VALUE) {
			*div_value = div;
			return 0;
		}

		if (div != *div_value) {
			ret = wrap_write_reg(offset, mask, *div_value);
			if (ret != 0) {
				return ret;
			}
		}
	}
	//rt_kprintf("----------div done----------\n");
	return 0;
	//*div_flag |= PRE_DIV_ENABLE;
}

void cal_baud_hz(rt_uint32_t clk_in, rt_uint32_t div_flag, rt_uint32_t pre_div,
		rt_uint32_t div, rt_uint32_t div_multi, rt_uint32_t *baud_out)
{
	//div += 1;
	if (div_flag & PRE_DIV_ENABLE) {
		*baud_out = (clk_in / pre_div);
	} else {
		*baud_out = clk_in;
	}

	if (div_flag & DIV_ENABLE) {
		*baud_out /= ((div + 1) * div_multi);
	}

}

void cal_baud_div(rt_uint32_t clk_in, rt_uint32_t div_flag, rt_uint32_t pre_div,
		rt_uint32_t *div, rt_uint32_t div_multi, rt_uint32_t baud_out)
{
	//div += 1;
	rt_uint32_t temp_baud_hz, temp_baud_div;

	if (div_flag & DIV_ENABLE) {
		if (div_flag & PRE_DIV_ENABLE) {
			temp_baud_hz = (clk_in / pre_div);
		} else {
			temp_baud_hz = clk_in;
		}
		temp_baud_div = temp_baud_hz / baud_out;
		*div = temp_baud_div - 1;
	}

}

rt_int32_t process_gate(rt_uint32_t gate_flag, rt_uint32_t reg_offset,
		rt_uint32_t reg_mask, rt_uint32_t *sw_status,
		rt_uint32_t *pclk_status)
{
	//rt_kprintf("----------gate go----------\n");
	rt_uint32_t hw_gate;
	rt_int32_t ret;
	if (gate_flag == HAS_GATE) {
		ret = wrap_read_reg(reg_offset, reg_mask, &hw_gate);
		if (ret != 0) {
			return ret;
		}

		if (*sw_status == FH_CLK_GATE_DEFAULT_VALUE) {
			*sw_status = hw_gate;
			*pclk_status = *sw_status;
			return 0;
		}

//		rt_kprintf("gate hw is :%x\n",hw_gate);
//		rt_kprintf("gate sw is :%x\n",sw_status);
		if (hw_gate != *sw_status) {
			//update the gate..
//			rt_kprintf("gate reg offset is :%x\n",reg_offset);
//			rt_kprintf("gate reg mask is :%x\n",reg_mask);
//			rt_kprintf("gate reg write is :%x\n",sw_status);
			ret = wrap_write_reg(reg_offset, reg_mask, *sw_status);
			if (ret != 0) {
				return ret;
			}
		}

		*pclk_status = *sw_status;
	}

	else {
		*pclk_status |= CLK_HAS_NO_GATE;
	}
	//rt_kprintf("---------gate done---------\n");
	return 0;

}

void clk_handle(struct fh_clk* p_clk, struct fh_clk *parent)
{
	//rt_uint32_t div;
	//rt_uint32_t sw_gate;
	rt_uint32_t phase;
	rt_int32_t ret;
	p_clk->parent = parent;
//	switch
	//fh_clk_debug(p_clk,"----parent----\t ----clk out rate----\n ");
	if (p_clk->parent)
		//rt_kprintf("%-8.*s 0x%02x", RT_NAME_MAX, thread->name, thread->current_priority);
		fh_clk_debug(p_clk, "parent:'%s'\n", p_clk->parent->name);
	else
		fh_clk_debug(p_clk, "'root node'\n");

	switch (p_clk->level) {

	case LEVEL_CRYSTAL:
		//fh_clk_debug(p_clk,"clk out:%d\n",p_clk->clk_out_rate);
		break;
	case LEVEL_PLL:
		//fh_clk_debug(p_clk,"%d\n",p_clk->clk_out_rate);
		break;
	case LEVEL_PERIPHERAL:

		switch (p_clk->clk.peri.peri_flag) {

		case LEVEL_PERI_NORMAL:
			//div = p_clk->clk.peri.obj.normal.div.sw_div_value;
			ret =
					sw_div_process(
							p_clk->clk.peri.obj.normal.div.div_flag,
							p_clk->clk.peri.obj.normal.div.reg_offset,
							p_clk->clk.peri.obj.normal.div.reg_mask,
							&p_clk->clk.peri.obj.normal.div.sw_div_value);

			if (ret != 0) {
				fh_clk_err(p_clk,
						"div process failed.error no:%x\n",
						ret);
				break;
			}

			//fh_clk_debug(p_clk,"hw div is %d\n",p_clk->clk.peri.obj.ddr.div.hw_div_value);
//			fh_clk_debug(p_clk,"sw div is %d\n",p_clk->clk.peri.obj.normal.div.sw_div_value);
//			fh_clk_debug(p_clk,"pre div is %d\n",p_clk->clk.peri.obj.normal.div.pdiv_value);
//			fh_clk_debug(p_clk,"clk in is %d\n",p_clk->parent->clk_out_rate);
//			fh_clk_debug(p_clk,"peri flag is %x\n",p_clk->clk.peri.obj.normal.div.div_flag);
			//hw will self add 1..

			cal_baud_hz(p_clk->parent->clk_out_rate,
					p_clk->clk.peri.obj.normal.div.div_flag,
					p_clk->clk.peri.obj.normal.div.pdiv_value,
					p_clk->clk.peri.obj.normal.div.sw_div_value,
					p_clk->clk.peri.obj.normal.div.sw_div_multi,
					&p_clk->clk_out_rate);

			//fh_clk_debug_no_handle("%d\n",p_clk->clk_out_rate);
			//fix the gate..
			//sw_gate = p_clk->clk.peri.obj.normal.gate.sw_status;
			ret =
					process_gate(
							p_clk->clk.peri.obj.normal.gate.gate_flag,
							p_clk->clk.peri.obj.normal.gate.reg_offset,
							p_clk->clk.peri.obj.normal.gate.reg_mask,
							&p_clk->clk.peri.obj.normal.gate.sw_status,
							&p_clk->gate);

			if (ret != 0) {
				fh_clk_err(p_clk,
						"gate process failed.error no:%x\n",
						ret);
				break;
			}

			break;
		case LEVEL_PERI_DDR:
			//rt_uint32_t mux0,mux1;
			//div = p_clk->clk.peri.obj.ddr.div.sw_div_value;

			ret =
					sw_div_process(
							p_clk->clk.peri.obj.ddr.div.div_flag,
							p_clk->clk.peri.obj.ddr.div.reg_offset,
							p_clk->clk.peri.obj.ddr.div.reg_mask,
							&p_clk->clk.peri.obj.ddr.div.sw_div_value);

			if (ret != 0) {
				fh_clk_err(p_clk,
						"div process failed.error no:%x\n",
						ret);
				break;
			}

//			fh_clk_debug(p_clk,"sw div is %d\n",p_clk->clk.peri.obj.ddr.div.sw_div_value);
//			fh_clk_debug(p_clk,"pre div is %d\n",p_clk->clk.peri.obj.ddr.div.pdiv_value);
//			fh_clk_debug(p_clk,"clk in is %d\n",p_clk->parent->clk_out_rate);
//			fh_clk_debug(p_clk,"peri flag is %x\n",p_clk->clk.peri.obj.ddr.div.div_flag);

			cal_baud_hz(p_clk->parent->clk_out_rate,
					p_clk->clk.peri.obj.ddr.div.div_flag,
					p_clk->clk.peri.obj.ddr.div.pdiv_value,
					p_clk->clk.peri.obj.ddr.div.sw_div_value,
					p_clk->clk.peri.obj.ddr.div.sw_div_multi,
					&p_clk->clk_out_rate);

			//fh_clk_debug_no_handle("%d\n",p_clk->clk_out_rate);
			//fix the gate..
			//fh_clk_debug(p_clk,"gate reg add is:%x\t mask is:%x\n",p_clk->clk.peri.obj.ddr.gate.reg_offset,p_clk->clk.peri.obj.ddr.gate.reg_mask);
			//sw_gate = p_clk->clk.peri.obj.ddr.gate.sw_status;

			ret = process_gate(
					p_clk->clk.peri.obj.ddr.gate.gate_flag,
					p_clk->clk.peri.obj.ddr.gate.reg_offset,
					p_clk->clk.peri.obj.ddr.gate.reg_mask,
					&p_clk->clk.peri.obj.ddr.gate.sw_status,
					&p_clk->gate);

			if (ret != 0) {
				fh_clk_err(p_clk,
						"gate process failed.error no:%x\n",
						ret);
				break;
			}

			break;
		case LEVEL_PERI_SDC:
			//just need to handle the phase....
			p_clk->clk_out_rate = p_clk->parent->clk_out_rate;
			if (p_clk->clk.peri.obj.sdc.phase_diff & DIFF_REFERENCE) {
				//fh_clk_debug(p_clk,"this is the reference..no need to process..\n");
				break;
			}

			//baud ...

			//phase..
			//fh_clk_debug_no_handle("%d\n",p_clk->clk_out_rate);
			//hw status..
			ret = wrap_read_reg(p_clk->clk.peri.obj.sdc.reg_offset,
					p_clk->clk.peri.obj.sdc.reg_mask,
					&phase);

			if (ret != 0) {
				fh_clk_err(p_clk,
						"read pmu failed.error no:%x\n",
						ret);
				break;
			}

//			fh_clk_debug(p_clk,"hw phase is :%x\n",phase);
//			fh_clk_debug(p_clk,"sw phase is :%x\n",p_clk->clk.peri.obj.sdc.phase_diff);
			if (phase != p_clk->clk.peri.obj.sdc.phase_diff) {
				//update the hw para..
				ret =
						wrap_write_reg(
								p_clk->clk.peri.obj.sdc.reg_offset,
								p_clk->clk.peri.obj.sdc.reg_mask,
								p_clk->clk.peri.obj.sdc.phase_diff);
				if (ret != 0) {
					fh_clk_err(p_clk,
							"write pmu failed.error no:%x\n",
							ret);
					break;
				}
			}

			break;
		case LEVEL_PERI_GMAC:
			break;
		default:
			break;

		}
	}

	fh_clk_debug(p_clk, "clk out:%d\n", p_clk->clk_out_rate);

}

//
void clk_in_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, RT_NULL);
}

void cis_pclk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, RT_NULL);
}

void pll1_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &clk_in);
}

void pll0_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &clk_in);
}

void ddr_clk_update(struct fh_clk* p_clk)
{

	//check if pll0 or pll1
	rt_uint32_t mux0, mux1;
	rt_int32_t ret;
	struct fh_clk* parent;
	//1 step: fix the parent..
	ret = wrap_read_reg(p_clk->clk.peri.obj.ddr.mux[1].reg_offset,
			p_clk->clk.peri.obj.ddr.mux[1].reg_mask, &mux1);
	if (ret != 0) {
		fh_clk_err(p_clk, "read pmu failed.error no:%x\n", ret);
		return;
	}

	if (mux1 == MUX1_PLL0_CLK) {
		ret = check_xtal_pll0(p_clk->clk.peri.obj.ddr.mux[0].reg_offset,
				p_clk->clk.peri.obj.ddr.mux[0].reg_mask, &mux0);
		if (ret != 0) {
			fh_clk_err(p_clk, "read pmu failed.error no:%x\n", ret);
			return;
		}
		if (mux0 == MUX0_PLL0_CLK) {
			//ddr normal parent is pll0
			parent = &pll0;
		} else {
			//ddr normal parent is xtal
			parent = &clk_in;
		}
	} else {
		//ddr normal parent is pll1
		parent = &pll1;
	}
	p_clk->clk.peri.obj.ddr.mux[0].mux_flag = HAS_MUX;
	p_clk->clk.peri.obj.ddr.mux[1].mux_flag = HAS_MUX;
	clk_handle(p_clk, parent);

}

void fclk_update(struct fh_clk* p_clk)
{

	//check if pll0 or xtal
	rt_uint32_t mux0;
	rt_int32_t ret;
	struct fh_clk* parent;	//1 step: fix the parent..

	//mux0 = check_xtal_pll0(p_clk->clk.peri.obj.ddr.mux[0].reg_offset,p_clk->clk.peri.obj.ddr.mux[0].reg_mask);
	ret = check_xtal_pll0(p_clk->clk.peri.obj.normal.mux.reg_offset,
			p_clk->clk.peri.obj.normal.mux.reg_mask, &mux0);
	if (ret != 0) {
		fh_clk_err(p_clk, "read pmu failed.error no:%x\n", ret);
		return;
	}

	//fh_clk_debug(p_clk,"mux0 wrap value is %x\n",mux0);
	if (mux0 == MUX0_PLL0_CLK) {
		//ddr normal parent is pll0
		parent = &pll0;
	} else {
		//ddr normal parent is xtal
		parent = &clk_in;
	}
	p_clk->clk.peri.obj.normal.mux.mux_flag = HAS_MUX;
	//2 step:fix the div...
	if (mux0 == MUX0_PLL0_CLK) {
		//cal_pll0_prediv(&p_clk->clk.peri.obj.ddr.div.div_flag,&p_clk->clk.peri.obj.ddr.div.pdiv_value);
		cal_pll0_prediv(&p_clk->clk.peri.obj.normal.div.div_flag,
				&p_clk->clk.peri.obj.normal.div.pdiv_value);
	}
	clk_handle(p_clk, parent);
}

void pix_update(struct fh_clk* p_clk)
{

	//check if pll0 or xtal
	rt_uint32_t mux0;
	rt_int32_t ret;
	struct fh_clk* parent;	//1 step: fix the parent..
#if(1)
	//mux0 = check_xtal_pll0(p_clk->clk.peri.obj.ddr.mux[0].reg_offset,p_clk->clk.peri.obj.ddr.mux[0].reg_mask);
	ret = check_pix_clk_source(p_clk->clk.peri.obj.normal.mux.reg_offset,
			p_clk->clk.peri.obj.normal.mux.reg_mask, &mux0);
	if (ret != 0) {
		fh_clk_err(p_clk, "read pmu failed.error no:%x\n", ret);
		return;
	}
//#define CIS_PIX_CLK				(0)
//#define CIS_PIX_CLK_OPPOSITE	(1)
//#define MIPI_PIX_CLK			(2)

	//fh_clk_debug(p_clk,"mux0 wrap value is %x\n",mux0);
	if (mux0 == CIS_PIX_CLK || mux0 == CIS_PIX_CLK_OPPOSITE) {
		//ddr normal parent is pll0
		parent = &cis_pclk;
	} else {
		parent = &mipi_pix_clk;
	}
	p_clk->clk.peri.obj.normal.mux.mux_flag = HAS_MUX;

#endif
	clk_handle(p_clk, parent);
}

void aclk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &cpu_fclk);

}

void hclk_update(struct fh_clk* p_clk)
{

	fclk_update(p_clk);
}

void pclk_update(struct fh_clk* p_clk)
{

	clk_handle(p_clk, &cpu_hclk);
}

void isp_aclk_update(struct fh_clk* p_clk)
{

	fclk_update(p_clk);
}

void vcu_clk_update(struct fh_clk* p_clk)
{
	fclk_update(p_clk);
}

void vou_clk_update(struct fh_clk* p_clk)
{
	fclk_update(p_clk);
}

void mipi_p32_clk_update(struct fh_clk* p_clk)
{
	fclk_update(p_clk);
}

void cis_clk_out_update(struct fh_clk* p_clk)
{
	fclk_update(p_clk);
}

void pts_update(struct fh_clk* p_clk)
{
	fclk_update(p_clk);
}

void mipi_pix_clk_update(struct fh_clk* p_clk)
{
	fclk_update(p_clk);
}

void spi0_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void spi1_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void mipi_dphy_clk20m_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void i2c0_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void i2c1_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void uart0_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void pwm_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void time0_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void time1_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void uart1_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void sadc_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

//sdc0...
void sdc0_clk2x_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void sdc0_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc0_clk2x);
}

void sdc0_clk_out_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc0_clk);
}

void sdc0_clk_sample_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc0_clk2x);
}

void sdc0_clk_drv_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc0_clk2x);
}

void sdc1_clk2x_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void sdc1_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc1_clk2x);
}

void sdc1_clk_out_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc1_clk);
}

void sdc1_clk_sample_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc1_clk2x);
}

void sdc1_clk_drv_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &sdc1_clk2x);
}

void eth_ref_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &pll1);
}

void wdt_clk_update(struct fh_clk* p_clk)
{
	clk_handle(p_clk, &cpu_pclk);
}

/**
 * @brief System Clock Configuration
 */
#define CLK_CONTROL_BASE			PMU_REG_BASE
void rt_hw_clock_init(void)
{
	struct fh_clk *p;
	int i;
	fh_clk_tree.c_base_addr = CLK_CONTROL_BASE;
	fh_clk_tree.clk_head = fh_clk_array;

	//first open all the clock..
	FH_TIMER_WRITEL(REG_PMU_CLK_GATE, 0x0);
	for (i = 0; i < sizeof(fh_clk_array) / sizeof(struct fh_clk *); i++) {
		p = fh_clk_tree.clk_head[i];
		if (p->update_func)
			p->update_func(p);
	}
}

/***************
 *
 * new add
 *
 **************/

/* clocks cannot be de-registered no refcounting necessary */
struct fh_clk *clk_get(const char *name)
{

	struct fh_clk *p;
	int i;

	for (i = 0; i < sizeof(fh_clk_array) / sizeof(struct fh_clk *); i++) {
		p = fh_clk_tree.clk_head[i];
		if (!strcmp(p->name, name)) {
			return p;
		}
	}

	return RT_NULL;
}

//
//#define HAS_GATE			(0)
//#define HAS_NO_GATE			(1)
//	rt_uint32_t gate_flag;
//#define CLK_UNGATE			(0)
//#define CLK_GATE			(1)

void clk_gate_control(struct fh_clk *p_clk, rt_uint32_t status)
{

	if (status > CLK_GATE)
		return;

	if (p_clk->level == LEVEL_PERIPHERAL) {

		switch (p_clk->clk.peri.peri_flag) {
		case LEVEL_PERI_NORMAL:

			if (p_clk->clk.peri.obj.normal.gate.gate_flag
					== HAS_GATE) {
				p_clk->clk.peri.obj.normal.gate.sw_status =
						status;
			} else {
				rt_kprintf("[%-16.15s]: no gate...\t\n",
						p_clk->name);
			}

			break;
		case LEVEL_PERI_DDR:
			if (p_clk->clk.peri.obj.ddr.gate.gate_flag == HAS_GATE) {
				p_clk->clk.peri.obj.ddr.gate.sw_status = status;
			} else {
				rt_kprintf("[%-16.15s]: no gate...\t\n",
						p_clk->name);
			}

			break;

		default:
			break;
		}

		p_clk->update_func(p_clk);

	}

}

void clk_gate(struct fh_clk *p_clk)
{
	clk_gate_control(p_clk, CLK_GATE);
}

void clk_ungate(struct fh_clk *p_clk)
{
	clk_gate_control(p_clk, CLK_UNGATE);
}

rt_uint32_t clk_get_rate(struct fh_clk *p_clk)
{
	rt_uint32_t rate;
	//first update the status
	p_clk->update_func(p_clk);
	rate = p_clk->clk_out_rate;
	return rate;
}

void clk_set_rate(struct fh_clk *p_clk, rt_uint32_t rate_value)
{

	rt_uint32_t clk_in, div_flag, pre_div, div_multi, baud_out;

	if (p_clk->level == LEVEL_PERIPHERAL) {

		switch (p_clk->clk.peri.peri_flag) {
		case LEVEL_PERI_NORMAL:

			clk_in = p_clk->parent->clk_out_rate;
			div_flag = p_clk->clk.peri.obj.normal.div.div_flag;
			pre_div = p_clk->clk.peri.obj.normal.div.pdiv_value;
			div_multi = p_clk->clk.peri.obj.normal.div.sw_div_multi;
			baud_out = rate_value;

			cal_baud_div(clk_in, div_flag, pre_div,
					&p_clk->clk.peri.obj.normal.div.sw_div_value,
					div_multi, baud_out);

			break;
		case LEVEL_PERI_DDR:
			//rt_uint32_t mux0,mux1;
			clk_in = p_clk->parent->clk_out_rate;
			div_flag = p_clk->clk.peri.obj.ddr.div.div_flag;
			pre_div = p_clk->clk.peri.obj.ddr.div.pdiv_value;
			div_multi = p_clk->clk.peri.obj.ddr.div.sw_div_multi;
			baud_out = rate_value;

			cal_baud_div(clk_in, div_flag, pre_div,
					&p_clk->clk.peri.obj.ddr.div.sw_div_value,
					div_multi, baud_out);
			break;
		case LEVEL_PERI_SDC:
			fh_clk_debug(p_clk,
					"sdc can't set baud,please set the 'sdcx_clk2x'\n");
			break;
		case LEVEL_PERI_GMAC:
			fh_clk_debug(p_clk, "gmac not support set baud\n");
			break;
		default:
			break;
		}
		p_clk->update_func(p_clk);

	}

}

rt_uint32_t sdc_get_phase(struct fh_clk *p_clk)
{

	if (p_clk->level == LEVEL_PERIPHERAL) {
		if (p_clk->clk.peri.peri_flag == LEVEL_PERI_SDC) {

			p_clk->update_func(p_clk);
			return p_clk->clk.peri.obj.sdc.phase_diff;
		}
	}
	return SDC_CLK_PARA_ERROR;

}

rt_uint32_t sdc_set_phase(struct fh_clk *p_clk, rt_uint32_t phase)
{

	if (phase > DIFF_SDC_REFCLK_270)
		return SDC_CLK_PARA_ERROR;

	if (p_clk->level == LEVEL_PERIPHERAL) {
		if (p_clk->clk.peri.peri_flag == LEVEL_PERI_SDC) {
			p_clk->clk.peri.obj.sdc.phase_diff = phase;
			p_clk->update_func(p_clk);
			return SDC_CLK_PARA_OK;
		}
	}
	return SDC_CLK_PARA_ERROR;

}

#ifdef FH_DBG_CLK
int fh_clk_nlist()
{
	struct fh_clk *p;
	int i;

	for(i = 0;i<sizeof(fh_clk_array)/sizeof(struct fh_clk *);i++) {
		p = fh_clk_tree.clk_head[i];
		//p->update_func(p);
		rt_kprintf("[%-16.15s]:\t\t[baud]:%d\t\n",p->name,p->clk_out_rate);
	}

	return 0;
}

int fh_clk_glist()
{
	struct fh_clk *p;
	int i;
	rt_kprintf("first bit set means has no gate..\n");
	for(i = 0;i<sizeof(fh_clk_array)/sizeof(struct fh_clk *);i++) {
		p = fh_clk_tree.clk_head[i];
		//p->update_func(p);
		if(!(p->gate & CLK_HAS_NO_GATE))
		rt_kprintf("[%-16.15s]:\t\t[gate]:%d\t\n",p->name,p->gate);
		else
		rt_kprintf("[%-16.15s]:\t\t[gate]:no gate..\t\n",p->name);
	}

	return 0;
}
#endif


#ifdef RT_USING_FINSH
#include <finsh.h>
#ifdef FH_DBG_CLK
FINSH_FUNCTION_EXPORT(fh_clk_nlist, fh_clk_name_list..);
FINSH_FUNCTION_EXPORT(fh_clk_glist, fh_clk_gate_list..);
#endif
#endif


