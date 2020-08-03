#include "i2c.h"

#define _XTAL_FREQ 20000000
#define feq_K 100

#define I2C_Hold()     while ((SSPCON2 & 0b00011111)||(SSPSTAT & 0b00000100))

void i2c_init(void)
{
    TRISC3 = 1;  TRISC4 = 1;  //Set SDA and SCL pins as input pins

    SSPCON  = 0b00101000;    //pg84/234
    SSPCON2 = 0b00000000;    //pg85/234

    SSPADD = (_XTAL_FREQ/(4*feq_K*100))-1; //Setting Clock Speed pg99/234
    SSPSTAT = 0b00000000;    //pg83/234
}

void i2c_start(void)
{
    I2C_Hold();  //Hold the program is I2C is busy 
    SEN = 1;     //Begin IIC pg85/234
}

void i2c_stop(void)
{
    I2C_Hold(); //Hold the program is I2C is busy 
    PEN = 1;    //End IIC pg85/234
}

void i2c_wb(unsigned char val)
{
    I2C_Hold(); //Hold the program is I2C is busy
    SSPBUF = val;         //pg82/234
}

unsigned char i2c_rb(unsigned short ack)
{
    unsigned short incoming;
    I2C_Hold();
    RCEN = 1;

    I2C_Hold();
    incoming = SSPBUF;      //get the data saved in SSPBUF

    I2C_Hold();
    ACKDT = (ack)?0:1;    //check if ack bit received 
    ACKEN = 1;          //pg 85/234

    return incoming;
}



