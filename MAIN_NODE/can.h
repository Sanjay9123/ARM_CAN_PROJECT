#include <LPC21xx.H>

typedef unsigned int u32;

typedef signed int s32;

typedef unsigned char u8;

typedef signed char s8;

typedef unsigned short int u16;

typedef signed short int s16;

typedef struct can_msg
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 da;
	u32 db;
}can_m;

void can_init(void);

void can_tx(can_m);
void can_rx(can_m *msg);

