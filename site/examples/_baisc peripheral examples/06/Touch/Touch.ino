/*
  В този пример стойностите на сензорите за допир TS1, TS2, TS3
  се показват на серийния монитор (Tools -> Serial Monitor).
  
  Трите сензора за допир (TS1, TS2 и TS3) са свързани съответно към пинове D27, D33 и D32.
*/

// константи, описващи използваните пинове
const int TS1_pin = 27;
const int TS2_pin = 33;
const int TS3_pin = 32;

// променливи, използвани при четенето на сензорите
int TS1_value;
int TS2_value;
int TS3_value;

void setup() {
  // настройване на серийната комуникация
  // Забележка: в серийният монитор трябва да бъда избрана същата скорост
  Serial.begin(115200);
}

void loop() {
  // прочитане на стойностите на сензорите:
  TS1_value = touchRead(TS1_pin);
  TS2_value = touchRead(TS2_pin);
  TS3_value = touchRead(TS3_pin);

  // показване на стойностите на серийния монитор
  // (стойността намалява при допир)
  Serial.print("TS1= ");
  Serial.print(TS1_value);
  Serial.print("\t\t");

  Serial.print("TS2= ");
  Serial.print(TS2_value);
  Serial.print("\t\t");

  Serial.print("TS3= ");
  Serial.print(TS3_value);
  Serial.println("\t\t");

  delay(100);
}
