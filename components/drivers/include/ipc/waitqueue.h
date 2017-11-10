#ifndef WAITQUEUE_H__
#define WAITQUEUE_H__

#include <rtthread.h>

struct rt_wqueue_node;

typedef rt_list_t rt_wqueue_t;
typedef int (*rt_wqueue_func_t)(struct rt_wqueue_node *wait, void *key);

struct rt_wqueue_node
{
	rt_thread_t polling_thread;
	rt_list_t   list;

	rt_wqueue_func_t wakeup;
	rt_uint32_t key;
};
typedef struct rt_wqueue_node rt_wqueue_node_t;

int __wqueue_default_wake(struct rt_wqueue_node *wait, void *key);

void rt_wqueue_add(rt_wqueue_t *queue, struct rt_wqueue_node *node);
void rt_wqueue_remove(struct rt_wqueue_node *node);
int  rt_wqueue_wait(rt_wqueue_t *queue, int condition, int timeout);
void rt_wqueue_wakeup(rt_wqueue_t *queue, void *key);

#define DEFINE_WAIT_FUNC(name, function)                \
    struct rt_wqueue_node name = {                      \
        rt_current_thread,                              \
        RT_LIST_OBJECT_INIT(((name).list)),             \
                                                        \
        function,                                       \
        0                                               \
    }

#define DEFINE_WAIT(name) DEFINE_WAIT_FUNC(name, __wqueue_default_wake)

#endif
