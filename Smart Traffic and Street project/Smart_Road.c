//--- RTOS IMPLEMENTATION ---

#include <LPC214x.h>
#include <stdio.h>
#include "LCD.h"
#include "ADC.h"


void task1(void *a);
void task2(void *b);

void delay()
{
	for(int x=0; x<1000; x++)
		for(int y=0; y<2000; y++);
}

