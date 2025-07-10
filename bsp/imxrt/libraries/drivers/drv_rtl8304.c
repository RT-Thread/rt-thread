/*
*  Copyright (c) 2006-2020, Chukie
*
*  SPDX-License-Identifier: Apache-2.0
*
*  @file     : drv_rtl8304.c
*
*  @brief    : Realtek RTL8304 driver
*
*
*  Change Logs:
*  Date           Author          Notes
*  2022-07-16     weiyf           created
*/
/* Includes -----------------------------------------------------------------*/
#include "drv_rtl8304.h"
#include "rtdevice.h"
#include "drv_gpio.h"
#include "fsl_iomuxc.h"
#include "rthw.h"
//#include "MIMXRT1061.h"
/* Private typedef ----------------------------------------------------------*/

/* Private define -----------------------------------------------------------*/
#define RTL8304_QOS_RATE_TX_MAX     0x640       /*100M bps*/

#define RTL_PHY_ID1                 0x001C
// #define RTL_PHY_ID2                 0xCA52   //RTL8304MBI-CG
#define RTL_PHY_ID2                 0xC860      //RTL8304MBI-VB-CG

#define RTL_MDCS_GPIO               GET_PIN(RTL8304_MDCS_PORT, RTL8304_MDCS_PIN)
#define RTL_MDIO_GPIO               GET_PIN(RTL8304_MDIO_PORT, RTL8304_MDIO_PIN)

#define RTL_PORT0_LED               GET_PIN(BSP_USING_PHY_LED_PORT1_PORT, BSP_USING_PHY_LED_PORT1_PIN)
#define RTL_PORT1_LED               GET_PIN(BSP_USING_PHY_LED_PORT2_PORT, BSP_USING_PHY_LED_PORT2_PIN)
#define RTL_LED_ON                  PIN_LOW
#define RTL_LED_OFF                 PIN_HIGH

#define RTL_SMI_MODES(GPIO, MODE)   rt_pin_mode(GPIO, MODE)

#define RTL_SMI_WRITE(GPIO, WRITE)  rt_pin_write(GPIO, WRITE)

#define RTL_SMI_READS(GPIO)         rt_pin_read(GPIO)

#define RTL_DELAY                   100
#define RTL_CLK_KEEPS(DELAY)        { for (int i = 0; i < (DELAY); i++); }

typedef struct rtl_rma_entry_s
{
	uint32_t action;
	uint32_t enable_rmapri;
	uint32_t priority;
}rtl_rma_entry_t;

enum RTL_ACTION
{
    RTL_ACT_PERMIT = 0,      /*permit the packet*/ 
	RTL_ACT_COPY2CPU,		/*copy to CPU*/
    RTL_ACT_TRAP2CPU,   /*trap the packet to cpu*/	
    RTL_ACT_DROP,    /*drop the packet*/    
    RTL_ACT_MIRROR,     /*mirror the packet */
    RTL_ACT_FLOOD,      /*flood the packet  */   
    RTL_ACTION_END
};


enum RTL_RMA
{      
    RTL_RMA00,      /*reserved address "01-80-c2-00-00-00"*/
    RTL_RMA01,     /*reserved address "01-80-c2-00-00-01"*/
	RTL_RMA02,		/*reserved address "01-80-c2-00-00-02"*/
	RTL_RMA03,		/*reserved address "01-80-c2-00-00-03"*/
	RTL_RMA04_0D0F,    /*reserved address "01-80-C2-00-00-04 --- 01-80-C2-00-00-0D" */
	                  /* "01-80-C2-00-00-0F" */
	RTL_RMA0E,      /*reserved address "01-80-C2-00-00-0E"*/
	RTL_RMA10,		 /*reserved address "01-80-c2-00-00-10"*/
	RTL_RMA11_1F,    /*reserved address "01-80-C2-00-00-11 --- 01-80-C2-00-00-1F"*/
	RTL_RMA20,		 /*reserved address "01-80-c2-00-00-20"*/
	RTL_RMA21,		 /*reserved address "01-80-c2-00-00-21"*/ 
	RTL_RMA22_2F,    /*reserved address "01-80-c2-00-00-22 --- 01-80-c2-00-00-2F"*/
	RTL_RMA31_3F,    /*reserved address "01-80-c2-00-00-31 --- 01-80-c2-00-00-3F"*/ 
	RTL_RMAIGMP,     /*IGMP packet without pppoe header*/
	RTL_RMAMLD,      /*MLD packet without pppoe header*/
	RTL_RMAPPPOE_IPV4,   /*IGMP packet with pppoe header*/
	RTL_RMAPPPOE_MLD,    /*MLD packet with pppoe header*/
	RTL_RMASWITCH_MAC,   /*RMA = switch MAC*/
	RTL_RMAUNKNOWN_UNIDA,    /*reserved address "xxxxxxx0-xx-xx-xx-xx-xx"*/
	RTL_RMAUNKNOWN_MULTDA,   /*reserved address "xxxxxxx1-xx-xx-xx-xx-xx"*/
	RTL_RMAUSER         /*USER defined Reserved address*/
};

enum RTL_SPAN_STATE
{
    RTL_SPAN_DISABLE = 0,
    RTL_SPAN_BLOCK,
    RTL_SPAN_LEARN,
    RTL_SPAN_FORWARD, 
    RTL_SPAN_END
};




/* Private variables --------------------------------------------------------*/
static rt_base_t rtl_lock = 0;
/* Extern variables ---------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/**
 * @brief initilize RTL8304 SMI(MDC/MDIO) gpio for default mode
 *
 * @return int
 */
static int rtl_smi_init(void)
{
    RTL_SMI_MODES(RTL_MDCS_GPIO, PIN_MODE_OUTPUT);
    RTL_SMI_MODES(RTL_MDIO_GPIO, PIN_MODE_OUTPUT);
    return RT_EOK;
}
INIT_APP_EXPORT(rtl_smi_init);

/**
 * @brief disable interrupt
 *
 */
