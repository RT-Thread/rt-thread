#include "bflb_sec_aes.h"
#include "hardware/sec_eng_reg.h"

#define CONFIG_BFLB_AES_USE_BE

#define BFLB_PUT_LE32(p) ((p[3] << 24) | (p[2] << 16) | (p[1] << 8) | (p[0]))
#define BFLB_PUT_BE32(p) ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | (p[3]))

volatile uint8_t hw_key_sel = 1;

void bflb_aes_init(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

#ifdef CONFIG_BFLB_AES_USE_BE
    putreg32(0x1f, reg_base + SEC_ENG_SE_AES_0_ENDIAN_OFFSET);
#else
    putreg32(0x10, reg_base + SEC_ENG_SE_AES_0_ENDIAN_OFFSET);
#endif

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval |= SEC_ENG_SE_AES_0_EN;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
}

void bflb_aes_deinit(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval &= ~SEC_ENG_SE_AES_0_EN;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
}

void bflb_aes_set_hwkey(uint8_t keysel)
{
    hw_key_sel = keysel;
}

void bflb_aes_set_mode(struct bflb_device_s *dev, uint8_t mode)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval &= ~SEC_ENG_SE_AES_0_BLOCK_MODE_MASK;
    regval |= (mode << SEC_ENG_SE_AES_0_BLOCK_MODE_SHIFT);

    if (mode == AES_MODE_CTR) {
        regval |= SEC_ENG_SE_AES_0_DEC_KEY_SEL;
    } else {
        regval &= ~SEC_ENG_SE_AES_0_DEC_KEY_SEL; /* clear key to set new key */
    }

    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
}

void bflb_aes_setkey(struct bflb_device_s *dev, const uint8_t *key, uint16_t keybits)
{
    uint32_t regval;
    uint32_t reg_base;
    uint8_t mode;
    uint8_t *temp_key = (uint8_t *)key;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    mode = (regval & SEC_ENG_SE_AES_0_BLOCK_MODE_MASK) >> SEC_ENG_SE_AES_0_BLOCK_MODE_SHIFT;

    regval &= ~SEC_ENG_SE_AES_0_MODE_MASK;
    regval &= ~SEC_ENG_SE_AES_0_HW_KEY_EN;
    if (key == NULL) {
        regval |= SEC_ENG_SE_AES_0_HW_KEY_EN;
    }

    if (keybits == 128) {
        regval |= (0 << SEC_ENG_SE_AES_0_MODE_SHIFT);
    } else if (keybits == 192) {
        regval |= (2 << SEC_ENG_SE_AES_0_MODE_SHIFT);
    } else if (keybits == 256) {
        regval |= (1 << SEC_ENG_SE_AES_0_MODE_SHIFT);
    } else {
        regval |= (3 << SEC_ENG_SE_AES_0_MODE_SHIFT);
    }
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);

    if (key == NULL) {
        regval = getreg32(reg_base + SEC_ENG_SE_AES_0_KEY_SEL_OFFSET);
        regval &= ~SEC_ENG_SE_AES_0_KEY_SEL_MASK;
        regval |= (hw_key_sel << SEC_ENG_SE_AES_0_KEY_SEL_SHIFT);
        putreg32(regval, reg_base + SEC_ENG_SE_AES_0_KEY_SEL_OFFSET);

        regval = getreg32(reg_base + SEC_ENG_SE_AES_1_KEY_SEL_OFFSET);
        regval &= ~SEC_ENG_SE_AES_1_KEY_SEL_MASK;
        regval |= (hw_key_sel << SEC_ENG_SE_AES_1_KEY_SEL_SHIFT);
        putreg32(regval, reg_base + SEC_ENG_SE_AES_1_KEY_SEL_OFFSET);
    } else {
        putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_0_OFFSET);
        temp_key += 4;
        putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_1_OFFSET);
        temp_key += 4;
        putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_2_OFFSET);
        temp_key += 4;
        putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_3_OFFSET);
        temp_key += 4;

        if (keybits == 192) {
            putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_4_OFFSET);
            temp_key += 4;
            putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_5_OFFSET);
            temp_key += 4;
        } else if ((keybits == 256) || (mode == AES_MODE_XTS)) {
            putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_4_OFFSET);
            temp_key += 4;
            putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_5_OFFSET);
            temp_key += 4;
            putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_6_OFFSET);
            temp_key += 4;
            putreg32(BFLB_PUT_LE32(temp_key), reg_base + SEC_ENG_SE_AES_0_KEY_7_OFFSET);
            temp_key += 4;
        }
    }
}

