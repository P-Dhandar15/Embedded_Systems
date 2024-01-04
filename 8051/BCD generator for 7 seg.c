#include <reg51.h>

void delay();

sbit Po=P0 ;

void main()
{
	while(1)
	{
		Po = 0X00;
		delay();
		
		Po = 0X01;
		delay();
		
		Po = 0X02;
		delay();
		
		Po = 0X03;
		delay();
		
		Po = 0X04;
		delay();
		
		Po = 0X05;
		delay();
		
		Po = 0X06;
		delay();
		
		Po = 0X07;
		delay();
		
		Po = 0X08;
		delay();
		
		Po = 0X09;
		delay();
	
	}
	
}

void delay()
{
	TMOD = 0X01;
	TH0 = 0XFF;				//10 MS
	TL0 = 0XA3;
	TR0 = 1;
	
	while(TF0==0);
	TR0 = 0;
	TF0 = 0;
}