static void rtl_interrupt_lock(void)
{
    rtl_lock = rt_hw_interrupt_disable();
}

/**
 * @brief enable interrupt
 *
 */
static void rtl_interrupt_unlock(void)
{
    rt_hw_interrupt_enable(rtl_lock);
}

/**
 * @brief set RTL8304 SMI(MDC/MDIO) gpio output low level
 *
 */
static void rtl_smi_zero(void)
{
    RTL_SMI_WRITE(RTL_MDCS_GPIO, PIN_LOW);
    RTL_SMI_WRITE(RTL_MDIO_GPIO, PIN_LOW);
    RTL_CLK_KEEPS(RTL_DELAY);
}

/**
 * @brief read one bit from MDIO
 *
 * @return uint8_t
 */
static rt_uint8_t rtl_smi_read_bit(void)
{
    RTL_SMI_MODES(RTL_MDIO_GPIO, PIN_MODE_INPUT);
    RTL_SMI_WRITE(RTL_MDCS_GPIO, PIN_HIGH);
    RTL_CLK_KEEPS(RTL_DELAY);
    RTL_SMI_WRITE(RTL_MDCS_GPIO, PIN_LOW);
    rt_uint8_t ret = RTL_SMI_READS(RTL_MDIO_GPIO);
    RTL_CLK_KEEPS(RTL_DELAY);
    return  ret;
}

/**
 * @brief write one bit to MDIO
 *
 * @param bit
 */
static void rtl_smi_write_bit(rt_uint8_t bit)
{
    RTL_SMI_MODES(RTL_MDIO_GPIO, PIN_MODE_OUTPUT);
    RTL_SMI_WRITE(RTL_MDIO_GPIO, bit > 0 ? PIN_HIGH : PIN_LOW);
    RTL_SMI_WRITE(RTL_MDCS_GPIO, PIN_LOW);
    RTL_CLK_KEEPS(RTL_DELAY);
    RTL_SMI_WRITE(RTL_MDCS_GPIO, PIN_HIGH);
    RTL_CLK_KEEPS(RTL_DELAY);
}

/**
 * @brief keep smi bit 32 high level for preamble
 *
 */
static void rtl_smi_preamble(void)
{
    for (signed char i = 0; i < 32; i++)
    {
        rtl_smi_write_bit(1);
    }
}

/**
 * @brief set smi bit <01> to start frame
 *
 */
static void rtl_smi_start(void)
{
    rtl_smi_write_bit(0);
    rtl_smi_write_bit(1);
}

/**
 * @brief set smi bit <10> for read
 *
 */
static void rtl_smi_option_read(void)
{
    rtl_smi_write_bit(1);
    rtl_smi_write_bit(0);
}

/**
 * @brief set smi bit <01> to write
 *
 */
static void rtl_smi_option_write(void)
{
    rtl_smi_write_bit(0);
    rtl_smi_write_bit(1);
}

/**
 * @brief send phy address to MDIO
 *
 * @param phy
 */
static void rtl_smi_send_phy_addr(rtl_phy_t phy)
{
    for (signed char i = 4; i >= 0; i--)
    {
        rtl_smi_write_bit(((rt_uint8_t)phy >> i) & 0x1);
    }
}

/**
 * @brief send reg address to MDIO
 *
 * @param reg
 */
static void rtl_smi_send_reg_addr(rtl_reg_t reg)
{
    for (signed char i = 4; i >= 0; i--)
    {
        rtl_smi_write_bit(((rt_uint8_t)reg >> i) & 0x1);
    }
}

/**
 * @brief read register from MDIO
 *
 * @param phy
 * @param reg
 * @return uint16_t
 */
static rt_uint16_t rtl_smi_read(rtl_phy_t phy, rtl_reg_t reg)
{
    rt_uint8_t  bit = 0;
    rt_uint16_t ret = 0;
    rtl_smi_preamble();
    rtl_smi_start();
    rtl_smi_option_read();
    rtl_smi_send_phy_addr(phy);
    rtl_smi_send_reg_addr(reg);
    rtl_smi_zero();
    /* after MDIO zero drop first bit */
    bit = rtl_smi_read_bit();
    for (signed char i = 15; i >= 0; i--)
    {
        bit = rtl_smi_read_bit();
        ret = (ret << 1) | bit;
    }
    rtl_smi_write_bit(1);
    rtl_smi_zero();
    return ret;
}

/**
 * @brief write register to MDIO
 *
 * @param phy
 * @param reg
 * @param data
 */
static void rtl_smi_write(rtl_phy_t phy, rtl_reg_t reg, rt_uint16_t data)
{
    rtl_smi_preamble();
    rtl_smi_start();
    rtl_smi_option_write();
    rtl_smi_send_phy_addr(phy);
    rtl_smi_send_reg_addr(reg);
    rtl_smi_write_bit(1);
    rtl_smi_write_bit(0);
    for (signed char i = 15; i >= 0; i--)
    {
        rtl_smi_write_bit((data >> i) & 0x1);
    }
    rtl_smi_zero();
}

/**
 * @brief get RTL8304 register by Asic
 *
 * @param phy
 * @param reg
 * @param page
 * @return rt_uint16_t
 */
static rt_uint16_t rtl_smi_reg_get(rtl_phy_t phy, rtl_reg_t reg, rtl_page_t page)
{
    rt_uint16_t ret = 0;
    rtl_interrupt_lock();
    ret = rtl_smi_read(RTL_PHY_8, RTL_REG_31);
    ret &= ~((0x1 << 15) | 0xFF);
    ret |= page;
    rtl_smi_write(RTL_PHY_8, RTL_REG_31, ret);
    ret = rtl_smi_read(phy, reg);
    rtl_interrupt_unlock();
    return ret;
}

/**
 * @brief set RTL8304 register by Asic
 *
 * @param phy
 * @param reg
 * @param page
 * @param data
 */
