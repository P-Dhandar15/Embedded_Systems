#include <reg51.h>

void delay();

sbit sm=P0^7;   	    			 //Port 0 pin 7= Soil moisture

sbit rs=P0^3;   	    			//Port 0 pin 3= Rain sensor

sbit esp_motor=P2^0;  	    //Port 2 Pin 0= ESP_data pin input

sbit esp_cont=P2^2;					//Port 2 pin 2= Aoto/Manual control signal

sbit rsout=P2^4;						//Port 2 pin 4= Rain sensor to Esp

sbit motor=P1^1;  					//Port 1 Pin 1= Motor output 

//----------------------------------------------------------------------------

void main()
{
 while(1)
 {
  if(esp_cont == 1)							//esp_data
	{ 
		esp_motor = 0;
			
			if(sm == 1)     					//Soil moisture 
			{
				motor=1;    } }

   
  
    else if(esp_cont == 0)     	//esp_data
  {
		if(esp_motor == 1)
		{
			motor=1;    } }
	 
	
	else if(rs == 0)      			//Rain sensor
  {
    motor=0;  
		rsout=1;   }

    else                			//else off
  {
    motor=0; 
		rsout=0;    }
	
	delay();									//10 us delay
 }
}

//--------------------------------------------------

void delay()
{
 TMOD= 0x01;
 TH0 = 0xFF;
 TL0 = 0xF6;					// 10 us delay
 TR0 = 1;
	
 while(TF0==0);
 TR0 =0;
 TF0 =0;
}
