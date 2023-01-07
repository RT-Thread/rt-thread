#ifndef __BL808_COMMON_H__
#define __BL808_COMMON_H__

#include "bl808.h"
#include "misc.h"

#ifndef __set_MSP
#define __set_MSP(msp) __ASM volatile("add sp, x0, %0" ::"r"(msp))
#endif

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  COMMON
 *  @{
 */

/** @defgroup  COMMON_Public_Types
 *  @{
 */

/*@} end of group COMMON_Public_Types */

/** @defgroup  COMMON_Public_Constants
 *  @{
 */

/** @defgroup DRIVER_INT_PERIPH
 *  @{
 */
#define IS_INT_PERIPH(INT_PERIPH) ((INT_PERIPH) < IRQn_LAST)

/*@} end of group DRIVER_INT_PERIPH */

/** @defgroup DRIVER_INT_MASK
 *  @{
 */
#define IS_BL_MASK_TYPE(type) (((type) == MASK) || ((type) == UNMASK))

/*@} end of group COMMON_Public_Constants */

/** @defgroup DRIVER_Public_FunctionDeclaration
 *  @brief DRIVER functions declaration
 *  @{
 */

void ASM_Delay_Us(uint32_t core, uint32_t cnt, uint32_t loopT);
void arch_delay_us(uint32_t cnt);
void arch_delay_ms(uint32_t cnt);

void C906_All_Int_Enable(void);
void C906_All_Int_Disable(void);
/*@} end of group DRIVER_COMMON  */

#endif /* __BL808_COMMON_H__ */
