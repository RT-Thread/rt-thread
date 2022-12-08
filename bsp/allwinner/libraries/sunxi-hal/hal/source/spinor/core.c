#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <hal_timer.h>

#include "inter.h"

#define NOR_CMD_READ 0x03
#define NOR_CMD_FAST_READ 0x0B
#define NOR_CMD_DUAL_READ 0x3B
#define NOR_CMD_QUAD_READ 0x6B
#define NOR_CMD_DUAL_IO_READ 0xBB
#define NOR_CMD_QUAD_IO_READ 0xEB
#define NOR_CMD_PROG 0x02
#define NOR_CMD_QUAD_PROG 0x32
#define NOR_CMD_QUAD_IO_PROG 0x38
#define NOR_CMD_ERASE_BLK4K 0x20
#define NOR_CMD_ERASE_BLK32K 0x52
#define NOR_CMD_ERASE_BLK64K 0xD8
#define NOR_CMD_ERASE_CHIP 0x60
#define NOR_CMD_WREN 0x06
#define NOR_CMD_WRDI 0x04
#define NOR_CMD_READ_SR 0x05
#define NOR_CMD_WRITE_SR 0x01
#define NOR_CMD_READ_CR 0x15
#define NOR_CMD_READ_SCUR 0x2B
#define NOR_CMD_RESET_EN 0x66
#define NOR_CMD_RESET 0x99
#define NOR_CMD_RDID 0x9F

#define cmd_4bytes(cmd) (nor->addr_width == 4 ? cmd ## 4B : cmd)
#define NOR_CMD_EN4B 0xB7
#define NOR_CMD_EX4B 0xE9
#define NOR_CMD_MXC_EX4B 0x29
#define NOR_CMD_READ4B 0x13
#define NOR_CMD_FAST_READ4B 0x0C
#define NOR_CMD_DUAL_READ4B 0x3C
#define NOR_CMD_QUAD_READ4B 0x6C
#define NOR_CMD_DUAL_IO_READ4B 0xBC
#define NOR_CMD_QUAD_IO_READ4B 0xEC
#define NOR_CMD_PROG4B 0x12
#define NOR_CMD_QUAD_PROG4B 0x34
#define NOR_CMD_QUAD_IO_PROG4B 0x3E
#define NOR_CMD_ERASE_BLK4K4B 0x21
#define NOR_CMD_ERASE_BLK32K4B 0x5C
#define NOR_CMD_ERASE_BLK64K4B 0xDC

#define NOR_BUSY_MASK BIT(0)
#define NOR_SR_BIT_WEL BIT(1)

static struct nor_flash g_nor, *nor = &g_nor;
static struct nor_factory g_fhead;

static inline int nor_lock_init(void)
{
    nor->hal_sem = hal_sem_create(1);
    if (!nor->hal_sem) {
        SPINOR_ERR("create hal_sem lock for nor_flash failed");
        return -1;
    }
    return 0;
}

static inline int nor_lock(void)
{
    return hal_sem_wait(nor->hal_sem);
}

static inline int nor_unlock(void)
{
    return hal_sem_post(nor->hal_sem);
}

static inline void nor_msleep(unsigned int msec)
{
    hal_usleep(msec * 1000);
}

static int cmd_bit(unsigned char cmd)
{
    switch (cmd)
    {
        case NOR_CMD_DUAL_READ:
        case NOR_CMD_DUAL_IO_READ:
        case NOR_CMD_DUAL_READ4B:
        case NOR_CMD_DUAL_IO_READ4B:
            return 2;
        case NOR_CMD_QUAD_READ:
        case NOR_CMD_QUAD_IO_READ:
        case NOR_CMD_QUAD_READ4B:
        case NOR_CMD_QUAD_IO_READ4B:
        case NOR_CMD_QUAD_PROG:
        case NOR_CMD_QUAD_IO_PROG:
        case NOR_CMD_QUAD_PROG4B:
        case NOR_CMD_QUAD_IO_PROG4B:
            return 4;
        default:
            return 1;
    }
}

