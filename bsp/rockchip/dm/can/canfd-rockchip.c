/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "can_dm.h"

#define DBG_TAG "canfd.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define CAN_MODE            0x00
#define CAN_CMD             0x04
#define CAN_STATE           0x08
#define CAN_INT             0x0c
#define CAN_INT_MASK        0x10
#define CAN_LOSTARB_CODE    0x28
#define CAN_ERR_CODE        0x2c
#define CAN_RX_ERR_CNT      0x34
#define CAN_TX_ERR_CNT      0x38
#define CAN_IDCODE          0x3c
#define CAN_IDMASK          0x40
#define CAN_TX_CHECK_FIC    0x50
#define CAN_NBTP            0x100
#define CAN_DBTP            0x104
#define CAN_TDCR            0x108
#define CAN_TSCC            0x10c
#define CAN_TSCV            0x110
#define CAN_TXEFC           0x114
#define CAN_RXFC            0x118
#define CAN_AFC             0x11c
#define CAN_IDCODE0         0x120
#define CAN_IDMASK0         0x124
#define CAN_IDCODE1         0x128
#define CAN_IDMASK1         0x12c
#define CAN_IDCODE2         0x130
#define CAN_IDMASK2         0x134
#define CAN_IDCODE3         0x138
#define CAN_IDMASK3         0x13c
#define CAN_IDCODE4         0x140
#define CAN_IDMASK4         0x144
#define CAN_TXFIC           0x200
#define CAN_TXID            0x204
#define CAN_TXDAT0          0x208
#define CAN_TXDAT1          0x20c
#define CAN_TXDAT2          0x210
#define CAN_TXDAT3          0x214
#define CAN_TXDAT4          0x218
#define CAN_TXDAT5          0x21c
#define CAN_TXDAT6          0x220
#define CAN_TXDAT7          0x224
#define CAN_TXDAT8          0x228
#define CAN_TXDAT9          0x22c
#define CAN_TXDAT10         0x230
#define CAN_TXDAT11         0x234
#define CAN_TXDAT12         0x238
#define CAN_TXDAT13         0x23c
#define CAN_TXDAT14         0x240
#define CAN_TXDAT15         0x244
#define CAN_RXFIC           0x300
#define CAN_RXID            0x304
#define CAN_RXTS            0x308
#define CAN_RXDAT0          0x30c
#define CAN_RXDAT1          0x310
#define CAN_RXDAT2          0x314
#define CAN_RXDAT3          0x318
#define CAN_RXDAT4          0x31c
#define CAN_RXDAT5          0x320
#define CAN_RXDAT6          0x324
#define CAN_RXDAT7          0x328
#define CAN_RXDAT8          0x32c
#define CAN_RXDAT9          0x330
#define CAN_RXDAT10         0x334
#define CAN_RXDAT11         0x338
#define CAN_RXDAT12         0x33c
#define CAN_RXDAT13         0x340
#define CAN_RXDAT14         0x344
#define CAN_RXDAT15         0x348
#define CAN_RXFRD           0x400
#define CAN_TXEFRD          0x500

enum
{
    ROCKCHIP_CANFD_MODE = 0,
    ROCKCHIP_CAN_MODE,
    ROCKCHIP_RK3568_CAN_MODE,
    ROCKCHIP_RK3568_CAN_MODE_V2,
};

#define DATE_LENGTH_12_BYTE     0x9
#define DATE_LENGTH_16_BYTE     0xa
#define DATE_LENGTH_20_BYTE     0xb
#define DATE_LENGTH_24_BYTE     0xc
#define DATE_LENGTH_32_BYTE     0xd
#define DATE_LENGTH_48_BYTE     0xe
#define DATE_LENGTH_64_BYTE     0xf

#define CAN_TX0_REQ             RT_BIT(0)
#define CAN_TX1_REQ             RT_BIT(1)
#define CAN_TX_REQ_FULL         ((CAN_TX0_REQ) | (CAN_TX1_REQ))

#define MODE_FDOE               RT_BIT(15)
#define MODE_BRSD               RT_BIT(13)
#define MODE_SPACE_RX           RT_BIT(12)
#define MODE_AUTO_RETX          RT_BIT(10)
#define MODE_RXSORT             RT_BIT(7)
#define MODE_TXORDER            RT_BIT(6)
#define MODE_RXSTX              RT_BIT(5)
#define MODE_LBACK              RT_BIT(4)
#define MODE_SILENT             RT_BIT(3)
#define MODE_SELF_TEST          RT_BIT(2)
#define MODE_SLEEP              RT_BIT(1)
#define RESET_MODE              0
#define WORK_MODE               RT_BIT(0)

#define RX_FINISH_INT           RT_BIT(0)
#define TX_FINISH_INT           RT_BIT(1)
#define ERR_WARN_INT            RT_BIT(2)
#define RX_BUF_OV_INT           RT_BIT(3)
#define PASSIVE_ERR_INT         RT_BIT(4)
#define TX_LOSTARB_INT          RT_BIT(5)
#define BUS_ERR_INT             RT_BIT(6)
#define RX_FIFO_FULL_INT        RT_BIT(7)
#define RX_FIFO_OV_INT          RT_BIT(8)
#define BUS_OFF_INT             RT_BIT(9)
#define BUS_OFF_RECOVERY_INT    RT_BIT(10)
#define TSC_OV_INT              RT_BIT(11)
#define TXE_FIFO_OV_INT         RT_BIT(12)
#define TXE_FIFO_FULL_INT       RT_BIT(13)
#define WAKEUP_INT              RT_BIT(14)