static void rtl_smi_reg_set(rtl_phy_t phy, rtl_reg_t reg, rtl_page_t page, rt_uint16_t data)
{
    rt_uint16_t ret = 0;
    rtl_interrupt_lock();
    /* switch to phy register first */
    rtl_smi_write(RTL_PHY_8, RTL_REG_31, 0x8000);
    /* write phy page to unavailable page */
    ret = rtl_smi_read(phy, RTL_REG_31);
    ret &= ~0xFF;
    ret |= 0xA;
    rtl_smi_write(phy, RTL_REG_31, ret);
    /* switch to MAC page through configuring PHY 8 register 31 bit 15 */
    ret = rtl_smi_read(RTL_PHY_8, RTL_REG_31);
    ret &= ~((0x1 << 15) | 0xFF);
    ret |= page;
    rtl_smi_write(RTL_PHY_8, RTL_REG_31, ret);
    /* write MAC register value */
    rtl_smi_write(phy, reg, data);
    rtl_interrupt_unlock();
}

/**
 * @brief :  Write one bit of Asic Register
 * @param  phy
 * @param  reg : 0~31
 * @param  page : 0~17
 * @param  bit : 0~15
 * @param  value : 0/1
 */
static void rtl_smi_regbit_set(rtl_phy_t phy, rtl_reg_t reg, rtl_page_t page, rt_uint16_t bit, rt_uint16_t value)
{
    rt_uint16_t regvalue;

    if (reg > RTL_REG_31 || phy > RTL_PHY_8)
    {
        return ;
    }
    if (page > RTL_PAGE_17 || bit > 15)
    {
        return ;
    }

    regvalue = rtl_smi_reg_get(phy, reg, page);
    if (value)
    {
        rtl_smi_reg_set(phy, reg, page, (regvalue | (1 << bit)));
    }
    else
    {
        rtl_smi_reg_set(phy, reg, page, (regvalue & (~(1 << bit))));
    }
}

/**
 * @brief get RTL8304 register by PCS
 *
 * @param phy
 * @param reg
 * @param page
 * @return rt_uint16_t
 */
static rt_uint16_t rtl_smi_phy_get(rtl_phy_t phy, rtl_reg_t reg, rtl_page_t page)
{
    rt_uint16_t ret = 0;
    rt_uint16_t val = 0;
    rtl_interrupt_lock();
    rtl_smi_write(RTL_PHY_8, RTL_REG_31, 0x8000);
    ret = rtl_smi_read(phy, RTL_REG_31);
    ret &= ~0xFF;
    ret |= page;
    rtl_smi_write(phy, RTL_REG_31, ret);
    val = rtl_smi_read(phy, reg);
    ret = rtl_smi_read(RTL_PHY_8, RTL_REG_31);
    ret &= ~(0x1 << 15);
    rtl_smi_write(RTL_PHY_8, RTL_REG_31, ret);
    rtl_interrupt_unlock();
    return val;
}

/**
 * @brief set RTL8304 register by PCS
 *
 * @param phy
 * @param reg
 * @param page
 * @param data
 */
static void rtl_smi_phy_set(rtl_phy_t phy, rtl_reg_t reg, rtl_page_t page, rt_uint16_t data)
{
    rt_uint16_t ret = 0;
    rtl_interrupt_lock();
    /* switch to phy register first */
    rtl_smi_write(RTL_PHY_8, RTL_REG_31, 0x8000);
    /* set phy page number */
    ret = rtl_smi_read(phy, RTL_REG_31);
    ret &= ~0xFF;
    ret |= page;
    rtl_smi_write(phy, RTL_REG_31, ret);
    /* write register */
    rtl_smi_write(phy, reg, data);
    ret = rtl_smi_read(RTL_PHY_8, RTL_REG_31);
    ret &= ~(0x1 << 15);
    rtl_smi_write(RTL_PHY_8, RTL_REG_31, ret);
    rtl_interrupt_unlock();
}

#if defined(RT_USING_FINSH)
/**
 * @brief RTL8304 console interface
 *
 * @param argc
 * @param argv
 */
