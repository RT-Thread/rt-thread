/*
** ###################################################################
**     Processor:           S32K344
**     Reference manual:    S32K3xx RM Rev.3
**     Version:             rev. 1.9, 2021-10-27
**     Build:               b211026
**
**     Abstract:
**         Peripheral Access Layer for S32K344
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     - rev. 1.0 Taru Shree 22-Oct-19  Initial release based on 
**                                      RM Rev.1 Draft C.
**
**     - rev. 1.1 Taru Shree 11-Feb-20  1)Initial release based on 
**                                      RM Rev.1 Draft D.
**                                      2)CONFIGURATION_GPR-
**                                      Following register names are changed-
**                                      -from CONFIG_CFPRAB to CONFIG_CFPRL.
**                                      -from CONFIG_CFPRP to CONFIG_CFPRH. 
**                                      -from CONFIG_CFPRAB_ALT to CONFIG_CFPRL_ALT.
**                                      -from CONFIG_CFPRP_ALT to CONFIG_CFPRH_ALT.
**                                      3)VIRT_WRAPPER-
**                                      Following register names are changed-
**                                      -from E to A.
**                                      -from REG_F to REG_B. 
**                                      -from REG_G to REG_C.
**                                      -from REG_H to REG_D.
**                                      4)Addresses of following blocks have
**                                      been changed-
**                                      -MCM_0_CM7:from 0xE008000 to 0xE0080000.
**                                      -MU_2__MUA:from 0x404F0000 to 0x400B8000.
**                                      -MU_2__MUB:from 0x404F4000 to 0x400BC000.
**                                      5)FLASH_ALT block is added.
**                                      6)REG_PROT and POR_WDOG blocks are removed.
**
**     -rev. 1.2 Taru Shree 17-Mar-20   1)Initial release based on
**                                      RM Rev.1 Draft E.
**                                      2)ADC-
**                                      -CEOCFR1 register- SIEOCF24…31 bitfields
**                                       are removed.
**                                      -CIMR1 register- SIEOCIEN24…31 bitfields
**                                       are removed.
**                                      -WTIMR register- LAWIFEN5…16 and HDWIFEN5…16 
**                                       bitfields are removed.
**                                      -DMAR1 register- SIDMAREN24…31 bitfields 
**                                       are removed.
**                                      -CWSELRPI register- Few bitfields names
**                                       are changed from WSEL_PIx to WSEL_SIx_0 and  
**                                       WSEL_SIx_0.
**                                      -CWSELRSI register- Few bitfields names
**                                       are changed from WSEL_SIx to WSEL_SIx_0 and
**                                       WSEL_SIx_1.
**                                      -CWSELRSI array size is changed from 4 to 3.
**                                      -CWSELREI register- Few bitfields names
**                                       are changed from WSEL_EIx to WSEL_SIx_0 and
**                                       WSEL_SIx_1.
**                                      -STAW3R register is removed.
**                                      3)BCTU-
**                                      -FIFO1DR register- Bitfield name is changed
**                                       from ADC_SRC to ADC_NUM.
**                                      -FIFO2DR register- Bitfield name is changed
**                                       from ADC_SRC to ADC_NUM.
**                                      4)DCM- 
**                                      DCMDEB register is added.
**                                      5)DCM_GPR- 
**                                      -DCMROD5 register- Bitfields are changed from 
**                                       lower-case to upper-case.
**                                       -rd_stam_edc_err_out bitfield is removed.
**                                      -DCMROF20 register- Following bitfields are 
**                                       removed-
**                                       -HSE_EXPORT_CNTRL
**                                       -HSE_APP_DIS_FLD
**                                       -HSE_APP_DIS_OEM
**                                       -HSE_DBG_EN_FLD
**                                       -HSE_DBG_EN_OEM
**                                       -HSE_DIS_CUS
**                                       -HSE_DIS_FLD
**                                       -HSE_DIS_OEM
**                                       -HSE_DIS_PRE_FA
**                                       -APPIN_DBG_EN
**                                       -HSE_B_IPT_SWT_DIS
**                                      -DCMRWD2 register- BACKDOOR_DIS_ANOTHER 
**                                       bitfield is added.
**                                      -DCMRWD3 register- Bitfields are changed 
**                                       from lower-case to upper-case.
**                                       -CM7_1_TAG_MULTI_ERR, CM7_0_IC_MULTI_ERR
**                                        and CM7_1_IC_MULTI_ERR bitfields are added.
**                                      -DCMRWD4 register- Bitfields are changed 
**                                       from lower-case to upper-case.
**                                      -DCMRWD5 register- Bitfields are changed 
**                                       from lower-case to upper-case.
**                                       -rd_stam_edc_err_out bitfield is removed.
**                                      -DCMRWF4 register- cm7_0_cpuwait and 
**                                       cm7_1_cpuwait bitfields are changed 
**                                       from lower-case to upper-case.
**                                      -DCMRWF5 register- boot_address cpuwait 
**                                       bitfield is changed from lower-case to 
**                                       upper-case.
**                                      6)FCCU-
**                                      -CGF register- FOP and FOPE bitfields are 
**                                       removed.
**                                      7)MC_ME-
**                                      -PRTN1_COFB3_STAT register- BLOCK102, BLOCK103, 
**                                       BLOCK105, BLOCK106, BLOCK107 and BLOCK110 
**                                       bitfields are removed.
**                                      -PRTN1_COFB3_CLKEN register- REQ102 bitfield 
**                                       is removed.
**                                      8)MC_RGM-
**                                      -FERD and LPDEBUG registers are added.
**                                      9)MDM_AP-
**                                      -Following registers are removed-
**                                       -MDMAPSTTS2
**                                       -MDMAPDBG 
**                                       -MDMAPTRC
**                                       -MDMAPSECDBG
**                                       -MDMAPSECTRC
**                                       -CORE0_HALT_DBG_A
**                                       -CORE1_HALT_DBG_A
**                                       -CORE2_HALT_DBG_A
**                                       -CORE3_HALT_DBG_A
**                                       -DAP_EN_STATUS 
**                                      10)MSCM-
**                                      -ENEDC register- STAM and EN_QSPI bitfields
**                                       are removed.
**                                      11)PFLASH-
**                                      -PFCBLK_SSPELOCK register- SSLCK bitfield size 
**                                       is changed from 3 to 12.
**                                      -PFCBLK_SSETSLOCK register- SSETSLCK bitfield 
**                                       size is changed from 3 to 12.
**                                      -PFCBLKI_SSPELOCK and PFCBLKI_SSETSLOCK array 
**                                       size is changed from 5 to 4.
**                                      -PFCDBLK_SSPELOCK and PFCDBLK_SSETSLOCK registers
**                                       are added.
**                                      12)QuadSPI-
**                                      -MCR register- DQS_FB_SEL bitfield is removed.
**                                      -SMPR register- DLLFSMPFB bitfield is removed.
**                                      -DLLCRB, DLSR_FB, SFB1AD and SFB2AD registers 
**                                       are removed.
**                                      13)SDA_AP-
**                                      -KEYCHAL individual registers changed to array.
**                                      -KEYRESP individual registers changed to array.  
**                                      -AUTHSTTS register- HSENEWDATASTATUS and HSEDBGEN 
**                                       bitfields are removed.
**                                      -SDAAPGENSTATUSx registers- DAP_GENx_STATUS 
**                                       bitfields are changed to SDAAPGENSTATUS.
**                                      -AUTHCTL and DAP_GEN1_CTRL registers are removed.
**                                      14)SIUL2-
**                                      -MSCR register- SRE bitfield is changed to SRC.
**                                      15)STCU- 
**                                      -LB_CTRL register- PFT bitfield is added. 
**                                      16)GMAC block is renamed as EMAC.
**                                      17)Following blocks are added- 
**                                      -PERIPHERAL_DEBUG_FREEZE
**                                      -SELFTEST_GPR
**                                      -XBIC_AXBS_EDMA
**                                      -XBIC_AXBS_TCM
**
**     -rev. 1.3 Taru Shree 22-Jul-20   1)Initial release based on
**                                      RM Rev.1 Draft G.
**                                      2)ADC-
**                                      -TRGCFG register- Bitfield name is
**                                       changed from CHANNEL_VALUE_OR_LADDR_7BITS
**                                       to CHANNEL_VALUE_OR_LADDR.
**                                      3)BCTU-
**                                      -ADC0DR, ADC1DR and ADC2DR registers are 
**                                       converted into array.
**                                      4)CMU_FC-
**                                      -SR register- STATE bitfield is removed.
**                                      5)CMU_FM-
**                                      -SR register- STATE bitfield is removed.
**                                      6)CONFIGURATION_GPR-
**                                      -CONFIG_REG1, CONFIG_REG2, CONFIG_REG3, 
**                                       CONFIG_REG, CONFIG_REG5 and CONFIG_NVM_TESTMODE 
**                                       registers are removed.
**                                      -CONFIG_PE_LOCK registers- LOCK_BLOCK_5 bitfield 
**                                       is removed.
**                                      7)DCM-
**                                      -DCMDCFC, DCMDCFA, DCMDCFD, DCMBVL, DCMBVH and TESTPASS 
**                                       registers are removed.
**                                      -DCMLCS, DCMSRR and DCMLCS_2 registers are added.
**                                      -DCMDEB register- HSE_APP_DIS_FLD, HSE_DBG_EN_FLD, 
**                                       HSE_APP_DIS_OEM and HSE_DBG_EN_OEM bitfields are 
**                                       removed.
**                                      -DCMSRR register array is added.
**                                      -DCMSTAT register- DCMTPSCAN bitfield is removed.
**                                      8)DCM_GPR-
**                                      -All bitfield names are changed in DCMROD3,
**                                       DCMROD4, DCMROD5, DCMRWD3, DCMRWD4 and DCMRWD5
**                                       registers.
**                                      -DCMROD5 register- All bitfields names are changed 
**                                       except STCU_NCF.
**                                      -DCMROF19 register- Bitfield name is changed from
**                                       LOCKSTEP_ENB to LOCKSTEP_EN.
**                                      -DCMRWD2 register- BACKDOOR_DIS_ANOTHER bitfield 
**                                       is removed.
**                                      -DCMRWD7 register- I3C_DBG_DIS_CM7_0 bitfield is 
**                                       added.
**                                      -DCMRWD9 register- I3C_DBG_DIS_CM7_1 bitfield is 
**                                       added.
**                                      -DCMRWD10, DCMRWD11, DCMRWD12, DCMRWD13, DCMRWD14 
**                                       and DCMRWD15 registers are removed.
**                                      -DCMRWF1 register- VDD_HV_B_IO_CTRL_LATCH bitfield
**                                       is added.
**                                      9)FLEXCAN_n is changed to CAN_n.
**                                      10)LCU-
**                                      -Array name is changed from LC_CTRL to LC.
**                                      -Array name is changed from LC_SEL to SEL.
**                                      -LC prefix is removed from registers.
**                                      11)LPCMP-
**                                      -CMP block is renamed as LPCMP.
**                                      -Interrupt names are changed from CMPn to LPCMPn.
**                                      12)LPUART-
**                                      -BAUD register- RIDMAE bitfield is removed.
**                                      -Interrupt names are changed from LPUART_n to LPUARTn.
**                                      13)MC_CGM-
**                                      -MUX_0_DC_5 register- PHASE bitfield is removed.
**                                      14)MC_ME-
**                                      -PRTN1_COFB3_STAT register- BLOCK102, BLOCK103, 
**                                       BLOCK105, BLOCK106, BLOCK107 and BLOCK110 bitfields 
**                                       are added.
**                                      -PRTN1_COFB3_CLKEN register- REQ102 bitfield is 
**                                       added.
**                                      15)MSCM-
**                                      -IRSPRC0 register is removed.
**                                      16)MU-
**                                      -Single structure is created i.e MU instead of 
**                                       MUA and MUB.
**                                      17)PFLASH-
**                                      -PFAPR register- All bitfields positions are 
**                                       reverted.
**                                      18)Peripheral_Debug_Freeze-
**                                      -Register name is changed from CORE0_DBGFRZ_CTRL_GPR_LP12C0 
**                                       to CORE0_DBGFRZ_CTRL_GPR_LPI2C0.
**                                      -Register name is changed from CORE0_DBGFRZ_CTRL_GPR_LP12C1 
**                                       to CORE0_DBGFRZ_CTRL_GPR_LPI2C1.
**                                      -Register name is changed from CORE1_DBGFRZ_CTRL_GPR_LP12C0 
**                                       to CORE1_DBGFRZ_CTRL_GPR_LPI2C0.
**                                      -Register name is changed from CORE1_DBGFRZ_CTRL_GPR_LP12C1 
**                                       to CORE1_DBGFRZ_CTRL_GPR_LPI2C1.
**                                      19)QuadSPI-
**                                      -SFB1AD and SFB2AD registers are added.
**                                      20)SDA_AP-
**                                      -AUTHCTL register is added.
**                                      -DAP_GEN2_CTRL, DAP_GEN3_CTRL and DAP_GEN4_CTRL
**                                       registers are removed.
**                                      21)SELFTEST_GPR-
**                                      -GENERIC_REG0 register is renamed as CONFIG_REG.
**                                      22)SIUL2-
**                                      -MPGPDO register's array size is changed from 13 to 14.
**                                      23)STCU-
**                                      -LBRMSW0 register is removed.
**                                      24)TEMPSENSE-
**                                      -TMU is renamed as TEMPSENSE.
**                                      25)TRGMUX-
**                                      -ANLCMP_n is renamed as LPCMP_n in index offset.
**                                      26)EMIOS-
**                                      -EMIOS_0, EMIOS_1 and EMIOS_2 instances are merged 
**                                       together.
**
**     -1.4 Taru Shree 17-Sep-20        1)Initial release based on            
**                                      RM Rev.1.    
**                                      2)EMIOS interrupt counting is changed.
**                                      3)ENET_x_IRQn is renamed as EMAC_x_IRQn.
**                                      4)STCU_LBIST_MBIST_IRQn is added.                           
**                                      5)ADC-  
**                                      -ADC_CDR1_COUNT is removed.
**                                      -ADC_CDR2_COUNT is removed.    
**                                      -PCDR and ICDR registers are unrolled.                          
**                                      -CEOCFR0 register- PIEOCF8 and PIEOCF9
**                                       bitfields are removed.               
**                                      -CIMR0 register- PIEOCIEN8 and        
**                                       PIEOCIEN9 bitfields are removed.     
**                                      -DMAR0 register- PIDMAREN8 and        
**                                       PIDMAREN9 bitfields are removed.      
**                                      -PSR0 register- PRES8 and PRES9       
**                                       bitfields are removed.                
**                                      -CTR1 register- TSENSOR_SEL bitfield  
**                                       is removed.                          
**                                      -NCMR0 register- CH8 and CH9 bitfields
**  								     are removed.                         
**                                      -JCMR0 register- CH8 and CH9 bitfields 
**                                       are removed.                         
**                                      -CWENR0 register- CWEN8 and CWEN9     
**                                       bitfields are removed.               
**                                      -AWORR0 register- AWOR_CH8 and        
**                                       AWOR_CH9 bitfields are removed.      
**                                      -AWORR1 register- AWOR_CH24,…AWOR_CH31
**                                       bitfields are removed.               
**                                      6)CONFIGURATION_GPR-                    
**                                      CONFIG_REG6 register- ENET_CLOCK_GATE 
**                                      bitfield is renamed as EMAC_CLOCK_GATE.
**                                      7)DCM-                                
**                                      DCMSRR register array size is changed 
**                                      from 1 to 16.                         
**                                      8)DCM_GPR-                             
**                                      -DCMROD4 register-                    
**                                       TEST_ACTIVATION_2_ERR bitfield is    
**                                       removed.                             
**                                      -DCMROD5 register-                    
**                                       TEST_ACTIVATION_3_ERR bitfield is    
**                                       removed.                             
**                                      -DCMRWD4 register-                    
**                                       TEST_ACTIVATION_2_ERR_EN bitfield is 
**                                       removed.                             
**                                      -DCMRWD5 register-                    
**                                       TEST_ACTIVATION_3_ERR_EN bitfield is 
**                                       removed.                             
**                                      -DCMRWF2 register-                    
**                                       SIRC_TRIM_BYP_STDBY_EXT bitfield is  
**                                       added.                               
**                                      -DCMRWF5 register-                    
**                                      -BOOT_MODE bitfield is added.        
**                                      -BOOT_ADDRESS bitfield's size is     
**                                       changed from 32 to 31.              
**                                      9)FCCU-                               
**                                      CFG register- SM bitfield is removed.  
**                                      10)LCU-              
**                                      -LCU_LC_LUTCTRL_COUNT is added.
**                                      -LCU_LC_FILT_COUNT is added.                   
**                                      -LUTCTRL and FILT registers are       
**                                       converted into array.                
**                                      11)LPSPI-  
**                                      -LPSPI_TDBR_COUNT is added.
**                                      -LPSPI_RDBR_COUNT is added.                            
**                                      -TDBR register is converted into array
**                                       of size 128.                         
**                                      -RDBR register is converted into array
**                                       of size 128.                         
**                                      12)MC_CGM-                             
**                                      PCFS_DIVC8, PCFS_DIVE8 and PCFS_DIVS8 
**                                      registers are added.                  
**                                      13)MC_RGM-                            
**                                      -FBRE register is added.              
**                                      -FRENTC register is added.            
**                                      14)MDM_AP-                            
**                                      -MDMAPCTL register- POR_WDG_DIS       
**                                       bitfield is added.                   
**                                      -CM7_0_CORE_ACCESS and                
**                                       CM7_1_CORE_ACCESS bitfields are      
**                                       removed.                             
**                                      15)MSCM-                              
**                                      -ENEDC register- ENET bitfield is     
**                                       changed to EMAC.                    
**                                      -IAHBCFGREG register- ENET_DIS_WR_OPT 
**                                       is renamed as EMAC_DIS_WR_OPT.       
**                                      16)PFLASH-        
**                                      -PFLASH_D_PFCBLKI_SSPELOCK_COUNT is removed.
**                                      -PFLASH_D_PFCBLKI_SSETSLOCK_COUNT is removed.   
**                                      -PFLASH_PFCBLKI_LOCKMASTER_SS_PFCBLKI_LOCKMASTER_SSJ_COUNT
**                                       is added.
**                                      -PFLASH_PFCBLKI_LOCKMASTER_SS_COUNT is added.                 
**                                      -PFCDBLK_SSPELOCK register is removed.
**                                      -PFCDBLK_SSETSLOCK register is removed
**                                      -PFCBLKx_LOCKMASTER_SSx registers are 
**                                       converted into array.                
**                                      17)Peripheral_Debug_Freeze module is  
**                                      removed.                              
**                                      18)QuadSPI-                           
**                                      -DLLCRA register- SLV_DLY_FINE        
**                                       bitfield is removed.                   
**                                      19)SIUL2-       
**                                      -SIUL2_IMCR_COUNT's value is changed  
**                                       from 409 to 379.                                         
**                                      -MIDR1 register- CC_REVISION bitfield 
**                                       is removed.                          
**                                      -MIDR3 register- SYS_RAM_SIZE,        
**                                       PART_NO_SUF, PROD_FAM_NO and         
**                                       PROD_FAM_LET bitfields are added.    
**                                      -MIDR4 register- CORE_PLAT_FET,       
**                                       EMAC_FET and SEC_FET bitfields are   
**                                       added.                                
**                                      20)STCU-                              
**                                      CTRL register- PFT bitfield is     
**                                      removed.                               
**                                      21)XRDC-                              
**                                      XRDC_PDAC_SLOT_PDACN_COUNT's value is
**                                      changed from 111 to 109.
**
**     -1.5 Taru Shree 11-Nov-20        1)Initial release based on            
**                                      RM Rev.2. Draft A.    
**                                      2)ADC-
**                                      -ICDR registers are merged into single 
**                                       array.
**                                      -AMSIO and CAL_2 registers are added.
**                                      3)DCM-
**                                      -DCMSTAT register- 
**                                       -DCMERR and DCMUTS bitfields are added.
**                                       -DCMOTAA and DCMOTAR bitfields are removed.
**                                      -DCMMISC register-
**                                       DCMDBGE bitfield is added.
**                                      4)LPI2C-
**                                      SIER register- AM1F bitfield is renamed as 
**                                      AM1IE.
**   
**     -1.6 Taru Shree 02-March-20      1)Initial release based on            
**                                      RM Rev.2. Draft B.    
**                                      2)Following interrupt names are
**                                      changed-
**                                      -From HSE_B_0_IRQn to HSE_MU0_TX_IRQn.
**                                      -From HSE_B_1_IRQn to HSE_MU0_RX_IRQn.
**                                      -From HSE_B_2_IRQn to HSE_MU0_ORED_IRQn.
**                                      -From HSE_B_3_IRQn to HSE_MU1_TX_IRQn.
**                                      -From HSE_B_4_IRQn to HSE_MU1_RX_IRQn.
**                                      -From HSE_B_5_IRQn to HSE_MU1_ORED_IRQn. 
**                                      3)FLASH-
**                                      -ADATA register array is removed.
**                                      -AMCR, AMCRS, APEADR,ASPELOCK
**                                       and ASSPELOCK registers are 
**                                       removed.
**                                      4)FLASH_ALT instance is removed.
**                                      5)MDM_AP register-
**                                      -MDMAPSTTS register-
**                                       HSEHLT, HSEBPDPSLP, HSEBSLPNG
**                                       and CM0PDBGRST bitfields are 
**                                       removed.
**                                      -MDMAPCTL register-
**                                       HSEBDBGREQ and CM0PDBGRSRT
**                                       bitfields are removed.
**                                      6)MSCM-
**                                      -ENEDC register-
**                                       -CM7_0_AHBM bitfield name is
**                                        changed to EN_RD_CM7_0_AHBM.
**                                       -CM7_0_AHBP bitfield name is
**                                        changed to EN_RD_CM7_0_AHBP.
**                                       -eDMA bitfield name is changed
**                                        to EN_RD_EDMA.
**                                       -HSE bitfield name is changed to
**                                        EN_RD_HSE.
**                                       -EMAC bitfield name is changed to
**                                        EN_RD_EMAC.
**                                       -CM7_1_AHBM bitfield name is changed
**                                        to EN_RD_CM7_1_AHBM.    
**                                       -CM7_1_AHBP bitfield name is changed
**                                        to EN_RD_CM7_1_AHBP.   
**                                       -TCM bitfield name is changed
**                                        to EN_RD_TCM. 
**                                       -P_FLASH_PORT0 bitfield name is changed
**                                        to EN_ADD_PFLASH_PORT0.   
**                                       -P_FLASH_PORT1 bitfield name is changed
**                                        to EN_ADD_PFLASH_PORT1.  
**                                       -P_FLASH_PORT2 bitfield name is changed
**                                        to EN_ADD_PFLASH_PORT2.     
**                                       -EN_PRAM0 bitfield name is changed
**                                        to EN_WR_PRAM0.     
**                                       -PRAM0 bitfield name is changed
**                                        to EN_ADD_PRAM0.     
**                                       -EN_PRAM1 bitfield name is changed
**                                        to EN_WR_PRAM1.     
**                                       -EN_PRAM1 bitfield name is changed
**                                        to EN_WR_PRAM1. 
**                                       -EN_TCM bitfield name is changed
**                                        to EN_WR_TCM.  
**                                       -ADD_TCM bitfield name is changed
**                                        to EN_ADD_TCM.  
**                                       -EN_AIPS0 bitfield name is changed
**                                        to EN_WR_AIPS0.  
**                                       -EN_AIPS1 bitfield name is changed
**                                        to EN_WR_AIPS1.  
**                                       -EN_AIPS2 bitfield name is changed
**                                        to EN_WR_AIPS2. 
**                                       -CM7_0_TCM bitfield name is changed
**                                        to EN_WR_CM7_0_TCM.  
**                                       -ADD_CM7_0_TCM bitfield name is changed
**                                        to EN_ADD_CM7_0_TCM.   
**                                       -CM7_1_TCM bitfield name is changed
**                                        to EN_WR_CM7_1_TCM.   
**                                       -ADD_CM7_1_TCM bitfield name is changed
**                                        to EN_ADD_CM7_1_TCM.   
**                                      7)PFLASH-
**                                      -PFCPGM_APEADR_L and PFCPGM_APEADR_P 
**                                       registers are removed. 
**                                      8)PFLASH_ALT instance is removed.
**                                      9)SAI-
**                                      -TCR2 register-
**                                       BCS bitfield is removed.
**                                      -RCR2 register-
**                                       BCS bitfield is removed.
**                                      10)VIRT_WRAPPER-
**                                      -Following register array names
**                                       are changed-
**                                       -From REG to REG_A.
**                                       -From REG_32 to REG_B.
**                                       -From REG_64 to REG_C.
**                                       -From REG_65 to REG_D.
**
**     -1.7 Taru Shree 16-Aug-21      1)Initial release based on            
**                                      RM Rev.2.
**                                    2)SoC_PLL interrupt is added.
**                                    3)ADC-                                
**                                    -PCDR registers are converted into    
**                                     array.                               
**                                    -AMSIO register: HSEN bitfield’s size 
**                                     changed from HSEN 1 to 2.            
**                                    4)DCM-                                
**                                    DCMMISC register: MRKLSTRCHK bitfield 
**                                    is removed.                           
**                                    5)DCM_GPR-                            
**                                    -DCMROD3 register: CM7_1_LOCKUP,      
**                                     CM7_1_DCDATA_ECC_ERR,                
**                                     CM7_1_DCTAG_ECC_ERR and              
**                                     CM7_1_ICDATA_ECC_ERR bitfields are   
**                                     removed.                             
**                                    -DCMROD4 register:                    
**                                     CM7_1_ICTAG_ECC_ERR,                 
**                                     PF2_CODE_ECC_ERR, PF2_DATA_ECC_ERR   
**                                     and FLASH_ECC_ERR bitfields are      
**                                     removed.                             
**                                    -DCMROD5 register:                    
**                                     CM7_1_AHBP_RDATA_EDC_ERR and         
**                                     CM7_1_AHBM_RDATA_EDC_ERR bitfields   
**                                     are removed.                         
**                                    -DCMROF20 register: CM7_TCM_WS_EN     
**                                     bitfield is removed.                 
**                                    -DCMRWD3 register: CM7_1_LOCKUP_EN,   
**                                     CM7_1_DCDATA_ECC_ERR_EN,             
**                                     CM7_1_DCTAG_ECC_ERR_EN and           
**                                     CM7_1_ICDATA_ECC_ERR_EN bitfields are
**                                     removed.                             
**                                    -DCMRWD4 register:                    
**                                     CM7_1_ICTAG_ECC_ERR_EN,              
**                                     PF2_CODE_ECC_ERR_EN,                 
**                                     PF2_DATA_ECC_ERR_EN and              
**                                     FLASH_ECC_ERR_EN bitfields are       
**                                     removed.                             
**                                    -DCMRWD5 register:                    
**                                     CM7_1_AHBP_RDATA_EDC_ERR_EN and      
**                                     CM7_1_AHBM_RDATA_EDC_ERR_EN bitfields
**                                     are removed.                         
**                                    -DCMRWD7 register: All bitfields are  
**                                     removed.                             
**                                    -DCMRWD8 register: All bitfields are  
**                                     removed.                             
**                                    -DCMRWD9 register: All bitfields are  
**                                     removed.                             
**                                    -DCMRWF4 register: CM7_1_CPUWAIT      
**                                     bitfield is removed.                 
**                                    6)EMAC-                               
**                                    Following registers are added:
**                                    -MAC_VLAN_TAG
**                                    -MAC_VLAN_TAG_FILTER0
**                                    -MAC_VLAN_TAG_FILTER1
**                                    -MAC_VLAN_TAG_FILTER2
**                                    -MAC_VLAN_TAG_FILTER3                 
**                                    7)LPI2C-                              
**                                    SRDR register: RADDR bitfield is added
**                                    8)XRDC-                               
**                                    PID register: LMNUM and ELK22H        
**                                    bitfields are removed.                
**
**     -1.8 Taru Shree 08-Sep-21      1)Updated the Header file for        
**                                    RM Rev.2.
**                                    2)AXBS_LITE-
**                                    -PRS0 register: M4 bitfield is removed.
**                                     CRS0 register: HPE4 bitfield is 
**                                     removed.
**                                    -PRS1 register: M4 bitfield is 
**                                     removed.
**                                    -CRS1 register: HPE4 bitfield is 
**                                     removed.
**                                    -PRS2 register: M4 bitfield is 
**                                     removed.
**                                    -CRS2 register: HPE4 bitfield is 
**                                     removed.
**                                    -PRS3 register: M4 bitfield is 
**                                     removed.
**                                    -CRS3 register: HPE4 bitfield is 
**                                     removed.
**                                    -PRS4 register: M4 bitfield is 
**                                     removed.
**                                    -CRS4 register: HPE4 bitfield is 
**                                     removed.
**                                    -PRS5 register: M4 bitfield is 
**                                     removed.
**                                    -CRS5 register: HPE4 bitfield is 
**                                     removed.
**                                    -PRS6 register: M4 bitfield is 
**                                     removed.
**                                    -CRS6 register: HPE4 bitfield is 
**                                     removed.
**                                    3)MC_ME-
**                                    -PRTN0_CORE1_PCONF, PRTN0_CORE1_PUPD, 
**                                     PRTN0_CORE1_STAT and PRTN0_CORE1_ADDR 
**                                     registers are removed.
**                                    -PRTN2_COFB0_STAT register: BLOCK27 
**                                     bitfield is removed.
**                                    -PRTN2_COFB0_CLKEN register: REQ27 
**                                     bitfield is removed.
**                                    4)MC_RGM-
**                                    -FES register: SWT1_RST bitfield is 
**                                     removed.
**                                    -FERD register: D_SWT1_RST bitfield 
**                                     is removed.
**                                    -FBRE register: BE_SWT1_RST bitfield 
**                                     is removed.
**                                    5)MDM_AP-
**                                    -MDMAPSTTS register: CM71HLT, CM71DPSLP, 
**                                     CM71SLPNG and CM71DBGRSTRD bitfields 
**                                     are removed.
**                                    -MDMAPCTL register: CM71DBGREQ and CM71DBGRSRT 
**                                     bitfields are removed.
**                                    6)MSCM-
**                                    -CP1TYPE, CP1NUM, CP1REV, CP1CFG0, CP1CFG1, 
**                                     CP1CFG2 and CP1CFG3 registers are removed.
**                                    -IRCP0ISR0 register: CP1_INT bitfield is removed.
**                                    -IRCP0ISR1 register: CP1_INT bitfield is removed.
**                                    -IRCP0ISR2 register: CP1_INT bitfield is removed.
**                                    -IRCP0ISR3 register: CP1_INT bitfield is removed.
**                                    -IRCP1ISR0 register: CP1_INT bitfield is removed.
**                                    -IRCP1ISR1 register: CP1_INT bitfield is removed.
**                                    -IRCP1ISR2 register: CP1_INT bitfield is removed.
**                                    -IRCP1ISR3 register: CP1_INT bitfield is removed.
**                                    -IRCPCFG register: CP1_TR bitfield is removed.
**                                    -IRSPRC register: M7_1 bitfield is removed.
**                                    7)PFLASH-
**                                    PFCR register array size is changed from 3 to 2.
**                                    8)SDA_AP-
**                                    SDAAPRSTCTRL register: RSTRELTLCM71 bitfield is 
**                                    removed.
**                                    9)XRDC-
**                                    -MDA_W0_4_DFMT0 register is removed.
**                                    -MDACFG’s Valid array indices are 0-3, 5.
**                                    -PID array size is changed from 5 to 4.
**                                    10)MCM_1_CM7, MU_2__MUA, MU_2__MUB and SWT_1 
**                                    instances are removed.
**
**     -1.9 Taru Shree 26-Oct-21      1)Initial release based on RM Rev.3.
**                                    2)EMAC-
**                                    MAC_VLAN_INCL register array with MAC_VLAN_INCL, 
**                                    MAC_VLAN_INCL0, MAC_VLAN_INCL1, MAC_VLAN_INCL2, 
**                                    MAC_VLAN_INCL3, MAC_VLAN_INCL4, MAC_VLAN_INCL5, 
**                                    MAC_VLAN_INCL6 and MAC_VLAN_INCL7 registers is 
**                                    added.
**                                    3)XBIC_PERI and XBIC_EDMA instances positions 
**                                    are interchanged.
** ###################################################################
*/

