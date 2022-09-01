#ifndef GPIIC_H
#define GPIIC_H

      

typedef enum{
	PA,  
	PB,  
	PC,  
	PD,  
	PE,  
	PF,
	PG
}IoPortId;

typedef enum
{
	BITS0 = 0x1,
	BITS1 = 0x2,
	BITS2 = 0x4,
	BITS3 = 0x8,
	BITS4 = 0x10,
	BITS5 = 0x20,
	BITS6 = 0x40,
	BITS7 = 0x80
}BIT_INFO;



typedef struct {
	IoPortId sck_reg;
	BIT_INFO sck_pin;
	IoPortId sda_reg;
	BIT_INFO sda_pin;

	SBYTE u16_freq;
} GPI2C_INIT;



extern GPI2C_INIT gpi2c_module;

void gpi2c_start_condition(GPI2C_INIT* iic);
void gpi2c_stop_condition(GPI2C_INIT* iic);
void gpi2c_restart_condition(GPI2C_INIT* iic);
int gpi2c_write(GPI2C_INIT* iic, BYTE byte);
BYTE gpi2c_read(GPI2C_INIT* iic, BYTE* byte, BYTE status); //status 0 : nack ??, 1: ack ??.
#endif