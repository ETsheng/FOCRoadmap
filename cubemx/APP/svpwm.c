/***********************************************************/
#include    "Ramdef.h"
#include    "MathUtils.h"
#include    "svpwm.h"
/***********************************************************/
void svpwm_get_duty(SVPWM_Data *svpwm_data)
{
    u8 u8L_Sector = 0;
    q_t Q_Ts = Q_Max;
    q_t Q_T1,Q_T2,Q_T3,Q_T4,Q_T5,Q_T6,Q_T7 = 0;
    q_t Q_sum = 0;
    q_t k_svpwm = 0;
    
    if(svpwm_data->Q_Ia > 0)
    {
        u8L_Sector += 1;
    }
    
    if(svpwm_data->Q_Ib > 0)
    {
        u8L_Sector += 2;
    }
    
    if(svpwm_data->Q_Ic > 0)
    {
        u8L_Sector += 4;
    }
    
    svpwm_data->u8Sector = u8L_Sector;
    switch(u8L_Sector)
    {
        case 1:
            Q_T2 = -svpwm_data->Q_Ic;
            Q_T6 = -svpwm_data->Q_Ib;
            Q_sum = Q_T2 + Q_T6;
            if(Q_sum > Q_Ts)
            {
                k_svpwm = Q_DIV(Q_Ts,Q_sum);
                Q_T2 = Q_MUL(Q_T2,k_svpwm);
                Q_T6 = Q_MUL(Q_T6,k_svpwm);
            }
            Q_T7 = (Q_Ts - Q_T2 - Q_T6)/2;
            svpwm_data->Q_DutyA = Q_T6 + Q_T7;
            svpwm_data->Q_DutyB = Q_T2 + Q_T6 + Q_T7;
            svpwm_data->Q_DutyC = Q_T7;
        break;
        
        case 2:
            Q_T1 = -svpwm_data->Q_Ia;
            Q_T3 = -svpwm_data->Q_Ic;
            Q_sum = Q_T1 + Q_T3;
            if(Q_sum > Q_Ts)
            {
                k_svpwm = Q_DIV(Q_Ts,Q_sum);
                Q_T1 = Q_MUL(Q_T1,k_svpwm);
                Q_T3 = Q_MUL(Q_T3,k_svpwm);
            }
            Q_T7 = (Q_Ts - Q_T1 - Q_T3)/2;
            svpwm_data->Q_DutyA = Q_T7;
            svpwm_data->Q_DutyB = Q_T3 + Q_T7;
            svpwm_data->Q_DutyC = Q_T1 + Q_T3 + Q_T7;
        break;
        
        case 3:
            Q_T2 = svpwm_data->Q_Ia;
            Q_T3 = svpwm_data->Q_Ib;
            Q_sum = Q_T2 + Q_T3;
            if(Q_sum > Q_Ts)
            {
                k_svpwm = Q_DIV(Q_Ts,Q_sum);
                Q_T2 = Q_MUL(Q_T2,k_svpwm);
                Q_T3 = Q_MUL(Q_T3,k_svpwm);
            }
            Q_T7 = (Q_Ts - Q_T2 - Q_T3)/2;
            svpwm_data->Q_DutyA = Q_T7;
            svpwm_data->Q_DutyB = Q_T2 + Q_T3 + Q_T7;
            svpwm_data->Q_DutyC = Q_T3 + Q_T7;
        break;
        
        case 4:
            Q_T4 = -svpwm_data->Q_Ib;
            Q_T5 = -svpwm_data->Q_Ia;
            Q_sum = Q_T4 + Q_T5;
            if(Q_sum > Q_Ts)
            {
                k_svpwm = Q_DIV(Q_Ts,Q_sum);
                Q_T4 = Q_MUL(Q_T4,k_svpwm);
                Q_T5 = Q_MUL(Q_T5,k_svpwm);
            }
            Q_T7 = (Q_Ts - Q_T4 - Q_T5)/2;
            svpwm_data->Q_DutyA = Q_T4 + Q_T5 + Q_T7;
            svpwm_data->Q_DutyB = Q_T7;
            svpwm_data->Q_DutyC = Q_T5 + Q_T7;
        break;
        
        case 5:
            Q_T4 = svpwm_data->Q_Ic;
            Q_T6 = svpwm_data->Q_Ia;
            Q_sum = Q_T4 + Q_T6;
            if(Q_sum > Q_Ts)
            {
                k_svpwm = Q_DIV(Q_Ts,Q_sum);
                Q_T4 = Q_MUL(Q_T4,k_svpwm);
                Q_T6 = Q_MUL(Q_T6,k_svpwm);
            }
            Q_T7 = (Q_Ts - Q_T4 - Q_T6)/2;
            svpwm_data->Q_DutyA = Q_T4 + Q_T6 + Q_T7;
            svpwm_data->Q_DutyB = Q_T6 + Q_T7;
            svpwm_data->Q_DutyC = Q_T7;
        break;
        
        case 6:
            Q_T1 = svpwm_data->Q_Ib;
            Q_T5 = svpwm_data->Q_Ic;
            Q_sum = Q_T1 + Q_T5;
            if(Q_sum > Q_Ts)
            {
                k_svpwm = Q_DIV(Q_Ts,Q_sum);
                Q_T1 = Q_MUL(Q_T1,k_svpwm);
                Q_T5 = Q_MUL(Q_T5,k_svpwm);
            }
            Q_T7 = (Q_Ts - Q_T1 - Q_T5)/2;
            svpwm_data->Q_DutyA = Q_T5 + Q_T7;
            svpwm_data->Q_DutyB = Q_T7;
            svpwm_data->Q_DutyC = Q_T1 + Q_T5 + Q_T7;
        break;
        
        default:
            svpwm_data->Q_DutyA = 0;
            svpwm_data->Q_DutyB = 0;
            svpwm_data->Q_DutyC = 0;
        break;
    }
}


