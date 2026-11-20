/*****************************************************************/
#include	"foc_fsm.h"
#include	"Ramdef.h"
#include	"adc.h"
#include	"tim.h"
/*****************************************************************/
FOCFSMData unFOCFSM;
/*****************************************************************/
static void FOC_FSMManger(void);
static void FOCFSM_TimeExtend(void);
static void FOCFSM_INIT(void);
/*****************************************************************/
void FOCFSM(void)
{
	FOCFSM_TimeExtend();
	FOC_FSMManger();
}
/*****************************************************************/
static void FOCFSM_TimeExtend(void)
{
	static u8 LF_FSM1msCache = 0;
	
	if(LF_FSM1msCache != unTimerData.F_TimeBase1ms)
	{
		LF_FSM1msCache = unTimerData.F_TimeBase1ms;
		
		FUN_Dec(unFOCFSM.u16WaitTime_1ms);
	}
}
/*****************************************************************/
static void FOC_FSMManger(void)
{
	u8 u8L_StateH = (unFOCFSM.u8State & 0xf0);
	
	switch(u8L_StateH)
	{
		case C_FOC_INIT:
			FOCFSM_INIT();
		break;
		
		case C_FOC_IDLE:
			
		break;
		
		case C_FOC_PRECHARGE:
			
		break;
		
		case C_FOC_ALIGN:
			
		break;
		
		case C_FOC_OPENLOOP:
			
		break;
		
		case C_FOC_RUN:
			
		break;
		
		case C_FOC_STOP:
			
		break;
		
		case C_FOC_FAULT:
			
		break;
		
		default:
//			unFOCFSM.u8State = ;
		break;
	}
}
/*****************************************************************/
static void FOCFSM_INIT(void)
{
	switch(unFOCFSM.u8State)
	{
		case C_FOC_INIT_WAIT:
			if(!unFOCFSM.F_Init)
			{
				unFOCFSM.F_Init = 1;
				
				unFOCFSM.u16WaitTime_1ms = 500;
			}
			
			if(unFOCFSM.u16WaitTime_1ms == 0)
			{
				unFOCFSM.u8State = C_FOC_INIT_CFG;
			}				
		break;
		
		case C_FOC_INIT_CFG:						
		  HAL_ADCEx_Calibration_Start(&hadc1);
		  if(READ_BIT(ADC1->CR2,ADC_CR2_ADON) == 0)
		  {
			__HAL_ADC_ENABLE(&hadc1);
		  }
		  __HAL_ADC_DISABLE_IT(&hadc1,ADC_IT_JEOC);
		  __HAL_ADC_ENABLE_IT(&hadc1,ADC_IT_EOC);
		  
		  __HAL_ADC_CLEAR_FLAG(&hadc1,ADC_FLAG_EOC|ADC_FLAG_JEOC);
		  
		  // inject extern trig
		  HAL_ADCEx_InjectedStart(&hadc1);
		  
		  // enable ch4 event, start timer but not output (MOE=0)
		  TIM_CCxChannelCmd(TIM1,TIM_CHANNEL_4,TIM_CCx_ENABLE);
		  HAL_TIM_Base_Start(&htim1);
		  
		  unFOCFSM.u8State = C_FOC_INIT_CALIB;
		break;
		
		case C_FOC_INIT_CALIB:
			ADC_OffsetSub();
		break;
		
		case C_FOC_INIT_VERIF:
			
		break;
		
		default:
			
		break;
	}
}
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/



