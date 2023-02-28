/**************************************************************************//**
 * @file     gfx_reg.h
 * @brief    GFX register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __GFX_REG_H__
#define __GFX_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup GFX 2D Graphic Engine (GFX)
    Memory Mapped Structure for GFX Controller
@{ */

typedef struct
{


    /**
     * @var GFX_T::AQHiClockControl
     * Offset: 0x00  Clock control register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CLK3D_DIS |Disable 3D clock
     * |        |          |Software core clock disable signal for core (clk1x) clock.
     * |        |          |When set to 1, the clock is frozen.
     * |[1]     |CLK2D_DIS |Disable 2D clock
     * |        |          |Software clock disable signal.
     * |        |          |For this core both bits CLK3D_DIS and CLK2D_DIS should be controlled by software.
     * |        |          |The AXI interface clock is the only block not stalled at that point.
     * |[8:2]   |FSCALE_VAL|Core clock frequency scale value
     * |        |          |If this value is set to 1, the core clock will be 1/64 of clk1x, otherwise clock is fully frequency
     * |[9]     |FSCALE_CMD_LOAD|Core clock frequency scale value
     * |        |          |When writing a 1 to this bit, it updates the frequency scale factor with the value FSCALE_VAL.
     * |        |          |The bit must be set back to 0 after that.
     * |        |          |If this bit is set and FSCALE_VAL=0 (an invalid combination), the HREADYOUT output signal will get stuck to 0.
     * |[10]    |DISABLE_RAM_CLOCK_GATING|Disables clock gating for rams.
     * |[12]    |SOFT_RESET|Soft resets the GFX.
     * |[17]    |IDLE2_D   |2D pipe is idle.
     * |[19]    |ISOLATE_GPU|Isolate GPU bit
     * |        |          |Used for power on/off sequence.
     * @var GFX_T::AQHiIdle
     * Offset: 0x04  Idle status register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |IDLE_FE   |FE is idle.
     * |[1]     |IDLE_DE   |DE is idle.
     * |[2]     |IDLE_PE   |PE is idle.
     * |[31]    |AXI_LP    |AXI is in low power mode.
     * @var GFX_T::AQAxiConfig
     * Offset: 0x08  AXI configuration register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[11:8]  |AWCACHE   |Set AWCACHE[3:0] value
     * |[15:12] |ARCACHE   |Set ARCACHE[3:0] value
     * |[17:16] |AXDOMAIN_SHARED|Configure AxDOMAIN value for shareable request.
     * |[19:18] |AXDOMAIN_NON_SHARED|Configure AxDOMAIN value for non-shareable request.
     * |[23:20] |AXCACHE_OVERRIDE_SHARED|Configure AxCACHE value for shareable request.
     * @var GFX_T::AQAxiStatus
     * Offset: 0x0C  AXI status register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |WR_ERR_ID |Write error ID
     * |[7:4]   |RD_ERR_ID |Read error ID
     * |[8]     |DET_WR_ERR|1 = Detect write error
     * |[9]     |DET_RD_ERR|1 = Detect read error
     * @var GFX_T::AQIntrAcknowledge
     * Offset: 0x10  Interrupt acknowledge register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |INTR_VEC  |Interrupt Vector
     * |        |          |Each bit represents a corresponding event being triggered.
     * |        |          |Reading from this register clears the outstanding interrupt.
     * |        |          |For each interrupt event, 0=Clear, 1=Interrupt Active.
     * |        |          |INTR_VEC[31] is AXI_BUS_ERROR, 0 = No Error.
     * @var GFX_T::AQIntrEnbl
     * Offset: 0x14  Interrupt enable register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |INTR_ENBL_VEC|Interrupt enable
     * |        |          |Each bit enables a corresponding event.
     * @var GFX_T::GCChipRev
     * Offset: 0x24  Revision register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |REV       |Revision
     * @var GFX_T::GCChipDate
     * Offset: 0x28  Release date register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DATE      |Date (YYYY/MM/DD)
     * @var GFX_T::gcTotalCycles
     * Offset: 0x78  Total cycles register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CYCLES    |Total cycles
     * |        |          |This register is a free running counter.
     * |        |          |It can be reset by writing 0 to it.
     * @var GFX_T::gcregHIChipPatchRev
     * Offset: 0x98  Patch revision level register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PATCH_REV |Patch revision level for the chip.
     * @var GFX_T::gcProductId
     * Offset: 0xA8  Product ID register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |GRADE_LEVEL|Grade Level
     * |        |          |0 = None-no extra letter on the product name;.
     * |        |          |2 = L-Lite.
     * |        |          |3 = UL-Ultra Lite.
     * |[23:4]  |NUM       |Product Number
     * |        |          |520 for this core.
     * |[27:24] |TYPE      |Core Type
     * |        |          |0 = GC (2D or 3D Graphics Cores).
     * @var GFX_T::gcModulePowerControls
     * Offset: 0x100  Control register for module level power
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ENABLE_MODULE_CLOCK_GATING|Enables module level clock gating.
     * |[1]     |DISABLE_STALL_MODULE_CLOCK_GATING|Disables module level clock gating for stall condition.
     * |[2]     |DISABLE_STARVE_MODULE_CLOCK_GATING|Disables module level clock gating for starve/idle condition.
     * @var GFX_T::gcregMMUControl
     * Offset: 0x18C  MMU Control register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ENABLE    |Enable the MMU
     * |        |          |For security reasons, once the MMU is enabled it cannot be disabled anymore.
     * |        |          |1 = enable.
     * @var GFX_T::AQMemoryDebug
     * Offset: 0x414  Memory debug register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |MAX_OUTSTANDING_READS|Limits the total number of outstanding read requests.
     * @var GFX_T::AQRegisterTImingControl
     * Offset: 0x42C  SRAM timing control register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |FOR_RF1P  |For 1 port RAM
     * |[15:8]  |FOR_RF2P  |For 2 port RAM
     * |[17:16] |FAST_RTC  |RTC for fast RAMs
     * |[19:18] |FAST_WTC  |WTC for fast RAMs
     * |[20]    |POWER_DOW |Power down
     * |[21]    |DEEP_SLEEP|Deep sleep
     * |[22]    |LIGHT_SLEEP|Light sleep
     * @var GFX_T::AQCmdBufferAddr
     * Offset: 0x654  Command buffer base address register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ADDRESS   |Base address for the command buffer
     * |        |          |The address must be 64-bit alignment and it is always physical.
     * |        |          |To check the value of the current fetch address use AQFEDebugCurCmdAdr register.
     * |        |          |Since this is a write only register is has no reset value.
     * @var GFX_T::AQCmdBufferCtrl
     * Offset: 0x658  Command buffer control register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |PREFETCH  |Prefetch (write only)
     * |        |          |Number of 64-bit words to fetch from the command buffer.
     * |[16]    |ENABLE    |Enable
     * |        |          |Enable the command parser.
     * @var GFX_T::AQFEDebugCurCmdAdr
     * Offset: 0x664  Command decoder address register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:4]  |CUR_CMD_ADR|This is the command decoder address
     * |        |          |The address is always physical so the MSB should always be 0.
     * |        |          |Note that with the current MMU all 32 bits are valid.
     * |        |          |It has no reset value.
     */
    __IO uint32_t AQHiClockControl;      /*!< [0x0000] Clock control register                                           */
    __I  uint32_t AQHiIdle;              /*!< [0x0004] Idle status register                                             */
    __IO uint32_t AQAxiConfig;           /*!< [0x0008] AXI configuration register                                       */
    __I  uint32_t AQAxiStatus;           /*!< [0x000c] AXI status register                                              */
    __I  uint32_t AQIntrAcknowledge;     /*!< [0x0010] Interrupt acknowledge register                                   */
    __IO uint32_t AQIntrEnbl;            /*!< [0x0014] Interrupt enable register                                        */
    __I  uint32_t RESERVE0[3];
    __I  uint32_t GCChipRev;             /*!< [0x0024] Revision register                                                */
    __I  uint32_t GCChipDate;            /*!< [0x0028] Release date register                                            */
    __I  uint32_t RESERVE1[19];
    __IO uint32_t gcTotalCycles;         /*!< [0x0078] Total cycles register                                            */
    __I  uint32_t RESERVE2[7];
    __I  uint32_t gcregHIChipPatchRev;   /*!< [0x0098] Patch revision level register                                    */
    __I  uint32_t RESERVE3[3];
    __I  uint32_t gcProductId;           /*!< [0x00a8] Product ID register                                              */
    __I  uint32_t RESERVE4[21];
    __IO uint32_t gcModulePowerControls; /*!< [0x0100] Control register for module level power                          */
    __I  uint32_t RESERVE5[34];
    __O  uint32_t gcregMMUControl;       /*!< [0x018c] MMU Control register                                             */
    __I  uint32_t RESERVE6[161];
    __IO uint32_t AQMemoryDebug;         /*!< [0x0414] Memory debug register                                            */
    __I  uint32_t RESERVE7[5];
    __IO uint32_t AQRegisterTImingControl; /*!< [0x042c] SRAM timing control register                                     */
    __I  uint32_t RESERVE8[137];
    __O  uint32_t AQCmdBufferAddr;       /*!< [0x0654] Command buffer base address register                             */
    __IO uint32_t AQCmdBufferCtrl;       /*!< [0x0658] Command buffer control register                                  */
    __I  uint32_t RESERVE9[2];
    __I  uint32_t AQFEDebugCurCmdAdr;    /*!< [0x0664] Command decoder address register                                 */

} GFX_T;

