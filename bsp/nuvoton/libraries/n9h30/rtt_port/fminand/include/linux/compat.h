#ifndef _LINUX_COMPAT_H_
#define _LINUX_COMPAT_H_

#include "rtthread.h"
#include "rtdevice.h"
#include <stdbool.h>

#define __UBOOT__
//#include <malloc.h>
//#include <linux/types.h>
//#include <linux/err.h>
//#include <linux/kernel.h>

typedef off_t loff_t;
typedef uint8_t  __u8;
typedef uint16_t __u16;
typedef uint32_t __u32;
typedef uint64_t __u64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef u8 __le8;
typedef u16 __le16;
typedef u32 __le32;
typedef u64 __le64;

typedef unsigned int     u_int;
typedef unsigned char    u_char;
typedef unsigned long    u_long;

typedef unsigned gfp_t;

#define min_t(type,x,y) ((type)x < (type)y ? (type) x: (type)y)
#define max_t(type,x,y) ((type)x > (type)y ? (type) x: (type)y)
#ifndef min
    #define min(a, b) (a < b ? a : b)
#endif
#ifndef max
    #define max(a, b) (a > b ? a : b)
#endif

#define __iomem

#define do_div(n,base) (n = n/base)

static __inline __attribute__((const))
bool is_power_of_2(unsigned long n)
{
    return (n != 0 && ((n & (n - 1)) == 0));
}


/*
 * ffs: find first bit set. This is defined the same way as
 * the libc and compiler builtin ffs routines, therefore
 * differs in spirit from the above ffz (man ffs).
 */

static __inline int generic_ffs(int x)
{
    int r = 1;

    if (!x)
        return 0;
    if (!(x & 0xffff))
    {
        x >>= 16;
        r += 16;
    }
    if (!(x & 0xff))
    {
        x >>= 8;
        r += 8;
    }
    if (!(x & 0xf))
    {
        x >>= 4;
        r += 4;
    }
    if (!(x & 3))
    {
        x >>= 2;
        r += 2;
    }
    if (!(x & 1))
    {
        x >>= 1;
        r += 1;
    }
    return r;
}

/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static __inline int generic_fls(int x)
{
    int r = 32;

    if (!x)
        return 0;
    if (!(x & 0xffff0000u))
    {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u))
    {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u))
    {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u))
    {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u))
    {
        x <<= 1;
        r -= 1;
    }
    return r;
}


/*
 * hweightN: returns the hamming weight (i.e. the number
 * of bits set) of a N-bit word
 */

static __inline unsigned int generic_hweight32(unsigned int w)
{
    unsigned int res = (w & 0x55555555) + ((w >> 1) & 0x55555555);
    res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
    res = (res & 0x0F0F0F0F) + ((res >> 4) & 0x0F0F0F0F);
    res = (res & 0x00FF00FF) + ((res >> 8) & 0x00FF00FF);
    return (res & 0x0000FFFF) + ((res >> 16) & 0x0000FFFF);
}

static __inline unsigned int generic_hweight16(unsigned int w)
{
    unsigned int res = (w & 0x5555) + ((w >> 1) & 0x5555);
    res = (res & 0x3333) + ((res >> 2) & 0x3333);
    res = (res & 0x0F0F) + ((res >> 4) & 0x0F0F);
    return (res & 0x00FF) + ((res >> 8) & 0x00FF);
}

static __inline unsigned int generic_hweight8(unsigned int w)
{
    unsigned int res = (w & 0x55) + ((w >> 1) & 0x55);
    res = (res & 0x33) + ((res >> 2) & 0x33);
    return (res & 0x0F) + ((res >> 4) & 0x0F);
}

#define hweight32(x) generic_hweight32(x)
#define hweight16(x) generic_hweight16(x)
#define hweight8(x) generic_hweight8(x)

#define memset  rt_memset
#define memcpy  rt_memcpy
#define strncmp rt_strncmp
#define strcmp  rt_strcmp

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define BIT(nr)         (1UL << (nr))
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#ifndef PLATFORM__SET_BIT
    #define __set_bit generic_set_bit
#endif

#ifndef PLATFORM__CLEAR_BIT
    #define __clear_bit generic_clear_bit
