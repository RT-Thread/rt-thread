/* generated configuration header file - do not edit */
#ifndef R_GPT_CFG_H_
#define R_GPT_CFG_H_
#ifdef __cplusplus
extern "C" {
#endif

#define GPT_CFG_PARAM_CHECKING_ENABLE (BSP_CFG_PARAM_CHECKING_ENABLE)
#define GPT_CFG_OUTPUT_SUPPORT_ENABLE (1)
#define GPT_CFG_WRITE_PROTECT_ENABLE  (0)

#ifndef BSP_CFG_GPT_COUNT_CLOCK_SOURCE
#define GPT_CFG_GPTCLK_BYPASS         (0)
#else
#define GPT_CFG_GPTCLK_BYPASS         (BSP_CFG_GPT_COUNT_CLOCK_SOURCE)
#endif

#ifdef __cplusplus
}
#endif
#endif /* R_GPT_CFG_H_ */
