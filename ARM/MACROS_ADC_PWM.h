/*
 * MACROS_ADC_PWM.h
 *
 * Created: 9/11/2021 5:11:00 AM
 *  Author: Micheal
 */ 


#ifndef MACROS_ADC_PWM_H_
#define MACROS_ADC_PWM_H_

#include <LPC213X.h>
#include <stdint.h>


#define Volts_To_Temp							0.325					// ((Vref*100)/1024) equals approx. 0.325 , Vref here is 3.3V
#define MINIMUM_SPEED							80
#define MAXIMUM_SPEED							255
#define SPEED											5

void ADC0_Init(void);         	 // ADC0 initiallization function
unsigned int ADC0_Read(void);		// This function returns the data converted from analog to digital
void pwm_init(void);								//PWM initiallization function
void delay(int x);							// A delay function



#endif /* MACROS_ADC_PWM_H_ */
