#include "bflb_sec_trng.h"
#include "hardware/sec_eng_reg.h"

#define BFLB_PUT_LE32TOBYTES(p, val) \
    {                                \
        p[0] = val & 0xff;           \
        p[1] = (val >> 8) & 0xff;    \
        p[2] = (val >> 16) & 0xff;   \
        p[3] = (val >> 24) & 0xff;   \
    }

int bflb_trng_read(struct bflb_device_s *dev, uint8_t data[32])
{
    uint32_t regval;
    uint32_t reg_base;
    uint64_t start_time;
    uint8_t *p = (uint8_t *)data;

    reg_base = dev->reg_base;

    /* enable trng */
    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval |= SEC_ENG_SE_TRNG_0_EN;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval |= SEC_ENG_SE_TRNG_0_INT_CLR_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    /* busy will be set to 1 after trigger, the gap is 1T */
    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");

    start_time = bflb_mtimer_get_time_ms();
    while (getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET) & SEC_ENG_SE_TRNG_0_BUSY) {
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return -ETIMEDOUT;
        }
    }

    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval |= SEC_ENG_SE_TRNG_0_INT_CLR_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval |= SEC_ENG_SE_TRNG_0_TRIG_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    /* busy will be set to 1 after trigger, the gap is 1T */
    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");
    __ASM volatile("nop");

    start_time = bflb_mtimer_get_time_ms();
    while (getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET) & SEC_ENG_SE_TRNG_0_BUSY) {
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return -ETIMEDOUT;
        }
    }

    /* copy trng value */
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_0_OFFSET));
    p += 4;
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_1_OFFSET));
    p += 4;
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_2_OFFSET));
    p += 4;
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_3_OFFSET));
    p += 4;
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_4_OFFSET));
    p += 4;
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_5_OFFSET));
    p += 4;
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_6_OFFSET));
    p += 4;
    BFLB_PUT_LE32TOBYTES(p, getreg32(reg_base + SEC_ENG_SE_TRNG_0_DOUT_7_OFFSET));
    p += 4;

    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval &= ~SEC_ENG_SE_TRNG_0_TRIG_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval |= SEC_ENG_SE_TRNG_0_DOUT_CLR_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval &= ~SEC_ENG_SE_TRNG_0_DOUT_CLR_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    /* disable trng */
    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval &= ~SEC_ENG_SE_TRNG_0_EN;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    regval = getreg32(reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);
    regval |= SEC_ENG_SE_TRNG_0_INT_CLR_1T;
    putreg32(regval, reg_base + SEC_ENG_SE_TRNG_0_CTRL_0_OFFSET);

    return 0;
}

int bflb_trng_readlen(uint8_t *data, uint32_t len)
{
    struct bflb_device_s *trng;

    uint8_t tmp_buf[32];
    uint32_t readlen = 0;
    uint32_t i = 0, cnt = 0;

    trng = bflb_device_get_by_name("trng");

    while (readlen < len) {
        if (bflb_trng_read(trng, tmp_buf) != 0) {
            return -ETIMEDOUT;
        }

        cnt = len - readlen;

        if (cnt > sizeof(tmp_buf)) {
            cnt = sizeof(tmp_buf);
        }

        for (i = 0; i < cnt; i++) {
            data[readlen + i] = tmp_buf[i];
        }

        readlen += cnt;
    }

    return 0;
}

__WEAK long random(void)
{
    uint32_t data[8];
    struct bflb_device_s *trng;

    trng = bflb_device_get_by_name("trng");
    bflb_trng_read(trng, (uint8_t *)data);

    return data[0];
}

void bflb_group0_request_trng_access(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + SEC_ENG_SE_CTRL_PROT_RD_OFFSET);
    if (((regval >> 4) & 0x03) == 0x03) {
        putreg32(0x04, reg_base + SEC_ENG_SE_TRNG_0_CTRL_PROT_OFFSET);

        regval = getreg32(reg_base + SEC_ENG_SE_CTRL_PROT_RD_OFFSET);
        if (((regval >> 4) & 0x03) == 0x01) {
        }
    }
}

void bflb_group0_release_trng_access(struct bflb_device_s *dev)
{
    uint32_t reg_base;

    reg_base = dev->reg_base;

    putreg32(0x06, reg_base + SEC_ENG_SE_TRNG_0_CTRL_PROT_OFFSET);
}