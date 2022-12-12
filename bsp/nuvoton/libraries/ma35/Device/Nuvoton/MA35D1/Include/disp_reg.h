/**************************************************************************//**
* @file     disp_reg.h
* @brief    LCD Display Controller driver header file
*
* SPDX-License-Identifier: Apache-2.0
* @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#ifndef __DISP_REG_H__
#define __DISP_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup DISP LCD Display Controller(DISP)
    Memory Mapped Structure for DISP Controller
@{ */

typedef struct
{
    /**
     * @var DISP_T::AQHiClockControl
     * Offset: 0x00  Clock Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |CLKDC_DIS |Disable DC clock.
     * |[8:2]   |FSCALE_VAL|Core clock frequency scale value.
     * |[9]     |FSCALE_CMD_LOAD|Core clock frequency scale value enable When writing a 1 to this bit, it updates the frequency scale factor with the value FSCALE_VAL[6:0] The bit must be set back to 0 after that If this bit is set and FSCALE_VAL=0 (an invalid combination), the HREADYOUT output signal will get stuck to 0.
     * |[10]    |DISABLE_RAM_CLOCK_GATING|Disables clock gating for rams.
     * |[11]    |DISABLE_DEBUG_REGISTERS|Disable debug registers If this bit is 1, debug registers are clock gated(reset=1).
     * |[12]    |SOFT_RESET|Soft resets the IP.
     * |[13]    |DISABLE_RAM_POWER_OPTIMIZATION|Disables ram power optimization.
     * @var DISP_T::FrameBufferAddress0
     * Offset: 0x1400  Framebuffer Start Address Register. Starting address of the framebuffer. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[30:0]  |ADDRESS   |Framebuffer Start Address
     * |[31]    |TYPE      |0 => SYSTEM 1 => VIRTUAL_SYSTEM
     * @var DISP_T::FrameBufferStride0
     * Offset: 0x1408  Framebuffer Stride Register. Stride of the framebuffer in bytes. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[16:0]  |STRIDE    |Number of bytes from start of one line to next line.
     * @var DISP_T::DisplayDitherConfig0
     * Offset: 0x1410  Display Dither Configuration Register. Configuration register for dithering. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31]    |ENABLE    |Enabling dithering allows R8G8B8 modes to show better on panels with less bits- per-pixel Note: This field is double buffered.
     * @var DISP_T::PanelConfig0
     * Offset: 0x1418  Panel Configuration Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DE        |Data Enable enabled/disabled 0 => DISABLED 1 => ENABLED
     * |[1]     |DE_POLARITY|Data Enable polarity 0 => POSITIVE 1 => NEGATIVE
     * |[4]     |DATA_ENABLE|Data enabled/disabled 0 => DISABLED 1 => ENABLED
     * |[5]     |DATA_POLARITY|Data polarity 0 => POSITIVE 1 => NEGATIVE
     * |[8]     |CLOCK     |Clock enabled/disabled 0 => DISABLED 1 => ENABLED
     * |[9]     |CLOCK_POLARITY|Clock polarity 0 => POSITIVE 1 => NEGATIVE
     * @var DISP_T::DisplayDitherTableLow0
     * Offset: 0x1420  Display Dither Table Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |Y0_X0     |Dither threshold value for x,y=0,0.
     * |[7:4]   |Y0_X1     |Dither threshold value for x,y=1,0.
     * |[11:8]  |Y0_X2     |Dither threshold value for x,y=2,0.
     * |[15:12] |Y0_X3     |Dither threshold value for x,y=3,0.
     * |[19:16] |Y1_X0     |Dither threshold value for x,y=0,1.
     * |[23:20] |Y1_X1     |Dither threshold value for x,y=1,1.
     * |[27:24] |Y1_X2     |Dither threshold value for x,y=2,1.
     * |[31:28] |Y1_X3     |Dither threshold value for x,y=3,1.
     * @var DISP_T::DisplayDitherTableHigh0
     * Offset: 0x1428  Display Dither Table Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |Y2_X0     |Dither threshold value for x,y=0,2.
     * |[7:4]   |Y2_X1     |Dither threshold value for x,y=1,2.
     * |[11:8]  |Y2_X2     |Dither threshold value for x,y=2,2.
     * |[15:12] |Y2_X3     |Dither threshold value for x,y=3,2.
     * |[19:16] |Y3_X0     |Dither threshold value for x,y=0,3.
     * |[23:20] |Y3_X1     |Dither threshold value for x,y=1,3.
     * |[27:24] |Y3_X2     |Dither threshold value for x,y=2,3.
     * |[31:28] |Y3_X3     |Dither threshold value for x,y=3,3.
     * @var DISP_T::HDisplay0
     * Offset: 0x1430  Horizontal Total and Display End Counter Register. Note: This register is double buffered
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |DISPLAY_END|Visible number of horizontal pixels.
     * |[30:16] |TOTAL     |Total number of horizontal pixels.
     * @var DISP_T::HSync0
     * Offset: 0x1438  Horizontal Sync Counter Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |START     |Start of horizontal sync pulse.
     * |[29:15] |END       |End of horizontal sync pulse.
     * |[30]    |PULSE     |Horizontal sync pulse control 0 => DISABLED 1 => ENABLED
     * |[31]    |POLARITY  |Polarity of the horizontal sync pulse 0 => POSITIVE 1 => NEGATIVE
     * @var DISP_T::VDisplay0
     * Offset: 0x1440  Vertical Total and Display End Counter Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |DISPLAY_END|Visible number of vertical lines
     * |[30:16] |TOTAL     |Total number of vertical lines.
     * @var DISP_T::VSync0
     * Offset: 0x1448  Vertical Sync Counter Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |START     |Start of the vertical sync pulse
     * |[29:15] |END       |End of the vertical sync pulse.
     * |[30]    |PULSE     |Vertical sync pulse control 0 => DISABLED 1 => ENABLED
     * |[31]    |POLARITY  |Polarity of the vertical sync pulse 0 => POSITIVE 1 => NEGATIVE
     * @var DISP_T::DisplayCurrentLocation0
     * Offset: 0x1450  Display Current Location Register. Current x,y location of display controller.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |X         |Current X location.
     * |[31:16] |Y         |Current Y location.
     * @var DISP_T::GammaIndex0
     * Offset: 0x1458  Gamma Table Index Register. Index into gamma table. See GammaData for more information.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |INDEX     |Index into gamma table.
     * @var DISP_T::GammaData0
     * Offset: 0x1460  Gamma Data Translation Register. Translation values for the gamma table. When this register gets written, the data gets stored in the gamma table at the index specified by the GammaIndex register. After the register is written, the index gets incremented.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |BLUE      |Blue translation value.
     * |[19:10] |GREEN     |Green translation value.
     * |[29:20] |READ      |Red translation value.
     * @var DISP_T::CursorConfig
     * Offset: 0x1468  Cursor Configuration Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |FORMAT    |Format of the cursor Note: This field is double buffered.
     * |[4]     |DISPLAY   |Display Controller owning the cursor.
     * |[12:8]  |HOT_SPOT_Y|Vertical offset to cursor hotspot Note: This field is double buffered.
     * |[20:16] |HOT_SPOT_X|Horizontal offset to cursor hotspot Note: This field is double buffered.
     * @var DISP_T::CursorAddress
     * Offset: 0x146C  Cursor Address Register. Address of the cursor shape. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[30:0]  |ADDRESS   |Cursor Address
     * |[31]    |TYPE      |0 => SYSTEM 1 => VIRTUAL_SYSTEM
     * @var DISP_T::CursorLocation
     * Offset: 0x1470  Cursor Location Register. Location of the cursor on the owning display. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |X         |X location of cursor's hotspot.
     * |[30:16] |Y         |Y location of cursor's hotspot.
     * @var DISP_T::CursorBackground
     * Offset: 0x1474  Masked Cursor Background Color Register. The background color for Masked cursors. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |Blue value.
     * |[15:8]  |GREEN     |Green value.
     * |[23:16] |RED       |Red value.
     * @var DISP_T::CursorForeground
     * Offset: 0x1478  Masked Cursor Foreground Color Register. The foreground color for Masked cursors. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |Blue value.
     * |[15:8]  |GREEN     |Green value.
     * |[23:16] |RED       |Red value.
     * @var DISP_T::DisplayIntr
     * Offset: 0x147C  Display Interrupt Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DISP0     |Display0 interrupt(read only)
     * @var DISP_T::DisplayIntrEnable
     * Offset: 0x1480  Display Interrupt Enable Register. The interrupt enable register for display_0. Note: Interrupt enable for register DisplayIntr.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DISP0     |Display0 interrupt enable (read only)
     * @var DISP_T::CursorModuleClockGatingControl
     * Offset: 0x1484  Clock Gating Control for Cursor Register. Module level clock gating control for cursor.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DISABLE_MODULE_CLOCK_GATING_CURSOR|Disable module clock gating cursor 0 => ENABLED 1 => DISABLED
     * @var DISP_T::GeneralConfig0
     * Offset: 0x14B0  General Miscellaneous Configuration Register. Misc option configuration. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |ENDIAN_CONTROL|Control endian swapping 0 => NO_SWAP 1 => SWAP_WORD 2 => SWAP_DWORD 3 => SWAP_DDWORD
     * |[2]     |STALL_OUTPUT_WHEN_UNDERFLOW|If enabled, when FIFO underflow happens, output is stalled 0 => DISABLED 1 => ENABLED
     * |[3]     |DISABLE_IDLE|Disable idle signal 0 => DISABLED 1 => ENABLED
     * @var DISP_T::DpiConfig0
     * Offset: 0x14B8  DPI Configuration Register. The configuration register for DPI output. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |DPI_DATA_FORMAT|DPI interface data format Refer to DPI spec 'Interface color coding' for details 0 => D16CFG1 1 => D16CFG2 2 => D16CFG3 3 => D18CFG1 4 => D18CFG2 5 => D24
     * @var DISP_T::DebugCounterSelect0
     * Offset: 0x14D0  Debug Counter Selection Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |SELECT    |Write a value to this field to pick up from 0~255 counters Then the counter will be on DebugCounterValue 00 => TOTAL_AXI_VIDEO_RD_REQ_CNT * video read request number * 01 => TOTAL_AXI_VIDEO_RD_LAST_CNT * video read return data last number * 02 => TOTAL_AXI_VIDEO_REQ_BURST_CNT * video number of 16 byte burst requests bytes * 03 => TOTAL_AXI_VIDEO_RD_BURST_CUNT * video number of 16 byte burst read return data * 04 => TOTAL_PIXEL_CNT * total pixels sent * 05 => TOTAL_FRAME_CNT * total frames sent * 06 => TOTAL_INPUT_DBI_CMD_CNT * total DBI input command * 07 => TOTAL_OUTPUT_DBI_CMD_CNT * total DBI output command * 08 => DEBUG_SIGNALS0 * debug signals * 09 => TOTAL_AXI_OVERLAY0_RD_REQ_CNT * overlay read request number * 0A => TOTAL_AXI_OVERLAY0_RD_LAST_CNT * overlay read return data last number * 0B => TOTAL_AXI_OVERLAY0_REQ_BURST_CNT * overlay number of 16 byte bursts of request bytes * 0C => TOTAL_AXI_OVERLAY0_RD_BURST_CUNT * overlay number of 16 bytes bursts of read return data * 0D => DEBUG_SIGNALS_FREE_POOL 0E => DEBUG_SIGNALS_INFOBUF_RD 0F => DEBUG_SIGNALS_INFOBUF_WR0 10 => DEBUG_SIGNALS_INFOBUF_WR1 11 => DEBUG_SIGNALS_INFOBUF_WR2 12 => DEBUG_SIGNALS_INFOBUF_WR3 13 => DEBUG_SIGNALS_OVERLAY0_FREE_POOL 14 => DEBUG_SIGNALS_OVERLAY0_INFOBUF_RD 15 => DEBUG_SIGNALS_OVERLAY0_INFOBUF_WR0 16 => DEBUG_SIGNALS_OVERLAY0_INFOBUF_WR1 17 => DEBUG_SIGNALS_OVERLAY0_INFOBUF_WR2 18 => DEBUG_SIGNALS_OVERLAY0_INFOBUF_WR3 19 => OVERLAY_BLEND_DEBUGSIGNALS 1A => CURSOR_BLEND_DEBUGSIGNALS 1C => VIDEO_WALKER_DEBUGSIGNALS_1 1D => VIDEO_WALKER_DEBUGSIGNALS_2 1E => VIDEO_WALKER_DEBUGSIGNALS_3 1F => OVERLAY_WALKER_DEBUGSIGNALS_1 20 => OVERLAY_WALKER_DEBUGSIGNALS_2 21 => OVERLAY_WALKER_DEBUGSIGNALS_3 FF => RESET_ALL_DEBUG_COUNTERS * Reset all debug counters *.
     * @var DISP_T::DebugCounterValue0
     * Offset: 0x14D8  Debug Counter Value Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VALUE     |Selected debug counter value
     * @var DISP_T::FrameBufferColorKey0
     * Offset: 0x1508  Framebuffer Color Key Start Address Register. Start of color key range of framebuffer. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::FrameBufferColorKeyHigh0
     * Offset: 0x1510  Framebuffer Color Key End Address Register. End of color key range of framebuffer. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::FrameBufferConfig0
     * Offset: 0x1518  Framebuffer Configuration Register. Framebuffer attribute configuration. Note: This register is double buffered. Some fields are double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |OUTPUT    |When Output is enabled, pixels will be displayed When Output is disabled, all pixels will be black This allows a panel to have the correct timing but without any pixels Note: This field is double buffered 0 => DISABLED 1 => ENABLED.
     * |[2]     |GAMMA     |When Gamma is enabled, the R, G, and B channels will be routed through the Gamma LUT to perform gamma correction Note: This field is double buffered 0 => DISABLED 1 => ENABLED.
     * |[3]     |VALID     |The valid field defines whether we can copy a new set of registers at the next VBLANK or not This ensures a frame will always start with a valid working set if this register is programmed last, which reduces the need for SW to wait for the start of a VBLANK signal in order to ensure all states are loaded before the next VBLANK 0 => WORKING 1 => PENDING.
     * |[4]     |RESET     |Enable reset for the display controller
     * |        |          |0: See below for DPI
     * |        |          |For DBI,this field should be 0
     * |        |          |1: RESET
     * |        |          |Enable DPI timing, start a DPI transfer
     * |        |          |Write 0 to this bit to reset the display controller, then configure the other registers and lastly write a 1 to this bit to let the display controller start
     * |        |          |When the display controller starts, it begins at VBLANK_START, and all registers get flopped to the working set at VSYNC_END
     * |        |          |Counters will be reset to the end of HSYNC and VSYNC
     * |        |          |(Refer the Timing Diagram provided in the Hardware Feature document)
     * |        |          |For DBI, do not write 1 to this field
     * |        |          |Use DbiReset DBI_IF_LEVEL_RESET instead
     * |        |          |This bit is WRITE ONLY.
     * |        |          |1 => RESET.
     * |[5]     |UNDERFLOW |0: NO 1: YES When the display FIFO underflows, this bit gets set to one Reading this register will reset it back to zero This field is READ ONLY 0 => NO 1 => YES.
     * |[6]     |FLIP_IN_PROGRESS|0: NO 1: YES When the framebuffer address gets written to, this bit gets set to one It will be reset to zero at the start of the next VBLANK when the registers gets copied into the working set This field is (READ ONLY) 0 => NO 1 => YES.
     * |[8]     |CLEAR     |When enabled, the pixel value of the framebuffer comes from FrameBufferClearValue; otherwise, the pixel value comes from memory 0 => DISABLED 1 => ENABLED
     * |[10:9]  |TRANSPARENCY|Transparency of framebuffer 0 => OPAQUE 1 => MASK 2 => KEY
     * |[16:14] |YUV       |YUV standard 1 => SELECT_709 * BT709 * 3 => SELECT_2020 * BT2020 *
     * |[24:23] |SWIZZLE   |0 => ARGB 1 => RGBA 2 => ABGR 3 => BGRA
     * |[25]    |UV_SWIZZLE|UV swizzle type
     * |[31:26] |FORMAT    |The format of the framebuffer 00 => X4R4G4B4 01 => A4R4G4B4 02 => X1R5G5B5 03 => A1R5G5B5 04 => R5G6B5 05 => X8R8G8B8 06 => A8R8G8B8 07 => YUY2 08 => UYVY 09 => INDEX8 0A => MONOCHROME 0F => YV12 10 => A8 11 => NV12 12 => NV16 13 => RG16 14 => R8 15 => NV12_10BIT 16 => A2R10G10B10 17 => NV16_10BIT 18 => INDEX1 19 => INDEX2 1A => INDEX4 1B => P010 1C => NV12_10BIT_L1 1D => NV16_10BIT_L1
     * @var DISP_T::FrameBufferBGColor0
     * Offset: 0x1528  Framebuffer Background Color Register. Background color used when a pixel from the framebuffer falls outside of the range of color key.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::FrameBufferUPlanarAddress0
     * Offset: 0x1530  Framebuffer Second Plane U Start Address Register. Starting address of the second planar (often the U plane) of the framebuffer if one exists.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[30:0]  |ADDRESS   |Framebuffer Second Plane U Start Address
     * |[31]    |TYPE      |0 => SYSTEM 1 => VIRTUAL_SYSTEM
     * @var DISP_T::FrameBufferVPlanarAddress0
     * Offset: 0x1538  Framebuffer Third Plane V Start Address Register. Starting address of the third planar (often the V plane) of the framebuffer if one exists. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[30:0]  |ADDRESS   |Framebuffer Third Plane V Start Address
     * |[31]    |TYPE      |0 => SYSTEM 1 => VIRTUAL_SYSTEM
     * @var DISP_T::OverlayConfig0
     * Offset: 0x1540  Overlay Configuration Register. Overlay attributes control. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |TRANSPARENCY|Transparency of the overlay 0 => OPAQUE 1 => MASK 2 => KEY
     * |[7:5]   |YUV       |YUV standard
     * |        |          |1 => SELECT_709 * BT709 * 3 => SELECT_2020 * BT2020 *.
     * |[14:13] |SWIZZLE   |0 => ARGB 1 => RGBA 2 => ABGR 3 => BGRA
     * |[15]    |UV_SWIZZLE|UV swizzle type.
     * |[21:16] |FORMAT    |The format of the overlay
     * |        |          |00 => X4R4G4B4 01 => A4R4G4B4 02 => X1R5G5B5 03 => A1R5G5B5 04 => R5G6B5 05 => X8R8G8B8 06 => A8R8G8B8 07 => YUY2 08 => UYVY 09 => INDEX8 0A => MONOCHROME 0F => YV12 10 => A8 11 => NV12 12 => NV16 13 => RG16 14 => R8 15 => NV12_10BIT 16 => A2R10G10B10 17 => NV16_10BIT 18 => INDEX1 19 => INDEX2 1A => INDEX4 1B => P010 1C => NV12_10BIT_L1 1D => NV16_10BIT_L1.
     * |[23]    |UNDERFLOW |When the overlay FIFO underflows, this bit gets set to one Reading this register will reset it back to zero 0 => NO 1 => YES.
     * |[24]    |ENABLE    |Enable this overlay layer 0 => DISABLE 1 => ENABLE
     * |[25]    |CLEAR     |When enabled, the pixel value of the overlay comes from OverlayClearValue; otherwise the pixel value comes from memory 0 => DISABLED 1 => ENABLED
     * @var DISP_T::OverlayAlphaBlendConfig0
     * Offset: 0x1580  Overlay Alpha Blending Configuration Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SRC_ALPHA_MODE|0 => NORMAL 1 => INVERSED
     * |[1]     |DISABLE_ALPHA_BLEND|0 => DISABLED 1 => ENABLED
     * |[4:3]   |SRC_GLOBAL_ALPHA_MODE|0 => NORMAL 1 => GLOBAL 2 => SCALED
     * |[7:5]   |SRC_BLENDING_MODE|0 => ZERO 1 => ONE 2 => NORMAL 3 => INVERSED 4 => COLOR 5 => COLOR_INVERSED 6 => SATURATED_ALPHA 7 => SATURATED_DEST_ALPHA
     * |[8]     |SRC_ALPHA_FACTOR|Src Blending factor is calculated from Src alpha 0 => DISABLED 1 => ENABLED
     * |[9]     |DST_ALPHA_MODE|0 => NORMAL 1 => INVERSED
     * |[11:10] |DST_GLOBAL_ALPHA_MODE|0 => NORMAL 1 => GLOBAL 2 => SCALED
     * |[14:12] |DST_BLENDING_MODE|0 => ZERO 1 => ONE 2 => NORMAL 3 => INVERSED 4 => COLOR 5 => COLOR_INVERSED 6 => SATURATED_ALPHA 7 => SATURATED_DEST_ALPHA
     * |[15]    |DST_ALPHA_FACTOR|Dst Blending factor is calculated from Dst alpha 0 => DISABLED 1 => ENABLED
     * @var DISP_T::OverlayAddress0
     * Offset: 0x15C0  Overlay Start Address Register. Starting address of the overlay. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[30:0]  |ADDRESS   |Overlay Start Address
     * |[31]    |TYPE      |0 => SYSTEM 1 => VIRTUAL_SYSTEM
     * @var DISP_T::OverlayStride0
     * Offset: 0x1600  Overlay Stride Register. Stride of the overlay in bytes. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[16:0]  |STRIDE    |Number of bytes from the start of one line to next line.
     * @var DISP_T::OverlayTL0
     * Offset: 0x1640  Overlay Origin Register. Top left coordinate of the panel pixel where the overlay should start. Be aware there is no panning inside the overlay. Note: This register is double buffered
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |X         |Left boundary of overlay window.
     * |[29:15] |Y         |Top boundary of overlay window.
     * @var DISP_T::OverlayBR0
     * Offset: 0x1680  Overlay End Register. Bottom right coordinate of the panel pixel where the overlay should end. The border is inclusive. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |X         |Right boundary of overlay.
     * |[29:15] |Y         |Bottom boundary of overlay.
     * @var DISP_T::OverlaySrcGlobalColor0
     * Offset: 0x16C0  Overlay Source Global Color Register. Color value used when alpha blending process is configured to use global color for source. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::OverlayDstGlobalColor0
     * Offset: 0x1700  Overlay Destination Global Color Register. Color value used when alpha blending process is configured to use global color for destination. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::OverlayColorKey0
     * Offset: 0x1740  Overlay Color Key Start Address Register. Start of color key range for overlay. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::OverlayColorKeyHigh0
     * Offset: 0x1780  Overlay Color Key End Address Register. End of color key range for overlay. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::OverlaySize0
     * Offset: 0x17C0  Overlay Window Size Register. Window size of the overlay buffer in memory - in pixels. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |WIDTH     |Overlay width
     * |[29:15] |HEIGHT    |Overlay height
     * @var DISP_T::FrameBufferUStride0
     * Offset: 0x1800  Framebuffer Second Plane U Stride Register. Stride of the second planar (often the U plane) of the framebuffer if one exists. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[16:0]  |STRIDE    |Number of bytes from the start of one line to next line.
     * @var DISP_T::FrameBufferVStride0
     * Offset: 0x1808  Framebuffer Third Plane V Stride Register. Stride of the third planar (often the V plane) of the framebuffer if one exists. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[16:0]  |STRIDE    |Number of bytes from the start of one line to next line.
     * @var DISP_T::FrameBufferSize0
     * Offset: 0x1810  Framebuffer Size Register. Window size of the framebuffer in memory - in pixels. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[14:0]  |WIDTH     |Frame width
     * |[29:15] |HEIGHT    |Frame height
     * @var DISP_T::IndexColorTableIndex0
     * Offset: 0x1818  Index Color Table Index Register. Index into index color table. See IndexColorTableData for more information.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |INDEX     |index into index color table.
     * @var DISP_T::IndexColorTableData0
     * Offset: 0x1820  Index Color Table Data Translation Register. Translation values for the index color table. When this register gets written, the data gets stored in the index color table at the index specified by the IndexColorTableIndex register. After the register is written, the index gets incremented. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::OverlayUPlanarAddress0
     * Offset: 0x1840  Overlay Second Plane U Start Address Register. Address of the second planar (often U plane) of the overlay if one exists. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[30:0]  |ADDRESS   |Overlay Third Plane V Start Address
     * |[31]    |TYPE      |0 => SYSTEM 1 => VIRTUAL_SYSTEM
     * @var DISP_T::OverlayVPlanarAddress0
     * Offset: 0x1880  Overlay Third Plane V Start Address Register. Address of the third planar (often V plane) of the overlay if one exists. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[30:0]  |ADDRESS   |Overlay Second Plane U Stride
     * |[31]    |TYPE      |0 => SYSTEM 1 => VIRTUAL_SYSTEM
     * @var DISP_T::OverlayUStride0
     * Offset: 0x18C0  Overlay Second Plane U Stride Register. Stride of the second planar of the overlay if one exists. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[16:0]  |STRIDE    |Number of bytes from the start of one line to next line.
     * @var DISP_T::OverlayVStride0
     * Offset: 0x1900  Overlay Third Plane V Stride Register. Stride of the third planar of the overlay if one exists. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[16:0]  |STRIDE    |Number of bytes from start of one line to next line.
     * @var DISP_T::OverlayClearValue0
     * Offset: 0x1940  Overlay Clear Value Register. Clear value used when OverlayConfig.Clear is enabled. Format is A8R8G8B8. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::OverlayIndexColorTableIndex0
     * Offset: 0x1980  Overlay Index Color Table Index Register. Index into overlay index color table. See OverlayIndexColorTableData for more information.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |INDEX     |Index into index color table.
     * @var DISP_T::OverlayIndexColorTableData0
     * Offset: 0x19C0  Index Color Table Data Translation Register. Translation values for the index color table of the overlay. When this register gets written, the data gets stored in the index color table at the index specified by the OverlayIndexColorTableIndex register. After the register is written, the index gets incremented. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::FrameBufferClearValue0
     * Offset: 0x1A18  Framebuffer Clear Value Register. Clear value used when FrameBufferConfig. Clear is enabled, format is A8R8G8B8. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |BLUE      |BLUE value
     * |[15:8]  |GREEN     |GREEN value
     * |[23:16] |RED       |RED value
     * |[31:24] |ALPHA     |ALPHA value
     * @var DISP_T::ModuleClockGatingControl0
     * Offset: 0x1A28  Clock Gating Module Control Register. Module level clock gating control for video and overlay.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DISABLE_MODULE_CLOCK_GATING_VIDEO|Disable module clock gating video 0 => ENABLE 1 => DISABLE.
     * |[1]     |DISABLE_MODULE_CLOCK_GATING_OVERLAY0|Disable module clock gating overlay0 0 => ENABLE 1 => DISABLE.
     * |[9]     |DISABLE_MODULE_CLOCK_GATING_WB_FIFO|Disable module clock gating WBFifo 0 => ENABLE 1 => DISABLE.
     * @var DISP_T::LatencyCounter0
     * Offset: 0x1A30  Latency Counter Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |COUNTER   |Latency counter value which is used to judge whether latency is low or high.
     * @var DISP_T::Qos0
     * Offset: 0x1A38  Quality of Service Latency Value Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |LOW       |If latency low, will send low value.
     * |[7:4]   |HIGH      |If latency high, will send high value.
     * @var DISP_T::MpuIntfCmd0
     * Offset: 0x1C40  MPU Command Configuration Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |REG_DATA  |Register address or register configured parameter.
     * |[26:24] |READ_COUNT|0 is invalid value, one read operation returns 1 data at least, Max value is 5 It is designed to prepare 5 registers to save returned data.
     * |[29]    |START     |HW generates a pulse while writing 1 to this field, then HW starts to send display data to the LCD.
     * |[31:30] |CMD       |0: Not a valid command, HW ignores the CMD/REGDATA/READCOUNT field Usage: only want to trigger HW, don't configure other fields 1: Write register by MPU interface 2: Write register parameter by MPU interface 3: Read register by MPU interface.
     * @var DISP_T::MpuIntfReadPara00
     * Offset: 0x1C48  MPU Read Parameter0 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |DATA      |Read register returned parameter0.
     * @var DISP_T::MpuIntfReadPara10
     * Offset: 0x1C50  MPU Read Parameter1 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |DATA      |Read register returned parameter1.
     * @var DISP_T::MpuIntfReadPara20
     * Offset: 0x1C58  MPU Read Parameter2 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |DATA      |Read register returned parameter2.
     * @var DISP_T::MpuIntfReadPara30
     * Offset: 0x1C60  MPU Read Parameter3 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |DATA      |Read register returned parameter3.
     * @var DISP_T::MpuIntfReadPara40
     * Offset: 0x1C68  MPU Read Parameter4 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |DATA      |Read register returned parameter4.
     * @var DISP_T::MpuIntfReadStatus0
     * Offset: 0x1C70  MPU Read Parameter Status Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DATA      |Returned parameter readiness
     * |        |          |0 = UNREADY
     * |        |          |The returned parameters of all read registers are not ready
     * |        |          |1 = READY
     * |        |          |The returned parameters of all read registers are ready.
     * @var DISP_T::MpuIntfConfig0
     * Offset: 0x1C78  MPU Interface Configuration Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REGISTER_MODE|0: 8 bit register mode, only MpuIntfCmd[7:0] are valid Only send 8 bits valid data each time to LCD by MPU Interface 1: 16 bit register mode, only MpuIntfCmd[15:0] are valid, Only send 16 bits valid data each time to the LCD by MPU Interface 0 = MODE_8_BIT 1 = MODE_16_BIT
     * |[2:1]   |DATA_BUS_WIDTH|MPU interface bus width 0 = WIDTH_8_BIT 1 = WIDTH_9_BIT 2 = WIDTH_16_BIT 3 = WIDTH_18_BIT
     * |[3]     |DATA_BUS_MODE|0 = MODE0. Mode0: 8-bit:DB[7:0]; 9-bit:DB[8:0]; 16-bit:DB[15:0]; 18-bit:DB[17:0], 1 = MODE1. Mode1: 8-bit:DB[17:10]; 9-bit:DB[17:9]; 16-bit:{DB[17:10],DB[8:1]}; 18-bit:DB[17:0].
     * |[4]     |INTERFACE_MODE|System Interface.
     * |[5]     |ENABLE_VSYNC|0: Disable; 1: Enable VSYNC interface 0 = DISABLE 1 = ENABLE
     * |[6]     |VSYNC_POLARITY|VSYNC signal is negative or positive value 0 = NEGATIVE 1 = POSITIVE
     * |[7]     |ENABLE_TE |0: Disable; 1: Enable TE interface 0 = DISABLE 1 = ENABLE
     * |[8]     |TE_POLARITY|TE signal is positive or negative value 0 = POSITIVE 1 = NEGATIVE
     * |[9]     |DCX_POLARITY|DCX polarity for command and data 0 = MODE0. 0-command, 1-data 1 = MODE1. 1-command, 0-data.
     * |[10]    |DATA_MODE24_BIT|16 bit data bus, 24 bit data output 0 = MODE0. 0: 2 pixels per 3 transfers 1 = MODE1. 1: 1 pixel per 2 transfers.
     * |[11]    |INTERFACE_RESET|Write 1 to this field, HW will reset the MPU interface.
     * |[12]    |ENABLE_MPU_INTF|O:Disable; 1: Enable MPU interface 0 = DISABLE 1 = ENABLE
     * @var DISP_T::MpuIntfFrame0
     * Offset: 0x1C80  MPU Frame Configuration Register. Note: This register is double buffered.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FRAME_UPDATE|0: When using VSync interface/TE mode, if this bit is 0, this frame data won't be updated 1: When using VSync interface/TE mode, if this bit is 1, this frame data will be updated 0 => NO 1 => YES.
     * |[2:1]   |DATA_FORMAT|0: 16 bit format R5G6B5 1: 18 bit format R6G6B6 2: 24 bit format R8G8B8. 3: Reserved 0 => R5G6B5 1 => R6G6B6 2 => R8G8B8
     * |[3]     |MPU_WRITE_BACK|0: Disable MPU data write back 1: Enable MPU interface data write back 0 => DISABLE 1 => ENABLE.
     * @var DISP_T::MpuIntfACWrI800
     * Offset: 0x1C88  MPU Write AC Characteristics I80 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |WR_PERIOD_I80|I80 system write period cycle number Minimum number is 3 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[19:10] |WRX_ASSERT|I80 system WRX assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[29:20] |WRX_DE_ASSERT|I80 system WRX de-assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock
     * @var DISP_T::MpuIntfACRdI800
     * Offset: 0x1C90  MPU Read AC Characteristics I80 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |RD_PERIOD_I80|I80 system read period cycle number Minimum number is 3 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[19:10] |RDX_ASSERT|I80 system RDX assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[29:20] |RDX_DE_ASSERT|I80 system RDX de-assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * @var DISP_T::MpuIntfACWrM680
     * Offset: 0x1C98  MPU Write AC Characteristics M68 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |WR_PERIOD_M68|M68 system write period cycle number Minimum number is 3 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[19:10] |WR_EASSERT|M68 system write E assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[29:20] |WR_EDE_ASSERT|M68 system write E de-assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * @var DISP_T::MpuIntfACRdM680
     * Offset: 0x1CA0  MPU Read AC Characteristics M68 Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |RD_PERIOD_I80|M68 system read period cycle number Minimum number is 3 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[19:10] |RDX_ASSERT|M68 system RDX assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * |[29:20] |RDX_DE_ASSERT|M68 system RDX de-assert cycle number Minimum number is 1 Default number is 0, 0 means 1024 cycle number Cycle unit is pixel clock.
     * @var DISP_T::MpuIntfACVsyncCSX0
     * Offset: 0x1CA8  MPU CSX Assert Register.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |CSX_ASSERT|Add delay between VSYNC-high and CSX- low This field specifies how many transfer-one-pixel period.
     */
    __IO uint32_t AQHiClockControl;      /*!< [0x0000] Clock Control Register                                           */
    __I  uint32_t RESERVE0[1279];
    __IO uint32_t FrameBufferAddress0;   /*!< [0x1400] Framebuffer Start Address Register. Starting address of the framebuffer. Note: This register is double buffered. */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t FrameBufferStride0; /*!< [0x1408] Framebuffer Stride Register. Stride of the framebuffer in bytes. Note: This register is double buffered. */
    __I  uint32_t RESERVE2[1];
    __IO uint32_t DisplayDitherConfig0; /*!< [0x1410] Display Dither Configuration Register. Configuration register for dithering. Note: This register is double buffered. */
    __I  uint32_t RESERVE3[1];
    __IO uint32_t PanelConfig0;     /*!< [0x1418] Panel Configuration Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE4[1];
    __IO uint32_t DisplayDitherTableLow0; /*!< [0x1420] Display Dither Table Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE5[1];
    __IO uint32_t DisplayDitherTableHigh0; /*!< [0x1428] Display Dither Table Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE6[1];
    __IO uint32_t HDisplay0;        /*!< [0x1430] Horizontal Total and Display End Counter Register. Note: This register is double buffered */
    __I  uint32_t RESERVE7[1];
    __IO uint32_t HSync0;           /*!< [0x1438] Horizontal Sync Counter Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE8[1];
    __IO uint32_t VDisplay0;        /*!< [0x1440] Vertical Total and Display End Counter Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE9[1];
    __IO uint32_t VSync0;           /*!< [0x1448] Vertical Sync Counter Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE10[1];
    __I  uint32_t DisplayCurrentLocation0; /*!< [0x1450] Display Current Location Register. Current x,y location of display controller. */
    __I  uint32_t RESERVE11[1];
    __O  uint32_t GammaIndex0;      /*!< [0x1458] Gamma Table Index Register. Index into gamma table. See GammaData for more information. */
    __I  uint32_t RESERVE12[1];
    __O  uint32_t GammaData0;       /*!< [0x1460] Gamma Data Translation Register. Translation values for the gamma table. When this register gets written, the data gets stored in the gamma table at the index specified by the GammaIndex register. After the register is written, the index gets incremented. */
    __I  uint32_t RESERVE13[1];
    __IO uint32_t CursorConfig;     /*!< [0x1468] Cursor Configuration Register.                                   */
    __IO uint32_t CursorAddress;    /*!< [0x146c] Cursor Address Register. Address of the cursor shape. Note: This register is double buffered. */
    __IO uint32_t CursorLocation;   /*!< [0x1470] Cursor Location Register. Location of the cursor on the owning display. Note: This register is double buffered. */
    __IO uint32_t CursorBackground; /*!< [0x1474] Masked Cursor Background Color Register. The background color for Masked cursors. Note: This register is double buffered. */
    __IO uint32_t CursorForeground; /*!< [0x1478] Masked Cursor Foreground Color Register. The foreground color for Masked cursors. Note: This register is double buffered. */
    __I  uint32_t DisplayIntr;      /*!< [0x147c] Display Interrupt Register                                       */
    __IO uint32_t DisplayIntrEnable; /*!< [0x1480] Display Interrupt Enable Register. The interrupt enable register for display_0. Note: Interrupt enable for register DisplayIntr. */
    __IO uint32_t CursorModuleClockGatingControl; /*!< [0x1484] Clock Gating Control for Cursor Register. Module level clock gating control for cursor. */
    __IO uint32_t DbiConfig0;       /*!< [0x1488] Wayne Undertable register */
    __I  uint32_t RESERVE14[9];
    __IO uint32_t GeneralConfig0;   /*!< [0x14b0] General Miscellaneous Configuration Register. Misc option configuration. Note: This register is double buffered. */
    __I  uint32_t RESERVE15[1];
    __IO uint32_t DpiConfig0;       /*!< [0x14b8] DPI Configuration Register. The configuration register for DPI output. Note: This register is double buffered. */
    __I  uint32_t RESERVE16[5];
    __IO uint32_t DebugCounterSelect0; /*!< [0x14d0] Debug Counter Selection Register.                                */
    __I  uint32_t RESERVE17[1];
    __I  uint32_t DebugCounterValue0; /*!< [0x14d8] Debug Counter Value Register                                     */
    __I  uint32_t RESERVE18[11];
    __IO uint32_t FrameBufferColorKey0; /*!< [0x1508] Framebuffer Color Key Start Address Register. Start of color key range of framebuffer. Note: This register is double buffered. */
    __I  uint32_t RESERVE19[1];
    __IO uint32_t FrameBufferColorKeyHigh0; /*!< [0x1510] Framebuffer Color Key End Address Register. End of color key range of framebuffer. Note: This register is double buffered. */
    __I  uint32_t RESERVE20[1];
    __IO uint32_t FrameBufferConfig0; /*!< [0x1518] Framebuffer Configuration Register. Framebuffer attribute configuration. Note: This register is double buffered. Some fields are double buffered. */
    __I  uint32_t RESERVE21[3];
    __IO uint32_t FrameBufferBGColor0; /*!< [0x1528] Framebuffer Background Color Register. Background color used when a pixel from the framebuffer falls outside of the range of color key. */
    __I  uint32_t RESERVE22[1];
    __IO uint32_t FrameBufferUPlanarAddress0; /*!< [0x1530] Framebuffer Second Plane U Start Address Register. Starting address of the second planar (often the U plane) of the framebuffer if one exists. */
    __I  uint32_t RESERVE23[1];
    __IO uint32_t FrameBufferVPlanarAddress0; /*!< [0x1538] Framebuffer Third Plane V Start Address Register. Starting address of the third planar (often the V plane) of the framebuffer if one exists. Note: This register is double buffered. */
    __I  uint32_t RESERVE24[1];
    __IO uint32_t OverlayConfig0;   /*!< [0x1540] Overlay Configuration Register. Overlay attributes control. Note: This register is double buffered. */
    __I  uint32_t RESERVE25[15];
    __IO uint32_t OverlayAlphaBlendConfig0; /*!< [0x1580] Overlay Alpha Blending Configuration Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE26[15];
    __IO uint32_t OverlayAddress0;  /*!< [0x15c0] Overlay Start Address Register. Starting address of the overlay. Note: This register is double buffered. */
    __I  uint32_t RESERVE27[15];
    __IO uint32_t OverlayStride0;   /*!< [0x1600] Overlay Stride Register. Stride of the overlay in bytes. Note: This register is double buffered. */
    __I  uint32_t RESERVE28[15];
    __IO uint32_t OverlayTL0;       /*!< [0x1640] Overlay Origin Register. Top left coordinate of the panel pixel where the overlay should start. Be aware there is no panning inside the overlay. Note: This register is double buffered */
    __I  uint32_t RESERVE29[15];
    __IO uint32_t OverlayBR0;       /*!< [0x1680] Overlay End Register. Bottom right coordinate of the panel pixel where the overlay should end. The border is inclusive. Note: This register is double buffered. */
    __I  uint32_t RESERVE30[15];
    __IO uint32_t OverlaySrcGlobalColor0; /*!< [0x16c0] Overlay Source Global Color Register. Color value used when alpha blending process is configured to use global color for source. Note: This register is double buffered. */
    __I  uint32_t RESERVE31[15];
    __IO uint32_t OverlayDstGlobalColor0; /*!< [0x1700] Overlay Destination Global Color Register. Color value used when alpha blending process is configured to use global color for destination. Note: This register is double buffered. */
    __I  uint32_t RESERVE32[15];
    __IO uint32_t OverlayColorKey0; /*!< [0x1740] Overlay Color Key Start Address Register. Start of color key range for overlay. Note: This register is double buffered. */
    __I  uint32_t RESERVE33[15];
    __IO uint32_t OverlayColorKeyHigh0; /*!< [0x1780] Overlay Color Key End Address Register. End of color key range for overlay. Note: This register is double buffered. */
    __I  uint32_t RESERVE34[15];
    __IO uint32_t OverlaySize0;     /*!< [0x17c0] Overlay Window Size Register. Window size of the overlay buffer in memory - in pixels. Note: This register is double buffered. */
    __I  uint32_t RESERVE35[15];
    __IO uint32_t FrameBufferUStride0; /*!< [0x1800] Framebuffer Second Plane U Stride Register. Stride of the second planar (often the U plane) of the framebuffer if one exists. Note: This register is double buffered. */
    __I  uint32_t RESERVE36[1];
    __IO uint32_t FrameBufferVStride0; /*!< [0x1808] Framebuffer Third Plane V Stride Register. Stride of the third planar (often the V plane) of the framebuffer if one exists. Note: This register is double buffered. */
    __I  uint32_t RESERVE37[1];
    __IO uint32_t FrameBufferSize0; /*!< [0x1810] Framebuffer Size Register. Window size of the framebuffer in memory - in pixels. Note: This register is double buffered. */
    __I  uint32_t RESERVE38[1];
    __O  uint32_t IndexColorTableIndex0; /*!< [0x1818] Index Color Table Index Register. Index into index color table. See IndexColorTableData for more information. */
    __I  uint32_t RESERVE39[1];
    __O  uint32_t IndexColorTableData0; /*!< [0x1820] Index Color Table Data Translation Register. Translation values for the index color table. When this register gets written, the data gets stored in the index color table at the index specified by the IndexColorTableIndex register. After the register is written, the index gets incremented. Note: This register is double buffered. */
    __I  uint32_t RESERVE40[7];
    __IO uint32_t OverlayUPlanarAddress0; /*!< [0x1840] Overlay Second Plane U Start Address Register. Address of the second planar (often U plane) of the overlay if one exists. Note: This register is double buffered. */
    __I  uint32_t RESERVE41[15];
    __IO uint32_t OverlayVPlanarAddress0; /*!< [0x1880] Overlay Third Plane V Start Address Register. Address of the third planar (often V plane) of the overlay if one exists. Note: This register is double buffered. */
    __I  uint32_t RESERVE42[15];
    __IO uint32_t OverlayUStride0;  /*!< [0x18c0] Overlay Second Plane U Stride Register. Stride of the second planar of the overlay if one exists. Note: This register is double buffered. */
    __I  uint32_t RESERVE43[15];
    __IO uint32_t OverlayVStride0;  /*!< [0x1900] Overlay Third Plane V Stride Register. Stride of the third planar of the overlay if one exists. Note: This register is double buffered. */
    __I  uint32_t RESERVE44[15];
    __IO uint32_t OverlayClearValue0; /*!< [0x1940] Overlay Clear Value Register. Clear value used when OverlayConfig.Clear is enabled. Format is A8R8G8B8. Note: This register is double buffered. */
    __I  uint32_t RESERVE45[15];
    __O  uint32_t OverlayIndexColorTableIndex0; /*!< [0x1980] Overlay Index Color Table Index Register. Index into overlay index color table. See OverlayIndexColorTableData for more information. */
    __I  uint32_t RESERVE46[15];
    __O  uint32_t OverlayIndexColorTableData0; /*!< [0x19c0] Index Color Table Data Translation Register. Translation values for the index color table of the overlay. When this register gets written, the data gets stored in the index color table at the index specified by the OverlayIndexColorTableIndex register. After the register is written, the index gets incremented. Note: This register is double buffered. */
    __I  uint32_t RESERVE47[21];
    __IO uint32_t FrameBufferClearValue0; /*!< [0x1a18] Framebuffer Clear Value Register. Clear value used when FrameBufferConfig. Clear is enabled, format is A8R8G8B8. Note: This register is double buffered. */
    __I  uint32_t RESERVE48[3];
    __IO uint32_t ModuleClockGatingControl0; /*!< [0x1a28] Clock Gating Module Control Register. Module level clock gating control for video and overlay. */
    __I  uint32_t RESERVE49[1];
    __IO uint32_t LatencyCounter0;  /*!< [0x1a30] Latency Counter Register.                                        */
    __I  uint32_t RESERVE50[1];
    __IO uint32_t Qos0;             /*!< [0x1a38] Quality of Service Latency Value Register.                       */
    __I  uint32_t RESERVE51[129];
    __IO uint32_t MpuIntfCmd0;      /*!< [0x1c40] MPU Command Configuration Register.                              */
    __I  uint32_t RESERVE52[1];
    __I  uint32_t MpuIntfReadPara00; /*!< [0x1c48] MPU Read Parameter0 Register.                                    */
    __I  uint32_t RESERVE53[1];
    __I  uint32_t MpuIntfReadPara10; /*!< [0x1c50] MPU Read Parameter1 Register.                                    */
    __I  uint32_t RESERVE54[1];
    __I  uint32_t MpuIntfReadPara20; /*!< [0x1c58] MPU Read Parameter2 Register.                                    */
    __I  uint32_t RESERVE55[1];
    __I  uint32_t MpuIntfReadPara30; /*!< [0x1c60] MPU Read Parameter3 Register.                                    */
    __I  uint32_t RESERVE56[1];
    __I  uint32_t MpuIntfReadPara40; /*!< [0x1c68] MPU Read Parameter4 Register.                                    */
    __I  uint32_t RESERVE57[1];
    __I  uint32_t MpuIntfReadStatus0; /*!< [0x1c70] MPU Read Parameter Status Register.                              */
    __I  uint32_t RESERVE58[1];
    __IO uint32_t MpuIntfConfig0;   /*!< [0x1c78] MPU Interface Configuration Register.                            */
    __I  uint32_t RESERVE59[1];
    __IO uint32_t MpuIntfFrame0;    /*!< [0x1c80] MPU Frame Configuration Register. Note: This register is double buffered. */
    __I  uint32_t RESERVE60[1];
    __IO uint32_t MpuIntfACWrI800;  /*!< [0x1c88] MPU Write AC Characteristics I80 Register.                       */
    __I  uint32_t RESERVE61[1];
    __IO uint32_t MpuIntfACRdI800;  /*!< [0x1c90] MPU Read AC Characteristics I80 Register.                        */
    __I  uint32_t RESERVE62[1];
    __IO uint32_t MpuIntfACWrM680;  /*!< [0x1c98] MPU Write AC Characteristics M68 Register.                       */
    __I  uint32_t RESERVE63[1];
    __IO uint32_t MpuIntfACRdM680;  /*!< [0x1ca0] MPU Read AC Characteristics M68 Register.                        */
    __I  uint32_t RESERVE64[1];
    __IO uint32_t MpuIntfACVsyncCSX0; /*!< [0x1ca8] MPU CSX Assert Register.                                         */

} DISP_T;

