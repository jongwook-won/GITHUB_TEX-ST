#include "allinclude.h"

volatile unsigned short delay_timer;

void delay_us( unsigned char ucTime )
{
	unsigned char ucCnt;
	
	for( ucCnt = 0; ucCnt < ucTime; ucCnt ++ )	// 4 cycle +
	{
		asm(" PUSH  R0 ");        // 2 cycle +
    	asm(" POP   R0 ");        // 2 cycle = 16 cycle = 1 us for 16MHz
		
		asm(" PUSH  R0 ");        // 2 cycle +
    	asm(" POP   R0 ");        // 2 cycle = 16 cycle = 1 us for 16MHz
		
		asm(" PUSH  R0 ");        // 2 cycle +
    	asm(" POP   R0 ");        // 2 cycle = 16 cycle = 1 us for 16MHz
	}
}

void delay_ms( unsigned short unTime )
{ 
    //timer를 쓰므로 인터럽터 enable 후에 사용해라 
    delay_timer = 0;
    
    while(delay_timer <= unTime);   
}