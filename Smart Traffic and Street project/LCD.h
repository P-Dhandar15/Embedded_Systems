/*	Pin			LCD 1			LCD 2
		RS			P0.4			P0.21
		En			P0.6			P0.22
		Data		P0.8-15		P1.17-24
*/



#include <LPC214x.h>

void delayLCD()
{
	for(int i=0; i<60000; i++);
}

//---------------------------------------------------------------------------------------------------------------------	

void LCD1cmd(unsigned char cmd);
void LCD1data(unsigned char data);
void LCD1init();

void LCD2cmd(unsigned char cmd);
void LCD2data(unsigned char data);
void LCD2init();

//---------------------------------------------------------------------------------------------------------------------	

void LCD1cmd(unsigned char cmd)
{
	IOCLR0 = (IOCLR0) |(1<< 4);
	
		IOCLR0 = (IOCLR0) |(255 << 8);

	IOSET0 = (IOSET0) | (cmd << 8);
	
	IOSET0 = (IOSET0) | (1 << 6);
	delayLCD();
	IOCLR0 = (IOCLR0) | (1 << 6);
	
}

void LCD2cmd(unsigned char cmd)
{
	IOCLR0 = (IOCLR0) |(1<< 21);
	
		IOCLR1 = (IOCLR1) |(255 << 17);

	IOSET1 = (IOSET1) | (cmd << 17);
	
	IOSET0 = (IOSET0) | (1 << 22);
	delayLCD();
	IOCLR0 = (IOCLR0) | (1 << 22);
	
}

//---------------------------------------------------------------------------------------------------------------------	

void LCD1data(unsigned char data)
{
	IOSET0 = (IOSET0) |(1<< 4);
	
	IOCLR0 = (IOCLR0) |(255 << 8);

	
	IOSET0 = (IOSET0) | (data << 8);
	
	IOSET0 = (IOSET0) | (1 << 6);
	delayLCD();
	IOCLR0 = (IOCLR0) | (1 << 6);
}

void LCD2data(unsigned char data)
{
	IOSET0 = (IOSET0) |(1<< 21);
	
	IOCLR1 = (IOCLR1) |(255 << 17);

	
	IOSET1 = (IOSET1) | (data << 17);
	
	IOSET0 = (IOSET0) | (1 << 22);
	delayLCD();
	IOCLR0 = (IOCLR0) | (1 << 22);
}

//---------------------------------------------------------------------------------------------------------------------	

void LCD1init()
{
	LCD1cmd(0x38);
	LCD1cmd(0x0F);
	LCD1cmd(0x06);
	LCD1cmd(0x01);
	LCD1cmd(0x80);
}

void LCD2init()
{
	LCD2cmd(0x38);
	LCD2cmd(0x0F);
	LCD2cmd(0x06);
	LCD2cmd(0x01);
	LCD2cmd(0x80);
}
//---------------------------------------------------------------------------------------------------------------------	

void LCD1newLine()
{
	LCD1cmd(0xC0);
}

void LCD2newLine()
{
	LCD2cmd(0xC0);
}

//---------------------------------------------------------------------------------------------------------------------	

void LCD1clear()
{
	LCD1cmd(0x01);
	LCD1cmd(0x80);
}

void LCD2clear()
{
	LCD2cmd(0x01);
	LCD2cmd(0x80);
}


//---------------------------------------------------------------------------------------------------------------------	

void LCD1shiftLeft()
{
	LCD1cmd(0x18);
}

void LCD2shiftLeft()
{
	LCD2cmd(0x18);
}

//---------------------------------------------------------------------------------------------------------------------	

void LCD1shiftRight()
{
	LCD1cmd(0x1C);
}

void LCD2shiftRight()
{
	LCD2cmd(0x1C);
}

//---------------------------------------------------------------------------------------------------------------------	


void LCD1start()
{
	IODIR0 = (IODIR0) | 0x0000FFF0;
		LCD1init();

	int c=0;
	unsigned char p1[50] = "Welcome to.."; 
	unsigned char p2[50] = "Smart Road Safety Project";

	for(int i=0; p1[i] != '\0' ; i++)
	{
		LCD1data(p1[i]);
	}
	
	delayLCD();	delayLCD();
	LCD1clear();
	
	for(int i=0; p2[i] != '\0' ; i++)
	{
		LCD1data(p2[i]);
		c++;
		
		if(c == 11)
			LCD1newLine();
	}
	
}

void LCD2start()
{
	IODIR0 = IODIR0 | (1 << 21) | (1 << 22);
	IODIR1 = (IODIR1) | 0x01FE0000;
		LCD2init();

	int c=0;
	unsigned char p1[50] = "Welcome to.."; 
	unsigned char p2[50] = "Smart Road Safety Project";

	for(int i=0; p1[i] != '\0' ; i++)
	{
		LCD2data(p1[i]);
	}
	
	delayLCD();	delayLCD();
	LCD2clear();
	
	for(int i=0; p2[i] != '\0' ; i++)
	{
		LCD2data(p2[i]);
		c++;
		
		if(c == 11)
			LCD2newLine();
	}
	
}
//---------------------------------------------------------------------------------------------------------------------	

void LCD1text(unsigned char *sdat)
{
	while(*sdat) 
	{
		LCD1data(*sdat++);
	}
}

void LCD2text(unsigned char *sdat)
{
	while(*sdat) 
	{
		LCD2data(*sdat++);
	}
}

//---------------------------------------------------------------------------------------------------------------------	

