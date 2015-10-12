#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include <stdint.h>
#include "temperature.h"

uint32_t ticks = 0;
/*!
	Contains the code execution loop
 */
int main(){
	SysTick_Config(SystemCoreClock / 10000 );
	temperature_setup();
	int next = 0;
	while(1){
		while(!ticks);
		ticks = 0;
		fprintf(stdout,"%f,%f,,\n", out_mid, get_temperature());
		next++;
	}
	
	return 0;
}


void SysTick_Handler()
{
	ticks = 1;
}
