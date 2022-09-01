
#include "allinclude.h"

unsigned short  ext_usI2cData_2;
unsigned char  ext_ucI2cDelay = 5;
unsigned char eep_usPvcomDly = 10;

extern unsigned char ext_ucRxbuf[];
extern unsigned char ext_ucTxbuf[];
extern unsigned char ext_ucRxStatus;



SBYTE	Tx_Lenth_Update;
 
unsigned char  I2C_Write_1Byte( BYTE ucSlaveAddr, BYTE wSubAddress, BYTE ucData)
{
	gpi2c_start_condition(&gpi2c_module);	
	if(gpi2c_write(&gpi2c_module,ucSlaveAddr)){
        gpi2c_stop_condition(&gpi2c_module);
        return 0xaa;
    }
	if(gpi2c_write(&gpi2c_module,wSubAddress)){
        gpi2c_stop_condition(&gpi2c_module);
        return 0xaa;
    }
	if(gpi2c_write(&gpi2c_module,ucData)){
        gpi2c_stop_condition(&gpi2c_module);
        return 0xaa;
    }
	gpi2c_stop_condition(&gpi2c_module);
       
    return 0;   
}

/**************************************************************************************
//Function Name : nv_write
**************************************************************************************/
unsigned char I2C_Write_Several( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen )
{
    SBYTE usCnt;
    unsigned char ucAckErr = 0;

    gpi2c_start_condition(&gpi2c_module);	
	if(gpi2c_write(&gpi2c_module,ucSlaveAddr)){
        gpi2c_stop_condition(&gpi2c_module);
        return 0xaa;
    }
	if(gpi2c_write(&gpi2c_module,wSubAddress)){
        gpi2c_stop_condition(&gpi2c_module);
        return 0xaa;
    }
    for(usCnt = 0; usCnt < usLen ; usCnt++){    
        if(gpi2c_write(&gpi2c_module,ext_ucRxbuf[ ext_usI2cData_2 + usCnt])){
            gpi2c_stop_condition(&gpi2c_module);
            return 0xaa;
        }
    }    
	gpi2c_stop_condition(&gpi2c_module);  
    
    return ucAckErr;
}

/**************************************************************************************
//Function Name : i2c_read
**************************************************************************************/
unsigned char i2c_read( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen, unsigned char ODC_4096_flag )
{
    BYTE  uvVal = 0;
    SBYTE usCnt;
    unsigned char ucAckErr = 0;
    
	gpi2c_start_condition(&gpi2c_module);	
	if(gpi2c_write(&gpi2c_module,ucSlaveAddr)){   // slave address
        gpi2c_stop_condition(&gpi2c_module);
        return 0xaa;
    }
    if(ODC_4096_flag){
        if(gpi2c_write(&gpi2c_module,0x00)){      // address msb 0으로 박음 
            gpi2c_stop_condition(&gpi2c_module);
            return 0xaa;
        }
    }
	if(gpi2c_write(&gpi2c_module,wSubAddress)){   //address lsb
        gpi2c_stop_condition(&gpi2c_module);
        return 0xaa;
    }

	gpi2c_start_condition(&gpi2c_module);	
	gpi2c_write(&gpi2c_module,(ucSlaveAddr|0x01));
	for(usCnt = 0; usCnt < usLen-1 ; usCnt++){
        uvVal =  gpi2c_read(&gpi2c_module,&uvVal,1); //1BYTE READ ACK
//        send_comm(START_ADDR+usCnt, 0, uvVal);
    }
    uvVal =  gpi2c_read(&gpi2c_module,&uvVal,0); //1BYTE READ NACK
//    send_comm(START_ADDR+ (usLen-1), 0, uvVal);
    
	gpi2c_stop_condition(&gpi2c_module);   
 
    Tx_Lenth_Update = usLen;
    
    return ucAckErr;
}


/**************************************************************************************
//Function Name : nv_write
**************************************************************************************/
unsigned char I2C_Write_Change_Add( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen, unsigned char ucByteNum )
{
    SBYTE usCnt;
    unsigned char ucAckErr = 0;
    BYTE i;
    
    for(usCnt = 0; usCnt < (usLen/ucByteNum) ; usCnt++){
        
        gpi2c_start_condition(&gpi2c_module);	
        if(gpi2c_write(&gpi2c_module,ucSlaveAddr)){
            gpi2c_stop_condition(&gpi2c_module);
            return 0xaa;
        }
        if(gpi2c_write(&gpi2c_module,wSubAddress)){
            gpi2c_stop_condition(&gpi2c_module);
            return 0xaa;
        }
        for(i = 0; i < ucByteNum ; i++){    
            if(gpi2c_write(&gpi2c_module,ext_ucRxbuf[ ext_usI2cData_2])){
                gpi2c_stop_condition(&gpi2c_module);
                return 0xaa;
            }
            ext_usI2cData_2++;
        }    
        gpi2c_stop_condition(&gpi2c_module);  
        wSubAddress++;
        delay_ms(5);
    }
    
    return ucAckErr;
}

unsigned char I2C_Read_Change_Add( unsigned char ucSlaveAddr, unsigned char wSubAddress, unsigned short usLen, unsigned char ucByteNum )
{
    SBYTE usCnt;
    unsigned char ucAckErr = 0;
    BYTE i, sendaddcnt = 0;
    BYTE  uvVal = 0;

    for(usCnt = 0; usCnt < (usLen/ucByteNum) ; usCnt++){
        
            gpi2c_start_condition(&gpi2c_module);	
            if(gpi2c_write(&gpi2c_module,ucSlaveAddr)){
                gpi2c_stop_condition(&gpi2c_module);
                return 0xaa;
            }
            if(gpi2c_write(&gpi2c_module,wSubAddress)){
                gpi2c_stop_condition(&gpi2c_module);
                return 0xaa;
            }
            gpi2c_start_condition(&gpi2c_module);	
            gpi2c_write(&gpi2c_module,(ucSlaveAddr|0x01));
            
            for(i = 0; i < (ucByteNum-1) ; i++){
                uvVal =  gpi2c_read(&gpi2c_module,&uvVal,1); //1BYTE READ ACK
//                send_comm(START_ADDR + sendaddcnt, 0, uvVal);
                
                sendaddcnt++;
            }
            uvVal =  gpi2c_read(&gpi2c_module,&uvVal,0); //1BYTE READ NACK
//            send_comm(START_ADDR+ sendaddcnt, 0, uvVal);
            
            sendaddcnt++;
            
            gpi2c_stop_condition(&gpi2c_module);  
            wSubAddress++;
            delay_ms(5);
    }
    Tx_Lenth_Update = sendaddcnt;
    
    return ucAckErr;
}