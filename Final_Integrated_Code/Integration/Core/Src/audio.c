/*#include "audio.h"


 TIM_HandleTypeDef * ourtimer;

 DAC_HandleTypeDef*  ourdac;



#define TIM2_PRSC 12
#define LUT_SIZE 100
uint16_t SIN_LUT[LUT_SIZE];
const double AMP_PCENT = 70.0;

void audioInit(TIM_HandleTypeDef * timer, DAC_HandleTypeDef * dacHandler){
	ourtimer = timer;
	ourdac = dacHandler;
}

void fill_LUT(void)
{
	//creates a sine wave look up table centered at VREF/2
	double HALF_AMP = (AMP_PCENT/ 100.0) * 2047.0;//calculates a half amplitude given the desired volume
	uint16_t i = 0;
	for(; i < LUT_SIZE; ++i)
	{
		SIN_LUT[i] = (uint16_t) ( (sin( ( (double) i) * 360.0 / ((double) LUT_SIZE)  * 3.14159265/180.0) * HALF_AMP) + 2048.0);
	}
}


//sets compare value (period) for tim2
void setComp(uint32_t newComp)
{
	HAL_TIM_Base_Stop(ourtimer);
	ourtimer->Instance = TIM2;
	ourtimer->Init.Prescaler = TIM2_PRSC;
	ourtimer->Init.CounterMode = TIM_COUNTERMODE_UP;
	ourtimer->Init.Period = newComp;
	ourtimer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	ourtimer->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(ourtimer) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_TIM_Base_Start(ourtimer);
}


void changeNote(float frequency)
{
	setComp((uint32_t) (120000000.0f/TIM2_PRSC/((float)LUT_SIZE)/frequency) );
}
//used to iterate through the LUT
void TIM2_ISR()
{
	static uint32_t index = 0;
	HAL_DAC_SetValue(ourdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, SIN_LUT[index]);
	++index;
	if(index > LUT_SIZE) index = 0;
}


void runAudio(){

	 fill_LUT();
	   HAL_DAC_SetValue(ourdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0x0);
	   HAL_DAC_Start(ourdac, DAC_CHANNEL_1);
	   HAL_TIM_Base_Start_IT(ourtimer);

	while (1)
	 {changeNote(261.63);
	 HAL_Delay(1000);
	 changeNote(293.66);
	 HAL_Delay(1000);
	 //changeNote(329.63);
	 //HAL_Delay(1000);
	 changeNote(349.23);
	 HAL_Delay(1000);
	 /*changeNote(392.0);
	 HAL_Delay(1000);
	 changeNote(440.0);
	 HAL_Delay(1000);
	 changeNote(493.88);
	 HAL_Delay(1000);
	 changeNote(523.25);
	 HAL_Delay(1000);
	 changeNote(493.88);
	 HAL_Delay(1000);
	 changeNote(440.0);
	 HAL_Delay(1000);
	 changeNote(392.0);
	 HAL_Delay(1000);
	 changeNote(349.23);
	 HAL_Delay(1000);
	 changeNote(329.63);
	 HAL_Delay(1000);
	 changeNote(293.66);
	 HAL_Delay(1000);*/
 //}

//}

