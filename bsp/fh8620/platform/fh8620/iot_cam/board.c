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
 
/*****************************************************************************
 *  Include Section
 *  add all #include here
 *****************************************************************************/
#include <mmu.h>
#include "fh_def.h"
#include "arch.h"
#include "board_info.h"
#include "inc/fh_driverlib.h"
#include "iomux.h"
#include "fh_pmu.h"
#include "spi_fh_adapt.h"

#ifdef RT_USING_SADC
#include "sadc.h"
#endif

#ifdef RT_USING_SPI
#include "ssi.h"
#include "fh_dma.h"
#endif

#ifdef RT_USING_ENC28J60
#include "enc28j60.h"
#include "gpio.h"
#endif

#ifndef HW_WIFI_POWER_GPIO
    #define HW_WIFI_POWER_GPIO    47  // wifi power on
#endif
#ifndef HW_WIFI_POWER_GPIO_ON_LEVEL
    #define HW_WIFI_POWER_GPIO_ON_LEVEL 0
#endif

#ifndef HW_CIS_RST_GPIO
    #define HW_CIS_RST_GPIO       45  // cis(sensor) reset
#endif
#ifndef HW_CIS_RST_GPIO_LEVEL
    #define HW_CIS_RST_GPIO_LEVEL 1
#endif


#ifndef HW_SDCARD_POWER_GPIO
	#define HW_SDCARD_POWER_GPIO  63   //not used
#endif
/****************************************************************************
 * ADT section
 *  add definition of user defined Data Type that only be used in this file  here
 ***************************************************************************/
struct st_platform_info {
	char *name;
	void *private_data;
};

/******************************************************************************
 * Function prototype section
 * add prototypes for all functions called by this file,execepting those
 * declared in header file
 *****************************************************************************/

/*****************************************************************************
 * Global variables section - Exported
 * add declaration of global variables that will be exported here
 * e.g.
 *  int8_t foo;
 ****************************************************************************/

/*****************************************************************************
 * Global variables section - Local
 * define global variables(will be refered only in this file) here,
 * static keyword should be used to limit scope of local variable to this file
 * e.g.
 *  static uint8_t ufoo;
 *****************************************************************************/

void fh_mmc_reset(struct fh_mmc_obj *mmc_obj)
{
	rt_uint32_t value;
	if (mmc_obj->id)
		fh_pmu_write(REG_PMU_SWRST_AHB_CTRL, 0xfffffffd);
	else
		fh_pmu_write(REG_PMU_SWRST_AHB_CTRL, 0xfffffffb);
	do {
		fh_pmu_read(REG_PMU_SWRST_AHB_CTRL, &value);
	} while (value != 0xffffffff);
}

static struct fh_mmc_obj mmc0_obj =
{
    .id = 0,
    .irq = SDC0_IRQn,
    .base = SDC0_REG_BASE,
    .power_pin_gpio = HW_SDCARD_POWER_GPIO,
    .mmc_reset = fh_mmc_reset,
};

static struct fh_mmc_obj mmc1_obj =
{
    .id = 1,
    .irq = SDC1_IRQn,
    .base = SDC1_REG_BASE,
    .power_pin_gpio = HW_WIFI_POWER_GPIO,
    .mmc_reset = fh_mmc_reset,
};

#ifdef RT_USING_SPI
#define SPI0_CLK_IN					(50000000)
#define SPI0_MAX_BAUD				(SPI0_CLK_IN/2)

static struct spi_control_platform_data spi0_platform_data =
{
    .id = 0,
    .irq = SPI0_IRQn,
    .base = SPI0_REG_BASE,
    .max_hz = SPI0_MAX_BAUD,
    .slave_no = FH_SPI_SLAVE_MAX_NO,
    .clk_in = SPI0_CLK_IN,
    .rx_hs_no = SPI0_RX,
    .tx_hs_no = SPI0_TX,
    .dma_name = "fh81_dma",
    .transfer_mode = SPI0_TRANSFER_MODE,
    .plat_slave[0].cs_pin = SPI_CRTOLLER0_SLAVE0_CS,
    .plat_slave[0].actice_level = ACTIVE_LOW,
    .plat_slave[1].cs_pin = SPI_CRTOLLER0_SLAVE1_CS,
    .plat_slave[1].actice_level = ACTIVE_LOW,
};


