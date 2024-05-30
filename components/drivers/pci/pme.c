/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <drivers/pci.h>
#include <drivers/core/power_domain.h>

#define DBG_TAG "pci.pme"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * Power Management Capability Register:
 *
 *   31      27 26  25 24    22  21  20  19 18  16 15        8 7              0
 *  +---------+---+---+--------+---+---+---+------+-----------+----------------+
 *  |         |   |   |        |   |   |   |      |           | Capabilitiy ID |
 *  +---------+---+---+--------+---+---+---+------+-----------+----------------+
 *       ^      ^   ^      ^     ^   ^   ^     ^        ^
 *       |      |   |      |     |   |   |     |        |
 *       |      |   |      |     |   |   |     |        +---- Next Capabilitiy Pointer
 *       |      |   |      |     |   |   |     +------------- Version
 *       |      |   |      |     |   |   +------------------- PME Clock
 *       |      |   |      |     |   +----------------------- Immediate Readiness on Return to D0
 *       |      |   |      |     +--------------------------- Device Specifiic Initializtion
 *       |      |   |      +--------------------------------- Aux Current
 *       |      |   +---------------------------------------- D1 Support
 *       |      +-------------------------------------------- D2 Support
 *       +--------------------------------------------------- PME Support
 */

void rt_pci_pme_init(struct rt_pci_device *pdev)
{
    rt_uint16_t pmc;

    if (!pdev || !(pdev->pme_cap = rt_pci_find_capability(pdev, PCIY_PMG)))
    {
        return;
    }

    rt_pci_read_config_u16(pdev, pdev->pme_cap + PCIR_POWER_CAP, &pmc);

    if ((pmc & PCIM_PCAP_SPEC) > 3)
    {
        LOG_E("%s: Unsupported PME CAP regs spec %u",
                rt_dm_dev_get_name(&pdev->parent), pmc & PCIM_PCAP_SPEC);

        return;
    }

    pmc &= PCIM_PCAP_PMEMASK;

    if (pmc)
    {
        pdev->pme_support = RT_FIELD_GET(PCIM_PCAP_PMEMASK, pmc);

        rt_pci_pme_active(pdev, RT_FALSE);
    }
}

rt_err_t rt_pci_enable_wake(struct rt_pci_device *pdev,
        enum rt_pci_power state, rt_bool_t enable)
{
    if (!pdev || state >= RT_PCI_PME_MAX)
    {
        return -RT_EINVAL;
    }

    if (enable)
    {
        if (rt_pci_pme_capable(pdev, state) ||
            rt_pci_pme_capable(pdev, RT_PCI_D3COLD))
        {
            rt_pci_pme_active(pdev, RT_EOK);
        }
    }
    else
    {
        rt_pci_pme_active(pdev, RT_FALSE);
    }

    return RT_EOK;
}

static void pci_pme_active(struct rt_pci_device *pdev, rt_bool_t enable)
{
    rt_uint16_t pmcsr;

    if (!pdev->pme_support)
    {
        return;
    }

    rt_pci_read_config_u16(pdev, pdev->pme_cap + PCIR_POWER_STATUS, &pmcsr);
    /* Clear PME_Status by writing 1 to it and enable PME# */
    pmcsr |= PCIM_PSTAT_PME | PCIM_PSTAT_PMEENABLE;

    if (!enable)
    {
        pmcsr &= ~PCIM_PSTAT_PMEENABLE;
    }

    rt_pci_write_config_u16(pdev, pdev->pme_cap + PCIR_POWER_STATUS, pmcsr);
}

void rt_pci_pme_active(struct rt_pci_device *pdev, rt_bool_t enable)
{
    if (!pdev)
    {
        return;
    }

    pci_pme_active(pdev, enable);
    rt_dm_power_domain_attach(&pdev->parent, enable);
}
