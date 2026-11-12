/*****************************************************************/
#ifndef 		__SMO_H
#define			__SMO_H
/*****************************************************************/
#include	"DataTypeDef.h"
#include	"MathUtils.h"
/*****************************************************************/
typedef struct
{
	q_t		Q_F;
	q_t		Q_G;
	q_t		Q_KSlide;
	q_t		Q_InvPhi;
	q_t		Q_K_LPF;
	
	q_t		Q_Ialpha_est;
	q_t		Q_Ibeta_est;
	q_t		Q_Ealpha;
	q_t		Q_Ebeta;
}SMO_Handle;
/*****************************************************************/
extern SMO_Handle unSMO;
/*****************************************************************/
static q_t Q_SMO_Sat(q_t Q_Err, q_t Q_Kslide, q_t Q_InvPhi);
/*****************************************************************/
extern void SMO_Init(SMO_Handle *smo);
extern void SMO_Reset(SMO_Handle *smo);
extern void SMO_Update(SMO_Handle *smo,q_t Q_V_alpha,q_t Q_V_beta, q_t Q_I_alpha, q_t Q_I_beta);
/*****************************************************************/
#endif
/*****************************************************************/