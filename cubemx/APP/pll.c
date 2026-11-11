/*****************************************************************/
#include	"pll.h"
#include	"motor_para.h"
#include    "Ramdef.h"
/*****************************************************************/
PLL_Handle  unPLL;
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
	
	//err = Ea * cos(theta) + Ebeta * sin(theta) = -A*sin(delta theta), delta theta = theta_true - theta^
    q_t Q_err = Q_MUL(Q_Ealpha, Q_Cos) + Q_MUL(Q_Ebeta,Q_sin);
    
    // calc speed
    pll->Q_Speed = PID_Calc(&(pll->unPID),0,Q_err);
    
    // integrate for theta
    pll->Q_Theta = (q_t)(((u32)pll->Q_Theta + (u32)pll->Q_Speed) & ANGLE_MASK);
}
/*****************************************************************/
void PLL_Test(void)
{
    static u8 u8L_InitFlag = 0;
    static u8 u8L_Time1msCache = 0;
    
    #define     Q_Iq    Float2Q(0.1)
    #define     Q_Id    Float2Q(0)
    
    
    if(!u8L_InitFlag)
    {
        u8L_InitFlag = 1;
        
        PLL_Init(&unPLL,C_Q_PLL_Kp,C_Q_PLL_Ki);
    }
    
    if(u8L_Time1msCache != unTimerData.F_TimeBase1ms)
    {
        u8L_Time1msCache = unTimerData.F_TimeBase1ms;
        
        unPLL.Q_GenTheta = ((unPLL.Q_GenTheta+4194) & ANGLE_MASK);
        ipark(Q_Id,Q_Iq,unPLL.Q_GenTheta,&unPLL.Q_GenAlpha,&unPLL.Q_GenBeta);
        
        PLL_Update(&unPLL,unPLL.Q_GenAlpha,unPLL.Q_GenBeta);
    }
}

