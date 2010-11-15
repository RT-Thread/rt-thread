#ifndef __PTHREAD_SPIN_H__
#define __PTHREAD_SPIN_H__
#include <pthread.h>

/* spinlock implementation, (ADVANCED REALTIME THREADS)*/
struct pthread_spinlock
{
	int lock;
};
typedef struct pthread_spinlock pthread_spinlock_t;

int pthread_spin_init (pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy (pthread_spinlock_t *lock);

int pthread_spin_lock (pthread_spinlock_t * lock);
int pthread_spin_trylock (pthread_spinlock_t * lock);
int pthread_spin_unlock (pthread_spinlock_t * lock);

#endif
