#ifndef __EFUSE_SUN8IW19_H
#define __EFUSE_SUN8IW19_H


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

#define EFUSE_CHIPD             (0x00) /* 0x0-0xf, 128bits */
#define EFUSE_BROM_CONFIG       (0x10) /* 16 bit config, 16 bits try */
#define EFUSE_BROM_TRY          (0X12) /* 16 bit*/
#define EFUSE_THERMAL_SENSOR    (0x14) /* 0x14-0x1b, 64bits */
#define EFUSE_AUDIO_BIAS        (0X1C) /* 8bit */
#define EFUSE_LDOA              (0x1D) /* 8bit */
#define EFUSE_LDOB              (0x1E) /* 8bit */
#define EFUSE_DDR_CFG           (0x1F) /* 8bit */
#define EFUSE_TF_ZONE           (0x20) /* 0x20-0x2f, 128bits */
#define EFUSE_PSENSOR           (0x54) /* 0x54-0x57, 32bits */
#define EFUSE_RESERVED          (0x5C) /* 0x5c-0x7b, 256bits */

/* write protect */
#define EFUSE_WRITE_PROTECT     (0x7C) /* 0x7C-0x7D, 16bits */
/* read  protect */
#define EFUSE_READ_PROTECT      (0x7E) /* 0x7E-0x7F, 16bits */


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

#define EFUSE_HV_SWITCH     (0x07000000 + 0x204)

#endif
