/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <bitmap.h>

#define DBG_TAG "nvmem.rockchip.otp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* OTP Register Offsets */
#define OTPC_SBPI_CTRL                  0x0020
#define OTPC_SBPI_CMD_VALID_PRE         0x0024
#define OTPC_SBPI_CS_VALID_PRE          0x0028
#define OTPC_SBPI_STATUS                0x002C
#define OTPC_USER_CTRL                  0x0100
#define OTPC_USER_ADDR                  0x0104
#define OTPC_USER_ENABLE                0x0108
#define OTPC_USER_QP                    0x0120
#define OTPC_USER_Q                     0x0124
#define OTPC_INT_STATUS                 0x0304
#define OTPC_SBPI_CMD0_OFFSET           0x1000
#define OTPC_SBPI_CMD1_OFFSET           0x1004

#define OTPC_MODE_CTRL                  0x2000
#define OTPC_IRQ_ST                     0x2008
#define OTPC_ACCESS_ADDR                0x200c
#define OTPC_RD_DATA                    0x2010
#define OTPC_REPR_RD_TRANS_NUM          0x2020

#define OTPC_DEEP_STANDBY               0x0
#define OTPC_STANDBY                    0x1
#define OTPC_ACTIVE                     0x2
#define OTPC_READ_ACCESS                0x3
#define OTPC_TRANS_NUM                  0x1
#define OTPC_RDM_IRQ_ST                 RT_BIT(0)
#define OTPC_STB2ACT_IRQ_ST             RT_BIT(7)
#define OTPC_DP2STB_IRQ_ST              RT_BIT(8)
#define OTPC_ACT2STB_IRQ_ST             RT_BIT(9)
#define OTPC_STB2DP_IRQ_ST              RT_BIT(10)
#define PX30S_NBYTES                    4
#define PX30S_NO_SECURE_OFFSET          224

/* OTP Register bits and masks */
#define OTPC_USER_ADDR_MASK             RT_GENMASK(31, 16)
#define OTPC_USE_USER                   RT_BIT(0)
#define OTPC_USE_USER_MASK              RT_GENMASK(16, 16)
#define OTPC_USER_FSM_ENABLE            RT_BIT(0)
#define OTPC_USER_FSM_ENABLE_MASK       RT_GENMASK(16, 16)
#define OTPC_LOCK                       RT_BIT(0)
#define OTPC_LOCK_MASK                  RT_GENMASK(16, 16)
#define OTPC_SBPI_DONE                  RT_BIT(1)
#define OTPC_USER_DONE                  RT_BIT(2)

#define SBPI_DAP_ADDR                   0x02
#define SBPI_DAP_ADDR_SHIFT             8
#define SBPI_DAP_ADDR_MASK              RT_GENMASK(31, 24)
#define SBPI_CMD_VALID_MASK             RT_GENMASK(31, 16)
#define SBPI_DAP_CMD_WRF                0xc0
#define SBPI_DAP_REG_ECC                0x3a
#define SBPI_ECC_ENABLE                 0x00
#define SBPI_ECC_DISABLE                0x09
#define SBPI_ENABLE                     RT_BIT(0)
#define SBPI_ENABLE_MASK                RT_GENMASK(16, 16)

#define OTPC_TIMEOUT                    10000
#define OTPC_TIMEOUT_PROG               100000
#define RK3568_NBYTES                   2

#define RK3576_NO_SECURE_OFFSET         0x1c0

#define RK3588_OTPC_AUTO_CTRL           0x04
#define RK3588_OTPC_AUTO_EN             0x08
#define RK3588_OTPC_INT_ST              0x84
#define RK3588_OTPC_DOUT0               0x20
#define RK3588_NO_SECURE_OFFSET         0x300
#define RK3588_NBYTES                   4
#define RK3588_BURST_NUM                1
#define RK3588_BURST_SHIFT              8
#define RK3588_ADDR_SHIFT               16
#define RK3588_AUTO_EN                  RT_BIT(0)
#define RK3588_RD_DONE                  RT_BIT(1)