static void rtl8304(int argc, char **argv)
{
    if (argc < 2)
    {
        rt_kprintf("rtl8304 <read|write>\r\n");
        return;
    }
    if (!rt_strncmp(argv[1], "read", 4))
    {
        if (argc < 5)
        {
            rt_kprintf("rtl8304 read [phy] [reg] [page]\r\n");
            return;
        }
        if (atoi(argv[2]) > RTL_PHY_8 || atoi(argv[2]) < RTL_PHY_0)
        {
            rt_kprintf("rtl8304 phy just from %d to %d\r\n", (int)RTL_PHY_0, (int)RTL_PHY_8);
            return;
        }
        if (atoi(argv[3]) > RTL_REG_31 || atoi(argv[3]) < RTL_REG_0)
        {
            rt_kprintf("rtl8304 reg just from %d to %d\r\n", (int)RTL_REG_0, (int)RTL_REG_31);
            return;
        }
        if (atoi(argv[4]) > RTL_PAGE_17 || atoi(argv[4]) < RTL_PAGE_0)
        {
            rt_kprintf("rtl8304 page just from %d to %d\r\n", (int)RTL_PAGE_0, (int)RTL_PAGE_17);
            return;
        }
        rtl_phy_t   phy  = (rtl_phy_t)atoi(argv[2]);
        rtl_reg_t   reg  = (rtl_reg_t)atoi(argv[3]);
        rtl_page_t  page = (rtl_page_t)atoi(argv[4]);
        rt_kprintf("Asic read phy: %d; reg: %d; page: %d; data: %02X success\r\n", (int)phy, (int)reg, (int)page, rtl_smi_reg_get(phy, reg, page));
        rt_kprintf("PCS  read phy: %d; reg: %d; page: %d; data: %02X success\r\n", (int)phy, (int)reg, (int)page, rtl_smi_phy_get(phy, reg, page));
    }
    else if (!rt_strncmp(argv[1], "write", 5))
    {
        if (argc < 7)
        {
            rt_kprintf("rtl8304 write <asic|pcs> [phy] [reg] [page] [data]\r\n");
            return;
        }
        if (rt_strncmp(argv[2], "asic", 4) && rt_strncmp(argv[2], "pcs", 3))
        {
            rt_kprintf("rtl8304 phy just support asic or pcs write\r\n");
            return;
        }
        if (atoi(argv[3]) > RTL_PHY_8 || atoi(argv[3]) < RTL_PHY_0)
        {
            rt_kprintf("rtl8304 phy just from %d to %d\r\n", (int)RTL_PHY_0, (int)RTL_PHY_8);
            return;
        }
        if (atoi(argv[4]) > RTL_REG_31 || atoi(argv[4]) < RTL_REG_0)
        {
            rt_kprintf("rtl8304 reg just from %d to %d\r\n", (int)RTL_REG_0, (int)RTL_REG_31);
            return;
        }
        if (atoi(argv[5]) > RTL_PAGE_17 || atoi(argv[5]) < RTL_PAGE_0)
        {
            rt_kprintf("rtl8304 page just from %d to %d\r\n", (int)RTL_PAGE_0, (int)RTL_PAGE_17);
            return;
        }
        if (strtol(argv[6], RT_NULL, 16) > 65535 || strtol(argv[6], RT_NULL, 16) < 0)
        {
            rt_kprintf("rtl8304 data just from HEX 0000 to FFFF\r\n");
            return;
        }
        rtl_phy_t   phy  = (rtl_phy_t)atoi(argv[3]);
        rtl_reg_t   reg  = (rtl_reg_t)atoi(argv[4]);
        rtl_page_t  page = (rtl_page_t)atoi(argv[5]);
        rt_uint16_t data = (rt_uint16_t)strtol(argv[6], RT_NULL, 16);
        if (!rt_strncmp(argv[2], "asic", 4))
        {
            rtl_smi_reg_set(phy, reg, page, data);
            rt_kprintf("Asic write phy: %d; reg: %d; page: %d; data: %02X success\r\n", (int)phy, (int)reg, (int)page, data);
        }
        else
        {
            rtl_smi_phy_set(phy, reg, page, data);
            rt_kprintf("PCS write phy: %d; reg: %d; page: %d; data: %02X success\r\n", (int)phy, (int)reg, (int)page, data);
        }
    }
    else
    {
        rt_kprintf("rtl8304 <read|write>\r\n");
    }
}
MSH_CMD_EXPORT(rtl8304, Realtek RTL8304 interface);
#endif /* RT_USING_FINSH */
/* Public function prototypes -----------------------------------------------*/
/**
 * @brief get RTL8304 port link status
 *
 * @param port
 * @return rtl_link_t
 */
rtl_link_t rtl_get_link_status(rtl_port_t port)
{
    rt_uint16_t ret = rtl_smi_reg_get(RTL_PHY_2, RTL_REG_18, RTL_PAGE_14);
    rtl_link_t link = (ret & (1 << (int)port)) > 0 ? RTL_LINK_UP : RTL_LINK_DOWN;
    if (RTL_PORT_0 == port)
    {
        rt_pin_write(RTL_PORT0_LED, RTL_LINK_UP == link ? RTL_LED_ON : RTL_LED_OFF);
    }
    else if (RTL_PORT_1 == port)
    {
        rt_pin_write(RTL_PORT1_LED, RTL_LINK_UP == link ? RTL_LED_ON : RTL_LED_OFF);
    }
    return link;
}

/**
 * @brief get RTL8304 port speed status
 *
 * @param port
 * @return rtl_speed_t
 */
rtl_speed_t rtl_get_speed_status(rtl_port_t port)
{
    rt_uint16_t ret = rtl_smi_reg_get(RTL_PHY_2, RTL_REG_19, RTL_PAGE_14);
    return (ret & (1 << (int)port)) > 0 ? RTL_SPEED_100M : RTL_SPEED_10M;
}

/**
 * @brief get RTL8304 port duplex status
 *
 * @param port
 * @return rtl_duplex_t
 */
rtl_duplex_t rtl_get_duplex_status(rtl_port_t port)
{
    rt_uint16_t ret = rtl_smi_reg_get(RTL_PHY_2, RTL_REG_20, RTL_PAGE_14);
    return (ret & (1 << (int)port)) > 0 ? RTL_DUPLEX_FULL : RTL_DUPLEX_HALF;
}

/**
 * @brief set RTL8304 storm filter
 *
 * @param port
 */
void rtl_set_storm_filter(rtl_port_t port)
{
    /* enable broadcast storm control based on byte */
    rt_uint16_t ret = rtl_smi_reg_get((rtl_phy_t)port, RTL_REG_16, RTL_PAGE_8);
    ret |= 1 << 0;
    ret |= 1 << 1;
    rtl_smi_reg_set((rtl_phy_t)port, RTL_REG_16, RTL_PAGE_8, ret);
    /* set broadcast storm filter byte as 5Mbps */
    ret = rtl_smi_reg_get((rtl_phy_t)port, RTL_REG_17, RTL_PAGE_8);
    ret = 5 * 1024;
    rtl_smi_reg_set((rtl_phy_t)port, RTL_REG_17, RTL_PAGE_8, ret);
    /* enable multicast storm control based on byte */
    ret = rtl_smi_reg_get((rtl_phy_t)port, RTL_REG_19, RTL_PAGE_8);
    ret |= 1 << 0;
    ret |= 1 << 1;
    rtl_smi_reg_set((rtl_phy_t)port, RTL_REG_19, RTL_PAGE_8, ret);
    /* set multicast storm filter byte as 5Mbps */
    ret = rtl_smi_reg_get((rtl_phy_t)port, RTL_REG_20, RTL_PAGE_8);
    ret = 5 * 1024;
    rtl_smi_reg_set((rtl_phy_t)port, RTL_REG_20, RTL_PAGE_8, ret);
    /* enable unknown unicast storm control based on byte */
    ret = rtl_smi_reg_get((rtl_phy_t)port, RTL_REG_22, RTL_PAGE_8);
    ret |= 1 << 0;
    ret |= 1 << 1;
    rtl_smi_reg_set((rtl_phy_t)port, RTL_REG_22, RTL_PAGE_8, ret);
    /* set unknown unicast storm filter byte as 5Mbps */
    ret = rtl_smi_reg_get((rtl_phy_t)port, RTL_REG_23, RTL_PAGE_8);
    ret = 5 * 1024;
    rtl_smi_reg_set((rtl_phy_t)port, RTL_REG_23, RTL_PAGE_8, ret);
}

