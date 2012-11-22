/**
 * reimplement arm c library's basic functions
 */

#include <string.h>
#include <rt_sys.h>

#include "rtthread.h"

#pragma import(__use_no_semihosting_swi)

int remove(const char *filename)
{
    RT_ASSERT(0);
    for(;;);
}

/* rename() */

int system(const char *string)
{
    RT_ASSERT(0);
    for(;;);	
}

/* Standard IO device handles. */
#define STDIN       1
#define STDOUT      2
#define STDERR      3

/* Standard IO device name defines. */
const char __stdin_name[]  = "STDIN";
const char __stdout_name[] = "STDOUT";
const char __stderr_name[] = "STDERR";

FILEHANDLE _sys_open(const char *name, int openmode)
{
    /* Register standard Input Output devices. */
    if (strcmp(name, __stdin_name) == 0)
        return (STDIN);
    if (strcmp(name, __stdout_name) == 0)
        return (STDOUT);
    if (strcmp(name, __stderr_name) == 0)
        return (STDERR);

#ifndef RT_USING_DFS
    return 0;
#else
    /* TODO: adjust open file mode */
    return open(name, openmode, 0);
#endif
}

int _sys_close(FILEHANDLE fh)
{
#ifndef RT_USING_DFS
    return 0;
#else
    if (fh < 3)
        return 0;
    
    return close(fh);
#endif
}

int _sys_read(FILEHANDLE fh, unsigned char *buf, unsigned len, int mode)
{
    if (fh == STDIN)
    {
        /* TODO */
        
        return 0;
    }
    
#ifndef RT_USING_DFS
    return 0;
#else
    return read(fh, buf, len);
#endif
}

int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode)
{
    if ((fh == STDOUT) || (fh == STDERR))
    {
#ifndef RT_USING_CONSOLE
        return 0;
#else
        rt_device_t console_device;
        extern rt_device_t rt_console_get_device(void);

        console_device = rt_console_get_device();
        if (console_device != 0) rt_device_write(console_device, 0, buf, len);
        return len;
#endif
    }
    
#ifndef RT_USING_DFS
    return 0;
#else
    return write(fh, buf, len);
#endif
}

int _sys_seek(FILEHANDLE fh, long pos)
{
#ifndef RT_USING_DFS
    return 0;
#else
    /* TODO: adjust last parameter */
    return lseek(fh, pos, 0);
#endif
}

int _sys_tmpnam(char *name, int fileno, unsigned maxlength)
{
    return 0;
}

char *_sys_command_string(char *cmd, int len)
{
    return cmd;
}

void _ttywrch(int ch)
{
    
}

void _sys_exit(int return_code)
{
    while (1);
}

long _sys_flen(FILEHANDLE fh)
{
    return 0;
}

int _sys_istty(FILEHANDLE fh)
{
    return 0;
}



