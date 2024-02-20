/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-05-05     linzhenxing     first version
 */
#include <rtthread.h>
#include <dfs_fs.h>
#include <drivers/gpt.h>
#include <drivers/mmcsd_core.h>

#define DBG_TAG               "GPT"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

#define min(a, b) a < b ? a : b
static int force_gpt = 0;
static gpt_header *_gpt;
static gpt_entry *_ptes;
#define GPT_TYPE 1
#define MBR_TYPE 0

static inline int efi_guidcmp (gpt_guid_t left, gpt_guid_t right)
{
    return rt_memcmp(&left, &right, sizeof (gpt_guid_t));
}

static uint32_t last_lba(struct rt_mmcsd_card *card)
{
    RT_ASSERT(card != RT_NULL);
    return (card->card_sec_cnt) - 1;
}

static inline int pmbr_part_valid(gpt_mbr_record *part)
{
    if (part->os_type != EFI_PMBR_OSTYPE_EFI_GPT)
    {
        goto invalid;
    }

    /* set to 0x00000001 (i.e., the LBA of the GPT Partition Header) */
    if ((uint32_t)(part->starting_lba) != GPT_PRIMARY_PARTITION_TABLE_LBA)
    {
        goto invalid;
    }

    return GPT_MBR_PROTECTIVE;
invalid:
    return 0;
}

/*
*
* return ret
* ret = 0, invalid mbr
* ret = 1, protect mbr
* ret = 2, hybrid mbr
*/
int is_pmbr_valid(legacy_mbr *mbr, uint64_t total_sectors)
{
    uint32_t sz = 0;
    int i, part = 0, ret = 0; /* invalid by default */

    if (!mbr || (uint16_t)(mbr->signature) != MSDOS_MBR_SIGNATURE)
    {
        goto done;
    }

    for (i = 0; i < 4; i++)
    {
        ret = pmbr_part_valid(&mbr->partition_record[i]);
        if (ret == GPT_MBR_PROTECTIVE)
        {
            part = i;
            /*
             * Ok, we at least know that there's a protective MBR,
             * now check if there are other partition types for
             * hybrid MBR.
             */
            goto check_hybrid;
        }
    }

    if (ret != GPT_MBR_PROTECTIVE)
    {
        goto done;
    }

check_hybrid:
    for (i = 0; i < 4; i++)
    {
        if ((mbr->partition_record[i].os_type !=
            EFI_PMBR_OSTYPE_EFI_GPT) &&
            (mbr->partition_record[i].os_type != 0x00))
        {
            ret = GPT_MBR_HYBRID;
        }

    }

    /*
     * Protective MBRs take up the lesser of the whole disk
     * or 2 TiB (32bit LBA), ignoring the rest of the disk.
     * Some partitioning programs, nonetheless, choose to set
     * the size to the maximum 32-bit limitation, disregarding
     * the disk size.
     *
     * Hybrid MBRs do not necessarily comply with this.
     *
     * Consider a bad value here to be a warning to support dd'ing
     * an image from a smaller disk to a larger disk.
     */
    if (ret == GPT_MBR_PROTECTIVE)
    {
        sz = (uint32_t)(mbr->partition_record[part].size_in_lba);
        if (sz != (uint32_t) total_sectors - 1 && sz != 0xFFFFFFFF)
        {
            LOG_I("GPT: mbr size in lba (%u) different than whole disk (%u).",
                 sz, min(total_sectors - 1, 0xFFFFFFFF));
        }
    }

done:
    return ret;

}

static gpt_entry *alloc_read_gpt_entries(struct rt_mmcsd_card *card, gpt_header *gpt)
{
    size_t count;
    gpt_entry *pte;

    if (!gpt)
    {
        return RT_NULL;
    }

    count = (size_t)(gpt->num_partition_entries) * (gpt->sizeof_partition_entry);
    if (!count)
    {
        return RT_NULL;
    }

    pte = rt_malloc(count);
    if (!pte)
        return RT_NULL;

    if (read_lba(card, (size_t)(gpt->partition_entry_lba),(uint8_t *)pte, count/512) != RT_EOK)
    {
        rt_free(pte);
        return RT_NULL;
    }
    return pte;

}

