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
#include <drivers/byteorder.h>

#define DBG_TAG "mtd.cfi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "mtd-cfi.h"

struct cfi_flash_device
{
    struct rt_mtd_nor_device parent;

    struct rt_mutex rw_lock;

    rt_ubase_t sect[CFI_FLASH_SECT_MAX];
    rt_ubase_t protect[CFI_FLASH_SECT_MAX];
    rt_size_t sect_count;

    rt_uint8_t portwidth;
    rt_uint8_t chipwidth;
    rt_uint8_t chip_lsb;
    rt_uint8_t cmd_reset;
    rt_uint8_t cmd_erase_sector;
    rt_uint8_t sr_supported;
    rt_uint16_t ext_addr;
    rt_uint16_t version;
    rt_uint16_t offset;
    rt_uint16_t vendor;
    rt_uint16_t device_id;
    rt_uint16_t device_ext_id;
    rt_uint16_t manufacturer_id;
    rt_uint16_t interface;
    rt_ubase_t addr_unlock1;
    rt_ubase_t addr_unlock2;
    rt_ubase_t write_tout;
    rt_ubase_t erase_blk_tout;
    rt_size_t size;
};
#define raw_to_cfi_flash_device(raw)   rt_container_of(raw, struct cfi_flash_device, parent)

struct cfi_flash
{
    int count;
    struct cfi_flash_device dev[];
};

#define __get_unaligned_t(type, ptr)                                    \
({                                                                      \
    const rt_packed(struct { type x; }) *_ptr = (typeof(_ptr))(ptr);    \
    _ptr->x;                                                            \
})

#define __put_unaligned_t(type, val, ptr)                               \
do {                                                                    \
    rt_packed(struct { type x; }) *_ptr = (typeof(_ptr))(ptr);          \
    _ptr->x = (val);                                                    \
} while (0)

#define get_unaligned(ptr)      __get_unaligned_t(typeof(*(ptr)), (ptr))
#define put_unaligned(val, ptr) __put_unaligned_t(typeof(*(ptr)), (val), (ptr))

static rt_uint32_t cfi_flash_offset[2] = { FLASH_OFFSET_CFI, FLASH_OFFSET_CFI_ALT };

rt_inline void *cfi_flash_map(struct cfi_flash_device *fdev, rt_off_t sect, rt_off_t offset)
{
    rt_off_t byte_offset = offset * fdev->portwidth;

    return (void *)(fdev->sect[sect] + (byte_offset << fdev->chip_lsb));
}

rt_inline void cfi_flash_write8(void *addr, rt_uint8_t value)
{
    HWREG8(addr) = value;
}

rt_inline void cfi_flash_write16(void *addr, rt_uint16_t value)
{
    HWREG16(addr) = value;
}

rt_inline void cfi_flash_write32(void *addr, rt_uint32_t value)
{
    HWREG32(addr) = value;
}

rt_inline void cfi_flash_write64(void *addr, rt_uint64_t value)
{
    HWREG64(addr) = value;
}

rt_inline rt_uint8_t cfi_flash_read8(void *addr)
{
    return HWREG8(addr);
}

rt_inline rt_uint16_t cfi_flash_read16(void *addr)
{
    return HWREG16(addr);
}

rt_inline rt_uint32_t cfi_flash_read32(void *addr)
{
    return HWREG32(addr);
}

rt_inline rt_uint64_t cfi_flash_read64(void *addr)
{
    return HWREG64(addr);
}

rt_inline rt_uint8_t cfi_flash_read_byte(struct cfi_flash_device *fdev, rt_off_t offset)
{
    unsigned char *cp, value;

    cp = cfi_flash_map(fdev, 0, offset);

#ifndef ARCH_CPU_BIG_ENDIAN
    value = cfi_flash_read8(cp);
#else
    value = cfi_flash_read8(cp + fdev->portwidth - 1);
#endif

    return value;
}

rt_inline rt_uint16_t cfi_flash_read_word(struct cfi_flash_device *fdev, rt_off_t offset)
{
    rt_uint16_t *addr, value;

    addr = cfi_flash_map(fdev, 0, offset);
    value = cfi_flash_read16(addr);

    return value;
}

static void cfi_flash_make_cmd(struct cfi_flash_device *fdev, rt_uint32_t cmd, void *cmdbuf)
{
    int cword_offset, cp_offset;
    rt_uint8_t val, *cp = (rt_uint8_t *)cmdbuf;

#ifndef ARCH_CPU_BIG_ENDIAN
    cmd = rt_cpu_to_le32(cmd);
#endif

    for (int i = fdev->portwidth; i > 0; --i)
    {
        cword_offset = (fdev->portwidth - i) % fdev->chipwidth;

#ifndef ARCH_CPU_BIG_ENDIAN
        cp_offset = fdev->portwidth - i;
        val = *((rt_uint8_t *)&cmd + cword_offset);
#else
        cp_offset = i - 1;
        val = *((rt_uint8_t *)&cmd + sizeof(rt_uint32_t) - cword_offset - 1);
#endif
        cp[cp_offset] = (cword_offset >= sizeof(rt_uint32_t)) ? 0x00 : val;
    }
}

