/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-19     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/input.h>
#include <drivers/byteorder.h>

#define DBG_TAG "input.ts.goodix"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define GOODIX_MAX_HEIGHT            4096
#define GOODIX_MAX_WIDTH             4096
#define GOODIX_MAX_CONTACTS          10
#define GOODIX_CONTACT_SIZE          8
#define GOODIX_BUFFER_STATUS_READY   RT_BIT(7)
#define GOODIX_HAVE_KEY              RT_BIT(4)
#define GOODIX_BUFFER_STATUS_TIMEOUT 20
#define GOODIX_I2C_TEST_RETRIES      2
#define GOODIX_I2C_RETRY_DELAY_MS    20
#define GOODIX_POLL_INTERVAL_MS      8
#define GOODIX_CONFIG_WRITE_RETRIES  3
#define GOODIX_CONFIG_APPLY_DELAY_MS 20

#define GOODIX_CONFIG_MIN_LENGTH  186
#define GOODIX_CONFIG_911_LENGTH  186
#define GOODIX_CONFIG_GT9X_LENGTH 240

#define GOODIX_REG_ID               0x8140
#define GOODIX_READ_COOR_ADDR       0x814E
#define GOODIX_GT9X_REG_CONFIG_DATA 0x8047
#define GOODIX_GT1X_REG_CONFIG_DATA 0x8050

#define GOODIX_ID_MAX_LEN 4

#define RESOLUTION_LOC              1
#define MAX_CONTACTS_LOC            5
#define TRIGGER_LOC                 6
#define GOODIX_CONFIG_HEADER_LENGTH (TRIGGER_LOC + 1)

#define GOODIX_TP_SIZE_GT9112 9112

struct goodix_chip_info
{
    rt_uint16_t config_addr;
    rt_uint16_t config_len;
};

struct goodix_ts
{
    struct rt_input_device parent;

    struct rt_i2c_client *client;
    struct rt_regulator *supply;

    rt_base_t irq_pin;
    rt_base_t rst_pin;
    rt_uint8_t irq_mode;
    rt_uint8_t reset_assert_level;
    rt_uint8_t address_select_level;
    rt_uint8_t reset_release_level;
    rt_uint8_t int_sync_level;

    const struct goodix_chip_info *chip;
    rt_uint8_t max_touch_num;
    rt_uint8_t contact_size;
    rt_bool_t use_irq;
    rt_bool_t force_polling;
    rt_bool_t irq_sem_inited;
    rt_bool_t active_slots[GOODIX_MAX_CONTACTS];

    struct rt_thread *worker;
    struct rt_semaphore irq_sem;
    volatile rt_uint32_t irq_count;
    volatile rt_uint32_t handle_count;

    char id[GOODIX_ID_MAX_LEN + 1];
};

static const struct goodix_chip_info gt9x_chip = {
    .config_addr = GOODIX_GT9X_REG_CONFIG_DATA,
    .config_len = GOODIX_CONFIG_GT9X_LENGTH,
};

static const struct goodix_chip_info gt911_chip = {
    .config_addr = GOODIX_GT9X_REG_CONFIG_DATA,
    .config_len = GOODIX_CONFIG_911_LENGTH,
};

static const struct goodix_chip_info gt1x_chip = {
    .config_addr = GOODIX_GT1X_REG_CONFIG_DATA,
    .config_len = GOODIX_CONFIG_GT9X_LENGTH,
};

/* Radxa Display 8HD: CJ080258 GT911, 800x1280. */
static const rt_uint8_t goodix_gt9112_config[] = {
    0x62, 0x20, 0x03, 0x00, 0x05, 0x0A, 0x05, 0x00, 0x01, 0x08, 0x28, 0x05,
    0x50, 0x32, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x8C, 0x2A, 0x0E, 0x17, 0x15, 0x31, 0x0D, 0x00, 0x00,
    0x01, 0x9A, 0x04, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x64, 0x32,
    0x00, 0x00, 0x00, 0x0F, 0x36, 0x94, 0xC5, 0x02, 0x07, 0x00, 0x00, 0x04,
    0x9B, 0x11, 0x00, 0x7B, 0x16, 0x00, 0x64, 0x1C, 0x00, 0x4F, 0x25, 0x00,
    0x41, 0x2F, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x1A, 0x18, 0x16, 0x14, 0x12, 0x10, 0x0E,
    0x0C, 0x0A, 0x08, 0x06, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x22,
    0x21, 0x20, 0x1F, 0x1E, 0x1D, 0x1C, 0x18, 0x16, 0x14, 0x13, 0x12, 0x10,
    0x0F, 0x0C, 0x0A, 0x08, 0x06, 0x04, 0x02, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x72, 0x01
};

