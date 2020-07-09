#ifndef DRV_MMC_H__
#define DRV_MMC_H__

#include <stdint.h>

/* MSC configure */
#define MMC_MSC_INTERRUPT_ENABLE    1 /* 0: disable, 1: enable. */

//--------------------------------------------------------------------------
// MSC Registers Offset Definition
//--------------------------------------------------------------------------
#define MSC_CTRL_OFFSET             ( 0x00 )    //  W,  16, 0x000, MSC Control register
#define MSC_STAT_OFFSET             ( 0x04 )    //  R,  32, 0x00000040, MSC Status register
#define MSC_CLKRT_OFFSET            ( 0x08 )    //  RW, 16, 0x0000, MSC Clock Rate register
#define MSC_CMDAT_OFFSET            ( 0x0C )    //  RW, 32, 0x00000000, MSC Command and Data Control register
#define MSC_RESTO_OFFSET            ( 0x10 )    //  RW, 16, 0x0040, MSC Response Time Out register
#define MSC_RDTO_OFFSET             ( 0x14 )    //  RW, 16, 0xFFFF, MSC Read Time Out register
#define MSC_BLKLEN_OFFSET           ( 0x18 )    //  RW, 16, 0x0000, MSC Block Length register
#define MSC_NOB_OFFSET              ( 0x1C )    //  RW, 16, 0x0000, MSC Number of Block register
#define MSC_SNOB_OFFSET             ( 0x20 )    //  R,  16, 0x????, MSC Number of Successfully-transferred Blocks register
#define MSC_IMASK_OFFSET            ( 0x24 )    //  RW, 32, 0x000000FF, MSC Interrupt Mask register
#define MSC_IREG_OFFSET             ( 0x28 )    //  RW, 16, 0x2000, MSC Interrupt register
#define MSC_CMD_OFFSET              ( 0x2C )    //  RW,  8, 0x00, MSC Command Index register
#define MSC_ARG_OFFSET              ( 0x30 )    //  RW, 32, 0x00000000, MSC Command Argument register
#define MSC_RES_OFFSET              ( 0x34 )    //  R,  16, 0x????, MSC Response FIFO register
#define MSC_RXFIFO_OFFSET           ( 0x38 )    //  R,  32, 0x????????, MSC Receive Data FIFO register
#define MSC_TXFIFO_OFFSET           ( 0x3C )    //  W,  32, 0x????????, MSC Transmit Data FIFO register
#define MSC_LPM_OFFSET              ( 0x40 )    //  RW, 32, 0x00000000, MSC Low Power Mode register
#define MSC_DMAC_OFFSET             ( 0x44 )
#define MSC_DMANDA_OFFSET           ( 0x48 )
#define MSC_DMADA_OFFSET            ( 0x4C )
#define MSC_DMALEN_OFFSET           ( 0x50 )
#define MSC_DMACMD_OFFSET           ( 0x54 )
#define MSC_CTRL2_OFFSET            ( 0x58 )
#define MSC_RTCNT_OFFSET            ( 0x5C )

//--------------------------------------------------------------------------
// MMC/SD Control Register field descriptions (MSC_CTRL)
//--------------------------------------------------------------------------
#define MSC_CTRL_CLOCK_CONTROL_MASK     ( 3 << 0 )
#define MSC_CTRL_CLOCK_DONOTHING        ( 0 << 0 )
#define MSC_CTRL_CLOCK_STOP             ( 1 << 0 )
#define MSC_CTRL_CLOCK_START            ( 2 << 0 )

#define MSC_CTRL_START_OP               ( 1 << 2 )
#define MSC_CTRL_RESET                  ( 1 << 3 )
#define MSC_CTRL_STOP_RDWAIT            ( 1 << 4 )
#define MSC_CTRL_START_RDWAIT           ( 1 << 5 )
#define MSC_CTRL_EXIT_TRANSFER          ( 1 << 6 )
#define MSC_CTRL_EXIT_MULTIPLE          ( 1 << 7 )
#define MSC_CTRL_SEND_AS_CCSD           ( 1 << 14 )
#define MSC_CTRL_SEND_CCSD              ( 1 << 15 )

//--------------------------------------------------------------------------
// MSC Status Register field descriptions (MSC_STAT)
//--------------------------------------------------------------------------

#define MSC_STAT_TIME_OUT_READ           ( 1 << 0 )
#define MSC_STAT_TIME_OUT_RES            ( 1 << 1 )

