/*----------------------------------------------------------------------------+
|
|	This source code has been made available to you by IBM on an AS-IS
|	basis.	Anyone receiving this source is licensed under IBM
|	copyrights to use it in any way he or she deems fit, including
|	copying it, modifying it, compiling it, and redistributing it either
|	with or without modifications.	No license under IBM patents or
|	patent applications is to be implied by the copyright license.
|
|	Any user of this software should understand that IBM cannot provide
|	technical support for this software and will not be responsible for
|	any consequences resulting from the use of this software.
|
|	Any person who transfers this source code or any derivative work
|	must include the IBM copyright notice, this paragraph, and the
|	preceding two paragraphs in the transferred software.
|
|	COPYRIGHT   I B M   CORPORATION 1999
|	LICENSED MATERIAL  -  PROGRAM PROPERTY OF I B M
+----------------------------------------------------------------------------*/

#ifndef	__PPC405_H__
#define __PPC405_H__

/* Define bits and masks for real-mode storage attribute control registers */
#define PPC_128MB_SACR_BIT(addr)	((addr) >> 27)
#define PPC_128MB_SACR_VALUE(addr)	PPC_REG_VAL(PPC_128MB_SACR_BIT(addr),1)

/******************************************************************************
 * Special for PPC405GP
 ******************************************************************************/

/******************************************************************************
 * DMA
 ******************************************************************************/
#define DMA_DCR_BASE 0x100
#define dmacr0	(DMA_DCR_BASE+0x00)  /* DMA channel control register 0	     */
#define dmact0	(DMA_DCR_BASE+0x01)  /* DMA count register 0		     */
#define dmada0	(DMA_DCR_BASE+0x02)  /* DMA destination address register 0   */
#define dmasa0	(DMA_DCR_BASE+0x03)  /* DMA source address register 0	     */
#define dmasb0	(DMA_DCR_BASE+0x04)  /* DMA scatter/gather descriptor addr 0 */
#define dmacr1	(DMA_DCR_BASE+0x08)  /* DMA channel control register 1	     */
#define dmact1	(DMA_DCR_BASE+0x09)  /* DMA count register 1		     */
#define dmada1	(DMA_DCR_BASE+0x0a)  /* DMA destination address register 1   */
#define dmasa1	(DMA_DCR_BASE+0x0b)  /* DMA source address register 1	     */
#define dmasb1	(DMA_DCR_BASE+0x0c)  /* DMA scatter/gather descriptor addr 1 */
#define dmacr2	(DMA_DCR_BASE+0x10)  /* DMA channel control register 2	     */
#define dmact2	(DMA_DCR_BASE+0x11)  /* DMA count register 2		     */
#define dmada2	(DMA_DCR_BASE+0x12)  /* DMA destination address register 2   */
#define dmasa2	(DMA_DCR_BASE+0x13)  /* DMA source address register 2	     */
#define dmasb2	(DMA_DCR_BASE+0x14)  /* DMA scatter/gather descriptor addr 2 */
#define dmacr3	(DMA_DCR_BASE+0x18)  /* DMA channel control register 3	     */
#define dmact3	(DMA_DCR_BASE+0x19)  /* DMA count register 3		     */
#define dmada3	(DMA_DCR_BASE+0x1a)  /* DMA destination address register 3   */
#define dmasa3	(DMA_DCR_BASE+0x1b)  /* DMA source address register 3	     */
#define dmasb3	(DMA_DCR_BASE+0x1c)  /* DMA scatter/gather descriptor addr 3 */
#define dmasr	(DMA_DCR_BASE+0x20)  /* DMA status register		     */
#define dmasgc	(DMA_DCR_BASE+0x23)  /* DMA scatter/gather command register  */
#define dmaadr	(DMA_DCR_BASE+0x24)  /* DMA address decode register	     */

#ifndef CONFIG_405EP
/******************************************************************************
 * Decompression Controller
 ******************************************************************************/
#define DECOMP_DCR_BASE 0x14
#define kiar  (DECOMP_DCR_BASE+0x0)  /* Decompression controller addr reg    */
#define kidr  (DECOMP_DCR_BASE+0x1)  /* Decompression controller data reg    */
  /* values for kiar register - indirect addressing of these regs */
  #define kitor0      0x00    /* index table origin register 0	      */
  #define kitor1      0x01    /* index table origin register 1	      */
  #define kitor2      0x02    /* index table origin register 2	      */
  #define kitor3      0x03    /* index table origin register 3	      */
  #define kaddr0      0x04    /* address decode definition regsiter 0 */
  #define kaddr1      0x05    /* address decode definition regsiter 1 */
  #define kconf       0x40    /* decompression core config register   */
  #define kid	      0x41    /* decompression core ID	   register   */
  #define kver	      0x42    /* decompression core version # reg     */
  #define kpear       0x50    /* bus error addr reg (PLB addr)	      */
  #define kbear       0x51    /* bus error addr reg (DCP to EBIU addr)*/
  #define kesr0       0x52    /* bus error status reg 0  (R/clear)    */
  #define kesr0s      0x53    /* bus error status reg 0  (set)	      */
  /* There are 0x400 of the following registers, from krom0 to krom3ff*/
  /* Only the first one is given here.				      */
  #define krom0      0x400    /* SRAM/ROM read/write		      */
#endif

/******************************************************************************
 * Power Management
 ******************************************************************************/
#ifdef CONFIG_405EX
#define POWERMAN_DCR_BASE 0xb0
#else
#define POWERMAN_DCR_BASE 0xb8
#endif
#define cpmsr (POWERMAN_DCR_BASE+0x0) /* Power management status	     */
#define cpmer (POWERMAN_DCR_BASE+0x1) /* Power management enable	     */
#define cpmfr (POWERMAN_DCR_BASE+0x2) /* Power management force		     */

/******************************************************************************
 * Extrnal Bus Controller
 ******************************************************************************/
  /* values for ebccfga register - indirect addressing of these regs */
  #define pb0cr       0x00    /* periph bank 0 config reg	     */
  #define pb1cr       0x01    /* periph bank 1 config reg	     */
  #define pb2cr       0x02    /* periph bank 2 config reg	     */
  #define pb3cr       0x03    /* periph bank 3 config reg	     */
  #define pb4cr       0x04    /* periph bank 4 config reg	     */
#ifndef CONFIG_405EP
  #define pb5cr       0x05    /* periph bank 5 config reg	     */
  #define pb6cr       0x06    /* periph bank 6 config reg	     */
  #define pb7cr       0x07    /* periph bank 7 config reg	     */
#endif
  #define pb0ap       0x10    /* periph bank 0 access parameters     */
  #define pb1ap       0x11    /* periph bank 1 access parameters     */
  #define pb2ap       0x12    /* periph bank 2 access parameters     */
  #define pb3ap       0x13    /* periph bank 3 access parameters     */
  #define pb4ap       0x14    /* periph bank 4 access parameters     */
#ifndef CONFIG_405EP
  #define pb5ap       0x15    /* periph bank 5 access parameters     */
  #define pb6ap       0x16    /* periph bank 6 access parameters     */
  #define pb7ap       0x17    /* periph bank 7 access parameters     */
#endif
  #define pbear       0x20    /* periph bus error addr reg	     */
  #define pbesr0      0x21    /* periph bus error status reg 0	     */
  #define pbesr1      0x22    /* periph bus error status reg 1	     */
  #define epcr	      0x23    /* external periph control reg	     */
#define EBC0_CFG	0x23	/* external bus configuration reg	*/

#ifdef CONFIG_405EP
/******************************************************************************
 * Control
 ******************************************************************************/
#define CNTRL_DCR_BASE 0x0f0
#define cpc0_pllmr0   (CNTRL_DCR_BASE+0x0)  /* PLL mode  register 0		   */
#define cpc0_boot     (CNTRL_DCR_BASE+0x1)  /* Clock status register		   */
#define cpc0_epctl    (CNTRL_DCR_BASE+0x3)  /* EMAC to PHY control register	   */
#define cpc0_pllmr1   (CNTRL_DCR_BASE+0x4)  /* PLL mode  register 1		   */
#define cpc0_ucr      (CNTRL_DCR_BASE+0x5)  /* UART control register		   */
#define cpc0_pci      (CNTRL_DCR_BASE+0x9)  /* PCI control register		   */