int nor_register_factory(struct nor_factory *f)
{
    struct nor_factory *p = &g_fhead;

    if (!f)
        return -1;

    while (p->next)
        p = p->next;
    p->next = f;
    f->next = NULL;

    SPINOR_DEBUG("register factory 0x%x", f->factory);
    return 0;
}

int nor_transfer(int single_len, void *tbuf, int tlen, void *rbuf, int rlen)
{
    hal_spi_master_transfer_t tr;
    unsigned char cmd = *(unsigned char *)tbuf;
    int ret;

    tr.tx_buf = tbuf;
    tr.tx_len = tlen;
    tr.rx_buf = rbuf;
    tr.rx_len = rlen;
    tr.tx_single_len = single_len;
    tr.dummy_byte = 0;

    tr.rx_nbits = tr.tx_nbits = SPI_NBITS_SINGLE;
    switch (cmd)
    {
        case NOR_CMD_FAST_READ:
        case NOR_CMD_FAST_READ4B:
            tr.dummy_byte = 1;
            break;
        case NOR_CMD_DUAL_READ:
        case NOR_CMD_DUAL_IO_READ:
        case NOR_CMD_DUAL_READ4B:
        case NOR_CMD_DUAL_IO_READ4B:
            tr.rx_nbits = SPI_NBITS_DUAL;
            tr.dummy_byte = 1;
            break;
        case NOR_CMD_QUAD_READ:
        case NOR_CMD_QUAD_IO_READ:
        case NOR_CMD_QUAD_READ4B:
        case NOR_CMD_QUAD_IO_READ4B:
            tr.rx_nbits = SPI_NBITS_QUAD;
            tr.dummy_byte = 1;
            break;
        case NOR_CMD_QUAD_PROG:
        case NOR_CMD_QUAD_IO_PROG:
        case NOR_CMD_QUAD_PROG4B:
        case NOR_CMD_QUAD_IO_PROG4B:
            tr.tx_nbits = SPI_NBITS_QUAD;
            break;
    }

    ret = hal_spi_xfer(nor->spim.port, &tr);
    if (ret)
        SPINOR_ERR("spi transfer failed %d", ret);
    return ret;
}

int nor_read_status(unsigned char *sr)
{
    int ret;
    char cmd[1] = {NOR_CMD_READ_SR};
    char reg[2] = {0};

    ret = nor_transfer(1, cmd, 1, reg, 2);
    if (ret) {
        SPINOR_ERR("read status register fail");
        return ret;
    }

    *sr = reg[1];
    return 0;
}

static int nor_is_busy(void)
{
    int ret;
    unsigned char reg;

    ret = nor_read_status(&reg);
    if (ret)
        return ret;

    if (reg & NOR_BUSY_MASK)
        return true;
    else
        return false;
}

/**
 * As the minimum time is 1ms, to save time, we wait ready under 2 step:
 * 1. sleep on ms, which take mush time.
 * 2. check times on cpu. It will be ready soon in this case
 */
int nor_wait_ready(unsigned int ms, unsigned int times)
{
    unsigned int _ms = ms, _times = times;

    do {
        if (nor_is_busy() == false)
            return 0;
        if (_ms)
            nor_msleep(1);
    } while (--_ms > 0);

    do {
        if (nor_is_busy() == false)
            return 0;
    } while (--_times > 0);

    /* check the last time */
    if (nor_is_busy() == false)
        return 0;

    SPINOR_ERR("wait nor flash for %d ms and %d loop timeout", ms, times);
    return -EBUSY;
}

int nor_send_cmd(unsigned char cmd)
{
    int ret;
    ret = nor_transfer(1, &cmd, 1, NULL, 0);
    if (ret)
        return ret;
    return nor_wait_ready(0, 500);
}

static int nor_set_4byte(int enable)
{
    int ret;
    struct nor_factory *f = nor->factory;

    if (f && f->set_4bytes_addr)
        return f->set_4bytes_addr(nor, enable);

    ret = nor_send_cmd(NOR_CMD_EN4B);
    if (ret) {
        SPINOR_ERR("set 4byte %d fail", enable);
        return ret;
    }
    SPINOR_DEBUG("set 4byte %d success", enable);
    return 0;
}

