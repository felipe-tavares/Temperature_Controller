/*
 * definitions.h
 *
 *  Created on: 19 de set de 2019
 *      Author: Felipe
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/* TELAS */
#define MAIN	    0
#define SETPOINT    1
#define GAINH	    2
#define GAINF	    3
#define MANUAL_MODE 4
#define HEAT 	    5
#define FAN		    6
#define DRIVER	    7

/* PINS */
#define LM35  	  		  A0
#define P		  		  8
#define UP		  		  9
#define DOWN	  		  10
#define SET		  		  13
#define IN1		  		  5
#define IN2		   		  6
#define ENABLE	  		  7
#define PIN_HEART_BEATING A1

/* DELAY */
#define DELAY_HEART_BEATING 200

/* External Variables */
extern float current_temperature;
extern float setpoint;
extern float gainH;
extern float gainF;
extern bool manual_mode;
extern int heat_pwm_manual;
extern int heat_pwm_manual_in;
extern int fan_pwm_manual;
extern int fan_pwm_manual_in;
extern int heat_state;
extern int heat_state_manual;
extern int fan_state;
extern int fan_state_manual;
extern int driver_state;
extern int screen;
extern int inh;
extern int inf;

/* LCD HANDLER */
void init_lcd_display();
void main_screen();
void setpoint_screen_function();
void gainH_screen_function();
void gainF_screen_fucntion();
void manual_mode_screen_function();
void heat_screen_function();
void fan_screen_function();
void driver_screen_function();
void change_screen();

/* BUTTONS HANDLER */
void init_buttons();
void init_debouncer();
void update_buttons();
bool p_button();
bool set_button();
bool up_button();
bool down_button();

/* BUTTONS EVENTS HANDLERS */
void heat_state_manual_config_function();
void heat_pwm_manual_config_function();
void fan_state_manual_config_function();
void fan_pwm_manual_config_function();
void driver_state_config_function();
void gainH_config_function();
void gainF_config_function();
void manual_mode_config_function();

/* CONTROLLER */
extern void init_controller();
void controller();
void controller_manual();
void driver_read_state();

// LM35 handler
extern float get_LM35_temperature();

//HEART BEAT FUNCTION
extern void heart_beating();

#endif /* DEFINITIONS_H_ */
