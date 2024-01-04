#include <reg51.h>

void delay();

sbit k1=P1^0;			//initialize input pins
sbit k2=P1^1;
sbit k3=P1^2;
sbit k4=P1^3;

sbit d0=P0^4;			//initialize output pins
sbit d1=P0^5;
sbit d2=P0^6;
sbit d3=P0^7;


void main()
{
  while(1)
	{
		if(k1==1)
			d0=1;
		if(k1==0)
			d0=0;
		
		delay();
		
		if(k2==1)
			d1=1;
		if(k2==0)
			d1=0;
		
		delay();
		
		if(k3==1)
			d2=1;
		if(k3==0)
			d2=0;
		
		delay();
		
		if(k4==1)
			d3=1;
		if(k4==0)
			d3=0;	
		
		delay();
		}
	}
void delay() 		//50ms delay
{
	TMOD=0x01;    
	TH0=0x4B;
	TL0=0xFE;
	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
}