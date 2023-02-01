#ifndef __CE_PLATFORM_H
#define __CE_PLARFORM_H


#ifdef __cplusplus
extern "C"
{
#endif

/*define CE version*/
#define CE_SUPPORT_CE_V3_1

#define CE_NS_BASE_REG          (0x01904000)
#define CE_S_BASE_REG           (0x01904800)

#define SUNXI_IRQ_CE   98

#define SUNXI_CCM_BASE                      (0x03001000)
#define CCMU_CE_CLK_REG                     (SUNXI_CCM_BASE + 0x680)
#define CCMU_CE_BGR_REG                     (SUNXI_CCM_BASE + 0x68C)
#define MBUS_MAT_CLK_GATING_REG             (SUNXI_CCM_BASE + 0x804)

#define CE_CLK_SRC_MASK                     (0x1)
#define CE_CLK_SRC_SEL_BIT                  (24)
#define CE_CLK_SRC                          (0x01)
#define CE_CLK_DIV_RATION_N_BIT             (8)
#define CE_CLK_DIV_RATION_N_MASK            (0x3)
#define CE_CLK_DIV_RATION_N                 (0)

#define CE_CLK_DIV_RATION_M_BIT             (0)
#define CE_CLK_DIV_RATION_M_MASK            (0xF)
#define CE_CLK_DIV_RATION_M                 (3)

#define CE_SCLK_ONOFF_BIT                   (31)
#define CE_SCLK_ON                          (1)

#define CE_GATING_PASS                      (1)
#define CE_GATING_BIT                       (0)
#define CE_RST_BIT                          (16)
#define CE_DEASSERT                         (1)

#ifdef __cplusplus
}
#endif

#endif
