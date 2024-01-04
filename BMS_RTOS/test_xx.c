#include <LPC214x.h>
#include <string.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "ADC.h"
#include "UART.h"
#include "LCD.h"
#include "GPIO.h"
#include "EEPROM.h"

//---------------------------------------------------------------------------

void delayms();
void wmsg();

void readData_t1(void *r);			// task 1
void control_t2(void *p);			  // task 2
void show_t3(void *l);					// task 3


//--------------------------------------------------------------------------

unsigned int in, out, tp;
float vtgIN, vtgOUT, Temp, SOC;
char vtgIN_str[20], vtgOUT_str[20], Temp_str[20], SOC_str[20];
	
char str1[20] = "Output Voltage";
char str3[20] = "Temperature";
char str4[20] = "SOC";
	 
char msg2[20] = "Battrey full ";
char msg3[30] = "Battery temperature high";
char msg4[20] = "Charging on";
	 
int x = 0 , n = 0;

//---------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

void readData_t1(void *r)			// task 1
{
	while(1){
		
	out = ADC(1);												// P0.28 -- AD0.1 -- CN14.13
				
	vtgOUT = ( (out/660.0) * 12 );				// output Voltage
	
	
	tp = ADC(2);											// P0.29 -- AD0.2 -- CN13.3
				
	Temp = ((tp * 3.3)/100);							// Temperature
	}	
}

//---------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

void control_t2(void *p)			  // task 2
{
	// Dicision Making---------------------------------------------------------	
			
		LCDclear();		TX0_NL();		TX0_space();		TX0_NL();
		
		//if( (vtgOUT > 12) || (Temp > 30) )
		
		if ( vtgOUT >= 12 )
		{
				pinWrite(0, 12, 0);								// relay = 0;
			
			x = 0;
			while (msg2[x] != '\0') 
		{
        LCDdata(msg2[x]);			// lcd <-- Battrey full
				TX0(msg2[x]);
        x++;  
		}
			delayms();
			//RR(x);
		
		LCDclear();		TX0_NL();		TX0_space();
		}
//--------------------------------------------------------
		
		else if( Temp > 35 )
		{
				pinWrite(0, 12, 0);								// relay = 0;
				
				x = 0;
			while (msg3[x] != '\0') 
		{
        LCDdata(msg3[x]);			// lcd <-- Battery temperature high 
				TX0(msg3[x]);
        x++;  
		}
			delayms();
			RR(x);		delayms();
		
			LCDclear();		TX0_NL();		TX0_space();
		}
//---------------------------------------------------------
			
		else{
				pinWrite(0, 12, 1);							//relay = 1;
				
				x = 0;
			while (msg4[x] != '\0') 
		{
        LCDdata(msg4[x]);				// lcd <-- Charging on
				TX0(msg4[x]);
        x++;  
		}
			delayms();
		
			LCDclear();		TX0_NL();		TX0_space();		TX0_NL();
		}
}

//---------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

void show_t3(void *l)						// task 3
{
	// OUTPUT Voltage ------------------------------------------------

			LCDclear();		TX0_NL();		TX0_space();		TX0_NL();
		
			n=0;
			while(str1[n] != '\0') 
		 {
				LCDdata(str1[n]);		
				TX0(str1[n]);
				n++;	}
		 print_arrow();			send_arrow();
	
	sprintf(vtgOUT_str, "%.2f", vtgOUT);
	
	 x = 0;
  while (vtgOUT_str[x] != '\0') 
		{
        LCDdata(vtgOUT_str[x]);			// Send O/p vtg to LCD
			  TX0(vtgOUT_str[x]);					// Send O/p vtg to TX0
        x++;  
		}
			I2Csend(vtgOUT);			UART_msg();
	delayms();
		
		
		
// Temperature ----------------------------------------------- 
		
		LCDclear();		TX0_NL();		TX0_space();		TX0_NL();
		
				n=0;
			while(str3[n] != '\0') 
		 {
				LCDdata(str3[n]);		
				TX0(str3[n]);
				n++;	}
		 print_arrow();			send_arrow();
		
	sprintf(Temp_str, "%.2f", Temp);
		
	 x = 0;
  while (Temp_str[x] != '\0') 
		{
        LCDdata(Temp_str[x]);					// Send Temperature to LCD
			  TX0(Temp_str[x]);					// Send Temperature to TX0

        x++;  
		}
			I2Csend(Temp);				UART_msg();
	delayms();
		
		
// Calculations --------------------------------------------------------------
			
	SOC = ( vtgOUT / 12) *100;
		
	//SOH = (present_cond / ideal_cond) *100 ;
	
		sprintf(SOC_str, "%.2f", SOC);
		
				LCDclear();		TX0_NL();	
		
				n=0;
			while(str4[n] != '\0') 
		 {
				LCDdata(str4[n]);		
				TX0(str4[n]);
				n++;	}
		 
				LCDnewLine();		print_arrow();		send_arrow();
		
		x = 0;
	while (SOC_str[x] != '\0') 
		{
        LCDdata(SOC_str[x]);			// Send State of Charge % to LCD
				TX0(SOC_str[x]);
        x++;  
		}
		char percent[1] = "%"; 
		LCDdata(percent[0]);
		
			I2Csend(SOC);				UART_msg();		
	delayms();
		
}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

int main()
{
	UART_start();	
	
	LCDstart();
	
	EEPROM_start();
	
	LCDclear();	
	TX0_NL();
	
	wmsg();
	
	LCDclear();	
	TX0_NL();			TX0_space();		TX0_NL();

	
	PINSEL1 = (PINSEL1) | (0x05000000);			// set P0.28->AD0.1		P0.29->AD0.2
	
//---------------------------------------------------------------
	
	xTaskCreate(readData_t1,"task1",128,NULL,3,NULL);
	xTaskCreate(control_t2,"task2",128,NULL,2,NULL);
	xTaskCreate(show_t3,"task3",128,NULL,1,NULL);
	
	vTaskStartScheduler();
}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

void delayms()
{
		for(int i=0; i<1000; i++)
			for(int j=0; j<30000; j++);
}
//--------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

void wmsg()
{
	char a[10] = " wait..." ;
	int o=0;
	
	while(a[o] != '\0') {
	LCDdata(a[o]);
	TX0(a[o]);
	o++;	}
	
	unsigned int q = 54321;
	int n1=0;
	char num[20];
	
	sprintf(num, "%d", q);
	while(num[n] != '\0') {
				LCDdata(num[n]);		
				TX0(num[n]);
				n++;	}
}
//--------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