/**
    @addtogroup DISP_CONST DISP Bit Field Definition
    Constant Definitions for DISP Controller
@{ */

#define DISP_AQHiClockControl_CLKDC_DIS_Pos (1)                                            /*!< DISP_T::AQHiClockControl: CLKDC_DIS Position*/
#define DISP_AQHiClockControl_CLKDC_DIS_Msk (0x1ul << DISP_AQHiClockControl_CLKDC_DIS_Pos) /*!< DISP_T::AQHiClockControl: CLKDC_DIS Mask*/

#define DISP_AQHiClockControl_FSCALE_VAL_Pos (2)                                           /*!< DISP_T::AQHiClockControl: FSCALE_VAL Position*/
#define DISP_AQHiClockControl_FSCALE_VAL_Msk (0x7ful << DISP_AQHiClockControl_FSCALE_VAL_Pos) /*!< DISP_T::AQHiClockControl: FSCALE_VAL Mask*/

#define DISP_AQHiClockControl_FSCALE_CMD_LOAD_Pos (9)                                      /*!< DISP_T::AQHiClockControl: FSCALE_CMD_LOAD Position*/
#define DISP_AQHiClockControl_FSCALE_CMD_LOAD_Msk (0x1ul << DISP_AQHiClockControl_FSCALE_CMD_LOAD_Pos) /*!< DISP_T::AQHiClockControl: FSCALE_CMD_LOAD Mask*/