#define CPC0_PLLMR0  (CNTRL_DCR_BASE+0x0)  /* PLL mode 0 register	   */
#define CPC0_BOOT    (CNTRL_DCR_BASE+0x1)  /* Chip Clock Status register   */
#define CPC0_CR1     (CNTRL_DCR_BASE+0x2)  /* Chip Control 1 register	   */
#define CPC0_EPRCSR  (CNTRL_DCR_BASE+0x3)  /* EMAC PHY Rcv Clk Src register*/
#define CPC0_PLLMR1  (CNTRL_DCR_BASE+0x4)  /* PLL mode 1 register	   */
#define CPC0_UCR     (CNTRL_DCR_BASE+0x5)  /* UART Control register	   */
#define CPC0_SRR     (CNTRL_DCR_BASE+0x6)  /* Soft Reset register	   */
#define CPC0_JTAGID  (CNTRL_DCR_BASE+0x7)  /* JTAG ID register		   */
#define CPC0_SPARE   (CNTRL_DCR_BASE+0x8)  /* Spare DCR			   */
#define CPC0_PCI     (CNTRL_DCR_BASE+0x9)  /* PCI Control register	   */

/* Bit definitions */
#define PLLMR0_CPU_DIV_MASK	 0x00300000	/* CPU clock divider */
#define PLLMR0_CPU_DIV_BYPASS	 0x00000000
#define PLLMR0_CPU_DIV_2	 0x00100000
#define PLLMR0_CPU_DIV_3	 0x00200000
#define PLLMR0_CPU_DIV_4	 0x00300000

#define PLLMR0_CPU_TO_PLB_MASK	 0x00030000	/* CPU:PLB Frequency Divisor */
#define PLLMR0_CPU_PLB_DIV_1	 0x00000000
#define PLLMR0_CPU_PLB_DIV_2	 0x00010000
#define PLLMR0_CPU_PLB_DIV_3	 0x00020000
#define PLLMR0_CPU_PLB_DIV_4	 0x00030000

#define PLLMR0_OPB_TO_PLB_MASK	 0x00003000	/* OPB:PLB Frequency Divisor */
#define PLLMR0_OPB_PLB_DIV_1	 0x00000000
#define PLLMR0_OPB_PLB_DIV_2	 0x00001000
#define PLLMR0_OPB_PLB_DIV_3	 0x00002000
#define PLLMR0_OPB_PLB_DIV_4	 0x00003000

#define PLLMR0_EXB_TO_PLB_MASK	 0x00000300	/* External Bus:PLB Divisor  */
#define PLLMR0_EXB_PLB_DIV_2	 0x00000000
#define PLLMR0_EXB_PLB_DIV_3	 0x00000100
#define PLLMR0_EXB_PLB_DIV_4	 0x00000200
#define PLLMR0_EXB_PLB_DIV_5	 0x00000300

#define PLLMR0_MAL_TO_PLB_MASK	 0x00000030	/* MAL:PLB Divisor  */
#define PLLMR0_MAL_PLB_DIV_1	 0x00000000
#define PLLMR0_MAL_PLB_DIV_2	 0x00000010
#define PLLMR0_MAL_PLB_DIV_3	 0x00000020
#define PLLMR0_MAL_PLB_DIV_4	 0x00000030

#define PLLMR0_PCI_TO_PLB_MASK	 0x00000003	/* PCI:PLB Frequency Divisor */
#define PLLMR0_PCI_PLB_DIV_1	 0x00000000
#define PLLMR0_PCI_PLB_DIV_2	 0x00000001
#define PLLMR0_PCI_PLB_DIV_3	 0x00000002
#define PLLMR0_PCI_PLB_DIV_4	 0x00000003

#define PLLMR1_SSCS_MASK	 0x80000000	/* Select system clock source */
#define PLLMR1_PLLR_MASK	 0x40000000	/* PLL reset */
#define PLLMR1_FBMUL_MASK	 0x00F00000	/* PLL feedback multiplier value */
#define PLLMR1_FBMUL_DIV_16	 0x00000000
#define PLLMR1_FBMUL_DIV_1	 0x00100000
#define PLLMR1_FBMUL_DIV_2	 0x00200000
#define PLLMR1_FBMUL_DIV_3	 0x00300000
#define PLLMR1_FBMUL_DIV_4	 0x00400000
#define PLLMR1_FBMUL_DIV_5	 0x00500000
#define PLLMR1_FBMUL_DIV_6	 0x00600000
#define PLLMR1_FBMUL_DIV_7	 0x00700000
#define PLLMR1_FBMUL_DIV_8	 0x00800000
#define PLLMR1_FBMUL_DIV_9	 0x00900000
#define PLLMR1_FBMUL_DIV_10	 0x00A00000
#define PLLMR1_FBMUL_DIV_11	 0x00B00000
#define PLLMR1_FBMUL_DIV_12	 0x00C00000
#define PLLMR1_FBMUL_DIV_13	 0x00D00000
#define PLLMR1_FBMUL_DIV_14	 0x00E00000
#define PLLMR1_FBMUL_DIV_15	 0x00F00000

#define PLLMR1_FWDVA_MASK	 0x00070000	/* PLL forward divider A value */
#define PLLMR1_FWDVA_DIV_8	 0x00000000
#define PLLMR1_FWDVA_DIV_7	 0x00010000
#define PLLMR1_FWDVA_DIV_6	 0x00020000
#define PLLMR1_FWDVA_DIV_5	 0x00030000
#define PLLMR1_FWDVA_DIV_4	 0x00040000
#define PLLMR1_FWDVA_DIV_3	 0x00050000
#define PLLMR1_FWDVA_DIV_2	 0x00060000
#define PLLMR1_FWDVA_DIV_1	 0x00070000
#define PLLMR1_FWDVB_MASK	 0x00007000	/* PLL forward divider B value */
#define PLLMR1_TUNING_MASK	 0x000003FF	/* PLL tune bits */

/* Defines for CPC0_EPRCSR register */
#define CPC0_EPRCSR_E0NFE	   0x80000000
#define CPC0_EPRCSR_E1NFE	   0x40000000
#define CPC0_EPRCSR_E1RPP	   0x00000080
#define CPC0_EPRCSR_E0RPP	   0x00000040
#define CPC0_EPRCSR_E1ERP	   0x00000020
#define CPC0_EPRCSR_E0ERP	   0x00000010
#define CPC0_EPRCSR_E1PCI	   0x00000002
#define CPC0_EPRCSR_E0PCI	   0x00000001

/* Defines for CPC0_PCI Register */
#define CPC0_PCI_SPE			   0x00000010 /* PCIINT/WE select	*/
#define CPC0_PCI_HOST_CFG_EN		   0x00000008 /* PCI host config Enable */
#define CPC0_PCI_ARBIT_EN		   0x00000001 /* PCI Internal Arb Enabled*/

/* Defines for CPC0_BOOR Register */
#define CPC0_BOOT_SEP			   0x00000002 /* serial EEPROM present	*/

/* Defines for CPC0_PLLMR1 Register fields */
#define PLL_ACTIVE		   0x80000000
#define CPC0_PLLMR1_SSCS	   0x80000000
#define PLL_RESET		   0x40000000
#define CPC0_PLLMR1_PLLR	   0x40000000
    /* Feedback multiplier */
#define PLL_FBKDIV		   0x00F00000
#define CPC0_PLLMR1_FBDV	   0x00F00000
#define PLL_FBKDIV_16		   0x00000000
#define PLL_FBKDIV_1		   0x00100000
#define PLL_FBKDIV_2		   0x00200000
#define PLL_FBKDIV_3		   0x00300000
#define PLL_FBKDIV_4		   0x00400000
#define PLL_FBKDIV_5		   0x00500000
#define PLL_FBKDIV_6		   0x00600000
#define PLL_FBKDIV_7		   0x00700000
#define PLL_FBKDIV_8		   0x00800000
#define PLL_FBKDIV_9		   0x00900000
#define PLL_FBKDIV_10		   0x00A00000
#define PLL_FBKDIV_11		   0x00B00000
#define PLL_FBKDIV_12		   0x00C00000
#define PLL_FBKDIV_13		   0x00D00000
#define PLL_FBKDIV_14		   0x00E00000
#define PLL_FBKDIV_15		   0x00F00000
    /* Forward A divisor */
