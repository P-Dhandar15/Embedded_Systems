#include<reg51.h>

void main()
{	
	unsigned char seg[]={0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
	unsigned char x;
	unsigned int i;
	
	P0=0x00;
	
	while(1)
	{	
		for(x=0; x<10; x++)
		{	
			P0=seg[x];
			
			for(i=0; i<60000; i++);
		
		}	
	}
}