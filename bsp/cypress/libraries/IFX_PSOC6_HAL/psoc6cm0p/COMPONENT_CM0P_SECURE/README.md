# PSoC 64 Cortex M0+ Secure prebuilt image (CM0P_SECURE)

### Overview

Secure prebuilt application image is required to be executed on the Cortex M0+ core of the PSoC 64 dual-core MCU.

Users of PSoC 64 Secure Boot devices have multi image boot scheme. In this case the Bootloader assumes 2 images are present in system - CM0p and CM4 in MCUBoot compatible format.

All applications developed for CM4 need to be combined with Secure CM0p prebuild image. This is a requirement of Secure Boot system architecture.

Secure prebuilt image executes the following steps:
- Enable/Disable CM4 access port per provisioning details acquired from Secure Flashboot
- Implement acquire procedure to enable programming and debugging if needed
- Implement acquire window time adjustment per provisioning details
- Set protection context to correspond User Application on CM4 level (per SAS on Secure Flashboot)
- Starts the CM4 core from the default address of image ID 16's BOOT section as found in default device family policy file provided by `cysecuretools` package

### Usage

This image is used by default by all Cypress BSPs that target PSoC 64 Dual-Core MCU.

This image is integrated with development environments which support PSoC 64 chips.

---
Copyright (c) Cypress Semiconductor Corporation, 2020.