/**
    @addtogroup GFX_CONST GFX Bit Field Definition
    Constant Definitions for GFX Controller
@{ */

#define GFX_AQHiClockControl_CLK3D_DIS_Pos (0)                                             /*!< GFX_T::AQHiClockControl: CLK3D_DIS Position*/
#define GFX_AQHiClockControl_CLK3D_DIS_Msk (0x1ul << GFX_AQHiClockControl_CLK3D_DIS_Pos)   /*!< GFX_T::AQHiClockControl: CLK3D_DIS Mask*/

#define GFX_AQHiClockControl_CLK2D_DIS_Pos (1)                                             /*!< GFX_T::AQHiClockControl: CLK2D_DIS Position*/
#define GFX_AQHiClockControl_CLK2D_DIS_Msk (0x1ul << GFX_AQHiClockControl_CLK2D_DIS_Pos)   /*!< GFX_T::AQHiClockControl: CLK2D_DIS Mask*/

#define GFX_AQHiClockControl_FSCALE_VAL_Pos (2)                                            /*!< GFX_T::AQHiClockControl: FSCALE_VAL Position*/
#define GFX_AQHiClockControl_FSCALE_VAL_Msk (0x7ful << GFX_AQHiClockControl_FSCALE_VAL_Pos) /*!< GFX_T::AQHiClockControl: FSCALE_VAL Mask*/

