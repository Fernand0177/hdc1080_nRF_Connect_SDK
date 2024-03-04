# Print sensor data example
A simple example of how to read all the registers from the hdc1080 I2C sensor and print it to the serial monitor.
---
### Notes
Check the **prj.conf** file to configure it according to your board, this example uses a custom board, and the following configurations were added just for it:
- CONFIG_CLOCK_CONTROL_NRF_K32SRC_RC=y
  - Works with the internal RC oscillator due to this board doesn't have an external crystal. 
- CONFIG_BOARD_ENABLE_DCDC=n
    - Works with the internal LDO regulator, doesn't have an external LC filter.

