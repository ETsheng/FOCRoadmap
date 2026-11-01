/*****************************************************************/
#include	"pll.h"
#include	"motor_para.h"
/*****************************************************************/
void	PLL_Init(PLL_Handle *pll, q_t kp, q_t ki)
{
	PID_Init(&(pll->unPID),kp,ki,0,C_Q_MotorSpeedMax,-C_Q_MotorSpeedMax);

	pll->Q_Speed = 0;
	pll->Q_Theta = 0;
}
/*****************************************************************/
void	PLL_Reset(PLL_Handle *pll, q_t init_theta)
{
	PID_Reset(&(pll->unPID));
	pll->Q_Theta = init_theta;
	pll->Q_Speed = 0;
}
/*****************************************************************/
void	PLL_Update(PLL_Handle *pll, q_t Q_Ealpha, q_t Q_Ebeta)
{
	//
	q_t	Q_sin = get_sin(pll->Q_Theta);
	q_t Q_Cos = get_cos(pll->Q_Theta);
	
	//
}
/*****************************************************************/