#ifndef __BL616_SDU_H__
#define __BL616_SDU_H__

#include "bl616.h"
#include "bl616_common.h"

#define NUM_FUNC         1        
#define FUNC_WIFI        0  

// SDIO I/O Enable
#define BL_SDIO_IO_ENABLE           SDU_BASE + 0x00000002 
//CCCR (Fn0) Registers

// SDIO Device Sleep
#define BL_SDIO_DEV_SLEEP           SDU_BASE + 0x00000092

// Start Address of CCR
#define BL_SDIO_CCR_BASE            SDU_BASE + 0x00000100
// Address offset of CCR between two functions
#define BL_SDIO_CCR_FUNC_OFFSET     0x00000100


// Address for sdio block size information
#define SDIO_FN1_BLK_SIZE_0        (SDU_BASE + 0x00000028)
#define SDIO_FN1_BLK_SIZE_1        (SDU_BASE + 0x00000029)
#define SDIO_FN1_BLK_SIZE_1_MASK   0x01

#define BL_FUNC_SCRATCH_BASE       SDU_BASE + 0x00000160

typedef struct
{
    uint8_t   HostToCardEvent;   // 0x100/200
    uint8_t   HostIntCause;      // 0x101/201
    uint8_t   HostIntMask;       // 0x102/202
    uint8_t   HostIntStatus;     // 0x103/203
    uint16_t  RdBitMap;          // 0x104/204
    uint16_t  WrBitMap;          // 0x106/206
    uint16_t  RdLen[16];         // 0x108/208
    uint8_t   HostTransferStatus;// 0x128/228
    uint8_t   reserved1[0x130-0x128-1];
    uint8_t   CardToHostEvent;   // 0x130/230
    uint8_t   reserved2[3];
    uint8_t   CardIntMask;       // 0x134/234
    uint8_t   reserved3[3];
    uint8_t   CardIntStatus;     // 0x138/238
    uint8_t   reserved4[3];
    uint8_t   CardIntMode;       // 0x13C/23C
    uint8_t   reserved5[3];
    uint32_t  SqReadBase;        // 0x140/240
    uint32_t  SqWriteBase;       // 0x144/244
    uint8_t   RdIdx;             // 0x148/248
    uint8_t   WrIdx;             // 0x149/249
    uint8_t   DnldQueueWrPtr;    // 0x14A/24A
    uint8_t   UpldQueueWrPtr;    // 0x14B/24B
    uint8_t   DnldQueue[8];      // 0x14C/24C
    uint8_t   UpldQueue[8];      // 0x154/254
    uint8_t   ChipRev;           // 0x15C      //RO
    uint8_t   reserved6;         // 0x15D      //NOT_DEFINE
    uint8_t   IPRev0;            // 0x15E      //RO
    uint8_t   IPRev1;            // 0x15F      //RO
    uint8_t   reserved7[4];      // 0x160/260
    uint16_t  Scratch2;          // 0x164/264
    uint16_t  Scratch1;          // 0x166/266
    uint8_t   Ocr0;              // 0x168/268
    uint8_t   Ocr1;              // 0x169/269
    uint8_t   Ocr2;              // 0x16A/26A
    uint8_t   Config;            // 0x16B/26B
    uint32_t  Config2;           // 0x16C/26C
    uint32_t  Debug;             // 0x170/270
    uint32_t  DmaAddr;           // 0x174/274
    uint8_t   IoPort[3];         // 0x178/278
} __attribute__((packed)) HidSdio_RegMap_t, *pHidSdio_RegMap_t;

// Common I/O Area Registers (CIA) Offset
//
// Bit Def. Host To Card Interrupt Event (Offset 0x100/200)
#define SDIO_HCR_CONFIG_HostPwrUp               (1<<1)

// Bit Def. Host Transfer Status (Offset 0x128/228)
#define SDIO_CCR_HOST_INT_DnLdReStart           (1<<0)
#define SDIO_CCR_HOST_INT_UpLdReStart           (1<<1)
#define SDIO_CCR_HOST_INT_DnLdCRC_err           (1<<2)

// Bit Def. Card To Host Interrupt Event (Offset 0x130/230)
#define SDIO_CCR_CS_DnLdRdy                     (1<<0)
#define SDIO_CCR_CS_UpLdRdy                     (1<<1)
#define SDIO_CCR_CS_ReadCISRdy                  (1<<2)
#define SDIO_CCR_CS_IORdy                       (1<<3)


// Bit Def. Card Interrupt Mask (Offset 0x134/234)
#define SDIO_CCR_CIM_DnLdOvr                    (1<<0)
#define SDIO_CCR_CIM_UpLdOvr                    (1<<1)
#define SDIO_CCR_CIM_Abort                      (1<<2)
#define SDIO_CCR_CIM_PwrDn                      (1<<3)
#define SDIO_CCR_CIM_PwrUp                      (1<<4)

