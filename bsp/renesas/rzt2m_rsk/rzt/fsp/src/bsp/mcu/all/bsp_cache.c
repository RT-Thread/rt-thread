/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_PRV_SCTLR_ELX_BIT_I                 (0x1000U)
#define BSP_PRV_SCTLR_ELX_BIT_C                 (0x4U)
#define BSP_PRV_SCTLR_ELX_BIT_M                 (0x1U)

#define BSP_PRV_CLIDR_CTYPE_OFFSET              (3U)
#define BSP_PRV_CLIDR_CTYPE_MASK                (7U)
#define BSP_PRV_CLIDR_CTYPE_EXIST_DATACACHE     (2U)
#define BSP_PRV_CLIDR_LOC_OFFSET                (24U)
#define BSP_PRV_CLIDR_LOC_MASK                  (7U)

#define BSP_PRV_CCSIDR_LINESIZE_OFFSET          (0U)
#define BSP_PRV_CCSIDR_LINESIZE_MASK            (7U)
#define BSP_PRV_CCSIDR_LINESIZE_ACTUAL_VALUE    (4U)
#define BSP_PRV_CCSIDR_ASSOCIATIVITY_OFFSET     (3U)
#define BSP_PRV_CCSIDR_ASSOCIATIVITY_MASK       (0x3FFU)
#define BSP_PRV_CCSIDR_NUMSETS_OFFSET           (13U)
#define BSP_PRV_CCSIDR_NUMSETS_MASK             (0x7FFFU)
#define BSP_PRV_CCSIDR_SHIFT_MAX                (32U)

#define BSP_PRV_CSSELR_LEVEL_OFFSET             (1U)

#define BSP_PRV_CTR_IMINLINE_OFFSET             (0U)
#define BSP_PRV_CTR_IMINLINE_MASK               (0xFU)
#define BSP_PRV_CTR_IMINLINE_NUMBER_OF_WORDS    (4U)
#define BSP_PRV_CTR_IMINLINE_ADDRESS_MASK       (1U)
#define BSP_PRV_CTR_DMINLINE_OFFSET             (16U)
#define BSP_PRV_CTR_DMINLINE_MASK               (0xFU)
#define BSP_PRV_CTR_DMINLINE_NUMBER_OF_WORDS    (4U)
#define BSP_PRV_CTR_DMINLINE_ADDRESS_MASK       (1U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enable instruction caching.
 **********************************************************************************************************************/
