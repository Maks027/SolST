#ifndef _FLASH_H_
#define _FLASH_H_

#include "stm32f10x.h"
#include "main.h"

#define START_ADR				0x0800F800
#define LEN_PARAM				2

typedef enum
{
	//PID controller parameters
	ADR_KP 			= 	START_ADR,							//Kp
	ADR_KI			= 	ADR_KP 			+ 	LEN_PARAM,		//Ki
	ADR_KD 			= 	ADR_KI 			+ 	LEN_PARAM,		//Kd
	ADR_MAX_INT 	= 	ADR_KD 			+ 	LEN_PARAM,		//Maximum intergrator value(+/-)
	ADR_SMP_FREQ	=	ADR_MAX_INT 	+	LEN_PARAM,		//Sample frequency 
	ADR_OUT_SCALE	= 	ADR_SMP_FREQ 	+	LEN_PARAM,		//Output scaling factor
	//Maximum and minimum temperature
	ADR_MAX_TMP_LIM =	ADR_OUT_SCALE 	+ 	LEN_PARAM, 		//Maximum settable temperature
	ADR_MIN_TMP_LIM = 	ADR_MAX_TMP_LIM + 	LEN_PARAM,		//Minimum settable temperature
	//Automatic standby mode parameters
	ADR_SBY_START_T	=	ADR_MIN_TMP_LIM +	LEN_PARAM, 		//Inactivity time before entering standby mode
	ADR_SBY_STEP_T	=	ADR_SBY_START_T +	LEN_PARAM,		//Time step of decreasing temperature after entering sleep mode
	ADR_SBY_TMP_STEP=	ADR_SBY_STEP_T	+	LEN_PARAM,		//Decreasing temperature step
	ADR_SBY_PWR_DEV	=	ADR_SBY_TMP_STEP+	LEN_PARAM,		//Power deviation that prevents entering standby mode
	ADR_SBY_PWR_WKP	=	ADR_SBY_PWR_DEV + 	LEN_PARAM,		//Power deviation to wakeup after entering standby mode
	//Temperature calibration
	ADR_TMP_CAL_NUM	=	ADR_SBY_PWR_WKP + 	LEN_PARAM,		//ADC to temperature conversion factor(numerator)
	ADR_TMP_CAL_DEN	=	ADR_TMP_CAL_NUM + 	LEN_PARAM,		//ADC to temperature conversion factor(denominator)
	//Voltage calibration
	ADR_V_CAL_NUM	=	ADR_TMP_CAL_DEN + 	LEN_PARAM,		//ADC to volts conversion factor(numerator)
	ADR_V_CAL_DEN	=	ADR_V_CAL_NUM	+	LEN_PARAM,		//ADC to volts conversion factor(denominator)
	//Current calibration
	ADR_I_CAL_NUM	=	ADR_V_CAL_DEN	+	LEN_PARAM,		//ADC to amperes conversion factor(numerator)
	ADR_I_CAL_DEN	=	ADR_I_CAL_NUM	+	LEN_PARAM,		//ADC to amperes conversion factor(denominator)
	
	ADR_TMP_SET		=	ADR_I_CAL_DEN	+	LEN_PARAM
	
}addresses;

typedef struct
{
	//PID controller parameters
	uint16_t Kp;
	uint16_t Ki;
	uint16_t Kd;
	uint16_t maxInt;
	uint16_t smpFreq;
	uint16_t outScale;
	//Maximum and minimum temperature
	uint16_t maxSetTmp;
	uint16_t minSetTmp;
	//Automatic standby mode parameters
	uint16_t sbyStartTime;
	uint16_t sbyStepTime;
	uint16_t sbyStepTmp;
	uint16_t sbyPwrDev;
	uint16_t sbyPwrWkp;
	//Temperature calibration
	uint16_t tmpCalNum;
	uint16_t tmpCalDen;
	//Voltage calibration
	uint16_t voltCalNum;
	uint16_t voltCalDen;
	//Current calibration
	uint16_t currentCalNum;
	uint16_t currentCalDen;
	
	uint16_t tmpSet;
	
} flashParametersType;
	
extern flashParametersType flashParameters;
void rewriteFlashPage(uint32_t Adr, uint16_t data);
void readFlashParameters(void);
void writeParametersToFlash(void);

#endif