#define GFX_AQHiClockControl_FSCALE_CMD_LOAD_Pos (9)                                       /*!< GFX_T::AQHiClockControl: FSCALE_CMD_LOAD Position*/
#define GFX_AQHiClockControl_FSCALE_CMD_LOAD_Msk (0x1ul << GFX_AQHiClockControl_FSCALE_CMD_LOAD_Pos) /*!< GFX_T::AQHiClockControl: FSCALE_CMD_LOAD Mask*/

#define GFX_AQHiClockControl_DISABLE_RAM_CLOCK_GATING_Pos (10)                             /*!< GFX_T::AQHiClockControl: DISABLE_RAM_CLOCK_GATING Position*/
#define GFX_AQHiClockControl_DISABLE_RAM_CLOCK_GATING_Msk (0x1ul << GFX_AQHiClockControl_DISABLE_RAM_CLOCK_GATING_Pos) /*!< GFX_T::AQHiClockControl: DISABLE_RAM_CLOCK_GATING Mask*/

#define GFX_AQHiClockControl_SOFT_RESET_Pos (12)                                           /*!< GFX_T::AQHiClockControl: SOFT_RESET Position*/
#define GFX_AQHiClockControl_SOFT_RESET_Msk (0x1ul << GFX_AQHiClockControl_SOFT_RESET_Pos) /*!< GFX_T::AQHiClockControl: SOFT_RESET Mask*/

#define GFX_AQHiClockControl_IDLE2_D_Pos (17)                                              /*!< GFX_T::AQHiClockControl: IDLE2_D Position*/
#define GFX_AQHiClockControl_IDLE2_D_Msk (0x1ul << GFX_AQHiClockControl_IDLE2_D_Pos)       /*!< GFX_T::AQHiClockControl: IDLE2_D Mask  */

