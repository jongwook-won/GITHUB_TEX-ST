#ifndef MAIN_H
#define MAIN_H

extern unsigned char PC_pwm_H, PC_pwm_L,PC_pwm_flag,eeprom_pwm_H,eeprom_pwm_L;
extern unsigned short pc_duty_100;
extern unsigned short chk_PWMTimer;

void init_mcu(void);
void check_comm(void);
void analyze_packet(void);
void EEPROM_Write(unsigned short address , unsigned char Data);
unsigned char EEPROM_Read(unsigned short address);
void eeprom_write_chk(void);
void chk_pwm_data(void);
void start_pwm(void);
void fs_i2c_dimming_fun(void);


#endif