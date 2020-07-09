/*
 * File      : gt9xx.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-01-01     Urey      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include <board.h>
#include <drv_gpio.h>
#include "gt9xx.h"
#include "gt9xx_cfg.h"
#include "gt9xx_firmware.h"

#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#ifdef RT_USING_GT9XX

static int tpd_flag = 0;
int tpd_halt = 0;

#ifdef TPD_HAVE_BUTTON
static int tpd_keys_local[TPD_KEY_COUNT] = TPD_KEYS;
static int tpd_keys_dim_local[TPD_KEY_COUNT][4] = TPD_KEYS_DIM;
#endif

#if GTP_GESTURE_WAKEUP
typedef enum
{
    DOZE_DISABLED = 0,
    DOZE_ENABLED = 1,
    DOZE_WAKEUP = 2,
}DOZE_T;
static DOZE_T doze_status = DOZE_DISABLED;
static int8_t gtp_enter_doze(struct rt_i2c_bus_device *client);
#endif

#if GTP_HAVE_TOUCH_KEY
const uint16_t touch_key_array[] = GTP_KEY_TAB;
#define GTP_MAX_KEY_NUM ( sizeof( touch_key_array )/sizeof( touch_key_array[0] ) )
#endif

#if (defined(TPD_WARP_START) && defined(TPD_WARP_END))
static int tpd_wb_start_local[TPD_WARP_CNT] = TPD_WARP_START;
static int tpd_wb_end_local[TPD_WARP_CNT]   = TPD_WARP_END;
#endif

#if (defined(TPD_HAVE_CALIBRATION) && !defined(TPD_CUSTOM_CALIBRATION))
static int tpd_calmat_local[8]     = TPD_CALIBRATION_MATRIX;
static int tpd_def_calmat_local[8] = TPD_CALIBRATION_MATRIX;
#endif

static rt_mailbox_t gt9xx_mb;

int gtp_send_cfg(struct rt_i2c_bus_device *client);
void gtp_reset_guitar(struct rt_i2c_bus_device *client, int ms);


static uint8_t config[GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH]
                      = {GTP_REG_CONFIG_DATA >> 8, GTP_REG_CONFIG_DATA & 0xff};

#pragma pack(1)
typedef struct
{
    u16 pid;                 //product id   //
    u16 vid;                 //version id   //
} st_tpd_info;
#pragma pack()

st_tpd_info tpd_info;
u8 int_type = 0;
u32 abs_x_max = 0;
u32 abs_y_max = 0;
u8 gtp_rawdiff_mode = 0;
u8 cfg_len = 0;
u8 pnl_init_error = 0;



/* proc file system */
s32 i2c_read_bytes(struct rt_i2c_bus_device *i2c, u16 addr, u8 *rxbuf, int len)
{
    struct rt_i2c_msg         msgs[2];
    u8 buffer[MAX_TRANSACTION_LENGTH];
    u8 retry;
    u16 left = len;
    u16 offset = 0;

    msgs[0].addr    = GT910_IIC_ADDR;
    msgs[0].flags   = RT_I2C_WR;
    msgs[0].buf     = &buffer[0];
    msgs[0].len     = 2;

    msgs[1].addr    = GT910_IIC_ADDR;
    msgs[1].flags   = RT_I2C_RD;
    msgs[1].buf     = rxbuf;
    msgs[1].len     = len;

    while(left > 0)
    {
        buffer[0] = (addr >> 8) & 0xFF;
        buffer[1] = (addr >> 0) & 0xFF;

        msgs[1].buf     = &rxbuf[offset];

        if (left > MAX_TRANSACTION_LENGTH)
        {
            msgs[1].len = MAX_TRANSACTION_LENGTH;
            left -= MAX_TRANSACTION_LENGTH;
            offset += MAX_TRANSACTION_LENGTH;
        }
        else
        {
            msgs[1].len = left;
            left = 0;
        }

        retry = 0;

        while (rt_i2c_transfer(i2c, &msgs[0], 2) != 2)
        {
            retry++;

            if (retry == 5)
            {
                GTP_ERROR("I2C read 0x%X length=%d failed\n", addr + offset, len);
                return -1;
            }
        }
    }

    return 0;
}
s32 i2c_write_bytes(struct rt_i2c_bus_device *i2c, u16 addr, u8 *txbuf, int len)
{
    struct rt_i2c_msg         msgs[1];
    u8 buffer[MAX_TRANSACTION_LENGTH];
    u16 left = len;
    u16 offset = 0;
    u8 retry = 0;

    msgs[0].addr    = GT910_IIC_ADDR;
    msgs[0].flags   = RT_I2C_WR;
    msgs[0].buf     = &buffer[0];
    msgs[0].len     = 2;

    GTP_DEBUG("i2c_write_bytes to device %02X address %04X len %d\n", GT910_IIC_ADDR, addr, len);
    while (left > 0)
    {
        retry = 0;

        buffer[0] = ((addr + offset) >> 8) & 0xFF;
        buffer[1] = (addr + offset) & 0xFF;

        if (left > MAX_I2C_TRANSFER_SIZE)
        {
            memcpy(&buffer[GTP_ADDR_LENGTH], &txbuf[offset], MAX_I2C_TRANSFER_SIZE);
            msgs[0].len = MAX_TRANSACTION_LENGTH;
            left -= MAX_I2C_TRANSFER_SIZE;
            offset += MAX_I2C_TRANSFER_SIZE;
        }
        else
        {
            memcpy(&buffer[GTP_ADDR_LENGTH], &txbuf[offset], left);
            msgs[0].len = left + GTP_ADDR_LENGTH;
            left = 0;
        }

        //GTP_DEBUG("byte left %d offset %d\n", left, offset);
        while (rt_i2c_transfer(i2c, &msgs[0], 1) != 1)
        {
            retry++;

            //if (retry == 20)
            if (retry == 5)
            {
                GTP_ERROR("I2C write 0x%X%X length=%d failed\n", buffer[0], buffer[1], len);
                return -1;
            }
        }
    }

    return 0;
}

s32 gtp_i2c_write(struct rt_i2c_bus_device *i2c, u8 *buf, s32 len)
{
    s32 ret = -1;
    u16 addr = (buf[0] << 8) + buf[1];

    ret = i2c_write_bytes(i2c, addr, &buf[2], len - 2);
    if (!ret)
    {
        return 1;
    }
    else
    {
    #if GTP_GESTURE_WAKEUP
        if (DOZE_ENABLED == doze_status)
        {
            return ret;
        }
    #endif
    #if GTP_COMPATIBLE_MODE
        if (CHIP_TYPE_GT9F == gtp_chip_type)
        {
            gtp_recovery_reset(client);
        }
        else
    #endif
        {
            gtp_reset_guitar(i2c, 20);
        }
        return ret;
    }
}

