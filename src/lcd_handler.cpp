/*
 * lcd_handler.cpp
 *
 *  Created on: 19 de set de 2019
 *      Author: Felipe
 */

#include "Arduino.h"
#include "definitions.h"
#include <LiquidCrystal.h>
#include <Bounce2.h>

LiquidCrystal lcd(12, 11, 4, 3, 2, 1);

int screen = MAIN;
bool manual_mode = false;

void init_lcd_display() {
	//Define o número de colunas e linhas do LCD
	lcd.begin(16, 2);
}

//MAIN SCREEN
void main_screen() {
	lcd.clear();

	while (screen == MAIN) {
		heart_beating();
		update_buttons();

		lcd.setCursor(0, 0);
		lcd.print("SP: ");
		delay(100);
		lcd.print(setpoint, 1);

		get_LM35_temperature();

		lcd.setCursor(0, 1);
		lcd.print("PV: ");
		lcd.print(current_temperature, 1);

		driver_read_state();
		if(manual_mode == true){ controller_manual();
		}else if (manual_mode == false) controller();

		if (driver_state == 0) {
			lcd.setCursor(10, 0);
			lcd.print("Driver");
			lcd.setCursor(12, 1);
			lcd.print("OFF");
		} else if (driver_state == 1 && heat_state == 0 && fan_state == 0 && fan_state_manual == 0 && heat_state_manual == 0) {
			lcd.setCursor(10, 0);
			lcd.print("Driver");
			lcd.setCursor(12, 1);
			lcd.print("ON ");
		}

		if ((driver_state == 1 && heat_state == 1 && fan_state == 0) || heat_state_manual == 1) { //if heat on print "Heat ON"
			lcd.setCursor(12, 0);
			lcd.print("Heat");
			lcd.setCursor(12, 1);
			lcd.print("ON ");

		} else if ((driver_state == 1 && fan_state == 1 && heat_state == 0) || fan_state_manual == 1) { //if fan on print "Fan ON"
			lcd.setCursor(12, 0);
			lcd.print("Fan ");
			lcd.setCursor(12, 1);
			lcd.print("ON ");
		}

		if (p_button())
			screen = SETPOINT; //if P button pressed change to SETPOINT screen

	}
}