/*!
 * @file S32K344.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/* Prevention from multiple including the same memory map */
#if !defined(S32K344_H_)  /* Check if memory map has not been already included */
#define S32K344_H_

/* ----------------------------------------------------------------------------
   -- IP Header Files
   ---------------------------------------------------------------------------- */

/* IP Header Files List */
#include "S32K344_ADC.h"
#include "S32K344_AXBS_LITE.h"
#include "S32K344_BCTU.h"
#include "S32K344_CMU_FC.h"
#include "S32K344_CMU_FM.h"
#include "S32K344_CONFIGURATION_GPR.h"
#include "S32K344_CRC.h"
#include "S32K344_DCM.h"
#include "S32K344_DCM_GPR.h"
#include "S32K344_DMA.h"
#include "S32K344_DMAMUX.h"
#include "S32K344_DMA_TCD.h"
#include "S32K344_EIM.h"
#include "S32K344_EMAC.h"
#include "S32K344_EMIOS.h"
#include "S32K344_ERM.h"
#include "S32K344_FCCU.h"
#include "S32K344_FIRC.h"
#include "S32K344_FLASH.h"
#include "S32K344_FLEXCAN.h"
#include "S32K344_FLEXIO.h"
#include "S32K344_FXOSC.h"
#include "S32K344_INTM.h"
#include "S32K344_JDC.h"
#include "S32K344_LCU.h"
#include "S32K344_LPCMP.h"
#include "S32K344_LPI2C.h"
#include "S32K344_LPSPI.h"
#include "S32K344_LPUART.h"
#include "S32K344_MCM_CM7.h"
#include "S32K344_MC_CGM.h"
#include "S32K344_MC_ME.h"
#include "S32K344_MC_RGM.h"
#include "S32K344_MDM_AP.h"
#include "S32K344_MSCM.h"
#include "S32K344_MU.h"
#include "S32K344_PFLASH.h"
#include "S32K344_PIT.h"
#include "S32K344_PLL.h"
#include "S32K344_PMC.h"
#include "S32K344_PRAMC.h"
#include "S32K344_QUADSPI.h"
#include "S32K344_QUADSPI_ARDB.h"
#include "S32K344_RTC.h"
#include "S32K344_SAI.h"
#include "S32K344_SDA_AP.h"
#include "S32K344_SELFTEST_GPR.h"
#include "S32K344_SEMA42.h"
#include "S32K344_SIRC.h"
#include "S32K344_SIUL2.h"
#include "S32K344_STCU.h"
#include "S32K344_STM.h"
#include "S32K344_SWT.h"
#include "S32K344_SXOSC.h"
#include "S32K344_TEMPSENSE.h"
#include "S32K344_TRGMUX.h"
#include "S32K344_TSPC.h"
#include "S32K344_VIRT_WRAPPER.h"
#include "S32K344_WKPU.h"
#include "S32K344_XBIC.h"
#include "S32K344_XRDC.h"
#include "S32K344_NVIC.h"
#include "S32K344_SCB.h"
#include "S32K344_SYSTICK.h"
#include "S32K344_MPU.h"

#endif  /* #if !defined(S32K344_H_) */