static void cfi_flash_write_cmd(struct cfi_flash_device *fdev,
        rt_off_t sect, rt_off_t offset, rt_uint32_t cmd)
{
    void *addr;
    union cfi_word word;

    addr = cfi_flash_map(fdev, sect, offset);
    cfi_flash_make_cmd(fdev, cmd, &word);

    switch (fdev->portwidth)
    {
    case FLASH_CFI_8BIT:
        cfi_flash_write8(addr, word.w8);
        break;

    case FLASH_CFI_16BIT:
        cfi_flash_write16(addr, word.w16);
        break;

    case FLASH_CFI_32BIT:
        cfi_flash_write32(addr, word.w32);
        break;

    case FLASH_CFI_64BIT:
        cfi_flash_write64(addr, word.w64);
        break;
    }

    rt_hw_isb();
}

static void cfi_flash_unlock_seq(struct cfi_flash_device *fdev, rt_off_t sect)
{
    cfi_flash_write_cmd(fdev, sect, fdev->addr_unlock1, AMD_CMD_UNLOCK_START);
    cfi_flash_write_cmd(fdev, sect, fdev->addr_unlock2, AMD_CMD_UNLOCK_ACK);
}

static rt_off_t cfi_flash_find(struct cfi_flash_device *fdev, rt_ubase_t addr)
{
    rt_off_t sect = 0;

    while (sect < fdev->sect_count - 1 && fdev->sect[sect] < addr)
    {
        sect++;
    }

    while (fdev->sect[sect] > addr && sect > 0)
    {
        sect--;
    }

    return sect;
}

static rt_bool_t cfi_flash_isequal(struct cfi_flash_device *fdev,
        rt_off_t sect, rt_off_t offset, rt_uint32_t cmd)
{
    void *addr;
    union cfi_word word;

    addr = cfi_flash_map(fdev, sect, offset);
    cfi_flash_make_cmd(fdev, cmd, &word);

    switch (fdev->portwidth)
    {
    case FLASH_CFI_8BIT:
        return cfi_flash_read8(addr) == word.w8;

    case FLASH_CFI_16BIT:
        return cfi_flash_read16(addr) == word.w16;

    case FLASH_CFI_32BIT:
        return cfi_flash_read32(addr) == word.w32;

    case FLASH_CFI_64BIT:
        return cfi_flash_read64(addr) == word.w64;

    default:
        break;
    }

    return RT_FALSE;
}

static void cfi_flash_add_byte(struct cfi_flash_device *fdev,
        union cfi_word *word, rt_uint8_t c)
{
#ifndef ARCH_CPU_BIG_ENDIAN
    rt_uint16_t w;
    rt_uint32_t l;
    rt_uint64_t ll;
#endif

    switch (fdev->portwidth)
    {
    case FLASH_CFI_8BIT:
        word->w8 = c;
        break;

    case FLASH_CFI_16BIT:
    #ifndef ARCH_CPU_BIG_ENDIAN
        w = c;
        w <<= 8;
        word->w16 = (word->w16 >> 8) | w;
    #else
        word->w16 = (word->w16 << 8) | c;
    #endif
        break;

    case FLASH_CFI_32BIT:
    #ifndef ARCH_CPU_BIG_ENDIAN
        l = c;
        l <<= 24;
        word->w32 = (word->w32 >> 8) | l;
    #else
        word->w32 = (word->w32 << 8) | c;
    #endif
        break;

    case FLASH_CFI_64BIT:
    #ifndef ARCH_CPU_BIG_ENDIAN
        ll = c;
        ll <<= 56;
        word->w64 = (word->w64 >> 8) | ll;
    #else
        word->w64 = (word->w64 << 8) | c;
    #endif
        break;
    }
}

static rt_bool_t cfi_flash_isset(struct cfi_flash_device *fdev,
        rt_off_t sect, rt_off_t offset, rt_uint8_t cmd)
{
    rt_bool_t res;
    rt_uint8_t *addr;
    union cfi_word word;

    addr = cfi_flash_map(fdev, sect, offset);
    cfi_flash_make_cmd(fdev, cmd, &word);

    switch (fdev->portwidth)
    {
    case FLASH_CFI_8BIT:
        res = (cfi_flash_read8(addr) & word.w8) == word.w8;
        break;

    case FLASH_CFI_16BIT:
        res = (cfi_flash_read16(addr) & word.w16) == word.w16;
        break;

    case FLASH_CFI_32BIT:
        res = (cfi_flash_read32(addr) & word.w32) == word.w32;
        break;

    case FLASH_CFI_64BIT:
        res = (cfi_flash_read64(addr) & word.w64) == word.w64;
        break;

    default:
        res = RT_FALSE;
        break;
    }

    return res;
}

static rt_bool_t cfi_flash_toggle(struct cfi_flash_device *fdev,
        rt_off_t sect, rt_off_t offset, rt_uint8_t cmd)
{
    rt_bool_t res;
    rt_uint8_t *addr;
    union cfi_word word;

    addr = cfi_flash_map(fdev, sect, offset);
    cfi_flash_make_cmd(fdev, cmd, &word);

    switch (fdev->portwidth)
    {
    case FLASH_CFI_8BIT:
        res = cfi_flash_read8(addr) != cfi_flash_read8(addr);
        break;

    case FLASH_CFI_16BIT:
        res = cfi_flash_read16(addr) != cfi_flash_read16(addr);
        break;

    case FLASH_CFI_32BIT:
        res = cfi_flash_read32(addr) != cfi_flash_read32(addr);
        break;

    case FLASH_CFI_64BIT:
        res = cfi_flash_read32(addr) != cfi_flash_read32(addr) ||
              cfi_flash_read32(addr + 4) != cfi_flash_read32(addr + 4);
        break;

    default:
        res = RT_FALSE;
        break;
    }

    return res;
}

