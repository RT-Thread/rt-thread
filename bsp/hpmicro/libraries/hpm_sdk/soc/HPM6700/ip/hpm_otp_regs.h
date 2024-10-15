/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_OTP_H
#define HPM_OTP_H

typedef struct {
    __RW uint32_t SHADOW[128];                 /* 0x0 - 0x1FC: Fuse shadow registers */
    __RW uint32_t SHADOW_LOCK[8];              /* 0x200 - 0x21C: Fuse shadow lock */
    __R  uint8_t  RESERVED0[480];              /* 0x220 - 0x3FF: Reserved */
    __RW uint32_t FUSE[128];                   /* 0x400 - 0x5FC: Fuse Array */
    __RW uint32_t FUSE_LOCK[8];                /* 0x600 - 0x61C: Fuse lock */
    __R  uint8_t  RESERVED1[480];              /* 0x620 - 0x7FF: Reserved */
    __RW uint32_t UNLOCK;                      /* 0x800: UNLOCK */
    __RW uint32_t DATA;                        /* 0x804: DATA */
    __RW uint32_t ADDR;                        /* 0x808: ADDR */
    __RW uint32_t CMD;                         /* 0x80C: CMD */
    __R  uint8_t  RESERVED2[496];              /* 0x810 - 0x9FF: Reserved */
    __RW uint32_t LOAD_REQ;                    /* 0xA00: LOAD Request */
    __RW uint32_t LOAD_COMP;                   /* 0xA04: LOAD complete */
    __R  uint8_t  RESERVED3[24];               /* 0xA08 - 0xA1F: Reserved */
    __RW uint32_t REGION[4];                   /* 0xA20 - 0xA2C: LOAD region */
    __R  uint8_t  RESERVED4[464];              /* 0xA30 - 0xBFF: Reserved */
    __RW uint32_t INT_FLAG;                    /* 0xC00: interrupt flag */
    __RW uint32_t INT_EN;                      /* 0xC04: interrupt enable */
} OTP_Type;


/* Bitfield definition for register array: SHADOW */
/*
 * SHADOW (RW)
 *
 * shadow register of fuse for pmic area
 * for PMIC, index valid for 0-15, for SOC index valid for 16-128
 */
#define OTP_SHADOW_SHADOW_MASK (0xFFFFFFFFUL)
#define OTP_SHADOW_SHADOW_SHIFT (0U)
#define OTP_SHADOW_SHADOW_SET(x) (((uint32_t)(x) << OTP_SHADOW_SHADOW_SHIFT) & OTP_SHADOW_SHADOW_MASK)
#define OTP_SHADOW_SHADOW_GET(x) (((uint32_t)(x) & OTP_SHADOW_SHADOW_MASK) >> OTP_SHADOW_SHADOW_SHIFT)

/* Bitfield definition for register array: SHADOW_LOCK */
/*
 * LOCK (RW)
 *
 * lock for pmic part shadow registers, 2 bits per 32 bit word, lock behavior is different between different fuse types
 * 00: not locked
 * 01: soft locked
 * 10: not locked, and cannot lock in furture
 * 11: double locked
 */
#define OTP_SHADOW_LOCK_LOCK_MASK (0xFFFFFFFFUL)
#define OTP_SHADOW_LOCK_LOCK_SHIFT (0U)
#define OTP_SHADOW_LOCK_LOCK_SET(x) (((uint32_t)(x) << OTP_SHADOW_LOCK_LOCK_SHIFT) & OTP_SHADOW_LOCK_LOCK_MASK)
#define OTP_SHADOW_LOCK_LOCK_GET(x) (((uint32_t)(x) & OTP_SHADOW_LOCK_LOCK_MASK) >> OTP_SHADOW_LOCK_LOCK_SHIFT)

/* Bitfield definition for register array: FUSE */
/*
 * FUSE (RW)
 *
 * fuse array, valid in PMIC part only
 * read operation will read out value in fuse array
 * write operation will update fuse array value(please make sure fuse is unlocked and  2.5V power is ready)
 */
