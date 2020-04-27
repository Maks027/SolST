#include"gui.h"

#define PWM_ON()			(TIM1->BDTR |= TIM_BDTR_MOE);
#define PWM_OFF()			(TIM1->BDTR &= ~TIM_BDTR_MOE);

#define SET_TMP_SHOW_T		1200//ms

#define BUT_LONG_PRESS		1200
#define BUT_DEBOUNCE		100

char buffer[20];
char bM[] = "M";
char bS[] = "S";

typedef struct par{
	char p1[16];
	uint16_t p1_val;
	uint8_t p1_ch;
	char p2[16];
	uint16_t p2_val;
	uint8_t p2_ch;
	char p3[16];
	uint16_t p3_val;
	uint8_t p3_ch;
	char p4[16];
	uint16_t p4_val;
	uint8_t p4_ch;
	char p5[16];
	uint16_t p5_val;
	uint8_t p5_ch;
	char p6[16];
	uint16_t p6_val;
	uint8_t p6_ch;
	char p7[16];
	uint16_t p7_val;
	uint8_t p7_ch;
	char p8[16];
	uint16_t p8_val;
	uint8_t p8_ch;
	char p9[16];
	uint16_t p9_val;
	uint8_t p9_ch;
	char p10[16];
	uint16_t p10_val;
	uint8_t p10_ch;
	
	uint8_t totalParNr;
	uint8_t parCnt;
	uint8_t lastParCnt;
	uint8_t parSelect;
	uint8_t firstPar;
	uint8_t secPar;
} param_list;

param_list mainMenuParam;
param_list pidMenuParam;

typedef enum{
	p1,
	p2,
	p3,
	p4,
	p5,
	p6,
	p7,
	p8,
	p9,
	p10
}param_enum;

void setParamString()
{
	mainMenuParam.p1_ch = sprintf(mainMenuParam.p1, "PID Config");
	mainMenuParam.p2_ch = sprintf(mainMenuParam.p2, "Limits Config");
	mainMenuParam.p3_ch = sprintf(mainMenuParam.p3, "Standby Config");
	mainMenuParam.p4_ch = sprintf(mainMenuParam.p4, "Temperature Cal.");
	mainMenuParam.p5_ch = sprintf(mainMenuParam.p5, "Voltage Cal.");
	mainMenuParam.p6_ch = sprintf(mainMenuParam.p6, "Current Cal.");
	mainMenuParam.p7_ch = sprintf(mainMenuParam.p7, "Exit Menu");
	
	mainMenuParam.totalParNr = 7;
	mainMenuParam.parCnt = 0;
	mainMenuParam.lastParCnt = 0;
	mainMenuParam.firstPar = 0;
	mainMenuParam.secPar = 1;
	mainMenuParam.parSelect = SELECTED;
	setEncoder(0 , 0xFFFF, DIV_BY_4);
	
	pidMenuParam.p6_ch = sprintf(pidMenuParam.p6, "Save");
	pidMenuParam.p7_ch = sprintf(pidMenuParam.p7, "Back");
	pidMenuParam.totalParNr = 7;
	pidMenuParam.parCnt = 0;
	pidMenuParam.lastParCnt = 0;
	pidMenuParam.firstPar = 0;
	pidMenuParam.secPar = 1;
	pidMenuParam.parSelect = SELECTED;
}

void updatePidMenuStruct()
{
	pidMenuParam.p1_ch = sprintf(pidMenuParam.p1, "Kp=%5d", flashParameters.Kp);
	pidMenuParam.p2_ch = sprintf(pidMenuParam.p2, "Ki=%5d", flashParameters.Ki);
	pidMenuParam.p3_ch = sprintf(pidMenuParam.p3, "Kd=%5d", flashParameters.Kd);
	pidMenuParam.p4_ch = sprintf(pidMenuParam.p4, "Sc=%5d", flashParameters.outScale);
	pidMenuParam.p5_ch = sprintf(pidMenuParam.p5, "Im=%5d", flashParameters.maxInt);
}

typedef enum{
	up_left,
	down_left,
	up_right,
	down_right,
	left_side,
	right_side
}position;



