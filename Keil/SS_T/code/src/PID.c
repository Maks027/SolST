#include"pid.h"

#define MIN_OUT			0
#define MAX_OUT			3600
#define ERROR_MARGIN	5

//arm_pid_instance_q15 tmpPid;

//void pidInit(uint8_t reset)
//{
//	tmpPid.Kp = flashParameters.Kp;
//	tmpPid.Ki = flashParameters.Ki;
//	tmpPid.Kd = flashParameters.Kd;
//	
//	arm_pid_init_q15(&tmpPid, reset);
//}
	
//uint16_t pidCalc(int setPoint, int processVal)
//{

//	int error, out = 0;
//	
//	error = setPoint - processVal;
//	
//	
//	if(error < -ERROR_MARGIN)
//	{
//		out = MIN_OUT;
//	} 
//	else if(error > ERROR_MARGIN)
//	{
//		out = MAX_OUT;
//	}
//	else
//	{
//		out = arm_pid_q15(&tmpPid, error);
//	}
//	
//	if(out >= MAX_OUT)
//	{
//		out = MAX_OUT;
////		arm_pid_reset_q15(&tmpPid);
//		tmpPid.state[2] = MAX_OUT;
//	}
//	else if(out <= MIN_OUT)
//	{
//		out = MIN_OUT;
////		arm_pid_reset_q15(&tmpPid);
//		tmpPid.state[2] = MIN_OUT;
//	}
//	return out;
//}


//#define Kp			500
//#define Ki			0
//#define Kd			0

//int Kp = 500;
//int Ki = 0;
//int Kd = 0;

//int OUT_SCALE = 10;
//int MAX_INT = 36000;
//int MIN_INT = -36000;

//#define MAX_INT		36000
//#define MIN_INT		-MAX_INT



//#define OUT_SCALE	1000


uint16_t pidCalc(int setPoint, int processVal)
{
	static int sumError, out, lastErr, error;
	
	error = setPoint - processVal;
	
	sumError += error;
	if(sumError >= flashParameters.maxInt)
		sumError = flashParameters.maxInt;
	if(sumError <= -flashParameters.maxInt)
		sumError = -flashParameters.maxInt;

	out += (((flashParameters.Kp * error) + (flashParameters.Ki * sumError) + (flashParameters.Kd * (error - lastErr))) / flashParameters.outScale);
	
	lastErr = error;
	
	if(out >= MAX_OUT)
	{
		out = MAX_OUT;
		//sumError = 0;
	}
		
	
	if(out <= MIN_OUT)
	{
		out = MIN_OUT;
		//sumError = 0;
	}
		
	
	return out;
}	

//void TIM1_UP_IRQHandler(void)
//{
//	TIM1->SR &= ~TIM_SR_UIF;
//	
//	pidCnt++;
//	
//	if(pidCnt >= PID_RATE)
//	{
//		updPwmVal(pidCalc(200, tmpVal));
//		
//		pidCnt = 0;
//	}
//	
//}


