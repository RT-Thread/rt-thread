/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-05-05     linzhenxing   first version
 * 2023-02-25     GuEe-GUI      make blk interface
 */

#include "efi.h"

#define DBG_TAG "blk.part.efi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_bool_t force_gpt = 0;

static int force_gpt_setup(void)
{
#ifdef RT_USING_OFW
    force_gpt = !!rt_ofw_bootargs_select("gpt", 0);
#endif

    return 0;
}
INIT_CORE_EXPORT(force_gpt_setup);

/**
 * @brief This function is EFI version of crc32 function.
 *
 * @param buf the buffer to calculate crc32 of.
 * @param len the length of buf.
 * @return EFI-style CRC32 value for @buf.
 */
rt_inline rt_uint32_t efi_crc32(const rt_uint8_t *buf, rt_size_t len)
{
    rt_ubase_t crc = 0xffffffffUL;

    for (rt_size_t i = 0; i < len; ++i)
    {
        crc ^= buf[i];

        for (int j = 0; j < 8; ++j)
        {
            crc = (crc >> 1) ^ ((crc & 1) ? 0xedb88320L : 0);
        }
    }

    return ~crc;
}

/**
 * @brief This function get number of last logical block of device.
 *
 * @param disk the blk of disk.
 * @return last LBA value on success, 0 on error.
 *  This is stored (by sd and ide-geometry) in
 *  the part[0] entry for this disk, and is the number of
 *  physical sectors available on the disk.
 */
static rt_size_t last_lba(struct rt_blk_disk *disk)
{
    return rt_blk_disk_get_capacity(disk) - 1ULL;
}

rt_inline int pmbr_part_valid(gpt_mbr_record *part)
{
    if (part->os_type != EFI_PMBR_OSTYPE_EFI_GPT)
    {
        return 0;
    }

    /* set to 0x00000001 (i.e., the LBA of the GPT Partition Header) */
    if (rt_le32_to_cpu(part->starting_lba) != GPT_PRIMARY_PARTITION_TABLE_LBA)
    {
        return 0;
    }

    return GPT_MBR_PROTECTIVE;
}

/**
 * @brief This function test Protective MBR for validity.
 *
 * @param mbr the pointer to a legacy mbr structure.
 * @param total_sectors the amount of sectors in the device
 * @return
 *  0 -> Invalid MBR
 *  1 -> GPT_MBR_PROTECTIVE
 *  2 -> GPT_MBR_HYBRID
 */
static int is_pmbr_valid(legacy_mbr *mbr, rt_size_t total_sectors)
{
    rt_uint32_t sz = 0;
    int part = 0, ret = 0; /* invalid by default */

    if (!mbr || rt_le16_to_cpu(mbr->signature) != MSDOS_MBR_SIGNATURE)
    {
        goto _done;
    }

    for (int i = 0; i < 4; ++i)
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
            goto _check_hybrid;
        }
    }

    if (ret != GPT_MBR_PROTECTIVE)
    {
        goto _done;
    }

_check_hybrid:
    for (int i = 0; i < 4; i++)
    {
        if (mbr->partition_record[i].os_type != EFI_PMBR_OSTYPE_EFI_GPT &&
            mbr->partition_record[i].os_type != 0x00)
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
        sz = rt_le32_to_cpu(mbr->partition_record[part].size_in_lba);

        if (sz != (rt_uint32_t)total_sectors - 1 && sz != 0xffffffff)
        {
            LOG_W("GPT: mbr size in lba (%u) different than whole disk (%u)",
                    sz, rt_min_t(rt_uint32_t, total_sectors - 1, 0xffffffff));
        }
    }

_done:
    return ret;
}

/**
 * @brief This function read bytes from disk, starting at given LBA.
 *
 * @param disk the blk of disk.
 * @param lba the Logical Block Address of the partition table.
 * @param buffer the destination buffer.
 * @param count the bytes to read.
 * @return number of bytes read on success, 0 on error.
 */
static rt_size_t read_lba(struct rt_blk_disk *disk,
        rt_uint64_t lba, rt_uint8_t *buffer, rt_size_t count)
{
    rt_size_t totalreadcount = 0;

    if (!buffer || lba > last_lba(disk))
    {
        return 0;
    }

    for (rt_uint64_t n = lba; count; ++n)
    {
        int copied = 512;

        disk->ops->read(disk, n, buffer, 1);

        if (copied > count)
        {
            copied = count;
        }

        buffer += copied;
        totalreadcount += copied;
        count -= copied;
    }

    return totalreadcount;
}