#define RV1126_OTP_NVM_CEB              0x00
#define RV1126_OTP_NVM_RSTB             0x04
#define RV1126_OTP_NVM_ST               0x18
#define RV1126_OTP_NVM_RADDR            0x1c
#define RV1126_OTP_NVM_RSTART           0x20
#define RV1126_OTP_NVM_RDATA            0x24
#define RV1126_OTP_NVM_TRWH             0x28
#define RV1126_OTP_READ_ST              0x30
#define RV1126_OTP_NVM_PRADDR           0x34
#define RV1126_OTP_NVM_PRLEN            0x38
#define RV1126_OTP_NVM_PRDATA           0x3c
#define RV1126_OTP_NVM_FAILTIME         0x40
#define RV1126_OTP_NVM_PRSTART          0x44
#define RV1126_OTP_NVM_PRSTATE          0x48

/*
 * +----------+------------------+--------------------------+
 * | TYPE     | RANGE(byte)      | NOTE                     |
 * +----------+------------------+--------------------------+
 * | system   | 0x000 ~ 0x0ff    | system info, read only   |
 * +----------+------------------+--------------------------+
 * | oem      | 0x100 ~ 0x1ef    | for customized           |
 * +----------+------------------+--------------------------+
 * | reserved | 0x1f0 ~ 0x1f7    | future extension         |
 * +----------+------------------+--------------------------+
 * | wp       | 0x1f8 ~ 0x1ff    | write protection for oem |
 * +----------+------------------+--------------------------+
 *
 * +-----+    +------------------+
 * | wp  | -- | wp for oem range |
 * +-----+    +------------------+
 * | 1f8 |    | 0x100 ~ 0x11f    |
 * +-----+    +------------------+
 * | 1f9 |    | 0x120 ~ 0x13f    |
 * +-----+    +------------------+
 * | 1fa |    | 0x140 ~ 0x15f    |
 * +-----+    +------------------+
 * | 1fb |    | 0x160 ~ 0x17f    |
 * +-----+    +------------------+
 * | 1fc |    | 0x180 ~ 0x19f    |
 * +-----+    +------------------+
 * | 1fd |    | 0x1a0 ~ 0x1bf    |
 * +-----+    +------------------+
 * | 1fe |    | 0x1c0 ~ 0x1df    |
 * +-----+    +------------------+
 * | 1ff |    | 0x1e0 ~ 0x1ef    |
 * +-----+    +------------------+
 */
#define RV1126_OTP_OEM_OFFSET           0x100
#define RV1126_OTP_OEM_SIZE             0xf0
#define RV1126_OTP_WP_OFFSET            0x1f8
#define RV1126_OTP_WP_SIZE              0x8

/* each bit mask 32 bits in OTP NVM */
#define ROCKCHIP_OTP_WP_MASK_NBITS      64

#define OFFSET_IS_ALIGNED(x, a)         (((x) & ((typeof(x))(a) - 1)) == 0)

struct rockchip_otp;

struct rockchip_otp_data
{
    int size;
    int ns_offset;

    rt_ssize_t (*read)(struct rockchip_otp *, int offset, void *buf, rt_size_t bytes);
    rt_ssize_t (*write)(struct rockchip_otp *, int offset, void *buf, rt_size_t bytes);
    rt_err_t (*init)(struct rockchip_otp *);
};

struct rockchip_otp
{
    struct rt_nvmem_device parent;
    void *regs;

    rt_bool_t was_written;
    struct rt_clk_array *clk_arr;
    struct rt_reset_control *rstc;
    const struct rockchip_otp_data *soc_data;

    struct rt_mutex mutex;
    RT_BITMAP_DECLARE(wp_mask, ROCKCHIP_OTP_WP_MASK_NBITS);
};

#define raw_to_rockchip_otp(raw) rt_container_of(raw, struct rockchip_otp, parent)

#define readl_poll_timeout(ADDR, VAL, COND, DELAY_US, TIMEOUT_US) \
({                                                      \
    rt_uint64_t timeout_us = (TIMEOUT_US);              \
    rt_int64_t left_ns = timeout_us * 1000L;            \
    rt_ubase_t delay_us = (DELAY_US);                   \
    rt_uint64_t delay_ns = delay_us * 1000L;            \
    for (;;)                                            \
    {                                                   \
        (VAL) = HWREG32(ADDR);                          \
        if (COND)                                       \
        {                                               \
            break;                                      \
        }                                               \
        if (timeout_us && left_ns < 0)                  \
        {                                               \
            (VAL) = HWREG32(ADDR);                      \
            break;                                      \
        }                                               \
        if (delay_us)                                   \
        {                                               \
            rt_hw_us_delay(delay_us);                   \
            if (timeout_us)                             \
            {                                           \
                left_ns -= delay_ns;                    \
            }                                           \
        }                                               \
        rt_hw_cpu_relax();                              \
        if (timeout_us)                                 \
        {                                               \
            --left_ns;                                  \
        }                                               \
    }                                                   \
    (COND) ? RT_EOK : -RT_ETIMEOUT;                     \
})

