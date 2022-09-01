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
    //timer�� ���Ƿ� ���ͷ��� enable �Ŀ� ����ض� 
    delay_timer = 0;
    
    while(delay_timer <= unTime);   
}