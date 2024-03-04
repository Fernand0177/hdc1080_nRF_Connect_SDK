# Print sensor data example
A simple example of how to read all the registers from the hdc1080 I2C sensor and print it to the serial monitor.
---
### Notes
Check the **prj.conf** file to configure it according to your board, this example uses a custom board, and the following configurations were added just for it:
- CONFIG_CLOCK_CONTROL_NRF_K32SRC_RC=y
  - Works with the internal RC oscillator due to this board doesn't have an external crystal. 
- CONFIG_BOARD_ENABLE_DCDC=n
    - Works with the internal LDO regulator, doesn't have an external LC filter.
 
## Pinout

- SDA: P0.25
- SCL: P0.26

![image](https://github.com/Fernand0177/hdc1080_nRF_Connect_SDK/assets/68255428/24f3a1cc-4ae5-45dc-9848-d10fe1f2ed33)