static const rt_uint8_t goodix_irq_modes[] = {
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_FALLING,
    PIN_IRQ_MODE_LOW_LEVEL,
    PIN_IRQ_MODE_HIGH_LEVEL,
};

static rt_uint16_t goodix_get_le16(const rt_uint8_t *p)
{
    rt_uint16_t val;

    rt_memcpy(&val, p, sizeof(val));

    return rt_le16_to_cpu(val);
}

static rt_ssize_t goodix_get_named_pin(struct rt_device *dev, const char *name,
                                       const char *alt_name, rt_uint8_t *out_mode)
{
    rt_ssize_t pin;

    pin = rt_pin_get_named_pin(dev, name, 0, out_mode, RT_NULL);

    if (pin == PIN_NONE && alt_name)
    {
        pin = rt_pin_get_named_pin(dev, alt_name, 0, out_mode, RT_NULL);
    }

    return pin;
}

static rt_err_t goodix_i2c_read(struct rt_i2c_client *client, rt_uint16_t reg,
                                rt_uint8_t *buf, rt_size_t len)
{
    rt_uint8_t addr[2] = { reg >> 8, reg & 0xff };
    struct rt_i2c_msg msgs[2];
    rt_ssize_t res;

    msgs[0].addr = client->client_addr;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = addr;
    msgs[0].len = 2;

    msgs[1].addr = client->client_addr;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = buf;
    msgs[1].len = len;

    res = rt_i2c_transfer(client->bus, msgs, 2);

    if (res < 0)
    {
        return res;
    }

    return res == 2 ? RT_EOK : -RT_EIO;
}

static rt_err_t goodix_i2c_write(struct rt_i2c_client *client, rt_uint16_t reg,
                                 const rt_uint8_t *buf, rt_size_t len)
{
    rt_uint8_t stack_buf[32];
    rt_uint8_t *tx;
    struct rt_i2c_msg msg;
    rt_ssize_t res;

    if (len + 2 > sizeof(stack_buf))
    {
        tx = rt_malloc(len + 2);

        if (!tx)
        {
            return -RT_ENOMEM;
        }
    }
    else
    {
        tx = stack_buf;
    }

    tx[0] = reg >> 8;
    tx[1] = reg & 0xff;
    rt_memcpy(&tx[2], buf, len);

    msg.addr = client->client_addr;
    msg.flags = RT_I2C_WR;
    msg.buf = tx;
    msg.len = len + 2;

    res = rt_i2c_transfer(client->bus, &msg, 1);

    if (tx != stack_buf)
    {
        rt_free(tx);
    }

    if (res < 0)
    {
        return res;
    }

    return res == 1 ? RT_EOK : -RT_EIO;
}

static rt_err_t goodix_i2c_write_u8(struct rt_i2c_client *client, rt_uint16_t reg,
                                    rt_uint8_t value)
{
    return goodix_i2c_write(client, reg, &value, 1);
}

static rt_err_t goodix_i2c_read_confirm(struct rt_i2c_client *client,
                                        rt_uint16_t reg, rt_uint8_t *buf, rt_size_t len)
{
    rt_uint8_t stack_buf[32];
    rt_uint8_t *confirm = stack_buf;
    rt_err_t err;

    if (len > sizeof(stack_buf))
    {
        confirm = rt_malloc(len);

        if (!confirm)
        {
            return -RT_ENOMEM;
        }
    }

    err = goodix_i2c_read(client, reg, buf, len);

    if (!err)
    {
        err = goodix_i2c_read(client, reg, confirm, len);

        if (!err && rt_memcmp(buf, confirm, len))
        {
            err = -RT_EIO;
        }
    }

    if (confirm != stack_buf)
    {
        rt_free(confirm);
    }

    return err;
}

static rt_err_t goodix_irq_direction_output(struct goodix_ts *ts, rt_uint8_t value)
{
    /* Preload the output latch so changing direction cannot glitch INT. */
    rt_pin_write(ts->irq_pin, value);
    rt_pin_mode(ts->irq_pin, PIN_MODE_OUTPUT);

    return RT_EOK;
}

