/* This is all about APIs for/from other modules */

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <hal_timer.h>
#include <sunxi_hal_common.h>

#ifdef CONFIG_COMPONENTS_AW_BLKPART
#include <blkpart.h>
#include <part_efi.h>
#endif

#include "inter.h"

#ifdef CONFIG_COMPONENTS_AW_BLKPART
struct syspart {
    char name[MAX_BLKNAME_LEN];
    u32 bytes;
};

static const struct syspart syspart[] = {
    /* contain boot0 and gpt, gpt offset is (128-16)k */
    {"boot0", 128 * 1024},
};

static struct blkpart norblk;
#endif

static sunxi_hal_spinor_info hal_spinor_info = {0};

sunxi_hal_version_t hal_spinor_get_version(int32_t dev)
{
    sunxi_hal_version_t ver;
    HAL_ARG_UNUSED(dev);

    ver.api = SUNXI_HAL_SPINOR_API_VERSION;
    ver.drv = SUNXI_HAL_SPINOR_DRV_VERSION;
    return ver;
}

sunxi_hal_spinor_capabilities_t hal_spinor_get_capabilities(void)
{
    sunxi_hal_spinor_capabilities_t cap;

    cap.event_ready = 1;
    cap.data_width = 1;
    cap.erase_chip = 1;
    cap.reserved = 0;

    return cap;
}

#ifdef CONFIG_COMPONENTS_AW_BLKPART
static int nor_get_gpt(char *buf, int len)
{
    if (len < GPT_TABLE_SIZE) {
        SPINOR_ERR("buf too small for gpt\n");
        return -EINVAL;
    }

    return nor_read(GPT_ADDRESS, buf, GPT_TABLE_SIZE);
}

#ifdef CONFIG_RESERVE_IMAGE_PART

typedef struct sbrom_toc1_head_info
{
    char name[16]   ;   //user can modify
    uint32_t  magic ;   //must equal TOC_U32_MAGIC
    uint32_t  add_sum   ;

    uint32_t  serial_num    ;   //user can modify
    uint32_t  status        ;   //user can modify,such as TOC_MAIN_INFO_STATUS_ENCRYP_NOT_USED

    uint32_t  items_nr; //total entry number
    uint32_t  valid_len;
    uint32_t  version_main; //only one byte
    uint32_t  version_sub;   //two bytes
    uint32_t  reserved[3];  //reserved for future

    uint32_t  end;
}__attribute__((aligned(1))) sbrom_toc1_head_info_t;

/*
 * get_rtos_toc_package_size: get rtos toc package size
 * @param gpt_buf: gpt table buf
 * @param name   : gpt entry name
 * @param page_bytes: page size
 * @return value : toc pageage size
 */
int get_rtos_toc_package_size(void *gpt_buf, char *name, int page_bytes)
{
    unsigned int len = 0x0;
    unsigned int sectors = 0;
    unsigned int start_sector = 0;
    int toc_offset = 0;
    int ret = -1;

    char *buf = malloc(page_bytes);
    if (!buf)
        return -1;
    memset(buf, 0, page_bytes);

    ret = get_part_info_by_name(gpt_buf, name, &start_sector, &sectors);
    if (ret)
        goto out;

    toc_offset = start_sector << 9;
    ret = nor_read(toc_offset, buf, page_bytes);
    if (ret)
        goto out;

    sbrom_toc1_head_info_t *head = (sbrom_toc1_head_info_t *)buf;
    if (strncmp(head->name, "sunxi-", 6))
        goto out;

#define ALIGN_UP(size, align) (((size) + (align) - 1) & ~((align) - 1))
    len = ALIGN_UP(head->valid_len, page_bytes);

out:
    free(buf);

    return len;
}

/*
 * get_rtos_offset: get rtos offset
 * @param gpt_buf: gpt table buf
 * @param name   : gpt entry name
 * @return value : rtos part offset
 */
int get_rtos_offset(void *gpt_buf, char *name)
{
    unsigned int sectors = 0;
    unsigned int start_sector = 0;
    int ret = -1;

    ret = get_part_info_by_name(gpt_buf, name, &start_sector, &sectors);
    if (ret)
        goto out;

    ret = start_sector << 9;
out:

    return ret;
}

#endif

