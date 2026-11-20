/*****************************************************************/
#ifndef			__FOC_FSM_H
#define			__FOC_FSM_H
/*****************************************************************/
#include 	"DataTypeDef.h"
/*****************************************************************/
typedef struct
{
	u8		u8State;
	
	u8		F_Init;
	u16		u16WaitTime_1ms;
}FOCFSMData;
/*****************************************************************/
#define		C_FOC_INIT			0x00
#define		C_FOC_IDLE			0x10
#define		C_FOC_PRECHARGE		0x20
#define		C_FOC_ALIGN			0x30
#define		C_FOC_OPENLOOP		0x40
#define		C_FOC_RUN			0x50
#define		C_FOC_STOP			0x60
#define		C_FOC_FAULT			0x70


#define		C_FOC_INIT_WAIT		0x00
#define		C_FOC_INIT_CFG		0x01
#define		C_FOC_INIT_CALIB	0x02
#define		C_FOC_INIT_VERIF	0x03

/*****************************************************************/
extern void FOCFSM(void);
/*****************************************************************/

#endif
/*****************************************************************/

