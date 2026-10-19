/***********************************************************/
#ifndef		__MATHUTILS_H
#define		__MATHUTILS_H
/***********************************************************/
#include    "DataTypeDef.h"
#include    <stdint.h>
/***********************************************************/
#define     GLOBAL_Q_NUM    24
/***********************************************************/
#define     Q_Max           ((1u << GLOBAL_Q_NUM) - 1)
/***********************************************************/
typedef     s32     q_t;
typedef     s64     q64_t;
/***********************************************************/
//#define     Q_CONST(x)      ((q_t)((x) * (1UL << GLOBAL_Q_NUM)))
#define     Float2Q(x)      ((q_t)((x) * (1UL << GLOBAL_Q_NUM)))
#define     Q2Float(x)      ((float)((x) / (1UL << GLOBAL_Q_NUM)))
/***********************************************************/
#define     Q_MUL(a,b)      ((q_t)(((q64_t)(a) * (q64_t)(b)) >> GLOBAL_Q_NUM))
#define     Q_DIV(a, b)     ((q_t)((((q64_t)(a)) << GLOBAL_Q_NUM) / (q64_t)(b)))
/***********************************************************/
#define     SQRT3               Float2Q(1.7320508076f)
#define     ONE_OVER_SQRT3      Float2Q(0.5773502692f)
#define     TWO_OVER_THREE      Float2Q(0.6666666667f)
/***********************************************************/
extern q_t get_sin(q_t angle);
extern q_t get_cos(q_t angle);
extern void sin_test(void);
/***********************************************************/
static inline q_t Qmul(q_t a, q_t b)
{
    return (q_t)(((s64)a * (s64)b) >> GLOBAL_Q_NUM);
}
/***********************************************************/
static inline void clarke_3ph(q_t ia, q_t ib, q_t ic,
                              q_t *i_alpha, q_t *i_beta)
{
//    Ialpha = (2/3)*(1*Ia-cos60*Ib-cos60*Ic)
//    Ibeta = (2/3)*(0*Ia+cos30*Ib-cos30*Ic)

    q_t alpha_sum = ia - (q_t)((ib + ic) >> 1);   // ia - 0.5(ib+ic)
    q_t beta_diff = ib - ic;

    *i_alpha = Qmul(alpha_sum, TWO_OVER_THREE);
    *i_beta  = Qmul(beta_diff, ONE_OVER_SQRT3);
}
/***********************************************************/
static inline void park(q_t i_alpha, q_t i_beta, q_t angle,
                        q_t *i_d, q_t *i_q)
{
    q_t s = get_sin(angle);   // Q24
    q_t c = get_cos(angle);   // Q24

    //Park Transform
    //Id = Ialpha*cos(theta)+Ibeta*sin(theta)
    //Iq = -Ialpha*sin(theta)+Ibeta*cos(theta)

    *i_d = Qmul(i_alpha, c) + Qmul(i_beta,  s);
    *i_q = Qmul(i_beta,  c) - Qmul(i_alpha, s);
}
/***********************************************************/
#endif
/***********************************************************/
