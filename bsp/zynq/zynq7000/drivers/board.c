#include <rthw.h>
#include <rtthread.h>
#include "xil_assert.h"
#include "rtdevice.h"
#include "drv_gpio.h"
#include <mmu.h>
#include "interrupt.h"

extern rt_uint32_t __text_start;

struct mem_desc platform_mem_desc[] = {
    /* no access to the memory below .text */
    /* 521Mb cached DDR memory */
    {(rt_uint32_t)&__text_start, 0x3F600000-1, (rt_uint32_t)&__text_start, NORMAL_MEM},
    /* PL region */
    {0x40000000, 0xBFFFFFFF, 0x40000000, DEVICE_MEM},
    /* IOP registers */
    {0xE0000000, 0xE02FFFFF, 0xE0000000, DEVICE_MEM},
    /* SLCR, PS and CPU private registers, note we map more memory space as the
     * entry is 1MB in size. */
    {0xF8000000, 0xFFFFFFFF, 0xF8000000, DEVICE_MEM},
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    asm volatile ("wfi");
}

static void rt_xil_assert_callback(const char8 *File, s32 Line)
{
    rt_kprintf("Xil_AssertCallback: %s, %d\n", File, Line);
    RT_ASSERT(0);
}

#ifdef BSP_USING_SDK_SRC

int usleep(unsigned long useconds)
{
    useconds /= 1000;
    if (useconds == 0)
        useconds = 1;

    rt_thread_mdelay(useconds);

    return 0;
}
#else

typedef void (*usleep_hook_t) (unsigned long useconds);

// note: should edit usleep.c in bsp to fix it
//
// static usleep_hook_t usleep_hook;
//
// void zynq_set_usleep_hook(usleep_hook_t hook)
// {
//  usleep_hook = hook;
// }
//
// int usleep(unsigned long useconds)
// {
//  if (usleep_hook)
//  {
//      usleep_hook(useconds);
//      return 0;
//  }

//  XTime tEnd, tCur;

//  XTime_GetTime(&tCur);
//  tEnd = tCur + (((XTime) useconds) * COUNTS_PER_USECOND);
//  do
//  {
//      XTime_GetTime(&tCur);
//  } while (tCur < tEnd);

//  return 0;
// }
//

extern void zynq_set_usleep_hook(usleep_hook_t hook);

static void hw_usleep_hook(unsigned long useconds)
{
    useconds /= 1000;
    if (useconds == 0)
        useconds = 1;

    rt_thread_mdelay(useconds);
}

static int setup_zynq_usleep_hook(void)
{
    zynq_set_usleep_hook(hw_usleep_hook);
    return 0;
}
INIT_BOARD_EXPORT(setup_zynq_usleep_hook);

#endif // #ifndef BSP_USING_SDK_SRC end

static void _assert_hook (const char *ex, const char *func, rt_size_t line)
{
    RT_ASSERT(0);
}

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void)
{
    Xil_AssertSetCallback(rt_xil_assert_callback);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();
    /* initialize system heap */
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    rt_hw_pin_init();

    rt_components_board_init();

    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
#endif

    rt_assert_set_hook(_assert_hook);
}

#include "xil_io.h"
#define PSS_RST_CTRL_REG 0xF8000200
#define SLCR_UNLOCK_ADDR 0xF8000008
#define UNLOCK_KEY 0xDF0D
#define PSS_RST_MASK 0x01

static void zynq_hw_software_reset(void)
{
    Xil_Out32(SLCR_UNLOCK_ADDR, UNLOCK_KEY);
    Xil_Out32(PSS_RST_CTRL_REG, PSS_RST_MASK);
}
MSH_CMD_EXPORT_ALIAS(zynq_hw_software_reset, reboot, soft reboot);
