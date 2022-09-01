/********************************************************************************
*	File Name	:	uart.c
*	Compile		:	IAR Embedded Workbench avr 6.10
*	History		:	
*	- 20120725	created by suhyoun
*********************************************************************************/
#include "allinclude.h"


unsigned char	ext_ucRxStatus;
unsigned char	ext_ucRxbuf[20];
unsigned char	ext_ucTxbuf[20];

unsigned short	ext_usRxCnt;
unsigned short	ext_usLen;

extern unsigned short	ext_usRxTimer;

//-------------------------------------------------------------------------------
//	DESCRIPTION   : 
//	HISTORY       :
//		- 2012/07/25 	created by suhyoun
//-------------------------------------------------------------------------------
void init_uart0( SBYTE Baudrate )
{
   // 16Mhz에서 보레이트 2배 모드 일때
   //Baudrate 115,200    --> UBRR1L 16    error 2.1%
   //Baudrate  38,400    --> UBRR1L 51    error 0.2%
   //Baudrate  19,200    --> UBRR1L 103   error 0.2%
   //Baudrate   9,600    --> UBRR1L 207   error 0.2%
   volatile BYTE ucDummy;
   
   UBRR0H	= 0;
   UBRR0L	= (unsigned char)(Baudrate & 0x0FF);
   UCSR0A	= 0x02;			//BIT1 : 1 보레이트 2배 ,    asynchronous normal mode
   
   //UCSR0B	= 0x98;			//Rx / Tx enable, 8 data   // RX 인터럽트 허용 
   //UCSR0B	= 0x18;			//Rx / Tx enable, 8 data   // RX 인터럽트는 사용안함  
       UCSR0B	= 0x08;			    //     Tx enable, 8 data   // TX만 사용, RX는 사용안함 
   //UCSR0B	= 0x98;   //RX,TX 둘다 사요 , 이거 쓰면 RX 인터럽터 걸리며 문제 생기는거 같음 
   
   UCSR0C	= 0x06;			//no parity, 1 stop, 8 data
   ucDummy	= UDR0;			//dummy read
}

void init_uart1( SBYTE Baudrate )
{
   // 16Mhz에서 보레이트 2배 모드 일때
   //Baudrate 115,200    --> UBRR1L 16    error 2.1%
   //Baudrate  38,400    --> UBRR1L 51    error 0.2%
   //Baudrate  19,200    --> UBRR1L 103   error 0.2%
   //Baudrate   9,600    --> UBRR1L 207   error 0.2%
   volatile BYTE ucDummy;
   
   UBRR1H	= 0;
   UBRR1L	= (unsigned char)(Baudrate  & 0x0FF);
   UCSR1A	= 0x02;			//BIT1 : 1 보레이트 2배 , asynchronous normal mode
   
   UCSR1B	= 0x98;			//Rx / Tx enable, 8 data   //RX 인터럽트 허용
   //UCSR1B	= 0x18;         //Rx / Tx enable, 8 data   //RX 인터럽트는 사용안함 
   //UCSR1B	= 0x90;         //   / Tx enable, 8 data   //RX 인터럽트 사용, TX 사용안함    
   
   UCSR1C	= 0x06;			//no parity, 1 stop, 8 data
   ucDummy	= UDR1;			//dummy read
}

int putchar(int ucData)
{
    
	while(( UCSR0A & 0x20 ) == 0x00 )
	{
	}; // data register empty ?
	UDR0 = ucData;
    
	return 0;
} 
//-------------------------------------------------------------------------------
//	DESCRIPTION   : 
//	HISTORY       :
//		- 2012/07/25 	created by suhyoun
//-------------------------------------------------------------------------------

unsigned char uart0_rx_char( void )
{
  while(( UCSR0A & 0x80 ) == 0x00 );  // data received ?
  return UDR0;
}