s32 gtp_i2c_read(struct rt_i2c_bus_device *i2c, u8 *buf, s32 len)
{
    s32 ret = -1;
    u16 addr = (buf[0] << 8) + buf[1];

    ret = i2c_read_bytes(i2c, addr, &buf[2], len - 2);

    if (!ret)
    {
        return 2;
    }
    else
    {
#if GTP_GESTURE_WAKEUP
        if (DOZE_ENABLED == doze_status)
        {
            return ret;
        }
#endif
#if GTP_COMPATIBLE_MODE
        if (CHIP_TYPE_GT9F == gtp_chip_type)
        {
            gtp_recovery_reset(client);
        }
        else
#endif
        {
            gtp_reset_guitar(i2c, 20);
        }
        return ret;
    }
}

s32 gtp_i2c_read_dbl_check(struct rt_i2c_bus_device *i2c, u16 addr, u8 *rxbuf, int len)
{
    u8 buf[16] = {0};
    u8 confirm_buf[16] = {0};
    u8 retry = 0;

    while (retry++ < 3)
    {
        memset(buf, 0xAA, 16);
        buf[0] = (u8)(addr >> 8);
        buf[1] = (u8)(addr & 0xFF);
        gtp_i2c_read(i2c, buf, len + 2);

        memset(confirm_buf, 0xAB, 16);
        confirm_buf[0] = (u8)(addr >> 8);
        confirm_buf[1] = (u8)(addr & 0xFF);
        gtp_i2c_read(i2c, confirm_buf, len + 2);

        if (!memcmp(buf, confirm_buf, len+2))
        {
            memcpy(rxbuf, confirm_buf+2, len);
            return SUCCESS;
        }
    }
    GTP_ERROR("i2c read 0x%04X, %d bytes, double check failed!", addr, len);
    return FAIL;
}

s32 gtp_send_cfg(struct rt_i2c_bus_device *i2c)
{
    s32 ret = 1;

#if GTP_DRIVER_SEND_CFG
    s32 retry = 0;

    if (pnl_init_error)
    {
        GTP_INFO("Error occurred in init_panel, no config sent!");
        return 0;
    }

    GTP_INFO("Driver Send Config");
    for (retry = 0; retry < 5; retry++)
    {
        ret = gtp_i2c_write(i2c, config, GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH);

        if (ret > 0)
        {
            break;
        }
    }
#endif
    return ret;
}

#if GTP_CHARGER_SWITCH
static int gtp_send_chr_cfg(struct rt_i2c_bus_device *i2c)
{
    s32 ret = 1;
#if GTP_DRIVER_SEND_CFG
    s32 retry = 0;

    if (pnl_init_error) {
        GTP_INFO("Error occurred in init_panel, no config sent!");
        return 0;
    }

    GTP_INFO("Driver Send Config");
    for (retry = 0; retry < 5; retry++) {
        ret = gtp_i2c_write(i2c, gtp_charger_config, GTP_CONFIG_MAX_LENGTH + GTP_ADDR_LENGTH);
        if (ret > 0) {
            break;
        }
    }
#endif
    return ret;
}
#endif


s32 gtp_read_version(struct rt_i2c_bus_device *i2c, u16 *version)
{
    s32 ret = -1;
    s32 i;
    u8 buf[8] = {GTP_REG_VERSION >> 8, GTP_REG_VERSION & 0xff};

    GTP_DEBUG_FUNC();

    ret = gtp_i2c_read(i2c, buf, sizeof(buf));

    if (ret < 0)
    {
        GTP_ERROR("GTP read version failed");
        return ret;
    }

    if (version)
    {
        *version = (buf[7] << 8) | buf[6];
    }

    tpd_info.vid = *version;
    tpd_info.pid = 0x00;

    for (i = 0; i < 4; i++)
    {
        if (buf[i + 2] < 0x30)break;

        tpd_info.pid |= ((buf[i + 2] - 0x30) << ((3 - i) * 4));
    }

    if (buf[5] == 0x00)
    {
        GTP_INFO("IC VERSION: %c%c%c_%02x%02x",
             buf[2], buf[3], buf[4], buf[7], buf[6]);
    }
    else
    {
        GTP_INFO("IC VERSION:%c%c%c%c_%02x%02x",
             buf[2], buf[3], buf[4], buf[5], buf[7], buf[6]);
    }
    return ret;
}

