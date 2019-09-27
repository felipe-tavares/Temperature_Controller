/*
 * lm35_handler.cpp
 *
 *  Created on: 19 de set de 2019
 *      Author: Felipe
 */

#include <Arduino.h>
#include "definitions.h"

float current_temperature;

float get_LM35_temperature() {
	//int LM35_digital_read = analogRead(LM35);
	float auxSum = 0;

	// 1ºC = 10mV
	// 1023 - 5V
	// 0 - 0V
	// current_temp = (LM35_digital_read*5.0/1023)/0.01;
	//temperatura_atual = (LM35_digital_read*5.0/1023)/0.1;

	auxSum = 0;
	for (int i = 0; i < 100; i++) {
		auxSum += (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
	}
	auxSum = (auxSum / 100);
	current_temperature = auxSum;

	return current_temperature;

}