/**
 * @brief This function reads partition entries from disk.
 *
 * @param disk the blk of disk.
 * @param gpt the GPT header
 * @return ptes on success, null on error.
 */
static gpt_entry *alloc_read_gpt_entries(struct rt_blk_disk *disk,
        gpt_header *gpt)
{
    rt_size_t count;
    gpt_entry *pte;
    rt_uint64_t entry_lba;

    if (!gpt)
    {
        return RT_NULL;
    }

    count = (rt_size_t)rt_le32_to_cpu(gpt->num_partition_entries) *
            rt_le32_to_cpu(gpt->sizeof_partition_entry);

    if (!count)
    {
        return RT_NULL;
    }

    pte = rt_malloc(count);

    if (!pte)
    {
        return RT_NULL;
    }

    entry_lba = rt_le64_to_cpu(gpt->partition_entry_lba);

    if (read_lba(disk, entry_lba, (rt_uint8_t *)pte, count) < count)
    {
        rt_free(pte);
        pte = RT_NULL;

        return RT_NULL;
    }

    /* Remember to free pte when done */
    return pte;
}

/**
 * @brief This function allocates GPT header, reads into it from disk.
 *
 * @param disk the blk of disk.
 * @param lba the Logical Block Address of the partition table
 * @return GPT header on success, null on error.
 */
static gpt_header *alloc_read_gpt_header(struct rt_blk_disk *disk, rt_uint64_t lba)
{
    gpt_header *gpt;
    rt_uint32_t ssz = rt_blk_disk_get_logical_block_size(disk);

    gpt = rt_malloc(ssz);

    if (!gpt)
    {
        return RT_NULL;
    }

    if (read_lba(disk, lba, (rt_uint8_t *)gpt, ssz) < ssz)
    {
        rt_free(gpt);
        gpt = RT_NULL;

        return RT_NULL;
    }

    /* Remember to free gpt when finished with it */
    return gpt;
}

/**
 * @brief This function tests one GPT header and PTEs for validity.
 *
 * @param disk the blk of disk.
 * @param lba the Logical Block Address of the GPT header to test.
 * @param gpt the GPT header ptr, filled on return.
 * @param ptes the PTEs ptr, filled on return.
 * @returns true if valid, false on error.
 *  If valid, returns pointers to newly allocated GPT header and PTEs.
 */
