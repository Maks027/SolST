/**
  ******************************************************************************
  * @file		delay.c
  * @author	Yohanes Erwin Setiawan
  * @date		10 January 2016
  ******************************************************************************
  */
	
#include "delay.h"

// For store tick counts in us
static __IO uint32_t msTicks;

volatile uint32_t msCnt = 0;

// SysTick_Handler function will be called every 1 us
void SysTick_Handler()
{
	if (msTicks != 0)
	{
		msTicks--;
	}
	msCnt++;
}
void DelayInit()
{
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config(SystemCoreClock / 1000);
}

void DelayMs(uint32_t ms)
{
	// Reload us value
	msTicks = ms;
	// Wait until usTick reach zero
	while (msTicks);
}