static rt_err_t goodix_irq_direction_input(struct goodix_ts *ts)
{
    rt_pin_mode(ts->irq_pin, PIN_MODE_INPUT);

    return RT_EOK;
}

static rt_err_t goodix_int_sync(struct goodix_ts *ts)
{
    goodix_irq_direction_output(ts, 0);
    rt_thread_mdelay(50);
    ts->int_sync_level = rt_pin_read(ts->irq_pin);
    goodix_irq_direction_input(ts);

    return RT_EOK;
}

static rt_err_t goodix_reset(struct goodix_ts *ts)
{
    /* Preload the output latch so changing direction cannot pulse reset. */
    rt_pin_write(ts->rst_pin, 0);
    rt_pin_mode(ts->rst_pin, PIN_MODE_OUTPUT);
    rt_thread_mdelay(20);
    ts->reset_assert_level = rt_pin_read(ts->rst_pin);

    goodix_irq_direction_output(ts, ts->client->client_addr == 0x14);
    rt_thread_mdelay(2);
    ts->address_select_level = rt_pin_read(ts->irq_pin);

    rt_pin_write(ts->rst_pin, 1);
    rt_thread_mdelay(6);
    ts->reset_release_level = rt_pin_read(ts->rst_pin);
    rt_pin_mode(ts->rst_pin, PIN_MODE_INPUT);

    return goodix_int_sync(ts);
}

static void goodix_i2c_failure_diagnose(struct goodix_ts *ts, rt_err_t id_err)
{
    rt_uint16_t address = ts->client->client_addr;
    rt_uint8_t value;
    rt_err_t cfg_err, alt_err = -RT_ENOSYS;

    cfg_err = goodix_i2c_read(ts->client, GOODIX_GT9X_REG_CONFIG_DATA,
                              &value, 1);

    if (address != 0x5d)
    {
        ts->client->client_addr = 0x5d;
        alt_err = goodix_i2c_read(ts->client, GOODIX_REG_ID, &value, 1);
        ts->client->client_addr = address;
    }

    LOG_E("diagnostic: id@0x%02x=%s cfg@0x%02x=%s id@0x5d=%s "
          "seq(rst0/intsel/rst1/sync0)=%u/%u/%u/%u "
          "irq=%ld level=%ld reset=%ld level=%ld",
          address, rt_strerror(id_err), address, rt_strerror(cfg_err),
          rt_strerror(alt_err), (unsigned int)ts->reset_assert_level,
          (unsigned int)ts->address_select_level,
          (unsigned int)ts->reset_release_level,
          (unsigned int)ts->int_sync_level, (long)ts->irq_pin,
          (long)rt_pin_read(ts->irq_pin), (long)ts->rst_pin,
          (long)rt_pin_read(ts->rst_pin));
}

static rt_err_t goodix_i2c_test(struct rt_i2c_client *client)
{
    rt_uint8_t test;
    rt_err_t err = -RT_EIO;
    int retry = 0;

    while (retry++ < GOODIX_I2C_TEST_RETRIES)
    {
        err = goodix_i2c_read(client, GOODIX_REG_ID, &test, 1);

        if (!err)
        {
            return RT_EOK;
        }

        rt_thread_mdelay(GOODIX_I2C_RETRY_DELAY_MS);
    }

    return err;
}

static rt_bool_t goodix_product_id_valid(const rt_uint8_t *id)
{
    rt_size_t length = 0;
    int i;

    for (i = 0; i < GOODIX_ID_MAX_LEN && id[i]; i++)
    {
        if (!((id[i] >= '0' && id[i] <= '9') ||
              (id[i] >= 'A' && id[i] <= 'Z') ||
              (id[i] >= 'a' && id[i] <= 'z')))
        {
            return RT_FALSE;
        }

        length++;
    }

    return length >= 2;
}