static gpt_header *alloc_read_gpt_header(struct rt_mmcsd_card *card, size_t lba)
{
    gpt_header *gpt;
    void *buf;

    buf = rt_malloc(512);
    if (!buf)
    {
        return RT_NULL;
    }

    if (read_lba(card, lba, (uint8_t *)buf, 1) != RT_EOK)
    {
        rt_free(buf);
        return RT_NULL;
    }
    gpt = (gpt_header *)buf;

    return gpt;
}

static int is_gpt_valid(struct rt_mmcsd_card *card, size_t lba, gpt_header **gpt, gpt_entry **ptes)
{
    size_t lastlba;

    if (!ptes || !gpt)
    {
        return 0;
    }

    *gpt = alloc_read_gpt_header(card, lba);
    if (!(*gpt))
    {
        return 0;
    }

    /* Check the GUID Partition Table signature */
    if ((uint64_t)((*gpt)->signature) != GPT_HEADER_SIGNATURE)
    {
        LOG_E("GUID Partition Table Header signature is wrong:"
             "%ld != %ld",(uint64_t)((*gpt)->signature),(uint64_t)GPT_HEADER_SIGNATURE);
        goto fail;
    }

    /* Check the GUID Partition Table header size is too small */
    if ((uint32_t)((*gpt)->header_size) < sizeof(gpt_header))
    {
        LOG_E("GUID Partition Table Header size is too small: %u < %zu",
            (uint32_t)((*gpt)->header_size),sizeof(gpt_header));
        goto fail;
    }

    /* Check that the start_lba entry points to the LBA that contains
     * the GUID Partition Table */
    if ((uint64_t)((*gpt)->start_lba) != lba)
    {
        LOG_E("GPT start_lba incorrect: %ld != %ld",
             (uint64_t)((*gpt)->start_lba),
             (uint64_t)lba);
        goto fail;
    }

    /* Check the first_usable_lba and last_usable_lba are
     * within the disk.
     */
    lastlba = last_lba(card);
    if ((uint64_t)((*gpt)->first_usable_lba) > lastlba)
    {
        LOG_E("GPT: first_usable_lba incorrect: %ld > %ld",
             ((uint64_t)((*gpt)->first_usable_lba)),
             (size_t)lastlba);
        goto fail;
    }

    if ((uint64_t)((*gpt)->last_usable_lba) > lastlba)
    {
        LOG_E("GPT: last_usable_lba incorrect: %ld > %ld",
             (uint64_t)((*gpt)->last_usable_lba),
             (size_t)lastlba);
        goto fail;
    }

    if ((uint64_t)((*gpt)->last_usable_lba) < (uint64_t)((*gpt)->first_usable_lba))
    {
        LOG_E("GPT: last_usable_lba incorrect: %ld > %ld",
             (uint64_t)((*gpt)->last_usable_lba),
             (uint64_t)((*gpt)->first_usable_lba));
        goto fail;
    }
    /* Check that sizeof_partition_entry has the correct value */
    if ((uint32_t)((*gpt)->sizeof_partition_entry) != sizeof(gpt_entry)) {
        LOG_E("GUID Partition Entry Size check failed.");
        goto fail;
    }

    *ptes = alloc_read_gpt_entries(card, *gpt);
    if (!(*ptes))
    {
        goto fail;
    }

    /* We're done, all's well */
    return 1;

 fail:
    rt_free(*gpt);
    *gpt = RT_NULL;
    return 0;
}

/**
 * is_pte_valid() - tests one PTE for validity
 * pte:pte to check
 * lastlba: last lba of the disk
 *
 * Description: returns 1 if valid,  0 on error.
 */
static inline int is_pte_valid(const gpt_entry *pte, const size_t lastlba)
{
    if ((!efi_guidcmp(pte->partition_type_guid, NULL_GUID)) ||
        (uint64_t)(pte->starting_lba) > lastlba         ||
        (uint64_t)(pte->ending_lba)   > lastlba)
    {
        return 0;
    }

    return 1;
}

/**
 * compare_gpts() - Search disk for valid GPT headers and PTEs
 * pgpt: primary GPT header
 * agpt: alternate GPT header
 * lastlba: last LBA number
 *
 * Description: Returns nothing.  Sanity checks pgpt and agpt fields
 * and prints warnings on discrepancies.
 *
 */
