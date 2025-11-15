#include <LPC21xx.H>
#include "can.h"
#include"delay.h"
#include "4bit_lcd.h"
#include "ultra.h"
 int main()
 {
 
 	float data; 
	can_m msg1;	
	 can_init();
	 lcd_init();
	 msg1.id=0x25;
	 msg1.rtr=0;
	 msg1.dlc=4;
	 msg1.da=0x0; 
	 msg1.db=0;
	 lcd_str("check");
	 delay_ms(1000);
	 while(1)
	 {
	   data=U_data();    
	   lcd_cmd(0x80);
	  lcd_str("distance : ");
		lcd_float(data);
		

		if(data==0)
		msg1.da=123;
		
		else if(data<15)
		msg1.da=0;

		else
		msg1.da=1;
		
		can_tx(msg1);

		delay_ms(500);
		
		
		
	 }				   
	  }

