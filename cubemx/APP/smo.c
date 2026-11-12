/*****************************************************************/
#include	"smo.h"
#include	"motor_para.h"
/*****************************************************************/
SMO_Handle unSMO;
/*****************************************************************/
/*
vα = R·iα + L·diα/dt + eα
vβ = R·iβ + L·diβ/dt + eβ

eα = −ω·ψf·sinθ
eβ = +ω·ψf·cosθ
*/
/*****************************************************************/
static q_t Q_SMO_Sat(q_t Q_Err, q_t Q_Kslide, q_t Q_InvPhi)
{
	q_t	Q_Ret = Q_MUL(Q_Err,Q_InvPhi);
	
	if(Q_Ret > C_Q_OneQ)
	{
		Q_Ret = Q_Kslide;
	}
	else if(Q_Ret < -C_Q_OneQ)
	{
		Q_Ret = -Q_Kslide;
	}
	else
	{
		Q_Ret = Q_MUL(Q_Ret,Q_Kslide);
	}
	
	return Q_Ret;
}
/*****************************************************************/
void SMO_Init(SMO_Handle *smo)
{
	smo->Q_F = C_Q_SMO_F;
	smo->Q_G = C_Q_SMO_G;
	smo->Q_KSlide = C_Q_SMO_Kslide;
	smo->Q_InvPhi = C_Q_SMO_INV_PHI;
	smo->Q_K_LPF = C_Q_SMO_K_LPF;
	
	SMO_Reset(smo);
}
/*****************************************************************/
void SMO_Reset(SMO_Handle *smo)
{
	smo->Q_Ialpha_est = 0;
	smo->Q_Ibeta_est = 0;
	smo->Q_Ealpha = 0;
	smo->Q_Ebeta = 0;
}
/*****************************************************************/
void SMO_Update(SMO_Handle *smo,q_t Q_V_alpha,q_t Q_V_beta, q_t Q_I_alpha, q_t Q_I_beta)
{
	q_t	QL_Err_IAlpha = 0;
	q_t QL_Err_IBeta = 0;
	q_t QL_Z_Alpha = 0;
	q_t QL_Z_Beta = 0;
	q_t	QL_IAlpha_Est = 0;
	q_t QL_IBeta_Est = 0;
	
	QL_Err_IAlpha = smo->Q_Ialpha_est - Q_I_alpha;
	QL_Err_IBeta = smo->Q_Ibeta_est - Q_I_beta;
	
	QL_Z_Alpha = Q_SMO_Sat(QL_Err_IAlpha,smo->Q_KSlide,smo->Q_InvPhi);
	QL_Z_Beta = Q_SMO_Sat(QL_Err_IBeta,smo->Q_KSlide,smo->Q_InvPhi);
	
}
/*****************************************************************/
/*****************************************************************/


