#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
#include <stdint.h>

#include "temperature.h"

/*!
	Contains the code execution loop
 */
 int main(){
	temperature_setup();
	while(1){
		printf("temp = %f\n", get_temperature());
	}
	
	return 0;
}