static rt_err_t rockchip_otp_reset(struct rockchip_otp *rk_otp)
{
    rt_err_t err;

    if ((err = rt_reset_control_assert(rk_otp->rstc)))
    {
        LOG_E("Failed to assert otp phy error = %s", rt_strerror(err));
        return err;
    }

    rt_hw_us_delay(2);

    if ((err = rt_reset_control_deassert(rk_otp->rstc)))
    {
        LOG_E("Failed to deassert otp phy error = %s", rt_strerror(err));
        return err;
    }

    return RT_EOK;
}

static rt_err_t px30_otp_wait_status(struct rockchip_otp *rk_otp, rt_uint32_t flag)
{
    rt_err_t err;
    rt_uint32_t status = 0;

    err = readl_poll_timeout(rk_otp->regs + OTPC_INT_STATUS, status,
            (status & flag), 1, OTPC_TIMEOUT);

    if (err)
    {
        return err;
    }

    /* Clean int status */
    HWREG32(rk_otp->regs + OTPC_INT_STATUS) = flag;

    return RT_EOK;
}

static rt_err_t px30_otp_ecc_enable(struct rockchip_otp *rk_otp, rt_bool_t enable)
{
    rt_err_t err;

    HWREG32(rk_otp->regs + OTPC_SBPI_CTRL) = SBPI_DAP_ADDR_MASK |
            (SBPI_DAP_ADDR << SBPI_DAP_ADDR_SHIFT);
    HWREG32(rk_otp->regs + OTPC_SBPI_CMD_VALID_PRE) = SBPI_CMD_VALID_MASK | 0x1;
    HWREG32(rk_otp->regs + OTPC_SBPI_CMD0_OFFSET) =
            SBPI_DAP_CMD_WRF | SBPI_DAP_REG_ECC;

    HWREG32(rk_otp->regs + OTPC_SBPI_CMD1_OFFSET) =
            enable ? SBPI_ECC_ENABLE : SBPI_ECC_DISABLE;
    HWREG32(rk_otp->regs + OTPC_SBPI_CTRL) = SBPI_ENABLE_MASK | SBPI_ENABLE;

    if ((err = px30_otp_wait_status(rk_otp, OTPC_SBPI_DONE)) < 0)
    {
        LOG_E("Timeout during ecc_enable");
    }

    return err;
}

static rt_ssize_t px30_otp_read(struct rockchip_otp *rk_otp, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res;
    rt_uint8_t *buf = val;

    if ((res = rt_clk_array_prepare_enable(rk_otp->clk_arr)) < 0)
    {
        LOG_E("Failed to prepare/enable clks");

        return res;
    }

    if ((res = rockchip_otp_reset(rk_otp)))
    {
        LOG_E("Failed to reset otp phy");

        goto _disable_clks;
    }

    if ((res = px30_otp_ecc_enable(rk_otp, RT_FALSE)) < 0)
    {
        LOG_E("Enable ECC error = %s", rt_strerror(res));

        goto _disable_clks;
    }

    HWREG32(rk_otp->regs + OTPC_USER_CTRL) = OTPC_USE_USER | OTPC_USE_USER_MASK;
    rt_hw_us_delay(5);

    for (int i = 0; i < bytes; ++i)
    {
        HWREG32(rk_otp->regs + OTPC_USER_ADDR) = offset++ | OTPC_USER_ADDR_MASK;
        HWREG32(rk_otp->regs + OTPC_USER_ENABLE) =
                OTPC_USER_FSM_ENABLE | OTPC_USER_FSM_ENABLE_MASK;

        if ((res = px30_otp_wait_status(rk_otp, OTPC_USER_DONE)) < 0)
        {
            LOG_E("Timeout during read setup");

            goto _read_end;
        }

        *buf++ = HWREG8(rk_otp->regs + OTPC_USER_Q);
    }

_read_end:
    HWREG32(rk_otp->regs + OTPC_USER_CTRL) = 0x0 | OTPC_USE_USER_MASK;

_disable_clks:
    rt_clk_array_disable_unprepare(rk_otp->clk_arr);

    return bytes;
}

