#include <rtthread.h>

int cplusplus_system_init(void)
{
#if defined(__GNUC__) && !defined(__CC_ARM)
    extern unsigned char __ctors_start__;
    extern unsigned char __ctors_end__;
    typedef void (*func)(void);

    /* .ctors initalization */
    func *ctors_func;

    for (ctors_func = (func *)&__ctors_start__;
         ctors_func < (func *)&__ctors_end__;
         ctors_func ++)
    {
        (*ctors_func)();
    }
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(cplusplus_system_init);

