/***********************************************************/
#include    "MathUtils.h"
#include    "Ramdef.h"
#include    "svpwm.h"
/***********************************************************/
#define     SIN_TABLE_SIZE      256
#define     SIN_TABLE_LAST     (SIN_TABLE_SIZE - 1)
/***********************************************************/
#define     ANGLE_MASK         ((1u << GLOBAL_Q_NUM) - 1)      // 0x00FFFFFF
#define     ANGLE_90           (1u << (GLOBAL_Q_NUM - 2))      // 0x00400000
#define     ANGLE_180          (1u << (GLOBAL_Q_NUM - 1))      // 0x00800000
#define     ANGLE_270          (3u << (GLOBAL_Q_NUM - 2))      // 0x00C00000
#define     ANGLE_360          (1u << GLOBAL_Q_NUM)            // 0x01000000
#define     ANGLE_360          (1u << GLOBAL_Q_NUM)            // 0x01000000
#define     ANGLE_60            ((q_t)(((u64)1u << GLOBAL_Q_NUM) / 6u))       // p/3
#define     ANGLE_120           ((q_t)(((u64)1u << GLOBAL_Q_NUM) / 3u))       // 2p/3
#define     ANGLE_240           ((q_t)(((u64)1u << GLOBAL_Q_NUM) * 2u / 3u))  // 4p/3
#define     ANGLE_300           ((q_t)(((u64)1u << GLOBAL_Q_NUM) * 5u / 6u))  // 5p/3

