#include <arm-tpl.h>

extern "C" int __ARM_TPL_execute_once(__ARM_TPL_exec_once_flag *__flag,
                                      void (*__init_routine)(void))
{
    if (*__flag == 0)
    {
        __init_routine();
        *__flag = 1;
    }
    return 0;
}