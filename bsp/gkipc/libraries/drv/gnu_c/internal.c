#include "stdio.h"
#include "internal.h"

static enter_crit  st_enter_critical = NULL;
static exit_crit   st_exit_critical = NULL;

int st_register_crit_func(enter_crit ent, exit_crit exit)
{
    if(ent == NULL || ent == NULL)
    {
        printf("parameter error\n");
        return -1;
    }
    st_enter_critical = ent;
    st_exit_critical = exit;
    return 0;
}

uint32_t st_enter_crit_func()
{
    if(st_enter_critical)
    {
        return st_enter_critical();
    }
    else
    {
        return -1;
    }
}

void st_exit_crit_func(uint32_t flags)
{
    if(st_exit_critical)
    {
        st_exit_critical(flags);
    }

}