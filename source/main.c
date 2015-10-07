#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "display.h"
// #include "temperature.h"

// manipulated by SysTick_Handler
uint32_t ticks = 0;
uint32_t cnt = 0;
/*!
	Contains the code execution loop
 */
int main()
{
	// temperature_setup();
	//display_setup();
	led_setup();
	printf("hello world");
	SysTick_Config(SystemCoreClock / 50);
	while(1)
	{
		while (!ticks);
		ticks = 0;
		if (cnt++ % 100 == 0)
		{
			blink_leds();
		}
	}
	return 0;
}

void SysTick_Handler()
{
	ticks = 1;
}
