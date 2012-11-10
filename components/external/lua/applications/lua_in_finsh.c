/**
 * run lua interpreter from finsh
 */

#include "rtthread.h"
#include "finsh.h"
#include "shell.h"

struct
{
    struct rt_semaphore sem;
    rt_device_t device;
} dev4lua;

extern int lua_main(int argc, char **argv);

rt_err_t lua_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&dev4lua.sem);

    return RT_EOK;
}

void finsh_lua(void *parameter)
{
    rt_err_t (*rx_indicate)(rt_device_t dev, rt_size_t size);

    rt_sem_init(&(dev4lua.sem), "luasem", 0, 0);

    /* save old rx_indicate */
    rx_indicate = dev4lua.device->rx_indicate;

    /* set new rx_indicate */
    rt_device_set_rx_indicate(dev4lua.device, lua_rx_ind);

    {
        int argc = 1;
        char *argv[] = {"lua", NULL};

        /* run lua interpreter */
        lua_main(argc, argv);
    }

    /* recover old rx_indicate */
    rt_device_set_rx_indicate(dev4lua.device, rx_indicate);
}

static void lua(void)
{
    rt_thread_t lua_thread;
    const char* device_name = finsh_get_device();
    rt_device_t device = rt_device_find(device_name);
    if (device == RT_NULL)
    {
        rt_kprintf("%s not find\n", device_name);
        return;
    }
    dev4lua.device = device;

#if 0
    /* Run lua interpreter in separate thread */
    lua_thread = rt_thread_create("lua",
                                  finsh_lua,
                                  0,
                                  2048,
                                  rt_thread_self()->current_priority + 1,
                                  20);
    if (lua_thread != RT_NULL)
    {
        rt_thread_startup(lua_thread);
    }
#else
    /* Directly run lua interpreter in finsh */
    finsh_lua(0);
#endif
}
FINSH_FUNCTION_EXPORT(lua, lua interpreter)

int readline4lua(const char *prompt, char *buffer, int buffer_size)
{
    char ch;
    int line_position;

start:
    /* show prompt */
    rt_kprintf(prompt);

    line_position = 0;
    memset(buffer, 0, buffer_size);
    while (1)
    {
        if (rt_sem_take(&dev4lua.sem, RT_WAITING_FOREVER) != RT_EOK)
        {
            return 0;
        }

        while (rt_device_read(dev4lua.device, 0, &ch, 1) == 1)
        {
            /* handle CR key */
            if (ch == '\r')
            {
                char next;
                if (rt_device_read(dev4lua.device, 0, &next, 1) == 1)
                    ch = next;
            }
            /* backspace key */
            else if (ch == 0x7f || ch == 0x08)
            {
                if (line_position > 0)
                {
                    rt_kprintf("%c %c", ch, ch);
                    line_position--;
                }
                buffer[line_position] = 0;
                continue;
            }
            /* EOF(ctrl+d) */
            else if (ch == 0x04)
            {
                if (line_position == 0)
                    /* No input which makes lua interpreter close */
                    return 0;
                else
                    continue;
            }
            
            /* end of line */
            if (ch == '\r' || ch == '\n')
            {
                buffer[line_position] = 0;
                rt_kprintf("\n");
                if (line_position == 0)
                {
                    /* Get a empty line, then go to get a new line */
                    goto start;
                }
                else
                {
                    return line_position;
                }
            }

            /* other control character or not an acsii character */
            if (ch < 0x20 || ch >= 0x80)
            {
                continue;
            }

            /* echo */
            rt_kprintf("%c", ch);
            buffer[line_position] = ch;
            ch = 0;
            line_position++;

            /* it's a large line, discard it */
            if (line_position >= buffer_size)
                line_position = 0;
       }
    }
}


