/*
 * drv_sfc.h
 *
 *  Created on: 2016Äê4ÔÂ5ÈÕ
 *      Author: Urey
 */

#ifndef DRIVER_DRV_SFC_H_
#define DRIVER_DRV_SFC_H_

#include <stdint.h>

#define SFC_USE_SWAP
#define SFC_USE_DMA
#define SFC_USE_QUAD


#define UNCACHE(addr)   ((((uint32_t)(addr)) | 0xa0000000))


/* SFC register */
#define SFC_GLB             (0x0000)
#define SFC_DEV_CONF            (0x0004)
#define SFC_DEV_STA_EXP         (0x0008)
#define SFC_DEV_STA_RT          (0x000c)
#define SFC_DEV_STA_MSK         (0x0010)
#define SFC_TRAN_CONF(n)        (0x0014 + (n * 4))
#define SFC_TRAN_LEN            (0x002c)
#define SFC_DEV_ADDR(n)         (0x0030 + (n * 4))
#define SFC_DEV_ADDR_PLUS(n)        (0x0048 + (n * 4))
#define SFC_MEM_ADDR            (0x0060)
#define SFC_TRIG            (0x0064)
#define SFC_SR              (0x0068)
#define SFC_SCR             (0x006c)
#define SFC_INTC            (0x0070)
#define SFC_FSM             (0x0074)
#define SFC_CGE             (0x0078)
#define SFC_RM_DR           (0x1000)

/* For SFC_GLB */
#define GLB_TRAN_DIR            (1 << 13)
#define GLB_TRAN_DIR_WRITE      (1)
#define GLB_TRAN_DIR_READ       (0)
#define GLB_THRESHOLD_OFFSET        (7)
#define GLB_THRESHOLD_MSK       (0x3f << GLB_THRESHOLD_OFFSET)
#define GLB_OP_MODE         (1 << 6)
#define SLAVE_MODE          (0x0)
#define DMA_MODE            (0x1)
#define GLB_PHASE_NUM_OFFSET        (3)
#define GLB_PHASE_NUM_MSK       (0x7  << GLB_PHASE_NUM_OFFSET)
#define GLB_WP_EN           (1 << 2)
#define GLB_BURST_MD_OFFSET     (0)
#define GLB_BURST_MD_MSK        (0x3  << GLB_BURST_MD_OFFSET)

/* For SFC_DEV_CONF */
#define DEV_CONF_ONE_AND_HALF_CYCLE_DELAY   (3)
#define DEV_CONF_ONE_CYCLE_DELAY    (2)
#define DEV_CONF_HALF_CYCLE_DELAY   (1)
#define DEV_CONF_NO_DELAY           (0)
#define DEV_CONF_SMP_DELAY_OFFSET   (16)
#define DEV_CONF_SMP_DELAY_MSK      (0x3 << DEV_CONF_SMP_DELAY_OFFSET)
#define DEV_CONF_CMD_TYPE       (0x1 << 15)
#define DEV_CONF_STA_TYPE_OFFSET    (13)
#define DEV_CONF_STA_TYPE_MSK       (0x1 << DEV_CONF_STA_TYPE_OFFSET)
#define DEV_CONF_THOLD_OFFSET       (11)
#define DEV_CONF_THOLD_MSK      (0x3 << DEV_CONF_THOLD_OFFSET)
#define DEV_CONF_TSETUP_OFFSET      (9)
#define DEV_CONF_TSETUP_MSK     (0x3 << DEV_CONF_TSETUP_OFFSET)
#define DEV_CONF_TSH_OFFSET     (5)
#define DEV_CONF_TSH_MSK        (0xf << DEV_CONF_TSH_OFFSET)
#define DEV_CONF_CPHA           (0x1 << 4)
#define DEV_CONF_CPOL           (0x1 << 3)
#define DEV_CONF_CEDL           (0x1 << 2)
#define DEV_CONF_HOLDDL         (0x1 << 1)
#define DEV_CONF_WPDL           (0x1 << 0)