static rt_err_t px30s_otp_wait_status(struct rockchip_otp *rk_otp, rt_uint32_t flag)
{
    rt_err_t err;
    rt_uint32_t status = 0;

    err = readl_poll_timeout(rk_otp->regs + OTPC_IRQ_ST, status,
            (status & flag), 1, OTPC_TIMEOUT);

    if (err)
    {
        return err;
    }

    /* clean int status */
    HWREG32(rk_otp->regs + OTPC_IRQ_ST) = flag;

    return RT_EOK;
}

static rt_err_t px30s_otp_active(struct rockchip_otp *rk_otp)
{
    rt_uint32_t mode;
    rt_err_t err = RT_EOK;

    mode = HWREG32(rk_otp->regs + OTPC_MODE_CTRL);

    switch (mode)
    {
    case OTPC_DEEP_STANDBY:
        HWREG32(rk_otp->regs + OTPC_MODE_CTRL) = OTPC_STANDBY;

        if ((err = px30s_otp_wait_status(rk_otp, OTPC_DP2STB_IRQ_ST)) < 0)
        {
            LOG_E("Timeout during wait dp2stb");

            return err;
        }

    /* Fallthrough */
    case OTPC_STANDBY:
        HWREG32(rk_otp->regs + OTPC_MODE_CTRL) = OTPC_ACTIVE;

        if ((err = px30s_otp_wait_status(rk_otp, OTPC_STB2ACT_IRQ_ST)) < 0)
        {
            LOG_E("Timeout during wait stb2act");

            return err;
        }

        break;

    default:
        break;
    }

    return err;
}

static rt_err_t px30s_otp_standby(struct rockchip_otp *rk_otp)
{
    rt_uint32_t mode;
    rt_err_t err = RT_EOK;

    mode = HWREG32(rk_otp->regs + OTPC_MODE_CTRL);

    switch (mode)
    {
    case OTPC_ACTIVE:
        HWREG32(rk_otp->regs + OTPC_MODE_CTRL) = OTPC_STANDBY;

        if ((err = px30s_otp_wait_status(rk_otp, OTPC_ACT2STB_IRQ_ST)) < 0)
        {
            LOG_E("Timeout during wait act2stb");

            return err;
        }

    /* Fallthrough */
    case OTPC_STANDBY:
        HWREG32(rk_otp->regs + OTPC_MODE_CTRL) = OTPC_DEEP_STANDBY;

        if ((err = px30s_otp_wait_status(rk_otp, OTPC_STB2DP_IRQ_ST)) < 0)
        {
            LOG_E("Timeout during wait stb2dp");

            return err;
        }

        break;

    default:
        break;
    }

    return err;
}

static rt_ssize_t px30s_otp_read(struct rockchip_otp *rk_otp, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res;
    rt_uint8_t *buf;
    rt_uint32_t out_value;
    int addr_start, addr_end, addr_offset, addr_len;

    if (offset >= rk_otp->soc_data->size)
    {
        return -RT_ENOMEM;
    }

    if (offset + bytes > rk_otp->soc_data->size)
    {
        bytes = rk_otp->soc_data->size - offset;
    }

    if ((res = rt_clk_array_prepare_enable(rk_otp->clk_arr)) < 0)
    {
        LOG_E("Failed to prepare/enable clks");

        return res;
    }

    if ((res = rockchip_otp_reset(rk_otp)))
    {
        LOG_E("Failed to reset otp phy");

        goto _disable_clks;
    }

    if ((res = px30s_otp_active(rk_otp)))
    {
        goto _disable_clks;
    }

    addr_start = rt_rounddown(offset, PX30S_NBYTES) / PX30S_NBYTES;
    addr_end = rt_roundup(offset + bytes, PX30S_NBYTES) / PX30S_NBYTES;
    addr_offset = offset % PX30S_NBYTES;
    addr_len = addr_end - addr_start;
    addr_start += PX30S_NO_SECURE_OFFSET;

    buf = rt_calloc(PX30S_NBYTES, addr_len * sizeof(*buf));
    if (!buf)
    {
        res = -RT_ENOMEM;
        goto _read_end;
    }

    for (int i = 0; addr_len--; i += PX30S_NBYTES)
    {
        HWREG32(rk_otp->regs + OTPC_REPR_RD_TRANS_NUM) = OTPC_TRANS_NUM;
        HWREG32(rk_otp->regs + OTPC_ACCESS_ADDR) = addr_start++;
        HWREG32(rk_otp->regs + OTPC_MODE_CTRL) = OTPC_READ_ACCESS;

        if ((res = px30s_otp_wait_status(rk_otp, OTPC_RDM_IRQ_ST)) < 0)
        {
            LOG_E("timeout during wait rd");

            goto _read_end;
        }

        out_value = HWREG32(rk_otp->regs + OTPC_RD_DATA);
        rt_memcpy(&buf[i], &out_value, PX30S_NBYTES);
    }

    rt_memcpy(val, buf + addr_offset, (rt_uint32_t)bytes);
    res = bytes;

_read_end:
    rt_free(buf);
    px30s_otp_standby(rk_otp);

_disable_clks:
    rt_clk_array_disable_unprepare(rk_otp->clk_arr);

    return res;
}

