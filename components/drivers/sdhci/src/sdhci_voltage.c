#include "sdhci_voltage.h"
#include "sdhci_host.h"
int mmc_regulator_get_supply(struct mmc_host *mmc)
{
    mmc->supply.vmmc = -RT_NULL;
    mmc->supply.vqmmc = -RT_NULL;

    return 0;
}
int regulator_get_current_limit(struct regulator *regulator)
{
    return 0;
}

int regulator_is_supported_voltage(struct regulator *regulator,

                   int min_uV, int max_uV)
{
    return 0;
}

int regulator_enable(struct regulator *regulator)
{


	return 0;
}
void regulator_disable(struct regulator *regulator)
{


}
