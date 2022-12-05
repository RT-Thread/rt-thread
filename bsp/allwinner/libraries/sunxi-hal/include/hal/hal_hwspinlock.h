#ifndef __HW_SPIN_LOCK__
#define __HW_SPIN_LOCK__

void hal_hwspinlock_init(void);
void hal_hwspinlock_put(int num);
void hal_hwspinlock_get(int num);
int hal_hwspinlock_check_taken(int num);

#endif