static void compare_gpts(gpt_header *pgpt, gpt_header *agpt, size_t lastlba)
{
    int error_found = 0;
    if (!pgpt || !agpt)
    {
        return;
    }

    if ((uint64_t)(pgpt->start_lba) != (uint64_t)(agpt->alternate_lba))
    {
        LOG_I("GPT:Primary header LBA != Alt. header alternate_lba");
        LOG_I("GPT:%lld != %lld",
               (uint64_t)(pgpt->start_lba),
                       (uint64_t)(agpt->alternate_lba));
        error_found++;
    }

    if ((uint64_t)(pgpt->alternate_lba) != (uint64_t)(agpt->start_lba))
    {
        LOG_I("GPT:Primary header alternate_lba != Alt. header start_lba");
        LOG_I("GPT:%lld != %lld",
               (uint64_t)(pgpt->alternate_lba),
                       (uint64_t)(agpt->start_lba));
        error_found++;
    }

    if ((uint64_t)(pgpt->first_usable_lba) != (uint64_t)(agpt->first_usable_lba))
    {
        LOG_I("GPT:first_usable_lbas don't match.");
        LOG_I("GPT:%lld != %lld",
               (uint64_t)(pgpt->first_usable_lba),
                       (uint64_t)(agpt->first_usable_lba));
        error_found++;
    }

    if ((uint64_t)(pgpt->last_usable_lba) != (uint64_t)(agpt->last_usable_lba))
    {
        LOG_I("GPT:last_usable_lbas don't match.");
        LOG_I("GPT:%lld != %lld",
               (uint64_t)(pgpt->last_usable_lba),
                       (uint64_t)(agpt->last_usable_lba));
        error_found++;
    }

    if (efi_guidcmp(pgpt->disk_guid, agpt->disk_guid))
    {
        LOG_I("GPT:disk_guids don't match.");
        error_found++;
    }

    if ((pgpt->num_partition_entries) != (agpt->num_partition_entries))
    {
        LOG_I("GPT:num_partition_entries don't match: "
               "0x%x != 0x%x",
               (pgpt->num_partition_entries),
               (agpt->num_partition_entries));
        error_found++;
    }

    if ((pgpt->sizeof_partition_entry) != (agpt->sizeof_partition_entry))
    {
        LOG_I("GPT:sizeof_partition_entry values don't match: "
               "0x%x != 0x%x",
                       (pgpt->sizeof_partition_entry),
               (agpt->sizeof_partition_entry));
        error_found++;
    }

    if ((pgpt->partition_entry_array_crc32) != (agpt->partition_entry_array_crc32))
    {
        LOG_I("GPT:partition_entry_array_crc32 values don't match: "
               "0x%x != 0x%x",
                       (pgpt->partition_entry_array_crc32),
               (agpt->partition_entry_array_crc32));
        error_found++;
    }

    if ((pgpt->alternate_lba) != lastlba)
    {
        LOG_I("GPT:Primary header thinks Alt. header is not at the end of the disk.");
        LOG_I("GPT:%lld != %lld",
            (uint64_t)(pgpt->alternate_lba),
            (size_t)lastlba);
        error_found++;
    }

    if ((agpt->start_lba) != lastlba)
    {
        LOG_I("GPT:Alternate GPT header not at the end of the disk.");
        LOG_I("GPT:%lld != %lld",
            (uint64_t)(agpt->start_lba),
            (size_t)lastlba);
        error_found++;
    }

    if (error_found)
    {
        LOG_I("GPT: Use GNU Parted to correct GPT errors.");
    }
    return;
}

/**
 * find_valid_gpt() - Search disk for valid GPT headers and PTEs
 * state: disk parsed partitions
 * gpt: GPT header ptr, filled on return.
 * ptes: PTEs ptr, filled on return.
 *
 * Description: Returns 1 if valid, 0 on error.
 * If valid, returns pointers to newly allocated GPT header and PTEs.
 * Validity depends on PMBR being valid (or being overridden by the
 * 'gpt' kernel command line option) and finding either the Primary
 * GPT header and PTEs valid, or the Alternate GPT header and PTEs
 * valid.  If the Primary GPT header is not valid, the Alternate GPT header
 * is not checked unless the 'gpt' kernel command line option is passed.
 * This protects against devices which misreport their size, and forces
 * the user to decide to use the Alternate GPT.
 */