#define     ANGLE_INDEX_SHIFT   (GLOBAL_Q_NUM - 2 - 8)      // 8bits table + 2bits stand for 0-pi/2 + pi/2-pi
#define     ANGLE_FRAC_MASK     ((1 << ANGLE_INDEX_SHIFT) - 1)
/***********************************************************/
static q_t sin_LUT(q_t angle_0_90);
/***********************************************************/
// 0-pi/2
const q_t sin_table[SIN_TABLE_SIZE] = {
    Float2Q(0.0000000000f), Float2Q(0.0061358846f), Float2Q(0.0122715384f), Float2Q(0.0184067299f),
    Float2Q(0.0245412285f), Float2Q(0.0306748032f), Float2Q(0.0368072229f), Float2Q(0.0429382569f),
    Float2Q(0.0490676744f), Float2Q(0.0551952443f), Float2Q(0.0613207363f), Float2Q(0.0674439196f),
    Float2Q(0.0735645636f), Float2Q(0.0796824380f), Float2Q(0.0857973123f), Float2Q(0.0919089565f),
    Float2Q(0.0980171403f), Float2Q(0.1041216338f), Float2Q(0.1102222073f), Float2Q(0.1163186309f),
    Float2Q(0.1224106752f), Float2Q(0.1284981110f), Float2Q(0.1345807085f), Float2Q(0.1406582382f),
    Float2Q(0.1467304745f), Float2Q(0.1527971853f), Float2Q(0.1588581433f), Float2Q(0.1649131213f),
    Float2Q(0.1709618888f), Float2Q(0.1770042204f), Float2Q(0.1830398880f), Float2Q(0.1890686641f),
    Float2Q(0.1950903220f), Float2Q(0.2011046348f), Float2Q(0.2071113762f), Float2Q(0.2131103199f),
    Float2Q(0.2191012402f), Float2Q(0.2250839114f), Float2Q(0.2310581083f), Float2Q(0.2370236059f),
    Float2Q(0.2429801799f), Float2Q(0.2489276057f), Float2Q(0.2548656596f), Float2Q(0.2607941179f),
    Float2Q(0.2667127575f), Float2Q(0.2726213554f), Float2Q(0.2785196894f), Float2Q(0.2844075372f),
    Float2Q(0.2902846773f), Float2Q(0.2961508882f), Float2Q(0.3020059493f), Float2Q(0.3078496400f),
    Float2Q(0.3136817404f), Float2Q(0.3195020307f), Float2Q(0.3253102922f), Float2Q(0.3311063058f),
    Float2Q(0.3368898534f), Float2Q(0.3426607173f), Float2Q(0.3484186802f), Float2Q(0.3541635254f),
    Float2Q(0.3598950365f), Float2Q(0.3656129978f), Float2Q(0.3713171940f), Float2Q(0.3770074102f),
    Float2Q(0.3826834324f), Float2Q(0.3883450467f), Float2Q(0.3939920401f), Float2Q(0.3996241998f),
    Float2Q(0.4052413141f), Float2Q(0.4108431711f), Float2Q(0.4164295601f), Float2Q(0.4220002708f),
    Float2Q(0.4275550934f), Float2Q(0.4330938189f), Float2Q(0.4386162385f), Float2Q(0.4441221446f),
    Float2Q(0.4496113297f), Float2Q(0.4550835871f), Float2Q(0.4605387110f), Float2Q(0.4659764958f),
    Float2Q(0.4713967368f), Float2Q(0.4767992301f), Float2Q(0.4821837721f), Float2Q(0.4875501601f),
    Float2Q(0.4928981922f), Float2Q(0.4982276669f), Float2Q(0.5035383837f), Float2Q(0.5088301425f),
    Float2Q(0.5141027442f), Float2Q(0.5193559902f), Float2Q(0.5245896827f), Float2Q(0.5298036247f),
    Float2Q(0.5349976199f), Float2Q(0.5401714727f), Float2Q(0.5453249884f), Float2Q(0.5504579729f),
    Float2Q(0.5555702330f), Float2Q(0.5606615762f), Float2Q(0.5657318108f), Float2Q(0.5707807459f),
    Float2Q(0.5758081914f), Float2Q(0.5808139581f), Float2Q(0.5857978575f), Float2Q(0.5907597019f),
    Float2Q(0.5956993045f), Float2Q(0.6006164794f), Float2Q(0.6055110414f), Float2Q(0.6103828063f),
    Float2Q(0.6152315906f), Float2Q(0.6200572120f), Float2Q(0.6248594888f), Float2Q(0.6296382389f),
    Float2Q(0.6343932842f), Float2Q(0.6391244449f), Float2Q(0.6438315429f), Float2Q(0.6485144010f),
    Float2Q(0.6531728430f), Float2Q(0.6578066933f), Float2Q(0.6624157776f), Float2Q(0.6669999223f),
    Float2Q(0.6715589548f), Float2Q(0.6760927036f), Float2Q(0.6806009981f), Float2Q(0.6850836678f),
    Float2Q(0.6895405447f), Float2Q(0.6939714609f), Float2Q(0.6983762494f), Float2Q(0.7027547445f),
    Float2Q(0.7071067812f), Float2Q(0.7114321957f), Float2Q(0.7157308253f), Float2Q(0.7200020590f),
    Float2Q(0.7242470830f), Float2Q(0.7284643904f), Float2Q(0.7326542717f), Float2Q(0.7368165689f),
    Float2Q(0.7409511254f), Float2Q(0.7450577854f), Float2Q(0.7491363945f), Float2Q(0.7531867990f),
    Float2Q(0.7572088465f), Float2Q(0.7612023855f), Float2Q(0.7651672656f), Float2Q(0.7691033376f),
    Float2Q(0.7730104534f), Float2Q(0.7768884657f), Float2Q(0.7807372286f), Float2Q(0.7845565972f),
    Float2Q(0.7883464276f), Float2Q(0.7921065773f), Float2Q(0.7958369046f), Float2Q(0.7995372691f),
    Float2Q(0.8032075315f), Float2Q(0.8068475535f), Float2Q(0.8104571983f), Float2Q(0.8140363297f),
    Float2Q(0.8175848132f), Float2Q(0.8211025150f), Float2Q(0.8245893028f), Float2Q(0.8280450453f),
    Float2Q(0.8314696123f), Float2Q(0.8348628750f), Float2Q(0.8382247056f), Float2Q(0.8415549774f),
    Float2Q(0.8448535652f), Float2Q(0.8481203448f), Float2Q(0.8513551931f), Float2Q(0.8545579884f),
    Float2Q(0.8577286100f), Float2Q(0.8608669386f), Float2Q(0.8639728561f), Float2Q(0.8670462455f),
    Float2Q(0.8700869911f), Float2Q(0.8730949784f), Float2Q(0.8760700942f), Float2Q(0.8790122264f),
    Float2Q(0.8819212643f), Float2Q(0.8847970984f), Float2Q(0.8876396204f), Float2Q(0.8904487232f),
    Float2Q(0.8932243012f), Float2Q(0.8959662498f), Float2Q(0.8986744657f), Float2Q(0.9013488470f),
    Float2Q(0.9039892931f), Float2Q(0.9065957045f), Float2Q(0.9091679831f), Float2Q(0.9117060320f),
    Float2Q(0.9142097557f), Float2Q(0.9166790599f), Float2Q(0.9191138517f), Float2Q(0.9215140393f),
    Float2Q(0.9238795325f), Float2Q(0.9262102421f), Float2Q(0.9285060805f), Float2Q(0.9307669611f),
    Float2Q(0.9329927988f), Float2Q(0.9351835099f), Float2Q(0.9373390119f), Float2Q(0.9394592236f),
    Float2Q(0.9415440652f), Float2Q(0.9435934582f), Float2Q(0.9456073254f), Float2Q(0.9475855910f),
    Float2Q(0.9495281806f), Float2Q(0.9514350210f), Float2Q(0.9533060404f), Float2Q(0.9551411683f),
    Float2Q(0.9569403357f), Float2Q(0.9587034749f), Float2Q(0.9604305194f), Float2Q(0.9621214043f),
    Float2Q(0.9637760658f), Float2Q(0.9653944418f), Float2Q(0.9669764710f), Float2Q(0.9685220943f),
    Float2Q(0.9700312532f), Float2Q(0.9715038909f), Float2Q(0.9729399522f), Float2Q(0.9743393828f),
    Float2Q(0.9757021300f), Float2Q(0.9770281427f), Float2Q(0.9783173707f), Float2Q(0.9795697657f),
    Float2Q(0.9807852804f), Float2Q(0.9819638691f), Float2Q(0.9831054874f), Float2Q(0.9842100924f),
    Float2Q(0.9852776424f), Float2Q(0.9863080972f), Float2Q(0.9873014182f), Float2Q(0.9882575677f),
    Float2Q(0.9891765100f), Float2Q(0.9900582103f), Float2Q(0.9909026354f), Float2Q(0.9917097537f),
    Float2Q(0.9924795346f), Float2Q(0.9932119492f), Float2Q(0.9939069700f), Float2Q(0.9945645707f),
    Float2Q(0.9951847267f), Float2Q(0.9957674145f), Float2Q(0.9963126122f), Float2Q(0.9968202993f),
    Float2Q(0.9972904567f), Float2Q(0.9977230669f), Float2Q(0.9981181129f), Float2Q(0.9984755806f),
    Float2Q(0.9987954562f), Float2Q(0.9990777278f), Float2Q(0.9993223846f), Float2Q(0.9995294175f),
    Float2Q(0.9996988187f), Float2Q(0.9998305818f), Float2Q(0.9999247018f), Float2Q(1.0000000000f)
};
/***********************************************************/
static q_t sin_LUT(q_t angle_0_90)
{
    u32     u32L_Index = angle_0_90 >> ANGLE_INDEX_SHIFT;
    u32     u32L_frac = angle_0_90 & ANGLE_FRAC_MASK;
    q_t     q_t_y0 = 0;
    q_t     q_t_y1 = 0;
    s64     s64_diff = 0;
    s64     s64_interp = 0;
    
    // 
    if (u32L_Index >= SIN_TABLE_LAST) {
        return sin_table[SIN_TABLE_LAST];
    }
    
    q_t_y0 = sin_table[u32L_Index];
    q_t_y1 = sin_table[u32L_Index+1];
    
    s64_diff = (s64)q_t_y1 - (s64)q_t_y0;
    s64_interp = (s64_diff*(s64)u32L_frac) >> ANGLE_INDEX_SHIFT;
    
    return (q_t)((s64)q_t_y0 + s64_interp);
}
/***********************************************************/
q_t get_sin(q_t angle)
{
    u32 u32L_Angle = (u32)angle & ANGLE_MASK;
    
    if (u32L_Angle < ANGLE_90) 
    {
        // 0 ~ pi/2
        return sin_LUT(u32L_Angle);
    }
    else if (u32L_Angle < ANGLE_180) 
    {
        // pi/2 ~ pi
        return sin_LUT(ANGLE_180 - u32L_Angle);
    } 
    else if (u32L_Angle < ANGLE_270) 
    {
        // pi ~ 3pi/2
        return -sin_LUT(u32L_Angle - ANGLE_180);
    } 
    else 
    {
        // 3pi/2 ~ 2pi
        return -sin_LUT(ANGLE_360 - u32L_Angle);
    }
}
/***********************************************************/
q_t get_cos(q_t angle)
{
    return get_sin(angle + ANGLE_90);
}
/***********************************************************/
void sin_test(void)
{
    
    unDebug.q_tData_U = get_sin(unDebug.q_tAngle);
    if(unDebug.q_tAngle+ANGLE_120 < ANGLE_360)
    {
        unDebug.q_tData_V = get_sin(unDebug.q_tAngle+ANGLE_120);
    }
    else
    {
        unDebug.q_tData_V = get_sin(unDebug.q_tAngle+ANGLE_120-ANGLE_360);
    }
    
    if(unDebug.q_tAngle+ANGLE_240 < ANGLE_360)
    {
        unDebug.q_tData_W = get_sin(unDebug.q_tAngle+ANGLE_240);
    }
    else
    {
        unDebug.q_tData_W = get_sin(unDebug.q_tAngle+ANGLE_240-ANGLE_360);
    }
    
    unDebug.q_tAngle += 10;
    if(unDebug.q_tAngle >= ANGLE_360)
    {
        unDebug.q_tAngle = 0;
    }
    
    clarke_3ph(unDebug.q_tData_U,unDebug.q_tData_V,unDebug.q_tData_W,&unDebug.q_tData_Alpha,&unDebug.q_tData_Beta);
    park(unDebug.q_tData_Alpha,unDebug.q_tData_Beta,ANGLE_360 - unDebug.q_tAngle,&unDebug.q_tData_Id,&unDebug.q_tData_Iq);

    unDebug.unSVPWM.Q_Ia = unDebug.q_tData_U*0.5;
    unDebug.unSVPWM.Q_Ib = unDebug.q_tData_V*0.5;
    unDebug.unSVPWM.Q_Ic = unDebug.q_tData_W*0.5;
    
    svpwm_get_duty(&unDebug.unSVPWM);
}


