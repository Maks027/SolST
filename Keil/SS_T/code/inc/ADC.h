#ifndef _ADC_H_
#define _ADC_H_

#include<stm32f10x.h>
#include<stm32f10x_rcc.h>
#include<ssd1306.h>
#include"pwm.h"
#include"pid.h"
#include"delay.h"


void ADC_INIT(void);
void PID_INIT(void);
extern int tmpVal;




#endif
