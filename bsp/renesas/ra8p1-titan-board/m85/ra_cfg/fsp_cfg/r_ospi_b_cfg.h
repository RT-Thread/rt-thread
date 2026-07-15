/* generated configuration header file - do not edit */
#ifndef R_OSPI_B_CFG_H_
#define R_OSPI_B_CFG_H_
#ifdef __cplusplus
extern "C" {
#endif

#define OSPI_B_CFG_PARAM_CHECKING_ENABLE          (BSP_CFG_PARAM_CHECKING_ENABLE)
#define OSPI_B_CFG_DMAC_SUPPORT_ENABLE            (0)
#define OSPI_B_CFG_XIP_SUPPORT_ENABLE             (0)
#define OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE (0)
#define OSPI_B_CFG_PREFETCH_FUNCTION              (1)
#define OSPI_B_CFG_COMBINATION_FUNCTION           (OSPI_B_COMBINATION_FUNCTION_64BYTE)
#define OSPI_B_CFG_ROW_ADDRESSING_SUPPORT_ENABLE  (0)

#if (2 == 0)
    #define OSPI_B_CFG_DOTF_SUPPORT_ENABLE            (1)
    #define OSPI_B_CFG_DOTF_PROTECTED_MODE_SUPPORT_ENABLE
#else
    #define OSPI_B_CFG_DOTF_SUPPORT_ENABLE            (0)
#endif

#ifdef __cplusplus
}
#endif
#endif /* R_OSPI_B_CFG_H_ */
