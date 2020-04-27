#include"adc.h"


#define START_ADC()		(ADC1->CR2 |= ADC_CR2_SWSTART)

int16_t dutyCycle;



int tmpVal, adcVal;// filteredAdcVal;


void ADC_INIT(void)
{
	RCC->APB2ENR |= RCC_APB2Periph_ADC1;
	RCC->CFGR |= RCC_CFGR_ADCPRE_1;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= 0xFF0FFFFF; //PA5 - analog input
	ADC1->SQR3 |= ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_2;
	ADC1->CR1 |= ADC_CR1_EOCIE;
	ADC1->CR2 = ADC_CR2_EXTSEL_0 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTTRIG;
	ADC1->CR2 |= ADC_CR2_ADON;
	
	
	
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while ((ADC1->CR2 & ADC_CR2_RSTCAL) == ADC_CR2_RSTCAL);

	ADC1->CR2 |= ADC_CR2_CAL;
	while ((ADC1->CR2 & ADC_CR2_RSTCAL) == ADC_CR2_CAL);
	
	NVIC_EnableIRQ(ADC1_2_IRQn);
	NVIC_SetPriority(ADC1_2_IRQn, 1);
}



//int16_t filter(int16_t readVal ,uint16_t N, uint16_t k)
//{
//	static int sum = 0, avg = 0, rm = 0, lastVal = 30;
//	
//	sum = lastVal * k + avg * (N - k) + rm;
//	
//	avg = sum / N;
//	rm = sum - avg * N;
//	

//	lastVal = readVal;
//	
//	return (int16_t)avg;
//}

void ADC1_2_IRQHandler()
{
	ADC1->SR &= ~ADC_SR_EOC;
	
	adcVal = ADC1->DR;//filter(ADC1->DR, 20, 1);
//	filteredAdcVal = filter(adcVal, 20, 1);
	PWM_ON();
}




//Functia de prelucrare a itreruperilor TIM3 pentru efectuarea masurarii temperaturii
void TIM3_IRQHandler(){
	if(!(TIM3->SR & TIM_SR_CC1IF)){
		PWM_OFF();
	}
	if(!(TIM3->SR & TIM_SR_UIF)){
		
		START_ADC();
		
		if(adcVal <= 300)
			tmpVal = (242 * adcVal + 7557) / 1000;
		else if(adcVal < 900)
			tmpVal = (163 * adcVal + 29328) / 1000;
		else if(adcVal >= 900)
			tmpVal = (133 * adcVal + 58300) / 1000;
		
		
		
		updPwmVal(pidCalc(flashParameters.tmpSet, tmpVal));

	}
	TIM3->SR &= TIM_SR_CC1IF;
	TIM3->SR &= TIM_SR_UIF;
}
