#ifndef AVR_PWM_H
#define AVR_PWM_H

extern unsigned int OCR3A_VAL;
extern unsigned int OCR3B_VAL;
extern unsigned int DUTY_VAL;

void Timer3_pwm_initial(void);
void pwm_dimming_fun(void);

#endif