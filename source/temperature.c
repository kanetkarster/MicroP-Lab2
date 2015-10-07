#include "temperature.h"

float get_temperature(int HIGH)
{
	if (HIGH == 1) {
		return 30.0f;
	}
	return 70.0f;
}