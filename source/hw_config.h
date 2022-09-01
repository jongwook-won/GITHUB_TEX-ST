#ifndef	_HW_CONFIG_
#define _HW_CONFIG_

//==========================================================================//
//**************             DEBUG 함수               **********************//
//==========================================================================//
#define USE         On
#define N_USE       Off
#define DEBUG       USE

//==========================================================================//
//**************             자료형 정리              **********************//
//==========================================================================//
typedef unsigned char			BYTE;
typedef unsigned short			SBYTE;
typedef unsigned int			IBYTE;
typedef unsigned long			LBYTE;
typedef volatile unsigned char		V_BYTE;
typedef volatile unsigned short		V_SBYTE;
typedef volatile unsigned long		V_LBYTE;

//==========================================================================//
//**************             Enum Declarations        **********************//
//==========================================================================//
enum                                                      
{
    Bit0  = 0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7,   // Port Bit State
    Input = 0, Output,                                     // Input / Output State
    LOW   = 0, HIGH,                                       // Up / Down State
    CLR = 0, SET, ALL_CLR,                                 // DAC State
    Off   = 0, On,
    DISABLE = 0,ENABLE,
    FALSE = 0,TRUE,
    READ =0,  WRITE, 
    mA_sel=0,  uA_sel,
    
};

//==========================================================================//
//**************             Timer 변수               **********************//
//==========================================================================//
#define MCK_16Mhz					16000000 
#define MCK						MCK_16Mhz
#define Get_Mcu_Frequency()			        ((LBYTE)MCK)	

//==========================================================================//
//**************             Atmega128 PORT 입출력 설정 ********************//
//==========================================================================//
#define PAD0						(V_BYTE)(Output<<Bit0)  // 
#define PAD1						(V_BYTE)(Output<<Bit1)  // 
#define PAD2						(V_BYTE)(Output<<Bit2)  // 
#define PAD3						(V_BYTE)(Output<<Bit3)  // 
#define PAD4						(V_BYTE)(Output<<Bit4)  // 
#define PAD5						(V_BYTE)(Output<<Bit5)  // 
#define PAD6						(V_BYTE)(Output<<Bit6)  // 
#define PAD7						(V_BYTE)(Output<<Bit7)  

#define PBD0						(V_BYTE)(Output<<Bit0)	// 
#define PBD1						(V_BYTE)(Output<<Bit1)	// 
#define PBD2						(V_BYTE)(Output<<Bit2)	// 
#define PBD3						(V_BYTE)(Output<<Bit3)	// 
#define PBD4						(V_BYTE)(Output<<Bit4)	// 
#define PBD5						(V_BYTE)(Output<<Bit5)	// 
#define PBD6						(V_BYTE)(Output<<Bit6)	// 
#define PBD7						(V_BYTE)(Output<<Bit7)	// 

#define PCD0						(V_BYTE)(Output<<Bit0)  // LED1
#define PCD1						(V_BYTE)(Output<<Bit1)  // LED2
#define PCD2						(V_BYTE)(Output<<Bit2)  // 
#define PCD3						(V_BYTE)(Output<<Bit3)  // 
#define PCD4						(V_BYTE)(Output<<Bit4)  // 
#define PCD5						(V_BYTE)(Output<<Bit5)  // 
#define PCD6						(V_BYTE)(Output<<Bit6)  //
#define PCD7						(V_BYTE)(Output<<Bit7)  // 

#define PDD0						(V_BYTE)(Output<<Bit0)	// SCL
#define PDD1						(V_BYTE)(Output<<Bit1)	// SDA
#define PDD2						(V_BYTE)(Input<<Bit2)	// RXD
#define PDD3						(V_BYTE)(Input<<Bit3)  // TXD
#define PDD4						(V_BYTE)(Output<<Bit4)  // 
#define PDD5						(V_BYTE)(Output<<Bit5)  // 
#define PDD6						(V_BYTE)(Output<<Bit6)  // 
#define PDD7						(V_BYTE)(Output<<Bit7)  // 

#define PED0						(V_BYTE)(Output<<Bit0)	// ISP_RXD
#define PED1						(V_BYTE)(Output<<Bit1)  // ISP_TXD
#define PED2						(V_BYTE)(Output<<Bit2)  // 
#define PED3						(V_BYTE)(Output<<Bit3)  // 
#define PED4						(V_BYTE)(Output<<Bit4)  // 
#define PED5						(V_BYTE)(Output<<Bit5) 	// 
#define PED6						(V_BYTE)(Output<<Bit6) 	// 
#define PED7						(V_BYTE)(Output<<Bit7) 	// 

#define PFD0						(V_BYTE)(Output<<Bit0)  // 
#define PFD1						(V_BYTE)(Output<<Bit1)  // 
#define PFD2						(V_BYTE)(Output<<Bit2)  // 
#define PFD3						(V_BYTE)(Output<<Bit3)  // 
#define PFD4						(V_BYTE)(Output<<Bit4)  // PWM     //pwm 사용시 출력으로 설정해야 함.
#define PFD5						(V_BYTE)(Output<<Bit5)  // 
#define PFD6						(V_BYTE)(Output<<Bit6)  // 
#define PFD7						(V_BYTE)(Output<<Bit7)  // 

