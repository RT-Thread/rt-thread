#ifndef __PTHREAD_ATTR_H__
#define __PTHREAD_ATTR_H__

struct pthread_attr
{
    void* 		stack_base;
	rt_uint16_t stack_size;		/* stack size of thread */

	rt_uint8_t priority;		/* priority of thread */
	rt_uint8_t detachstate;		/* detach state */
	rt_uint8_t policy;			/* scheduler policy */
	rt_uint8_t inheritsched;	/* Inherit parent prio/policy */
};
typedef struct pthread_attr pthread_attr_t;
extern const pthread_attr_t pthread_default_attr;

int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_init(pthread_attr_t *attr);

#endif