#define PLL_FWDDIVA		   0x00070000
#define CPC0_PLLMR1_FWDVA	   0x00070000
#define PLL_FWDDIVA_8		   0x00000000
#define PLL_FWDDIVA_7		   0x00010000
#define PLL_FWDDIVA_6		   0x00020000
#define PLL_FWDDIVA_5		   0x00030000
#define PLL_FWDDIVA_4		   0x00040000
#define PLL_FWDDIVA_3		   0x00050000
#define PLL_FWDDIVA_2		   0x00060000
#define PLL_FWDDIVA_1		   0x00070000
    /* Forward B divisor */
#define PLL_FWDDIVB		   0x00007000
#define CPC0_PLLMR1_FWDVB	   0x00007000
#define PLL_FWDDIVB_8		   0x00000000
#define PLL_FWDDIVB_7		   0x00001000
#define PLL_FWDDIVB_6		   0x00002000
#define PLL_FWDDIVB_5		   0x00003000
#define PLL_FWDDIVB_4		   0x00004000
#define PLL_FWDDIVB_3		   0x00005000
#define PLL_FWDDIVB_2		   0x00006000
#define PLL_FWDDIVB_1		   0x00007000
    /* PLL tune bits */
#define PLL_TUNE_MASK		 0x000003FF
#define PLL_TUNE_2_M_3		 0x00000133	/*  2 <= M <= 3		      */
#define PLL_TUNE_4_M_6		 0x00000134	/*  3 <  M <= 6		      */
#define PLL_TUNE_7_M_10		 0x00000138	/*  6 <  M <= 10	      */
#define PLL_TUNE_11_M_14	 0x0000013C	/* 10 <  M <= 14	      */
#define PLL_TUNE_15_M_40	 0x0000023E	/* 14 <  M <= 40	      */
#define PLL_TUNE_VCO_LOW	 0x00000000	/* 500MHz <= VCO <=  800MHz   */
#define PLL_TUNE_VCO_HI		 0x00000080	/* 800MHz <  VCO <= 1000MHz   */

/* Defines for CPC0_PLLMR0 Register fields */
    /* CPU divisor */
#define PLL_CPUDIV		   0x00300000
#define CPC0_PLLMR0_CCDV	   0x00300000
#define PLL_CPUDIV_1		   0x00000000
#define PLL_CPUDIV_2		   0x00100000
#define PLL_CPUDIV_3		   0x00200000
#define PLL_CPUDIV_4		   0x00300000
    /* PLB divisor */
#define PLL_PLBDIV		   0x00030000
#define CPC0_PLLMR0_CBDV	   0x00030000
#define PLL_PLBDIV_1		   0x00000000
#define PLL_PLBDIV_2		   0x00010000
#define PLL_PLBDIV_3		   0x00020000
#define PLL_PLBDIV_4		   0x00030000
    /* OPB divisor */
#define PLL_OPBDIV		   0x00003000
#define CPC0_PLLMR0_OPDV	   0x00003000
#define PLL_OPBDIV_1		   0x00000000
#define PLL_OPBDIV_2		   0x00001000
#define PLL_OPBDIV_3		   0x00002000
#define PLL_OPBDIV_4		   0x00003000
    /* EBC divisor */
#define PLL_EXTBUSDIV		   0x00000300
#define CPC0_PLLMR0_EPDV	   0x00000300
#define PLL_EXTBUSDIV_2		   0x00000000
#define PLL_EXTBUSDIV_3		   0x00000100
#define PLL_EXTBUSDIV_4		   0x00000200
#define PLL_EXTBUSDIV_5		   0x00000300
    /* MAL divisor */
#define PLL_MALDIV		   0x00000030
#define CPC0_PLLMR0_MPDV	   0x00000030
#define PLL_MALDIV_1		   0x00000000
#define PLL_MALDIV_2		   0x00000010
#define PLL_MALDIV_3		   0x00000020
#define PLL_MALDIV_4		   0x00000030
    /* PCI divisor */
#define PLL_PCIDIV		   0x00000003
#define CPC0_PLLMR0_PPFD	   0x00000003
#define PLL_PCIDIV_1		   0x00000000
#define PLL_PCIDIV_2		   0x00000001
#define PLL_PCIDIV_3		   0x00000002
#define PLL_PCIDIV_4		   0x00000003

/*
 *-------------------------------------------------------------------------------
 * PLL settings for 266MHz CPU, 133MHz PLB/SDRAM, 66MHz EBC, 33MHz PCI,
 * assuming a 33.3MHz input clock to the 405EP.
 *-------------------------------------------------------------------------------
 */
#define PLLMR0_266_133_66  (PLL_CPUDIV_1 | PLL_PLBDIV_2 |  \
			    PLL_OPBDIV_2 | PLL_EXTBUSDIV_2 |  \
			    PLL_MALDIV_1 | PLL_PCIDIV_4)
#define PLLMR1_266_133_66  (PLL_FBKDIV_8  |  \
			    PLL_FWDDIVA_3 | PLL_FWDDIVB_3 |  \
			    PLL_TUNE_15_M_40 | PLL_TUNE_VCO_LOW)

#define PLLMR0_133_66_66_33  (PLL_CPUDIV_1 | PLL_PLBDIV_1 |  \
			      PLL_OPBDIV_2 | PLL_EXTBUSDIV_4 |	\
			      PLL_MALDIV_1 | PLL_PCIDIV_4)
#define PLLMR1_133_66_66_33  (PLL_FBKDIV_4  |  \
			      PLL_FWDDIVA_6 | PLL_FWDDIVB_6 |  \
			      PLL_TUNE_15_M_40 | PLL_TUNE_VCO_LOW)
#define PLLMR0_200_100_50_33 (PLL_CPUDIV_1 | PLL_PLBDIV_2 |  \
			      PLL_OPBDIV_2 | PLL_EXTBUSDIV_3 |	\
			      PLL_MALDIV_1 | PLL_PCIDIV_4)
#define PLLMR1_200_100_50_33 (PLL_FBKDIV_6  |  \
			      PLL_FWDDIVA_4 | PLL_FWDDIVB_4 |  \
			      PLL_TUNE_15_M_40 | PLL_TUNE_VCO_LOW)
#define PLLMR0_266_133_66_33 (PLL_CPUDIV_1 | PLL_PLBDIV_2 |  \
			      PLL_OPBDIV_2 | PLL_EXTBUSDIV_4 |	\
			      PLL_MALDIV_1 | PLL_PCIDIV_4)
#define PLLMR1_266_133_66_33 (PLL_FBKDIV_8  |  \
			      PLL_FWDDIVA_3 | PLL_FWDDIVB_3 |  \
			      PLL_TUNE_15_M_40 | PLL_TUNE_VCO_LOW)
#define PLLMR0_266_66_33_33 (PLL_CPUDIV_1 | PLL_PLBDIV_4 |  \
			      PLL_OPBDIV_2 | PLL_EXTBUSDIV_2 |	\
			      PLL_MALDIV_1 | PLL_PCIDIV_2)
#define PLLMR1_266_66_33_33 (PLL_FBKDIV_8  |  \
			      PLL_FWDDIVA_3 | PLL_FWDDIVB_3 |  \
			      PLL_TUNE_15_M_40 | PLL_TUNE_VCO_LOW)
#define PLLMR0_333_111_55_37 (PLL_CPUDIV_1 | PLL_PLBDIV_3 |  \
			      PLL_OPBDIV_2 | PLL_EXTBUSDIV_2 |	\
			      PLL_MALDIV_1 | PLL_PCIDIV_3)
#define PLLMR1_333_111_55_37 (PLL_FBKDIV_10  |	\
			      PLL_FWDDIVA_3 | PLL_FWDDIVB_3 |  \
			      PLL_TUNE_15_M_40 | PLL_TUNE_VCO_HI)
#define PLLMR0_333_111_55_111 (PLL_CPUDIV_1 | PLL_PLBDIV_3 |  \
			      PLL_OPBDIV_2 | PLL_EXTBUSDIV_2 |	\
			      PLL_MALDIV_1 | PLL_PCIDIV_1)
#define PLLMR1_333_111_55_111 (PLL_FBKDIV_10  |  \
			      PLL_FWDDIVA_3 | PLL_FWDDIVB_3 |  \
			      PLL_TUNE_15_M_40 | PLL_TUNE_VCO_HI)

/*
 * PLL Voltage Controlled Oscillator (VCO) definitions
 * Maximum and minimum values (in MHz) for correct PLL operation.
 */
#define VCO_MIN     500
#define VCO_MAX     1000
#elif defined(CONFIG_405EZ)
#define sdrnand0	0x4000
#define sdrultra0	0x4040
#define sdrultra1	0x4050
#define sdricintstat	0x4510

