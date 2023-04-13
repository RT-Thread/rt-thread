/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Bernard      port from FreeBSD
 */

/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2019 Mitchell Horne <mhorne@FreeBSD.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "sbi.h"
#include <rtthread.h>
#include <stdbool.h>

/* SBI Implementation-Specific Definitions */
#define OPENSBI_VERSION_MAJOR_OFFSET 16
#define OPENSBI_VERSION_MINOR_MASK 0xFFFF

unsigned long sbi_spec_version;
unsigned long sbi_impl_id;
unsigned long sbi_impl_version;

static bool has_time_extension = false;
static bool has_ipi_extension = false;
static bool has_rfnc_extension = false;

static struct sbi_ret sbi_get_spec_version(void)
{
    return (SBI_CALL0(SBI_EXT_ID_BASE, SBI_BASE_GET_SPEC_VERSION));
}

static struct sbi_ret sbi_get_impl_id(void)
{
    return (SBI_CALL0(SBI_EXT_ID_BASE, SBI_BASE_GET_IMPL_ID));
}

static struct sbi_ret sbi_get_impl_version(void)
{
    return (SBI_CALL0(SBI_EXT_ID_BASE, SBI_BASE_GET_IMPL_VERSION));
}

void sbi_print_version(void)
{
    unsigned int major;
    unsigned int minor;

    /* For legacy SBI implementations. */
    if (sbi_spec_version == 0)
    {
        rt_kprintf("SBI: Unknown (Legacy) Implementation\n");
        rt_kprintf("SBI Specification Version: 0.1\n");
        return;
    }

    switch (sbi_impl_id)
    {
    case (SBI_IMPL_ID_BBL):
        rt_kprintf("SBI: Berkely Boot Loader %lu\n", sbi_impl_version);
        break;
    case (SBI_IMPL_ID_XVISOR):
        rt_kprintf("SBI: eXtensible Versatile hypervISOR %lu\n",
                   sbi_impl_version);
        break;
    case (SBI_IMPL_ID_KVM):
        rt_kprintf("SBI: Kernel-based Virtual Machine %lu\n", sbi_impl_version);
        break;
    case (SBI_IMPL_ID_RUSTSBI):
        rt_kprintf("SBI: RustSBI %lu\n", sbi_impl_version);
        break;
    case (SBI_IMPL_ID_DIOSIX):
        rt_kprintf("SBI: Diosix %lu\n", sbi_impl_version);
        break;
    case (SBI_IMPL_ID_OPENSBI):
        major = sbi_impl_version >> OPENSBI_VERSION_MAJOR_OFFSET;
        minor = sbi_impl_version & OPENSBI_VERSION_MINOR_MASK;
        rt_kprintf("SBI: OpenSBI v%u.%u\n", major, minor);
        break;
    default:
        rt_kprintf("SBI: Unrecognized Implementation: %lu\n", sbi_impl_id);
        break;
    }

    major = (sbi_spec_version & SBI_SPEC_VERS_MAJOR_MASK) >>
            SBI_SPEC_VERS_MAJOR_OFFSET;
    minor = (sbi_spec_version & SBI_SPEC_VERS_MINOR_MASK);
    rt_kprintf("SBI Specification Version: %u.%u\n", major, minor);
}

void sbi_set_timer(uint64_t val)
{
    struct sbi_ret ret;

    /* Use the TIME legacy replacement extension, if available. */
    if (has_time_extension)
    {
        ret = SBI_CALL1(SBI_EXT_ID_TIME, SBI_TIME_SET_TIMER, val);
        RT_ASSERT(ret.error == SBI_SUCCESS);
    }
    else
    {
        (void)SBI_CALL1(SBI_SET_TIMER, 0, val);
    }
}

void sbi_send_ipi(const unsigned long *hart_mask)
{
    struct sbi_ret ret;

    /* Use the IPI legacy replacement extension, if available. */
    if (has_ipi_extension)
    {
        ret = SBI_CALL2(SBI_EXT_ID_IPI, SBI_IPI_SEND_IPI, *hart_mask, 0);
        RT_ASSERT(ret.error == SBI_SUCCESS);
    }
    else
    {
        (void)SBI_CALL1(SBI_SEND_IPI, 0, (uint64_t)hart_mask);
    }
}