/* For SFC_TRAN_CONF */
#define TRAN_CONF_TRAN_MODE_OFFSET  (29)
#define TRAN_CONF_TRAN_MODE_MSK     (0x7)
#define TRAN_CONF_ADDR_WIDTH_OFFSET (26)
#define TRAN_CONF_ADDR_WIDTH_MSK    (0x7 << ADDR_WIDTH_OFFSET)
#define TRAN_CONF_POLLEN        (1 << 25)
#define TRAN_CONF_CMDEN         (1 << 24)
#define TRAN_CONF_FMAT          (1 << 23)
#define TRAN_CONF_DMYBITS_OFFSET    (17)
#define TRAN_CONF_DMYBITS_MSK       (0x3f << DMYBITS_OFFSET)
#define TRAN_CONF_DATEEN        (1 << 16)
#define TRAN_CONF_CMD_OFFSET        (0)
#define TRAN_CONF_CMD_MSK       (0xffff << CMD_OFFSET)
#define TRAN_CONF_CMD_LEN       (1 << 15)

/* For SFC_TRIG */
#define TRIG_FLUSH          (1 << 2)
#define TRIG_STOP           (1 << 1)
#define TRIG_START          (1 << 0)

/* For SFC_SCR */
#define CLR_END         (1 << 4)
#define CLR_TREQ        (1 << 3)
#define CLR_RREQ        (1 << 2)
#define CLR_OVER        (1 << 1)
#define CLR_UNDER       (1 << 0)

/* For SFC_TRAN_CONFx */
#define TRAN_MODE_OFFSET    (29)
#define TRAN_MODE_MSK       (0x7 << TRAN_MODE_OFFSET)
#define TRAN_SPI_STANDARD   (0x0)
#define TRAN_SPI_DUAL   (0x1 )
#define TRAN_SPI_QUAD   (0x5 )
#define TRAN_SPI_IO_QUAD   (0x6 )


#define ADDR_WIDTH_OFFSET   (26)
#define ADDR_WIDTH_MSK      (0x7 << ADDR_WIDTH_OFFSET)
#define POLLEN          (1 << 25)
#define CMDEN           (1 << 24)
#define FMAT            (1 << 23)
#define DMYBITS_OFFSET      (17)
#define DMYBITS_MSK     (0x3f << DMYBITS_OFFSET)
#define DATEEN          (1 << 16)
#define CMD_OFFSET      (0)
#define CMD_MSK         (0xffff << CMD_OFFSET)

#define N_MAX               6
#define MAX_SEGS        128

#define CHANNEL_0       0
#define CHANNEL_1       1
#define CHANNEL_2       2
#define CHANNEL_3       3
#define CHANNEL_4       4
#define CHANNEL_5       5

#define ENABLE          1
#define DISABLE         0

#define COM_CMD         1   // common cmd
#define POLL_CMD        2   // the cmd will poll the status of flash,ext: read status

#define DMA_OPS         1
#define CPU_OPS         0

#define TM_STD_SPI      0
#define TM_DI_DO_SPI    1
#define TM_DIO_SPI      2
#define TM_FULL_DIO_SPI 3
#define TM_QI_QO_SPI    5
#define TM_QIO_SPI      6
#define TM_FULL_QIO_SPI 7

#define DEFAULT_ADDRSIZE    3

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

