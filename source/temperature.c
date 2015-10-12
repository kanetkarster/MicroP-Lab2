#include <stdio.h>
#include "stm32f4xx.h"                  					// Device header
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include <stdint.h>

#include "temperature.h"

#define BUFF_SIZE 30


typedef struct{
	float buffer[BUFF_SIZE];
	int replace;
	float avg;
	float sum;
}FilterBuffer;

FilterBuffer new_filter;


float out_mid;

int voltage_to_celcius(uint16_t voltage, float* ouput);
int filter(FilterBuffer *inout, float temp);

int temperature_setup() 
{
	ADC_InitTypeDef adc_init_s;														//Initializes definitions of SDC
	ADC_CommonInitTypeDef adc_common_init_s;							//Used to def common paramters for ADC peripheral
	
	ADC_DeInit();																					//reset ADC peripheral value to their defaults
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//Enable Power for APB2 bus connected to ADC1 (temp sensor)

	adc_common_init_s.ADC_Mode = ADC_Mode_Independent; 		//Configures the ADC for indepedent mode
	adc_common_init_s.ADC_Prescaler = ADC_Prescaler_Div2; //Sets Frequency of the clock to ADC. Count 0 and 1.
	adc_common_init_s.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //turn off direct memory access mode
	adc_common_init_s.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //sets the delay between two sampling phases as 5
	
	ADC_CommonInit(&adc_common_init_s);										//initializes the struct for values set (above)
	
	adc_init_s.ADC_Resolution = ADC_Resolution_12b;				//Configures the ADC resolution 12 bits
	adc_init_s.ADC_ScanConvMode = DISABLE;								//sets conversion to Single channel mode
	adc_init_s.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //Set the external trigger edge to none
	adc_init_s.ADC_DataAlign = ADC_DataAlign_Right;				//MSB in register is 0, data saved starting from LSB
	adc_init_s.ADC_NbrOfConversion = 1; 									//Specifies the number of ADC conversions that will be done
	
	ADC_TempSensorVrefintCmd(ENABLE);											//wake up desired sensor (temp)
	ADC_Cmd(ADC1, ENABLE);																//turn on the ADC1 peripheral
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_480Cycles);	//Configures ADC1_channel 16 which is the tempature sensor
	//ADC_RegularChannelConfig(ADC1, , 1, ADC_SampleTime_480Cycles);
	ADC_Init(ADC1, &adc_init_s);													//initialize ADC1
	

	new_filter.avg = 0, new_filter.replace = 0, new_filter.sum = 0;
	
	return 0;
}

float get_temperature()
{
	
	
	ADC_SoftwareStartConv(ADC1);													//start conversion of temp
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	//Wait for converion to finish
	float out_temp;
	uint16_t temp_mV = ADC_GetConversionValue(ADC1);	//Returns the last ADC1 converted value
	int c = voltage_to_celcius(temp_mV, &out_temp);
	int s = filter(&new_filter, out_temp);
	return new_filter.avg;
}

/*!
	Converts a voltage to Degrees Celcius
	@param voltage input voltage, from temperature sensor
	@param temp output temperature in Celcius
	@return 0 if successful, -1 on failure
 */
int voltage_to_celcius(uint16_t voltage, float* output)
{
	//printf("voltage = %hu\n", voltage);
//	//scaling factor .732 ~ 760/1038
//	float scaling_f = .732f; 	//mV/mV
//	printf("scaling_f = %f\n", scaling_f);
//	float	V_25 = 760.0f;					//mV
//	printf("V_25 = %f\n", V_25);
//	float avg_slope	 = 2.5f;		//mV/degC
//	printf("avg_slope = %f\n", avg_slope);
//	float val = (scaling_f*(float)(voltage) - V_25)/avg_slope + 25.0f;
//	printf("val = %f\n", val);
	
	float max = 4095.0f;
	//printf("max = %f\n", max);
	float val2 = ((float)(voltage)/max) *3.0f;
	//printf("val2 = %f\n", val2);
	out_mid = (val2*1000.0f - 760.0f)/2.5f + 25.0f;
	
	*output = out_mid;
	//printf("%f\t", *(output));

	return 0;
}

/*!
	Filters temperature reading for noise
	@TODO
 */
int filter(FilterBuffer *inout, float temp)
{
	inout->sum -= inout->buffer[inout->replace % BUFF_SIZE];
	inout->sum += (inout->buffer[inout->replace % BUFF_SIZE] = temp);
	inout->avg = inout->replace++ < BUFF_SIZE 
											? inout->sum/inout->replace 
											: inout->sum/BUFF_SIZE;
	return 0;
}