#define DISP_AQHiClockControl_DISABLE_RAM_CLOCK_GATING_Pos (10)                            /*!< DISP_T::AQHiClockControl: DISABLE_RAM_CLOCK_GATING Position*/
#define DISP_AQHiClockControl_DISABLE_RAM_CLOCK_GATING_Msk (0x1ul << DISP_AQHiClockControl_DISABLE_RAM_CLOCK_GATING_Pos) /*!< DISP_T::AQHiClockControl: DISABLE_RAM_CLOCK_GATING Mask*/

#define DISP_AQHiClockControl_DISABLE_DEBUG_REGISTERS_Pos (11)                             /*!< DISP_T::AQHiClockControl: DISABLE_DEBUG_REGISTERS Position*/
#define DISP_AQHiClockControl_DISABLE_DEBUG_REGISTERS_Msk (0x1ul << DISP_AQHiClockControl_DISABLE_DEBUG_REGISTERS_Pos) /*!< DISP_T::AQHiClockControl: DISABLE_DEBUG_REGISTERS Mask*/

#define DISP_AQHiClockControl_SOFT_RESET_Pos (12)                                          /*!< DISP_T::AQHiClockControl: SOFT_RESET Position*/
#define DISP_AQHiClockControl_SOFT_RESET_Msk (0x1ul << DISP_AQHiClockControl_SOFT_RESET_Pos) /*!< DISP_T::AQHiClockControl: SOFT_RESET Mask*/

