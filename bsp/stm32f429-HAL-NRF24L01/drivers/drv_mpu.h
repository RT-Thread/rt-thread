#ifndef __DRV_MPU_H
#define __DRV_MPU_H

/* Initialize Cortex M4 MPU */
int mpu_init(void);
void mpu_enable(int enable);

#endif
