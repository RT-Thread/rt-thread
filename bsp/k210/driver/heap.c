#include <rtthread.h>
#include <stdlib.h>

size_t get_free_heap_size(void)
{
    rt_uint32_t total, used, max;

    rt_memory_info(&total, &used, &max);

    return total - used;
}
