/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY'S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS'SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY'S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <hal_log.h>
#include <hal_cmd.h>
#include <sunxi_hal_spi.h>

#define TEST_READ 0
#define TEST_WRITE 1

static int cmd_test_spi(int argc, const char **argv)
{
    hal_spi_master_port_t  port;
    hal_spi_master_config_t cfg;
    hal_spi_master_status_t status;

    char tbuf[10]={0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20};
    char rbuf[10];
    char rw = 1;
    int c;

    if (argc < 3)
    {
        hal_log_info("Usage:");
        hal_log_info("\tspi <port> <-r|-w>");
        return -1;
    }

    hal_log_info("Run spi test");

    port = strtol(argv[1], NULL, 0);
    while ((c = getopt(argc, (char *const *)argv, "r:w")) != -1)
    {
        switch (c)
        {
            case 'r':
                rw = TEST_READ;
                break;
            case 'w':
                rw = TEST_WRITE;
                break;
        }
    }

    cfg.clock_frequency = 5000000;
    cfg.slave_port = HAL_SPI_MASTER_SLAVE_0;
    cfg.cpha = HAL_SPI_MASTER_CLOCK_PHASE0;
    cfg.cpol = HAL_SPI_MASTER_CLOCK_POLARITY0;
    hal_spi_init(port, &cfg);
    if (rw == TEST_READ)
    {
        status = hal_spi_read(port, rbuf, 10);
        hal_log_info("rbuf: %s", rbuf);
        hal_log_info("status: %d", status);

    }
    else if (rw == TEST_WRITE)
    {
        status = hal_spi_write(port, tbuf, 10);
        hal_log_info("status: %d", status);
    }

    hal_log_info("Spi test finish");

    hal_spi_deinit(port);

    return 0;
}

MSH_CMD_EXPORT_ALIAS(cmd_test_spi, hal_spi, spi hal APIs tests)
