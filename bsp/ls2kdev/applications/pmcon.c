#include <rtthread.h>

static void reboot()
{
	rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, reboot sample);


static void poweroff()
{
	rt_hw_cpu_shutdown();
}
MSH_CMD_EXPORT(poweroff, shutdown power sample);

