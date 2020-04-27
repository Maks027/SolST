#include"FLASH.h"

flashParametersType flashParameters;

uint16_t readFlashData (uint32_t Adress)
{
	return*(uint16_t *) Adress;
}

void rewriteFlashPage(uint32_t Adr, uint16_t data)
{
	uint16_t Kp_temp, Ki_temp, Kd_temp, maxInt_temp, smpFreq_temp, outScale_temp, maxSetTmp_temp, minSetTmp_temp, sbyStartTime_temp, 
			 sbyStepTime_temp, sbyStepTmp_temp, sbyPwrDev_temp, sbyPwrWkp_temp, tmpCalNum_temp, tmpCalDen_temp, voltCalNum_temp, 
			 voltCalDen_temp, currentCalNum_temp, currentCalDen_temp, tmpSet_temp;
	
	Kp_temp 			= 	readFlashData(ADR_KP);
	Ki_temp 			= 	readFlashData(ADR_KI);
	Kd_temp 			= 	readFlashData(ADR_KD);
	maxInt_temp 		= 	readFlashData(ADR_MAX_INT);
	smpFreq_temp 		= 	readFlashData(ADR_SMP_FREQ);
	outScale_temp 		= 	readFlashData(ADR_OUT_SCALE);
	maxSetTmp_temp 		= 	readFlashData(ADR_MAX_TMP_LIM);
	minSetTmp_temp 		= 	readFlashData(ADR_MIN_TMP_LIM);
	sbyStartTime_temp 	= 	readFlashData(ADR_SBY_START_T);	
	sbyStepTime_temp 	= 	readFlashData(ADR_SBY_STEP_T);
	sbyStepTmp_temp 	= 	readFlashData(ADR_SBY_TMP_STEP);
	sbyPwrDev_temp 		= 	readFlashData(ADR_SBY_PWR_DEV);
	sbyPwrWkp_temp 		= 	readFlashData(ADR_SBY_PWR_WKP);
	tmpCalNum_temp 		= 	readFlashData(ADR_TMP_CAL_NUM);
	tmpCalDen_temp 		= 	readFlashData(ADR_TMP_CAL_DEN);
	voltCalNum_temp 	= 	readFlashData(ADR_V_CAL_NUM);
	voltCalDen_temp 	= 	readFlashData(ADR_V_CAL_DEN);
	currentCalNum_temp 	= 	readFlashData(ADR_I_CAL_NUM);
	currentCalDen_temp 	= 	readFlashData(ADR_I_CAL_DEN);
	tmpSet_temp			= 	readFlashData(ADR_TMP_SET);
	
	switch(Adr)
	{
		case ADR_KP: 			Kp_temp 			= data; break;
		case ADR_KI:			Ki_temp				= data; break;
		case ADR_KD:			Kd_temp 			= data; break;
		case ADR_MAX_INT:		maxInt_temp			= data; break;
		case ADR_SMP_FREQ:		smpFreq_temp 		= data; break;
		case ADR_OUT_SCALE:		outScale_temp 		= data; break;
		case ADR_MAX_TMP_LIM:	maxSetTmp_temp 		= data; break;
		case ADR_MIN_TMP_LIM:	minSetTmp_temp 		= data; break;
		case ADR_SBY_START_T:	sbyStartTime_temp 	= data; break;
		case ADR_SBY_STEP_T:	sbyStepTime_temp 	= data; break;
		case ADR_SBY_TMP_STEP:	sbyStepTmp_temp 	= data; break;
		case ADR_SBY_PWR_DEV:	sbyPwrDev_temp 		= data; break;
		case ADR_SBY_PWR_WKP:	sbyPwrWkp_temp 		= data; break;
		case ADR_TMP_CAL_NUM:	tmpCalNum_temp 		= data; break;
		case ADR_TMP_CAL_DEN:	tmpCalDen_temp 		= data; break;
		case ADR_V_CAL_NUM:		voltCalNum_temp 	= data; break;
		case ADR_V_CAL_DEN:		voltCalDen_temp 	= data; break;
		case ADR_I_CAL_NUM:		currentCalNum_temp 	= data; break;
		case ADR_I_CAL_DEN:		currentCalDen_temp 	= data; break;
		case ADR_TMP_SET:		tmpSet_temp 		= data; break;
		default:											break;
	}
	
	FLASH_Unlock();
	FLASH_ErasePage(START_ADR);
	
	FLASH_ProgramHalfWord(ADR_KP, Kp_temp);
	FLASH_ProgramHalfWord(ADR_KI, Ki_temp);
	FLASH_ProgramHalfWord(ADR_KD, Kd_temp);
	FLASH_ProgramHalfWord(ADR_MAX_INT, maxInt_temp);
	FLASH_ProgramHalfWord(ADR_SMP_FREQ, smpFreq_temp);
	FLASH_ProgramHalfWord(ADR_OUT_SCALE, outScale_temp);
	FLASH_ProgramHalfWord(ADR_MAX_TMP_LIM, maxSetTmp_temp);
	FLASH_ProgramHalfWord(ADR_MIN_TMP_LIM, minSetTmp_temp);
	FLASH_ProgramHalfWord(ADR_SBY_START_T, sbyStartTime_temp);
	FLASH_ProgramHalfWord(ADR_SBY_STEP_T, sbyStepTime_temp);
	FLASH_ProgramHalfWord(ADR_SBY_TMP_STEP, sbyStepTmp_temp);
	FLASH_ProgramHalfWord(ADR_SBY_PWR_DEV, sbyPwrDev_temp);
	FLASH_ProgramHalfWord(ADR_SBY_PWR_WKP, sbyPwrWkp_temp);
	FLASH_ProgramHalfWord(ADR_TMP_CAL_NUM, tmpCalNum_temp);
	FLASH_ProgramHalfWord(ADR_TMP_CAL_DEN, tmpCalDen_temp);
	FLASH_ProgramHalfWord(ADR_V_CAL_NUM, voltCalNum_temp);
	FLASH_ProgramHalfWord(ADR_V_CAL_DEN, voltCalDen_temp);
	FLASH_ProgramHalfWord(ADR_I_CAL_NUM, currentCalNum_temp);
	FLASH_ProgramHalfWord(ADR_I_CAL_DEN, currentCalDen_temp);
	FLASH_ProgramHalfWord(ADR_TMP_SET, tmpSet_temp);
	
	FLASH_Lock();
}

