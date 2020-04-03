// See LICENSE for license details.

#ifndef _HBIRD_PWM_H
#define _HBIRD_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Register offsets */

#define PWM_CFG   0x00
#define PWM_COUNT 0x08
#define PWM_S     0x10
#define PWM_CMP0  0x20
#define PWM_CMP1  0x24
#define PWM_CMP2  0x28
#define PWM_CMP3  0x2C

/* Constants */

#define PWM_CFG_SCALE       0x0000000F
#define PWM_CFG_STICKY      0x00000100
#define PWM_CFG_ZEROCMP     0x00000200
#define PWM_CFG_DEGLITCH    0x00000400
#define PWM_CFG_ENALWAYS    0x00001000
#define PWM_CFG_ONESHOT     0x00002000
#define PWM_CFG_CMP0CENTER  0x00010000
#define PWM_CFG_CMP1CENTER  0x00020000
#define PWM_CFG_CMP2CENTER  0x00040000
#define PWM_CFG_CMP3CENTER  0x00080000
#define PWM_CFG_CMP0GANG    0x01000000
#define PWM_CFG_CMP1GANG    0x02000000
#define PWM_CFG_CMP2GANG    0x04000000
#define PWM_CFG_CMP3GANG    0x08000000
#define PWM_CFG_CMP0IP      0x10000000
#define PWM_CFG_CMP1IP      0x20000000
#define PWM_CFG_CMP2IP      0x40000000
#define PWM_CFG_CMP3IP      0x80000000

#ifdef __cplusplus
}
#endif
#endif /* _HBIRD_PWM_H */
