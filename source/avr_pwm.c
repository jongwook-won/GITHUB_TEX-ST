#include "allinclude.h"

unsigned int OCR3A_VAL = 0    ;
unsigned int OCR3B_VAL = 0    ;
unsigned int DUTY_VAL  = 100  ;
unsigned int cur_DUTY_VAL = 100;

void Timer3_pwm_initial(void)
{

    
//SFR_B_N(0x8A, TCCR3B, ICNC3, ICES3, Dummy5, WGM33, WGM32, CS32, CS31, CS30)         /* Timer/Counter 3 Control Register B */
//SFR_B_N(0x8B, TCCR3A, COM3A1, COM3A0, COM3B1, COM3B0, COM3C1, COM3C0, WGM31, WGM30) /* Timer/Counter 3 Control Register A */
//SFR_B_N(0x8C, TCCR3C, FOC3A, FOC3B, FOC3C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)/* Timer/Counter 3 Control Register C */    
    
    //COM3A1, COM3A0, COM3B1, COM3B0, COM3C1, COM3C0, WGM31, WGM30) /* Timer/Counter 3 Control Register A */
    TCCR3A = 0x21;		// Phase and Frequency Correct PWM mode(9) TONR1A(TOP), no OC1A, output OC1B, no OC1C   //OC1B가 MATCH에서 CLEAR, BOTTOM에서 SET된다. 
    //ICNC3, ICES3, Dummy5, WGM33, WGM32, CS32, CS31, CS30)         /* Timer/Counter 3 Control Register B */
	TCCR3B = 0x13;		// Pre-scale : 64
    
	OCR3A_VAL = 125000 / 120;			 // 주파수에 따른 OCR3A에 대입하는 값 계산.    60hz
	OCR3AH = ( OCR3A_VAL >> 8 );
	OCR3AL =   OCR3A_VAL & 0xFF; 
	
    
	OCR3B_VAL = (unsigned long)OCR3A_VAL * DUTY_VAL / 100;	 // OCR3A입력값으로 OCR1B에 대입하는 값 계산.
	OCR3BH = ( OCR3B_VAL >> 8 );
	OCR3BL =   OCR3B_VAL & 0xFF; 
}

void pwm_dimming_fun(void)
{
  if(PC_pwm_flag & 0x02){ 
    
    OCR3B_VAL = (unsigned long)OCR3A_VAL * pc_duty_100 / 100;	 // OCR3A입력값으로 OCR1B에 대입하는 값 계산.
    OCR3BH = ( OCR3B_VAL >> 8 );
    OCR3BL =   OCR3B_VAL & 0xFF;
    PC_pwm_flag &= ~0x02;
    
    printf("set ok pc_duty_100 = %d\r\n",pc_duty_100);
  }
  cur_DUTY_VAL = 200; // MANUAL DUTY로 전환되면 처음 값 WRITE되도록 변수값을 이상하게 설정 
}