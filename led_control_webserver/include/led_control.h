// include/led_control.h

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#define LED_BLUE_PIN 12
#define LED_GREEN_PIN 11
#define LED_RED_PIN 13

void process_led_command(const char *request);
void init_leds(void);

#endif // LED_CONTROL_H
