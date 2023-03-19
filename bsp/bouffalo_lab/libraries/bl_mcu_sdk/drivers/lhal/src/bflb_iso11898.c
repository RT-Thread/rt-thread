#include "bflb_iso11898.h"
#include "hardware/iso11898_reg.h"

void bflb_iso11898_init(struct bflb_device_s *dev, struct bflb_iso11898_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    /* first enter reset mode */
    regval = getreg32(reg_base + ISO11898_MODE_OFFSET);
    regval |= ISO11898_RESET_REQUEST;
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);

    /* force using PeliISO11898 not BasicISO11898 */
    regval = getreg32(reg_base + ISO11898_CLOCK_DIVIDER_OFFSET);
    regval |= ISO11898_CAN_MODE;
    putreg32(regval, reg_base + ISO11898_CLOCK_DIVIDER_OFFSET);

    /* config prescale and synchronisation_jump_width */
    regval = getreg32(reg_base + ISO11898_BUS_TIMING_0_OFFSET);
    regval &= ~ISO11898_BAUD_RATE_PRESCALER_MASK;
    regval |= (config->prescaler << ISO11898_BAUD_RATE_PRESCALER_SHIFT);
    regval &= ~ISO11898_SYNC_JUMP_WIDTH_MASK;
    regval |= (config->sjw << ISO11898_SYNC_JUMP_WIDTH_SHIFT);
    putreg32(regval, reg_base + ISO11898_BUS_TIMING_0_OFFSET);

    /* config samping and bit_segment_1/2 */
    regval = getreg32(reg_base + ISO11898_BUS_TIMING_1_OFFSET);
    if (config->sample == ISO11898_SAMPLE_SINGLE) {
        regval &= ~ISO11898_SAMPLING;
    } else {
        regval |= ISO11898_SAMPLING;
    }
    regval &= ~ISO11898_TIME_SEGMENT_1_MASK;
    regval |= (config->bs1 << ISO11898_TIME_SEGMENT_1_SHIFT);
    regval &= ~ISO11898_TIME_SEGMENT_2_MASK;
    regval |= (config->bs2 << ISO11898_TIME_SEGMENT_2_SHIFT);
    putreg32(regval, reg_base + ISO11898_BUS_TIMING_1_OFFSET);

    /* config mode */
    regval = getreg32(reg_base + ISO11898_MODE_OFFSET);
    if (config->mode == ISO11898_MODE_NORMAL) {
        regval &= ~ISO11898_LISTEN_ONLY;
        regval &= ~ISO11898_SELF_TEST;
    } else if (config->mode == ISO11898_MODE_LOOPBACK) {
        regval &= ~ISO11898_LISTEN_ONLY;
        regval |= ISO11898_SELF_TEST;
    } else if (config->mode == ISO11898_MODE_SILENT) {
        regval |= ISO11898_LISTEN_ONLY;
        regval &= ~ISO11898_SELF_TEST;
    } else if (config->mode == ISO11898_MODE_SILENT_LOOPBACK) {
        regval |= ISO11898_LISTEN_ONLY;
        regval |= ISO11898_SELF_TEST;
    } else {
    }
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);

    /* last leave reset mode */
    regval = getreg32(reg_base + ISO11898_MODE_OFFSET);
    regval &= ~ISO11898_RESET_REQUEST;
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);
}

void bflb_iso11898_deinit(struct bflb_device_s *dev)
{
}

void bflb_iso11898_abort_send(struct bflb_device_s *dev)
{
    putreg32(ISO11898_ABORT_TRANSMISSION, dev->reg_base + ISO11898_COMMAND_OFFSET);
}

