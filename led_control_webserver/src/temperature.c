// src/temperature.c

#include "temperature.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

volatile float current_temperature = 0.0f;

void init_temperature_sensor(void) {
    adc_init();
    adc_set_temp_sensor_enabled(true);
}

void update_temperature(void) {
    adc_select_input(4);
    uint16_t raw = adc_read();
    const float conv = 3.3f / (1 << 12);
    current_temperature = 27.0f - ((raw * conv - 0.706f) / 0.001721f);
}
