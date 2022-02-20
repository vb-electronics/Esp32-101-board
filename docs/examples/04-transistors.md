=== "Примерен код"
    ``` c++
    /*
    В този пример червения, зеления и синия светодиод се димират последователно.
    
    Трите светодиода (LED-R, LED-G и LED-B) са свързани съответно към пинове D4, D2 и D25.
    */

    // константи, описващи използваните пинове
    const int LEDR_pin = 4;
    const int LEDG_pin = 2;
    const int LEDB_pin = 25;

    // константи, описващи използваните PWM канали
    const int LEDR_ch = 0;
    const int LEDG_ch = 1;
    const int LEDB_ch = 2;

    void setup() {
    // настройване на PWM каналите, използване за димиране на светодиодите:
    ledcSetup(LEDR_ch, 5000, 8);      // канал 0, честота 5 kHz, 8 бита (0-255)
    ledcSetup(LEDG_ch, 5000, 8);      // канал 1, честота 5 kHz, 8 бита (0-255)
    ledcSetup(LEDB_ch, 5000, 8);      // канал 2, честота 5 kHz, 8 бита (0-255)

    // свързване на каналите към светодиодните пинове:
    ledcAttachPin(LEDR_pin, LEDR_ch); // червен светодиод към канал 0
    ledcAttachPin(LEDG_pin, LEDG_ch); // зелен светодиод към канал 1
    ledcAttachPin(LEDB_pin, LEDB_ch); // син светодиод към канал 2
    }

    void loop() {
    // увеличаване на яркостта на червения светодиод
    for(int dc = 0; dc <= 255; dc++){   
        ledcWrite(LEDR_ch, dc);
        delay(15);
    }

    // намаляване на яркостта на червения светодиод
    for(int dc = 255; dc >= 0; dc--){
        ledcWrite(LEDR_ch, dc);
        delay(15);
    }


    // увеличаване на яркостта на зеления светодиод
    for(int dc = 0; dc <= 255; dc++){   
        ledcWrite(LEDG_ch, dc);
        delay(15);
    }

    // намаляване на яркостта на зеления светодиод
    for(int dc = 255; dc >= 0; dc--){
        ledcWrite(LEDG_ch, dc);
        delay(15);
    }


    // увеличаване на яркостта на синия светодиод
    for(int dc = 0; dc <= 255; dc++){   
        ledcWrite(LEDB_ch, dc);
        delay(15);
    }

    // намаляване на яркостта на синия светодиод
    for(int dc = 255; dc >= 0; dc--){
        ledcWrite(LEDB_ch, dc);
        delay(15);
    }
    }

    ```

=== "Принципна схема на свързване"