/*SPI NOR FLASH Instructions*/
#define CMD_WREN        0x06 /* Write Enable */
#define CMD_WRDI        0x04 /* Write Disable */
#define CMD_RDSR        0x05 /* Read Status Register */
#define CMD_RDSR_1      0x35 /* Read Status1 Register */
#define CMD_RDSR_2      0x15 /* Read Status2 Register */
#define CMD_WRSR        0x01 /* Write Status Register */
#define CMD_WRSR_1      0x31 /* Write Status1 Register */
#define CMD_WRSR_2      0x11 /* Write Status2 Register */
#define CMD_READ        0x03 /* Read Data */
#define CMD_DUAL_READ   0x3b /* DUAL Read Data */
#define CMD_QUAD_READ   0x6b /* QUAD Read Data */
#define CMD_QUAD_IO_FAST_READ   0xeb /* QUAD FAST Read Data */
#define CMD_QUAD_IO_WORD_FAST_READ   0xe7 /* QUAD IO WORD Read Data */
#define CMD_FAST_READ   0x0B /* Read Data at high speed */
#define CMD_PP          0x02 /* Page Program(write data) */
#define CMD_QPP         0x32 /* QUAD Page Program(write data) */
#define CMD_BE_4K       0x20
#define CMD_BE_32K      0x52 /* Block Erase */
#define CMD_BE_64K      0XD8 /* Block Erase */
#define CMD_CE          0xC7 /* Bulk or Chip Erase */
#define CMD_DP          0xB9 /* Deep Power-Down */
#define CMD_RES         0xAB /* Release from Power-Down and Read Electronic Signature */
#define CMD_REMS        0x90 /* Read Manufacture ID/ Device ID */
#define CMD_RDID        0x9F /* Read Identification */
#define CMD_NON         0x00 /* Read Identification */
#define CMD_RUID        0x4B    /* ReadUnique ID */
#define CMD_NON         0x00 /* Read Identification */
#define CMD_EN4B        0xB7 /* Enter 4 bytes address mode */
#define CMD_EX4B        0xE9 /* Exit 4 bytes address mode */

struct cmd_info
{
    uint32_t cmd;
    uint32_t cmd_len;/*reserved; not use*/
    uint32_t dataen;
    uint32_t sta_exp;
    uint32_t sta_msk;
};

struct sfc_transfer
{
    uint32_t direction;

    struct cmd_info *cmd_info;

    uint32_t addr_len;
    uint32_t addr;
    uint32_t addr_plus;
    uint32_t addr_dummy_bits;/*cmd + addr_dummy_bits + addr*/

    const uint8_t *data;
    uint32_t data_dummy_bits;/*addr + data_dummy_bits + data*/
    uint32_t len;
    uint32_t cur_len;

    uint32_t sfc_mode;
    uint32_t ops_mode;
    uint32_t phase_format;/*we just use default value;phase1:cmd+dummy+addr... phase0:cmd+addr+dummy...*/

    rt_list_t transfer_list;

};

struct sfc_message
{
    rt_list_t   transfers;
    uint32_t    actual_length;
    uint32_t    status;
};


struct sfc
{
    void       *iomem;
    int         irq;
    struct clk *clk;
    struct clk *clk_gate;
    uint32_t    src_clk;
    uint32_t    threshold;
    struct sfc_transfer    *transfer;
    struct rt_completion    done;
};

struct sfc_quad_mode
{
    uint8_t  RDSR_CMD;
    uint32_t RD_DATE_SIZE;//the data is write the spi status register for QE bit
    uint8_t  sfc_mode;
    uint8_t  WRSR_CMD;
    uint32_t WD_DATE_SIZE;//the data is write the spi status register for QE bit
    uint8_t  cmd_read;
    uint32_t RDSR_DATE;//the data is write the spi status register for QE bit
    uint32_t WRSR_DATE;//this bit should be the flash QUAD mode enable

    uint32_t dummy_byte;
};

struct sfc_flash
{
    struct rt_mtd_nor_device    mtd;
    char    *name;
    uint32_t id;
    uint8_t  uid[8];

    uint32_t pagesize;
    uint32_t sectorsize;
    uint32_t chipsize;
    uint32_t erasesize;
    uint32_t writesize;
    uint32_t addrsize;

    struct sfc          *sfc;
    uint32_t            sfc_mode;
#ifdef SFC_USE_QUAD
    struct sfc_quad_mode    *quad_mode;
#endif
    struct rt_mutex         lock;
};

int     sfc_norflash_probe(struct sfc_flash *flash);
size_t  sfc_norflash_read(struct sfc_flash *flash, rt_off_t from, uint8_t *buf, size_t len);
size_t  sfc_norflash_write(struct sfc_flash *flash, rt_off_t to,  const uint8_t *buf, size_t len);
int     sfc_norflash_erase_sector(struct sfc_flash *flash, uint32_t addr);
int     sfc_norflash_set_addr_width_4byte(struct sfc_flash *flash,int on);

#endif /* DRIVER_DRV_SFC_H_ */
