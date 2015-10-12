// display.h

/*!
	Sets up the PWM using system calls. 
 */
int display_setup(void);

/*!
	Uses the servo to move dial on thermometer
	
	@param temperature temperature to dispaly
	
	@return 0 on success, -1 on failure
 */
 int show_temperature(float temperature);

/*!
	rotates through the four LEDS, while the temperature is too high
	
	@return 1 if alarm went off, else 0
 */
uint32_t blink_leds(void);
