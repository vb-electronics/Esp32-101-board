# 1 "c:\\Users\\KolevBM\\Documents\\Arduino\\BLE_client_test\\BLE_client_test.ino"

extern "C"{
# 4 "c:\\Users\\KolevBM\\Documents\\Arduino\\BLE_client_test\\BLE_client_test.ino" 2
# 5 "c:\\Users\\KolevBM\\Documents\\Arduino\\BLE_client_test\\BLE_client_test.ino" 2

}
esp_err_t ret;
esp_adc_cal_characteristics_t structADC;

void setup(){

  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &structADC);

  ret = adc1_config_width(ADC_WIDTH_BIT_12);
  ret = adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);



}
void loop(){

  int raw = adc1_get_raw(ADC1_CHANNEL_0);
  int voltage = esp_adc_cal_raw_to_voltage(raw, &structADC);
  Serial.printf("voltage is:{1}" + voltage);
  delay(1000);
}
