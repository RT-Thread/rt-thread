/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PINCTRL
 *  @{
 */

#ifndef __HAL_PINCTRL_H__
#define __HAL_PINCTRL_H__

#include "hal_def.h"

/***************************** MACRO Definition ******************************/
/** @defgroup PINCTRL_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/** PINCTRL IOFUNC Select definition */
typedef enum {
    IOFUNC_SEL_M0,
    IOFUNC_SEL_M1,
    IOFUNC_SEL_M2,
} eIOFUNC_SEL;

typedef enum {
#if defined(GPIO0)
    GPIO0_A0 = 0,
    GPIO0_A1,
    GPIO0_A2,
    GPIO0_A3,
    GPIO0_A4,
    GPIO0_A5,
    GPIO0_A6,
    GPIO0_A7,
    GPIO0_B0 = 8,
    GPIO0_B1,
    GPIO0_B2,
    GPIO0_B3,
    GPIO0_B4,
    GPIO0_B5,
    GPIO0_B6,
    GPIO0_B7,
    GPIO0_C0 = 16,
    GPIO0_C1,
    GPIO0_C2,
    GPIO0_C3,
    GPIO0_C4,
    GPIO0_C5,
    GPIO0_C6,
    GPIO0_C7,
    GPIO0_D0 = 24,
    GPIO0_D1,
    GPIO0_D2,
    GPIO0_D3,
    GPIO0_D4,
    GPIO0_D5,
    GPIO0_D6,
    GPIO0_D7,
#endif
#if defined(GPIO1)
    GPIO1_A0 = 32,
    GPIO1_A1,
    GPIO1_A2,
    GPIO1_A3,
    GPIO1_A4,
    GPIO1_A5,
    GPIO1_A6,
    GPIO1_A7,
    GPIO1_B0 = 40,
    GPIO1_B1,
    GPIO1_B2,
    GPIO1_B3,
    GPIO1_B4,
    GPIO1_B5,
    GPIO1_B6,
    GPIO1_B7,
    GPIO1_C0 = 48,
    GPIO1_C1,
    GPIO1_C2,
    GPIO1_C3,
    GPIO1_C4,
    GPIO1_C5,
    GPIO1_C6,
    GPIO1_C7,
    GPIO1_D0 = 56,
    GPIO1_D1,
    GPIO1_D2,
    GPIO1_D3,
    GPIO1_D4,
    GPIO1_D5,
    GPIO1_D6,
    GPIO1_D7,
#endif
#if defined(GPIO2)
    GPIO2_A0 = 64,
    GPIO2_A1,
    GPIO2_A2,
    GPIO2_A3,
    GPIO2_A4,
    GPIO2_A5,
    GPIO2_A6,
    GPIO2_A7,
    GPIO2_B0 = 72,
    GPIO2_B1,
    GPIO2_B2,
    GPIO2_B3,
    GPIO2_B4,
    GPIO2_B5,
    GPIO2_B6,
    GPIO2_B7,
    GPIO2_C0 = 80,
    GPIO2_C1,
    GPIO2_C2,
    GPIO2_C3,
    GPIO2_C4,
    GPIO2_C5,
    GPIO2_C6,
    GPIO2_C7,
    GPIO2_D0 = 88,
    GPIO2_D1,
    GPIO2_D2,
    GPIO2_D3,
    GPIO2_D4,
    GPIO2_D5,
    GPIO2_D6,
    GPIO2_D7,
#endif
#if defined(GPIO3)
    GPIO3_A0 = 96,
    GPIO3_A1,
    GPIO3_A2,
    GPIO3_A3,
    GPIO3_A4,
    GPIO3_A5,
    GPIO3_A6,
    GPIO3_A7,
    GPIO3_B0 = 104,
    GPIO3_B1,
    GPIO3_B2,
    GPIO3_B3,
    GPIO3_B4,
    GPIO3_B5,
    GPIO3_B6,
    GPIO3_B7,
    GPIO3_C0 = 112,
    GPIO3_C1,
    GPIO3_C2,
    GPIO3_C3,
    GPIO3_C4,
    GPIO3_C5,
    GPIO3_C6,
    GPIO3_C7,
    GPIO3_D0 = 120,
    GPIO3_D1,
    GPIO3_D2,
    GPIO3_D3,
    GPIO3_D4,
    GPIO3_D5,
    GPIO3_D6,
    GPIO3_D7,
#endif
#if defined(GPIO4)
    GPIO4_A0 = 128,
    GPIO4_A1,
    GPIO4_A2,
    GPIO4_A3,
    GPIO4_A4,
    GPIO4_A5,
    GPIO4_A6,
    GPIO4_A7,
    GPIO4_B0 = 136,
    GPIO4_B1,
    GPIO4_B2,
    GPIO4_B3,
    GPIO4_B4,
    GPIO4_B5,
    GPIO4_B6,
    GPIO4_B7,
    GPIO4_C0 = 144,
    GPIO4_C1,
    GPIO4_C2,
    GPIO4_C3,
    GPIO4_C4,
    GPIO4_C5,
    GPIO4_C6,
    GPIO4_C7,
    GPIO4_D0 = 152,
    GPIO4_D1,
    GPIO4_D2,
    GPIO4_D3,
    GPIO4_D4,
    GPIO4_D5,
    GPIO4_D6,
    GPIO4_D7,
#endif
    GPIO_NUM_MAX
} ePINCTRL_PIN;

/** PINCTRL IOMUX definition */
typedef enum {
    PINCTRL_IOMUX_FUNC0,
    PINCTRL_IOMUX_FUNC1,
    PINCTRL_IOMUX_FUNC2,
    PINCTRL_IOMUX_FUNC3,
    PINCTRL_IOMUX_FUNC4,
    PINCTRL_IOMUX_FUNC5,
    PINCTRL_IOMUX_FUNC6,
    PINCTRL_IOMUX_FUNC7
} ePINCTRL_iomuxFunc;

/** PINCTRL PULL definition */
typedef enum {
    PINCTRL_PULL_OD,
    PINCTRL_PULL_UP,
    PINCTRL_PULL_DOWN,
    PINCTRL_PULL_KEEP
} ePINCTRL_pullMode;

/** PINCTRL Drive Strength definition */
typedef enum {
    PINCTRL_DRIVE_LEVEL0,
    PINCTRL_DRIVE_LEVEL1,
    PINCTRL_DRIVE_LEVEL2,
    PINCTRL_DRIVE_LEVEL3,
    PINCTRL_DRIVE_LEVEL4,
    PINCTRL_DRIVE_LEVEL5,
    PINCTRL_DRIVE_LEVEL6,
    PINCTRL_DRIVE_LEVEL7
} ePINCTRL_driveLevel;

/** PINCTRL Slew Rate definition */
typedef enum {
    PINCTRL_SLEWRATE_SLOW,
    PINCTRL_SLEWRATE_FAST
} ePINCTRL_slewRate;

/** PINCTRL Schmitt enable definition */
typedef enum {
    PINCTRL_SCHMITT_DIS,
    PINCTRL_SCHMITT_EN
} ePINCTRL_schmitt;

#define FLAG_MUX  HAL_BIT(31)
#define FLAG_PUL  HAL_BIT(30)
#define FLAG_DRV  HAL_BIT(29)
#define FLAG_SRT  HAL_BIT(28)
#define FLAG_SMT  HAL_BIT(27)
#define SHIFT_MUX (0)
#define SHIFT_PUL (4)
#define SHIFT_DRV (8)
#define SHIFT_SRT (16)
#define SHIFT_SMT (18)
#define MASK_MUX  (0xFU << SHIFT_MUX)
#define MASK_PUL  (0xFU << SHIFT_PUL)
#define MASK_DRV  (0xFFU << SHIFT_DRV)
#define MASK_SRT  (0x3U << SHIFT_SRT)
#define MASK_SMT  (0x3U << SHIFT_SMT)

/** @brief  PIN Configuration Mode
 *  Elements values convention: gggg g000 0000 ttrr dddd dddd pppp xxxx
 *      - ggggg  : Flag to set Mux/Pull/Drive/Slewrate/Schmitt
 *      - tt  : Schmitt value
 *      - rr  : Slewrate value
 *      - dddddddd  : Drive value
 *      - pppp  : Pull value
 *      - xxxx  : Mux mode value
 */
typedef enum {
    PIN_CONFIG_MUX_FUNC0   = (0x0 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC1   = (0x1 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC2   = (0x2 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC3   = (0x3 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC4   = (0x4 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC5   = (0x5 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC6   = (0x6 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC7   = (0x7 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC8   = (0x8 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC9   = (0x9 << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC10  = (0xa << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC11  = (0xb << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC12  = (0xc << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC13  = (0xd << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC14  = (0xe << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_FUNC15  = (0xf << SHIFT_MUX | FLAG_MUX),
    PIN_CONFIG_MUX_DEFAULT = PIN_CONFIG_MUX_FUNC0,

#if defined(SOC_SWALLOW)
    PIN_CONFIG_PUL_NORMAL  = (0x1 << SHIFT_PUL | FLAG_PUL),
    PIN_CONFIG_PUL_DEFAULT = (0x0 << SHIFT_PUL | FLAG_PUL),
    PIN_CONFIG_PUL_UP      = PIN_CONFIG_PUL_DEFAULT,
    PIN_CONFIG_PUL_DOWN    = PIN_CONFIG_PUL_DEFAULT,
    PIN_CONFIG_PUL_KEEP    = PIN_CONFIG_PUL_DEFAULT,
#else
    PIN_CONFIG_PUL_NORMAL  = (0x0 << SHIFT_PUL | FLAG_PUL),
    PIN_CONFIG_PUL_UP      = (0x1 << SHIFT_PUL | FLAG_PUL),
    PIN_CONFIG_PUL_DOWN    = (0x2 << SHIFT_PUL | FLAG_PUL),
    PIN_CONFIG_PUL_KEEP    = (0x3 << SHIFT_PUL | FLAG_PUL),
    PIN_CONFIG_PUL_DEFAULT = PIN_CONFIG_PUL_NORMAL,
#endif

#if defined(SOC_RK3568)
    PIN_CONFIG_DRV_LEVEL0        = (0x1 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL1        = (0x3 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL2        = (0x7 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL3        = (0xf << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL4        = (0x1f << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL5        = (0x3f << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL_DEFAULT = PIN_CONFIG_DRV_LEVEL2,
#else
    PIN_CONFIG_DRV_LEVEL0        = (0x0 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL1        = (0x1 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL2        = (0x2 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL3        = (0x3 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL4        = (0x4 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL5        = (0x5 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL6        = (0x6 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL7        = (0x7 << SHIFT_DRV | FLAG_DRV),
    PIN_CONFIG_DRV_LEVEL_DEFAULT = PIN_CONFIG_DRV_LEVEL2,
#endif

    PIN_CONFIG_SRT_SLOW    = (0x0 << SHIFT_SRT | FLAG_SRT),
    PIN_CONFIG_SRT_FAST    = (0x1 << SHIFT_SRT | FLAG_SRT),
    PIN_CONFIG_SRT_DEFAULT = PIN_CONFIG_SRT_SLOW,

    PIN_CONFIG_SMT_DISABLE = (0x0 << SHIFT_SMT | FLAG_SMT),
    PIN_CONFIG_SMT_ENABLE  = (0x1 << SHIFT_SMT | FLAG_SMT),
    PIN_CONFIG_SMT_DEFAULT = PIN_CONFIG_SMT_DISABLE,

    PIN_CONFIG_MAX = 0xFFFFFFFFU,
} ePINCTRL_configParam;

typedef enum {
    GRF_MUX_INFO = 0,
    GRF_PUL_INFO,
    GRF_DRV_INFO,
    GRF_SRT_INFO,
    GRF_SMT_INFO,
    GRF_INFO_NUM
} ePIN_GRF_INFO_ID;

#define PIN_BANK_CFG_FLAGS(chn, cnt, reg,                                                       \
                           offset0, bpp0, ppr0,                                                 \
                           offset1, bpp1, ppr1,                                                 \
                           offset2, bpp2, ppr2,                                                 \
                           offset3, bpp3, ppr3,                                                 \
                           offset4, bpp4, ppr4)                                                 \
    {                                                                                           \
        .channel = chn,                                                                         \
        .pinCount = cnt,                                                                        \
        .grfBase = reg,                                                                         \
        .GRFInfo[GRF_MUX_INFO] = { .offset = offset0, .bitsPerPin = bpp0, .pinsPerReg = ppr0 }, \
        .GRFInfo[GRF_PUL_INFO] = { .offset = offset1, .bitsPerPin = bpp1, .pinsPerReg = ppr1 }, \
        .GRFInfo[GRF_DRV_INFO] = { .offset = offset2, .bitsPerPin = bpp2, .pinsPerReg = ppr2 }, \
        .GRFInfo[GRF_SRT_INFO] = { .offset = offset3, .bitsPerPin = bpp3, .pinsPerReg = ppr3 }, \
        .GRFInfo[GRF_SMT_INFO] = { .offset = offset4, .bitsPerPin = bpp4, .pinsPerReg = ppr4 }, \
    }

/** @defgroup ePINCTRL_GPIO_PINS Pins Definition
 *  @{
 */
typedef enum {
    GPIO_PIN_A0 = 0x00000001U,  /*!< Pin 0 selected    */
    GPIO_PIN_A1 = 0x00000002U,  /*!< Pin 1 selected    */
    GPIO_PIN_A2 = 0x00000004U,  /*!< Pin 2 selected    */
    GPIO_PIN_A3 = 0x00000008U,  /*!< Pin 3 selected    */
    GPIO_PIN_A4 = 0x00000010U,  /*!< Pin 4 selected    */
    GPIO_PIN_A5 = 0x00000020U,  /*!< Pin 5 selected    */
    GPIO_PIN_A6 = 0x00000040U,  /*!< Pin 6 selected    */
    GPIO_PIN_A7 = 0x00000080U,  /*!< Pin 7 selected    */
    GPIO_PIN_B0 = 0x00000100U,  /*!< Pin 8 selected    */
    GPIO_PIN_B1 = 0x00000200U,  /*!< Pin 9 selected    */
    GPIO_PIN_B2 = 0x00000400U,  /*!< Pin 10 selected   */
    GPIO_PIN_B3 = 0x00000800U,  /*!< Pin 11 selected   */
    GPIO_PIN_B4 = 0x00001000U,  /*!< Pin 12 selected   */
    GPIO_PIN_B5 = 0x00002000U,  /*!< Pin 13 selected   */
    GPIO_PIN_B6 = 0x00004000U,  /*!< Pin 14 selected   */
    GPIO_PIN_B7 = 0x00008000U,  /*!< Pin 15 selected   */
    GPIO_PIN_C0 = 0x00010000U,  /*!< Pin 16 selected   */
    GPIO_PIN_C1 = 0x00020000U,  /*!< Pin 17 selected   */
    GPIO_PIN_C2 = 0x00040000U,  /*!< Pin 18 selected   */
    GPIO_PIN_C3 = 0x00080000U,  /*!< Pin 19 selected   */
    GPIO_PIN_C4 = 0x00100000U,  /*!< Pin 20 selected   */
    GPIO_PIN_C5 = 0x00200000U,  /*!< Pin 21 selected   */
    GPIO_PIN_C6 = 0x00400000U,  /*!< Pin 22 selected   */
    GPIO_PIN_C7 = 0x00800000U,  /*!< Pin 23 selected   */
    GPIO_PIN_D0 = 0x01000000U,  /*!< Pin 24 selected   */
    GPIO_PIN_D1 = 0x02000000U,  /*!< Pin 25 selected   */
    GPIO_PIN_D2 = 0x04000000U,  /*!< Pin 26 selected   */
    GPIO_PIN_D3 = 0x08000000U,  /*!< Pin 27 selected   */
    GPIO_PIN_D4 = 0x10000000U,  /*!< Pin 28 selected   */
    GPIO_PIN_D5 = 0x20000000U,  /*!< Pin 29 selected   */
    GPIO_PIN_D6 = 0x40000000U,  /*!< Pin 30 selected   */
    GPIO_PIN_D7 = 0x80000000U,  /*!< Pin 31 selected   */
} ePINCTRL_GPIO_PINS;

#define GPIO_PIN_ALL (0xFFFFFFFFU)  /*!< All pins selected */

/** @} */

#define ROUTE_VAL(v, s, m) (((v) << (s)) | (m) << ((s) + 16))

/***************************** Structure Definition **************************/

struct PINCTRL_GRF_INFO {
    uint16_t offset;
    uint8_t bitsPerPin;
    uint8_t pinsPerReg;
};

struct PINCTRL_MUX_RECAL_DATA {
    uint32_t reg;
    uint8_t bank;
    uint8_t pin;
    uint8_t bit;
    uint8_t mask;
};

struct PINCTRL_MUX_ROUTE_DATA {
    uint32_t routeReg;
    uint32_t routeVal;
    uint32_t pin;
    uint8_t bank;
    uint8_t func;
};

struct PINCTRL_BANK_INFO {
    struct PINCTRL_GRF_INFO GRFInfo[GRF_INFO_NUM];
    uint32_t grfBase;
    uint8_t pinCount;
    uint8_t channel;
};

struct HAL_PINCTRL_DEV {
    const struct PINCTRL_BANK_INFO *banks;
    const struct PINCTRL_MUX_RECAL_DATA *muxRecalData;
    const struct PINCTRL_MUX_ROUTE_DATA *muxRouteData;
    uint8_t banksNum;
    uint8_t muxRecalDataNum;
    uint8_t muxRouteDataNum;
};

/** @brief  Rockchip pinctrl device struct define
 * Define a struct for pinctrl, including banks info, bank number,
 * and grf info about iomux offset, iomux bit info, drive/pull/
 * slewrate/schmitt offset and bit info.
 */
extern const struct HAL_PINCTRL_DEV g_pinDev;

/** @} */

/***************************** Function Declare ******************************/
/** @defgroup PINCTRL_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_PINCTRL_Suspend(void);
HAL_Status HAL_PINCTRL_Resume(void);

HAL_Status HAL_PINCTRL_Init(void);
HAL_Status HAL_PINCTRL_DeInit(void);

HAL_Status HAL_PINCTRL_SetParam(eGPIO_bankId bank, uint32_t mPins, ePINCTRL_configParam param);
HAL_Status HAL_PINCTRL_SetIOMUX(eGPIO_bankId bank, uint32_t mPins, ePINCTRL_configParam param);

HAL_Status HAL_PINCTRL_IOFuncSelForCIF(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForEMMC(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForFLASH(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForFSPI(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForLCDC(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForMIPICSI(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForRGMII(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForGMAC0(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForGMAC1(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSDIO(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSDMMC0(eIOFUNC_SEL mode);

HAL_Status HAL_PINCTRL_IOFuncSelForCAN0(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForCAN1(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForCAN2(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForCAN3(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForCAN4(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForCAN5(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2C0(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2C1(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2C2(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2C3(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2C4(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2C5(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2S0(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2S1(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForI2S2(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM0(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM1(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM2(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM3(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM4(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM5(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM6(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM7(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM8(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM9(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM10(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForPWM11(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSPI0(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSPI1(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSPI2(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSPI3(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSPI4(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForSPI5(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART0(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART1(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART2(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART3(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART4(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART5(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART6(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART7(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART8(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART9(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART10(eIOFUNC_SEL mode);
HAL_Status HAL_PINCTRL_IOFuncSelForUART11(eIOFUNC_SEL mode);

/** @} */

#endif /* __HAL_PINCTRL_H__ */

/** @} */

/** @} */