/**
 * @brief set LED status
 *
 * @param status
 */
void rtl_set_led_status(rtl_led_t status)
{
    rt_uint16_t ret = rtl_smi_reg_get(RTL_PHY_1, RTL_REG_16, RTL_PAGE_14);
    ret |= (rt_uint8_t)status;
    rtl_smi_reg_set(RTL_PHY_1, RTL_REG_16, RTL_PAGE_14, ret);
}

/**
 * @brief : Software reset the asic
 */
void rtl_qos_softreset(void)
{
    rtl_smi_regbit_set(RTL_PHY_0, RTL_REG_16, RTL_PAGE_14, 1, 1);
}

/**
 * @brief : Set priority to Queue ID mapping
 * @param  port
 * @param  que_id : 0~3
 * @param  pri : 0~3
 * @return int 
 */
int rtl_set_queue_pri(rtl_port_t port, rt_uint16_t que_id, rt_uint16_t pri)
{
    rt_uint16_t regaddress, regvalue;

    if (que_id < 0 || que_id > 3)
    {
        return -RT_EINVAL;
    }

    if (pri < 0 || pri > 3)
    {
        return -RT_EINVAL;
    }

    regaddress = 17 + port;
    regvalue = rtl_smi_reg_get(RTL_PHY_6, (rtl_reg_t)regaddress, RTL_PAGE_16);

    switch (pri)
    {
    case 0:
        regvalue &= ~(0x3 << 6);
        regvalue |= (que_id << 6);
        break;
    case 1:
        regvalue &= ~(0x3 << 4);
        regvalue |= (que_id << 4);
        break;
    case 2:
        regvalue &= ~(0x3 << 2);
        regvalue |= (que_id << 2);
        break;
    case 3:
        regvalue &= ~0x3;
        regvalue |= que_id;
        break;
    default:
        return -RT_EINVAL;
    }

    rtl_smi_reg_set(RTL_PHY_6, (rtl_reg_t)regaddress, RTL_PAGE_16, regvalue);

    return RT_EOK;
}

/**
 * @brief : set port flow control
 * @param  port
 * @param  que_id : 0~3
 * @param  enable : 0-off,1-on
 */
void rtl_set_queue_flow(rtl_port_t port, rt_uint16_t que_id, rt_uint16_t enable)
{
    if (port > RTL_PORT_3 || que_id > 3)
    {
        return;
    }

    switch (port)
    {
    case RTL_PORT_0:
        rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_25, RTL_PAGE_16, que_id, enable);
        break;
    case RTL_PORT_1:
        rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_25, RTL_PAGE_16, 12 + que_id, enable);
        break;
    case RTL_PORT_2:
        rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_26, RTL_PAGE_16, que_id, enable);
        break;
    case RTL_PORT_3:
        rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_24, RTL_PAGE_16, 12 + que_id, enable);
        break;
    default:
        break;
    }

}

/**
 * @brief : Configure Qos
 * @param  queuenum : Queue number of each port(from 1 to 4)
 * @return int 
 *
 * Note:
 *    This API will initialize related Qos function. First it will set the ASIC's queue number
 *    globally for all port. Then it will set priority to queue mapping table based on the queue number
 *    for all ports. And it will enable output and input flow control abilities.
 */
