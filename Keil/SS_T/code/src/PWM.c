#include"pwm.h"


uint16_t DutyC;
//--------------------------------------------------------------------------------------//
//							Initializare PWM principal -> TIM1:CH1						//
//--------------------------------------------------------------------------------------//
void PWM_INIT(){
	//Tactarea TIM1 si portului GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_TIM1EN;	
	//Iinitializarea pinului PA8 ca Alternate function output push-pull
	GPIOA->CRH &= 0x11111110;
	GPIOA->CRH |= GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0 | GPIO_CRH_CNF8_1; //| GPIO_CRH_CNF8_0;
	//Initializarea TIM1 
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; 
	TIM1->CCER |= TIM_CCER_CC1E;// | TIM_CCER_CC1P; 
	TIM1->ARR = PWMPeriod;
//	TIM1->CCR1 = 100;
	
//	TIM1->DIER |= TIM_DIER_UIE;
//	NVIC_EnableIRQ(TIM1_UP_IRQn);
//	NVIC_SetPriority(TIM1_UP_IRQn, 1);
}

void updPwmVal(uint16_t pwmVal)
{
	if(pwmVal >= MaxDC)
		pwmVal = MaxDC;
	
	if(pwmVal <= MinDC)
		pwmVal = MinDC;
	
	TIM1->CCR1 = pwmVal;
}
//---------------------------------------------------------------------------------------//
//					Initializare tiemer pentru prelucrarea encoderului					 //
//---------------------------------------------------------------------------------------//
void Enc_INIT(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~GPIO_CRL_MODE0; 
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	GPIOA->CRL &= ~GPIO_CRL_MODE1; 
	GPIOA->CRL &= ~GPIO_CRL_CNF1;
	GPIOA->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1;
	GPIOA->BSRR |= GPIO_BSRR_BR0 | GPIO_BSRR_BR1;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;
	TIM2->CCER |= TIM_CCER_CC1P;// | TIM_CCER_CC2P;
	TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	
	TIM2->SMCR |= TIM_SMCR_ETF_0 | TIM_SMCR_ETF_3;
	
	TIM2->SMCR |= TIM_SMCR_ETPS_1;

	TIM2->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM2->ARR = 10000;
	TIM2->CNT = 800;
	TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	
	if(TIM2->CR1 & TIM_CR1_DIR)
		TIM2->CNT = 0;
	else
		TIM2->CNT = TIM2->ARR;	
}

void setEncoder(uint16_t initVal, uint16_t reloadVal, uint8_t divByFour)
{
	if(divByFour)
	{	
		TIM2->ARR = reloadVal * 4;
		TIM2->CNT = initVal * 4;
	}
	else
	{
		TIM2->ARR = reloadVal;
		TIM2->CNT = initVal;
	}
	
}

uint16_t readEncoder(uint8_t divByFour)
{
	if(divByFour)
		return TIM2->CNT / 4;
	else
		return TIM2->CNT;
}
//---------------------------------------------------------------------------------------//
//		Initializare TIM3 crearea intervalelor necesare la citirea temperaturii	    	 //
//---------------------------------------------------------------------------------------//
void TIM3_INIT(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
	TIM3->DIER |= TIM_DIER_UIE | TIM_DIER_CC1IE;
	TIM3->PSC = 7200;
	TIM3->ARR = 100;
	TIM3->CCR1 = 10;

	NVIC_EnableIRQ(TIM3_IRQn);
}



