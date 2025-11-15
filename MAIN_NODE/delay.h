#include <LPC21xx.H>
 
 void delay_sec(int sec);
 void delay_ms(int ms);
 void delay_us(int us);

 void delay_sec(int sec)	
{		 
T0PR=15000000-1	 ;
T0TCR=0X01;
while(T0TC<sec);
T0TCR=0x03;
T0TCR=0X00;
}

void delay_ms(int ms)
{
T0PR=15000-1	 ;
T0TCR=0X01;
while(T0TC<ms);
T0TCR=3;	 
T0TCR=0X00;
}

void delay_us(int us)
{
T0PR=15-1	 ;
T0TCR=1;
while(T0TC<us);
T0TCR=0X03;
T0TCR=0X00;
} 