void readFlashParameters(void)
{
	flashParameters.Kp 				= 	(uint16_t)readFlashData(ADR_KP);
	flashParameters.Ki 				= 	(uint16_t)readFlashData(ADR_KI); 
	flashParameters.Kd 				= 	(uint16_t)readFlashData(ADR_KD); 
	flashParameters.maxInt 			= 	(uint16_t)readFlashData(ADR_MAX_INT); 
	flashParameters.smpFreq 		= 	(uint16_t)readFlashData(ADR_SMP_FREQ); 
	flashParameters.outScale 		=  	(uint16_t)readFlashData(ADR_OUT_SCALE);
	flashParameters.maxSetTmp 		= 	(uint16_t)readFlashData(ADR_MAX_TMP_LIM); 
	flashParameters.minSetTmp 		= 	(uint16_t)readFlashData(ADR_MIN_TMP_LIM); 
	flashParameters.sbyStartTime 	= 	(uint16_t)readFlashData(ADR_SBY_START_T); 
	flashParameters.sbyStepTime 	= 	(uint16_t)readFlashData(ADR_SBY_STEP_T); 
	flashParameters.sbyStepTmp 		= 	(uint16_t)readFlashData(ADR_SBY_TMP_STEP); 
	flashParameters.sbyPwrDev 		= 	(uint16_t)readFlashData(ADR_SBY_PWR_DEV); 
	flashParameters.sbyPwrWkp 		= 	(uint16_t)readFlashData(ADR_SBY_PWR_WKP); 
	flashParameters.tmpCalNum 		= 	(uint16_t)readFlashData(ADR_TMP_CAL_NUM); 
	flashParameters.tmpCalDen 		= 	(uint16_t)readFlashData(ADR_TMP_CAL_DEN); 
	flashParameters.voltCalNum 		= 	(uint16_t)readFlashData(ADR_V_CAL_NUM); 
	flashParameters.voltCalDen 		= 	(uint16_t)readFlashData(ADR_V_CAL_DEN); 
	flashParameters.currentCalNum 	= 	(uint16_t)readFlashData(ADR_I_CAL_NUM); 
	flashParameters.currentCalDen 	= 	(uint16_t)readFlashData(ADR_I_CAL_DEN); 
	flashParameters.tmpSet			=	(uint16_t)readFlashData(ADR_TMP_SET);
}


void writeParametersToFlash(void){
	FLASH_Unlock();
	FLASH_ErasePage(START_ADR);
	
	FLASH_ProgramHalfWord(ADR_KP, flashParameters.Kp);
	FLASH_ProgramHalfWord(ADR_KI, flashParameters.Ki);
	FLASH_ProgramHalfWord(ADR_KD, flashParameters.Kd);
	FLASH_ProgramHalfWord(ADR_MAX_INT, flashParameters.maxInt);
	FLASH_ProgramHalfWord(ADR_SMP_FREQ, flashParameters.smpFreq);
	FLASH_ProgramHalfWord(ADR_OUT_SCALE, flashParameters.outScale);
	FLASH_ProgramHalfWord(ADR_MAX_TMP_LIM, flashParameters.maxSetTmp);
	FLASH_ProgramHalfWord(ADR_MIN_TMP_LIM, flashParameters.minSetTmp);
	FLASH_ProgramHalfWord(ADR_SBY_START_T, flashParameters.sbyStartTime);
	FLASH_ProgramHalfWord(ADR_SBY_STEP_T, flashParameters.sbyStepTime);
	FLASH_ProgramHalfWord(ADR_SBY_TMP_STEP, flashParameters.sbyStepTmp);
	FLASH_ProgramHalfWord(ADR_SBY_PWR_DEV, flashParameters.sbyPwrDev);
	FLASH_ProgramHalfWord(ADR_SBY_PWR_WKP, flashParameters.sbyPwrWkp);
	FLASH_ProgramHalfWord(ADR_TMP_CAL_NUM, flashParameters.tmpCalNum);
	FLASH_ProgramHalfWord(ADR_TMP_CAL_DEN, flashParameters.tmpCalDen);
	FLASH_ProgramHalfWord(ADR_V_CAL_NUM, flashParameters.voltCalNum);
	FLASH_ProgramHalfWord(ADR_V_CAL_DEN, flashParameters.voltCalDen);
	FLASH_ProgramHalfWord(ADR_I_CAL_NUM, flashParameters.currentCalNum);
	FLASH_ProgramHalfWord(ADR_I_CAL_DEN, flashParameters.currentCalDen);
	FLASH_ProgramHalfWord(ADR_TMP_SET, flashParameters.tmpSet);
	
	FLASH_Lock();
}