//-------------------------------------------------------------------------------
//	DESCRIPTION   : 
//	HISTORY       :
//		- 2012/07/25 	created by suhyoun
//-------------------------------------------------------------------------------
void send_data( unsigned char ucMainCmd, unsigned char ucSubCmd, unsigned short usLen )
{
    unsigned char ucSum, ucLenH, ucLenL;
	unsigned short usCnt;
	
	ucSum = 0x00;
	
    ucLenH = usLen >> 8;
    ucLenL = usLen;
							
	uart_tx_char( STX );				        // STX
	//ucSum += STX;
	delay_us( RS_DELAY );
	
	uart_tx_char( ucMainCmd );			        // Main Command
	ucSum += ucMainCmd;
	delay_us( RS_DELAY );
	
	uart_tx_char( ucSubCmd );			        // Sub Command
	ucSum += ucSubCmd;
	delay_us( RS_DELAY );

    uart_tx_char( ucLenH );                     // data length high
    ucSum += ucLenH;
    delay_us( RS_DELAY );
	
    uart_tx_char( ucLenL );                     // data length low
    ucSum += ucLenL;
    delay_us( RS_DELAY );

    for( usCnt = 0; usCnt < usLen; usCnt ++ )	// Fill Data Field
	{
		uart_tx_char( ext_ucTxbuf[ usCnt ] );
		ucSum += ext_ucTxbuf[ usCnt ];
		delay_us( RS_DELAY );
	}
	
	uart_tx_char( ucSum );		                // CheckSum
	delay_us( RS_DELAY );
	uart_tx_char( ETX );		                // ETX
}

//-------------------------------------------------------------------------------
//	DESCRIPTION   : 
//	HISTORY       :
//		- 2012/07/25 	created by suhyoun
//-------------------------------------------------------------------------------
#pragma vector = USART1_RXC_vect
__interrupt void uart_interrupt_routine(void)
{
   unsigned char ucTemp;
   
   ucTemp = UDR1;
   
   LED_2=0;
  
   //uart_tx_char(ucTemp);
   
   // Receive STX
   //        printf("UDR0 = 0x%x\r\n",UDR0);
   if( ext_ucRxStatus == 0x00 )
   {
      //       printf("ucTemp = 0x%x\r\n",ucTemp);
      if( ucTemp == STX )
      {
         ext_ucRxbuf[ 0 ] = ucTemp;
         ext_ucRxStatus = 0x80;
         ext_usRxTimer = 0;
      }
   }
   // Receive Main Command
   else if( ext_ucRxStatus == 0x80 )
   {
      ext_ucRxbuf[ 1 ] = ucTemp;
      ext_ucRxStatus = 0xC0;
   }
   // Receive Sub Command
   else if( ext_ucRxStatus == 0xC0 )
   {
      ext_ucRxbuf[ 2 ] = ucTemp;
      ext_ucRxStatus = 0xE0;
   }
   // Receive Data Length
   else if( ext_ucRxStatus == 0xE0 )	// high byte
   {
      ext_ucRxbuf[ 3 ] = ucTemp;
      ext_ucRxStatus = 0xE1;
   }
   else if( ext_ucRxStatus == 0xE1 )	// low byte
   {
      ext_ucRxbuf[ 4 ] = ucTemp;
      ext_ucRxStatus = 0xF0;
      ext_usLen  = ( ext_ucRxbuf[ 3 ] * 0x100 ) | ext_ucRxbuf[ 4 ];
      ext_usRxCnt = 0;
   }
   // Receive Data
   else if( ext_ucRxStatus == 0xF0 )
   {
      if( ext_usRxCnt < ext_usLen )
      {
         ext_ucRxbuf[ ext_usRxCnt + 5 ] = ucTemp;
         ext_usRxCnt ++;
      }
      else //if( ext_usRxCnt == ext_usLen )
      {
         ext_ucRxbuf[ ext_usRxCnt + 5 ] = ucTemp;
         ext_ucRxStatus = 0xFC;
      }
   }
   // Receive ETX
   else if( ext_ucRxStatus == 0xFC )
   {
      if( ucTemp == ETX )
      {
         ext_ucRxbuf[ ext_usRxCnt + 6 ] = ucTemp;
         ext_ucRxStatus = 0xFD;
      }
      else
      {
         ext_ucRxStatus = 0x00;
      }
   }
}