#include "allinclude.h"


void fs_i2c_dimming_fun(void)
{
    unsigned short temp;
    unsigned short cal_chk;
    unsigned char tempH, tempL;
    unsigned char chk_NG;
    BYTE i;
   

        if(PC_pwm_flag & 0x01){ //20msec * 50 =  1000msec 1초 
            // I2C DIMMING MAX 1023
            // 100% : 1023
            //  50% : 512
            //  25% : 255
            //   5% :  51
          
            tempH = PC_pwm_H;
            tempL = PC_pwm_L;
            tempL |= 0x3F; // 하위 6 Bit, high로 할것  211217 신동엽 책임 추가 요청
            
            cal_chk = tempH + tempL;
            cal_chk = ~cal_chk;    //1의 보수 
            //printf("1 complement = 0x%X\r\n",cal_chk);
            cal_chk = cal_chk +1;  //2의 보수 
            //printf("2 complement = 0x%X\r\n",cal_chk);
            
            twi_write(0xA4, 73, tempH);
            delay_ms(1);
            twi_write(0xA4, 74, tempL);
            delay_ms(1);
            twi_write(0xA4, 254, (unsigned char)cal_chk); //chk
            delay_ms(20);
            
            for(i=0; i<10; i++){
                chk_NG = twi_read(0xA4, 5);
                printf("pc chk_NG =  0x%X\r\n",chk_NG);
                if((chk_NG & 0x01) == 0){ // 0번 비트가 0이면 ok  
                    twi_write(0xA4, 255, 0xAA);   // 0 :ok , 1: NG
                    PC_pwm_flag &= ~0x01;
                    break;
                }
                delay_ms(10);
            }

            ext_usLEDTimer = 0;
        }
   
    
    
}