#define MSC_STAT_CRC_WRITE_ERR_MASK     ( 3 << 2 )
#define MSC_STAT_CRC_WRITE_NO_ERR       ( 0 << 2 )
#define MSC_STAT_CRC_WRITE_ERR          ( 1 << 2 )
#define MSC_STAT_CRC_WRITE_NO_STATUS    ( 2 << 2 )

#define MSC_STAT_CRC_READ_ERR           ( 1 << 4 )

#define MSC_CMDAT_RESP_FORMAT_MASK      ( 7 << 0 )

#define MSC_STAT_CRC_RES_ERR            ( 1 << 5 )
#define MSC_STAT_DATA_FIFO_EMPTY        ( 1 << 6 )
#define MSC_STAT_DATA_FIFO_FULL         ( 1 << 7 )
#define MSC_STAT_CLK_EN                 ( 1 << 8 )
#define MSC_STAT_IS_READWAIT            ( 1 << 9 )
#define MSC_STAT_DATA_FIFO_AFULL        ( 1 << 10 )
#define MSC_STAT_END_CMD_RES            ( 1 << 11 )
#define MSC_STAT_DATA_TRAN_DONE         ( 1 << 12 )
#define MSC_STAT_PRG_DONE               ( 1 << 13 )
#define MSC_STAT_SDIO_INT_ACTIVE        ( 1 << 14 )
#define MSC_STAT_IS_RESETTING           ( 1 << 15 )
#define MSC_STAT_AUTO_CMD_DONE          ( 1 << 31 )

//--------------------------------------------------------------------------
//MMC/SD Command and Data Control Register field descriptions (MSC_CMDAT)
//--------------------------------------------------------------------------
#define MSC_CMDAT_RESP_FORMAT_MASK      ( 7 << 0 )
#define MSC_CMDAT_RESPONSE_NONE         ( 0 << 0 )/* No response */
#define MSC_CMDAT_RESPONSE_R1           ( 1 << 0 )/* Format R1 and R1b */
#define MSC_CMDAT_RESPONSE_R2           ( 2 << 0 )/* Format R2 */
#define MSC_CMDAT_RESPONSE_R3           ( 3 << 0 )/* Format R3 */
#define MSC_CMDAT_RESPONSE_R4           ( 4 << 0 )/* Format R4 */
#define MSC_CMDAT_RESPONSE_R5           ( 5 << 0 )/* Format R5 */
#define MSC_CMDAT_RESPONSE_R6           ( 6 << 0 )/* Format R6 */
#define MSC_CMDAT_RESPONSE_R7           ( 7 << 0 )/* Format R7 */

#define MSC_CMDAT_DATA_EN               ( 1 << 3 )
#define MSC_CMDAT_WRRD_MASK             ( 1 << 4 )
#define MSC_CMDAT_WRITE                 ( 1 << 4 )
#define MSC_CMDAT_READ                  ( 0 << 4 )
#define MSC_CMDAT_STREAM_BLOCK          ( 1 << 5 )
#define MSC_CMDAT_BUSY                  ( 1 << 6 )
#define MSC_CMDAT_INIT                  ( 1 << 7 )
#define MSC_CMDAT_DMA_EN                ( 1 << 8 )

#define MSC_CMDAT_BUS_WIDTH_MASK        ( 3 << 9 )
#define MSC_CMDAT_BUS_WIDTH_1BIT        ( 0 << 9 )
#define MSC_CMDAT_BUS_WIDTH_4BIT        ( 2 << 9 )
#define MSC_CMDAT_BUS_WIDTH_8BIT        ( 3 << 9 )

#define MSC_CMDAT_STOP_ABORT            ( 1 << 11 )

#define MSC_CMDAT_TTRG_MASK             ( 3 << 12 )
#define MSC_CMDAT_TTRG_08               ( 0 << 12 )
#define MSC_CMDAT_TTRG_16               ( 1 << 12 )
#define MSC_CMDAT_TTRG_24               ( 2 << 12 )

#define MSC_CMDAT_RTRG_MASK             ( 3 << 14 )
#define MSC_CMDAT_RTRG_08               ( 0 << 14 )
#define MSC_CMDAT_RTRG_16               ( 1 << 14 )
#define MSC_CMDAT_RTRG_24               ( 2 << 14 )

#define MSC_CMDAT_SEND_AS_STOP          ( 1 << 16 )
#define MSC_CMDAT_SDIO_PRDT             ( 1 << 17 )
#define MSC_CMDAT_READ_CEATA            ( 1 << 30 )
#define MSC_CMDAT_CCS_EXPECTED          ( 1 << 31 )