void displayParameter(param_list* par, param_enum p, position pos, uint8_t select)
{	
	uint8_t strLength, currentX, currentY;
	
	switch(pos)
	{
		case up_left:
		{
			currentX = LEFT_PARAMETER_X;
			currentY = FIRST_PARAMETER_Y;
			break;
		}
		case down_left:
		{
			currentX = LEFT_PARAMETER_X;
			currentY = SECOND_PARAMETER_Y;
			break;
		}
		case up_right:
		{
			currentX = RIGHT_PARAMETER_X;
			currentY = FIRST_PARAMETER_Y;
			break;
		}
		case down_right:
		{
			currentX = RIGHT_PARAMETER_X;
			currentY = SECOND_PARAMETER_Y;
			break;
		}
		default: break;
	}
	
	SSD1306_GotoXY(currentX, currentY);
	
	switch(p)
	{
		case p1:{
			SSD1306_Puts(par->p1, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p1_ch;
			break;
		}
		case p2:{
			SSD1306_Puts(par->p2, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p2_ch;
			break;
		}
		case p3:{
			SSD1306_Puts(par->p3, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p3_ch;
			break;
		}
		case p4:{
			SSD1306_Puts(par->p4, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p4_ch;
			break;
		}
		case p5:{
			SSD1306_Puts(par->p5, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p5_ch;
			break;
		}
		case p6:{
			SSD1306_Puts(par->p6, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p6_ch;
			break;
		}
		case p7:{
			SSD1306_Puts(par->p7, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p7_ch;
			break;
		}
		case p8:{
			SSD1306_Puts(par->p8, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p8_ch;
			break;
		}
		case p9:{
			SSD1306_Puts(par->p9, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p9_ch;
			break;
		}
		case p10:{
			SSD1306_Puts(par->p10, &Font_7x10, SSD1306_COLOR_WHITE);
			strLength = par->p10_ch;
			break;
		}
		
		default: break;
	}

	if(select)
	{
		SSD1306_DrawRectangle(currentX - 2, currentY - 2, strLength*FONT_7x10_LENGHT + 3, FONT_7x10_HIGHT + 3, SSD1306_COLOR_WHITE);
	}
}


typedef enum{
	noPress = 0,
	shortPress = 1,
	longPress = 2
}butPress;

typedef enum{
	measMode,
	setMode
}showModes;

typedef enum{
	FIRST_PARAM,
	pidConfig,
	tmpLimConfig,
	standbyConfig,
	tmpCalibration,
	voltageCalibration,
	currentCalibration,
	returnToMain,
	LAST_PARAM
}menuParameter;

typedef enum{
	pidKp,
	pidKi,
	pidKd,
	pidOutScale,
	pidMaxInt,
	pidSave,
	pidBack
}pidParam;

typedef enum{
	
	FIRST_MODE,
	mainScreen,
	menuScreen,
	standbyScreen,
	offScreen,
	LAST_MODE
}screenModes;



menuParameter currentMode;
screenModes currentScreenMode;

void BUT_INIT()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= 0x100;
	GPIOA->CRL |= GPIO_CRL_CNF2_1;
	GPIOA->BSRR |= GPIO_BSRR_BS2;
}

butPress encButHandler(uint32_t* lastMs, uint8_t* butPressFlag)
{
	static uint8_t lastState = 0;
	
	if(ENC_BUT_PRESSED)
	{
		if(*butPressFlag == RESET)
		{
			*lastMs = msCnt;
			*butPressFlag = SET;
		}
		
		if((msCnt - *lastMs) >= BUT_LONG_PRESS)
		{
//			*butPressFlag = RESET;
			return longPress;
		}	
	}
	
	if(ENC_BUT_RELEASED)
	{
		if(*butPressFlag == SET)
		{
			if((msCnt - *lastMs) >= BUT_DEBOUNCE)
			{
				*butPressFlag = RESET;
				return shortPress;
			}	
		}
		
		return noPress;
	}
	
	return 4;
}

void ShowStartScreen()
{
	SSD1306_GotoXY(36, 0);
	sprintf(buffer, "START");
	SSD1306_Puts(buffer, &Font_11x18, SSD1306_COLOR_WHITE);
	
	SSD1306_UpdateScreen();	
	for(uint8_t i = 0 ; i < 17 ; i++){
		SSD1306_DrawFilledRectangle(i * 4, 20, 2, 11, SSD1306_COLOR_WHITE);
		
		SSD1306_DrawFilledRectangle(129-i * 4, 20, 2, 11, SSD1306_COLOR_WHITE);
		SSD1306_UpdateScreen();
		
	}
	for(uint16_t i = 1 ; i < 10 ; i++){
		SSD1306_UpdateScreen();
	}
	SSD1306_Fill(SSD1306_COLOR_BLACK);
}


int16_t filter(int16_t readVal ,uint16_t N, uint16_t k)
{
	static int sum = 0, avg = 0, rm = 0, lastVal = 30;
	
	sum = lastVal * k + avg * (N - k) + rm;
	
	avg = sum / N;
	rm = sum - avg * N;
	

	lastVal = readVal;
	
	return (int16_t)avg;
}

void showTemp(showModes mode)
{
	if(mode == measMode)
	{
		SSD1306_DrawRectangle(1, 1, 60, 22, SSD1306_COLOR_WHITE);
		SSD1306_DrawRectangle(0, 0, 62, 24, SSD1306_COLOR_WHITE);
		sprintf(buffer, "%3d C", filter(tmpVal ,50, 1));
		SSD1306_GotoXY(3,4);
		SSD1306_Puts(buffer, &Font_11x18, SSD1306_COLOR_WHITE);
		SSD1306_GotoXY(38, 16);
		SSD1306_Puts(bM, &Font_7x10, SSD1306_COLOR_WHITE);
	}
	else if(mode == setMode)
	{
		SSD1306_DrawRectangle(1, 1, 60, 22, SSD1306_COLOR_WHITE);
		SSD1306_DrawRectangle(0, 0, 62, 24, SSD1306_COLOR_BLACK);
		
		if(flashParameters.tmpSet <= MAX_TMP_SET)
			if(flashParameters.tmpSet >= MIN_TMP_SET)
				sprintf(buffer, "%3d C", flashParameters.tmpSet);
			else
			{
				sprintf(buffer, "MIN");
				setEncoder(flashParameters.tmpSet + 1, 0xFFFF, DIV_BY_4);
				
			}
		else
		{
			sprintf(buffer, "MAX");
			setEncoder(flashParameters.tmpSet - 1, 0xFFFF, DIV_BY_4);
		}
		
		
		SSD1306_GotoXY(3,4);
		SSD1306_Puts(buffer, &Font_11x18, SSD1306_COLOR_WHITE);
		SSD1306_GotoXY(38, 16);
		SSD1306_Puts(bS, &Font_7x10, SSD1306_COLOR_WHITE);
	}
	
	SSD1306_DrawCircle(43, 5, 2, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
}


void displayMainScreen(void)
{
	static uint16_t lastSetTmp = 0;
	static uint32_t lastMs = 0;
	static uint8_t tmpChangeFlag = RESET, initFlag = SET;
	
	if(initFlag == SET)
	{
		setEncoder(flashParameters.tmpSet, 0xFFFF, DIV_BY_4);
		initFlag = RESET;
	}
	else
		flashParameters.tmpSet = readEncoder(DIV_BY_4);
	
	if(lastSetTmp != flashParameters.tmpSet)
	{
		tmpChangeFlag = SET;
		lastSetTmp = flashParameters.tmpSet;
		lastMs = msCnt;
	}

	if((msCnt - lastMs) >= SET_TMP_SHOW_T)
	{
		showTemp(measMode);
		if(tmpChangeFlag == SET)
		{
			tmpChangeFlag = RESET;
			writeParametersToFlash();
		}
	}
	else
		showTemp(setMode);
}




void displayMenu(param_list* par, position side, uint8_t scroll_en)
{	
	if(scroll_en)
		par->parCnt = readEncoder(DIV_BY_4);

	if(par->parCnt > par->totalParNr - 1)
	{
		par->parCnt = par->totalParNr - 1;
		setEncoder(par->parCnt , 0xFFFF, DIV_BY_4);
	}
	
	if(par->parCnt != par->lastParCnt)
	{
		if(side == left_side)
			SSD1306_DrawFilledRectangle(0, 0, 63, 31, SSD1306_COLOR_BLACK);
		if(side == right_side)
			SSD1306_DrawFilledRectangle(64, 0, 127, 31, SSD1306_COLOR_BLACK);
	}
	
	if(par->parCnt > par->lastParCnt)  
	{
		if(par->parSelect == SELECTED)
			par->parSelect = DESELECTED;
		
		par->firstPar = par->parCnt - 1;
		par->secPar = par->parCnt;
	}
	else if(par->parCnt < par->lastParCnt)
	{
		if(par->parSelect == DESELECTED)
			par->parSelect = SELECTED;
		
		par->firstPar = par->parCnt;
		
		par->secPar = par->parCnt + 1;
	}
	

	if(side == left_side)
	{
		displayParameter(par, par->firstPar, up_left, par->parSelect);
	
		if(par->secPar < par->totalParNr)
			displayParameter(par, par->secPar, down_left, !par->parSelect);
		
	}
	else if(side == right_side)
	{
		displayParameter(par, par->firstPar, up_right, par->parSelect);
	
		if(par->secPar < par->totalParNr)
			displayParameter(par, par->secPar, down_right, !par->parSelect);
	}
	
	SSD1306_UpdateScreen();
	
	par->lastParCnt = par->parCnt;
}
	

void showSubMenuPid(void)
{
	static uint8_t modFlag = 0, initFlag = 1;
	
	static uint32_t last_ms = 0;
	static uint8_t pressFlag = 0;
	
	if(encButHandler(&last_ms, &pressFlag) == shortPress)
	{
		modFlag ^= 1;
		initFlag = 1;
	}
	
	updatePidMenuStruct();	
	
	showTemp(measMode);
	
	if(modFlag)
	{
		displayMenu(&pidMenuParam, right_side, 0);
		
		switch(pidMenuParam.parCnt)
		{
			case pidKp:
			{
				if(initFlag)
				{
					setEncoder(flashParameters.Kp, 0xFFFF, DIV_BY_4);
					initFlag = 0;
				}
				else
					flashParameters.Kp = readEncoder(DIV_BY_4);
				break;
			}
			case pidKi:
			{
				if(initFlag)
				{
					setEncoder(flashParameters.Ki , 0xFFFF, DIV_BY_4);
					initFlag = 0;
				}
				else
					flashParameters.Ki = readEncoder(DIV_BY_4);
				break;
			}
			
			case pidKd:
			{
				if(initFlag)
				{
					setEncoder(flashParameters.Kd, 0xFFFF, DIV_BY_4);
					initFlag = 0;
				}
				else
					flashParameters.Kd = readEncoder(DIV_BY_4);
				break;
			}
			
			case pidOutScale:
			{
				if(initFlag)
				{
					setEncoder(flashParameters.outScale, 0xFFFF, DIV_BY_4);
					initFlag = 0;
				}
				else
					flashParameters.outScale = readEncoder(DIV_BY_4);
				break;
			}
			case pidMaxInt:
			{
				if(initFlag)
				{
					setEncoder(flashParameters.maxInt / 10, 0xFFFF, DIV_BY_4);
					initFlag = 0;
				}
				else
					flashParameters.maxInt = readEncoder(DIV_BY_4) * 10;
				break;
			}
			
			case pidSave:
			{
				if(initFlag)
				{
					writeParametersToFlash();
					initFlag = 0;
					modFlag = 0;
				}
				
				break;
			}
			
			default:break;
		}
	}
	else
	{
		
		if(initFlag)
		{
			setEncoder(pidMenuParam.parCnt, 0xFFFF, DIV_BY_4);
			//pidInit(1);
			initFlag = 0;
		}
		
		displayMenu(&pidMenuParam, right_side, 1);
		
	}
	
	
}





void showScreen(void)
{
	
	static screenModes currentScreenMode = mainScreen;
//	static uint32_t lastMs = 0; 
//	static uint8_t butPressFlag = 0;
	
	switch(currentScreenMode)
	{
		case mainScreen:{
			displayMainScreen();
			//showSubMenuPid();
			//displayMenu(&mainMenuParam);
			break;
		}
		case menuScreen:{
			//displayMainMenu();
			break;
		}
		case standbyScreen:{
			
			break;
		}
		case offScreen:{
			
			break;
		}
		case LAST_MODE:{
			
			break;
		}
		
		case FIRST_MODE:{
			
			break;
		}
	}
	
}