static int find_valid_gpt(struct rt_mmcsd_card *card, gpt_header **gpt,
              gpt_entry **ptes)
{
    int good_pgpt = 0, good_agpt = 0, good_pmbr = 0;
    gpt_header *pgpt = RT_NULL, *agpt = RT_NULL;
    gpt_entry *pptes = RT_NULL, *aptes = RT_NULL;
    legacy_mbr *legacymbr;
    size_t total_sectors = last_lba(card) + 1;
    size_t lastlba;
    int status = 0;

    if (!ptes)
    {
        return 0;
    }

    lastlba = last_lba(card);
    if (!force_gpt)
    {
        /* This will be added to the EFI Spec. per Intel after v1.02. */
        legacymbr = rt_malloc(512);
        if (!legacymbr)
        {
            goto fail;
        }

        status = read_lba(card, 0, (uint8_t *)legacymbr, 1);
        if (status)
        {
            LOG_I("status:%d", status);
            goto fail;
        }

        good_pmbr = is_pmbr_valid(legacymbr, total_sectors);
        rt_free(legacymbr);

        if (!good_pmbr)
        {
            goto fail;
        }

        rt_kprintf("Device has a %s MBR\n",
             good_pmbr == GPT_MBR_PROTECTIVE ?
                        "protective" : "hybrid");
    }

    good_pgpt = is_gpt_valid(card, GPT_PRIMARY_PARTITION_TABLE_LBA,
                 &pgpt, &pptes);
    if (good_pgpt)
    {
        good_agpt = is_gpt_valid(card, (pgpt->alternate_lba), &agpt, &aptes);
        if (!good_agpt && force_gpt)
        {
             good_agpt = is_gpt_valid(card, lastlba, &agpt, &aptes);
        }

        /* The obviously unsuccessful case */
        if (!good_pgpt && !good_agpt)
        {
            goto fail;
        }

        compare_gpts(pgpt, agpt, lastlba);

        /* The good cases */
        if (good_pgpt)
        {
            *gpt  = pgpt;
            *ptes = pptes;
            rt_free(agpt);
            rt_free(aptes);
            if (!good_agpt)
            {
                LOG_D("Alternate GPT is invalid, using primary GPT.");
            }
            return 1;
        }
        else if (good_agpt)
        {
            *gpt  = agpt;
            *ptes = aptes;
            rt_free(pgpt);
            rt_free(pptes);
            LOG_D("Primary GPT is invalid, using alternate GPT.");
                return 1;
        }
    }

 fail:
        rt_free(pgpt);
        rt_free(agpt);
        rt_free(pptes);
        rt_free(aptes);
        *gpt = RT_NULL;
        *ptes = RT_NULL;
        return 0;
}

int check_gpt(struct rt_mmcsd_card *card)
{
    if (!find_valid_gpt(card, &_gpt, &_ptes) || !_gpt || !_ptes)
    {
        rt_free(_gpt);
        rt_free(_ptes);
        return MBR_TYPE;
    }
    return GPT_TYPE;
}

int gpt_get_partition_param(struct rt_mmcsd_card *card, struct dfs_partition *part, uint32_t pindex)
{
    if (!is_pte_valid(&_ptes[pindex], last_lba(card)))
    {
        return -1;
    }

    part->offset = (off_t)(_ptes[pindex].starting_lba);
    part->size = (_ptes[pindex].ending_lba) - (_ptes[pindex].starting_lba) + 1ULL;

    rt_kprintf("found part[%d], begin(sector): %d, end(sector):%d size: ",
             pindex, _ptes[pindex].starting_lba, _ptes[pindex].ending_lba);

    if ((part->size >> 11) == 0)
    {
        rt_kprintf("%d%s", part->size >> 1, "KB\n"); /* KB */
    }
    else
    {
        unsigned int part_size;
        part_size = part->size >> 11;                /* MB */
        if ((part_size >> 10) == 0)
            rt_kprintf("%d.%d%s", part_size, (part->size >> 1) & 0x3FF, "MB\n");
        else
            rt_kprintf("%d.%d%s", part_size >> 10, part_size & 0x3FF, "GB\n");
    }
    return 0;
}

void gpt_free(void)
{
    rt_free(_ptes);
    rt_free(_gpt);
}
