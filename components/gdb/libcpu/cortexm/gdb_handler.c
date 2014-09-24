#include <rtthread.h>
#include <gdb_stub.h>

void rt_hw_debugmon_exception(void *regs)
{
#ifdef RT_USING_GDB
    gdb_arch_late();
    gdb_handle_exception(SIGTRAP, regs);
    gdb_arch_exit();
#endif
}
