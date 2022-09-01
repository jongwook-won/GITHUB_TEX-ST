#include "allinclude.h"

extern unsigned char ext_ucRxbuf[];
extern unsigned char ext_ucTxbuf[];
//extern unsigned char edid_data[];

__flash unsigned char edid_data_3200_930[EDID_DATA_SIZE] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x1E, 0x6D, 0xBB, 0x5A, 0x01, 0x01, 0x01, 0x01,
0x01, 0x18, 0x01, 0x03, 0x80, 0x30, 0x1B, 0x78, 0xEA, 0x31, 0x35, 0xA5, 0x55, 0x4E, 0xA1, 0x26,
0x0C, 0x50, 0x54, 0xA5, 0x4B, 0x00, 0x71, 0x4F, 0x81, 0x80, 0x95, 0x00, 0xB3, 0x00, 0xA9, 0xC0,
0x81, 0x00, 0x81, 0xC0, 0x90, 0x40, 0xA5, 0x49, 0x80, 0x28, 0xC0, 0xA2, 0x0A, 0x30, 0x18, 0x10,
0x4E, 0x00, 0xE0, 0x0E, 0x11, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x38, 0x4B, 0x1E,
0x53, 0x0F, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x4C,
0x47, 0x20, 0x46, 0x55, 0x4C, 0x4C, 0x20, 0x48, 0x44, 0x0A, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFF,
0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x0F};

__flash unsigned char edid_data_1920_1080[EDID_DATA_SIZE] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x30, 0xE4, 0x52, 0xB7, 0x00, 0x00, 0x00, 0x00, 0x00,
0x18, 0x01, 0x03, 0x80, 0x16, 0x0D, 0x78, 0x0A, 0xA6, 0x33, 0x90, 0x50, 0x50, 0x8B, 0x26,
0x1D, 0x4E, 0x51, 0x00, 0x00, 0x00, 0x45, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF7, 0x35, 0x80, 0xA0, 0x70, 0x38, 0x1B, 0x40, 0x30, 0x20,
0x3A, 0x00, 0x24, 0x6D, 0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9B};

BYTE edid_read_data[128];

void init_Twi(void)// Twi init
{
    // CPU Clock frequcncy / 16 + 2(TWBR) * 4^TWPS  
  	unsigned char ucDummy;
	TWCR = 0x00;
    TWBR = 100;			
	TWSR = 0;
	ucDummy = TWDR;
}

void TWI_Start(void)
{
	unsigned long cnt;
	TWCR = 0xA4;	//TWINT + TWSTA + TWEN 
	cnt = 0; 
	while((TWCR & 0x80) != 0x80){if(++cnt > 0x1000)break;}
}

void Twi_Byte_Write(unsigned char Data)      //BYTE Write
{
    unsigned long cnt;
	TWDR =	Data; 
	TWCR = 0x84;    //TWINT + TWEN
	cnt = 0;
	while((TWCR & 0x80) != 0x80){if(++cnt > 0xF000)break;}
}
unsigned char Twi_Byte_Read(void) 			//BYTE Read ÈÄ Non Ack Pulse
{
	unsigned long cnt;
	TWCR = 0x84;    //TWINT + TWEN
	cnt = 0;
	while((TWCR & 0x80) != 0x80){if(++cnt > 0x1000)break;}
	
	return	TWDR; 
}
unsigned char Twi_Multiple_Read(void)		//BYTE Read ÈÄ Ack Pulse
{
  	unsigned long cnt;
  	TWCR = 0xC4;    //TWINT + TEWA + TWEN
	cnt = 0;
	while((TWCR & 0x80) != 0x80)if(++cnt > 0x1000)break;
	
	return	TWDR; 
}

void twi_write(unsigned char ucDev_add , unsigned char ucReg_add , unsigned short usData)
{
    TWI_Start();
    delay_us(2);
//    delay_ms(6);
    Twi_Byte_Write(ucDev_add);
    delay_us(5);
//    delay_ms(6);
    Twi_Byte_Write(ucReg_add);
    delay_us(5);    
//    delay_ms(6);
    Twi_Byte_Write((unsigned char)usData);
    delay_us(2);      
//    delay_ms(6);
    TWI_Stop;
    delay_ms(10);
}

unsigned short twi_read(unsigned char ucDev_add , unsigned char ucReg_add)
{
    unsigned char temp_H, temp_L;
    BYTE i;
    edid_read_data[0] = 1;
    //unsigned short read_v=0;
    
//    for(i=0; i<128; i++){
//    
      TWI_Start();
      delay_us(5);
      //delay_ms(6);
      Twi_Byte_Write(ucDev_add);
      delay_us(2);
      //delay_ms(6);
      Twi_Byte_Write(ucReg_add);
//       Twi_Byte_Write(i);
      
      delay_us(2);
      //delay_ms(6);
      
      TWI_Start();
      delay_us(2);
      delay_us(2); 
      //delay_ms(6);
      Twi_Byte_Write(ucDev_add + 1); 
      //delay_ms(6);
  
      delay_us(2);
      
//      for(i = 0 ; i < 127 ; i++)
//      {    
//      edid_read_data[i] = Twi_Multiple_Read();
//      }
      edid_read_data[0] = Twi_Byte_Read();  
      //delay_ms(6);
//      edid_read_data[i] = Twi_Byte_Read();
      
      TWI_Stop;
      delay_ms(1);
//    }
    delay_us(5);
    
    temp_L = 0;
    //read_v = (unsigned short)temp_H << 8;
    //read_v = read_v | temp_L;
    
    //read_v = read_v >> 6;
    
//    for(i = 0; i<128;i++)
//    {
//      printf("edid_read_data[%d] = %x\r\n",i,edid_read_data[i]);
//    }
    
//    return temp_L;
//    printf("edid_read_data[0] = %d\r\n",edid_read_data[0]);
    return edid_read_data[0];
}
/*
void edid_save(unsigned short add_edid)
{
    BYTE i;
    TWI_Start();
    delay_us(2);
    
    Twi_Byte_Write(add_edid);
    delay_us(2);
    
    Twi_Byte_Write(0);
    delay_us(2);
    
    for(i = 0 ; i < EDID_DATA_SIZE; i++)
    {
    Twi_Byte_Write(edid_data[i]);
    delay_us(2);
//    printf("edid_data[i] = %x\r\n",edid_data[i]);
    }
    
    TWI_Stop;
}
*/
void edid_save_3200(unsigned short add_edid)
{
    BYTE i;
    
    for(i = 0 ; i < EDID_DATA_SIZE; i++)
    {
      TWI_Start();
      delay_us(2);
      
      Twi_Byte_Write(add_edid);
      delay_us(2);
      
      Twi_Byte_Write(i);
      delay_us(2);
      
      Twi_Byte_Write(edid_data_3200_930[i]);
      delay_us(2);
      //    printf("edid_data[i] = %x\r\n",edid_data[i]);
      TWI_Stop;
      delay_ms(10);
    }
}
void edid_save_1920(unsigned short add_edid)
{
    BYTE i;
    
    for(i = 0 ; i < EDID_DATA_SIZE; i++)
    {
      TWI_Start();
      delay_us(2);
      
      Twi_Byte_Write(add_edid);
      delay_us(2);
      
      Twi_Byte_Write(i);
      delay_us(2);
      
      Twi_Byte_Write(edid_data_1920_1080[i]);
      delay_us(2);
      //    printf("edid_data[i] = %x\r\n",edid_data[i]);
      TWI_Stop;
      delay_ms(10);
    }
}
