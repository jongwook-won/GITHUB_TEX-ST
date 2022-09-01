/********************************************************************************
*	File Name	:	main.c
*	Compile		:	IAR Embedded Workbench avr 6.10
*	History		:	
*	- 20120725	created by suhyoun
*********************************************************************************/
#include "allinclude.h"

//-------------------------------------------------------------------------------
//	external variable
//-------------------------------------------------------------------------------

unsigned short ext_usRxTimer;
unsigned short ext_usLEDTimer;
unsigned short chk_PWMTimer;
BYTE LED_TIMER;
//-------------------------------------------------------------------------------
//	DESCRIPTION   : 
//	HISTORY       :
//		- 2012/07/25	created by suhyoun
//-------------------------------------------------------------------------------
void init_timer( void )
{
	unsigned int Timmer_Value;
	unsigned int Use_Hz;

    TIMSK = 0;

    // Set Timer 0  // 1ms --> 0.001S
	TCCR0			=  (1 << WGM01)|(1 << CS02) ;  //CTC MODE , CLK / 64     //FOC0, WGM00, COM01, COM00, WGM01, CS02, CS01, CS00
	OCR0			=  249;                        // 16MHz/ 64 / (1+249)  = 1000Hz --> CTC 모드의 실제 인터럽트 발생주파수      // OC0핀의 출력주파수는 1/2배 해야함.   16MHz/ 2 / 64 / (1+249)  = 500Hz
	TCNT0			=  0x00;
    TIMSK			|=  (1 << OCIE0) ;              // TIMER0  OCIE0 출력 비교 인터럽트 ENABLE
    TIFR			=  0x00;                       // 인터럽트 플래그 클리어
    ////////////////////////////////////////////////////////////////

	Use_Hz			= TIMER1_HZ;
	Timmer_Value	= (OSC / 256 / Use_Hz) - 1;
	TCCR1A			= 0x00;
	TCCR1B			= 0x0C;
	TCCR1C			= 0x00;
	OCR1AH			= ( Timmer_Value >> 8 );
	OCR1AL			= ( Timmer_Value & 0xFF );
	TCNT1H			= 0x00;					//Clear Timer / Counter1
	TCNT1L			= 0x00;
    TIMSK			|= (1 << OCIE1A);

    TIFR			= 0x00;
/*
	// Set Timer 3	//10ms --> 0.01S
	Use_Hz			= TIMER3_HZ;
	Timmer_Value	= (OSC / 256 / Use_Hz) - 1;
	TCCR3A			= 0x00;
	TCCR3B			= 0x0C;
	TCCR3C			= 0x00;
	OCR3AH			= ( Timmer_Value >> 8 );
	OCR3AL			= ( Timmer_Value & 0xFF );
	TCNT3H			= 0x00;					//Clear Timer / Counter1
	TCNT3L			= 0x00;

	ETIMSK			= (1 << OCIE3A);		                 // TIMER3 OCIE3A 출력 비교 인터럽트 ENABLE	  // Dummy7, Dummy6, TICIE3, OCIE3A, OCIE3B, TOIE3, OCIE3C, OCIE1C
	ETIFR			= 0x00;                                  // 인터럽트 플래그 클리어
 */
    // Dummy7, Dummy6, ICF3, OCF3A, OCF3B, TOV3, OCF3C, OCF1C
}

#pragma vector = TIMER0_COMP_vect
__interrupt void timer0_isr()  //1msec
{
  delay_timer++;
}
//----------------------------------------------------------------
//  Timer 1 Interrupt routine
//----------------------------------------------------------------
#pragma vector = TIMER1_COMPA_vect
__interrupt void timer_interrupt_routine()  //20msec timer
{
	ext_usRxTimer++;
    ext_usLEDTimer++;
    LED_TIMER++;
    chk_PWMTimer++;
}