static s32 gtp_init_panel(struct rt_i2c_bus_device *i2c)
{
    s32 ret = 0;

#if GTP_DRIVER_SEND_CFG
    s32 i;
    u8 check_sum = 0;
    u8 opr_buf[16];
    u8 sensor_id = 0;
    u8 drv_cfg_version;
    u8 flash_cfg_version;

    u8 cfg_info_group0[] = CTP_CFG_GROUP0;
    u8 cfg_info_group1[] = CTP_CFG_GROUP1;
    u8 cfg_info_group2[] = CTP_CFG_GROUP2;
    u8 cfg_info_group3[] = CTP_CFG_GROUP3;
    u8 cfg_info_group4[] = CTP_CFG_GROUP4;
    u8 cfg_info_group5[] = CTP_CFG_GROUP5;
    u8 *send_cfg_buf[] = {
                    cfg_info_group0,
                    cfg_info_group1,
                    cfg_info_group2,
                    cfg_info_group3,
                    cfg_info_group4,
                    cfg_info_group5
    };
    u8 cfg_info_len[] = {
                    CFG_GROUP_LEN(cfg_info_group0),
                    CFG_GROUP_LEN(cfg_info_group1),
                    CFG_GROUP_LEN(cfg_info_group2),
                    CFG_GROUP_LEN(cfg_info_group3),
                    CFG_GROUP_LEN(cfg_info_group4),
                    CFG_GROUP_LEN(cfg_info_group5)
    };
#if GTP_CHARGER_SWITCH
    const u8 cfg_grp0_charger[] = GTP_CFG_GROUP0_CHARGER;
    const u8 cfg_grp1_charger[] = GTP_CFG_GROUP1_CHARGER;
    const u8 cfg_grp2_charger[] = GTP_CFG_GROUP2_CHARGER;
    const u8 cfg_grp3_charger[] = GTP_CFG_GROUP3_CHARGER;
    const u8 cfg_grp4_charger[] = GTP_CFG_GROUP4_CHARGER;
    const u8 cfg_grp5_charger[] = GTP_CFG_GROUP5_CHARGER;
    const u8 *cfgs_charger[] = {
                    cfg_grp0_charger,
                    cfg_grp1_charger,
                    cfg_grp2_charger,
                    cfg_grp3_charger,
                    cfg_grp4_charger,
                    cfg_grp5_charger
    };
    u8 cfg_lens_charger[] = {
                    CFG_GROUP_LEN(cfg_grp0_charger),
                    CFG_GROUP_LEN(cfg_grp1_charger),
                    CFG_GROUP_LEN(cfg_grp2_charger),
                    CFG_GROUP_LEN(cfg_grp3_charger),
                    CFG_GROUP_LEN(cfg_grp4_charger),
                    CFG_GROUP_LEN(cfg_grp5_charger)
    };
#endif

    GTP_DEBUG("Config Groups\' Lengths: %d, %d, %d, %d, %d, %d",
              cfg_info_len[0],
              cfg_info_len[1],
              cfg_info_len[2],
              cfg_info_len[3],
              cfg_info_len[4],
              cfg_info_len[5] );

    if ((!cfg_info_len[1]) && (!cfg_info_len[2]) && (!cfg_info_len[3]) && (!cfg_info_len[4]) && (!cfg_info_len[5]))
    {
        sensor_id = 0;
    }
    else
    {
#if GTP_COMPATIBLE_MODE
        if (CHIP_TYPE_GT9F == gtp_chip_type)
        {
            rt_thread_delay(rt_tick_from_millisecond(50));
        }
#endif
        ret = gtp_i2c_read_dbl_check(i2c, GTP_REG_SENSOR_ID, &sensor_id, 1);
        if (SUCCESS == ret)
        {
            if (sensor_id >= 0x06)
            {
                GTP_ERROR("Invalid sensor_id(0x%02X), No Config Sent!", sensor_id);
                pnl_init_error = 1;
                return -1;
            }
        }
        else
        {
            GTP_ERROR("Failed to get sensor_id, No config sent!");
            pnl_init_error = 1;
            return -1;
        }
        GTP_INFO("Sensor_ID: %d", sensor_id);
    }

    cfg_len = cfg_info_len[sensor_id];

    GTP_INFO("CTP_CONFIG_GROUP%d used, config length: %d", sensor_id, cfg_len);

    if (cfg_len < GTP_CONFIG_MIN_LENGTH)
    {
        GTP_ERROR("CTP_CONFIG_GROUP%d is INVALID CONFIG GROUP! NO Config Sent! You need to check you header file CFG_GROUP section!",
                  sensor_id);
        pnl_init_error = 1;
        return -1;
    }

#if GTP_COMPATIBLE_MODE
    if (CHIP_TYPE_GT9F != gtp_chip_type)
#endif
    {
        ret = gtp_i2c_read_dbl_check(i2c, GTP_REG_CONFIG_DATA, &opr_buf[0], 1);
        if (ret == SUCCESS)
        {
            GTP_DEBUG("CFG_CONFIG_GROUP%d Config Version: %d, 0x%02X; IC Config Version: %d, 0x%02X",
                      sensor_id,
                      send_cfg_buf[sensor_id][0],
                      send_cfg_buf[sensor_id][0],
                      opr_buf[0],
                      opr_buf[0]);

            flash_cfg_version = opr_buf[0];
            drv_cfg_version = send_cfg_buf[sensor_id][0];       // backup  config version

            if (flash_cfg_version < 90 && flash_cfg_version > drv_cfg_version)
            {
                send_cfg_buf[sensor_id][0] = 0x00;
            }
        }
        else
        {
            GTP_ERROR("Failed to get ic config version!No config sent!");
            return -1;
        }
    }
    memset(&config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
    memcpy(&config[GTP_ADDR_LENGTH], send_cfg_buf[sensor_id], cfg_len);

#if GTP_CUSTOM_CFG
    config[RESOLUTION_LOC] = (u8)GTP_MAX_WIDTH;
    config[RESOLUTION_LOC + 1] = (u8)(GTP_MAX_WIDTH>>8);
    config[RESOLUTION_LOC + 2] = (u8)GTP_MAX_HEIGHT;
    config[RESOLUTION_LOC + 3] = (u8)(GTP_MAX_HEIGHT>>8);

    if (GTP_INT_TRIGGER == 0)    //RISING
    {
        config[TRIGGER_LOC] &= 0xfe;
    }
    else if (GTP_INT_TRIGGER == 1)    //FALLING
    {
        config[TRIGGER_LOC] |= 0x01;
    }
#endif  // GTP_CUSTOM_CFG

    check_sum = 0;
    for (i = GTP_ADDR_LENGTH; i < cfg_len; i++)
    {
        check_sum += config[i];
    }
    config[cfg_len] = (~check_sum) + 1;

#if GTP_CHARGER_SWITCH
    GTP_DEBUG("Charger Config Groups Length: %d, %d, %d, %d, %d, %d",
              cfg_lens_charger[0], cfg_lens_charger[1],
              cfg_lens_charger[2], cfg_lens_charger[3],
              cfg_lens_charger[4], cfg_lens_charger[5]);

    memset(&gtp_charger_config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);
    if (cfg_lens_charger[sensor_id] == cfg_len)
        memcpy(&gtp_charger_config[GTP_ADDR_LENGTH], cfgs_charger[sensor_id], cfg_len);

#if GTP_CUSTOM_CFG
    gtp_charger_config[RESOLUTION_LOC] = (u8) GTP_MAX_WIDTH;
    gtp_charger_config[RESOLUTION_LOC + 1] = (u8) (GTP_MAX_WIDTH >> 8);
    gtp_charger_config[RESOLUTION_LOC + 2] = (u8) GTP_MAX_HEIGHT;
    gtp_charger_config[RESOLUTION_LOC + 3] = (u8) (GTP_MAX_HEIGHT >> 8);

    if (GTP_INT_TRIGGER == 0) /* RISING  */
    gtp_charger_config[TRIGGER_LOC] &= 0xfe;
    else if (GTP_INT_TRIGGER == 1) /* FALLING */
    gtp_charger_config[TRIGGER_LOC] |= 0x01;
#endif /* END GTP_CUSTOM_CFG */
    if (cfg_lens_charger[sensor_id] != cfg_len)
        memset(&gtp_charger_config[GTP_ADDR_LENGTH], 0, GTP_CONFIG_MAX_LENGTH);

    check_sum = 0;
    for (i = GTP_ADDR_LENGTH; i < cfg_len; i++)
    {
        check_sum += gtp_charger_config[i];
    }
    gtp_charger_config[cfg_len] = (~check_sum) + 1;

#endif /* END GTP_CHARGER_SWITCH */

#else // DRIVER NOT SEND CONFIG
    cfg_len = GTP_CONFIG_MAX_LENGTH;
    ret = gtp_i2c_read(client, config, cfg_len + GTP_ADDR_LENGTH);
    if (ret < 0)
    {
        GTP_ERROR("Read Config Failed, Using DEFAULT Resolution & INT Trigger!");
        abs_x_max = GTP_MAX_WIDTH;
        abs_y_max = GTP_MAX_HEIGHT;
        int_type = GTP_INT_TRIGGER;
    }
#endif // GTP_DRIVER_SEND_CFG

    GTP_DEBUG_FUNC();
    if ((abs_x_max == 0) && (abs_y_max == 0))
    {
        abs_x_max = (config[RESOLUTION_LOC + 1] << 8) + config[RESOLUTION_LOC];
        abs_y_max = (config[RESOLUTION_LOC + 3] << 8) + config[RESOLUTION_LOC + 2];
        int_type = (config[TRIGGER_LOC]) & 0x03;
    }

#if GTP_COMPATIBLE_MODE
    if (CHIP_TYPE_GT9F == gtp_chip_type)
    {
        u8 have_key = 0;
        if (is_950)
        {
            driver_num = config[GTP_REG_MATRIX_DRVNUM - GTP_REG_CONFIG_DATA + 2];
            sensor_num = config[GTP_REG_MATRIX_SENNUM - GTP_REG_CONFIG_DATA + 2];
        }
        else
        {
            driver_num = (config[CFG_LOC_DRVA_NUM]&0x1F) + (config[CFG_LOC_DRVB_NUM]&0x1F);
            sensor_num = (config[CFG_LOC_SENS_NUM]&0x0F) + ((config[CFG_LOC_SENS_NUM]>>4)&0x0F);
        }

        have_key = config[GTP_REG_HAVE_KEY - GTP_REG_CONFIG_DATA + 2] & 0x01;    // have key or not
        if (1 == have_key)
        {
            driver_num--;
        }

        GTP_INFO("Driver * Sensor: %d * %d(Key: %d), X_MAX = %d, Y_MAX = %d, TRIGGER = 0x%02x",
                        driver_num, sensor_num, have_key, abs_x_max,abs_y_max,int_type);
    }
    else
#endif
    {
#if GTP_DRIVER_SEND_CFG
        ret = gtp_send_cfg(i2c);
        if (ret < 0)
        {
            GTP_ERROR("Send config error.");
        }
#if GTP_COMPATIBLE_MODE
        if (CHIP_TYPE_GT9F != gtp_chip_type)
#endif
        {
            /* for resume to send config */
            if (flash_cfg_version < 90 && flash_cfg_version > drv_cfg_version)
            {
                config[GTP_ADDR_LENGTH] = drv_cfg_version;
                check_sum = 0;
                for (i = GTP_ADDR_LENGTH; i < cfg_len; i++)
                {
                    check_sum += config[i];
                }
                config[cfg_len] = (~check_sum) + 1;
            }
        }
#endif
        GTP_INFO("X_MAX = %d, Y_MAX = %d, TRIGGER = 0x%02x", abs_x_max, abs_y_max, int_type);
    }

    rt_thread_delay(RT_TICK_PER_SECOND / 20);
    return 0;
}

static s8 gtp_i2c_test(struct rt_i2c_bus_device *i2c)
{
    u8 retry = 0;
    s8 ret = -1;
    u32 hw_info = 0;

    GTP_DEBUG_FUNC();

    while (retry++ < 5)
    {
        ret = i2c_read_bytes(i2c, GTP_REG_HW_INFO, (u8 *)&hw_info, sizeof(hw_info));

        if ((!ret) && (hw_info == 0x00900600))              //20121212
        {
            return ret;
        }

        GTP_ERROR("GTP_REG_HW_INFO : %08X", hw_info);
        GTP_ERROR("GTP i2c test failed time %d.", retry);
        rt_thread_delay(rt_tick_from_millisecond(10));
    }

    return -1;
}


void gtp_int_sync(s32 ms)
{
    gpio_direction_output(GTP_INT_PORT,GTP_INT_PIN,0);
    rt_thread_delay(rt_tick_from_millisecond(ms));
    gpio_set_func(GTP_INT_PORT, GTP_INT_PIN, GPIO_INPUT | GPIO_INT_FE);
}

void gtp_reset_guitar(struct rt_i2c_bus_device *i2c, s32 ms)
{
    GTP_INFO("GTP RESET!\n");

    /* RESET skip */
//    GTP_GPIO_OUTPUT(GTP_RST_PORT, 0);
//    rt_thread_delay(rt_tick_from_millisecond(ms));
//    GTP_GPIO_OUTPUT(GTP_INT_PORT, client->addr == 0x14);
//
//    rt_thread_delay(rt_tick_from_millisecond(2));
//    GTP_GPIO_OUTPUT(GTP_RST_PORT, 1);


#if GTP_COMPATIBLE_MODE
    if (CHIP_TYPE_GT9F == gtp_chip_type)
    {
        return;
    }
#endif

    gtp_int_sync(50);
}

#if GTP_GESTURE_WAKEUP
static s8 gtp_enter_doze(struct rt_i2c_bus_device *i2c)
{
    s8 ret = -1;
    s8 retry = 0;
    u8 i2c_control_buf[3] = {(u8)(GTP_REG_SLEEP >> 8), (u8)GTP_REG_SLEEP, 8};

    GTP_DEBUG_FUNC();

    GTP_DEBUG("Entering gesture mode...");
    while(retry++ < 5)
    {
        i2c_control_buf[0] = 0x80;
        i2c_control_buf[1] = 0x46;
        ret = gtp_i2c_write(i2c, i2c_control_buf, 3);
        if (ret < 0)
        {
            GTP_DEBUG("Failed to set gesture flag into 0x8046, %d", retry);
            continue;
        }
        i2c_control_buf[0] = 0x80;
        i2c_control_buf[1] = 0x40;
        ret = gtp_i2c_write(i2c, i2c_control_buf, 3);
        if (ret > 0)
        {
            doze_status = DOZE_ENABLED;
            GTP_INFO("Gesture mode enabled.");
            return ret;
        }
        rt_thread_delay(rt_tick_from_millisecond(10));
    }
    GTP_ERROR("GTP send gesture cmd failed.");
    return ret;
}

#else
/*******************************************************
Function:
    Eter sleep function.

Input:
    client:i2c_client.

Output:
    Executive outcomes.0--success,non-0--fail.
*******************************************************/
static s8 gtp_enter_sleep(struct rt_i2c_bus_device *i2c)
{
#if GTP_COMPATIBLE_MODE
    if (CHIP_TYPE_GT9F == gtp_chip_type)
    {
        u8 i2c_status_buf[3] = {0x80, 0x44, 0x00};
        s32 ret = 0;

        ret = gtp_i2c_read(i2c, i2c_status_buf, 3);
        if(ret <= 0)
        {
             GTP_ERROR("[gtp_enter_sleep]Read ref status reg error.");
        }

        if (i2c_status_buf[2] & 0x80)
        {
            //Store bak ref
            ret = gtp_bak_ref_proc(i2c, GTP_BAK_REF_STORE);
            if(FAIL == ret)
            {
                GTP_ERROR("[gtp_enter_sleep]Store bak ref failed.");
            }
        }
    }
#endif
#if GTP_POWER_CTRL_SLEEP

    GTP_GPIO_OUTPUT(GTP_RST_PORT, 0);
    GTP_GPIO_OUTPUT(GTP_INT_PORT, 0);
    rt_thread_delay(rt_tick_from_millisecond(10));

#ifdef MT6573
    mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
    mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
    mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ZERO);
    rt_thread_delay(rt_tick_from_millisecond(30));
#else               // ( defined(MT6575) || defined(MT6577) || defined(MT6589) )

    #ifdef TPD_POWER_SOURCE_1800
        hwPowerDown(TPD_POWER_SOURCE_1800, "TP");
    #endif

    #ifdef TPD_POWER_SOURCE_CUSTOM
        hwPowerDown(TPD_POWER_SOURCE_CUSTOM, "TP");
    #else
        hwPowerDown(MT65XX_POWER_LDO_VGP2, "TP");
    #endif
#endif

    GTP_INFO("GTP enter sleep by poweroff!");
    return 0;

#else
    {
        s8 ret = -1;
        s8 retry = 0;
        u8 i2c_control_buf[3] = {(u8)(GTP_REG_SLEEP >> 8), (u8)GTP_REG_SLEEP, 5};


        GTP_GPIO_OUTPUT(GTP_INT_PORT, 0);
        rt_thread_delay(rt_tick_from_millisecond(5));

        while (retry++ < 5)
        {
            ret = gtp_i2c_write(i2c, i2c_control_buf, 3);

            if (ret > 0)
            {
                GTP_INFO("GTP enter sleep!");

                return ret;
            }

            rt_thread_delay(rt_tick_from_millisecond(10));
        }

        GTP_ERROR("GTP send sleep cmd failed.");
        return ret;
    }
#endif
}
#endif