#define OTP_FUSE_FUSE_MASK (0xFFFFFFFFUL)
#define OTP_FUSE_FUSE_SHIFT (0U)
#define OTP_FUSE_FUSE_SET(x) (((uint32_t)(x) << OTP_FUSE_FUSE_SHIFT) & OTP_FUSE_FUSE_MASK)
#define OTP_FUSE_FUSE_GET(x) (((uint32_t)(x) & OTP_FUSE_FUSE_MASK) >> OTP_FUSE_FUSE_SHIFT)

/* Bitfield definition for register array: FUSE_LOCK */
/*
 * LOCK (RW)
 *
 * lock for fuse array, 2 bits per 32 bit word, lock behavior is different between different fuse types
 * 00: not locked
 * 01: soft locked
 * 10: not locked, and cannot lock in furture
 * 11: double locked
 */
#define OTP_FUSE_LOCK_LOCK_MASK (0xFFFFFFFFUL)
#define OTP_FUSE_LOCK_LOCK_SHIFT (0U)
#define OTP_FUSE_LOCK_LOCK_SET(x) (((uint32_t)(x) << OTP_FUSE_LOCK_LOCK_SHIFT) & OTP_FUSE_LOCK_LOCK_MASK)
#define OTP_FUSE_LOCK_LOCK_GET(x) (((uint32_t)(x) & OTP_FUSE_LOCK_LOCK_MASK) >> OTP_FUSE_LOCK_LOCK_SHIFT)

/* Bitfield definition for register: UNLOCK */
/*
 * UNLOCK (RW)
 *
 * unlock word for fuse array operation
 * write "OPEN" to unlock fuse array, write any other value will lock write to fuse.
 * Please make sure 24M crystal is running and 2.5V LDO working properly
 */
#define OTP_UNLOCK_UNLOCK_MASK (0xFFFFFFFFUL)
#define OTP_UNLOCK_UNLOCK_SHIFT (0U)
#define OTP_UNLOCK_UNLOCK_SET(x) (((uint32_t)(x) << OTP_UNLOCK_UNLOCK_SHIFT) & OTP_UNLOCK_UNLOCK_MASK)
#define OTP_UNLOCK_UNLOCK_GET(x) (((uint32_t)(x) & OTP_UNLOCK_UNLOCK_MASK) >> OTP_UNLOCK_UNLOCK_SHIFT)

/* Bitfield definition for register: DATA */
/*
 * DATA (RW)
 *
 * data register for non-blocking access
 * this register hold dat read from fuse array or data to by programmed to fuse array
 */
#define OTP_DATA_DATA_MASK (0xFFFFFFFFUL)
#define OTP_DATA_DATA_SHIFT (0U)
#define OTP_DATA_DATA_SET(x) (((uint32_t)(x) << OTP_DATA_DATA_SHIFT) & OTP_DATA_DATA_MASK)
#define OTP_DATA_DATA_GET(x) (((uint32_t)(x) & OTP_DATA_DATA_MASK) >> OTP_DATA_DATA_SHIFT)

/* Bitfield definition for register: ADDR */
/*
 * ADDR (RW)
 *
 * word address to be read or write
 */
#define OTP_ADDR_ADDR_MASK (0x7FU)
#define OTP_ADDR_ADDR_SHIFT (0U)
#define OTP_ADDR_ADDR_SET(x) (((uint32_t)(x) << OTP_ADDR_ADDR_SHIFT) & OTP_ADDR_ADDR_MASK)
#define OTP_ADDR_ADDR_GET(x) (((uint32_t)(x) & OTP_ADDR_ADDR_MASK) >> OTP_ADDR_ADDR_SHIFT)

/* Bitfield definition for register: CMD */
/*
 * CMD (RW)
 *
 * command to access fure array
 * "BLOW" will update fuse word at ADDR to value hold in DATA
 * "READ" will fetch fuse value in at ADDR to DATA register
 */
#define OTP_CMD_CMD_MASK (0xFFFFFFFFUL)
#define OTP_CMD_CMD_SHIFT (0U)
#define OTP_CMD_CMD_SET(x) (((uint32_t)(x) << OTP_CMD_CMD_SHIFT) & OTP_CMD_CMD_MASK)
#define OTP_CMD_CMD_GET(x) (((uint32_t)(x) & OTP_CMD_CMD_MASK) >> OTP_CMD_CMD_SHIFT)

