 #include <LPC21xx.H>
#include"can.h"
#include"delay.h"
#include"spi.h"
#include"adc.h"
#include"4bit_lcd.h"
int main()
{	
	int d1;
	can_m msg;
	float data;
	msg.id=69;
	msg.rtr=0;
	msg.dlc=4;
	msg.da=0;
	msg.db=0;
	can_init();
	lcd_init();
	spi_init();
	lcd_cmd(0x80);
	lcd_str("spi");
	while(1)
	{
		data=adc(0);
		d1=(data*100)/4096;
		data=(data*5.0)/4096;
		msg.da=d1;
		lcd_cmd(0x80);
		lcd_str("speed :");
		lcd_float(data);
		delay_ms(1000);
		lcd_cmd(0x01);
		can_tx(msg);
	}
	
}