#define SDR_NAND0_NDEN		0x80000000
#define SDR_NAND0_NDBTEN	0x40000000
#define SDR_NAND0_NDBADR_MASK	0x30000000
#define SDR_NAND0_NDBPG_MASK	0x0f000000
#define SDR_NAND0_NDAREN	0x00800000
#define SDR_NAND0_NDRBEN	0x00400000

#define SDR_ULTRA0_NDGPIOBP	0x80000000
#define SDR_ULTRA0_CSN_MASK	0x78000000
#define SDR_ULTRA0_CSNSEL0	0x40000000
#define SDR_ULTRA0_CSNSEL1	0x20000000
#define SDR_ULTRA0_CSNSEL2	0x10000000
#define SDR_ULTRA0_CSNSEL3	0x08000000
#define SDR_ULTRA0_EBCRDYEN	0x04000000
#define SDR_ULTRA0_SPISSINEN	0x02000000
#define SDR_ULTRA0_NFSRSTEN	0x01000000

#define SDR_ULTRA1_LEDNENABLE	0x40000000

#define SDR_ICRX_STAT	0x80000000
#define SDR_ICTX0_STAT	0x40000000
#define SDR_ICTX1_STAT	0x20000000

#define SDR_PINSTP	0x40

/******************************************************************************
 * Control
 ******************************************************************************/
/* CPR Registers */
#define cprclkupd	0x020		/* CPR_CLKUPD */
#define cprpllc		0x040		/* CPR_PLLC */
#define cprplld		0x060		/* CPR_PLLD */
#define cprprimad	0x080		/* CPR_PRIMAD */
#define cprperd0	0x0e0		/* CPR_PERD0 */
#define cprperd1	0x0e1		/* CPR_PERD1 */
#define cprperc0	0x180		/* CPR_PERC0 */
#define cprmisc0	0x181		/* CPR_MISC0 */
#define cprmisc1	0x182		/* CPR_MISC1 */

#define CPR_CLKUPD_ENPLLCH_EN  0x40000000     /* Enable CPR PLL Changes */
#define CPR_CLKUPD_ENDVCH_EN   0x20000000     /* Enable CPR Sys. Div. Changes */
#define CPR_PERD0_SPIDV_MASK   0x000F0000     /* SPI Clock Divider */

#define PLLC_SRC_MASK	       0x20000000     /* PLL feedback source */

#define PLLD_FBDV_MASK	       0x1F000000     /* PLL feedback divider value */
#define PLLD_FWDVA_MASK        0x000F0000     /* PLL forward divider A value */
#define PLLD_FWDVB_MASK        0x00000700     /* PLL forward divider B value */

#define PRIMAD_CPUDV_MASK      0x0F000000     /* CPU Clock Divisor Mask */
#define PRIMAD_PLBDV_MASK      0x000F0000     /* PLB Clock Divisor Mask */
#define PRIMAD_OPBDV_MASK      0x00000F00     /* OPB Clock Divisor Mask */
#define PRIMAD_EBCDV_MASK      0x0000000F     /* EBC Clock Divisor Mask */

#define PERD0_PWMDV_MASK       0xFF000000     /* PWM Divider Mask */
#define PERD0_SPIDV_MASK       0x000F0000     /* SPI Divider Mask */
#define PERD0_U0DV_MASK        0x0000FF00     /* UART 0 Divider Mask */
#define PERD0_U1DV_MASK        0x000000FF     /* UART 1 Divider Mask */

#else /* #ifdef CONFIG_405EP */
/******************************************************************************
 * Control
 ******************************************************************************/
#define CNTRL_DCR_BASE 0x0b0
#define pllmd	(CNTRL_DCR_BASE+0x0)  /* PLL mode  register		     */
#define cntrl0	(CNTRL_DCR_BASE+0x1)  /* Control 0 register		     */
#define cntrl1	(CNTRL_DCR_BASE+0x2)  /* Control 1 register		     */
#define reset	(CNTRL_DCR_BASE+0x3)  /* reset register			     */
#define strap	(CNTRL_DCR_BASE+0x4)  /* strap register			     */

#define CPC0_CR0  (CNTRL_DCR_BASE+0x1)	/* chip control register 0	     */
#define CPC0_CR1  (CNTRL_DCR_BASE+0x2)	/* chip control register 1	     */
#define CPC0_PSR  (CNTRL_DCR_BASE+0x4)	/* chip pin strapping register	     */

/* CPC0_ECR/CPC0_EIRR: PPC405GPr only */
#define CPC0_EIRR (CNTRL_DCR_BASE+0x6)	/* external interrupt routing register */
#define CPC0_ECR  (0xaa)		/* edge conditioner register */

#define ecr	(0xaa)		      /* edge conditioner register (405gpr)  */

/* Bit definitions */
#define PLLMR_FWD_DIV_MASK	0xE0000000     /* Forward Divisor */
#define PLLMR_FWD_DIV_BYPASS	0xE0000000
#define PLLMR_FWD_DIV_3		0xA0000000
#define PLLMR_FWD_DIV_4		0x80000000
#define PLLMR_FWD_DIV_6		0x40000000

#define PLLMR_FB_DIV_MASK	0x1E000000     /* Feedback Divisor */
#define PLLMR_FB_DIV_1		0x02000000
#define PLLMR_FB_DIV_2		0x04000000
#define PLLMR_FB_DIV_3		0x06000000
#define PLLMR_FB_DIV_4		0x08000000

#define PLLMR_TUNING_MASK	0x01F80000

#define PLLMR_CPU_TO_PLB_MASK	0x00060000     /* CPU:PLB Frequency Divisor */
#define PLLMR_CPU_PLB_DIV_1	0x00000000
#define PLLMR_CPU_PLB_DIV_2	0x00020000
#define PLLMR_CPU_PLB_DIV_3	0x00040000
#define PLLMR_CPU_PLB_DIV_4	0x00060000

#define PLLMR_OPB_TO_PLB_MASK	0x00018000     /* OPB:PLB Frequency Divisor */
#define PLLMR_OPB_PLB_DIV_1	0x00000000
#define PLLMR_OPB_PLB_DIV_2	0x00008000
#define PLLMR_OPB_PLB_DIV_3	0x00010000
#define PLLMR_OPB_PLB_DIV_4	0x00018000

#define PLLMR_PCI_TO_PLB_MASK	0x00006000     /* PCI:PLB Frequency Divisor */
#define PLLMR_PCI_PLB_DIV_1	0x00000000
#define PLLMR_PCI_PLB_DIV_2	0x00002000
#define PLLMR_PCI_PLB_DIV_3	0x00004000
#define PLLMR_PCI_PLB_DIV_4	0x00006000

#define PLLMR_EXB_TO_PLB_MASK	0x00001800     /* External Bus:PLB Divisor  */
#define PLLMR_EXB_PLB_DIV_2	0x00000000
#define PLLMR_EXB_PLB_DIV_3	0x00000800
#define PLLMR_EXB_PLB_DIV_4	0x00001000
#define PLLMR_EXB_PLB_DIV_5	0x00001800

/* definitions for PPC405GPr (new mode strapping) */
#define PLLMR_FWDB_DIV_MASK	0x00000007     /* Forward Divisor B */

#define PSR_PLL_FWD_MASK	0xC0000000
#define PSR_PLL_FDBACK_MASK	0x30000000
#define PSR_PLL_TUNING_MASK	0x0E000000
#define PSR_PLB_CPU_MASK	0x01800000
#define PSR_OPB_PLB_MASK	0x00600000
#define PSR_PCI_PLB_MASK	0x00180000
#define PSR_EB_PLB_MASK		0x00060000
#define PSR_ROM_WIDTH_MASK	0x00018000
#define PSR_ROM_LOC		0x00004000
#define PSR_PCI_ASYNC_EN	0x00001000
#define PSR_PERCLK_SYNC_MODE_EN 0x00000800     /* PPC405GPr only */
#define PSR_PCI_ARBIT_EN	0x00000400
#define PSR_NEW_MODE_EN		0x00000020     /* PPC405GPr only */

#ifndef CONFIG_IOP480
/*
 * PLL Voltage Controlled Oscillator (VCO) definitions
 * Maximum and minimum values (in MHz) for correct PLL operation.
 */