/* Bitfield definition for register: LOAD_REQ */
/*
 * REQUEST (RW)
 *
 * reload request for 4 regions
 * bit0: region0
 * bit1: region1
 * bit2: region2
 * bit3: region3
 */
#define OTP_LOAD_REQ_REQUEST_MASK (0xFU)
#define OTP_LOAD_REQ_REQUEST_SHIFT (0U)
#define OTP_LOAD_REQ_REQUEST_SET(x) (((uint32_t)(x) << OTP_LOAD_REQ_REQUEST_SHIFT) & OTP_LOAD_REQ_REQUEST_MASK)
#define OTP_LOAD_REQ_REQUEST_GET(x) (((uint32_t)(x) & OTP_LOAD_REQ_REQUEST_MASK) >> OTP_LOAD_REQ_REQUEST_SHIFT)

/* Bitfield definition for register: LOAD_COMP */
/*
 * COMPLETE (RW)
 *
 * reload complete sign for 4 regions
 * bit0: region 0
 * bit1: region1
 * bit2: region2
 * bit3: region3
 */
#define OTP_LOAD_COMP_COMPLETE_MASK (0xFU)
#define OTP_LOAD_COMP_COMPLETE_SHIFT (0U)
#define OTP_LOAD_COMP_COMPLETE_SET(x) (((uint32_t)(x) << OTP_LOAD_COMP_COMPLETE_SHIFT) & OTP_LOAD_COMP_COMPLETE_MASK)
#define OTP_LOAD_COMP_COMPLETE_GET(x) (((uint32_t)(x) & OTP_LOAD_COMP_COMPLETE_MASK) >> OTP_LOAD_COMP_COMPLETE_SHIFT)

/* Bitfield definition for register array: REGION */
/*
 * STOP (RW)
 *
 * stop address of load region, fuse word at end address will NOT be reloaded
 * region0: fixed at 8
 * region1: fixed at 16
 * region2: fixed at 0,
 * region3: usrer configurable
 */
#define OTP_REGION_STOP_MASK (0x7F00U)
#define OTP_REGION_STOP_SHIFT (8U)
#define OTP_REGION_STOP_SET(x) (((uint32_t)(x) << OTP_REGION_STOP_SHIFT) & OTP_REGION_STOP_MASK)
#define OTP_REGION_STOP_GET(x) (((uint32_t)(x) & OTP_REGION_STOP_MASK) >> OTP_REGION_STOP_SHIFT)

/*
 * START (RW)
 *
 * start address of load region,  fuse word at start address will be reloaded
 * region0: fixed at 0
 * region1: fixed at 8
 * region2: fixed at 16,
 * region3: usrer configurable
 */
#define OTP_REGION_START_MASK (0x7FU)
#define OTP_REGION_START_SHIFT (0U)
#define OTP_REGION_START_SET(x) (((uint32_t)(x) << OTP_REGION_START_SHIFT) & OTP_REGION_START_MASK)
#define OTP_REGION_START_GET(x) (((uint32_t)(x) & OTP_REGION_START_MASK) >> OTP_REGION_START_SHIFT)

/* Bitfield definition for register: INT_FLAG */
/*
 * WRITE (RW)
 *
 * fuse write flag, write 1 to clear
 * 0: fuse is not written or writing
 * 1: value in DATA register is programmed into fuse
 */
#define OTP_INT_FLAG_WRITE_MASK (0x4U)
#define OTP_INT_FLAG_WRITE_SHIFT (2U)
#define OTP_INT_FLAG_WRITE_SET(x) (((uint32_t)(x) << OTP_INT_FLAG_WRITE_SHIFT) & OTP_INT_FLAG_WRITE_MASK)
#define OTP_INT_FLAG_WRITE_GET(x) (((uint32_t)(x) & OTP_INT_FLAG_WRITE_MASK) >> OTP_INT_FLAG_WRITE_SHIFT)

