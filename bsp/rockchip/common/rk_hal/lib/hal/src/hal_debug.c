/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup DEBUG
 *  @{
 */

/** @defgroup DEBUG_How_To_Use How To Use
 *  @{

 The DEBUG driver can be used as follows:

 Implement DBG hook:

 - printf func: define new HAL_SYSLOG in hal_conf.h or use HAL_DBG_Printf() in default;
 - assert func: redefine AssertFailed().

 Define debug level in hal_conf.h:

 - HAL_DBG_ON: print master switch;
 - HAL_DBG_INFO_ON: information printing switch;
 - HAL_DBG_WRN_ON: information printing switch;
 - HAL_DBG_ERR_ON: information printing switch;
 - HAL_ASSERT_ON: Support assert.

 APIS:

 - printf information by calling HAL_DBG();
 - printf warning by calling HAL_DBG_WRN();
 - printf error by calling HAL_DBG_ERR();
 - do assert by calling HAL_ASSERT().

 @} */

#include "hal_base.h"

/** @defgroup DEBUG_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

/********************* Private Structure Definition **************************/

/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/

/** @} */
/********************* Public Function Definition ****************************/

/** @defgroup DEBUG_Exported_Functions_Group5 Other Functions

 This section provides functions allowing to init and deinit module as follows:

 *  @{
 */

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the HAL_ASSERT error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: HAL_ASSERT error line source number
  */
__WEAK void HAL_AssertFailed(const char *file, uint32_t line)
{
    HAL_DBG_ERR("assert failed at %s %lu\n", file, line);
    while (1) {
        ;
    }
}

/**
 * @brief  format hex print.
 * @param  s: head tag for every new line.
 * @param  buf: buffer for printing.
 * @param  width: every single printed object width.
 * @param  len: the number of printed objects.
 * @return HAL_Status: HAL_OK.
 * sum = width * len (BYTE).
 */
HAL_Status HAL_DBG_HEX(char *s, void *buf, uint32_t width, uint32_t len)
{
#ifdef HAL_DBG_ON
    uint32_t i, j;
    unsigned char *p8 = (unsigned char *)buf;
    unsigned short *p16 = (unsigned short *)buf;
    uint32_t *p32 = (uint32_t *)buf;

    j = 0;
    for (i = 0; i < len; i++) {
        if (j == 0) {
            HAL_SYSLOG("[HAL_DBG_HEX] %s %p + 0x%lx:", s, buf, i * width);
        }

        if (width == 4) {
            HAL_SYSLOG("0x%08lx,", p32[i]);
        } else if (width == 2) {
            HAL_SYSLOG("0x%04x,", p16[i]);
        } else {
            HAL_SYSLOG("0x%02x,", p8[i]);
        }

        if (++j >= 16) {
            j = 0;
            HAL_SYSLOG("\n");
        }
    }
    HAL_SYSLOG("\n");
#endif

    return HAL_OK;
}

/**
 * @brief  format and print data
 * @param  format: format printf param.
 * @return int32_t.
 */
__WEAK int32_t HAL_DBG_Printf(const char *format, ...)
{
    return 0;
}

/** @} */

/** @} */

/** @} */
