//See LICENSE for license details

#ifndef _HBIRD_I2C_H
#define _HBIRD_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* register offsets */
//all registers are 8 bits width
#define I2C_REG_PRERlo          0x00
#define I2C_REG_PRERhi          0x01
#define I2C_REG_CTR             0X02
#define I2C_REG_TXR             0x03
#define I2C_REG_RXR             0X03
#define I2C_REG_CR              0X04
#define I2C_REG_SR              0X04

#define I2C_CTR_EN              (1 << 7)
#define I2C_CTR_IE              (1 << 6)

#define I2C_CR_STA              (1 << 7)
#define I2C_CR_STO              (1 << 6)
#define I2C_CR_RD               (1 << 5)
#define I2C_CR_WR               (1 << 4)
#define I2C_CR_ACK              (1 << 3)
#define I2C_CR_IACK             (1 << 0)

#define I2C_TXR_WRRD            (1 << 0)//0:write to slave; 1:read from slave;

#define I2C_SR_RXACK            (1 << 7)//0:received; 1:no ack resceived
#define I2C_SR_BUSY             (1 << 6)//0:after 'STOP' detected; 1:after 'START' detected
#define I2C_SR_AL               (1 << 5)
#define I2C_SR_TIP              (1 << 1)//0:transfer complete; 1:transfering
#define I2C_SR_IF               (1 << 0)
#if 0
/*fileds*/

#define I2C_CTR_ENABLE          1
#define I2C_CTR_DISABLE         0 

#define I2C_CTR_INTEN           1
#define I2C_CTR_INTDIS          0

#define I2C_TXR_RFS             1       //read from slave
#define I2C_TXR_WTS             0       //write to slave

#define I2C

#endif

#ifdef __cplusplus
}
#endif
#endif /* _HBIRD_I2C_H */