#define SPI1_CLK_IN					(50000000)
#define SPI1_MAX_BAUD				(SPI1_CLK_IN/2)

static struct spi_control_platform_data spi1_platform_data =
{
    .id = 1,
    .irq = SPI1_IRQn,
    .base = SPI1_REG_BASE,
    .max_hz = SPI1_MAX_BAUD,
    .slave_no = FH_SPI_SLAVE_MAX_NO,
    .clk_in = SPI1_CLK_IN,
    .rx_hs_no = SPI1_RX,
    .tx_hs_no = SPI1_TX,
    .dma_name = "fh81_dma",
    .transfer_mode = SPI1_TRANSFER_MODE,
    .plat_slave[0].cs_pin = SPI_CRTOLLER1_SLAVE0_CS,
    .plat_slave[0].actice_level = ACTIVE_LOW,
    .plat_slave[1].cs_pin = SPI_CRTOLLER1_SLAVE1_CS,
    .plat_slave[1].actice_level = ACTIVE_LOW,
};
#endif

static struct fh_i2c_obj i2c0_obj =
{
    .id = 0,
    .irq = I2C0_IRQn,
    .base = I2C0_REG_BASE,
};

static struct fh_i2c_obj i2c1_obj =
{
    .id = 1,
    .irq = I2C1_IRQn,
    .base = I2C1_REG_BASE,
};

static struct fh_gpio_obj gpio0_obj =
{
    .id = 0,
    .irq = GPIO0_IRQn,
};

static struct fh_gpio_obj gpio1_obj =
{
    .id = 1,
    .irq = GPIO1_IRQn,
};

static struct fh_pwm_obj pwm_obj =
{
    .id = 0,
    .base = PWM_REG_BASE,
};

static struct fh_wdt_obj wdt_obj =
{
    .id = 0,
    .base = WDT_REG_BASE,
    .irq = WDT_IRQn,
};


#ifdef RT_USING_SADC
static struct wrap_sadc_obj sadc_obj =
{
		.id = 0,
		.regs = (void *)SADC_REG_BASE,
		.irq_no = SADC_IRQn,
		.sample_mode = ISR_MODE,
};
#endif


static struct mtd_partition fh_sf_parts[] = {
    {
        /* head & Ramboot */
        .name       = "bootstrap",
        .offset     = 0,
        .size       = 0x4000,
        .mask_flags = MTD_WRITEABLE, /* force read-only */
    }, {
        /* isp param */
        .name       = "isp-param",
        .offset     = 0x4000,
        .size       = 0x4000,
        .mask_flags = MTD_WRITEABLE, /* force read-only */
    }, {
        /* pae param */
        .name       = "pae-param",
        .offset     = 0x8000,
        .size       = 0x8000,
        .mask_flags = MTD_WRITEABLE, /* force read-only */
    }, {
        /* Uboot SPL */
        .name       = "uboot-spl",
        .offset     = 0x10000,
        .size       = 0x10000,
        .mask_flags = MTD_WRITEABLE, /* force read-only */
    }, {
        /* U-Boot environment */
        .name       = "uboot-env",
        .offset     = 0x20000,
        .size       = 0x10000,
        .mask_flags = MTD_WRITEABLE, /* force read-only */
    }, {
        /* U-Boot */
        .name       = "uboot",
        .offset     = 0x30000,
        .size       = 0x30000,
        .mask_flags = MTD_WRITEABLE, /* force read-only */
    }, {
        .name       = "kernel",
        .offset     = 0x60000,
        .size       = 0x400000,
        .mask_flags = 0,
    }, {
        .name       = "rootfs",
        .offset     = 0x460000,
        .size       = 0x300000,
        .mask_flags = 0,
    }, {
        .name       = "app",
        .offset     = 0x760000,
        .size       = 0x8a0000,
        .mask_flags = 0,
    }//mtdparts=spi0.0:64k(bootstrap),64k(u-boot-env),192k(u-boot),4M(kernel),8M(rootfs),-(app)
    /* two blocks with bad block table (and mirror) at the end */
};