int nor_write_enable(void)
{
    int ret;
    unsigned char sr;

    ret = nor_send_cmd(NOR_CMD_WREN);
    if (ret) {
        SPINOR_ERR("send WREN failed - %d", ret);
        return ret;
    }

    ret = nor_read_status(&sr);
    if (ret)
        return ret;

    if (!(sr & NOR_SR_BIT_WEL)) {
        SPINOR_ERR("enable write failed");
        return -EINVAL;
    }
    return 0;
}

int nor_write_status(unsigned char *sr, unsigned int len)
{
    int ret, i;
    char tbuf[5] = {0};

    ret = nor_write_enable();
    if (ret)
        return ret;

    if (len > 5)
        return -EINVAL;

    tbuf[0] = NOR_CMD_WRITE_SR;
    for (i = 0; i < len; i++)
        tbuf[i + 1] = *(sr + i);
    i++;
    ret = nor_transfer(i, tbuf, i, NULL, 0);
    if (ret) {
        SPINOR_ERR("write status register fail");
        return ret;
    }

    return nor_wait_ready(10, MAX_WAIT_LOOP);
}

static int nor_read_id(char *id, int len)
{
    int ret;
    char cmd[1] = {NOR_CMD_RDID};

    if (nor_wait_ready(0, 500)) {
        SPINOR_ERR("nor is busy before read id");
        return -EBUSY;
    }

    ret = nor_transfer(1, cmd, 1, id, MIN(len, (int)MAX_ID_LEN));
    if (ret)
        SPINOR_ERR("read nor id failed - %d", ret);
    return ret;
}

static int nor_reset(void)
{
    int ret;
    char cmd[2] = {NOR_CMD_RESET_EN, NOR_CMD_RESET};

    ret = nor_transfer(2, cmd, 2, NULL, 0);
    if (ret)
        SPINOR_ERR("reset nor failed - %d", ret);
    return ret;
}

static int nor_spi_master_init(struct nor_spi_master *spim)
{
    int ret;

    spim->port = HAL_SPI_MASTER_0;

#ifdef CONFIG_DRIVERS_SPINOR_FREQ
    spim->cfg.clock_frequency = CONFIG_DRIVERS_SPINOR_FREQ;
#else
    spim->cfg.clock_frequency = NOR_DEFAULT_FREQUENCY;
#endif
    spim->cfg.clock_frequency *= 1000 * 1000;
    spim->cfg.slave_port = HAL_SPI_MASTER_SLAVE_0;
    spim->cfg.cpha = HAL_SPI_MASTER_CLOCK_PHASE0;
    spim->cfg.cpol = HAL_SPI_MASTER_CLOCK_POLARITY0;
    spim->cfg.bit_order = HAL_SPI_MASTER_LSB_FIRST;

    ret = hal_spi_init(spim->port, &spim->cfg);
    if (ret != HAL_SPI_MASTER_STATUS_OK)
        SPINOR_ERR("init spi master failed - %d", ret);
    return ret;
}

static int nor_spi_master_deinit(struct nor_spi_master *spim)
{
    return hal_spi_deinit(spim->port);
}

static int match_nor(struct nor_flash *nor, char *id, int id_len)
{
    struct nor_factory *f = g_fhead.next;
    struct nor_info *info;
    int i;

    for (; f; f = f->next) {
        if (f->factory != (unsigned char)id[0])
            continue;
        for (i = 0; i < f->idt_cnt; i++) {
            info = &f->idt[i];
            if (!memcmp(info->id, id, id_len)) {
                SPINOR_DEBUG("match nor %s on table", info->model);
                nor->factory = f;
                nor->info = info;
                return 0;
            }
        }
        /* the factory already check all ids but not match */
        SPINOR_ERR("not match any id on factory 0x%x ids table", f->factory);
        return -1;
    }
    SPINOR_ERR("not match any factory 0x%x ids table", id[0]);
    return -1;
}