#define ERR_TYPE_MASK           RT_GENMASK(28, 26)
#define ERR_TYPE_SHIFT          26
#define BIT_ERR                 0
#define STUFF_ERR               1
#define FORM_ERR                2
#define ACK_ERR                 3
#define CRC_ERR                 4
#define ERR_DIR_RX              RT_BIT(25)
#define ERR_LOC_MASK            RT_GENMASK(15, 0)

/* Nominal Bit Timing & Prescaler Register (NBTP) */
#define NBTP_MODE_3_SAMPLES     RT_BIT(31)
#define NBTP_NSJW_SHIFT         24
#define NBTP_NSJW_MASK          (0x7f << NBTP_NSJW_SHIFT)
#define NBTP_NBRP_SHIFT         16
#define NBTP_NBRP_MASK          (0xff << NBTP_NBRP_SHIFT)
#define NBTP_NTSEG2_SHIFT       8
#define NBTP_NTSEG2_MASK        (0x7f << NBTP_NTSEG2_SHIFT)
#define NBTP_NTSEG1_SHIFT       0
#define NBTP_NTSEG1_MASK        (0x7f << NBTP_NTSEG1_SHIFT)

/* Data Bit Timing & Prescaler Register (DBTP) */
#define DBTP_MODE_3_SAMPLES     RT_BIT(21)
#define DBTP_DSJW_SHIFT         17
#define DBTP_DSJW_MASK          (0xf << DBTP_DSJW_SHIFT)
#define DBTP_DBRP_SHIFT         9
#define DBTP_DBRP_MASK          (0xff << DBTP_DBRP_SHIFT)
#define DBTP_DTSEG2_SHIFT       5
#define DBTP_DTSEG2_MASK        (0xf << DBTP_DTSEG2_SHIFT)
#define DBTP_DTSEG1_SHIFT       0
#define DBTP_DTSEG1_MASK        (0x1f << DBTP_DTSEG1_SHIFT)

/* Transmitter Delay Compensation Register (TDCR) */
#define TDCR_TDCO_SHIFT         1
#define TDCR_TDCO_MASK          (0x3f << TDCR_TDCO_SHIFT)
#define TDCR_TDC_ENABLE         RT_BIT(0)

#define TX_FD_ENABLE            RT_BIT(5)
#define TX_FD_BRS_ENABLE        RT_BIT(4)

#define FIFO_ENABLE             RT_BIT(0)
#define RX_FIFO_CNT0_SHIFT      4
#define RX_FIFO_CNT0_MASK       (0x7 << RX_FIFO_CNT0_SHIFT)
#define RX_FIFO_CNT1_SHIFT      5
#define RX_FIFO_CNT1_MASK       (0x7 << RX_FIFO_CNT1_SHIFT)
#define RX_FIFO_COUNT_MAX       (RT_GENMASK(7, 5) >> RX_FIFO_CNT1_SHIFT)
#define RX_FIFO_ERR_IDX         RX_FIFO_COUNT_MAX

#define FORMAT_SHIFT            7
#define FORMAT_MASK             (0x1 << FORMAT_SHIFT)
#define RTR_SHIFT               6
#define RTR_MASK                (0x1 << RTR_SHIFT)
#define FDF_SHIFT               5
#define FDF_MASK                (0x1 << FDF_SHIFT)
#define BRS_SHIFT               4
#define BRS_MASK                (0x1 << BRS_SHIFT)
#define TDC_SHIFT               1
#define TDC_MASK                (0x3f << TDC_SHIFT)
#define DLC_SHIFT               0
#define DLC_MASK                (0xf << DLC_SHIFT)

#define CAN_RF_SIZE             0x48
#define CAN_TEF_SIZE            0x8
#define CAN_TXEFRD_OFFSET(n)    (CAN_TXEFRD + CAN_TEF_SIZE * (n))
#define CAN_RXFRD_OFFSET(n)     (CAN_RXFRD + CAN_RF_SIZE * (n))

#define CAN_RX_FILTER_MASK      0x1fffffff
#define NOACK_ERR_FLAG          0xc200800
#define CAN_BUSOFF_FLAG         0x20
#define NSEC_PER_USEC           1000L

struct rockchip_canfd
{
    struct rt_can_device parent;

    int irq;
    void *regs;
    rt_ubase_t mode;
    rt_bool_t txtorx;
    rt_uint32_t tx_invalid[4];
    rt_uint32_t rx_fifo_shift;
    rt_uint32_t rx_fifo_mask;
    rt_uint32_t delay_time_ms;

    struct rt_can_msg rx_msg[RX_FIFO_COUNT_MAX + 1], tx_msg;