int rtl_qos_init(rt_uint8_t queuenum)
{
    rt_uint16_t value_u16;

    if (queuenum > 4)
    {
        queuenum = 4;
    }
    if (queuenum < 1)
    {
        queuenum = 1;
    }

    /*queue number set*/
    value_u16 = rtl_smi_reg_get(RTL_PHY_5, RTL_REG_16, RTL_PAGE_16);
    value_u16 &= ~0x3;
    value_u16 |= (queuenum - 1);
    rtl_smi_reg_set(RTL_PHY_5, RTL_REG_16, RTL_PAGE_16, value_u16);
    /*A soft-reset is required after configuring queue num*/
    rtl_qos_softreset();

    /*priority to queue mapping*/
    switch (queuenum)
    {
    case 1:
    {
        rtl_set_queue_pri(RTL_PORT_0, 0, 0);
        rtl_set_queue_pri(RTL_PORT_0, 0, 1);
        rtl_set_queue_pri(RTL_PORT_0, 0, 2);
        rtl_set_queue_pri(RTL_PORT_0, 0, 3);

        rtl_set_queue_pri(RTL_PORT_1, 0, 0);
        rtl_set_queue_pri(RTL_PORT_1, 0, 1);
        rtl_set_queue_pri(RTL_PORT_1, 0, 2);
        rtl_set_queue_pri(RTL_PORT_1, 0, 3);

        rtl_set_queue_pri(RTL_PORT_2, 0, 0);
        rtl_set_queue_pri(RTL_PORT_2, 0, 1);
        rtl_set_queue_pri(RTL_PORT_2, 0, 2);
        rtl_set_queue_pri(RTL_PORT_2, 0, 3);

        rtl_set_queue_pri(RTL_PORT_3, 0, 0);
        rtl_set_queue_pri(RTL_PORT_3, 0, 1);
        rtl_set_queue_pri(RTL_PORT_3, 0, 2);
        rtl_set_queue_pri(RTL_PORT_3, 0, 3);
    }
    break;
    case 2:
    {
        rtl_set_queue_pri(RTL_PORT_0, 0, 0);
        rtl_set_queue_pri(RTL_PORT_0, 0, 1);
        rtl_set_queue_pri(RTL_PORT_0, 1, 2);
        rtl_set_queue_pri(RTL_PORT_0, 1, 3);

        rtl_set_queue_pri(RTL_PORT_1, 0, 0);
        rtl_set_queue_pri(RTL_PORT_1, 0, 1);
        rtl_set_queue_pri(RTL_PORT_1, 1, 2);
        rtl_set_queue_pri(RTL_PORT_1, 1, 3);

        rtl_set_queue_pri(RTL_PORT_2, 0, 0);
        rtl_set_queue_pri(RTL_PORT_2, 0, 1);
        rtl_set_queue_pri(RTL_PORT_2, 1, 2);
        rtl_set_queue_pri(RTL_PORT_2, 1, 3);

        rtl_set_queue_pri(RTL_PORT_3, 0, 0);
        rtl_set_queue_pri(RTL_PORT_3, 0, 1);
        rtl_set_queue_pri(RTL_PORT_3, 1, 2);
        rtl_set_queue_pri(RTL_PORT_3, 1, 3);
    }
    break;
    case 3:
    {
        rtl_set_queue_pri(RTL_PORT_0, 0, 0);
        rtl_set_queue_pri(RTL_PORT_0, 1, 1);
        rtl_set_queue_pri(RTL_PORT_0, 1, 2);
        rtl_set_queue_pri(RTL_PORT_0, 2, 3);

        rtl_set_queue_pri(RTL_PORT_1, 0, 0);
        rtl_set_queue_pri(RTL_PORT_1, 1, 1);
        rtl_set_queue_pri(RTL_PORT_1, 1, 2);
        rtl_set_queue_pri(RTL_PORT_1, 2, 3);

        rtl_set_queue_pri(RTL_PORT_2, 0, 0);
        rtl_set_queue_pri(RTL_PORT_2, 1, 1);
        rtl_set_queue_pri(RTL_PORT_2, 1, 2);
        rtl_set_queue_pri(RTL_PORT_2, 2, 3);

        rtl_set_queue_pri(RTL_PORT_3, 0, 0);
        rtl_set_queue_pri(RTL_PORT_3, 1, 1);
        rtl_set_queue_pri(RTL_PORT_3, 1, 2);
        rtl_set_queue_pri(RTL_PORT_3, 2, 3);
    }
    break;
    case 4:
    {
        rtl_set_queue_pri(RTL_PORT_0, 0, 0);
        rtl_set_queue_pri(RTL_PORT_0, 1, 1);
        rtl_set_queue_pri(RTL_PORT_0, 2, 2);
        rtl_set_queue_pri(RTL_PORT_0, 3, 3);

        rtl_set_queue_pri(RTL_PORT_1, 0, 0);
        rtl_set_queue_pri(RTL_PORT_1, 1, 1);
        rtl_set_queue_pri(RTL_PORT_1, 2, 2);
        rtl_set_queue_pri(RTL_PORT_1, 3, 3);

        rtl_set_queue_pri(RTL_PORT_2, 0, 0);
        rtl_set_queue_pri(RTL_PORT_2, 1, 1);
        rtl_set_queue_pri(RTL_PORT_2, 2, 2);
        rtl_set_queue_pri(RTL_PORT_2, 3, 3);

        rtl_set_queue_pri(RTL_PORT_3, 0, 0);
        rtl_set_queue_pri(RTL_PORT_3, 1, 1);
        rtl_set_queue_pri(RTL_PORT_3, 2, 2);
        rtl_set_queue_pri(RTL_PORT_3, 3, 3);
    }
    break;
    default:
        return -RT_EINVAL;
    }

    /*port discriptor based output flow control enable*/
    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_23, RTL_PAGE_16, RTL_PORT_0, 0);
    /*queue based output flow control enble*/
    for (int i = 0; i < queuenum; i++)
    {
        rtl_set_queue_flow(RTL_PORT_0, i, 0);
    }
    /*output flow control enble*/
    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_24, RTL_PAGE_16, RTL_PORT_0, 0);

    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_23, RTL_PAGE_16, RTL_PORT_1, 0);
    for (int i = 0; i < queuenum; i++)
    {
        rtl_set_queue_flow(RTL_PORT_1, i, 0);
    }
    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_24, RTL_PAGE_16, RTL_PORT_1, 0);

    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_23, RTL_PAGE_16, RTL_PORT_2, 0);
    for (int i = 0; i < queuenum; i++)
    {
        rtl_set_queue_flow(RTL_PORT_2, i, 0);
    }
    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_24, RTL_PAGE_16, RTL_PORT_2, 0);

    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_23, RTL_PAGE_16, RTL_PORT_3, 0);
    for (int i = 0; i < queuenum; i++)
    {
        rtl_set_queue_flow(RTL_PORT_3, i, 0);
    }
    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_24, RTL_PAGE_16, RTL_PORT_3, 0);

    /*input flow control enable*/
    rtl_smi_regbit_set(RTL_PHY_7, RTL_REG_18, RTL_PAGE_16, 0, 1);

    /*software reset*/
    rtl_qos_softreset();

    return RT_EOK;
}

/**
 * @brief set egress rate by qos
 *          rtk_rate_egrBandwidthCtrlRate_set
 * @param port : only set RTL_PORT_3
 * @param rate : max speed could be 100Mbps
 */
int rtl_set_egr_rate(rtl_port_t port, rt_uint32_t rate)
{
    rt_uint16_t value_u16;

    if (port != RTL_PORT_3 || rate > RTL8304_QOS_RATE_TX_MAX)
    {
        return -RT_EINVAL;
    }

    /* Enable port Tx bucket */
    rtl_smi_regbit_set((rtl_phy_t)port, RTL_REG_16, RTL_PAGE_9, 2, 1);
    /* Set port bandwidth control */
    value_u16 = rtl_smi_reg_get((rtl_phy_t)port, RTL_REG_26, RTL_PAGE_9);
    value_u16 &= ~0xFFF;
    value_u16 |= rate;
    rtl_smi_reg_set((rtl_phy_t)port, RTL_REG_26, RTL_PAGE_9, value_u16);
    /* calculate rate with or without ifg  */


    return RT_EOK;
}

