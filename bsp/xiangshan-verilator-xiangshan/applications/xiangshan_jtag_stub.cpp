#include "remote_bitbang.h"

remote_bitbang_t *jtag = nullptr;
bool enable_simjtag = false;
uint16_t remote_jtag_port = 23334;

extern "C" void jtag_init()
{
}

extern "C" int jtag_tick(unsigned char *jtag_TCK,
                          unsigned char *jtag_TMS,
                          unsigned char *jtag_TDI,
                          unsigned char *jtag_TRSTn,
                          unsigned char jtag_TDO)
{
    (void)jtag_TCK;
    (void)jtag_TMS;
    (void)jtag_TDI;
    (void)jtag_TRSTn;
    (void)jtag_TDO;
    return 0;
}