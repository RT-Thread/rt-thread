#include <string.h>

__attribute__((used))
char *strupr(char *str)
{
    char *str_iter = str;

    while (*str_iter != 0)
    {
        if ((*str_iter >= 'a') && (*str_iter <= 'z'))
            *str_iter -= 0x20;
        ++str_iter;
    }

    return str;
}