/*
 * READ (RW)
 *
 * fuse read flag, write 1 to clear
 * 0: fuse is not read or reading
 * 1: fuse value is put in DATA register
 */
#define OTP_INT_FLAG_READ_MASK (0x2U)
#define OTP_INT_FLAG_READ_SHIFT (1U)
#define OTP_INT_FLAG_READ_SET(x) (((uint32_t)(x) << OTP_INT_FLAG_READ_SHIFT) & OTP_INT_FLAG_READ_MASK)
#define OTP_INT_FLAG_READ_GET(x) (((uint32_t)(x) & OTP_INT_FLAG_READ_MASK) >> OTP_INT_FLAG_READ_SHIFT)

/*
 * LOAD (RW)
 *
 * fuse load flag, write 1 to clear
 * 0: fuse is not loaded or loading
 * 1: fuse loaded
 */
#define OTP_INT_FLAG_LOAD_MASK (0x1U)
#define OTP_INT_FLAG_LOAD_SHIFT (0U)
#define OTP_INT_FLAG_LOAD_SET(x) (((uint32_t)(x) << OTP_INT_FLAG_LOAD_SHIFT) & OTP_INT_FLAG_LOAD_MASK)
#define OTP_INT_FLAG_LOAD_GET(x) (((uint32_t)(x) & OTP_INT_FLAG_LOAD_MASK) >> OTP_INT_FLAG_LOAD_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * WRITE (RW)
 *
 * fuse write interrupt enable
 * 0: fuse write interrupt is not enable
 * 1: fuse write interrupt is enable
 */
#define OTP_INT_EN_WRITE_MASK (0x4U)
#define OTP_INT_EN_WRITE_SHIFT (2U)
#define OTP_INT_EN_WRITE_SET(x) (((uint32_t)(x) << OTP_INT_EN_WRITE_SHIFT) & OTP_INT_EN_WRITE_MASK)
#define OTP_INT_EN_WRITE_GET(x) (((uint32_t)(x) & OTP_INT_EN_WRITE_MASK) >> OTP_INT_EN_WRITE_SHIFT)

/*
 * READ (RW)
 *
 * fuse read interrupt enable
 * 0: fuse read interrupt is not enable
 * 1: fuse read interrupt is enable
 */
#define OTP_INT_EN_READ_MASK (0x2U)
#define OTP_INT_EN_READ_SHIFT (1U)
#define OTP_INT_EN_READ_SET(x) (((uint32_t)(x) << OTP_INT_EN_READ_SHIFT) & OTP_INT_EN_READ_MASK)
#define OTP_INT_EN_READ_GET(x) (((uint32_t)(x) & OTP_INT_EN_READ_MASK) >> OTP_INT_EN_READ_SHIFT)

/*
 * LOAD (RW)
 *
 * fuse load interrupt enable
 * 0: fuse load interrupt is not enable
 * 1: fuse load interrupt is enable
 */
#define OTP_INT_EN_LOAD_MASK (0x1U)
#define OTP_INT_EN_LOAD_SHIFT (0U)
#define OTP_INT_EN_LOAD_SET(x) (((uint32_t)(x) << OTP_INT_EN_LOAD_SHIFT) & OTP_INT_EN_LOAD_MASK)
#define OTP_INT_EN_LOAD_GET(x) (((uint32_t)(x) & OTP_INT_EN_LOAD_MASK) >> OTP_INT_EN_LOAD_SHIFT)