#define GFX_AQHiClockControl_ISOLATE_GPU_Pos (19)                                          /*!< GFX_T::AQHiClockControl: ISOLATE_GPU Position*/
#define GFX_AQHiClockControl_ISOLATE_GPU_Msk (0x1ul << GFX_AQHiClockControl_ISOLATE_GPU_Pos) /*!< GFX_T::AQHiClockControl: ISOLATE_GPU Mask*/

#define GFX_AQHiIdle_IDLE_FE_Pos         (0)                                               /*!< GFX_T::AQHiIdle: IDLE_FE Position      */
#define GFX_AQHiIdle_IDLE_FE_Msk         (0x1ul << GFX_AQHiIdle_IDLE_FE_Pos)               /*!< GFX_T::AQHiIdle: IDLE_FE Mask          */

#define GFX_AQHiIdle_IDLE_DE_Pos         (1)                                               /*!< GFX_T::AQHiIdle: IDLE_DE Position      */
#define GFX_AQHiIdle_IDLE_DE_Msk         (0x1ul << GFX_AQHiIdle_IDLE_DE_Pos)               /*!< GFX_T::AQHiIdle: IDLE_DE Mask          */

#define GFX_AQHiIdle_IDLE_PE_Pos         (2)                                               /*!< GFX_T::AQHiIdle: IDLE_PE Position      */
#define GFX_AQHiIdle_IDLE_PE_Msk         (0x1ul << GFX_AQHiIdle_IDLE_PE_Pos)               /*!< GFX_T::AQHiIdle: IDLE_PE Mask          */

#define GFX_AQHiIdle_AXI_LP_Pos          (31)                                              /*!< GFX_T::AQHiIdle: AXI_LP Position       */
#define GFX_AQHiIdle_AXI_LP_Msk          (0x1ul << GFX_AQHiIdle_AXI_LP_Pos)                /*!< GFX_T::AQHiIdle: AXI_LP Mask           */

#define GFX_AQAxiConfig_AWCACHE_Pos      (8)                                               /*!< GFX_T::AQAxiConfig: AWCACHE Position   */
#define GFX_AQAxiConfig_AWCACHE_Msk      (0xful << GFX_AQAxiConfig_AWCACHE_Pos)            /*!< GFX_T::AQAxiConfig: AWCACHE Mask       */

#define GFX_AQAxiConfig_ARCACHE_Pos      (12)                                              /*!< GFX_T::AQAxiConfig: ARCACHE Position   */
#define GFX_AQAxiConfig_ARCACHE_Msk      (0xful << GFX_AQAxiConfig_ARCACHE_Pos)            /*!< GFX_T::AQAxiConfig: ARCACHE Mask       */

#define GFX_AQAxiConfig_AXDOMAIN_SHARED_Pos (16)                                           /*!< GFX_T::AQAxiConfig: AXDOMAIN_SHARED Position*/
#define GFX_AQAxiConfig_AXDOMAIN_SHARED_Msk (0x3ul << GFX_AQAxiConfig_AXDOMAIN_SHARED_Pos) /*!< GFX_T::AQAxiConfig: AXDOMAIN_SHARED Mask*/

#define GFX_AQAxiConfig_AXDOMAIN_NON_SHARED_Pos (18)                                       /*!< GFX_T::AQAxiConfig: AXDOMAIN_NON_SHARED Position*/
#define GFX_AQAxiConfig_AXDOMAIN_NON_SHARED_Msk (0x3ul << GFX_AQAxiConfig_AXDOMAIN_NON_SHARED_Pos) /*!< GFX_T::AQAxiConfig: AXDOMAIN_NON_SHARED Mask*/

#define GFX_AQAxiConfig_AXCACHE_OVERRIDE_SHARED_Pos (20)                                   /*!< GFX_T::AQAxiConfig: AXCACHE_OVERRIDE_SHARED Position*/
#define GFX_AQAxiConfig_AXCACHE_OVERRIDE_SHARED_Msk (0xful << GFX_AQAxiConfig_AXCACHE_OVERRIDE_SHARED_Pos) /*!< GFX_T::AQAxiConfig: AXCACHE_OVERRIDE_SHARED Mask*/

