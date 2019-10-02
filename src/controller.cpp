/*
 * controller.cpp
 *
 *  Created on: 19 de set de 2019
 *      Author: Felipe
 */

#include <Arduino.h>
#include "definitions.h"

float setpoint;
float gainH = 20.0;
float gainF = 20.0;
int heat_pwm_manual;
int heat_pwm_manual_in;
int heat_state_manual;
int fan_pwm_manual;
int fan_pwm_manual_in;
int fan_state_manual;
int inh = 0;
int inf = 0;
int heat_state = 0;
int fan_state = 0;
int driver_state = 1;

void init_controller() {
	setpoint = 23.0;

	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(ENABLE, OUTPUT);

	analogWrite(IN1, 0);
	analogWrite(IN2, 0);
	digitalWrite(ENABLE, driver_state);
}

void controller() {

	inh = (setpoint - current_temperature) * gainH;
	if (inh >= 150)
		inh = 150; //3.3V

	inf = (setpoint + current_temperature) * gainF;
	if (inf >= 255)
		inh = 255;
	else if (inf <= 56)
		inf = 56; //2.6V

	if ((current_temperature < setpoint) && driver_state == 1
			&& manual_mode == false) {
		heat_state = 1;
		fan_state = 0;
		analogWrite(IN1, inh);
		analogWrite(IN2, 0);
	} else if ((current_temperature > setpoint) && driver_state == 1
			&& manual_mode == false) {
		heat_state = 0;
		fan_state = 1;
		analogWrite(IN2, inf);
		analogWrite(IN1, 0);
	}
}

void controller_manual(){
	if(driver_state == 1 && fan_state_manual == 0 && heat_state_manual == 0 && manual_mode == true){
				heat_state = 0;
				fan_state = 0;
				analogWrite(IN1, 0);
				analogWrite(IN2, 0);
	}else if (driver_state == 1 && heat_state_manual == 1 && manual_mode == true) {
			heat_state = 1;
			fan_state = 0;
			heat_pwm_manual_in = map(heat_pwm_manual, 0, 100, 0, 70);
			analogWrite(IN1, heat_pwm_manual);
			analogWrite(IN2, 0);

		} else 	if (driver_state == 1 && fan_state_manual == 1 && manual_mode == true) {
			heat_state = 0;
			fan_state = 1;
			fan_pwm_manual_in = map(fan_pwm_manual, 0, 100, 56, 255);
			analogWrite(IN2, (fan_pwm_manual * 255) / 100);
			analogWrite(IN1, 0);
		}
}
void driver_read_state() {
	digitalWrite(ENABLE, driver_state);
}