#define VCO_MIN     400
#define VCO_MAX     800
#endif /* #ifndef CONFIG_IOP480 */
#endif /* #ifdef CONFIG_405EP */

/******************************************************************************
 * Memory Access Layer
 ******************************************************************************/
#if defined(CONFIG_405EZ)
#define	MAL_DCR_BASE	0x380
#define	malmcr		(MAL_DCR_BASE+0x00)	/* MAL Config reg	      */
#define	malesr		(MAL_DCR_BASE+0x01)	/* Err Status reg (Read/Clear)*/
#define	malier		(MAL_DCR_BASE+0x02)	/* Interrupt enable reg	      */
#define	maldbr		(MAL_DCR_BASE+0x03)	/* Mal Debug reg (Read only)  */
#define	maltxcasr	(MAL_DCR_BASE+0x04)	/* TX Channel active reg (set)*/
#define	maltxcarr	(MAL_DCR_BASE+0x05)	/* TX Channel active reg (Reset)     */
#define	maltxeobisr	(MAL_DCR_BASE+0x06)	/* TX End of buffer int status reg   */
#define	maltxdeir	(MAL_DCR_BASE+0x07)	/* TX Descr. Error Int reg    */
/*				      0x08-0x0F	   Reserved		      */
#define	malrxcasr	(MAL_DCR_BASE+0x10)	/* RX Channel active reg (set)*/
#define	malrxcarr	(MAL_DCR_BASE+0x11)	/* RX Channel active reg (Reset)     */
#define	malrxeobisr	(MAL_DCR_BASE+0x12)	/* RX End of buffer int status reg   */
#define	malrxdeir	(MAL_DCR_BASE+0x13)	/* RX Descr. Error Int reg  */
/*				      0x14-0x1F	   Reserved		    */
#define	maltxctp0r	(MAL_DCR_BASE+0x20)  /* TX 0 Channel table ptr reg  */
#define	maltxctp1r	(MAL_DCR_BASE+0x21)  /* TX 1 Channel table ptr reg  */
#define	maltxctp2r	(MAL_DCR_BASE+0x22)  /* TX 2 Channel table ptr reg  */
#define	maltxctp3r	(MAL_DCR_BASE+0x23)  /* TX 3 Channel table ptr reg  */
#define	maltxctp4r	(MAL_DCR_BASE+0x24)  /* TX 4 Channel table ptr reg  */
#define	maltxctp5r	(MAL_DCR_BASE+0x25)  /* TX 5 Channel table ptr reg  */
#define	maltxctp6r	(MAL_DCR_BASE+0x26)  /* TX 6 Channel table ptr reg  */
#define	maltxctp7r	(MAL_DCR_BASE+0x27)  /* TX 7 Channel table ptr reg  */
#define	maltxctp8r	(MAL_DCR_BASE+0x28)  /* TX 8 Channel table ptr reg  */
#define	maltxctp9r	(MAL_DCR_BASE+0x29)  /* TX 9 Channel table ptr reg  */
#define	maltxctp10r	(MAL_DCR_BASE+0x2A)  /* TX 10 Channel table ptr reg */
#define	maltxctp11r	(MAL_DCR_BASE+0x2B)  /* TX 11 Channel table ptr reg */
#define	maltxctp12r	(MAL_DCR_BASE+0x2C)  /* TX 12 Channel table ptr reg */
#define	maltxctp13r	(MAL_DCR_BASE+0x2D)  /* TX 13 Channel table ptr reg */
#define	maltxctp14r	(MAL_DCR_BASE+0x2E)  /* TX 14 Channel table ptr reg */
#define	maltxctp15r	(MAL_DCR_BASE+0x2F)  /* TX 15 Channel table ptr reg */
#define	maltxctp16r	(MAL_DCR_BASE+0x30)  /* TX 16 Channel table ptr reg */
#define	maltxctp17r	(MAL_DCR_BASE+0x31)  /* TX 17 Channel table ptr reg */
#define	maltxctp18r	(MAL_DCR_BASE+0x32)  /* TX 18 Channel table ptr reg */
#define	maltxctp19r	(MAL_DCR_BASE+0x33)  /* TX 19 Channel table ptr reg */
#define	maltxctp20r	(MAL_DCR_BASE+0x34)  /* TX 20 Channel table ptr reg */
#define	maltxctp21r	(MAL_DCR_BASE+0x35)  /* TX 21 Channel table ptr reg */
#define	maltxctp22r	(MAL_DCR_BASE+0x36)  /* TX 22 Channel table ptr reg */
#define	maltxctp23r	(MAL_DCR_BASE+0x37)  /* TX 23 Channel table ptr reg */
#define	maltxctp24r	(MAL_DCR_BASE+0x38)  /* TX 24 Channel table ptr reg */
#define	maltxctp25r	(MAL_DCR_BASE+0x39)  /* TX 25 Channel table ptr reg */
#define	maltxctp26r	(MAL_DCR_BASE+0x3A)  /* TX 26 Channel table ptr reg */
#define	maltxctp27r	(MAL_DCR_BASE+0x3B)  /* TX 27 Channel table ptr reg */
#define	maltxctp28r	(MAL_DCR_BASE+0x3C)  /* TX 28 Channel table ptr reg */
#define	maltxctp29r	(MAL_DCR_BASE+0x3D)  /* TX 29 Channel table ptr reg */
#define	maltxctp30r	(MAL_DCR_BASE+0x3E)  /* TX 30 Channel table ptr reg */
#define	maltxctp31r	(MAL_DCR_BASE+0x3F)  /* TX 31 Channel table ptr reg */
#define	malrxctp0r	(MAL_DCR_BASE+0x40)  /* RX 0 Channel table ptr reg  */
#define	malrxctp1r	(MAL_DCR_BASE+0x41)  /* RX 1 Channel table ptr reg  */
#define	malrxctp2r	(MAL_DCR_BASE+0x42)  /* RX 2 Channel table ptr reg  */
#define	malrxctp3r	(MAL_DCR_BASE+0x43)  /* RX 3 Channel table ptr reg  */
#define	malrxctp4r	(MAL_DCR_BASE+0x44)  /* RX 4 Channel table ptr reg  */
#define	malrxctp5r	(MAL_DCR_BASE+0x45)  /* RX 5 Channel table ptr reg  */
#define	malrxctp6r	(MAL_DCR_BASE+0x46)  /* RX 6 Channel table ptr reg  */
#define	malrxctp7r	(MAL_DCR_BASE+0x47)  /* RX 7 Channel table ptr reg  */
#define	malrxctp8r	(MAL_DCR_BASE+0x48)  /* RX 8 Channel table ptr reg  */
#define	malrxctp9r	(MAL_DCR_BASE+0x49)  /* RX 9 Channel table ptr reg  */
#define	malrxctp10r	(MAL_DCR_BASE+0x4A)  /* RX 10 Channel table ptr reg */
#define	malrxctp11r	(MAL_DCR_BASE+0x4B)  /* RX 11 Channel table ptr reg */
#define	malrxctp12r	(MAL_DCR_BASE+0x4C)  /* RX 12 Channel table ptr reg */
#define	malrxctp13r	(MAL_DCR_BASE+0x4D)  /* RX 13 Channel table ptr reg */
#define	malrxctp14r	(MAL_DCR_BASE+0x4E)  /* RX 14 Channel table ptr reg */
#define	malrxctp15r	(MAL_DCR_BASE+0x4F)  /* RX 15 Channel table ptr reg */
#define	malrxctp16r	(MAL_DCR_BASE+0x50)  /* RX 16 Channel table ptr reg */
#define	malrxctp17r	(MAL_DCR_BASE+0x51)  /* RX 17 Channel table ptr reg */
#define	malrxctp18r	(MAL_DCR_BASE+0x52)  /* RX 18 Channel table ptr reg */
#define	malrxctp19r	(MAL_DCR_BASE+0x53)  /* RX 19 Channel table ptr reg */
#define	malrxctp20r	(MAL_DCR_BASE+0x54)  /* RX 20 Channel table ptr reg */
#define	malrxctp21r	(MAL_DCR_BASE+0x55)  /* RX 21 Channel table ptr reg */
#define	malrxctp22r	(MAL_DCR_BASE+0x56)  /* RX 22 Channel table ptr reg */
#define	malrxctp23r	(MAL_DCR_BASE+0x57)  /* RX 23 Channel table ptr reg */
#define	malrxctp24r	(MAL_DCR_BASE+0x58)  /* RX 24 Channel table ptr reg */
#define	malrxctp25r	(MAL_DCR_BASE+0x59)  /* RX 25 Channel table ptr reg */
#define	malrxctp26r	(MAL_DCR_BASE+0x5A)  /* RX 26 Channel table ptr reg */
#define	malrxctp27r	(MAL_DCR_BASE+0x5B)  /* RX 27 Channel table ptr reg */
#define	malrxctp28r	(MAL_DCR_BASE+0x5C)  /* RX 28 Channel table ptr reg */
#define	malrxctp29r	(MAL_DCR_BASE+0x5D)  /* RX 29 Channel table ptr reg */
#define	malrxctp30r	(MAL_DCR_BASE+0x5E)  /* RX 30 Channel table ptr reg */
#define	malrxctp31r	(MAL_DCR_BASE+0x5F)  /* RX 31 Channel table ptr reg */
#define	malrcbs0	(MAL_DCR_BASE+0x60)  /* RX 0 Channel buffer size reg */
#define	malrcbs1	(MAL_DCR_BASE+0x61)  /* RX 1 Channel buffer size reg */
#define	malrcbs2	(MAL_DCR_BASE+0x62)  /* RX 2 Channel buffer size reg */
#define	malrcbs3	(MAL_DCR_BASE+0x63)  /* RX 3 Channel buffer size reg */
#define	malrcbs4	(MAL_DCR_BASE+0x64)  /* RX 4 Channel buffer size reg */
#define	malrcbs5	(MAL_DCR_BASE+0x65)  /* RX 5 Channel buffer size reg */
#define	malrcbs6	(MAL_DCR_BASE+0x66)  /* RX 6 Channel buffer size reg */
#define	malrcbs7	(MAL_DCR_BASE+0x67)  /* RX 7 Channel buffer size reg */
#define	malrcbs8	(MAL_DCR_BASE+0x68)  /* RX 8 Channel buffer size reg */
#define	malrcbs9	(MAL_DCR_BASE+0x69)  /* RX 9 Channel buffer size reg */
#define	malrcbs10	(MAL_DCR_BASE+0x6A)  /* RX 10 Channel buffer size reg */
#define	malrcbs11	(MAL_DCR_BASE+0x6B)  /* RX 11 Channel buffer size reg */
#define	malrcbs12	(MAL_DCR_BASE+0x6C)  /* RX 12 Channel buffer size reg */
#define	malrcbs13	(MAL_DCR_BASE+0x6D)  /* RX 13 Channel buffer size reg */
#define	malrcbs14	(MAL_DCR_BASE+0x6E)  /* RX 14 Channel buffer size reg */
#define	malrcbs15	(MAL_DCR_BASE+0x6F)  /* RX 15 Channel buffer size reg */
#define	malrcbs16	(MAL_DCR_BASE+0x70)  /* RX 16 Channel buffer size reg */
#define	malrcbs17	(MAL_DCR_BASE+0x71)  /* RX 17 Channel buffer size reg */
#define	malrcbs18	(MAL_DCR_BASE+0x72)  /* RX 18 Channel buffer size reg */
#define	malrcbs19	(MAL_DCR_BASE+0x73)  /* RX 19 Channel buffer size reg */
#define	malrcbs20	(MAL_DCR_BASE+0x74)  /* RX 20 Channel buffer size reg */
#define	malrcbs21	(MAL_DCR_BASE+0x75)  /* RX 21 Channel buffer size reg */
#define	malrcbs22	(MAL_DCR_BASE+0x76)  /* RX 22 Channel buffer size reg */
#define	malrcbs23	(MAL_DCR_BASE+0x77)  /* RX 23 Channel buffer size reg */
#define	malrcbs24	(MAL_DCR_BASE+0x78)  /* RX 24 Channel buffer size reg */
#define	malrcbs25	(MAL_DCR_BASE+0x79)  /* RX 25 Channel buffer size reg */
#define	malrcbs26	(MAL_DCR_BASE+0x7A)  /* RX 26 Channel buffer size reg */
#define	malrcbs27	(MAL_DCR_BASE+0x7B)  /* RX 27 Channel buffer size reg */
#define	malrcbs28	(MAL_DCR_BASE+0x7C)  /* RX 28 Channel buffer size reg */
#define	malrcbs29	(MAL_DCR_BASE+0x7D)  /* RX 29 Channel buffer size reg */
#define	malrcbs30	(MAL_DCR_BASE+0x7E)  /* RX 30 Channel buffer size reg */
#define	malrcbs31	(MAL_DCR_BASE+0x7F)  /* RX 31 Channel buffer size reg */