/* SHADOW register group index macro definition */
#define OTP_SHADOW_SHADOW000 (0UL)
#define OTP_SHADOW_SHADOW001 (1UL)
#define OTP_SHADOW_SHADOW002 (2UL)
#define OTP_SHADOW_SHADOW003 (3UL)
#define OTP_SHADOW_SHADOW004 (4UL)
#define OTP_SHADOW_SHADOW005 (5UL)
#define OTP_SHADOW_SHADOW006 (6UL)
#define OTP_SHADOW_SHADOW007 (7UL)
#define OTP_SHADOW_SHADOW008 (8UL)
#define OTP_SHADOW_SHADOW009 (9UL)
#define OTP_SHADOW_SHADOW010 (10UL)
#define OTP_SHADOW_SHADOW011 (11UL)
#define OTP_SHADOW_SHADOW012 (12UL)
#define OTP_SHADOW_SHADOW013 (13UL)
#define OTP_SHADOW_SHADOW014 (14UL)
#define OTP_SHADOW_SHADOW015 (15UL)
#define OTP_SHADOW_SHADOW016 (16UL)
#define OTP_SHADOW_SHADOW017 (17UL)
#define OTP_SHADOW_SHADOW018 (18UL)
#define OTP_SHADOW_SHADOW019 (19UL)
#define OTP_SHADOW_SHADOW020 (20UL)
#define OTP_SHADOW_SHADOW021 (21UL)
#define OTP_SHADOW_SHADOW022 (22UL)
#define OTP_SHADOW_SHADOW023 (23UL)
#define OTP_SHADOW_SHADOW024 (24UL)
#define OTP_SHADOW_SHADOW025 (25UL)
#define OTP_SHADOW_SHADOW026 (26UL)
#define OTP_SHADOW_SHADOW027 (27UL)
#define OTP_SHADOW_SHADOW028 (28UL)
#define OTP_SHADOW_SHADOW029 (29UL)
#define OTP_SHADOW_SHADOW030 (30UL)
#define OTP_SHADOW_SHADOW031 (31UL)
#define OTP_SHADOW_SHADOW032 (32UL)
#define OTP_SHADOW_SHADOW033 (33UL)
#define OTP_SHADOW_SHADOW034 (34UL)
#define OTP_SHADOW_SHADOW035 (35UL)
#define OTP_SHADOW_SHADOW036 (36UL)
#define OTP_SHADOW_SHADOW037 (37UL)
#define OTP_SHADOW_SHADOW038 (38UL)
#define OTP_SHADOW_SHADOW039 (39UL)
#define OTP_SHADOW_SHADOW040 (40UL)
#define OTP_SHADOW_SHADOW041 (41UL)
#define OTP_SHADOW_SHADOW042 (42UL)
#define OTP_SHADOW_SHADOW043 (43UL)
#define OTP_SHADOW_SHADOW044 (44UL)
#define OTP_SHADOW_SHADOW045 (45UL)
#define OTP_SHADOW_SHADOW046 (46UL)
#define OTP_SHADOW_SHADOW047 (47UL)
#define OTP_SHADOW_SHADOW048 (48UL)
#define OTP_SHADOW_SHADOW049 (49UL)
#define OTP_SHADOW_SHADOW050 (50UL)
#define OTP_SHADOW_SHADOW051 (51UL)
#define OTP_SHADOW_SHADOW052 (52UL)
#define OTP_SHADOW_SHADOW053 (53UL)
#define OTP_SHADOW_SHADOW054 (54UL)
#define OTP_SHADOW_SHADOW055 (55UL)
#define OTP_SHADOW_SHADOW056 (56UL)
#define OTP_SHADOW_SHADOW057 (57UL)
#define OTP_SHADOW_SHADOW058 (58UL)
#define OTP_SHADOW_SHADOW059 (59UL)
#define OTP_SHADOW_SHADOW060 (60UL)
#define OTP_SHADOW_SHADOW061 (61UL)
#define OTP_SHADOW_SHADOW062 (62UL)
#define OTP_SHADOW_SHADOW063 (63UL)
#define OTP_SHADOW_SHADOW064 (64UL)
#define OTP_SHADOW_SHADOW065 (65UL)
#define OTP_SHADOW_SHADOW066 (66UL)
#define OTP_SHADOW_SHADOW067 (67UL)
#define OTP_SHADOW_SHADOW068 (68UL)
#define OTP_SHADOW_SHADOW069 (69UL)
#define OTP_SHADOW_SHADOW070 (70UL)
#define OTP_SHADOW_SHADOW071 (71UL)
#define OTP_SHADOW_SHADOW072 (72UL)
#define OTP_SHADOW_SHADOW073 (73UL)
#define OTP_SHADOW_SHADOW074 (74UL)
#define OTP_SHADOW_SHADOW075 (75UL)
#define OTP_SHADOW_SHADOW076 (76UL)
#define OTP_SHADOW_SHADOW077 (77UL)
#define OTP_SHADOW_SHADOW078 (78UL)
#define OTP_SHADOW_SHADOW079 (79UL)
#define OTP_SHADOW_SHADOW080 (80UL)
#define OTP_SHADOW_SHADOW081 (81UL)
#define OTP_SHADOW_SHADOW082 (82UL)
#define OTP_SHADOW_SHADOW083 (83UL)
#define OTP_SHADOW_SHADOW084 (84UL)
#define OTP_SHADOW_SHADOW085 (85UL)
#define OTP_SHADOW_SHADOW086 (86UL)
#define OTP_SHADOW_SHADOW087 (87UL)
#define OTP_SHADOW_SHADOW088 (88UL)
#define OTP_SHADOW_SHADOW089 (89UL)
#define OTP_SHADOW_SHADOW090 (90UL)
#define OTP_SHADOW_SHADOW091 (91UL)
#define OTP_SHADOW_SHADOW092 (92UL)
#define OTP_SHADOW_SHADOW093 (93UL)
#define OTP_SHADOW_SHADOW094 (94UL)
#define OTP_SHADOW_SHADOW095 (95UL)
#define OTP_SHADOW_SHADOW096 (96UL)
#define OTP_SHADOW_SHADOW097 (97UL)
#define OTP_SHADOW_SHADOW098 (98UL)
#define OTP_SHADOW_SHADOW099 (99UL)
#define OTP_SHADOW_SHADOW100 (100UL)
#define OTP_SHADOW_SHADOW101 (101UL)
#define OTP_SHADOW_SHADOW102 (102UL)
#define OTP_SHADOW_SHADOW103 (103UL)
#define OTP_SHADOW_SHADOW104 (104UL)
#define OTP_SHADOW_SHADOW105 (105UL)
#define OTP_SHADOW_SHADOW106 (106UL)
#define OTP_SHADOW_SHADOW107 (107UL)
#define OTP_SHADOW_SHADOW108 (108UL)
#define OTP_SHADOW_SHADOW109 (109UL)
#define OTP_SHADOW_SHADOW110 (110UL)
#define OTP_SHADOW_SHADOW111 (111UL)
#define OTP_SHADOW_SHADOW112 (112UL)
#define OTP_SHADOW_SHADOW113 (113UL)
#define OTP_SHADOW_SHADOW114 (114UL)
#define OTP_SHADOW_SHADOW115 (115UL)
#define OTP_SHADOW_SHADOW116 (116UL)
#define OTP_SHADOW_SHADOW117 (117UL)
#define OTP_SHADOW_SHADOW118 (118UL)
#define OTP_SHADOW_SHADOW119 (119UL)
#define OTP_SHADOW_SHADOW120 (120UL)
#define OTP_SHADOW_SHADOW121 (121UL)
#define OTP_SHADOW_SHADOW122 (122UL)
#define OTP_SHADOW_SHADOW123 (123UL)
#define OTP_SHADOW_SHADOW124 (124UL)
#define OTP_SHADOW_SHADOW125 (125UL)
#define OTP_SHADOW_SHADOW126 (126UL)
#define OTP_SHADOW_SHADOW127 (127UL)

