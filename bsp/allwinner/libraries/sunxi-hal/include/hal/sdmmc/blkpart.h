#ifndef __BLKPART_H__
#define __BLKPART_H__

#include <sys/types.h>
#include <stdint.h>
#include <rtthread.h>

#include <log.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SECTOR_SIZE
#undef SECTOR_SIZE
#endif
#define SECTOR_SHIFT 9
#define SECTOR_SIZE (1 << SECTOR_SHIFT)

typedef enum
{
    STORAGE_NAND =0,
    STORAGE_SDC0,
    STORAGE_SDC1,
    STORAGE_NOR,
    STORAGE_SDC2,
    STORAGE_SPI_NAND,
}SUNXI_BOOT_STORAGE;


struct part
{
    /* public */
#define BLKPART_OFF_APPEND UINT32_MAX
    uint64_t off;
#define BLKPART_SIZ_FULL UINT32_MAX
    uint64_t bytes;
#define MAX_BLKNAME_LEN 16
    char name[MAX_BLKNAME_LEN];      /* name: UDISK */

    /* private */
    char devname[MAX_BLKNAME_LEN];   /* name: nor0p1 */
    struct blkpart *blk;
    uint32_t n_part;
    uint32_t erase_flag;
};

struct blkpart
{
    /* public */
    const char *name;
    uint64_t total_bytes;
    uint32_t blk_bytes;
    uint32_t page_bytes;
    int (*erase)(unsigned int, unsigned int);
    int (*program)(unsigned int, char *, unsigned int);
    int (*read)(unsigned int, char *, unsigned int);

    /* if no any partition, the follow can be NULL */
    struct part *parts;
    uint32_t n_parts;

    /* private */
    int blk_cnt;
    struct part root;
    struct blkpart *next;
    uint32_t n_blk;
    rt_device_t dev;
};

typedef enum BLOCK_DEVICE_CMD_T
{
    BLOCK_DEVICE_CMD_ERASE_ALL = 0x00,
    BLOCK_DEVICE_CMD_ERASE_SECTOR,
    BLOCK_DEVICE_CMD_GET_TOTAL_SIZE,
    BLOCK_DEVICE_CMD_GET_PAGE_SIZE,
    BLOCK_DEVICE_CMD_GET_BLOCK_SIZE,
    BLOCK_DEVICE_CMD_NUM,
} BLOCK_DEVICE_CMD;

typedef enum DEVICE_PART_CMD_T
{
    DEVICE_PART_CMD_ERASE_ALL = 0x00,
    DEVICE_PART_CMD_ERASE_SECTOR,
    DEVICE_PART_CMD_GET_TOTAL_SIZE,
    DEVICE_PART_CMD_GET_BLOCK_SIZE,
    DEVICE_PART_CMD_NUM,
} DEVICE_PART_CMD;

typedef struct _blk_dev_erase_t
{
    uint32_t addr;
    uint32_t len;
} blk_dev_erase_t;

void del_blkpart(struct blkpart *blk);
void blkpart_add_list(struct blkpart *blk);
void blkpart_del_list(struct blkpart *blk);

#define PARTINDEX_THE_LAST UINT32_MAX
struct blkpart *get_blkpart_by_name(const char *name);
struct part *get_part_by_index(const char *blk_name, uint32_t index);
struct part *get_part_by_name(const char *name);


#define PARTINDEX_THE_LAST UINT32_MAX
struct part *get_part_by_name(const char *name);

int remove_part_from_list(struct part *target_part);
int add_part_to_list(struct part *target_part);

int create_register_part(rt_device_t dev,
                         const char *part_name,
                         unsigned int part_offset,
                         unsigned int part_bytes);

int part_system_init(void);

rt_size_t part_erase_before_write(rt_device_t dev, rt_off_t offset, const void *data, rt_size_t size);
rt_size_t part_erase_without_write(rt_device_t dev, rt_off_t offset, const void *data, rt_size_t size);
rt_size_t part_read(rt_device_t dev, rt_off_t offset, void *data, rt_size_t size);
rt_err_t part_control(rt_device_t dev, int cmd, void *args);

#ifdef __cplusplus
}
#endif

#endif