int bflb_aes_encrypt(struct bflb_device_s *dev,
                     const uint8_t *input,
                     const uint8_t *iv,
                     uint8_t *output,
                     uint32_t len)
{
    uint32_t regval;
    uint32_t reg_base;
    uint64_t start_time;
    uint8_t mode;
    uint8_t *temp_iv = (uint8_t *)iv;

    reg_base = dev->reg_base;

    if (len % 16) {
        return -EINVAL;
    }

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval &= ~SEC_ENG_SE_AES_0_TRIG_1T;
    if (temp_iv) {
        regval &= ~SEC_ENG_SE_AES_0_IV_SEL; /* Clear aes iv sel to select new iv */
    } else {
        regval |= SEC_ENG_SE_AES_0_IV_SEL; /* Clear aes iv sel to select last iv */
    }
    regval &= ~SEC_ENG_SE_AES_0_DEC_EN; /* Set AES encryption */
    regval &= ~SEC_ENG_SE_AES_0_MSG_LEN_MASK;
    regval |= SEC_ENG_SE_AES_0_INT_CLR_1T;
    regval |= ((len / 16) << SEC_ENG_SE_AES_0_MSG_LEN_SHIFT);
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);

    mode = (regval & SEC_ENG_SE_AES_0_BLOCK_MODE_MASK) >> SEC_ENG_SE_AES_0_BLOCK_MODE_SHIFT;

    if (temp_iv) {
        if (mode == AES_MODE_XTS) {
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_3_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_2_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_1_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_0_OFFSET);
            temp_iv += 4;
        } else {
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_0_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_1_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_2_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_3_OFFSET);
            temp_iv += 4;
        }
    }

    /* Set input and output address */
    putreg32((uint32_t)input, reg_base + SEC_ENG_SE_AES_0_MSA_OFFSET);
    putreg32((uint32_t)output, reg_base + SEC_ENG_SE_AES_0_MDA_OFFSET);

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval |= SEC_ENG_SE_AES_0_TRIG_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);

    start_time = bflb_mtimer_get_time_ms();
    while (getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET) & SEC_ENG_SE_AES_0_BUSY) {
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return -ETIMEDOUT;
        }
    }
    return 0;
}

int bflb_aes_decrypt(struct bflb_device_s *dev,
                     const uint8_t *input,
                     const uint8_t *iv,
                     uint8_t *output,
                     uint32_t len)
{
    uint32_t regval;
    uint32_t reg_base;
    uint64_t start_time;
    uint8_t mode;
    uint8_t *temp_iv = (uint8_t *)iv;

    reg_base = dev->reg_base;

    if (len % 16) {
        return -EINVAL;
    }

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval &= ~SEC_ENG_SE_AES_0_TRIG_1T;
    if (temp_iv) {
        regval &= ~SEC_ENG_SE_AES_0_IV_SEL; /* Clear aes iv sel to select new iv */
    } else {
        regval |= SEC_ENG_SE_AES_0_IV_SEL; /* Clear aes iv sel to select last iv */
    }
    regval |= SEC_ENG_SE_AES_0_DEC_EN; /* Set AES decryption */
    regval |= SEC_ENG_SE_AES_0_INT_CLR_1T;
    regval &= ~SEC_ENG_SE_AES_0_MSG_LEN_MASK;
    regval |= ((len / 16) << SEC_ENG_SE_AES_0_MSG_LEN_SHIFT);
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);

    mode = (regval & SEC_ENG_SE_AES_0_BLOCK_MODE_MASK) >> SEC_ENG_SE_AES_0_BLOCK_MODE_SHIFT;

    if (temp_iv) {
        if (mode == AES_MODE_XTS) {
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_3_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_2_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_1_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_BE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_0_OFFSET);
            temp_iv += 4;
        } else {
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_0_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_1_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_2_OFFSET);
            temp_iv += 4;
            putreg32(BFLB_PUT_LE32(temp_iv), reg_base + SEC_ENG_SE_AES_0_IV_3_OFFSET);
            temp_iv += 4;
        }
    }

    /* Set input and output address */
    putreg32((uint32_t)input, reg_base + SEC_ENG_SE_AES_0_MSA_OFFSET);
    putreg32((uint32_t)output, reg_base + SEC_ENG_SE_AES_0_MDA_OFFSET);

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval |= SEC_ENG_SE_AES_0_TRIG_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);

    start_time = bflb_mtimer_get_time_ms();
    while (getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET) & SEC_ENG_SE_AES_0_BUSY) {
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return -ETIMEDOUT;
        }
    }
    return 0;
}