static struct flash_platform_data fh_flash_platform_data  =
{
    .flash_name = "fh_flash",
    .spi_name   = "ssi0_0",
    .parts      = fh_sf_parts,
    .nr_parts   = ARRAY_SIZE(fh_sf_parts),
};

struct st_platform_info plat_mmc0 =
{
    .name = "mmc",
    .private_data = &mmc0_obj,
};


struct st_platform_info plat_mmc1 =
{
    .name = "mmc",
    .private_data = &mmc1_obj,
};
#ifdef RT_USING_SPI
struct st_platform_info plat_spi0 =
{
    .name = "spi",
    .private_data = &spi0_platform_data,
};

struct st_platform_info plat_spi1 =
{
    .name = "spi",
    .private_data = &spi1_platform_data,
};
#endif

struct st_platform_info plat_flash =
{
    .name = "fh_flash",
    .private_data = &fh_flash_platform_data,
};

struct st_platform_info plat_i2c0 =
{
    .name = "i2c",
    .private_data = &i2c0_obj,
};

struct st_platform_info plat_i2c1 =
{
    .name = "i2c",
    .private_data = &i2c1_obj,
};

struct st_platform_info plat_gpio0 =
{
    .name = "gpio",
    .private_data = &gpio0_obj,
};

struct st_platform_info plat_gpio1 =
{
    .name = "gpio",
    .private_data = &gpio1_obj,
};

struct st_platform_info plat_pwm =
{
    .name = "pwm",
    .private_data = &pwm_obj,
};

struct st_platform_info plat_wdt =
{
    .name = "wdt",
    .private_data = &wdt_obj,
};
#ifdef RT_USING_SADC
struct st_platform_info plat_sadc =
{
    .name = "sadc",
    .private_data = &sadc_obj,
};
#endif

const static struct st_platform_info *platform_info[] = {
		&plat_mmc0,
		//&plat_mmc1,//by PeterJiang, wifi don't use SDIO framework...
#ifdef RT_USING_SPI
        &plat_spi0,
#endif
#ifdef RT_USING_SPI1
        &plat_spi1,
#endif
        &plat_flash,
        &plat_i2c0,
        &plat_i2c1,
        &plat_gpio0,
        &plat_gpio1,
        &plat_pwm,
        &plat_wdt,
#ifdef RT_USING_SADC
        &plat_sadc,
#endif
};


 /* function body */

/*****************************************************************************
 * Description:
 *      add funtion description here
 * Parameters:
 *      description for each argument, new argument starts at new line
 * Return:
 *      what does this function returned?
 *****************************************************************************/

 void clock_init(void)
 {
 	//UINT32 reg;
 	//gate enable, spi0, gmac, uart0, timer0, wdt, pts
#ifdef YG_TEK
	fh_pmu_write_mask(REG_PMU_PAD_MAC_TXER_CFG, 0x100000, 0x100000);
#endif
 	//SPI0
	fh_pmu_write_mask(REG_PMU_CLK_DIV3, 0xb, 0xff);

 	//GMAC
	fh_pmu_write_mask(REG_PMU_CLK_DIV6, 0x5000000, 0xf000000);

 	//UART0
	fh_pmu_write_mask(REG_PMU_CLK_DIV4, 0x1, 0xf);

 	//TIMER0
	fh_pmu_write_mask(REG_PMU_CLK_DIV5, 0x1d0000, 0x3f0000);

 	//PTS
	fh_pmu_write_mask(REG_PMU_CLK_DIV2, 0x23, 0x3f);

 	//WDT
	//fh_pmu_write_mask(REG_PMU_CLK_DIV5, 0x1d00, 0x3f00);
	fh_pmu_write_mask(REG_PMU_CLK_DIV5, 0x3500, 0x3f00);

 	//clock enable
	fh_pmu_write_mask(REG_PMU_CLK_GATE, 0, 0x720ba080);

    //sd0_drv_sel
	fh_pmu_write_mask(REG_PMU_CLK_SEL, 0x200000, 0x300000);
    //sd0_sample_sel
	fh_pmu_write_mask(REG_PMU_CLK_SEL, 0x00000, 0x30000);

 	//sd1_drv_sel
	fh_pmu_write_mask(REG_PMU_CLK_SEL, 0x2000, 0x3000);
 	//sd1_sample_sel
	fh_pmu_write_mask(REG_PMU_CLK_SEL, 0x000, 0x300);

 }


