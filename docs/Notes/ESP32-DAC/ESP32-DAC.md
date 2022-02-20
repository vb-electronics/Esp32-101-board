# ESP32-DAC
*****
## DAC Digital-Analog-Convertor

available on **GPIO25** and **GPIO26** 

### Difference beteween DAC and PWM

ESP32 has two 8-bit DAC (digital to analog converter) channels, connected to GPIO25 (Channel 1) and GPIO26 (Channel 2).

The DAC driver allows these channels to be set to arbitrary voltages.

The DAC channels can also be driven with DMA-style written sample data by the digital controller, via the I2S driver when using the “built-in DAC mode”.

****
## arduino ESP32 core

Voltage reference from the VDD3P3_RTC pin wich is typicaly 3.3V

Setting DAC channel 1 (GPIO25) voltage to approx 0.78 of `VDD3P3_RTC` voltage (VDD * 200 / 255). For `VDD3P3_RTC` 3.3V, this is 2.59V:

$$
Vout = 3.3*(desired 8 bit value/ 255)
$$


```c
dacWrite(uint8_t pin, uint8_t value)
```
`pin `= **GPIO25** or **GPIO26**

`value` = 0-255

```arduino

void setup(){
    pinMode(25,ANALOG);
}
void loop(){
    dacWrite(25,116);
 
}
```