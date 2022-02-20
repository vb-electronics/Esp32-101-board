
=== "Примерен код"
    ```c++
    /*
    В този пример посокота на въртене на ротационния енкодер и състоянието на бутона му
    се показват на серийния монитор (Tools -> Serial Monitor).
    
    Двата сигнала за посока и бутона (ENC-A, ENC-B и ENC-SW) са свързани съответно към пинове D13, D14 и D12.
    Използва се допълнителната библиотека "ESP32Encoder" на "madhephaestus",
    която трябва да се инсталира предварително (https://github.com/madhephaestus/ESP32Encoder/)
    */

    // включване на допълнителната библиотека за четене на ротационен енкодер
    #include <ESP32Encoder.h>

    // константи, описващи използваните пинове
    const int ENC_A_pin = 13;
    const int ENC_B_pin = 14;
    const int ENC_SW_pin = 12;

    // променливи, използвани при четенето
    ESP32Encoder encoder;
    int encoderCount;
    int ENC_SW_state;

    void setup() {
    // настройване на пина на бутона като "вход"
    pinMode(ENC_SW_pin, INPUT_PULLUP);
    
    // настройване на енкодерната библиотека
    //encoder.attachFullQuad(ENC_A_pin, ENC_B_pin);
    //encoder.attachHalfQuad(ENC_A_pin, ENC_B_pin);
    encoder.attachSingleEdge(ENC_A_pin, ENC_B_pin);
    encoder.clearCount();

    // настройване на серийната комуникация
    // Забележка: в серийният монитор трябва да бъда избрана същата скорост
    Serial.begin(115200);
    }

    void loop() {
    // прочитане на състоянието на бутона (0/LOW при натиснат, 1/HIGH при отпуснат):
    ENC_SW_state = digitalRead(ENC_SW_pin);

    // прочитане на състоянието на енкодера
    encoderCount = encoder.getCount();

    // показване на стойностите на серийния монитор
    Serial.print("SWITCH= ");
    Serial.print(ENC_SW_state);
    Serial.print("\t\t");

    Serial.print("COUNT= ");
    Serial.print(encoderCount);
    Serial.println("\t\t");

    delay(100);
    }

    ```
=== "Принципна схема на свързване"
    ![schematic]()