void fh_platform_info_register(void){
	struct fh_board_info *test_info;
	int i;

	for(i=0;i<sizeof(platform_info)/sizeof(struct st_platform_info *);i++){
		test_info = fh_board_info_register(platform_info[i]->name,platform_info[i]->private_data);
		if(!test_info){
			rt_kprintf("info_name(%s) failed registered\n", platform_info[i]->name);
		}
	}
}

void rt_hw_board_init()
{
	/* initialize the system clock */
	rt_hw_clock_init();
	//add iomux init 2015-3-11 by yu.zhang for fh81(fullhan)
	//iomux_init();
    fh_iomux_init(PMU_REG_BASE + 0x5c);
	//add clk init  2015-3-11 by yu.zhang for fh81(fullhan)
	clock_init();
	/* initialize uart */
	rt_hw_uart_init();
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
	/* initialize timer1 */
	rt_hw_timer_init();
	//board data info init...
	fh_board_info_init();
	fh_platform_info_register();

}

void rt_board_driver_init(){

	//add board init lock here...
	/*rt_show_version();*/
	int ret;

/* Filesystem Initialization */
#ifdef RT_USING_DFS
	{
		/* init the device filesystem */
		dfs_init();
		rt_kprintf("DFS initialized!\n");
#if defined(RT_USING_DFS_ELMFAT)
		/* init the elm chan FatFs filesystam*/
		elm_init();
		rt_kprintf("ELM initialized!\n");
#endif

#if defined(RT_USING_DFS_ROMFS)
		dfs_romfs_init();
		if (dfs_mount(RT_NULL, "/rom", "rom", 0, &romfs_root) == 0)
		{
			rt_kprintf("ROM File System initialized!\n");
		}
		else
			rt_kprintf("ROM File System initialzation failed!\n");
#endif

#if defined(RT_USING_DFS_DEVFS)
		devfs_init();
		if (dfs_mount(RT_NULL, "/dev", "devfs", 0, 0) == 0)
			rt_kprintf("Device File System initialized!\n");
		else
			rt_kprintf("Device File System initialzation failed!\n");

		#ifdef RT_USING_NEWLIB
		/* init libc */
		libc_system_init(RT_CONSOLE_DEVICE_NAME);
		#endif
#endif

#if defined(RT_USING_DFS_UFFS)
	{
		/* init the uffs filesystem */
		dfs_uffs_init();

		/* mount flash device as flash directory */
		if(dfs_mount("nand0", "/nand0", "uffs", 0, 0) == 0)
			rt_kprintf("UFFS File System initialized!\n");
		else
			rt_kprintf("UFFS File System initialzation failed!\n");
	}
#endif


#ifdef RT_USING_DFS_RAMFS
	dfs_ramfs_init();
	{
		rt_uint8_t *ramfs_pool = RT_NULL;
		struct dfs_ramfs* ramfs;
		ramfs_pool = rt_malloc(0x800000);
		if(ramfs_pool)
		{
			ramfs =(struct dfs_ramfs*) dfs_ramfs_create((rt_uint8_t*)ramfs_pool, 0x800000);
			if (ramfs != RT_NULL)
			{
				if (dfs_mount(RT_NULL, "/", "ram", 0, ramfs) == 0)
				{
					rt_kprintf("Mount RAMDisk done!\n");
				}
				else
				{
					rt_kprintf("Mount RAMDisk failed.\n");
				}
			}
		}
		else
		{
			rt_kprintf("alloc ramfs poll failed\n");
		}
	}
#endif
	}
#endif
/* Filesystem Initialization end*/

#ifdef RT_USING_GPIO
    {
        rt_hw_gpio_init();
	rt_kprintf("GPIO initialized!\n");

#ifdef RT_USING_SDIO
        //wifi
        gpio_request(HW_WIFI_POWER_GPIO);
        gpio_direction_output(HW_WIFI_POWER_GPIO, !HW_WIFI_POWER_GPIO_ON_LEVEL);
        udelay(1000);
        gpio_direction_output(HW_WIFI_POWER_GPIO, HW_WIFI_POWER_GPIO_ON_LEVEL);
        //micro sd
        gpio_request(HW_SDCARD_POWER_GPIO);
        gpio_direction_output(HW_SDCARD_POWER_GPIO, 0);
	rt_kprintf("SDIO initialized!\n");
#endif
        //sensor
        gpio_request(HW_CIS_RST_GPIO);
        gpio_direction_output(HW_CIS_RST_GPIO, HW_CIS_RST_GPIO_LEVEL);


    }
#endif

#ifdef RT_USING_SDIO
#ifndef RT_USING_WIFI_MARVEL
    rt_hw_mmc_init();
	rt_kprintf("MMC initialized!\n");
    rt_thread_delay(RT_TICK_PER_SECOND*2);
    /* mount sd card fat partition 1 as root directory */
    #ifdef RT_USING_DFS_ELMFAT
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
        {
            rt_kprintf("File System initialized!\n");
        }
        else
            rt_kprintf("File System initialization failed!\n");
    #endif
#endif
#endif


#ifdef RT_USING_FH_DMA
	{
        rt_fh_dma_init();
	rt_kprintf("DMA initialized!\n");
	}
#endif



#ifdef RT_USING_FH_ACW
	{
		 fh_audio_init();
			rt_kprintf("AUDIO initialized!\n");
	}
#endif

#ifdef RT_USING_LWIP
	{
		/* init lwip system */
		lwip_sys_init();
		rt_kprintf("LWIP SYS initialized!\n");
		eth_system_device_init();
		rt_kprintf("ETH initialized!\n");
	}
#endif

#ifdef RT_USING_GMAC
        /* register ethernetif device */
        rt_app_fh_gmac_init();
	rt_kprintf("GMAC initialized!\n");
#endif


#ifdef RT_USING_I2C
	{
	    rt_hw_i2c_init();
		rt_kprintf("I2C initialized!\n");
	}
#endif

#ifdef RT_USING_PWM
    {
        rt_hw_pwm_init();
	rt_kprintf("PWM initialized!\n");
}
#endif

#ifdef RT_USING_WDT
    {
        rt_hw_wdt_init();
	rt_kprintf("WDT initialized!\n");
}
#endif


#ifdef RT_USING_SPI
    {
        rt_hw_spi_init();
	rt_kprintf("SPI initialized!\n");
    }
#endif


#ifdef RT_USING_FH_FLASH_ADAPT
    fh_flash_adapt_init();
    rt_kprintf("FLASH initialized!\n");
#endif

	rt_kprintf("init done\n");
#ifdef RT_USING_SADC
    rt_hw_sadc_init();
	rt_kprintf("SADC initialized!\n");
#endif

#ifdef RT_USING_ENC28J60
	gpio_request(ENC28J60_INT);
	gpio_direction_input(ENC28J60_INT);
	gpio_set_irq_type(ENC28J60_INT, IRQ_TYPE_EDGE_FALLING);
	rt_hw_interrupt_install(gpio_to_irq(ENC28J60_INT), (void *)enc28j60_isr, RT_NULL, RT_NULL);
	gpio_irq_enable(gpio_to_irq(ENC28J60_INT));
	gpio_release(ENC28J60_INT);

	enc28j60_attach(ENC28J60_SPI_DEV);
#endif
}

