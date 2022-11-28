/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY¡¯S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS¡¯SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY¡¯S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __DMA_SUN8IW19_H__
#define __DMA_SUN8IW19_H__

#define SUNXI_DMAC_PBASE         0x03002000

#define DMA_IRQ_NUM 42

#define NR_MAX_CHAN 8   /* total of channels */
#define START_CHAN_OFFSET      0

#define SUNXI_CLK_DMA HAL_CLK_PERIPH_DMA
#define SUNXI_CLK_MBUS_DMA (0)
#define SUNXI_RST_DMA (0)


/*
 * The source DRQ type and port corresponding relation
 */
#define DRQSRC_SRAM     0
#define DRQSRC_SDRAM        0
/* #define DRQSRC_RESEVER       2 */
#define DRQSRC_DAUDIO_0_RX  3
#define DRQSRC_DAUDIO_1_RX  4
/*#define DRQSRC_DAUDIO_2_RX    5 */
#define DRQSRC_AUDIO_CODEC  6
#define DRQSRC_DMIC     7
/* #define DRQSRC_RESEVER       8 */
/* #define DRQSRC_RESEVER       9 */
/*#define DRQSRC_NAND0      10 */
/* #define DRQSRC_RESEVER       11 */
#define DRQSRC_GPADC        12
/* #define DRQSRC_RESEVER       13 */
#define DRQSRC_UART0_RX     14
#define DRQSRC_UART1_RX     15
#define DRQSRC_UART2_RX         16
#define DRQSRC_UART3_RX     17
/*#define DRQSRC_UART4_RX         18 */
/* #define DRQSRC_RESEVER       19 */
/* #define DRQSRC_RESEVER       20 */
/* #define DRQSRC_RESEVER       21 */
#define DRQSRC_SPI0_RX      22
#define DRQSRC_SPI1_RX      23
#define DRQSRC_SPI2_RX      24
/*#define DRQSRC_SPI3_RX    25 */
/* #define DRQSRC_RESEVER       26 */
/* #define DRQSRC_RESEVER       27 */
/* #define DRQSRC_RESEVER       28 */
/* #define DRQSRC_RESEVER       29 */
#define DRQSRC_OTG_EP1      30
#define DRQSRC_OTG_EP2      31
#define DRQSRC_OTG_EP3          32
#define DRQSRC_OTG_EP4          33
#define DRQSRC_OTG_EP5          34
#define DRQSRC_TWI0_RX      43
#define DRQSRC_TWI1_RX      44
#define DRQSRC_TWI2_RX      45
#define DRQSRC_TWI3_RX      46
#define DRQSRC_R_TWI0       48

/*
 * The destination DRQ type and port corresponding relation
 */
#define DRQDST_SRAM     0
#define DRQDST_SDRAM        0
/* #define DRQSRC_RESEVER       2 */
#define DRQDST_DAUDIO_0_TX  3
#define DRQDST_DAUDIO_1_TX  4
/*#define DRQDST_DAUDIO_2_TX    5 */
#define DRQDST_AUDIO_CODEC  6
/* #define DRQSRC_RESEVER       7 */
/* #define DRQSRC_RESEVER       8 */
/* #define DRQSRC_RESEVER       9 */
/*#define DRQDST_NAND0      10 */
/* #define DRQSRC_RESEVER       11*/
/* #define DRQSRC_RESEVER       12 */
/*#define DRQDST_IR_TX      13 */
#define DRQDST_UART0_TX     14
#define DRQDST_UART1_TX     15
#define DRQDST_UART2_TX         16
#define DRQDST_UART3_TX         17
/*#define DRQDST_UART4_TX       18 */
/* #define DRQSRC_RESEVER       19 */
/* #define DRQSRC_RESEVER       20 */
/* #define DRQSRC_RESEVER       21 */
#define DRQDST_SPI0_TX      22
#define DRQDST_SPI1_TX          23
#define DRQDST_SPI2_TX          24
/*#define DRQDST_SPI3_TX        25 */
/* #define DRQSRC_RESEVER       26 */
/* #define DRQSRC_RESEVER       27 */
/* #define DRQSRC_RESEVER       28 */
/* #define DRQSRC_RESEVER       29 */
#define DRQDST_OTG_EP1      30
#define DRQDST_OTG_EP2      31
#define DRQDST_OTG_EP3          32
#define DRQDST_OTG_EP4          33
#define DRQDST_OTG_EP5          34
#define DRQDST_TWI0_TX      43
#define DRQDST_TWI1_TX          44
#define DRQDST_TWI2_TX          45
#define DRQDST_TWI3_TX          46
#define DRQDST_R_TWI0       48


#endif /*__DMA_SUN8IW19_H__  */