int8_t bflb_iso11898_send(struct bflb_device_s *dev, struct bflb_iso11898_msg_s *msg, uint32_t timeout)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t data_base_addr;
    uint8_t mode;
    uint64_t start_time;

    reg_base = dev->reg_base;

    start_time = bflb_mtimer_get_time_ms();
    while (!(bflb_iso11898_get_status(dev) & ISO11898_STATUS_TX_AVAILABLE)) {
        if ((bflb_mtimer_get_time_ms() - start_time) > timeout) {
            return -ETIMEDOUT;
        }
    }

    /* config frame information register */
    regval = getreg32(reg_base + ISO11898_FRAME_INFORMATION_OFFSET);
    regval &= ~ISO11898_FRAME_INFORMATION_DLC_MASK;
    regval |= (msg->dlc << ISO11898_FRAME_INFORMATION_DLC_SHIFT);
    if (msg->id_type == ISO11898_ID_STANDARD) {
        regval &= ~ISO11898_FRAME_INFORMATION_FF;
    } else {
        regval |= ISO11898_FRAME_INFORMATION_FF;
    }
    if (msg->rtr == ISO11898_RTR_DATA) {
        regval &= ~ISO11898_FRAME_INFORMATION_RTR;
    } else {
        regval |= ISO11898_FRAME_INFORMATION_RTR;
    }
    putreg32(regval, reg_base + ISO11898_FRAME_INFORMATION_OFFSET);

    /* config id */
    if (msg->id_type == ISO11898_ID_STANDARD) {
        putreg32(msg->std_id >> (8 - ISO11898_SFF_ID2_BIT20_18_SHIFT), reg_base + ISO11898_SFF_ID1_OFFSET);
        putreg32(msg->std_id << ISO11898_SFF_ID2_BIT20_18_SHIFT, reg_base + ISO11898_SFF_ID2_OFFSET);
        data_base_addr = reg_base + ISO11898_SFF_DATA1_OFFSET;
    } else {
        putreg32(msg->ext_id >> 21, reg_base + ISO11898_EFF_ID1_OFFSET);
        putreg32(msg->ext_id >> 13, reg_base + ISO11898_EFF_ID2_OFFSET);
        putreg32(msg->ext_id >> 5, reg_base + ISO11898_EFF_ID3_OFFSET);
        putreg32(msg->ext_id << ISO11898_EFF_ID4_BIT4_0_SHIFT, reg_base + ISO11898_EFF_ID4_OFFSET);
        data_base_addr = reg_base + ISO11898_EFF_DATA1_OFFSET;
    }

    /* move data from user buff to registers */
    for (uint32_t i = 0; i < msg->dlc; i++) {
        *((uint32_t *)data_base_addr + i) = msg->data[i];
    }

    /* trig a request for transmit */
    mode = bflb_iso11898_get_mode(dev);
    if (mode == ISO11898_MODE_SILENT_LOOPBACK || mode == ISO11898_MODE_LOOPBACK) {
        putreg32(ISO11898_SELF_REQUEST, reg_base + ISO11898_COMMAND_OFFSET);
    } else if (mode == ISO11898_MODE_NORMAL) {
        putreg32(ISO11898_TRANSMIT_REQUEST, reg_base + ISO11898_COMMAND_OFFSET);
    } else {
        return -2;
    }
    return 0;
}

