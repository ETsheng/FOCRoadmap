/*****************************************************************/
#include	"smo.h"
#include	"motor_para.h"
#include    "Ramdef.h"
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
static q_t Q_SMO_Sat(q_t Q_Err, const SMO_Handle *smo)
{
	if(Q_Err >  smo->Q_Phi)  return  smo->Q_KSlide;
	if(Q_Err < -smo->Q_Phi)  return -smo->Q_KSlide;

	/* 边界层内: z = k·(e/φ)，此时 |e/φ| < 1，两次 Q_MUL 都不会溢出 */
	return Q_MUL(Q_MUL(Q_Err, smo->Q_InvPhi), smo->Q_KSlide);
}
/*****************************************************************/
void SMO_Init(SMO_Handle *smo)
{
	smo->Q_F = C_Q_SMO_F;
	smo->Q_G = C_Q_SMO_G;
	smo->Q_KSlide = C_Q_SMO_Kslide;
	smo->Q_Phi = C_Q_SMO_Phi;
    smo->Q_InvPhi = Q_DIV(C_Q_OneQ, C_Q_SMO_Phi);
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
    
    smo->Q_Zalpha = 0;
    smo->Q_Zbeta = 0;
}
/*****************************************************************/
void SMO_Update(SMO_Handle *smo,q_t Q_V_alpha,q_t Q_V_beta, q_t Q_I_alpha, q_t Q_I_beta)
{
	q_t	QL_Err_IAlpha = 0;
	q_t QL_Err_IBeta = 0;
	q_t QL_Z_Alpha = 0;
	q_t QL_Z_Beta = 0;
	
	QL_Err_IAlpha = smo->Q_Ialpha_est - Q_I_alpha;
	QL_Err_IBeta = smo->Q_Ibeta_est - Q_I_beta;
	
	QL_Z_Alpha = Q_SMO_Sat(QL_Err_IAlpha, smo);
    QL_Z_Beta  = Q_SMO_Sat(QL_Err_IBeta,  smo);
    
    smo->Q_Ialpha_est = Q_MUL(smo->Q_F,smo->Q_Ialpha_est) + Q_MUL(smo->Q_G,Q_V_alpha-QL_Z_Alpha);
	smo->Q_Ibeta_est = Q_MUL(smo->Q_F,smo->Q_Ibeta_est) + Q_MUL(smo->Q_G,Q_V_beta-QL_Z_Beta);
    
    //LPF
    smo->Q_Ealpha += Q_MUL(smo->Q_K_LPF,QL_Z_Alpha-smo->Q_Ealpha);
    smo->Q_Ebeta += Q_MUL(smo->Q_K_LPF,QL_Z_Beta-smo->Q_Ebeta);
    
    smo->Q_Zalpha = QL_Z_Alpha;
    smo->Q_Zbeta = QL_Z_Beta;
}
/*****************************************************************/
//debug
/* 测试参数 */
#define Q_Im      Float2Q(1.0f)     /* 电流幅值 1 A */
#define Q_A       Float2Q(3.0f)     /* 反电势幅值 V */
#define Q_W       Float2Q(0.005f)     /* 每拍角增量 = 5Hz @1kHz(1步/ms) */
#define Q_INV_G   Float2Q(10.0f)    /* 1/G，G=0.1 */

q_t Q_theta_true, Q_Va, Q_Vb, Q_Ia, Q_Ib, Q_Ea, Q_Eb;

void Sim_Step(void)
{
    q_t s0 = get_sin(Q_theta_true);
    q_t c0 = get_cos(Q_theta_true);
    q_t s1 = get_sin(Q_theta_true + Q_W);      /* 下一拍的角度 */
    q_t c1 = get_cos(Q_theta_true + Q_W);

    /* 本拍电流（q 轴，与 E 同向） */
    Q_Ia = -Q_MUL(Q_Im, s0);
    Q_Ib =  Q_MUL(Q_Im, c0);

    /* 真值反电势 */
    Q_Ea = -Q_MUL(Q_A, s0);
    Q_Eb =  Q_MUL(Q_A, c0);

    /* 由模型反算电压：V = (I[k+1] − F·I[k])/G + E */
    Q_Va = Q_MUL(Q_INV_G, (-Q_MUL(Q_Im, s1)) - Q_MUL(C_Q_SMO_F, Q_Ia)) + Q_Ea;
    Q_Vb = Q_MUL(Q_INV_G, ( Q_MUL(Q_Im, c1)) - Q_MUL(C_Q_SMO_F, Q_Ib)) + Q_Eb;

    Q_theta_true = (q_t)(((u32)Q_theta_true + (u32)Q_W) & ANGLE_MASK);
}
/*****************************************************************/
void SMO_Test_Run(void)
{
    static u8 init = 0, tick = 0;

    if(!init) { init = 1; SMO_Init(&unSMO); PLL_Init(&unPLL, C_Q_PLL_Kp, C_Q_PLL_Ki); }

    if(tick == unTimerData.F_TimeBase1ms) return;
    tick = unTimerData.F_TimeBase1ms;

    /* 1 步 / 1ms：调试器每次读到的都是相邻的真实状态，不被 burst 打乱 */
    Sim_Step();
    SMO_Update(&unSMO, Q_Va, Q_Vb, Q_Ia, Q_Ib);
    PLL_Update(&unPLL, unSMO.Q_Ealpha, unSMO.Q_Ebeta);
}