    struct rt_clk_array *clk_arr;
    struct rt_reset_control *rstc;

    struct rt_work tx_err_work;
};

#define raw_to_rockchip_canfd(raw) rt_container_of(raw, struct rockchip_canfd, parent)

#define READ_POLL_TIMEOUT_ATOMIC(OP, VAL, COND, DELAY_US,   \
        TIMEOUT_US, DELAY_BEFORE_READ, ARGS...)             \
({                                                          \
    rt_uint64_t timeout_us = (TIMEOUT_US);                  \
    rt_int64_t left_ns = timeout_us * NSEC_PER_USEC;        \
    rt_ubase_t delay_us = (DELAY_US);                       \
    rt_uint64_t delay_ns = delay_us * NSEC_PER_USEC;        \
    if (DELAY_BEFORE_READ && delay_us)                      \
    {                                                       \
        rt_hw_us_delay(delay_us);                           \
        if (timeout_us)                                     \
        {                                                   \
            left_ns -= delay_ns;                            \
        }                                                   \
    }                                                       \
    for (;;)                                                \
    {                                                       \
        (VAL) = OP(ARGS);                                   \
        if (COND)                                           \
        {                                                   \
            break;                                          \
        }                                                   \
        if (timeout_us && left_ns < 0)                      \
        {                                                   \
            (VAL) = OP(ARGS);                               \
            break;                                          \
        }                                                   \
        if (delay_us)                                       \
        {                                                   \
            rt_hw_us_delay(delay_us);                       \
            if (timeout_us)                                 \
            {                                               \
                left_ns -= delay_ns;                        \
            }                                               \
        }                                                   \
        rt_hw_cpu_relax();                                  \
        if (timeout_us)                                     \
        {                                                   \
            --left_ns;                                      \
        }                                                   \
    }                                                       \
    (COND) ? 0 : -RT_ETIMEOUT;                              \
})

static const struct rt_can_bit_timing rockchip_canfd_bittiming_const =
{
    .prescaler = 256,
    .num_seg1 = 128,
    .num_seg2 = 128,
    .num_sjw = 128,
    .num_sspoff = 2,
};

static const struct rt_can_bit_timing rockchip_canfd_data_bittiming_const =
{
    .prescaler = 256,
    .num_seg1 = 32,
    .num_seg2 = 16,
    .num_sjw = 16,
    .num_sspoff = 2,
};

rt_inline rt_uint32_t rockchip_canfd_read(struct rockchip_canfd *rk_canfd,
        int offset)
{
    return HWREG32(rk_canfd->regs + offset);
}

rt_inline void rockchip_canfd_write(struct rockchip_canfd *rk_canfd,
        int offset, rt_uint32_t val)
{
    HWREG32(rk_canfd->regs + offset) = val;
}

static rt_err_t set_reset_mode(struct rockchip_canfd *rk_canfd)
{
    rt_reset_control_assert(rk_canfd->rstc);
    rt_hw_us_delay(2);
    rt_reset_control_deassert(rk_canfd->rstc);

    rockchip_canfd_write(rk_canfd, CAN_MODE, 0);

    return RT_EOK;
}

static rt_err_t set_normal_mode(struct rockchip_canfd *rk_canfd)
{
    rt_uint32_t val;

    val = rockchip_canfd_read(rk_canfd, CAN_MODE);
    val |= WORK_MODE;
    rockchip_canfd_write(rk_canfd, CAN_MODE, val);

    return RT_EOK;
}

static int rockchip_canfd_get_rx_fifo_cnt(struct rockchip_canfd *rk_canfd)
{
    int quota = 0;

    if (READ_POLL_TIMEOUT_ATOMIC(rockchip_canfd_read, quota,
            (quota & rk_canfd->rx_fifo_mask) >> rk_canfd->rx_fifo_shift,
                0, 500000, false, rk_canfd, CAN_RXFC))
    {
        LOG_D("%s get fifo cnt failed",
                rt_dm_dev_get_name(&rk_canfd.parent.parent));
    }

    quota = (quota & rk_canfd->rx_fifo_mask) >> rk_canfd->rx_fifo_shift;

    return quota;
}

static void rockchip_canfd_tx_err_delay_work(struct rt_work *work, void *work_data)
{
    rt_uint32_t mode, err_code;
    struct rockchip_canfd *rk_canfd = work_data;

    mode = rockchip_canfd_read(rk_canfd, CAN_MODE);
    err_code = rockchip_canfd_read(rk_canfd, CAN_ERR_CODE);

    if ((err_code & NOACK_ERR_FLAG) == NOACK_ERR_FLAG)
    {
        rockchip_canfd_write(rk_canfd, CAN_MODE,
                rockchip_canfd_read(rk_canfd, CAN_MODE) | MODE_SPACE_RX);
        rockchip_canfd_write(rk_canfd, CAN_CMD, CAN_TX0_REQ);
        rockchip_canfd_write(rk_canfd, CAN_MODE,
                rockchip_canfd_read(rk_canfd, CAN_MODE) & (~MODE_SPACE_RX));

        rt_work_submit(&rk_canfd->tx_err_work,
                rt_tick_from_millisecond(rk_canfd->delay_time_ms));
    }
    else
    {
        rockchip_canfd_write(rk_canfd, CAN_MODE, 0);
        rockchip_canfd_write(rk_canfd, CAN_MODE, mode);
        rockchip_canfd_write(rk_canfd, CAN_MODE,
                rockchip_canfd_read(rk_canfd, CAN_MODE) | MODE_SPACE_RX);
        rockchip_canfd_write(rk_canfd, CAN_CMD, CAN_TX0_REQ);
        rockchip_canfd_write(rk_canfd, CAN_MODE,
                rockchip_canfd_read(rk_canfd, CAN_MODE) & (~MODE_SPACE_RX));

        rt_work_submit(&rk_canfd->tx_err_work,
                rt_tick_from_millisecond(rk_canfd->delay_time_ms));
    }
}