static s8 gtp_wakeup_sleep(struct rt_i2c_bus_device *i2c)
{
    u8 retry = 0;
    s8 ret = -1;

    GTP_DEBUG("GTP wakeup begin.");

#if (GTP_POWER_CTRL_SLEEP)

#if GTP_COMPATIBLE_MODE
    if (CHIP_TYPE_GT9F == gtp_chip_type)
    {
        force_reset_guitar();
        GTP_INFO("Esd recovery wakeup.");
        return 0;
    }
#endif

    while (retry++ < 5)
    {
        ret = tpd_power_on(client);

        if (ret < 0)
        {
            GTP_ERROR("I2C Power on ERROR!");
            continue;
        }
        GTP_INFO("Ic wakeup by poweron");
        return 0;
    }
#else

#if GTP_COMPATIBLE_MODE
    if (CHIP_TYPE_GT9F == gtp_chip_type)
    {
        u8 opr_buf[2] = {0};

        while (retry++ < 10)
        {
            GTP_GPIO_OUTPUT(GTP_INT_PORT, 1);
            rt_thread_delay(rt_tick_from_millisecond(5));

            ret = gtp_i2c_test(client);

            if (ret >= 0)
            {
                // Hold ss51 & dsp
                opr_buf[0] = 0x0C;
                ret = i2c_write_bytes(i2c, 0x4180, opr_buf, 1);
                if (ret < 0)
                {
                    GTP_DEBUG("Hold ss51 & dsp I2C error,retry:%d", retry);
                    continue;
                }

                // Confirm hold
                opr_buf[0] = 0x00;
                ret = i2c_read_bytes(i2c, 0x4180, opr_buf, 1);
                if (ret < 0)
                {
                    GTP_DEBUG("confirm ss51 & dsp hold, I2C error,retry:%d", retry);
                    continue;
                }
                if (0x0C != opr_buf[0])
                {
                    GTP_DEBUG("ss51 & dsp not hold, val: %d, retry: %d", opr_buf[0], retry);
                    continue;
                }
                GTP_DEBUG("ss51 & dsp has been hold");

                ret = gtp_fw_startup(i2c);
                if (FAIL == ret)
                {
                    GTP_ERROR("[gtp_wakeup_sleep]Startup fw failed.");
                    continue;
                }
                GTP_INFO("flashless wakeup sleep success");
                return ret;
            }
            force_reset_guitar();
            retry = 0;
            break;
        }
        if (retry >= 10)
        {
            GTP_ERROR("wakeup retry timeout, process esd reset");
            force_reset_guitar();
        }
        GTP_ERROR("GTP wakeup sleep failed.");
        return ret;
    }
#endif
    while (retry++ < 10)
    {
#if GTP_GESTURE_WAKEUP
        if (DOZE_WAKEUP != doze_status)
        {
            GTP_INFO("Powerkey wakeup.");
        }
        else
        {
            GTP_INFO("Gesture wakeup.");
        }
        doze_status = DOZE_DISABLED;

        gtp_reset_guitar(i2c, 20);
#else

        GTP_GPIO_OUTPUT(GTP_INT_PORT, 1);
        rt_thread_delay(rt_tick_from_millisecond(5));
#endif

        ret = gtp_i2c_test(i2c);

        if (ret >= 0)
        {
            GTP_INFO("GTP wakeup sleep.");
#if (!GTP_GESTURE_WAKEUP)
            {
                gtp_int_sync(25);
#if GTP_ESD_PROTECT
                gtp_init_ext_watchdog(client);
#endif
            }
#endif

            return ret;
        }
        gtp_reset_guitar(i2c, 20);
    }
#endif
    GTP_ERROR("GTP wakeup sleep failed.");
    return ret;
}

