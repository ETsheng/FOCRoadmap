/***********************************************************/
#ifndef     __RAMDEF_H
#define     __RAMDEF_H
/***********************************************************/
#include    "DataTypeDef.h"
#include    "pid.h"
#include    "MathUtils.h"
/***********************************************************/
typedef struct
{
    q_t Q_Ia;
    q_t Q_Ib;
    q_t Q_Ic;
    
    q_t Q_DutyA;
    q_t Q_DutyB;
    q_t Q_DutyC;
    
    u8 u8Sector;
}SVPWM_Data;
/***********************************************************/
typedef struct
{
    u8      u8Test1;
    s8      s8Test1;
    u16     u16Test1;
    s16     s16Test1;
    u32     u32Test1;
    s32     s32Test1;
    
    q_t     q_tData_U;
    q_t     q_tData_V;
    q_t     q_tData_W;
    q_t     q_tAngle;
    
    q_t     q_tData_Alpha;
    q_t     q_tData_Beta;
    
    q_t     q_tData_Iq;
    q_t     q_tData_Id;
    
    SVPWM_Data unSVPWM;
    
    q_t     y;
}DebugData;
/***********************************************************/
extern DebugData   unDebug;
/***********************************************************/



/***********************************************************/
#endif
/***********************************************************/