static rt_err_t rockchip_canfd_configure(struct rt_can_device *can,
        struct can_configure *conf)
{
    rt_uint32_t val, reg_btp;
    rt_uint16_t brp, sjw, tseg1, tseg2;
    struct rockchip_canfd *rk_canfd = raw_to_rockchip_canfd(can);
    struct rt_can_bit_timing *bt = &rk_canfd->parent.config.can_timing;
    struct rt_can_bit_timing *dbt = &rk_canfd->parent.config.canfd_timing;

    set_reset_mode(rk_canfd);

    rockchip_canfd_write(rk_canfd, CAN_INT_MASK, 0);

    /* RECEIVING FILTER, accept all */
    rockchip_canfd_write(rk_canfd, CAN_IDCODE, 0);
    rockchip_canfd_write(rk_canfd, CAN_IDMASK, CAN_RX_FILTER_MASK);
    rockchip_canfd_write(rk_canfd, CAN_IDCODE0, 0);
    rockchip_canfd_write(rk_canfd, CAN_IDMASK0, CAN_RX_FILTER_MASK);
    rockchip_canfd_write(rk_canfd, CAN_IDCODE1, 0);
    rockchip_canfd_write(rk_canfd, CAN_IDMASK1, CAN_RX_FILTER_MASK);
    rockchip_canfd_write(rk_canfd, CAN_IDCODE2, 0);
    rockchip_canfd_write(rk_canfd, CAN_IDMASK2, CAN_RX_FILTER_MASK);
    rockchip_canfd_write(rk_canfd, CAN_IDCODE3, 0);
    rockchip_canfd_write(rk_canfd, CAN_IDMASK3, CAN_RX_FILTER_MASK);
    rockchip_canfd_write(rk_canfd, CAN_IDCODE4, 0);
    rockchip_canfd_write(rk_canfd, CAN_IDMASK4, CAN_RX_FILTER_MASK);

    /* Set mode */
    val = rockchip_canfd_read(rk_canfd, CAN_MODE);

    /* RX fifo enable */
    rockchip_canfd_write(rk_canfd, CAN_RXFC,
            rockchip_canfd_read(rk_canfd, CAN_RXFC) | FIFO_ENABLE);

    val |= MODE_FDOE;

    /* Mode */
    if (conf->mode & RT_CAN_MODE_LISTEN)
    {
        val |= MODE_SILENT;
    }

    if (conf->mode & RT_CAN_MODE_LOOPBACK)
    {
        val |= MODE_SELF_TEST | MODE_LBACK;
    }

    rockchip_canfd_write(rk_canfd, CAN_MODE, val);

    /* Set bittiming */
    brp = (bt->prescaler >> 1) - 1;
    sjw = bt->num_sjw ? bt->num_sjw - 1 : 0;
    tseg1 = bt->num_seg1;
    tseg2 = bt->num_seg2;
    reg_btp = (brp << NBTP_NBRP_SHIFT) | (sjw << NBTP_NSJW_SHIFT) |
            (tseg1 << NBTP_NTSEG1_SHIFT) | (tseg2 << NBTP_NTSEG2_SHIFT);

    rockchip_canfd_write(rk_canfd, CAN_NBTP, reg_btp);

    if (rk_canfd->parent.config.mode == RT_CAN_MODE_NORMAL)
    {
        rt_uint32_t baud_rate_fd = rk_canfd->parent.config.baud_rate_fd;

        brp = (dbt->prescaler >> 1) - 1;
        sjw = dbt->num_sjw ? dbt->num_sjw - 1 : 0;
        tseg1 = dbt->num_seg1;
        tseg2 = dbt->num_seg2;

        if (baud_rate_fd > 2200000)
        {
            rt_uint32_t tdco;

            tdco = (rk_canfd->parent.config.baud_rate / baud_rate_fd) * 2 / 3;

            /* Max valid TDCO value is 63 */
            if (tdco > 63)
            {
                tdco = 63;
            }

            rockchip_canfd_write(rk_canfd, CAN_TDCR,
                    (tdco << TDC_SHIFT) | TDCR_TDC_ENABLE);
        }

        reg_btp = (brp << DBTP_DBRP_SHIFT) | (sjw << DBTP_DSJW_SHIFT) |
                (tseg1 << DBTP_DTSEG1_SHIFT) | (tseg2 << DBTP_DTSEG2_SHIFT);

        rockchip_canfd_write(rk_canfd, CAN_DBTP, reg_btp);
    }

