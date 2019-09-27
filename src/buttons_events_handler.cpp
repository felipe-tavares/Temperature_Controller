/*
 * buttons_events_handler.cpp
 *
 *  Created on: 21 de set de 2019
 *      Author: Felipe
 */

#include <Arduino.h>
#include "definitions.h"


void heat_state_manual_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button() && fan_state_manual == 0 && fan_state == 0)
		heat_state_manual = 1; //UP turn on the heat
	//BUTTON DOWN
	if (down_button()){
		heat_state_manual = 0; //DOWN turn off the heat
		heat_state = 0;
	}
}

void heat_pwm_manual_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button()) {
		if (heat_pwm_manual < 100)
			heat_pwm_manual += 5; //UP increases pwm
	}
	//BUTTON DOWN
	if (down_button()) {
		if (heat_pwm_manual > 0)
			heat_pwm_manual -= 5; //DOWN decreases pwm
	}
}

void fan_state_manual_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button() && heat_state_manual == 0 && heat_state == 0)
		fan_state_manual = 1; //UP turn on the fan
	//BUTTON DOWN
	if (down_button()){
		fan_state_manual = 0; //DOWN turn off the fan
		fan_state=0;
	}
}


void fan_pwm_manual_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button()) {
		if (fan_pwm_manual < 100)
			fan_pwm_manual += 5; //UP increases pwm
	}
	//BUTTON DOWN
	if (down_button()) {
		if (fan_pwm_manual > 0)
			fan_pwm_manual -= -5; //DOWN decreases pwm
	}
}

void driver_state_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button())
		driver_state = 1; //UP turn on the drive
	//BUTTON DOWN
	if (down_button())
		driver_state = 0; //DOWN turn off the drive
}

void gainH_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button())
		gainH += 1; //UP increases gainH
	//BUTTON DOWN
	if (down_button() && gainH > 0)
		gainH -= 1; //DOWN decreases gainH
}

void gainF_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button())
		gainF += 1; //UP increases gainF
	//BUTTON DOWN
	if (down_button() && gainF > 0)
		gainF -= 1; //DOWN decreases gainF
}

void manual_mode_config_function() {
	update_buttons();
	//BUTTON UP
	if (up_button() && manual_mode == false){
		manual_mode = true; //UP turn on manual_mode
	}
	//BUTTON DOWN
	if (down_button() && manual_mode == true){
		manual_mode = false; //DOWN turn off manual_mode
		heat_state_manual = 0;
		fan_state_manual = 0;
	}

}