/**
 * @brief get phy id1 by PCS
 *
 * @param phy
 * @return rt_uint16_t
 */
rt_uint16_t rtl_get_id1(rtl_phy_t phy)
{
    return rtl_smi_phy_get(phy, RTL_REG_2, RTL_PAGE_0);
}

/**
 * @brief get phy id2 by PCS
 *
 * @param phy
 * @return rt_uint16_t
 */
rt_uint16_t rtl_get_id2(rtl_phy_t phy)
{
    return rtl_smi_phy_get(phy, RTL_REG_3, RTL_PAGE_0);
}

/**
 * @brief : reset by hardware
 */
void rtl_hard_reset(void)
{
    /* reset by gpio */    
    rt_pin_mode(GET_PIN(BSP_USING_PHY_RST_PORT, BSP_USING_PHY_RST_PIN), PIN_MODE_OUTPUT);
    rt_pin_write(GET_PIN(BSP_USING_PHY_RST_PORT, BSP_USING_PHY_RST_PIN), PIN_LOW);
    rt_thread_mdelay(100);
    rt_pin_write(GET_PIN(BSP_USING_PHY_RST_PORT, BSP_USING_PHY_RST_PIN), PIN_HIGH);
    rt_thread_mdelay(1000);
}
void rtl_rma_entry_set(uint32_t type, rtl_rma_entry_t *pRmaentry)
{
	uint16_t regVal;
	uint16_t enableVal, actionVal;
	
	/*if(type > RTL8309N_RMAUNKNOWN_MULTDA) 
		return FAILED;
	if (NULL == pRmaentry)
		return FAILED;
	*/
	
	/*get value from pRmaentry*/
	switch(pRmaentry->action)
	{
		case RTL_ACT_PERMIT:
			actionVal = 0;
			break;
			
		case RTL_ACT_COPY2CPU:
			actionVal = 1;
			break;

		case RTL_ACT_TRAP2CPU:
			actionVal = 2;
			break;

		case RTL_ACT_DROP:
			actionVal = 3;
			break;

		default:
			break;
	}
	enableVal = (RTL_ENABLED == pRmaentry->enable_rmapri) ? 1 : 0;
	/*set rma entry*/
	switch(type)
	{
		case RTL_RMA00:
			regVal = rtl_smi_reg_get(2, 16, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 16, 15, regVal);
			break;
			
		case RTL_RMA01:
			regVal = rtl_smi_reg_get(2, 16, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 16, 15, regVal);
			break;
			
		case RTL_RMA02:
			regVal = rtl_smi_reg_get(2, 17, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 17, 15, regVal);
			break;
			
		case RTL_RMA03:
			regVal = rtl_smi_reg_get(2, 17, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 17, 15, regVal);
			break;
			
		case RTL_RMA04_0D0F:
			regVal = rtl_smi_reg_get(2, 18, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 18, 15, regVal);
			break;
			
		case RTL_RMA0E:
			regVal = rtl_smi_reg_get(2, 18, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 18, 15, regVal);		
			break;

		case RTL_RMA10:
			regVal = rtl_smi_reg_get(2, 19, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 19, 15, regVal);
			break;
			
		case RTL_RMA11_1F:
			regVal = rtl_smi_reg_get(2, 19, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 19, 15, regVal);
			break;		

		case RTL_RMA20:
			regVal = rtl_smi_reg_get(2, 20, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 20, 15, regVal);
			break;

		case RTL_RMA21:
			regVal = rtl_smi_reg_get(2, 20, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 20, 15, regVal);
			break;	

		case RTL_RMA22_2F:
			regVal = rtl_smi_reg_get(2, 21, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 21, 15, regVal);
			break;	

		case RTL_RMA31_3F:
			regVal = rtl_smi_reg_get(2, 21, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 21, 15, regVal);
			break;

		case RTL_RMAIGMP:
			regVal = rtl_smi_reg_get(2, 22, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 22, 15, regVal);
			break;	
			
		case RTL_RMAMLD:
			regVal = rtl_smi_reg_get(2, 22, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 22, 15, regVal);
			break;

		case RTL_RMAPPPOE_IPV4:
			regVal = rtl_smi_reg_get(2, 23, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 23, 15, regVal);
			break;	

		case RTL_RMAPPPOE_MLD:
			regVal = rtl_smi_reg_get(2, 23, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 23, 15, regVal);
			break;

		case RTL_RMASWITCH_MAC:
			regVal = rtl_smi_reg_get(2, 24, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 24, 15, regVal);
			break;				

		case RTL_RMAUNKNOWN_UNIDA:
			regVal = rtl_smi_reg_get(2, 24, 15);
			regVal &= ~(0x1F00);
			regVal |= (pRmaentry->priority << 11) | (enableVal << 10) | (actionVal << 8);
			rtl_smi_reg_set(2, 24, 15, regVal);
			break;	

		case RTL_RMAUNKNOWN_MULTDA:
			regVal = rtl_smi_reg_get(2, 25, 15);
			regVal &= ~0x001F;
			regVal |= (pRmaentry->priority << 3) | (enableVal << 2) | actionVal;
			rtl_smi_reg_set(2, 25, 15, regVal);
			break;	

		default:
			break;
	}	
	
}


void rtl_stp_set(uint32_t port, uint32_t state) 
{
    rt_uint16_t regValue;
	rtl_rma_entry_t rmaEntry;
	
    if ((port <= RTL_PORT_3) && (state <= RTL_SPAN_END))
    {  
    	/*enable trap BPDU(RMA 00) to cpu*/
    	rmaEntry.action = RTL_ACT_TRAP2CPU;
    	rmaEntry.enable_rmapri = RTL_DISABLED;
    	rmaEntry.priority = 0;
    	rtl_rma_entry_set(RTL_RMA00, &rmaEntry);
    	/*set port STP state*/
    	regValue = rtl_smi_reg_get((rtl_phy_t)port, 16, 2);
    	regValue &= ~0x3;
    	regValue |= state;
    	rtl_smi_reg_set((rtl_phy_t)port, 16, 2, regValue);
	}    
}