/* SHADOW_LOCK register group index macro definition */
#define OTP_SHADOW_LOCK_LOCK00 (0UL)
#define OTP_SHADOW_LOCK_LOCK01 (1UL)
#define OTP_SHADOW_LOCK_LOCK02 (2UL)
#define OTP_SHADOW_LOCK_LOCK03 (3UL)
#define OTP_SHADOW_LOCK_LOCK04 (4UL)
#define OTP_SHADOW_LOCK_LOCK05 (5UL)
#define OTP_SHADOW_LOCK_LOCK06 (6UL)
#define OTP_SHADOW_LOCK_LOCK07 (7UL)

/* FUSE register group index macro definition */
#define OTP_FUSE_FUSE000 (0UL)
#define OTP_FUSE_FUSE001 (1UL)
#define OTP_FUSE_FUSE002 (2UL)
#define OTP_FUSE_FUSE003 (3UL)
#define OTP_FUSE_FUSE004 (4UL)
#define OTP_FUSE_FUSE005 (5UL)
#define OTP_FUSE_FUSE006 (6UL)
#define OTP_FUSE_FUSE007 (7UL)
#define OTP_FUSE_FUSE008 (8UL)
#define OTP_FUSE_FUSE009 (9UL)
#define OTP_FUSE_FUSE010 (10UL)
#define OTP_FUSE_FUSE011 (11UL)
#define OTP_FUSE_FUSE012 (12UL)
#define OTP_FUSE_FUSE013 (13UL)
#define OTP_FUSE_FUSE014 (14UL)
#define OTP_FUSE_FUSE015 (15UL)
#define OTP_FUSE_FUSE016 (16UL)
#define OTP_FUSE_FUSE017 (17UL)
#define OTP_FUSE_FUSE018 (18UL)
#define OTP_FUSE_FUSE019 (19UL)
#define OTP_FUSE_FUSE020 (20UL)
#define OTP_FUSE_FUSE021 (21UL)
#define OTP_FUSE_FUSE022 (22UL)
#define OTP_FUSE_FUSE023 (23UL)
#define OTP_FUSE_FUSE024 (24UL)
#define OTP_FUSE_FUSE025 (25UL)
#define OTP_FUSE_FUSE026 (26UL)
#define OTP_FUSE_FUSE027 (27UL)
#define OTP_FUSE_FUSE028 (28UL)
#define OTP_FUSE_FUSE029 (29UL)
#define OTP_FUSE_FUSE030 (30UL)
#define OTP_FUSE_FUSE031 (31UL)
#define OTP_FUSE_FUSE032 (32UL)
#define OTP_FUSE_FUSE033 (33UL)
#define OTP_FUSE_FUSE034 (34UL)
#define OTP_FUSE_FUSE035 (35UL)
#define OTP_FUSE_FUSE036 (36UL)
#define OTP_FUSE_FUSE037 (37UL)
#define OTP_FUSE_FUSE038 (38UL)
#define OTP_FUSE_FUSE039 (39UL)
#define OTP_FUSE_FUSE040 (40UL)
#define OTP_FUSE_FUSE041 (41UL)
#define OTP_FUSE_FUSE042 (42UL)
#define OTP_FUSE_FUSE043 (43UL)
#define OTP_FUSE_FUSE044 (44UL)
#define OTP_FUSE_FUSE045 (45UL)
#define OTP_FUSE_FUSE046 (46UL)
#define OTP_FUSE_FUSE047 (47UL)
#define OTP_FUSE_FUSE048 (48UL)
#define OTP_FUSE_FUSE049 (49UL)
#define OTP_FUSE_FUSE050 (50UL)
#define OTP_FUSE_FUSE051 (51UL)
#define OTP_FUSE_FUSE052 (52UL)
#define OTP_FUSE_FUSE053 (53UL)
#define OTP_FUSE_FUSE054 (54UL)
#define OTP_FUSE_FUSE055 (55UL)
#define OTP_FUSE_FUSE056 (56UL)
#define OTP_FUSE_FUSE057 (57UL)
#define OTP_FUSE_FUSE058 (58UL)
#define OTP_FUSE_FUSE059 (59UL)
#define OTP_FUSE_FUSE060 (60UL)
#define OTP_FUSE_FUSE061 (61UL)
#define OTP_FUSE_FUSE062 (62UL)
#define OTP_FUSE_FUSE063 (63UL)
#define OTP_FUSE_FUSE064 (64UL)
#define OTP_FUSE_FUSE065 (65UL)
#define OTP_FUSE_FUSE066 (66UL)
#define OTP_FUSE_FUSE067 (67UL)
#define OTP_FUSE_FUSE068 (68UL)
#define OTP_FUSE_FUSE069 (69UL)
#define OTP_FUSE_FUSE070 (70UL)
#define OTP_FUSE_FUSE071 (71UL)
#define OTP_FUSE_FUSE072 (72UL)
#define OTP_FUSE_FUSE073 (73UL)
#define OTP_FUSE_FUSE074 (74UL)
#define OTP_FUSE_FUSE075 (75UL)
#define OTP_FUSE_FUSE076 (76UL)
#define OTP_FUSE_FUSE077 (77UL)
#define OTP_FUSE_FUSE078 (78UL)
#define OTP_FUSE_FUSE079 (79UL)
#define OTP_FUSE_FUSE080 (80UL)
#define OTP_FUSE_FUSE081 (81UL)
#define OTP_FUSE_FUSE082 (82UL)
#define OTP_FUSE_FUSE083 (83UL)
#define OTP_FUSE_FUSE084 (84UL)
#define OTP_FUSE_FUSE085 (85UL)
#define OTP_FUSE_FUSE086 (86UL)
#define OTP_FUSE_FUSE087 (87UL)
#define OTP_FUSE_FUSE088 (88UL)
#define OTP_FUSE_FUSE089 (89UL)
#define OTP_FUSE_FUSE090 (90UL)
#define OTP_FUSE_FUSE091 (91UL)
#define OTP_FUSE_FUSE092 (92UL)
#define OTP_FUSE_FUSE093 (93UL)
#define OTP_FUSE_FUSE094 (94UL)
#define OTP_FUSE_FUSE095 (95UL)
#define OTP_FUSE_FUSE096 (96UL)
#define OTP_FUSE_FUSE097 (97UL)
#define OTP_FUSE_FUSE098 (98UL)
#define OTP_FUSE_FUSE099 (99UL)
#define OTP_FUSE_FUSE100 (100UL)
#define OTP_FUSE_FUSE101 (101UL)
#define OTP_FUSE_FUSE102 (102UL)
#define OTP_FUSE_FUSE103 (103UL)
#define OTP_FUSE_FUSE104 (104UL)
#define OTP_FUSE_FUSE105 (105UL)
#define OTP_FUSE_FUSE106 (106UL)
#define OTP_FUSE_FUSE107 (107UL)
#define OTP_FUSE_FUSE108 (108UL)
#define OTP_FUSE_FUSE109 (109UL)
#define OTP_FUSE_FUSE110 (110UL)
#define OTP_FUSE_FUSE111 (111UL)
#define OTP_FUSE_FUSE112 (112UL)
#define OTP_FUSE_FUSE113 (113UL)
#define OTP_FUSE_FUSE114 (114UL)
#define OTP_FUSE_FUSE115 (115UL)
#define OTP_FUSE_FUSE116 (116UL)
#define OTP_FUSE_FUSE117 (117UL)
#define OTP_FUSE_FUSE118 (118UL)
#define OTP_FUSE_FUSE119 (119UL)
#define OTP_FUSE_FUSE120 (120UL)
#define OTP_FUSE_FUSE121 (121UL)
#define OTP_FUSE_FUSE122 (122UL)
#define OTP_FUSE_FUSE123 (123UL)
#define OTP_FUSE_FUSE124 (124UL)
#define OTP_FUSE_FUSE125 (125UL)
#define OTP_FUSE_FUSE126 (126UL)
#define OTP_FUSE_FUSE127 (127UL)

/* FUSE_LOCK register group index macro definition */
#define OTP_FUSE_LOCK_LOCK00 (0UL)
#define OTP_FUSE_LOCK_LOCK01 (1UL)
#define OTP_FUSE_LOCK_LOCK02 (2UL)
#define OTP_FUSE_LOCK_LOCK03 (3UL)
#define OTP_FUSE_LOCK_LOCK04 (4UL)
#define OTP_FUSE_LOCK_LOCK05 (5UL)
#define OTP_FUSE_LOCK_LOCK06 (6UL)
#define OTP_FUSE_LOCK_LOCK07 (7UL)

/* REGION register group index macro definition */
#define OTP_REGION_LOAD_REGION0 (0UL)
#define OTP_REGION_LOAD_REGION1 (1UL)
#define OTP_REGION_LOAD_REGION2 (2UL)
#define OTP_REGION_LOAD_REGION3 (3UL)


#endif /* HPM_OTP_H */