static rt_bool_t cfi_flash_is_busy(struct cfi_flash_device *fdev, rt_off_t sect)
{
    switch (fdev->vendor)
    {
    case CFI_CMDSET_INTEL_PROG_REGIONS:
    case CFI_CMDSET_INTEL_STANDARD:
    case CFI_CMDSET_INTEL_EXTENDED:
        return !cfi_flash_isset(fdev, sect, 0, FLASH_STATUS_DONE);

    case CFI_CMDSET_AMD_STANDARD:
    case CFI_CMDSET_AMD_EXTENDED:
        if (fdev->sr_supported)
        {
            cfi_flash_write_cmd(fdev, sect, fdev->addr_unlock1, FLASH_CMD_READ_STATUS);

            return !cfi_flash_isset(fdev, sect, 0, FLASH_STATUS_DONE);
        }
        else
        {
            return cfi_flash_toggle(fdev, sect, 0, AMD_STATUS_TOGGLE);
        }

    default:
        break;
    }

    return RT_FALSE;
}

static rt_err_t cfi_flash_status_check(struct cfi_flash_device *fdev,
        rt_off_t sect, rt_ubase_t tout)
{
    rt_tick_t tick;

    tick = rt_tick_from_millisecond(rt_max_t(rt_ubase_t, tout / 1000, 1));
    tick += rt_tick_get();

    while (cfi_flash_is_busy(fdev, sect))
    {
        if (rt_tick_get() > tick)
        {
            cfi_flash_write_cmd(fdev, sect, 0, fdev->cmd_reset);
            rt_hw_us_delay(1);

            return -RT_ETIMEOUT;
        }

        rt_hw_us_delay(1);
    }

    return RT_EOK;
}

static rt_err_t cfi_flash_full_status_check(struct cfi_flash_device *fdev,
        rt_off_t sect, rt_ubase_t tout)
{
    rt_err_t err;

    err = cfi_flash_status_check(fdev, sect, tout);

    switch (fdev->vendor)
    {
    case CFI_CMDSET_INTEL_PROG_REGIONS:
    case CFI_CMDSET_INTEL_EXTENDED:
    case CFI_CMDSET_INTEL_STANDARD:
        cfi_flash_write_cmd(fdev, sect, 0, fdev->cmd_reset);
        rt_hw_us_delay(1);
        break;

    default:
        break;
    }

    return err;
}

static rt_err_t cfi_flash_write_word(struct cfi_flash_device *fdev,
        rt_ubase_t dest, union cfi_word word)
{
    int flag;
    void *dstaddr;
    rt_off_t sect = 0;
    rt_bool_t sect_found = RT_FALSE;

    dstaddr = (void *)dest;

    /* Check if Flash is (sufficiently) erased */
    switch (fdev->portwidth)
    {
    case FLASH_CFI_8BIT:
        flag = (cfi_flash_read8(dstaddr) & word.w8) == word.w8;
        break;

    case FLASH_CFI_16BIT:
        flag = (cfi_flash_read16(dstaddr) & word.w16) == word.w16;
        break;

    case FLASH_CFI_32BIT:
        flag = (cfi_flash_read32(dstaddr) & word.w32) == word.w32;
        break;

    case FLASH_CFI_64BIT:
        flag = (cfi_flash_read64(dstaddr) & word.w64) == word.w64;
        break;

    default:
        flag = 0;
        break;
    }

    if (!flag)
    {
        return -RT_EIO;
    }

    switch (fdev->vendor)
    {
    case CFI_CMDSET_INTEL_PROG_REGIONS:
    case CFI_CMDSET_INTEL_EXTENDED:
    case CFI_CMDSET_INTEL_STANDARD:
        cfi_flash_write_cmd(fdev, 0, 0, FLASH_CMD_CLEAR_STATUS);
        cfi_flash_write_cmd(fdev, 0, 0, FLASH_CMD_WRITE);
        break;

    case CFI_CMDSET_AMD_EXTENDED:
    case CFI_CMDSET_AMD_STANDARD:
        sect = cfi_flash_find(fdev, dest);
        cfi_flash_unlock_seq(fdev, sect);
        cfi_flash_write_cmd(fdev, sect, fdev->addr_unlock1, AMD_CMD_WRITE);
        sect_found = RT_TRUE;
        break;
    }

    switch (fdev->portwidth)
    {
    case FLASH_CFI_8BIT:
        cfi_flash_write8(dstaddr, word.w8);
        break;

    case FLASH_CFI_16BIT:
        cfi_flash_write16(dstaddr, word.w16);
        break;

    case FLASH_CFI_32BIT:
        cfi_flash_write32(dstaddr, word.w32);
        break;

    case FLASH_CFI_64BIT:
        cfi_flash_write64(dstaddr, word.w64);
        break;
    }

    if (!sect_found)
    {
        sect = cfi_flash_find(fdev, dest);
    }

    return cfi_flash_full_status_check(fdev, sect, fdev->write_tout);
}

