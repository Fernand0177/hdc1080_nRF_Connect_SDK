#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include "hdc1080.h"


#define I2C0_HDC1080 DT_NODELABEL(hdc1080)

float hdc1080_temperature;
int hdc1080_humidity;
uint16_t hdc1080_serial_number[3];
uint16_t hdc1080_id;

int main(void)
{
    int ret;
    static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_HDC1080);
    if (!device_is_ready(dev_i2c.bus)) {
        printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
        return -1;
    }

    if (hdc1080_begin(&dev_i2c, -1) != 0)
    {
        printk("HDC1080 sensor couldn't be initialize\n");
        return -1;
    }
    k_msleep(20);
    while(true)
    {
        hdc1080_read_temperature(&hdc1080_temperature);
        hdc1080_read_humidity(&hdc1080_humidity);
        hdc1080_read_serial(&hdc1080_serial_number);
        hdc1080_read_id(&hdc1080_id);

        printk("Temperature: %.2f\n", hdc1080_temperature);
        printk("Humidity: %d\n", hdc1080_humidity);
        printk("Serial: ");
        for (size_t i = 0; i < sizeof(hdc1080_serial_number)/sizeof(hdc1080_serial_number[0]); i++)
        {
            printk("%x", hdc1080_serial_number[i]);
        }
        printk("\n");
        printk("Sensor ID: %X\n\n", hdc1080_id);
        k_msleep(1000);
    }

    return 0;
}
