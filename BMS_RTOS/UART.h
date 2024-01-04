#include <LPC214x.h>

int i=0;

void delayUART()
{
	for(int i=0; i<1000; i++);
}



void initTX0()
{
	PINSEL0 = (PINSEL0) | 0x05;
	
	U0LCR = 0x83;
	
	U0DLL = 0x62;
	U0DLM = 0x00;
	
	U0LCR = 0x03;
	
	U0THR = 0;
}



void TX0(char msg)
{
	U0THR = 0;
	
	while( (U0LSR & (1<< 5)) ==0 );
	U0THR = msg;
	delayUART();
}



void TX0_space()
{
	U0THR = 0;
	
	char sp[7] = ". . .";	
	
	i=0;
	while(sp[i] != '\0')
	{
		TX0(sp[i]);
		i++;
	}
}



void send_arrow()
{
	U0THR = 0;
	
	char a[3] = "-->";		
	
	i=0;
	while(a[i] != '\0')
	{
		TX0(a[i]);
		i++;
	}
}


void TX0_NL()
{
	char ch[5] = "\r\n\0";
	int ab=0;
	while(ch[ab] != '\0'){
	TX0(ch[ab]);
		ab++;
	}
}


void UART_start()
{
	char msg[20] = "Welcome to BMS" ;
	
	initTX0();
	
	for(int i=0; i<14 ; i++)
	{
		TX0(msg[i]);
		delayUART();
	}
}



void UART_msg()
{
	char msg1[30] = ". . .data sent on EEPROM . . ." ;
	
	initTX0();
	int a = 0;
	while(msg1[a] != '\0')
	{
		TX0(msg1[a]);
		delayUART();
		
		a++;
	}
}

//----------------------------------------------------------------------
void RX0()
{	
	U0LCR =0; U0DLL =0; U0DLM =0; U0LSR =0; U0THR =0; 
	
	unsigned int msg;
	
	U0LCR = 0x83;
	
	U0DLL = 0x62;
	U0DLM = 0;
	
	U0LCR = 0x03;
	
	U0RBR = 0;
	
	while( (U0LSR & (1)) ==0 );
	msg = U0RBR;
	delayUART();
}


/*
int main()
{ 
	while(1)
	{
		RX0();
		delay();
		TX0();
		delay();
	}
	return 0;
}
*/