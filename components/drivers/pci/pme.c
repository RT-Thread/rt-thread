/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

/**
 * @file pme.c
 * @brief PCI Power Management Event (PME) support
 *
 * Implements PCI Power Management capability handling:
 * - PME capability detection and initialization
 * - Device wake-up enable/disable (PME# signal control)
 * - Power state transition tracking
 *
 * The PM Capability Register layout is documented in the PCI Power
 * Management Specification:
 *   bits 31:27 - PME Support (which power states support PME#)
 *   bits 26    - D2 Support
 *   bits 25    - D1 Support
 *   bits 24:22 - Aux Current
 *   bit  21    - Device Specific Initialization
 *   bit  20    - Immediate Readiness on Return to D0
 *   bit  19    - PME Clock
 *   bits 18:16 - Version
 *   bits 15:8  - Next Capability Pointer
 *   bits 7:0   - Capability ID (always 0x01 for PM)
 */

#include <drivers/pci.h>
#include <drivers/core/power_domain.h>

#define DBG_TAG "pci.pme"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/**
 * @brief Initialize PME (Power Management Event) for a PCI device
 *
 * Finds the PCI Power Management capability (PCIY_PMG) and reads the
 * PM Capabilities register to determine which power states support PME#.
 * If PME is supported, it disables PME# initially (safe default state).
 *
 * @param[in] pdev PCI device
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

/**
 * @brief Enable or disable device wake-up from a given power state
 *
 * If the device supports PME in the requested state (or D3cold as
 * fallback), enables the PME# signal. Otherwise disables it.
 *
 * @param[in] pdev   PCI device
 * @param[in] state  Power state to check PME capability for (RT_PCI_D0 through RT_PCI_D3COLD)
 * @param[in] enable RT_TRUE to enable wake, RT_FALSE to disable
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters
 */
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

/**
 * @brief Internal: Activate or deactivate the PME# signal
 *
 * Modifies the PME_Status and PME_Enable bits in the Power Management
 * Control/Status register (PMCSR). Writing 1 to PME_Status clears it
 * (per PCI spec).
 *
 * @param[in] pdev   PCI device
 * @param[in] enable RT_TRUE to enable PME#, RT_FALSE to disable
 */
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
    pdev->pm_enabled = enable;
}

/**
 * @brief Public API: Activate or deactivate PME# and manage power domain
 *
 * In addition to the PMCSR manipulation, also attaches/detaches
 * the device's power domain for runtime PM.
 *
 * @param[in] pdev   PCI device
 * @param[in] enable RT_TRUE to enable PME#, RT_FALSE to disable
 */
void rt_pci_pme_active(struct rt_pci_device *pdev, rt_bool_t enable)
{
    if (!pdev)
    {
        return;
    }

    pci_pme_active(pdev, enable);
    rt_dm_power_domain_attach(&pdev->parent, enable);
}