#define DISP_AQHiClockControl_DISABLE_RAM_POWER_OPTIMIZATION_Pos (13)                      /*!< DISP_T::AQHiClockControl: DISABLE_RAM_POWER_OPTIMIZATION Position*/
#define DISP_AQHiClockControl_DISABLE_RAM_POWER_OPTIMIZATION_Msk (0x1ul << DISP_AQHiClockControl_DISABLE_RAM_POWER_OPTIMIZATION_Pos) /*!< DISP_T::AQHiClockControl: DISABLE_RAM_POWER_OPTIMIZATION Mask*/

#define DISP_FrameBufferAddress0_ADDRESS_Pos (0)                                      /*!< DISP_T::FrameBufferAddress0: ADDRESS Position*/
#define DISP_FrameBufferAddress0_ADDRESS_Msk (0x7ffffffful << DISP_FrameBufferAddress0_ADDRESS_Pos) /*!< DISP_T::FrameBufferAddress0: ADDRESS Mask*/

#define DISP_FrameBufferAddress0_TYPE_Pos (31)                                        /*!< DISP_T::FrameBufferAddress0: TYPE Position*/
#define DISP_FrameBufferAddress0_TYPE_Msk (0x1ul << DISP_FrameBufferAddress0_TYPE_Pos) /*!< DISP_T::FrameBufferAddress0: TYPE Mask*/

#define DISP_FrameBufferStride0_STRIDE_Pos (0)                                        /*!< DISP_T::FrameBufferStride0: STRIDE Position*/
#define DISP_FrameBufferStride0_STRIDE_Msk (0x1fffful << DISP_FrameBufferStride0_STRIDE_Pos) /*!< DISP_T::FrameBufferStride0: STRIDE Mask*/

#define DISP_DisplayDitherConfig0_ENABLE_Pos (31)                                     /*!< DISP_T::DisplayDitherConfig0: ENABLE Position*/
#define DISP_DisplayDitherConfig0_ENABLE_Msk (0x1ul << DISP_DisplayDitherConfig0_ENABLE_Pos) /*!< DISP_T::DisplayDitherConfig0: ENABLE Mask*/

#define DISP_PanelConfig0_DE_Pos    (0)                                               /*!< DISP_T::PanelConfig0: DE Position */
#define DISP_PanelConfig0_DE_Msk    (0x1ul << DISP_PanelConfig0_DE_Pos)          /*!< DISP_T::PanelConfig0: DE Mask     */

#define DISP_PanelConfig0_DE_POLARITY_Pos (1)                                         /*!< DISP_T::PanelConfig0: DE_POLARITY Position*/
#define DISP_PanelConfig0_DE_POLARITY_Msk (0x1ul << DISP_PanelConfig0_DE_POLARITY_Pos) /*!< DISP_T::PanelConfig0: DE_POLARITY Mask*/

#define DISP_PanelConfig0_DATA_ENABLE_Pos (4)                                         /*!< DISP_T::PanelConfig0: DATA_ENABLE Position*/
#define DISP_PanelConfig0_DATA_ENABLE_Msk (0x1ul << DISP_PanelConfig0_DATA_ENABLE_Pos) /*!< DISP_T::PanelConfig0: DATA_ENABLE Mask*/

#define DISP_PanelConfig0_DATA_POLARITY_Pos (5)                                       /*!< DISP_T::PanelConfig0: DATA_POLARITY Position*/
#define DISP_PanelConfig0_DATA_POLARITY_Msk (0x1ul << DISP_PanelConfig0_DATA_POLARITY_Pos) /*!< DISP_T::PanelConfig0: DATA_POLARITY Mask*/

#define DISP_PanelConfig0_CLOCK_Pos (8)                                               /*!< DISP_T::PanelConfig0: CLOCK Position*/
#define DISP_PanelConfig0_CLOCK_Msk (0x1ul << DISP_PanelConfig0_CLOCK_Pos)       /*!< DISP_T::PanelConfig0: CLOCK Mask  */

#define DISP_PanelConfig0_CLOCK_POLARITY_Pos (9)                                      /*!< DISP_T::PanelConfig0: CLOCK_POLARITY Position*/
#define DISP_PanelConfig0_CLOCK_POLARITY_Msk (0x1ul << DISP_PanelConfig0_CLOCK_POLARITY_Pos) /*!< DISP_T::PanelConfig0: CLOCK_POLARITY Mask*/

#define DISP_DisplayDitherTableLow0_Y0_X0_Pos (0)                                     /*!< DISP_T::DisplayDitherTableLow0: Y0_X0 Position*/
#define DISP_DisplayDitherTableLow0_Y0_X0_Msk (0xful << DISP_DisplayDitherTableLow0_Y0_X0_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y0_X0 Mask*/

#define DISP_DisplayDitherTableLow0_Y0_X1_Pos (4)                                     /*!< DISP_T::DisplayDitherTableLow0: Y0_X1 Position*/
#define DISP_DisplayDitherTableLow0_Y0_X1_Msk (0xful << DISP_DisplayDitherTableLow0_Y0_X1_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y0_X1 Mask*/

#define DISP_DisplayDitherTableLow0_Y0_X2_Pos (8)                                     /*!< DISP_T::DisplayDitherTableLow0: Y0_X2 Position*/
#define DISP_DisplayDitherTableLow0_Y0_X2_Msk (0xful << DISP_DisplayDitherTableLow0_Y0_X2_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y0_X2 Mask*/

#define DISP_DisplayDitherTableLow0_Y0_X3_Pos (12)                                    /*!< DISP_T::DisplayDitherTableLow0: Y0_X3 Position*/
#define DISP_DisplayDitherTableLow0_Y0_X3_Msk (0xful << DISP_DisplayDitherTableLow0_Y0_X3_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y0_X3 Mask*/

#define DISP_DisplayDitherTableLow0_Y1_X0_Pos (16)                                    /*!< DISP_T::DisplayDitherTableLow0: Y1_X0 Position*/
#define DISP_DisplayDitherTableLow0_Y1_X0_Msk (0xful << DISP_DisplayDitherTableLow0_Y1_X0_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y1_X0 Mask*/

#define DISP_DisplayDitherTableLow0_Y1_X1_Pos (20)                                    /*!< DISP_T::DisplayDitherTableLow0: Y1_X1 Position*/
#define DISP_DisplayDitherTableLow0_Y1_X1_Msk (0xful << DISP_DisplayDitherTableLow0_Y1_X1_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y1_X1 Mask*/

#define DISP_DisplayDitherTableLow0_Y1_X2_Pos (24)                                    /*!< DISP_T::DisplayDitherTableLow0: Y1_X2 Position*/
#define DISP_DisplayDitherTableLow0_Y1_X2_Msk (0xful << DISP_DisplayDitherTableLow0_Y1_X2_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y1_X2 Mask*/

#define DISP_DisplayDitherTableLow0_Y1_X3_Pos (28)                                    /*!< DISP_T::DisplayDitherTableLow0: Y1_X3 Position*/
#define DISP_DisplayDitherTableLow0_Y1_X3_Msk (0xful << DISP_DisplayDitherTableLow0_Y1_X3_Pos) /*!< DISP_T::DisplayDitherTableLow0: Y1_X3 Mask*/

#define DISP_DisplayDitherTableHigh0_Y2_X0_Pos (0)                                    /*!< DISP_T::DisplayDitherTableHigh0: Y2_X0 Position*/
#define DISP_DisplayDitherTableHigh0_Y2_X0_Msk (0xful << DISP_DisplayDitherTableHigh0_Y2_X0_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y2_X0 Mask*/

#define DISP_DisplayDitherTableHigh0_Y2_X1_Pos (4)                                    /*!< DISP_T::DisplayDitherTableHigh0: Y2_X1 Position*/
#define DISP_DisplayDitherTableHigh0_Y2_X1_Msk (0xful << DISP_DisplayDitherTableHigh0_Y2_X1_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y2_X1 Mask*/

#define DISP_DisplayDitherTableHigh0_Y2_X2_Pos (8)                                    /*!< DISP_T::DisplayDitherTableHigh0: Y2_X2 Position*/
#define DISP_DisplayDitherTableHigh0_Y2_X2_Msk (0xful << DISP_DisplayDitherTableHigh0_Y2_X2_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y2_X2 Mask*/

#define DISP_DisplayDitherTableHigh0_Y2_X3_Pos (12)                                   /*!< DISP_T::DisplayDitherTableHigh0: Y2_X3 Position*/
#define DISP_DisplayDitherTableHigh0_Y2_X3_Msk (0xful << DISP_DisplayDitherTableHigh0_Y2_X3_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y2_X3 Mask*/

#define DISP_DisplayDitherTableHigh0_Y3_X0_Pos (16)                                   /*!< DISP_T::DisplayDitherTableHigh0: Y3_X0 Position*/
#define DISP_DisplayDitherTableHigh0_Y3_X0_Msk (0xful << DISP_DisplayDitherTableHigh0_Y3_X0_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y3_X0 Mask*/

#define DISP_DisplayDitherTableHigh0_Y3_X1_Pos (20)                                   /*!< DISP_T::DisplayDitherTableHigh0: Y3_X1 Position*/
#define DISP_DisplayDitherTableHigh0_Y3_X1_Msk (0xful << DISP_DisplayDitherTableHigh0_Y3_X1_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y3_X1 Mask*/

#define DISP_DisplayDitherTableHigh0_Y3_X2_Pos (24)                                   /*!< DISP_T::DisplayDitherTableHigh0: Y3_X2 Position*/
#define DISP_DisplayDitherTableHigh0_Y3_X2_Msk (0xful << DISP_DisplayDitherTableHigh0_Y3_X2_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y3_X2 Mask*/

#define DISP_DisplayDitherTableHigh0_Y3_X3_Pos (28)                                   /*!< DISP_T::DisplayDitherTableHigh0: Y3_X3 Position*/
#define DISP_DisplayDitherTableHigh0_Y3_X3_Msk (0xful << DISP_DisplayDitherTableHigh0_Y3_X3_Pos) /*!< DISP_T::DisplayDitherTableHigh0: Y3_X3 Mask*/

#define DISP_HDisplay0_DISPLAY_END_Pos (0)                                            /*!< DISP_T::HDisplay0: DISPLAY_END Position*/
#define DISP_HDisplay0_DISPLAY_END_Msk (0x7ffful << DISP_HDisplay0_DISPLAY_END_Pos) /*!< DISP_T::HDisplay0: DISPLAY_END Mask*/

#define DISP_HDisplay0_TOTAL_Pos    (16)                                              /*!< DISP_T::HDisplay0: TOTAL Position */
#define DISP_HDisplay0_TOTAL_Msk    (0x7ffful << DISP_HDisplay0_TOTAL_Pos)       /*!< DISP_T::HDisplay0: TOTAL Mask     */

#define DISP_HSync0_START_Pos       (0)                                               /*!< DISP_T::HSync0: START Position    */
#define DISP_HSync0_START_Msk       (0x7ffful << DISP_HSync0_START_Pos)          /*!< DISP_T::HSync0: START Mask        */

#define DISP_HSync0_END_Pos         (15)                                              /*!< DISP_T::HSync0: END Position      */
#define DISP_HSync0_END_Msk         (0x7ffful << DISP_HSync0_END_Pos)            /*!< DISP_T::HSync0: END Mask          */

#define DISP_HSync0_PULSE_Pos       (30)                                              /*!< DISP_T::HSync0: PULSE Position    */
#define DISP_HSync0_PULSE_Msk       (0x1ul << DISP_HSync0_PULSE_Pos)             /*!< DISP_T::HSync0: PULSE Mask        */

#define DISP_HSync0_POLARITY_Pos    (31)                                              /*!< DISP_T::HSync0: POLARITY Position */
#define DISP_HSync0_POLARITY_Msk    (0x1ul << DISP_HSync0_POLARITY_Pos)          /*!< DISP_T::HSync0: POLARITY Mask     */

#define DISP_VDisplay0_DISPLAY_END_Pos (0)                                            /*!< DISP_T::VDisplay0: DISPLAY_END Position*/
#define DISP_VDisplay0_DISPLAY_END_Msk (0x7ffful << DISP_VDisplay0_DISPLAY_END_Pos) /*!< DISP_T::VDisplay0: DISPLAY_END Mask*/

#define DISP_VDisplay0_TOTAL_Pos    (16)                                              /*!< DISP_T::VDisplay0: TOTAL Position */
#define DISP_VDisplay0_TOTAL_Msk    (0x7ffful << DISP_VDisplay0_TOTAL_Pos)       /*!< DISP_T::VDisplay0: TOTAL Mask     */

#define DISP_VSync0_START_Pos       (0)                                               /*!< DISP_T::VSync0: START Position    */
#define DISP_VSync0_START_Msk       (0x7ffful << DISP_VSync0_START_Pos)          /*!< DISP_T::VSync0: START Mask        */

#define DISP_VSync0_END_Pos         (15)                                              /*!< DISP_T::VSync0: END Position      */
#define DISP_VSync0_END_Msk         (0x7ffful << DISP_VSync0_END_Pos)            /*!< DISP_T::VSync0: END Mask          */

#define DISP_VSync0_PULSE_Pos       (30)                                              /*!< DISP_T::VSync0: PULSE Position    */
#define DISP_VSync0_PULSE_Msk       (0x1ul << DISP_VSync0_PULSE_Pos)             /*!< DISP_T::VSync0: PULSE Mask        */

#define DISP_VSync0_POLARITY_Pos    (31)                                              /*!< DISP_T::VSync0: POLARITY Position */
#define DISP_VSync0_POLARITY_Msk    (0x1ul << DISP_VSync0_POLARITY_Pos)          /*!< DISP_T::VSync0: POLARITY Mask     */

#define DISP_DisplayCurrentLocation0_X_Pos (0)                                        /*!< DISP_T::DisplayCurrentLocation0: X Position*/
#define DISP_DisplayCurrentLocation0_X_Msk (0xfffful << DISP_DisplayCurrentLocation0_X_Pos) /*!< DISP_T::DisplayCurrentLocation0: X Mask*/

#define DISP_DisplayCurrentLocation0_Y_Pos (16)                                       /*!< DISP_T::DisplayCurrentLocation0: Y Position*/
#define DISP_DisplayCurrentLocation0_Y_Msk (0xfffful << DISP_DisplayCurrentLocation0_Y_Pos) /*!< DISP_T::DisplayCurrentLocation0: Y Mask*/

#define DISP_GammaIndex0_INDEX_Pos  (0)                                               /*!< DISP_T::GammaIndex0: INDEX Position*/
#define DISP_GammaIndex0_INDEX_Msk  (0xfful << DISP_GammaIndex0_INDEX_Pos)       /*!< DISP_T::GammaIndex0: INDEX Mask   */