static struct rtgui_event_mouse emouse = {0};
static int xx = 0, yy = 0, zz = 0;
static int touch_down_up_status;
static void tpd_down(s32 x, s32 y, s32 size, s32 id)
{
    int result;

    if ((!size) && (!id))
    {
//        input_report_abs(tpd->dev, ABS_MT_PRESSURE, 100);
//        input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 100);
    }
    else
    {
//        input_report_abs(tpd->dev, ABS_MT_PRESSURE, size);
//        input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, size);
//        /* track id Start 0 */
//        input_report_abs(tpd->dev, ABS_MT_TRACKING_ID, id);
    }

//    input_report_key(tpd->dev, BTN_TOUCH, 1);
//    input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
//    input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
//    input_mt_sync(tpd->dev);
//    TPD_EM_PRINT(x, y, x, y, id, 1);

    x = x + y;
    y = x - y;
    x = x - y;
    x = 479 - x;
    
    if(touch_down_up_status)
    {
        emouse.parent.type = RTGUI_EVENT_MOUSE_MOTION;
        emouse.x = x;
        emouse.y = y;
        emouse.ts = rt_tick_get();
        
        if (xx != 0 || yy != 0 || (xx == 0 && yy == 0))
        {
            if (xx != emouse.x || emouse.y != yy)
            {
                rtgui_server_post_event(&emouse.parent, sizeof(emouse));
                zz = 0;
            }
            else
            {
                zz ++;
            }
        }
        
        xx = emouse.x;
        yy = emouse.y;
        
        if (zz >= 10)
        {
            xx = 0;
            yy = 0;
        }
    }
    else
    {
        touch_down_up_status = 1;

        //send mouse down event
        emouse.parent.sender = RT_NULL;
        emouse.wid = RT_NULL;

        emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
        emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_DOWN;
        emouse.x = x;
        emouse.y = y;
        emouse.ts = rt_tick_get();
        emouse.id = emouse.ts;

        do
        {
            result = rtgui_server_post_event(&emouse.parent, sizeof(emouse));
            if (result != RT_EOK)
            {
                rt_thread_delay(RT_TICK_PER_SECOND / 10);
            }
        }
        while (result != RT_EOK);
    }

}

