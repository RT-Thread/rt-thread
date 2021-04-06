#include "rtthread.h"
#include <stdlib.h>

rt_base_t _level = 0;

rt_base_t rt_hw_interrupt_disable(void)
{
    return _level;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    _level = level;
}

void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to)
{

}

void rt_hw_context_switch_interrupt(rt_uint32_t from, rt_uint32_t to)
{

}

RT_WEAK void rt_hw_cpu_shutdown(void)
{

}

void rt_hw_context_switch_to(rt_uint32_t to)
{

}

rt_uint8_t* rt_hw_stack_init(void *pEntry,void *pParam,rt_uint8_t *pStackAddr,void *pExit)
{
    return RT_NULL;
}

// stdout spy

struct outputNode
{
    char *data_t;
    struct outputNode* next;
};

static struct outputNode* head = RT_NULL, *tail = RT_NULL;

void rt_hw_console_output(const char *str)
{
    const char *pStr = str;

    int strLength = 0;
    while(*pStr++ != '\0') strLength++;

    if (strLength == 0)
    {
        return;
    }

    struct outputNode* p = malloc(sizeof(struct outputNode));
    p->data_t = malloc(sizeof(char) * (strLength + 1));

    for (int i = 0; i < strLength; i++)
    {
        p->data_t[i] = str[i];
    }
    p->data_t[strLength] = '\0';

    if (head == RT_NULL) 
    {
        head = tail = p;
        return;
    }

    tail->next = p;
    tail = p;

    return;
}

const char* stdouSpy_getOutput(void) 
{
    return head->data_t;
}

void stdouSpy_Pop(void)
{
    if (head == RT_NULL)
    {
        return;
    }

    struct outputNode* p = head;
    head = head->next;

    free(p->data_t);
    free(p);
}

void stdouSpy_Clear(void)
{
    while(head)
    {
        stdouSpy_Pop();
    }
}

int stdouSpy_Length(void)
{
    int length = 0;
    const struct outputNode* p = head;

    while(p != RT_NULL)
    {
        p = p->next;
        length++;
    }

    return length;
}
