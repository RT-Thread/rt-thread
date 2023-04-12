#ifndef _SPINOR_INTER_H_
#define _SPINOR_INTER_H_

#include <sunxi_hal_common.h>
#include <sunxi_hal_spi.h>
#include <sunxi_hal_spinor.h>
#include <hal_log.h>

#define SPINOR_FMT(fmt) "spinor: "fmt
#define SPINOR_ERR(fmt, arg...) hal_log_err(SPINOR_FMT(fmt), ##arg)
#define SPINOR_WARN(fmt, arg...) hal_log_warn(SPINOR_FMT(fmt), ##arg)
#define SPINOR_DEBUG(fmt, arg...) hal_log_debug(SPINOR_FMT(fmt), ##arg)
#define SPINOR_INFO(fmt, arg...) hal_log_info(SPINOR_FMT(fmt), ##arg)

#ifndef BIT
#define BIT(x) (1UL << (x))
#endif

#ifndef MIN
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))
#endif

#undef ALIGN
#undef ALIGN_DOWN

#define ALIGN(x, a) __ALIGN_KERNEL((x), (a))
#define ALIGN_DOWN(x, a) __ALIGN_KERNEL((x) - ((a) - 1), (a))
#define __ALIGN_KERNEL(x, a) __ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_KERNEL_MASK(x, mask) (((x) + (mask)) & ~(mask))

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_PER_BYTE 8
#define BITS_PER_LONG (sizeof(long) * BITS_PER_BYTE)

#ifndef BITS_TO_LONGS
#define BITS_TO_LONGS(nr) DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#endif

#define SZ_4K       (4 * 1024)
#define SZ_32K      (32 * 1024)
#define SZ_64K      (64 * 1024)
#define SZ_128K     (128 * 1024)
#define SZ_256K     (256 * 1024)
#define SZ_512K     (512 * 1024)
#define SZ_1M       (1 * 1024 * 1024)
#define SZ_2M       (2 * 1024 * 1024)
#define SZ_4M       (4 * 1024 * 1024)
#define SZ_8M       (8 * 1024 * 1024)
#define SZ_12M      (12 * 1024 * 1024)
#define SZ_14M      (14 * 1024 * 1024)
#define SZ_15M      (15 * 1024 * 1024)
#define SZ_15872K   (15872 * 1024)
#define SZ_16128K   (16128 * 1024)
#define SZ_16M      (16 * 1024 * 1024)
#define SZ_32M      (32 * 1024 * 1024)
#define SZ_64M      (64 * 1024 * 1024)

#define MAX_ID_LEN 3
#define MAX_WAIT_LOOP ((unsigned int)(-1))
#define NOR_DEFAULT_FREQUENCY 50
#define NOR_PAGE_SIZE 256
#define NOR_HALF_BLK_SIZE (SZ_32K)
#define NOR_BLK_SIZE (SZ_64K)

#define FACTORY_ZETTA   0xBA
#define FACTORY_PUYA    0x85
#define FACTORY_MXIC    0xC2
#define FACTORY_GD      0xC8
#define FACTORY_WINBOND 0xEF
#define FACTORY_FM      0xA1
#define FACTORY_ESMT    0x1C
#define FACTORY_XTX     0x0B
#define FACTORY_XMC     0x20

struct nor_info
{
    char *model;
    unsigned char id[MAX_ID_LEN];
    unsigned int total_size;

    int flag;
#define SUPPORT_4K_ERASE_BLK        BIT(0)
#define SUPPORT_32K_ERASE_BLK       BIT(1)
#define SUPPORT_64K_ERASE_BLK       BIT(2)
#define SUPPORT_DUAL_READ           BIT(3)
#define SUPPORT_QUAD_READ           BIT(4)
#define SUPPORT_QUAD_WRITE          BIT(5)
#define SUPPORT_INDIVIDUAL_PROTECT  BIT(6)
#define SUPPORT_ALL_ERASE_BLK       (SUPPORT_4K_ERASE_BLK | \
                                     SUPPORT_32K_ERASE_BLK | \
                                     SUPPORT_64K_ERASE_BLK)