static rt_ssize_t rk3568_otp_read(struct rockchip_otp *rk_otp, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res;
    rt_uint8_t *buf;
    rt_uint32_t otp_qp, out_value;
    int addr_start, addr_end, addr_offset, addr_len;

    addr_start = rt_rounddown(offset, RK3568_NBYTES) / RK3568_NBYTES;
    addr_end = rt_roundup(offset + bytes, RK3568_NBYTES) / RK3568_NBYTES;
    addr_offset = offset % RK3568_NBYTES;
    addr_len = addr_end - addr_start;

    buf = rt_calloc(RK3568_NBYTES, addr_len * sizeof(*buf));
    if (!buf)
    {
        return -RT_ENOMEM;
    }

    if ((res = rt_clk_array_prepare_enable(rk_otp->clk_arr)) < 0)
    {
        LOG_E("Failed to prepare/enable clks");
        goto _out_free;
    }

    if ((res = rockchip_otp_reset(rk_otp)))
    {
        LOG_E("failed to reset otp phy");

        goto _disable_clks;
    }

    if ((res = px30_otp_ecc_enable(rk_otp, RT_TRUE)) < 0)
    {
        LOG_E("Enable ECC error = %s", rt_strerror(res));

        goto _disable_clks;
    }

    HWREG32(rk_otp->regs + OTPC_USER_CTRL) = OTPC_USE_USER | OTPC_USE_USER_MASK;

    rt_hw_us_delay(5);

    for (int i = 0; addr_len--; i += RK3568_NBYTES)
    {
        HWREG32(rk_otp->regs + OTPC_USER_ADDR) =
                addr_start++ | OTPC_USER_ADDR_MASK;
        HWREG32(rk_otp->regs + OTPC_USER_ENABLE) =
                OTPC_USER_FSM_ENABLE | OTPC_USER_FSM_ENABLE_MASK;

        if ((res = px30_otp_wait_status(rk_otp, OTPC_USER_DONE)) < 0)
        {
            LOG_E("Timeout during read setup");

            goto _read_end;
        }

        otp_qp = HWREG32(rk_otp->regs + OTPC_USER_QP);

        if (((otp_qp & 0xc0) == 0xc0) || (otp_qp & 0x20))
        {
            res = -RT_EIO;
            LOG_E("ECC check error during read setup");

            goto _read_end;
        }

        out_value = HWREG32(rk_otp->regs + OTPC_USER_Q);
        rt_memcpy(&buf[i], &out_value, RK3568_NBYTES);
    }

    rt_memcpy(val, buf + addr_offset, bytes);
    res = bytes;

_read_end:
    HWREG32(rk_otp->regs + OTPC_USER_CTRL) = 0x0 | OTPC_USE_USER_MASK;

_disable_clks:

    rt_clk_array_disable_unprepare(rk_otp->clk_arr);
_out_free:
    rt_free(buf);

    return res;
}

static rt_err_t rk3588_otp_wait_status(struct rockchip_otp *rk_otp,
        rt_uint32_t flag)
{
    rt_err_t err;
    rt_uint32_t status = 0;

    err = readl_poll_timeout(rk_otp->regs + RK3588_OTPC_INT_ST, status,
            (status & flag), 1, OTPC_TIMEOUT);

    if (err)
    {
        return err;
    }

    /* clean int status */
    HWREG32(rk_otp->regs + RK3588_OTPC_INT_ST) = flag;

    return RT_EOK;
}