void rtl_cpu_tagInsertEnable_set(uint32_t enabled)
{
  	rtl_smi_regbit_set(2, 16, 17, 6, ((RTL_ENABLED == enabled) ? 1 : 0));
}

void rtl_cpu_tagRemoveEnable_set(uint32_t enabled)
{
	rtl_smi_regbit_set(2, 16, 17, 7, ((RTL_ENABLED == enabled) ? 1 : 0));

}

void rtl_cpu_cpuTagAwareEnable_set(uint32_t enabled)
{
	rtl_smi_regbit_set(2, 16, 17, 5, ((RTL_ENABLED == enabled) ? 1 : 0));
}

/*enable or disable CPU port Function */
void rtl_cpu_enable_set(uint32_t enabled)
{    
  	rtl_smi_regbit_set(2, 16, 17, 0, ((RTL_ENABLED == enabled) ? 0 : 1));
}


//Enable drop unkown Da unicast packets
void rtl_l2_unkownDaDropEnable_set(uint32_t enabled)
{
	rtl_smi_regbit_set(6, 16, 15, 13, ((RTL_ENABLED == enabled) ? 0 : 1));
}

void rtl_external_port_isolation_set(uint32_t enabled)
{
    if(RTL_ENABLED == enabled) 
    {
        rtl_smi_reg_set((rtl_phy_t)RTL_PORT_0,16,4,0x101);
        rtl_smi_reg_set((rtl_phy_t)RTL_PORT_1,16,4,0x108);
    } 
    else if(RTL_DISABLED == enabled)
    {
        rtl_smi_reg_set((rtl_phy_t)RTL_PORT_0,16,4,0x1FF);
        rtl_smi_reg_set((rtl_phy_t)RTL_PORT_1,16,4,0x1FF);
    }
}

void rtl_external_cpu_tag_insert_en(uint32_t enabled)
{
#if CPU_TAG_ENABLE
    rtl_cpu_enable_set(enabled);       
    rtl_cpu_tagInsertEnable_set(enabled);
#endif
}

void rtl_external_cpu_tag_remove_en(uint32_t enabled)
{
    rtl_cpu_tagRemoveEnable_set(enabled);
    rtl_cpu_cpuTagAwareEnable_set(enabled);
}


/**
 * @brief init rtl8304
 *
 * @param phy
 * @return rt_uint16_t
 */
int rtl_init(eEthMode eth_mode)
{
    rt_uint16_t get_id[2] = {0};
    
    rtl_hard_reset();

    /* set gpio for link led */    
    rt_pin_mode(RTL_PORT0_LED, PIN_MODE_OUTPUT);
    rt_pin_mode(RTL_PORT1_LED, PIN_MODE_OUTPUT);
    rt_pin_write(RTL_PORT0_LED, RTL_LED_OFF);
    rt_pin_write(RTL_PORT1_LED, RTL_LED_OFF);

    /* check phy id1 & id2 */
    get_id[0] = rtl_get_id1((rtl_phy_t)RTL_PORT_0);
    get_id[1] = rtl_get_id1((rtl_phy_t)RTL_PORT_1);
    rt_kprintf("id0=0x%x,id1=0x%x\n",get_id[0],get_id[1]);
    if (RTL_PHY_ID1 != rtl_get_id1((rtl_phy_t)RTL_PORT_0) ||
        RTL_PHY_ID2 != rtl_get_id2((rtl_phy_t)RTL_PORT_0))
    {
        rt_kprintf("check rtl8304 phy id failed\r\n");
        return -RT_ERROR;
    }
    /* set storm filter */
    rtl_set_storm_filter(RTL_PORT_3);
    /* set led status */
    rtl_set_led_status(RTL_LED_LINK_ACT_SPEED);
    /* set egress rate */
    rtl_qos_init(4);
    rtl_set_egr_rate(RTL_PORT_3, 0x50);

    rtl_l2_unkownDaDropEnable_set(1);
    
    if(ETH_SEPARATE == eth_mode) {
        rtl_external_port_isolation_set(RTL_ENABLED);
        rtl_external_cpu_tag_insert_en(RTL_ENABLED);
    }

#if 0 //isolation between port0 and port1
    rtl_smi_reg_set((rtl_phy_t)RTL_PORT_0,16,4,0x101);
    rtl_smi_reg_set((rtl_phy_t)RTL_PORT_1,16,4,0x108);
#endif

#if 0
    rtl_stp_set(RTL_PORT_0,RTL_SPAN_LEARN);
    rtl_stp_set(RTL_PORT_1,RTL_SPAN_LEARN);
    
    rtl_cpu_enable_set(1);       
    rtl_cpu_tagInsertEnable_set(1);
    rtl_cpu_tagRemoveEnable_set(1);
    rtl_cpu_cpuTagAwareEnable_set(1);
#endif
    
    return RT_EOK;
}

void rtl_read_reg(int argc, char** argv)
{
    rt_uint16_t val;
    
    if(argc == 4) {
        val = rtl_smi_reg_get((rt_uint8_t)atoi(argv[1]),(rt_uint8_t)atoi(argv[2]),(rt_uint8_t)atoi(argv[3]));
        rt_kprintf("val=0x%x\n",val);
    }
}

void rtl_write_reg(int argc, char** argv){    
    
    if(argc == 5) {
        rtl_smi_reg_set((rt_uint8_t)atoi(argv[1]),(rt_uint8_t)atoi(argv[2]),(rt_uint8_t)atoi(argv[3]),(rt_uint16_t)atoi(argv[4]));
        rt_kprintf("rtl_write_reg ok!\n");
    }
}

MSH_CMD_EXPORT(rtl_read_reg,);
MSH_CMD_EXPORT(rtl_write_reg,);




/* End of file****************************************************************/
