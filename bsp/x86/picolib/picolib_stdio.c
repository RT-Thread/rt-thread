#include <rtthread.h>
#include <stdio.h>

static int picolibc_putc(char c, FILE *file)
{
    (void)file;

    if (c == '\n')
    {
        rt_hw_console_output("\r");
    }

    rt_hw_console_output((const char *)&c);
    return c;
}

static FILE __stdio_out = FDEV_SETUP_STREAM(picolibc_putc, NULL, NULL, _FDEV_SETUP_WRITE);

FILE *const stdout = &__stdio_out;
FILE *const stderr = &__stdio_out;