static int nor_blkpart_init(void)
{
    int ret, index;
    char *gpt_buf;
    struct nor_flash *nor;
    struct gpt_part *gpt_part;
    struct part *part;

    nor = get_nor_flash();
    if (!nor || !nor->info)
        return -EBUSY;

    gpt_buf = malloc(GPT_TABLE_SIZE);
    if (!gpt_buf) {
        ret = -ENOMEM;
        goto err;
    }
    memset(gpt_buf, 0, GPT_TABLE_SIZE);

    ret = nor_get_gpt(gpt_buf, GPT_TABLE_SIZE);
    if (ret) {
        SPINOR_ERR("get gpt from nor flash failed - %d\n", ret);
        goto err;
    }

    memset(&norblk, 0, sizeof(struct blkpart));
    norblk.name = "nor";
    norblk.page_bytes = nor->page_size;
#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    norblk.erase = nor_cache_erase;
    norblk.program = nor_cache_write;
    norblk.read = nor_cache_read;
    norblk.sync = nor_cache_sync;
#else
    norblk.erase = nor_erase;
    norblk.program = nor_write;
    norblk.read = nor_read;
    norblk.sync = NULL;
#endif
    norblk.noncache_erase = nor_erase;
    norblk.noncache_program = nor_write;
    norblk.noncache_read = nor_read;
    norblk.total_bytes = nor->total_size;
    norblk.blk_bytes = nor->blk_size;

    ret = gpt_part_cnt(gpt_buf);
    if (ret < 0) {
        SPINOR_ERR("get part count from gpt failed\n");
        goto err;
    }
#ifdef CONFIG_RESERVE_IMAGE_PART
    norblk.n_parts = ret + ARRAY_SIZE(syspart) + 2;
#else
    norblk.n_parts = ret + ARRAY_SIZE(syspart);
#endif
    norblk.parts = malloc(norblk.n_parts * sizeof(struct part));
    if (!norblk.parts)
        goto err;
    SPINOR_INFO("total %u part\n", norblk.n_parts);

    for (index = 0; index < ARRAY_SIZE(syspart); index++) {
        part = &norblk.parts[index];
        part->bytes = syspart[index].bytes;
        part->off = BLKPART_OFF_APPEND;
        strcpy(part->name, syspart[index].name);
    }

    foreach_gpt_part(gpt_buf, gpt_part) {
        part = &norblk.parts[index++];
        part->bytes = gpt_part->sects << SECTOR_SHIFT;
        part->off = BLKPART_OFF_APPEND;
        snprintf(part->name, MAX_BLKNAME_LEN, "%s", gpt_part->name);
#ifdef CONFIG_RESERVE_IMAGE_PART
        if (!strcmp("rtosA", part->name) || !strcmp("rtosB", part->name)) {
            int rtos_index = index - 1;
            struct part *last_part = part;
            int toc_package_size = get_rtos_toc_package_size(gpt_buf, last_part->name, norblk.page_bytes);
            int rtos_offset = get_rtos_offset(gpt_buf, last_part->name);
            if (toc_package_size > 0 && rtos_offset > 0) {
                part = &norblk.parts[index++];
                part->bytes = norblk.parts[rtos_index].bytes - toc_package_size;
                part->off = rtos_offset + toc_package_size;
                if (!strcmp("rtosA", last_part->name))
                    snprintf(part->name, MAX_BLKNAME_LEN, "%s", "reserveA");
                else
                    snprintf(part->name, MAX_BLKNAME_LEN, "%s", "reserveB");
            } else {
                norblk.n_parts --;
            }
        }
#endif
    }
    norblk.parts[--index].bytes = BLKPART_SIZ_FULL;

    ret = add_blkpart(&norblk);
    if (ret)
        goto free_parts;

    /* check bytes align */
    for (index = 0; index < norblk.n_parts; index++) {
        part = &norblk.parts[index];
        if (part->bytes % nor->blk_size) {
            SPINOR_ERR("part %s with bytes %u should align to block size %u\n",
                    part->name, part->bytes, nor->blk_size);
            goto del_blk;
        }
    }

    free(gpt_buf);
    return 0;

del_blk:
    del_blkpart(&norblk);
free_parts:
    free(norblk.parts);
err:
    free(gpt_buf);
    SPINOR_ERR("init blkpart for nor failed - %d\n", ret);
    return ret;
}

int32_t hal_spinor_init(sunxi_hal_spinor_signal_event_t cb_event)
{
    int ret;

    ret = nor_init();
    if (ret)
        return ret;

    return nor_blkpart_init();
}
#else
int32_t hal_spinor_init(sunxi_hal_spinor_signal_event_t cb_event)
{
    return nor_init();
}
#endif

int32_t hal_spinor_deinit(void)
{
    hal_spinor_sync();
    return nor_deinit();
}

int32_t hal_spinor_power_control(sunxi_hal_power_state_e state)
{
    return SUNXI_HAL_OK;
}

int32_t hal_spinor_read_data(uint32_t addr, void *buf, uint32_t cnt)
{
#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    return nor_cache_read(addr, buf, cnt);
#else
    return nor_read(addr, (void *)buf, cnt);
#endif
}

int32_t hal_spinor_program_data(uint32_t addr, const void *buf, uint32_t cnt)
{
#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    return nor_cache_write(addr, (void *)buf, cnt);
#else
    return nor_write(addr, (void *)buf, cnt);
#endif
}

int32_t hal_spinor_sync(void)
{
#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    return nor_cache_sync();
#else
    return 0;
#endif
}

int32_t hal_spinor_erase_sector(uint32_t addr, uint32_t size)
{
#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    return nor_cache_erase(addr, size);
#else
    return nor_erase(addr, size);
#endif
}

int32_t hal_spinor_erase_chip(void)
{
    struct nor_flash *nor = get_nor_flash();

#ifdef CONFIG_DRIVERS_SPINOR_CACHE
    nor_cache_sync();
#endif
    return nor_erase(0, nor->total_size);
}

sunxi_hal_spinor_status_t hal_spinor_get_status(void)
{
    sunxi_hal_spinor_status_t spinor_status = {0, 0, 0};

    return spinor_status;
}

sunxi_hal_spinor_info *hal_spinor_get_info(void)
{
    struct nor_flash *nor = get_nor_flash();

    if (!nor->info)
        return NULL;

    hal_spinor_info.sector_size = nor->blk_size;
    hal_spinor_info.sector_count = nor->total_size / nor->blk_size;
    hal_spinor_info.page_size = nor->page_size;
    hal_spinor_info.program_unit = nor->page_size;
    return &hal_spinor_info;
}

void hal_spinor_signal_event(uint32_t event)
{
    return;
}

int32_t hal_spinor_control(int32_t dev, uint32_t command, uint32_t arg)
{
    return SUNXI_HAL_OK;
}
