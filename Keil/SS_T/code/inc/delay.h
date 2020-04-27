/**
  ******************************************************************************
  * @file		delay.h
  * @author	Yohanes Erwin Setiawan
  * @date		10 January 2016
  ******************************************************************************
  */
	
#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

void DelayInit(void);

void DelayMs(uint32_t ms);

extern uint32_t TmpReadTimer;

extern volatile uint32_t msCnt;
#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
