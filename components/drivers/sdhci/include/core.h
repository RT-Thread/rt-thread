
#define lower_32_bits(n) ((rt_uint32_t)((n) & 0xffffffff))
#define upper_32_bits(n) ((rt_uint32_t)(((n) >> 16) >> 16))

int regulator_is_supported_voltage(struct regulator *regulator,
				   int min_uV, int max_uV)
{
	// struct regulator_dev *rdev = regulator->rdev;
	// int i, voltages, ret;

	// /* If we can't change voltage check the current voltage */
	// if (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE)) {
	// 	ret = regulator_get_voltage(regulator);
	// 	if (ret >= 0)
	// 		return min_uV <= ret && ret <= max_uV;
	// 	else
	// 		return ret;
	// }

	// /* Any voltage within constrains range is fine? */
	// if (rdev->desc->continuous_voltage_range)
	// 	return min_uV >= rdev->constraints->min_uV &&
	// 			max_uV <= rdev->constraints->max_uV;

	// ret = regulator_count_voltages(regulator);
	// if (ret < 0)
	// 	return 0;
	// voltages = ret;

	// for (i = 0; i < voltages; i++) {
	// 	ret = regulator_list_voltage(regulator, i);

	// 	if (ret >= min_uV && ret <= max_uV)
	// 		return 1;
	// }

	// return 0;
}

int regulator_enable(struct regulator *regulator)
{
	// struct regulator_dev *rdev = regulator->rdev;
	// struct ww_acquire_ctx ww_ctx;
	// int ret;

	// regulator_lock_dependent(rdev, &ww_ctx);
	// ret = _regulator_enable(regulator);
	// regulator_unlock_dependent(rdev, &ww_ctx);

	// return ret;
}


int regulator_get_current_limit(struct regulator *regulator)
{
    // return 0;
}

void dma_free_coherent(struct rt_device *dev, size_t size,
        void *cpu_addr, dma_addr_t dma_handle)
{
}

rt_bool_t mmc_can_gpio_cd(struct mmc_host *host)
{
    if(host->slot.handler_priv->cd)
    {
        struct mmc_gpio *ctx = host->slot.handler_priv;

	    return ctx->cd_gpio ? true : false;

    }
    return false;
}

struct mmc_data;
struct mmc_request;

enum mmc_blk_status {
	MMC_BLK_SUCCESS = 0,
	MMC_BLK_PARTIAL,
	MMC_BLK_CMD_ERR,
	MMC_BLK_RETRY,
	MMC_BLK_ABORT,
	MMC_BLK_DATA_ERR,
	MMC_BLK_ECC_ERR,
	MMC_BLK_NOMEDIUM,
	MMC_BLK_NEW_REQUEST,
};

