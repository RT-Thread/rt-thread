/*!
    \file  gd32f30x_dbg.c
    \brief DBG driver
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#include "gd32f30x_dbg.h"

/*!
    \brief      read DBG_ID code register
    \param[in]  none
    \param[out] none
    \retval     DBG_ID code
*/
uint32_t dbg_id_get(void)
{
    return DBG_ID;
}

/*!
    \brief      enable low power behavior when the mcu is in debug mode
    \param[in]  dbg_low_power:
                this parameter can be any combination of the following values:
      \arg        DBG_LOW_POWER_SLEEP: keep debugger connection during sleep mode
      \arg        DBG_LOW_POWER_DEEPSLEEP: keep debugger connection during deepsleep mode
      \arg        DBG_LOW_POWER_STANDBY: keep debugger connection during standby mode
    \param[out] none
    \retval     none
*/
void dbg_low_power_enable(uint32_t dbg_low_power)
{
    DBG_CTL0 |= dbg_low_power;
}

/*!
    \brief      disable low power behavior when the mcu is in debug mode
    \param[in]  dbg_low_power:
                this parameter can be any combination of the following values:
      \arg        DBG_LOW_POWER_SLEEP: donot keep debugger connection during sleep mode
      \arg        DBG_LOW_POWER_DEEPSLEEP: donot keep debugger connection during deepsleep mode
      \arg        DBG_LOW_POWER_STANDBY: donot keep debugger connection during standby mode
    \param[out] none
    \retval     none
*/
void dbg_low_power_disable(uint32_t dbg_low_power)
{
    DBG_CTL0 &= ~dbg_low_power;
}

/*!
    \brief      enable peripheral behavior when the mcu is in debug mode
    \param[in]  dbg_periph: refer to dbg_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        DBG_FWDGT_HOLD : debug FWDGT kept when core is halted
      \arg        DBG_WWDGT_HOLD : debug WWDGT kept when core is halted
      \arg        DBG_CANx_HOLD (x=0,1,CAN1 is only available for CL series): hold CANx counter when core is halted
      \arg        DBG_I2Cx_HOLD (x=0,1): hold I2Cx smbus when core is halted
      \arg        DBG_TIMERx_HOLD (x=0,1,2,3,4,5,6,7,8,9,10,11,12,13,TIMER8..13 are not available for HD series): hold TIMERx counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_enable(dbg_periph_enum dbg_periph)
{
    DBG_CTL0 |= (uint32_t)dbg_periph;
}

/*!
    \brief      disable peripheral behavior when the mcu is in debug mode
    \param[in]  dbg_periph: refer to dbg_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        DBG_FWDGT_HOLD : debug FWDGT kept when core is halted
      \arg        DBG_WWDGT_HOLD : debug WWDGT kept when core is halted
      \arg        DBG_CANx_HOLD (x=0,1,CAN1 is only available for CL series): hold CAN0 counter when core is halted
      \arg        DBG_I2Cx_HOLD (x=0,1): hold I2Cx smbus when core is halted
      \arg        DBG_TIMERx_HOLD (x=0,1,2,3,4,5,6,7,8,9,10,11,12,13,TIMER8..13 are not available for HD series): hold TIMERx counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_disable(dbg_periph_enum dbg_periph)
{
    DBG_CTL0 &= ~(uint32_t)dbg_periph;
}

/*!
    \brief      enable trace pin assignment
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_trace_pin_enable(void)
{
    DBG_CTL0 |= DBG_CTL0_TRACE_IOEN;
}

/*!
    \brief      disable trace pin assignment
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_trace_pin_disable(void)
{
    DBG_CTL0 &= ~DBG_CTL0_TRACE_IOEN;
}

/*!
    \brief      trace pin mode selection 
    \param[in]  trace_mode:
      \arg        TRACE_MODE_ASYNC: trace pin used for async mode 
      \arg        TRACE_MODE_SYNC_DATASIZE_1: trace pin used for sync mode and data size is 1
      \arg        TRACE_MODE_SYNC_DATASIZE_2: trace pin used for sync mode and data size is 2
      \arg        TRACE_MODE_SYNC_DATASIZE_4: trace pin used for sync mode and data size is 4
    \param[out] none
    \retval     none
*/
void dbg_trace_pin_mode_set(uint32_t trace_mode)
{
    DBG_CTL0 &= ~DBG_CTL0_TRACE_MODE;
    DBG_CTL0 |= trace_mode;
}
