/*!
	Sets up the PWM using system calls. 
 */
int display_setup();

/*!
	Uses the servo to move dial on thermometer
	
	@param temperature temperature to dispaly
	
	@return 0 on success, -1 on failure
 */
 int show_temperature(float temperature);
 