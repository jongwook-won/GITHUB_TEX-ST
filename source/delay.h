#ifndef DELAY_H
#define DELAY_H


extern volatile unsigned short delay_timer;

void delay_us( unsigned char ucTime );
void delay_ms( unsigned short unTime );



#endif