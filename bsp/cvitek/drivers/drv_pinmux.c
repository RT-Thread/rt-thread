/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/05/24     unicornx     first version
 */

#include <string.h>

#include <rtthread.h>
#include "mmio.h"
#include "pinctrl.h"
#include "drv_pinmux.h"

#define DBG_TAG              "drv.pinmux"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(ar)     (sizeof(ar)/sizeof(ar[0]))
#endif

/**
 * @brief Function Selection for one Pin
 *
 * type: type of function
 * select: value of selection
 */
struct fselect {
    fs_type type;
    uint8_t select;
};

/**
 * @brief Function Mux for one Pin
 *
 * name: Pin Name
 * addr: offset of pinmux registers against PINMUX_BASE
 * offset: offset of function selection field in the pinmux register
 * mask: mask of function selection field in the pinmux register
 * selected: 1 if this pin has been selected, used for binding check.
 */
struct fmux {
    char *name;
    uint16_t addr;
    uint8_t offset;
    uint8_t mask;
    uint8_t selected;
};

#define FS_NONE {fs_none, 0}

#define FS_PINMUX(PIN_NAME) {                   \
        .name = #PIN_NAME,                      \
        .addr = FMUX_GPIO_FUNCSEL_##PIN_NAME,   \
        .offset = PINMUX_OFFSET(PIN_NAME),      \
        .mask = PINMUX_MASK(PIN_NAME),          \
        .selected = 0,                          \
    }


/**
 * @brief Define TWO tables for every SOC.
 *
 * Table-1: pinmux_array: every line maps to one pin register, store basic info.
 * Table-2: pin_selects_array: function selection array, extend Table-1, store
 *          function selection info.
 * NOTE: Index of pinmux_array matches the same as that in pin_selects_array.
 */
#if defined(SOC_TYPE_CV180X)

struct fmux pinmux_array[] = {
    FS_PINMUX(SD0_CLK),
    FS_PINMUX(SD0_CMD),
    FS_PINMUX(SD0_D0),
    FS_PINMUX(SD0_D1),
    FS_PINMUX(SD0_D2),
    FS_PINMUX(SD0_D3),
    FS_PINMUX(SD0_CD),
    FS_PINMUX(SD0_PWR_EN),
    FS_PINMUX(SPK_EN),
    FS_PINMUX(UART0_TX),
    FS_PINMUX(UART0_RX),
    FS_PINMUX(SPINOR_HOLD_X),
    FS_PINMUX(SPINOR_SCK),
    FS_PINMUX(SPINOR_MOSI),
    FS_PINMUX(SPINOR_WP_X),
    FS_PINMUX(SPINOR_MISO),
    FS_PINMUX(SPINOR_CS_X),
    FS_PINMUX(JTAG_CPU_TMS),
    FS_PINMUX(JTAG_CPU_TCK),
    FS_PINMUX(IIC0_SCL),
    FS_PINMUX(IIC0_SDA),
    FS_PINMUX(AUX0),
    FS_PINMUX(GPIO_ZQ),
    FS_PINMUX(PWR_VBAT_DET),
    FS_PINMUX(PWR_RSTN),
    FS_PINMUX(PWR_SEQ1),
    FS_PINMUX(PWR_SEQ2),
    FS_PINMUX(PWR_WAKEUP0),
    FS_PINMUX(PWR_BUTTON1),
    FS_PINMUX(XTAL_XIN),
    FS_PINMUX(PWR_GPIO0),
    FS_PINMUX(PWR_GPIO1),
    FS_PINMUX(PWR_GPIO2),
    FS_PINMUX(SD1_GPIO1),
    FS_PINMUX(SD1_GPIO0),
    FS_PINMUX(SD1_D3),
    FS_PINMUX(SD1_D2),
    FS_PINMUX(SD1_D1),
    FS_PINMUX(SD1_D0),
    FS_PINMUX(SD1_CMD),
    FS_PINMUX(SD1_CLK),
    FS_PINMUX(PWM0_BUCK),
    FS_PINMUX(ADC1),
    FS_PINMUX(PKG_TYPE0),
    FS_PINMUX(USB_VBUS_DET),
    FS_PINMUX(PKG_TYPE1),
    FS_PINMUX(PKG_TYPE2),
    FS_PINMUX(MUX_SPI1_MISO),
    FS_PINMUX(MUX_SPI1_MOSI),
    FS_PINMUX(MUX_SPI1_CS),
    FS_PINMUX(MUX_SPI1_SCK),
    FS_PINMUX(PAD_ETH_TXP),
    FS_PINMUX(PAD_ETH_TXM),
    FS_PINMUX(PAD_ETH_RXP),
    FS_PINMUX(PAD_ETH_RXM),
    FS_PINMUX(GPIO_RTX),
    FS_PINMUX(PAD_MIPIRX4N),
    FS_PINMUX(PAD_MIPIRX4P),
    FS_PINMUX(PAD_MIPIRX3N),
    FS_PINMUX(PAD_MIPIRX3P),
    FS_PINMUX(PAD_MIPIRX2N),
    FS_PINMUX(PAD_MIPIRX2P),
    FS_PINMUX(PAD_MIPIRX1N),
    FS_PINMUX(PAD_MIPIRX1P),
    FS_PINMUX(PAD_MIPIRX0N),
    FS_PINMUX(PAD_MIPIRX0P),
    FS_PINMUX(PAD_MIPI_TXM2),
    FS_PINMUX(PAD_MIPI_TXP2),
    FS_PINMUX(PAD_MIPI_TXM1),
    FS_PINMUX(PAD_MIPI_TXP1),
    FS_PINMUX(PAD_MIPI_TXM0),
    FS_PINMUX(PAD_MIPI_TXP0),
    FS_PINMUX(PAD_AUD_AINL_MIC),
    FS_PINMUX(PAD_AUD_AINR_MIC),
    FS_PINMUX(PAD_AUD_AOUTL),
    FS_PINMUX(PAD_AUD_AOUTR),
};