#define GFX_AQAxiStatus_WR_ERR_ID_Pos    (0)                                               /*!< GFX_T::AQAxiStatus: WR_ERR_ID Position */
#define GFX_AQAxiStatus_WR_ERR_ID_Msk    (0xful << GFX_AQAxiStatus_WR_ERR_ID_Pos)          /*!< GFX_T::AQAxiStatus: WR_ERR_ID Mask     */

#define GFX_AQAxiStatus_RD_ERR_ID_Pos    (4)                                               /*!< GFX_T::AQAxiStatus: RD_ERR_ID Position */
#define GFX_AQAxiStatus_RD_ERR_ID_Msk    (0xful << GFX_AQAxiStatus_RD_ERR_ID_Pos)          /*!< GFX_T::AQAxiStatus: RD_ERR_ID Mask     */

#define GFX_AQAxiStatus_DET_WR_ERR_Pos   (8)                                               /*!< GFX_T::AQAxiStatus: DET_WR_ERR Position*/
#define GFX_AQAxiStatus_DET_WR_ERR_Msk   (0x1ul << GFX_AQAxiStatus_DET_WR_ERR_Pos)         /*!< GFX_T::AQAxiStatus: DET_WR_ERR Mask    */

#define GFX_AQAxiStatus_DET_RD_ERR_Pos   (9)                                               /*!< GFX_T::AQAxiStatus: DET_RD_ERR Position*/
#define GFX_AQAxiStatus_DET_RD_ERR_Msk   (0x1ul << GFX_AQAxiStatus_DET_RD_ERR_Pos)         /*!< GFX_T::AQAxiStatus: DET_RD_ERR Mask    */

#define GFX_AQIntrAcknowledge_INTR_VEC_Pos (0)                                             /*!< GFX_T::AQIntrAcknowledge: INTR_VEC Position*/
#define GFX_AQIntrAcknowledge_INTR_VEC_Msk (0xfffffffful << GFX_AQIntrAcknowledge_INTR_VEC_Pos) /*!< GFX_T::AQIntrAcknowledge: INTR_VEC Mask*/

#define GFX_AQIntrEnbl_INTR_ENBL_VEC_Pos (0)                                               /*!< GFX_T::AQIntrEnbl: INTR_ENBL_VEC Position*/
#define GFX_AQIntrEnbl_INTR_ENBL_VEC_Msk (0xfffffffful << GFX_AQIntrEnbl_INTR_ENBL_VEC_Pos) /*!< GFX_T::AQIntrEnbl: INTR_ENBL_VEC Mask  */

#define GFX_GCChipRev_REV_Pos            (0)                                               /*!< GFX_T::GCChipRev: REV Position         */
#define GFX_GCChipRev_REV_Msk            (0xfffffffful << GFX_GCChipRev_REV_Pos)           /*!< GFX_T::GCChipRev: REV Mask             */

#define GFX_GCChipDate_DATE_Pos          (0)                                               /*!< GFX_T::GCChipDate: DATE Position       */
#define GFX_GCChipDate_DATE_Msk          (0xfffffffful << GFX_GCChipDate_DATE_Pos)         /*!< GFX_T::GCChipDate: DATE Mask           */

#define GFX_gcTotalCycles_CYCLES_Pos     (0)                                               /*!< GFX_T::gcTotalCycles: CYCLES Position  */
#define GFX_gcTotalCycles_CYCLES_Msk     (0xfffffffful << GFX_gcTotalCycles_CYCLES_Pos)    /*!< GFX_T::gcTotalCycles: CYCLES Mask      */

#define GFX_gcregHIChipPatchRev_PATCH_REV_Pos (0)                                          /*!< GFX_T::gcregHIChipPatchRev: PATCH_REV Position*/
#define GFX_gcregHIChipPatchRev_PATCH_REV_Msk (0xfful << GFX_gcregHIChipPatchRev_PATCH_REV_Pos) /*!< GFX_T::gcregHIChipPatchRev: PATCH_REV Mask*/

