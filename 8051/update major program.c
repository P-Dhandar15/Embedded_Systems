#include <reg51.h>

void delay();

sbit sm=P0^7;   	    			 //Port 0 pin 7= Soil moisture

sbit rs=P0^3;   	    			//Port 0 pin 3= Rain sensor

sbit motor=P1^1;  					//Port 1 Pin 1= Motor output 

//----------------------------------------------------------------------------

void main()
{
 while(1)
 {	
	 if(sm == 1)
   {
     motor=1;
   }
   else if(sm == 0)
   {
      motor=0;
   }
	 else 
   { 
     motor=0;
   }

    while(rs == 0)
    {
      motor = 0;
		}
	 
	 delay();
 }
}

void delay()
{
 TMOD = 0x01;
 TH0 = 0xFF;
 TL0 = 0xF6;					// 10 us delay
 TR0 = 1;
	
 while(TF0==0);
 TR0 =0;
 TF0 =0;
}
		