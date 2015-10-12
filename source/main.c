#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include <stdint.h>

#include "display.h"
#include "temperature.h"

// manipulated by SysTick_Handler
uint32_t ticks = 0;

/*!
	Contains the code execution loop
 */
int main()
{
	float temp;
	
	// setup
	temperature_setup();
	display_setup();
	SysTick_Config(SystemCoreClock / 50);
	
	// super loop
	while(1)
	{
		while (!ticks);
		ticks = 0;
		temp = get_temperature();
		printf("%f\n", temp);
		show_temperature(temp);
		blink_leds();
	}
}

void SysTick_Handler()
{
	ticks = 1;
}
