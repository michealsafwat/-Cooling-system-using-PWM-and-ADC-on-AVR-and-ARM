#include "MACROS_ADC_PWM.h"


	
	
	int main()
 {
		
			int adc_data;		// variable to hold the return data after conversion
			int temp,t;
			IODIR0=0x1F;			//enable p0.0 to P0.4 as output while P0.5 as input as it is a button
		
		
			ADC0_Init();  // initiallize ADC0
			pwm_init();    // initiallize pwm          
                      
		while (1)
  {
				adc_data = ADC0_Read();			// get the value of the data after conversion
				
		
	
				temp = adc_data * Volts_To_Temp;   	//  temp will hold the value of the measured temperature
		
		if (temp<20){
					
		PWMMR1 	=0;							//if temp is less than 20 the motor won't operate
		PWMLER	= (1<<1);					// update PWMMR1 
		IO0PIN |=(1<<1)|(1<<4);		// Green LED on and buzzer is off(buzzer is active low)
	
	}
		
	else if(temp==20)
	{
			PWMMR1 	= MINIMUM_SPEED ; 	  // if temp is equal 20 degrees then the motor(Fan) is on with minimum speed
			PWMLER	= (1<<1);							// update PWMMR1 
			IO0PIN |=(1<<2)|(1<<4);			//Yellow LED is on and Green LED and buzzer are off (buzzer is active low)			
	}
		else if (20< temp && temp < 40){
						
						PWMMR1 	= temp*SPEED;				// at this range of temperature the speed increases gradually in proporion with temp
						PWMLER	= (1<<1);						// update PWMMR1 
						IO0PIN |=(1<<2)|(1<<4);			//Yellow LED is on and Green LED and buzzer are off (buzzer is active low)							
		}
		else if (temp>=40)
		{					
			  PWMMR1 	=MAXIMUM_SPEED;		// if temp is equal 40 degrees or higher then the motor(Fan) is on with maximum speed
				PWMLER	= (1<<1);					// update PWMMR1 
			
			  IO0PIN &=~(1<<4);  // Buzzer is on(active low)
			  IO0PIN |=(1<<3);	// Red LED is on while Green and Yellow LEDs are off
			
			 while(1){
				 
				 t=ADC0_Read()*Volts_To_Temp;		// t is always updated with any change in temp.
				 
			if (((IO0PIN>>5)&0x01)&& (t<40)) 	// only when current temp is <40 and a push button is pressed then 
				
			{
				delay(100);											// for button debounce
																				//turn red LED and buzzer off then break from the loop and proceed normally 
				IO0PIN&=~(1<<3);								//at the current temp.
				IO0PIN |=(1<<4);
				
				break;
			}
							}
		
		
		}
  }
 } 