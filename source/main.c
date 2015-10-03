#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"

#include "display.h"
#include "temperature.h"

/*!
	Contains the code execution loop
 */
int main(){
	temperature_setup();
	display_setup();
	while(1){
	}
	
	return 0;
}