#define GFX_gcProductId_GRADE_LEVEL_Pos  (0)                                               /*!< GFX_T::gcProductId: GRADE_LEVEL Position*/
#define GFX_gcProductId_GRADE_LEVEL_Msk  (0xful << GFX_gcProductId_GRADE_LEVEL_Pos)        /*!< GFX_T::gcProductId: GRADE_LEVEL Mask   */

#define GFX_gcProductId_NUM_Pos          (4)                                               /*!< GFX_T::gcProductId: NUM Position       */
#define GFX_gcProductId_NUM_Msk          (0xffffful << GFX_gcProductId_NUM_Pos)            /*!< GFX_T::gcProductId: NUM Mask           */

#define GFX_gcProductId_TYPE_Pos         (24)                                              /*!< GFX_T::gcProductId: TYPE Position      */
#define GFX_gcProductId_TYPE_Msk         (0xful << GFX_gcProductId_TYPE_Pos)               /*!< GFX_T::gcProductId: TYPE Mask          */

#define GFX_gcModulePowerControls_ENABLE_MODULE_CLOCK_GATING_Pos (0)                       /*!< GFX_T::gcModulePowerControls: ENABLE_MODULE_CLOCK_GATING Position*/
#define GFX_gcModulePowerControls_ENABLE_MODULE_CLOCK_GATING_Msk (0x1ul << GFX_gcModulePowerControls_ENABLE_MODULE_CLOCK_GATING_Pos) /*!< GFX_T::gcModulePowerControls: ENABLE_MODULE_CLOCK_GATING Mask*/

#define GFX_gcModulePowerControls_DISABLE_STALL_MODULE_CLOCK_GATING_Pos (1)                /*!< GFX_T::gcModulePowerControls: DISABLE_STALL_MODULE_CLOCK_GATING Position*/
#define GFX_gcModulePowerControls_DISABLE_STALL_MODULE_CLOCK_GATING_Msk (0x1ul << GFX_gcModulePowerControls_DISABLE_STALL_MODULE_CLOCK_GATING_Pos) /*!< GFX_T::gcModulePowerControls: DISABLE_STALL_MODULE_CLOCK_GATING Mask*/

#define GFX_gcModulePowerControls_DISABLE_STARVE_MODULE_CLOCK_GATING_Pos (2)               /*!< GFX_T::gcModulePowerControls: DISABLE_STARVE_MODULE_CLOCK_GATING Position*/
#define GFX_gcModulePowerControls_DISABLE_STARVE_MODULE_CLOCK_GATING_Msk (0x1ul << GFX_gcModulePowerControls_DISABLE_STARVE_MODULE_CLOCK_GATING_Pos) /*!< GFX_T::gcModulePowerControls: DISABLE_STARVE_MODULE_CLOCK_GATING Mask*/

#define GFX_gcregMMUControl_ENABLE_Pos   (0)                                               /*!< GFX_T::gcregMMUControl: ENABLE Position*/
#define GFX_gcregMMUControl_ENABLE_Msk   (0x1ul << GFX_gcregMMUControl_ENABLE_Pos)         /*!< GFX_T::gcregMMUControl: ENABLE Mask    */

#define GFX_AQMemoryDebug_MAX_OUTSTANDING_READS_Pos (0)                                    /*!< GFX_T::AQMemoryDebug: MAX_OUTSTANDING_READS Position*/
#define GFX_AQMemoryDebug_MAX_OUTSTANDING_READS_Msk (0xfful << GFX_AQMemoryDebug_MAX_OUTSTANDING_READS_Pos) /*!< GFX_T::AQMemoryDebug: MAX_OUTSTANDING_READS Mask*/

#define GFX_AQRegisterTImingControl_FOR_RF1P_Pos (0)                                       /*!< GFX_T::AQRegisterTImingControl: FOR_RF1P Position*/
#define GFX_AQRegisterTImingControl_FOR_RF1P_Msk (0xfful << GFX_AQRegisterTImingControl_FOR_RF1P_Pos) /*!< GFX_T::AQRegisterTImingControl: FOR_RF1P Mask*/

#define GFX_AQRegisterTImingControl_FOR_RF2P_Pos (8)                                       /*!< GFX_T::AQRegisterTImingControl: FOR_RF2P Position*/
#define GFX_AQRegisterTImingControl_FOR_RF2P_Msk (0xfful << GFX_AQRegisterTImingControl_FOR_RF2P_Pos) /*!< GFX_T::AQRegisterTImingControl: FOR_RF2P Mask*/