static rt_bool_t is_gpt_valid(struct rt_blk_disk *disk,
        rt_uint64_t lba, gpt_header **gpt, gpt_entry **ptes)
{
    rt_uint32_t crc, origcrc;
    rt_uint64_t lastlba, pt_size;
    rt_ssize_t logical_block_size;

    if (!ptes)
    {
        return RT_FALSE;
    }

    if (!(*gpt = alloc_read_gpt_header(disk, lba)))
    {
        return RT_FALSE;
    }

    /* Check the GUID Partition Table signature */
    if (rt_le64_to_cpu((*gpt)->signature) != GPT_HEADER_SIGNATURE)
    {
        LOG_D("%s: GUID Partition Table Header signature is wrong: %lld != %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu((*gpt)->signature),
                (rt_uint64_t)GPT_HEADER_SIGNATURE);

        goto _fail;
    }

    /* Check the GUID Partition Table header size is too big */
    logical_block_size = rt_blk_disk_get_logical_block_size(disk);

    if (rt_le32_to_cpu((*gpt)->header_size) > logical_block_size)
    {
        LOG_D("%s: GUID Partition Table Header size is too large: %u > %u",
                to_disk_name(disk),
                rt_le32_to_cpu((*gpt)->header_size),
                logical_block_size);

        goto _fail;
    }

    /* Check the GUID Partition Table header size is too small */
    if (rt_le32_to_cpu((*gpt)->header_size) < sizeof(gpt_header))
    {
        LOG_D("%s: GUID Partition Table Header size is too small: %u < %u",
                to_disk_name(disk),
                rt_le32_to_cpu((*gpt)->header_size),
                sizeof(gpt_header));

        goto _fail;
    }

    /* Check the GUID Partition Table CRC */
    origcrc = rt_le32_to_cpu((*gpt)->header_crc32);
    (*gpt)->header_crc32 = 0;
    crc = efi_crc32((const rt_uint8_t *)(*gpt), rt_le32_to_cpu((*gpt)->header_size));

    if (crc != origcrc)
    {
        LOG_D("%s: GUID Partition Table Header CRC is wrong: %x != %x",
                to_disk_name(disk), crc, origcrc);

        goto _fail;
    }

    (*gpt)->header_crc32 = rt_cpu_to_le32(origcrc);

    /*
     * Check that the start_lba entry points to the LBA that contains
     * the GUID Partition Table
     */
    if (rt_le64_to_cpu((*gpt)->start_lba) != lba)
    {
        LOG_D("%s: GPT start_lba incorrect: %lld != %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu((*gpt)->start_lba),
                (rt_uint64_t)lba);

        goto _fail;
    }

    /* Check the first_usable_lba and last_usable_lba are within the disk */
    lastlba = last_lba(disk);

    if (rt_le64_to_cpu((*gpt)->first_usable_lba) > lastlba)
    {
        LOG_D("%s: GPT: first_usable_lba incorrect: %lld > %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu((*gpt)->first_usable_lba),
                (rt_uint64_t)lastlba);

        goto _fail;
    }

    if (rt_le64_to_cpu((*gpt)->last_usable_lba) > lastlba)
    {
        LOG_D("%s: GPT: last_usable_lba incorrect: %lld > %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu((*gpt)->last_usable_lba),
                (rt_uint64_t)lastlba);

        goto _fail;
    }
    if (rt_le64_to_cpu((*gpt)->last_usable_lba) < rt_le64_to_cpu((*gpt)->first_usable_lba))
    {
        LOG_D("%s: GPT: last_usable_lba incorrect: %lld > %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu((*gpt)->last_usable_lba),
                (rt_uint64_t)rt_le64_to_cpu((*gpt)->first_usable_lba));

        goto _fail;
    }

    /* Check that sizeof_partition_entry has the correct value */
    if (rt_le32_to_cpu((*gpt)->sizeof_partition_entry) != sizeof(gpt_entry))
    {
        LOG_D("%s: GUID Partition Entry Size check failed", to_disk_name(disk));

        goto _fail;
    }

    /* Sanity check partition table size */
    pt_size = (rt_uint64_t)rt_le32_to_cpu((*gpt)->num_partition_entries) *
            rt_le32_to_cpu((*gpt)->sizeof_partition_entry);

    if (!(*ptes = alloc_read_gpt_entries(disk, *gpt)))
    {
        goto _fail;
    }

    /* Check the GUID Partition Entry Array CRC */
    crc = efi_crc32((const rt_uint8_t *)(*ptes), pt_size);

    if (crc != rt_le32_to_cpu((*gpt)->partition_entry_array_crc32))
    {
        LOG_D("%s: GUID Partition Entry Array CRC check failed", to_disk_name(disk));

        goto _fail_ptes;
    }

    /* We're done, all's well */
    return RT_TRUE;

_fail_ptes:
    rt_free(*ptes);
    *ptes = RT_NULL;

_fail:
    rt_free(*gpt);
    *gpt = RT_NULL;

    return RT_FALSE;
}

/**
 * @brief This function tests one PTE for validity.
 *
 * @param pte the pte to check.
 * @param lastlba the last lba of the disk.
 * @return valid boolean of pte.
 */
