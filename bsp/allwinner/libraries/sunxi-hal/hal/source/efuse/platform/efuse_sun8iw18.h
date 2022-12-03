#ifndef __EFUSE_SUN8IW18_H
#define __EFUSE_SUN8IW18_H


#ifdef __cplusplus
extern "C"
{
#endif

#define SUNXI_SID_BASE          0x03006000
#define SID_PRCTL               (SUNXI_SID_BASE + 0x40)
#define SID_PRKEY               (SUNXI_SID_BASE + 0x50)
#define SID_RDKEY               (SUNXI_SID_BASE + 0x60)
#define SJTAG_AT0               (SUNXI_SID_BASE + 0x80)
#define SJTAG_AT1               (SUNXI_SID_BASE + 0x84)
#define SJTAG_S                 (SUNXI_SID_BASE + 0x88)

#define EFUSE_SRAM              (SUNXI_SID_BASE + 0x200)
#define EFUSE_SECURE_MODE       (SUNXI_SID_BASE + 0xA0)

#define EFUSE_CHIPD             (0x00) /* 0x0-0xf, 128bits */
#define EFUSE_BROM_CONFIG       (0x10) /* 16 bit config, 16 bits try */
#define EFUSE_BROM_TRY          (0X12) /* 16 bit*/
#define EFUSE_THERMAL_SENSOR    (0x14) /* 0x14-0x1b, 64bits */
#define EFUSE_TF_ZONE           (0X1C) /* 0x1c-0x2B, 128bits */


/* write protect */
#define EFUSE_WRITE_PROTECT     (0x30) /* 0x30-0x33, 32bits */
/* read  protect */
#define EFUSE_READ_PROTECT      (0x34) /* 0x34-0x37, 32bits */


#define SID_OP_LOCK  (0xAC)


/*It can not be seen.*/
#define EFUSE_PRIVATE (0)
/*After burned ,cpu can not access.*/
#define EFUSE_NACCESS (1)

#define EFUSE_RO (2)    /* burn read_protect bit disable */
#define EFUSE_RW (3)    /* burn read/write_protect bit disable */

#define EFUSE_ACL_SET_BRUN_BIT      (1<<29)
#define EFUSE_ACL_SET_RD_FORBID_BIT (1<<30)
#define EFUSE_BRUN_RD_OFFSET_MASK    (0xFFFFFF)

#endif
