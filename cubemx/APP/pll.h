/*****************************************************************/
#ifndef		__PLL_H
#define		__PLL_H
/*****************************************************************/
#include	"MathUtils.h"
#include	"pid.h"
/*****************************************************************/
typedef struct
{
	PID_Handle	unPID;
	
	q_t		Q_Theta;
	q_t		Q_Speed;
    
    q_t     Q_GenTheta;
    q_t     Q_GenSpeed;
    q_t     Q_GenAlpha;
    q_t     Q_GenBeta;
}PLL_Handle;
/*****************************************************************/
extern void	PLL_Init(PLL_Handle *pll, q_t kp, q_t ki);
extern void	PLL_Reset(PLL_Handle *pll, q_t init_theta);
extern void	PLL_Update(PLL_Handle *pll, q_t Q_Ealpha, q_t Q_Ebeta);
extern void PLL_Test(void);
/*****************************************************************/
extern PLL_Handle  unPLL;
/*****************************************************************/
#endif
/*****************************************************************/

