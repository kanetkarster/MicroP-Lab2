#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "display.h"
#include "temperature.h"

#define _EMERGENCY_TEMP 50

// Convert Clock Cycles to time
#define US_TO_CLOCK_TICKS 28ul // 6 clock cyles in each cycle of the loop and 28*6 == 168
#define MS_TO_CLOCK_TICKS US_TO_CLOCK_TICKS*1000ul

// Parameters for Motor Movement
#define ZERO_DEGREES 700.0f
#define MAX_DEGREES 2900.0f
#define DELTA MAX_DEGREES-ZERO_DEGREES

uint32_t cnt = 0;
uint16_t PINS[4] = {GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15};
/*!
	Sets up the PWM using system calls. 
 */
int display_setup() 
{
	GPIO_InitTypeDef gpio_init_s; // Structure to initilize definitions of GPIO
	GPIO_StructInit(&gpio_init_s); // Fills each GPIO_InitStruct member with its default value

	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE); // Provides power for motor
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
	// figure out how long to keep pulse high
	if (temperature > 60) temperature = 60.0f;
	if (temperature < 20) temperature = 20.0f;
	int delay = ZERO_DEGREES + (int)(((DELTA) / 40.0f) * (temperature - 20));
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	// keep on for delay ms
	for (int i=0; i <delay*US_TO_CLOCK_TICKS; i++);	// wait for delay ms
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	return 0;
}

/*!
	rotates through the four LEDS, while the temperature is too high
	
	@return 1 if alarm went off, else 0
 */
uint32_t blink_leds()
{
		if(get_temperature() > _EMERGENCY_TEMP) {
			// led on
			GPIO_SetBits(GPIOD, PINS[cnt%4]);
			// keep led on for .1 sec
			for(uint32_t i=0; i < 100*MS_TO_CLOCK_TICKS; i++);	// wait 100 ms
			// led off
			GPIO_ResetBits(GPIOD, PINS[cnt%4]);
			cnt++;
			return 1;
		}
		return 0;
}