static rt_ssize_t rk3588_otp_read(struct rockchip_otp *rk_otp, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res = 0;
    rt_uint8_t *buf;
    rt_uint32_t out_value;
    int addr_start, addr_end, addr_offset, addr_len;

    if (offset >= rk_otp->soc_data->size)
    {
        return -RT_ENOMEM;
    }

    if (offset + bytes > rk_otp->soc_data->size)
    {
        bytes = rk_otp->soc_data->size - offset;
    }

    addr_start = rt_rounddown(offset, RK3588_NBYTES) / RK3588_NBYTES;
    addr_end = rt_roundup(offset + bytes, RK3588_NBYTES) / RK3588_NBYTES;
    addr_offset = offset % RK3588_NBYTES;
    addr_len = addr_end - addr_start;
    addr_start += rk_otp->soc_data->ns_offset;

    buf = rt_calloc(RK3588_NBYTES, addr_len * sizeof(*buf));
    if (!buf)
    {
        return -RT_ENOMEM;
    }

    if ((res = rt_clk_array_prepare_enable(rk_otp->clk_arr)) < 0)
    {
        LOG_E("Failed to prepare/enable clks");

        goto _out_free;
    }

    for (int i = 0; addr_len--; i += RK3588_NBYTES, ++addr_start)
    {
        HWREG32(rk_otp->regs + RK3588_OTPC_AUTO_CTRL) =
                (addr_start << RK3588_ADDR_SHIFT) |
                    (RK3588_BURST_NUM << RK3588_BURST_SHIFT);
        HWREG32(rk_otp->regs + RK3588_OTPC_AUTO_EN) = RK3588_AUTO_EN;

        if ((res = rk3588_otp_wait_status(rk_otp, RK3588_RD_DONE)) < 0)
        {
            LOG_E("Timeout during read setup");

            goto _read_end;
        }

        out_value = HWREG32(rk_otp->regs + RK3588_OTPC_DOUT0);
        rt_memcpy(&buf[i], &out_value, RK3588_NBYTES);
    }

   rt_memcpy(val, buf + addr_offset, bytes);
   res = bytes;

_read_end:
    rt_clk_array_disable_unprepare(rk_otp->clk_arr);

_out_free:
    rt_free(buf);

    return res;
}

static rt_err_t rv1126_otp_init(struct rockchip_otp *rk_otp)
{
    rt_err_t err;
    rt_uint32_t status = 0;

    HWREG32(rk_otp->regs + RV1126_OTP_NVM_CEB) = 0x0;
    err = readl_poll_timeout(rk_otp->regs + RV1126_OTP_NVM_ST, status,
            status & 0x1, 1, OTPC_TIMEOUT);

    if (err < 0)
    {
        LOG_E("Timeout during set ceb");

        return err;
    }

    HWREG32(rk_otp->regs + RV1126_OTP_NVM_RSTB) = 0x1;
    err = readl_poll_timeout(rk_otp->regs + RV1126_OTP_NVM_ST, status,
            status & 0x4, 1, OTPC_TIMEOUT);

    if (err < 0)
    {
        LOG_E("Timeout during set rstb");

        return err;
    }

    return RT_EOK;
}

static rt_ssize_t rv1126_otp_read(struct rockchip_otp *rk_otp, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res;
    rt_uint8_t *buf = val;
    rt_uint32_t status = 0;

    for (int i = 0; i < bytes; ++i)
    {
        HWREG32(rk_otp->regs + RV1126_OTP_NVM_RADDR) = offset++;
        HWREG32(rk_otp->regs + RV1126_OTP_NVM_RSTART) = 0x1;

        res = readl_poll_timeout(rk_otp->regs + RV1126_OTP_READ_ST,
                status, status == 0, 1, OTPC_TIMEOUT);

        if (res < 0)
        {
            LOG_E("Timeout during read setup");

            return res;
        }

        *buf++ = HWREG8(rk_otp->regs + RV1126_OTP_NVM_RDATA);
    }

    return bytes;
}

