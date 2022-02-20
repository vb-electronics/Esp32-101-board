
#include "C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.2\cores\esp32\esp32-hal-timer.h"
#include "Arduino.h"

volatile int interruptCounter;
int totalInterruptCounter;
 
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
 
}
 
void setup() {
 
  Serial.begin(115200);
 
  timer = timerBegin(0, 80, true);   //from 0 to 3, since we have 4 hardware timers)
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
 
}
 
void loop() {
 
  if (interruptCounter > 0) {
 
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;
 
    Serial.print("An interrupt as occurred. Total number: ");
    Serial.println(totalInterruptCounter);
 
  }
}

/*
#include <Arduino.h>
#include "C:\Users\KolevBM\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.2\libraries\Ticker\src\Ticker.h"

// attach a LED to GPIO 21
#define LED_PIN 2

Ticker blinker;
Ticker toggler;
Ticker changer;
float blinkerPace = 0.1;  //seconds
const float togglePeriod = 5; //seconds

void change() {
  blinkerPace = 0.5;
}

void blink() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void toggle() {
  static bool isBlinking = false;
  if (isBlinking) {
    blinker.detach();
    isBlinking = false;
  }
  else {
    blinker.attach(blinkerPace, blink);
    isBlinking = true;
  }
  digitalWrite(LED_PIN, LOW);  //make sure LED on on after toggling (pin LOW = led ON)
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  toggler.attach(togglePeriod, toggle);
  changer.once(30, change);
}

void loop() {
  
}

*/