    if (conf->baud_rate > 200000)
    {
        rk_canfd->delay_time_ms = 1;
    }
    else if (conf->baud_rate > 50000)
    {
        rk_canfd->delay_time_ms = 5;
    }
    else
    {
        rk_canfd->delay_time_ms = 20;
    }

    set_normal_mode(rk_canfd);

    return RT_EOK;
}

static rt_err_t rockchip_canfd_control(struct rt_can_device *can, int cmd, void *args)
{
    struct rt_can_bit_timing_config *timing;

    switch (cmd)
    {
    case RT_CAN_CMD_SET_MODE:
        switch ((rt_base_t)args)
        {
        case RT_CAN_MODE_NORMAL:
        case RT_CAN_MODE_LISTEN:
        case RT_CAN_MODE_LOOPBACK:
        case RT_CAN_MODE_LOOPBACKANLISTEN:
            can->config.mode = (rt_uint32_t)(rt_base_t)args;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        can->config.baud_rate = (rt_uint32_t)(rt_base_t)args;
        break;

    case RT_CAN_CMD_GET_STATUS:
        rt_memcpy(args, &can->status, sizeof(can->status));
        return RT_EOK;

    case RT_CAN_CMD_SET_CANFD:
        can->config.enable_canfd = (rt_ubase_t)args;
        break;

    case RT_CAN_CMD_SET_BAUD_FD:
        can->config.baud_rate_fd = (rt_ubase_t)args;
        break;

    case RT_CAN_CMD_SET_BITTIMING:
        timing = args;

        if (!timing || timing->count < 1 || timing->count > 2)
        {
            return -RT_EINVAL;
        }

        if (timing->count)
        {
            rt_memcpy(&can->config.can_timing, &timing->items[0],
                    sizeof(&timing->items[0]));
        }

        if (timing->count == 2)
        {
            rt_memcpy(&can->config.canfd_timing, &timing->items[1],
                    sizeof(&timing->items[1]));
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    if (can->config.enable_canfd)
    {
        rockchip_canfd_configure(can, &can->config);
    }

    return RT_EOK;
}

static rt_err_t rockchip_canfd_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t boxno)
{
    rt_uint32_t id, dlc, cmd;
    struct rt_can_msg *tx_msg;
    struct rockchip_canfd *rk_canfd = raw_to_rockchip_canfd(can);

    tx_msg = &rk_canfd->tx_msg;
    rt_memcpy(tx_msg, buf, sizeof(*tx_msg));

    if (rockchip_canfd_read(rk_canfd, CAN_CMD) & CAN_TX0_REQ)
    {
        cmd = CAN_TX1_REQ;
    }
    else
    {
        cmd = CAN_TX0_REQ;
    }

    if (tx_msg->id & CAN_EFF_FLAG)
    {
        /* Extended CAN ID format */
        id = tx_msg->id & CAN_EFF_MASK;
        dlc = (can_len2dlc(tx_msg->len) & DLC_MASK) | FORMAT_MASK;
    }
    else
    {
        /* Standard CAN ID format */
        id = tx_msg->id & CAN_SFF_MASK;
        dlc = can_len2dlc(tx_msg->len) & DLC_MASK;
    }

    if (tx_msg->id & CAN_RTR_FLAG)
    {
        dlc |= RTR_MASK;
    }

    if (can->config.mode == RT_CAN_MODE_NORMAL && tx_msg->len <= CANFD_MAX_DLEN)
    {
        dlc |= TX_FD_ENABLE;
    }

    if (tx_msg->ide)
    {
        dlc |= FORMAT_MASK;
    }

    if (tx_msg->rtr)
    {
        dlc |= RTR_MASK;
    }

    if (rk_canfd->txtorx && rk_canfd->mode <= ROCKCHIP_RK3568_CAN_MODE &&
        tx_msg->id & CAN_EFF_FLAG)
    {
        rockchip_canfd_write(rk_canfd, CAN_MODE,
                rockchip_canfd_read(rk_canfd, CAN_MODE) | MODE_RXSTX);
    }
    else
    {
        rockchip_canfd_write(rk_canfd, CAN_MODE,
                rockchip_canfd_read(rk_canfd, CAN_MODE) & (~MODE_RXSTX));
    }

    if (!rk_canfd->txtorx && rk_canfd->mode <= ROCKCHIP_RK3568_CAN_MODE &&
        tx_msg->id & CAN_EFF_FLAG)
    {
        /*
         * Two frames are sent consecutively.
         * Before the first frame is tx finished,
         * the register of the second frame is configured.
         * Don't be interrupted in the middle.
         */
        rt_ubase_t level;
        static struct rt_spinlock pe_lock = {};

        level = rt_spin_lock_irqsave(&pe_lock);

        rockchip_canfd_write(rk_canfd, CAN_TXID, rk_canfd->tx_invalid[1]);
        rockchip_canfd_write(rk_canfd, CAN_TXFIC, rk_canfd->tx_invalid[0]);
        rockchip_canfd_write(rk_canfd, CAN_TXDAT0, rk_canfd->tx_invalid[2]);
        rockchip_canfd_write(rk_canfd, CAN_TXDAT1, rk_canfd->tx_invalid[3]);
        rockchip_canfd_write(rk_canfd, CAN_CMD, CAN_TX0_REQ);
        rockchip_canfd_write(rk_canfd, CAN_TXID, id);
        rockchip_canfd_write(rk_canfd, CAN_TXFIC, dlc);

        for (int i = 0; i < tx_msg->len; i += 4)
        {
            rockchip_canfd_write(rk_canfd, CAN_TXDAT0 + i,
                    *(rt_uint32_t *)(tx_msg->data + i));
        }

        rockchip_canfd_write(rk_canfd, CAN_CMD, CAN_TX1_REQ);

        rt_spin_unlock_irqrestore(&pe_lock, level);

        return RT_EOK;
    }

    rockchip_canfd_write(rk_canfd, CAN_TXID, id);
    rockchip_canfd_write(rk_canfd, CAN_TXFIC, dlc);

    for (int i = 0; i < tx_msg->len; i += 4)
    {
        rockchip_canfd_write(rk_canfd, CAN_TXDAT0 + i,
                *(rt_uint32_t *)(tx_msg->data + i));
    }

    rockchip_canfd_write(rk_canfd, CAN_MODE,
            rockchip_canfd_read(rk_canfd, CAN_MODE) | MODE_SPACE_RX);
    rockchip_canfd_write(rk_canfd, CAN_CMD, cmd);
    rockchip_canfd_write(rk_canfd, CAN_MODE,
            rockchip_canfd_read(rk_canfd, CAN_MODE) & (~MODE_SPACE_RX));

    rt_work_submit(&rk_canfd->tx_err_work,
            rt_tick_from_millisecond(rk_canfd->delay_time_ms));

    return RT_EOK;
}

static rt_err_t rockchip_canfd_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t boxno)
{
    struct rockchip_canfd *rk_canfd = raw_to_rockchip_canfd(can);

    rt_memcpy(buf, &rk_canfd->rx_msg[boxno], sizeof(rk_canfd->rx_msg[boxno]));

    return RT_EOK;
}

static const struct rt_can_ops rockchip_canfd_ops =
{
    .configure = rockchip_canfd_configure,
    .control = rockchip_canfd_control,
    .sendmsg = rockchip_canfd_sendmsg,
    .recvmsg = rockchip_canfd_recvmsg,
};

static rt_uint32_t rockchip_canfd_rx(struct rockchip_canfd *rk_canfd, int boxno)
{
    struct rt_can_msg *rx_msg = &rk_canfd->rx_msg[boxno];
    rt_uint32_t id_rockchip_canfd, dlc, tx_id, ts, data[16] = { 0 };

    dlc = rockchip_canfd_read(rk_canfd, CAN_RXFRD);
    id_rockchip_canfd = rockchip_canfd_read(rk_canfd, CAN_RXFRD);
    ts = rockchip_canfd_read(rk_canfd, CAN_RXFRD);

    for (int i = 0; i < RT_ARRAY_SIZE(data); ++i)
    {
        data[i] = rockchip_canfd_read(rk_canfd, CAN_RXFRD);
    }

    if (rk_canfd->mode >= ROCKCHIP_CAN_MODE)
    {
        if (!dlc && !id_rockchip_canfd)
        {
            return 1;
        }

        if (rk_canfd->txtorx)
        {
            if (rockchip_canfd_read(rk_canfd, CAN_TX_CHECK_FIC) & FORMAT_MASK)
            {
                tx_id = rockchip_canfd_read(rk_canfd, CAN_TXID) & CAN_SFF_MASK;

                if (id_rockchip_canfd == tx_id && !(dlc & FORMAT_MASK))
                {
                    rockchip_canfd_write(rk_canfd, CAN_TX_CHECK_FIC,
                            ts | CAN_TX0_REQ);

                    return 1;
                }
            }
        }
    }

    if (dlc & FDF_MASK)
    {
        rx_msg->len = can_dlc2len(dlc & DLC_MASK);
    }
    else
    {
        rx_msg->len = can_get_dlc(dlc & DLC_MASK);
    }

    rx_msg->id = id_rockchip_canfd;

    if (dlc & FORMAT_MASK)
    {
        rx_msg->id |= CAN_EFF_FLAG;
    }

    if (dlc & RTR_MASK)
    {
        rx_msg->id |= CAN_RTR_FLAG;
    }

    rx_msg->ide = (dlc & FORMAT_MASK) >> FORMAT_SHIFT;
    rx_msg->rtr = (dlc & RTR_MASK) >> RTR_SHIFT;

    if (!(rx_msg->id & CAN_RTR_FLAG))
    {
        for (int i = 0; i < rx_msg->len; i += 4)
        {
            *(rt_uint32_t *)(rx_msg->data + i) = data[i / 4];
        }
    }

    return 1;
}

static rt_err_t rockchip_canfd_err(struct rockchip_canfd *rk_canfd, rt_uint8_t ints)
{
    rt_uint32_t sta_reg;
    struct rt_can_device *can = &rk_canfd->parent;

    can->status.rcverrcnt = rockchip_canfd_read(rk_canfd, CAN_RX_ERR_CNT);
    can->status.snderrcnt = rockchip_canfd_read(rk_canfd, CAN_TX_ERR_CNT);
    sta_reg = rockchip_canfd_read(rk_canfd, CAN_STATE);

    if (ints & BUS_OFF_INT)
    {
        can->status.errcode = BUSOFF;
    }
    else if (ints & ERR_WARN_INT)
    {
        can->status.errcode = ERRWARNING;
    }
    else if (ints & PASSIVE_ERR_INT)
    {
        can->status.errcode = ERRPASSIVE;
    }

    if (can->status.errcode >= BUSOFF ||
        (sta_reg & CAN_BUSOFF_FLAG) == CAN_BUSOFF_FLAG)
    {
        rt_work_cancel(&rk_canfd->tx_err_work);

        /* Stop */
        set_reset_mode(rk_canfd);
        /* Disable all interrupts */
        rockchip_canfd_write(rk_canfd, CAN_INT_MASK, 0xffff);

        /* Start */
        rockchip_canfd_configure(&rk_canfd->parent, &can->config);
    }

    return RT_EOK;
}

static void rockchip_canfd_isr(int irqno, void *param)
{
    rt_uint32_t ints, dlc, quota, work_done = 0;
    struct rockchip_canfd *rk_canfd = param;
    const rt_uint32_t err_ints = ERR_WARN_INT | RX_BUF_OV_INT | PASSIVE_ERR_INT |
            TX_LOSTARB_INT | BUS_ERR_INT | BUS_OFF_INT;

    ints = rockchip_canfd_read(rk_canfd, CAN_INT);

    if (ints & TX_FINISH_INT)
    {
        rt_work_cancel(&rk_canfd->tx_err_work);
        dlc = rockchip_canfd_read(rk_canfd, CAN_TXFIC);

        if (rk_canfd->txtorx && rk_canfd->mode <= ROCKCHIP_RK3568_CAN_MODE &&
            dlc & FORMAT_MASK)
        {
            rockchip_canfd_write(rk_canfd, CAN_TX_CHECK_FIC, FORMAT_MASK);
            quota = rockchip_canfd_get_rx_fifo_cnt(rk_canfd);

            for (int boxno = 0; work_done < quota; ++boxno)
            {
                work_done += rockchip_canfd_rx(rk_canfd, boxno);
                rt_hw_can_isr(&rk_canfd->parent, RT_CAN_EVENT_TX_DONE | (boxno << 8));
            }

            if (rockchip_canfd_read(rk_canfd, CAN_TX_CHECK_FIC) & CAN_TX0_REQ)
            {
                rockchip_canfd_write(rk_canfd, CAN_CMD, CAN_TX1_REQ);
            }
            rockchip_canfd_write(rk_canfd, CAN_TX_CHECK_FIC, 0);
        }
        else
        {
            rt_hw_can_isr(&rk_canfd->parent, RT_CAN_EVENT_TX_DONE);
        }

        if (READ_POLL_TIMEOUT_ATOMIC(rockchip_canfd_read, quota,
                !(quota & 0x3), 0, 5000000, false, rk_canfd, CAN_CMD))
        {
            LOG_E("%s: Wait tx req timeout",
                    rt_dm_dev_get_name(&rk_canfd->parent.parent));
        }

        rockchip_canfd_write(rk_canfd, CAN_CMD, 0);
    }

    if (ints & RX_FINISH_INT)
    {
        if (rk_canfd->mode == ROCKCHIP_RK3568_CAN_MODE_V2)
        {
            rockchip_canfd_write(rk_canfd, CAN_INT_MASK, 0x1);
        }
        else
        {
            work_done = 0;
            quota = (rockchip_canfd_read(rk_canfd, CAN_RXFC) &
                    rk_canfd->rx_fifo_mask) >> rk_canfd->rx_fifo_shift;

            for (int boxno = 0; work_done < quota; ++boxno)
            {
                work_done += rockchip_canfd_rx(rk_canfd, boxno);
                rt_hw_can_isr(&rk_canfd->parent, RT_CAN_EVENT_RX_IND | (boxno << 8));
            }
        }

    }

    if (ints & (RX_FIFO_FULL_INT | RX_FIFO_OV_INT))
    {
        rt_hw_can_isr(&rk_canfd->parent, RT_CAN_EVENT_RXOF_IND);
        rockchip_canfd_rx(rk_canfd, RX_FIFO_ERR_IDX);
    }

    if (ints & err_ints)
    {
        rockchip_canfd_err(rk_canfd, ints);
        rockchip_canfd_rx(rk_canfd, RX_FIFO_ERR_IDX);
    }

    rockchip_canfd_write(rk_canfd, CAN_INT, ints);
}

static void rockchip_canfd_free(struct rockchip_canfd *rk_canfd)
{
    if (rk_canfd->regs)
    {
        rt_iounmap(rk_canfd->regs);
    }

    if (!rt_is_err_or_null(rk_canfd->clk_arr))
    {
        rt_clk_array_put(rk_canfd->clk_arr);
    }

    if (!rt_is_err_or_null(rk_canfd->rstc))
    {
        rt_reset_control_put(rk_canfd->rstc);
    }

    rt_free(rk_canfd);
}

static rt_err_t rockchip_canfd_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_can_device *can;
    struct can_configure *conf;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_canfd *rk_canfd = rt_calloc(1, sizeof(*rk_canfd));

    if (!rk_canfd)
    {
        return -RT_ENOMEM;
    }

    rk_canfd->mode = (rt_ubase_t)pdev->id->data;
    rk_canfd->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_canfd->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_canfd->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk_canfd->irq < 0)
    {
        err = rk_canfd->irq;
        goto _fail;
    }

    rk_canfd->clk_arr = rt_clk_get_array(dev);

    if (rt_is_err(rk_canfd->clk_arr))
    {
        err = rt_ptr_err(rk_canfd->clk_arr);
        goto _fail;
    }

    rk_canfd->rstc = rt_reset_control_get_array(dev);

    if (rt_is_err(rk_canfd->rstc))
    {
        err = rt_ptr_err(rk_canfd->rstc);
        goto _fail;
    }