#else /* !defined(CONFIG_405EZ) */

#define MAL_DCR_BASE 0x180
#define malmcr	(MAL_DCR_BASE+0x00)  /* MAL Config reg			     */
#define malesr	(MAL_DCR_BASE+0x01)  /* Error Status reg (Read/Clear)	     */
#define malier	(MAL_DCR_BASE+0x02)  /* Interrupt enable reg		     */
#define maldbr	(MAL_DCR_BASE+0x03)  /* Mal Debug reg (Read only)	     */
#define maltxcasr  (MAL_DCR_BASE+0x04)	/* TX Channel active reg (set)	     */
#define maltxcarr  (MAL_DCR_BASE+0x05)	/* TX Channel active reg (Reset)     */
#define maltxeobisr (MAL_DCR_BASE+0x06) /* TX End of buffer int status reg   */
#define maltxdeir  (MAL_DCR_BASE+0x07)	/* TX Descr. Error Int reg	     */
#define malrxcasr  (MAL_DCR_BASE+0x10)	/* RX Channel active reg (set)	     */
#define malrxcarr  (MAL_DCR_BASE+0x11)	/* RX Channel active reg (Reset)     */
#define malrxeobisr (MAL_DCR_BASE+0x12) /* RX End of buffer int status reg   */
#define malrxdeir  (MAL_DCR_BASE+0x13)	/* RX Descr. Error Int reg	     */
#define maltxctp0r (MAL_DCR_BASE+0x20)	/* TX 0 Channel table pointer reg    */
#define maltxctp1r (MAL_DCR_BASE+0x21)	/* TX 1 Channel table pointer reg    */
#define maltxctp2r (MAL_DCR_BASE+0x22)	/* TX 2 Channel table pointer reg    */
#define malrxctp0r (MAL_DCR_BASE+0x40)	/* RX 0 Channel table pointer reg    */
#define malrxctp1r (MAL_DCR_BASE+0x41)	/* RX 1 Channel table pointer reg    */
#define malrcbs0   (MAL_DCR_BASE+0x60)	/* RX 0 Channel buffer size reg      */
#define malrcbs1   (MAL_DCR_BASE+0x61)	/* RX 1 Channel buffer size reg      */
#endif /* defined(CONFIG_405EZ) */

/*-----------------------------------------------------------------------------
| IIC Register Offsets
'----------------------------------------------------------------------------*/
#define    IICMDBUF	    0x00
#define    IICSDBUF	    0x02
#define    IICLMADR	    0x04
#define    IICHMADR	    0x05
#define    IICCNTL	    0x06
#define    IICMDCNTL	    0x07
#define    IICSTS	    0x08
#define    IICEXTSTS	    0x09
#define    IICLSADR	    0x0A
#define    IICHSADR	    0x0B
#define    IICCLKDIV	    0x0C
#define    IICINTRMSK	    0x0D
#define    IICXFRCNT	    0x0E
#define    IICXTCNTLSS	    0x0F
#define    IICDIRECTCNTL    0x10

/*-----------------------------------------------------------------------------
| UART Register Offsets
'----------------------------------------------------------------------------*/
#define		DATA_REG	0x00
#define		DL_LSB		0x00
#define		DL_MSB		0x01
#define		INT_ENABLE	0x01
#define		FIFO_CONTROL	0x02
#define		LINE_CONTROL	0x03
#define		MODEM_CONTROL	0x04
#define		LINE_STATUS	0x05
#define		MODEM_STATUS	0x06
#define		SCRATCH		0x07

/******************************************************************************
 * On Chip Memory
 ******************************************************************************/
