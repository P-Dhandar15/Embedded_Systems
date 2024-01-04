//Analog to Digital Convertor 0

#include <LPC214x.h>

unsigned int ADC( int ch)
{
	unsigned int ADCval = 0;
	
	AD0CR = 0x00000000;
	AD0GDR = 0x00000000;
	
	AD0CR = (AD0CR) | (0x01 << ch);	// select channel
	AD0CR = (AD0CR) | (4 << 8);	  // Clock Div = 4.5Mhz
	AD0CR = (AD0CR) | (0x01 << 16);	// Burst Mode
	AD0CR = (AD0CR) | (0x01 << 21);	// PDN = 1
	
	AD0CR = (AD0CR) | (0x01 << 24);		// Start Conversion
	
	while( (AD0GDR & (0x01 << 31)) == 0 );
	
	//ADCval = AD0GDR;
	ADCval = ((AD0GDR >> 6) & 0x3FF );
	
	return ADCval;
	
	
}

/*
PINSEL1 = (0x01 << 24);		// AD0.1
PINSEL1 = (0x01 << 26);		// AD0.2
PINSEL1 = (0x01 << 28);		// AD0.3
*/
