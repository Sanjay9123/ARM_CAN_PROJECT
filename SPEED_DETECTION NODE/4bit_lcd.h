

#include <LPC21xx.H>

#define pin 0x0f<<20
#define rs  1<<17
#define en	1<<19
#define rw  1<<18


typedef unsigned char u8;
void lcd_int(int );
void lcd_str(char *);
void lcd_init(void);
void lcd_cmd(u8);
void lcd_data(u8 data);
void lcd_init()
{
	IODIR1 =rs|en|rw|pin;
	
	
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
   	lcd_cmd(0x28);
	lcd_cmd(0x80);
	
}				 

void lcd_cmd(u8 data)
{  
	IOCLR1=rs;

   IOCLR1=pin;
   IOSET1=(data&0xf0)<<16;   
   IOSET1=en;
   delay_ms(2);
   IOCLR1=en;

   IOCLR1=pin;
   IOSET1=(data&0x0f)<<20;
   IOSET1=en;
   delay_ms(2);
   IOCLR1=en;
	
} 

void lcd_data(u8 data)
{
	 IOSET1=rs;

   IOCLR1=pin;
   IOSET1=(data&0xf0)<<16; 
   IOSET1=en;
   delay_ms(2);
   IOCLR1=en;

   IOCLR1=pin;
   IOSET1=(data&0x0f)<<20;
   IOSET1=en;
   delay_ms(2);
   IOCLR1=en;
} 

void lcd_str(char *s)
{
	while(*s)
	{
	  lcd_data(*s++);
	}
}

void lcd_int(int a)
{
	unsigned char b[100];
	int i=0;
	if(a==0)
	lcd_data(48);	

	if(a<0)
	{
	  lcd_data('-');
	  a=-a;
	}
	while(a)
	{
		b[i++]=a%10;
		a/=10;
	}
	for(i--;i>=0;i--)
	lcd_data(b[i]+48);
	
}

void lcd_float(float a)
{
    int b=a;
	lcd_int(b);
	lcd_data('.');
	lcd_int((a-b)*100);
	

}
	

	
	
	
	
	
						  