#define PGD0						(V_BYTE)(Output<<Bit0)	//
#define PGD1						(V_BYTE)(Output<<Bit1)	//
#define PGD2						(V_BYTE)(Output<<Bit2)	//
#define PGD3						(V_BYTE)(Output<<Bit3)  //
#define PGD4						(V_BYTE)(Output<<Bit4)  //

//==========================================================================//
//**************             Atmega128 PORT 초기 상태 설정 *****************//
//==========================================================================//
#define PAP0						(V_BYTE)(LOW<<Bit0)  //
#define PAP1						(V_BYTE)(LOW<<Bit1)  // 
#define PAP2						(V_BYTE)(LOW<<Bit2)  // 
#define PAP3						(V_BYTE)(LOW<<Bit3)  // 
#define PAP4						(V_BYTE)(LOW<<Bit4)  // 
#define PAP5						(V_BYTE)(LOW<<Bit5)  // 
#define PAP6						(V_BYTE)(LOW<<Bit6)  // 
#define PAP7						(V_BYTE)(LOW<<Bit7)  // 

#define PBP0						(V_BYTE)(LOW<<Bit0)	// 
#define PBP1						(V_BYTE)(LOW<<Bit1)	// 
#define PBP2						(V_BYTE)(LOW<<Bit2)	// 
#define PBP3						(V_BYTE)(LOW<<Bit3)	// 
#define PBP4						(V_BYTE)(LOW<<Bit4)	// 
#define PBP5						(V_BYTE)(LOW<<Bit5)	// 
#define PBP6						(V_BYTE)(LOW<<Bit6)	// 
#define PBP7						(V_BYTE)(LOW<<Bit7)	// 

#define PCP0						(V_BYTE)(HIGH<<Bit0)  // LED1
#define PCP1						(V_BYTE)(HIGH<<Bit1)  // LED2
#define PCP2						(V_BYTE)(HIGH<<Bit2)  // 
#define PCP3						(V_BYTE)(HIGH<<Bit3)  // 
#define PCP4						(V_BYTE)(LOW<<Bit4)  // 
#define PCP5						(V_BYTE)(LOW<<Bit5)  // 
#define PCP6						(V_BYTE)(LOW<<Bit6)  // 
#define PCP7						(V_BYTE)(LOW<<Bit7)  // 

#define PDP0						(V_BYTE)(HIGH<<Bit0)  // SCL
#define PDP1						(V_BYTE)(HIGH<<Bit1)  // SDA
#define PDP2						(V_BYTE)(HIGH<<Bit2)  // RXD
#define PDP3						(V_BYTE)(HIGH<<Bit3)  // TXD
#define PDP4						(V_BYTE)(HIGH<<Bit4)   // 
#define PDP5						(V_BYTE)(HIGH<<Bit5)  // 
#define PDP6						(V_BYTE)(HIGH<<Bit6)  // 
#define PDP7						(V_BYTE)(HIGH<<Bit7)  // 

#define PEP0						(V_BYTE)(LOW<<Bit0)	  // 
#define PEP1						(V_BYTE)(LOW<<Bit1)   // 
#define PEP2						(V_BYTE)(LOW<<Bit2)   // 
#define PEP3						(V_BYTE)(LOW<<Bit3)   // 
#define PEP4						(V_BYTE)(HIGH<<Bit4)  // PWM
#define PEP5						(V_BYTE)(LOW<<Bit5)   // 
#define PEP6						(V_BYTE)(LOW<<Bit6)   // 
#define PEP7						(V_BYTE)(LOW<<Bit7)   // 

#define PFP0						(V_BYTE)(LOW<<Bit0)  //
#define PFP1						(V_BYTE)(LOW<<Bit1)  //
#define PFP2						(V_BYTE)(LOW<<Bit2)  //
#define PFP3						(V_BYTE)(LOW<<Bit3)  //
#define PFP4						(V_BYTE)(LOW<<Bit4)  // 
#define PFP5						(V_BYTE)(LOW<<Bit5)  // 
#define PFP6						(V_BYTE)(LOW<<Bit6)  // 
#define PFP7						(V_BYTE)(LOW<<Bit7)  // 

#define PGP0						(V_BYTE)(LOW<<Bit0)	//
#define PGP1						(V_BYTE)(LOW<<Bit1)	//
#define PGP2						(V_BYTE)(LOW<<Bit2)	// 
#define PGP3						(V_BYTE)(LOW<<Bit3)  //
#define PGP4						(V_BYTE)(LOW<<Bit4)  //


//=========================================================================//
//**************             PORT Define             **********************//
//=========================================================================//


#define LED_1                       PORTC_Bit0
#define LED_2                       PORTC_Bit1


////////////////////////////////////////////////////////////



#endif