#define DISP_GammaData0_BLUE_Pos    (0)                                               /*!< DISP_T::GammaData0: BLUE Position */
#define DISP_GammaData0_BLUE_Msk    (0x3fful << DISP_GammaData0_BLUE_Pos)        /*!< DISP_T::GammaData0: BLUE Mask     */

#define DISP_GammaData0_GREEN_Pos   (10)                                              /*!< DISP_T::GammaData0: GREEN Position*/
#define DISP_GammaData0_GREEN_Msk   (0x3fful << DISP_GammaData0_GREEN_Pos)       /*!< DISP_T::GammaData0: GREEN Mask    */

#define DISP_GammaData0_READ_Pos    (20)                                              /*!< DISP_T::GammaData0: READ Position */
#define DISP_GammaData0_READ_Msk    (0x3fful << DISP_GammaData0_READ_Pos)        /*!< DISP_T::GammaData0: READ Mask     */

#define DISP_CursorConfig_FORMAT_Pos (0)                                              /*!< DISP_T::CursorConfig: FORMAT Position*/
#define DISP_CursorConfig_FORMAT_Msk (0x3ul << DISP_CursorConfig_FORMAT_Pos)     /*!< DISP_T::CursorConfig: FORMAT Mask */

#define DISP_CursorConfig_DISPLAY_Pos (4)                                             /*!< DISP_T::CursorConfig: DISPLAY Position*/
#define DISP_CursorConfig_DISPLAY_Msk (0x1ul << DISP_CursorConfig_DISPLAY_Pos)   /*!< DISP_T::CursorConfig: DISPLAY Mask*/

#define DISP_CursorConfig_HOT_SPOT_Y_Pos (8)                                          /*!< DISP_T::CursorConfig: HOT_SPOT_Y Position*/
#define DISP_CursorConfig_HOT_SPOT_Y_Msk (0x1ful << DISP_CursorConfig_HOT_SPOT_Y_Pos) /*!< DISP_T::CursorConfig: HOT_SPOT_Y Mask*/

#define DISP_CursorConfig_HOT_SPOT_X_Pos (16)                                         /*!< DISP_T::CursorConfig: HOT_SPOT_X Position*/
#define DISP_CursorConfig_HOT_SPOT_X_Msk (0x1ful << DISP_CursorConfig_HOT_SPOT_X_Pos) /*!< DISP_T::CursorConfig: HOT_SPOT_X Mask*/

#define DISP_CursorAddress_ADDRESS_Pos (0)                                            /*!< DISP_T::CursorAddress: ADDRESS Position*/
#define DISP_CursorAddress_ADDRESS_Msk (0x7ffffffful << DISP_CursorAddress_ADDRESS_Pos) /*!< DISP_T::CursorAddress: ADDRESS Mask*/

#define DISP_CursorAddress_TYPE_Pos (31)                                              /*!< DISP_T::CursorAddress: TYPE Position*/
#define DISP_CursorAddress_TYPE_Msk (0x1ul << DISP_CursorAddress_TYPE_Pos)       /*!< DISP_T::CursorAddress: TYPE Mask  */

#define DISP_CursorLocation_X_Pos   (0)                                               /*!< DISP_T::CursorLocation: X Position*/
#define DISP_CursorLocation_X_Msk   (0x7ffful << DISP_CursorLocation_X_Pos)      /*!< DISP_T::CursorLocation: X Mask    */

#define DISP_CursorLocation_Y_Pos   (16)                                              /*!< DISP_T::CursorLocation: Y Position*/
#define DISP_CursorLocation_Y_Msk   (0x7ffful << DISP_CursorLocation_Y_Pos)      /*!< DISP_T::CursorLocation: Y Mask    */

#define DISP_CursorBackground_BLUE_Pos (0)                                            /*!< DISP_T::CursorBackground: BLUE Position*/
#define DISP_CursorBackground_BLUE_Msk (0xfful << DISP_CursorBackground_BLUE_Pos) /*!< DISP_T::CursorBackground: BLUE Mask*/

#define DISP_CursorBackground_GREEN_Pos (8)                                           /*!< DISP_T::CursorBackground: GREEN Position*/
#define DISP_CursorBackground_GREEN_Msk (0xfful << DISP_CursorBackground_GREEN_Pos) /*!< DISP_T::CursorBackground: GREEN Mask*/

#define DISP_CursorBackground_RED_Pos (16)                                            /*!< DISP_T::CursorBackground: RED Position*/
#define DISP_CursorBackground_RED_Msk (0xfful << DISP_CursorBackground_RED_Pos)  /*!< DISP_T::CursorBackground: RED Mask*/

#define DISP_CursorForeground_BLUE_Pos (0)                                            /*!< DISP_T::CursorForeground: BLUE Position*/
#define DISP_CursorForeground_BLUE_Msk (0xfful << DISP_CursorForeground_BLUE_Pos) /*!< DISP_T::CursorForeground: BLUE Mask*/

#define DISP_CursorForeground_GREEN_Pos (8)                                           /*!< DISP_T::CursorForeground: GREEN Position*/
#define DISP_CursorForeground_GREEN_Msk (0xfful << DISP_CursorForeground_GREEN_Pos) /*!< DISP_T::CursorForeground: GREEN Mask*/

#define DISP_CursorForeground_RED_Pos (16)                                            /*!< DISP_T::CursorForeground: RED Position*/
#define DISP_CursorForeground_RED_Msk (0xfful << DISP_CursorForeground_RED_Pos)  /*!< DISP_T::CursorForeground: RED Mask*/

#define DISP_DisplayIntr_DISP0_Pos  (0)                                               /*!< DISP_T::DisplayIntr: DISP0 Position*/
#define DISP_DisplayIntr_DISP0_Msk  (0x1ul << DISP_DisplayIntr_DISP0_Pos)        /*!< DISP_T::DisplayIntr: DISP0 Mask   */

#define DISP_DisplayIntrEnable_DISP0_Pos (0)                                          /*!< DISP_T::DisplayIntrEnable: DISP0 Position*/
#define DISP_DisplayIntrEnable_DISP0_Msk (0x1ul << DISP_DisplayIntrEnable_DISP0_Pos) /*!< DISP_T::DisplayIntrEnable: DISP0 Mask*/

#define DISP_CursorModuleClockGatingControl_DISABLE_MODULE_CLOCK_GATING_CURSOR_Pos (0) /*!< DISP_T::CursorModuleClockGatingControl: DISABLE_MODULE_CLOCK_GATING_CURSOR Position*/
#define DISP_CursorModuleClockGatingControl_DISABLE_MODULE_CLOCK_GATING_CURSOR_Msk (0x1ul << DISP_CursorModuleClockGatingControl_DISABLE_MODULE_CLOCK_GATING_CURSOR_Pos) /*!< DISP_T::CursorModuleClockGatingControl: DISABLE_MODULE_CLOCK_GATING_CURSOR Mask*/

#define DISP_GeneralConfig0_ENDIAN_CONTROL_Pos (0)                                    /*!< DISP_T::GeneralConfig0: ENDIAN_CONTROL Position*/
#define DISP_GeneralConfig0_ENDIAN_CONTROL_Msk (0x3ul << DISP_GeneralConfig0_ENDIAN_CONTROL_Pos) /*!< DISP_T::GeneralConfig0: ENDIAN_CONTROL Mask*/

#define DISP_GeneralConfig0_STALL_OUTPUT_WHEN_UNDERFLOW_Pos (2)                       /*!< DISP_T::GeneralConfig0: STALL_OUTPUT_WHEN_UNDERFLOW Position*/
#define DISP_GeneralConfig0_STALL_OUTPUT_WHEN_UNDERFLOW_Msk (0x1ul << DISP_GeneralConfig0_STALL_OUTPUT_WHEN_UNDERFLOW_Pos) /*!< DISP_T::GeneralConfig0: STALL_OUTPUT_WHEN_UNDERFLOW Mask*/

#define DISP_GeneralConfig0_DISABLE_IDLE_Pos (3)                                      /*!< DISP_T::GeneralConfig0: DISABLE_IDLE Position*/
#define DISP_GeneralConfig0_DISABLE_IDLE_Msk (0x1ul << DISP_GeneralConfig0_DISABLE_IDLE_Pos) /*!< DISP_T::GeneralConfig0: DISABLE_IDLE Mask*/

#define DISP_DpiConfig0_DPI_DATA_FORMAT_Pos (0)                                       /*!< DISP_T::DpiConfig0: DPI_DATA_FORMAT Position*/
#define DISP_DpiConfig0_DPI_DATA_FORMAT_Msk (0x7ul << DISP_DpiConfig0_DPI_DATA_FORMAT_Pos) /*!< DISP_T::DpiConfig0: DPI_DATA_FORMAT Mask*/

#define DISP_DebugCounterSelect0_SELECT_Pos (0)                                       /*!< DISP_T::DebugCounterSelect0: SELECT Position*/
#define DISP_DebugCounterSelect0_SELECT_Msk (0xfful << DISP_DebugCounterSelect0_SELECT_Pos) /*!< DISP_T::DebugCounterSelect0: SELECT Mask*/

#define DISP_DebugCounterValue0_VALUE_Pos (0)                                         /*!< DISP_T::DebugCounterValue0: VALUE Position*/
#define DISP_DebugCounterValue0_VALUE_Msk (0xfffffffful << DISP_DebugCounterValue0_VALUE_Pos) /*!< DISP_T::DebugCounterValue0: VALUE Mask*/

#define DISP_FrameBufferColorKey0_BLUE_Pos (0)                                        /*!< DISP_T::FrameBufferColorKey0: BLUE Position*/
#define DISP_FrameBufferColorKey0_BLUE_Msk (0xfful << DISP_FrameBufferColorKey0_BLUE_Pos) /*!< DISP_T::FrameBufferColorKey0: BLUE Mask*/

#define DISP_FrameBufferColorKey0_GREEN_Pos (8)                                       /*!< DISP_T::FrameBufferColorKey0: GREEN Position*/
#define DISP_FrameBufferColorKey0_GREEN_Msk (0xfful << DISP_FrameBufferColorKey0_GREEN_Pos) /*!< DISP_T::FrameBufferColorKey0: GREEN Mask*/

#define DISP_FrameBufferColorKey0_RED_Pos (16)                                        /*!< DISP_T::FrameBufferColorKey0: RED Position*/
#define DISP_FrameBufferColorKey0_RED_Msk (0xfful << DISP_FrameBufferColorKey0_RED_Pos) /*!< DISP_T::FrameBufferColorKey0: RED Mask*/

#define DISP_FrameBufferColorKey0_ALPHA_Pos (24)                                      /*!< DISP_T::FrameBufferColorKey0: ALPHA Position*/
#define DISP_FrameBufferColorKey0_ALPHA_Msk (0xfful << DISP_FrameBufferColorKey0_ALPHA_Pos) /*!< DISP_T::FrameBufferColorKey0: ALPHA Mask*/

#define DISP_FrameBufferColorKeyHigh0_BLUE_Pos (0)                                    /*!< DISP_T::FrameBufferColorKeyHigh0: BLUE Position*/
#define DISP_FrameBufferColorKeyHigh0_BLUE_Msk (0xfful << DISP_FrameBufferColorKeyHigh0_BLUE_Pos) /*!< DISP_T::FrameBufferColorKeyHigh0: BLUE Mask*/

#define DISP_FrameBufferColorKeyHigh0_GREEN_Pos (8)                                   /*!< DISP_T::FrameBufferColorKeyHigh0: GREEN Position*/
#define DISP_FrameBufferColorKeyHigh0_GREEN_Msk (0xfful << DISP_FrameBufferColorKeyHigh0_GREEN_Pos) /*!< DISP_T::FrameBufferColorKeyHigh0: GREEN Mask*/

#define DISP_FrameBufferColorKeyHigh0_RED_Pos (16)                                    /*!< DISP_T::FrameBufferColorKeyHigh0: RED Position*/
#define DISP_FrameBufferColorKeyHigh0_RED_Msk (0xfful << DISP_FrameBufferColorKeyHigh0_RED_Pos) /*!< DISP_T::FrameBufferColorKeyHigh0: RED Mask*/

#define DISP_FrameBufferColorKeyHigh0_ALPHA_Pos (24)                                  /*!< DISP_T::FrameBufferColorKeyHigh0: ALPHA Position*/
#define DISP_FrameBufferColorKeyHigh0_ALPHA_Msk (0xfful << DISP_FrameBufferColorKeyHigh0_ALPHA_Pos) /*!< DISP_T::FrameBufferColorKeyHigh0: ALPHA Mask*/

#define DISP_FrameBufferConfig0_OUTPUT_Pos (0)                                        /*!< DISP_T::FrameBufferConfig0: OUTPUT Position*/
#define DISP_FrameBufferConfig0_OUTPUT_Msk (0x1ul << DISP_FrameBufferConfig0_OUTPUT_Pos) /*!< DISP_T::FrameBufferConfig0: OUTPUT Mask*/

#define DISP_FrameBufferConfig0_GAMMA_Pos (2)                                         /*!< DISP_T::FrameBufferConfig0: GAMMA Position*/
#define DISP_FrameBufferConfig0_GAMMA_Msk (0x1ul << DISP_FrameBufferConfig0_GAMMA_Pos) /*!< DISP_T::FrameBufferConfig0: GAMMA Mask*/

#define DISP_FrameBufferConfig0_VALID_Pos (3)                                         /*!< DISP_T::FrameBufferConfig0: VALID Position*/
#define DISP_FrameBufferConfig0_VALID_Msk (0x1ul << DISP_FrameBufferConfig0_VALID_Pos) /*!< DISP_T::FrameBufferConfig0: VALID Mask*/

#define DISP_FrameBufferConfig0_RESET_Pos (4)                                         /*!< DISP_T::FrameBufferConfig0: RESET Position*/
#define DISP_FrameBufferConfig0_RESET_Msk (0x1ul << DISP_FrameBufferConfig0_RESET_Pos) /*!< DISP_T::FrameBufferConfig0: RESET Mask*/

#define DISP_FrameBufferConfig0_UNDERFLOW_Pos (5)                                     /*!< DISP_T::FrameBufferConfig0: UNDERFLOW Position*/
#define DISP_FrameBufferConfig0_UNDERFLOW_Msk (0x1ul << DISP_FrameBufferConfig0_UNDERFLOW_Pos) /*!< DISP_T::FrameBufferConfig0: UNDERFLOW Mask*/

#define DISP_FrameBufferConfig0_FLIP_IN_PROGRESS_Pos (6)                              /*!< DISP_T::FrameBufferConfig0: FLIP_IN_PROGRESS Position*/
#define DISP_FrameBufferConfig0_FLIP_IN_PROGRESS_Msk (0x1ul << DISP_FrameBufferConfig0_FLIP_IN_PROGRESS_Pos) /*!< DISP_T::FrameBufferConfig0: FLIP_IN_PROGRESS Mask*/

#define DISP_FrameBufferConfig0_CLEAR_Pos (8)                                         /*!< DISP_T::FrameBufferConfig0: CLEAR Position*/
#define DISP_FrameBufferConfig0_CLEAR_Msk (0x1ul << DISP_FrameBufferConfig0_CLEAR_Pos) /*!< DISP_T::FrameBufferConfig0: CLEAR Mask*/

#define DISP_FrameBufferConfig0_TRANSPARENCY_Pos (9)                                  /*!< DISP_T::FrameBufferConfig0: TRANSPARENCY Position*/
#define DISP_FrameBufferConfig0_TRANSPARENCY_Msk (0x3ul << DISP_FrameBufferConfig0_TRANSPARENCY_Pos) /*!< DISP_T::FrameBufferConfig0: TRANSPARENCY Mask*/

#define DISP_FrameBufferConfig0_YUV_Pos (14)                                          /*!< DISP_T::FrameBufferConfig0: YUV Position*/
#define DISP_FrameBufferConfig0_YUV_Msk (0x7ul << DISP_FrameBufferConfig0_YUV_Pos) /*!< DISP_T::FrameBufferConfig0: YUV Mask*/

#define DISP_FrameBufferConfig0_SWIZZLE_Pos (23)                                      /*!< DISP_T::FrameBufferConfig0: SWIZZLE Position*/
#define DISP_FrameBufferConfig0_SWIZZLE_Msk (0x3ul << DISP_FrameBufferConfig0_SWIZZLE_Pos) /*!< DISP_T::FrameBufferConfig0: SWIZZLE Mask*/