rt_inline rt_bool_t is_pte_valid(const gpt_entry *pte, const rt_size_t lastlba)
{
    if ((!efi_guidcmp(pte->partition_type_guid, NULL_GUID)) ||
        rt_le64_to_cpu(pte->starting_lba) > lastlba ||
        rt_le64_to_cpu(pte->ending_lba) > lastlba)
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

/**
 * @brief This function search disk for valid GPT headers and PTEs.
 *
 * @param disk the blk of disk.
 * @param pgpt the primary GPT header.
 * @param agpt the alternate GPT header.
 * @param lastlba the last LBA number.
 */
static void compare_gpts(struct rt_blk_disk *disk,
        gpt_header *pgpt, gpt_header *agpt, rt_uint64_t lastlba)
{
    int error_found = 0;

    if (!pgpt || !agpt)
    {
        return;
    }

    if (rt_le64_to_cpu(pgpt->start_lba) != rt_le64_to_cpu(agpt->alternate_lba))
    {
        LOG_W("%s: GPT:Primary header LBA(%lld) != Alt(%lld), header alternate_lba",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu(pgpt->start_lba),
                (rt_uint64_t)rt_le64_to_cpu(agpt->alternate_lba));

        ++error_found;
    }

    if (rt_le64_to_cpu(pgpt->alternate_lba) != rt_le64_to_cpu(agpt->start_lba))
    {
        LOG_W("%s: GPT:Primary header alternate_lba(%lld) != Alt(%lld), header start_lba",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu(pgpt->alternate_lba),
                (rt_uint64_t)rt_le64_to_cpu(agpt->start_lba));

        ++error_found;
    }

    if (rt_le64_to_cpu(pgpt->first_usable_lba) != rt_le64_to_cpu(agpt->first_usable_lba))
    {
        LOG_W("%s: GPT:first_usable_lbas don't match %lld != %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu(pgpt->first_usable_lba),
                (rt_uint64_t)rt_le64_to_cpu(agpt->first_usable_lba));

        ++error_found;
    }

    if (rt_le64_to_cpu(pgpt->last_usable_lba) != rt_le64_to_cpu(agpt->last_usable_lba))
    {
        LOG_W("%s: GPT:last_usable_lbas don't match %lld != %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu(pgpt->last_usable_lba),
                (rt_uint64_t)rt_le64_to_cpu(agpt->last_usable_lba));

        ++error_found;
    }

    if (efi_guidcmp(pgpt->disk_guid, agpt->disk_guid))
    {
        LOG_W("%s: GPT:disk_guids don't match", to_disk_name(disk));

        ++error_found;
    }

    if (rt_le32_to_cpu(pgpt->num_partition_entries) !=
            rt_le32_to_cpu(agpt->num_partition_entries))
    {
        LOG_W("%s: GPT:num_partition_entries don't match: 0x%x != 0x%x",
                to_disk_name(disk),
                rt_le32_to_cpu(pgpt->num_partition_entries),
                rt_le32_to_cpu(agpt->num_partition_entries));

        ++error_found;
    }

    if (rt_le32_to_cpu(pgpt->sizeof_partition_entry) !=
            rt_le32_to_cpu(agpt->sizeof_partition_entry))
    {
        LOG_W("%s: GPT:sizeof_partition_entry values don't match: 0x%x != 0x%x",
                to_disk_name(disk),
                rt_le32_to_cpu(pgpt->sizeof_partition_entry),
                rt_le32_to_cpu(agpt->sizeof_partition_entry));

        ++error_found;
    }

    if (rt_le32_to_cpu(pgpt->partition_entry_array_crc32) !=
            rt_le32_to_cpu(agpt->partition_entry_array_crc32))
    {
        LOG_W("%s: GPT:partition_entry_array_crc32 values don't match: 0x%x != 0x%x",
                to_disk_name(disk),
                rt_le32_to_cpu(pgpt->partition_entry_array_crc32),
                rt_le32_to_cpu(agpt->partition_entry_array_crc32));

        ++error_found;
    }

    if (rt_le64_to_cpu(pgpt->alternate_lba) != lastlba)
    {
        LOG_W("%s: GPT:Primary header thinks Alt. header is not at the end of the disk: %lld != %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu(pgpt->alternate_lba),
                (rt_uint64_t)lastlba);

        ++error_found;
    }

    if (rt_le64_to_cpu(agpt->start_lba) != lastlba)
    {
        LOG_W("%s: GPT:Alternate GPT header not at the end of the disk: %lld != %lld",
                to_disk_name(disk),
                (rt_uint64_t)rt_le64_to_cpu(agpt->start_lba),
                (rt_uint64_t)lastlba);

        ++error_found;
    }

    if (error_found)
    {
        LOG_W("GPT: Use GNU Parted to correct GPT errors");
    }
}

/**
 * @brief This function search disk for valid GPT headers and PTEs.
 *
 * @param disk the disk parsed partitions.
 * @param gpt the GPT header ptr, filled on return.
 * @param ptes the PTEs ptr, filled on return.
 * @return 1 if valid, 0 on error.
 *  If valid, returns pointers to newly allocated GPT header and PTEs.
 *  Validity depends on PMBR being valid (or being overridden by the
 *  'gpt' kernel command line option) and finding either the Primary
 *  GPT header and PTEs valid, or the Alternate GPT header and PTEs
 *  valid.  If the Primary GPT header is not valid, the Alternate GPT header
 *  is not checked unless the 'gpt' kernel command line option is passed.
 *  This protects against devices which misreport their size, and forces
 *  the user to decide to use the Alternate GPT.
 */
static rt_bool_t find_valid_gpt(struct rt_blk_disk *disk,
        gpt_header **gpt, gpt_entry **ptes)
{
    int good_pgpt = 0, good_agpt = 0, good_pmbr = 0;
    gpt_header *pgpt = RT_NULL, *agpt = RT_NULL;
    gpt_entry *pptes = RT_NULL, *aptes = RT_NULL;
    legacy_mbr *legacymbr;
    rt_size_t total_sectors = rt_blk_disk_get_capacity(disk);
    rt_size_t lastlba;

    if (!ptes)
    {
        return RT_FALSE;
    }

    lastlba = last_lba(disk);

    if (!force_gpt)
    {
        /* This will be added to the EFI Spec. per Intel after v1.02. */
        legacymbr = rt_malloc(sizeof(*legacymbr));

        if (!legacymbr)
        {
            return RT_FALSE;
        }

        read_lba(disk, 0, (rt_uint8_t *)legacymbr, sizeof(*legacymbr));
        good_pmbr = is_pmbr_valid(legacymbr, total_sectors);
        rt_free(legacymbr);

        if (!good_pmbr)
        {
            return RT_FALSE;
        }

        LOG_D("%s: Device has a %s MBR", to_disk_name(disk),
                good_pmbr == GPT_MBR_PROTECTIVE ? "protective" : "hybrid");
    }

    good_pgpt = is_gpt_valid(disk, GPT_PRIMARY_PARTITION_TABLE_LBA, &pgpt, &pptes);

    if (good_pgpt)
    {
        good_agpt = is_gpt_valid(disk, rt_le64_to_cpu(pgpt->alternate_lba), &agpt, &aptes);
    }

    if (!good_agpt && force_gpt)
    {
        good_agpt = is_gpt_valid(disk, lastlba, &agpt, &aptes);
    }

    /* The obviously unsuccessful case */
    if (!good_pgpt && !good_agpt)
    {
        goto _fail;
    }

    compare_gpts(disk, pgpt, agpt, lastlba);

    /* The good cases */
    if (good_pgpt)
    {
        *gpt = pgpt;
        *ptes = pptes;
        rt_free(agpt);
        rt_free(aptes);

        if (!good_agpt)
        {
            LOG_D("%s: Alternate GPT is invalid, using primary GPT", to_disk_name(disk));
        }

        return RT_TRUE;
    }
    else if (good_agpt)
    {
        *gpt = agpt;
        *ptes = aptes;
        rt_free(pgpt);
        rt_free(pptes);

        LOG_D("%s: Primary GPT is invalid, using alternate GPT", to_disk_name(disk));

        return RT_TRUE;
    }

_fail:
    rt_free(pgpt);
    rt_free(agpt);
    rt_free(pptes);
    rt_free(aptes);

    *gpt = RT_NULL;
    *ptes = RT_NULL;

    return RT_FALSE;
}

rt_err_t efi_partition(struct rt_blk_disk *disk)
{
    rt_uint32_t entries_nr;
    gpt_header *gpt = RT_NULL;
    gpt_entry *ptes = RT_NULL;

    if (!find_valid_gpt(disk, &gpt, &ptes) || !gpt || !ptes)
    {
        rt_free(gpt);
        rt_free(ptes);

        return -RT_EINVAL;
    }

    entries_nr = rt_le32_to_cpu(gpt->num_partition_entries);

    for (int i = 0; i < entries_nr && i < disk->max_partitions; ++i)
    {
        rt_uint64_t start = rt_le64_to_cpu(ptes[i].starting_lba);
        rt_uint64_t size = rt_le64_to_cpu(ptes[i].ending_lba) -
                rt_le64_to_cpu(ptes[i].starting_lba) + 1ULL;

        if (!is_pte_valid(&ptes[i], last_lba(disk)))
        {
            continue;
        }

        if (blk_put_partition(disk, "gpt", start, size, i) == -RT_ENOMEM)
        {
            break;
        }
    }

    rt_free(gpt);
    rt_free(ptes);

    return RT_EOK;
}
