#include <LPC21xx.H>
#include "can.h"

void can_init(void)
{
	 PINSEL1|= 1<<14|1<<16;
	 C2MOD	=0X1;
	 C2BTR|=0X7;
	 AFMR=0x2;
	 C2MOD=0x0;
}

void can_tx(can_m msg1)
{
	C2TID1=msg1.id;
	C2TFI1=(msg1.dlc<<16);
	if(msg1.rtr==0)
	{
		C2TFI1&=~(1<<30);//RTR=0
		C2TDA1=msg1.da; //lower 4bytes of data
		C2TDB1=msg1.db;	
	}
	else
	{
		  C2TFI1|=(1<<30);
	}
	C2CMR=(1<<0)|(1<<5);
	while((C2GSR&(1<<3))==0);
}

void can_rx(can_m *msg)
{
  msg->id=C2RID;
  msg->dlc=((C2RFS>>16)&0x0f);
  msg->rtr=(C2RFS>>30)&1;
  if(msg->rtr==0)
  {
  	msg->da=C2RDA;
	msg->db=C2RDB;
  }
  C2CMR=(1<<2);
}