static int nor_set_quad_mode(void)
{
    if (nor->factory->set_quad_mode)
        return nor->factory->set_quad_mode(nor);
    return 0;
}

static int nor_factory_register(void)
{
    nor_register_factory_gd();
    nor_register_factory_mxic();
    nor_register_factory_winbond();
    nor_register_factory_xtx();
    nor_register_factory_esmt();
    nor_register_factory_fm();
    nor_register_factory_xmc();
    nor_register_factory_puya();
    nor_register_factory_zetta();
    return 0;
}

static int nor_factory_init(void)
{
    if (nor->factory->init)
        return nor->factory->init(nor);
    return 0;
}

static void nor_factory_deinit(void)
{
    if (nor->factory->deinit)
        nor->factory->deinit(nor);
}

static int nor_scan(void)
{
    int ret;
    char id[MAX_ID_LEN];

    ret = nor_read_id(id, MAX_ID_LEN);
    if (ret) {
        goto err;
    }
    ret = match_nor(nor, id, MAX_ID_LEN);
    if (ret)
        goto err;

    if (nor->info->flag == 0)
        nor->info->flag = SUPPORT_GENERAL;

    nor->total_size = nor->info->total_size;
    nor->addr_width = 3;
    if (nor->total_size > SZ_16M) {
        nor->addr_width = 4;
        nor_set_4byte(true);
    }

    nor->page_size = NOR_PAGE_SIZE;
#ifdef CONFIG_DRIVERS_SPINOR_4K_SECTORS
    nor->blk_size = SZ_4K;
#else
    if (nor->info->flag & SUPPORT_64K_ERASE_BLK) {
        nor->blk_size = NOR_BLK_SIZE;
    } else if (nor->info->flag & SUPPORT_32K_ERASE_BLK) {
        nor->blk_size = NOR_HALF_BLK_SIZE;
    } else if (nor->info->flag & SUPPORT_4K_ERASE_BLK) {
        nor->blk_size = NOR_PAGE_SIZE;
    } else {
        SPINOR_ERR("invalid blk size");
        ret = -EINVAL;
        goto err;
    }
#endif

    /* program property */
    nor->w_cmd_slen = nor->addr_width == 4 ? 5 : 4;
    nor->cmd_write = cmd_4bytes(NOR_CMD_PROG);
    if (nor->info->flag & SUPPORT_QUAD_WRITE) {
        nor->cmd_write = cmd_4bytes(NOR_CMD_QUAD_PROG);
        if (nor->info->flag & USE_IO_PROG_X4) {
            nor->cmd_write = cmd_4bytes(NOR_CMD_QUAD_IO_PROG);
            nor->w_cmd_slen = 1;
        }
    }

    /* read property */
    nor->r_cmd_slen = nor->addr_width == 4 ? 6 : 5;
    nor->cmd_read = cmd_4bytes(NOR_CMD_FAST_READ);
    if (nor->info->flag & SUPPORT_QUAD_READ) {
        nor->cmd_read = cmd_4bytes(NOR_CMD_QUAD_READ);
        if (nor->info->flag & USE_IO_READ_X4) {
            nor->cmd_read = cmd_4bytes(NOR_CMD_QUAD_IO_READ);
            nor->r_cmd_slen = 1;
        }
    } else if (nor->info->flag & SUPPORT_DUAL_READ) {
        nor->cmd_read = cmd_4bytes(NOR_CMD_DUAL_READ);
        if (nor->info->flag & USE_IO_READ_X2) {
            nor->cmd_read = cmd_4bytes(NOR_CMD_DUAL_IO_READ);
            nor->r_cmd_slen = 1;
        }
    }

    if (cmd_bit(nor->cmd_read) == 4 || cmd_bit(nor->cmd_write) == 4) {
        ret = nor_set_quad_mode();
        if (ret) {
            SPINOR_ERR("enable quad mode failed");
            goto err;
        }
    }

    return 0;
err:
    SPINOR_ERR("scan nor flash failed");
    nor->info = NULL;
    return ret;
}

