#include <LPC21xx.H>

void spi_init(void)
{
	PINSEL0|= 0X1500;
	S0SPCCR=150;
	S0SPCR=(1<<5)|(3<<3);
	IODIR0|=1<<7;
}

unsigned char spio(unsigned char data)
{
	char clr;
	clr=S0SPSR;
	S0SPDR=data;
	while((S0SPSR&0x80)==0);
	return S0SPDR;

}
