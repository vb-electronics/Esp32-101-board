#include <Arduino.h>
#line 1 "c:\\Users\\KolevBM\\Documents\\Arduino\\BLE_client_test\\BLE_client_test.ino"

extern "C"{
  #include "C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.4\tools\sdk\include\driver\driver\adc.h"
  #include "C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.4\tools\sdk\include\esp_adc_cal\esp_adc_cal.h"
  
}
esp_err_t ret;
esp_adc_cal_characteristics_t structADC;

void setup(){
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_11db, ADC_WIDTH_12Bit, 0, &structADC);
  
  ret = adc1_config_width(ADC_WIDTH_BIT_12);
  ret = adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);

  

}
void loop(){

  int raw =  adc1_get_raw(ADC1_CHANNEL_0);
  int voltage = esp_adc_cal_raw_to_voltage(raw, &structADC);
  Serial.printf("voltage is:{1}" + voltage);
  delay(1000);
}