void sbi_remote_fence_i(const unsigned long *hart_mask)
{
    struct sbi_ret ret;

    /* Use the RFENCE legacy replacement extension, if available. */
    if (has_rfnc_extension)
    {
        ret =
            SBI_CALL2(SBI_EXT_ID_RFNC, SBI_RFNC_REMOTE_FENCE_I, *hart_mask, 0);
        RT_ASSERT(ret.error == SBI_SUCCESS);
    }
    else
    {
        (void)SBI_CALL1(SBI_REMOTE_FENCE_I, 0, (uint64_t)hart_mask);
    }
}

int sbi_remote_sfence_vma(const unsigned long *hart_mask,
                          const unsigned long hart_mask_base,
                          unsigned long start, unsigned long size)
{
    struct sbi_ret ret = {.error = SBI_SUCCESS};

    /* Use the RFENCE legacy replacement extension, if available. */
    if (has_rfnc_extension)
    {
        ret = SBI_CALL4(SBI_EXT_ID_RFNC, SBI_RFNC_REMOTE_SFENCE_VMA, *hart_mask,
                        hart_mask_base, start, size);
    }
    else
    {
        (void)SBI_CALL3(SBI_REMOTE_SFENCE_VMA, 0, (uint64_t)hart_mask, start,
                        size);
    }
    return ret.error;
}

void sbi_remote_sfence_vma_asid(const unsigned long *hart_mask,
                                unsigned long start, unsigned long size,
                                unsigned long asid)
{
    struct sbi_ret ret;

    /* Use the RFENCE legacy replacement extension, if available. */
    if (has_rfnc_extension)
    {
        ret = SBI_CALL5(SBI_EXT_ID_RFNC, SBI_RFNC_REMOTE_SFENCE_VMA_ASID,
                        *hart_mask, 0, start, size, asid);
        RT_ASSERT(ret.error == SBI_SUCCESS);
    }
    else
    {
        (void)SBI_CALL4(SBI_REMOTE_SFENCE_VMA_ASID, 0, (uint64_t)hart_mask,
                        start, size, asid);
    }
}

int sbi_hsm_hart_start(unsigned long hart, unsigned long start_addr,
                       unsigned long priv)
{
    struct sbi_ret ret;

    ret = SBI_CALL3(SBI_EXT_ID_HSM, SBI_HSM_HART_START, hart, start_addr, priv);
    return (ret.error != 0 ? (int)ret.error : 0);
}

void sbi_hsm_hart_stop(void)
{
    (void)SBI_CALL0(SBI_EXT_ID_HSM, SBI_HSM_HART_STOP);
}

int sbi_hsm_hart_status(unsigned long hart)
{
    struct sbi_ret ret;

    ret = SBI_CALL1(SBI_EXT_ID_HSM, SBI_HSM_HART_STATUS, hart);

    return (ret.error != 0 ? (int)ret.error : (int)ret.value);
}

void sbi_init(void)
{
    struct sbi_ret sret;

    /*
     * Get the spec version. For legacy SBI implementations this will
     * return an error, otherwise it is guaranteed to succeed.
     */
    sret = sbi_get_spec_version();
    if (sret.error != 0)
    {
        /* We are running a legacy SBI implementation. */
        sbi_spec_version = 0;
        return;
    }

    /* Set the SBI implementation info. */
    sbi_spec_version = sret.value;
    sbi_impl_id = sbi_get_impl_id().value;
    sbi_impl_version = sbi_get_impl_version().value;

    /* Probe for legacy replacement extensions. */
    if (sbi_probe_extension(SBI_EXT_ID_TIME) != 0)
        has_time_extension = true;
    if (sbi_probe_extension(SBI_EXT_ID_IPI) != 0)
        has_ipi_extension = true;
    if (sbi_probe_extension(SBI_EXT_ID_RFNC) != 0)
        has_rfnc_extension = true;
}

void rt_hw_console_output(const char *str)
{
    while (*str)
    {
        sbi_console_putchar(*str++);
    }
}
