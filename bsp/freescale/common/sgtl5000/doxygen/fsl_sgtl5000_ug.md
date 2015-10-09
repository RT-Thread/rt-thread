SGTL5000 Driver {#sgtl5000}
================
@ingroup sgtl5000

# Overview

The SGTL5000 driver is used to access SGTL5000 chip via I2C.

# Initialization

To initialize sgtl5000, call SGTL_Init(). Users need to transfer the sgtl_handler_t type pointer and user config pointer to this function. 

# Default setting

The sgtl5000 codec now use default settings, the main settings are shown below:
1. Use I2C0 as the transmit way, baud rate at 100K.
2. Sgtl5000 as audio slave.
3. The playback rounite is I2S IN->DAC->Headphone.
4. The record rounite is LINE IN->ADC->I2S OUT.

# Configuration

This version do not provide configure functions. Users can configure the sgtl5000 parameters through directly write or modify the sgtl5000 registers. Users can use SGTL_WriteReg() or SGTL_ModifyReg() to change the sgtl5000 settings.


# Call diagram 

To use sgtl5000 driver, follow the steps below:
1. Initialize the sgtl5000 codec by calling SGTL_Init().
2. Configure the data format of sgtl5000 by calling SGTL_ConfigDataFormat().
3. While applications end, call SGTL_Deinit() to close the sgtl5000 codec. 