//SETPOINT SCREEN
void setpoint_screen_function() {
	lcd.clear();
	int config_mode = 0;

	while (screen == SETPOINT) {
		heart_beating();
		update_buttons();

		lcd.setCursor(0, 0);
		lcd.print("New Set Point");
		lcd.setCursor(0, 1);
		lcd.print("SP: ");
		lcd.print(setpoint, 1);

		if (set_button()) {
			config_mode = 1;

			lcd.setCursor(8, 1);
			lcd.print("<");

			while (config_mode == 1) {
				update_buttons();
				//BUTTON UP
				if (up_button())
					setpoint += 1; //UP increases setpoint
				//BUTTON DOWN
				if (down_button())
					setpoint -= 1; //DOWN decreases setpoint

				lcd.setCursor(0, 1);
				lcd.print("SP: ");
				lcd.print(setpoint, 1);

				//BUTTON SET
				if (set_button()) { //set confirm changes
					lcd.setCursor(8, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}

		}

		if (p_button())
			screen = GAINH; //if P button pressed change to gainH screen
	}
}

//HEAT GAIN SCREEN
void gainH_screen_function() {
	int config_mode = 0;
	lcd.clear();

	while (screen == GAINH) {
		heart_beating();
		update_buttons();

		lcd.setCursor(0, 0);
		lcd.print("New Prop. Gain H");
		lcd.setCursor(0, 1);
		lcd.print("Kp: ");
		lcd.print(gainH, 1);

		if (set_button()) {
			config_mode = 1;

			while (config_mode == 1) {
				gainH_config_function();

				lcd.setCursor(8, 1);
				lcd.print("<");
				lcd.setCursor(4, 1);
				lcd.print(gainH, 1);

				//BUTTON SET
				if (set_button()) { //set confirm changes
					lcd.setCursor(8, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}
		}

		if (p_button())
			screen = GAINF; //if P button pressed change to gainF screen

	}
}

//FAN GAIN SCREEN
void gainF_screen_function() {
	lcd.clear();
	int config_mode = 0;

	while (screen == GAINF) {
		heart_beating();
		update_buttons();

		lcd.setCursor(0, 0);
		lcd.print("New Prop. Gain F");
		lcd.setCursor(0, 1);
		lcd.print("Kp: ");
		lcd.print(gainF, 1);

		if (set_button()) {
			config_mode = 1;

			while (config_mode == 1) {
				gainF_config_function();

				lcd.setCursor(8, 1);
				lcd.print("<");
				lcd.setCursor(4, 1);
				lcd.print(gainF, 1);

				//BUTTON SET
				if (set_button()) { //set confirm changes
					lcd.setCursor(8, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}
		}

		if (p_button())
			screen = MANUAL_MODE; //if P button pressed change to HEAT screen

	}
}

//MANUAL MODE SET SCREEN
void manual_mode_screen_function() {
	lcd.clear();
	int config_mode = 0;

	while (screen == MANUAL_MODE) {
		heart_beating();
		update_buttons();

		driver_read_state();
				if(manual_mode == true){ controller_manual();
				}else if (manual_mode == false) controller();

		lcd.setCursor(2, 0);
		lcd.print("Manual Mode");
		if (manual_mode == true) {
			lcd.setCursor(7, 1);
			lcd.print("ON ");
		} else if (manual_mode == 0) {
			lcd.setCursor(7, 1);
			lcd.print("OFF");
		}

		if (set_button()) {
			config_mode = 1;

			lcd.setCursor(10, 1);
			lcd.print("<");

			while (config_mode == 1) {
				manual_mode_config_function();

				if (manual_mode == 1) {
					lcd.setCursor(7, 1);
					lcd.print("ON ");
				} else if (manual_mode == 0) {
					lcd.setCursor(7, 1);
					lcd.print("OFF");
				}

				//BUTTON SET
				if (set_button()) { //set confirm changes
					lcd.setCursor(10, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}

		}

		if (manual_mode == true) {
			if (p_button())
				screen = HEAT; //if P button pressed with manual_mode ON change to HEAT screen
		} else if (manual_mode == false) {
			if (p_button())
				screen = DRIVER; //if P button pressed with manual_mode OFF change to DRIVER screen
		}
	}

}

//HEAT SCREEN MANUAL FUNCTION
void heat_screen_function() {
	lcd.clear();
	int config_mode = 0;

	while (screen == HEAT) {
		heart_beating();
		update_buttons();

		lcd.setCursor(2, 0);
		lcd.print("Manual Mode");
		lcd.setCursor(0, 1);
		lcd.print("Heat: ");
		if (heat_state_manual == 1) {
			lcd.setCursor(6, 1);
			lcd.print("ON ");
			lcd.setCursor(11, 1);
			lcd.print(heat_pwm_manual);
			if (heat_pwm_manual == 100) {
				lcd.setCursor(14, 1);
				lcd.print("%");
			} else if (heat_pwm_manual >= 10) {
				lcd.setCursor(13, 1);
				lcd.print("% ");
			} else if (heat_pwm_manual < 10) {
				lcd.setCursor(12, 1);
				lcd.print("%  ");
			}
		} else if (heat_state_manual == 0) {
			lcd.setCursor(6, 1);
			lcd.print("OFF");
			lcd.setCursor(11, 1);
			lcd.print("    ");
		}

		if (set_button()) {
			config_mode = 1;

			lcd.setCursor(9, 1);
			lcd.print("<");

			while (config_mode == 1) {
				heat_state_manual_config_function();

				if (heat_state_manual == 1) {
					lcd.setCursor(6, 1);
					lcd.print("ON ");
				} else if (heat_state_manual == 0) {
					lcd.setCursor(6, 1);
					lcd.print("OFF");
					lcd.setCursor(11, 1);
					lcd.print("    ");
				}

				//BUTTON SET
				if (set_button()) {

					if (heat_state_manual == 1) {
						config_mode = 2;

						while (config_mode == 2) {

							heat_pwm_manual_config_function();

							lcd.setCursor(9, 1);
							lcd.print(">");
							lcd.setCursor(11, 1);
							lcd.print(heat_pwm_manual);
							if (heat_pwm_manual == 100) {
								lcd.setCursor(14, 1);
								lcd.print("%");
							} else if (heat_pwm_manual >= 10) {
								lcd.setCursor(13, 1);
								lcd.print("% ");
							} else if (heat_pwm_manual < 10) {
								lcd.setCursor(12, 1);
								lcd.print("%  ");
							}

							if (set_button()) {
								config_mode = 0;
								lcd.setCursor(9, 1);
								lcd.print(" ");
							}
						}
					}
					if (heat_state_manual == 0) {
						config_mode = 0;
						lcd.setCursor(9, 1);
						lcd.print(" ");
					}
				}
			}
		}

		if (p_button())
			screen = FAN; //if P button pressed change to FAN screen
	}
}

//FAN SCREEN MANUAL FUNCTION
void fan_screen_function() {
	lcd.clear();
	int config_mode = 0;

	while (screen == FAN) {
		heart_beating();
		update_buttons();

		lcd.setCursor(2, 0);
		lcd.print("Manual Mode");
		lcd.setCursor(0, 1);
		lcd.print("Fan: ");
		if (fan_state_manual == 1) {
			lcd.setCursor(5, 1);
			lcd.print("ON ");
			lcd.setCursor(10, 1);
			lcd.print(fan_pwm_manual);
			lcd.setCursor(13, 1);
			if (fan_pwm_manual == 100) {
				lcd.setCursor(13, 1);
				lcd.print("%");
			} else if (fan_pwm_manual >= 10) {
				lcd.setCursor(12, 1);
				lcd.print("% ");
			} else if (fan_pwm_manual < 10) {
				lcd.setCursor(11, 1);
				lcd.print("%  ");
			}
		} else if (fan_state_manual == 0) {
			lcd.setCursor(5, 1);
			lcd.print("OFF");
			lcd.setCursor(10, 1);
			lcd.print("    ");
		}

		if (set_button()) {
			config_mode = 1;

			lcd.setCursor(8, 1);
			lcd.print("<");

			while (config_mode == 1) {
				fan_state_manual_config_function();

				if (fan_state_manual == 1) {
					lcd.setCursor(5, 1);
					lcd.print("ON ");
				} else if (fan_state_manual == 0) {
					lcd.setCursor(5, 1);
					lcd.print("OFF");
					lcd.setCursor(10, 1);
					lcd.print("    ");
				}

				//BUTTON SET
				if (set_button()) {

					if (fan_state_manual == 1) {
						config_mode = 2;

						while (config_mode == 2) {
							fan_pwm_manual_config_function();

							lcd.setCursor(8, 1);
							lcd.print(">");
							lcd.setCursor(10, 1);
							lcd.print(fan_pwm_manual);
							if (fan_pwm_manual == 100) {
								lcd.setCursor(13, 1);
								lcd.print("%");
							} else if (fan_pwm_manual >= 10) {
								lcd.setCursor(12, 1);
								lcd.print("% ");
							} else if (fan_pwm_manual < 10) {
								lcd.setCursor(11, 1);
								lcd.print("%  ");
							}

							if (set_button()) {
								config_mode = 0;
								lcd.setCursor(8, 1);
								lcd.print(" ");
							}
						}
					}
					if (fan_state_manual == 0) {
						config_mode = 0;
						lcd.setCursor(8, 1);
						lcd.print(" ");
					}
				}
			}
		}

		if (p_button())
			screen = DRIVER; //if P button pressed change to DRIVER screen
	}
}

//DRIVER SCREEN MANUAL FUNCTION
void driver_screen_function() {
	int config_mode = 0;
	lcd.clear();

	while (screen == DRIVER) {
		update_buttons();

		lcd.setCursor(2, 0);
		lcd.print("Driver Status");
		if (driver_state == 1) {
			lcd.setCursor(4, 1);
			lcd.print("Enabled ");
		} else if (driver_state == 0) {
			lcd.setCursor(4, 1);
			lcd.print("Disabled");
		}

		if (set_button()) {
			config_mode = 1;

			while (config_mode == 1) {
				driver_state_config_function();

				lcd.setCursor(12, 1);
				lcd.print("<");
				if (driver_state == 1) {
					lcd.setCursor(4, 1);
					lcd.print("Enabled ");
				} else if (driver_state == 0) {
					lcd.setCursor(4, 1);
					lcd.print("Disabled");
				}

				//BUTTON SET
				if (set_button()) { //set confirm changes
					lcd.setCursor(12, 1);
					lcd.print(" ");
					config_mode = 0;
				}
			}
		}

		if (p_button())
			screen = MAIN; //if P button pressed change to MAIN screen
	}
}

void change_screen() {
	switch (screen) {
	case MAIN:
		main_screen();
		break;

	case SETPOINT:
		setpoint_screen_function();
		break;

	case GAINH:
		gainH_screen_function();
		break;

	case GAINF:
		gainF_screen_function();
		break;

	case MANUAL_MODE:
		manual_mode_screen_function();
		break;

	case HEAT:
		heat_screen_function();
		break;

	case FAN:
		fan_screen_function();
		break;

	case DRIVER:
		driver_screen_function();
		break;
	}

}

