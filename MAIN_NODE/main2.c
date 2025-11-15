#include <LPC21xx.H>
#include "delay.h"
#include "4bit_lcd.h"
#include "can.h"

can_m msg;

void can_interupt(void);
int ddata,ldata,sdata;

void can_isr()__irq
{
	int temp=C2ICR;	
    IOCLR0=1<<17;
	can_rx(&msg);
	if(msg.id==37)
	ddata=msg.da;
	if(msg.id==15)
	ldata=msg.da;
	if(msg.id==69)
	sdata=msg.da;
    VICVectAddr=0;
				
}

void pwm_init(void)
{
 PINSEL0=2<<16|2<<18;	//PIN 8 AND 9 
 PWMPR=150;
 PWMMR0=100;
 PWMMR4=0;
 PWMMR6=0;
 PWMLER=1<<0|1<<4|1<<6; // 
 PWMMCR=0X02;			   //RESET 	MR0
 PWMPCR=1<<14|1<<12;
 PWMTCR=1<<0|1<<4|1<<6;
}

int main()
{	
 	can_init();
	lcd_init();
	pwm_init();
	IODIR0|=1<<17;
	delay_ms(1000);
	IOSET0=1<<17;
	can_interupt();

	while(1)
	{	
			lcd_cmd(0x80);
			lcd_str("light : ");
			lcd_int(ldata);	
			lcd_data('%');
			lcd_cmd(0xc0);
			lcd_str("ob: ");
			lcd_int(ddata);
			lcd_cmd(0xc7);
			lcd_str("sp: ");
			lcd_int(sdata);
			PWMMR4=ldata;
			PWMMR6=sdata;
			PWMLER=1<<0|1<<4|1<<6;						
	}
	}

void can_interupt()
{
	VICVectCntl0=0x20|27;
	VICVectAddr0=(int)can_isr;
    C2IER=1<<0;
	VICIntEnable =1<<27;
}



