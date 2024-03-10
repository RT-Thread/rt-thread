/* Generate scaled (nearest-neighbor) fonts. This can be used for displaying
 * larger text without spending the memory required for including larger fonts.
 */

#ifndef _MF_SCALEDFONT_H_
#define _MF_SCALEDFONT_H_

#include "mf_font.h"

struct mf_scaledfont_s
{
    struct mf_font_s font;

    const struct mf_font_s *basefont;
    uint8_t x_scale;
    uint8_t y_scale;
};

MF_EXTERN void mf_scale_font(struct mf_scaledfont_s *newfont,
                             const struct mf_font_s *basefont,
                             uint8_t x_scale, uint8_t y_scale);

#endif
