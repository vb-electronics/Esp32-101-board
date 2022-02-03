/** 
 * LEDC Test / example arduino ESP32 CORE
 * 
 * **/ 
const int ledPin = 2;
const uint8_t channel = 8;
const double freq = 10000; 
const uint8_t pwmResolution = 12;

void setup(){
    ledcSetup(channel,freq,pwmResolution);
    ledcAttachPin(ledPin,channel);
    Serial.begin(9600);
}
void loop(){

    for (int i = 0; i < 4095; i++)
    {
        ledcWrite(channel,i);
        delay(1);
    }
    delay(1000);
    for (int i = 4095; i > 0; i--)
    {
        ledcWrite(channel,i);
        delay(1);
      
    }
    delay(1000);
    
   
  
}