int nor_init(void)
{
    int ret = -1;

    if (nor->info)
        return 0;

    ret = nor_lock_init();
    if (ret) {
        SPINOR_ERR("create hal_sem lock for nor_flash failed");
        goto out;
    }

    nor_lock();

    ret = nor_spi_master_init(&nor->spim);
    if (ret)
        goto unlock;

    ret = nor_reset();
    if (ret)
        goto unlock;

    ret = nor_factory_register();
    if (ret)
        goto unlock;

    ret = nor_scan();
    if (ret)
        goto unlock;

    ret = nor_factory_init();
    if (ret) {
        SPINOR_ERR("factory init failed");
        goto unlock;
    }

    SPINOR_INFO("Nor Flash %s size %uMB write %dbit read %dbit blk size %uKB",
            nor->info->model, nor->total_size / 1024 / 1024,
            cmd_bit(nor->cmd_write), cmd_bit(nor->cmd_read), nor->blk_size / 1024);
    SPINOR_INFO("Nor Flash ID (hex): %02x %02x %02x", nor->info->id[0],
            nor->info->id[1], nor->info->id[2]);

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    ret = nor_wr_lock_init(nor);
    if (ret) {
        SPINOR_ERR("write lock init failed");
        goto unlock;
    }

    /* ensure all block is locked default */
    ret = nor_wr_lock_all(nor);
    if (ret) {
        SPINOR_ERR("write lock all failed");
        goto unlock;
    }
#endif

#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    ret = nor_cache_init(nor);
    if (ret) {
        SPINOR_ERR("cache init failed");
        goto unlock;
    }
#endif

    ret = 0;
unlock:
    nor_unlock();
out:
    if (ret)
        SPINOR_ERR("init nor flash failed");
    else
        SPINOR_INFO("nor flash init ok");
    return ret;
}

int nor_deinit(void)
{
    if (!nor->info)
        return -EBUSY;

    if (nor_lock()) {
        SPINOR_ERR("deinit: lock nor failed");
        return -EBUSY;
    }

#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    nor_cache_exit();
#endif

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    nor_wr_unlock_all(nor);
#endif

    if (nor->info) {
        if (nor->addr_width == 4)
            nor_set_4byte(0);
        nor_spi_master_deinit(&nor->spim);
    nor->info = NULL;
    }

    /* we do not unlock nor in case other task using nor after deinit */
    return 0;
}

static int nor_erase_do(char cmd, unsigned int addr)
{
    int ret = -EBUSY;
    char tbuf[5] = {0};
    int cmdlen;

    ret = nor_write_enable();
    if (ret)
        goto out;

    tbuf[0] = cmd;
    if (nor->addr_width == 4) {
        tbuf[1] = addr >> 24;
        tbuf[2] = addr >> 16;
        tbuf[3] = addr >> 8;
        tbuf[4] = addr & 0xFF;
        cmdlen = 5;
    } else {
        tbuf[1] = addr >> 16;
        tbuf[2] = addr >> 8;
        tbuf[3] = addr & 0xFF;
        cmdlen = 4;
    }

    ret = nor_transfer(cmdlen, tbuf, cmdlen, NULL, 0);
out:
    if (ret)
        SPINOR_ERR("erase address 0x%x with cmd 0x%x failed\n", addr, cmd);
    return ret;
}

static inline int nor_erase_4k(unsigned int addr)
{
    int ret;

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    ret = nor_wr_unlock(nor, addr, SZ_4K);
    if (ret)
        return -1;
#endif

    ret = nor_erase_do(cmd_4bytes(NOR_CMD_ERASE_BLK4K), addr);
    if (ret)
        goto out;

    ret = nor_wait_ready(30, MAX_WAIT_LOOP);
out:
#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    nor_wr_lock_all(nor);
#endif
    return ret;
}

static inline int nor_erase_32k(unsigned int addr)
{
    int ret;

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    ret = nor_wr_unlock(nor, addr, SZ_32K);
    if (ret)
        return -1;
#endif

    ret = nor_erase_do(cmd_4bytes(NOR_CMD_ERASE_BLK32K), addr);
    if (ret)
        goto out;

    ret = nor_wait_ready(120, MAX_WAIT_LOOP);
out:
#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    nor_wr_lock_all(nor);
#endif
    return ret;
}