static rt_err_t rv1126_otp_prog(struct rockchip_otp *rk_otp,
        rt_uint32_t bit_offset, rt_uint32_t data, rt_uint32_t bit_len)
{
    rt_err_t err;
    rt_uint32_t status = 0;

    if (!data)
    {
        return RT_EOK;
    }

    HWREG32(rk_otp->regs + RV1126_OTP_NVM_PRADDR) = bit_offset;
    HWREG32(rk_otp->regs + RV1126_OTP_NVM_PRLEN) = bit_len - 1;
    HWREG32(rk_otp->regs + RV1126_OTP_NVM_PRDATA) = data;
    HWREG32(rk_otp->regs + RV1126_OTP_NVM_PRSTART) = 1;

    /* Wait max 100 ms */
    err = readl_poll_timeout(rk_otp->regs + RV1126_OTP_NVM_PRSTATE,
            status, status == 0, 1, OTPC_TIMEOUT_PROG);

    if (err)
    {
        LOG_E("Timeout during prog");
    }

    return err;
}

static rt_ssize_t rv1126_otp_write(struct rockchip_otp *rk_otp, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res;
    rt_uint8_t *buf = val, val_r, val_w;

    for (int i = 0; i < bytes; ++i)
    {
        if ((res = rv1126_otp_read(rk_otp, offset, &val_r, 1)))
        {
            return res;
        }

        val_w = *buf & (~val_r);

        if ((res = rv1126_otp_prog(rk_otp, offset * 8, val_w, 8)))
        {
            return res;
        }

        ++buf;
        ++offset;
    }

    return bytes;
}

static rt_ssize_t rv1126_otp_wp(struct rockchip_otp *rk_otp, int offset,
        rt_size_t bytes)
{
    int nbits = bytes / 4;
    rt_uint32_t bit_idx = (offset - RV1126_OTP_OEM_OFFSET) / 4;

    for (int i = 0; i < nbits; ++i)
    {
        rt_bitmap_set_bit(rk_otp->wp_mask, bit_idx + i);
    }

    return rv1126_otp_write(rk_otp, RV1126_OTP_WP_OFFSET, rk_otp->wp_mask,
            RV1126_OTP_WP_SIZE);
}

static rt_ssize_t rv1126_otp_oem_write(struct rockchip_otp *rk_otp, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res;

    if (offset < RV1126_OTP_OEM_OFFSET ||
        offset > (RV1126_OTP_OEM_OFFSET + RV1126_OTP_OEM_SIZE - 1) ||
        bytes > RV1126_OTP_OEM_SIZE ||
        (offset + bytes) > (RV1126_OTP_OEM_OFFSET + RV1126_OTP_OEM_SIZE))
    {
        return -RT_EINVAL;
    }

    if (!OFFSET_IS_ALIGNED(offset, 4) || !OFFSET_IS_ALIGNED(bytes, 4))
    {
        return -RT_EINVAL;
    }

    if (!(res = rv1126_otp_write(rk_otp, offset, val, bytes)))
    {
        res = rv1126_otp_wp(rk_otp, offset, bytes);
    }

    return res;
}

static rt_ssize_t rockchip_otp_read(struct rt_nvmem_device *ndev, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res = -RT_EINVAL;
    struct rockchip_otp *rk_otp = raw_to_rockchip_otp(ndev);

    rt_mutex_take(&rk_otp->mutex, RT_WAITING_FOREVER);

    if (rk_otp->soc_data && rk_otp->soc_data->read)
    {
        res = rk_otp->soc_data->read(rk_otp, offset, val, bytes);
    }

    rt_mutex_release(&rk_otp->mutex);

    return res;
}

static rt_ssize_t rockchip_otp_write(struct rt_nvmem_device *ndev, int offset,
        void *val, rt_size_t bytes)
{
    rt_ssize_t res = -RT_EINVAL;
    struct rockchip_otp *rk_otp = raw_to_rockchip_otp(ndev);

    rt_mutex_take(&rk_otp->mutex, RT_WAITING_FOREVER);

    if (!rk_otp->was_written && rk_otp->soc_data && rk_otp->soc_data->write)
    {
        res = rk_otp->soc_data->write(rk_otp, offset, val, bytes);
    }

    rt_mutex_release(&rk_otp->mutex);

    return res;
}

static const struct rockchip_otp_data px30_data =
{
    .size = 0x40,
    .read = px30_otp_read,
};