static rt_err_t cfi_flash_read_id(struct rt_mtd_nor_device *dev)
{
    struct cfi_flash_device *fdev = raw_to_cfi_flash_device(dev);

    return fdev->device_id;
}

static rt_ssize_t cfi_flash_read(struct rt_mtd_nor_device *dev, rt_off_t offset, rt_uint8_t *data, rt_size_t length)
{
    struct cfi_flash_device *fdev = raw_to_cfi_flash_device(dev);

    rt_mutex_take(&fdev->rw_lock, RT_WAITING_FOREVER);

    rt_memcpy(data, (void *)fdev->sect[0] + offset, length);

    rt_mutex_release(&fdev->rw_lock);

    return length;
}

static rt_ssize_t cfi_flash_write(struct rt_mtd_nor_device *dev, rt_off_t offset,
        const rt_uint8_t *data, rt_size_t length)
{
    int i;
    rt_ubase_t wp;
    rt_uint8_t *ptr;
    rt_ssize_t res;
    rt_size_t size, written = 0, tail_written = 0;
    union cfi_word word;
    struct cfi_flash_device *fdev = raw_to_cfi_flash_device(dev);

    rt_mutex_take(&fdev->rw_lock, RT_WAITING_FOREVER);

    offset += fdev->sect[0];
    wp = offset & ~(fdev->portwidth - 1);
    size = offset - wp;

    if (size)
    {
        rt_size_t head_written = 0;

        word.w32 = 0;
        ptr = (rt_uint8_t *)wp;

        for (i = 0; i < size; ++i)
        {
            cfi_flash_add_byte(fdev, &word, cfi_flash_read8(ptr + i));
        }

        for (; i < fdev->portwidth && length > 0; ++i)
        {
            cfi_flash_add_byte(fdev, &word, *data++);
            --length;
            ++head_written;
        }

        for (; !length && i < fdev->portwidth; ++i)
        {
            cfi_flash_add_byte(fdev, &word, cfi_flash_read8(ptr + i));
        }

        if ((res = cfi_flash_write_word(fdev, wp, word)))
        {
            goto _out_lock;
        }

        written += head_written;
        wp += i;
    }

    /* Handle the aligned part */
    while (length >= fdev->portwidth)
    {
        word.w32 = 0;

        for (i = 0; i < fdev->portwidth; ++i)
        {
            cfi_flash_add_byte(fdev, &word, *data++);
        }

        if ((res = cfi_flash_write_word(fdev, wp, word)))
        {
            goto _out_lock;
        }

        wp += fdev->portwidth;
        length -= fdev->portwidth;
        written += fdev->portwidth;  /* new: accumulate bytes */
    }

    if (!length)
    {
        res = written;
        goto _out_lock;
    }

    /* Handle unaligned tail bytes */
    word.w32 = 0;
    ptr = (rt_uint8_t *)wp;

    for (i = 0; i < fdev->portwidth && length > 0; ++i)
    {
        cfi_flash_add_byte(fdev, &word, *data++);
        --length;
        ++tail_written;
    }

    for (; i < fdev->portwidth; ++i)
    {
        cfi_flash_add_byte(fdev, &word, cfi_flash_read8(ptr + i));
    }

    if ((res = cfi_flash_write_word(fdev, wp, word)))
    {
        goto _out_lock;
    }

    written += tail_written;
    res = written;

_out_lock:
    rt_mutex_release(&fdev->rw_lock);

    return res;
}

static rt_err_t cfi_flash_erase_block(struct rt_mtd_nor_device *dev,
        rt_off_t offset, rt_size_t length)
{
    rt_err_t err = RT_EOK;
    rt_ubase_t sect, sect_end;
    struct cfi_flash_device *fdev = raw_to_cfi_flash_device(dev);

    rt_mutex_take(&fdev->rw_lock, RT_WAITING_FOREVER);

    sect = cfi_flash_find(fdev, fdev->sect[0] + offset);
    sect_end = cfi_flash_find(fdev, fdev->sect[0] + offset + length);

    for (; sect <= sect_end; ++sect)
    {
        if (fdev->protect[sect])
        {
            continue;
        }

        switch (fdev->vendor)
        {
        case CFI_CMDSET_INTEL_PROG_REGIONS:
        case CFI_CMDSET_INTEL_STANDARD:
        case CFI_CMDSET_INTEL_EXTENDED:
            cfi_flash_write_cmd(fdev, sect, 0, FLASH_CMD_CLEAR_STATUS);
            cfi_flash_write_cmd(fdev, sect, 0, FLASH_CMD_BLOCK_ERASE);
            cfi_flash_write_cmd(fdev, sect, 0, FLASH_CMD_ERASE_CONFIRM);
            break;

        case CFI_CMDSET_AMD_STANDARD:
        case CFI_CMDSET_AMD_EXTENDED:
            cfi_flash_unlock_seq(fdev, sect);
            cfi_flash_write_cmd(fdev, sect, fdev->addr_unlock1, AMD_CMD_ERASE_START);
            cfi_flash_unlock_seq(fdev, sect);
            cfi_flash_write_cmd(fdev, sect, 0, fdev->cmd_erase_sector);
            break;

        default:
            break;
        }

        err = cfi_flash_full_status_check(fdev, sect, fdev->erase_blk_tout);
    }

    rt_mutex_release(&fdev->rw_lock);

    return err;
}

