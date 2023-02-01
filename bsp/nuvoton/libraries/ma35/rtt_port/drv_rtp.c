/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-9-27       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_RTP) && defined(RT_USING_DFS)

#define LOG_TAG    "drv.rtp"
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL      LOG_LVL_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include <rtdevice.h>
#include "drv_sys.h"
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>

#include "drv_sspcc.h"

/* Link to rtthread.bin in ma35-rtp folder. */
#define PATH_RTP_INCBIN          "..//ma35-rtp//rtthread.bin"

#define READ_BLOCK_SIZE       128

#if !defined(PATH_RTP_FW_FILE)
    #define PATH_RTP_FW_FILE "/mnt/sd1p0/rtp.bin"
#endif

#if defined(RTP_USING_AT_STARTUP)

#define STR2(x) #x
#define STR(x) STR2(x)

#define INCBIN(name, file) \
    __asm__(".section .rodata\n" \
            ".global incbin_" STR(name) "_start\n" \
            ".balign 16\n" \
            "incbin_" STR(name) "_start:\n" \
            ".incbin \"" file "\"\n" \
            \
            ".global incbin_" STR(name) "_end\n" \
            ".balign 1\n" \
            "incbin_" STR(name) "_end:\n" \
            ".byte 0\n" \
    ); \
    extern const __attribute__((aligned(16))) void* incbin_ ## name ## _start; \
    extern const void* incbin_ ## name ## _end; \

INCBIN(rtp, PATH_RTP_INCBIN);

static int nu_rtp_load_from_memory(void *pvBuf, int len)
{
    int remaining;

    if (!pvBuf || !len)
        goto exit_nu_rtp_load_from_memory;

    /* Limit memory usage to 4MB. */
    if (len > REGION_MAXSIZE_LIMIT)
        goto exit_nu_rtp_load_from_memory;

    remaining = len;

    /* Copy to SRAM0 */
    if (remaining > REGION_MAXSIZE_SRAM0)
    {
        rt_memcpy((void *)REGION_ADDR_SRAM0, pvBuf, REGION_MAXSIZE_SRAM0);
        remaining -= REGION_MAXSIZE_SRAM0;
    }
    else
    {
        rt_memcpy((void *)REGION_ADDR_SRAM0, pvBuf, remaining);
        remaining -= remaining;
    }

    /* Copy to non-cacheable DDR memory if the size over 128KB. */
    if (remaining > 0)
    {
        rt_memcpy((void *)REGION_ADDR_DDR, (pvBuf + REGION_MAXSIZE_SRAM0), remaining);
        remaining -= remaining;
    }

    return 0;

exit_nu_rtp_load_from_memory:

    return -1;
}
#endif

rt_weak void nu_rtp_sspcc_setup(void)
{
    SSPCC_SET_REALM(SSPCC_UART16, SSPCC_SSET_SUBM);

    SSPCC_SET_GPIO_REALM(PK, 0, SSPCC_SSET_SUBM);
    SSPCC_SET_GPIO_REALM(PK, 1, SSPCC_SSET_SUBM);
    SSPCC_SET_GPIO_REALM(PK, 2, SSPCC_SSET_SUBM);
    SSPCC_SET_GPIO_REALM(PK, 3, SSPCC_SSET_SUBM);
}

static void nu_rtp_init(void)
{
    /* Enable WDT1/WDT2 reset */
    SYS->MISCRFCR |= SYS_MISCRFCR_WDT1RSTAEN_Msk | SYS_MISCRFCR_WDT2RSTAEN_Msk | SYS_MISCRFCR_WDT1RSTMEN_Msk;

    /* Enable M4 I/D cache */
    SYS->MISCFCR0 |= (SYS_MISCFCR0_RTPICACHEN_Msk | SYS_MISCFCR0_RTPDCACHEN_Msk | SYS_MISCFCR0_RTPDRMAEN_Msk);

    nu_rtp_sspcc_setup();
}

void nu_rtp_start(void)
{
    /* Enable RTP clock */
    CLK_EnableModuleClock(RTP_MODULE);

    /* Disable M4 Core reset*/
    SYS->IPRST0 &= ~SYS_IPRST0_CM4RST_Msk;
}
MSH_CMD_EXPORT(nu_rtp_start, start rtp);

void nu_rtp_stop(void)
{
    /* Enable M4 Core reset*/
    SYS->IPRST0 |= SYS_IPRST0_CM4RST_Msk;

    /* Disable RTP clock */
    CLK_DisableModuleClock(RTP_MODULE);
}
MSH_CMD_EXPORT(nu_rtp_stop, stop rtp);


#if defined(RT_USING_DFS)
static int nu_rtp_load_from_file(char *szAbsFilePath)
{
    int fd, ret = -1;
    char *buff_ptr = RT_NULL;
    rt_size_t offset = 0;

    fd = open(szAbsFilePath, O_RDONLY);
    if (fd < 0)
    {
        LOG_E("Could not open %s for rtp loading.", szAbsFilePath);
        goto exit_nu_rtp_load_from_file;
    }

    while (1)
    {
        int length;

        if (offset < REGION_MAXSIZE_SRAM0)
        {
            buff_ptr = (char *)(REGION_ADDR_SRAM0 + offset);
        }
        else
        {
            buff_ptr = (char *)(REGION_ADDR_DDR + offset - REGION_MAXSIZE_SRAM0);
        }

        /* Limit memory usage to 4MB. */
        if ((offset + READ_BLOCK_SIZE) >= REGION_MAXSIZE_SRAM0)
            goto exit_nu_rtp_load_from_file;

        length = read(fd, buff_ptr, READ_BLOCK_SIZE);

        if (length <= 0) break;
        offset += length;

        //rt_kprintf("readed (%d/%d) to %08x\n", length, offset, buff_ptr);
    }

    ret = 0;

exit_nu_rtp_load_from_file:

    if (fd >= 0)
        close(fd);

    return ret;
}

int nu_rtp_load_run(int argc, char *argv[])
{
    char *szFilePath = RT_NULL;

    if (argc == 1)
    {
        szFilePath = PATH_RTP_FW_FILE;
    }
    else if (argc == 2)
    {
        szFilePath = argv[1];
    }

    nu_rtp_stop();
    nu_rtp_init();

    if (!szFilePath || nu_rtp_load_from_file(szFilePath) < 0)
        return -1;

    LOG_I("Loaded %s, then run...", szFilePath);

    nu_rtp_start();

    return 0;
}
MSH_CMD_EXPORT(nu_rtp_load_run, load rtp code then run);
#endif

int rt_hw_rtp_init(void)
{
#if defined(RTP_USING_AT_STARTUP)
    int fw_size = (int)((char *)&incbin_rtp_end - (char *)&incbin_rtp_start);
    LOG_I("INCBIN RTP Start = %p", &incbin_rtp_start);
    LOG_I("INCBIN RTP Size = %p", fw_size);
#endif

    /* Enable RTP and reset M4 reset */
    nu_rtp_init();

#if defined(RTP_USING_AT_STARTUP)
    nu_rtp_stop();
    nu_rtp_load_from_memory(&incbin_rtp_start, fw_size);
#endif

    nu_rtp_start();

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_rtp_init);

#endif //#if defined(BSP_USING_RTP)
