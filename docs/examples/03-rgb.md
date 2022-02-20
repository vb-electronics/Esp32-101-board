=== "Примерен код"
    ``` c++
    /*
    В този пример червения, зеления и синия светодиод се превключват последователно.
    
    Трите светодиода (LED-R, LED-G и LED-B) са свързани съответно към пинове D4, D2 и D25.
    */

    // константи, описващи използваните пинове
    const int LEDR_pin = 4;
    const int LEDG_pin = 2;
    const int LEDB_pin = 25;

    void setup() {
    // настройване на пиновете на светодиодите като "изходи"
    pinMode(LEDR_pin, OUTPUT);
    pinMode(LEDG_pin, OUTPUT);
    pinMode(LEDB_pin, OUTPUT);
    }

    void loop() {
    digitalWrite(LEDR_pin, HIGH);   // включване на червения светодиод
    delay(1000);                    // изчакване 1 секунда
    digitalWrite(LEDR_pin, LOW);    // изключване на червения светодиод
    delay(1000);                    // изчакване 1 секунда

    digitalWrite(LEDG_pin, HIGH);   // включване на зеления светодиод
    delay(1000);                    // изчакване 1 секунда
    digitalWrite(LEDG_pin, LOW);    // изключване на зеления светодиод
    delay(1000);                    // изчакване 1 секунда

    digitalWrite(LEDB_pin, HIGH);   // включване на синия светодиод
    delay(1000);                    // изчакване 1 секунда
    digitalWrite(LEDB_pin, LOW);    // изключване на синия светодиод
    delay(1000);                    // изчакване 1 секунда
    }

    ```
=== "Принципна схема на свързване"