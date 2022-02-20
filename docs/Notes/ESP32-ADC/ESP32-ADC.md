# Use of ADCs in ESP32 Arduino core

Main information is from official [docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html#adc-channels)

## attenuation of Measured input voltage 

Vref is the reference voltage used internally by ESP32 ADCs for measuring the input voltage. The ESP32 ADCs can measure analog voltages from 0 V to Vref. Among different chips, the Vref varies, the median is 1.1 V. In order to convert voltages larger than Vref, input voltages can be attenuated before being input to the ADCs. 

The median of Vref is 1.1 V with 0 db attenuation(gain), most of the chips comes with factory calibrated ADC_cal values

to check the  Vref of your Chip

 verify if eFuse Vref is present by running the espefuse.py tool with adc_info parameter
in CMD:
```
~/esptool_py/esptool/espefuse.py --port "PORTNAME" adc_info
```
example return:
```
ADC VRef calibration: 1093 mV
```

There are 4 available attenuation options, the higher the attenuation is, the higher the measurable input voltage could be.
 You can change the attenuation (negative gain) of input voltage  with `analogSetAttenuation(val)`  

 ADC_ATTEN_DB_0 = 1 x Vref

 ADC_ATTEN_DB_2_5 = 1.33 x Vref

 ADC_ATTEN_DB_6 = 1.99 x Vref

 ADC_ATTEN_DB_11 = 3.54 x Vref

There is an online converter [Decibels to Voltage Gain/Loss](http://www.sengpielaudio.com/calculator-gainloss.htm)

## default values for ADC config

    default ADC resolution = 12 bit
    default Attenuation - 11 db

## Code functions

For full available code functions check the core library:

`C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.4\cores\esp32\esp32-hal-adc.c`

`C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.4\cores\esp32\esp32-hal-adc.h`

Here are listed sopme of tha basics functions:

`analogReadResolution(resolution)`: set the sample bits and resolution. It can be a value between 9 (0 – 511) and 12 bits (0 – 4095). Default is 12-bit resolution.

`analogSetWidth(width)`: set the sample bits and resolution. It can be a value between 9 (0 – 511) and 12 bits (0 – 4095). Default is 12-bit resolution.

`analogSetCycles(cycles)`: set the number of cycles per sample. Default is 8. Range: 1 to 255.

`analogSetSamples(samples)`: set the number of samples in the range. Default is 1 sample. It has an effect of increasing sensitivity.

`analogSetClockDiv(attenuation)`: set the divider for the ADC clock. Default is 1. Range: 1 to 255.

`analogSetAttenuation(attenuation)`: sets the input attenuation for all ADC pins. Default is ADC_11db. Accepted values:
```
ADC_0db: sets no attenuation. ADC can measure up to approximately 800 mV (1V input = ADC reading of 1088).

ADC_2_5db: The input voltage of ADC will be attenuated, extending the range of measurement to up to approx. 1100 mV. (1V input = ADC reading of 3722).

ADC_6db: The input voltage of ADC will be attenuated, extending the range of measurement to up to approx. 1350 mV. (1V input = ADC reading of 3033).

ADC_11db: The input voltage of ADC will be attenuated, extending the range of measurement to up to approx. 2600 mV. (1V input = ADC reading of 1575).
```
`analogSetPinAttenuation(pin, attenuation)`: sets the input attenuation for the specified pin. The default is ADC_11db. Attenuation values are the same from previous function.

`adcAttachPin(pin)`: Attach a pin to ADC (also clears any other analog mode that could be on). Returns TRUE or FALSE result.

`adcStart(pin)`, `adcBusy(pin)` and `resultadcEnd(pin)`: starts an ADC convertion on attached pin’s bus. Check if conversion on the pin’s ADC bus is currently running (returns TRUE or FALSE). Get the result of the conversion: returns 16-bit integer.
