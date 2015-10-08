#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "display.h"
#include "temperature.h"

#define _EMERGENCY_TEMP 60
#define MS_TO_CLOCK_TICKS 50*1000


/*!
	Sets up the PWM using system calls. 
 */
int display_setup() 
{
	GPIO_InitTypeDef gpio_init_s; // Structure to initilize definitions of GPIO
	GPIO_StructInit(&gpio_init_s); // Fills each GPIO_InitStruct member with its default value

	//RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE); // Provides power for motor
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOD, ENABLE); // Provides power for LEDs

	gpio_init_s.GPIO_Mode = GPIO_Mode_OUT; 			// Set as Output
	gpio_init_s.GPIO_Speed = GPIO_Speed_100MHz; // Don't limit slew rate, allow values to change as fast as they are set
	gpio_init_s.GPIO_OType = GPIO_OType_PP;			// Operating output type (push-pull) for selected pins
	gpio_init_s.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// If there is no input, don't pull.

	gpio_init_s.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; // select the 4 GPIO Pins for LEDs
	GPIO_Init(GPIOD, &gpio_init_s); 						// Initializes the  LEDs
	
	gpio_init_s.GPIO_Pin = GPIO_Pin_1; // Initializes motor pin
	GPIO_Init(GPIOB, &gpio_init_s); // Initializes the Motor
	return 0;
}

/*!
	Uses the servo to move dial on thermometer
	
	@param temperature temperature to dispaly
	
	@return 0 on success, -1 on failure
 */
int show_temperature(float temperature) 
{
	return 0;
}

/*!
	
 */
uint32_t blink_leds()
{
	uint32_t cnt = 0;
	while (1)
	{
		if(get_temperature(0) > _EMERGENCY_TEMP) {
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			for(int i=0; i < 120*MS_TO_CLOCK_TICKS; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			cnt++;
		}
		else return cnt;
		
		if(get_temperature(0) > _EMERGENCY_TEMP) {
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			for(int i=0; i < 120*MS_TO_CLOCK_TICKS; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			cnt++;
		}
		else return cnt;
		
		if(get_temperature(0) > _EMERGENCY_TEMP) {
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			for(int i=0; i < 120*MS_TO_CLOCK_TICKS; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			cnt++;
		}
		else return cnt;
		
		if(get_temperature(0) > _EMERGENCY_TEMP) {
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			for(int i=0; i < 120*MS_TO_CLOCK_TICKS; i++);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			cnt++;
		}
		else return cnt;
	}
}