#ifdef RT_USING_OFW
    /* RockChip CPU version = 3 */
    if ((rt_ofw_machine_is_compatible("rockchip,rk3566") ||
        rt_ofw_machine_is_compatible("rockchip,rk3568")))
    {
        rk_canfd->mode = ROCKCHIP_RK3568_CAN_MODE_V2;
    }
#endif

    can = &rk_canfd->parent;
    conf = &can->config;

    conf->baud_rate = rt_clk_get_rate(rk_canfd->clk_arr->clks[0]);
    conf->msgboxsz = 1;
    conf->sndboxnumber = 1;
    conf->mode = RT_CAN_MODE_NORMAL;
    conf->ticks = 50;
#ifdef RT_CAN_USING_HDR
    conf->maxhdr = 4;
#endif
    conf->use_bit_timing = 1;
    rt_memcpy(&conf->can_timing, &rockchip_canfd_bittiming_const, sizeof(conf->can_timing));

    if (rk_canfd->mode == ROCKCHIP_CAN_MODE)
    {
        rk_canfd->rx_fifo_shift = RX_FIFO_CNT1_SHIFT;
        rk_canfd->rx_fifo_mask = RX_FIFO_CNT1_MASK;
    }
    else
    {
        if (rk_canfd->mode == ROCKCHIP_CANFD_MODE)
        {
            rt_memcpy(&conf->canfd_timing, &rockchip_canfd_data_bittiming_const,
                    sizeof(conf->canfd_timing));
        }

        rk_canfd->rx_fifo_shift = RX_FIFO_CNT0_SHIFT;
        rk_canfd->rx_fifo_mask = RX_FIFO_CNT0_MASK;
    }

    if (rt_dm_dev_prop_read_u32_array_index(dev, "rockchip,tx-invalid-info",
            0, 4, rk_canfd->tx_invalid) < 0)
    {
        rk_canfd->txtorx = RT_TRUE;
    }

    if (rk_canfd->mode == ROCKCHIP_RK3568_CAN_MODE_V2)
    {
        rk_canfd->txtorx = RT_FALSE;
    }

    dev->user_data = rk_canfd;

    rt_work_init(&rk_canfd->tx_err_work, rockchip_canfd_tx_err_delay_work, rk_canfd);

    rt_dm_dev_set_name_auto(&can->parent, "can");
    dev_name = rt_dm_dev_get_name(&can->parent);

    rt_hw_interrupt_install(rk_canfd->irq, rockchip_canfd_isr, rk_canfd, dev_name);
    rt_hw_interrupt_umask(rk_canfd->irq);

    if ((err = rt_hw_can_register(can, dev_name, &rockchip_canfd_ops, rk_canfd)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rockchip_canfd_free(rk_canfd);

    return err;
}

static rt_err_t rockchip_canfd_remove(struct rt_platform_device *pdev)
{
    struct rockchip_canfd *rk_canfd = pdev->parent.user_data;

    rt_hw_interrupt_mask(rk_canfd->irq);
    rt_pic_detach_irq(rk_canfd->irq, rk_canfd);

    rt_device_unregister(&rk_canfd->parent.parent);

    rockchip_canfd_free(rk_canfd);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_canfd_ofw_ids[] =
{
    { .compatible = "rockchip,canfd-1.0", .data = (void *)ROCKCHIP_CANFD_MODE },
    { .compatible = "rockchip,can-2.0", .data = (void *)ROCKCHIP_CAN_MODE },
    { .compatible = "rockchip,rk3568-can-2.0", .data = (void *)ROCKCHIP_RK3568_CAN_MODE },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_canfd_driver =
{
    .name = "canfd-rockchip",
    .ids = rockchip_canfd_ofw_ids,

    .probe = rockchip_canfd_probe,
    .remove = rockchip_canfd_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_canfd_driver);
