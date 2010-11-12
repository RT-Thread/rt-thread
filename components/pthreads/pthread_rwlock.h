#ifndef __PTHREAD_RWLOCK_H__
#define __PTHREAD_RWLOCK_H__

int pthread_rwlock_init (pthread_rwlock_t * rwlock, const pthread_rwlockattr_t * attr);
int pthread_rwlock_destroy (pthread_rwlock_t * rwlock);

int pthread_rwlock_rdlock (pthread_rwlock_t * rwlock);
int pthread_rwlock_tryrdlock (pthread_rwlock_t * rwlock);
int pthread_rwlock_timedrdlock (pthread_rwlock_t * rwlock, const struct timespec *abstime);

int pthread_rwlock_timedwrlock (pthread_rwlock_t * rwlock, const struct timespec *abstime);
int pthread_rwlock_trywrlock (pthread_rwlock_t * rwlock);
int pthread_rwlock_unlock (pthread_rwlock_t * rwlock);
int pthread_rwlock_wrlock (pthread_rwlock_t * rwlock);

int pthread_rwlockattr_init (pthread_rwlockattr_t * attr);
int pthread_rwlockattr_destroy (pthread_rwlockattr_t * attr);
int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t * attr, int *pshared);
int pthread_rwlockattr_setpshared (pthread_rwlockattr_t * attr, int pshared);

#endif