void R_BSP_CacheEnableInst (void)
{
    uintptr_t sctlr;

    sctlr  = __get_SCTLR();
    sctlr |= BSP_PRV_SCTLR_ELX_BIT_I;

    __asm volatile ("DSB SY");

    __set_SCTLR(sctlr);

    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Enable data caching.
 **********************************************************************************************************************/
void R_BSP_CacheEnableData (void)
{
    uintptr_t sctlr;

    sctlr  = __get_SCTLR();
    sctlr |= BSP_PRV_SCTLR_ELX_BIT_C;

    __asm volatile ("DSB SY");

    __set_SCTLR(sctlr);

    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Enable memory protect.
 **********************************************************************************************************************/
void R_BSP_CacheEnableMemoryProtect (void)
{
    uintptr_t sctlr;

    sctlr  = __get_SCTLR();
    sctlr |= BSP_PRV_SCTLR_ELX_BIT_M;

    __asm volatile ("DSB SY");

    __set_SCTLR(sctlr);

    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Disable instruction caching.
 **********************************************************************************************************************/
void R_BSP_CacheDisableInst (void)
{
    uintptr_t sctlr;

    sctlr  = __get_SCTLR();
    sctlr &= ~(BSP_PRV_SCTLR_ELX_BIT_I);

    __asm volatile ("DSB SY");

    __set_SCTLR(sctlr);

    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Disable data caching.
 **********************************************************************************************************************/
void R_BSP_CacheDisableData (void)
{
    uintptr_t sctlr;

    sctlr  = __get_SCTLR();
    sctlr &= ~(BSP_PRV_SCTLR_ELX_BIT_C);

    __asm volatile ("DSB SY");

    __set_SCTLR(sctlr);

    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Disable memory protect.
 **********************************************************************************************************************/
void R_BSP_CacheDisableMemoryProtect (void)
{
    uintptr_t sctlr;

    sctlr  = __get_SCTLR();
    sctlr &= ~(BSP_PRV_SCTLR_ELX_BIT_M);

    __asm volatile ("DSB SY");

    __set_SCTLR(sctlr);

    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Clean data cache by set/way.
 * Clean means writing the cache data to memory and clear the dirty bits
 * if there is a discrepancy between the cache and memory data.
 **********************************************************************************************************************/
void R_BSP_CacheCleanAll (void)
{
    uintptr_t clidr;
    uintptr_t clidr_loc;
    uintptr_t clidr_ctype;
    uintptr_t clidr_ctype_shift;

    uintptr_t csselr;
    uintptr_t csselr_level;

    uintptr_t ccsidr;
    uintptr_t ccsidr_linesize;
    uintptr_t ccsidr_associativity;
    uintptr_t ccsidr_associativity_clz;
    uintptr_t ccsidr_associativity_value;
    uintptr_t ccsidr_associativity_msb;
    uintptr_t ccsidr_numsets;
    uintptr_t ccsidr_numsets_total;

    uintptr_t dccsw;

    __asm volatile ("DSB SY");

    __set_ICIALLU(0);

    __asm volatile ("DMB SY");

    /* Reads the maximum level of cache implemented */
    clidr     = __get_CLIDR();
    clidr_loc = (clidr >> BSP_PRV_CLIDR_LOC_OFFSET) & BSP_PRV_CLIDR_LOC_MASK;

    /* If the cache does not exist, do not process */
    if (0 != clidr_loc)
    {
        /* Loop until all levels of cache are processed */
        for (csselr = 0; csselr < clidr_loc; csselr++)
        {
            /* Read the current level cache type */
            clidr_ctype_shift = csselr * BSP_PRV_CLIDR_CTYPE_OFFSET;
            clidr_ctype       = (clidr >> clidr_ctype_shift) & BSP_PRV_CLIDR_CTYPE_MASK;

            /* If no data cache exists in the current level of cache, do not process  */
            if (BSP_PRV_CLIDR_CTYPE_EXIST_DATACACHE <= clidr_ctype)
            {
                /* Set the current level to Cache Size Selection Register */
                csselr_level = csselr << BSP_PRV_CSSELR_LEVEL_OFFSET;
                __set_CSSELR(csselr_level);

                __asm volatile ("DSB SY");

                /* Read the line size, number of ways, and number of sets for the current level of cache */
                ccsidr          = __get_CCSIDR();
                ccsidr_linesize = ((ccsidr >> BSP_PRV_CCSIDR_LINESIZE_OFFSET) & BSP_PRV_CCSIDR_LINESIZE_MASK) +
                                  BSP_PRV_CCSIDR_LINESIZE_ACTUAL_VALUE;
                ccsidr_associativity = (ccsidr >> BSP_PRV_CCSIDR_ASSOCIATIVITY_OFFSET) &
                                       BSP_PRV_CCSIDR_ASSOCIATIVITY_MASK;
                ccsidr_numsets = (ccsidr >> BSP_PRV_CCSIDR_NUMSETS_OFFSET) & BSP_PRV_CCSIDR_NUMSETS_MASK;

                /* Count consecutive number of 0 starting from the most significant bit (CLZ = Count Leading Zeros) */
                ccsidr_associativity_clz = __CLZ((uint32_t) ccsidr_associativity);
                if (BSP_PRV_CCSIDR_SHIFT_MAX == ccsidr_associativity_clz)
                {
                    ccsidr_associativity_clz--;
                }
                else
                {
                    /* Do Nothing */
                }

                /* Loop until all sets are processed */
                while (1)
                {
                    /* Working copy of number of ways */
                    ccsidr_associativity_value = ccsidr_associativity;

                    /* Loop until all ways are processed */
                    while (1)
                    {
                        ccsidr_associativity_msb = (ccsidr_associativity_value << ccsidr_associativity_clz) |
                                                   csselr_level;                                /* Left shift way */
                        ccsidr_numsets_total = ccsidr_numsets << ccsidr_linesize;               /* Left shift set */
                        dccsw                = ccsidr_associativity_msb | ccsidr_numsets_total; /* Combine set and way */

                        /* DCCSW - Data or unified Cache line Clean by Set/Way */
                        __set_DCCSW(dccsw);

                        if (0 != ccsidr_associativity_value)
                        {
                            ccsidr_associativity_value--;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (0 != ccsidr_numsets)
                    {
                        ccsidr_numsets--;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                /* Do Nothing */
            }
        }

        __asm volatile ("DSB SY");
        __asm volatile ("ISB SY");
    }
    else
    {
        /* Do Nothing */
    }
}

/*******************************************************************************************************************//**
 * Invalidate data cache by set/way.
 * Also Invalidate instruction cache.
 *
 * Invalidate means to delete cache data.
 **********************************************************************************************************************/
void R_BSP_CacheInvalidateAll (void)
{
    uintptr_t clidr;
    uintptr_t clidr_loc;
    uintptr_t clidr_ctype;
    uintptr_t clidr_ctype_shift;

    uintptr_t csselr;
    uintptr_t csselr_level;

    uintptr_t ccsidr;
    uintptr_t ccsidr_linesize;
    uintptr_t ccsidr_associativity;
    uintptr_t ccsidr_associativity_clz;
    uintptr_t ccsidr_associativity_value;
    uintptr_t ccsidr_associativity_msb;
    uintptr_t ccsidr_numsets;
    uintptr_t ccsidr_numsets_total;

    uintptr_t dcisw;

    __asm volatile ("DSB SY");

    __set_ICIALLU(0);

    __asm volatile ("DMB SY");

    /* Reads the maximum level of cache implemented */
    clidr     = __get_CLIDR();
    clidr_loc = (clidr >> BSP_PRV_CLIDR_LOC_OFFSET) & BSP_PRV_CLIDR_LOC_MASK;

    /* If the cache does not exist, do not process */
    if (0 != clidr_loc)
    {
        /* Loop until all levels of cache are processed */
        for (csselr = 0; csselr < clidr_loc; csselr++)
        {
            /* Read the current level cache type */
            clidr_ctype_shift = csselr * BSP_PRV_CLIDR_CTYPE_OFFSET;
            clidr_ctype       = (clidr >> clidr_ctype_shift) & BSP_PRV_CLIDR_CTYPE_MASK;

            /* If no data cache exists in the current level of cache, do not process  */
            if (BSP_PRV_CLIDR_CTYPE_EXIST_DATACACHE <= clidr_ctype)
            {
                /* Set the current level to Cache Size Selection Register */
                csselr_level = csselr << BSP_PRV_CSSELR_LEVEL_OFFSET;
                __set_CSSELR(csselr_level);

                __asm volatile ("DSB SY");

                /* Read the line size, number of ways, and number of sets for the current level of cache */
                ccsidr          = __get_CCSIDR();
                ccsidr_linesize = ((ccsidr >> BSP_PRV_CCSIDR_LINESIZE_OFFSET) & BSP_PRV_CCSIDR_LINESIZE_MASK) +
                                  BSP_PRV_CCSIDR_LINESIZE_ACTUAL_VALUE;
                ccsidr_associativity = (ccsidr >> BSP_PRV_CCSIDR_ASSOCIATIVITY_OFFSET) &
                                       BSP_PRV_CCSIDR_ASSOCIATIVITY_MASK;
                ccsidr_numsets = (ccsidr >> BSP_PRV_CCSIDR_NUMSETS_OFFSET) & BSP_PRV_CCSIDR_NUMSETS_MASK;

                /* Count consecutive number of 0 starting from the most significant bit (CLZ = Count Leading Zeros) */
                ccsidr_associativity_clz = __CLZ((uint32_t) ccsidr_associativity);
                if (BSP_PRV_CCSIDR_SHIFT_MAX == ccsidr_associativity_clz)
                {
                    ccsidr_associativity_clz--;
                }
                else
                {
                    /* Do Nothing */
                }

                /* Loop until all sets are processed */
                while (1)
                {
                    /* Working copy of number of ways */
                    ccsidr_associativity_value = ccsidr_associativity;

                    /* Loop until all ways are processed */
                    while (1)
                    {
                        ccsidr_associativity_msb = (ccsidr_associativity_value << ccsidr_associativity_clz) |
                                                   csselr_level;                                /* Left shift way */
                        ccsidr_numsets_total = ccsidr_numsets << ccsidr_linesize;               /* Left shift set */
                        dcisw                = ccsidr_associativity_msb | ccsidr_numsets_total; /* Combine set and way */

                        /* DCISW - Data or unified Cache line Invalidate by Set/Way */
                        __set_DCISW(dcisw);

                        if (0 != ccsidr_associativity_value)
                        {
                            ccsidr_associativity_value--;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (0 != ccsidr_numsets)
                    {
                        ccsidr_numsets--;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                /* Do Nothing */
            }
        }

        __asm volatile ("DSB SY");
        __asm volatile ("ISB SY");
    }
    else
    {
        /* Do Nothing */
    }
}

/*******************************************************************************************************************//**
 * Clean and Invalidate data cache by set/way.
 * Also Invalidate instruction cache.
 *
 * Clean means writing the cache data to memory and clear the dirty bits
 * if there is a discrepancy between the cache and memory data.
 *
 * Invalidate means to delete cache data.
 **********************************************************************************************************************/
void R_BSP_CacheCleanInvalidateAll (void)
{
    uintptr_t clidr;
    uintptr_t clidr_loc;
    uintptr_t clidr_ctype;
    uintptr_t clidr_ctype_shift;

    uintptr_t csselr;
    uintptr_t csselr_level;

    uintptr_t ccsidr;
    uintptr_t ccsidr_linesize;
    uintptr_t ccsidr_associativity;
    uintptr_t ccsidr_associativity_clz;
    uintptr_t ccsidr_associativity_value;
    uintptr_t ccsidr_associativity_msb;
    uintptr_t ccsidr_numsets;
    uintptr_t ccsidr_numsets_total;

    uintptr_t dccisw;

    __asm volatile ("DSB SY");

    __set_ICIALLU(0);

    __asm volatile ("DMB SY");

    /* Reads the maximum level of cache implemented */
    clidr     = __get_CLIDR();
    clidr_loc = (clidr >> BSP_PRV_CLIDR_LOC_OFFSET) & BSP_PRV_CLIDR_LOC_MASK;

    /* If the cache does not exist, do not process */
    if (0 != clidr_loc)
    {
        /* Loop until all levels of cache are processed */
        for (csselr = 0; csselr < clidr_loc; csselr++)
        {
            /* Read the current level cache type */
            clidr_ctype_shift = csselr * BSP_PRV_CLIDR_CTYPE_OFFSET;
            clidr_ctype       = (clidr >> clidr_ctype_shift) & BSP_PRV_CLIDR_CTYPE_MASK;

            /* If no data cache exists in the current level of cache, do not process  */
            if (BSP_PRV_CLIDR_CTYPE_EXIST_DATACACHE <= clidr_ctype)
            {
                /* Set the current level to Cache Size Selection Register */
                csselr_level = csselr << BSP_PRV_CSSELR_LEVEL_OFFSET;
                __set_CSSELR(csselr_level);

                __asm volatile ("DSB SY");

                /* Read the line size, number of ways, and number of sets for the current level of cache */
                ccsidr          = __get_CCSIDR();
                ccsidr_linesize = ((ccsidr >> BSP_PRV_CCSIDR_LINESIZE_OFFSET) & BSP_PRV_CCSIDR_LINESIZE_MASK) +
                                  BSP_PRV_CCSIDR_LINESIZE_ACTUAL_VALUE;
                ccsidr_associativity = (ccsidr >> BSP_PRV_CCSIDR_ASSOCIATIVITY_OFFSET) &
                                       BSP_PRV_CCSIDR_ASSOCIATIVITY_MASK;
                ccsidr_numsets = (ccsidr >> BSP_PRV_CCSIDR_NUMSETS_OFFSET) & BSP_PRV_CCSIDR_NUMSETS_MASK;

                /* Count consecutive number of 0 starting from the most significant bit (CLZ = Count Leading Zeros) */
                ccsidr_associativity_clz = __CLZ((uint32_t) ccsidr_associativity);
                if (BSP_PRV_CCSIDR_SHIFT_MAX == ccsidr_associativity_clz)
                {
                    ccsidr_associativity_clz--;
                }
                else
                {
                    /* Do Nothing */
                }

                /* Loop until all sets are processed */
                while (1)
                {
                    /* Working copy of number of ways */
                    ccsidr_associativity_value = ccsidr_associativity;

                    /* Loop until all ways are processed */
                    while (1)
                    {
                        ccsidr_associativity_msb = (ccsidr_associativity_value << ccsidr_associativity_clz) |
                                                   csselr_level;                                /* Left shift way */
                        ccsidr_numsets_total = ccsidr_numsets << ccsidr_linesize;               /* Left shift set */
                        dccisw               = ccsidr_associativity_msb | ccsidr_numsets_total; /* Combine set and way */

                        /* DCCISW - Data or unified Cache line Clean and Invalidate by Set/Way */
                        __set_DCCISW(dccisw);

                        if (0 != ccsidr_associativity_value)
                        {
                            ccsidr_associativity_value--;
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (0 != ccsidr_numsets)
                    {
                        ccsidr_numsets--;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                /* Do Nothing */
            }
        }

        __asm volatile ("DSB SY");
        __asm volatile ("ISB SY");
    }
    else
    {
        /* Do Nothing */
    }
}

/*******************************************************************************************************************//**
 * Clean data cache and Invalidate instruction cache by address.
 *
 * Clean means writing the cache data to memory and clear the dirty bits
 * if there is a discrepancy between the cache and memory data.
 *
 * Invalidate means to delete cache data.
 *
 * @param[in] base_address    Start address of area you want to Clean.
 * @param[in] length          Size of area you want to Clean.
 **********************************************************************************************************************/
void R_BSP_CacheCleanRange (uintptr_t base_address, uintptr_t length)
{
    uintptr_t end_address;
    uintptr_t ctr;

    uintptr_t dminline;
    uintptr_t dminline_size;
    uintptr_t dccvac;

    uintptr_t iminline;
    uintptr_t iminline_size;
    uintptr_t icivau;

    end_address = base_address + length;

    /* Calculate data cache line size */
    ctr           = __get_CTR();
    dminline      = (ctr >> BSP_PRV_CTR_DMINLINE_OFFSET) & BSP_PRV_CTR_DMINLINE_MASK;
    dminline_size = (BSP_PRV_CTR_DMINLINE_NUMBER_OF_WORDS << dminline);

    /* Align base address with cache line */
    dccvac = base_address & ~(dminline_size - BSP_PRV_CTR_DMINLINE_ADDRESS_MASK);
    do
    {
        /* Data or unified Cache line Clean by VA to PoC */
        __set_DCCVAC(dccvac);

        dccvac += dminline_size;       /* Next data line */
    } while (end_address > dccvac);

    __asm volatile ("DSB SY");

    /* Calculate instruction cache line size */
    iminline      = (ctr >> BSP_PRV_CTR_IMINLINE_OFFSET) & BSP_PRV_CTR_IMINLINE_MASK;
    iminline_size = (BSP_PRV_CTR_IMINLINE_NUMBER_OF_WORDS << iminline);

    /* Align base address with cache line */
    icivau = base_address & ~(iminline_size - BSP_PRV_CTR_IMINLINE_ADDRESS_MASK);
    do
    {
        /* Instruction Cache line Invalidate by VA to PoU */
        __set_ICIVAU(icivau);

        icivau += iminline_size;       /* Next data line */
    } while (end_address == icivau);

    __asm volatile ("DSB SY");
    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Invalidate instruction and data cache by address.
 *
 * Invalidate means to delete cache data.
 *
 * @param[in] base_address    Start address of area you want to Invalidate.
 * @param[in] length          Size of area you want to Invalidate.
 **********************************************************************************************************************/
void R_BSP_CacheInvalidateRange (uintptr_t base_address, uintptr_t length)
{
    uintptr_t end_address;
    uintptr_t ctr;

    uintptr_t dminline;
    uintptr_t dminline_size;
    uintptr_t dcivac;

    uintptr_t iminline;
    uintptr_t iminline_size;
    uintptr_t icivau;

    end_address = base_address + length;

    /* Calculate data cache line size */
    ctr           = __get_CTR();
    dminline      = (ctr >> BSP_PRV_CTR_DMINLINE_OFFSET) & BSP_PRV_CTR_DMINLINE_MASK;
    dminline_size = (BSP_PRV_CTR_DMINLINE_NUMBER_OF_WORDS << dminline);

    /* Align base address with cache line */
    dcivac = base_address & ~(dminline_size - BSP_PRV_CTR_DMINLINE_ADDRESS_MASK);
    do
    {
        /* Data or unified Cache line Invalidate by VA to PoC */
        __set_DCIVAC(dcivac);

        dcivac += dminline_size;       /* Next data line */
    } while (end_address > dcivac);

    __asm volatile ("DSB SY");

    /* Calculate instruction cache line size */
    iminline      = (ctr >> BSP_PRV_CTR_IMINLINE_OFFSET) & BSP_PRV_CTR_IMINLINE_MASK;
    iminline_size = (BSP_PRV_CTR_IMINLINE_NUMBER_OF_WORDS << iminline);

    /* Align base address with cache line */
    icivau = base_address & ~(iminline_size - BSP_PRV_CTR_IMINLINE_ADDRESS_MASK);
    do
    {
        /* Instruction Cache line Invalidate by VA to PoU */
        __set_ICIVAU(icivau);

        icivau += iminline_size;       /* Next data line */
    } while (end_address == icivau);

    __asm volatile ("DSB SY");
    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Clean and Invalidate data cache and Invalidate instruction cache by address.
 *
 * Clean means writing the cache data to memory and clear the dirty bits
 * if there is a discrepancy between the cache and memory data.
 *
 * Invalidate means to delete cache data.
 *
 * @param[in] base_address    Start address of area you want to Clean and Invalidate.
 * @param[in] length          Size of area you want to Clean and Invalidate.
 **********************************************************************************************************************/
void R_BSP_CacheCleanInvalidateRange (uintptr_t base_address, uintptr_t length)
{
    uintptr_t end_address;
    uintptr_t ctr;

    uintptr_t dminline;
    uintptr_t dminline_size;
    uintptr_t dccivac;

    uintptr_t iminline;
    uintptr_t iminline_size;
    uintptr_t icivau;

    end_address = base_address + length;

    /* Calculate data cache line size */
    ctr           = __get_CTR();
    dminline      = (ctr >> BSP_PRV_CTR_DMINLINE_OFFSET) & BSP_PRV_CTR_DMINLINE_MASK;
    dminline_size = (BSP_PRV_CTR_DMINLINE_NUMBER_OF_WORDS << dminline);

    /* Align base address with cache line */
    dccivac = base_address & ~(dminline_size - BSP_PRV_CTR_DMINLINE_ADDRESS_MASK);
    do
    {
        /* Data or unified Cache line Clean and Invalidate by VA to PoC */
        __set_DCCIVAC(dccivac);

        dccivac += dminline_size;      /* Next data line */
    } while (end_address > dccivac);

    __asm volatile ("DSB SY");

    /* Calculate instruction cache line size */
    iminline      = (ctr >> BSP_PRV_CTR_IMINLINE_OFFSET) & BSP_PRV_CTR_IMINLINE_MASK;
    iminline_size = (BSP_PRV_CTR_IMINLINE_NUMBER_OF_WORDS << iminline);

    /* Align base address with cache line */
    icivau = base_address & ~(iminline_size - BSP_PRV_CTR_IMINLINE_ADDRESS_MASK);
    do
    {
        /* Instruction Cache line Invalidate by VA to PoU */
        __set_ICIVAU(icivau);

        icivau += iminline_size;       /* Next data line */
    } while (end_address == icivau);

    __asm volatile ("DSB SY");
    __asm volatile ("ISB SY");
}

/*******************************************************************************************************************//**
 * Powers on and off the L3 cache way.
 * CA55 only.
 **********************************************************************************************************************/
void R_BSP_CacheL3PowerCtrl (void)
{
    r_bsp_cache_l3_power_ctrl();
}

/*******************************************************************************************************************//**
 * @} (end addtogroup BSP_MCU)
 **********************************************************************************************************************/
