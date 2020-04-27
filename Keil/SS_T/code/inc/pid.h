#ifndef _PID_H_
#define _PID_H_

#define ARM_MATH_CM3
#include<stm32f10x.h>

#include<arm_math.h>
#include"pwm.h"
#include"adc.h"
#include"FLASH.h"

//void ApplyPID(void);
uint16_t pidCalc(int setPoint, int processVal);
//void PID_INIT(void);

void pidInit(uint8_t reset);

#endif