int8_t bflb_iso11898_recv(struct bflb_device_s *dev, struct bflb_iso11898_msg_s *msg, uint32_t timeout)
{
    uint32_t reg_base;
    uint32_t regval, regval2, regval3, regval4;
    uint32_t data_base_addr;
    uint64_t start_time;

    reg_base = dev->reg_base;

    start_time = bflb_mtimer_get_time_ms();
    while (!(bflb_iso11898_get_status(dev) & ISO11898_STATUS_RX_NOT_EMPTY)) {
        if ((bflb_mtimer_get_time_ms() - start_time) > timeout) {
            return -ETIMEDOUT;
        }
    }

    /* read information register */
    regval = getreg32(reg_base + ISO11898_FRAME_INFORMATION_OFFSET);
    msg->dlc = (uint8_t)((regval & ISO11898_FRAME_INFORMATION_DLC_MASK) >> ISO11898_FRAME_INFORMATION_DLC_SHIFT);
    if (regval & ISO11898_FRAME_INFORMATION_FF) {
        msg->id_type = ISO11898_ID_EXTENDED;
    } else {
        msg->id_type = ISO11898_ID_STANDARD;
    }
    if (regval & ISO11898_FRAME_INFORMATION_RTR) {
        msg->rtr = ISO11898_RTR_REMOTE;
    } else {
        msg->rtr = ISO11898_RTR_DATA;
    }

    /* receive with 11 or 29 bits ID */
    if (msg->id_type == ISO11898_ID_STANDARD) {
        regval = getreg32(reg_base + ISO11898_SFF_ID1_OFFSET);
        regval &= ISO11898_SFF_ID1_BIT28_21_MASK;
        regval <<= (8 - ISO11898_SFF_ID2_BIT20_18_SHIFT);
        regval2 = getreg32(reg_base + ISO11898_SFF_ID2_OFFSET);
        regval2 &= ISO11898_SFF_ID2_BIT20_18_MASK;
        regval2 >>= ISO11898_SFF_ID2_BIT20_18_SHIFT;
        msg->std_id = regval | regval2;
        data_base_addr = reg_base + ISO11898_SFF_DATA1_OFFSET;
    } else {
        regval = getreg32(reg_base + ISO11898_EFF_ID1_OFFSET);
        regval &= ISO11898_EFF_ID1_BIT28_21_MASK;
        regval <<= 21;
        regval2 = getreg32(reg_base + ISO11898_EFF_ID2_OFFSET);
        regval2 &= ISO11898_EFF_ID2_BIT20_13_MASK;
        regval2 <<= 13;
        regval3 = getreg32(reg_base + ISO11898_EFF_ID3_OFFSET);
        regval3 &= ISO11898_EFF_ID3_BIT12_5_MASK;
        regval3 <<= 5;
        regval4 = getreg32(reg_base + ISO11898_EFF_ID4_OFFSET);
        regval4 &= ISO11898_EFF_ID4_BIT4_0_MASK;
        regval4 >>= ISO11898_EFF_ID4_BIT4_0_SHIFT;
        msg->ext_id = regval | regval2 | regval3 | regval4;
        data_base_addr = reg_base + ISO11898_EFF_DATA1_OFFSET;
    }

    /* move data from registers to user buff */
    for (uint32_t i = 0; i < msg->dlc; i++) {
        msg->data[i] = (uint8_t)(*((uint32_t *)data_base_addr + i));
    }
    putreg32(ISO11898_RELEASE_RECEIVE_BUFFER, reg_base + ISO11898_COMMAND_OFFSET);
    return 0;
}

uint8_t bflb_iso11898_get_status(struct bflb_device_s *dev)
{
    return getreg32(dev->reg_base + ISO11898_STATUS_OFFSET) & 0xff;
}

void bflb_iso11898_set_mode(struct bflb_device_s *dev, uint8_t mode)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    /* first enter reset mode */
    regval = getreg32(reg_base + ISO11898_MODE_OFFSET);
    regval |= ISO11898_RESET_REQUEST;
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);

    /* config mode */
    regval = getreg32(reg_base + ISO11898_MODE_OFFSET);
    if (mode == ISO11898_MODE_NORMAL) {
        regval &= ~ISO11898_LISTEN_ONLY;
        regval &= ~ISO11898_SELF_TEST;
    } else if (mode == ISO11898_MODE_LOOPBACK) {
        regval &= ~ISO11898_LISTEN_ONLY;
        regval |= ISO11898_SELF_TEST;
    } else if (mode == ISO11898_MODE_SILENT) {
        regval |= ISO11898_LISTEN_ONLY;
        regval &= ~ISO11898_SELF_TEST;
    } else if (mode == ISO11898_MODE_SILENT_LOOPBACK) {
        regval |= ISO11898_LISTEN_ONLY;
        regval |= ISO11898_SELF_TEST;
    } else {
    }
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);

    /* last leave reset mode */
    regval = getreg32(reg_base + ISO11898_MODE_OFFSET);
    regval &= ~ISO11898_RESET_REQUEST;
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);
}

uint8_t bflb_iso11898_get_mode(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint8_t silent, loopback;

    regval = getreg32(dev->reg_base + ISO11898_MODE_OFFSET);
    if (regval & ISO11898_SELF_TEST) {
        loopback = 1;
    } else {
        loopback = 0;
    }
    if (regval & ISO11898_LISTEN_ONLY) {
        silent = 1;
    } else {
        silent = 0;
    }
    if (loopback && silent) {
        return ISO11898_MODE_SILENT_LOOPBACK;
    } else if (!loopback && silent) {
        return ISO11898_MODE_SILENT;
    } else if (loopback && !silent) {
        return ISO11898_MODE_LOOPBACK;
    } else {
        return ISO11898_MODE_NORMAL;
    }
}