static rt_err_t goodix_try_alternate_address(struct goodix_ts *ts)
{
    rt_uint16_t address = ts->client->client_addr;
    rt_uint16_t alternate;
    rt_uint8_t id[GOODIX_ID_MAX_LEN + 1] = { 0 };
    rt_err_t err;

    if (address == 0x14)
    {
        alternate = 0x5d;
    }
    else if (address == 0x5d)
    {
        alternate = 0x14;
    }
    else
    {
        return -RT_EINVAL;
    }

    /*
     * Select the alternate address deliberately. Merely probing it is not
     * enough because the address is sampled from INT while reset is released.
     */
    ts->client->client_addr = alternate;

    if (ts->rst_pin >= 0 && ts->irq_pin >= 0)
    {
        err = goodix_reset(ts);
    }
    else
    {
        err = RT_EOK;
    }

    if (!err)
    {
        err = goodix_i2c_read(ts->client, GOODIX_REG_ID, id,
                              GOODIX_ID_MAX_LEN);
    }

    if (!err && !goodix_product_id_valid(id))
    {
        err = -RT_EIO;
    }

    if (err)
    {
        ts->client->client_addr = address;

        return err;
    }

    LOG_D("device selected alternate I2C address 0x%02x (DT 0x%02x), ID %s",
          alternate, address, id);
    ts->force_polling = RT_TRUE;

    return RT_EOK;
}

static rt_err_t goodix_read_version(struct goodix_ts *ts)
{
    rt_uint8_t buf[6];
    rt_err_t err;

    err = goodix_i2c_read(ts->client, GOODIX_REG_ID, buf, sizeof(buf));

    if (err)
    {
        return err;
    }

    rt_memcpy(ts->id, buf, GOODIX_ID_MAX_LEN);
    ts->id[GOODIX_ID_MAX_LEN] = '\0';

    LOG_I("ID %s, version: %04x", ts->id, goodix_get_le16(&buf[4]));

    return RT_EOK;
}

static rt_bool_t goodix_config_is_valid(const rt_uint8_t *config, rt_size_t len)
{
    rt_uint32_t x_max, y_max;
    rt_uint8_t contacts;

    if (len <= TRIGGER_LOC)
    {
        return RT_FALSE;
    }

    x_max = goodix_get_le16(&config[RESOLUTION_LOC]);
    y_max = goodix_get_le16(&config[RESOLUTION_LOC + 2]);
    contacts = config[MAX_CONTACTS_LOC] & 0x0f;

    return x_max && x_max <= GOODIX_MAX_WIDTH &&
           y_max && y_max <= GOODIX_MAX_HEIGHT &&
           contacts && contacts <= GOODIX_MAX_CONTACTS;
}

static rt_err_t goodix_load_gt9112_config(struct goodix_ts *ts)
{
    rt_uint8_t config[sizeof(goodix_gt9112_config)];
    rt_uint8_t verify[GOODIX_CONFIG_HEADER_LENGTH] = {};
    rt_uint8_t checksum = 0;
    rt_uint32_t tp_size;
    rt_size_t i;
    rt_err_t err = -RT_EIO;
    int retry;

    if (rt_dm_dev_prop_read_u32(&ts->client->parent, "tp-size", &tp_size) ||
        tp_size != GOODIX_TP_SIZE_GT9112 ||
        rt_strncmp(ts->id, "911", 3))
    {
        return -RT_EINVAL;
    }

    rt_memcpy(config, goodix_gt9112_config, sizeof(config));

    /* A zero version forces GT9xx controllers to accept the new config. */
    config[0] = 0;

    for (i = 0; i < sizeof(config) - 2; ++i)
    {
        checksum += config[i];
    }

    config[sizeof(config) - 2] = (rt_uint8_t)(0U - checksum);
    config[sizeof(config) - 1] = 1;

    for (retry = 0; retry < GOODIX_CONFIG_WRITE_RETRIES; ++retry)
    {
        /*
         * Config_Fresh is the final byte of the packet. Keep the complete
         * configuration in one I2C message so the controller never observes
         * a partially updated table.
         */
        err = goodix_i2c_write(ts->client, GOODIX_GT9X_REG_CONFIG_DATA,
                               config, sizeof(config));

        if (err)
        {
            continue;
        }

        rt_thread_mdelay(GOODIX_CONFIG_APPLY_DELAY_MS);
        err = goodix_i2c_read_confirm(ts->client, GOODIX_GT9X_REG_CONFIG_DATA,
                                      verify, sizeof(verify));

        if (!err &&
            !rt_memcmp(&verify[RESOLUTION_LOC], &config[RESOLUTION_LOC],
                       GOODIX_CONFIG_HEADER_LENGTH - RESOLUTION_LOC))
        {
            LOG_D("loaded GT9112 800x1280 configuration");
            return RT_EOK;
        }

        err = -RT_EIO;
        rt_thread_mdelay(GOODIX_I2C_RETRY_DELAY_MS);
    }

    LOG_E("GT9112 configuration write did not verify: "
          "%02x %02x %02x %02x %02x %02x %02x",
          verify[0], verify[1], verify[2], verify[3],
          verify[4], verify[5], verify[6]);

    return err;
}