static inline int nor_erase_64k(unsigned int addr)
{
    int ret;

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    ret = nor_wr_unlock(nor, addr, SZ_64K);
    if (ret)
        return -1;
#endif

    ret = nor_erase_do(cmd_4bytes(NOR_CMD_ERASE_BLK64K), addr);
    if (ret)
        goto out;

    ret = nor_wait_ready(150, MAX_WAIT_LOOP);
out:
#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    nor_wr_lock_all(nor);
#endif
    return ret;
}

static inline int nor_erase_all(void)
{
    int ret;

    if (!nor->info)
        return -EBUSY;

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    nor_wr_unlock_all(nor);
#endif

    ret = nor_write_enable();
    if (ret)
        goto out;

    ret = nor_send_cmd(NOR_CMD_ERASE_CHIP);
    if (ret)
        goto out;

    ret = nor_wait_ready(26 * 1000, MAX_WAIT_LOOP);
out:
#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
    nor_wr_lock_all(nor);
#endif
    return ret;
}

int nor_erase(unsigned int addr, unsigned int size)
{
    int ret;
    struct nor_info *info = nor->info;

    ret = nor_lock();
    if (ret) {
        SPINOR_ERR("erase: lock nor failed\n");
        return ret;
    }

    ret = -EBUSY;
    if (!nor->info)
        goto unlock;

    /*
     * nor erase size can be 4k/32k/64k, driver should erase block size base
     * on given size. Here must be align to 4k
     */
    if (size % SZ_4K) {
        SPINOR_ERR("erase size 4k is not align to %u\n", size);
        ret = -EINVAL;
        goto unlock;
    }

    if (addr + size > nor->total_size) {
        SPINOR_ERR("addr 0x%x with size %u over total size %u\n",
                addr, size, nor->total_size);
        ret = -EINVAL;
        goto unlock;
    }

    SPINOR_DEBUG("try to erase addr 0x%x with size %u\n", addr, size);

    if (addr == 0 && size == nor->total_size) {
        ret = nor_erase_all();
        goto unlock;
    }

    while (size) {

        if ((size >= SZ_64K) &&
                        (addr % SZ_64K == 0) &&
                        (info->flag & SUPPORT_64K_ERASE_BLK) &&
                        !(info->flag & USE_4K_ERASE)) {
            SPINOR_DEBUG("try to erase 64k from 0x%x\n", addr);
            ret = nor_erase_64k(addr);
            if (ret)
                goto unlock;
            addr += SZ_64K;
            size -= SZ_64K;
            continue;
        }

        if ((size >= SZ_32K) &&
                        (addr % SZ_32K == 0) &&
                        (info->flag & SUPPORT_32K_ERASE_BLK) &&
                        !(info->flag & USE_4K_ERASE)) {
            SPINOR_DEBUG("try to erase 32k from 0x%x\n", addr);
            ret = nor_erase_32k(addr);
            if (ret)
                goto unlock;
            addr += SZ_32K;
            size -= SZ_32K;
            continue;
        }

        if ((size >= SZ_4K) &&
                        (addr % SZ_4K == 0) &&
                        (info->flag & SUPPORT_4K_ERASE_BLK)) {
            SPINOR_DEBUG("try to erase 4k from 0x%x\n", addr);
            ret = nor_erase_4k(addr);
            if (ret)
                goto unlock;
            addr += SZ_4K;
            size -= SZ_4K;
            continue;
        }

        SPINOR_ERR("no erase cmd matched, addr 0x%x, size 0x%x flag:0x%x\n",
                        addr, size, info->flag);
        break;
    }

    ret = size ? -EINVAL : 0;
unlock:
    nor_unlock();
    return ret;
}