void bflb_iso11898_set_filter(struct bflb_device_s *dev, struct bflb_iso11898_filter_s *filter)
{
    uint32_t reg_base;
    uint32_t regval;
    uint8_t mode;

    reg_base = dev->reg_base;
    /* first save mode */
    mode = bflb_iso11898_get_mode(dev);

    /* enter reset mode */
    regval = getreg32(reg_base + ISO11898_MODE_OFFSET);
    regval |= ISO11898_RESET_REQUEST;
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);

    /* config filter type */
    regval = getreg32(dev->reg_base + ISO11898_MODE_OFFSET);
    if (filter->filter_type == ISO11898_FILTER_TYPE_SINGLE) {
        regval |= ISO11898_FILTER_TYPE;
    } else {
        regval &= ~ISO11898_FILTER_TYPE;
    }
    putreg32(regval, reg_base + ISO11898_MODE_OFFSET);

    /* config filter code and mask */
    putreg32(filter->code0, reg_base + ISO11898_ACCEPTANCE_CODE_0_OFFSET);
    putreg32(filter->code1, reg_base + ISO11898_ACCEPTANCE_CODE_1_OFFSET);
    putreg32(filter->code2, reg_base + ISO11898_ACCEPTANCE_CODE_2_OFFSET);
    putreg32(filter->code3, reg_base + ISO11898_ACCEPTANCE_CODE_3_OFFSET);
    putreg32(filter->mask0, reg_base + ISO11898_ACCEPTANCE_MASK_0_OFFSET);
    putreg32(filter->mask1, reg_base + ISO11898_ACCEPTANCE_MASK_1_OFFSET);
    putreg32(filter->mask2, reg_base + ISO11898_ACCEPTANCE_MASK_2_OFFSET);
    putreg32(filter->mask3, reg_base + ISO11898_ACCEPTANCE_MASK_3_OFFSET);

    /* restore saved mode */
    bflb_iso11898_set_mode(dev, mode);
}

void bflb_iso11898_txint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + ISO11898_INTERRUPT_ENABLE_OFFSET);
    if (mask) {
        regval &= ~ISO11898_TRANSMIT_INT_EN;
    } else {
        regval |= ISO11898_TRANSMIT_INT_EN;
    }

    putreg32(regval, reg_base + ISO11898_INTERRUPT_ENABLE_OFFSET);
}

void bflb_iso11898_rxint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + ISO11898_INTERRUPT_ENABLE_OFFSET);
    if (mask) {
        regval &= ~ISO11898_RECEIVE_INT_EN;
    } else {
        regval |= ISO11898_RECEIVE_INT_EN;
    }

    putreg32(regval, reg_base + ISO11898_INTERRUPT_ENABLE_OFFSET);
}

void bflb_iso11898_errint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + ISO11898_INTERRUPT_ENABLE_OFFSET);
    if (mask) {
        regval &= ~ISO11898_ERROR_INT_EN;
        regval &= ~ISO11898_DATA_OVERRUN_INT_EN;
        regval &= ~ISO11898_ERROR_PASSIVE_INT_EN;
        regval &= ~ISO11898_ARB_LOST_INT_EN;
        regval &= ~ISO11898_BUS_ERROR_INT_EN;
    } else {
        regval |= ISO11898_ERROR_INT_EN;
        regval |= ISO11898_DATA_OVERRUN_INT_EN;
        regval |= ISO11898_ERROR_PASSIVE_INT_EN;
        regval |= ISO11898_ARB_LOST_INT_EN;
        regval |= ISO11898_BUS_ERROR_INT_EN;
    }

    putreg32(regval, reg_base + ISO11898_INTERRUPT_ENABLE_OFFSET);
}

uint32_t bflb_iso11898_get_int_status(struct bflb_device_s *dev)
{
    return getreg32(dev->reg_base + ISO11898_INTERRUPT_OFFSET);
}