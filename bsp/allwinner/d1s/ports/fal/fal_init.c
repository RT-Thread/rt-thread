#include <rtthread.h>
#include <fal.h>

int fal_init_auto(void)
{
    return fal_init();
}
INIT_COMPONENT_EXPORT(fal_init_auto);
