#include "sdhci_host.h"
#include <rtthread.h>

int mmc_gpio_get_cd(struct mmc_host *host)
{
    return -ENOSYS;
}

void mmc_detect_change(struct mmc_host *host, unsigned long delay)
{

}


int mmc_regulator_set_vqmmc(struct mmc_host *mmc, struct rt_mmcsd_io_cfg *ios)
{
    return 0;
}

rt_bool_t mmc_can_gpio_ro(struct mmc_host *host)
{
    return RT_FALSE;
}

int mmc_gpio_get_ro(struct mmc_host *host)
{
    return 0;
}