#define GFX_AQRegisterTImingControl_FAST_RTC_Pos (16)                                      /*!< GFX_T::AQRegisterTImingControl: FAST_RTC Position*/
#define GFX_AQRegisterTImingControl_FAST_RTC_Msk (0x3ul << GFX_AQRegisterTImingControl_FAST_RTC_Pos) /*!< GFX_T::AQRegisterTImingControl: FAST_RTC Mask*/

#define GFX_AQRegisterTImingControl_FAST_WTC_Pos (18)                                      /*!< GFX_T::AQRegisterTImingControl: FAST_WTC Position*/
#define GFX_AQRegisterTImingControl_FAST_WTC_Msk (0x3ul << GFX_AQRegisterTImingControl_FAST_WTC_Pos) /*!< GFX_T::AQRegisterTImingControl: FAST_WTC Mask*/

#define GFX_AQRegisterTImingControl_POWER_DOW_Pos (20)                                     /*!< GFX_T::AQRegisterTImingControl: POWER_DOW Position*/
#define GFX_AQRegisterTImingControl_POWER_DOW_Msk (0x1ul << GFX_AQRegisterTImingControl_POWER_DOW_Pos) /*!< GFX_T::AQRegisterTImingControl: POWER_DOW Mask*/

#define GFX_AQRegisterTImingControl_DEEP_SLEEP_Pos (21)                                    /*!< GFX_T::AQRegisterTImingControl: DEEP_SLEEP Position*/
#define GFX_AQRegisterTImingControl_DEEP_SLEEP_Msk (0x1ul << GFX_AQRegisterTImingControl_DEEP_SLEEP_Pos) /*!< GFX_T::AQRegisterTImingControl: DEEP_SLEEP Mask*/

#define GFX_AQRegisterTImingControl_LIGHT_SLEEP_Pos (22)                                   /*!< GFX_T::AQRegisterTImingControl: LIGHT_SLEEP Position*/
#define GFX_AQRegisterTImingControl_LIGHT_SLEEP_Msk (0x1ul << GFX_AQRegisterTImingControl_LIGHT_SLEEP_Pos) /*!< GFX_T::AQRegisterTImingControl: LIGHT_SLEEP Mask*/

#define GFX_AQCmdBufferAddr_ADDRESS_Pos  (0)                                               /*!< GFX_T::AQCmdBufferAddr: ADDRESS Position*/
#define GFX_AQCmdBufferAddr_ADDRESS_Msk  (0xfffffffful << GFX_AQCmdBufferAddr_ADDRESS_Pos) /*!< GFX_T::AQCmdBufferAddr: ADDRESS Mask   */

#define GFX_AQCmdBufferCtrl_PREFETCH_Pos (0)                                               /*!< GFX_T::AQCmdBufferCtrl: PREFETCH Position*/
#define GFX_AQCmdBufferCtrl_PREFETCH_Msk (0xfffful << GFX_AQCmdBufferCtrl_PREFETCH_Pos)    /*!< GFX_T::AQCmdBufferCtrl: PREFETCH Mask  */

#define GFX_AQCmdBufferCtrl_ENABLE_Pos   (16)                                              /*!< GFX_T::AQCmdBufferCtrl: ENABLE Position*/
#define GFX_AQCmdBufferCtrl_ENABLE_Msk   (0x1ul << GFX_AQCmdBufferCtrl_ENABLE_Pos)         /*!< GFX_T::AQCmdBufferCtrl: ENABLE Mask    */

#define GFX_AQFEDebugCurCmdAdr_CUR_CMD_ADR_Pos (4)                                         /*!< GFX_T::AQFEDebugCurCmdAdr: CUR_CMD_ADR Position*/
#define GFX_AQFEDebugCurCmdAdr_CUR_CMD_ADR_Msk (0xffffffful << GFX_AQFEDebugCurCmdAdr_CUR_CMD_ADR_Pos) /*!< GFX_T::AQFEDebugCurCmdAdr: CUR_CMD_ADR Mask*/

/**@}*/ /* GFX_CONST */
/**@}*/ /* end of GFX register group */

/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __GFX_REG_H__ */