static void tpd_up(s32 x, s32 y, s32 id)
{
    int result;
//    input_report_key(tpd->dev, BTN_TOUCH, 0);
//    input_mt_sync(tpd->dev);
//    TPD_EM_PRINT(x, y, x, y, id, 0);

#if (defined(MT6575) || defined(MT6577))

    if (FACTORY_BOOT == get_boot_mode() || RECOVERY_BOOT == get_boot_mode())
    {
        tpd_button(x, y, 0);
    }

#endif

    touch_down_up_status = 0;
    /* Always send touch up event. */
    emouse.parent.type = RTGUI_EVENT_MOUSE_BUTTON;
    emouse.button = RTGUI_MOUSE_BUTTON_LEFT | RTGUI_MOUSE_BUTTON_UP;
    emouse.x = xx;
    emouse.y = yy;
    emouse.ts = rt_tick_get();
    do
    {
        result = rtgui_server_post_event(&emouse.parent, sizeof(emouse));
        if (result != RT_EOK)
        {
            rt_thread_delay(RT_TICK_PER_SECOND / 10);
        }
    }
    while (result != RT_EOK);    
}

static int tpd_power_on(struct rt_i2c_bus_device *client)
{
    int ret = 0;
    int reset_count = 0;

reset_proc:
    GTP_GPIO_OUTPUT(GTP_RST_PORT, 0);
    GTP_GPIO_OUTPUT(GTP_INT_PORT, 0);
    rt_thread_delay(rt_tick_from_millisecond(10));

    gtp_reset_guitar(client, 20);

#if GTP_COMPATIBLE_MODE
    gtp_get_chip_type(client);

    if (CHIP_TYPE_GT9F == gtp_chip_type)
    {
        ret = gup_fw_download_proc(NULL, GTP_FL_FW_BURN);

        if(FAIL == ret)
        {
            GTP_ERROR("[tpd_power_on]Download fw failed.");
            if(reset_count++ < TPD_MAX_RESET_COUNT)
            {
                goto reset_proc;
            }
            else
            {
                return -1;
            }
        }

        ret = gtp_fw_startup(client);
        if(FAIL == ret)
        {
            GTP_ERROR("[tpd_power_on]Startup fw failed.");
            if(reset_count++ < TPD_MAX_RESET_COUNT)
            {
                goto reset_proc;
            }
            else
            {
                return -1;
            }
        }
    }
    else
#endif
    {
        ret = gtp_i2c_test(client);

        if (ret < 0)
        {
            GTP_ERROR("I2C communication ERROR!");

            if (reset_count < TPD_MAX_RESET_COUNT)
            {
                reset_count++;
                goto reset_proc;
            }
        }
    }
    return ret;
}


static int tpd_local_init(void)
{
#if GTP_ESD_PROTECT
    clk_tick_cnt = 2 * HZ;   // HZ: clock ticks in 1 second generated by system
    GTP_DEBUG("Clock ticks for an esd cycle: %d", clk_tick_cnt);
    INIT_DELAYED_WORK(&gtp_esd_check_work, gtp_esd_check_func);
    gtp_esd_check_workqueue = create_workqueue("gtp_esd_check");
    spin_lock_init(&esd_lock);          // 2.6.39 & later
    // esd_lock = SPIN_LOCK_UNLOCKED;   // 2.6.39 & before
#endif

#ifdef TPD_HAVE_BUTTON
    tpd_button_setting(TPD_KEY_COUNT, tpd_keys_local, tpd_keys_dim_local);// initialize tpd button data
#endif

#if (defined(TPD_WARP_START) && defined(TPD_WARP_END))
    TPD_DO_WARP = 1;
    memcpy(tpd_wb_start, tpd_wb_start_local, TPD_WARP_CNT * 4);
    memcpy(tpd_wb_end, tpd_wb_start_local, TPD_WARP_CNT * 4);
#endif

#if (defined(TPD_HAVE_CALIBRATION) && !defined(TPD_CUSTOM_CALIBRATION))
//    memcpy(tpd_calmat, tpd_def_calmat_local, 8 * 4);
//    memcpy(tpd_def_calmat, tpd_def_calmat_local, 8 * 4);
#endif

    GTP_INFO("end %s, %d\n", __FUNCTION__, __LINE__);
}

static void tpd_int_srv(void *param)
{
    if(gt9xx_mb)
    {
        rt_mb_send(gt9xx_mb, 0);

        gpio_mask_irq(GTP_INT_PORT, GTP_INT_PIN);
    }
}


static void tpd_event_process(void *param)
{
    struct rt_i2c_bus_device *i2c = (struct rt_i2c_bus_device *)param;

    u8  end_cmd[3] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF, 0};
    u8  point_data[2 + 1 + 8 * GTP_MAX_TOUCH + 1] = {GTP_READ_COOR_ADDR >> 8, GTP_READ_COOR_ADDR & 0xFF};
    u8  touch_num = 0;
    u8  finger = 0;
    static u8 pre_touch = 0;
    static u8 pre_key = 0;
#if GTP_WITH_PEN
    u8 pen_active = 0;
    static u8 pre_pen = 0;
#endif
    u8  key_value = 0;
    u8 *coor_data = NULL;
    s32 input_x = 0;
    s32 input_y = 0;
    s32 input_w = 0;
    s32 id = 0;
    s32 i  = 0;
    s32 ret = -1;

#if GTP_COMPATIBLE_MODE
    u8  rqst_data[3] = {(u8)(GTP_REG_RQST >> 8), (u8)(GTP_REG_RQST & 0xFF), 0};
#endif

#ifdef TPD_PROXIMITY
    s32 err = 0;
    hwm_sensor_data sensor_data;
    u8 proximity_status;
#endif

#if GTP_GESTURE_WAKEUP
    u8 doze_buf[3] = {0x81, 0x4B};
