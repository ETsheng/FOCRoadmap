/***********************************************************/
#include    "pid.h"
/***********************************************************/
void    PID_Init(PID_Handle *pL_pid,q_t kp, q_t ki, q_t kd, q_t out_max, q_t out_min)
{
    pL_pid->Q_Kp = kp;
    pL_pid->Q_Ki = ki;
    pL_pid->Q_Kd = kd;
    pL_pid->Q_OutMax = out_max;
    pL_pid->Q_OutMin = out_min;
    
    pL_pid->Q_Integral = 0;
    pL_pid->Q_Prev_error = 0;
    pL_pid->Q_Prev_measure = 0;
    
    pL_pid->Q_Out = 0;
}
/***********************************************************/
void    PID_Reset(PID_Handle *pL_pid)
{
    pL_pid->Q_Integral = 0;
    pL_pid->Q_Prev_error = 0;
    pL_pid->Q_Prev_measure = 0;
    
    pL_pid->Q_Out = 0;
}
/***********************************************************/
q_t     PID_Calc(PID_Handle *pL_pid, q_t Q_ref, q_t Q_fbk)
{
    q_t Q_error = 0;
    q_t Q_P_term = 0;
    q_t Q_D_term = 0;
    q_t Q_Out = 0;
    
    Q_error = Q_ref - Q_fbk;
    Q_P_term = Q_MUL(pL_pid->Q_Kp, Q_error);
    
    pL_pid->Q_Integral += Q_MUL(pL_pid->Q_Ki, Q_error);
    if(pL_pid->Q_Integral > pL_pid->Q_OutMax)
    {
        pL_pid->Q_Integral = pL_pid->Q_OutMax;
    }
    if(pL_pid->Q_Integral < pL_pid->Q_OutMin)
    {
        pL_pid->Q_Integral = pL_pid->Q_OutMin;
    }
    
    Q_D_term = Q_MUL(pL_pid->Q_Kd,Q_error - pL_pid->Q_Prev_error);
    pL_pid->Q_Prev_error = Q_error;
    
    Q_Out = Q_P_term + pL_pid->Q_Integral + Q_D_term;
    
    if(Q_Out > pL_pid->Q_OutMax)
    {
        Q_Out = pL_pid->Q_OutMax;
    }
    
    if(Q_Out < pL_pid->Q_OutMin)
    {
        Q_Out = pL_pid->Q_OutMin;
    }
    
    pL_pid->Q_Out = Q_Out;
    
    return Q_Out;
}
/***********************************************************/