#define SUPPORT_GENERAL             (SUPPORT_ALL_ERASE_BLK | \
                                     SUPPORT_QUAD_WRITE | \
                                     SUPPORT_QUAD_READ | \
                                     SUPPORT_DUAL_READ)
#define USE_4K_ERASE                BIT(20)
#define USE_IO_PROG_X4              BIT(21)
#define USE_IO_READ_X2              BIT(22)
#define USE_IO_READ_X4              BIT(23)
};

struct nor_spi_master
{
    hal_spi_master_port_t port;
    hal_spi_master_config_t cfg;
};

struct nor_flash
{
    unsigned char cmd_read;
    unsigned char cmd_write;

    unsigned int r_cmd_slen: 3;
    unsigned int w_cmd_slen: 3;
    unsigned int total_size;
    unsigned int blk_size;
    unsigned int page_size;
    unsigned int addr_width;

    struct nor_spi_master spim;
    struct nor_info *info;
    struct nor_factory *factory;

    hal_sem_t hal_sem;
};

struct nor_factory {
    unsigned char factory;
    unsigned int idt_cnt;
    struct nor_info *idt;

    int (*init)(struct nor_flash *nor);
    void (*deinit)(struct nor_flash *nor);
    int (*init_lock)(struct nor_flash *nor);
    void (*deinit_lock)(struct nor_flash *nor);
    int (*lock)(struct nor_flash *nor, unsigned int addr, unsigned int len);
    int (*unlock)(struct nor_flash *nor, unsigned int addr, unsigned int len);
    bool (*islock)(struct nor_flash *nor, unsigned int addr, unsigned int len);
    int (*set_quad_mode)(struct nor_flash *nor);
    int (*set_4bytes_addr)(struct nor_flash *nor, int enable);

    struct nor_factory *next;
};

int nor_register_factory(struct nor_factory *f);
int nor_register_factory_gd(void);
int nor_register_factory_mxic(void);
int nor_register_factory_winbond(void);
int nor_register_factory_xtx(void);
int nor_register_factory_esmt(void);
int nor_register_factory_fm(void);
int nor_register_factory_xmc(void);
int nor_register_factory_puya(void);
int nor_register_factory_zetta(void);

int nor_transfer(int single_len, void *tbuf, int tlen, void *rbuf, int rlen);
int nor_send_cmd(unsigned char cmd);
int nor_read_status(unsigned char *sr);
int nor_write_status(unsigned char *sr, unsigned int len);
int nor_wait_ready(unsigned int ms, unsigned int times);
int nor_write_enable(void);

int nor_init(void);
int nor_deinit(void);
int nor_write(unsigned int addr, char *buf, unsigned int len);
int nor_read(unsigned int addr, char *buf, unsigned int len);
int nor_erase(unsigned int addr, unsigned int size);
struct nor_flash *get_nor_flash(void);

#ifdef CONFIG_DRIVERS_SPINOR_CACHE
int nor_cache_init(struct nor_flash *nor);
void nor_cache_exit(void);
int nor_cache_read(unsigned int addr, char *buf, unsigned int len);
int nor_cache_write(unsigned int addr, char *buf, unsigned int len);
int nor_cache_sync(void);
int nor_cache_erase(unsigned int addr, unsigned int len);
#endif /* CONFIG_DRIVERS_SPINOR_CACHE */

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
int nor_wr_lock_init(struct nor_flash *nor);
void nor_wr_lock_deinit(struct nor_flash *nor);
int nor_wr_lock(struct nor_flash *nor, unsigned int addr, unsigned int len);
int nor_wr_unlock(struct nor_flash *nor, unsigned int addr, unsigned int len);
bool nor_wr_islock(struct nor_flash *nor, unsigned int addr, unsigned int len);
int nor_wr_unlock_all(struct nor_flash *nor);
int nor_wr_lock_all(struct nor_flash *nor);
#endif /* CONFIG_DRIVERS_SPINOR_WRITE_LOCK */

#ifdef CONFIG_DRIVERS_SPINOR_WRITE_LOCK
#define is_wrlock_work(nor) (nor->info->flag & SUPPORT_INDIVIDUAL_PROTECT)
#else
#define is_wrlock_work(nor) (false)
#endif

#endif
