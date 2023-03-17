#include "bflb_cks.h"
#include "hardware/cks_reg.h"

void bflb_cks_reset(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + CKS_CONFIG_OFFSET);
    regval |= CKS_CR_CKS_CLR;
    putreg32(regval, reg_base + CKS_CONFIG_OFFSET);
}

void bflb_cks_set_endian(struct bflb_device_s *dev, uint8_t endian)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;
    putreg32(endian << 1, reg_base + CKS_CONFIG_OFFSET);
}

uint16_t bflb_cks_compute(struct bflb_device_s *dev, uint8_t *data, uint32_t length)
{
    uint32_t reg_base;
    uint32_t i;

    reg_base = dev->reg_base;
    for (i = 0; i < length; i++) {
        putreg32(data[i], reg_base + CKS_DATA_IN_OFFSET);
    }

    return ((uint16_t)(getreg32(reg_base + CKS_OUT_OFFSET) & 0xffff));
}