static rt_err_t goodix_read_config(struct goodix_ts *ts)
{
    rt_uint8_t config[GOODIX_CONFIG_HEADER_LENGTH];
    rt_uint32_t x_max, y_max;
    rt_err_t err;

    err = goodix_i2c_read(ts->client, ts->chip->config_addr,
                          config, sizeof(config));

    if (err)
    {
        ts->max_touch_num = GOODIX_MAX_CONTACTS;
        return err;
    }

    if (!goodix_config_is_valid(config, sizeof(config)))
    {
        if ((err = goodix_load_gt9112_config(ts)))
        {
            return err;
        }

        err = goodix_i2c_read(ts->client, ts->chip->config_addr,
                              config, sizeof(config));

        if (err)
        {
            return err;
        }

        if (!goodix_config_is_valid(config, sizeof(config)))
        {
            return -RT_EIO;
        }
    }

    ts->max_touch_num = config[MAX_CONTACTS_LOC] & 0x0f;
    ts->irq_mode = goodix_irq_modes[config[TRIGGER_LOC] & 0x03];

    if (!ts->max_touch_num)
    {
        ts->max_touch_num = GOODIX_MAX_CONTACTS;
    }

    x_max = goodix_get_le16(&config[RESOLUTION_LOC]);
    y_max = goodix_get_le16(&config[RESOLUTION_LOC + 2]);

    if (x_max && y_max)
    {
        rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_X, 0, x_max - 1, 0, 0);
        rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_Y, 0, y_max - 1, 0, 0);
    }

    return RT_EOK;
}

static void goodix_parse_panel_size(struct goodix_ts *ts, struct rt_device *dev)
{
    rt_uint32_t max_x = 0, max_y = 0;

    if (!rt_dm_dev_prop_read_u32(dev, "max-x", &max_x) && max_x)
    {
        rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_X, 0, max_x - 1, 0, 0);
    }

    if (!rt_dm_dev_prop_read_u32(dev, "max-y", &max_y) && max_y)
    {
        rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_Y, 0, max_y - 1, 0, 0);
    }
}

static rt_err_t goodix_ts_read_input_report(struct goodix_ts *ts, rt_uint8_t *data,
                                            int *touch_num_out)
{
    rt_uint16_t addr = GOODIX_READ_COOR_ADDR;
    rt_size_t header_size = 1 + ts->contact_size;
    rt_tick_t timeout;
    rt_uint8_t touch_num;
    rt_err_t err;

    timeout = rt_tick_get() + rt_tick_from_millisecond(GOODIX_BUFFER_STATUS_TIMEOUT);

    do
    {
        err = goodix_i2c_read(ts->client, addr, data, header_size);

        if (err)
        {
            return err;
        }

        if (data[0] & GOODIX_BUFFER_STATUS_READY)
        {
            touch_num = data[0] & 0x0f;

            if (touch_num > ts->max_touch_num)
            {
                return -RT_EINVAL;
            }

            if (touch_num > 1)
            {
                addr += header_size;
                data += header_size;

                err = goodix_i2c_read(ts->client, addr, data,
                                      ts->contact_size * (touch_num - 1));

                if (err)
                {
                    return err;
                }
            }

            *touch_num_out = touch_num;
            return RT_EOK;
        }

        if (!ts->use_irq)
        {
            break;
        }

        rt_thread_mdelay(1);
    } while (rt_tick_get() < timeout);

    return -RT_ETIMEOUT;
}

static void goodix_release_unused_slots(struct goodix_ts *ts,
                                        const rt_bool_t *seen_slots)
{
    struct rt_input_device *idev = &ts->parent;
    int i;

    for (i = 0; i < GOODIX_MAX_CONTACTS; ++i)
    {
        if (ts->active_slots[i] && !seen_slots[i])
        {
            rt_input_report_touch_slot(idev, i);
            rt_input_event(idev, EV_ABS, ABS_MT_TRACKING_ID, -1);
            ts->active_slots[i] = RT_FALSE;
        }
    }
}