static const struct rockchip_otp_data px30s_data =
{
    .size = 0x80,
    .read = px30s_otp_read,
};

static const struct rockchip_otp_data rk3568_data =
{
    .size = 0x80,
    .read = rk3568_otp_read,
};

static const struct rockchip_otp_data rk3576_data =
{
    .size = 0x100,
    .ns_offset = RK3576_NO_SECURE_OFFSET,
    .read = rk3588_otp_read,
};

static const struct rockchip_otp_data rk3588_data =
{
    .size = 0x400,
    .ns_offset = RK3588_NO_SECURE_OFFSET,
    .read = rk3588_otp_read,
};

static const struct rockchip_otp_data rv1106_data =
{
    .size = 0x80,
    .read = rk3568_otp_read,
};

static const struct rockchip_otp_data rv1126_data =
{
    .size = 0x200,
    .init = rv1126_otp_init,
    .read = rv1126_otp_read,
    .write = rv1126_otp_oem_write,
};

static rt_err_t rockchip_otp_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_nvmem_device *nvmem;
    struct rt_device *dev = &pdev->parent;
    const struct rockchip_otp_data *soc_data = pdev->id->data;
    struct rockchip_otp *rk_otp = rt_calloc(1, sizeof(*rk_otp));

    if (!rk_otp)
    {
        return -RT_ENOMEM;
    }

    rk_otp->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_otp->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_otp->clk_arr = rt_clk_get_array(dev);

    if (rt_is_err(rk_otp->clk_arr))
    {
        err = rt_ptr_err(rk_otp->clk_arr);
        goto _fail;
    }

    rk_otp->rstc = rt_reset_control_get_array(dev);

    if (rt_is_err(rk_otp->rstc))
    {
        err = rt_ptr_err(rk_otp->rstc);
        goto _fail;
    }

    if (soc_data->init)
    {
        if ((err = soc_data->init(rk_otp)))
        {
            goto _fail;
        }
    }

    dev->user_data = rk_otp;

    rk_otp->soc_data = soc_data;
    nvmem = &rk_otp->parent;

    nvmem->parent.ofw_node = dev->ofw_node;
    nvmem->reg_read = rockchip_otp_read,
    nvmem->reg_write = rockchip_otp_write,
    nvmem->size = soc_data->size;
    nvmem->read_only = soc_data->write == RT_NULL;
    nvmem->stride = 1;
    nvmem->word_size = 1;

    if ((err = rt_nvmem_device_register(nvmem)))
    {
        goto _fail;
    }

    rt_mutex_init(&rk_otp->mutex, "rockchip-otp", RT_IPC_FLAG_PRIO);

    return RT_EOK;

_fail:
    if (rk_otp->regs)
    {
        rt_iounmap(rk_otp->regs);
    }

    if (!rt_is_err_or_null(rk_otp->clk_arr))
    {
        rt_clk_array_put(rk_otp->clk_arr);
    }

    rt_free(rk_otp);

    return err;
}

static rt_err_t rockchip_otp_remove(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rockchip_otp *rk_otp = pdev->parent.user_data;

    err = rt_nvmem_device_unregister(&rk_otp->parent);

    rt_iounmap(rk_otp->regs);
    rt_clk_array_put(rk_otp->clk_arr);

    rt_free(rk_otp);

    return err;
}

static const struct rt_ofw_node_id rockchip_otp_ofw_ids[] =
{
    { .compatible = "rockchip,px30-otp", .data = &px30_data, },
    { .compatible = "rockchip,px30s-otp", .data = &px30s_data, },
    { .compatible = "rockchip,rk3308-otp", .data = &px30_data, },
    { .compatible = "rockchip,rk3308bs-otp", .data = &px30s_data, },
    { .compatible = "rockchip,rk3568-otp", .data = &rk3568_data, },
    { .compatible = "rockchip,rk3576-otp", .data = &rk3576_data, },
    { .compatible = "rockchip,rk3588-otp", .data = &rk3588_data, },
    { .compatible = "rockchip,rv1106-otp", .data = &rv1106_data, },
    { .compatible = "rockchip,rv1126-otp", .data = &rv1126_data, },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_otp_driver =
{
    .name = "nvmem-rockchip-otp",
    .ids = rockchip_otp_ofw_ids,

    .probe = rockchip_otp_probe,
    .remove = rockchip_otp_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_otp_driver);
