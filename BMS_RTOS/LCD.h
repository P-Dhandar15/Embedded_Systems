#include <LPC214x.h>

void delayLCD()
{
	for(int i=0; i<500000; i++);
}

void delayLCD2()
{
	for(int i=0; i<900000; i++);
}


void LCDcmd(unsigned char cmd);
void LCDdata(unsigned char data);
void LCDinit();
void LCDnewLine();
void RR(int x);

void LCDcmd(unsigned char cmd)
{
	IOCLR0 = (IOCLR0) |(1<< 11);					// RS =0
	
	IOCLR0 = (IOCLR0) |(1<< 20);					// RW =0
	
		IOCLR1 = (IOCLR1) |(255 << 16);

	IOSET1 = (IOSET1) | (cmd << 16);
	
	IOSET0 = (IOSET0) | (1 << 10);
	delayLCD();
	IOCLR0 = (IOCLR0) | (1 << 10);
	
}

void LCDdata(unsigned char data)
{
	IOSET0 = (IOSET0) |(1<< 11);
	IOCLR0 = (IOCLR0) |(1<< 20);				
	
	IOCLR1 = (IOCLR1) |(255 << 16);

	
	IOSET1 = (IOSET1) | (data << 16);
	
	IOSET0 = (IOSET0) | (1 << 10);
	delayLCD2();
	IOCLR0 = (IOCLR0) | (1 << 10);
}


void LCDinit()
{
	IODIR0 = (IODIR0) | 0x00100C00;
	IODIR1 = (IODIR1) | 0x00FF0000;
	
	LCDcmd(0x38);
	LCDcmd(0x0F);
	LCDcmd(0x06);
	LCDcmd(0x01);
	LCDcmd(0x80);
}

void LCDnewLine()
{
	LCDcmd(0xC0);
}
void LCDclear()
{
	LCDcmd(0x01);
	LCDcmd(0x80);
}
void LCDshiftLeft()
{
	LCDcmd(0x18);
}
void LCDshiftRight()
{
	LCDcmd(0x1C);
}


void LCDstart()
{
		LCDinit();
	int i =0;

	unsigned char p1[20] = "Welcome to BMS" ;
	unsigned char p2[50] = "Battery Management System" ;

	for(i=0; p1[i] != '\0' ; i++)
	LCDdata(p1[i]);
	delayLCD();
	
	LCDnewLine();
	
	for(i=0; p2[i] != '\0' ; i++)
	LCDdata(p2[i]);
	delayLCD();
	RR(i);
}

void print_arrow()
{
	char a[5] = "-->";
	int i=0;
	LCDcmd(0xC0);
	
	while(a[i] != '\0')
	{
		LCDdata(a[i]);
		i++;
	}
}

void RR(int x)
{
	int j=0;
	for(j=0; j<x; j++) {
			LCDcmd(0x18);
			delayLCD2();
	}
}