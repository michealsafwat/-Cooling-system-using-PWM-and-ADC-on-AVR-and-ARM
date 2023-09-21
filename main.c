/*
 * GccApplication1.c
 *
 * Created: 9/16/2021 8:21:56 PM
 * Author : Micheal
 */ 


#include "MACROS_ADC_PWM.h"

int main(void)
{
	int temp,t;
	DDRB=0x0f;			// initialize the first 4 pins of port B as output and the fifth as input
	DDRD|=(1<<6);			
	
	InitADC();
	
	
	  while (1)
 {
		  
		  temp=ReadADC(0)*Volts_To_Temp;
		
		// the following is the setup of timer0 to use PWM in order to control the speeds of the motor
		
		
		//settings for timer0
		TCCR0A|=(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);		/* select mode of operation to be Fast PWM 
														and clear OC0A and OC0B on compare match, set OC0A and OC0B at BOTTOM, (non-inverting mode).*/	
		
		TCCR0B|=(1<<CS00)|(1<<CS02);					// select prescaler to be 1024
		
		if(temp<20){
					
			PORTB=0x09;			// Green LED on and buzzer is off (active low)
			OCR0A=0;			// don't operate the motor
		}
		
		else if(temp==20){
			PORTB=0x0A;				// Yellow LED on and buzzer is off (active low)
			OCR0A=MINIMUM_SPEED;		// operate the motor with minimum speed
		}
		
		else if (20<temp && temp<40){
			PORTB=0x0A;					// Yellow LED on and buzzer is off (active low)
			OCR0A=temp*SPEED;			//operate the motor with a speed proportional to the current temp, so the speed gradually increases
		}
		
		else if (temp>=40)
		{	
			 PORTB=0x04;               // Red LED on and buzzer is on (active low)
			 OCR0A=MAXIMUM_SPEED;		// operate the motor with maximum speed
			
			 while(1){
				 
				  t=ReadADC(0)*Volts_To_Temp;		//variable t is always updated with the current temp
				  
			if (((PINB&0x80)==0x80) && (t<40))		// only when both a button is pressed and temp is <40, turn the red LED and the buzzer off
			{
				_delay_ms(100);						// for button debounce
				
				PORTB=0x08;
				break;								// break of the loop and operate normally at the current temp.
			}
					}
		
		
		}

 }
}