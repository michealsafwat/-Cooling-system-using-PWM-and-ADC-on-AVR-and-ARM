/*
 * MACROS_ADC_PWM.h
 *
 * Created: 9/19/2021 1:53:19 AM
 *  Author: Micheal
 */ 


#ifndef MACROS_ADC_PWM_H_
#define MACROS_ADC_PWM_H_

#include <avr/io.h>
#include <util/delay.h>

#define MINIMUM_SPEED			((30*255)/100)
#define MAXIMUM_SPEED			(255)
#define SPEED					((2*255)/100)
#define Volts_To_Temp			(0.49)			// ((Vref*100)/1024) equals approx. 0.49, Vref here is 5V

void InitADC();									// ADC initialization function
uint16_t ReadADC(uint8_t ADCchannel);			// function that returns converted data






#endif /* MACROS_ADC_PWM_H_ */