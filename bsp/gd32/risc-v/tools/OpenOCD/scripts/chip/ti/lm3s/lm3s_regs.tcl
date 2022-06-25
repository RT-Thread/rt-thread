#*****************************************************************************
#
# The following are defines for the System Control register addresses.
#
#*****************************************************************************

set SYSCTL_DID0             0x400FE000  ;# Device Identification 0
set SYSCTL_DID1             0x400FE004  ;# Device Identification 1
set SYSCTL_DC0              0x400FE008  ;# Device Capabilities 0
set SYSCTL_DC1              0x400FE010  ;# Device Capabilities 1
set SYSCTL_DC2              0x400FE014  ;# Device Capabilities 2
set SYSCTL_DC3              0x400FE018  ;# Device Capabilities 3
set SYSCTL_DC4              0x400FE01C  ;# Device Capabilities 4
set SYSCTL_DC5              0x400FE020  ;# Device Capabilities 5
set SYSCTL_DC6              0x400FE024  ;# Device Capabilities 6
set SYSCTL_DC7              0x400FE028  ;# Device Capabilities 7
set SYSCTL_DC8              0x400FE02C  ;# Device Capabilities 8 ADC
                                        ;# Channels
set SYSCTL_PBORCTL          0x400FE030  ;# Brown-Out Reset Control
set SYSCTL_LDOPCTL          0x400FE034  ;# LDO Power Control
set SYSCTL_SRCR0            0x400FE040  ;# Software Reset Control 0
set SYSCTL_SRCR1            0x400FE044  ;# Software Reset Control 1
set SYSCTL_SRCR2            0x400FE048  ;# Software Reset Control 2
set SYSCTL_RIS              0x400FE050  ;# Raw Interrupt Status
set SYSCTL_IMC              0x400FE054  ;# Interrupt Mask Control
set SYSCTL_MISC             0x400FE058  ;# Masked Interrupt Status and
                                        ;# Clear
set SYSCTL_RESC             0x400FE05C  ;# Reset Cause
set SYSCTL_RCC              0x400FE060  ;# Run-Mode Clock Configuration
set SYSCTL_PLLCFG           0x400FE064  ;# XTAL to PLL Translation
set SYSCTL_GPIOHSCTL        0x400FE06C  ;# GPIO High-Speed Control
set SYSCTL_GPIOHBCTL        0x400FE06C  ;# GPIO High-Performance Bus
                                        ;# Control
set SYSCTL_RCC2             0x400FE070  ;# Run-Mode Clock Configuration 2
set SYSCTL_MOSCCTL          0x400FE07C  ;# Main Oscillator Control
set SYSCTL_RCGC0            0x400FE100  ;# Run Mode Clock Gating Control
                                        ;# Register 0
set SYSCTL_RCGC1            0x400FE104  ;# Run Mode Clock Gating Control
                                        ;# Register 1
set SYSCTL_RCGC2            0x400FE108  ;# Run Mode Clock Gating Control
                                        ;# Register 2
set SYSCTL_SCGC0            0x400FE110  ;# Sleep Mode Clock Gating Control
                                        ;# Register 0
set SYSCTL_SCGC1            0x400FE114  ;# Sleep Mode Clock Gating Control
                                        ;# Register 1
set SYSCTL_SCGC2            0x400FE118  ;# Sleep Mode Clock Gating Control
                                        ;# Register 2
set SYSCTL_DCGC0            0x400FE120  ;# Deep Sleep Mode Clock Gating
                                        ;# Control Register 0
set SYSCTL_DCGC1            0x400FE124  ;# Deep-Sleep Mode Clock Gating
                                        ;# Control Register 1
set SYSCTL_DCGC2            0x400FE128  ;# Deep Sleep Mode Clock Gating
                                        ;# Control Register 2
set SYSCTL_DSLPCLKCFG       0x400FE144  ;# Deep Sleep Clock Configuration
set SYSCTL_CLKVCLR          0x400FE150  ;# Clock Verification Clear
set SYSCTL_PIOSCCAL         0x400FE150  ;# Precision Internal Oscillator
                                        ;# Calibration
set SYSCTL_PIOSCSTAT        0x400FE154  ;# Precision Internal Oscillator
                                        ;# Statistics
set SYSCTL_LDOARST          0x400FE160  ;# Allow Unregulated LDO to Reset
                                        ;# the Part
set SYSCTL_I2SMCLKCFG       0x400FE170  ;# I2S MCLK Configuration
set SYSCTL_DC9              0x400FE190  ;# Device Capabilities 9 ADC
                                        ;# Digital Comparators
set SYSCTL_NVMSTAT          0x400FE1A0  ;# Non-Volatile Memory Information

set SYSCTL_RCC_USESYSDIV    0x00400000  ;# Enable System Clock Divider
set SYSCTL_RCC2_BYPASS2     0x00000800  ;# PLL Bypass 2
set SYSCTL_RCC_MOSCDIS      0x00000001  ;# Main Oscillator Disable

set SYSCTL_SRCR0            0x400FE040  ;# Software Reset Control 0
set SYSCTL_SRCR1            0x400FE044  ;# Software Reset Control 1
set SYSCTL_SRCR2            0x400FE048  ;# Software Reset Control 2

set SYSCTL_MISC             0x400FE058  ;# Masked Interrupt Status and Clear

set FLASH_FMA               0x400FD000  ;# Flash Memory Address
set FLASH_FMD               0x400FD004  ;# Flash Memory Data
set FLASH_FMC               0x400FD008  ;# Flash Memory Control
set FLASH_FCRIS             0x400FD00C  ;# Flash Controller Raw Interrupt Status
set FLASH_FCIM              0x400FD010  ;# Flash Controller Interrupt Mask
set FLASH_FCMISC            0x400FD014  ;# Flash Controller Masked Interrupt Status and Clear
set FLASH_FMC2              0x400FD020  ;#  Flash Memory Control 2
set FLASH_FWBVAL            0x400FD030  ;# Flash Write Buffer Valid
