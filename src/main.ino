/*
 * definitions.h
 *
 *  Created on: 18 de set de 2019
 *      Author: Felipe
 */

#include "Arduino.h"
#include "definitions.h"

void heart_beating(){
	static unsigned long long int millis_heart_beating = 0;

	if(driver_state == 1){
	if (millis()-millis_heart_beating >= DELAY_HEART_BEATING){
			millis_heart_beating = millis();
			digitalWrite(PIN_HEART_BEATING, !digitalRead(PIN_HEART_BEATING));
		}
	}else if(driver_state == 0) digitalWrite(PIN_HEART_BEATING, HIGH);
}

void setup() {
	pinMode(PIN_HEART_BEATING, OUTPUT);

	init_buttons();
	init_debouncer();
	init_controller();
	init_lcd_display();


}

void loop() {
	change_screen();
}