static void goodix_report_touch(struct goodix_ts *ts, rt_uint8_t *coor_data)
{
    struct rt_input_device *idev = &ts->parent;
    rt_uint32_t id = coor_data[0] & 0x0f;
    rt_uint32_t x = goodix_get_le16(&coor_data[1]);
    rt_uint32_t y = goodix_get_le16(&coor_data[3]);
    rt_uint32_t w = goodix_get_le16(&coor_data[5]);

    if (id >= GOODIX_MAX_CONTACTS)
    {
        return;
    }

    rt_input_report_touch_slot(idev, id);
    rt_input_event(idev, EV_ABS, ABS_MT_TRACKING_ID, id);
    ts->active_slots[id] = RT_TRUE;
    rt_input_report_touch_position(idev, x, y, RT_TRUE);
    rt_input_report_abs(idev, ABS_MT_TOUCH_MAJOR, w);
    rt_input_report_abs(idev, ABS_MT_WIDTH_MAJOR, w);
}

static rt_err_t goodix_process_events(struct goodix_ts *ts)
{
    rt_uint8_t point_data[2 + GOODIX_MAX_CONTACTS * GOODIX_CONTACT_SIZE];
    rt_bool_t seen_slots[GOODIX_MAX_CONTACTS] = { RT_FALSE };
    rt_uint8_t *coor_data;
    rt_uint32_t id;
    int touch_num = 0;
    int i;
    rt_err_t err;

    err = goodix_ts_read_input_report(ts, point_data, &touch_num);

    if (err)
    {
        return err;
    }

    for (i = 0; i < touch_num; ++i)
    {
        coor_data = &point_data[1 + ts->contact_size * i];
        id = coor_data[0] & 0x0f;

        if (id < GOODIX_MAX_CONTACTS)
        {
            seen_slots[id] = RT_TRUE;
            goodix_report_touch(ts, coor_data);
        }
    }

    goodix_release_unused_slots(ts, seen_slots);
    rt_input_sync(&ts->parent);

    return RT_EOK;
}

static void goodix_handle_events(struct goodix_ts *ts)
{
    rt_err_t err;

    err = goodix_process_events(ts);

    if (err)
    {
        return;
    }

    ++ts->handle_count;
    err = goodix_i2c_write_u8(ts->client, GOODIX_READ_COOR_ADDR, 0);

    if (err)
    {
        LOG_D("failed to clear coordinate status: %s", rt_strerror(err));
    }
}

static void goodix_worker_entry(void *param)
{
    struct goodix_ts *ts = param;

    while (RT_TRUE)
    {
        rt_sem_take(&ts->irq_sem, RT_WAITING_FOREVER);

        goodix_handle_events(ts);
    }
}

static void goodix_irq_callback(void *param)
{
    struct goodix_ts *ts = param;

    ++ts->irq_count;
    rt_sem_release(&ts->irq_sem);
}

static void goodix_poll(struct rt_input_device *idev)
{
    struct goodix_ts *ts = rt_container_of(idev, struct goodix_ts, parent);

    goodix_handle_events(ts);
}

static rt_err_t goodix_setup_polling(struct goodix_ts *ts)
{
    rt_err_t err;

    err = rt_input_setup_polling(&ts->parent, goodix_poll);

    if (err)
    {
        return err;
    }

    err = rt_input_set_poll_interval(&ts->parent, GOODIX_POLL_INTERVAL_MS);

    if (!err)
    {
        LOG_D("poll interval set to %d ms", GOODIX_POLL_INTERVAL_MS);
    }

    return err;
}

static rt_err_t goodix_request_irq(struct goodix_ts *ts)
{
    rt_err_t err;

    if (ts->irq_pin < 0 || ts->irq_pin == PIN_NONE)
    {
        return -RT_ENOSYS;
    }

    /*
     * An old ready flag keeps INT asserted and prevents a new edge from
     * arriving after the GPIO interrupt is enabled.
     */
    err = goodix_i2c_write_u8(ts->client, GOODIX_READ_COOR_ADDR, 0);

    if (err)
    {
        return err;
    }

    err = rt_pin_attach_irq(ts->irq_pin, ts->irq_mode, goodix_irq_callback, ts);

    if (err)
    {
        return err;
    }

    err = rt_pin_irq_enable(ts->irq_pin, RT_TRUE);

    if (err)
    {
        rt_pin_detach_irq(ts->irq_pin);
        return err;
    }

    return RT_EOK;
}