#define DISP_FrameBufferConfig0_UV_SWIZZLE_Pos (25)                                   /*!< DISP_T::FrameBufferConfig0: UV_SWIZZLE Position*/
#define DISP_FrameBufferConfig0_UV_SWIZZLE_Msk (0x1ul << DISP_FrameBufferConfig0_UV_SWIZZLE_Pos) /*!< DISP_T::FrameBufferConfig0: UV_SWIZZLE Mask*/

#define DISP_FrameBufferConfig0_FORMAT_Pos (26)                                       /*!< DISP_T::FrameBufferConfig0: FORMAT Position*/
#define DISP_FrameBufferConfig0_FORMAT_Msk (0x3ful << DISP_FrameBufferConfig0_FORMAT_Pos) /*!< DISP_T::FrameBufferConfig0: FORMAT Mask*/

#define DISP_FrameBufferBGColor0_BLUE_Pos (0)                                         /*!< DISP_T::FrameBufferBGColor0: BLUE Position*/
#define DISP_FrameBufferBGColor0_BLUE_Msk (0xfful << DISP_FrameBufferBGColor0_BLUE_Pos) /*!< DISP_T::FrameBufferBGColor0: BLUE Mask*/

#define DISP_FrameBufferBGColor0_GREEN_Pos (8)                                        /*!< DISP_T::FrameBufferBGColor0: GREEN Position*/
#define DISP_FrameBufferBGColor0_GREEN_Msk (0xfful << DISP_FrameBufferBGColor0_GREEN_Pos) /*!< DISP_T::FrameBufferBGColor0: GREEN Mask*/

#define DISP_FrameBufferBGColor0_RED_Pos (16)                                         /*!< DISP_T::FrameBufferBGColor0: RED Position*/
#define DISP_FrameBufferBGColor0_RED_Msk (0xfful << DISP_FrameBufferBGColor0_RED_Pos) /*!< DISP_T::FrameBufferBGColor0: RED Mask*/

#define DISP_FrameBufferBGColor0_ALPHA_Pos (24)                                       /*!< DISP_T::FrameBufferBGColor0: ALPHA Position*/
#define DISP_FrameBufferBGColor0_ALPHA_Msk (0xfful << DISP_FrameBufferBGColor0_ALPHA_Pos) /*!< DISP_T::FrameBufferBGColor0: ALPHA Mask*/

#define DISP_FrameBufferUPlanarAddress0_ADDRESS_Pos (0)                               /*!< DISP_T::FrameBufferUPlanarAddress0: ADDRESS Position*/
#define DISP_FrameBufferUPlanarAddress0_ADDRESS_Msk (0x7ffffffful << DISP_FrameBufferUPlanarAddress0_ADDRESS_Pos) /*!< DISP_T::FrameBufferUPlanarAddress0: ADDRESS Mask*/

#define DISP_FrameBufferUPlanarAddress0_TYPE_Pos (31)                                 /*!< DISP_T::FrameBufferUPlanarAddress0: TYPE Position*/
#define DISP_FrameBufferUPlanarAddress0_TYPE_Msk (0x1ul << DISP_FrameBufferUPlanarAddress0_TYPE_Pos) /*!< DISP_T::FrameBufferUPlanarAddress0: TYPE Mask*/

#define DISP_FrameBufferVPlanarAddress0_ADDRESS_Pos (0)                               /*!< DISP_T::FrameBufferVPlanarAddress0: ADDRESS Position*/
#define DISP_FrameBufferVPlanarAddress0_ADDRESS_Msk (0x7ffffffful << DISP_FrameBufferVPlanarAddress0_ADDRESS_Pos) /*!< DISP_T::FrameBufferVPlanarAddress0: ADDRESS Mask*/

#define DISP_FrameBufferVPlanarAddress0_TYPE_Pos (31)                                 /*!< DISP_T::FrameBufferVPlanarAddress0: TYPE Position*/
#define DISP_FrameBufferVPlanarAddress0_TYPE_Msk (0x1ul << DISP_FrameBufferVPlanarAddress0_TYPE_Pos) /*!< DISP_T::FrameBufferVPlanarAddress0: TYPE Mask*/

#define DISP_OverlayConfig0_TRANSPARENCY_Pos (0)                                      /*!< DISP_T::OverlayConfig0: TRANSPARENCY Position*/
#define DISP_OverlayConfig0_TRANSPARENCY_Msk (0x3ul << DISP_OverlayConfig0_TRANSPARENCY_Pos) /*!< DISP_T::OverlayConfig0: TRANSPARENCY Mask*/

#define DISP_OverlayConfig0_YUV_Pos (5)                                               /*!< DISP_T::OverlayConfig0: YUV Position*/
#define DISP_OverlayConfig0_YUV_Msk (0x7ul << DISP_OverlayConfig0_YUV_Pos)       /*!< DISP_T::OverlayConfig0: YUV Mask  */

#define DISP_OverlayConfig0_SWIZZLE_Pos (13)                                          /*!< DISP_T::OverlayConfig0: SWIZZLE Position*/
#define DISP_OverlayConfig0_SWIZZLE_Msk (0x3ul << DISP_OverlayConfig0_SWIZZLE_Pos) /*!< DISP_T::OverlayConfig0: SWIZZLE Mask*/

#define DISP_OverlayConfig0_UV_SWIZZLE_Pos (15)                                       /*!< DISP_T::OverlayConfig0: UV_SWIZZLE Position*/
#define DISP_OverlayConfig0_UV_SWIZZLE_Msk (0x1ul << DISP_OverlayConfig0_UV_SWIZZLE_Pos) /*!< DISP_T::OverlayConfig0: UV_SWIZZLE Mask*/

#define DISP_OverlayConfig0_FORMAT_Pos (16)                                           /*!< DISP_T::OverlayConfig0: FORMAT Position*/
#define DISP_OverlayConfig0_FORMAT_Msk (0x3ful << DISP_OverlayConfig0_FORMAT_Pos) /*!< DISP_T::OverlayConfig0: FORMAT Mask*/

#define DISP_OverlayConfig0_UNDERFLOW_Pos (23)                                        /*!< DISP_T::OverlayConfig0: UNDERFLOW Position*/
#define DISP_OverlayConfig0_UNDERFLOW_Msk (0x1ul << DISP_OverlayConfig0_UNDERFLOW_Pos) /*!< DISP_T::OverlayConfig0: UNDERFLOW Mask*/

#define DISP_OverlayConfig0_ENABLE_Pos (24)                                           /*!< DISP_T::OverlayConfig0: ENABLE Position*/
#define DISP_OverlayConfig0_ENABLE_Msk (0x1ul << DISP_OverlayConfig0_ENABLE_Pos) /*!< DISP_T::OverlayConfig0: ENABLE Mask*/

#define DISP_OverlayConfig0_CLEAR_Pos (25)                                            /*!< DISP_T::OverlayConfig0: CLEAR Position*/
#define DISP_OverlayConfig0_CLEAR_Msk (0x1ul << DISP_OverlayConfig0_CLEAR_Pos)   /*!< DISP_T::OverlayConfig0: CLEAR Mask*/

#define DISP_OverlayAlphaBlendConfig0_SRC_ALPHA_MODE_Pos (0)                          /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_ALPHA_MODE Position*/
#define DISP_OverlayAlphaBlendConfig0_SRC_ALPHA_MODE_Msk (0x1ul << DISP_OverlayAlphaBlendConfig0_SRC_ALPHA_MODE_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_ALPHA_MODE Mask*/

#define DISP_OverlayAlphaBlendConfig0_DISABLE_ALPHA_BLEND_Pos (1)                     /*!< DISP_T::OverlayAlphaBlendConfig0: DISABLE_ALPHA_BLEND Position*/
#define DISP_OverlayAlphaBlendConfig0_DISABLE_ALPHA_BLEND_Msk (0x1ul << DISP_OverlayAlphaBlendConfig0_DISABLE_ALPHA_BLEND_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: DISABLE_ALPHA_BLEND Mask*/

#define DISP_OverlayAlphaBlendConfig0_SRC_GLOBAL_ALPHA_MODE_Pos (3)                   /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_GLOBAL_ALPHA_MODE Position*/
#define DISP_OverlayAlphaBlendConfig0_SRC_GLOBAL_ALPHA_MODE_Msk (0x3ul << DISP_OverlayAlphaBlendConfig0_SRC_GLOBAL_ALPHA_MODE_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_GLOBAL_ALPHA_MODE Mask*/

#define DISP_OverlayAlphaBlendConfig0_SRC_BLENDING_MODE_Pos (5)                       /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_BLENDING_MODE Position*/
#define DISP_OverlayAlphaBlendConfig0_SRC_BLENDING_MODE_Msk (0x7ul << DISP_OverlayAlphaBlendConfig0_SRC_BLENDING_MODE_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_BLENDING_MODE Mask*/

#define DISP_OverlayAlphaBlendConfig0_SRC_ALPHA_FACTOR_Pos (8)                        /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_ALPHA_FACTOR Position*/
#define DISP_OverlayAlphaBlendConfig0_SRC_ALPHA_FACTOR_Msk (0x1ul << DISP_OverlayAlphaBlendConfig0_SRC_ALPHA_FACTOR_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: SRC_ALPHA_FACTOR Mask*/

#define DISP_OverlayAlphaBlendConfig0_DST_ALPHA_MODE_Pos (9)                          /*!< DISP_T::OverlayAlphaBlendConfig0: DST_ALPHA_MODE Position*/
#define DISP_OverlayAlphaBlendConfig0_DST_ALPHA_MODE_Msk (0x1ul << DISP_OverlayAlphaBlendConfig0_DST_ALPHA_MODE_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: DST_ALPHA_MODE Mask*/

#define DISP_OverlayAlphaBlendConfig0_DST_GLOBAL_ALPHA_MODE_Pos (10)                  /*!< DISP_T::OverlayAlphaBlendConfig0: DST_GLOBAL_ALPHA_MODE Position*/
#define DISP_OverlayAlphaBlendConfig0_DST_GLOBAL_ALPHA_MODE_Msk (0x3ul << DISP_OverlayAlphaBlendConfig0_DST_GLOBAL_ALPHA_MODE_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: DST_GLOBAL_ALPHA_MODE Mask*/

#define DISP_OverlayAlphaBlendConfig0_DST_BLENDING_MODE_Pos (12)                      /*!< DISP_T::OverlayAlphaBlendConfig0: DST_BLENDING_MODE Position*/
#define DISP_OverlayAlphaBlendConfig0_DST_BLENDING_MODE_Msk (0x7ul << DISP_OverlayAlphaBlendConfig0_DST_BLENDING_MODE_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: DST_BLENDING_MODE Mask*/

#define DISP_OverlayAlphaBlendConfig0_DST_ALPHA_FACTOR_Pos (15)                       /*!< DISP_T::OverlayAlphaBlendConfig0: DST_ALPHA_FACTOR Position*/
#define DISP_OverlayAlphaBlendConfig0_DST_ALPHA_FACTOR_Msk (0x1ul << DISP_OverlayAlphaBlendConfig0_DST_ALPHA_FACTOR_Pos) /*!< DISP_T::OverlayAlphaBlendConfig0: DST_ALPHA_FACTOR Mask*/

#define DISP_OverlayAddress0_ADDRESS_Pos (0)                                          /*!< DISP_T::OverlayAddress0: ADDRESS Position*/
#define DISP_OverlayAddress0_ADDRESS_Msk (0x7ffffffful << DISP_OverlayAddress0_ADDRESS_Pos) /*!< DISP_T::OverlayAddress0: ADDRESS Mask*/

#define DISP_OverlayAddress0_TYPE_Pos (31)                                            /*!< DISP_T::OverlayAddress0: TYPE Position*/
#define DISP_OverlayAddress0_TYPE_Msk (0x1ul << DISP_OverlayAddress0_TYPE_Pos)   /*!< DISP_T::OverlayAddress0: TYPE Mask*/

#define DISP_OverlayStride0_STRIDE_Pos (0)                                            /*!< DISP_T::OverlayStride0: STRIDE Position*/
#define DISP_OverlayStride0_STRIDE_Msk (0x1fffful << DISP_OverlayStride0_STRIDE_Pos) /*!< DISP_T::OverlayStride0: STRIDE Mask*/

#define DISP_OverlayTL0_X_Pos       (0)                                               /*!< DISP_T::OverlayTL0: X Position    */
#define DISP_OverlayTL0_X_Msk       (0x7ffful << DISP_OverlayTL0_X_Pos)          /*!< DISP_T::OverlayTL0: X Mask        */

#define DISP_OverlayTL0_Y_Pos       (15)                                              /*!< DISP_T::OverlayTL0: Y Position    */
#define DISP_OverlayTL0_Y_Msk       (0x7ffful << DISP_OverlayTL0_Y_Pos)          /*!< DISP_T::OverlayTL0: Y Mask        */

#define DISP_OverlayBR0_X_Pos       (0)                                               /*!< DISP_T::OverlayBR0: X Position    */
#define DISP_OverlayBR0_X_Msk       (0x7ffful << DISP_OverlayBR0_X_Pos)          /*!< DISP_T::OverlayBR0: X Mask        */

#define DISP_OverlayBR0_Y_Pos       (15)                                              /*!< DISP_T::OverlayBR0: Y Position    */
#define DISP_OverlayBR0_Y_Msk       (0x7ffful << DISP_OverlayBR0_Y_Pos)          /*!< DISP_T::OverlayBR0: Y Mask        */

#define DISP_OverlaySrcGlobalColor0_BLUE_Pos (0)                                      /*!< DISP_T::OverlaySrcGlobalColor0: BLUE Position*/
#define DISP_OverlaySrcGlobalColor0_BLUE_Msk (0xfful << DISP_OverlaySrcGlobalColor0_BLUE_Pos) /*!< DISP_T::OverlaySrcGlobalColor0: BLUE Mask*/

#define DISP_OverlaySrcGlobalColor0_GREEN_Pos (8)                                     /*!< DISP_T::OverlaySrcGlobalColor0: GREEN Position*/
#define DISP_OverlaySrcGlobalColor0_GREEN_Msk (0xfful << DISP_OverlaySrcGlobalColor0_GREEN_Pos) /*!< DISP_T::OverlaySrcGlobalColor0: GREEN Mask*/

#define DISP_OverlaySrcGlobalColor0_RED_Pos (16)                                      /*!< DISP_T::OverlaySrcGlobalColor0: RED Position*/
#define DISP_OverlaySrcGlobalColor0_RED_Msk (0xfful << DISP_OverlaySrcGlobalColor0_RED_Pos) /*!< DISP_T::OverlaySrcGlobalColor0: RED Mask*/

#define DISP_OverlaySrcGlobalColor0_ALPHA_Pos (24)                                    /*!< DISP_T::OverlaySrcGlobalColor0: ALPHA Position*/
#define DISP_OverlaySrcGlobalColor0_ALPHA_Msk (0xfful << DISP_OverlaySrcGlobalColor0_ALPHA_Pos) /*!< DISP_T::OverlaySrcGlobalColor0: ALPHA Mask*/

#define DISP_OverlayDstGlobalColor0_BLUE_Pos (0)                                      /*!< DISP_T::OverlayDstGlobalColor0: BLUE Position*/
#define DISP_OverlayDstGlobalColor0_BLUE_Msk (0xfful << DISP_OverlayDstGlobalColor0_BLUE_Pos) /*!< DISP_T::OverlayDstGlobalColor0: BLUE Mask*/

#define DISP_OverlayDstGlobalColor0_GREEN_Pos (8)                                     /*!< DISP_T::OverlayDstGlobalColor0: GREEN Position*/
#define DISP_OverlayDstGlobalColor0_GREEN_Msk (0xfful << DISP_OverlayDstGlobalColor0_GREEN_Pos) /*!< DISP_T::OverlayDstGlobalColor0: GREEN Mask*/

#define DISP_OverlayDstGlobalColor0_RED_Pos (16)                                      /*!< DISP_T::OverlayDstGlobalColor0: RED Position*/
#define DISP_OverlayDstGlobalColor0_RED_Msk (0xfful << DISP_OverlayDstGlobalColor0_RED_Pos) /*!< DISP_T::OverlayDstGlobalColor0: RED Mask*/

