#ifndef __SDHCI_VOLTAGE_H__
#define __SDHCI_VOLTAGE_H__

struct regulator {
    const char *supply_name;
};

int regulator_get_current_limit(struct regulator *regulator);

int regulator_is_supported_voltage(struct regulator *regulator,
                   int min_uV, int max_uV);
int regulator_enable(struct regulator *regulator);

void regulator_disable(struct regulator *regulator);
#endif