const static struct rt_mtd_nor_driver_ops cfi_flash_ops =
{
    .read_id = cfi_flash_read_id,
    .read = cfi_flash_read,
    .write = cfi_flash_write,
    .erase_block = cfi_flash_erase_block,
};

static rt_bool_t cfi_flash_detect_info(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    rt_uint8_t *buffer;

    /* Reset, unknown reset's cmd now, so try Intel and AMD both. */
    cfi_flash_write_cmd(fdev, 0, 0, AMD_CMD_RESET);
    rt_hw_us_delay(1);
    cfi_flash_write_cmd(fdev, 0, 0, FLASH_CMD_RESET);

    for (int i = 0; i < RT_ARRAY_SIZE(cfi_flash_offset); ++i)
    {
        cfi_flash_write_cmd(fdev, 0, cfi_flash_offset[i], FLASH_CMD_CFI);

        if (cfi_flash_isequal(fdev, 0, FLASH_OFFSET_CFI_RESP, 'Q') &&
            cfi_flash_isequal(fdev, 0, FLASH_OFFSET_CFI_RESP + 1, 'R') &&
            cfi_flash_isequal(fdev, 0, FLASH_OFFSET_CFI_RESP + 2, 'Y'))
        {
            buffer = (void *)query;

            for (int byte = 0; byte < sizeof(*query); ++byte)
            {
                buffer[byte] = cfi_flash_read_byte(fdev, FLASH_OFFSET_CFI_RESP + byte);
            }

            fdev->interface = rt_le16_to_cpu(query->interface_desc);

            /*
             * Some flash chips can support multiple bus widths.
             * In this case, override the interface width and
             * limit it to the port width.
             */
            if (fdev->interface == FLASH_CFI_X8X16 &&
                fdev->portwidth == FLASH_CFI_8BIT)
            {
                fdev->interface = FLASH_CFI_X8;
            }
            else if (fdev->interface == FLASH_CFI_X16X32 &&
                     fdev->portwidth == FLASH_CFI_16BIT)
            {
                fdev->interface = FLASH_CFI_X16;
            }

            fdev->offset = cfi_flash_offset[i];

            fdev->addr_unlock1 = 0x555;
            fdev->addr_unlock2 = 0x2aa;

            /* modify the unlock address if we are in compatibility mode */
            if ((fdev->chipwidth == FLASH_CFI_BY8 &&    /* x8/x16 in x8 mode */
                fdev->interface == FLASH_CFI_X8X16) ||
                (fdev->chipwidth == FLASH_CFI_BY16 &&   /* x16/x32 in x16 mode */
                fdev->interface == FLASH_CFI_X16X32))
            {
                fdev->addr_unlock1 = 0xaaa;
                fdev->addr_unlock2 = 0x555;
            }

            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_bool_t cfi_flash_detect(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    for (fdev->portwidth = FLASH_CFI_8BIT;
         fdev->portwidth <= FLASH_CFI_64BIT;
         fdev->portwidth <<= 1)
    {
        for (fdev->chipwidth = FLASH_CFI_BY8;
             fdev->chipwidth <= fdev->portwidth;
             fdev->chipwidth <<= 1)
        {
            /*
             * First, try detection without shifting the addresses
             * for 8bit devices (16bit wide connection)
             */
            fdev->chip_lsb = 0;
            if (cfi_flash_detect_info(fdev, query))
            {
                return RT_TRUE;
            }

            /* Not detected, so let's try with shifting for 8bit devices */
            fdev->chip_lsb = 1;
            if (cfi_flash_detect_info(fdev, query))
            {
                return RT_TRUE;
            }
        }
    }

    return RT_FALSE;
}

static void cfi_cmdset_intel_init(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    fdev->cmd_reset = FLASH_CMD_RESET;

    /* Intel read jedec IDs */
    cfi_flash_write_cmd(fdev, 0, 0, FLASH_CMD_RESET);
    rt_hw_us_delay(1);

    cfi_flash_write_cmd(fdev, 0, 0, FLASH_CMD_READ_ID);
    rt_hw_us_delay(1000);

    fdev->manufacturer_id = cfi_flash_read_byte(fdev, FLASH_OFFSET_MANUFACTURER_ID);
    fdev->device_id = (fdev->chipwidth == FLASH_CFI_16BIT) ?
            cfi_flash_read_word(fdev, FLASH_OFFSET_DEVICE_ID) :
            cfi_flash_read_byte(fdev, FLASH_OFFSET_DEVICE_ID);
    cfi_flash_write_cmd(fdev, 0, 0, FLASH_CMD_RESET);

    /* Read end */
    cfi_flash_write_cmd(fdev, 0, fdev->offset, FLASH_CMD_CFI);
}

static void cfi_cmdset_amd_init(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    rt_uint16_t bank_id = 0;
    rt_uint8_t manu_id, feature;

    fdev->cmd_reset = AMD_CMD_RESET;
    fdev->cmd_erase_sector = AMD_CMD_ERASE_SECTOR;

    /* AMD read jedec IDs */
    cfi_flash_write_cmd(fdev, 0, 0, AMD_CMD_RESET);
    cfi_flash_unlock_seq(fdev, 0);
    cfi_flash_write_cmd(fdev, 0, fdev->addr_unlock1, FLASH_CMD_READ_ID);
    rt_hw_us_delay(1000);

    manu_id = cfi_flash_read_byte(fdev, FLASH_OFFSET_MANUFACTURER_ID);
    /* JEDEC JEP106Z specifies ID codes up to bank 7 */
    while (manu_id == FLASH_CONTINUATION_CODE && bank_id < 0x800)
    {
        bank_id += 0x100;
        manu_id = cfi_flash_read_byte(fdev, bank_id | FLASH_OFFSET_MANUFACTURER_ID);
    }
    fdev->manufacturer_id = manu_id;

    if (fdev->ext_addr && fdev->version >= 0x3134)
    {
        /* Read software feature (at 0x53) */
        feature = cfi_flash_read_byte(fdev, fdev->ext_addr + 0x13);
        fdev->sr_supported = feature & 0x1;
    }

    switch (fdev->chipwidth)
    {
    case FLASH_CFI_8BIT:
        fdev->device_id = cfi_flash_read_byte(fdev, FLASH_OFFSET_DEVICE_ID);

        if (fdev->device_id == 0x7e)
        {
            /* AMD 3-byte (expanded) device ids */
            fdev->device_ext_id = cfi_flash_read_byte(fdev, FLASH_OFFSET_DEVICE_ID2);
            fdev->device_ext_id <<= 8;
            fdev->device_ext_id |= cfi_flash_read_byte(fdev, FLASH_OFFSET_DEVICE_ID3);
        }
        break;

    case FLASH_CFI_16BIT:
        fdev->device_id = cfi_flash_read_word(fdev, FLASH_OFFSET_DEVICE_ID);

        if ((fdev->device_id & 0xff) == 0x7e)
        {
            /* AMD 3-byte (expanded) device ids */
            fdev->device_ext_id = cfi_flash_read_byte(fdev, FLASH_OFFSET_DEVICE_ID2);
            fdev->device_ext_id <<= 8;
            fdev->device_ext_id |= cfi_flash_read_byte(fdev, FLASH_OFFSET_DEVICE_ID3);
        }
        break;

    default:
        break;
    }

    cfi_flash_write_cmd(fdev, 0, 0, AMD_CMD_RESET);
    rt_hw_us_delay(1);

    /* Read end */
    cfi_flash_write_cmd(fdev, 0, fdev->offset, FLASH_CMD_CFI);
}

static void cfi_reverse_geometry(struct cfi_query *query)
{
    rt_uint32_t info;

    for (int i = 0, j = query->num_erase_regions - 1; i < j; ++i, --j)
    {
        info = get_unaligned(&query->erase_region_info[i]);

        put_unaligned(get_unaligned(&query->erase_region_info[j]),
                &query->erase_region_info[i]);

        put_unaligned(info, &query->erase_region_info[j]);
    }
}

static void cfi_flash_fixup_amd(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    /* check if flash geometry needs reversal */
    if (query->num_erase_regions > 1)
    {
        /* reverse geometry if top boot part */
        if (fdev->version < 0x3131)
        {
            /* CFI < 1.1, try to guess from device id */
            if ((fdev->device_id & 0x80) != 0)
            {
                cfi_reverse_geometry(query);
            }
        }
        else if (cfi_flash_read_byte(fdev, fdev->ext_addr + 0xf) == 3)
        {
            /*
             * CFI >= 1.1, deduct from top/bottom flag,
             * ext_addr is valid since cfi version > 0.
             */
            cfi_reverse_geometry(query);
        }
    }
}

static void cfi_flash_fixup_atmel(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    int reverse_geometry = 0;

    /* Check the "top boot" bit in the PRI */
    if (fdev->ext_addr && !(cfi_flash_read_byte(fdev, fdev->ext_addr + 6) & 1))
    {
        reverse_geometry = 1;
    }

    /*
     * AT49BV6416(T) list the erase regions in the wrong order.
     * However, the device ID is identical with the non-broken
     * AT49BV642D they differ in the high byte.
     */
    if (fdev->device_id == 0xd6 || fdev->device_id == 0xd2)
    {
        reverse_geometry = !reverse_geometry;
    }

    if (reverse_geometry)
    {
        cfi_reverse_geometry(query);
    }
}

static void cfi_flash_fixup_stm(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    /* Check if flash geometry needs reversal */
    if (query->num_erase_regions > 1)
    {
        /* Reverse geometry if top boot part */
        if (fdev->version < 0x3131)
        {
            /*
             * CFI < 1.1, guess by device id:
             * M29W320DT, M29W320ET, M29W800DT
             */
            if (fdev->device_id == 0x22ca ||
                fdev->device_id == 0x2256 ||
                fdev->device_id == 0x22d7)
            {
                cfi_reverse_geometry(query);
            }
        }
        else if (cfi_flash_read_byte(fdev, fdev->ext_addr + 0xf) == 3)
        {
            /*
             * CFI >= 1.1, deduct from top/bottom flag,
             * ext_addr is valid since cfi version > 0.
             */
            cfi_reverse_geometry(query);
        }
    }
}

static void cfi_flash_fixup_sst(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    /*
     * SST, for many recent nor parallel flashes, says they are
     * CFI-conformant. This is not true, since qry struct.
     * reports a std. AMD command set (0x0002), while SST allows to
     * erase two different sector sizes for the same memory.
     * 64KB sector (SST call it block)  needs 0x30 to be erased.
     * 4KB  sector (SST call it sector) needs 0x50 to be erased.
     * Since CFI query detect the 4KB number of sectors, users expects
     * a sector granularity of 4KB, and it is here set.
     */

    /* SST39VF3201B, SST39VF3202B */
    if (fdev->device_id == 0x5d23 || fdev->device_id == 0x5c23)
    {
        /* Set sector granularity to 4KB */
        fdev->cmd_erase_sector = 0x50;
    }
}

static void cfi_flash_fixup_num(struct cfi_flash_device *fdev, struct cfi_query *query)
{
    /*
     * The M29EW devices seem to report the CFI information wrong
     * when it's in 8 bit mode.
     * There's an app note from Numonyx on this issue.
     * So adjust the buffer size for M29EW while operating in 8-bit mode
     */
    if (query->max_buf_write_size > 0x8 && fdev->device_id == 0x7e &&
        (fdev->device_ext_id == 0x2201 || fdev->device_ext_id == 0x2301 ||
         fdev->device_ext_id == 0x2801 || fdev->device_ext_id == 0x4801))
    {
        query->max_buf_write_size = 0x8;
    }
}

static rt_err_t cfi_flash_dev_probe(struct rt_device *dev, struct cfi_flash_device *fdev, int index)
{
    rt_err_t err;
    int size_ratio;
    const char *name;
    rt_uint64_t addr, size;
    rt_ubase_t sect, value;
    rt_size_t max_size, sect_count;
    int num_erase_regions, erase_region_count, erase_region_size;
    struct cfi_query *query = rt_malloc(sizeof(*query));

    if (!query)
    {
        return -RT_ENOMEM;
    }

    if (rt_dm_dev_get_address(dev, index, &addr, &size) < 0)
    {
        err = -RT_EIO;
        goto _fail;
    }

    fdev->sect[0] = (rt_ubase_t)rt_ioremap((void *)addr, size);

    if (!cfi_flash_detect(fdev, query))
    {
        err = -RT_EEMPTY;
        goto _fail;
    }

    fdev->vendor = rt_le16_to_cpu(get_unaligned(&query->primary_id));
    fdev->ext_addr = rt_le16_to_cpu(get_unaligned(&query->primary_address));
    num_erase_regions = query->num_erase_regions;

    if (fdev->ext_addr)
    {
        fdev->version = cfi_flash_read_byte(fdev, fdev->ext_addr + 3) << 8;
        fdev->version |= cfi_flash_read_byte(fdev, fdev->ext_addr + 4);
    }

    switch (fdev->vendor)
    {
    case CFI_CMDSET_INTEL_PROG_REGIONS:
    case CFI_CMDSET_INTEL_STANDARD:
    case CFI_CMDSET_INTEL_EXTENDED:
        cfi_cmdset_intel_init(fdev, query);
        break;

    case CFI_CMDSET_AMD_STANDARD:
    case CFI_CMDSET_AMD_EXTENDED:
        cfi_cmdset_amd_init(fdev, query);
        break;

    default:
        /* Try an Intel-style reset*/
        cfi_flash_write_cmd(fdev, 0, 0, FLASH_CMD_RESET);
        break;
    }

    switch (fdev->manufacturer_id)
    {
    case 0x0001: /* AMD */
    case 0x0037: /* AMIC */
        cfi_flash_fixup_amd(fdev, query);
        break;

    case 0x001f:
        cfi_flash_fixup_atmel(fdev, query);
        break;

    case 0x0020:
        cfi_flash_fixup_stm(fdev, query);
        break;

    case 0x00bf: /* SST */
        cfi_flash_fixup_sst(fdev, query);
        break;

    case 0x0089: /* Numonyx */
        cfi_flash_fixup_num(fdev, query);
        break;
    }

    size_ratio = fdev->portwidth / fdev->chipwidth;

    if (fdev->interface == FLASH_CFI_X8X16 && fdev->chipwidth == FLASH_CFI_BY8)
    {
        size_ratio >>= 1;
    }

    fdev->size = 1 << query->dev_size;
    /* Multiply the size by the number of chips */
    fdev->size *= size_ratio;

    max_size = size;
    if (max_size && fdev->size > max_size)
    {
        fdev->size = max_size;
    }

    sect_count = 0;
    sect = fdev->sect[0];

    for (int i = 0; i < num_erase_regions; ++i)
    {
        if (i > RT_ARRAY_SIZE(query->erase_region_info))
        {
            LOG_E("Too many %d (> %d) erase regions found",
                   num_erase_regions, RT_ARRAY_SIZE(query->erase_region_info));
            break;
        }

        value = rt_le32_to_cpu(get_unaligned(&query->erase_region_info[i]));

        erase_region_count = (value & 0xffff) + 1;
        value >>= 16;
        erase_region_size = (value & 0xffff) ? ((value & 0xffff) * 256) : 128;

        for (int j = 0; j < erase_region_count; ++j)
        {
            if (sect - fdev->sect[0] >= fdev->size)
            {
                break;
            }

            if (sect_count > RT_ARRAY_SIZE(fdev->sect))
            {
                LOG_E("Too many %d (> %d) sector found",
                       sect_count, RT_ARRAY_SIZE(fdev->sect));
                break;
            }

            fdev->sect[sect_count] = sect;
            sect += (erase_region_size * size_ratio);

            switch (fdev->vendor)
            {
            case CFI_CMDSET_INTEL_PROG_REGIONS:
            case CFI_CMDSET_INTEL_EXTENDED:
            case CFI_CMDSET_INTEL_STANDARD:
                /*
                 * Set flash to read-id mode. Otherwise
                 * reading protected status is not guaranteed.
                 */
                cfi_flash_write_cmd(fdev, sect_count, 0, FLASH_CMD_READ_ID);
                fdev->protect[sect_count] = cfi_flash_isset(fdev,
                        sect_count, FLASH_OFFSET_PROTECT, FLASH_STATUS_PROTECT);
                cfi_flash_write_cmd(fdev, sect_count, 0, FLASH_CMD_RESET);
                break;

            case CFI_CMDSET_AMD_EXTENDED:
            case CFI_CMDSET_AMD_STANDARD:
            default:
                /* Default: not protected */
                fdev->protect[sect_count] = RT_NULL;
            }

            ++sect_count;
        }

        fdev->sect_count = sect_count;
    }

    if (fdev->interface == FLASH_CFI_X8X16 && fdev->chipwidth == FLASH_CFI_BY8)
    {
        /* Need to test on x8/x16 in parallel. */
        fdev->portwidth >>= 1;
    }

    value = 1 << query->block_erase_timeout_type;
    fdev->erase_blk_tout = value * (1 << query->block_erase_timeout_max);

    value = (1 << query->word_write_timeout_type) * (1 << query->word_write_timeout_max);
    /* Round up when converting to ms */
    fdev->write_tout = (value + 999) / 1000;

    cfi_flash_write_cmd(fdev, 0, 0, fdev->cmd_reset);

    fdev->parent.ops = &cfi_flash_ops;
    fdev->parent.block_start = 0;
    fdev->parent.block_end = fdev->sect_count;
    fdev->parent.block_size = size / fdev->sect_count;

    if ((err = rt_dm_dev_set_name_auto(&fdev->parent.parent, "nor")) < 0)
    {
        goto _fail;
    }

    name = rt_dm_dev_get_name(&fdev->parent.parent);

    if ((err = rt_mutex_init(&fdev->rw_lock, name, RT_IPC_FLAG_PRIO)))
    {
        goto _fail;
    }

    if ((err = rt_mtd_nor_register_device(name, &fdev->parent)))
    {
        goto _fail;
    }

    rt_free(query);

    return RT_EOK;

_fail:
    if (fdev->sect[0])
    {
        rt_iounmap((void *)fdev->sect[0]);
    }
    rt_free(query);

    return err;
}

static void cfi_flash_dev_remove(struct rt_device *dev, struct cfi_flash_device *fdev)
{
    if (fdev->rw_lock.parent.parent.name[0])
    {
        rt_mutex_detach(&fdev->rw_lock);
    }

    if (fdev->sect[0])
    {
        rt_iounmap((void *)fdev->sect[0]);
    }
}

static rt_err_t cfi_flash_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t count;
    struct cfi_flash *cfi;
    struct rt_device *dev = &pdev->parent;

    if ((count = rt_dm_dev_get_address_count(dev)) <= 0)
    {
        return -RT_EEMPTY;
    }

    cfi = rt_calloc(1, sizeof(*cfi) + count * sizeof(cfi->dev[0]));

    if (!cfi)
    {
        return -RT_ENOMEM;
    }
    cfi->count = count;

    for (int i = 0; i < cfi->count; ++i)
    {
        if ((err = cfi_flash_dev_probe(dev, &cfi->dev[i], i)))
        {
            goto _fail;
        }
    }

    dev->user_data = cfi;

    return RT_EOK;

_fail:
    for (int i = 0; i < cfi->count; ++i)
    {
        cfi_flash_dev_remove(dev, &cfi->dev[i]);
    }

    rt_free(cfi);

    return err;
}

static rt_err_t cfi_flash_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct cfi_flash *cfi = pdev->parent.user_data;

    for (int i = 0; i < cfi->count; ++i)
    {
        cfi_flash_dev_remove(dev, &cfi->dev[i]);
    }

    rt_free(cfi);

    return RT_EOK;
}

static const struct rt_ofw_node_id cfi_flash_ofw_ids[] =
{
    { .compatible = "cfi-flash" },
    { .compatible = "jedec-flash" },
    { /* sentinel */ }
};

static struct rt_platform_driver cfi_flash_driver =
{
    .name = "cfi-flash",
    .ids = cfi_flash_ofw_ids,

    .probe = cfi_flash_probe,
    .remove = cfi_flash_remove,
};
RT_PLATFORM_DRIVER_EXPORT(cfi_flash_driver);
