

extern "C"{
    #include "C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.2\cores\esp32\esp32-hal-adc.h"
    #include "C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.2\cores\esp32\esp32-hal.h"
}

int val = 0;
void setup() {
  Serial.begin(9600);
    }

void loop() {
  // put your main code here, to run repeatedly:
  val = hallRead();
  // print the results to the serial monitor:
  //Serial.print("sensor = ");
  Serial.println(val);//to graph 
  delay(200);
}
