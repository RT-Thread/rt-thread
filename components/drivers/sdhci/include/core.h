#ifndef __SDHCI_CORE_H__
#define __SDHCI_CORE_H__


#define lower_32_bits(n) ((rt_uint32_t)((n) & 0xffffffff))
#define upper_32_bits(n) ((rt_uint32_t)(((n) >> 16) >> 16))


struct mmc_data;

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


struct mmc_host;


// void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq);
// int mmc_wait_for_cmd(struct mmc_host *host, struct mmc_command *cmd,
// 		int retries);

// int mmc_hw_reset(struct mmc_card *card);
// int mmc_sw_reset(struct mmc_card *card);
// void mmc_set_data_timeout(struct mmc_data *data, const struct mmc_card *card);
#endif
