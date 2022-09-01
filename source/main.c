#include "allinclude.h"

unsigned char PC_pwm_H, PC_pwm_L,PC_pwm_flag,eeprom_pwm_H,eeprom_pwm_L;

unsigned short pc_duty_100;



void init_mcu(void)
{
  DDRA = (PAD0|PAD1|PAD2|PAD3|PAD4|PAD5|PAD6|PAD7);	
  DDRB = (PBD0|PBD1|PBD2|PBD3|PBD4|PBD5|PBD6|PBD7);	
  DDRC = (PCD0|PCD1|PCD2|PCD3|PCD4|PCD5|PCD6|PCD7);	
  DDRD = (PDD0|PDD1|PDD2|PDD3|PDD4|PDD5|PDD6|PDD7);	
  DDRE = (PED0|PED1|PED2|PED3|PED4|PED5|PED6|PED7);	
  DDRF = (PFD0|PFD1|PFD2|PFD3|PFD4|PFD5|PFD6|PFD7);
  DDRG = (PGD0|PGD1|PGD2|PGD3|PGD4);
  
  PORTA = (PAP0|PAP1|PAP2|PAP3|PAP4|PAP5|PAP6|PAP7);	
  PORTB = (PBP0|PBP1|PBP2|PBP3|PBP4|PBP5|PBP6|PBP7);	
  PORTC = (PCP0|PCP1|PCP2|PCP3|PCP4|PCP5|PCP6|PCP7);	
  PORTD = (PDP0|PDP1|PDP2|PDP3|PDP4|PDP5|PDP6|PDP7);	
  PORTE = (PEP0|PEP1|PEP2|PEP3|PEP4|PEP5|PEP6|PEP7);	
  PORTF = (PFP0|PFP1|PFP2|PFP3|PFP4|PFP5|PFP6|PFP7);
  PORTG = (PGP0|PGP1|PGP2|PGP3|PGP4);
}

void main( void )
{
  init_mcu();
  init_timer();
  init_uart0(207);
  init_uart1(207);
  init_Twi();
  
  __enable_interrupt();
  
 
  delay_ms(200);
  
  printf("\r\n Power ON ok\r\n");
  
  ext_ucRxStatus = 0x00;
  
  while(1)
  {
    if(LED_TIMER > 50)
      {
         if(LED_1==0) LED_1=1;
         else if (LED_1==1) LED_1=0;
         LED_TIMER = 0;
         //printf("%d\r\n",UDR1);
      }
    
    
    check_comm();
    
    fs_i2c_dimming_fun();
    pwm_dimming_fun();
    
    if(chk_PWMTimer>250)   //5 seconds
      {
        if(!(PC_pwm_flag & 0x08)) //check change pwm
        {
          chk_pwm_data();  // check before pwm , after pwm
        }
      }
  }
}



void check_comm(void)
{
  unsigned char ucSum;
  unsigned short usCnt, usLen;
  
  
  if( ext_ucRxStatus == 0xFD )
      {
         //            PIN_LED1 = HIGH;
        LED_2=0;
         ucSum = 0x00;
         usLen = (( ext_ucRxbuf[ 3 ] * 0x100 ) | ext_ucRxbuf[ 4 ]) + 4;
         
         for( usCnt = 0; usCnt < usLen; usCnt ++ )
            ucSum += ext_ucRxbuf[ 1 + usCnt ];	//check checksum
         
         if( ucSum == ext_ucRxbuf[ 1 + usLen ] )
         {
            printf("MC[0x%X],SC[0x%X],len[0x%X]\r\n", ext_ucRxbuf[ MAIN_CMD ],ext_ucRxbuf[ SUB_CMD ],usLen);
            printf("d0[0x%X],d1[0x%X]\r\n", ext_ucRxbuf[ 5 ],ext_ucRxbuf[ 6 ]);
            analyze_packet();
         }
         ext_ucRxStatus = 0x00;
      }
      if( ext_ucRxStatus )
      {
         if( ext_usRxTimer > 200 )
         {
            ext_usRxTimer = 0;
            ext_ucRxStatus = 0x00;
         }
      }
}

void analyze_packet(void)
{
  unsigned short temp;
    
    switch(ext_ucRxbuf[ MAIN_CMD ])
    {
        case 0xAA:
            PC_pwm_H = ext_ucRxbuf[ 5 ];
            PC_pwm_L = ext_ucRxbuf[ 6 ];
            
            start_pwm();  // first pwm_data take eeprom
            
            
            printf("PC_pwm_H = 0x%x\r\n",PC_pwm_H);
            printf("PC_pwm_L = 0x%x\r\n",PC_pwm_L);
            
            //AVR PWM 출력 내려고 0~100%로 다시 복원 
            temp =  ((unsigned short)PC_pwm_H << 8)| PC_pwm_L;
            temp = temp >> 6;
            pc_duty_100 = (unsigned short)((((float)temp / 1023) * 100) + 0.1);//연산시 0.1 모자라 1씩 짤려서 0.1 보상      
           
            printf("pc_duty_100 = %d\r\n",pc_duty_100); 
            
            chk_PWMTimer=0;
            PC_pwm_flag = 7;
        break;
    }
}

void EEPROM_Write(unsigned short address , unsigned char Data)
{
    while(EECR & (1 << EEWE));
    
    EEAR = address;
    EEDR = Data;
    
    EECR |= (1 << EEMWE);
    EECR |= (1 << EEWE);
}

unsigned char EEPROM_Read(unsigned short address)
{
    while(EECR & (1 << EEWE));
    
    EEAR = address;
    
    EECR |= (1<<EERE);
    
    return EEDR;
}


void chk_pwm_data(void)
{
  if(eeprom_pwm_H != PC_pwm_H)
  {
    if(eeprom_pwm_L != PC_pwm_L)  // check pwm data change
    {
      EEPROM_Write(0x2fe,PC_pwm_H);     // pwm_data to EEPROM
      EEPROM_Write(0x2ff,PC_pwm_L);
      
      printf("change eeprom pwm \r\n");
      PC_pwm_flag |= 0x08;              // toggle flag
    }
  }
}

void start_pwm(void)
{
  if(!(PC_pwm_flag & 0x04))  //start take EEPROM DATA
  {
    PC_pwm_H = EEPROM_Read(0x2fe);
    PC_pwm_L = EEPROM_Read(0x2ff);
    eeprom_pwm_H=PC_pwm_H;
    eeprom_pwm_L=PC_pwm_L;
  }
}
