#ifndef __HWSPINLOCK_H
#define __HWSPINLOCK_H

#include "platform-hwspinlock.h"

#define SPINLOCK_SYSTATUS_REG (SPIN_LOCK_BASE + 0x000)
#define SPINLOCK_STATUS_REG   (SPIN_LOCK_BASE + 0x010)
#define SPINLOCK_LOCK_REG(x)  (SPIN_LOCK_BASE + 0x100 + x * 4)

#endif /* __HWSPINLOCK_H */
