#include <LPC21xx.H>
#include "ultrasonic.h"
 #include"delay.h"
void ultra_init(void)
{
	IODIR0|=trig;
}

void send(void)
{
		      IOSET0=trig;

			  delay_us(10);

			  IOCLR0=trig;
}


float ultra_data(void)
{ 
  int i=0;			
  float time=0,dis;	    
  T1PR=15;

  send();

  while(((IOPIN0>>20)&1)==0)
  {
	if((i++)>1200000)
	return 200;
  }

T1TCR=1;
i=0;
while(((IOPIN0>>1)&1)==1)
{
	if((i++)>12000000)
	return 500;
  }

time=T1TC;

T1TCR=3;

T1TCR=0;	  

dis=time/58.0;


return dis;
}
