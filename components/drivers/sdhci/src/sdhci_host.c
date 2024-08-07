#include "sdhci_host.h"
#include <rtthread.h>
#include <drivers/core/dm.h>

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

int mmc_send_abort_tuning(struct mmc_host *host, rt_uint32_t opcode)
{
    return 0;
}
int mmc_of_parse(struct mmc_host *host)
{
    struct rt_device *dev = host->parent;
    rt_uint32_t bus_width;

    if (!dev || !dev->ofw_node)
        return 0;

    /* "bus-width" is translated to MMC_CAP_*_BIT_DATA flags */
    if (rt_dm_dev_prop_read_u32(dev, "bus-width", &bus_width) < 0)
    {
        bus_width = 1;
    }

    switch (bus_width)
    {
    case 8:
        host->caps |= MMC_CAP_8_BIT_DATA;
        break; /* Hosts capable of 8-bit can also do 4 bits */
    case 4:
        host->caps |= MMC_CAP_4_BIT_DATA;
        break;
    case 1:
        break;
    default:
        return -EINVAL;
    }

    /* f_max is obtained from the optional "max-frequency" property */
    rt_dm_dev_prop_read_u32(dev, "max-frequency", &host->f_max);

    if (rt_dm_dev_prop_read_bool(dev, "cap-mmc-highspeed"))
    {
        host->caps |= MMC_CAP_MMC_HIGHSPEED;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-hs200-1_8v"))
    {
        host->caps |= MMC_CAP2_HS200_1_8V_SDR;
    }

    if (rt_dm_dev_prop_read_bool(dev, "non-removable"))
    {
        host->caps |= MMC_CAP_NONREMOVABLE;
    }

    if (rt_dm_dev_prop_read_bool(dev, "no-sdio"))
    {
        host->caps2 |= MMC_CAP2_NO_SDIO;
    }

    if (rt_dm_dev_prop_read_bool(dev, "no-sd"))
    {
        host->caps2 |= MMC_CAP2_NO_SD;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-ddr-3_3v"))
    {
        host->caps |= MMC_CAP_3_3V_DDR;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-ddr-1_8v"))
    {
        host->caps |= MMC_CAP_1_8V_DDR;
    }

    if (rt_dm_dev_prop_read_bool(dev, "mmc-ddr-1_2v"))
    {
        host->caps |= MMC_CAP_1_2V_DDR;
    }

    return 0;
}