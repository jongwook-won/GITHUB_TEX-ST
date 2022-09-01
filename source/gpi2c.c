#include "allinclude.h"


//GPI2C_INIT gpi2c_eep = {IOPORT_G, BIT_12, IOPORT_G, BIT_14, 400}; //sck_reg , sck pin, sda_reg, sda_pin
/*
GPI2C_INIT gpi2c_module =
{
    PG,BITS3,  PG,BITS4, 20
};
*/

#define ACK_WAIT  30
//*****************************************************************************//
//**************************** 1 Byte ?? ???? Library *******************//
//************************************** I2C *********************************//
//************************************************************ SYW 151026 V0.1*//

void PORTSetBits(IoPortId id, BIT_INFO bit)
{
	switch(id)
	{
		case PA:    PORTA |= bit;	DDRA &= (~bit);break;
		case PB:    PORTB |= bit;	DDRB &= (~bit);break;
		case PC:    PORTC |= bit;	DDRC &= (~bit);break;
		case PD:    PORTD |= bit;	DDRD &= (~bit);break;
		case PE:    PORTE |= bit;	DDRE &= (~bit);break;
		case PF:    PORTF |= bit;	DDRF &= (~bit);break;
		case PG:    PORTG |= bit;	DDRG &= (~bit);break;
	}
}

void PORTClearBits(IoPortId id, BIT_INFO bit)
{
	switch(id)
	{
		case PA:    PORTA &= (~bit);	DDRA |= (bit);break;  
		case PB:    PORTB &= (~bit);	DDRB |= (bit);break;		
		case PC:    PORTC &= (~bit);	DDRC |= (bit);break;
		case PD:    PORTD &= (~bit);	DDRD |= (bit);break;
		case PE:    PORTE &= (~bit);	DDRE |= (bit);break;
		case PF:    PORTF &= (~bit);	DDRF |= (bit);break;
		case PG:    PORTG &= (~bit);	DDRG |= (bit);break;
	}
	
}

BYTE PORTReadBits(IoPortId id, BIT_INFO bit)
{  
	switch(id)
	{
		case PA: 
		  	DDRA &= (~bit);
			if(PINA & bit)	return 1;
			else			return 0;
			break;
		case PB: 
		  	DDRB &= (~bit);
			if(PINB & bit)	return 1;
			else			return 0;
			break;
		case PC:
			DDRC &= (~bit);
			if(PINC & bit)	return 1;
			else			return 0;
			break;
		case PD:  
			DDRD &= (~bit);
			if(PIND & bit)	return 1;
			else			return 0;
			break;
		case PE: 
			DDRE &= (~bit);
			if(PINE & bit)	return 1;
			else			return 0;
			break;
		case PF: 
		  	DDRF &= (~bit);
			if(PINF & bit)	return 1;
			else			return 0;
			break;
		case PG:  
			DDRG &= (~bit);
			if(PING & bit)	return 1;
			else			return 0;
			break;
	}
    
	return 0;
}


void gpi2c_start_condition(GPI2C_INIT* iic) {
    PORTSetBits(iic->sda_reg, iic->sda_pin);
    delay_us(iic->u16_freq);
    PORTSetBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);

    PORTClearBits(iic->sda_reg, iic->sda_pin);
    delay_us(iic->u16_freq);
    PORTClearBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);
}

void gpi2c_stop_condition(GPI2C_INIT* iic) {
    PORTClearBits(iic->sck_reg, iic->sck_pin);
    PORTClearBits(iic->sda_reg, iic->sda_pin);
    delay_us(iic->u16_freq);
    PORTSetBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);
    PORTSetBits(iic->sda_reg, iic->sda_pin);
    delay_us(iic->u16_freq);
}

void gpi2c_restart_condition(GPI2C_INIT* iic) {

    PORTSetBits(iic->sda_reg, iic->sda_pin);
    delay_us(iic->u16_freq);

    PORTSetBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);

    PORTClearBits(iic->sda_reg, iic->sda_pin);
    delay_us(iic->u16_freq);

    PORTClearBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);
}



//void gpi2c_write(GPI2C_INIT* iic, BYTE byte)
//I2C 1BYTE Write.

int gpi2c_write(GPI2C_INIT* iic, BYTE byte) {
    int i = 0, err = 0;
    for (i = 0; i < 8; i++) {

        if (byte & 0x80) PORTSetBits(iic->sda_reg, iic->sda_pin);
        else PORTClearBits(iic->sda_reg, iic->sda_pin);

        delay_us(iic->u16_freq);
        PORTSetBits(iic->sck_reg, iic->sck_pin);
        delay_us(iic->u16_freq);
        PORTClearBits(iic->sck_reg, iic->sck_pin);
        delay_us(iic->u16_freq);
        byte <<= 1;
    }
    delay_us(iic->u16_freq);
	PORTReadBits(iic->sda_reg, iic->sda_pin);//SDA INPUT 으로 만들어줌.
	
    PORTSetBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);
    for (i = 0; i < ACK_WAIT; i++) {
        if (!PORTReadBits(iic->sda_reg, iic->sda_pin)) {
            err = 0;
            break;
        }
        delay_us(iic->u16_freq);
    }
    if (i >= ACK_WAIT) err = 0xAA;
    PORTClearBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);

    return err;
}

//void gpi2c_write(GPI2C_INIT* iic, BYTE byte)
//I2C 1BYTE Write.

BYTE gpi2c_read(GPI2C_INIT* iic, BYTE* byte, BYTE status) //status 0 : nack ??, 1: ack ??.
{
    int i = 0;
    BYTE rdData = 0;
    
    PORTReadBits(iic->sda_reg, iic->sda_pin);//SDA INPUT 으로 만들어줌.
    delay_us(iic->u16_freq);
    for (i = 0; i < 8; i++) {
        PORTSetBits(iic->sck_reg, iic->sck_pin);
        delay_us(iic->u16_freq);
        rdData <<= 1;
        if (PORTReadBits(iic->sda_reg, iic->sda_pin)) rdData |= 0x01;

        PORTClearBits(iic->sck_reg, iic->sck_pin);
        delay_us(iic->u16_freq);
    }

    if (status) {
        PORTClearBits(iic->sda_reg, iic->sda_pin);  //ACK
    } else {
        PORTSetBits(iic->sda_reg, iic->sda_pin);   //NACK
    }
    delay_us(iic->u16_freq);
    PORTSetBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);
    PORTClearBits(iic->sck_reg, iic->sck_pin);
    delay_us(iic->u16_freq);
    PORTClearBits(iic->sda_reg, iic->sda_pin);

    *byte = rdData;
    return rdData;
}