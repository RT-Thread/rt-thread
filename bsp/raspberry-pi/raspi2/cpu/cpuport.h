#ifndef  CPUPORT_H__
#define  CPUPORT_H__

typedef union {
    unsigned long slock;
    struct __arch_tickets {
        unsigned short owner;
        unsigned short next;
    } tickets;
} rt_hw_spinlock_t;

#endif  /*CPUPORT_H__*/
