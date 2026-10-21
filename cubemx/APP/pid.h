/***********************************************************/
#ifndef     __PID_H
#define     __PID_H
/***********************************************************/
#include    "MathUtils.h"
/***********************************************************/
typedef struct
{
    q_t     Q_Kp;
    q_t     Q_Ki;
    q_t     Q_Kd;
    q_t     Q_OutMax;
    q_t     Q_OutMin;
    
    q_t     Q_Integral;
    q_t     Q_Prev_error;
    q_t     Q_Prev_measure;
    
    q_t     Q_Out;
}PID_Handle;
/***********************************************************/
extern void    PID_Init(PID_Handle *pL_pid,q_t kp, q_t ki, q_t kd, q_t out_max, q_t out_min);
extern void    PID_Reset(PID_Handle *pL_pid);
extern q_t     PID_Calc(PID_Handle *pL_pid, q_t Q_ref, q_t Q_fbk);
extern void    PID_Debug_Step(PID_Handle *pid, q_t ref);
/***********************************************************/
/***********************************************************/
/***********************************************************/
#endif
/***********************************************************/