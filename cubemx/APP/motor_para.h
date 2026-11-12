/*****************************************************************/
#ifndef		__MOTOR_PARA_H
#define		__MOTOR_PARA_H
/*****************************************************************/
#include	"MathUtils.h"
/*****************************************************************/
// SYSTEM
#define		C_FOC_Freq					(10000.0f)
#define		C_FOC_Ts					((1.0f)/C_FOC_Freq)
/*****************************************************************/
//motor para
#define		C_MotorRs					(0.1f)
#define		C_MotorLs					(0.1f)

/*****************************************************************/
#define		C_Q_MotorSpeedMax			Float2Q(2.0f)
/*****************************************************************/
// SMO
#define		C_Q_OneQ					Float2Q(1.0f)
#define		C_Q_SMO_F					Float2Q(1.0f - C_MotorRs/(C_FOC_Freq * C_MotorLs))
#define		C_Q_SMO_G					Float2Q(1.0f / (C_MotorLs * C_FOC_Freq))
#define		C_Q_SMO_Kslide				Float2Q(1.2f)
#define		C_Q_SMO_INV_PHI				Float2Q(1.0f/0.05f)
#define		C_SMO_LPF_Fc_Hz				(300.0f)
#define		C_Q_SMO_K_LPF				Float2Q(C_2PI*C_SMO_LPF_Fc_Hz*C_FOC_Ts)
/*****************************************************************/
// PLL
#define     C_Q_PLL_Kp                  Float2Q(0.01f)
#define     C_Q_PLL_Ki                  Float2Q(0.001f)

/*****************************************************************/
/*****************************************************************/
#endif
/*****************************************************************/

