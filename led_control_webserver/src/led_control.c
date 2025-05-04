// src/led_control.c

#include "pico/stdlib.h"
#include "led_control.h"
#include <string.h>

void process_led_command(const char *request) {
    if (strstr(request, "GET /blue_on")) gpio_put(LED_BLUE_PIN, 1);
    else if (strstr(request, "GET /blue_off")) gpio_put(LED_BLUE_PIN, 0);
    else if (strstr(request, "GET /green_on")) gpio_put(LED_GREEN_PIN, 1);
    else if (strstr(request, "GET /green_off")) gpio_put(LED_GREEN_PIN, 0);
    else if (strstr(request, "GET /red_on")) gpio_put(LED_RED_PIN, 1);
    else if (strstr(request, "GET /red_off")) gpio_put(LED_RED_PIN, 0);
}

void init_leds(void) {
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_put(LED_BLUE_PIN, 0);

    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_put(LED_GREEN_PIN, 0);

    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_put(LED_RED_PIN, 0);
}
