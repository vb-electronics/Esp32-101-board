=== "Примерен код"
    ```c++
    /*
    В този пример стойностите на осите на джойстика и състоянието на бутона му
    се показват на серийния монитор (Tools -> Serial Monitor).
    
    Ос X, ос Y и бутона (JOY-X, JOY-Y и JOY-SW) са свързани съответно към пинове D39, D36 и D23.
    */

    // константи, описващи използваните пинове
    const int JOY_X_pin = 39;
    const int JOY_Y_pin = 36;
    const int JOY_SW_pin = 23;

    // променливи, използвани при четенето на осите и бутона
    int JOY_X_value;
    int JOY_Y_value;
    int JOY_SW_state;

    void setup() {
    // настройване на пина на бутона като "вход"
    pinMode(JOY_SW_pin, INPUT_PULLUP);
    
    // настройване на серийната комуникация
    // Забележка: в серийният монитор трябва да бъда избрана същата скорост
    Serial.begin(115200);
    }

    void loop() {  
    // прочитане на стойностите на осите (между 0 и 4095):
    JOY_X_value = analogRead(JOY_X_pin);
    JOY_Y_value = analogRead(JOY_Y_pin);

    // прочитане на състоянието на бутона (0 при натиснат, 1 при отпуснат):
    JOY_SW_state = digitalRead(JOY_SW_pin);

    // показване на стойностите на серийния монитор:
    Serial.print("X= ");
    Serial.print(JOY_X_value);
    Serial.print("\t\t");

    Serial.print("Y= ");
    Serial.print(JOY_Y_value);
    Serial.print("\t\t");

    Serial.print("SW= ");
    Serial.print(JOY_SW_state);
    Serial.println("\t\t");

    delay(100);
    }
        
    ```

=== "Принципна схема на свързване"
    ![schematic]()