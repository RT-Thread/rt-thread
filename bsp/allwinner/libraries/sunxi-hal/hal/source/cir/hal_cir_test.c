#include <stdio.h>
#include <stdlib.h>
#include <console.h>
#include <sunxi_hal_cir.h>

int cir_test(int argc, char *argv[])
{
    cir_port_t port = CIR_MASTER_0;
    cir_status_t ret = 0;

    ret = hal_cir_master_init(port);
    printf("ret:%d\n", ret);

    return ret;
}

FINSH_FUNCTION_EXPORT_CMD(cir_test, cirtest, test r-ir-tx);
