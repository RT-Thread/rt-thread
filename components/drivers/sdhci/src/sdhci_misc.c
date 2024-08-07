#include "sdhci_misc.h"
#include <rtthread.h>


rt_bool_t mmc_can_gpio_cd(struct mmc_host *host)
{
    return RT_FALSE;
}