#ifndef _PWM_H_
#define _PWM_H_

#include<stm32f10x_rcc.h>
#include<stm32f10x_gpio.h>

#define PWMPeriod		3600	//20kHz
#define MaxDC			3600	
#define MinDC			0		

#define PWM_ON()	(TIM1->BDTR |= TIM_BDTR_MOE);
#define PWM_OFF()	(TIM1->BDTR &= ~TIM_BDTR_MOE);

#define EncData		(TIM2->CNT)

#define DIV_BY_4	1
#define NO_DIV		0

void Enc_INIT(void);
void PWM_INIT(void);
void TIM3_INIT(void);
void updPwmVal(uint16_t pwmVal);

void setEncoder(uint16_t initVal, uint16_t reloadVal, uint8_t divByFour);
uint16_t readEncoder(uint8_t divByFour);

extern uint16_t DutyC;

#endif