void bflb_aes_link_init(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

#ifdef CONFIG_BFLB_AES_USE_BE
    putreg32(0x1f, reg_base + SEC_ENG_SE_AES_0_ENDIAN_OFFSET);
#else
    putreg32(0x10, reg_base + SEC_ENG_SE_AES_0_ENDIAN_OFFSET);
#endif

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval |= SEC_ENG_SE_AES_0_LINK_MODE;
    regval |= SEC_ENG_SE_AES_0_EN;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
}

void bflb_aes_link_deinit(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval &= ~SEC_ENG_SE_AES_0_LINK_MODE;
    regval &= ~SEC_ENG_SE_AES_0_EN;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
}

int bflb_aes_link_update(struct bflb_device_s *dev,
                         uint32_t link_addr,
                         const uint8_t *input,
                         uint8_t *output,
                         uint32_t len)
{
    uint32_t regval;
    uint32_t reg_base;
    uint64_t start_time;

    reg_base = dev->reg_base;

    if ((len % 16) || ((link_addr & 0x03))) {
        return -EINVAL;
    }

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval &= ~SEC_ENG_SE_AES_0_TRIG_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);

    /* Set link address */
    putreg32(link_addr, reg_base + SEC_ENG_SE_AES_0_LINK_OFFSET);

    /* Change source buffer address and destination buffer address */
    *(uint32_t *)(uintptr_t)(link_addr + 4) = (uint32_t)(uintptr_t)input;
    *(uint32_t *)(uintptr_t)(link_addr + 8) = (uint32_t)(uintptr_t)output;

    /* Set data length */
    *((uint16_t *)(uintptr_t)link_addr + 1) = len / 16;

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);
    regval |= SEC_ENG_SE_AES_0_TRIG_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET);

    __asm volatile("nop");
    __asm volatile("nop");

    start_time = bflb_mtimer_get_time_ms();
    while (getreg32(reg_base + SEC_ENG_SE_AES_0_CTRL_OFFSET) & SEC_ENG_SE_AES_0_BUSY) {
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return -ETIMEDOUT;
        }
    }

    return 0;
}

void bflb_group0_request_aes_access(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + SEC_ENG_SE_CTRL_PROT_RD_OFFSET);
    if (((regval >> 2) & 0x03) == 0x03) {
        putreg32(0x02, reg_base + SEC_ENG_SE_AES_0_CTRL_PROT_OFFSET);

        regval = getreg32(reg_base + SEC_ENG_SE_CTRL_PROT_RD_OFFSET);
        if (((regval >> 2) & 0x03) == 0x01) {
        }
    }
}

void bflb_group0_release_aes_access(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg32(0x06, reg_base + SEC_ENG_SE_AES_0_CTRL_PROT_OFFSET);
}

void bflb_aes_set_hwkey_source(struct bflb_device_s *dev, uint8_t source)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + SEC_ENG_SE_AES_0_SBOOT_OFFSET);
    regval |= (source << 0);
    putreg32(0x02, reg_base + SEC_ENG_SE_AES_0_SBOOT_OFFSET);
}
