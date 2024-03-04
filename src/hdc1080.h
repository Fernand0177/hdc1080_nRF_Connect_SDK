#ifndef _CLOSEDCUBE_HDC1080_h

#define _CLOSEDCUBE_HDC1080_h

#include <zephyr/drivers/i2c.h>

extern const uint8_t REG_HDC1080_TEMPERATURE;
extern const uint8_t REG_HDC1080_HUMIDITY;
extern const uint8_t REG_HDC1080_CONFIGURATION;
extern const uint8_t REG_HDC1080_MANUFACTURER_ID;
extern const uint8_t REG_HDC1080_DEVICE_ID;
extern const uint8_t REG_HDC1080_SERIAL_ID_FIRST;
extern const uint8_t REG_HDC1080_SERIAL_ID_MID;
extern const uint8_t REG_HDC1080_SERIAL_ID_LAST;

extern const int DEFAULT_CONFIG;

extern const struct i2c_dt_spec *_i2c_sensor_spec;

int hdc1080_begin(const struct i2c_dt_spec *i2c_sensor_spec, int config);
int read_data(uint8_t *reg_pointer, uint16_t *raw_data);
int hdc1080_read_id(int *pointer);
int hdc1080_read_temperature(float *pointer);
int hdc1080_read_humidity(int *pointer);
int hdc1080_read_serial(uint16_t *pointer);


#endif