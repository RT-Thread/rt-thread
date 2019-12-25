/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdint.h>
#include "nrf.h"
#include "nrf_mpu_lib.h"
#include "app_util_platform.h"
#include "sdk_config.h"

#if NRF_MPU_LIB_CLI_CMDS
#include "nrf_cli.h"
#endif

#define NRF_LOG_MODULE_NAME nrf_mpu_lib

#if NRF_MPU_LIB_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       NRF_MPU_LIB_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  NRF_MPU_LIB_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR NRF_MPU_LIB_CONFIG_DEBUG_COLOR
#else
#define NRF_LOG_LEVEL       0
#endif
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

// Check module requirements.
STATIC_ASSERT(__MPU_PRESENT);
STATIC_ASSERT(__CORTEX_M == 4);

/**@brief Return the number of unified regions avaiable in MPU. */
__STATIC_INLINE unsigned int nrf_mpu_lib_get_number_of_regions(void)
{
    return (MPU->TYPE & MPU_TYPE_DREGION_Msk) >> MPU_TYPE_DREGION_Pos;
}

/**@brief Extract human-readable memory type from attributes. */
static const char *nrf_mpu_lib_mem_type(uint32_t attributes)
{
    attributes &= MPU_RASR_TEX_Msk | MPU_RASR_C_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk;

    switch (attributes)
    {
        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
            return "Strongly-ordered, Shareable";

        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
            return "Device, Shareable";

        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x01 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x01 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
            return "Normal";

        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x01 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x01 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
            return "Normal, Shareable";

        case (0x02 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x02 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
            return "Device";

        default:
            if (((attributes & MPU_RASR_TEX_Msk) >> MPU_RASR_TEX_Pos) >= 0x04)
            {
                return (attributes & MPU_RASR_S_Msk) ? "Normal, Shareable" : "Normal";
            }
            else
            {
                return "Reserved or Implementation Defined";
            }
    }

    // Not reached.
}

/**@brief Extract human-readable access level from attributes. */
static const char *nrf_mpu_lib_mem_access(uint32_t attributes)
{
    switch ((attributes & MPU_RASR_AP_Msk) >> MPU_RASR_AP_Pos)
    {
        case 0x00:
            return "--/--";

        case 0x01:
            return "RW/--";

        case 0x02:
            return "RW/RO";

        case 0x03:
            return "RW/RW";

        case 0x04:
            return "\?\?/\?\?";

        case 0x05:
            return "RO/--";

        case 0x06:
        case 0x07:
            return "RO/RO";

        default:
            return "Unknown";
    }

    // Not reached.
}

ret_code_t nrf_mpu_lib_init(void)
{
    unsigned int i, regions;

    // Make sure that MPU uses unified regions. Separate are not supported.
    if ((MPU->TYPE & MPU_TYPE_SEPARATE_Msk) >> MPU_TYPE_SEPARATE_Pos)
    {
        NRF_LOG_ERROR("Non-unified MPU is not supported!");
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Make sure that we can handle all avaiable regions.
    regions = nrf_mpu_lib_get_number_of_regions();
    if (regions > ((1 << (8 * sizeof(nrf_mpu_lib_region_t))) - 1))
    {
        NRF_LOG_ERROR("MPU with %u regions is not supported!", regions);
        return NRF_ERROR_NOT_SUPPORTED;
    }

    // Disable MPU.
    MPU->CTRL = 0;

    // Clear all regions.
    for (i = 0; i < regions; i++)
    {
        MPU->RNR    = i;
        MPU->RASR   = 0;
        MPU->RBAR   = 0;
    }

    /* Enable MPU */
    MPU->CTRL = (1 << MPU_CTRL_ENABLE_Pos) |
                (1 << MPU_CTRL_PRIVDEFENA_Pos);

    // Make sure that configuration changes are active.
    __DSB();

    NRF_LOG_INFO("MPU Initalized. %u unified regions avaiable.", regions);

    return NRF_SUCCESS;
}

ret_code_t nrf_mpu_lib_region_create(nrf_mpu_lib_region_t *p_region,
                                     void *address,
                                     size_t size,
                                     uint32_t attributes)
{
    unsigned long addr = (unsigned long)(address);
    unsigned int i, regions = nrf_mpu_lib_get_number_of_regions();

    // Size must be power of 2, greater than or equal to 32
    if ((size & (size - 1)) || (size < 32))
    {
        NRF_LOG_ERROR("Cannot create MPU region 0x%08X-0x%08X: Region size is not valid!", addr, addr + size - 1);
        return NRF_ERROR_INVALID_PARAM;
    }

    // Region must be aligned to it's size.
    if (addr & (size - 1))
    {
        NRF_LOG_ERROR("Cannot create MPU region 0x%08X-0x%08X: Region alignment is not valid!", addr, addr + size - 1);
        return NRF_ERROR_INVALID_PARAM;
    }

    // Check if attributes are valid.
    if (attributes & ~MPU_RASR_ATTRS_Msk)
    {
        NRF_LOG_ERROR("Cannot create MPU region 0x%08X-0x%08X: Region attributes are not valid!", addr, addr + size - 1);
        return NRF_ERROR_INVALID_PARAM;
    }

    NRF_LOG_DEBUG("MPU region creating (location: 0x%08X-0x%08X)",
                 addr,
                 addr + size - 1);
    // Create region.
    CRITICAL_REGION_ENTER();
    for (i = 0; i < regions; i++)
    {
        MPU->RNR = i;
        if (MPU->RASR & MPU_RASR_ENABLE_Msk)
        {
            continue;
        }

        MPU->RBAR = addr;
        MPU->RASR = attributes |
                    (1 << MPU_RASR_ENABLE_Pos) |
                    ((31 - __CLZ(size) - 1) << MPU_RASR_SIZE_Pos);

        break;
    }
    CRITICAL_REGION_EXIT();

    if (i >= regions)
    {
        NRF_LOG_ERROR("Cannot create MPU region 0x%08X-0x%08X: No free region found!", addr, addr + size - 1);
        return NRF_ERROR_NO_MEM;
    }

    // Apply changes.
    __DSB();

    // Save region number;
    *p_region = i;

    NRF_LOG_DEBUG("MPU region %u created (location: 0x%08X-0x%08X, access: %s, type: %s, flags: %s).",
                 i,
                 addr,
                 addr + size - 1,
                 (uint32_t)nrf_mpu_lib_mem_access(attributes),
                 (uint32_t)nrf_mpu_lib_mem_type(attributes),
                 (uint32_t)((attributes & MPU_RASR_XN_Msk) ? "XN" : "--"));

    return NRF_SUCCESS;
}

ret_code_t nrf_mpu_lib_region_destroy(nrf_mpu_lib_region_t region)
{
    if (region >= nrf_mpu_lib_get_number_of_regions())
    {
        NRF_LOG_ERROR("Cannot destroy MPU region %u: Invaid region!", region);
        return NRF_ERROR_INVALID_PARAM;
    }

    CRITICAL_REGION_ENTER();
    MPU->RNR    = region;
    MPU->RASR   = 0;
    MPU->RBAR   = 0;
    CRITICAL_REGION_EXIT();

    // Apply changes.
    __DSB();

    NRF_LOG_DEBUG("MPU region %u destroyed.", region);

    return NRF_SUCCESS;
}

#if NRF_MPU_LIB_CLI_CMDS

/**@brief Extract human-readable caching policy from attributes. */
static const char *nrf_mpu_lib_mem_caching(uint32_t attributes)
{
    static const char *caching[] =
    {
        "--/--",    "WBWA/--",  "WT/--",    "WB/--",
        "--/WBWA",  "WBWA/WBWA","WT/WBWA",  "WB/WBWA",
        "--/WT",    "WBWA/WT",  "WT/WT",    "WB/WT",
        "--/WB",    "WBWA/WB",  "WT/WB",    "WB/WB",
    };

    uint32_t tex = (attributes & MPU_RASR_TEX_Msk) >> MPU_RASR_TEX_Pos;
    uint32_t c = (attributes & MPU_RASR_C_Msk) >> MPU_RASR_C_Pos;
    uint32_t b = (attributes & MPU_RASR_B_Msk) >> MPU_RASR_B_Pos;

    attributes &= MPU_RASR_TEX_Msk | MPU_RASR_C_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk;

    switch (attributes)
    {
        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x01 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x01 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x01 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
        case (0x02 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
        case (0x02 << MPU_RASR_TEX_Pos) | (0 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (1 << MPU_RASR_S_Pos):
            return "--/--";

        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (0 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
            return "WT/WT";

        case (0x00 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
            return "WB/WB";

        case (0x01 << MPU_RASR_TEX_Pos) | (1 << MPU_RASR_C_Pos) | (1 << MPU_RASR_B_Pos) | (0 << MPU_RASR_S_Pos):
            return "WBWA/WBWA";

        default:
            if (tex >= 0x04)
            {
                return caching[((tex & 0x03) << 2) | ((c & 0x01) << 1) | (b & 0x01)];
            }
            break;
    }

    return "Unknown";
}
/**@brief Implementation of "mpu info" command. */
static void nrf_mpu_lib_cmd_info(nrf_cli_t const *p_cli, size_t argc, char **argv)
{
    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    unsigned int i, regions = nrf_mpu_lib_get_number_of_regions();

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "MPU State: %s, %u unified regions aviable.\r\n\r\n",
                    (MPU->CTRL & MPU_CTRL_ENABLE_Msk) ? "Enabled" : "Disabled",
                    regions);


    for (i = 0; i < regions; i++)
    {
        uint32_t rasr, rbar;
        uint32_t size;

        CRITICAL_REGION_ENTER();
        MPU->RNR = i;
        rasr = MPU->RASR;
        rbar = MPU->RBAR;
        CRITICAL_REGION_EXIT();

        if ((rasr & MPU_RASR_ENABLE_Msk) == 0)
        {
            nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Region %u: Disabled\r\n", i);
            continue;
        }

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "Region %u: Enabled\r\n", i);

        size = 1ul << (((rasr & MPU_RASR_SIZE_Msk) >> MPU_RASR_SIZE_Pos) + 1);
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t- Location:\t0x%08X-0x%08X (size: %u bytes)\r\n",
                       rbar,
                       rbar + size - 1,
                       size);

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t- Access:\t%s\r\n", nrf_mpu_lib_mem_access(rasr));
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t- Type:\t\t%s\r\n", nrf_mpu_lib_mem_type(rasr));
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t- Caching:\t%s\r\n", nrf_mpu_lib_mem_caching(rasr));
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\t- Flags:\t%s\r\n\r\n", (rasr & MPU_RASR_XN_Msk) ? "XN" : "--");
    }
}

/**@brief Implementation of "mpu dump" command. */
static void nrf_mpu_lib_cmd_dump(nrf_cli_t const *p_cli, size_t argc, char **argv)
{
    unsigned int i, regions = nrf_mpu_lib_get_number_of_regions();

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "MPU_TYPE:\t0x%08X\r\n", MPU->TYPE);
    nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "MPU_CTRL:\t0x%08X\r\n", MPU->CTRL);

    for (i = 0; i < regions; i++)
    {
        uint32_t rasr, rbar;

        CRITICAL_REGION_ENTER();
        MPU->RNR = i;
        rasr = MPU->RASR;
        rbar = MPU->RBAR;
        CRITICAL_REGION_EXIT();

        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "\r\nMPU_RBAR[%u]:\t0x%08X\r\n", i, rbar);
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL, "MPU_RASR[%u]:\t0x%08X\r\n", i, rasr);
    }
}

/**@brief Implementation of "mpu" command. */
static void nrf_mpu_lib_cmd_unknown(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    if ((argc == 1) || nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "%s: unknown parameter: %s\r\n", argv[0], argv[1]);
}

// Register "mpu" command and it's subcommands in CLI.
NRF_CLI_CREATE_STATIC_SUBCMD_SET(nrf_mpu_lib_commands)
{
     NRF_CLI_CMD(dump, NULL, "Dump MPU registers.", nrf_mpu_lib_cmd_dump),
     NRF_CLI_CMD(info, NULL, "Print information about MPU state.", nrf_mpu_lib_cmd_info),
     NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(mpu, &nrf_mpu_lib_commands, "Commands for MPU management", nrf_mpu_lib_cmd_unknown);

#endif //NRF_MPU_LIB_CLI_CMDS