#define SDIO_CCR_CIM_MASK                       0x0007


// Bit Def. Card Interrupt Status (Offset 0x138/238)
#define SDIO_CCR_CIC_DnLdOvr                    (1<<0)
#define SDIO_CCR_CIC_UpLdOvr                    (1<<1)
#define SDIO_CCR_CIC_Abort                      (1<<2)
#define SDIO_CCR_CIC_PwrDn                      (1<<3)
#define SDIO_CCR_CIC_PwrUp                      (1<<4)



#define SDIO_CCR_CIC_MASK                       0x001F

// Bit Def. Card Interrupt RSR (Offset 0x13C/23C)
#define SDIO_CCR_CIO_DnLdOvr                    (1<<0)
#define SDIO_CCR_CIO_UpLdOvr                    (1<<1)
#define SDIO_CCR_CIO_Abort                      (1<<2)
#define SDIO_CCR_CIO_PwrDn                      (1<<3)
#define SDIO_CCR_CIO_PwrUp                      (1<<4)
#define SDIO_CCR_CIO_MASK                       0x001F


//Config2 register mask
#define CONFIG2_MSK                             0x00000C00


//CardIntMode register mask

#define CARD_INT_MODE_MSK                       0x00000003
#define HOST_INT_MSK                            0x00000002

//=============================================================================
//                                PUBLIC MACROS
//=============================================================================

#define BL_REGS8(x)     (*(volatile unsigned char *)(x))
#define BL_REGS16(x)    (*(volatile unsigned short *)(x))
#define BL_REGS32(x)    (*(volatile unsigned long *)(x))

#define BL_READ_REGS8(reg,val)      ((val) = BL_REGS8(reg))
#define BL_READ_REGS16(reg,val)     ((val) = BL_REGS16(reg))
#define BL_READ_REGS32(reg,val)     ((val) = BL_REGS32(reg))
#define BL_READ_BYTE(reg,val)       ((val) = BL_REGS8(reg))
#define BL_READ_HWORD(reg,val)      ((val) = BL_REGS16(reg)) /*half word; */
#define BL_READ_WORD(reg,val)       ((val) = BL_REGS32(reg)) /*32 bits */

#define BL_WRITE_REGS8(reg,val)     (BL_REGS8(reg) = (val))
#define BL_WRITE_REGS16(reg,val)    (BL_REGS16(reg) = (val))
#define BL_WRITE_REGS32(reg,val)    (BL_REGS32(reg) = (val))
#define BL_WRITE_BYTE(reg,val)      (BL_REGS8(reg) = (val))
#define BL_WRITE_HWORD(reg,val)     (BL_REGS16(reg) = (val))  /*half word; */
#define BL_WRITE_WORD(reg,val)      (BL_REGS32(reg) = (val))  /*32 bits */
// Write uint32 to a low 16-bit register and a high 16-bit register
#define WRITE2REGS(lo,hi,u32) \
    BL_WRITE_HWORD(lo, (uint16_t)((u32) & 0xffff)); \
    BL_WRITE_HWORD(hi, (uint16_t)(((u32) >> 16) & 0xffff))

#define BL_REGS8_SETBITS(reg, val)  (BL_REGS8(reg) |= (uint8)(val))
#define BL_REGS16_SETBITS(reg, val) (BL_REGS16(reg) |= (uint16)(val))
#define BL_REGS32_SETBITS(reg, val) (BL_REGS32(reg) |= (val))
#define BL_REGS8_CLRBITS(reg, val)  (BL_REGS8(reg) = (uint8)(BL_REGS8(reg)&~(val)))
#define BL_REGS16_CLRBITS(reg, val) (BL_REGS16(reg) = (uint16)(BL_REGS16(reg)&~(val)))
#define BL_REGS32_CLRBITS(reg, val) (BL_REGS32(reg) = (BL_REGS32(reg)&~(val)))

//=============================================================================
//                                ENUM TYPE DEFINITION
//=============================================================================

/******************************************************************/
/*!
 *  \enum SDIO_CMD_TYPE
 *
 *******************************************************************/
typedef enum
{
  IOCTL_GET_CONFIG = 0,         /*!< Get configuration info */


 /* HID IOCTLs*/
  IOCTL_HID_GET_BLOCK_SIZE,		/*!< Get Block size */

} SDIO_CMD_TYPE;

//=============================================================================
//                                FUNCTION DECLARATION
//=============================================================================
extern void sdio_GEN_CARD2HOST_INT(uint32_t port_id, uint16_t value);
extern uint32_t sdio_ioctl(uint32_t port_id, SDIO_CMD_TYPE cmd, void *arg);

//=============================================================================
//                                Variable DECLARATION
//=============================================================================
extern volatile pHidSdio_RegMap_t SdioFuncReg[];
extern uint8_t flag_mport[];
#endif /* __BL616_SDU_H__ */

