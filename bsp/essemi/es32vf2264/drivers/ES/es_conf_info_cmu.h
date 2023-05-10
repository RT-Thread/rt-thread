/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_CMU_H__
#define __ES_CONF_INFO_CMU_H__


/* 时钟树 配置 */

#define  ES_C_DIV_1          ALD_CMU_DIV_1
#define  ES_C_DIV_2          ALD_CMU_DIV_2
#define  ES_C_DIV_4          ALD_CMU_DIV_4
#define  ES_C_DIV_8          ALD_CMU_DIV_8
#define  ES_C_DIV_16          ALD_CMU_DIV_16
#define  ES_C_DIV_32          ALD_CMU_DIV_32
#define  ES_C_DIV_64          ALD_CMU_DIV_64
#define  ES_C_DIV_128          ALD_CMU_DIV_128
#define  ES_C_DIV_256          ALD_CMU_DIV_256
#define  ES_C_DIV_512          ALD_CMU_DIV_512
#define  ES_C_DIV_1024          ALD_CMU_DIV_1024
#define  ES_C_DIV_2048          ALD_CMU_DIV_2048
#define  ES_C_DIV_4096          ALD_CMU_DIV_4096

#define  ES_C_HOSC_DIV_1        ALD_CMU_PLL1_INPUT_HOSC
#define  ES_C_HOSC_DIV_2        ALD_CMU_PLL1_INPUT_HOSC_2
#define  ES_C_HOSC_DIV_3        ALD_CMU_PLL1_INPUT_HOSC_3
#define  ES_C_HOSC_DIV_4        ALD_CMU_PLL1_INPUT_HOSC_4
#define  ES_C_HOSC_DIV_5        ALD_CMU_PLL1_INPUT_HOSC_5
#define  ES_C_HOSC_DIV_6        ALD_CMU_PLL1_INPUT_HOSC_6
#define  ES_C_HRC_DIV_6         ALD_CMU_PLL1_INPUT_HRC_6





#define   ES_PLL1_REFER_CLK           ES_C_PLL_REF_HOSC8M
#define   ES_PLL1_OUT_CLK             ES_C_PLL_OUT_72M
#define   ES_CMU_PLL1_SAFE_EN         ES_C_DISABLE
#define   ES_CMU_HOSM_SAFE_EN         ES_C_DISABLE
#define   ES_CMU_LRC_EN               ES_C_ENABLE
#define   ES_CMU_HRC4M_EN             ES_C_ENABLE
#define   ES_CMU_HRC48M_EN            ES_C_ENABLE
#define   ES_CMU_SYS_DIV              ES_C_DIV_1
#define   ES_CMU_PCLK_DIV             ES_C_DIV_1
#define   ES_CMU_UART_BUAND_MAX       XXXXXX
#define   ES_CMU_UART_BUAND_MIN       XXXXXX
#define   ES_CMU_SPI_BUAND_MAX        XXXXXX
#define   ES_CMU_SPI_BUAND_MIN        XXXXXX
#define   ES_SYS_CLK_SOURSE           CMU_CLOCK_PLL
#define   ES_SYS_SOURCE_CLK           72000000
#define   ES_PCLK_CLK                 72000000
#define   ES_SYS_HCLK_CLK             72000000
#define   ES_CMU_EXTERN_CLK_HOSC      8000000




#endif
