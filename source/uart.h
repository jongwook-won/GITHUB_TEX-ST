#ifndef UART_H
#define UART_H
  
extern unsigned char ext_ucRxStatus;
extern unsigned char ext_ucRxbuf[];
extern unsigned char ext_ucTxbuf[];
extern unsigned short ext_usRxTimer;
extern unsigned short ext_usLEDTimer;


void init_uart0( SBYTE Baudrate );
void init_uart1( SBYTE Baudrate );
int putchar(int ucData);
unsigned char uart0_rx_char( void );
void send_data( unsigned char ucMainCmd, unsigned char ucSubCmd, unsigned short usLen );
void uart_tx_char( unsigned char ucData );

#define	STX				    0x02
#define	ETX				    0x03

#define	MAIN_CMD            0x01
#define	SUB_CMD             0x02
#define LENGTH_H            0x03
#define LENGTH_L            0x04
#define RX_DATA             0x05


//Main CMD
#define GSP_M_PACKET        0x01
#define FUN_M_PACKET        0x02
//Sub CMD

#define	RS_DELAY		    100

#define UART_BAUD           9600

#endif