#define DISP_OverlayDstGlobalColor0_ALPHA_Pos (24)                                    /*!< DISP_T::OverlayDstGlobalColor0: ALPHA Position*/
#define DISP_OverlayDstGlobalColor0_ALPHA_Msk (0xfful << DISP_OverlayDstGlobalColor0_ALPHA_Pos) /*!< DISP_T::OverlayDstGlobalColor0: ALPHA Mask*/

#define DISP_OverlayColorKey0_BLUE_Pos (0)                                            /*!< DISP_T::OverlayColorKey0: BLUE Position*/
#define DISP_OverlayColorKey0_BLUE_Msk (0xfful << DISP_OverlayColorKey0_BLUE_Pos) /*!< DISP_T::OverlayColorKey0: BLUE Mask*/

#define DISP_OverlayColorKey0_GREEN_Pos (8)                                           /*!< DISP_T::OverlayColorKey0: GREEN Position*/
#define DISP_OverlayColorKey0_GREEN_Msk (0xfful << DISP_OverlayColorKey0_GREEN_Pos) /*!< DISP_T::OverlayColorKey0: GREEN Mask*/

#define DISP_OverlayColorKey0_RED_Pos (16)                                            /*!< DISP_T::OverlayColorKey0: RED Position*/
#define DISP_OverlayColorKey0_RED_Msk (0xfful << DISP_OverlayColorKey0_RED_Pos)  /*!< DISP_T::OverlayColorKey0: RED Mask*/

#define DISP_OverlayColorKey0_ALPHA_Pos (24)                                          /*!< DISP_T::OverlayColorKey0: ALPHA Position*/
#define DISP_OverlayColorKey0_ALPHA_Msk (0xfful << DISP_OverlayColorKey0_ALPHA_Pos) /*!< DISP_T::OverlayColorKey0: ALPHA Mask*/

#define DISP_OverlayColorKeyHigh0_BLUE_Pos (0)                                        /*!< DISP_T::OverlayColorKeyHigh0: BLUE Position*/
#define DISP_OverlayColorKeyHigh0_BLUE_Msk (0xfful << DISP_OverlayColorKeyHigh0_BLUE_Pos) /*!< DISP_T::OverlayColorKeyHigh0: BLUE Mask*/

#define DISP_OverlayColorKeyHigh0_GREEN_Pos (8)                                       /*!< DISP_T::OverlayColorKeyHigh0: GREEN Position*/
#define DISP_OverlayColorKeyHigh0_GREEN_Msk (0xfful << DISP_OverlayColorKeyHigh0_GREEN_Pos) /*!< DISP_T::OverlayColorKeyHigh0: GREEN Mask*/

#define DISP_OverlayColorKeyHigh0_RED_Pos (16)                                        /*!< DISP_T::OverlayColorKeyHigh0: RED Position*/
#define DISP_OverlayColorKeyHigh0_RED_Msk (0xfful << DISP_OverlayColorKeyHigh0_RED_Pos) /*!< DISP_T::OverlayColorKeyHigh0: RED Mask*/

#define DISP_OverlayColorKeyHigh0_ALPHA_Pos (24)                                      /*!< DISP_T::OverlayColorKeyHigh0: ALPHA Position*/
#define DISP_OverlayColorKeyHigh0_ALPHA_Msk (0xfful << DISP_OverlayColorKeyHigh0_ALPHA_Pos) /*!< DISP_T::OverlayColorKeyHigh0: ALPHA Mask*/

#define DISP_OverlaySize0_WIDTH_Pos (0)                                               /*!< DISP_T::OverlaySize0: WIDTH Position*/
#define DISP_OverlaySize0_WIDTH_Msk (0x7ffful << DISP_OverlaySize0_WIDTH_Pos)    /*!< DISP_T::OverlaySize0: WIDTH Mask  */

#define DISP_OverlaySize0_HEIGHT_Pos (15)                                             /*!< DISP_T::OverlaySize0: HEIGHT Position*/
#define DISP_OverlaySize0_HEIGHT_Msk (0x7ffful << DISP_OverlaySize0_HEIGHT_Pos)  /*!< DISP_T::OverlaySize0: HEIGHT Mask */

#define DISP_FrameBufferUStride0_STRIDE_Pos (0)                                       /*!< DISP_T::FrameBufferUStride0: STRIDE Position*/
#define DISP_FrameBufferUStride0_STRIDE_Msk (0x1fffful << DISP_FrameBufferUStride0_STRIDE_Pos) /*!< DISP_T::FrameBufferUStride0: STRIDE Mask*/

#define DISP_FrameBufferVStride0_STRIDE_Pos (0)                                       /*!< DISP_T::FrameBufferVStride0: STRIDE Position*/
#define DISP_FrameBufferVStride0_STRIDE_Msk (0x1fffful << DISP_FrameBufferVStride0_STRIDE_Pos) /*!< DISP_T::FrameBufferVStride0: STRIDE Mask*/

#define DISP_FrameBufferSize0_WIDTH_Pos (0)                                           /*!< DISP_T::FrameBufferSize0: WIDTH Position*/
#define DISP_FrameBufferSize0_WIDTH_Msk (0x7ffful << DISP_FrameBufferSize0_WIDTH_Pos) /*!< DISP_T::FrameBufferSize0: WIDTH Mask*/

#define DISP_FrameBufferSize0_HEIGHT_Pos (15)                                         /*!< DISP_T::FrameBufferSize0: HEIGHT Position*/
#define DISP_FrameBufferSize0_HEIGHT_Msk (0x7ffful << DISP_FrameBufferSize0_HEIGHT_Pos) /*!< DISP_T::FrameBufferSize0: HEIGHT Mask*/

#define DISP_IndexColorTableIndex0_INDEX_Pos (0)                                      /*!< DISP_T::IndexColorTableIndex0: INDEX Position*/
#define DISP_IndexColorTableIndex0_INDEX_Msk (0xfful << DISP_IndexColorTableIndex0_INDEX_Pos) /*!< DISP_T::IndexColorTableIndex0: INDEX Mask*/

#define DISP_IndexColorTableData0_BLUE_Pos (0)                                        /*!< DISP_T::IndexColorTableData0: BLUE Position*/
#define DISP_IndexColorTableData0_BLUE_Msk (0xfful << DISP_IndexColorTableData0_BLUE_Pos) /*!< DISP_T::IndexColorTableData0: BLUE Mask*/

#define DISP_IndexColorTableData0_GREEN_Pos (8)                                       /*!< DISP_T::IndexColorTableData0: GREEN Position*/
#define DISP_IndexColorTableData0_GREEN_Msk (0xfful << DISP_IndexColorTableData0_GREEN_Pos) /*!< DISP_T::IndexColorTableData0: GREEN Mask*/

#define DISP_IndexColorTableData0_RED_Pos (16)                                        /*!< DISP_T::IndexColorTableData0: RED Position*/
#define DISP_IndexColorTableData0_RED_Msk (0xfful << DISP_IndexColorTableData0_RED_Pos) /*!< DISP_T::IndexColorTableData0: RED Mask*/

#define DISP_IndexColorTableData0_ALPHA_Pos (24)                                      /*!< DISP_T::IndexColorTableData0: ALPHA Position*/
#define DISP_IndexColorTableData0_ALPHA_Msk (0xfful << DISP_IndexColorTableData0_ALPHA_Pos) /*!< DISP_T::IndexColorTableData0: ALPHA Mask*/

#define DISP_OverlayUPlanarAddress0_ADDRESS_Pos (0)                                   /*!< DISP_T::OverlayUPlanarAddress0: ADDRESS Position*/
#define DISP_OverlayUPlanarAddress0_ADDRESS_Msk (0x7ffffffful << DISP_OverlayUPlanarAddress0_ADDRESS_Pos) /*!< DISP_T::OverlayUPlanarAddress0: ADDRESS Mask*/

#define DISP_OverlayUPlanarAddress0_TYPE_Pos (31)                                     /*!< DISP_T::OverlayUPlanarAddress0: TYPE Position*/
#define DISP_OverlayUPlanarAddress0_TYPE_Msk (0x1ul << DISP_OverlayUPlanarAddress0_TYPE_Pos) /*!< DISP_T::OverlayUPlanarAddress0: TYPE Mask*/

#define DISP_OverlayVPlanarAddress0_ADDRESS_Pos (0)                                   /*!< DISP_T::OverlayVPlanarAddress0: ADDRESS Position*/
#define DISP_OverlayVPlanarAddress0_ADDRESS_Msk (0x7ffffffful << DISP_OverlayVPlanarAddress0_ADDRESS_Pos) /*!< DISP_T::OverlayVPlanarAddress0: ADDRESS Mask*/

#define DISP_OverlayVPlanarAddress0_TYPE_Pos (31)                                     /*!< DISP_T::OverlayVPlanarAddress0: TYPE Position*/
#define DISP_OverlayVPlanarAddress0_TYPE_Msk (0x1ul << DISP_OverlayVPlanarAddress0_TYPE_Pos) /*!< DISP_T::OverlayVPlanarAddress0: TYPE Mask*/

#define DISP_OverlayUStride0_STRIDE_Pos (0)                                           /*!< DISP_T::OverlayUStride0: STRIDE Position*/
#define DISP_OverlayUStride0_STRIDE_Msk (0x1fffful << DISP_OverlayUStride0_STRIDE_Pos) /*!< DISP_T::OverlayUStride0: STRIDE Mask*/

#define DISP_OverlayVStride0_STRIDE_Pos (0)                                           /*!< DISP_T::OverlayVStride0: STRIDE Position*/
#define DISP_OverlayVStride0_STRIDE_Msk (0x1fffful << DISP_OverlayVStride0_STRIDE_Pos) /*!< DISP_T::OverlayVStride0: STRIDE Mask*/

#define DISP_OverlayClearValue0_BLUE_Pos (0)                                          /*!< DISP_T::OverlayClearValue0: BLUE Position*/
#define DISP_OverlayClearValue0_BLUE_Msk (0xfful << DISP_OverlayClearValue0_BLUE_Pos) /*!< DISP_T::OverlayClearValue0: BLUE Mask*/

#define DISP_OverlayClearValue0_GREEN_Pos (8)                                         /*!< DISP_T::OverlayClearValue0: GREEN Position*/
#define DISP_OverlayClearValue0_GREEN_Msk (0xfful << DISP_OverlayClearValue0_GREEN_Pos) /*!< DISP_T::OverlayClearValue0: GREEN Mask*/

#define DISP_OverlayClearValue0_RED_Pos (16)                                          /*!< DISP_T::OverlayClearValue0: RED Position*/
#define DISP_OverlayClearValue0_RED_Msk (0xfful << DISP_OverlayClearValue0_RED_Pos) /*!< DISP_T::OverlayClearValue0: RED Mask*/

#define DISP_OverlayClearValue0_ALPHA_Pos (24)                                        /*!< DISP_T::OverlayClearValue0: ALPHA Position*/
#define DISP_OverlayClearValue0_ALPHA_Msk (0xfful << DISP_OverlayClearValue0_ALPHA_Pos) /*!< DISP_T::OverlayClearValue0: ALPHA Mask*/

#define DISP_OverlayIndexColorTableIndex0_INDEX_Pos (0)                               /*!< DISP_T::OverlayIndexColorTableIndex0: INDEX Position*/
#define DISP_OverlayIndexColorTableIndex0_INDEX_Msk (0xfful << DISP_OverlayIndexColorTableIndex0_INDEX_Pos) /*!< DISP_T::OverlayIndexColorTableIndex0: INDEX Mask*/

#define DISP_OverlayIndexColorTableData0_BLUE_Pos (0)                                 /*!< DISP_T::OverlayIndexColorTableData0: BLUE Position*/
#define DISP_OverlayIndexColorTableData0_BLUE_Msk (0xfful << DISP_OverlayIndexColorTableData0_BLUE_Pos) /*!< DISP_T::OverlayIndexColorTableData0: BLUE Mask*/

#define DISP_OverlayIndexColorTableData0_GREEN_Pos (8)                                /*!< DISP_T::OverlayIndexColorTableData0: GREEN Position*/
#define DISP_OverlayIndexColorTableData0_GREEN_Msk (0xfful << DISP_OverlayIndexColorTableData0_GREEN_Pos) /*!< DISP_T::OverlayIndexColorTableData0: GREEN Mask*/

#define DISP_OverlayIndexColorTableData0_RED_Pos (16)                                 /*!< DISP_T::OverlayIndexColorTableData0: RED Position*/
#define DISP_OverlayIndexColorTableData0_RED_Msk (0xfful << DISP_OverlayIndexColorTableData0_RED_Pos) /*!< DISP_T::OverlayIndexColorTableData0: RED Mask*/

#define DISP_OverlayIndexColorTableData0_ALPHA_Pos (24)                               /*!< DISP_T::OverlayIndexColorTableData0: ALPHA Position*/
#define DISP_OverlayIndexColorTableData0_ALPHA_Msk (0xfful << DISP_OverlayIndexColorTableData0_ALPHA_Pos) /*!< DISP_T::OverlayIndexColorTableData0: ALPHA Mask*/

#define DISP_FrameBufferClearValue0_BLUE_Pos (0)                                      /*!< DISP_T::FrameBufferClearValue0: BLUE Position*/
#define DISP_FrameBufferClearValue0_BLUE_Msk (0xfful << DISP_FrameBufferClearValue0_BLUE_Pos) /*!< DISP_T::FrameBufferClearValue0: BLUE Mask*/

#define DISP_FrameBufferClearValue0_GREEN_Pos (8)                                     /*!< DISP_T::FrameBufferClearValue0: GREEN Position*/
#define DISP_FrameBufferClearValue0_GREEN_Msk (0xfful << DISP_FrameBufferClearValue0_GREEN_Pos) /*!< DISP_T::FrameBufferClearValue0: GREEN Mask*/

#define DISP_FrameBufferClearValue0_RED_Pos (16)                                      /*!< DISP_T::FrameBufferClearValue0: RED Position*/
#define DISP_FrameBufferClearValue0_RED_Msk (0xfful << DISP_FrameBufferClearValue0_RED_Pos) /*!< DISP_T::FrameBufferClearValue0: RED Mask*/

#define DISP_FrameBufferClearValue0_ALPHA_Pos (24)                                    /*!< DISP_T::FrameBufferClearValue0: ALPHA Position*/
#define DISP_FrameBufferClearValue0_ALPHA_Msk (0xfful << DISP_FrameBufferClearValue0_ALPHA_Pos) /*!< DISP_T::FrameBufferClearValue0: ALPHA Mask*/

#define DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_VIDEO_Pos (0)      /*!< DISP_T::ModuleClockGatingControl0: DISABLE_MODULE_CLOCK_GATING_VIDEO Position*/
#define DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_VIDEO_Msk (0x1ul << DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_VIDEO_Pos) /*!< DISP_T::ModuleClockGatingControl0: DISABLE_MODULE_CLOCK_GATING_VIDEO Mask*/

#define DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_OVERLAY0_Pos (1)   /*!< DISP_T::ModuleClockGatingControl0: DISABLE_MODULE_CLOCK_GATING_OVERLAY0 Position*/
#define DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_OVERLAY0_Msk (0x1ul << DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_OVERLAY0_Pos) /*!< DISP_T::ModuleClockGatingControl0: DISABLE_MODULE_CLOCK_GATING_OVERLAY0 Mask*/

#define DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_WB_FIFO_Pos (9)    /*!< DISP_T::ModuleClockGatingControl0: DISABLE_MODULE_CLOCK_GATING_WB_FIFO Position*/
#define DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_WB_FIFO_Msk (0x1ul << DISP_ModuleClockGatingControl0_DISABLE_MODULE_CLOCK_GATING_WB_FIFO_Pos) /*!< DISP_T::ModuleClockGatingControl0: DISABLE_MODULE_CLOCK_GATING_WB_FIFO Mask*/

#define DISP_LatencyCounter0_COUNTER_Pos (0)                                          /*!< DISP_T::LatencyCounter0: COUNTER Position*/
#define DISP_LatencyCounter0_COUNTER_Msk (0xfffffffful << DISP_LatencyCounter0_COUNTER_Pos) /*!< DISP_T::LatencyCounter0: COUNTER Mask*/

#define DISP_Qos0_LOW_Pos           (0)                                               /*!< DISP_T::Qos0: LOW Position        */
#define DISP_Qos0_LOW_Msk           (0xful << DISP_Qos0_LOW_Pos)                 /*!< DISP_T::Qos0: LOW Mask            */

#define DISP_Qos0_HIGH_Pos          (4)                                               /*!< DISP_T::Qos0: HIGH Position       */
#define DISP_Qos0_HIGH_Msk          (0xful << DISP_Qos0_HIGH_Pos)                /*!< DISP_T::Qos0: HIGH Mask           */