//--------------------------------------------------------------------------
// IRQ Number descriptions
//--------------------------------------------------------------------------
#define MSC_DATA_TRAN_DONE      ( 1 << 0 )
#define MSC_PRG_DONE            ( 1 << 1 )
#define MSC_END_CMD_RES         ( 1 << 2 )
#define MSC_RXFIFO_RD_REQ       ( 1 << 5 )
#define MSC_TXFIFO_WR_REQ       ( 1 << 6 )
#define MSC_SDIO                ( 1 << 7 )
#define MSC_TIME_OUT_READ       ( 1 << 8 )
#define MSC_TIME_OUT_RES        ( 1 << 9 )
#define MSC_CRC_WRITE_ERR       ( 1 << 10 )
#define MSC_CRC_READ_ERR        ( 1 << 11 )
#define MSC_CRC_RES_ERR         ( 1 << 12 )
#define MSC_DATA_FIFO_EMP       ( 1 << 13 )
#define MSC_DATA_FIFO_FULL      ( 1 << 14 )
#define MSC_AUTO_CMD_DONE       ( 1 << 15 )
#define MSC_DMAEND              ( 1 << 16 )
#define MSC_BAR                 ( 1 << 17 )
#define MSC_BAE                 ( 1 << 18 )
#define MSC_BDE                 ( 1 << 19 )
#define MSC_BCE                 ( 1 << 20 )
#define MSC_WR_ALL_DONE         ( 1 << 23 )
#define MSC_PIN_LEVEL           ( 1 << 24 )
#define MSC_DMA_DATA_DONE       ( 1 << 31 )

/* MSC Interrupts Mask Register (MSC_IMASK) */
#define	IMASK_DMA_DATA_DONE		(1 << 31)
#define	IMASK_WR_ALL_DONE		(1 << 23)
#define	IMASK_AUTO_CMD23_DONE	(1 << 30)
#define	IMASK_SVS				(1 << 29)
#define	IMASK_PIN_LEVEL_SHF		24
#define	IMASK_PIN_LEVEL_MASK	(0x1f << IMASK_PIN_LEVEL_SHF)
#define	IMASK_BCE				(1 << 20)
#define	IMASK_BDE				(1 << 19)
#define	IMASK_BAE				(1 << 18)
#define	IMASK_BAR				(1 << 17)
#define	IMASK_DMAEND			(1 << 16)
#define	IMASK_AUTO_CMD12_DONE	(1 << 15)
#define	IMASK_DATA_FIFO_FULL	(1 << 14)
#define	IMASK_DATA_FIFO_EMP		(1 << 13)
#define	IMASK_CRC_RES_ERR		(1 << 12)
#define	IMASK_CRC_READ_ERR		(1 << 11)
#define	IMASK_CRC_WRITE_ERR		(1 << 10)
#define	IMASK_TIME_OUT_RES		(1 << 9)
#define	IMASK_TIME_OUT_READ		(1 << 8)
#define	IMASK_SDIO				(1 << 7)
#define	IMASK_TXFIFO_WR_REQ		(1 << 6)
#define	IMASK_RXFIFO_RD_REQ		(1 << 5)
#define	IMASK_END_CMD_RES		(1 << 2)
#define	IMASK_PRG_DONE			(1 << 1)
#define	IMASK_DATA_TRAN_DONE	(1 << 0)

/* MSC Interrupts Status Register (MSC_IREG) */
#define IFLG_DMA_DATA_DONE      (1 << 31)
#define IFLG_WR_ALL_DONE        (1 << 23)
#define IFLG_AUTO_CMD23_DONE        (1 << 30)
#define IFLG_SVS            (1 << 29)
#define IFLG_PIN_LEVEL_SHF      24
#define IFLG_PIN_LEVEL_MASK     (0x1f << IFLG_PIN_LEVEL_SHF)
#define IFLG_BCE            (1 << 20)
#define IFLG_BDE            (1 << 19)
#define IFLG_BAE            (1 << 18)
#define IFLG_BAR            (1 << 17)
#define IFLG_DMAEND         (1 << 16)
#define IFLG_AUTO_CMD12_DONE        (1 << 15)
#define IFLG_DATA_FIFO_FULL     (1 << 14)
#define IFLG_DATA_FIFO_EMP      (1 << 13)
#define IFLG_CRC_RES_ERR        (1 << 12)
#define IFLG_CRC_READ_ERR       (1 << 11)
#define IFLG_CRC_WRITE_ERR      (1 << 10)
#define IFLG_TIMEOUT_RES        (1 << 9)
#define IFLG_TIMEOUT_READ       (1 << 8)
#define IFLG_SDIO           (1 << 7)
#define IFLG_TXFIFO_WR_REQ      (1 << 6)
#define IFLG_RXFIFO_RD_REQ      (1 << 5)
#define IFLG_END_CMD_RES        (1 << 2)
#define IFLG_PRG_DONE           (1 << 1)
#define IFLG_DATA_TRAN_DONE     (1 << 0)

