/* all about mxic factory */

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <hal_timer.h>

#include "inter.h"

#define NOR_MXIC_CMD_READ_CR 0x15
#define NOR_MXIC_CMD_RDSCUR 0x2B
#define NOR_MXIC_CMD_WRSCUR 0x2F
#define NOR_MXIC_CMD_WPSEL 0x68
#define NOR_MXIC_CMD_ESSPB 0xE4
#define NOR_MXIC_CMD_RDSPB 0xE2
#define NOR_MXIC_CMD_WRSPB 0xE3
#define NOR_MXIC_CMD_RDDPB 0xE0
#define NOR_MXIC_CMD_WRDPB 0xE1
#define NOR_MXIC_WPSEL_BIT BIT(7)
#define NOR_MXIC_QE_BIT BIT(6)
#define NOR_MXIC_DPB_LOCK (0xFF)
#define NOR_MXIC_DPB_UNLOCK (0x00)
#define NOR_MXIC_PT_MASK (BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define NOR_MXIC_PROTECT_BP_SHIFT 2

static struct nor_info idt_mxic[] =
{
    {
        .model = "mx25l6433f",
        .id = {0xc2, 0x20, 0x17},
        .total_size = SZ_8M,
        .flag = SUPPORT_GENERAL | USE_IO_PROG_X4 | SUPPORT_INDIVIDUAL_PROTECT,
    },
    {
        .model = "mx25l12833f",
        .id = {0xc2, 0x20, 0x18},
        .total_size = SZ_16M,
        .flag = SUPPORT_GENERAL | USE_IO_PROG_X4 | SUPPORT_INDIVIDUAL_PROTECT,
    },
    {
        .model = "mx25l51234g",
        .id = {0xc2, 0x20, 0x1a},
        .total_size = SZ_64M,
        .flag = SUPPORT_GENERAL | USE_IO_PROG_X4,
    }
};

static int nor_mxic_quad_mode(struct nor_flash *nor)
{
    int ret;
    unsigned char sr;

    ret = nor_read_status(&sr);
    if (ret)
        return ret;

    if (sr & NOR_MXIC_QE_BIT)
        return 0;

    sr |= NOR_MXIC_QE_BIT;
    /*
     * If individual protect mode is enable, BP can't not write. If BP bits
     * are set, write status will go failed, which make QE bit set failed.
     */
    if (is_wrlock_work(nor))
        sr &= ~(NOR_MXIC_PT_MASK << NOR_MXIC_PROTECT_BP_SHIFT);
    ret = nor_write_status(&sr, 1);
    if (ret)
        return ret;

    ret = nor_read_status(&sr);
    if (ret)
        return ret;

    if (!(sr & NOR_MXIC_QE_BIT)) {
        SPINOR_ERR("set mxic QE failed (0x%x)\n", sr);
        return -EINVAL;
    }
    return 0;
}

static int nor_mxic_set_wps(void)
{
    int ret;
    unsigned char cmd, sr;

    cmd = NOR_MXIC_CMD_RDSCUR;
    ret = nor_transfer(1, &cmd, 1, &sr, 1);
    if (ret)
        return ret;

    /* already set before, no need to set again */
    if (sr & NOR_MXIC_WPSEL_BIT)
        return 0;

    ret = nor_write_enable();
    if (ret)
        return ret;

    ret = nor_send_cmd(NOR_MXIC_CMD_WPSEL);
    if (ret)
        return ret;

    ret = nor_wait_ready(10, 100 * 1000);
    if (ret)
        return ret;

    cmd = NOR_MXIC_CMD_RDSCUR;
    ret = nor_transfer(1, &cmd, 1, &sr, 1);
    if (ret)
        return ret;
    return !(sr & NOR_MXIC_WPSEL_BIT);
}

static int nor_mxic_reset_spb(void)
{
    int ret;

    ret = nor_write_enable();
    if (ret)
        return ret;

    ret = nor_send_cmd(NOR_MXIC_CMD_ESSPB);
    if (ret)
        return ret;

    ret = nor_wait_ready(10, 500);
    if (ret)
        return ret;

    return 0;
}

static int nor_mxic_init_lock(struct nor_flash *nor)
{
    int ret;

    ret = nor_mxic_set_wps();
    if (ret)
        return ret;

    ret = nor_mxic_reset_spb();
    if (ret)
        return ret;

    return 0;
}

static bool nor_mxic_blk_islock(unsigned int addr)
{
    int ret;
    unsigned char tbuf[5], st;

    tbuf[0] = NOR_MXIC_CMD_RDDPB;
    tbuf[1] = addr >> 24;
    tbuf[2] = addr >> 16;
    tbuf[3] = addr >> 8;
    tbuf[4] = addr & 0xFF;
    ret = nor_transfer(5, tbuf, 5, &st, 1);
    if (ret)
        return ret;

    return st == 0xFF ? true : false;
}

static int nor_mxic_blk_unlock(unsigned int addr)
{
    int ret;
    unsigned char tbuf[6];

    ret = nor_write_enable();
    if (ret)
        return ret;

    tbuf[0] = NOR_MXIC_CMD_WRDPB;
    tbuf[1] = addr >> 24;
    tbuf[2] = addr >> 16;
    tbuf[3] = addr >> 8;
    tbuf[4] = addr & 0xFF;
    tbuf[5] = NOR_MXIC_DPB_UNLOCK;
    ret = nor_transfer(6, tbuf, 6, NULL, 0);
    if (ret) {
        SPINOR_ERR("mxic unlock 0x%x failed - %d\n", addr, ret);
        return ret;
    }
    if (nor_mxic_blk_islock(addr) == true)
        return -EBUSY;
    return 0;
}

static int nor_mxic_blk_lock(unsigned int addr)
{
    int ret;
    unsigned char tbuf[6];

    ret = nor_write_enable();
    if (ret)
        return ret;

    tbuf[0] = NOR_MXIC_CMD_WRDPB;
    tbuf[1] = addr >> 24;
    tbuf[2] = addr >> 16;
    tbuf[3] = addr >> 8;
    tbuf[4] = addr & 0xFF;
    tbuf[5] = NOR_MXIC_DPB_LOCK;
    ret = nor_transfer(6, tbuf, 6, NULL, 0);
    if (ret) {
        SPINOR_ERR("mxic lock 0x%x failed - %d\n", addr, ret);
        return ret;
    }
    if (nor_mxic_blk_islock(addr) == false)
        return -EBUSY;
    return 0;
}

static int nor_mxic_lock(struct nor_flash *nor, unsigned int addr,
        unsigned int len)
{
    return nor_mxic_blk_lock(addr);
}

static int nor_mxic_unlock(struct nor_flash *nor, unsigned int addr,
        unsigned int len)
{
    return nor_mxic_blk_unlock(addr);
}

static bool nor_mxic_islock(struct nor_flash *nor, unsigned int addr,
        unsigned int len)
{
    return nor_mxic_blk_islock(addr);
}

static struct nor_factory nor_mxic = {
    .factory = FACTORY_MXIC,
    .idt = idt_mxic,
    .idt_cnt = sizeof(idt_mxic),

    .init = NULL,
    .deinit = NULL,
    .init_lock = nor_mxic_init_lock,
    .deinit_lock = NULL,
    .lock = nor_mxic_lock,
    .unlock = nor_mxic_unlock,
    .islock = nor_mxic_islock,
    .set_quad_mode = nor_mxic_quad_mode,
    .set_4bytes_addr = NULL,
};

int nor_register_factory_mxic(void)
{
    return nor_register_factory(&nor_mxic);
}
