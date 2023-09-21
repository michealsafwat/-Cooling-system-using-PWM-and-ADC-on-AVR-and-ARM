/*
 * MACROS_ADC_PWM.c
 *
 * Created: 9/19/2021 1:53:38 AM
 *  Author: Micheal
 */ 

#include "MACROS_ADC_PWM.h"

void InitADC()			// ADC initialization function
{
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaler to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}


uint16_t ReadADC(uint8_t ADCchannel)			// function that returns converted data
{
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}