static int nor_read_do(unsigned int addr, char *buf, unsigned int len)
{
    char cmd[5] = {0};
    int cmdlen;

    if (len > NOR_PAGE_SIZE)
        return -EINVAL;

    cmd[0] = nor->cmd_read;
    if (nor->addr_width == 4) {
        cmd[1] = addr >> 24;
        cmd[2] = addr >> 16;
        cmd[3] = addr >> 8;
        cmd[4] = addr & 0xFF;
        cmdlen = 5;
    } else {
        cmd[1] = addr >> 16;
        cmd[2] = addr >> 8;
        cmd[3] = addr & 0xFF;
        cmdlen = 4;
    }
    return nor_transfer(nor->r_cmd_slen, cmd, cmdlen, buf, len);
}

int nor_read(unsigned int addr, char *buf, unsigned int len)
{
    int ret;

    ret = nor_lock();
    if (ret) {
        SPINOR_ERR("read: lock nor failed\n");
        goto out;
    }

    ret = -EBUSY;
    if (!nor->info)
        goto unlock;

//    SPINOR_DEBUG("try to read addr 0x%x with len %u\n", addr, len);

    if (nor_wait_ready(0, 500))
        goto unlock;

    while (len) {
        unsigned int align_addr = ALIGN(addr + 1, NOR_PAGE_SIZE);
        unsigned int rlen = MIN(align_addr - addr, len);

        ret = nor_read_do(addr, buf, rlen);
        if (ret)
            goto unlock;

        addr += rlen;
        buf += rlen;
        len -= rlen;
    }

unlock:
    nor_unlock();
out:
    if (ret)
        SPINOR_ERR("read address 0x%x with len %u failed\n", addr, len);
    return ret;
}

static int nor_write_do(unsigned int addr, char *buf, unsigned int len)
{
    int ret = -EINVAL;
    char tbuf[NOR_PAGE_SIZE + 5] = {0};
    int cmdlen;

    if (len > NOR_PAGE_SIZE)
        return -EINVAL;

    ret = nor_write_enable();
    if (ret)
        return ret;

    if (nor->addr_width == 4) {
        tbuf[0] = nor->cmd_write;
        tbuf[1] = addr >> 24;
        tbuf[2] = addr >> 16;
        tbuf[3] = addr >> 8;
        tbuf[4] = addr & 0xFF;
        cmdlen = 5;
    } else {
        tbuf[0] = nor->cmd_write;
        tbuf[1] = addr >> 16;
        tbuf[2] = addr >> 8;
        tbuf[3] = addr & 0xFF;
        cmdlen = 4;
    }

    memcpy(tbuf + cmdlen, buf, MIN(len, (unsigned int)NOR_PAGE_SIZE));
    ret = nor_transfer(nor->w_cmd_slen, tbuf, len + cmdlen, NULL, 0);
    if (ret)
        return ret;

    return nor_wait_ready(0, 100 * 1000);
}

int nor_write(unsigned int addr, char *buf, unsigned int len)
{
    int ret;

    ret = nor_lock();
    if (ret) {
        SPINOR_ERR("write: lock nor failed\n");
        goto out;
    }

    ret = -EBUSY;
    if (!nor->info)
        goto unlock;

    SPINOR_DEBUG("try to write addr 0x%x with len %u\n", addr, len);

    if (nor_wait_ready(0, 500))
        goto unlock;

    while (len) {
        unsigned int align_addr = ALIGN(addr + 1, NOR_PAGE_SIZE);
        unsigned int wlen = MIN(align_addr - addr, len);

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
        ret = nor_wr_unlock(nor, addr, len);
        if (ret)
            goto unlock;
#endif

        ret = nor_write_do(addr, buf, wlen);
        if (ret)
            goto unlock;

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
        ret = nor_wr_lock_all(nor);
        if (ret)
            goto unlock;
#endif

        addr += wlen;
        buf += wlen;
        len -= wlen;
    }

unlock:
    nor_unlock();
out:
    if (ret)
        SPINOR_ERR("write address 0x%x with len %u failed\n", addr, len);
    return ret;
}

struct nor_flash *get_nor_flash(void)
{
    return nor;
}