#endif

    while(1)
    {
        while (tpd_halt)
        {
#if GTP_GESTURE_WAKEUP
            if (DOZE_ENABLED == doze_status)
            {
                break;
            }
#endif
            tpd_flag = 0;
            rt_thread_delay(rt_tick_from_millisecond(20));
        }

//        wait_event_interruptible(waiter, tpd_flag != 0);
        /* wait */
        tpd_flag = 0;

#if GTP_CHARGER_SWITCH
        gtp_charger_switch(0);
#endif

#if GTP_GESTURE_WAKEUP
        if (DOZE_ENABLED == doze_status)
        {
            ret = gtp_i2c_read(i2c, doze_buf, 3);
            GTP_DEBUG("0x814B = 0x%02X", doze_buf[2]);
            if (ret > 0)
            {
                if ((doze_buf[2] == 'a') || (doze_buf[2] == 'b') || (doze_buf[2] == 'c') ||
                    (doze_buf[2] == 'd') || (doze_buf[2] == 'e') || (doze_buf[2] == 'g') ||
                    (doze_buf[2] == 'h') || (doze_buf[2] == 'm') || (doze_buf[2] == 'o') ||
                    (doze_buf[2] == 'q') || (doze_buf[2] == 's') || (doze_buf[2] == 'v') ||
                    (doze_buf[2] == 'w') || (doze_buf[2] == 'y') || (doze_buf[2] == 'z') ||
                    (doze_buf[2] == 0x5E) /* ^ */
                    )
                {
                    if (doze_buf[2] != 0x5E)
                    {
                        GTP_INFO("Wakeup by gesture(%c), light up the screen!", doze_buf[2]);
                    }
                    else
                    {
                        GTP_INFO("Wakeup by gesture(^), light up the screen!");
                    }
                    doze_status = DOZE_WAKEUP;
//                    input_report_key(tpd->dev, KEY_POWER, 1);
//                    input_sync(tpd->dev);
//                    input_report_key(tpd->dev, KEY_POWER, 0);
//                    input_sync(tpd->dev);
                    // clear 0x814B
                    doze_buf[2] = 0x00;
                    gtp_i2c_write(i2c, doze_buf, 3);
                }
                else if ( (doze_buf[2] == 0xAA) || (doze_buf[2] == 0xBB) ||
                    (doze_buf[2] == 0xAB) || (doze_buf[2] == 0xBA) )
                {
                    char *direction[4] = {"Right", "Down", "Up", "Left"};
                    u8 type = ((doze_buf[2] & 0x0F) - 0x0A) + (((doze_buf[2] >> 4) & 0x0F) - 0x0A) * 2;

                    GTP_INFO("%s slide to light up the screen!", direction[type]);
                    doze_status = DOZE_WAKEUP;
//                    input_report_key(tpd->dev, KEY_POWER, 1);
//                    input_sync(tpd->dev);
//                    input_report_key(tpd->dev, KEY_POWER, 0);
//                    input_sync(tpd->dev);
                    // clear 0x814B
                    doze_buf[2] = 0x00;
                    gtp_i2c_write(i2c, doze_buf, 3);
                }
                else if (0xCC == doze_buf[2])
                {
                    GTP_INFO("Double click to light up the screen!");
                    doze_status = DOZE_WAKEUP;
//                    input_report_key(tpd->dev, KEY_POWER, 1);
//                    input_sync(tpd->dev);
//                    input_report_key(tpd->dev, KEY_POWER, 0);
//                    input_sync(tpd->dev);
                    // clear 0x814B
                    doze_buf[2] = 0x00;
                    gtp_i2c_write(i2c, doze_buf, 3);
                }
                else
                {
                    // clear 0x814B
                    doze_buf[2] = 0x00;
                    gtp_i2c_write(i2c, doze_buf, 3);
                    gtp_enter_doze(i2c);
                }
            }
            continue;
        }
#endif
        ret = gtp_i2c_read(i2c, point_data, 12);
        if (ret < 0)
        {
            GTP_ERROR("I2C transfer error. errno:%d\n ", ret);
            continue;
        }
        finger = point_data[GTP_ADDR_LENGTH];

#if GTP_COMPATIBLE_MODE
        if ((finger == 0x00) && (CHIP_TYPE_GT9F == gtp_chip_type))
        {
            ret = gtp_i2c_read(i2c_client_point, rqst_data, 3);

            if(ret < 0)
            {
                GTP_ERROR("I2C transfer error. errno:%d\n ", ret);
                continue;
            }
            switch (rqst_data[2])
            {
                case GTP_RQST_BAK_REF:
                    GTP_INFO("Request Ref.");
                    rqst_processing = 1;
                    ret = gtp_bak_ref_proc(i2c_client_point, GTP_BAK_REF_SEND);
                    if(SUCCESS == ret)
                    {
                        GTP_INFO("Send ref success.");
                        rqst_data[2] = GTP_RQST_RESPONDED;
                        gtp_i2c_write(i2c_client_point, rqst_data, 3);
                        rqst_processing = 0;
                    }
                    goto exit_work_func;

                case GTP_RQST_CONFIG:
                    GTP_INFO("Request Config.");
                    ret = gtp_send_cfg(i2c_client_point);
                    if (ret < 0)
                    {
                        GTP_ERROR("Send config error.");
                    }
                    else
                    {
                        GTP_INFO("Send config success.");
                        rqst_data[2] = GTP_RQST_RESPONDED;
                        gtp_i2c_write(i2c_client_point, rqst_data, 3);
                    }
                    goto exit_work_func;

                case GTP_RQST_MAIN_CLOCK:
                    GTP_INFO("Request main clock.");
                    rqst_processing = 1;
                    ret = gtp_main_clk_proc(i2c_client_point);
                    if(SUCCESS == ret)
                    {
                        GTP_INFO("Send main clk success.");

                        rqst_data[2] = GTP_RQST_RESPONDED;
                        gtp_i2c_write(i2c_client_point, rqst_data, 3);
                        rqst_processing = 0;
                    }
                    goto exit_work_func;

                case GTP_RQST_RESET:
                    GTP_INFO("Request Reset.");
                    gtp_recovery_reset(i2c_client_point);
                    goto exit_work_func;

                default:
                    GTP_INFO("Undefined request code: 0x%02X", rqst_data[2]);
                    rqst_data[2] = GTP_RQST_RESPONDED;
                    gtp_i2c_write(i2c_client_point, rqst_data, 3);
                    break;
            }
        }
#endif

        if (finger == 0x00)
        {
            continue;
        }

        if ((finger & 0x80) == 0)
        {
            goto exit_work_func;
        }

#ifdef TPD_PROXIMITY
        if (tpd_proximity_flag == 1)
        {
            proximity_status = point_data[GTP_ADDR_LENGTH];
            GTP_DEBUG("REG INDEX[0x814E]:0x%02X\n", proximity_status);

            if (proximity_status & 0x60)                //proximity or large touch detect,enable hwm_sensor.
            {
                tpd_proximity_detect = 0;
                //sensor_data.values[0] = 0;
            }
            else
            {
                tpd_proximity_detect = 1;
                //sensor_data.values[0] = 1;
            }

            //get raw data
            GTP_DEBUG(" ps change\n");
            GTP_DEBUG("PROXIMITY STATUS:0x%02X\n", tpd_proximity_detect);
            //map and store data to hwm_sensor_data
            sensor_data.values[0] = tpd_get_ps_value();
            sensor_data.value_divide = 1;
            sensor_data.status = SENSOR_STATUS_ACCURACY_MEDIUM;
            //report to the up-layer
            ret = hwmsen_get_interrupt_data(ID_PROXIMITY, &sensor_data);

            if (ret)
            {
                GTP_ERROR("Call hwmsen_get_interrupt_data fail = %d\n", err);
            }
        }

#endif

        touch_num = finger & 0x0f;

        if (touch_num > GTP_MAX_TOUCH)
        {
            goto exit_work_func;
        }

        if (touch_num > 1)
        {
            u8 buf[8 * GTP_MAX_TOUCH] = {(GTP_READ_COOR_ADDR + 10) >> 8, (GTP_READ_COOR_ADDR + 10) & 0xff};

            ret = gtp_i2c_read(i2c, buf, 2 + 8 * (touch_num - 1));
            memcpy(&point_data[12], &buf[2], 8 * (touch_num - 1));
        }

#if (GTP_HAVE_TOUCH_KEY || GTP_PEN_HAVE_BUTTON)
        key_value = point_data[3 + 8 * touch_num];

        if (key_value || pre_key)
        {
        #if GTP_PEN_HAVE_BUTTON
            if (key_value == 0x40)
            {
                GTP_DEBUG("BTN_STYLUS & BTN_STYLUS2 Down.");
                input_report_key(pen_dev, BTN_STYLUS, 1);
                input_report_key(pen_dev, BTN_STYLUS2, 1);
                pen_active = 1;
            }
            else if (key_value == 0x10)
            {
                GTP_DEBUG("BTN_STYLUS Down, BTN_STYLUS2 Up.");
                input_report_key(pen_dev, BTN_STYLUS, 1);
                input_report_key(pen_dev, BTN_STYLUS2, 0);
                pen_active = 1;
            }
            else if (key_value == 0x20)
            {
                GTP_DEBUG("BTN_STYLUS Up, BTN_STYLUS2 Down.");
                input_report_key(pen_dev, BTN_STYLUS, 0);
                input_report_key(pen_dev, BTN_STYLUS2, 1);
                pen_active = 1;
            }
            else
            {
                GTP_DEBUG("BTN_STYLUS & BTN_STYLUS2 Up.");
                input_report_key(pen_dev, BTN_STYLUS, 0);
                input_report_key(pen_dev, BTN_STYLUS2, 0);
                if ( (pre_key == 0x40) || (pre_key == 0x20) ||
                     (pre_key == 0x10)
                   )
                {
                    pen_active = 1;
                }
            }
            if (pen_active)
            {
                touch_num = 0;      // shield pen point
                //pre_touch = 0;    // clear last pen status
            }
#endif
#if GTP_HAVE_TOUCH_KEY
            if (!pre_touch)
            {
                for (i = 0; i < GTP_MAX_KEY_NUM; i++)
                {
                    input_report_key(tpd->dev, touch_key_array[i], key_value & (0x01 << i));
                }
                touch_num = 0;  // shiled fingers
            }
#endif
        }
#endif
        pre_key = key_value;

        GTP_DEBUG("pre_touch:%02x, finger:%02x.", pre_touch, finger);

        if (touch_num)
        {
            for (i = 0; i < touch_num; i++)
            {
                coor_data = &point_data[i * 8 + 3];

                id = coor_data[0] & 0x0F;
                input_x  = coor_data[1] | coor_data[2] << 8;
                input_y  = coor_data[3] | coor_data[4] << 8;
                input_w  = coor_data[5] | coor_data[6] << 8;

                input_x = TPD_WARP_X(abs_x_max, input_x);
                input_y = TPD_WARP_Y(abs_y_max, input_y);

#if GTP_WITH_PEN
                id = coor_data[0];
                if ((id & 0x80))      // pen/stylus is activated
                {
                    GTP_DEBUG("Pen touch DOWN!");
                    pre_pen = 1;
                    //id &= 0x7F;
                    id = 0;
                    GTP_DEBUG("(%d)(%d, %d)[%d]", id, input_x, input_y, input_w);
                    gtp_pen_down(input_x, input_y, input_w, id);
                    pen_active = 1;
                }
                else
#endif
                {
                    GTP_DEBUG(" (%d)(%d, %d)[%d]", id, input_x, input_y, input_w);
                    tpd_down(input_x, input_y, input_w, id);
                }
            }
        }
        else
        {
            if (pre_touch)
            {
#if GTP_WITH_PEN
                if (pre_pen)
                {
                    GTP_DEBUG("Pen touch UP!");
                    gtp_pen_up();
                    pre_pen = 0;
                    pen_active = 1;
                }
                else
#endif
                {
                    GTP_DEBUG("Touch Release!");
                    tpd_up(0, 0, 0);
                }
            }
        }
        pre_touch = touch_num;

#if GTP_WITH_PEN
        if (pen_active)
        {
            pen_active = 0;
            input_sync(pen_dev);
        }
        else
#endif
        {
//            input_sync(tpd->dev);
        }

exit_work_func:

        if (!gtp_rawdiff_mode)
        {
            ret = gtp_i2c_write(i2c, end_cmd, 3);

            if (ret < 0)
            {
                GTP_INFO("I2C write end_cmd  error!");
            }
        }

    }
}

