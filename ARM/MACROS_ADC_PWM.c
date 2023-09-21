/*
 * MACROS_ADC_PWM.c
 *
 * Created: 9/18/2021 5:13:32 AM
 *  Author: Micheal
 */ 


#include "MACROS_ADC_PWM.h"


void ADC0_Init(void)
{
	/*************Initialize ADC AD0.0*************/
	AD0CR = 1<<21;								//A/D is Operational
	AD0CR = 0<<21;								//A/D is in Power Down Mode
	PCONP = (PCONP &0x001817BE) | (1UL<<12);		// power the ADC peripheral
	PINSEL1 = 0x00400000;					//P0.27 is Configured as Analog to Digital Converter Pin AD0.0
	
	AD0CR = 0x00200401;						//operate with 10 bits / 11 clocks,Channel-0.0 Selected,A/D is Operational
	
	/**********************************************/
}



unsigned int ADC0_Read(void)
{
	unsigned long adc_data;
	
		AD0CR |= 1<<24;							//Start Conversion
	
		do
	{
		adc_data = AD0GDR;
	}while(!(adc_data & 0x80000000));			//Wait until the DONE bit is Set

	
	AD0CR &= ~0x01000000;					//Stops the A/D Conversion   
	
	adc_data = (adc_data >> 6) & 0x3FF;			//Extract the 10 bits of data by shifting and Clearing all other Bits
	   
return (adc_data);
}
/*********************************************/


void pwm_init(void)	
{
	
	PINSEL0 = (1<<1); 	// Select PWM1 on P0.0 
	PWMPR	= 512;
	/*
		PWMPR = (PWMPR+1)/(PCLK*10^6)
		Taking PCLk = 60 (60 MHz)
	*/
	PWMMR0	= 256;	// 1 sec time period
	PWMMCR 	= (1<<1);		// Reset PWMTC on PWMMR0 match
	PWMLER	= (1<<0);	// update PWMMR0 and PWMMR1
	PWMPCR	= (1<<9);	// Enable PWM output
	PWMTCR 	= (1<<1);	// Reset PWM TC and PR
	PWMTCR  = (1<<0)|(1<<3);		// Enable counter's and PWM mode  

}
//******************************************************

// delay function
void delay(int x)
{
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<1000;j++);
}
