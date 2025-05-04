#ifndef TEMPERATURE_H
#define TEMPERATURE_H

void init_temperature_sensor(void);
float read_temperature(void);
void update_temperature(void);
extern volatile float current_temperature;

#endif
