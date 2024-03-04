#include "hdc1080.h"

const uint8_t REG_HDC1080_TEMPERATURE       = 0x00;
const uint8_t REG_HDC1080_HUMIDITY          = 0x01;
const uint8_t REG_HDC1080_CONFIGURATION     = 0x02;
const uint8_t REG_HDC1080_MANUFACTURER_ID   = 0xFE;
const uint8_t REG_HDC1080_DEVICE_ID         = 0xFF;
const uint8_t REG_HDC1080_SERIAL_ID_FIRST   = 0xFB;
const uint8_t REG_HDC1080_SERIAL_ID_MID     = 0xFC;
const uint8_t REG_HDC1080_SERIAL_ID_LAST    = 0xFD;

const int DEFAULT_CONFIG               = 0x0000;

const struct i2c_dt_spec *_i2c_sensor_spec;

int hdc1080_begin(const struct i2c_dt_spec *i2c_sensor_spec, int config)
{
    _i2c_sensor_spec = i2c_sensor_spec;
    uint8_t write_buf[3];
    write_buf[0] = REG_HDC1080_CONFIGURATION;

    if (config == -1)
    {
        write_buf[1] = (uint8_t)(DEFAULT_CONFIG >> 8);
        write_buf[2] = (uint8_t)(DEFAULT_CONFIG & 0xFF);
    }
    else if (config > 0x0000 || config <= 0xFE00)
    {
        write_buf[1] = (uint8_t)(config >> 8);
        write_buf[2] = (uint8_t)(config & 0xFF);
    }
    else
    {
        printk("Invalid configuration, check HDC1080 documentation.");
        return -1;
    }
        
    printk("Configuration to write: 0x%02X%02X\n", write_buf[1], write_buf[2]);
    
    return i2c_write_dt(_i2c_sensor_spec, write_buf, sizeof(write_buf));

}

int hdc1080_read_id(int *pointer)
{
    uint16_t raw_data;
    int ret;
    ret = i2c_write_read_dt(_i2c_sensor_spec, &REG_HDC1080_DEVICE_ID, 1, &raw_data, 2);
    raw_data = ((raw_data << 8) & 0xff00) | ((raw_data >> 8) & 0x00ff);
    *pointer =  raw_data;
    return ret;
}

int read_data(uint8_t *reg_pointer, uint16_t *raw_data)
{
    uint8_t rawBytes[2] = {0};
    int ret;
    i2c_write_dt(_i2c_sensor_spec, reg_pointer, 1);
    k_msleep(10);
    ret = i2c_read_dt(_i2c_sensor_spec, rawBytes, 2);
    *raw_data = (rawBytes[0] << 8) | rawBytes[1];
    return ret;
}

int hdc1080_read_temperature(float *pointer)
{
    uint16_t raw_data;
    int ret;
    ret = read_data(&REG_HDC1080_TEMPERATURE, &raw_data);
    *pointer = ((raw_data/65536.0)*165)-40;
    return ret;
}

int hdc1080_read_humidity(int *pointer)
{
    uint16_t raw_data;
    int ret;
    ret = read_data(&REG_HDC1080_HUMIDITY, &raw_data);
    *pointer = (raw_data/65536.0)*100;
    return ret;
}

int hdc1080_read_serial(uint16_t *pointer)
{
    uint16_t raw_data[3] = {0};
    int ret[3];
    ret[0] = read_data(&REG_HDC1080_SERIAL_ID_LAST, &raw_data[0]);
    ret[1] = read_data(&REG_HDC1080_SERIAL_ID_MID, &raw_data[1]);
    ret[2] = read_data(&REG_HDC1080_SERIAL_ID_FIRST, &raw_data[2]);
    memcpy(pointer, raw_data, sizeof(raw_data));
    return ret[0] || ret[1] || ret[2];
}