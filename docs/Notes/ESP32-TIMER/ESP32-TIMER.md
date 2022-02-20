# Hardware Timers in esp32

The ESP32 chip contains two hardware timer groups. Each group has two general-purpose hardware timers. They are all 64-bit generic timers based on 16-bit pre-scalers and 64-bit up / down counters which are capable of being auto-reloaded.
 - 2 groups x 2 hw timers = 4 timers (0-3)
 - 16 bit prescaler
 - typically the frequency of the base signal used by the ESP32 counters is **80 MHz** (this is true for the FireBeetle board)   **80 000 000 times per second**
   - using a **prescaler of 80** will lead to **1 000 000 times per second**  
     - each microsecond the counter will go up




## simple watchdog timer



``` c
extern "C"{
    #include "esp_system.h"
}
const int button = 0;         //gpio to use to trigger delay
const int wdtTimeout = 3000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;

void ARDUINO_ISR_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("running setup");

  pinMode(button, INPUT_PULLUP);                    //init control pin
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt
}

void loop() {
  Serial.println("running main loop");

  timerWrite(timer, 0); //reset timer (feed watchdog)
  long loopTime = millis();
  //while button is pressed, delay up to 3 seconds to trigger the timer
  while (!digitalRead(button)) {
    Serial.println("button pressed");
    delay(500);
  }
  delay(1000); //simulate work
  loopTime = millis() - loopTime;
  
  Serial.print("loop time is = ");
  Serial.println(loopTime); //should be under 3000
}

```

##  not so simple repeat timer


****
we will need to declare a variable of type portMUX_TYPE, which we will use to take care of the synchronization between the main loop and the ISR, when modifying a shared variable.

`portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;`

`volatile int interruptCounter;` the shared variable

*when changing the value of shared variable we use **spinlock macros***

```c
portENTER_CRITICAL(&timerMux);
interruptCounter--;
portEXIT_CRITICAL(&timerMux);
```

###  basic initialization usage
 
 1. initialize timer 
    -  initialize our timer with a call to the `timerBegin` function, which will return a pointer to a structure of type hw_timer_t, which is the one of the timer global variable we declared in the previous section.
     ```c
    hw_timer_t * timerBegin(uint8_t num, uint16_t divider, bool countUp)
    ```
    - As input, this function receives the number of the timer we want to use (from 0 to 3, since we have 4 hardware timers), the value of the prescaler and a flag indicating if the counter should count up (true) or down (false).

2. attatch ISR
    - bind it to a handling function
    ```c
    void timerAttachInterrupt(hw_timer_t *timer, void (*fn)(void), bool edge)
    ```
    - This function receives as input **a pointer** to the initialized timer, which we stored in our global variable, the **address of the function** that will handle the interrupt and **a flag** indicating if the interrupt to be generated is edge (true) or level (false)
3.  specify the counter value in which the timer interrupt will be generated
    ```c
    void timerAlarmWrite(hw_timer_t *timer, uint64_t alarm_value, bool autoreload)
    ```
    -  this function receives as **first** input the pointer to the timer, as **second** the value of the counter in which the interrupt should be generated, and as **third** a flag indicating if the timer should automatically reload upon generating the interrupt.
 
    - Regarding the second argument, remember that we set the prescaler in order for this to mean the number of microseconds after which the interrupt should occur. So, for this example, we assume that we want to generate an interrupt each second, and thus we pass the value of 1 000 000 microseconds, which is equal to 1 second. 
    
        Important: Take in consideration that this value is specified in microseconds only if we specify the value 80 for the prescaler. We can use different prescaler values and in that case we need to do the calculations to know when the counter will reach a certain value.

4. enable the timer
   - We finish our setup function by enabling the timer with a call to the timerAlarmEnable function, passing as input our timer variable.
   ```c
   void timerAlarmEnable(hw_timer_t *timer)
   ```
***example setup***
```c
void setup() {
 
  Serial.begin(115200);
 
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
 
}
```

###  ISR

The interrupt handling routine should have the IRAM_ATTR attribute, in order for the compiler to place the code in IRAM. Also, interrupt handling routines should only call functions also placed in IRAM

As usual, since this counter **variable will be shared amongst the main loop and the ISR**, then it needs to be **declared with** the `volatile` keyword, **which avoids it being removed due to compiler optimizations**.

```c
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
```  

# Resources

- <https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/>

- [polling spinlock vs semaphore](https://www.geeksforgeeks.org/difference-between-spinlock-and-semaphore/)


- <https://techtutorialsx.com/2021/08/07/esp32-ticker-library/> 

# USE <Ticker.h>

- builtin library in Arduino core `Timer.h`
 - limitations:
   - count seconds or milliseconds, no microseconds  
 - useful for simple tasks
 - no ISR needed
 - no volatile ect.

```c
#include <Arduino.h>
#include <Ticker.h>

// attach a LED to GPIO 21
#define LED_PIN 2

Ticker tickerSetHigh;
Ticker tickerSetLow;

void setPin(int state) {
  digitalWrite(LED_PIN, state);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(1, LOW);
  
  // every 25 ms, call setPin(0) 
  tickerSetLow.attach(5, setPin, 0);
  
  // every 26 ms, call setPin(1)
  tickerSetHigh.attach(6, setPin, 1);
}

void loop() {

}
```