#endif

#ifndef PLATFORM_FFS
    #define ffs generic_ffs
#endif

#ifndef PLATFORM_FLS
    #define fls generic_fls
#endif

#define udelay      rt_hw_us_delay
#define sysprintf rt_kprintf

#define MAX_ERRNO   4095

#define IS_ERR_VALUE(x) ((x) >= (unsigned long)-MAX_ERRNO)

static __inline void *ERR_PTR(long error)
{
    return (void *) error;
}

static __inline long PTR_ERR(const void *ptr)
{
    return (long) ptr;
}

static __inline long IS_ERR(const void *ptr)
{
    return IS_ERR_VALUE((unsigned long)ptr);
}


//extern void sysprintf (char *pcStr,...);
//struct unused {};
//typedef struct unused unused_t;

struct p_current
{
    int pid;
};

extern struct p_current *current;

#define ndelay(x)   udelay(1)

#define dev_dbg(dev, fmt, args...)      \
    debug(fmt, ##args)
#define dev_vdbg(dev, fmt, args...)     \
    debug(fmt, ##args)
#define dev_info(dev, fmt, args...)     \
    rt_kprintf(fmt, ##args)
#define dev_err(dev, fmt, args...)      \
    rt_kprintf(fmt, ##args)
#define dev_warn(dev, fmt, args...)     \
    rt_kprintf(fmt, ##args)
#define printk  rt_kprintf
#define printk_once rt_kprintf

#define KERN_EMERG
#define KERN_ALERT
#define KERN_CRIT
#define KERN_ERR
#define KERN_WARNING
#define KERN_NOTICE
#define KERN_INFO
#define KERN_DEBUG

#define GFP_ATOMIC ((gfp_t) 0)
#define GFP_KERNEL ((gfp_t) 0)
#define GFP_NOFS ((gfp_t) 0)
#define GFP_USER ((gfp_t) 0)
#define __GFP_NOWARN ((gfp_t) 0)
#define __GFP_ZERO  ((__force gfp_t)0x8000u)    /* Return zeroed page on success */

#if 0

void *kmalloc(size_t size, int flags);

static inline void *kzalloc(size_t size, gfp_t flags)
{
    return kmalloc(size, flags | __GFP_ZERO);
}

static inline void *kmalloc_array(size_t n, size_t size, gfp_t flags)
{
    if (size != 0 && n > SIZE_MAX / size)
        return NULL;
    return kmalloc(n * size, flags | __GFP_ZERO);
}

static inline void *kcalloc(size_t n, size_t size, gfp_t flags)
{
    return kmalloc_array(n, size, flags | __GFP_ZERO);
}

#define vmalloc(size)   kmalloc(size, 0)
#define __vmalloc(size, flags, pgsz)    kmalloc(size, flags)
static inline void *vzalloc(unsigned long size)
{
    return kzalloc(size, 0);
}
static inline void kfree(const void *block)
{
    free((void *)block);
}
static inline void vfree(const void *addr)
{
    free((void *)addr);
}

struct kmem_cache
{
    int sz;
};

struct kmem_cache *get_mem(int element_sz);
#define kmem_cache_create(a, sz, c, d, e)   get_mem(sz)
void *kmem_cache_alloc(struct kmem_cache *obj, int flag);
static inline void kmem_cache_free(struct kmem_cache *cachep, void *obj)
{
    free(obj);
}
static inline void kmem_cache_destroy(struct kmem_cache *cachep)
{
    free(cachep);
}
#endif // if 0

#define DECLARE_WAITQUEUE(...)  do { } while (0)
#define add_wait_queue(...) do { } while (0)
#define remove_wait_queue(...)  do { } while (0)

#define KERNEL_VERSION(a,b,c)   (((a) << 16) + ((b) << 8) + (c))

#ifndef BUG
#define BUG() do { \
    rt_kprintf("U-Boot BUG at %s:%d!\n", __FILE__, __LINE__); \
} while (0)

#define BUG_ON(condition) do { if (condition) BUG(); } while(0)
#endif /* BUG */

#define WARN_ON(x) if (x) {sysprintf("WARNING in %s line %d\n" \
                  , __FILE__, __LINE__); }

#define PAGE_SIZE   4096

#if 0
/* drivers/char/random.c */
#define get_random_bytes(...)

/* include/linux/leds.h */
struct led_trigger {};

#define DEFINE_LED_TRIGGER(x)       static struct led_trigger *x;
enum led_brightness
{
    LED_OFF     = 0,
    LED_HALF    = 127,
    LED_FULL    = 255,
};

static inline void led_trigger_register_simple(const char *name,
        struct led_trigger **trigger) {}
static inline void led_trigger_unregister_simple(struct led_trigger *trigger) {}
static inline void led_trigger_event(struct led_trigger *trigger,
                                     enum led_brightness event) {}
#endif // if 0

/* uapi/linux/limits.h */
#define XATTR_LIST_MAX 65536    /* size of extended attribute namelist (64k) */

/**
 * The type used for indexing onto a disc or disc partition.
 *
 * Linux always considers sectors to be 512 bytes long independently
 * of the devices real block size.
 *
 * blkcnt_t is the type of the inode's block count.
 */
//#ifdef CONFIG_LBDAF
//    typedef u64 sector_t;
//    typedef u64 blkcnt_t;
//#else
//    typedef unsigned long sector_t;
//    typedef unsigned long blkcnt_t;
//#endif

/* module */
#define THIS_MODULE     0
#define try_module_get(...) 1
#define module_put(...)     do { } while (0)
#define module_init(...)
#define module_exit(...)
#define EXPORT_SYMBOL(...)
#define EXPORT_SYMBOL_GPL(...)
#define module_param(...)
#define module_param_call(...)
#define MODULE_PARM_DESC(...)
#define MODULE_VERSION(...)
#define MODULE_DESCRIPTION(...)
#define MODULE_AUTHOR(...)
#define MODULE_LICENSE(...)
#define MODULE_ALIAS(...)
#define __module_get(...)

/* character device */
#define MKDEV(...)          0
#define MAJOR(dev)          0
#define MINOR(dev)          0

#define alloc_chrdev_region(...)    0
#define unregister_chrdev_region(...)

#define class_create(...)       __builtin_return_address(0)
#define class_create_file(...)      0
#define class_register(...)     0
#define class_unregister(...)
#define class_remove_file(...)
#define class_destroy(...)
#define misc_register(...)      0
#define misc_deregister(...)

#define blocking_notifier_call_chain(...) 0

#define __initdata
#define late_initcall(...)

#define dev_set_name(...)       do { } while (0)
#define device_register(...)        0
#define device_unregister(...)
#define volume_sysfs_init(...)      0
#define volume_sysfs_close(...)     do { } while (0)

#define init_waitqueue_head(...)    do { } while (0)
#define wait_event_interruptible(...)   0
#define wake_up_interruptible(...)  do { } while (0)
#define print_hex_dump(...)     do { } while (0)
#define dump_stack(...)         do { } while (0)

#define task_pid_nr(x)          0
#define set_freezable(...)      do { } while (0)
#define try_to_freeze(...)      0
#define set_current_state(...)      do { } while (0)
#define kthread_should_stop(...)    0
#define schedule()          do { } while (0)

#define setup_timer(timer, func, data) do {} while (0)
#define del_timer_sync(timer) do {} while (0)
#define schedule_work(work) do {} while (0)
#define INIT_WORK(work, fun) do {} while (0)

//struct work_struct {};

unsigned long copy_from_user(void *dest, const void *src,
                             unsigned long count);

//typedef unused_t spinlock_t;
typedef int wait_queue_head_t;

#define spin_lock_init(lock) do {} while (0)
#define spin_lock(lock) do {} while (0)
#define spin_unlock(lock) do {} while (0)
#define spin_lock_irqsave(lock, flags) do { debug("%lu\n", flags); } while (0)
#define spin_unlock_irqrestore(lock, flags) do { flags = 0; } while (0)

#define DEFINE_MUTEX(...)
#define mutex_init(...)
#define mutex_lock(...)
#define mutex_unlock(...)

#define init_rwsem(...)         do { } while (0)
#define down_read(...)          do { } while (0)
#define down_write(...)         do { } while (0)
#define down_write_trylock(...)     1
#define up_read(...)            do { } while (0)
#define up_write(...)           do { } while (0)

//#define cond_resched()            do { } while (0)
#define yield()             do { } while (0)

#define __init
#define __exit
#define __devinit
#define __devinitdata
#define __devinitconst

#define kthread_create(...) __builtin_return_address(0)
#define kthread_stop(...)   do { } while (0)
#define wake_up_process(...)    do { } while (0)

struct rw_semaphore
{
    int i;
};
#define down_write(...)         do { } while (0)
#define up_write(...)           do { } while (0)
#define down_read(...)          do { } while (0)
#define up_read(...)            do { } while (0)
struct device
{
    struct device       *parent;
    struct class        *class;
    dev_t           devt;   /* dev_t, creates the sysfs "dev" */
    void (*release)(struct device *dev);
    /* This is used from drivers/usb/musb-new subsystem only */
    void        *driver_data;   /* data private to the driver */
    void            *device_data;   /* data private to the device */
};
struct mutex
{
    int i;
};
struct kernel_param
{
    int i;
};

struct cdev
{
    int owner;
    dev_t dev;
};
#define cdev_init(...)      do { } while (0)
#define cdev_add(...)       0
#define cdev_del(...)       do { } while (0)

#define prandom_u32(...)    0

typedef struct
{
    uid_t val;
} kuid_t;

typedef struct
{
    gid_t val;
} kgid_t;

/* from include/linux/types.h */

/**
 * struct callback_head - callback structure for use with RCU and task_work
 * @next: next update requests in a list
 * @func: actual update function to call after the grace period.
 */
struct callback_head
{
    struct callback_head *next;
    void (*func)(struct callback_head *head);
};
#define rcu_head callback_head
enum writeback_sync_modes
{
    WB_SYNC_NONE,   /* Don't wait on anything */
    WB_SYNC_ALL,    /* Wait on every mapping */
};

/* from include/linux/writeback.h */
/*
 * A control structure which tells the writeback code what to do.  These are
 * always on the stack, and hence need no locking.  They are always initialised
 * in a manner such that unspecified fields are set to zero.
 */
struct writeback_control
{
    long nr_to_write;       /* Write this many pages, and decrement
                       this for each page written */
    long pages_skipped;     /* Pages which were not written */

    /*
     * For a_ops->writepages(): if start or end are non-zero then this is
     * a hint that the filesystem need only write out the pages inside that
     * byterange.  The byte at `end' is included in the writeout request.
     */
    loff_t range_start;
    loff_t range_end;

    enum writeback_sync_modes sync_mode;

    unsigned for_kupdate: 1;    /* A kupdate writeback */
    unsigned for_background: 1; /* A background writeback */
    unsigned tagged_writepages: 1;  /* tag-and-write to avoid livelock */
    unsigned for_reclaim: 1;    /* Invoked from the page allocator */
    unsigned range_cyclic: 1;   /* range_start is cyclic */
    unsigned for_sync: 1;       /* sync(2) WB_SYNC_ALL writeback */
};

//void *kmemdup(const void *src, size_t len, gfp_t gfp);

typedef int irqreturn_t;

//struct timer_list {};
//struct notifier_block {};

typedef unsigned long dmaaddr_t;

#define pm_runtime_get_sync(dev) do {} while (0)
#define pm_runtime_put(dev) do {} while (0)
#define pm_runtime_put_sync(dev) do {} while (0)
#define pm_runtime_use_autosuspend(dev) do {} while (0)
#define pm_runtime_set_autosuspend_delay(dev, delay) do {} while (0)
#define pm_runtime_enable(dev) do {} while (0)

#define IRQ_NONE 0
#define IRQ_HANDLED 1
#define IRQ_WAKE_THREAD 2

#define dev_set_drvdata(dev, data) do {} while (0)

#define enable_irq(...)
#define disable_irq(...)
#define disable_irq_wake(irq) do {} while (0)
#define enable_irq_wake(irq) -EINVAL
#define free_irq(irq, data) do {} while (0)
#define request_irq(nr, f, flags, nm, data) 0

#endif
