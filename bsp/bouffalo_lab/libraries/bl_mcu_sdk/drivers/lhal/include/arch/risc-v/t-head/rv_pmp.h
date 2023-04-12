#ifndef _RV_PMP_H_
#define _RV_PMP_H_

#include "stdint.h"

#define RV_PMP_ENTRY          (8)

#define ENTRY_FLAG_PERM_R     (1 << 0)
#define ENTRY_FLAG_PERM_W     (1 << 1)
#define ENTRY_FLAG_PERM_X     (1 << 2)
#define ENTRY_FLAG_ADDR_OFF   (0 << 3)
#define ENTRY_FLAG_ADDR_TOR   (1 << 3)
#define ENTRY_FLAG_ADDR_NAPOT (3 << 3)
#define ENTRY_FLAG_ADDR_MASK  (3 << 3)
#define ENTRY_FLAG_M_MODE_L   (1 << 7)

#define ENTRY_FLAG_SIZE       (8)
#define ENTRY_FLAG_MASK       (0xFF)

#define ENTRY_IN_CFG_REG      (__riscv_xlen / ENTRY_FLAG_SIZE)

/* E907: the smallest granularity is 128B */
/* C906: the smallest granularity is 4K */
#define PMP_REG_SZ_128B       (1 << 7)
#define PMP_REG_SZ_256B       (1 << 8)
#define PMP_REG_SZ_512B       (1 << 9)
#define PMP_REG_SZ_1K         (1 << 10)
#define PMP_REG_SZ_2K         (1 << 11)
#define PMP_REG_SZ_4K         (1 << 12)
#define PMP_REG_SZ_8K         (1 << 13)
#define PMP_REG_SZ_16K        (1 << 14)
#define PMP_REG_SZ_32K        (1 << 15)
#define PMP_REG_SZ_64K        (1 << 16)
#define PMP_REG_SZ_128K       (1 << 17)
#define PMP_REG_SZ_256K       (1 << 18)
#define PMP_REG_SZ_512K       (1 << 19)
#define PMP_REG_SZ_1M         (1 << 20)
#define PMP_REG_SZ_2M         (1 << 21)
#define PMP_REG_SZ_4M         (1 << 22)
#define PMP_REG_SZ_8M         (1 << 23)
#define PMP_REG_SZ_16M        (1 << 24)
#define PMP_REG_SZ_32M        (1 << 25)
#define PMP_REG_SZ_64M        (1 << 26)
#define PMP_REG_SZ_128M       (1 << 27)
#define PMP_REG_SZ_256M       (1 << 28)
#define PMP_REG_SZ_512M       (1 << 29)
#define PMP_REG_SZ_1G         (1 << 30)
#define PMP_REG_SZ_1024M      (PMP_REG_SZ_1G)

typedef enum _pmp_status_type_ {
    PMP_STATUS_OK = 0,
    PMP_STATUS_BUSY,
    PMP_STATUS_DENIED,
    PMP_STATUS_INVALID,
    PMP_STATUS_UNSUPPORTED,
    PMP_STATUS_MAX = 0x7FFFFFFF
} pmp_status_type_e;

typedef enum _addr_match_type_ {
    PMP_ADDR_MATCH_OFF = 0,
    PMP_ADDR_MATCH_TOR,
    PMP_ADDR_MATCH_NA4,
    PMP_ADDR_MATCH_NAPOT
} pmp_addr_match_type_e;

typedef struct _pmp_config_entry {
    uintptr_t entry_pa_base;
    uintptr_t entry_pa_length;
    uintptr_t entry_flag;
} pmp_config_entry_t;

pmp_status_type_e rvpmp_fill_entry(const pmp_config_entry_t *entry, uintptr_t i, uintptr_t force);
pmp_status_type_e rvpmp_init(const pmp_config_entry_t *entry, uintptr_t n);

#endif /* _RV_PMP_H_ */
