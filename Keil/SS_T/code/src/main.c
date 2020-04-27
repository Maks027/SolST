#include"main.h"

int main(){
	SSD1306_Init();
	ShowStartScreen();
	__enable_irq();
	SystemInit();
	
	readFlashParameters();
	
	DelayInit();
	ADC_INIT();
	PWM_INIT();
//	PID_INIT();
	BUT_INIT();

	Enc_INIT();
	TIM3_INIT();
	setParamString();
	
//	pidInit(1);
	
//	setEncoder(1, 100, DIV_BY_4);
	
	while(1){
		
		showScreen();


	}
}	