#if defined(CONFIG_405EZ)
#define OCM_DCR_BASE 0x020
#define ocmplb3cr1	(OCM_DCR_BASE+0x00)  /* OCM PLB3 Bank 1 Config Reg    */
#define ocmplb3cr2	(OCM_DCR_BASE+0x01)  /* OCM PLB3 Bank 2 Config Reg    */
#define ocmplb3bear	(OCM_DCR_BASE+0x02)  /* OCM PLB3 Bus Error Add Reg    */
#define ocmplb3besr0	(OCM_DCR_BASE+0x03)  /* OCM PLB3 Bus Error Stat Reg 0 */
#define ocmplb3besr1	(OCM_DCR_BASE+0x04)  /* OCM PLB3 Bus Error Stat Reg 1 */
#define ocmcid		(OCM_DCR_BASE+0x05)  /* OCM Core ID		      */
#define ocmrevid	(OCM_DCR_BASE+0x06)  /* OCM Revision ID		      */
#define ocmplb3dpc	(OCM_DCR_BASE+0x07)  /* OCM PLB3 Data Parity Check    */
#define ocmdscr1	(OCM_DCR_BASE+0x08)  /* OCM D-side Bank 1 Config Reg  */
#define ocmdscr2	(OCM_DCR_BASE+0x09)  /* OCM D-side Bank 2 Config Reg  */
#define ocmiscr1	(OCM_DCR_BASE+0x0A)  /* OCM I-side Bank 1 Config Reg  */
#define ocmiscr2	(OCM_DCR_BASE+0x0B)  /* OCM I-side Bank 2 Config Reg  */
#define ocmdsisdpc	(OCM_DCR_BASE+0x0C)  /* OCM D-side/I-side Data Par Chk*/
#define ocmdsisbear	(OCM_DCR_BASE+0x0D)  /* OCM D-side/I-side Bus Err Addr*/
#define ocmdsisbesr	(OCM_DCR_BASE+0x0E)  /* OCM D-side/I-side Bus Err Stat*/
#else
#define OCM_DCR_BASE 0x018
#define ocmisarc   (OCM_DCR_BASE+0x00)	/* OCM I-side address compare reg    */
#define ocmiscntl  (OCM_DCR_BASE+0x01)	/* OCM I-side control reg	     */
#define ocmdsarc   (OCM_DCR_BASE+0x02)	/* OCM D-side address compare reg    */
#define ocmdscntl  (OCM_DCR_BASE+0x03)	/* OCM D-side control reg	     */
#endif /* CONFIG_405EZ */

/******************************************************************************
 * GPIO macro register defines
 ******************************************************************************/
#if defined(CONFIG_405EZ)
/* Only the 405EZ has 2 GPIOs */
#define GPIO_BASE  0xEF600700
#define GPIO0_OR		(GPIO_BASE+0x0)
#define GPIO0_TCR		(GPIO_BASE+0x4)
#define GPIO0_OSRL		(GPIO_BASE+0x8)
#define GPIO0_OSRH		(GPIO_BASE+0xC)
#define GPIO0_TSRL		(GPIO_BASE+0x10)
#define GPIO0_TSRH		(GPIO_BASE+0x14)
#define GPIO0_ODR		(GPIO_BASE+0x18)
#define GPIO0_IR		(GPIO_BASE+0x1C)
#define GPIO0_RR1		(GPIO_BASE+0x20)
#define GPIO0_RR2		(GPIO_BASE+0x24)
#define GPIO0_RR3		(GPIO_BASE+0x28)
#define GPIO0_ISR1L		(GPIO_BASE+0x30)
#define GPIO0_ISR1H		(GPIO_BASE+0x34)
#define GPIO0_ISR2L		(GPIO_BASE+0x38)
#define GPIO0_ISR2H		(GPIO_BASE+0x3C)
#define GPIO0_ISR3L		(GPIO_BASE+0x40)
#define GPIO0_ISR3H		(GPIO_BASE+0x44)

#define GPIO1_BASE  0xEF600800
#define GPIO1_OR		(GPIO1_BASE+0x0)
#define GPIO1_TCR		(GPIO1_BASE+0x4)
#define GPIO1_OSRL		(GPIO1_BASE+0x8)
#define GPIO1_OSRH		(GPIO1_BASE+0xC)
#define GPIO1_TSRL		(GPIO1_BASE+0x10)
#define GPIO1_TSRH		(GPIO1_BASE+0x14)
#define GPIO1_ODR		(GPIO1_BASE+0x18)
#define GPIO1_IR		(GPIO1_BASE+0x1C)
#define GPIO1_RR1		(GPIO1_BASE+0x20)
#define GPIO1_RR2		(GPIO1_BASE+0x24)
#define GPIO1_RR3		(GPIO1_BASE+0x28)
#define GPIO1_ISR1L		(GPIO1_BASE+0x30)
#define GPIO1_ISR1H		(GPIO1_BASE+0x34)
#define GPIO1_ISR2L		(GPIO1_BASE+0x38)
#define GPIO1_ISR2H		(GPIO1_BASE+0x3C)
#define GPIO1_ISR3L		(GPIO1_BASE+0x40)
#define GPIO1_ISR3H		(GPIO1_BASE+0x44)

#elif defined(CONFIG_405EX)
#define GPIO_BASE  0xEF600800
#define GPIO0_OR	       (GPIO_BASE+0x0)
#define GPIO0_TCR	       (GPIO_BASE+0x4)
#define GPIO0_OSRL	       (GPIO_BASE+0x8)
#define GPIO0_OSRH	       (GPIO_BASE+0xC)
#define GPIO0_TSRL	       (GPIO_BASE+0x10)
#define GPIO0_TSRH	       (GPIO_BASE+0x14)
#define GPIO0_ODR	       (GPIO_BASE+0x18)
#define GPIO0_IR	       (GPIO_BASE+0x1C)
#define GPIO0_RR1	       (GPIO_BASE+0x20)
#define GPIO0_RR2	       (GPIO_BASE+0x24)
#define GPIO0_ISR1L	       (GPIO_BASE+0x30)
#define GPIO0_ISR1H	       (GPIO_BASE+0x34)
#define GPIO0_ISR2L	       (GPIO_BASE+0x38)
#define GPIO0_ISR2H	       (GPIO_BASE+0x3C)
#define GPIO0_ISR3L	       (GPIO_BASE+0x40)
#define GPIO0_ISR3H	       (GPIO_BASE+0x44)

#else	/* !405EZ */

#define GPIO_BASE  0xEF600700
#define GPIO0_OR	       (GPIO_BASE+0x0)
#define GPIO0_TCR	       (GPIO_BASE+0x4)
#define GPIO0_OSRH	       (GPIO_BASE+0x8)
#define GPIO0_OSRL	       (GPIO_BASE+0xC)
#define GPIO0_TSRH	       (GPIO_BASE+0x10)
#define GPIO0_TSRL	       (GPIO_BASE+0x14)
#define GPIO0_ODR	       (GPIO_BASE+0x18)
#define GPIO0_IR	       (GPIO_BASE+0x1C)
#define GPIO0_RR1	       (GPIO_BASE+0x20)
#define GPIO0_RR2	       (GPIO_BASE+0x24)
#define GPIO0_ISR1H	       (GPIO_BASE+0x30)
#define GPIO0_ISR1L	       (GPIO_BASE+0x34)
#define GPIO0_ISR2H	       (GPIO_BASE+0x38)
#define GPIO0_ISR2L	       (GPIO_BASE+0x3C)

#endif /* CONFIG_405EZ */

#define GPIO0_BASE		GPIO_BASE

#if defined(CONFIG_405EX)
#define SDR0_SRST		0x0200

/*
 * Software Reset Register
 */