struct mmc_command {
	u32			opcode;
	u32			arg;
#define MMC_CMD23_ARG_REL_WR	(1 << 31)
#define MMC_CMD23_ARG_TAG_REQ	(1 << 29)
	u32			resp[4];
	unsigned int		flags;		/* expected response type */
#define MMC_RSP_PRESENT	(1 << 0)
#define MMC_RSP_136	(1 << 1)		/* 136 bit response */
#define MMC_RSP_CRC	(1 << 2)		/* expect valid crc */
#define MMC_RSP_BUSY	(1 << 3)		/* card may send busy */
#define MMC_RSP_OPCODE	(1 << 4)		/* response contains opcode */

#define MMC_CMD_MASK	(3 << 5)		/* non-SPI command type */
#define MMC_CMD_AC	(0 << 5)
#define MMC_CMD_ADTC	(1 << 5)
#define MMC_CMD_BC	(2 << 5)
#define MMC_CMD_BCR	(3 << 5)

#define MMC_RSP_SPI_S1	(1 << 7)		/* one status byte */
#define MMC_RSP_SPI_S2	(1 << 8)		/* second byte */
#define MMC_RSP_SPI_B4	(1 << 9)		/* four data bytes */
#define MMC_RSP_SPI_BUSY (1 << 10)		/* card may send busy */

/*
 * These are the native response types, and correspond to valid bit
 * patterns of the above flags.  One additional valid pattern
 * is all zeros, which means we don't expect a response.
 */
#define MMC_RSP_NONE	(0)
#define MMC_RSP_R1	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R1B	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE|MMC_RSP_BUSY)
#define MMC_RSP_R2	(MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#define MMC_RSP_R3	(MMC_RSP_PRESENT)
#define MMC_RSP_R4	(MMC_RSP_PRESENT)
#define MMC_RSP_R5	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R6	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R7	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

/* Can be used by core to poll after switch to MMC HS mode */
#define MMC_RSP_R1_NO_CRC	(MMC_RSP_PRESENT|MMC_RSP_OPCODE)

#define mmc_resp_type(cmd)	((cmd)->flags & (MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC|MMC_RSP_BUSY|MMC_RSP_OPCODE))

/*
 * These are the SPI response types for MMC, SD, and SDIO cards.
 * Commands return R1, with maybe more info.  Zero is an error type;
 * callers must always provide the appropriate MMC_RSP_SPI_Rx flags.
 */
#define MMC_RSP_SPI_R1	(MMC_RSP_SPI_S1)
#define MMC_RSP_SPI_R1B	(MMC_RSP_SPI_S1|MMC_RSP_SPI_BUSY)
#define MMC_RSP_SPI_R2	(MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R3	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R4	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R5	(MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R7	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)

#define mmc_spi_resp_type(cmd)	((cmd)->flags & \
		(MMC_RSP_SPI_S1|MMC_RSP_SPI_BUSY|MMC_RSP_SPI_S2|MMC_RSP_SPI_B4))

/*
 * These are the command types.
 */
#define mmc_cmd_type(cmd)	((cmd)->flags & MMC_CMD_MASK)

	unsigned int		retries;	/* max number of retries */
	int			error;		/* command error */

/*
 * Standard errno values are used for errors, but some have specific
 * meaning in the MMC layer:
 *
 * ETIMEDOUT    Card took too long to respond
 * EILSEQ       Basic format problem with the received or sent data
 *              (e.g. CRC check failed, incorrect opcode in response
 *              or bad end bit)
 * EINVAL       Request cannot be performed because of restrictions
 *              in hardware and/or the driver
 * ENOMEDIUM    Host can determine that the slot is empty and is
 *              actively failing requests
 */

	unsigned int		busy_timeout;	/* busy detect timeout in ms */
	struct mmc_data		*data;		/* data segment associated with cmd */
	struct mmc_request	*mrq;		/* associated request */
};


struct mmc_host;
struct mmc_request {
	struct mmc_command	*sbc;		/* SET_BLOCK_COUNT for multiblock */
	struct mmc_command	*cmd;
	struct mmc_data		*data;
	struct mmc_command	*stop;

	struct completion	completion;
	struct completion	cmd_completion;
	void			(*done)(struct mmc_request *);/* completion function */
	/*
	 * Notify uppers layers (e.g. mmc block driver) that recovery is needed
	 * due to an error associated with the mmc_request. Currently used only
	 * by CQE.
	 */
	void			(*recovery_notifier)(struct mmc_request *);
	struct mmc_host		*host;

	/* Allow other commands during this ongoing data transfer or busy wait */
	bool			cap_cmd_during_tfr;

	int			tag;

#ifdef CONFIG_MMC_CRYPTO
	const struct bio_crypt_ctx *crypto_ctx;
	int			crypto_key_slot;
#endif
};

struct mmc_card;

void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq);
int mmc_wait_for_cmd(struct mmc_host *host, struct mmc_command *cmd,
		int retries);

int mmc_hw_reset(struct mmc_card *card);
int mmc_sw_reset(struct mmc_card *card);
void mmc_set_data_timeout(struct mmc_data *data, const struct mmc_card *card);

