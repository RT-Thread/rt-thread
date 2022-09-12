/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-9-3        Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_DA9062)

#include <rtthread.h>
#include <rtdevice.h>
#include "da9062_reg.h"

#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "da9062"
#define DBG_COLOR
#include <rtdbg.h>

struct regmap_range
{
    uint32_t range_min;
    uint32_t range_max;
};
#define regmap_reg_range(low, high) { .range_min = low, .range_max = high, }
#define ARRAY_SIZE(arr)    (sizeof(arr) / sizeof((arr)[0]))

#define BYTE_TO_BINARY_PATTERN "\t%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')


#define DEF_DA9062_PAGE0_SLAVEADDR    (0xB0>>1)

static struct rt_i2c_bus_device *g_psNuEpwmCap = RT_NULL;

static const struct regmap_range da9062_aa_readable_ranges[] =
{
    regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
    regmap_reg_range(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
    regmap_reg_range(DA9062AA_IRQ_MASK_A, DA9062AA_IRQ_MASK_C),
    regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_GPIO_4),
    regmap_reg_range(DA9062AA_GPIO_WKUP_MODE, DA9062AA_BUCK4_CONT),
    regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
    regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
    regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
    regmap_reg_range(DA9062AA_COUNT_S, DA9062AA_SECOND_D),
    regmap_reg_range(DA9062AA_SEQ, DA9062AA_ID_4_3),
    regmap_reg_range(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
    regmap_reg_range(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
    regmap_reg_range(DA9062AA_SEQ_A, DA9062AA_BUCK3_CFG),
    regmap_reg_range(DA9062AA_VBUCK2_A, DA9062AA_VBUCK4_A),
    regmap_reg_range(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
    regmap_reg_range(DA9062AA_VLDO1_A, DA9062AA_VLDO4_A),
    regmap_reg_range(DA9062AA_VBUCK2_B, DA9062AA_VBUCK4_B),
    regmap_reg_range(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
    regmap_reg_range(DA9062AA_VLDO1_B, DA9062AA_VLDO4_B),
    regmap_reg_range(DA9062AA_BBAT_CONT, DA9062AA_BBAT_CONT),
#if 0
    regmap_reg_range(DA9062AA_INTERFACE, DA9062AA_CONFIG_E),
    regmap_reg_range(DA9062AA_CONFIG_G, DA9062AA_CONFIG_K),
    regmap_reg_range(DA9062AA_CONFIG_M, DA9062AA_CONFIG_M),
    regmap_reg_range(DA9062AA_TRIM_CLDR, DA9062AA_GP_ID_19),
    regmap_reg_range(DA9062AA_DEVICE_ID, DA9062AA_CONFIG_ID),
#endif
};

static const struct regmap_range da9062_aa_writeable_ranges[] =
{
    regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_PAGE_CON),
    regmap_reg_range(DA9062AA_FAULT_LOG, DA9062AA_EVENT_C),
    regmap_reg_range(DA9062AA_IRQ_MASK_A, DA9062AA_IRQ_MASK_C),
    regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_GPIO_4),
    regmap_reg_range(DA9062AA_GPIO_WKUP_MODE, DA9062AA_BUCK4_CONT),
    regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
    regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
    regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
    regmap_reg_range(DA9062AA_COUNT_S, DA9062AA_ALARM_Y),
    regmap_reg_range(DA9062AA_SEQ, DA9062AA_ID_4_3),
    regmap_reg_range(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
    regmap_reg_range(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
    regmap_reg_range(DA9062AA_SEQ_A, DA9062AA_BUCK3_CFG),
    regmap_reg_range(DA9062AA_VBUCK2_A, DA9062AA_VBUCK4_A),
    regmap_reg_range(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
    regmap_reg_range(DA9062AA_VLDO1_A, DA9062AA_VLDO4_A),
    regmap_reg_range(DA9062AA_VBUCK2_B, DA9062AA_VBUCK4_B),
    regmap_reg_range(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
    regmap_reg_range(DA9062AA_VLDO1_B, DA9062AA_VLDO4_B),
    regmap_reg_range(DA9062AA_BBAT_CONT, DA9062AA_BBAT_CONT),
    regmap_reg_range(DA9062AA_GP_ID_0, DA9062AA_GP_ID_19),
};

static const struct regmap_range da9062_aa_volatile_ranges[] =
{
    regmap_reg_range(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
    regmap_reg_range(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
    regmap_reg_range(DA9062AA_CONTROL_A, DA9062AA_CONTROL_B),
    regmap_reg_range(DA9062AA_CONTROL_E, DA9062AA_CONTROL_F),
    regmap_reg_range(DA9062AA_BUCK2_CONT, DA9062AA_BUCK4_CONT),
    regmap_reg_range(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
    regmap_reg_range(DA9062AA_LDO1_CONT, DA9062AA_LDO4_CONT),
    regmap_reg_range(DA9062AA_DVC_1, DA9062AA_DVC_1),
    regmap_reg_range(DA9062AA_COUNT_S, DA9062AA_SECOND_D),
    regmap_reg_range(DA9062AA_SEQ, DA9062AA_SEQ),
    regmap_reg_range(DA9062AA_EN_32K, DA9062AA_EN_32K),
};

static int da9062_i2c_write(uint8_t u8addr, uint8_t u8data)
{
    struct rt_i2c_msg msg;
    char au8TxData[2];

    RT_ASSERT(g_psNuEpwmCap != NULL);

    au8TxData[0] = u8addr;          //addr [ 7:0]
    au8TxData[1] = u8data;          //data [ 7:0]

    msg.addr  = DEF_DA9062_PAGE0_SLAVEADDR;      /* Slave address */
    msg.flags = RT_I2C_WR;                       /* Write flag */
    msg.buf   = (rt_uint8_t *)&au8TxData[0];     /* Slave register address */
    msg.len   = sizeof(au8TxData);               /* Number of bytes sent */

    if (g_psNuEpwmCap && rt_i2c_transfer(g_psNuEpwmCap, &msg, 1) != 1)
    {
        rt_kprintf("[Failed] addr=%x, data=%d\n", u8addr, u8data);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int da9062_i2c_read(uint8_t u8addr, uint8_t *pu8data)
{
    struct rt_i2c_msg msgs[2];
    char u8TxData;

    RT_ASSERT(g_psNuEpwmCap != NULL);
    RT_ASSERT(pu8data != NULL);

    u8TxData      = u8addr;        //addr [ 7:0]

    msgs[0].addr  = DEF_DA9062_PAGE0_SLAVEADDR;  /* Slave address */
    msgs[0].flags = RT_I2C_WR;                   /* Write flag */
    msgs[0].buf   = (rt_uint8_t *)&u8TxData;     /* Number of bytes sent */
    msgs[0].len   = sizeof(u8TxData);            /* Number of bytes read */

    msgs[1].addr  = DEF_DA9062_PAGE0_SLAVEADDR;  /* Slave address */
    msgs[1].flags = RT_I2C_RD;                   /* Read flag */
    msgs[1].buf   = (rt_uint8_t *)pu8data ;      /* Read data pointer */
    msgs[1].len   = 1;                           /* Number of bytes read */

    if (rt_i2c_transfer(g_psNuEpwmCap, &msgs[0], 2) != 2)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

int da9062_regs_dump(void)
{
    int i;

    rt_kprintf("============================================================================\n");
    rt_kprintf("|Value@Addr |\t7\t6\t5\t4\t3\t2\t1\t0  |\n");
    rt_kprintf("============================================================================\n");
    for (i = 0; i < ARRAY_SIZE(da9062_aa_readable_ranges); i++)
    {
        int start = da9062_aa_readable_ranges[i].range_min;
        int end = da9062_aa_readable_ranges[i].range_max;
        while (start <= end)
        {
            uint8_t u8Value = 0;
            if (da9062_i2c_read((uint8_t)start, &u8Value) != RT_EOK)
            {
                rt_kprintf("Can't readback value@0x%2x!\n", start);
                return -RT_ERROR;
            }
            else
            {
                rt_kprintf("| 0x%02X@0x%02X | "BYTE_TO_BINARY_PATTERN  "  |\n", u8Value, start, BYTE_TO_BINARY(u8Value));
            }
            start++;
        }
    }
    rt_kprintf("============================================================================\n");
    return RT_EOK;
}

int rt_hw_da9062_init(const char *i2c_dev)
{
    RT_ASSERT(i2c_dev != RT_NULL);

    /* Find I2C bus */
    g_psNuEpwmCap = (struct rt_i2c_bus_device *)rt_device_find(i2c_dev);
    if (g_psNuEpwmCap == RT_NULL)
    {
        LOG_E("Can't found I2C bus - %s..!\n", i2c_dev);
        goto exit_rt_hw_da9062_init;
    }

    return RT_EOK;

exit_rt_hw_da9062_init:

    return -RT_ERROR;
}

static int da9062_dump(int argc, char **argv)
{
    rt_hw_da9062_init("i2c0");
    da9062_regs_dump();
}

#ifdef FINSH_USING_MSH
    MSH_CMD_EXPORT(da9062_dump, dump da9062 registers);
#endif

#endif //#if defined(NU_PKG_USING_DA9062)
