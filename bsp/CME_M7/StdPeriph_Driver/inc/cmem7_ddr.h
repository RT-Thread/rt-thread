/**
    *****************************************************************************
    * @file     cmem7_ddr.h
    *
    * @brief    CMEM7 AES header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_DDR_H
#define __CMEM7_DDR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"
/** @defgroup _MEM_TYPE
  * @{
  */
enum _MEM_TYPE
{
    MEM_DDR2=1,
    MEM_DDR3
} ;
/**
  * @}
  */

/** @defgroup _BUS_WIDTH
  * @{
  */
enum _BUS_WIDTH
{
    BUS_WIDTH_8,
    BUS_WIDTH_16,
    BUS_WIDTH_MAX
};
/**
  * @}
  */
/** @defgroup _CHIP_TYPE
  * @{
  */
enum _CHIP_TYPE
{
    _32Mbx8,
    _64Mbx8,
    _128Mbx8,
    _256Mbx8,
    _512Mbx8,
    _16Mbx16,
    _32Mbx16,
    _64Mbx16,
    _128Mbx16,
    _256Mbx16,
    _512Mbx16,
    CHIP_TYPE_MAX
};
/**
  * @}
  */

/** @defgroup _CHIP_NUM
  * @{
  */
enum _CHIP_NUM
{
    CHIP_NUM_x1,
    CHIP_NUM_x2,
    CHIP_NUM_MAX
};
/**
  * @}
  */

/** @defgroup MEM_CHIP_INFO
  * @{
  */
typedef struct {
    uint8_t mem_type;     /*!< ddr type @ref _MEM_TYPE*/
    uint8_t Bus_width;  /*!< ddr qs bus width @ref _BUS_WIDTH*/
    uint8_t Chip_type;  /*!< chip type @ref _CHIP_TYPE*/
    uint8_t Chip_num;   /*!< chip number @ref _CHIP_NUM*/
    uint8_t Chip_bank;      /*!< chip bank number*/
} MEM_CHIP_INFO;
/**
  * @}
  */


/** @defgroup DDR2MEM
  * @{
  */
typedef struct {
    uint32_t tCK;               /*!< Period of clock(ps), not data period */
    uint32_t tCL;                       /*!< tCL */
    uint32_t tRCD;                      /*!< tRCD */
    uint32_t tRP;                       /*!< tRP */
    uint32_t tRC;                       /*!< tRC */
    uint32_t tRAS;                      /*!< tRAS */
    uint32_t tWR;                       /*!< tWR */
    uint32_t tRRD;                      /*!< tRRD */
    uint32_t tWTR;                      /*!< tWTR */
    uint32_t tRTP;                      /*!< tRTP */
    uint32_t tFAW;                      /*!< tFAW */
} DDR2MEM;                              /*!< DDR2时序定义 */
/**
  * @}
  */

/** @defgroup DDR3MEM
  * @{
  */
typedef struct {
    uint32_t tCK;               /*!< Period of clock(ps), not data period */
    uint32_t tCL;                       /*!< tCL */
    uint32_t tWCL;                      /*!< tWCL */
    uint32_t tRCD;                      /*!< tRCD */
    uint32_t tRAS;                      /*!< tRAS */
    uint32_t tRP;                       /*!< tRP */
    uint32_t tRC;                       /*!< tRC */
    uint32_t tRRD;                      /*!< tRRD */
    uint32_t tFAW;                      /*!< tFAW */
    uint32_t tWR;                       /*!< tWR */
    uint32_t tRTP;                      /*!< tRTP */
    uint32_t tZQoper;                   /*!< tZQCL */
    uint32_t tZQCS;                     /*!< tZQCS */
} DDR3MEM;                              /*!< DDR3时序定义 */
/**
  * @}
  */

/** @defgroup DDR2PREDEF
  * @{
  */
extern const DDR2MEM DDR2PREDEF[];      /*!< Pre-defined DDR2 Timing in library */
#define DDR2_400C           0           /*!< sg5E: DDR2-400C CL=4, tCK=5000ps */

/**
  * @}
  */

/** @defgroup DDR3PREDEF
  * @{
  */
extern const DDR3MEM DDR3PREDEF[];      /*!< Pre-defined DDR3 Timing in library */
#define DDR3_400            0
#define DDR3_667        1

/**
  * @}
  */

/**
 * @brief DDR Timing Configuration
   * @param[in] chip information ,A pointer to struct @ref MEM_CHIP_INFO
   * @param[in] ddr A pointer to struct @ref DDR2MEM or @ref DDR3MEM that specified DDR Timing. Some typital DDR2/3 Timings are defined in arrays @ref DDR2PREDEF and @ref DDR3PREDEF.
 * @retval void
   */
BOOL  DDR_Init(const MEM_CHIP_INFO *chip_info, const void *ddr);
#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_DDR_H */