/* MSC Low Power Mode Register (MSC_LPM) */
#define LPM_DRV_SEL_SHF         30
#define LPM_DRV_SEL_MASK        (0x3 << LPM_DRV_SEL_SHF)
#define LPM_SMP_SEL             (1 << 29)
#define LPM_LPM                 (1 << 0)

/* MSC DMA Control Register (MSC_DMAC) */
#define DMAC_MODE_SEL           (1 << 7)
#define DMAC_AOFST_SHF          5
#define DMAC_AOFST_MASK         (0x3 << DMAC_AOFST_SHF)
#define DMAC_AOFST_0            (0 << DMAC_AOFST_SHF)
#define DMAC_AOFST_1            (1 << DMAC_AOFST_SHF)
#define DMAC_AOFST_2            (2 << DMAC_AOFST_SHF)
#define DMAC_AOFST_3            (3 << DMAC_AOFST_SHF)
#define DMAC_ALIGNEN            (1 << 4)
#define DMAC_INCR_SHF           2
#define DMAC_INCR_MASK          (0x3 << DMAC_INCR_SHF)
#define DMAC_INCR_16            (0 << DMAC_INCR_SHF)
#define DMAC_INCR_32            (1 << DMAC_INCR_SHF)
#define DMAC_INCR_64            (2 << DMAC_INCR_SHF)
#define DMAC_DMASEL             (1 << 1)
#define DMAC_DMAEN              (1 << 0)

/* MSC DMA Command Register (MSC_DMACMD) */
#define DMACMD_IDI_SHF          24
#define DMACMD_IDI_MASK         (0xff << DMACMD_IDI_SHF)
#define DMACMD_ID_SHF           16
#define DMACMD_ID_MASK          (0xff << DMACMD_ID_SHF)
#define DMACMD_OFFSET_SHF       9
#define DMACMD_OFFSET_MASK      (0x3 << DMACMD_OFFSET_SHF)
#define DMACMD_ALIGN_EN         (1 << 8)
#define DMACMD_ENDI             (1 << 1)
#define DMACMD_LINK             (1 << 0)

/* Error codes */
enum mmc_result_t {
    MMC_NO_RESPONSE        = -1,
    MMC_NO_ERROR           = 0,
    MMC_ERROR_OUT_OF_RANGE,
    MMC_ERROR_ADDRESS,
    MMC_ERROR_BLOCK_LEN,
    MMC_ERROR_ERASE_SEQ,
    MMC_ERROR_ERASE_PARAM,
    MMC_ERROR_WP_VIOLATION,
    MMC_ERROR_CARD_IS_LOCKED,
    MMC_ERROR_LOCK_UNLOCK_FAILED,
    MMC_ERROR_COM_CRC,
    MMC_ERROR_ILLEGAL_COMMAND,
    MMC_ERROR_CARD_ECC_FAILED,
    MMC_ERROR_CC,
    MMC_ERROR_GENERAL,
    MMC_ERROR_UNDERRUN,
    MMC_ERROR_OVERRUN,
    MMC_ERROR_CID_CSD_OVERWRITE,
    MMC_ERROR_STATE_MISMATCH,
    MMC_ERROR_HEADER_MISMATCH,
    MMC_ERROR_TIMEOUT,
    MMC_ERROR_CRC,
    MMC_ERROR_DRIVER_FAILURE,
};

struct jz_sdma_desc
{
    volatile rt_uint32_t nda;
    volatile rt_uint32_t da;
    volatile rt_uint32_t len;
    volatile rt_uint32_t dcmd;
};

struct jzmmc_host
{
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req  *req;
    struct rt_mmcsd_cmd  *cmd;
	struct rt_mmcsd_data *data;

    uint32_t hw_base;
    uint32_t msc_clock;
    uint32_t irqno;
    uint32_t flags;
    /* 确保是32字节对齐 */
    struct jz_sdma_desc dma_desc;
    //uint32_t reserve[4];
    
	unsigned int cmdat;
    struct rt_completion completion;
    

    struct clk *clock;
    struct clk *clock_gate;

    uint8_t * _dma_buffer;
    int sdio_clk; /* clock for sdio */
    rt_uint32_t current_status;
};

int jzmmc_sdio_init(void);

#endif /* DRV_MMC_H__ */