static rt_err_t goodix_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    struct rt_device *dev = &client->parent;
    struct rt_touch_info touch_info = {};
    struct goodix_ts *ts = rt_calloc(1, sizeof(*ts));

    if (!ts)
    {
        return -RT_ENOMEM;
    }

    ts->client = client;
    ts->contact_size = GOODIX_CONTACT_SIZE;
    ts->irq_mode = PIN_IRQ_MODE_FALLING;
    ts->chip = rt_i2c_client_id_data(client);

    if (!ts->chip)
    {
        ts->chip = &gt9x_chip;
    }

    ts->parent.parent.ofw_node = dev->ofw_node;
    dev->user_data = ts;

    ts->irq_pin = goodix_get_named_pin(dev, "irq", "touch", RT_NULL);
    ts->rst_pin = goodix_get_named_pin(dev, "reset", RT_NULL, RT_NULL);

    if (ts->irq_pin < 0 && ts->irq_pin != PIN_NONE)
    {
        err = ts->irq_pin;
        goto _free;
    }

    if (ts->rst_pin < 0 && ts->rst_pin != PIN_NONE)
    {
        err = ts->rst_pin;
        goto _free;
    }

    ts->supply = rt_regulator_get(dev, "tp");

    if (rt_is_err(ts->supply))
    {
        err = rt_ptr_err(ts->supply);
        ts->supply = RT_NULL;
        goto _free;
    }

    if (!ts->supply && rt_dm_dev_prop_read_bool(dev, "tp-supply"))
    {
        LOG_E("tp-supply is present but its regulator is unavailable");
        err = -RT_EIO;
        goto _free;
    }

    if (ts->supply)
    {
        err = rt_regulator_enable(ts->supply);

        if (err)
        {
            goto _put_supply;
        }

        rt_thread_mdelay(20);
    }
    else
    {
        ts->supply = RT_NULL;
    }

    if (ts->rst_pin >= 0 && ts->irq_pin >= 0)
    {
        if ((err = goodix_reset(ts)))
        {
            goto _disable_supply;
        }
    }
    else if (ts->rst_pin >= 0)
    {
        LOG_W("reset GPIO present without IRQ GPIO, skip hardware reset");
    }

    if ((err = goodix_i2c_test(client)))
    {
        if (ts->rst_pin >= 0 && ts->irq_pin >= 0)
        {
            LOG_D("initial I2C test failed: %s, retry after reset",
                  rt_strerror(err));

            if (!(err = goodix_reset(ts)))
            {
                err = goodix_i2c_test(client);
            }
        }
    }

    if (err && !goodix_try_alternate_address(ts))
    {
        err = RT_EOK;
    }

    if (err)
    {
        goodix_i2c_failure_diagnose(ts, err);
        LOG_E("I2C communication failed at 0x%02x: %s (irq=%ld reset=%ld)",
              client->client_addr, rt_strerror(err),
              (long)ts->irq_pin, (long)ts->rst_pin);
        goto _disable_supply;
    }

    if ((err = goodix_read_version(ts)))
    {
        LOG_E("failed to read controller version: %s", rt_strerror(err));
        goto _disable_supply;
    }

    err = rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_SLOT);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_TRACKING_ID);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_POSITION_X);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_POSITION_Y);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_TOUCH_MAJOR);
    err |= rt_input_set_capability(&ts->parent, EV_ABS, ABS_MT_WIDTH_MAJOR);

    if (err)
    {
        goto _disable_supply;
    }

    rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_X, 0, GOODIX_MAX_WIDTH - 1, 0, 0);
    rt_input_set_absinfo(&ts->parent, ABS_MT_POSITION_Y, 0, GOODIX_MAX_HEIGHT - 1, 0, 0);
    rt_input_set_absinfo(&ts->parent, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
    rt_input_set_absinfo(&ts->parent, ABS_MT_WIDTH_MAJOR, 0, 255, 0, 0);

    goodix_parse_panel_size(ts, dev);

    touch_info.type = RT_TOUCH_TYPE_CAPACITANCE;
    touch_info.vendor = RT_TOUCH_VENDOR_GT;
    touch_info.point_num = GOODIX_MAX_CONTACTS;

    if ((err = rt_input_setup_touch(&ts->parent, GOODIX_MAX_CONTACTS, &touch_info)))
    {
        goto _remove_input;
    }

    if ((err = goodix_read_config(ts)))
    {
        LOG_W("failed to read configuration: %s, use falling-edge IRQ",
              rt_strerror(err));
        ts->irq_mode = PIN_IRQ_MODE_FALLING;
    }

    err = rt_sem_init(&ts->irq_sem, "goodix", 0, RT_IPC_FLAG_FIFO);

    if (err)
    {
        goto _remove_input;
    }
    ts->irq_sem_inited = RT_TRUE;

    if (ts->force_polling)
    {
        LOG_W("INT address selection failed, using %d ms polling at 0x%02x",
              GOODIX_POLL_INTERVAL_MS, ts->client->client_addr);
        err = -RT_ENOSYS;
    }
    else
    {
        err = goodix_request_irq(ts);
    }

    if (err)
    {
        if (!ts->force_polling)
        {
            LOG_W("IRQ setup failed on pin %ld: %s, using polling mode",
                  (long)ts->irq_pin, rt_strerror(err));
        }

        rt_sem_detach(&ts->irq_sem);
        ts->irq_sem_inited = RT_FALSE;

        if ((err = goodix_setup_polling(ts)))
        {
            goto _remove_input;
        }

        ts->use_irq = RT_FALSE;
    }
    else
    {
        ts->use_irq = RT_TRUE;

        ts->worker = rt_thread_create(rt_dm_dev_get_name(dev), goodix_worker_entry,
                                      ts, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

        if (!ts->worker)
        {
            rt_pin_irq_enable(ts->irq_pin, RT_FALSE);
            rt_pin_detach_irq(ts->irq_pin);
            rt_sem_detach(&ts->irq_sem);
            ts->irq_sem_inited = RT_FALSE;
            ts->use_irq = RT_FALSE;

            if ((err = goodix_setup_polling(ts)))
            {
                goto _remove_input;
            }
        }
    }

    if ((err = rt_input_device_register(&ts->parent)))
    {
        goto _remove_input;
    }

    if (ts->worker)
    {
        rt_thread_startup(ts->worker);
    }

    return RT_EOK;

_remove_input:
    if (ts->use_irq && ts->irq_pin >= 0)
    {
        rt_pin_irq_enable(ts->irq_pin, RT_FALSE);
        rt_pin_detach_irq(ts->irq_pin);
    }

    if (ts->worker)
    {
        rt_thread_delete(ts->worker);
        ts->worker = RT_NULL;
    }

    if (ts->irq_sem_inited)
    {
        rt_sem_detach(&ts->irq_sem);
        ts->irq_sem_inited = RT_FALSE;
    }

    rt_input_remove_config(&ts->parent);

_disable_supply:
    if (ts->supply)
    {
        rt_regulator_disable(ts->supply);
    }

_put_supply:
    if (ts->supply)
    {
        rt_regulator_put(ts->supply);
    }

_free:
    if (dev->user_data == ts)
    {
        dev->user_data = RT_NULL;
    }

    rt_free(ts);

    return err;
}

static rt_err_t goodix_remove(struct rt_i2c_client *client)
{
    struct goodix_ts *ts = client->parent.user_data;

    if (!ts)
    {
        return RT_EOK;
    }

    client->parent.user_data = RT_NULL;

    if (ts->use_irq && ts->irq_pin >= 0)
    {
        rt_pin_irq_enable(ts->irq_pin, RT_FALSE);
        rt_pin_detach_irq(ts->irq_pin);
    }

    if (ts->worker)
    {
        rt_thread_delete(ts->worker);
    }

    if (ts->irq_sem_inited)
    {
        rt_sem_detach(&ts->irq_sem);
    }

    rt_input_device_unregister(&ts->parent);

    if (ts->supply)
    {
        rt_regulator_disable(ts->supply);
        rt_regulator_put(ts->supply);
    }

    rt_free(ts);

    return RT_EOK;
}

static const struct rt_i2c_device_id goodix_ts_ids[] = {
    { .name = "gt9xx" },
    { .name = "gt911" },
    { .name = "gt967" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id goodix_ts_ofw_ids[] = {
    { .compatible = "goodix,gt9xx", .data = (void *)&gt9x_chip },
    { .compatible = "goodix,gt911", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt9110", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt927", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt9271", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt928", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt912", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt9147", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt967", .data = (void *)&gt911_chip },
    { .compatible = "goodix,gt917s", .data = (void *)&gt1x_chip },
    { .compatible = "goodix,gt9286", .data = (void *)&gt1x_chip },
    { /* sentinel */ },
};

static struct rt_i2c_driver goodix_ts_driver = {
    .ids = goodix_ts_ids,
    .ofw_ids = goodix_ts_ofw_ids,

    .probe = goodix_probe,
    .remove = goodix_remove,
};
RT_I2C_DRIVER_EXPORT(goodix_ts_driver);
