#include <LPC214x.h>
#include <stdio.h>
#include "LCD.h"
#include "ADC.h"

void delay()
{
	for(int x=0; x<1000; x++)
		for(int y=0; y<2000; y++);
}

int main()
{
	LCD1start();		LCD2start();
					delayLCD();
	LCD1clear();		LCD2clear();
	
	unsigned int LDR, pir1, pir2, pir3, pir4, speed;
	unsigned char LDRstr[10], SPEEDstr[10];
		
		IODIR1 = ( IODIR1 | 0xFF010000 );					// output
		IODIR0 = ( IODIR0 | (~ 0x0001000F) );			// input
	
//---------------------------------------------------------------------------------------------------------------------	

	while(1) {
	
	LDR = IOPIN0;		LDR = ((LDR >> 16) & 0x00000001);
	
	if(LDR >= 1)
	{
		IOSET1 = (IOSET1 | (1 << 16));
		/*
		LCDclear();
		LCDtext("Lights On");
		delayLCD();							*/
	}
	
	else
	{
		IOCLR1 = (IOCLR1 | (1 << 16));
		/*
		LCDclear();
		LCDtext("Lights Off");
		delayLCD();							*/					
	}			
		
	
//---------------------------------------------------------------------------------------------------------------------	

	pir1 = IOPIN0;		pir1 = (( pir1 >> 0) & 0x00000001);		 // Yellow 1 <-- 31
	pir2 = IOPIN0;		pir2 = (( pir2 >> 1) & 0x00000001);		 // Red 1 		<-- 30
	pir3 = IOPIN0;		pir3 = (( pir3 >> 2) & 0x00000001);		 // Yellow 2 <-- 29
	pir4 = IOPIN0;		pir4 = (( pir4 >> 3) & 0x00000001);		 // Red 1 		<-- 28
	
	// Green 1 <-- 27		;		Green 2 <-- 26
	
	
	 if((pir1 == 1) && (pir3 == 1))
	{
		IOSET1 = IOSET1 | (1 << 31);	// Yellow 1
		IOSET1 = IOSET1 | (1 << 29);	// Yellow 2
		IOCLR1 = IOCLR1 | (1 << 30) | (1 << 28) | (1 << 27) | (1 << 26);
		
		LCD1clear();									LCD2clear();
		LCD1text("Slow Down..!");			LCD2text("Slow Down..!");
													delayLCD();
		LCD1clear();										LCD2clear();
		LCD1text("Vehicle on other ");	LCD2text("Vehicle on other ");
		LCD1newLine();									LCD2newLine();
		LCD1text("Side");								LCD2text("Side");
		
		delay();
	}
	
	else if((pir2 == 1) && (pir4 == 1))
	{
		IOSET1 = IOSET1 | (1 << 30);	// Red 1
		IOSET1 = IOSET1 | (1 << 28);	// Red 2
		IOCLR1 = IOCLR1 | (1 << 31) | (1 << 29) | (1 << 27) | (1 << 26);
		
		LCD1clear();												LCD2clear();
		LCD1text("Stop..!");								LCD2text("Stop..!");
												delayLCD();
		LCD1clear();												LCD2clear();
		LCD1text("Vehicle on other ");			LCD2text("Vehicle on other ");
		LCD1newLine();											LCD2newLine();
		LCD1text("Side");									LCD2text("Side");
		
		delay();
	}
	
		else if((pir1 == 1) && (pir4 == 1))
	{
		IOSET1 = IOSET1 | (1 << 31);	// Yellow 1
		IOSET1 = IOSET1 | (1 << 29);	// Yellow 2
		IOCLR1 = IOCLR1 | (1 << 30) | (1 << 28) | (1 << 27) | (1 << 26);
		
		LCD1clear();													LCD2clear();
		LCD1text("Stop..!");									LCD2text("Stop..!");
												delayLCD();
		LCD1clear();													LCD2clear();
		LCD1text("Vehicle on other ");				LCD2text("Vehicle on other ");
		LCD1newLine();												LCD2newLine();
		LCD1text("Side 1");									LCD2text("Side 1");
		
		delay();
	}
	
	else if((pir2 == 1) && (pir3 == 1))
	{
		IOSET1 = IOSET1 | (1 << 30);	// Red 1
		IOSET1 = IOSET1 | (1 << 28);	// Red 2
		IOCLR1 = IOCLR1 | (1 << 31) | (1 << 29) | (1 << 27) | (1 << 26);
		
		LCD1clear();														LCD2clear();
		LCD1text("Slow Down..!");								LCD2text("Slow Down..!");
														delayLCD();
		LCD1clear();														LCD2clear();
		LCD1text("Vehicle on other ");					LCD2text("Vehicle on other ");
		LCD1newLine();													LCD2newLine();
		LCD1text("Side 2");										LCD2text("Side 2");
	}
	
	else if(pir1 == 1) {
		IOSET1 = IOSET1 | (1 << 31) | (1 << 29) ;	// yellow.1
		IOCLR1 = IOCLR1 | (1 << 30) | (1 << 28) | (1 << 27) | (1 << 26);
		
		LCD1clear();														LCD2clear();
		LCD1text("Go Slow..!");								LCD2text("Go Slow..!");
													delayLCD();
		LCD1clear();														LCD2clear();
		LCD1text("Vehicle on");								LCD2text("Vehicle on");
		LCD1newLine();													LCD2newLine();
		LCD1text("Side 1");										LCD2text("Side 1");
		
		delay();
	}
	
	else if(pir2 == 1) {
		IOSET1 = IOSET1 | (1 << 30) | (1 << 26);	// red.1
		IOCLR1 = IOCLR1 | (1 << 31) | (1 << 29) | (1 << 28) | (1 << 27) ;
		
		LCD1clear();													LCD2clear();
		LCD1text("Wait..!");									LCD2text("Wait..!");
													delayLCD();
		LCD1clear();													LCD2clear();
		LCD1text("Vehicle comming");					LCD2text("Vehicle comming");
		LCD1newLine();												LCD2newLine();
		LCD1text("from Side 1");							LCD2text("from Side 1");
		
		delay();
	}
	
	else if(pir3 == 1) {
		IOSET1 = IOSET1 | (1 << 29) | (1 << 31);	// yellow.2
		IOCLR1 = IOCLR1 | (1 << 30) | (1 << 28) | (1 << 27) | (1 << 26);
		
		LCD1clear();													LCD2clear();
		LCD1text("Go Slow..!");								LCD2text("Go Slow..!");
														delayLCD();
		LCD1clear();													LCD2clear();
		LCD1text("Vehicle on");								LCD2text("Vehicle on");
		LCD1newLine();												LCD2newLine();
		LCD1text("Side 2");										LCD2text("Side 2");
		
		delay();
	}
	
	else if(pir4 == 1) {
		IOSET1 = IOSET1 | (1 << 28) | (1 << 27);	// red.1
		IOCLR1 = IOCLR1 | (1 << 31) | (1 << 30) | (1 << 29) | (1 << 26);
		
		LCD1clear();												LCD2clear();
		LCD1text("Wait..!");								LCD2text("Wait..!");
												delayLCD();
		LCD1clear();												LCD2clear();
		LCD1text("Vehicle comming");				LCD2text("Vehicle comming");
		LCD1newLine();											LCD2newLine();
		LCD1text("from Side 2");						LCD2text("from Side 2");
		
		delay();
	}
	

	
	else {
		IOSET1 = IOSET1 | (1 << 27);	// green
		IOSET1 = IOSET1 | (1 << 26);	// green
		IOCLR1 = IOCLR1 | (1 << 31) | (1 << 30) | (1 << 29) | (1 << 28) ;
		
		LCD1clear();										LCD2clear();
		LCD1text("Green Go..!");				LCD2text("Green Go..!");
		LCD1newLine();									LCD2newLine();
		LCD1text("Stay Safe :)");				LCD2text("Stay Safe :)");	
		
		IOCLR1 = (IOCLR1 | (1 << 16));
		
		delay();	
		
	} 
	
	}	
}



	/*
	//-----------ADC---------------------------
	
	PINSEL1 = (0x01 << 24);		// AD0.1 <-- LDR
	
	LDR = ADC(1);
	
	IODIR1 = IODIR1 | (1 << 16);
	
	if(LDR > 512)
		IOSET1 = IOSET1 | (1 << 16);
	
	else
		IOCLR1 = IOCLR1 | (1 << 16);
	
	sprintf(LDRstr , "%d" , LDR);
	
	LCDtext("Light Sensitivity");
	LCDshiftLeft();	LCDshiftLeft(); 
	LCDnewLine();
	LCDtext(":-");
	
	int c=0;
	while(LDRstr[c] != '\0')
		LCDdata(LDRstr[c]);
		
	*/



/*
IODIR0 = ( IODIR0 | 0x00000000 );
	
	pir1 = ( IOPIN0 >> 1 ) & 0x00000001;	// yellow.1
	pir2 = ( IOPIN0 >> 2 ) & 0x00000001;	// red.1
	pir3 = ( IOPIN0 >> 3 ) & 0x00000001;	// yellow.2
	pir4 = ( IOPIN0 >> 4 ) & 0x00000001;	// red.2
		
	if(pir1 == 1) {
		pinWrite(1, 31, 1);
		multiWrite(1, 26, 30, 0);
	}
	
	if(pir2 == 1) {
		pinWrite(1, 30, 1);
		multiWrite(1, 26, 29, 0);
		pinWrite(1, 31, 0);
	}
	
	if(pir3 == 1) {
		pinWrite(1, 29, 1);
		multiWrite(1,26, 28, 0);
		multiWrite(1, 30, 31, 0);
	}
	
	if(pir4 == 1) {
		pinWrite(1, 28, 1);
		multiWrite(1, 26, 27, 0);
		multiWrite(1, 27, 31, 0);
	}
	
	else {
		multiWrite(1, 26, 27, 1);
		multiWrite(1, 28, 31, 0);
	}
*/