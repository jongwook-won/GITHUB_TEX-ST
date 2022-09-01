#ifndef I2C_H
#define I2C_H

extern unsigned short  ext_usI2cData_2;
extern unsigned char  ext_ucI2cDelay;
extern unsigned char eep_usPvcomDly;
extern SBYTE	Tx_Lenth_Update;


#define FU_NO      0
#define FU_3P3V    1
#define FU_1P8V    2
#define FD_GND     3




/*I2C.c*********************************************************************************************************************************
*******************************************************************************************************************************************/
void full_up_sel(unsigned char sel);
void i2c_chsel( unsigned char ch, unsigned char ucLine);


unsigned char  I2C_Write_1Byte( BYTE ucSlaveAddr, BYTE wSubAddress, BYTE ucData);
unsigned char I2C_Write_Several( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen );

unsigned char i2c_read( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen, unsigned char ODC_4096_flag );
unsigned char I2C_Write_Change_Add( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen, unsigned char ucByteNum );
unsigned char I2C_Read_Change_Add( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen, unsigned char ucByteNum );

unsigned char edid_write( unsigned char	ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen );

unsigned char NVsel_pvcom_write(unsigned char ucNvFlag, unsigned char ucData);
unsigned char NV_Vcom_PC_Control(unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned char ucThirdAddr,unsigned char ucNvData, unsigned char ucData);
unsigned char PM_IC_READ( unsigned char ucSlaveAddr, unsigned short usLen);
unsigned char v12_v13_v14_pvcom( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned char ucRwFlag );


unsigned char AUO_pvcom_write( unsigned char ucData);
unsigned char AUO_pvcom_read(void);






#endif 