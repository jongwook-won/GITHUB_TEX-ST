#ifndef TWI_H
#define TWI_H



extern unsigned char LED_TIMER;

void init_Twi(void);
void TWI_Start(void);
void Twi_Byte_Write(unsigned char Data);
unsigned char Twi_Byte_Read(void);
unsigned char Twi_Multiple_Read(void);
void twi_write(unsigned char ucDev_add , unsigned char ucReg_add , unsigned short usData);
unsigned short twi_read(unsigned char ucDev_add , unsigned char ucReg_add);
void edid_save_3200(unsigned short add_edid);
void edid_save_1920(unsigned short add_edid);



#define TWI_Stop	TWCR = 0x94   // while((TWCR & 0x80) != 0x80) //TWINT + TWSTO + TEWN

#define I2C_SIG_OUT          0
#define EDID_I2C             1
#define UC_I2C               2

#define START_ADDR				0x0001

#define ADD_DDC_BANK_1 0xA2
#define ADD_DDC_BANK_2 0xA4
#define ADD_DDC_BANK_3 0xA6

#define EDID_DATA_SIZE 128

#endif