const struct fselect pin_selects_array[][8] = {
/* SD0_CLK          */ {{SDIO0_CLK, 0},      {IIC1_SDA, 1},      {SPI0_SCK, 2},     {XGPIOA_7, 3},    FS_NONE,        {PWM_15, 5},      {EPHY_LNK_LED, 6},      {DBG_0, 7}},
/* SD0_CMD          */ {{SDIO0_CMD, 0},      {IIC1_SCL, 1},      {SPI0_SDO, 2},     {XGPIOA_8, 3},    FS_NONE,        {PWM_14, 5},      {EPHY_SPD_LED, 6},      {DBG_1, 7}},
/* SD0_D0           */ {{SDIO0_D_0, 0},      {CAM_MCLK1, 1},     {SPI0_SDI, 2},     {XGPIOA_9, 3},    {UART3_TX, 4},  {PWM_13, 5},      {WG0_D0, 6},            {DBG_2, 7}},
/* SD0_D1           */ {{SDIO0_D_1, 0},      {IIC1_SDA, 1},      {AUX0, 2},         {XGPIOA_10, 3},   {UART1_TX, 4},  {PWM_12, 5},      {WG0_D1, 6},            {DBG_3, 7}},
/* SD0_D2           */ {{SDIO0_D_2, 0},      {IIC1_SCL, 1},      {AUX1, 2},         {XGPIOA_11, 3},   {UART1_RX, 4},  {PWM_11, 5},      {WG1_D0, 6},            {DBG_4, 7}},
/* SD0_D3           */ {{SDIO0_D_3, 0},      {CAM_MCLK0, 1},     {SPI0_CS_X, 2},    {XGPIOA_12, 3},   {UART3_RX, 4},  {PWM_10, 5},      {WG1_D1, 6},            {DBG_5, 7}},
/* SD0_CD           */ {{SDIO0_CD, 0},       FS_NONE,            FS_NONE,           {XGPIOA_13, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* SD0_PWR_EN       */ {{SDIO0_PWR_EN, 0},   FS_NONE,            FS_NONE,           {XGPIOA_14, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* SPK_EN           */ {FS_NONE,             FS_NONE,            FS_NONE,           {XGPIOA_15, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* UART0_TX         */ {{UART0_TX, 0},       {CAM_MCLK1, 1},     {PWM_4, 2},        {XGPIOA_16, 3},   {UART1_TX, 4},  {AUX1, 5},        {JTAG_TMS, 6},          {DBG_6, 7}},
/* UART0_RX         */ {{UART0_RX, 0},       {CAM_MCLK0, 1},     {PWM_5, 2},        {XGPIOA_17, 3},   {UART1_RX, 4},  {AUX0, 5},        {JTAG_TCK, 6},          {DBG_7, 7}},
/* SPINOR_HOLD_X    */ {FS_NONE,             {SPINOR_HOLD_X, 1}, {SPINAND_HOLD, 2}, {XGPIOA_26, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* SPINOR_SCK       */ {FS_NONE,             {SPINOR_SCK, 1},    {SPINAND_CLK, 2},  {XGPIOA_22, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* SPINOR_MOSI      */ {FS_NONE,             {SPINOR_MOSI, 1},   {SPINAND_MOSI, 2}, {XGPIOA_25, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* SPINOR_WP_X      */ {FS_NONE,             {SPINOR_WP_X, 1},   {SPINAND_WP, 2},   {XGPIOA_27, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* SPINOR_MISO      */ {FS_NONE,             {SPINOR_MISO, 1},   {SPINAND_MISO, 2}, {XGPIOA_23, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* SPINOR_CS_X      */ {FS_NONE,             {SPINOR_CS_X, 1},   {SPINAND_CS, 2},   {XGPIOA_24, 3},   FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* JTAG_CPU_TMS     */ {{JTAG_TMS, 0},       {CAM_MCLK0, 1},     {PWM_7, 2},        {XGPIOA_19, 3},   {UART1_RTS, 4}, {AUX0, 5},        {UART1_TX, 6},          FS_NONE},
/* JTAG_CPU_TCK     */ {{JTAG_TCK, 0},       {CAM_MCLK1, 1},     {PWM_6, 2},        {XGPIOA_18, 3},   {UART1_CTS, 4}, {AUX1, 5},        {UART1_RX, 6},          FS_NONE},
/* IIC0_SCL         */ {{JTAG_TDI, 0},       {UART1_TX, 1},      {UART2_TX, 2},     {XGPIOA_28, 3},   {IIC0_SCL, 4},  {WG0_D0, 5},      FS_NONE,                {DBG_10, 7}},
/* IIC0_SDA         */ {{JTAG_TDO, 0},       {UART1_RX, 1},      {UART2_RX, 2},     {XGPIOA_29, 3},   {IIC0_SDA, 4},  {WG0_D1, 5},      {WG1_D0, 6},            {DBG_11, 7}},
/* AUX0             */ {{AUX0, 0},           FS_NONE,            FS_NONE,           {XGPIOA_30, 3},   {IIS1_MCLK, 4}, FS_NONE,          {WG1_D1, 6},            {DBG_12, 7}},
/* GPIO_ZQ          */ {FS_NONE,             FS_NONE,            FS_NONE,           {PWR_GPIO_24, 3}, {PWM_2, 4},     FS_NONE,          FS_NONE,                FS_NONE},
/* PWR_VBAT_DET     */ {{PWR_VBAT_DET, 0},   FS_NONE,            FS_NONE,           FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* PWR_RSTN         */ {{PWR_RSTN, 0},       FS_NONE,            FS_NONE,           FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* PWR_SEQ1         */ {{PWR_SEQ1, 0},       FS_NONE,            {PWR_GPIO_3, 3},   FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* PWR_SEQ2         */ {{PWR_SEQ2, 0},       FS_NONE,            {PWR_GPIO_4, 3},   FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* PWR_WAKEUP0      */ {{PWR_WAKEUP0, 0},    {PWR_IR0, 1},       {PWR_UART0_TX, 2}, {PWR_GPIO_6, 3},  {UART1_TX, 4},  {IIC4_SCL, 5},    {EPHY_LNK_LED, 6},      {WG2_D0, 7}},
/* PWR_BUTTON1      */ {{PWR_BUTTON1, 0},    FS_NONE,            FS_NONE,           {PWR_GPIO_8, 3},  {UART1_RX, 4},  {IIC4_SDA, 5},    {EPHY_SPD_LED, 6},      {WG2_D1, 7}},
/* XTAL_XIN         */ {{PWR_XTAL_CLKIN, 0}, FS_NONE,            FS_NONE,           FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* PWR_GPIO0        */ {{PWR_GPIO_0, 0},     {UART2_TX, 1},      {PWR_UART0_RX, 2}, FS_NONE,          {PWM_8, 4},     FS_NONE,          FS_NONE,                FS_NONE},
/* PWR_GPIO1        */ {{PWR_GPIO_1, 0},     {UART2_RX, 1},      FS_NONE,           {EPHY_LNK_LED, 3},{PWM_9, 4},     {PWR_IIC_SCL, 5}, {IIC2_SCL, 6},          {IIC0_SDA, 7}},
/* PWR_GPIO2        */ {{PWR_GPIO_2, 0},     FS_NONE,            {PWR_SECTICK, 2},  {EPHY_SPD_LED, 3},{PWM_10, 4},    {PWR_IIC_SDA, 5}, {IIC2_SDA, 6},          {IIC0_SCL, 7}},
/* SD1_GPIO1        */ {FS_NONE,             {UART4_TX, 1},      FS_NONE,           {PWR_GPIO_26, 3}, FS_NONE,        FS_NONE,          FS_NONE,                {PWM_10, 7}},
/* SD1_GPIO0        */ {FS_NONE,             {UART4_RX, 1},      FS_NONE,           {PWR_GPIO_25, 3}, FS_NONE,        FS_NONE,          FS_NONE,                {PWM_11, 7}},
/* SD1_D3           */ {{PWR_SD1_D3, 0},     {SPI2_CS_X, 1},     {IIC1_SCL, 2},     {PWR_GPIO_18, 3}, {CAM_MCLK0, 4}, {UART3_CTS, 5},   {PWR_SPINOR1_CS_X, 6},  {PWM_4, 7}},
/* SD1_D2           */ {{PWR_SD1_D2, 0},     {IIC1_SCL, 1},      {UART2_TX, 2},     {PWR_GPIO_19, 3}, {CAM_MCLK0, 4}, {UART3_TX, 5},    {PWR_SPINOR1_HOLD_X, 6},{PWM_5, 7}},
/* SD1_D1           */ {{PWR_SD1_D1, 0},     {IIC1_SDA, 1},      {UART2_RX, 2},     {PWR_GPIO_20, 3}, {CAM_MCLK1, 4}, {UART3_RX, 5},    {PWR_SPINOR1_WP_X, 6},  {PWM_6, 7}},
/* SD1_D0           */ {{PWR_SD1_D0, 0},     {SPI2_SDI, 1},      {IIC1_SDA, 2},     {PWR_GPIO_21, 3}, {CAM_MCLK1, 4}, {UART3_RTS, 5},   {PWR_SPINOR1_MISO, 6},  {PWM_7, 7}},
/* SD1_CMD          */ {{PWR_SD1_CMD, 0},    {SPI2_SDO, 1},      {IIC3_SCL, 2},     {PWR_GPIO_22, 3}, {CAM_VS0, 4},   {EPHY_LNK_LED, 5},{PWR_SPINOR1_MOSI, 6},  {PWM_8, 7}},
/* SD1_CLK          */ {{PWR_SD1_CLK, 0},    {SPI2_SCK, 1},      {IIC3_SDA, 2},     {PWR_GPIO_23, 3}, {CAM_HS0, 4},   {EPHY_SPD_LED, 5},{PWR_SPINOR1_SCK, 6},   {PWM_9, 7}},
/* PWM0_BUCK        */ {{PWM_0, 0},          FS_NONE,            FS_NONE,           {XGPIOB_0, 3},    FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* ADC1             */ {FS_NONE,             FS_NONE,            FS_NONE,           {XGPIOB_3, 3},    {KEY_COL2, 4},  FS_NONE,          {PWM_3, 6},             FS_NONE},
/* PKG_TYPE0        */ {{PKG_TYPE0, 0},      FS_NONE,            FS_NONE,           FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* USB_VBUS_DET     */ {{USB_VBUS_DET, 0},   FS_NONE,            FS_NONE,           {XGPIOB_6, 3},    {CAM_MCLK0, 4}, {CAM_MCLK1, 5},   {PWM_4, 6},             FS_NONE},
/* PKG_TYPE1        */ {{PKG_TYPE1, 0},      FS_NONE,            FS_NONE,           FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* PKG_TYPE2        */ {{PKG_TYPE2, 0},      FS_NONE,            FS_NONE,           FS_NONE,          FS_NONE,        FS_NONE,          FS_NONE,                FS_NONE},
/* MUX_SPI1_MISO    */ {FS_NONE,             {UART3_RTS, 1},     {IIC1_SDA, 2},     {XGPIOB_8, 3},    {PWM_9, 4},     {KEY_COL1, 5},    {SPI1_SDI, 6},          {DBG_14, 7}},
/* MUX_SPI1_MOSI    */ {FS_NONE,             {UART3_RX, 1},      {IIC1_SCL, 2},     {XGPIOB_7, 3},    {PWM_8, 4},     {KEY_COL0, 5},    {SPI1_SDO, 6},          {DBG_13, 7}},
/* MUX_SPI1_CS      */ {FS_NONE,             {UART3_CTS, 1},     {CAM_MCLK0, 2},    {XGPIOB_10, 3},   {PWM_11, 4},    {KEY_ROW3, 5},    {SPI1_CS_X, 6},         {DBG_16, 7}},
/* MUX_SPI1_SCK     */ {FS_NONE,             {UART3_TX, 1},      {CAM_MCLK1, 2},    {XGPIOB_9, 3},    {PWM_10, 4},    {KEY_ROW2, 5},    {SPI1_SCK, 6},          {DBG_15, 7}},
/* PAD_ETH_TXP      */ {FS_NONE,             {UART3_RX, 1},      {IIC1_SCL, 2},     {XGPIOB_25, 3},   {PWM_13, 4},    {CAM_MCLK0, 5},   {SPI1_SDO, 6},          {IIS2_LRCK, 7}},
/* PAD_ETH_TXM      */ {FS_NONE,             {UART3_RTS, 1},     {IIC1_SDA, 2},     {XGPIOB_24, 3},   {PWM_12, 4},    {CAM_MCLK1, 5},   {SPI1_SDI, 6},          {IIS2_BCLK, 7}},
/* PAD_ETH_RXP      */ {FS_NONE,             {UART3_TX, 1},      {CAM_MCLK1, 2},    {XGPIOB_27, 3},   {PWM_15, 4},    {CAM_HS0, 5},     {SPI1_SCK, 6},          {IIS2_DO, 7}},
/* PAD_ETH_RXM      */ {FS_NONE,             {UART3_CTS, 1},     {CAM_MCLK0, 2},    {XGPIOB_26, 3},   {PWM_14, 4},    {CAM_VS0, 5},     {SPI1_CS_X, 6},         {IIS2_DI, 7}},
/* GPIO_RTX         */ {FS_NONE,             {VI0_D_15, 1},      FS_NONE,           {XGPIOB_23, 3},   {PWM_1, 4},     {CAM_MCLK0, 5},   FS_NONE,                {IIS2_MCLK, 7}},
/* PAD_MIPIRX4N     */ {FS_NONE,             {VI0_CLK, 1},       {IIC0_SCL, 2},     {XGPIOC_2, 3},    {IIC1_SDA, 4},  {CAM_MCLK0, 5},   {KEY_ROW0, 6},          {MUX_SPI1_SCK, 7}},
/* PAD_MIPIRX4P     */ {FS_NONE,             {VI0_D_0, 1},       {IIC0_SDA, 2},     {XGPIOC_3, 3},    {IIC1_SCL, 4},  {CAM_MCLK1, 5},   {KEY_ROW1, 6},          {MUX_SPI1_CS, 7}},
/* PAD_MIPIRX3N     */ {FS_NONE,             {VI0_D_1, 1},       FS_NONE,           {XGPIOC_4, 3},    {CAM_MCLK0, 4}, FS_NONE,          FS_NONE,                {MUX_SPI1_MISO, 7}},
/* PAD_MIPIRX3P     */ {FS_NONE,             {VI0_D_2, 1},       FS_NONE,           {XGPIOC_5, 3},    FS_NONE,        FS_NONE,          FS_NONE,                {MUX_SPI1_MOSI, 7}},
/* PAD_MIPIRX2N     */ {FS_NONE,             {VI0_D_3, 1},       FS_NONE,           {XGPIOC_6, 3},    FS_NONE,        {IIC4_SCL, 5},    FS_NONE,                {DBG_6, 7}},
/* PAD_MIPIRX2P     */ {FS_NONE,             {VI0_D_4, 1},       FS_NONE,           {XGPIOC_7, 3},    FS_NONE,        {IIC4_SDA, 5},    FS_NONE,                {DBG_7, 7}},
/* PAD_MIPIRX1N     */ {FS_NONE,             {VI0_D_5, 1},       FS_NONE,           {XGPIOC_8, 3},    FS_NONE,        FS_NONE,          {KEY_ROW3, 6},          {DBG_8, 7}},
/* PAD_MIPIRX1P     */ {FS_NONE,             {VI0_D_6, 1},       FS_NONE,           {XGPIOC_9, 3},    {IIC1_SDA, 4},  FS_NONE,          {KEY_ROW2, 6},          {DBG_9, 7}},
/* PAD_MIPIRX0N     */ {FS_NONE,             {VI0_D_7, 1},       FS_NONE,           {XGPIOC_10, 3},   {IIC1_SCL, 4},  {CAM_MCLK1, 5},   FS_NONE,                {DBG_10, 7}},
/* PAD_MIPIRX0P     */ {FS_NONE,             {VI0_D_8, 1},       FS_NONE,           {XGPIOC_11, 3},   {CAM_MCLK0, 4}, FS_NONE,          FS_NONE,                {DBG_11, 7}},
/* PAD_MIPI_TXM2    */ {FS_NONE,             {VI0_D_13, 1},      {IIC0_SDA, 2},     {XGPIOC_16, 3},   {IIC1_SDA, 4},  {PWM_8, 5},       {SPI0_SCK, 6},          FS_NONE},
/* PAD_MIPI_TXP2    */ {FS_NONE,             {VI0_D_14, 1},      {IIC0_SCL, 2},     {XGPIOC_17, 3},   {IIC1_SCL, 4},  {PWM_9, 5},       {SPI0_CS_X, 6},         {IIS1_MCLK, 7}},
/* PAD_MIPI_TXM1    */ {{SPI3_SDO, 0},       {VI0_D_11, 1},      {IIS1_LRCK, 2},    {XGPIOC_14, 3},   {IIC2_SDA, 4},  {PWM_10, 5},      {SPI0_SDO, 6},          {DBG_14, 7}},
/* PAD_MIPI_TXP1    */ {{SPI3_SDI, 0},       {VI0_D_12, 1},      {IIS1_DO, 2},      {XGPIOC_15, 3},   {IIC2_SCL, 4},  {PWM_11, 5},      {SPI0_SDI, 6},          {DBG_15, 7}},
/* PAD_MIPI_TXM0    */ {{SPI3_SCK, 0},       {VI0_D_9, 1},       {IIS1_DI, 2},      {XGPIOC_12, 3},   {CAM_MCLK1, 4}, {PWM_14, 5},      {CAM_VS0, 6},           {DBG_12, 7}},
/* PAD_MIPI_TXP0    */ {{SPI3_CS_X, 0},      {VI0_D_10, 1},      {IIS1_BCLK, 2},    {XGPIOC_13, 3},   {CAM_MCLK0, 4}, {PWM_15, 5},      {CAM_HS0, 6},           {DBG_13, 7}},
/* PAD_AUD_AINL_MIC */ {FS_NONE,             FS_NONE,            FS_NONE,           {XGPIOC_23, 3},   {IIS1_BCLK, 4}, {IIS2_BCLK, 5},   FS_NONE,                FS_NONE},
/* PAD_AUD_AINR_MIC */ {FS_NONE,             FS_NONE,            FS_NONE,           {XGPIOC_22, 3},   {IIS1_DO, 4},   {IIS2_DI, 5},     {IIS1_DI, 6},           FS_NONE},
/* PAD_AUD_AOUTL    */ {FS_NONE,             FS_NONE,            FS_NONE,           {XGPIOC_25, 3},   {IIS1_LRCK, 4}, {IIS2_LRCK, 5},   FS_NONE,                FS_NONE},
/* PAD_AUD_AOUTR    */ {FS_NONE,             FS_NONE,            FS_NONE,           {XGPIOC_24, 3},   {IIS1_DI, 4},   {IIS2_DO, 5},     {IIS1_DO, 6},           FS_NONE},
};

#elif defined(SOC_TYPE_SG2002) || defined(SOC_TYPE_SG2000)

struct fmux pinmux_array[] = {
    FS_PINMUX(CAM_MCLK0),
    FS_PINMUX(CAM_PD0),
    FS_PINMUX(CAM_RST0),
    FS_PINMUX(CAM_MCLK1),
    FS_PINMUX(CAM_PD1),
    FS_PINMUX(IIC3_SCL),
    FS_PINMUX(IIC3_SDA),
    FS_PINMUX(SD0_CLK),
    FS_PINMUX(SD0_CMD),
    FS_PINMUX(SD0_D0),
    FS_PINMUX(SD0_D1),
    FS_PINMUX(SD0_D2),
    FS_PINMUX(SD0_D3),
    FS_PINMUX(SD0_CD),
    FS_PINMUX(SD0_PWR_EN),
    FS_PINMUX(SPK_EN),
    FS_PINMUX(UART0_TX),
    FS_PINMUX(UART0_RX),
    FS_PINMUX(EMMC_RSTN),
    FS_PINMUX(EMMC_DAT2),
    FS_PINMUX(EMMC_CLK),
    FS_PINMUX(EMMC_DAT0),
    FS_PINMUX(EMMC_DAT3),
    FS_PINMUX(EMMC_CMD),
    FS_PINMUX(EMMC_DAT1),
    FS_PINMUX(JTAG_CPU_TMS),
    FS_PINMUX(JTAG_CPU_TCK),
    FS_PINMUX(JTAG_CPU_TRST),
    FS_PINMUX(IIC0_SCL),
    FS_PINMUX(IIC0_SDA),
    FS_PINMUX(AUX0),
    FS_PINMUX(PWR_VBAT_DET),
    FS_PINMUX(PWR_RSTN),
    FS_PINMUX(PWR_SEQ1),
    FS_PINMUX(PWR_SEQ2),
    FS_PINMUX(PWR_SEQ3),
    FS_PINMUX(PWR_WAKEUP0),
    FS_PINMUX(PWR_WAKEUP1),
    FS_PINMUX(PWR_BUTTON1),
    FS_PINMUX(PWR_ON),
    FS_PINMUX(XTAL_XIN),
    FS_PINMUX(PWR_GPIO0),
    FS_PINMUX(PWR_GPIO1),
    FS_PINMUX(PWR_GPIO2),
    FS_PINMUX(CLK32K),
    FS_PINMUX(CLK25M),
    FS_PINMUX(IIC2_SCL),
    FS_PINMUX(IIC2_SDA),
    FS_PINMUX(UART2_TX),
    FS_PINMUX(UART2_RTS),
    FS_PINMUX(UART2_RX),
    FS_PINMUX(UART2_CTS),
    FS_PINMUX(SD1_D3),
    FS_PINMUX(SD1_D2),
    FS_PINMUX(SD1_D1),
    FS_PINMUX(SD1_D0),
    FS_PINMUX(SD1_CMD),
    FS_PINMUX(SD1_CLK),
    FS_PINMUX(RSTN),
    FS_PINMUX(PWM0_BUCK),
    FS_PINMUX(ADC3),
    FS_PINMUX(ADC2),
    FS_PINMUX(ADC1),
    FS_PINMUX(USB_ID),
    FS_PINMUX(USB_VBUS_EN),
    FS_PINMUX(PKG_TYPE0),
    FS_PINMUX(USB_VBUS_DET),
    FS_PINMUX(PKG_TYPE1),
    FS_PINMUX(PKG_TYPE2),
    FS_PINMUX(MUX_SPI1_MISO),
    FS_PINMUX(MUX_SPI1_MOSI),
    FS_PINMUX(MUX_SPI1_CS),
    FS_PINMUX(MUX_SPI1_SCK),
    FS_PINMUX(PAD_ETH_TXM),
    FS_PINMUX(PAD_ETH_TXP),
    FS_PINMUX(PAD_ETH_RXM),
    FS_PINMUX(PAD_ETH_RXP),
    FS_PINMUX(VIVO_D10),
    FS_PINMUX(VIVO_D9),
    FS_PINMUX(VIVO_D8),
    FS_PINMUX(VIVO_D7),
    FS_PINMUX(VIVO_D6),
    FS_PINMUX(VIVO_D5),
    FS_PINMUX(VIVO_D4),
    FS_PINMUX(VIVO_D3),
    FS_PINMUX(VIVO_D2),
    FS_PINMUX(VIVO_D1),
    FS_PINMUX(VIVO_D0),
    FS_PINMUX(VIVO_CLK),
    FS_PINMUX(PAD_MIPIRX5N),
    FS_PINMUX(PAD_MIPIRX5P),
    FS_PINMUX(PAD_MIPIRX4N),
    FS_PINMUX(PAD_MIPIRX4P),
    FS_PINMUX(PAD_MIPIRX3N),
    FS_PINMUX(PAD_MIPIRX3P),
    FS_PINMUX(PAD_MIPIRX2N),
    FS_PINMUX(PAD_MIPIRX2P),
    FS_PINMUX(PAD_MIPIRX1N),
    FS_PINMUX(PAD_MIPIRX1P),
    FS_PINMUX(PAD_MIPIRX0N),
    FS_PINMUX(PAD_MIPIRX0P),
    FS_PINMUX(PAD_MIPI_TXM4),
    FS_PINMUX(PAD_MIPI_TXP4),
    FS_PINMUX(PAD_MIPI_TXM3),
    FS_PINMUX(PAD_MIPI_TXP3),
    FS_PINMUX(PAD_MIPI_TXM2),
    FS_PINMUX(PAD_MIPI_TXP2),
    FS_PINMUX(PAD_MIPI_TXM1),
    FS_PINMUX(PAD_MIPI_TXP1),
    FS_PINMUX(PAD_MIPI_TXM0),
    FS_PINMUX(PAD_MIPI_TXP0),
    FS_PINMUX(PAD_AUD_AINL_MIC),
    FS_PINMUX(PAD_AUD_AINR_MIC),
    FS_PINMUX(PAD_AUD_AOUTL),
    FS_PINMUX(PAD_AUD_AOUTR),
    FS_PINMUX(GPIO_RTX),
    FS_PINMUX(GPIO_ZQ),
};

const struct fselect pin_selects_array[][8] = {
/* CAM_MCLK0        */ {{CAM_MCLK0, 0},        FS_NONE,            {AUX1, 2},             {XGPIOA_0, 3},       FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* CAM_PD0          */ {FS_NONE,               {IIS1_MCLK, 1},     FS_NONE,               {XGPIOA_1, 3},       {CAM_HS0, 4},      FS_NONE,           FS_NONE,                FS_NONE},
/* CAM_RST0         */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOA_2, 3},       {CAM_VS0, 4},      FS_NONE,           {IIC4_SCL, 6},          FS_NONE},
/* CAM_MCLK1        */ {{CAM_MCLK1, 0},        FS_NONE,            {AUX2, 2},             {XGPIOA_3, 3},       {CAM_HS0, 4},      FS_NONE,           FS_NONE,                FS_NONE},
/* CAM_PD1          */ {FS_NONE,               {IIS1_MCLK, 1},     FS_NONE,               {XGPIOA_4, 3},       {CAM_VS0, 4},      FS_NONE,           {IIC4_SDA, 6},          FS_NONE},
/* IIC3_SCL         */ {{IIC3_SCL, 0},         FS_NONE,            FS_NONE,               {XGPIOA_5, 3},       FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* IIC3_SDA         */ {{IIC3_SDA, 0},         FS_NONE,            FS_NONE,               {XGPIOA_6, 3},       FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* SD0_CLK          */ {{SDIO0_CLK, 0},        {IIC1_SDA, 1},      {SPI0_SCK, 2},         {XGPIOA_7, 3},       FS_NONE,           {PWM_15, 5},       {EPHY_LNK_LED, 6},      {DBG_0, 7}},
/* SD0_CMD          */ {{SDIO0_CMD, 0},        {IIC1_SCL, 1},      {SPI0_SDO, 2},         {XGPIOA_8, 3},       FS_NONE,           {PWM_14, 5},       {EPHY_SPD_LED, 6},      {DBG_1, 7}},
/* SD0_D0           */ {{SDIO0_D_0, 0},        {CAM_MCLK1, 1},     {SPI0_SDI, 2},         {XGPIOA_9, 3},       {UART3_TX, 4},     {PWM_13, 5},       {WG0_D0, 6},            {DBG_2, 7}},
/* SD0_D1           */ {{SDIO0_D_1, 0},        {IIC1_SDA, 1},      {AUX0, 2},             {XGPIOA_10, 3},      {UART1_TX, 4},     {PWM_12, 5},       {WG0_D1, 6},            {DBG_3, 7}},
/* SD0_D2           */ {{SDIO0_D_2, 0},        {IIC1_SCL, 1},      {AUX1, 2},             {XGPIOA_11, 3},      {UART1_RX, 4},     {PWM_11, 5},       {WG1_D0, 6},            {DBG_4, 7}},
/* SD0_D3           */ {{SDIO0_D_3, 0},        {CAM_MCLK0, 1},     {SPI0_CS_X, 2},        {XGPIOA_12, 3},      {UART3_RX, 4},     {PWM_10, 5},       {WG1_D1, 6},            {DBG_5, 7}},
/* SD0_CD           */ {{SDIO0_CD, 0},         FS_NONE,            FS_NONE,               {XGPIOA_13, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* SD0_PWR_EN       */ {{SDIO0_PWR_EN, 0},     FS_NONE,            FS_NONE,               {XGPIOA_14, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* SPK_EN           */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOA_15, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* UART0_TX         */ {{UART0_TX, 0},         {CAM_MCLK1, 1},     {PWM_4, 2},            {XGPIOA_16, 3},      {UART1_TX, 4},     {AUX1, 5},         {JTAG_TMS, 6},          {DBG_6, 7}},
/* UART0_RX         */ {{UART0_RX, 0},         {CAM_MCLK0, 1},     {PWM_5, 2},            {XGPIOA_17, 3},      {UART1_RX, 4},     {AUX0, 5},         FS_NONE,                {DBG_7, 7}},
/* EMMC_RSTN        */ {{EMMC_RSTN, 0},        FS_NONE,            FS_NONE,               {XGPIOA_21, 3},      {AUX2, 4},         FS_NONE,           FS_NONE,                FS_NONE},
/* EMMC_DAT2        */ {{EMMC_DAT_2, 0},       {SPINOR_HOLD_X, 1}, {SPINAND_HOLD, 2},     {XGPIOA_26, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* EMMC_CLK         */ {{EMMC_CLK, 0},         {SPINOR_SCK, 1},    {SPINAND_CLK, 2},      {XGPIOA_22, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* EMMC_DAT0        */ {{EMMC_DAT_0, 0},       {SPINOR_MOSI, 1},   {SPINAND_MOSI, 2},     {XGPIOA_25, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* EMMC_DAT3        */ {{EMMC_DAT_3, 0},       {SPINOR_WP_X, 1},   {SPINAND_WP, 2},       {XGPIOA_27, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* EMMC_CMD         */ {{EMMC_CMD, 0},         {SPINOR_MISO, 1},   {SPINAND_MISO, 2},     {XGPIOA_23, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* EMMC_DAT1        */ {{EMMC_DAT_1, 0},       {SPINOR_CS_X, 1},   {SPINAND_CS, 2},       {XGPIOA_24, 3},      FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* JTAG_CPU_TMS     */ {{JTAG_CPU_TMS, 0},     {CAM_MCLK0, 1},     {PWM_7, 2},            {XGPIOA_19, 3},      {UART1_RTS, 4},    {AUX0, 5},         {UART1_TX, 6},          {VO_D_28, 7}},
/* JTAG_CPU_TCK     */ {{JTAG_CPU_TCK, 0},     {CAM_MCLK1, 1},     {PWM_6, 2},            {XGPIOA_18, 3},      {UART1_CTS, 4},    {AUX1, 5},         {UART1_RX, 6},          {VO_D_29, 7}},
/* JTAG_CPU_TRST    */ {{JTAG_CPU_TRST, 0},    FS_NONE,            FS_NONE,               {XGPIOA_20, 3},      FS_NONE,           FS_NONE,           {VO_D_30, 6},           FS_NONE},
/* IIC0_SCL         */ {{IIC0_SCL, 0},         {UART1_TX, 1},      {UART2_TX, 2},         {XGPIOA_28, 3},      FS_NONE,           {WG0_D0, 5},       FS_NONE,                {DBG_10, 7}},
/* IIC0_SDA         */ {{IIC0_SDA, 0},         {UART1_RX, 1},      {UART2_RX, 2},         {XGPIOA_29, 3},      FS_NONE,           {WG0_D1, 5},       {WG1_D0, 6},            {DBG_11, 7}},
/* AUX0             */ {{AUX0, 0},             FS_NONE,            FS_NONE,               {XGPIOA_30, 3},      {IIS1_MCLK, 4},    {VO_D_31, 5},      {WG1_D1, 6},            {DBG_12, 7}},
/* PWR_VBAT_DET     */ {{PWR_VBAT_DET, 0},     FS_NONE,            FS_NONE,               FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PWR_RSTN         */ {{PWR_RSTN, 0},         FS_NONE,            FS_NONE,               FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PWR_SEQ1         */ {{PWR_SEQ1, 0},         FS_NONE,            {PWR_GPIO_3, 3},       FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PWR_SEQ2         */ {{PWR_SEQ2, 0},         FS_NONE,            {PWR_GPIO_4, 3},       FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PWR_SEQ3         */ {{PWR_SEQ3, 0},         FS_NONE,            {PWR_GPIO_5, 3},       FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PWR_WAKEUP0      */ {{PWR_WAKEUP0, 0},      {PWR_IR0, 1},       {PWR_UART0_TX, 2},     {PWR_GPIO_6, 3},     {UART1_TX, 4},     {IIC4_SCL, 5},     {EPHY_LNK_LED, 6},      {WG2_D0, 7}},
/* PWR_WAKEUP1      */ {{PWR_WAKEUP1, 0},      {PWR_IR1, 1},       FS_NONE,               {PWR_GPIO_7, 3},     {UART1_TX, 4},     {IIC4_SCL, 5},     {EPHY_LNK_LED, 6},      {WG0_D0, 7}},
/* PWR_BUTTON1      */ {{PWR_BUTTON1, 0},      FS_NONE,            FS_NONE,               {PWR_GPIO_8, 3},     {UART1_RX, 4},     {IIC4_SDA, 5},     {EPHY_SPD_LED, 6},      {WG2_D1, 7}},
/* PWR_ON           */ {{PWR_ON, 0},           FS_NONE,            FS_NONE,               {PWR_GPIO_9, 3},     {UART1_RX, 4},     {IIC4_SDA, 5},     {EPHY_SPD_LED, 6},      {WG0_D1, 7}},
/* XTAL_XIN         */ {{PWR_XTAL_CLKIN, 0},   FS_NONE,            FS_NONE,               FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PWR_GPIO0        */ {{PWR_GPIO_0, 0},       {UART2_TX, 1},      {PWR_UART0_RX, 2},     FS_NONE,             {PWM_8, 4},        FS_NONE,           FS_NONE,                FS_NONE},
/* PWR_GPIO1        */ {{PWR_GPIO_1, 0},       {UART2_RX, 1},      FS_NONE,               {EPHY_LNK_LED, 3},   {PWM_9, 4},        {PWR_IIC_SCL, 5},  {IIC2_SCL, 6},          {PWR_MCU_JTAG_TMS, 7}},
/* PWR_GPIO2        */ {{PWR_GPIO_2, 0},       FS_NONE,            {PWR_SECTICK, 2},      {EPHY_SPD_LED, 3},   {PWM_10, 4},       {PWR_IIC_SDA, 5},  {IIC2_SDA, 6},          {PWR_MCU_JTAG_TCK, 7}},
/* CLK32K           */ {{CLK32K, 0},           {AUX0, 1},          {PWR_MCU_JTAG_TDI, 2}, {PWR_GPIO_10, 3},    {PWM_2, 4},        {KEY_COL0, 5},     {CAM_MCLK0, 6},         {DBG_0, 7}},
/* CLK25M           */ {{CLK25M, 0},           {AUX1, 1},          {PWR_MCU_JTAG_TDO, 2}, {PWR_GPIO_11, 3},    {PWM_3, 4},        {KEY_COL1, 5},     {CAM_MCLK1, 6},         {DBG_1, 7}},
/* IIC2_SCL         */ {{IIC2_SCL, 0},         {PWM_14, 1},        FS_NONE,               {PWR_GPIO_12, 3},    {UART2_RX, 4},     FS_NONE,           FS_NONE,                {KEY_COL2, 7}},
/* IIC2_SDA         */ {{IIC2_SDA, 0},         {PWM_15, 1},        FS_NONE,               {PWR_GPIO_13, 3},    {UART2_TX, 4},     {IIS1_MCLK, 5},    {IIS2_MCLK, 6},         {KEY_COL3, 7}},
/* UART2_TX         */ {{UART2_TX, 0},         {PWM_11, 1},        {PWR_UART1_TX, 2},     {PWR_GPIO_14, 3},    {KEY_ROW3, 4},     {UART4_TX, 5},     {IIS2_BCLK, 6},         {WG2_D0, 7}},
/* UART2_RTS        */ {{UART2_RTS, 0},        {PWM_8, 1},         FS_NONE,               {PWR_GPIO_15, 3},    {KEY_ROW0, 4},     {UART4_RTS, 5},    {IIS2_DO, 6},           {WG1_D0, 7}},
/* UART2_RX         */ {{UART2_RX, 0},         {PWM_10, 1},        {PWR_UART1_RX, 2},     {PWR_GPIO_16, 3},    {KEY_COL3, 4},     {UART4_RX, 5},     {IIS2_DI, 6},           {WG2_D1, 7}},
/* UART2_CTS        */ {{UART2_CTS, 0},        {PWM_9, 1},         FS_NONE,               {PWR_GPIO_17, 3},    {KEY_ROW1, 4},     {UART4_CTS, 5},    {IIS2_LRCK, 6},         {WG1_D1, 7}},
/* SD1_D3           */ {{PWR_SD1_D3_VO32, 0},  {SPI2_CS_X, 1},     {IIC1_SCL, 2},         {PWR_GPIO_18, 3},    {CAM_MCLK0, 4},    {UART3_CTS, 5},    {PWR_SPINOR1_CS_X, 6},  {PWM_4, 7}},
/* SD1_D2           */ {{PWR_SD1_D2_VO33, 0},  {IIC1_SCL, 1},      {UART2_TX, 2},         {PWR_GPIO_19, 3},    {CAM_MCLK0, 4},    {UART3_TX, 5},     {PWR_SPINOR1_HOLD_X, 6},{PWM_5, 7}},
/* SD1_D1           */ {{PWR_SD1_D1_VO34, 0},  {IIC1_SDA, 1},      {UART2_RX, 2},         {PWR_GPIO_20, 3},    {CAM_MCLK1, 4},    {UART3_RX, 5},     {PWR_SPINOR1_WP_X, 6},  {PWM_6, 7}},
/* SD1_D0           */ {{PWR_SD1_D0_VO35, 0},  {SPI2_SDI, 1},      {IIC1_SDA, 2},         {PWR_GPIO_21, 3},    {CAM_MCLK1, 4},    {UART3_RTS, 5},    {PWR_SPINOR1_MISO, 6},  {PWM_7, 7}},
/* SD1_CMD          */ {{PWR_SD1_CMD_VO36, 0}, {SPI2_SDO, 1},      {IIC3_SCL, 2},         {PWR_GPIO_22, 3},    {CAM_VS0, 4},      {EPHY_LNK_LED, 5}, {PWR_SPINOR1_MOSI, 6},  {PWM_8, 7}},
/* SD1_CLK          */ {{PWR_SD1_CLK_VO37, 0}, {SPI2_SCK, 1},      {IIC3_SDA, 2},         {PWR_GPIO_23, 3},    {CAM_HS0, 4},      {EPHY_SPD_LED, 5}, {PWR_SPINOR1_SCK, 6},   {PWM_9, 7}},
/* RSTN             */ {{RSTN, 0},             FS_NONE,            FS_NONE,               FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PWM0_BUCK        */ {{PWM_0, 0},            FS_NONE,            FS_NONE,               {XGPIOB_0, 3},       FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* ADC3             */ {FS_NONE,               {CAM_MCLK0, 1},     {IIC4_SCL, 2},         {XGPIOB_1, 3},       {PWM_12, 4},       {EPHY_LNK_LED, 5}, {WG2_D0, 6},            {UART3_TX, 7}},
/* ADC2             */ {FS_NONE,               {CAM_MCLK1, 1},     {IIC4_SDA, 2},         {XGPIOB_2, 3},       {PWM_13, 4},       {EPHY_SPD_LED, 5}, {WG2_D1, 6},            {UART3_RX, 7}},
/* ADC1             */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOB_3, 3},       {KEY_COL2, 4},     FS_NONE,           {PWM_3, 6},             FS_NONE},
/* USB_ID           */ {{USB_ID, 0},           FS_NONE,            FS_NONE,               {XGPIOB_4, 3},       FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* USB_VBUS_EN      */ {{USB_VBUS_EN, 0},      FS_NONE,            FS_NONE,               {XGPIOB_5, 3},       FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PKG_TYPE0        */ {{PKG_TYPE0, 0},        FS_NONE,            FS_NONE,               FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* USB_VBUS_DET     */ {{USB_VBUS_DET, 0},     FS_NONE,            FS_NONE,               {XGPIOB_6, 3},       {CAM_MCLK0, 4},    {CAM_MCLK1, 5},    FS_NONE,                FS_NONE},
/* PKG_TYPE1        */ {{PKG_TYPE1, 0},        FS_NONE,            FS_NONE,               FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* PKG_TYPE2        */ {{PKG_TYPE2, 0},        FS_NONE,            FS_NONE,               FS_NONE,             FS_NONE,           FS_NONE,           FS_NONE,                FS_NONE},
/* MUX_SPI1_MISO    */ {FS_NONE,               {UART3_RTS, 1},     {IIC1_SDA, 2},         {XGPIOB_8, 3},       {PWM_9, 4},        {KEY_COL1, 5},     {SPI1_SDI, 6},          {DBG_14, 7}},
/* MUX_SPI1_MOSI    */ {FS_NONE,               {UART3_RX, 1},      {IIC1_SCL, 2},         {XGPIOB_7, 3},       {PWM_8, 4},        {KEY_COL0, 5},     {SPI1_SDO, 6},          {DBG_13, 7}},
/* MUX_SPI1_CS      */ {FS_NONE,               {UART3_CTS, 1},     {CAM_MCLK0, 2},        {XGPIOB_10, 3},      {PWM_11, 4},       {KEY_ROW3, 5},     {SPI1_CS_X, 6},         {DBG_16, 7}},
/* MUX_SPI1_SCK     */ {FS_NONE,               {UART3_TX, 1},      {CAM_MCLK1, 2},        {XGPIOB_9, 3},       {PWM_10, 4},       {KEY_ROW2, 5},     {SPI1_SCK, 6},          {DBG_15, 7}},
/* PAD_ETH_TXM      */ {FS_NONE,               {UART3_RTS, 1},     {IIC1_SDA, 2},         {XGPIOB_24, 3},      {PWM_12, 4},       {CAM_MCLK1, 5},    {SPI1_SDI, 6},          {IIS2_BCLK, 7}},
/* PAD_ETH_TXP      */ {FS_NONE,               {UART3_RX, 1},      {IIC1_SCL, 2},         {XGPIOB_25, 3},      {PWM_13, 4},       {CAM_MCLK0, 5},    {SPI1_SDO, 6},          {IIS2_LRCK, 7}},
/* PAD_ETH_RXM      */ {FS_NONE,               {UART3_CTS, 1},     {CAM_MCLK0, 2},        {XGPIOB_26, 3},      {PWM_14, 4},       {CAM_VS0, 5},      {SPI1_CS_X, 6},         {IIS2_DI, 7}},
/* PAD_ETH_RXP      */ {FS_NONE,               {UART3_TX, 1},      {CAM_MCLK1, 2},        {XGPIOB_27, 3},      {PWM_15, 4},       {CAM_HS0, 5},      {SPI1_SCK, 6},          {IIS2_DO, 7}},
/* VIVO_D10         */ {{PWM_1, 0},            {VI1_D_10, 1},      {VO_D_23, 2},          {XGPIOB_11, 3},      {RMII0_IRQ, 4},    {CAM_MCLK0, 5},    {IIC1_SDA, 6},          {UART2_TX, 7}},
/* VIVO_D9          */ {{PWM_2, 0},            {VI1_D_9, 1},       {VO_D_22, 2},          {XGPIOB_12, 3},      FS_NONE,           {CAM_MCLK1, 5},    {IIC1_SCL, 6},          {UART2_RX, 7}},
/* VIVO_D8          */ {{PWM_3, 0},            {VI1_D_8, 1},       {VO_D_21, 2},          {XGPIOB_13, 3},      {RMII0_MDIO, 4},   {SPI3_SDO, 5},     {IIC2_SCL, 6},          {CAM_VS0, 7}},
/* VIVO_D7          */ {{VI2_D_7, 0},          {VI1_D_7, 1},       {VO_D_20, 2},          {XGPIOB_14, 3},      {RMII0_RXD1, 4},   {SPI3_SDI, 5},     {IIC2_SDA, 6},          {CAM_HS0, 7}},
/* VIVO_D6          */ {{VI2_D_6, 0},          {VI1_D_6, 1},       {VO_D_19, 2},          {XGPIOB_15, 3},      {RMII0_REFCLKI, 4},{SPI3_SCK, 5},     {UART2_TX, 6},          {CAM_VS0, 7}},
/* VIVO_D5          */ {{VI2_D_5, 0},          {VI1_D_5, 1},       {VO_D_18, 2},          {XGPIOB_16, 3},      {RMII0_RXD0, 4},   {SPI3_CS_X, 5},    {UART2_RX, 6},          {CAM_HS0, 7}},
/* VIVO_D4          */ {{VI2_D_4, 0},          {VI1_D_4, 1},       {VO_D_17, 2},          {XGPIOB_17, 3},      {RMII0_MDC, 4},    {IIC1_SDA, 5},     {UART2_CTS, 6},         {CAM_VS0, 7}},
/* VIVO_D3          */ {{VI2_D_3, 0},          {VI1_D_3, 1},       {VO_D_16, 2},          {XGPIOB_18, 3},      {RMII0_TXD0, 4},   {IIC1_SCL, 5},     {UART2_RTS, 6},         {CAM_HS0, 7}},
/* VIVO_D2          */ {{VI2_D_2, 0},          {VI1_D_2, 1},       {VO_D_15, 2},          {XGPIOB_19, 3},      {RMII0_TXD1, 4},   {CAM_MCLK1, 5},    {PWM_2, 6},             {UART2_TX, 7}},
/* VIVO_D1          */ {{VI2_D_1, 0},          {VI1_D_1, 1},       {VO_D_14, 2},          {XGPIOB_20, 3},      {RMII0_RXDV, 4},   {IIC3_SDA, 5},     {PWM_3, 6},             {IIC4_SCL, 7}},
/* VIVO_D0          */ {{VI2_D_0, 0},          {VI1_D_0, 1},       {VO_D_13, 2},          {XGPIOB_21, 3},      {RMII0_TXCLK, 4},  {IIC3_SCL, 5},     {WG1_D0, 6},            {IIC4_SDA, 7}},
/* VIVO_CLK         */ {{VI2_CLK, 0},          {VI1_CLK, 1},       {VO_CLK1, 2},          {XGPIOB_22, 3},      {RMII0_TXEN, 4},   {CAM_MCLK0, 5},    {WG1_D1, 6},            {UART2_RX, 7}},
/* PAD_MIPIRX5N     */ {FS_NONE,               {VI1_D_11, 1},      {VO_D_12, 2},          {XGPIOC_0, 3},       FS_NONE,           {CAM_MCLK0, 5},    {WG0_D0, 6},            {DBG_0, 7}},
/* PAD_MIPIRX5P     */ {FS_NONE,               {VI1_D_12, 1},      {VO_D_11, 2},          {XGPIOC_1, 3},       {IIS1_MCLK, 4},    {CAM_MCLK1, 5},    {WG0_D1, 6},            {DBG_1, 7}},
/* PAD_MIPIRX4N     */ {FS_NONE,               {VI0_CLK, 1},       {VI1_D_13, 2},         {XGPIOC_2, 3},       {IIC1_SDA, 4},     {CAM_MCLK0, 5},    {KEY_ROW0, 6},          {MUX_SPI1_SCK, 7}},
/* PAD_MIPIRX4P     */ {FS_NONE,               {VI0_D_0, 1},       {VI1_D_14, 2},         {XGPIOC_3, 3},       {IIC1_SCL, 4},     {CAM_MCLK1, 5},    {KEY_ROW1, 6},          {MUX_SPI1_CS, 7}},
/* PAD_MIPIRX3N     */ {FS_NONE,               {VI0_D_1, 1},       {VI1_D_15, 2},         {XGPIOC_4, 3},       {CAM_MCLK0, 4},    FS_NONE,           FS_NONE,                {MUX_SPI1_MISO, 7}},
/* PAD_MIPIRX3P     */ {FS_NONE,               {VI0_D_2, 1},       {VI1_D_16, 2},         {XGPIOC_5, 3},       FS_NONE,           FS_NONE,           FS_NONE,                {MUX_SPI1_MOSI, 7}},
/* PAD_MIPIRX2N     */ {FS_NONE,               {VI0_D_3, 1},       {VO_D_10, 2},          {XGPIOC_6, 3},       {VI1_D_17, 4},     {IIC4_SCL, 5},     FS_NONE,                {DBG_6, 7}},
/* PAD_MIPIRX2P     */ {FS_NONE,               {VI0_D_4, 1},       {VO_D_9, 2},           {XGPIOC_7, 3},       {VI1_D_18, 4},     {IIC4_SDA, 5},     FS_NONE,                {DBG_7, 7}},
/* PAD_MIPIRX1N     */ {FS_NONE,               {VI0_D_5, 1},       {VO_D_8, 2},           {XGPIOC_8, 3},       FS_NONE,           FS_NONE,           {KEY_ROW3, 6},          {DBG_8, 7}},
/* PAD_MIPIRX1P     */ {FS_NONE,               {VI0_D_6, 1},       {VO_D_7, 2},           {XGPIOC_9, 3},       {IIC1_SDA, 4},     FS_NONE,           {KEY_ROW2, 6},          {DBG_9, 7}},
/* PAD_MIPIRX0N     */ {FS_NONE,               {VI0_D_7, 1},       {VO_D_6, 2},           {XGPIOC_10, 3},      {IIC1_SCL, 4},     {CAM_MCLK1, 5},    FS_NONE,                {DBG_10, 7}},
/* PAD_MIPIRX0P     */ {FS_NONE,               {VI0_D_8, 1},       {VO_D_5, 2},           {XGPIOC_11, 3},      {CAM_MCLK0, 4},    FS_NONE,           FS_NONE,                {DBG_11, 7}},
/* PAD_MIPI_TXM4    */ {FS_NONE,               {SD1_CLK, 1},       {VO_D_24, 2},          {XGPIOC_18, 3},      {CAM_MCLK1, 4},    {PWM_12, 5},       {IIC1_SDA, 6},          {DBG_18, 7}},
/* PAD_MIPI_TXP4    */ {FS_NONE,               {SD1_CMD, 1},       {VO_D_25, 2},          {XGPIOC_19, 3},      {CAM_MCLK0, 4},    {PWM_13, 5},       {IIC1_SCL, 6},          {DBG_19, 7}},
/* PAD_MIPI_TXM3    */ {FS_NONE,               {SD1_D0, 1},        {VO_D_26, 2},          {XGPIOC_20, 3},      {IIC2_SDA, 4},     {PWM_14, 5},       {IIC1_SDA, 6},          {CAM_VS0, 7}},
/* PAD_MIPI_TXP3    */ {FS_NONE,               {SD1_D1, 1},        {VO_D_27, 2},          {XGPIOC_21, 3},      {IIC2_SCL, 4},     {PWM_15, 5},       {IIC1_SCL, 6},          {CAM_HS0, 7}},
/* PAD_MIPI_TXM2    */ {FS_NONE,               {VI0_D_13, 1},      {VO_D_0, 2},           {XGPIOC_16, 3},      {IIC1_SDA, 4},     {PWM_8, 5},        {SPI0_SCK, 6},          {SD1_D2, 7}},
/* PAD_MIPI_TXP2    */ {FS_NONE,               {VI0_D_14, 1},      {VO_CLK0, 2},          {XGPIOC_17, 3},      {IIC1_SCL, 4},     {PWM_9, 5},        {SPI0_CS_X, 6},         {SD1_D3, 7}},
/* PAD_MIPI_TXM1    */ {FS_NONE,               {VI0_D_11, 1},      {VO_D_2, 2},           {XGPIOC_14, 3},      {IIC2_SDA, 4},     {PWM_10, 5},       {SPI0_SDO, 6},          {DBG_14, 7}},
/* PAD_MIPI_TXP1    */ {FS_NONE,               {VI0_D_12, 1},      {VO_D_1, 2},           {XGPIOC_15, 3},      {IIC2_SCL, 4},     {PWM_11, 5},       {SPI0_SDI, 6},          {DBG_15, 7}},
/* PAD_MIPI_TXM0    */ {FS_NONE,               {VI0_D_9, 1},       {VO_D_4, 2},           {XGPIOC_12, 3},      {CAM_MCLK1, 4},    {PWM_14, 5},       {CAM_VS0, 6},           {DBG_12, 7}},
/* PAD_MIPI_TXP0    */ {FS_NONE,               {VI0_D_10, 1},      {VO_D_3, 2},           {XGPIOC_13, 3},      {CAM_MCLK0, 4},    {PWM_15, 5},       {CAM_HS0, 6},           {DBG_13, 7}},
/* PAD_AUD_AINL_MIC */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOC_23, 3},      {IIS1_BCLK, 4},    {IIS2_BCLK, 5},    FS_NONE,                FS_NONE},
/* PAD_AUD_AINR_MIC */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOC_22, 3},      {IIS1_DO, 4},      {IIS2_DI, 5},      {IIS1_DI, 6},           FS_NONE},
/* PAD_AUD_AOUTL    */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOC_25, 3},      {IIS1_LRCK, 4},    {IIS2_LRCK, 5},    FS_NONE,                FS_NONE},
/* PAD_AUD_AOUTR    */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOC_24, 3},      {IIS1_DI, 4},      {IIS2_DO, 5},      {IIS1_DO, 6},           FS_NONE},
/* GPIO_RTX         */ {FS_NONE,               FS_NONE,            FS_NONE,               {XGPIOB_23, 3},      {PWM_1, 4},        {CAM_MCLK0, 5},    FS_NONE,                FS_NONE},
/* GPIO_ZQ          */ {FS_NONE,               FS_NONE,            FS_NONE,               {PWR_GPIO_24, 3},    {PWM_2, 4},        FS_NONE,           FS_NONE,                FS_NONE},
};

#else

#error "Unsupported SOC type!"

#endif

static int8_t pinmux_get_index(uint8_t pin_index, fs_type func_type)
{
    const struct fselect *p;
    for (int i = 0; i < 8; i++) {
        p = &(pin_selects_array[pin_index][i]);
        LOG_D("[%d], type = %d, select = %d\n", i, p->type, p->select);
        if (p->type == func_type)
            return (int8_t)p->select; // it's safe bcos select should be [0, 7]
    }
    return -1;
}

static int pinmux_check_whitelist(const char *pin_name, const char *whitelist[])
{
    const char **name = &whitelist[0];
    while (*name) {
        if (0 == strcmp(pin_name, *name))
            return 0;
        name++;
    }
    return -1;
}

int pinmux_config(const char *pin_name, fs_type func_type, const char *whitelist[])
{
    const struct fmux *p_fmux;
    int index;
    int8_t select;

    if (whitelist) {
        if (0 != pinmux_check_whitelist(pin_name, whitelist)) {
            LOG_W("Pin Name \"%s\" is NOT Allowed by Whitelist!", pin_name);
            return -RT_ERROR;
        }
    }

    for (index = 0; index < ARRAY_SIZE(pinmux_array); index++) {
        p_fmux = &(pinmux_array[index]);
        LOG_D("index[%d]: name: %s, addr: %d, offset: %d, mask: %d\n",
                index, p_fmux->name, p_fmux->addr, p_fmux->offset, p_fmux->mask);
        if (0 == strcmp(pin_name, p_fmux->name)) {
            break;
        }
    }
    if (index == ARRAY_SIZE(pinmux_array)) {
        LOG_W("Pin Name \"%s\" is not found!", pin_name);
        return -RT_ERROR;;
    }
    if (p_fmux->selected) {
        LOG_W("Pin Name \"%s\" has been selected, duplicated?", pin_name);
        return -RT_ERROR;
    }

    select = pinmux_get_index(index, func_type);
    if (-1 == select) {
        LOG_W("Can not found Function selection for Pin \"%s\"", pin_name);
        return -RT_ERROR;
    }

    LOG_I("Pin Name = \"%s\", Func Type = %d, selected Func [%d]\n", pin_name, func_type, select);
    pinmux_array[index].selected = 1;
    mmio_clrsetbits_32(PINMUX_BASE + p_fmux->addr, p_fmux->mask << p_fmux->offset, select);
    return RT_EOK;
}