#define SDR0_SRST_BGO		PPC_REG_VAL(0, 1)
#define SDR0_SRST_PLB4		PPC_REG_VAL(1, 1)
#define SDR0_SRST_EBC		PPC_REG_VAL(2, 1)
#define SDR0_SRST_OPB		PPC_REG_VAL(3, 1)
#define SDR0_SRST_UART0		PPC_REG_VAL(4, 1)
#define SDR0_SRST_UART1		PPC_REG_VAL(5, 1)
#define SDR0_SRST_IIC0		PPC_REG_VAL(6, 1)
#define SDR0_SRST_BGI		PPC_REG_VAL(7, 1)
#define SDR0_SRST_GPIO		PPC_REG_VAL(8, 1)
#define SDR0_SRST_GPT		PPC_REG_VAL(9, 1)
#define SDR0_SRST_DMC		PPC_REG_VAL(10, 1)
#define SDR0_SRST_RGMII		PPC_REG_VAL(11, 1)
#define SDR0_SRST_EMAC0		PPC_REG_VAL(12, 1)
#define SDR0_SRST_EMAC1		PPC_REG_VAL(13, 1)
#define SDR0_SRST_CPM		PPC_REG_VAL(14, 1)
#define SDR0_SRST_EPLL		PPC_REG_VAL(15, 1)
#define SDR0_SRST_UIC		PPC_REG_VAL(16, 1)
#define SDR0_SRST_UPRST		PPC_REG_VAL(17, 1)
#define SDR0_SRST_IIC1		PPC_REG_VAL(18, 1)
#define SDR0_SRST_SCP		PPC_REG_VAL(19, 1)
#define SDR0_SRST_UHRST		PPC_REG_VAL(20, 1)
#define SDR0_SRST_DMA		PPC_REG_VAL(21, 1)
#define SDR0_SRST_DMAC		PPC_REG_VAL(22, 1)
#define SDR0_SRST_MAL		PPC_REG_VAL(23, 1)
#define SDR0_SRST_EBM		PPC_REG_VAL(24, 1)
#define SDR0_SRST_GPTR		PPC_REG_VAL(25, 1)
#define SDR0_SRST_PE0		PPC_REG_VAL(26, 1)
#define SDR0_SRST_PE1		PPC_REG_VAL(27, 1)
#define SDR0_SRST_CRYP		PPC_REG_VAL(28, 1)
#define SDR0_SRST_PKP		PPC_REG_VAL(29, 1)
#define SDR0_SRST_AHB		PPC_REG_VAL(30, 1)
#define SDR0_SRST_NDFC		PPC_REG_VAL(31, 1)

#define sdr_uart0	0x0120	/* UART0 Config */
#define sdr_uart1	0x0121	/* UART1 Config */
#define sdr_mfr		0x4300	/* SDR0_MFR reg */

/* Defines for CPC0_EPRCSR register */
#define CPC0_EPRCSR_E0NFE	   0x80000000
#define CPC0_EPRCSR_E1NFE	   0x40000000
#define CPC0_EPRCSR_E1RPP	   0x00000080
#define CPC0_EPRCSR_E0RPP	   0x00000040
#define CPC0_EPRCSR_E1ERP	   0x00000020
#define CPC0_EPRCSR_E0ERP	   0x00000010
#define CPC0_EPRCSR_E1PCI	   0x00000002
#define CPC0_EPRCSR_E0PCI	   0x00000001

#define cpr0_clkupd	0x020
#define cpr0_pllc	0x040
#define cpr0_plld	0x060
#define cpr0_cpud	0x080
#define cpr0_plbd	0x0a0
#define cpr0_opbd	0x0c0
#define cpr0_perd	0x0e0
#define cpr0_ahbd	0x100
#define cpr0_icfg	0x140

#define SDR_PINSTP	0x0040
#define sdr_sdcs	0x0060

#define SDR0_SDCS_SDD			(0x80000000 >> 31)

/* CUST0 Customer Configuration Register0 */
#define SDR0_CUST0		     0x4000
#define   SDR0_CUST0_MUX_E_N_G_MASK   0xC0000000     /* Mux_Emac_NDFC_GPIO */
#define   SDR0_CUST0_MUX_EMAC_SEL     0x40000000       /* Emac Selection */
#define   SDR0_CUST0_MUX_NDFC_SEL     0x80000000       /* NDFC Selection */
#define   SDR0_CUST0_MUX_GPIO_SEL     0xC0000000       /* GPIO Selection */

#define   SDR0_CUST0_NDFC_EN_MASK     0x20000000     /* NDFC Enable Mask */
#define   SDR0_CUST0_NDFC_ENABLE      0x20000000       /* NDFC Enable */
#define   SDR0_CUST0_NDFC_DISABLE     0x00000000       /* NDFC Disable */

#define   SDR0_CUST0_NDFC_BW_MASK     0x10000000     /* NDFC Boot Width */
#define   SDR0_CUST0_NDFC_BW_16_BIT   0x10000000       /* NDFC Boot Width = 16 Bit */
#define   SDR0_CUST0_NDFC_BW_8_BIT    0x00000000       /* NDFC Boot Width =  8 Bit */

#define   SDR0_CUST0_NDFC_BP_MASK     0x0F000000     /* NDFC Boot Page */
#define   SDR0_CUST0_NDFC_BP_ENCODE(n) ((((unsigned long)(n))&0xF)<<24)
#define   SDR0_CUST0_NDFC_BP_DECODE(n) ((((unsigned long)(n))>>24)&0x0F)

#define   SDR0_CUST0_NDFC_BAC_MASK    0x00C00000     /* NDFC Boot Address Cycle */
#define   SDR0_CUST0_NDFC_BAC_ENCODE(n) ((((unsigned long)(n))&0x3)<<22)
#define   SDR0_CUST0_NDFC_BAC_DECODE(n) ((((unsigned long)(n))>>22)&0x03)

#define   SDR0_CUST0_NDFC_ARE_MASK    0x00200000     /* NDFC Auto Read Enable */
#define   SDR0_CUST0_NDFC_ARE_ENABLE  0x00200000       /* NDFC Auto Read Enable */
#define   SDR0_CUST0_NDFC_ARE_DISABLE 0x00000000       /* NDFC Auto Read Disable */

#define   SDR0_CUST0_NRB_MASK	      0x00100000     /* NDFC Ready / Busy */
#define   SDR0_CUST0_NRB_BUSY	      0x00100000       /* Busy */
#define   SDR0_CUST0_NRB_READY	      0x00000000       /* Ready */

#define   SDR0_CUST0_NDRSC_MASK       0x0000FFF0     /* NDFC Device Reset Count Mask */
#define   SDR0_CUST0_NDRSC_ENCODE(n) ((((unsigned long)(n))&0xFFF)<<4)
#define   SDR0_CUST0_NDRSC_DECODE(n) ((((unsigned long)(n))>>4)&0xFFF)

#define   SDR0_CUST0_CHIPSELGAT_MASK  0x0000000F     /* Chip Select Gating Mask */
#define   SDR0_CUST0_CHIPSELGAT_DIS   0x00000000       /* Chip Select Gating Disable */
#define   SDR0_CUST0_CHIPSELGAT_ENALL 0x0000000F       /* All Chip Select Gating Enable */
#define   SDR0_CUST0_CHIPSELGAT_EN0   0x00000008       /* Chip Select0 Gating Enable */
#define   SDR0_CUST0_CHIPSELGAT_EN1   0x00000004       /* Chip Select1 Gating Enable */
#define   SDR0_CUST0_CHIPSELGAT_EN2   0x00000002       /* Chip Select2 Gating Enable */
#define   SDR0_CUST0_CHIPSELGAT_EN3   0x00000001       /* Chip Select3 Gating Enable */

#define SDR0_PFC0		0x4100
#define SDR0_PFC1		0x4101
#define SDR0_PFC1_U1ME		0x02000000
#define SDR0_PFC1_U0ME		0x00080000
#define SDR0_PFC1_U0IM		0x00040000
#define SDR0_PFC1_SIS		0x00020000
#define SDR0_PFC1_DMAAEN	0x00010000
#define SDR0_PFC1_DMADEN	0x00008000
#define SDR0_PFC1_USBEN		0x00004000
#define SDR0_PFC1_AHBSWAP	0x00000020
#define SDR0_PFC1_USBBIGEN	0x00000010
#define SDR0_PFC1_GPT_FREQ	0x0000000f
#endif

/* General Purpose Timer (GPT) Register Offsets */
#define GPT0_TBC		0x00000000
#define GPT0_IM			0x00000018
#define GPT0_ISS		0x0000001C
#define GPT0_ISC		0x00000020
#define GPT0_IE			0x00000024
#define GPT0_COMP0		0x00000080
#define GPT0_COMP1		0x00000084
#define GPT0_COMP2		0x00000088
#define GPT0_COMP3		0x0000008C
#define GPT0_COMP4		0x00000090
#define GPT0_COMP5		0x00000094
#define GPT0_COMP6		0x00000098
#define GPT0_MASK0		0x000000C0
#define GPT0_MASK1		0x000000C4
#define GPT0_MASK2		0x000000C8
#define GPT0_MASK3		0x000000CC
#define GPT0_MASK4		0x000000D0
#define GPT0_MASK5		0x000000D4
#define GPT0_MASK6		0x000000D8
#define GPT0_DCT0		0x00000110
#define GPT0_DCIS		0x0000011C

#endif	/* __PPC405_H__ */
