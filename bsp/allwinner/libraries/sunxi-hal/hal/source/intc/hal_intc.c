#include <stdint.h>
#include <hal_interrupt.h>
#include <hal_intc.h>

#include "intc.h"

static irqreturn_t intc_dispatcher(int dev, void *arg)
{
    interrupt_entry();

    return IRQ_HANDLED;
}

hal_intc_status_t hal_intc_init(uint32_t irq_no)
{
    hal_intc_status_t ret = HAL_INTC_STATUS_OK;

    /* initialize interrupt manager */
    interrupt_init();

    /* register intc main dispatcher handler */
    if (request_irq(irq_no, intc_dispatcher, 0, NULL, NULL) < 0) {
        ret = HAL_INTC_STATUS_FAIL;
        goto end;
    }

    enable_irq(irq_no);

end:
    return ret;
}
