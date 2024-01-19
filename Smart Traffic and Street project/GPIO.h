/* Driver for GPIO pins to Write and Read values...

 portWrite ( port_Num, value )
 pinWrite ( port_Num, pin_Num, Value )
 multiWrite (port_num, pin_first, pin_last, value)
 
 portRead ( port_Num )
 pinRead ( port_Num, pin_Num )
 multiRead (port_Num, pin_first, pin_last)

 */
 #include<LPC214x.h>
 
// write a whole PORT 

 void portWrite( int port_Num, int value )
 {
		if( port_Num == 0)						// Port 0
		{
			IODIR0 = 0XFFFFFFFF;
			
			if(value == 0){
				IOCLR0 = 0xFFFFFFFF;			// Write '0'
			}
			else{
				IOSET0 = 0xFFFFFFFF;			// Write '1'
			 }
		}
		else if( port_Num == 1)				// Port 1
		{
			IODIR1 = 0XFFFFFFFF;
			
			if(value == 0){
				IOCLR1 = 0xFFFFFFFF;			// Write '0'
			}
			else{
				IOSET1 = 0xFFFFFFFF;			// Write '1'
			 }
		}
 }
 
 
 
// write on specific Pin of any Port
 
 void pinWrite( int port_Num, int pin_Num, int value )
 {
		if( port_Num == 0)													// Port 0
		{
			IODIR0 = (IODIR0) | (1 << pin_Num);
			
			if(value == 0){
			IOCLR0 = (IOCLR0) | (1 << pin_Num);		// Write '0'
			}
			else{
			IOSET0 = (IOSET0) | (1 << pin_Num);		// Write '1'
			 }
		}
		else if( port_Num == 1)											// Port 1
		{
			IODIR1 = (IODIR1) | (1 << pin_Num);
			
			if(value == 0){
			IOCLR1 = (IOCLR1) | (1 << pin_Num);		// Write '0'
			}
			else{
			IOSET1 = (IOSET1) | (1 << pin_Num);		// Write '1'
			 }
		}
 }
 
 
// write on multiple Pins of any Port at a time
 
  void multiWrite (int port_Num, int pin_first, int pin_last, int value)
	{
			if(port_Num == 0) {													// Port 0
				
				for(int i= pin_first; i<= pin_last; i++)
				{
					IODIR0 = (IODIR0) | (1 << i);
				}
				if(value == 0)
				{
					for(int i= pin_last; i<= pin_first; i--) {
						IOCLR0 = (IOCLR0) | (1 << i);							// Write '0'
					}
				}
				else {
						for(int i= pin_last; i<= pin_first; i--) {
								IOSET0 = (IOSET0) | (1 << i);					// Write '1'
						 }
					}
			}
			
				else if(port_Num == 1) {								// Port 1
				
				for(int i= pin_first; i<= pin_last; i++)
				{
					IODIR1 = (IODIR1) | (1 << i);					
				}
				if(value == 0)
				{
					for(int i= pin_first; i<= pin_last; i++) {
						IOCLR1 = (IOCLR1) | (1 << i);							// Write '0'
					}
				}
				else {
						for(int i= pin_first; i<= pin_last; i++) {
								IOSET1 = (IOSET1) | (1 << i);					// Write '1'
						 }
				}
			}
	}

// Read whole Port
 
 unsigned int portRead ( int port_Num )
 {
		unsigned int data;
	 
		if(port_Num == 0) {						// Read Port 0
			IODIR0 = (IODIR0) & 0x00000000;
			data = IOPIN0;
		}
		else if(port_Num == 1) {			// Read Port 1
			IODIR1 = (IODIR1) & 0x00000000;
			data = IOPIN1;
		}
		
		return data;
 }
 
 
// Read specific Pin of any Port
 
	unsigned int  pinRead ( int port_Num, int pin_Num )
 {
		unsigned int data;

		if(port_Num == 0) {												// Read Port 0
			IODIR0 = (IODIR0) | (0 << pin_Num);
			data = IOPIN0;
		}
		else if(port_Num == 1) {									// Read Port 1
			IODIR1 = (IODIR1) | (0 << pin_Num);
			data = IOPIN1;
		}
		
		return data;
 }
 
	
// Read multiple Pins of any Port
 
	unsigned int multiRead (port_Num, pin_first, pin_last)
	{
		unsigned int data;
		
		if(port_Num == 0) 													// Read Port 0
			{
				for(int i= pin_first; i<= pin_last; i++)
				{
					IODIR0 = (IODIR0) | (0 << i);
				}
				data = IOPIN0;
			}
		else if(port_Num == 1)										// Read Port 1
		{
			for(int i= pin_first; i<= pin_last; i++)
			{
				IODIR1 = (IODIR1) | (0 << i);
			}
			data = IODIR1;
		}
		
		return data;
	}