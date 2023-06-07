#include <rtthread.h>

#if defined(__GNUC__)

int rtthread_startup(void);

static int start(void)
{
    rtthread_startup();
    return 0;
}
__attribute__((section(".init_array"))) typeof(start) *__init = start;
#endif
