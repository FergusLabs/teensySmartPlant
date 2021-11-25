/*
 * Project teensySoilTest
 * Description:
 * Author:
 * Date:
 */

int moisture;
unsigned long checkTime;

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  pinMode(A2,INPUT);
  Serial.begin();


}

void loop() {
  if ((millis()-checkTime)>1000) {
    moisture = analogRead(A2);
    Serial.printf("moisture = %i\n",moisture);
    checkTime = millis();
  }
}