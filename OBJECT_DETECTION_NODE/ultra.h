#include <LPC21xx.H>



float U_data()
{
		   float dis,time;
           IODIR1 |=1<<31;
			   T1PR=15;

	    	  IOSET1=1<<31;

			  delay_us(10);

			  IOCLR1=1<<31;

			  while(((IOPIN1>>30)&1)==0);

			  T1TCR=1;

			  while(((IOPIN1>>30)&1)==1);

			  time=T1TC;

			  T1TCR=3;

			  T1TCR=0;	  

			  dis=time/58.0;
			  return dis;
}