static int tpd_i2c_probe(struct rt_i2c_bus_device *i2c)
{
    s32 err = 0;
    s32 ret = 0;

    u16 version_info;
#if GTP_HAVE_TOUCH_KEY
    s32 idx = 0;
#endif
#ifdef TPD_PROXIMITY
    struct hwmsen_object obj_ps;
#endif

    ret = tpd_power_on(i2c);
    if (ret < 0)
    {
        GTP_ERROR("I2C communication ERROR!");
    }

    ret = gtp_read_version(i2c, &version_info);
    if (ret < 0)
    {
        GTP_ERROR("Read version failed.");
    }

    ret = gtp_init_panel(i2c);
    if (ret < 0)
    {
        GTP_ERROR("GTP init panel failed.");
    }


#if GTP_HAVE_TOUCH_KEY

    for (idx = 0; idx < GTP_MAX_KEY_NUM; idx++)
    {
        input_set_capability(tpd->dev, EV_KEY, touch_key_array[idx]);
    }

#endif
#if GTP_GESTURE_WAKEUP
//    input_set_capability(tpd->dev, EV_KEY, KEY_POWER);
#endif

#if GTP_WITH_PEN
    gtp_pen_init();
#endif

    // set INT mode
    gpio_direction_input(GTP_INT_PORT, GTP_INT_PIN);
    gpio_set_func(GTP_INT_PORT, GTP_INT_PIN, GPIO_INPUT | GPIO_INT_FE);
    gpio_set_irq_callback(GTP_INT_PORT, GTP_INT_PIN, tpd_int_srv, RT_NULL);
    rt_thread_delay(50);
    gpio_unmask_irq(GTP_INT_PORT, GTP_INT_PIN);

#if GTP_ESD_PROTECT
    gtp_esd_switch(client, SWITCH_ON);
#endif

#if GTP_AUTO_UPDATE
    ret = gup_init_update_proc(client);

    if (ret < 0)
    {
        GTP_ERROR("Create update thread error.");
    }
#endif

#ifdef TPD_PROXIMITY
    //obj_ps.self = cm3623_obj;
    obj_ps.polling = 0;         //0--interrupt mode;1--polling mode;
    obj_ps.sensor_operate = tpd_ps_operate;

    if ((err = hwmsen_attach(ID_PROXIMITY, &obj_ps)))
    {
        GTP_ERROR("hwmsen attach fail, return:%d.", err);
    }

#endif

    return 0;
}


/******************************************************************************/
// Description: rt_hw_touch_init
// Dependence:
// Note:   GPIO_PROD_TP_INT_ID
/******************************************************************************/
int rt_hw_touch_init(void)
{
    uint32_t reset_count;
    rt_thread_t tid;

    struct rt_i2c_bus_device *i2c_bus;

    i2c_bus = rt_i2c_bus_device_find("i2c0");
    if(i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find the i2c bus:%s\n","i2c0");
        return -RT_EIO;
    }

    gt9xx_mb = rt_mb_create("tp_mb",8,RT_IPC_FLAG_FIFO);
    tid = rt_thread_create("tp_serv",
                           tpd_event_process, i2c_bus,
                           4096,
                           RT_TOUCH_THREAD_PRIORITY,10);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    tpd_i2c_probe(i2c_bus);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_touch_init);

#endif