#ifndef _GUI_H_
#define _GUI_H_

#include"ssd1306.h"
#include"adc.h"
#include<stdio.h>
#include"FLASH.h"

#define OLED_LENGHT			128
#define OLED_HIGHT			32
#define FONT_11x18_LENGHT	11
#define FONT_11x18_HIGHT	18

#define FONT_7x10_LENGHT	7
#define FONT_7x10_HIGHT		10

#define MENU_POS_UP			0
#define MENU_POS_DOWN		1

#define SET					1
#define RESET				0

#define SELECTED			1
#define DESELECTED			0

#define LEFT_PARAMETER_X	5
#define RIGHT_PARAMETER_X	66

#define FIRST_PARAMETER_Y		2
#define SECOND_PARAMETER_Y		(FIRST_PARAMETER_Y + FONT_7x10_HIGHT + 3)

#define row1	0
#define row2	1
#define ENC_BUT_PRESSED		!(GPIOA->IDR & GPIO_IDR_IDR2)
#define ENC_BUT_RELEASED	(GPIOA->IDR & GPIO_IDR_IDR2)

#define MAX_TMP_SET	400
#define MIN_TMP_SET 20

#define Uk		0.008571
#define Ik		0.000805
#define Tk		0.2415



void BUT_INIT(void);
void showScreen(void);
void GetEncoderData(void);

void ShowStartScreen(void);

void setParamString(void);

#endif