#define DISP_MpuIntfCmd0_REG_DATA_Pos (0)                                             /*!< DISP_T::MpuIntfCmd0: REG_DATA Position*/
#define DISP_MpuIntfCmd0_REG_DATA_Msk (0xfffful << DISP_MpuIntfCmd0_REG_DATA_Pos) /*!< DISP_T::MpuIntfCmd0: REG_DATA Mask*/

#define DISP_MpuIntfCmd0_READ_COUNT_Pos (24)                                          /*!< DISP_T::MpuIntfCmd0: READ_COUNT Position*/
#define DISP_MpuIntfCmd0_READ_COUNT_Msk (0x7ul << DISP_MpuIntfCmd0_READ_COUNT_Pos) /*!< DISP_T::MpuIntfCmd0: READ_COUNT Mask*/

#define DISP_MpuIntfCmd0_START_Pos  (29)                                              /*!< DISP_T::MpuIntfCmd0: START Position*/
#define DISP_MpuIntfCmd0_START_Msk  (0x1ul << DISP_MpuIntfCmd0_START_Pos)        /*!< DISP_T::MpuIntfCmd0: START Mask   */

#define DISP_MpuIntfCmd0_CMD_Pos    (30)                                              /*!< DISP_T::MpuIntfCmd0: CMD Position */
#define DISP_MpuIntfCmd0_CMD_Msk    (0x3ul << DISP_MpuIntfCmd0_CMD_Pos)          /*!< DISP_T::MpuIntfCmd0: CMD Mask     */

#define DISP_MpuIntfReadPara00_DATA_Pos (0)                                           /*!< DISP_T::MpuIntfReadPara00: DATA Position*/
#define DISP_MpuIntfReadPara00_DATA_Msk (0x3fffful << DISP_MpuIntfReadPara00_DATA_Pos) /*!< DISP_T::MpuIntfReadPara00: DATA Mask*/

#define DISP_MpuIntfReadPara10_DATA_Pos (0)                                           /*!< DISP_T::MpuIntfReadPara10: DATA Position*/
#define DISP_MpuIntfReadPara10_DATA_Msk (0x3fffful << DISP_MpuIntfReadPara10_DATA_Pos) /*!< DISP_T::MpuIntfReadPara10: DATA Mask*/

#define DISP_MpuIntfReadPara20_DATA_Pos (0)                                           /*!< DISP_T::MpuIntfReadPara20: DATA Position*/
#define DISP_MpuIntfReadPara20_DATA_Msk (0x3fffful << DISP_MpuIntfReadPara20_DATA_Pos) /*!< DISP_T::MpuIntfReadPara20: DATA Mask*/

#define DISP_MpuIntfReadPara30_DATA_Pos (0)                                           /*!< DISP_T::MpuIntfReadPara30: DATA Position*/
#define DISP_MpuIntfReadPara30_DATA_Msk (0x3fffful << DISP_MpuIntfReadPara30_DATA_Pos) /*!< DISP_T::MpuIntfReadPara30: DATA Mask*/

#define DISP_MpuIntfReadPara40_DATA_Pos (0)                                           /*!< DISP_T::MpuIntfReadPara40: DATA Position*/
#define DISP_MpuIntfReadPara40_DATA_Msk (0x3fffful << DISP_MpuIntfReadPara40_DATA_Pos) /*!< DISP_T::MpuIntfReadPara40: DATA Mask*/

#define DISP_MpuIntfReadStatus0_DATA_Pos (0)                                          /*!< DISP_T::MpuIntfReadStatus0: DATA Position*/
#define DISP_MpuIntfReadStatus0_DATA_Msk (0x1ul << DISP_MpuIntfReadStatus0_DATA_Pos) /*!< DISP_T::MpuIntfReadStatus0: DATA Mask*/

#define DISP_MpuIntfConfig0_REGISTER_MODE_Pos (0)                                     /*!< DISP_T::MpuIntfConfig0: REGISTER_MODE Position*/
#define DISP_MpuIntfConfig0_REGISTER_MODE_Msk (0x1ul << DISP_MpuIntfConfig0_REGISTER_MODE_Pos) /*!< DISP_T::MpuIntfConfig0: REGISTER_MODE Mask*/

#define DISP_MpuIntfConfig0_DATA_BUS_WIDTH_Pos (1)                                    /*!< DISP_T::MpuIntfConfig0: DATA_BUS_WIDTH Position*/
#define DISP_MpuIntfConfig0_DATA_BUS_WIDTH_Msk (0x3ul << DISP_MpuIntfConfig0_DATA_BUS_WIDTH_Pos) /*!< DISP_T::MpuIntfConfig0: DATA_BUS_WIDTH Mask*/

#define DISP_MpuIntfConfig0_DATA_BUS_MODE_Pos (3)                                     /*!< DISP_T::MpuIntfConfig0: DATA_BUS_MODE Position*/
#define DISP_MpuIntfConfig0_DATA_BUS_MODE_Msk (0x1ul << DISP_MpuIntfConfig0_DATA_BUS_MODE_Pos) /*!< DISP_T::MpuIntfConfig0: DATA_BUS_MODE Mask*/

#define DISP_MpuIntfConfig0_INTERFACE_MODE_Pos (4)                                    /*!< DISP_T::MpuIntfConfig0: INTERFACE_MODE Position*/
#define DISP_MpuIntfConfig0_INTERFACE_MODE_Msk (0x1ul << DISP_MpuIntfConfig0_INTERFACE_MODE_Pos) /*!< DISP_T::MpuIntfConfig0: INTERFACE_MODE Mask*/

#define DISP_MpuIntfConfig0_ENABLE_VSYNC_Pos (5)                                      /*!< DISP_T::MpuIntfConfig0: ENABLE_VSYNC Position*/
#define DISP_MpuIntfConfig0_ENABLE_VSYNC_Msk (0x1ul << DISP_MpuIntfConfig0_ENABLE_VSYNC_Pos) /*!< DISP_T::MpuIntfConfig0: ENABLE_VSYNC Mask*/

#define DISP_MpuIntfConfig0_VSYNC_POLARITY_Pos (6)                                    /*!< DISP_T::MpuIntfConfig0: VSYNC_POLARITY Position*/
#define DISP_MpuIntfConfig0_VSYNC_POLARITY_Msk (0x1ul << DISP_MpuIntfConfig0_VSYNC_POLARITY_Pos) /*!< DISP_T::MpuIntfConfig0: VSYNC_POLARITY Mask*/

#define DISP_MpuIntfConfig0_ENABLE_TE_Pos (7)                                         /*!< DISP_T::MpuIntfConfig0: ENABLE_TE Position*/
#define DISP_MpuIntfConfig0_ENABLE_TE_Msk (0x1ul << DISP_MpuIntfConfig0_ENABLE_TE_Pos) /*!< DISP_T::MpuIntfConfig0: ENABLE_TE Mask*/

#define DISP_MpuIntfConfig0_TE_POLARITY_Pos (8)                                       /*!< DISP_T::MpuIntfConfig0: TE_POLARITY Position*/
#define DISP_MpuIntfConfig0_TE_POLARITY_Msk (0x1ul << DISP_MpuIntfConfig0_TE_POLARITY_Pos) /*!< DISP_T::MpuIntfConfig0: TE_POLARITY Mask*/

#define DISP_MpuIntfConfig0_DCX_POLARITY_Pos (9)                                      /*!< DISP_T::MpuIntfConfig0: DCX_POLARITY Position*/
#define DISP_MpuIntfConfig0_DCX_POLARITY_Msk (0x1ul << DISP_MpuIntfConfig0_DCX_POLARITY_Pos) /*!< DISP_T::MpuIntfConfig0: DCX_POLARITY Mask*/

#define DISP_MpuIntfConfig0_DATA_MODE24_BIT_Pos (10)                                  /*!< DISP_T::MpuIntfConfig0: DATA_MODE24_BIT Position*/
#define DISP_MpuIntfConfig0_DATA_MODE24_BIT_Msk (0x1ul << DISP_MpuIntfConfig0_DATA_MODE24_BIT_Pos) /*!< DISP_T::MpuIntfConfig0: DATA_MODE24_BIT Mask*/

#define DISP_MpuIntfConfig0_INTERFACE_RESET_Pos (11)                                  /*!< DISP_T::MpuIntfConfig0: INTERFACE_RESET Position*/
#define DISP_MpuIntfConfig0_INTERFACE_RESET_Msk (0x1ul << DISP_MpuIntfConfig0_INTERFACE_RESET_Pos) /*!< DISP_T::MpuIntfConfig0: INTERFACE_RESET Mask*/

#define DISP_MpuIntfConfig0_ENABLE_MPU_INTF_Pos (12)                                  /*!< DISP_T::MpuIntfConfig0: ENABLE_MPU_INTF Position*/
#define DISP_MpuIntfConfig0_ENABLE_MPU_INTF_Msk (0x1ul << DISP_MpuIntfConfig0_ENABLE_MPU_INTF_Pos) /*!< DISP_T::MpuIntfConfig0: ENABLE_MPU_INTF Mask*/

#define DISP_MpuIntfFrame0_FRAME_UPDATE_Pos (0)                                       /*!< DISP_T::MpuIntfFrame0: FRAME_UPDATE Position*/
#define DISP_MpuIntfFrame0_FRAME_UPDATE_Msk (0x1ul << DISP_MpuIntfFrame0_FRAME_UPDATE_Pos) /*!< DISP_T::MpuIntfFrame0: FRAME_UPDATE Mask*/

#define DISP_MpuIntfFrame0_DATA_FORMAT_Pos (1)                                        /*!< DISP_T::MpuIntfFrame0: DATA_FORMAT Position*/
#define DISP_MpuIntfFrame0_DATA_FORMAT_Msk (0x3ul << DISP_MpuIntfFrame0_DATA_FORMAT_Pos) /*!< DISP_T::MpuIntfFrame0: DATA_FORMAT Mask*/

#define DISP_MpuIntfFrame0_MPU_WRITE_BACK_Pos (3)                                     /*!< DISP_T::MpuIntfFrame0: MPU_WRITE_BACK Position*/
#define DISP_MpuIntfFrame0_MPU_WRITE_BACK_Msk (0x1ul << DISP_MpuIntfFrame0_MPU_WRITE_BACK_Pos) /*!< DISP_T::MpuIntfFrame0: MPU_WRITE_BACK Mask*/

#define DISP_MpuIntfACWrI800_WR_PERIOD_I80_Pos (0)                                    /*!< DISP_T::MpuIntfACWrI800: WR_PERIOD_I80 Position*/
#define DISP_MpuIntfACWrI800_WR_PERIOD_I80_Msk (0x3fful << DISP_MpuIntfACWrI800_WR_PERIOD_I80_Pos) /*!< DISP_T::MpuIntfACWrI800: WR_PERIOD_I80 Mask*/

#define DISP_MpuIntfACWrI800_WRX_ASSERT_Pos (10)                                      /*!< DISP_T::MpuIntfACWrI800: WRX_ASSERT Position*/
#define DISP_MpuIntfACWrI800_WRX_ASSERT_Msk (0x3fful << DISP_MpuIntfACWrI800_WRX_ASSERT_Pos) /*!< DISP_T::MpuIntfACWrI800: WRX_ASSERT Mask*/

#define DISP_MpuIntfACWrI800_WRX_DE_ASSERT_Pos (20)                                   /*!< DISP_T::MpuIntfACWrI800: WRX_DE_ASSERT Position*/
#define DISP_MpuIntfACWrI800_WRX_DE_ASSERT_Msk (0x3fful << DISP_MpuIntfACWrI800_WRX_DE_ASSERT_Pos) /*!< DISP_T::MpuIntfACWrI800: WRX_DE_ASSERT Mask*/

#define DISP_MpuIntfACRdI800_RD_PERIOD_I80_Pos (0)                                    /*!< DISP_T::MpuIntfACRdI800: RD_PERIOD_I80 Position*/
#define DISP_MpuIntfACRdI800_RD_PERIOD_I80_Msk (0x3fful << DISP_MpuIntfACRdI800_RD_PERIOD_I80_Pos) /*!< DISP_T::MpuIntfACRdI800: RD_PERIOD_I80 Mask*/

#define DISP_MpuIntfACRdI800_RDX_ASSERT_Pos (10)                                      /*!< DISP_T::MpuIntfACRdI800: RDX_ASSERT Position*/
#define DISP_MpuIntfACRdI800_RDX_ASSERT_Msk (0x3fful << DISP_MpuIntfACRdI800_RDX_ASSERT_Pos) /*!< DISP_T::MpuIntfACRdI800: RDX_ASSERT Mask*/

#define DISP_MpuIntfACRdI800_RDX_DE_ASSERT_Pos (20)                                   /*!< DISP_T::MpuIntfACRdI800: RDX_DE_ASSERT Position*/
#define DISP_MpuIntfACRdI800_RDX_DE_ASSERT_Msk (0x3fful << DISP_MpuIntfACRdI800_RDX_DE_ASSERT_Pos) /*!< DISP_T::MpuIntfACRdI800: RDX_DE_ASSERT Mask*/

#define DISP_MpuIntfACWrM680_WR_PERIOD_M68_Pos (0)                                    /*!< DISP_T::MpuIntfACWrM680: WR_PERIOD_M68 Position*/
#define DISP_MpuIntfACWrM680_WR_PERIOD_M68_Msk (0x3fful << DISP_MpuIntfACWrM680_WR_PERIOD_M68_Pos) /*!< DISP_T::MpuIntfACWrM680: WR_PERIOD_M68 Mask*/

#define DISP_MpuIntfACWrM680_WR_EASSERT_Pos (10)                                      /*!< DISP_T::MpuIntfACWrM680: WR_EASSERT Position*/
#define DISP_MpuIntfACWrM680_WR_EASSERT_Msk (0x3fful << DISP_MpuIntfACWrM680_WR_EASSERT_Pos) /*!< DISP_T::MpuIntfACWrM680: WR_EASSERT Mask*/

#define DISP_MpuIntfACWrM680_WR_EDE_ASSERT_Pos (20)                                   /*!< DISP_T::MpuIntfACWrM680: WR_EDE_ASSERT Position*/
#define DISP_MpuIntfACWrM680_WR_EDE_ASSERT_Msk (0x3fful << DISP_MpuIntfACWrM680_WR_EDE_ASSERT_Pos) /*!< DISP_T::MpuIntfACWrM680: WR_EDE_ASSERT Mask*/

#define DISP_MpuIntfACRdM680_RD_PERIOD_I80_Pos (0)                                    /*!< DISP_T::MpuIntfACRdM680: RD_PERIOD_I80 Position*/
#define DISP_MpuIntfACRdM680_RD_PERIOD_I80_Msk (0x3fful << DISP_MpuIntfACRdM680_RD_PERIOD_I80_Pos) /*!< DISP_T::MpuIntfACRdM680: RD_PERIOD_I80 Mask*/

#define DISP_MpuIntfACRdM680_RDX_ASSERT_Pos (10)                                      /*!< DISP_T::MpuIntfACRdM680: RDX_ASSERT Position*/
#define DISP_MpuIntfACRdM680_RDX_ASSERT_Msk (0x3fful << DISP_MpuIntfACRdM680_RDX_ASSERT_Pos) /*!< DISP_T::MpuIntfACRdM680: RDX_ASSERT Mask*/

#define DISP_MpuIntfACRdM680_RDX_DE_ASSERT_Pos (20)                                   /*!< DISP_T::MpuIntfACRdM680: RDX_DE_ASSERT Position*/
#define DISP_MpuIntfACRdM680_RDX_DE_ASSERT_Msk (0x3fful << DISP_MpuIntfACRdM680_RDX_DE_ASSERT_Pos) /*!< DISP_T::MpuIntfACRdM680: RDX_DE_ASSERT Mask*/

#define DISP_MpuIntfACVsyncCSX0_CSX_ASSERT_Pos (0)                                    /*!< DISP_T::MpuIntfACVsyncCSX0: CSX_ASSERT Position*/
#define DISP_MpuIntfACVsyncCSX0_CSX_ASSERT_Msk (0x3fful << DISP_MpuIntfACVsyncCSX0_CSX_ASSERT_Pos) /*!< DISP_T::MpuIntfACVsyncCSX0: CSX_ASSERT Mask*/

/**@}*/ /* DISP_CONST */
/**@}*/ /* end of DISP register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif  //__DISP_REG_H__
