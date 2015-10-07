// temperature.h

float get_temperature(int HIGH);

/*!
	Sets up the Temperature Sensor and ADC using system calls.
	
	It is connected to Pin ADC1_IN16
 */
int temperature_setup(void);

/*!
	Filters temperature reading for noise
	TODO
 */
int filter(void);

/*!
	Converts a voltage to Degrees Celcius
	@param voltage input voltage, from temperature sensor
	@param temp output temperature in Celcius
	@return 0 if successful, -1 on failure
 */
int voltage_to_celcius(float voltage, float* ouput);
