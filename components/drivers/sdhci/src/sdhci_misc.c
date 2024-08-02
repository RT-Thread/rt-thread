#include "sdhci_misc.h"
#include <rtthread.h>

int regulator_is_supported_voltage(struct regulator *regulator,
				   int min_uV, int max_uV)
{
	return 0;
}

int regulator_enable(struct regulator *regulator)
{
	return 0;

}


int regulator_get_current_limit(struct regulator *regulator)
{
    return 0;
}

rt_bool_t mmc_can_gpio_cd(struct mmc_host *host)
{
    return RT_FALSE;
}